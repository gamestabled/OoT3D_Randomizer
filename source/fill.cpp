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

#include <vector>

using namespace CustomMessages;
using namespace Logic;
using namespace Settings;

static void RemoveStartingItemsFromPool() {
  for (u32 startingItem : StartingInventory) {
    for (u16 i = 0; i < ItemPool.size(); i++) {
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
  if (ItemTable(Kak_50GoldSkulltulaReward.GetPlacedItem()).IsAdvancement() && ItemTable(Kak_50GoldSkulltulaReward.GetPlacedItem()).GetItemType() != ITEMTYPE_TOKEN) {
    maxUseful = 50;
  }
  else if (ItemTable(Kak_40GoldSkulltulaReward.GetPlacedItem()).IsAdvancement() && ItemTable(Kak_40GoldSkulltulaReward.GetPlacedItem()).GetItemType() != ITEMTYPE_TOKEN) {
    maxUseful = 40;
  }
  else if (ItemTable(Kak_30GoldSkulltulaReward.GetPlacedItem()).IsAdvancement() && ItemTable(Kak_30GoldSkulltulaReward.GetPlacedItem()).GetItemType() != ITEMTYPE_TOKEN) {
    maxUseful = 30;
  }
  else if (ItemTable(Kak_20GoldSkulltulaReward.GetPlacedItem()).IsAdvancement() && ItemTable(Kak_20GoldSkulltulaReward.GetPlacedItem()).GetItemType() != ITEMTYPE_TOKEN) {
    maxUseful = 20;
  }
  else if (ItemTable(Kak_10GoldSkulltulaReward.GetPlacedItem()).IsAdvancement() && ItemTable(Kak_10GoldSkulltulaReward.GetPlacedItem()).GetItemType() != ITEMTYPE_TOKEN) {
    maxUseful = 10;
  }
  //Return max of the two possible reasons tokens could be important
  return std::max(maxUseful, maxBridge);
}

//This function will return a vector of ItemLocations that are accessible with
//where items have been placed so far within the world. The allowedLocations argument
//specifies the pool of locations that we're trying to search for an accessible location in
std::vector<ItemLocation*> GetAccessibleLocations(const std::vector<ItemLocation*>& allowedLocations,
                                                  SearchMode mode) {
  std::vector<ItemLocation*> accessibleLocations;

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
  std::vector<ItemLocation *> newItemLocations;
  bool firstIteration = true;


  //If no new items are found and no events are updated, then the next iteration won't provide any new location
  while (newItemLocations.size() > 0 || EventsUpdated() || firstIteration) {
    firstIteration = false;

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

            if (location->GetPlacedItem() == NONE) {
              accessibleLocations.push_back(location); //Empty location, consider for placement
            } else {
              newItemLocations.push_back(location); //Add item to cache to be considered in logic next iteration
            }

            //Playthrough stuff
            //Generate the playthrough, so we want to add advancement items, unless we know to ignore them
            if (mode == SearchMode::GeneratePlaythrough) {
              //Item is an advancement item, figure out if it should be added to this sphere
              if (!playthroughBeatable && ItemTable(location->GetPlacedItem()).IsAdvancement()) {
                ItemType type = ItemTable(location->GetPlacedItem()).GetItemType();
                std::string itemName(location->GetPlacedItemName());
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
                  sphere.push_back(location);
                }
              }
              //Triforce has been found, seed is beatable, nothing else in this or future spheres matters
              else if (location->GetPlacedItem() == TRIFORCE) {
                sphere.clear();
                sphere.push_back(location);
                playthroughBeatable = true;
              }
            }
            //All we care about is if the game is beatable, used to pare down playthrough
            else if (mode == SearchMode::CheckBeatable && location->GetPlacedItem() == TRIFORCE) {
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
  erase_if(accessibleLocations, [&allowedLocations](ItemLocation* loc){
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
  GetAccessibleLocations(allLocations, SearchMode::GeneratePlaythrough);
}

//Remove unnecessary items from playthrough by removing their location, and checking if game is still beatable
//To reduce searches, some preprocessing is done in playthrough generation to avoid adding obviously unnecessary items
static void PareDownPlaythrough() {
  std::vector<ItemLocation*> toAddBackItem;
  //Start at sphere before Ganon's and count down
  for (int i = playthroughLocations.size() - 2; i >= 0; i--) {
    //Check each item location in sphere
    std::vector<int> erasableIndices;
    std::vector<ItemLocation*> sphere = playthroughLocations.at(i);
    for (int j = sphere.size() - 1; j >= 0; j--) {
      ItemLocation* location = sphere.at(j);
      u32 copy = location->GetPlacedItem(); //Copy out item
      location->SetPlacedItem(NONE); //Write in empty item
      playthroughBeatable = false;
      LogicReset();
      GetAccessibleLocations(allLocations, SearchMode::CheckBeatable); //Check if game is still beatable

      //Playthrough is still beatable without this item, therefore it can be removed from playthrough section.
      if (playthroughBeatable) {
        //Uncomment to print playthrough deletion log in citra
        // std::string locationname(copy.GetName());
        // std::string itemname(location->GetName());
        // std::string removallog = locationname + " at " + itemname + " removed from playthrough";
        // svcOutputDebugString(removallog.c_str(), removallog.length());
        playthroughLocations[i].erase(playthroughLocations[i].begin() + j);
        location->SetDelayedItem(copy); //Game is still beatable, don't add back until later
        toAddBackItem.push_back(location);
      }
      else {
        location->SetPlacedItem(copy); //Immediately put item back so game is beatable again
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
  for (ItemLocation* location : toAddBackItem) {
    location->SaveDelayedItem();
  }

  playthroughBeatable = true;
  //Do one last GetAccessibleLocations to avoid "NOT ADDED" in spoiler
  LogicReset();
  GetAccessibleLocations(allLocations);
}

//Will place things completely randomly, no logic checks are performed
static void FastFill(std::vector<u32> items, std::vector<ItemLocation*> locations) {

  while (!locations.empty()) {

    ItemLocation* location = RandomElement(locations, true);
    location->SetAsHintable();
    PlaceItemInLocation(location, RandomElement(items, true));

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
static void AssumedFill(const std::vector<u32>& items, const std::vector<ItemLocation*>& allowedLocations, bool setLocationsAsHintable = false) {
  if (items.size() > allowedLocations.size()) {
    printf("\x1b[H1;1ERROR: MORE ITEMS THAN LOCATIONS");
  }

  //keep retrying to place everything until it works
  bool unsuccessfulPlacement = false;
  std::vector<ItemLocation*> attemptedLocations;
  do {
    unsuccessfulPlacement = false;
    std::vector<u32> itemsToPlace = items;

    //copy all not yet placed advancement items so that we can apply their effects for the fill algorithm
    std::vector<u32> itemsToNotPlace = FilterFromPool(ItemPool, [](u32 i){ return ItemTable(i).IsAdvancement();});

    //shuffle the order of items to place
    Shuffle(itemsToPlace);
    while (!itemsToPlace.empty()) {
      u32 item = std::move(itemsToPlace.back());
      ItemTable(item).SetAsPlaythrough();
      itemsToPlace.pop_back();

      //assume we have all unplaced items
      LogicReset();
      for (u32 unplacedItem : itemsToPlace) {
        ItemTable(unplacedItem).ApplyEffect();
      }
      for (u32 unplacedItem : itemsToNotPlace) {
      ItemTable(unplacedItem).ApplyEffect();
      }

      //get all accessible locations that are allowed
      const std::vector<ItemLocation*> accessibleLocations = GetAccessibleLocations(allowedLocations);

      //retry if there are no more locations to place items
      if (accessibleLocations.empty()) {

        PlacementLog_Msg("\nCANNOT PLACE ");
        PlacementLog_Msg(ItemTable(item).GetName());
        PlacementLog_Msg(". TRYING AGAIN...\n");

        #ifdef ENABLE_DEBUG
          PlacementLog_Write();
        #endif

        //reset any locations that got an item
        for (ItemLocation* loc : attemptedLocations) {
          loc->SetPlacedItem(NONE);
          itemsPlaced--;
        }
        attemptedLocations.clear();

        unsuccessfulPlacement = true;
        break;
      }

      //place the item within one of the allowed locations
      ItemLocation* selectedLocation = RandomElement(accessibleLocations);
      PlaceItemInLocation(selectedLocation, item);
      attemptedLocations.push_back(selectedLocation);

      //This tells us the location went through the randomization algorithm
      //to distinguish it from locations which did not or that the player already
      //knows
      if (setLocationsAsHintable) {
        selectedLocation->SetAsHintable();
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
    std::vector<u32> rewards = FilterAndEraseFromPool(ItemPool, [](u32 i) {return ItemTable(i).GetItemType() == ITEMTYPE_DUNGEONREWARD;});
    AssumedFill(rewards, dungeonRewardLocations);
    for (size_t i = 0; i < dungeonRewardLocations.size(); i++) {
      const auto index = ItemTable(dungeonRewardLocations[i]->GetPlacedItem()).GetItemID() - baseOffset;
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
    std::vector<u32> rewards = FilterFromPool(ItemPool, [](u32 i) {return ItemTable(i).GetItemType() == ITEMTYPE_DUNGEONREWARD;});
    u32 startingReward = RandomElement(rewards, true);

    LinksPocketRewardBitMask = bitMaskTable[ItemTable(startingReward).GetItemID() - baseOffset];
    PlaceItemInLocation(&LinksPocket, startingReward);
    //erase the stone/medallion from the Item Pool
    FilterAndEraseFromPool(ItemPool, [startingReward](u32 i) {return i == startingReward;});
  }
}

//Fills any locations excluded by the player with junk items so that advancement items
//can't be placed there.
static void FillExcludedLocations() {
  //Only fill in excluded locations that don't already have something and are forbidden
  std::vector<ItemLocation*> excludedLocations = FilterFromPool(allLocations, [](ItemLocation* loc){
    return loc->IsExcluded();
  });

  for (ItemLocation* loc : excludedLocations) {
    PlaceJunkInExcludedLocation(loc);
  }
}

//Function to handle the Own Dungeon setting
static void RandomizeOwnDungeon(const Dungeon::DungeonInfo* dungeon) {
  std::vector<ItemLocation*> dungeonLocations = dungeon->GetDungeonLocations();
  std::vector<u32> dungeonItems;

  //Add specific items that need be randomized within this dungeon
  if (Keysanity.Is(KEYSANITY_OWN_DUNGEON) && dungeon->GetSmallKey() != NONE) {
    std::vector<u32> dungeonSmallKeys = FilterAndEraseFromPool(ItemPool, [dungeon](u32 i){ return i == dungeon->GetSmallKey();});
    AddElementsToPool(dungeonItems, dungeonSmallKeys);
  }

  if ((BossKeysanity.Is(BOSSKEYSANITY_OWN_DUNGEON) && dungeon->GetBossKey() != GANONS_CASTLE_BOSS_KEY) ||
      (GanonsBossKey.Is(GANONSBOSSKEY_OWN_DUNGEON) && dungeon->GetBossKey() == GANONS_CASTLE_BOSS_KEY)) {
        auto dungeonBossKey = FilterAndEraseFromPool(ItemPool, [dungeon](u32 i){ return i == dungeon->GetBossKey();});
        AddElementsToPool(dungeonItems, dungeonBossKey);
  }

  //randomize boss key and small keys together for even distribution
  AssumedFill(dungeonItems, dungeonLocations);

  //randomize map and compass separately since they're not progressive
  if (MapsAndCompasses.Is(MAPSANDCOMPASSES_OWN_DUNGEON) && dungeon->GetMap() != NONE && dungeon->GetCompass() != NONE) {
    auto dungeonMapAndCompass = FilterAndEraseFromPool(ItemPool, [dungeon](u32 i){ return i == dungeon->GetMap() || i == dungeon->GetCompass();});
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

  //Own Dungeon
  for (auto dungeon : dungeonList) {
    RandomizeOwnDungeon(dungeon);
  }

  //Get Any Dungeon and Overworld group locations
  std::vector<ItemLocation*> anyDungeonLocations = FilterFromPool(allLocations, [](ItemLocation* loc){return loc->IsDungeon();});
  //overworldLocations defined in item_location.cpp

  //Create Any Dungeon and Overworld item pools
  std::vector<u32> anyDungeonItems;
  std::vector<u32> overworldItems;

  for (auto dungeon : dungeonList) {
    if (Keysanity.Is(KEYSANITY_ANY_DUNGEON)) {
      auto dungeonKeys = FilterAndEraseFromPool(ItemPool, [dungeon](u32 i){return i == dungeon->GetSmallKey();});
      AddElementsToPool(anyDungeonItems, dungeonKeys);
    } else if (Keysanity.Is(KEYSANITY_OVERWORLD)) {
      auto dungeonKeys = FilterAndEraseFromPool(ItemPool, [dungeon](u32 i){return i == dungeon->GetSmallKey();});
      AddElementsToPool(overworldItems, dungeonKeys);
    }

    if (BossKeysanity.Is(BOSSKEYSANITY_ANY_DUNGEON) && dungeon->GetBossKey() != GANONS_CASTLE_BOSS_KEY) {
      auto bossKey = FilterAndEraseFromPool(ItemPool, [dungeon](u32 i){return i == dungeon->GetBossKey();});
      AddElementsToPool(anyDungeonItems, bossKey);
    } else if (BossKeysanity.Is(BOSSKEYSANITY_OVERWORLD) && dungeon->GetBossKey() != GANONS_CASTLE_BOSS_KEY) {
      auto bossKey = FilterAndEraseFromPool(ItemPool, [dungeon](u32 i){return i == dungeon->GetBossKey();});
      AddElementsToPool(overworldItems, bossKey);
    }

    if (GanonsBossKey.Is(GANONSBOSSKEY_ANY_DUNGEON)) {
      auto ganonBossKey = FilterAndEraseFromPool(ItemPool, [](u32 i){return i == GANONS_CASTLE_BOSS_KEY;});
      AddElementsToPool(anyDungeonItems, ganonBossKey);
    } else if (GanonsBossKey.Is(GANONSBOSSKEY_OVERWORLD)) {
      auto ganonBossKey = FilterAndEraseFromPool(ItemPool, [](u32 i){return i == GANONS_CASTLE_BOSS_KEY;});
      AddElementsToPool(overworldItems, ganonBossKey);
    }
  }

  if (GerudoKeys.Is(GERUDOKEYS_ANY_DUNGEON)) {
    auto gerudoKeys = FilterAndEraseFromPool(ItemPool, [](u32 i){return i == GERUDO_FORTRESS_SMALL_KEY;});
    AddElementsToPool(anyDungeonItems, gerudoKeys);
  } else if (GerudoKeys.Is(GERUDOKEYS_OVERWORLD)) {
    auto gerudoKeys = FilterAndEraseFromPool(ItemPool, [](u32 i){return i == GERUDO_FORTRESS_SMALL_KEY;});
    AddElementsToPool(overworldItems, gerudoKeys);
  }

  if (ShuffleRewards.Is(REWARDSHUFFLE_ANY_DUNGEON)) {
    auto rewards = FilterAndEraseFromPool(ItemPool, [](u32 i){return ItemTable(i).GetItemType() == ITEMTYPE_DUNGEONREWARD;});
    AddElementsToPool(anyDungeonItems, rewards);
  } else if (ShuffleRewards.Is(REWARDSHUFFLE_OVERWORLD)) {
    auto rewards = FilterAndEraseFromPool(ItemPool, [](u32 i){return ItemTable(i).GetItemType() == ITEMTYPE_DUNGEONREWARD;});
    AddElementsToPool(overworldItems, rewards);
  }

  //Randomize Any Dungeon and Overworld pools
  AssumedFill(anyDungeonItems, anyDungeonLocations, true);
  AssumedFill(overworldItems, overworldLocations, true);

  //Randomize maps and compasses after since they're not advancement items
  for (auto dungeon : dungeonList) {
    if (MapsAndCompasses.Is(MAPSANDCOMPASSES_ANY_DUNGEON)) {
      auto mapAndCompassItems = FilterAndEraseFromPool(ItemPool, [dungeon](u32 i){return i == dungeon->GetMap() || i == dungeon->GetCompass();});
      AssumedFill(mapAndCompassItems, anyDungeonLocations, true);
    } else if (MapsAndCompasses.Is(MAPSANDCOMPASSES_OVERWORLD)) {
      auto mapAndCompassItems = FilterAndEraseFromPool(ItemPool, [dungeon](u32 i){return i == dungeon->GetMap() || i == dungeon->GetCompass();});
      AssumedFill(mapAndCompassItems, overworldLocations, true);
    }
  }
}

static void RandomizeLinksPocket() {
  if (LinksPocketItem.Is(LINKSPOCKETITEM_ADVANCEMENT)) {
   //Get all the advancement items                                                                                     don't include tokens
   std::vector<u32> advancementItems = FilterAndEraseFromPool(ItemPool, [](u32 i){return ItemTable(i).IsAdvancement() && ItemTable(i).GetItemType() != ITEMTYPE_TOKEN;});
   //select a random one
   u32 startingItem = RandomElement(advancementItems, true);
   //add the others back
   AddElementsToPool(ItemPool, advancementItems);

   PlaceItemInLocation(&LinksPocket, startingItem);
 } else if (LinksPocketItem.Is(LINKSPOCKETITEM_NOTHING)) {
   PlaceItemInLocation(&LinksPocket, GREEN_RUPEE);
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
    SetVanillaShopItems(); //Set ShopItems vector to default, vanilla values
    if (Shopsanity.Is(SHOPSANITY_OFF)) {
      PlaceShopItems(); //Just place vanilla items
    } else {
      if (Shopsanity.Is(SHOPSANITY_ZERO)) { //Shopsanity 0
        Shuffle(ShopItems); //Shuffle shop items amongst themselves
        PlaceShopItems(); //Just place the shuffled shop items
      }
      else { //Shopsanity 1-4, random
        const std::array<int, 4> indices = {7, 5, 8, 6}; //Indices from OoTR. So shopsanity one will overwrite 7, three will overwrite 7, 5, 8, etc.

        //Shuffle shop items making sure to not place minShopItems in shop slots which can be overwritten
        std::vector<int> indicesToExclude;
        int max = Shopsanity.Is(SHOPSANITY_RANDOM) ? 4 : GetShopsanityReplaceAmount(); //With random it's up to 4 so to be safe we exclude all 4, otherwise exclude amount from settings
        for(int i = 0; i < max; i++) {
          indicesToExclude.push_back(indices[i]);
        }
        ShuffleShop(ShopItems, indicesToExclude); //Shuffle shop items, making sure some will not be overwritten

        //Overwrite appropriate number of shop items
        for (size_t i = 0; i < ShopLocationLists.size(); i++) {
          int num_to_replace = GetShopsanityReplaceAmount(); //1-4 shop items will be overwritten, depending on settings
          for(int j = 0; j < num_to_replace; j++) {
            int itemindex = indices[j];
            ShopItems[i*8+itemindex-1] = NONE; //Clear item so it can be filled during the general fill algo
            ShopItemsPrices[i*8+itemindex-1] = GetRandomShopPrice(); //Set price in ShopItemsPrices vector so it can be retrieved later by the patch
          }
        }
      }
      PlaceShopItems(); //Place shop items with some cleared for placement
    }

    //Place dungeon rewards
    RandomizeDungeonRewards();

    //Place songs first if song shuffle is set to specific locations
    if (ShuffleSongs.IsNot(SONGSHUFFLE_ANYWHERE)) {

      //Get each song
      std::vector<u32> songs = FilterAndEraseFromPool(ItemPool, [](u32 i) { return ItemTable(i).GetItemType() == ITEMTYPE_SONG;});

      //Get each song location
      std::vector<ItemLocation*> songLocations;
      if (ShuffleSongs.Is(SONGSHUFFLE_SONG_LOCATIONS)) {
        songLocations = FilterFromPool(allLocations, [](ItemLocation * loc){ return loc->IsCategory(Category::cSong);});

      } else if (ShuffleSongs.Is(SONGSHUFFLE_DUNGEON_REWARDS)) {
        songLocations = FilterFromPool(allLocations, [](ItemLocation * loc){ return loc->IsCategory(Category::cSongDungeonReward);});
      }

      AssumedFill(songs, songLocations, true);
    }

    //Then place dungeon items that are assigned to restrictive location pools
    RandomizeDungeonItems();

    //Then place Link's Pocket Item if it has to be an advancement item
    RandomizeLinksPocket();
    //Then place the rest of the advancement items
    std::vector<u32> remainingAdvancementItems = FilterAndEraseFromPool(ItemPool, [](u32 i) { return ItemTable(i).IsAdvancement();});
    AssumedFill(remainingAdvancementItems, allLocations, true);

    //Fast fill for the rest of the pool
    std::vector<u32> remainingPool = FilterAndEraseFromPool(ItemPool, [](u32 i) {return true;});
    LogicReset();
    FastFill(remainingPool, GetAccessibleLocations(allLocations));

    LogicReset();
    GeneratePlaythrough();
    //Successful placement, produced beatable result
    if(playthroughBeatable) {
      printf("Done");
      printf("\x1b[9;10HCalculating Playthrough...");
      PareDownPlaythrough();
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
    }
    retries++;
  }
  //All retries failed
  return -1;
}
