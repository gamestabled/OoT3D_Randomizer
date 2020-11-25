#include "playthrough.hpp"
#include "item_list.hpp"
#include "item_location.hpp"
#include "location_access.hpp"
#include "logic.hpp"
#include "random.hpp"
#include "spoiler_log.hpp"
#include "../code/src/item_override.h"

#include <set>
#include <cstdio>
#include <algorithm>
#include <3ds.h>
#include <string>
#include <unistd.h>
#include <stdio.h>

template <typename T, typename Predicate>
void erase_if(std::vector<T>& vector, Predicate pred) {
    vector.erase(std::remove_if(begin(vector), end(vector), pred), end(vector));
}

namespace Playthrough {

    static u32 totalLocationsFound = 0;
    static u32 totalItemsPlaced = 0;
    static u64 accessibleLocationIterations = 0;
    static std::vector<ItemLocation *> AccessibleLocationPool;

    static void PlaceItemInLocation(Item* item, ItemLocation* loc, std::set<ItemOverride, ItemOverride_Compare>& overrides, bool applyEffectImmediately = true) {
        // put item in the override table
        ItemOverride override;
        override.key.all = 0;

        override.value.all = 0;
        override.key = loc->key();
        override.value = item->value();

        overrides.insert(override);

        PlacementLog_Msg("\n");
        PlacementLog_Msg(item->name);
        PlacementLog_Msg(" placed at ");
        PlacementLog_Msg(loc->name);
        PlacementLog_Msg("\n\n");

        if (applyEffectImmediately) {
          item->applyEffect();
          loc->use();
        }

        loc->placedItem = *item;
        totalItemsPlaced++;
        printf("\x1b[2;20HPlacing Items...");
        if (Settings::Logic == LOGIC_GLITCHLESS) {
          printf("\x1b[3;25H%lu/%d", totalLocationsFound, allLocations.size() + dungeonRewardLocations.size());
        }

    }

    template <typename Container>
    static void RandomizeDungeonKeys(const Container& KeyRequirements, Item* smallKeyItem, u8 maxKeys, std::set<ItemOverride, ItemOverride_Compare>& overrides) {
      for (size_t i = 0; i < maxKeys; i++) {
        std::vector<ItemLocation *> dungeonPool;
        for (const ItemLocationKeyPairing& ilkp : KeyRequirements) {
          if (ilkp.keysRequired <= i && ilkp.loc->placedItem.name == "No Item") {
            dungeonPool.push_back(ilkp.loc);
          }
        }
        const u32 locIdx = Random() % dungeonPool.size();
        PlaceItemInLocation(smallKeyItem, dungeonPool[locIdx], overrides, false);
      }
    }

    template <typename Container>
    static void RandomizeDungeonItem(const Container& dungeonLocations, Item* item, std::set<ItemOverride, ItemOverride_Compare>& overrides) {
      std::vector<ItemLocation *> dungeonPool;
      for (const ItemLocationKeyPairing& ilkp : dungeonLocations) {
        if (ilkp.loc->placedItem.name == "No Item") {
          dungeonPool.push_back(ilkp.loc);
        }
      }
      const u32 locIdx = Random() % dungeonPool.size();
      PlaceItemInLocation(item, dungeonPool[locIdx], overrides, false);
    }

    void UpdateToDAccess(Exit* exit, u8 age, ExitPairing::Time ToD) {
      if (ToD == ExitPairing::Time::Day) {
        if (age == AGE_CHILD) {
          exit->dayChild = true;
        }
        if (age == AGE_ADULT) {
          exit->dayAdult = true;
        }
      } else if (ToD == ExitPairing::Time::Night) {
        if (age == AGE_CHILD) {
          exit->nightChild = true;
        }
        if (age == AGE_ADULT) {
          exit->nightAdult = true;
        }
      } else {
        //only update from false -> true, never true -> false
        if (age == AGE_CHILD) {
          exit->dayChild   = Logic::AtDay   || exit->dayChild;
          exit->nightChild = Logic::AtNight || exit->nightChild;
        }
        if (age == AGE_ADULT) {
          exit->dayAdult   = Logic::AtDay   || exit->dayAdult;
          exit->nightAdult = Logic::AtNight || exit->nightAdult;
        }
      }

      //special check for temple of time
      if (Exits::ToT_BeyondDoorOfTime.Child() && !Exits::ToT_BeyondDoorOfTime.Adult()) {
        Exits::Root.dayAdult   = Exits::ToT_BeyondDoorOfTime.dayChild;
        Exits::Root.nightAdult = Exits::ToT_BeyondDoorOfTime.nightChild;
      } else if (!Exits::ToT_BeyondDoorOfTime.Child() && Exits::ToT_BeyondDoorOfTime.Adult()){
        Exits::Root.dayChild   = Exits::ToT_BeyondDoorOfTime.dayAdult;
        Exits::Root.nightChild = Exits::ToT_BeyondDoorOfTime.nightAdult;
      }
    }

