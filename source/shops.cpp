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
    //First 48 items: Exist on shopsanity 2 or less
    BUY_BOMBCHU_20,
    BUY_ARROWS_30,
    BUY_RED_POTION_50,
    BUY_ARROWS_30,
    BUY_DEKU_NUT_5,
    BUY_ARROWS_50,
    BUY_ARROWS_50,
    BUY_GREEN_POTION,
    //First 56 items: Exist on shopsanity 1 or less
    BUY_POE,
    BUY_POE,
    BUY_HEART,
    BUY_HEART,
    BUY_HEART,
    BUY_HEART,
    BUY_HEART,
    BUY_HEART,
    //All 64 items: Only exist with shopsanity 0
  };
  //Now delete however many items there are to replace
  for (int i = 0; i < total_replaced; i++) {
    minShopItems.pop_back();
  }
  return minShopItems;
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

//A dictionary that maps a u16 to an array of 3 strings, which contain the easy, medium, and hard trick names respectively
static std::map<u16, std::array<std::string, 3>> IceTrapNames = {
  {GI_SWORD_KOKIRI, {"Butter Knife", "Kokiri Knife", "Kokiri's Sword"}},
  {GI_SWORD_BGS, {"Goron's Not-Broken Sword", "Big Goron Sword", "Biggoron's Sword"}},
  {GI_SHIELD_MIRROR, {"Not the 1.0 OoT Shield", "Red Shield", "Mirror Sheild"}},
  {GI_BOOMERANG, {"Prank Fetch Toy", "Magic Boomerang", "Fairy Boomerang"}},
  {GI_WEIRD_EGG, {"D.I.Y. Alarm Clock", "Lon Lon Egg", "Egg"}},
  {GI_LENS, {"Sheikah-leidoscope", "Eye of Truth", "Lens Of Truth"}},
  {GI_HAMMER, {"Goron Gavel", "Magic Hammer", "Metagon Hammer"}},
  {GI_BOOTS_IRON, {"Toe Shields", "Steel Boots", "Hover Boots"}},
  {GI_BOOTS_HOVER, {"Rito Slippers", "Pegasus Boots", "Iron Boots"}},
  {GI_STONE_OF_AGONY, {"Itemfinder", "Crystal Shard", "Stone of Agony"}},
  {GI_DINS_FIRE, {"Hylia's Grace", "Crystal of Power", "Din's Fire (Magic-Free)"}},
  {GI_FARORES_WIND, {"Farore's Escape Dust", "Crystal of Courage", "Farore's Wind (Magic-Free)"}},
  {GI_NAYRUS_LOVE, {"Zelda's Neutral Special", "Crystal of Wisdom", "Nayru's Love (Magic-Free)"}},
  {GI_ARROW_FIRE, {"Candy Apple on a Stick", "Ire Arrow", "Fire Arrows"}},
  {GI_ARROW_ICE, {"Ice Trap Arrow", "Lice Arrow", "Ice Arrows"}},
  {GI_ARROW_LIGHT, {"Shock Arrows (10)", "Fight Arrow", "Light Arrows"}},
  {GI_GERUDO_CARD, {"Gym Membership Card", "Goron Token", "Gerudo Card"}},
  {0xC9, {"Lots of Funky Beans", "Mystic Beans", "Magic Bean"}},
  {0xB8, {"Diamond Hearts", "Quadruple Defense", "Defense Upgrade"}},
  {GI_CLAIM_CHECK, {"Goron Parchment", "Biggoron's Check", "Progressive Adult Item"}},
  {0x80, {"Hookshot, no strings attached", "Progressive Grappling Hook", "Hookshot Upgrade"}},
  {0x81, {"Bracelet of Friendship", "Progressive Power Glove", "Strength Upgrade"}},
  {0x82, {"Bob-Omb Sleeping Bag", "Progressive Bomb Box", "Bomb Bag Upgrade"}},
  {0x83, {"Regressive Quiver", "Progressive Arrow Holder", "Quiver Upgrade"}},
  {0x84, {"Popcorn Bag", "Progressive Seed Pouch", "Bullet Bag Upgrade"}},
  {0x85, {"500 Rupees", "Progressive Rupee Bag", "Wallet Upgrade"}},
  {0x86, {"Bowling Ball Upgrade", "Progressive Diving Scale", "Scale Upgrade"}},
  {0x8A, {"Green Fuel", "Progressive Magic Oil", "Magic Upgrade"}},
  {0x8B, {"Duck Flute", "Progressive Memento", "Ocarina Upgrade"}},
  {0x0F, {"Transparent Canteen (7)", "Glass Bottle", "Bottle"}},
  {0x14, {"Bottle with 30% Cream", "Bottle with Cow Milk", "Bottle of Milk"}},
  {0x8C, {"Bottle with 2nd Potion", "Bottle with Red Medicine", "Bottle of Red Potion"}},
  {0x8D, {"Bottle with Vegetable Juice", "Bottle with Green Medicine", "Bottle of Green Potion"}},
  {0x8E, {"Bottle with Water", "Bottle with Blue Medicine", "Bottle of Blue Potion"}},
  {0x8F, {"Bottle with Forest Firefly", "Bottle with Faerie", "Bottled Fairy"}},
  {0x90, {"Bottle with Small Jabu-Jabu", "Bottle with Tasty Fish", "Bottled Fish"}},
  {0x91, {"Blue Fire in a Glass Cup", "Bottle with Blue Flame", "Bottled Blue Fire"}},
  {0x92, {"Bottle with Baby Tektites", "Bottle with Beetles", "Bottled Bugs"}},
  {0x94, {"Bottle with Sad Ghoul", "Bottle with Ghost", "Bottled Poe"}},
  {0x15, {"Bottle with Letter to Mama", "Bottle with Note", "Bottled Ruto's Letter"}},
  {0x93, {"Bottle with Smelly Ghost", "Bottle with Big Ghost", "Bottled Big Poe"}},
  {0xC1, {"Zelda's Best Hits", "Zelda's Song", "Nocturne of Shadow"}},
  {0xC2, {"Song of Cows", "Epona's Ballad", "Requiem of Spirit"}},
  {0xC3, {"Saria's Remix Album", "Saria's Fugue", "Minuet of Forest"}},
  {0xC4, {"Salute the Sun's Song", "Sun's Chimes", "Prelude of Light"}},
  {0xC5, {"Song of Passing Time", "Canon of Time", "Serenade of Water"}},
  {0xC6, {"Song of Happy Frogs", "Sonata of Storms", "Bolero of Fire"}},
  {0xBB, {"Saria's Karaoke", "Mazurka of Forest", "Saria's Song"}},
  {0xBC, {"Darunia's Tango", "Barcarolle of Fire", "Epona's Song"}},
  {0xBD, {"Ruto's Blues", "Sonatina of Water", "Song of Storms"}},
  {0xBE, {"Nabooru's Reggae", "Rhapsody of Spirit", "Epona's Song"}},
  {0xBF, {"Impa's Death Metal", "Nuptials of Shadow", "Zelda's Lullaby"}},
  {0xC0, {"Rauru's Sing-Along", "Etude of Light", "Sun's Song"}},
  {0xCB, {"Farore's Crystal Ball", "Deku Tree's Emerald", "Kokiri's Emerald"}},
  {0xCC, {"Din's Candied Rock", "Gerudo's Ruby", "Goron's Ruby"}},
  {0xCD, {"Nayru's Mood Ring", "Ruto's Sapphire", "Zora's Sapphire"}},
  {0xCE, {"Red Medallion of Fire", "Saria's Medallion", "Medallion of Forest"}},
  {0xCF, {"Fire Emblem", "Darunia's Medallion", "Medallion of Fire"}},
  {0xD0, {"Water Gym Badge", "Ruto's Medallion", "Medallion of Water"}},
  {0xD1, {"Gerudo Doubloon", "Nabooru's Medallion", "Medallion of Spirit"}},
  {0xD2, {"Hyrule Purple Coin", "Impa's Medallion", "Medallion of Shadow"}},
  {0xD3, {"Coins (50)", "Rauru's Medallion", "Medallion of Light"}},
};

//Generate a fake name for the ice trap based on the item it's written as
std::string GetIceTrapName(u8 id) {
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
