#include "fill.hpp"
#include "item_pool.hpp"
#include "starting_inventory.hpp"
#include "location_access.hpp"
#include "spoiler_log.hpp"
#include "logic.hpp"
#include "random.hpp"

std::vector<Item> unplacedItems = {};
std::vector<Item> placedItems = {};
std::vector<ItemLocation *> locations = {};

template <typename T, typename Predicate>
static void erase_if(std::vector<T>& vector, Predicate pred) {
    vector.erase(std::remove_if(begin(vector), end(vector), pred), end(vector));
}

static void RemoveStartingItemsFromPool() {
  for (Item& startingItem : StartingInventory) {
    for (u16 i = 0; i < ItemPool.size(); i++) {
      if (startingItem == ItemPool[i]) {
        ItemPool[i] = GetJunkItem();
        break;
      }
    }
  }
}

static void RandomizeDungeonRewards() {
  //shuffle an array of indices so that we can randomize the rewards both
  //logically and for the patch
  std::array<u8, 9> idxArray = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  std::shuffle(idxArray.begin(), idxArray.end(), std::default_random_engine(Random()));

  for (size_t i = 0; i < dungeonRewards.size(); i++) {
    const u8 idx = idxArray[i];
    PlaceItemInLocation(dungeonRewardLocations[i], dungeonRewards[idx]);
    Settings::rDungeonRewardOverrides[i] = idx;
  }
  Settings::LinksPocketRewardBitMask = LinksPocket.GetPlacedItem().GetItemID();
}

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

static Item GetItemToPlace() {
  for (size_t i = 0; i < unplacedItems.size(); i++) {
    //keep iterating to select a song during song shuffling to other song locations
    if (Settings::ShuffleSongs.Is(SONGSHUFFLE_SONG_LOCATIONS) && unplacedItems[i].GetItemType() != ITEMTYPE_SONG && placedItems.size() < songLocations.size()) {
      continue;
    }

    Item item = std::move(unplacedItems[i]);
    unplacedItems.erase(unplacedItems.begin() + i);
    return item;
  }

  PlacementLog_Msg("\nERROR: COULD NOT FIND ITEM TO PLACE\n");
  return NoItem;
}

static void GetAccessibleLocations(std::vector<ItemLocation *>& locations, bool playthrough = false) {
  //logically give the starting inventory
  ApplyStartingInventory();

  locations.clear();
  Exits::AccessReset();
  LocationReset();
  Logic::UpdateHelpers();
  std::vector<Exit *> exitPool = {&Exits::Root};

  u8 iterationsWithNoLocations = 0;
  while(iterationsWithNoLocations < 5) {
    iterationsWithNoLocations++;

    for (size_t i = 0; i < exitPool.size(); i++) {
      Exit* area = exitPool[i];
      //area->LogStatus(); for some reason this function crashes the app when attempting max randomization options

      //iterate twice on each area for different ages
      for (u8 age : {AGE_CHILD, AGE_ADULT}) {
        Logic::Age = age;

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

        //for each exit in this area
        for (size_t j = 0; j < area->exits.size(); j++) {
          ExitPairing& exitPair = area->exits[j];
          Exit* exit = exitPair.GetExit();

          if (exitPair.ConditionsMet() || Settings::Logic.Is(LOGIC_NONE)) {
            UpdateToDAccess(exit, age, exitPair.TimeOfDay());

            //If the exit is accessible, try adding it
            if (exit->HasAccess() && !exit->addedToPool) {

              exit->addedToPool = true;
              exitPool.push_back(exit);
            }
          }
        }

        // Erase ExitPairings whose conditions have been met while the exit has full day time access as both ages
        //erase_if(area->exits, [](const ExitPairing& ep){ return ep.ConditionsMet() && ep.GetExit()->AllAccess();});

        //for each ItemLocation in this area
        for (size_t k = 0; k < area->locations.size(); k++) {
          ItemLocationPairing& locPair = area->locations[k];
          ItemLocation* location = locPair.GetLocation();

          if ((locPair.ConditionsMet() || Settings::Logic.Is(LOGIC_NONE)) && !location->IsAddedToPool()) {

            location->AddToPool();
            iterationsWithNoLocations = 0;

            if (location->GetPlacedItemName() == "No Item") {
              locations.push_back(location);
            } else {

              //used when generating playthrough text
              if (playthrough) {
                if (location->GetPlacedItemName() == "Triforce") {
                  PlacementLog_Msg("\nSEED BEATABLE");
                  playthroughLocations.push_back(location);
                }

                //log the item location if it contains an advancement item
                for (const Item& item : placedItems) {
                  if (location->GetPlacedItemName() == item.GetName()) {
                    playthroughLocations.push_back(location);
                    break;
                  }
                }
              }
              location->ApplyPlacedItemEffect();
            }
          }
        }
      }
    }

    if (Logic::EventsUpdated()) {
      iterationsWithNoLocations = 0;
    }
  }
}