    static void AccessibleLocations_Update(std::set<ItemOverride, ItemOverride_Compare>& overrides) {
        bool advancementChange = true;
        while(advancementChange) {
          advancementChange = false;

          for (u32 i = 0; i < Exits::ExitPool.size(); i++) {
            //iterate twice on each area for different ages
            for (u8 age : {AGE_CHILD, AGE_ADULT}) {
              Logic::Age = age;
              Exit *area = Exits::ExitPool[i];

              //Check if the age can access this area and update ToD logic
              if (age == AGE_CHILD) {
                if (area->Child()) {
                  Logic::AtDay   = area->dayChild;
                  Logic::AtNight = area->nightChild;
                } else {
                  continue;
                }

              } else if (age == AGE_ADULT) {
                if (area->Adult()) {
                  Logic::AtDay   = area->dayAdult;
                  Logic::AtNight = area->nightAdult;
                } else {
                  continue;
                }
              }

              Logic::UpdateHelpers();
              area->UpdateEvents();
              area->UpdateAdvancementNeeds();

              //for each exit in this area
              for (u32 j = 0; j < area->exits.size(); j++) {
                ExitPairing exitPair = area->exits[j];
                Exit *exit = exitPair.GetExit();

                if (exitPair.ConditionsMet()) {
                  UpdateToDAccess(exit, age, exitPair.TimeOfDay());

                  //If the exit is accessible, but not in the exit pool, add it
                  if (exit->HasAccess() && !exit->addedToPool) {
                    PlacementLog_Msg("NEW EXIT FOUND: ");
                    PlacementLog_Msg(exit->regionName);
                    PlacementLog_Msg("\n");

                    Exits::ExitPool.push_back(exit);
                    exit->addedToPool = true;
                    advancementChange = true;
                  }
                }
              }

              //for each ItemLocation in this area
              for (u32 k = 0; k < area->locations.size(); k++) {
                ItemLocationPairing locPair = area->locations[k];
                ItemLocation *location = locPair.location;

                if (locPair.ConditionsMet() && !location->addedToPool) {
                  // PlacementLog_Msg("NEW LOCATION FOUND: ");
                  // PlacementLog_Msg(location->name);

                  totalLocationsFound++;
                  location->addedToPool = true;

                  if (location->placedItem.name == "No Item") {
                    PlacementLog_Msg(" | NO ITEM\n");
                    AccessibleLocationPool.push_back(location);
                    if (accessibleLocationIterations > 2) {
                      AccessibleLocationPool.push_back(location); //give the location more weight
                    }
                    Logic::CurAccessibleLocations++;
                  } else {
                    PlacementLog_Msg(" | ITEM HERE\n");
                    location->placedItem.applyEffect();
                    location->use();
                    advancementChange = true;
                  }
                }
              }

              //erase ItemLocationPairings that are placed into the AccessibleLocationPool
              erase_if(area->locations, [](const ItemLocationPairing& ilp){ return ilp.location->isUsed();});

              //erase ExitPairings whose conditions have been met while the exit has full day time access as both ages
              erase_if(area->exits, [](const ExitPairing& ep){ return ep.ConditionsMet() && ep.GetExit()->AllAccess();});
            }
          }
        }
        accessibleLocationIterations++;
        //erase exits from the ExitPool if they can't open up more access to anything
        erase_if(Exits::ExitPool, [](const Exit* exit){return exit->AllAccountedFor();});
    }

    static void AccessibleLocations_Init(std::set<ItemOverride, ItemOverride_Compare>& overrides) {
      //set first access variable based upon settings
      if(Settings::HasNightStart) {
        if(Settings::StartingAge == AGE_CHILD) {
          Exits::Root.nightChild = true;
        } else {
          Exits::Root.nightAdult = true;
        }
      } else {
        if(Settings::StartingAge == AGE_CHILD) {
          Exits::Root.dayChild = true;
        } else {
          Exits::Root.dayAdult = true;
        }
      }

      //glitchless logic or no logic
      if (Settings::Logic == LOGIC_GLITCHLESS) {
        Exits::ExitPool.push_back(&Exits::Root);
      } else if (Settings::Logic == LOGIC_NONE) {
        Exits::ExitPool.clear();
        AccessibleLocationPool.assign(allLocations.begin(), allLocations.end());
      }

      AccessibleLocations_Update(overrides);
      if (Logic::EventsUpdated()) {
        AccessibleLocations_Update(overrides);
      }
    }

