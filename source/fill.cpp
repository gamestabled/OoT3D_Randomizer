#include "fill.hpp"
#include "item_pool.hpp"
#include "starting_inventory.hpp"
#include "location_access.hpp"
#include "spoiler_log.hpp"
#include "logic.hpp"
#include "random.hpp"

using namespace Logic;
using namespace Settings;

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
  Shuffle(idxArray);

  for (size_t i = 0; i < dungeonRewards.size(); i++) {
    const u8 idx = idxArray[i];
    PlaceItemInLocation(dungeonRewardLocations[i], dungeonRewards[idx]);
    rDungeonRewardOverrides[i] = idx;
  }
  LinksPocketRewardBitMask = LinksPocket.GetPlacedItem().GetItemID();
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

//Get the max number of tokens that can possibly give a necessary item
static int GetMaxGSCount() {
  //If bridge is set to tokens, get how many are required
  int maxBridge = 0;
  if (Settings::Bridge.Is(RAINBOWBRIDGE_TOKENS)) {
    maxBridge = Settings::BridgeTokenCount.Value<u8>();
  }
  //Get the max amount of GS which could be useful from token reward locations
  int maxUseful = 0;
  //If the highest advancement item is a token, we know it is useless since it won't lead to an otherwise useful item
  if (Kak_50GoldSkulltulaReward.GetPlacedItem().IsAdvancement() && Kak_50GoldSkulltulaReward.GetPlacedItem().GetItemType() != ITEMTYPE_TOKEN) {
    maxUseful = 50;
  }
  else if (Kak_40GoldSkulltulaReward.GetPlacedItem().IsAdvancement() && Kak_40GoldSkulltulaReward.GetPlacedItem().GetItemType() != ITEMTYPE_TOKEN) {
    maxUseful = 40;
  }
  else if (Kak_30GoldSkulltulaReward.GetPlacedItem().IsAdvancement() && Kak_30GoldSkulltulaReward.GetPlacedItem().GetItemType() != ITEMTYPE_TOKEN) {
    maxUseful = 30;
  }
  else if (Kak_20GoldSkulltulaReward.GetPlacedItem().IsAdvancement() && Kak_20GoldSkulltulaReward.GetPlacedItem().GetItemType() != ITEMTYPE_TOKEN) {
    maxUseful = 20;
  }
  else if (Kak_10GoldSkulltulaReward.GetPlacedItem().IsAdvancement() && Kak_10GoldSkulltulaReward.GetPlacedItem().GetItemType() != ITEMTYPE_TOKEN) {
    maxUseful = 10;
  }
  //Return max of the two possible reasons tokens could be important
  return std::max(maxUseful, maxBridge);
}

enum SearchMode {REACHABILITY_SEARCH, GENERATE_PLAYTHROUGH, CHECK_BEATABLE};

