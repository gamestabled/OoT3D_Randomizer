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

 //  /opt/devkitpro/devkitARM/bin/arm-none-eabi-nm code.elf > symbols.txt

template<typename T> void erase_if(std::vector<T>& vector, std::function<bool(T)> pred) {
    vector.erase(std::remove_if(begin(vector), end(vector), pred), end(vector));
}

namespace Playthrough {

    //static int debug = 0;

    static u32 totalAccessibleLocations = 0;
    static std::vector<ItemLocation *> AccessibleLocationPool;

    void PlaceItemInLocation(Item* item, ItemLocation* loc, std::set<ItemOverride, ItemOverride_Compare>& overrides, bool applyEffectImmediately = true) {
        // put item in the override table
        ItemOverride override;
        override.key.all = 0;

        override.value.all = 0;
        override.key = loc->key();
        override.value = item->value();

        overrides.insert(override);

        PlacementLog_Msg("\n");
        PlacementLog_Msg(item->getName());
        PlacementLog_Msg(" placed at ");
        PlacementLog_Msg(loc->getName());
        PlacementLog_Msg("\n\n");

        if (applyEffectImmediately) {
          item->applyEffect();
        }

        loc->placedItem = *item;
        totalAccessibleLocations++;
    }


    //Graph building psuedocode
    /*
    For Each Age
      For each accessible exit:

        For each possible exit:
          If the exit is accessible:
            update its day/night accessibility

          If it's accessible and hasn't been accounted for yet:
            pop it off and add it to the pool of accessible exit locations

        For each non-accessible item_location:
          If it's accessible and hasn't been accounted for:
            pop it off and add it to the pool of accessible item location
    */

    //This implementation works but contains a lot of redundency
    static void AccessibleLocations_Update(std::set<ItemOverride, ItemOverride_Compare>& overrides) {

        if (Logic::CanBeChild) {
          Logic::Age = "Child";
          Logic::UpdateHelpers();
          for (u32 i = 0; i < Exits::ChildExitPool.size(); i++) {

            Exit area = Exits::ChildExitPool[i];
            erase_if<ExitPairing>        (area.exits,     [](ExitPairing ep)         { return ep.exit->accountedForChild;});
            erase_if<ItemLocationPairing>(area.locations, [](ItemLocationPairing ilp){ return ilp.location->isUsed();    });
            area.UpdateEvents();
            area.UpdateAdvancementNeeds();
            Logic::AtDay = area.dayChild;
            Logic::AtNight = area.nightChild;

            //for each Exit in this area
            for (auto exitPair = area.exits.begin(); exitPair != area.exits.end(); exitPair++) {
              Exit *exit = exitPair->exit;
              //if the exit is accessible, update day/night propogation
              if(exitPair->ConditionsMet()) {
                //If there are special day requirements

                if (exitPair->ToD == "Day") {
                  exit->dayChild = true;
                } else if (exitPair->ToD == "Night") {
                  exit->nightChild = true;
                } else {
                  //only update from false -> true, never true -> false
                  exit->dayChild   = Logic::AtDay   || exit->dayChild;
                  exit->nightChild = Logic::AtNight || exit->nightChild;
                }

                //If the exit is accessible and not accounted for, add it to the exit pool
                if (!exit->accountedForChild) {
                  PlacementLog_Msg("NEW CHILD EXIT FOUND: ");
                  PlacementLog_Msg(exit->regionName.c_str());
                  PlacementLog_Msg("\n");
                  Exits::ChildExitPool.push_back(*exit);
                  exit->accountedForChild = true;
                }
              }
            }

            //for each ItemLocation in this area
            for (auto locPair = area.locations.begin(); locPair != area.locations.end(); locPair++) {

              //If the item location is accessible and not accounted for, add it to the Accesible Location Pool
              if (locPair->ConditionsMet() && !locPair->location->isUsed()) {
                PlacementLog_Msg("NEW LOCATION FOUND: ");
                PlacementLog_Msg(locPair->location->getName());

                if (locPair->location->placedItem.name == "No Item") {
                  PlacementLog_Msg(" | NO ITEM\n");
                  AccessibleLocationPool.push_back(locPair->location);
                } else {
                  PlacementLog_Msg(" | ITEM HERE\n");
                  locPair->location->use();
                  locPair->location->placedItem.applyEffect();
                  AccessibleLocations_Update(overrides);
                  return;
                }
                locPair->location->use();
              }
            }
          }

          erase_if<Exit>(Exits::ChildExitPool, [](Exit e){ return e.AllAccountedFor(); });
        }

        if (Logic::CanBeAdult) {
          Logic::Age = "Adult";
          Logic::UpdateHelpers();
          for (u32 i = 0; i < Exits::AdultExitPool.size(); i++) {

            Exit area = Exits::AdultExitPool[i];
            erase_if<ExitPairing>        (area.exits,     [](ExitPairing ep)         { return ep.exit->accountedForAdult;});
            erase_if<ItemLocationPairing>(area.locations, [](ItemLocationPairing ilp){ return ilp.location->isUsed();     });
            area.UpdateEvents();
            area.UpdateAdvancementNeeds();
            Logic::AtDay = area.dayAdult;
            Logic::AtNight = area.nightAdult;

            //for each Exit in this area
            for (auto exitPair = area.exits.begin(); exitPair != area.exits.end(); exitPair++) {
              Exit *exit = exitPair->exit;
              //if the exit is accessible, update day/night propogation
              if(exitPair->ConditionsMet()) {
                //If there are special day requirements

                if (exitPair->ToD == "Day") {
                  exit->dayAdult = true;
                } else if (exitPair->ToD == "Night") {
                  exit->nightAdult = true;
                } else {
                  //only update from false -> true, never true -> false
                  exit->dayAdult   = Logic::AtDay   || exit->dayAdult;
                  exit->nightAdult = Logic::AtNight || exit->nightAdult;
                }

                //If the exit is accessible and not accounted for, add it to the exit pool
                if (!exit->accountedForAdult) {
                  PlacementLog_Msg("NEW ADULT EXIT FOUND: ");
                  PlacementLog_Msg(exit->regionName.c_str());
                  PlacementLog_Msg("\n");
                  Exits::AdultExitPool.push_back(*exit);
                  exit->accountedForAdult = true;
                }
              }
            }

            //for each ItemLocation in this area
            for (auto locPair = area.locations.begin(); locPair != area.locations.end(); locPair++) {
              //If the item location is accessible and not accounted for, add it to the Accesible Location Pool
              if (locPair->ConditionsMet() && !locPair->location->isUsed()) {
                PlacementLog_Msg("NEW LOCATION FOUND: ");
                PlacementLog_Msg(locPair->location->getName());

                if (locPair->location->placedItem.name == "No Item") {
                  PlacementLog_Msg(" | NO ITEM\n");
                  AccessibleLocationPool.push_back(locPair->location);
                } else {
                  PlacementLog_Msg(" | ITEM HERE\n");
                  locPair->location->use();
                  locPair->location->placedItem.applyEffect();
                  AccessibleLocations_Update(overrides);
                  return;
                }
                locPair->location->use();
              }
            }
          }

          erase_if<Exit>(Exits::AdultExitPool, [](Exit e){ return e.AllAccountedFor(); });
        }

    }