    static int PlaceAdvancementItem(std::set<ItemOverride, ItemOverride_Compare>& overrides) {
        if (AdvancementItemPool.empty()) {
            return -1;
        }

        if (AccessibleLocationPool.empty()) {
            return -2;
        }

        unsigned int itemIdx = Random() % AdvancementItemPool.size();
        unsigned int locIdx  = Random() % AccessibleLocationPool.size();

        PlaceItemInLocation(&AdvancementItemPool[itemIdx], AccessibleLocationPool[locIdx], overrides);
        advancementLocations.push_back(AccessibleLocationPool[locIdx]);

        AdvancementItemPool.erase(AdvancementItemPool.begin() + itemIdx);
        //erase locations that have been used
        erase_if<ItemLocation *>(AccessibleLocationPool, [](ItemLocation* il){return il->isUsed();});
        Logic::CurAccessibleLocations--;

        AccessibleLocations_Update(overrides);
        if (Logic::EventsUpdated()) {
          AccessibleLocations_Update(overrides);
        }
        return 1;
    }

    static int PlaceRandomItem(std::set<ItemOverride, ItemOverride_Compare>& overrides) {
        unsigned int itemIdx = Random() % ItemPool.size();
        unsigned int locIdx = Random() % AccessibleLocationPool.size();

        PlaceItemInLocation(&ItemPool[itemIdx], AccessibleLocationPool[locIdx], overrides);

        ItemPool.erase(ItemPool.begin() + itemIdx);
        //erase locations that have been used
        erase_if<ItemLocation *>(AccessibleLocationPool, [](ItemLocation* il){return il->isUsed();});
        Logic::CurAccessibleLocations--;

        AccessibleLocations_Update(overrides);
        if (Logic::EventsUpdated()) {
          AccessibleLocations_Update(overrides);
        }
        return 1;
    }



