#include "new_playthrough.hpp"

#include "world.hpp"
#include "random.hpp"
#include "pool_functions.hpp"
#include "logic.hpp"
#include "../code/src/item_override.h"

#include "items/new_item.hpp"


// #include <3ds.h>
// #include <unistd.h>


NewPlaythrough::NewPlaythrough(u32 seed) {
    //initialize the RNG with just the seed incase any settings need to be
    //resolved to something random
    Random_Init(seed);

    // overrides.clear();
    // CustomMessages::ClearMessages();
    // ItemReset();
    // HintReset();
    // Areas::AccessReset();

    World* world = World::getWorld();
    Random_Init(std::hash<std::string>{}(world->generateSettings.seed + world->getSettingsHash()));

    // Logic::UpdateHelpers();

    // if (Settings::Logic.Is(LOGIC_VANILLA)) {
    //     VanillaFill(); //Just place items in their vanilla locations
    // } else { //Fill locations with logic
    //     int ret = Fill(); //todo attempt this 5 times
    //     if (ret < 0) {
    //         return ret;
    //     }
    // } TODO

    // GenerateHash();
    // SpoilerLog::generateHash();

    // if (Settings::GenerateSpoilerLog) { TODO
    //     //write logs
    //     printf("\x1b[11;10HWriting Spoiler Log...");
    //     if (SpoilerLog_Write()) {
    //         printf("Done");
    //     } else {
    //         printf("Failed");
    //     }
    //     #ifdef ENABLE_DEBUG
    //     printf("\x1b[11;10HWriting Placement Log...");
    //     if (PlacementLog_Write()) {
    //         printf("Done\n");
    //     } else {
    //         printf("Failed\n");
    //     }
    //     #endif
    //     PlacementLog_Clear();
    // }
}

//used for generating a lot of seeds at once
void NewPlaythrough::repeat(int count /*= 1*/) {
    // printf("\x1b[0;0HGENERATING %d SEEDS", count);
    World* world = World::getWorld();
    u32 repeatedSeed = 0;
    for (int i = 0; i < count; i++) {
        repeatedSeed = rand() % 0xFFFFFFFF;
        world->generateSettings.seed = std::to_string(repeatedSeed);
        // CitraPrint("testing seed: " + world->generateSettings.seed);
        NewPlaythrough playthrough(std::hash<std::string>{}(world->generateSettings.seed));
        // PlacementLog_Clear();
        // printf("\x1b[15;15HSeeds Generated: %d\n", i + 1);
    }
}

