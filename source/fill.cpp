#include "fill.hpp"

#include "custom_messages.hpp"
#include "dungeon.hpp"
#include "item_location.hpp"
#include "item_pool.hpp"
#include "location_access.hpp"
#include "logic.hpp"
#include "random.hpp"
#include "spoiler_log.hpp"
#include "starting_inventory.hpp"
#include "hints.hpp"
#include "hint_list.hpp"
#include "shops.hpp"
#include "debug.hpp"

#include <vector>

using namespace CustomMessages;
using namespace Logic;
using namespace Settings;

static void RemoveStartingItemsFromPool() {
  for (ItemKey startingItem : StartingInventory) {
    for (size_t i = 0; i < ItemPool.size(); i++) {
      if (startingItem == ItemPool[i] || (ItemTable(startingItem).IsBottleItem() && ItemTable(ItemPool[i]).IsBottleItem())) {
        ItemPool[i] = GetJunkItem();
        break;
      }
    }
  }
}

//This function will propogate Time of Day access as the specified age to the
//new exit through the world.
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

//Get the max number of tokens that can possibly be useful
static int GetMaxGSCount() {
  //If bridge is set to tokens, get how many are required
  int maxBridge = 0;
  if (Settings::Bridge.Is(RAINBOWBRIDGE_TOKENS)) {
    maxBridge = Settings::BridgeTokenCount.Value<u8>();
  }
  //Get the max amount of GS which could be useful from token reward locations
  int maxUseful = 0;
  //If the highest advancement item is a token, we know it is useless since it won't lead to an otherwise useful item
  if (Location(KAK_50_GOLD_SKULLTULA_REWARD)->GetPlacedItem().IsAdvancement() && Location(KAK_50_GOLD_SKULLTULA_REWARD)->GetPlacedItem().GetItemType() != ITEMTYPE_TOKEN) {
    maxUseful = 50;
  }
  else if (Location(KAK_40_GOLD_SKULLTULA_REWARD)->GetPlacedItem().IsAdvancement() && Location(KAK_40_GOLD_SKULLTULA_REWARD)->GetPlacedItem().GetItemType() != ITEMTYPE_TOKEN) {
    maxUseful = 40;
  }
  else if (Location(KAK_30_GOLD_SKULLTULA_REWARD)->GetPlacedItem().IsAdvancement() && Location(KAK_30_GOLD_SKULLTULA_REWARD)->GetPlacedItem().GetItemType() != ITEMTYPE_TOKEN) {
    maxUseful = 30;
  }
  else if (Location(KAK_20_GOLD_SKULLTULA_REWARD)->GetPlacedItem().IsAdvancement() && Location(KAK_20_GOLD_SKULLTULA_REWARD)->GetPlacedItem().GetItemType() != ITEMTYPE_TOKEN) {
    maxUseful = 20;
  }
  else if (Location(KAK_10_GOLD_SKULLTULA_REWARD)->GetPlacedItem().IsAdvancement() && Location(KAK_10_GOLD_SKULLTULA_REWARD)->GetPlacedItem().GetItemType() != ITEMTYPE_TOKEN) {
    maxUseful = 10;
  }
  //Return max of the two possible reasons tokens could be important
  return std::max(maxUseful, maxBridge);
}

