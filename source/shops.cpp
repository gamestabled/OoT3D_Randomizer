#include "item_location.hpp"
#include "item_pool.hpp"
#include "location_access.hpp"
#include "random.hpp"
#include "item.hpp"
#include "shops.hpp"
#include "debug.hpp"

#include <math.h>
#include <map>

using namespace Settings;

std::vector<ItemKey> ShopItems = {};
std::array<int, 64> ShopItemsPrices;
std::vector<ItemAndPrice> NonShopItems = {};
//Shop items we don't want to overwrite
const std::array<ItemKey, 15> minShopItems = {
  BUY_DEKU_SHIELD, //1 in vanilla shop pool
  BUY_HYLIAN_SHIELD, //2
  BUY_GORON_TUNIC, //1
  BUY_ZORA_TUNIC, //1
  BUY_DEKU_NUT_5, //6
  BUY_DEKU_STICK_1, //3
  BUY_ARROWS_10, //4
  BUY_BOMBCHU_10, //3
  BUY_BOMBS_525, //1
  BUY_BOMBS_10, //1
  BUY_BOMBS_20, //1
  BUY_BOMBS_30, //1
  BUY_BLUE_FIRE, //2
  BUY_BOTTLE_BUG, //2
  BUY_FISH, //3
}; //Total: 32 items

//Set vanilla shop item locations before potentially shuffling
void SetVanillaShopItems() {
  ShopItems = {
    //Vanilla KF
    BUY_DEKU_SHIELD,
    BUY_DEKU_NUT_5,
    BUY_DEKU_NUT_10,
    BUY_DEKU_STICK_1,
    BUY_DEKU_SEEDS_30,
    BUY_ARROWS_10,
    BUY_ARROWS_30,
    BUY_HEART,
    //Vanilla Kak Potion
    BUY_DEKU_NUT_5,
    BUY_FISH,
    BUY_RED_POTION_30,
    BUY_GREEN_POTION,
    BUY_BLUE_FIRE,
    BUY_BOTTLE_BUG,
    BUY_POE,
    BUY_FAIRYS_SPIRIT,
    //Vanilla Bombchu
    BUY_BOMBCHU_5,
    BUY_BOMBCHU_10,
    BUY_BOMBCHU_10,
    BUY_BOMBCHU_10,
    BUY_BOMBCHU_20,
    BUY_BOMBCHU_20,
    BUY_BOMBCHU_20,
    BUY_BOMBCHU_20,
    //Vanilla MK Potion
    BUY_GREEN_POTION,
    BUY_BLUE_FIRE,
    BUY_RED_POTION_30,
    BUY_FAIRYS_SPIRIT,
    BUY_DEKU_NUT_5,
    BUY_BOTTLE_BUG,
    BUY_POE,
    BUY_FISH,
    //Vanilla MK Bazaar
    BUY_HYLIAN_SHIELD,
    BUY_BOMBS_535,
    BUY_DEKU_NUT_5,
    BUY_HEART,
    BUY_ARROWS_10,
    BUY_ARROWS_50,
    BUY_DEKU_STICK_1,
    BUY_ARROWS_30,
    //Vanilla Kak Bazaar
    BUY_HYLIAN_SHIELD,
    BUY_BOMBS_535,
    BUY_DEKU_NUT_5,
    BUY_HEART,
    BUY_ARROWS_10,
    BUY_ARROWS_50,
    BUY_DEKU_STICK_1,
    BUY_ARROWS_30,
    //Vanilla ZD Shop
    BUY_ZORA_TUNIC,
    BUY_ARROWS_10,
    BUY_HEART,
    BUY_ARROWS_30,
    BUY_DEKU_NUT_5,
    BUY_ARROWS_50,
    BUY_FISH,
    BUY_RED_POTION_50,
    //Vanilla GC Shop
    BUY_BOMBS_525,
    BUY_BOMBS_10,
    BUY_BOMBS_20,
    BUY_BOMBS_30,
    BUY_GORON_TUNIC,
    BUY_HEART,
    BUY_RED_POTION_40,
    BUY_HEART,
  };
  ItemAndPrice init;
  init.Name = "No Item";
  init.Price = -1;
  NonShopItems.assign(32, init);
}

//Get random price using a beta distribution with alpha = 1.5, beta = 2
//Average price = 126
//~45% chance of needing no wallet, ~25% chance of needing 1, ~30% chance of needing 2
int GetRandomShopPrice() {
  double random = RandomDouble();
  double rawprice = (1.001 + .5 * (pow(random, 1.5) * (3 * random - 5))); //Approximate CDF of a beta distribution
  int adjustedprice = static_cast<int>(rawprice * 60) * 5; //rawprice in range [0.0, 1.0], this gives range [0, 300]
  return adjustedprice;
}