    //Check for specific preset items in locations
    static void PlaceSetItems(std::set<ItemOverride, ItemOverride_Compare>& overrides) {
      totalItemsPlaced = 0;
      const bool NO_EFFECT = false;

      PlaceItemInLocation(&A_ZeldasLetter,    &HC_ZeldasLetter, overrides, NO_EFFECT);

      PlaceItemInLocation(&A_LightMedallion,  &LinksPocket,     overrides, NO_EFFECT);
      PlaceItemInLocation(&A_KokiriEmerald,   &QueenGohma,      overrides, NO_EFFECT);
      PlaceItemInLocation(&A_GoronRuby,       &KingDodongo,     overrides, NO_EFFECT);
      PlaceItemInLocation(&A_ZoraSaphhire,    &Barinade,        overrides, NO_EFFECT);
      PlaceItemInLocation(&A_ForestMedallion, &PhantomGanon,    overrides, NO_EFFECT);
      PlaceItemInLocation(&A_FireMedallion,   &Volvagia,        overrides, NO_EFFECT);
      PlaceItemInLocation(&A_WaterMedallion,  &Morpha,          overrides, NO_EFFECT);
      PlaceItemInLocation(&A_SpiritMedallion, &Twinrova,        overrides, NO_EFFECT);
      PlaceItemInLocation(&A_ShadowMedallion, &BongoBongo,      overrides, NO_EFFECT);

      if (!Settings::ShuffleKokiriSword)
        PlaceItemInLocation(&A_KokiriSword, &KF_KokiriSwordChest, overrides, NO_EFFECT);

      if (!Settings::ShuffleWeirdEgg)
        PlaceItemInLocation(&A_WeirdEgg, &HC_MalonEgg, overrides, NO_EFFECT);

      if (!Settings::ShuffleGerudoToken)
        PlaceItemInLocation(&A_GerudoToken, &GF_GerudoToken, overrides, NO_EFFECT);

      if (!Settings::ShuffleMagicBeans)
        PlaceItemInLocation(&A_MagicBean, &ZR_MagicBeanSalesman, overrides, NO_EFFECT);

      if (Settings::Skullsanity == TOKENSANITY_VANILLA) {
        //Overworld
        PlaceItemInLocation(&GoldSkulltulaToken, &KF_GS_BeanPatch,                             overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &KF_GS_KnowItAllHouse,                        overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &KF_GS_HouseOfTwins,                          overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &LW_GS_BeanPatchNearBridge,                   overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &LW_GS_BeanPatchNearTheater,                  overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &LW_GS_AboveTheater,                          overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &SFM_GS,                                      overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &HF_GS_NearKakGrotto,                         overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &HF_GS_CowGrotto,                             overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &MK_GS_GuardHouse,                            overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &HC_GS_Tree,                                  overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &HC_GS_StormsGrotto,                          overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &OGC_GS,                                      overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &LLR_GS_Tree,                                 overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &LLR_GS_RainShed,                             overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &LLR_GS_HouseWindow,                          overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &LLR_GS_BackWall,                             overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &Kak_GS_HouseUnderConstruction,               overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &Kak_GS_SkulltulaHouse,                       overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &Kak_GS_GuardsHouse,                          overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &Kak_GS_Tree,                                 overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &Kak_GS_Watchtower,                           overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &Kak_GS_AboveImpasHouse,                      overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &GY_GS_Wall,                                  overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &GY_GS_BeanPatch,                             overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &DMT_GS_BeanPatch,                            overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &DMT_GS_NearKak,                              overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &DMT_GS_FallingRocksPath,                     overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &DMT_GS_AboveDodongosCavern,                  overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &GC_GS_BoulderMaze,                           overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &GC_GS_CenterPlatform,                        overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &DMC_GS_Crate,                                overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &DMC_GS_BeanPatch,                            overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &ZR_GS_Ladder,                                overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &ZR_GS_Tree,                                  overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &ZR_GS_NearRaisedGrottos,                     overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &ZR_GS_AboveBridge,                           overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &ZD_GS_FrozenWaterfall,                       overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &ZF_GS_Tree,                                  overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &ZF_GS_AboveTheLog,                           overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &ZF_GS_HiddenCave,                            overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &LH_GS_BeanPatch,                             overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &LH_GS_LabWall,                               overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &LH_GS_SmallIsland,                           overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &LH_GS_Tree,                                  overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &LH_GS_LabCrate,                              overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &GV_GS_SmallBridge,                           overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &GV_GS_BeanPatch,                             overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &GV_GS_BehindTent,                            overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &GV_GS_Pillar,                                overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &GF_GS_ArcheryRange,                          overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &GF_GS_TopFloor,                              overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &HW_GS,                                       overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &Colossus_GS_BeanPatch,                       overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &Colossus_GS_Tree,                            overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &Colossus_GS_Hill,                            overrides, NO_EFFECT);

        //Dungeons
        PlaceItemInLocation(&GoldSkulltulaToken, &DekuTree_GS_CompassRoom,                     overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &DekuTree_GS_BasementVines,                   overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &DekuTree_GS_BasementGate,                    overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &DekuTree_GS_BasementBackRoom,                overrides, NO_EFFECT);

        PlaceItemInLocation(&GoldSkulltulaToken, &DodongosCavern_GS_SideRoomNearLowerLizalfos, overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &DodongosCavern_GS_VinesAboveStairs,          overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &DodongosCavern_GS_BackRoom,                  overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &DodongosCavern_GS_AlcoveAboveStairs,         overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &DodongosCavern_GS_Scarecrow,                 overrides, NO_EFFECT);

        PlaceItemInLocation(&GoldSkulltulaToken, &JabuJabusBelly_GS_WaterSwitchRoom,           overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &JabuJabusBelly_GS_LobbyBasementLower,        overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &JabuJabusBelly_GS_LobbyBasementUpper,        overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &JabuJabusBelly_GS_NearBoss,                  overrides, NO_EFFECT);

        PlaceItemInLocation(&GoldSkulltulaToken, &ForestTemple_GS_FirstRoom,                   overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &ForestTemple_GS_Lobby,                       overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &ForestTemple_GS_RaisedIslandCourtyard,       overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &ForestTemple_GS_LevelIslandCourtyard,        overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &ForestTemple_GS_Basement,                    overrides, NO_EFFECT);

        PlaceItemInLocation(&GoldSkulltulaToken, &FireTemple_GS_SongOfTimeRoom,                overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &FireTemple_GS_BoulderMaze,                   overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &FireTemple_GS_ScarecrowClimb,                overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &FireTemple_GS_ScarecrowTop,                  overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &FireTemple_GS_BossKeyLoop,                   overrides, NO_EFFECT);

        PlaceItemInLocation(&GoldSkulltulaToken, &WaterTemple_GS_BehindGate,                   overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &WaterTemple_GS_River,                        overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &WaterTemple_GS_FallingPlatformRoom,          overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &WaterTemple_GS_CentralPillar,                overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &WaterTemple_GS_NearBossKeyChest,             overrides, NO_EFFECT);

        PlaceItemInLocation(&GoldSkulltulaToken, &SpiritTemple_GS_MetalFence,                  overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &SpiritTemple_GS_SunOnFloorRoom,              overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &SpiritTemple_GS_HallAfterSunBlockRoom,       overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &SpiritTemple_GS_BoulderRoom,                 overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &SpiritTemple_GS_Lobby,                       overrides, NO_EFFECT);

        PlaceItemInLocation(&GoldSkulltulaToken, &ShadowTemple_GS_LikeLikeRoom,                overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &ShadowTemple_GS_FallingSpikesRoom,           overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &ShadowTemple_GS_SingleGiantPot,              overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &ShadowTemple_GS_NearShip,                    overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &ShadowTemple_GS_TripleGiantPot,              overrides, NO_EFFECT);

        PlaceItemInLocation(&GoldSkulltulaToken, &BottomOfTheWell_GS_WestInnerRoom,            overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &BottomOfTheWell_GS_EastInnerRoom,            overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &BottomOfTheWell_GS_LikeLikeCage,             overrides, NO_EFFECT);

        PlaceItemInLocation(&GoldSkulltulaToken, &IceCavern_GS_SpinningScytheRoom,             overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &IceCavern_GS_HeartPieceRoom,                 overrides, NO_EFFECT);
        PlaceItemInLocation(&GoldSkulltulaToken, &IceCavern_GS_PushBlockRoom,                  overrides, NO_EFFECT);
      }

      if (Settings::Keysanity == KEYSANITY_VANILLA) {
        //Forest Temple
        PlaceItemInLocation(&ForestTemple_SmallKey, &ForestTemple_FirstRoomChest,    overrides, NO_EFFECT);
        PlaceItemInLocation(&ForestTemple_SmallKey, &ForestTemple_FirstStalfosChest, overrides, NO_EFFECT);
        PlaceItemInLocation(&ForestTemple_SmallKey, &ForestTemple_FloormasterChest,  overrides, NO_EFFECT);
        PlaceItemInLocation(&ForestTemple_SmallKey, &ForestTemple_RedPoeChest,       overrides, NO_EFFECT);
        PlaceItemInLocation(&ForestTemple_SmallKey, &ForestTemple_WellChest,         overrides, NO_EFFECT);

        //Fire Temple
        PlaceItemInLocation(&FireTemple_SmallKey, &FireTemple_NearBossChest,                 overrides, NO_EFFECT);
        PlaceItemInLocation(&FireTemple_SmallKey, &FireTemple_BigLavaRoomBlockedDoorChest,   overrides, NO_EFFECT);
        PlaceItemInLocation(&FireTemple_SmallKey, &FireTemple_BigLavaRoomLowerOpenDoorChest, overrides, NO_EFFECT);
        PlaceItemInLocation(&FireTemple_SmallKey, &FireTemple_BoulderMazeLowerChest,         overrides, NO_EFFECT);
        PlaceItemInLocation(&FireTemple_SmallKey, &FireTemple_BoulderMazeUpperChest,         overrides, NO_EFFECT);
        PlaceItemInLocation(&FireTemple_SmallKey, &FireTemple_BoulderMazeShortcutChest,      overrides, NO_EFFECT);
        PlaceItemInLocation(&FireTemple_SmallKey, &FireTemple_BoulderMazeSideRoomChest,      overrides, NO_EFFECT);
        PlaceItemInLocation(&FireTemple_SmallKey, &FireTemple_HighestGoronChest,             overrides, NO_EFFECT);

        //Water Temple
        PlaceItemInLocation(&WaterTemple_SmallKey, &WaterTemple_TorchesChest,          overrides, NO_EFFECT);
        PlaceItemInLocation(&WaterTemple_SmallKey, &WaterTemple_RiverChest,            overrides, NO_EFFECT);
        PlaceItemInLocation(&WaterTemple_SmallKey, &WaterTemple_DragonChest,           overrides, NO_EFFECT);
        PlaceItemInLocation(&WaterTemple_SmallKey, &WaterTemple_CrackedWallChest,      overrides, NO_EFFECT);
        PlaceItemInLocation(&WaterTemple_SmallKey, &WaterTemple_CentralPillarChest,    overrides, NO_EFFECT);
        PlaceItemInLocation(&WaterTemple_SmallKey, &WaterTemple_CentralBowTargetChest, overrides, NO_EFFECT);

        //Spirit Temple
        PlaceItemInLocation(&SpiritTemple_SmallKey, &SpiritTemple_ChildEarlyTorchesChest, overrides, NO_EFFECT);
        PlaceItemInLocation(&SpiritTemple_SmallKey, &SpiritTemple_EarlyAdultRightChest,   overrides, NO_EFFECT);
        PlaceItemInLocation(&SpiritTemple_SmallKey, &SpiritTemple_NearFourArmosChest,     overrides, NO_EFFECT);
        PlaceItemInLocation(&SpiritTemple_SmallKey, &SpiritTemple_StatueRoomHandChest,    overrides, NO_EFFECT);
        PlaceItemInLocation(&SpiritTemple_SmallKey, &SpiritTemple_SunBlockRoomChest,      overrides, NO_EFFECT);

        //Shadow Temple
        PlaceItemInLocation(&ShadowTemple_SmallKey, &ShadowTemple_EarlySilverRupeeChest,     overrides, NO_EFFECT);
        PlaceItemInLocation(&ShadowTemple_SmallKey, &ShadowTemple_FallingSpikesSwitchChest,  overrides, NO_EFFECT);
        PlaceItemInLocation(&ShadowTemple_SmallKey, &ShadowTemple_InvisibleFloormasterChest, overrides, NO_EFFECT);
        PlaceItemInLocation(&ShadowTemple_SmallKey, &ShadowTemple_AfterWindHiddenChest,      overrides, NO_EFFECT);
        PlaceItemInLocation(&ShadowTemple_SmallKey, &ShadowTemple_FreestandingKey,           overrides, NO_EFFECT);

        //Bottom of the Well
        PlaceItemInLocation(&BottomOfTheWell_SmallKey, &BottomOfTheWell_FrontLeftFakeWallChest,   overrides, NO_EFFECT);
        PlaceItemInLocation(&BottomOfTheWell_SmallKey, &BottomOfTheWell_RightBottomFakeWallChest, overrides, NO_EFFECT);
        PlaceItemInLocation(&BottomOfTheWell_SmallKey, &BottomOfTheWell_FreestandingKey,          overrides, NO_EFFECT);

        //Gerudo Fortress
        PlaceItemInLocation(&GerudoFortress_SmallKey, &GF_NorthF1Carpenter, overrides, NO_EFFECT);
        PlaceItemInLocation(&GerudoFortress_SmallKey, &GF_NorthF2Carpenter, overrides, NO_EFFECT);
        PlaceItemInLocation(&GerudoFortress_SmallKey, &GF_SouthF1Carpenter, overrides, NO_EFFECT);
        PlaceItemInLocation(&GerudoFortress_SmallKey, &GF_SouthF2Carpenter, overrides, NO_EFFECT);

        //Gerudo Training Grounds
        PlaceItemInLocation(&GerudoTrainingGrounds_SmallKey, &GerudoTrainingGrounds_BeamosChest,                overrides, NO_EFFECT);
        PlaceItemInLocation(&GerudoTrainingGrounds_SmallKey, &GerudoTrainingGrounds_EyeStatueChest,             overrides, NO_EFFECT);
        PlaceItemInLocation(&GerudoTrainingGrounds_SmallKey, &GerudoTrainingGrounds_HammerRoomSwitchChest,      overrides, NO_EFFECT);
        PlaceItemInLocation(&GerudoTrainingGrounds_SmallKey, &GerudoTrainingGrounds_HeavyBlockThirdChest,       overrides, NO_EFFECT);
        PlaceItemInLocation(&GerudoTrainingGrounds_SmallKey, &GerudoTrainingGrounds_HiddenCeilingChest,         overrides, NO_EFFECT);
        PlaceItemInLocation(&GerudoTrainingGrounds_SmallKey, &GerudoTrainingGrounds_NearScarecrowChest,         overrides, NO_EFFECT);
        PlaceItemInLocation(&GerudoTrainingGrounds_SmallKey, &GerudoTrainingGrounds_StalfosChest,               overrides, NO_EFFECT);
        PlaceItemInLocation(&GerudoTrainingGrounds_SmallKey, &GerudoTrainingGrounds_UnderwaterSilverRupeeChest, overrides, NO_EFFECT);
        PlaceItemInLocation(&GerudoTrainingGrounds_SmallKey, &GerudoTrainingGrounds_FreestandingKey,            overrides, NO_EFFECT);

        //Ganon's Castle
        PlaceItemInLocation(&GanonsCastle_SmallKey, &GanonsCastle_LightTrialInvisibleEnemiesChest, overrides, NO_EFFECT);
        PlaceItemInLocation(&GanonsCastle_SmallKey, &GanonsCastle_LightTrialLullabyChest,          overrides, NO_EFFECT);
}

      if (Settings::BossKeysanity == BOSSKEYSANITY_VANILLA) {
        PlaceItemInLocation(&ForestTemple_BossKey, &ForestTemple_BossKeyChest, overrides, NO_EFFECT);
        PlaceItemInLocation(&FireTemple_BossKey,   &FireTemple_BossKeyChest,   overrides, NO_EFFECT);
        PlaceItemInLocation(&WaterTemple_BossKey,  &WaterTemple_BossKeyChest,  overrides, NO_EFFECT);
        PlaceItemInLocation(&SpiritTemple_BossKey, &SpiritTemple_BossKeyChest, overrides, NO_EFFECT);
        PlaceItemInLocation(&ShadowTemple_BossKey, &ShadowTemple_BossKeyChest, overrides, NO_EFFECT);
        PlaceItemInLocation(&GanonsCastle_BossKey, &GanonsCastle_BossKeyChest, overrides, NO_EFFECT);
      }

      if (Settings::MapsAndCompasses == MAPSANDCOMPASSES_VANILLA) {
        PlaceItemInLocation(&DekuTree_Map, &DekuTree_MapChest,               overrides, NO_EFFECT);
        PlaceItemInLocation(&DodongosCavern_Map, &DodongosCavern_MapChest,   overrides, NO_EFFECT);
        PlaceItemInLocation(&JabuJabusBelly_Map, &JabuJabusBelly_MapChest,   overrides, NO_EFFECT);
        PlaceItemInLocation(&ForestTemple_Map, &ForestTemple_MapChest,       overrides, NO_EFFECT);
        PlaceItemInLocation(&FireTemple_Map, &FireTemple_MapChest,           overrides, NO_EFFECT);
        PlaceItemInLocation(&WaterTemple_Map, &WaterTemple_MapChest,         overrides, NO_EFFECT);
        PlaceItemInLocation(&SpiritTemple_Map, &SpiritTemple_MapChest,       overrides, NO_EFFECT);
        PlaceItemInLocation(&ShadowTemple_Map, &ShadowTemple_MapChest,       overrides, NO_EFFECT);
        PlaceItemInLocation(&BottomOfTheWell_Map, &BottomOfTheWell_MapChest, overrides, NO_EFFECT);
        PlaceItemInLocation(&IceCavern_Map, &IceCavern_MapChest,             overrides, NO_EFFECT);

        PlaceItemInLocation(&DekuTree_Compass, &DekuTree_CompassChest,               overrides, NO_EFFECT);
        PlaceItemInLocation(&DodongosCavern_Compass, &DodongosCavern_CompassChest,   overrides, NO_EFFECT);
        PlaceItemInLocation(&JabuJabusBelly_Compass, &JabuJabusBelly_CompassChest,   overrides, NO_EFFECT);
        PlaceItemInLocation(&ForestTemple_Compass, &ForestTemple_BluePoeChest,       overrides, NO_EFFECT);
        PlaceItemInLocation(&FireTemple_Compass, &FireTemple_CompassChest,           overrides, NO_EFFECT);
        PlaceItemInLocation(&WaterTemple_Compass, &WaterTemple_CompassChest,         overrides, NO_EFFECT);
        PlaceItemInLocation(&SpiritTemple_Compass, &SpiritTemple_CompassChest,       overrides, NO_EFFECT);
        PlaceItemInLocation(&ShadowTemple_Compass, &ShadowTemple_CompassChest,       overrides, NO_EFFECT);
        PlaceItemInLocation(&BottomOfTheWell_Compass, &BottomOfTheWell_CompassChest, overrides, NO_EFFECT);
        PlaceItemInLocation(&IceCavern_Compass, &IceCavern_CompassChest,             overrides, NO_EFFECT);
      }

      if (Settings::Keysanity == KEYSANITY_DUNGEON_ONLY) {
        //Gerudo Fortress (not much to randomize here)
        PlaceItemInLocation(&GerudoFortress_SmallKey, &GF_NorthF1Carpenter, overrides, NO_EFFECT);
        PlaceItemInLocation(&GerudoFortress_SmallKey, &GF_NorthF2Carpenter, overrides, NO_EFFECT);
        PlaceItemInLocation(&GerudoFortress_SmallKey, &GF_SouthF1Carpenter, overrides, NO_EFFECT);
        PlaceItemInLocation(&GerudoFortress_SmallKey, &GF_SouthF2Carpenter, overrides, NO_EFFECT);

        //distribute keys into their dungeons
        RandomizeDungeonKeys(ForestTempleKeyRequirements,          &ForestTemple_SmallKey,          5, overrides);
        RandomizeDungeonKeys(FireTempleKeyRequirements,            &FireTemple_SmallKey,            8, overrides);
        RandomizeDungeonKeys(WaterTempleKeyRequirements,           &WaterTemple_SmallKey,           6, overrides);
        RandomizeDungeonKeys(SpiritTempleKeyRequirements,          &SpiritTemple_SmallKey,          5, overrides);
        RandomizeDungeonKeys(ShadowTempleKeyRequirements,          &ShadowTemple_SmallKey,          5, overrides);
        RandomizeDungeonKeys(BottomOfTheWellKeyRequirements,       &BottomOfTheWell_SmallKey,       3, overrides);
        RandomizeDungeonKeys(GerudoTrainingGroundsKeyRequirements, &GerudoTrainingGrounds_SmallKey, 9, overrides);
        RandomizeDungeonKeys(GanonsCastleKeyRequirements,          &GanonsCastle_SmallKey,          2, overrides);
        }

      if (Settings::BossKeysanity == BOSSKEYSANITY_DUNGEON_ONLY) {
        RandomizeDungeonItem(ForestTempleKeyRequirements, &ForestTemple_BossKey, overrides);
        RandomizeDungeonItem(FireTempleKeyRequirements,   &FireTemple_BossKey,   overrides);
        RandomizeDungeonItem(WaterTempleKeyRequirements,  &WaterTemple_BossKey,  overrides);
        RandomizeDungeonItem(SpiritTempleKeyRequirements, &SpiritTemple_BossKey, overrides);
        RandomizeDungeonItem(ShadowTempleKeyRequirements, &ShadowTemple_BossKey, overrides);
        RandomizeDungeonItem(GanonsCastleKeyRequirements, &GanonsCastle_BossKey, overrides);
      }

      if (Settings::MapsAndCompasses == MAPSANDCOMPASSES_DUNGEON_ONLY) {
        RandomizeDungeonItem(DekuTreeKeyRequirements,        &DekuTree_Map,        overrides);
        RandomizeDungeonItem(DodongosCavernKeyRequirements,  &DodongosCavern_Map,  overrides);
        RandomizeDungeonItem(JabuJabusBellyKeyRequirements,  &JabuJabusBelly_Map,  overrides);
        RandomizeDungeonItem(ForestTempleKeyRequirements,    &ForestTemple_Map,    overrides);
        RandomizeDungeonItem(FireTempleKeyRequirements,      &FireTemple_Map,      overrides);
        RandomizeDungeonItem(WaterTempleKeyRequirements,     &WaterTemple_Map,     overrides);
        RandomizeDungeonItem(SpiritTempleKeyRequirements,    &SpiritTemple_Map,    overrides);
        RandomizeDungeonItem(ShadowTempleKeyRequirements,    &ShadowTemple_Map,    overrides);
        RandomizeDungeonItem(BottomOfTheWellKeyRequirements, &BottomOfTheWell_Map, overrides);
        RandomizeDungeonItem(IceCavernKeyRequirements,       &IceCavern_Map,       overrides);

        RandomizeDungeonItem(DekuTreeKeyRequirements,        &DekuTree_Compass,        overrides);
        RandomizeDungeonItem(DodongosCavernKeyRequirements,  &DodongosCavern_Compass,  overrides);
        RandomizeDungeonItem(JabuJabusBellyKeyRequirements,  &JabuJabusBelly_Compass,  overrides);
        RandomizeDungeonItem(ForestTempleKeyRequirements,    &ForestTemple_Compass,    overrides);
        RandomizeDungeonItem(FireTempleKeyRequirements,      &FireTemple_Compass,      overrides);
        RandomizeDungeonItem(WaterTempleKeyRequirements,     &WaterTemple_Compass,     overrides);
        RandomizeDungeonItem(SpiritTempleKeyRequirements,    &SpiritTemple_Compass,    overrides);
        RandomizeDungeonItem(ShadowTempleKeyRequirements,    &ShadowTemple_Compass,    overrides);
        RandomizeDungeonItem(BottomOfTheWellKeyRequirements, &BottomOfTheWell_Compass, overrides);
        RandomizeDungeonItem(IceCavernKeyRequirements,       &IceCavern_Compass,       overrides);
      }
    }

