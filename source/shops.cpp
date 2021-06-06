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

std::vector<ItemAndPrice> NonShopItems = {};
//Shop items we don't want to overwrite

//Set vanilla shop item locations before potentially shuffling
void PlaceVanillaShopItems() {
  std::vector<ItemKey> VanillaShopItems = {
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
  //Loop to place vanilla items in each location
  for (size_t i = 0; i < ShopLocationLists.size(); i++) {
    for (size_t j = 0; j < ShopLocationLists[i].size(); j++) {
      //Multiply i by 8 to get the correct shop
      PlaceItemInLocation(ShopLocationLists[i][j], VanillaShopItems[i*8 + j]);
    }
  }
}

//These are the same items as SetVanillaShopItems, but in a priority order of importance
//However many shop item slots were cleared, this will return 64 minus that number of vanilla shop items to be placed with assumed fill
//The first 32 items here will always be present in shops
//Shopsanity 4 will only have the first 32, shopsanity 1 will have the first 56, etc.
//Shopsanity random will have anywhere from the first 32 to the first 56, so the order of items after 32 is relevant
std::vector<ItemKey> GetMinVanillaShopItems(int total_replaced) {
  std::vector<ItemKey> minShopItems = {
    BUY_DEKU_SHIELD,
    BUY_HYLIAN_SHIELD,
    BUY_GORON_TUNIC,
    BUY_ZORA_TUNIC,
    BUY_DEKU_NUT_5,
    BUY_DEKU_NUT_5,
    BUY_DEKU_NUT_10,
    BUY_DEKU_STICK_1,
    BUY_DEKU_STICK_1,
    BUY_DEKU_SEEDS_30,
    BUY_ARROWS_10,
    BUY_ARROWS_10,
    BUY_ARROWS_30,
    BUY_ARROWS_50,
    BUY_BOMBCHU_5,
    BUY_BOMBCHU_10,
    BUY_BOMBCHU_10,
    BUY_BOMBCHU_20,
    BUY_BOMBS_525,
    BUY_BOMBS_535,
    BUY_BOMBS_10,
    BUY_BOMBS_20,
    BUY_GREEN_POTION,
    BUY_RED_POTION_30,
    BUY_BLUE_FIRE,
    BUY_FAIRYS_SPIRIT,
    BUY_BOTTLE_BUG,
    BUY_FISH,
    //^First 28 items from OoTR
    BUY_HYLIAN_SHIELD,
    BUY_BOTTLE_BUG,
    BUY_DEKU_STICK_1,
    BUY_FAIRYS_SPIRIT,
    //^First 32 items: Always guaranteed
    BUY_BLUE_FIRE,
    BUY_FISH,
    BUY_BOMBCHU_10,
    BUY_DEKU_NUT_5,
    BUY_ARROWS_10,
    BUY_BOMBCHU_20,
    BUY_BOMBS_535,
    BUY_RED_POTION_30,
    //^First 40 items: Exist on shopsanity 3 or less
    BUY_BOMBS_30,
    BUY_BOMBCHU_20,
    BUY_DEKU_NUT_5,
    BUY_ARROWS_10,
    BUY_DEKU_NUT_5,
    BUY_ARROWS_30,
    BUY_RED_POTION_40,
    BUY_FISH,
    //^First 48 items: Exist on shopsanity 2 or less
    BUY_BOMBCHU_20,
    BUY_ARROWS_30,
    BUY_RED_POTION_50,
    BUY_ARROWS_30,
    BUY_DEKU_NUT_5,
    BUY_ARROWS_50,
    BUY_ARROWS_50,
    BUY_GREEN_POTION,
    //^First 56 items: Exist on shopsanity 1 or less
    BUY_POE,
    BUY_POE,
    BUY_HEART,
    BUY_HEART,
    BUY_HEART,
    BUY_HEART,
    BUY_HEART,
    BUY_HEART,
    //^All 64 items: Only exist with shopsanity 0
  };
  //Now delete however many items there are to replace
  for (int i = 0; i < total_replaced; i++) {
    minShopItems.pop_back();
  }
  return minShopItems;
}

//This table contains a cumulative probability for each possible shop price based on
// a beta distribution with alpha = 1.5, beta = 2, and the result of the distribution, a float in [0.0, 1.0),
// being mutliplied by 60, casted to an integer, then multiplied by 5 to give a value in range [0, 295] in increments of 5.
// Meaning the first value is the probability of 0, the next value is the probability of 0 plus the probability of 5, etc.
//Probabilities generated using a python script with 1 billion trials, so should hopefully be pretty good
//Average price ~126
//~38% chance of needing no wallet, ~45% chance of needing 1, ~17% chance of needing 2
static constexpr std::array<double, 60> ShopPriceProbability= {
  0.005326994, 0.014908518, 0.027114719, 0.041315285, 0.057136304, 0.074325887, 0.092667151, 0.112002061, 0.132198214, 0.153125390,
  0.174696150, 0.196810540, 0.219388148, 0.242361379, 0.265657012, 0.289205134, 0.312970402, 0.336877590, 0.360881110, 0.384932772,
  0.408976198, 0.432982176, 0.456902494, 0.480686053, 0.504313389, 0.527746488, 0.550938554, 0.573856910, 0.596465330, 0.618736235,
  0.640646600, 0.662162782, 0.683240432, 0.703859801, 0.724001242, 0.743631336, 0.762722631, 0.781259986, 0.799198449, 0.816521905,
  0.833208595, 0.849243398, 0.864579161, 0.879211177, 0.893112051, 0.906263928, 0.918639420, 0.930222611, 0.940985829, 0.950914731,
  0.959992180, 0.968187000, 0.975495390, 0.981884488, 0.987344345, 0.991851853, 0.995389113, 0.997937921, 0.999481947, 1.000000000,
};
int GetRandomShopPrice() {
  double random = RandomDouble(); //Randomly generated probability value
  for (size_t i = 0; i < ShopPriceProbability.size(); i++) {
    if (random < ShopPriceProbability[i]) {
      //The randomly generated value has surpassed the total probability up to this point, so this is the generated price
      return i * 5; //i in range [0, 59], output in range [0, 295] in increments of 5
    }
  }
  return -1; //Shouldn't happen
}

//Similar to above, beta distribution with alpha = 1, beta = 2,
// multiplied by 20 instead of 60 to give values in rage [0, 95] in increments of 5
//Average price ~31
static constexpr std::array<double, 20> ScrubPriceProbability = {
  0.097500187, 0.190002748, 0.277509301, 0.360018376, 0.437522571, 0.510021715, 0.577520272, 0.640029304, 0.697527584, 0.750024535,
  0.797518749, 0.840011707, 0.877508776, 0.910010904, 0.937504342, 0.960004661, 0.977502132, 0.989998967, 0.997500116, 1.000000000,
};
s16 GetRandomScrubPrice() {
  double random = RandomDouble();
  for (size_t i = 0; i < ScrubPriceProbability.size(); i++) {
    if (random < ScrubPriceProbability[i]) {
      return i * 5; //i in range [0, 19], output in range [0, 95] in increments of 5
    }
  }
  return -1;
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

//A dictionary that maps a u16 to an array of 3 strings, which contain the easy, medium, and hard trick names respectively
static std::map<u8, std::array<Text, 3>> IceTrapNames = {
  {GI_SWORD_KOKIRI, {Text{"Butter Knife","",""}, Text{"Kokiri Knife","",""}, Text{"Kokiri's Sword","",""}}},
  {GI_SWORD_BGS, {Text{"Goron's Not-Broken Sword","",""}, Text{"Big Goron Sword","",""}, Text{"Biggoron's Sword","",""}}},
  {GI_SHIELD_MIRROR, {Text{"Not the 1.0 OoT Shield","",""}, Text{"Magic Shield","",""}, Text{"Mirror Sheild","",""}}},
  {GI_BOOMERANG, {Text{"Prank Fetch Toy","",""}, Text{"Magic Boomerang","",""}, Text{"Fairy Boomerang","",""}}},
  {GI_WEIRD_EGG, {Text{"D.I.Y. Alarm Clock","",""}, Text{"Lon Lon Egg","",""}, Text{"Egg","",""}}},
  {GI_LENS, {Text{"Sheikah-leidoscope","",""}, Text{"Eye of Truth","",""}, Text{"Lens o’ Truth","",""}}},
  {GI_HAMMER, {Text{"Goron Gavel","",""}, Text{"Magic Hammer","",""}, Text{"Metagon Hammer","",""}}},
  {GI_BOOTS_IRON, {Text{"Toe Shields","",""}, Text{"Steel Boots","",""}, Text{"Hover Boots","",""}}},
  {GI_BOOTS_HOVER, {Text{"Rito Slippers","",""}, Text{"Pegasus Boots","",""}, Text{"Iron Boots","",""}}},
  {GI_STONE_OF_AGONY, {Text{"Itemfinder","",""}, Text{"Crystal Shard","",""}, Text{"Stone of Agony","",""}}},
  {GI_DINS_FIRE, {Text{"Hylia's Grace","",""}, Text{"Crystal of Power","",""}, Text{"Eldin’s Fire","",""}}},
  {GI_FARORES_WIND, {Text{"Farore's Escape Dust","",""}, Text{"Crystal of Courage","",""}, Text{"Faron’s Wind","",""}}},
  {GI_NAYRUS_LOVE, {Text{"Zelda's Neutral Special","",""}, Text{"Crystal of Wisdom","",""}, Text{"Lanayru’s Love","",""}}},
  {GI_ARROW_FIRE, {Text{"Candy Apple on a Stick","",""}, Text{"Ire Arrow","",""}, Text{"Fire Arrows","",""}}},
  {GI_ARROW_ICE, {Text{"Ice Trap Arrow","",""}, Text{"Lice Arrow","",""}, Text{"Ice Arrows","",""}}},
  {GI_ARROW_LIGHT, {Text{"Shock Arrows (10)","",""}, Text{"Fight Arrow","",""}, Text{"Light Arrows","",""}}},
  {GI_GERUDO_CARD, {Text{"Gym Membership Card","",""}, Text{"Goron Token","",""}, Text{"Gerudo Card","",""}}},
  {0xC9, {Text{"Lots of Funky Beans","",""}, Text{"Mystic Beans","",""}, Text{"Magic Bean","",""}}},
  {0xB8, {Text{"Diamond Hearts","",""}, Text{"Quadruple Defense","",""}, Text{"Defense Upgrade","",""}}},
  {GI_CLAIM_CHECK, {Text{"Goron Parchment","",""}, Text{"Goron Diploma","",""}, Text{"Biggoron’s Claim Check","",""}}},
  {0x80, {Text{"Hookshot, no strings attached","",""}, Text{"Progressive Grappling Hook","",""}, Text{"Hookshot Upgrade","",""}}},
  {0x81, {Text{"Bracelet of Friendship","",""}, Text{"Progressive Power Glove","",""}, Text{"Strength Upgrade","",""}}},
  {0x82, {Text{"Bob-Omb Sleeping Bag","",""}, Text{"Progressive Bomb Box","",""}, Text{"Bomb Bag Upgrade","",""}}},
  {0x83, {Text{"Regressive Quiver","",""}, Text{"Progressive Arrow Holder","",""}, Text{"Quiver Upgrade","",""}}},
  {0x84, {Text{"Popcorn Bag","",""}, Text{"Progressive Seed Pouch","",""}, Text{"Bullet Bag Upgrade","",""}}},
  {0x85, {Text{"500 Rupees","",""}, Text{"Progressive Rupee Bag","",""}, Text{"Wallet Upgrade","",""}}},
  {0x86, {Text{"Bowling Ball Upgrade","",""}, Text{"Progressive Diving Scale","",""}, Text{"Scale Upgrade","",""}}},
  {0x8A, {Text{"Green Fuel","",""}, Text{"Progressive Magic Oil","",""}, Text{"Magic Upgrade","",""}}},
  {0x8B, {Text{"Duck Flute","",""}, Text{"Progressive Memento","",""}, Text{"Ocarina Upgrade","",""}}},
  {0x0F, {Text{"Empty fishbowl","",""}, Text{"Glass Bottle","",""}, Text{"Bottle","",""}}},
  {0x14, {Text{"Bottle with Cooking Cream","",""}, Text{"Bottle with Cow Milk","",""}, Text{"Bottle of Milk","",""}}},
  {0x8C, {Text{"Bottle with 2nd Potion","",""}, Text{"Bottle with Red Medicine","",""}, Text{"Bottle of Red Potion","",""}}},
  {0x8D, {Text{"Bottle with Vegetable Juice","",""}, Text{"Bottle with Green Medicine","",""}, Text{"Bottle of Green Potion","",""}}},
  {0x8E, {Text{"Bottle with Water","",""}, Text{"Bottle with Blue Medicine","",""}, Text{"Bottle of Blue Potion","",""}}},
  {0x8F, {Text{"Bottle with Forest Firefly","",""}, Text{"Bottle with Faerie","",""}, Text{"Bottled Fairy","",""}}},
  {0x90, {Text{"Bottle with Small Jabu-Jabu","",""}, Text{"Bottle with Tasty Fish","",""}, Text{"Bottled Fish","",""}}},
  {0x91, {Text{"Bottle with Will-O-Wisp","",""}, Text{"Bottle with Blue Flame","",""}, Text{"Bottled Blue Fire","",""}}},
  {0x92, {Text{"Bottle with Baby Tektites","",""}, Text{"Bottle with Beetles","",""}, Text{"Bottled Bugs","",""}}},
  {0x94, {Text{"Bottle with Sad Ghoul","",""}, Text{"Bottle with Ghost","",""}, Text{"Bottled Poe","",""}}},
  {0x15, {Text{"Bottle with Letter to Mama","",""}, Text{"Bottle with Note","",""}, Text{"Bottled Ruto's Letter","",""}}},
  {0x93, {Text{"Bottle with Smelly Ghost","",""}, Text{"Bottle with Big Ghost","",""}, Text{"Bottled Big Poe","",""}}},
  {0xC1, {Text{"Zelda's Best Hits","",""}, Text{"Zelda's Song","",""}, Text{"Nocturne of Shadow","",""}}},
  {0xC2, {Text{"Song of Cows","",""}, Text{"Epona's Ballad","",""}, Text{"Requiem of Spirit","",""}}},
  {0xC3, {Text{"Saria's Remix Album","",""}, Text{"Saria's Fugue","",""}, Text{"Minuet of Forest","",""}}},
  {0xC4, {Text{"Salute the Sun's Song","",""}, Text{"Sun's Chimes","",""}, Text{"Prelude of Light","",""}}},
  {0xC5, {Text{"Song of Passing Time","",""}, Text{"Canon of Time","",""}, Text{"Serenade of Water","",""}}},
  {0xC6, {Text{"Song of Happy Frogs","",""}, Text{"Sonata of Storms","",""}, Text{"Bolero of Fire","",""}}},
  {0xBB, {Text{"Saria's Karaoke","",""}, Text{"Minuet of the Meadow","",""}, Text{"Saria's Song","",""}}},
  {0xBC, {Text{"Darunia's Tango","",""}, Text{"Bolero of the Crater","",""}, Text{"Epona's Song","",""}}},
  {0xBD, {Text{"Ruto's Blues","",""}, Text{"Serenade of the Lake","",""}, Text{"Song of Storms","",""}}},
  {0xBE, {Text{"Nabooru's Reggae","",""}, Text{"Requiem of the Colossus","",""}, Text{"Epona's Song","",""}}},
  {0xBF, {Text{"Impa's Death Metal","",""}, Text{"Nocturme of the Graveyard","",""}, Text{"Zelda's Lullaby","",""}}},
  {0xC0, {Text{"Rauru's Sing-Along","",""}, Text{"Prelude of Time","",""}, Text{"Sun's Song","",""}}},
  {0xCB, {Text{"Farore's Brooch","",""}, Text{"Deku Tree's Emerald","",""}, Text{"Kokiri's Emerald","",""}}},
  {0xCC, {Text{"Din's Candied Rock","",""}, Text{"Gerudo's Ruby","",""}, Text{"Goron's Ruby","",""}}},
  {0xCD, {Text{"Nayru's Mood Ring","",""}, Text{"Zola's Sapphire","",""}, Text{"Zora's Sapphire","",""}}},
  {0xCE, {Text{"Bombos","",""}, Text{"Saria's Medallion","",""}, Text{"Medallion of Forest","",""}}},
  {0xCF, {Text{"Fire Emblem","",""}, Text{"Darunia's Medallion","",""}, Text{"Medallion of Fire","",""}}},
  {0xD0, {Text{"Water Gym Badge","",""}, Text{"Ruto's Medallion","",""}, Text{"Medallion of Water","",""}}},
  {0xD1, {Text{"Gerudo Doubloon","",""}, Text{"Nabooru's Medallion","",""}, Text{"Medallion of Spirit","",""}}},
  {0xD2, {Text{"Hyrule Purple Coin","",""}, Text{"Impa's Medallion","",""}, Text{"Medallion of Shadow","",""}}},
  {0xD3, {Text{"Coins (50)","",""}, Text{"Rauru's Medallion","",""}, Text{"Medallion of Light","",""}}},
};
//Generate a fake name for the ice trap based on the item it's displayed as
Text GetIceTrapName(u8 id) {
  //Randomly get the easy, medium, or hard name for the given item id
  return RandomElement(IceTrapNames[id]);
}

//Get shop index based on a given location
static std::map<std::string_view, int> ShopNameToNum = {{"KF Shop", 0},{"Kak Potion Shop", 1},{"MK Bombchu Shop", 2},{"MK Potion Shop", 3},
                                                        {"MK Bazaar", 4},{"Kak Bazaar", 5},{"ZD Shop", 6},{"GC Shop", 7}};
int GetShopIndex(LocationKey loc) {
  //Kind of hacky, but extract the shop and item position from the name
  const std::string& name(Location(loc)->GetName());
  int split = name.find(" Item ");
  std::string_view shop(name.c_str(), split);
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
