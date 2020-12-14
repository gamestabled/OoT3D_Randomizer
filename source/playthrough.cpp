#include "playthrough.hpp"
#include "item_pool.hpp"
#include "item_location.hpp"
#include "location_access.hpp"
#include "logic.hpp"
#include "random.hpp"
#include "spoiler_log.hpp"
#include "../code/src/item_override.h"

#include <3ds.h>
#include <algorithm>
#include <cstdio>
#include <string>
#include <unistd.h>

template <typename T, typename Predicate>
static void erase_if(std::vector<T>& vector, Predicate pred) {
    vector.erase(std::remove_if(begin(vector), end(vector), pred), end(vector));
}

namespace Playthrough {

    static u64 accessibleLocationIterations = 0;
    static std::vector<ItemLocation *> AccessibleLocationPool;

    //apply an items effect while placing it
    const bool APPLY_IMMEDAITELY = true;

    static void UpdateToDAccess(Exit* exit, u8 age, ExitPairing::Time ToD) {
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

    static void AccessibleLocations_Update() {
        bool advancementChange = true;
        while(advancementChange) {
          advancementChange = false;

          for (size_t i = 0; i < Exits::ExitPool.size(); i++) {
            //iterate twice on each area for different ages
            for (u8 age : {AGE_CHILD, AGE_ADULT}) {
              Logic::Age = age;
              Exit* area = Exits::ExitPool[i];

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
              if (area->UpdateEvents()) {
                advancementChange = true;
              }
              area->UpdateAdvancementNeeds();

              //for each exit in this area
              for (size_t j = 0; j < area->exits.size(); j++) {
                ExitPairing& exitPair = area->exits[j];
                Exit* exit = exitPair.GetExit();

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
              for (size_t k = 0; k < area->locations.size(); k++) {
                ItemLocationPairing& locPair = area->locations[k];
                ItemLocation* location = locPair.GetLocation();

                if (locPair.ConditionsMet() && !location->IsAddedToPool()) {
                  PlacementLog_Msg("NEW LOCATION FOUND: ");
                  PlacementLog_Msg(location->GetName());

                  totalLocationsFound++;
                  location->AddToPool();

                  if (location->GetPlacedItemName() == "No Item") {
                    PlacementLog_Msg(" | NO ITEM\n");
                    AccessibleLocationPool.push_back(location);
                    if (accessibleLocationIterations > 2) {
                      AccessibleLocationPool.push_back(location); //give the location more weight
                    }
                    Logic::CurAccessibleLocations++;
                  } else {
                    PlacementLog_Msg(" | ITEM HERE\n");
                    location->ApplyPlacedItemEffect();
                    location->Use();
                    advancementChange = true;
                  }
                }
              }

              // Erase ItemLocationPairings that are placed into the AccessibleLocationPool
              erase_if(area->locations, [](const ItemLocationPairing& ilp){ return ilp.IsLocationUsed(); });

              // Erase ExitPairings whose conditions have been met while the exit has full day time access as both ages
              erase_if(area->exits, [](const ExitPairing& ep){ return ep.ConditionsMet() && ep.GetExit()->AllAccess();});
            }
          }
        }
        accessibleLocationIterations++;
        //erase exits from the ExitPool if they can't open up more access to anything
        erase_if(Exits::ExitPool, [](const Exit* exit){return exit->AllAccountedFor();});
    }

    static void AccessibleLocations_Init() {
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

      AccessibleLocations_Update();
      if (Logic::EventsUpdated()) {
        AccessibleLocations_Update();
      }
    }

    static int PlaceAdvancementItem() {
        if (AdvancementItemPool.empty()) {
            return -1;
        }

        if (AccessibleLocationPool.empty()) {
            return -2;
        }

        unsigned int itemIdx = Random() % AdvancementItemPool.size();
        unsigned int locIdx  = Random() % AccessibleLocationPool.size();

        PlaceItemInLocation(AccessibleLocationPool[locIdx], &AdvancementItemPool[itemIdx], APPLY_IMMEDAITELY);
        advancementLocations.push_back(AccessibleLocationPool[locIdx]);

        AdvancementItemPool.erase(AdvancementItemPool.begin() + itemIdx);
        //erase locations that have been used
        erase_if(AccessibleLocationPool, [](const ItemLocation* il){return il->IsUsed();});
        Logic::CurAccessibleLocations--;

        AccessibleLocations_Update();
        if (Logic::EventsUpdated()) {
          AccessibleLocations_Update();
        }
        return 1;
    }

    static int PlaceRandomItem() {
        unsigned int itemIdx = Random() % ItemPool.size();
        unsigned int locIdx = Random() % AccessibleLocationPool.size();

        PlaceItemInLocation(AccessibleLocationPool[locIdx], &ItemPool[itemIdx], APPLY_IMMEDAITELY);

        ItemPool.erase(ItemPool.begin() + itemIdx);
        //erase locations that have been used
        erase_if(AccessibleLocationPool, [](const ItemLocation* il){return il->IsUsed();});
        Logic::CurAccessibleLocations--;

        AccessibleLocations_Update();
        if (Logic::EventsUpdated()) {
          AccessibleLocations_Update();
        }
        return 1;
    }

    static void RandomizeDungeonRewards() {

      //shuffle an array of indices so that we can randomize the rewards both logically and for the patch
      std::array<u8, 9> idxArray = {0, 1, 2, 3, 4, 5, 6, 7, 8};
      std::shuffle(idxArray.begin(), idxArray.end(), std::default_random_engine(Random()));

      for (u8 i = 0; i < dungeonRewards.size(); i++) {
        u8 idx = idxArray[i];
        PlaceItemInLocation(dungeonRewardLocations[i], &dungeonRewards[idx]);
        Settings::rDungeonRewardOverrides[i] = idx;
      }
      Settings::LinksPocketRewardBitMask = LinksPocket.GetPlacedItem().GetItemID();
    }

    static void Playthrough_Init(u32 seed) {
        Random_Init(seed); //seed goes here
        Settings::UpdateSettings();
        Settings::PrintSettings();
        Logic::UpdateHelpers();
        GenerateItemPool();
        RandomizeDungeonRewards();
        AccessibleLocations_Init();
    }

    int Fill(u32 seed) {
        overrides.clear();
        Playthrough_Init(seed);
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
              ret = PlaceAdvancementItem();
            } else {
              ret = PlaceRandomItem();
            }

            if (ret < 0) {
                return ret;
            }

            if (ItemPool.empty() && !AccessibleLocationPool.empty()) {
              AddGreenRupee();
            }

        }
        printf("\x1b[9;10H");
        bool rv = SpoilerLog_Write();
        if (rv) printf("Wrote Spoiler Log\n");
        else    printf("failed to write log\n");

        rv = PlacementLog_Write();
        printf("\x1b[10;10HWrote Placement Log\n");
        return 1;
    }

    s16 GetRandomPrice() {
      return 5 * ((Random() % 19) + 1);
    }
}
