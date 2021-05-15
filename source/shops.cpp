#include "item_location.hpp"
#include "item_pool.hpp"
#include "location_access.hpp"
#include "random.hpp"
#include "item.hpp"

#include <math.h>

using namespace Settings;

std::vector<Item> ShopItems = {};
//Shop items we don't want to overwrite
const std::array<Item, 14> minShopItems = {
  BuyDekuShield, //1 in vanilla shop pool
  BuyHylianShield, //2
  BuyGoronTunic, //1
  BuyZoraTunic, //1
  BuyDekuNut5, //6
  BuyDekuStick1, //3
  BuyArrows10, //4
  BuyBombchu10, //3
  BuyBombs525, //1
  BuyBombs10, //1
  BuyBlueFire, //2
  BuyFairysSpirit, //2
  BuyBottleBug, //2
  BuyFish, //3
};

//Set vanilla shop item locations before potentially shuffling
void SetVanillaShopItems() {
  ShopItems = {
    //Vanilla KF
    BuyDekuShield,
    BuyDekuNut5,
    BuyDekuNut10,
    BuyDekuStick1,
    BuyDekuSeeds30,
    BuyArrows10,
    BuyArrows30,
    BuyHeart,
    //Vanilla Kak Potion
    BuyDekuNut5,
    BuyFish,
    BuyRedPotion30,
    BuyGreenPotion,
    BuyBlueFire,
    BuyBottleBug,
    BuyPoe,
    BuyFairysSpirit,
    //Vanilla Bombchu
    BuyBombchu5,
    BuyBombchu10,
    BuyBombchu10,
    BuyBombchu10,
    BuyBombchu20,
    BuyBombchu20,
    BuyBombchu20,
    BuyBombchu20,
    //Vanilla MK Potion
    BuyGreenPotion,
    BuyBlueFire,
    BuyRedPotion30,
    BuyFairysSpirit,
    BuyDekuNut5,
    BuyBottleBug,
    BuyPoe,
    BuyFish,
    //Vanilla MK Bazaar
    BuyHylianShield,
    BuyBombs535,
    BuyDekuNut5,
    BuyHeart,
    BuyArrows10,
    BuyArrows50,
    BuyDekuStick1,
    BuyArrows30,
    //Vanilla Kak Bazaar
    BuyHylianShield,
    BuyBombs535,
    BuyDekuNut5,
    BuyHeart,
    BuyArrows10,
    BuyArrows50,
    BuyDekuStick1,
    BuyArrows30,
    //Vanilla ZD
    BuyZoraTunic,
    BuyArrows10,
    BuyHeart,
    BuyArrows30,
    BuyDekuNut5,
    BuyArrows50,
    BuyFish,
    BuyRedPotion50,
    //Vanilla GC Shop
    BuyBombs525,
    BuyBombs10,
    BuyBombs20,
    BuyBombs30,
    BuyGoronTunic,
    BuyHeart,
    BuyRedPotion40,
    BuyHeart,
  };
}

//Get random price using a beta distribution
//Average price = 126
//~45% chance of needing no wallet, ~25% chance of needing 1, ~30% chance of needing 2
int GetRandomShopPrice() {
  double random = RandomDouble();
  double rawprice = (1.01 + .5 * (pow(random, 1.5) * (3 * random - 5))); //Approximate CDF of a beta distribution
  int adjustedprice = static_cast<int>(rawprice * 60) * 5; //rawprice in range [0.0, 1.0], this gives range [0, 300]
  return adjustedprice;
}

//Place each shop item from the shop item array into the appropriate location
void PlaceShopItems() {
  for (size_t i = 0; i < ShopLocationLists.size(); i++) {
    for (size_t j = 0; j < ShopLocationLists[i].size(); j++) {
      //Multiply i by 8 to get the correct shop
      PlaceShopItemInLocation(ShopLocationLists[i][j], ShopItems[i*8 + j], ShopItems[i*8 + j].GetPrice());
    }
  }
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

//Specialized shuffle function for shop items
void ShuffleShop(std::vector<Item>& ShopItems, std::vector<int> indicesToExclude) {
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