    static void Playthrough_Init(u32 seed, std::set<ItemOverride, ItemOverride_Compare>& overrides) {
        Random_Init(seed); //seed goes here
        Settings::UpdateSettings();
        Settings::PrintSettings();
        Logic::UpdateHelpers();
        GenerateItemPool();
        UpdateSetItems();
        PlaceSetItems(overrides);
        AccessibleLocations_Init(overrides);
    }

    int Fill(int settings, u32 seed, std::set<ItemOverride, ItemOverride_Compare>& overrides) {
        (void)settings;

        Playthrough_Init(seed, overrides);
        /*
        while (not all locations accessible)
          - Determine which items can be placed for advancement
          - Choose randomly from that list for placement
          - Update accessibility and items that can be used for advancement
          - Otherwise place a random item

        */
        while ((!ItemPool.empty() || !AdvancementItemPool.empty()) && !AccessibleLocationPool.empty()) {
            int ret;
            if (!AdvancementItemPool.empty()) {
              ret = PlaceAdvancementItem(overrides);
            } else {
              ret = PlaceRandomItem(overrides);
            }

            if (ret < 0) {
                return ret;
            }

            if (ItemPool.empty() && !AccessibleLocationPool.empty()) {
              AddGreenRupee();
            }

        }
        printf("\x1b[10;10H");
        bool rv = SpoilerLog_Write();
        if (rv) printf("Wrote Spoiler Log\n");
        else    printf("failed to write log\n");

        rv = PlacementLog_Write();
        return 1;
    }
}