void NewPlaythrough::fill() {
    placementFailure = false;
    showItemProgress = false;
    playthroughLocations.clear();
    // playthroughEntrances.clear();
    wothLocations.clear();
    World::getWorld()->reset();

    generateLocationPool();
    generateItemPool();
    // GenerateStartingInventory();
    // RemoveStartingItemsFromPool();
    // FillExcludedLocations();

    // //Temporarily add shop items to the ItemPool so that entrance randomization
    // //can validate the world using deku/hylian shields
    // AddElementsToPool(ItemPool, GetMinVanillaShopItems(32)); //assume worst case shopsanity 4
    // if (ShuffleEntrances) {
    //   printf("\x1b[7;10HShuffling Entrances...");
    //   ShuffleAllEntrances();
    //   printf("\x1b[7;32HDone");
    // }
    // //erase temporary shop items
    // FilterAndEraseFromPool(ItemPool, [](const ItemKey item){return ItemTable(item).GetItemType() == ITEMTYPE_SHOP;});

    // showItemProgress = true;
    // //Place shop items first, since a buy shield is needed to place a dungeon reward on Gohma due to access
    // NonShopItems = {};
    // if (Shopsanity.Is(SHOPSANITY_OFF)) {
    //   PlaceVanillaShopItems(); //Place vanilla shop items in vanilla location
    // } else {
    //   int total_replaced = 0;
    //   if (Shopsanity.IsNot(SHOPSANITY_ZERO)) { //Shopsanity 1-4, random
    //     //Initialize NonShopItems
    //     ItemAndPrice init;
    //     init.Name = Text{"No Item", "Sin objeto", "Pas d'objet"};
    //     init.Price = -1;
    //     init.Repurchaseable = false;
    //     NonShopItems.assign(32, init);
    //     //Indices from OoTR. So shopsanity one will overwrite 7, three will overwrite 7, 5, 8, etc.
    //     const std::array<int, 4> indices = {7, 5, 8, 6};
    //     //Overwrite appropriate number of shop items
    //     for (size_t i = 0; i < ShopLocationLists.size(); i++) {
    //       int num_to_replace = GetShopsanityReplaceAmount(); //1-4 shop items will be overwritten, depending on settings
    //       total_replaced += num_to_replace;
    //       for (int j = 0; j < num_to_replace; j++) {
    //         int itemindex = indices[j];
    //         int shopsanityPrice = GetRandomShopPrice();
    //         NonShopItems[TransformShopIndex(i*8+itemindex-1)].Price = shopsanityPrice; //Set price to be retrieved by the patch and textboxes
    //         Location(ShopLocationLists[i][itemindex - 1])->SetShopsanityPrice(shopsanityPrice);
    //       }
    //     }
    //   }
    //   //Get all locations and items that don't have a shopsanity price attached
    //   std::vector<LocationKey> shopLocations = {};
    //   //Get as many vanilla shop items as the total number of shop items minus the number of replaced items
    //   //So shopsanity 0 will get all 64 vanilla items, shopsanity 4 will get 32, etc.
    //   std::vector<ItemKey> shopItems = GetMinVanillaShopItems(total_replaced);

    //   for (size_t i = 0; i < ShopLocationLists.size(); i++) {
    //     for (size_t j = 0; j < ShopLocationLists[i].size(); j++) {
    //       LocationKey loc = ShopLocationLists[i][j];
    //       if (!(Location(loc)->HasShopsanityPrice())) {
    //         shopLocations.push_back(loc);
    //       }
    //     }
    //   }
    //   //Place the shop items which will still be at shop locations
    //   AssumedFill(shopItems, shopLocations);
    // }

    // //Place dungeon rewards
    // RandomizeDungeonRewards();

    // //Place dungeon items restricted to their Own Dungeon
    // for (auto dungeon : Dungeon::dungeonList) {
    //   RandomizeOwnDungeon(dungeon);
    // }

    // //Then Place songs if song shuffle is set to specific locations
    // if (ShuffleSongs.IsNot(SONGSHUFFLE_ANYWHERE)) {

    //   //Get each song
    //   std::vector<ItemKey> songs = FilterAndEraseFromPool(ItemPool, [](const ItemKey i) { return ItemTable(i).GetItemType() == ITEMTYPE_SONG;});

    //   //Get each song location
    //   std::vector<LocationKey> songLocations;
    //   if (ShuffleSongs.Is(SONGSHUFFLE_SONG_LOCATIONS)) {
    //     songLocations = FilterFromPool(allLocations, [](const LocationKey loc){ return Location(loc)->IsCategory(Category::cSong);});

    //   } else if (ShuffleSongs.Is(SONGSHUFFLE_DUNGEON_REWARDS)) {
    //     songLocations = FilterFromPool(allLocations, [](const LocationKey loc){ return Location(loc)->IsCategory(Category::cSongDungeonReward);});
    //   }

    //   AssumedFill(songs, songLocations, true);
    // }

    // //Then place dungeon items that are assigned to restrictive location pools
    // RandomizeDungeonItems();

    // //Then place Link's Pocket Item if it has to be an advancement item
    // RandomizeLinksPocket();
    // //Then place the rest of the advancement items
    std::vector<NewItem*> remainingAdvancementItems = FilterAndEraseFromPool(itemPool, [](NewItem* i) { return i->isAdvancement(); });
    assumedFill(remainingAdvancementItems, allLocations, true);

    //Fast fill for the rest of the pool
    std::vector<NewItem*> remainingPool = FilterAndEraseFromPool(itemPool, [](NewItem* i) { return true; });
    fastFill(remainingPool, getAllEmptyLocations(), false);
    // GeneratePlaythrough();
    // //Successful placement, produced beatable result
    // if(playthroughBeatable && !placementFailure) {
    //   printf("Done");
    //   printf("\x1b[9;10HCalculating Playthrough...");
    //   PareDownPlaythrough();
    //   CalculateWotH();
    //   printf("Done");
    //   CreateItemOverrides();
    //   CreateEntranceOverrides();
    //   CreateAlwaysIncludedMessages();
    //   if (GossipStoneHints.IsNot(HINTS_NO_HINTS)) {
    //     printf("\x1b[10;10HCreating Hints...");
    //     CreateAllHints();
    //     printf("Done");
    //   }
    //   if (ShuffleMerchants.Is(SHUFFLEMERCHANTS_HINTS)) {
    //     CreateMerchantsHints();
    //   }
    //   return 1;
    // }
    // //Unsuccessful placement
    // if(retries < 4) {
    //   GetAccessibleLocations(allLocations, SearchMode::AllLocationsReachable);
    //   printf("\x1b[9;10HFailed. Retrying... %d", retries+2);
    //   Areas::ResetAllLocations();
    //   LogicReset();
    // }
}


//sort through Vanilla and MQ dungeon locations
void NewPlaythrough::generateLocationPool() {

    allLocations.clear();
    // AddLocation(LINKS_POCKET);
    // AddLocations(overworldLocations);

    // for (auto dungeon : Dungeon::dungeonList) {
    //     AddLocations(dungeon->GetDungeonLocations());
    // }
}