static std::vector<ItemLocation*> GetAccessibleLocations(std::vector<ItemLocation*> allowedLocations, SearchMode mode = REACHABILITY_SEARCH) {

  std::vector<ItemLocation*> accessibleLocations = {};

  //Reset all access to begin a new search
  ApplyStartingInventory();
  Exits::AccessReset();
  LocationReset();
  Logic::UpdateHelpers();
  std::vector<Exit *> exitPool = {&Exits::Root};

  //Variables for playthrough
  int gsCount = 0;
  const int maxGsCount = GENERATE_PLAYTHROUGH ? GetMaxGSCount() : 0; //If generating playthrough want the max that's possibly useful, else doesn't matter
  bool bombchusFound = false;
  std::vector<std::string> buyIgnores;
  //Variables for search
  std::vector<ItemLocation *> newItemLocations;
  bool firstIteration = true;
  //If no new items are found, then the next iteration won't provide any new location
  while(newItemLocations.size() > 0 || firstIteration) {
    firstIteration = false;;

    //Add items found during previous search iteration to logic
    for (ItemLocation* location : newItemLocations) {
      location->ApplyPlacedItemEffect();
    }
    newItemLocations.clear();

    std::vector<ItemLocation *> sphere;

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

        //for each ItemLocation in this area
        for (size_t k = 0; k < area->locations.size(); k++) {
          ItemLocationPairing& locPair = area->locations[k];
          ItemLocation* location = locPair.GetLocation();

          if ((locPair.ConditionsMet() || Settings::Logic.Is(LOGIC_NONE)) && !location->IsAddedToPool()) {

            location->AddToPool();

            if (location->GetPlacedItem() == NoItem) {
              accessibleLocations.push_back(location); //Empty location, consider for placement
            } else {
              newItemLocations.push_back(location); //Add item to cache to be considered in logic next iteration
            }

            //Playthrough stuff
            //Generate the playthrough, so we want to add important items, unless we know to ignore them
            if (mode == GENERATE_PLAYTHROUGH) {
              //Item is an advancement item, figure out if it should be added to this sphere
              if (!playthroughBeatable && location->GetPlacedItem().IsAdvancement()) {
                ItemType type = location->GetPlacedItem().GetItemType();
                std::string itemName(location->GetPlacedItem().GetName());
                bool bombchus = itemName.find("Bombchu") != std::string::npos; //Is a bombchu location
                
                //Decide whether to exclude this location
                //This preprocessing is done to reduce the amount of searches performed in PareDownPlaythrough
                //Want to exclude:
                //1) Tokens after the last potentially useful one (the last one that gives an advancement item)
                //2) Bombchus after the first (including buy bombchus)
                //3) Buy items of the same type, after the first (So only see Buy Deku Nut once)
                bool exclude = true;
                //Exclude tokens after the last possibly useful one
                if (type == ITEMTYPE_TOKEN && gsCount < maxGsCount) {
                  gsCount++;
                  exclude = false;
                }
                //Only print first bombchu location found
                else if (bombchus && !bombchusFound) {
                  bombchusFound = true;
                  exclude = false;
                }
                //Handle buy items
                else if (!(bombchus && bombchusFound) && type == ITEMTYPE_SHOP) {
                  //Only check each buy item once
                  std::string buyItem = itemName.erase(0, 4); //Delete "Buy "
                  //Delete amount, if present
                  if (buyItem.find("(") != std::string::npos) {
                    buyItem = buyItem.erase(buyItem.find("(")); 
                  }
                  //Buy item not in list to ignore, add it to list and write to playthrough
                  if (std::find(buyIgnores.begin(), buyIgnores.end(), buyItem) == buyIgnores.end()) {
                    exclude = false;
                    buyIgnores.push_back(buyItem);
                  }
                }
                else if (!bombchus && type != ITEMTYPE_TOKEN && type != ITEMTYPE_SHOP) {
                  exclude = false;
                }

                if (!exclude) {
                  sphere.push_back(location);
                }
              }
              //Triforce has been found, seed is beatable, nothing else in this or future spheres matters
              else if (location->GetPlacedItem().GetName() == "Triforce") {
                sphere.clear(); 
                sphere.push_back(location);
                playthroughBeatable = true;
              }
            }
            //All we care about is if the game is beatable, used to pare down playthrough
            else if (mode == CHECK_BEATABLE && location->GetPlacedItem().GetName() == "Triforce") {
              playthroughBeatable = true;
              return {};
            }
          }
        }
      }
    }

    erase_if(exitPool, [](Exit* e){ return e->AllAccountedFor();});

    if (mode == GENERATE_PLAYTHROUGH && sphere.size() > 0) {
      playthroughLocations.push_back(sphere);
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
  GetAccessibleLocations(allLocations, GENERATE_PLAYTHROUGH);
}

//Remove unnecessary items from playthrough by removing their location, and checking if game is still beatable
//To reduce searches, some preprocessing done in playthrough generation to avoid adding obviously unnecessary items
static void PareDownPlaythrough() {
  for(int i = playthroughLocations.size() - 2; i >= 0; i--) {

  }
}