    static void AccessibleLocations_Init(std::set<ItemOverride, ItemOverride_Compare>& overrides) {
        Exits::Root.UpdateEvents();
        if (Logic::StartingAge == "Child") {
          Exits::ChildExitPool.push_back(Exits::Root);
        } else {
          Exits::AdultExitPool.push_back(Exits::Root);
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
        unsigned int locIdx = Random() % AccessibleLocationPool.size();

        PlaceItemInLocation(&AdvancementItemPool[itemIdx], AccessibleLocationPool[locIdx], overrides);

        AdvancementItemPool.erase(AdvancementItemPool.begin() + itemIdx);
        AccessibleLocationPool.erase(AccessibleLocationPool.begin() + locIdx);

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
        AccessibleLocationPool.erase(AccessibleLocationPool.begin() + locIdx);

        AccessibleLocations_Update(overrides);
        if (Logic::EventsUpdated()) {
          AccessibleLocations_Update(overrides);
        }
        return 1;
    }

    static void Playthrough_Init(u32 seed, std::set<ItemOverride, ItemOverride_Compare>& overrides) {
        Random_Init(seed); //seed goes here
        Logic::UpdateSettings();
        UpdateSetItems();
        PlaceSetItems(overrides);
        AccessibleLocations_Init(overrides);
    }

    void Reset() {

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
              AddHeartPiece();
            }
        }
        printf("Items Placed: %lu\n", totalAccessibleLocations);
        bool rv = SpoilerLog_Write();
        if (rv) printf("Wrote Spoiler Log\n");
        else    printf("failed to write log\n");

        rv = PlacementLog_Write();
        return 1;
    }

    //Check for specific preset items in locations
    void PlaceSetItems(std::set<ItemOverride, ItemOverride_Compare>& overrides) {
      const bool NO_EFFECT = false;

      if (!Logic::ShuffleKokiriSword)
        PlaceItemInLocation(&A_KokiriSword, &KF_KokiriSwordChest, overrides, NO_EFFECT);

      if (!Logic::ShuffleWeirdEgg )
        PlaceItemInLocation(&A_WeirdEgg, &HC_MalonEgg, overrides, NO_EFFECT);

      if (!Logic::ShuffleZeldasLetter)
        PlaceItemInLocation(&A_ZeldasLetter, &HC_ZeldasLetter, overrides, NO_EFFECT);

      if (!Logic::ShuffleGerudoToken)
        PlaceItemInLocation(&A_GerudoToken, &GF_GerudoToken, overrides, NO_EFFECT);

      if (Logic::Keysanity == "Vanilla") {
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

      if (Logic::BossKeysanity == "Vanilla") {
        PlaceItemInLocation(&ForestTemple_BossKey, &ForestTemple_BossKeyChest, overrides, NO_EFFECT);
        PlaceItemInLocation(&FireTemple_BossKey,   &FireTemple_BossKeyChest,   overrides, NO_EFFECT);
        PlaceItemInLocation(&WaterTemple_BossKey,  &WaterTemple_BossKeyChest,  overrides, NO_EFFECT);
        PlaceItemInLocation(&SpiritTemple_BossKey, &SpiritTemple_BossKeyChest, overrides, NO_EFFECT);
        PlaceItemInLocation(&ShadowTemple_BossKey, &ShadowTemple_BossKeyChest, overrides, NO_EFFECT);
        PlaceItemInLocation(&GanonsCastle_BossKey, &GanonsCastle_BossKeyChest, overrides, NO_EFFECT);
      }

      if (Logic::MapsAndCompasses == "Vanilla") {
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
    }
}