void NewPlaythrough::addItemToMainPool(NewItem* item, size_t count) {
    itemPool.insert(itemPool.end(), count, item);
}

void NewPlaythrough::generateItemPool() {
    NewItemTable* itemTable = &World::getWorld()->itemTable;
    NewLocationTable* locationTable = &World::getWorld()->locationTable;

    itemPool.clear();
    
    if (World::getWorld()->mainSettings.shuffleSettings.shuffleKokiriSword) {
        addItemToMainPool(&itemTable->kokiriSword);
        iceTrapModels.push_back(GI_SWORD_KOKIRI);
    } else {
        placeItemInLocation(&locationTable->KF_kokiriSwordChest, &itemTable->kokiriSword, false, true);
    }

    //TODO...
    addItemToMainPool(&itemTable->giantsKnife);
    addItemToMainPool(&itemTable->biggoronSword);
    addItemToMainPool(&itemTable->dekuShield);
    addItemToMainPool(&itemTable->hylianShield);
    addItemToMainPool(&itemTable->mirrorShield);

}

void NewPlaythrough::addLocation(NewItemLocation* loc, std::vector<NewItemLocation*>& dest) {
    dest.push_back(loc);
}

void NewPlaythrough::addLocation(NewItemLocation* loc) {
    addLocation(loc, allLocations);
}

template <typename Container>
void NewPlaythrough::addLocations(const Container& locations, std::vector<NewItemLocation*>& destination) {
    destination.insert(destination.end(), std::cbegin(locations), std::cend(locations));
}

template <typename Container>
void NewPlaythrough::addLocations(const Container& locations) {
    addLocations(locations, allLocations);
}

std::vector<NewItemLocation*> NewPlaythrough::getAllEmptyLocations() {
    return FilterFromPool(allLocations, [](const NewItemLocation* loc){ return loc->getPlacedItem() != &NewItemTable::none; });
}

void NewPlaythrough::assumedFill(const std::vector<NewItem*>& items, const std::vector<NewItemLocation*>& allowedLocations, bool setLocationsAsHintable) {
    if (items.size() > allowedLocations.size()) {
        //throw error
    }

    // if no logic fastfill

    int retries = 10;
    bool unsuccessfulPlacement = false;
    std::vector<NewItemLocation*> attemptedLocations;
    do {
        unsuccessfulPlacement = false;

        std::vector<NewItem*> itemsToPlace = items;

        //copy all not yet placed advancement items so that we can apply their effects for the fill algorithm
        std::vector<NewItem*> itemsToNotPlace = FilterFromPool(itemPool, [](NewItem* i){ return i->isAdvancement(); });

        //shuffle the order of items to place
        Shuffle(itemsToPlace);
        while (!itemsToPlace.empty()) {
            NewItem* item = itemsToPlace.back();
            itemsToPlace.pop_back();

            //assume we have all unplaced items
            Logic::LogicReset(); // should the logic "namespace" be rewritten into a logic class... probably... but... maybe later...
            for (NewItem* unplacedItem : itemsToPlace) {
                unplacedItem->applyEffect();
            }
            for (NewItem* unplacedItem : itemsToNotPlace) {
                unplacedItem->applyEffect();
            }

            //get all accessible locations that are allowed
            const std::vector<NewItemLocation*> accessibleLocations = getAccessibleLocations(allowedLocations);

            //retry if there are no more locations to place items
            if (accessibleLocations.empty()) {
                for (NewItemLocation* loc : attemptedLocations) {
                    loc->setPlacedItem(&NewItemTable::none);
                    itemsPlaced--;
                }
                attemptedLocations.clear();

                unsuccessfulPlacement = true;
                break;
            }

            //place the item within one of the allowed locations
            NewItemLocation* selectedLocation = RandomElement(accessibleLocations);
            placeItemInLocation(selectedLocation, item);
            attemptedLocations.push_back(selectedLocation);

            //This tells us the location went through the randomization algorithm
            //to distinguish it from locations which did not or that the player already
            //knows
            if (setLocationsAsHintable) {
                selectedLocation->setAsHintable();
            }

            //If ALR is off, then we check beatability after placing the item.
            //If the game is beatable, then we can stop placing items with logic.
            // TODO
        }

    } while (unsuccessfulPlacement && (retries-- > 0));
}

void NewPlaythrough::fastFill(std::vector<NewItem*> items, std::vector<NewItemLocation*> locations, bool endOnItemsEmpty) {
    //Loop until locations are empty, or also end if items are empty and the parameters specify to end then
    while (!locations.empty() && (!endOnItemsEmpty || !items.empty())) {
        NewItemLocation* loc = RandomElement(locations, true);
        loc->setAsHintable();
        placeItemInLocation(loc, RandomElement(items, true));

        if (items.empty() && !endOnItemsEmpty) {
            items.push_back(getJunkItem());
        }
    }
}
