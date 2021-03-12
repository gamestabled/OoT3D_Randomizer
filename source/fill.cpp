#include "fill.hpp"
#include "item_pool.hpp"
#include "starting_inventory.hpp"
#include "location_access.hpp"
#include "spoiler_log.hpp"
#include "logic.hpp"
#include "random.hpp"

const bool ERASE_AFTER_FILTER = true;

template <typename T, typename Predicate>
static void erase_if(std::vector<T>& vector, Predicate pred) {
    vector.erase(std::remove_if(begin(vector), end(vector), pred), end(vector));
}

template <typename T, typename Predicate>
static std::vector<T> FilterFromPool(std::vector<T>& vector, Predicate pred, bool eraseAfterFilter = false) {
  std::vector<T> filteredPool = {};
  std::copy_if(vector.begin(), vector.end(), std::back_inserter(filteredPool), pred);

  if (eraseAfterFilter) {
    erase_if(vector, pred);
  }

  return filteredPool;
}

template <typename T, typename Predicate>
static std::vector<T> FilterAndEraseFromPool(std::vector<T>& vector, Predicate pred) {
  return FilterFromPool(vector, pred, ERASE_AFTER_FILTER);
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

static std::vector<ItemLocation*> GetAccessibleLocations(std::vector<ItemLocation*> allowedLocations, bool playthrough = false) {
  //logically give the starting inventory
  ApplyStartingInventory();

  std::vector<ItemLocation*> accessibleLocations = {};
  Exits::AccessReset();
  LocationReset();
  Logic::UpdateHelpers();
  std::vector<Exit *> exitPool = {&Exits::Root};

  u8 iterationsWithNoLocations = 0;
  while(iterationsWithNoLocations < 5) {
    iterationsWithNoLocations++;

    for (size_t i = 0; i < exitPool.size(); i++) {
      Exit* area = exitPool[i];

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
              accessibleLocations.push_back(location);
            } else {
              location->ApplyPlacedItemEffect();
            }

            if (playthrough && location->GetPlacedItem().IsPlaythrough() && location->GetPlacedItem().IsAdvancement()) {
              playthroughLocations.push_back(location);
            }
          }
        }
      }
    }

    if (Logic::EventsUpdated()) {
      iterationsWithNoLocations = 0;
    }
  }
  erase_if(accessibleLocations, [allowedLocations](ItemLocation* loc){
    for (ItemLocation* allowedLocation : allowedLocations) {
      if (loc == allowedLocation) {
        return false;
      }
    }
    return true;
  });

  return accessibleLocations;
}

static void GeneratePlaythrough() {
  GetAccessibleLocations(allLocations, true);
}

static void FastFill(std::vector<Item> items, std::vector<ItemLocation*> locations) {

  //Place everything randomly
  while (!locations.empty()) {
    unsigned int itemIdx = Random() % items.size();
    unsigned int locIdx = Random() % locations.size();

    PlaceItemInLocation(locations[locIdx], items[itemIdx]);

    items.erase(items.begin() + itemIdx);
    locations.erase(locations.begin() + locIdx);

    if (items.empty()) {
      items.push_back(GetJunkItem());
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
static void AssumedFill(std::vector<Item> items, std::vector<ItemLocation*> allowedLocations) {

  //keep retrying to place everything until it works
  bool unsuccessfulPlacement = false;
  std::vector<ItemLocation*> attemptedLocations = {};
  do {
    unsuccessfulPlacement = false;
    std::vector<Item> itemsToPlace = items;

    //copy all not yet placed advancement items so that we can apply their effects for the fill algorithm
    std::vector<Item> itemsToNotPlace = {};
    std::copy_if(ItemPool.begin(), ItemPool.end(), std::back_inserter(itemsToNotPlace), [](const Item& i) {
      return i.IsAdvancement();
    });

    //shuffle the order of items to place
    std::shuffle(itemsToPlace.begin(), itemsToPlace.end(), std::default_random_engine(Random()));

    while (!itemsToPlace.empty()) {
      Item item = std::move(itemsToPlace.back());
      item.SetAsPlaythrough();
      itemsToPlace.pop_back();

      //assume we have all unplaced items
      Logic::LogicReset();
      for (Item& unplacedItem : itemsToPlace) {
        unplacedItem.ApplyEffect();
      }
      for (Item& unplacedItem : itemsToNotPlace) {
        unplacedItem.ApplyEffect();
      }

      //get all accessible locations that are allowed
      std::vector<ItemLocation*> accessibleLocations = GetAccessibleLocations(allowedLocations);

      //retry if there are no more locations to place items
      if (accessibleLocations.empty()) {

        PlacementLog_Msg("\nCANNOT PLACE ");
        PlacementLog_Msg(item.GetName());
        PlacementLog_Msg(". TRYING AGAIN...\n");

        //reset any locations that got an item
        for (ItemLocation* loc : attemptedLocations) {
          loc->SetPlacedItem(NoItem);
          itemsPlaced--;
        }
        attemptedLocations.clear();

        unsuccessfulPlacement = true;
        continue;
      }

      //place the item within one of the allowed locations
      unsigned int locIdx = Random() % accessibleLocations.size();
      PlaceItemInLocation(accessibleLocations[locIdx], item);
      attemptedLocations.push_back(accessibleLocations[locIdx]);

    }
  } while (unsuccessfulPlacement);
}

static void FillExcludedLocations() {
  //Only fill in excluded locations that don't already have something and are forbidden
  std::vector<ItemLocation*> excludedLocations = FilterFromPool(allLocations, [](ItemLocation* loc){
    return loc->IsExcluded();
  });

  for (ItemLocation* loc : excludedLocations) {
    PlaceJunkInExcludedLocation(loc);
  }
}

void Fill() {
  GenerateLocationPool();
  GenerateItemPool();
  GenerateStartingInventory();
  RemoveStartingItemsFromPool();
  RandomizeDungeonRewards();
  FillExcludedLocations();

  //place songs first if song shuffle is set to specific locations
  if (Settings::ShuffleSongs.IsNot(SONGSHUFFLE_ANYWHERE)) {

    //Get each song
    std::vector<Item> songs = FilterAndEraseFromPool(ItemPool, [](const Item& i) { return i.GetItemType() == ITEMTYPE_SONG;});

    //Get each song location
    std::vector<ItemLocation*> songLocations = {};
    if (Settings::ShuffleSongs.Is(SONGSHUFFLE_SONG_LOCATIONS)) {
      songLocations = FilterFromPool(allLocations, [](ItemLocation * loc){ return loc->IsCategory("Songs");});
    }

    AssumedFill(songs, songLocations);
  }

  //then place the rest of the advancement items
  std::vector<Item> remainingAdvancementItems = FilterAndEraseFromPool(ItemPool, [](const Item& i) { return i.IsAdvancement();});
  AssumedFill(remainingAdvancementItems, allLocations);

  //fast fill for the rest of the pool
  std::vector<Item> remainingPool = FilterAndEraseFromPool(ItemPool, [](const Item& i) {return true;});
  Logic::LogicReset();
  FastFill(remainingPool, GetAccessibleLocations(allLocations));

  Logic::LogicReset();
  GeneratePlaythrough();
}
