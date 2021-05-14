#include "item_location.hpp"
#include "item_pool.hpp"
#include "location_access.hpp"
#include "random.hpp"
#include "item.hpp"

using namespace Settings;

std::vector<Item> ShopItems = {};
//Shop items we don't want to overwrite
const std::array<Item, 28> minShopItems = {
  BuyDekuShield,
  BuyHylianShield,
  BuyGoronTunic,
  BuyZoraTunic,
  BuyDekuNut5,
  BuyDekuNut5,
  BuyDekuNut10,
  BuyDekuStick1,
  BuyDekuStick1,
  BuyDekuSeeds30,
  BuyArrows10,
  BuyArrows10,
  BuyArrows30,
  BuyArrows50,
  BuyBombchu5,
  BuyBombchu10,
  BuyBombchu10,
  BuyBombchu20,
  BuyBombs525,
  BuyBombs535,
  BuyBombs10,
  BuyBombs20,
  BuyGreenPotion,
  BuyRedPotion30,
  BuyBlueFire,
  BuyFairysSpirit,
  BuyBottleBug,
  BuyFish,
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

//OoTR uses a fancy betavariate function for a weighted distribution in [0, 300] in increments of 5... For now each price is just equally likely
int GetRandomShopPrice() {
  return Random(0, 61) * 5;
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
  } else { //Random
    return Random(1, 5);
  }
}

//Specialized shuffle function for shop items
void ShuffleShop(std::vector<Item>& ShopItems, std::vector<int> indicesToExclude) {
    for (std::size_t i = 0; i + 1 < ShopItems.size(); i++)
    {
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
        }
    }
}