static void FastFill(std::vector<ItemLocation*> locations) {

  //Place everything randomly
  while (!locations.empty()) {
    unsigned int itemIdx = Random() % ItemPool.size();
    unsigned int locIdx = Random() % locations.size();

    PlaceItemInLocation(locations[locIdx], ItemPool[itemIdx]);

    ItemPool.erase(ItemPool.begin() + itemIdx);
    locations.erase(locations.begin() + locIdx);

    if (ItemPool.empty()) {
      AddJunk();
    }
  }
}
/*
| The algorithm places items in the world in reverse.
| This means we first assume we have every item in the item pool and
| remove an item and try to place it somewhere that is still reachable
| This method helps distribution of items locked behind many requirements.
| - OoT Randomizer
*/
static int AssumedFill() {

  //get all the advancement items
  placedItems.clear();
  unplacedItems.clear();
  std::copy_if(ItemPool.begin(), ItemPool.end(), std::back_inserter(unplacedItems), [](const Item& i) {
    return i.IsAdvancement();
  });
  erase_if(ItemPool, [](const Item& i) { return i.IsAdvancement(); });

  //shuffle the order
  std::shuffle(unplacedItems.begin(), unplacedItems.end(), std::default_random_engine(Random()));

  while (!unplacedItems.empty()) {

    //move an item from unplaced to placed, this will be the item we place
    Item item = GetItemToPlace();
    if (item.GetName() == "No Item") {
      PlacementLog_Msg("\nRETRYING PLACEMENT...\n");
      return 0;
    }
    placedItems.push_back(item);

    //assume we have all of the unplaced items and nothing else
    Logic::LogicReset();
    for (Item& unplacedItem : unplacedItems) {
      unplacedItem.ApplyEffect();
    }

    //retrieve all possible locations to place the next item
    GetAccessibleLocations(locations);

    /*if songs are restricted to song locations and a song is being placed, then
      filter to only song locations.*/
    if (Settings::ShuffleSongs.Is(SONGSHUFFLE_SONG_LOCATIONS) && item.GetItemType() == ITEMTYPE_SONG) {
        erase_if(locations, [](ItemLocation* loc) { return !loc->IsCategory("Songs");});
    }

    //if we get stuck, retry
    if (locations.empty()) {
      PlacementLog_Msg("\nCANNOT PLACE ");
      PlacementLog_Msg(item.GetName());
      PlacementLog_Msg(". TRYING AGAIN...\n");
      return 0;
    }

    //place the item
    unsigned int locIdx = Random() % locations.size();
    PlaceItemInLocation(locations[locIdx], item);
  }

  //get the rest of locations that don't have items
  Logic::LogicReset();
  GetAccessibleLocations(locations);

  //fast fill for the rest
  FastFill(locations);

  //calculate playthrough
  Logic::LogicReset();
  GetAccessibleLocations(locations, true);

  return 1;
}

static void FillExcludedLocations() {
  //Only fill in excluded locations that don't already have something and are forbidden
  locations.assign(allLocations.begin(), allLocations.end());
  erase_if(locations, [](ItemLocation* il){return !il->IsExcluded() || il->GetPlacedItemName() != "No Item";});

  for (ItemLocation* il : locations) {
    PlaceJunkInExcludedLocation(il);
  }
}

int Fill() {
  itemsPlaced = 0;
  GenerateLocationPool();
  GenerateItemPool();
  GenerateStartingInventory();
  RemoveStartingItemsFromPool();
  RandomizeDungeonRewards();
  FillExcludedLocations();

  if (!AssumedFill()) {
    return 0;
  }

  return 1;
}