static void FastFill(std::vector<Item> items, std::vector<ItemLocation*> locations) {

  //Place everything randomly
  while (!locations.empty()) {

    PlaceItemInLocation(RandomElement(locations, true), RandomElement(items, true));

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

  if (items.size() > allowedLocations.size()) {
    printf("\x1b[H1;1ERROR: MORE ITEMS THAN LOCATIONS");
  }

  //keep retrying to place everything until it works
  bool unsuccessfulPlacement = false;
  std::vector<ItemLocation*> attemptedLocations = {};
  do {
    unsuccessfulPlacement = false;
    std::vector<Item> itemsToPlace = items;

    //copy all not yet placed advancement items so that we can apply their effects for the fill algorithm
    std::vector<Item> itemsToNotPlace = FilterFromPool(ItemPool, [](const Item& i){ return i .IsAdvancement();});

    //shuffle the order of items to place
    Shuffle(itemsToPlace);

    while (!itemsToPlace.empty()) {
      Item item = std::move(itemsToPlace.back());
      item.SetAsPlaythrough();
      itemsToPlace.pop_back();

      //assume we have all unplaced items
      LogicReset();
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

        PlacementLog_Write();

        //reset any locations that got an item
        for (ItemLocation* loc : attemptedLocations) {
          loc->SetPlacedItem(NoItem);
          itemsPlaced--;
        }
        attemptedLocations.clear();

        unsuccessfulPlacement = true;
        break;
      }

      //place the item within one of the allowed locations
      ItemLocation* selectedLocation = RandomElement(accessibleLocations, false);
      PlaceItemInLocation(selectedLocation, item);
      attemptedLocations.push_back(selectedLocation);

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

//Fill in dungeon items that have to be within their own dungeon
static void RandomizeOwnDungeon(Category dungeon, const Item bossKey, const Item map, const Item compass, const Item smallKey, u8 keyCount) {

  std::vector<ItemLocation*> dungeonLocations = FilterFromPool(allLocations, [dungeon](ItemLocation* loc){
    //prevent accidentally placing a map or compass at Sheik in Ice Cavern if a song needs to go there
    if (dungeon == Category::cIceCavern && loc->GetName() == "Sheik in Ice Cavern" && ShuffleSongs.IsNot(SONGSHUFFLE_ANYWHERE)) {
      return false;
    }

    //prevent using dungeon reward locations when songs need to go there
    if (ShuffleSongs.Is(SONGSHUFFLE_DUNGEON_REWARDS) && (loc->IsCategory(Category::cBossHeart) ||
       loc->GetName() == "Gerudo Training Grounds MQ Ice Arrows Chest" ||
       loc->GetName() == "Gerudo Training Grounds Maze Path Final Chest" ||
       loc->GetName() == "Bottom of the Well Lens of Truth Chest" ||
       loc->GetName() == "Bottom of the Well MQ Lens of Truth Chest")) {
      return false;
    }
    return loc->IsCategory(dungeon);
  });
  std::vector<Item> dungeonItems = {};

  if (Keysanity.Is(KEYSANITY_OWN_DUNGEON) && keyCount > 0) {
    AddItemToPool(dungeonItems, smallKey, keyCount);
  }

  if ((BossKeysanity.Is(BOSSKEYSANITY_OWN_DUNGEON) && dungeon != Category::cGanonsCastle && bossKey != NoItem) ||
      (GanonsBossKey.Is(GANONSBOSSKEY_OWN_DUNGEON) && dungeon == Category::cGanonsCastle)) {
        AddItemToPool(dungeonItems, bossKey);
  }

  //randomize boss key and small keys together for even distribution
  AssumedFill(dungeonItems, dungeonLocations);

  //randomize map and compass separately since they're not progressive
  if (MapsAndCompasses.Is(MAPSANDCOMPASSES_OWN_DUNGEON) && map != NoItem) {
    AssumedFill({map, compass}, dungeonLocations);
  }
}

static void RandomizeOwnDungeonItems() {
  //variable to hold Vanilla/MQ key count for each dungeon
  u8 keyCount = 0;

  //                  dungeon category         boss key, map,                compass,             small key, key count
  RandomizeOwnDungeon(Category::cDekuTree,       NoItem, DekuTree_Map,       DekuTree_Compass,       NoItem, keyCount);
  RandomizeOwnDungeon(Category::cDodongosCavern, NoItem, DodongosCavern_Map, DodongosCavern_Compass, NoItem, keyCount);
  RandomizeOwnDungeon(Category::cJabuJabusBelly, NoItem, JabuJabusBelly_Map, JabuJabusBelly_Compass, NoItem, keyCount);

  keyCount = (ForestTempleDungeonMode) ? 6 : 5; //MQ key count : Vanilla key count
  RandomizeOwnDungeon(Category::cForestTemple, ForestTemple_BossKey, ForestTemple_Map, ForestTemple_Compass, ForestTemple_SmallKey, keyCount);

  keyCount = (FireTempleDungeonMode) ? 5 : 8;
  RandomizeOwnDungeon(Category::cFireTemple, FireTemple_BossKey, FireTemple_Map, FireTemple_Compass, FireTemple_SmallKey, keyCount);

  keyCount = (WaterTempleDungeonMode) ? 2 : 6;
  RandomizeOwnDungeon(Category::cWaterTemple, WaterTemple_BossKey, WaterTemple_Map, WaterTemple_Compass, WaterTemple_SmallKey, keyCount);

  keyCount = (SpiritTempleDungeonMode) ? 7 : 5;
  RandomizeOwnDungeon(Category::cSpiritTemple, SpiritTemple_BossKey, SpiritTemple_Map, SpiritTemple_Compass, SpiritTemple_SmallKey, keyCount);

  keyCount = (ShadowTempleDungeonMode) ? 6 : 4; //TEMPORARY FIX FOR FREESTANDING KEY CRASH, VANILLA SHOULD BE 5
  RandomizeOwnDungeon(Category::cShadowTemple, ShadowTemple_BossKey, ShadowTemple_Map, ShadowTemple_Compass, ShadowTemple_SmallKey, keyCount);

  keyCount = (BottomOfTheWellDungeonMode) ? 2 : 3;
  RandomizeOwnDungeon(Category::cBottomOfTheWell, NoItem, BottomOfTheWell_Map, BottomOfTheWell_Compass, BottomOfTheWell_SmallKey, keyCount);

  keyCount = (IceCavernDungeonMode) ? 0 : 0;
  RandomizeOwnDungeon(Category::cIceCavern, NoItem, IceCavern_Map, IceCavern_Compass, NoItem, keyCount);

  keyCount = (GerudoTrainingGroundsDungeonMode) ? 3 : 8;//TEMPORARY FIX FOR FREESTANDING KEY CRASH, VANILLA SHOULD BE 9
  RandomizeOwnDungeon(Category::cGerudoTrainingGrounds, NoItem, NoItem, NoItem, GerudoTrainingGrounds_SmallKey, keyCount);

  keyCount = (GanonsCastleDungeonMode) ? 3 : 2;
  RandomizeOwnDungeon(Category::cGanonsCastle, GanonsCastle_BossKey, NoItem, NoItem, GanonsCastle_SmallKey, keyCount);
}

int Fill() {
  int retries = 0;
  while(retries < 5) {
    GenerateLocationPool();
    GenerateItemPool();
    GenerateStartingInventory();
    RemoveStartingItemsFromPool();
    RandomizeDungeonRewards();
    FillExcludedLocations();
    RandomizeOwnDungeonItems();

    //Place songs first if song shuffle is set to specific locations
    if (ShuffleSongs.IsNot(SONGSHUFFLE_ANYWHERE)) {

      //Get each song
      std::vector<Item> songs = FilterAndEraseFromPool(ItemPool, [](const Item& i) { return i.GetItemType() == ITEMTYPE_SONG;});

      //Get each song location
      std::vector<ItemLocation*> songLocations = {};
      if (ShuffleSongs.Is(SONGSHUFFLE_SONG_LOCATIONS)) {
        songLocations = FilterFromPool(allLocations, [](ItemLocation * loc){ return loc->IsCategory(Category::cSong);});

      } else if (ShuffleSongs.Is(SONGSHUFFLE_DUNGEON_REWARDS)) {
        songLocations = FilterFromPool(allLocations, [](ItemLocation * loc){ return loc->IsCategory(Category::cSongDungeonReward);});
      }

      AssumedFill(songs, songLocations);
    }

    //Then place the rest of the advancement items
    std::vector<Item> remainingAdvancementItems = FilterAndEraseFromPool(ItemPool, [](const Item& i) { return i.IsAdvancement();});
    AssumedFill(remainingAdvancementItems, allLocations);

    //Fast fill for the rest of the pool
    std::vector<Item> remainingPool = FilterAndEraseFromPool(ItemPool, [](const Item& i) {return true;});
    LogicReset();
    FastFill(remainingPool, GetAccessibleLocations(allLocations));

    LogicReset();
    GeneratePlaythrough();
    //Successful placement, produced beatable result
    if(playthroughBeatable) {
      PareDownPlaythrough();
      printf("Done");
      return 1;
    }
    //Unsuccessful placement
    if(retries < 4) {
      printf("\x1b[9;10HFailed. Retrying... %d", retries+2);
      Exits::ResetAllLocations();
      LogicReset();
      playthroughLocations.clear();
    }
    retries++;
  }
  //All retries failed
  return -1;
}