//Similar to above, beta distribution with alpha = 1, beta = 2
//Average price = 29
//^ Slightly different from OoTR where average is 32, due to using increments of 5
s16 GetRandomScrubPrice() {
  double random = RandomDouble();
  double rawprice = (1.001-(1-(pow(1-random, 2)))); //Approximate CDF of a beta distribution
  int adjustedprice = static_cast<int>(rawprice * 19) * 5; //rawprice in range [0.0, 1.0], this gives range [0, 95]
  return adjustedprice;
}

//Get 1 to 4, or a random number from 1-4 depending on shopsanity setting
int GetShopsanityReplaceAmount() {
  if (Settings::Shopsanity.Is(SHOPSANITY_ONE)) {
    return 1;
  } else if (Settings::Shopsanity.Is(SHOPSANITY_TWO)) {
    return 2;
  } else if (Settings::Shopsanity.Is(SHOPSANITY_THREE)) {
    return 3;
  } else if (Settings::Shopsanity.Is(SHOPSANITY_FOUR)) {
    return 4;
  } else { //Random, get number in [1, 4]
    return Random(1, 5);
  }
}

//Generate a fake name for the ice trap based on the item it's written as
std::string GetIceTrapName(u8 id) {
  return "Totally not an ice trap";
}

//Get shop index based on a given location
std::map<std::string, int> ShopNameToNum = {{"KF Shop", 0},{"Kak Potion Shop", 1},{"MK Bombchu Shop", 2},{"MK Potion Shop", 3},{"MK Bazaar", 4},{"Kak Bazaar", 5},{"ZD Shop", 6},{"GC Shop", 7}};
int GetShopIndex(LocationKey loc) {
  //Kind of hacky, but extract the shop and item position from the name
  std::string name = std::basic_string(Location(loc)->GetName());
  int split = name.find(" Item ");
  std::string shop = name.substr(0, split);
  int pos = std::stoi(name.substr(split+6, 1)) - 1;
  int shopnum = ShopNameToNum[shop];
  return shopnum*8 + pos;
}

//Without this transformed index, shop-related tables and arrays would need 64 entries- But only half of that is needed for shopsanity
//So we use this transformation to map only important indices to an array with 32 entries in the following manner:
//Shop index:  4  5  6  7 12 13 14 15 20 21 22 23...
//Transformed: 0  1  2  3  4  5  6  7  8  9 10 11...
//So we first divide the shop index by 4, then by 2 which basically tells us the index of the shop it's in,
//then multiply by 4 since there are 4 items per shop
//And finally we use a modulo by 4 to get the index within the "shop" of 4 items, and add
int TransformShopIndex(int index) {
  return 4*((index / 4) / 2) + index % 4;
}

//Place each shop item from the shop item array into the appropriate location
void PlaceShopItems() {
  for (size_t i = 0; i < ShopLocationLists.size(); i++) {
    for (size_t j = 0; j < ShopLocationLists[i].size(); j++) {
      //Multiply i by 8 to get the correct shop
      PlaceShopItemInLocation(ShopLocationLists[i][j], ShopItems[i*8 + j], ShopItemsPrices[i*8 + j]);
    }
  }
}

//Specialized shuffle function for shop items
void ShuffleShop(std::vector<ItemKey>& ShopItems, std::vector<int> indicesToExclude) {
  for (std::size_t i = 0; i + 1 < ShopItems.size(); i++) {
    int retries = 5;
    while (retries > 0) { //Retry a few times until item is eventually shuffled somewhere, so we don't end up with a bunch of unshuffled items
      size_t swapInto = Random(i, ShopItems.size()); //Get index to swap item into
      size_t shopIndex = swapInto % 8; //Get index within shop
      //If this item is within minShopItems, and it is about to be swapped in an index which may be overwritten, do not swap
      bool sourceItemInMin = std::find(minShopItems.begin(), minShopItems.end(), ShopItems[i]) != minShopItems.end();
      bool targetIndexToExcludeMinFrom = std::find(indicesToExclude.begin(), indicesToExclude.end(), shopIndex+1) != indicesToExclude.end();
      bool sourceToTargetGood = !(sourceItemInMin && targetIndexToExcludeMinFrom);
      //Vice versa, want to check that the target item being swapped is not being swapped into a bad index
      bool targetItemInMin = std::find(minShopItems.begin(), minShopItems.end(), ShopItems[swapInto]) != minShopItems.end();
      bool sourceIndexToExcludeMinFrom = std::find(indicesToExclude.begin(), indicesToExclude.end(), (i % 8)+1) != indicesToExclude.end();
      bool targetToSourceGood = !(targetItemInMin && sourceIndexToExcludeMinFrom);
      //If a min shop item is not being swapped into a bad index, then do the swap
      if (sourceToTargetGood && targetToSourceGood) {
        std::swap(ShopItems[i], ShopItems[swapInto]);
        break;
      }
      retries--;
    }
  }
}