//This function will return a vector of ItemLocations that are accessible with
//where items have been placed so far within the world. The allowedLocations argument
//specifies the pool of locations that we're trying to search for an accessible location in
std::vector<LocationKey> GetAccessibleLocations(const std::vector<LocationKey>& allowedLocations,
                                                  SearchMode mode) {
  std::vector<LocationKey> accessibleLocations;

  //Reset all access to begin a new search
  ApplyStartingInventory();
  Exits::AccessReset();
  LocationReset();
  Logic::UpdateHelpers();
  std::vector<Exit *> exitPool = {&Exits::Root};

  //Variables for playthrough
  int gsCount = 0;
  const int maxGsCount = mode == SearchMode::GeneratePlaythrough ? GetMaxGSCount() : 0; //If generating playthrough want the max that's possibly useful, else doesn't matter
  bool bombchusFound = false;
  std::vector<std::string> buyIgnores;
  //Variables for search
  std::vector<LocationKey> newItemLocations;
  bool firstIteration = true;


  //If no new items are found and no events are updated, then the next iteration won't provide any new location
  while (newItemLocations.size() > 0 || EventsUpdated() || firstIteration) {
    firstIteration = false;

    //Add items found during previous search iteration to logic
    for (LocationKey loc : newItemLocations) {
      Location(loc)->ApplyPlacedItemEffect();
    }

    newItemLocations.clear();

    std::vector<LocationKey> sphere;

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
          LocationKey loc = locPair.GetLocation();

          if ((locPair.ConditionsMet() || Settings::Logic.Is(LOGIC_NONE)) && !(Location(loc)->IsAddedToPool())) {

            Location(loc)->AddToPool();

            if (Location(loc)->GetPlacedItemKey() == NONE) {
              accessibleLocations.push_back(loc); //Empty location, consider for placement
            } else {
              newItemLocations.push_back(loc); //Add item to cache to be considered in logic next iteration
            }

            //Playthrough stuff
            //Generate the playthrough, so we want to add advancement items, unless we know to ignore them
            if (mode == SearchMode::GeneratePlaythrough) {
              //Item is an advancement item, figure out if it should be added to this sphere
              if (!playthroughBeatable && Location(loc)->GetPlacedItem().IsAdvancement()) {
                ItemType type = Location(loc)->GetPlacedItem().GetItemType();
                std::string itemName(Location(loc)->GetPlacedItemName());
                bool bombchus = itemName.find("Bombchu") != std::string::npos; //Is a bombchu location

                //Decide whether to exclude this location
                //This preprocessing is done to reduce the amount of searches performed in PareDownPlaythrough
                //Want to exclude:
                //1) Tokens after the last potentially useful one (the last one that gives an advancement item or last for token bridge)
                //2) Bombchus after the first (including buy bombchus)
                //3) Buy items of the same type, after the first (So only see Buy Deku Nut of any amount once)
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
                  //Delete amount, if present (so when it looks like Buy Deku Nut (10) remove the (10))
                  if (buyItem.find("(") != std::string::npos) {
                    buyItem = buyItem.erase(buyItem.find("("));
                  }
                  //Buy item not in list to ignore, add it to list and write to playthrough
                  if (std::find(buyIgnores.begin(), buyIgnores.end(), buyItem) == buyIgnores.end()) {
                    exclude = false;
                    buyIgnores.push_back(buyItem);
                  }
                }
                //Add all other advancement items
                else if (!bombchus && type != ITEMTYPE_TOKEN && type != ITEMTYPE_SHOP) {
                  exclude = false;
                }
                //Has not been excluded, add to playthrough
                if (!exclude) {
                  sphere.push_back(loc);
                }
              }
              //Triforce has been found, seed is beatable, nothing else in this or future spheres matters
              else if (Location(loc)->GetPlacedItemKey() == TRIFORCE) {
                sphere.clear();
                sphere.push_back(loc);
                playthroughBeatable = true;
              }
            }
            //All we care about is if the game is beatable, used to pare down playthrough
            else if (mode == SearchMode::CheckBeatable && Location(loc)->GetPlacedItemKey() == TRIFORCE) {
              playthroughBeatable = true;
              return {}; //Return early for efficiency
            }
          }
        }
      }
    }

    erase_if(exitPool, [](Exit* e){ return e->AllAccountedFor();});

    if (mode == SearchMode::GeneratePlaythrough && sphere.size() > 0) {
      playthroughLocations.push_back(sphere);
    }

  }
  //CitraPrint("Accessible Locations: ");
  erase_if(accessibleLocations, [&allowedLocations](LocationKey loc){
    //CitraPrint(Location(loc)->GetName());
    for (LocationKey allowedLocation : allowedLocations) {
      if (loc == allowedLocation) {
        return false;
      }
    }
    return true;
  });
  return accessibleLocations;
}

static void GeneratePlaythrough() {
  GetAccessibleLocations(allLocations, SearchMode::GeneratePlaythrough);
}

//Remove unnecessary items from playthrough by removing their location, and checking if game is still beatable
//To reduce searches, some preprocessing is done in playthrough generation to avoid adding obviously unnecessary items
static void PareDownPlaythrough() {
  std::vector<LocationKey> toAddBackItem;
  //Start at sphere before Ganon's and count down
  for (int i = playthroughLocations.size() - 2; i >= 0; i--) {
    //Check each item location in sphere
    std::vector<int> erasableIndices;
    std::vector<LocationKey> sphere = playthroughLocations.at(i);
    for (int j = sphere.size() - 1; j >= 0; j--) {
      LocationKey loc = sphere.at(j);
      ItemKey copy = Location(loc)->GetPlacedItemKey(); //Copy out item
      Location(loc)->SetPlacedItem(NONE); //Write in empty item
      playthroughBeatable = false;
      LogicReset();
      GetAccessibleLocations(allLocations, SearchMode::CheckBeatable); //Check if game is still beatable

      //Playthrough is still beatable without this item, therefore it can be removed from playthrough section.
      if (playthroughBeatable) {
        //Uncomment to print playthrough deletion log in citra
        // std::string locationname(copy.GetName());
        // std::string itemname(Location(loc)->GetName());
        // std::string removallog = locationname + " at " + itemname + " removed from playthrough";
        // svcOutputDebugString(removallog.c_str(), removallog.length());
        playthroughLocations[i].erase(playthroughLocations[i].begin() + j);
        Location(loc)->SetDelayedItem(copy); //Game is still beatable, don't add back until later
        toAddBackItem.push_back(loc);
      }
      else {
        Location(loc)->SetPlacedItem(copy); //Immediately put item back so game is beatable again
      }
    }
  }

  //Some spheres may now be empty, remove these
  for (int i = playthroughLocations.size() - 2; i >= 0; i--) {
    if (playthroughLocations.at(i).size() == 0) {
      playthroughLocations.erase(playthroughLocations.begin() + i);
    }
  }

  //Now we can add back items which were removed previously
  for (LocationKey loc : toAddBackItem) {
    Location(loc)->SaveDelayedItem();
  }
}

//Very similar to PareDownPlaythrough except it creates the list of Way of the Hero items
//Way of the Hero items are more specific than playthrough items in that they are items which *must*
// be obtained to logically be able to complete the seed, rather than playthrough items which 
// are just possible items you *can* collect to complete the seed.
static void CalculateWotH() {
  //First copy locations from the 2-dimensional playthroughLocations into the 1-dimensional wothLocations
  //size - 1 so Triforce is not counted
  for (size_t i = 0; i < playthroughLocations.size() - 1; i++) {
    for (size_t j = 0; j < playthroughLocations[i].size(); j++) {
      wothLocations.push_back(playthroughLocations[i][j]);
    }
  }

  //For hint purposes, we want to exclude unshuffled items from WotH
  //Also helps so less reachability searches will be required
  for (int i = wothLocations.size() - 1; i >= 0; i--) {
    ItemKey item = Location(wothLocations[i])->GetPlacedItemKey();
    if (item == GOLD_SKULLTULA_TOKEN && Tokensanity.Is(TOKENSANITY_OFF)) {
      wothLocations.erase(wothLocations.begin() + i);
    } else if (item == KOKIRI_SWORD && !ShuffleKokiriSword) {
      wothLocations.erase(wothLocations.begin() + i);
    } else if (item == WEIRD_EGG && !ShuffleWeirdEgg) {
      wothLocations.erase(wothLocations.begin() + i);
    } else if (item == PROGRESSIVE_OCARINA && !ShuffleOcarinas) {
      wothLocations.erase(wothLocations.begin() + i);
    } else if (item == GERUDO_TOKEN && !ShuffleGerudoToken) {
      wothLocations.erase(wothLocations.begin() + i);
    } else if (ItemTable(item).GetItemType() == ITEMTYPE_DUNGEONREWARD && ShuffleRewards.Is(REWARDSHUFFLE_END_OF_DUNGEON)) {
      wothLocations.erase(wothLocations.begin() + i);
    //Keys only count if their respective -sanity is enabled, including overworld or any dungeon only
    } else if (ItemTable(item).GetItemType() == ITEMTYPE_SMALLKEY && (Keysanity.Is(KEYSANITY_START_WITH) || Keysanity.Is(KEYSANITY_VANILLA) || Keysanity.Is(KEYSANITY_OWN_DUNGEON))) {
      wothLocations.erase(wothLocations.begin() + i);
    } else if (item == GANONS_CASTLE_BOSS_KEY && !(GanonsBossKey.Is(GANONSBOSSKEY_ANYWHERE) || GanonsBossKey.Is(GANONSBOSSKEY_OVERWORLD) || GanonsBossKey.Is(GANONSBOSSKEY_ANY_DUNGEON))) {
      wothLocations.erase(wothLocations.begin() + i);
    } else if (ItemTable(item).GetItemType() == ITEMTYPE_BOSSKEY && (BossKeysanity.Is(KEYSANITY_START_WITH) || BossKeysanity.Is(KEYSANITY_VANILLA) || BossKeysanity.Is(KEYSANITY_OWN_DUNGEON))) {
      wothLocations.erase(wothLocations.begin() + i);
    } else if (item == GERUDO_FORTRESS_SMALL_KEY && GerudoKeys.Is(GERUDOKEYS_VANILLA)) {
      wothLocations.erase(wothLocations.begin() + i);
    //Should be erased regardless of settings
    } else if (item == MAGIC_BEAN || item == ZELDAS_LETTER) {
      wothLocations.erase(wothLocations.begin() + i);
    }
  }

  //Now go through and check each location, seeing if it is strictly necessary for game completion
  for (int i = wothLocations.size() - 1; i >= 0; i--) {
    LocationKey loc = wothLocations[i];
    ItemKey copy = Location(loc)->GetPlacedItemKey(); //Copy out item
    Location(loc)->SetPlacedItem(NONE); //Write in empty item
    playthroughBeatable = false;
    LogicReset();
    GetAccessibleLocations(allLocations, SearchMode::CheckBeatable); //Check if game is still beatable
    Location(loc)->SetPlacedItem(copy); //Immediately put item back
    //If removing this item and no other item caused the game to become unbeatable, then it is strictly necessary, so keep it
    //Else, delete from wothLocations
    if (playthroughBeatable) {
      wothLocations.erase(wothLocations.begin() + i);
    }
  }

  playthroughBeatable = true;
  //Do one last GetAccessibleLocations to avoid "NOT ADDED" in spoiler
  LogicReset();
  GetAccessibleLocations(allLocations);
}

//Will place things completely randomly, no logic checks are performed
static void FastFill(std::vector<ItemKey> items, std::vector<LocationKey> locations) {

  while (!locations.empty()) {

    LocationKey loc = RandomElement(locations, true);
    Location(loc)->SetAsHintable();
    PlaceItemInLocation(loc, RandomElement(items, true));

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
static void AssumedFill(const std::vector<ItemKey>& items, const std::vector<LocationKey>& allowedLocations, bool setLocationsAsHintable = false) {
  if (items.size() > allowedLocations.size()) {
    printf("\x1b[2;2HERROR: MORE ITEMS THAN LOCATIONS IN GIVEN LISTS");
    PlacementLog_Msg("Items:\n");
    for (const ItemKey item: items) {
      PlacementLog_Msg("\t");
      PlacementLog_Msg(ItemTable(item).GetName());
      PlacementLog_Msg("\n");
    }
    PlacementLog_Msg("\nAllowed Locations:\n");
    for (const LocationKey loc: allowedLocations) {
      PlacementLog_Msg("\t");
      PlacementLog_Msg(Location(loc)->GetName());
      PlacementLog_Msg("\n");
    }
  }

  //keep retrying to place everything until it works
  bool unsuccessfulPlacement = false;
  std::vector<LocationKey> attemptedLocations;
  do {
    unsuccessfulPlacement = false;
    std::vector<ItemKey> itemsToPlace = items;

    //copy all not yet placed advancement items so that we can apply their effects for the fill algorithm
    std::vector<ItemKey> itemsToNotPlace = FilterFromPool(ItemPool, [](const ItemKey i){ return ItemTable(i).IsAdvancement();});

    //shuffle the order of items to place
    Shuffle(itemsToPlace);
    while (!itemsToPlace.empty()) {
      ItemKey item = std::move(itemsToPlace.back());
      ItemTable(item).SetAsPlaythrough();
      itemsToPlace.pop_back();

      //assume we have all unplaced items
      LogicReset();
      for (ItemKey unplacedItem : itemsToPlace) {
        ItemTable(unplacedItem).ApplyEffect();
      }
      for (ItemKey unplacedItem : itemsToNotPlace) {
        ItemTable(unplacedItem).ApplyEffect();
      }

      //get all accessible locations that are allowed
      const std::vector<LocationKey> accessibleLocations = GetAccessibleLocations(allowedLocations);

      // CitraPrint("\nPLACING ITEM: ");
      // CitraPrint(ItemTable(item).GetName());
      // CitraPrint("Allowed Locations: ");
      // for (const LocationKey loc : accessibleLocations) {
      //   CitraPrint(Location(loc)->GetName());
      // }

      //retry if there are no more locations to place items
      if (accessibleLocations.empty()) {

        PlacementLog_Msg("\nCANNOT PLACE ");
        PlacementLog_Msg(ItemTable(item).GetName());
        PlacementLog_Msg(". TRYING AGAIN...\n");

        #ifdef ENABLE_DEBUG
          PlacementLog_Write();
        #endif

        //reset any locations that got an item
        for (LocationKey loc : attemptedLocations) {
          Location(loc)->SetPlacedItem(NONE);
          itemsPlaced--;
        }
        attemptedLocations.clear();

        unsuccessfulPlacement = true;
        break;
      }

      //place the item within one of the allowed locations
      LocationKey selectedLocation = RandomElement(accessibleLocations);
      PlaceItemInLocation(selectedLocation, item);
      attemptedLocations.push_back(selectedLocation);

      //This tells us the location went through the randomization algorithm
      //to distinguish it from locations which did not or that the player already
      //knows
      if (setLocationsAsHintable) {
        Location(selectedLocation)->SetAsHintable();
      }
    }
  } while (unsuccessfulPlacement);
}

//This function will specifically randomize dungeon rewards for the End of Dungeons
//setting, or randomize one dungeon reward to Link's Pocket if that setting is on
static void RandomizeDungeonRewards() {

  //quest item bit mask of each stone/medallion for the savefile
  static constexpr std::array<u32, 9> bitMaskTable = {
    0x00040000, //Kokiri Emerald
    0x00080000, //Goron Ruby
    0x00100000, //Zora Sapphire
    0x00000001, //Forest Medallion
    0x00000002, //Fire Medallion
    0x00000004, //Water Medallion
    0x00000008, //Spirit Medallion
    0x00000010, //Shadow Medallion
    0x00000020, //Light Medallion
  };
  int baseOffset = ItemTable(KOKIRI_EMERALD).GetItemID();

  //End of Dungeons includes Link's Pocket
  if (ShuffleRewards.Is(REWARDSHUFFLE_END_OF_DUNGEON)) {
    //get stones and medallions
    std::vector<ItemKey> rewards = FilterAndEraseFromPool(ItemPool, [](const ItemKey i) {return ItemTable(i).GetItemType() == ITEMTYPE_DUNGEONREWARD;});
    AssumedFill(rewards, dungeonRewardLocations);
    for (size_t i = 0; i < dungeonRewardLocations.size(); i++) {
      const auto index = Location(dungeonRewardLocations[i])->GetPlacedItem().GetItemID() - baseOffset;
      rDungeonRewardOverrides[i] = index;

      //set the player's dungeon reward on file creation instead of pushing it to them at the start.
      //This is done mainly because players are already familiar with seeing their dungeon reward
      //before opening up their file
      if (i == dungeonRewardLocations.size()-1) {
        LinksPocketRewardBitMask = bitMaskTable[index];
      }
    }
  } else if (LinksPocketItem.Is(LINKSPOCKETITEM_DUNGEON_REWARD)) {
    //get 1 stone/medallion
    std::vector<ItemKey> rewards = FilterFromPool(ItemPool, [](const ItemKey i) {return ItemTable(i).GetItemType() == ITEMTYPE_DUNGEONREWARD;});
    ItemKey startingReward = RandomElement(rewards, true);

    LinksPocketRewardBitMask = bitMaskTable[ItemTable(startingReward).GetItemID() - baseOffset];
    PlaceItemInLocation(LINKS_POCKET, startingReward);
    //erase the stone/medallion from the Item Pool
    FilterAndEraseFromPool(ItemPool, [startingReward](const ItemKey i) {return i == startingReward;});
  }
}

//Fills any locations excluded by the player with junk items so that advancement items
//can't be placed there.
static void FillExcludedLocations() {
  //Only fill in excluded locations that don't already have something and are forbidden
  std::vector<LocationKey> excludedLocations = FilterFromPool(allLocations, [](const LocationKey loc){
    return Location(loc)->IsExcluded();
  });

  for (LocationKey loc : excludedLocations) {
    PlaceJunkInExcludedLocation(loc);
  }
}

//Function to handle the Own Dungeon setting
static void RandomizeOwnDungeon(const Dungeon::DungeonInfo* dungeon) {
  std::vector<LocationKey> dungeonLocations = dungeon->GetDungeonLocations();
  std::vector<ItemKey> dungeonItems;

  //filter out locations that may be required to have songs placed at them
  dungeonLocations = FilterFromPool(dungeonLocations, [](const LocationKey loc){
    if (ShuffleSongs.Is(SONGSHUFFLE_SONG_LOCATIONS)) {
      return !(Location(loc)->IsCategory(Category::cSong));
    }
    if (ShuffleSongs.Is(SONGSHUFFLE_DUNGEON_REWARDS)) {
      return !(Location(loc)->IsCategory(Category::cSongDungeonReward));
    }
    return true;
  });

  //Add specific items that need be randomized within this dungeon
  if (Keysanity.Is(KEYSANITY_OWN_DUNGEON) && dungeon->GetSmallKey() != NONE) {
    std::vector<ItemKey> dungeonSmallKeys = FilterAndEraseFromPool(ItemPool, [dungeon](const ItemKey i){ return i == dungeon->GetSmallKey();});
    AddElementsToPool(dungeonItems, dungeonSmallKeys);
  }

  if ((BossKeysanity.Is(BOSSKEYSANITY_OWN_DUNGEON) && dungeon->GetBossKey() != GANONS_CASTLE_BOSS_KEY) ||
      (GanonsBossKey.Is(GANONSBOSSKEY_OWN_DUNGEON) && dungeon->GetBossKey() == GANONS_CASTLE_BOSS_KEY)) {
        auto dungeonBossKey = FilterAndEraseFromPool(ItemPool, [dungeon](const ItemKey i){ return i == dungeon->GetBossKey();});
        AddElementsToPool(dungeonItems, dungeonBossKey);
  }

  //randomize boss key and small keys together for even distribution
  AssumedFill(dungeonItems, dungeonLocations);

  //randomize map and compass separately since they're not progressive
  if (MapsAndCompasses.Is(MAPSANDCOMPASSES_OWN_DUNGEON) && dungeon->GetMap() != NONE && dungeon->GetCompass() != NONE) {
    auto dungeonMapAndCompass = FilterAndEraseFromPool(ItemPool, [dungeon](const ItemKey i){ return i == dungeon->GetMap() || i == dungeon->GetCompass();});
    AssumedFill(dungeonMapAndCompass, dungeonLocations);
  }
}

/*Randomize items restricted to a certain set of locations.
  The fill order of location groups is as follows:
    - Own Dungeon
    - Any Dungeon
    - Overworld
  Small Keys, Gerudo Keys, Boss Keys, Ganon's Boss Key, and/or dungeon rewards
  will be randomized together if they have the same setting. Maps and Compasses
  are randomized separately once the dungeon advancement items have all been placed.*/
static void RandomizeDungeonItems() {
  using namespace Dungeon;

  //Get Any Dungeon and Overworld group locations
  std::vector<LocationKey> anyDungeonLocations = FilterFromPool(allLocations, [](const LocationKey loc){return Location(loc)->IsDungeon();});
  //overworldLocations defined in item_location.cpp

  //Create Any Dungeon and Overworld item pools
  std::vector<ItemKey> anyDungeonItems;
  std::vector<ItemKey> overworldItems;

  for (auto dungeon : dungeonList) {
    if (Keysanity.Is(KEYSANITY_ANY_DUNGEON)) {
      auto dungeonKeys = FilterAndEraseFromPool(ItemPool, [dungeon](const ItemKey i){return i == dungeon->GetSmallKey();});
      AddElementsToPool(anyDungeonItems, dungeonKeys);
    } else if (Keysanity.Is(KEYSANITY_OVERWORLD)) {
      auto dungeonKeys = FilterAndEraseFromPool(ItemPool, [dungeon](const ItemKey i){return i == dungeon->GetSmallKey();});
      AddElementsToPool(overworldItems, dungeonKeys);
    }

    if (BossKeysanity.Is(BOSSKEYSANITY_ANY_DUNGEON) && dungeon->GetBossKey() != GANONS_CASTLE_BOSS_KEY) {
      auto bossKey = FilterAndEraseFromPool(ItemPool, [dungeon](const ItemKey i){return i == dungeon->GetBossKey();});
      AddElementsToPool(anyDungeonItems, bossKey);
    } else if (BossKeysanity.Is(BOSSKEYSANITY_OVERWORLD) && dungeon->GetBossKey() != GANONS_CASTLE_BOSS_KEY) {
      auto bossKey = FilterAndEraseFromPool(ItemPool, [dungeon](const ItemKey i){return i == dungeon->GetBossKey();});
      AddElementsToPool(overworldItems, bossKey);
    }

    if (GanonsBossKey.Is(GANONSBOSSKEY_ANY_DUNGEON)) {
      auto ganonBossKey = FilterAndEraseFromPool(ItemPool, [](const ItemKey i){return i == GANONS_CASTLE_BOSS_KEY;});
      AddElementsToPool(anyDungeonItems, ganonBossKey);
    } else if (GanonsBossKey.Is(GANONSBOSSKEY_OVERWORLD)) {
      auto ganonBossKey = FilterAndEraseFromPool(ItemPool, [](const ItemKey i){return i == GANONS_CASTLE_BOSS_KEY;});
      AddElementsToPool(overworldItems, ganonBossKey);
    }
  }

  if (GerudoKeys.Is(GERUDOKEYS_ANY_DUNGEON)) {
    auto gerudoKeys = FilterAndEraseFromPool(ItemPool, [](const ItemKey i){return i == GERUDO_FORTRESS_SMALL_KEY;});
    AddElementsToPool(anyDungeonItems, gerudoKeys);
  } else if (GerudoKeys.Is(GERUDOKEYS_OVERWORLD)) {
    auto gerudoKeys = FilterAndEraseFromPool(ItemPool, [](const ItemKey i){return i == GERUDO_FORTRESS_SMALL_KEY;});
    AddElementsToPool(overworldItems, gerudoKeys);
  }

  if (ShuffleRewards.Is(REWARDSHUFFLE_ANY_DUNGEON)) {
    auto rewards = FilterAndEraseFromPool(ItemPool, [](const ItemKey i){return ItemTable(i).GetItemType() == ITEMTYPE_DUNGEONREWARD;});
    AddElementsToPool(anyDungeonItems, rewards);
  } else if (ShuffleRewards.Is(REWARDSHUFFLE_OVERWORLD)) {
    auto rewards = FilterAndEraseFromPool(ItemPool, [](const ItemKey i){return ItemTable(i).GetItemType() == ITEMTYPE_DUNGEONREWARD;});
    AddElementsToPool(overworldItems, rewards);
  }

  //Randomize Any Dungeon and Overworld pools
  AssumedFill(anyDungeonItems, anyDungeonLocations, true);
  AssumedFill(overworldItems, overworldLocations, true);

  //Randomize maps and compasses after since they're not advancement items
  for (auto dungeon : dungeonList) {
    if (MapsAndCompasses.Is(MAPSANDCOMPASSES_ANY_DUNGEON)) {
      auto mapAndCompassItems = FilterAndEraseFromPool(ItemPool, [dungeon](const ItemKey i){return i == dungeon->GetMap() || i == dungeon->GetCompass();});
      AssumedFill(mapAndCompassItems, anyDungeonLocations, true);
    } else if (MapsAndCompasses.Is(MAPSANDCOMPASSES_OVERWORLD)) {
      auto mapAndCompassItems = FilterAndEraseFromPool(ItemPool, [dungeon](const ItemKey i){return i == dungeon->GetMap() || i == dungeon->GetCompass();});
      AssumedFill(mapAndCompassItems, overworldLocations, true);
    }
  }
}

static void RandomizeLinksPocket() {
  if (LinksPocketItem.Is(LINKSPOCKETITEM_ADVANCEMENT)) {
   //Get all the advancement items                                                                                                     don't include tokens
   std::vector<ItemKey> advancementItems = FilterAndEraseFromPool(ItemPool, [](const ItemKey i){return ItemTable(i).IsAdvancement() && ItemTable(i).GetItemType() != ITEMTYPE_TOKEN;});
   //select a random one
   ItemKey startingItem = RandomElement(advancementItems, true);
   //add the others back
   AddElementsToPool(ItemPool, advancementItems);

   PlaceItemInLocation(LINKS_POCKET, startingItem);
 } else if (LinksPocketItem.Is(LINKSPOCKETITEM_NOTHING)) {
   PlaceItemInLocation(LINKS_POCKET, GREEN_RUPEE);
 }
}

int Fill() {
  int retries = 0;
  while(retries < 5) {
    GenerateLocationPool();
    GenerateItemPool();
    GenerateStartingInventory();
    RemoveStartingItemsFromPool();
    FillExcludedLocations();

    //Place shop items first, since a buy shield is needed to place a dungeon reward on Gohma due to access
    if (Shopsanity.Is(SHOPSANITY_OFF)) {
      PlaceVanillaShopItems(); //Place vanilla shop items in vanilla location
    } else {
      int total_replaced = 0;
      if (Shopsanity.IsNot(SHOPSANITY_ZERO)) { //Shopsanity 1-4, random
        //Initialize NonShopItems
        ItemAndPrice init;
        init.Name = "No Item";
        init.Price = -1;
        init.Repurchaseable = false;
        NonShopItems.assign(32, init);
        //Indices from OoTR. So shopsanity one will overwrite 7, three will overwrite 7, 5, 8, etc.
        const std::array<int, 4> indices = {7, 5, 8, 6}; 
        //Overwrite appropriate number of shop items
        for (size_t i = 0; i < ShopLocationLists.size(); i++) {
          int num_to_replace = GetShopsanityReplaceAmount(); //1-4 shop items will be overwritten, depending on settings
          total_replaced += num_to_replace;
          for (int j = 0; j < num_to_replace; j++) {
            int itemindex = indices[j];
            int shopsanityPrice = GetRandomShopPrice();
            NonShopItems[TransformShopIndex(i*8+itemindex-1)].Price = shopsanityPrice; //Set price to be retrieved by the patch and textboxes
            Location(ShopLocationLists[i][itemindex - 1])->SetShopsanityPrice(shopsanityPrice);
          }
        }
      }
      //Get all locations and items that don't have a shopsanity price attached
      std::vector<LocationKey> shopLocations = {};
      //Get as many vanilla shop items as the total number of shop items minus the number of replaced items
      //So shopsanity 0 will get all 64 vanilla items, shopsanity 4 will get 32, etc.
      std::vector<ItemKey> shopItems = GetMinVanillaShopItems(total_replaced);

      for (size_t i = 0; i < ShopLocationLists.size(); i++) {
        for (size_t j = 0; j < ShopLocationLists[i].size(); j++) {
          LocationKey loc = ShopLocationLists[i][j];
          if (!(Location(loc)->HasShopsanityPrice())) {
            shopLocations.push_back(loc);
          }
        }
      }
      //Place the shop items which will still be at shop locations
      AssumedFill(shopItems, shopLocations);
    }

    //Place dungeon rewards
    RandomizeDungeonRewards();

    //Place dungeon items restricted to their Own Dungeon
    for (auto dungeon : Dungeon::dungeonList) {
      RandomizeOwnDungeon(dungeon);
    }

    //Then Place songs if song shuffle is set to specific locations
    if (ShuffleSongs.IsNot(SONGSHUFFLE_ANYWHERE)) {

      //Get each song
      std::vector<ItemKey> songs = FilterAndEraseFromPool(ItemPool, [](const ItemKey i) { return ItemTable(i).GetItemType() == ITEMTYPE_SONG;});

      //Get each song location
      std::vector<LocationKey> songLocations;
      if (ShuffleSongs.Is(SONGSHUFFLE_SONG_LOCATIONS)) {
        songLocations = FilterFromPool(allLocations, [](const LocationKey loc){ return Location(loc)->IsCategory(Category::cSong);});

      } else if (ShuffleSongs.Is(SONGSHUFFLE_DUNGEON_REWARDS)) {
        songLocations = FilterFromPool(allLocations, [](const LocationKey loc){ return Location(loc)->IsCategory(Category::cSongDungeonReward);});
      }

      AssumedFill(songs, songLocations, true);
    }

    //Then place dungeon items that are assigned to restrictive location pools
    RandomizeDungeonItems();

    //Then place Link's Pocket Item if it has to be an advancement item
    RandomizeLinksPocket();
    //Then place the rest of the advancement items
    std::vector<ItemKey> remainingAdvancementItems = FilterAndEraseFromPool(ItemPool, [](const ItemKey i) { return ItemTable(i).IsAdvancement();});
    AssumedFill(remainingAdvancementItems, allLocations, true);

    //Fast fill for the rest of the pool
    std::vector<ItemKey> remainingPool = FilterAndEraseFromPool(ItemPool, [](const ItemKey i) {return true;});
    LogicReset();
    FastFill(remainingPool, GetAccessibleLocations(allLocations));

    LogicReset();
    GeneratePlaythrough();
    //Successful placement, produced beatable result
    if(playthroughBeatable) {
      printf("Done");
      printf("\x1b[9;10HCalculating Playthrough...");
      PareDownPlaythrough();
      CalculateWotH();
      printf("Done");
      CreateOverrides();
      CreateAlwaysIncludedMessages();
      if (GossipStoneHints.IsNot(HINTS_NO_HINTS)) {
        printf("\x1b[10;10HCreating Hints...");
        CreateAllHints();
        printf("Done");
      }
      return 1;
    }
    //Unsuccessful placement
    if(retries < 4) {
      printf("\x1b[9;10HFailed. Retrying... %d", retries+2);
      Exits::ResetAllLocations();
      LogicReset();
      playthroughLocations.clear();
      wothLocations.clear();
    }
    retries++;
  }
  //All retries failed
  return -1;
}
