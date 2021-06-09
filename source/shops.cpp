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

//A dictionary that maps a u16 to an array of 3 Text objects, which contain the easy, medium, and hard trick names respectively
static std::map<u8, std::array<Text, 3>> IceTrapNames = {
  {GI_SWORD_KOKIRI,
         //English          French                      Spanish
    {Text{"Butter Knife",  "Couteau à fromage Kokiri", ""},      //Easy
    Text{"Kokiri Knife",   "Épée Mojo",                ""},      //Medium
    Text{"Kokiri's Sword", "Épée de Kokiri",           ""}}},    //Hard
  {GI_SWORD_BGS, 
    {Text{"Goron's Not-Broken Sword", "Épée pas brisée de Goron", ""}, 
    Text{"Big Goron Sword",           "Épée de gros Goron",       ""}, 
    Text{"Biggoron's Sword",          "Épée Grogoron",            ""}}},
  {GI_SHIELD_MIRROR, 
    {Text{"Not the 1.0 OoT Shield", "Miroir magique",   ""}, 
    Text{"Magic Shield",            "Bouclier magique", ""}, 
    Text{"Mirror Sheild",           "Bouclier-miroir",  ""}}},
  {GI_BOOMERANG, 
    {Text{"Prank Fetch Toy", "Inséparable bâtonnet", ""}, 
    Text{"Magic Boomerang",  "Boomerang magique",    ""}, 
    Text{"Fairy Boomerang",  "Boomerang des fées",   ""}}},
  {GI_WEIRD_EGG, 
    {Text{"D.I.Y. Alarm Clock", "Réveille-matin improvisé", ""}, 
    Text{"Lon Lon Egg",         "Oeuf Lon Lon",             ""}, 
    Text{"Egg",                 "Oeuf",                     ""}}},
  {GI_LENS, 
    {Text{"Sheikah-leidoscope", "Sheikah-léidoscope", ""}, 
    Text{"Eye of Truth",        "Oeil de vérité",     ""}, 
    Text{"Lens o’ Truth",       "Loupe de la vérité", ""}}},
  {GI_HAMMER, 
    {Text{"Goron Gavel",        "Marteau de juge",    ""}, 
    Text{"Magic Hammer",        "Marteau des titans", ""}, 
    Text{"Metagon Hammer",      "Masse de titan",     ""}}},
  {GI_BOOTS_IRON, 
    {Text{"Toe Shields", "Couvre-orteils",  ""}, 
    Text{"Steel Boots",  "Bottes plombées", ""}, 
    Text{"Hover Boots",  "Bottes de fer",   ""}}},
  {GI_BOOTS_HOVER, 
    {Text{"Rito Slippers", "Pantoufles Rito", ""}, 
    Text{"Pegasus Boots",  "Bottes pégase",   ""}, 
    Text{"Iron Boots",     "Bottes de l’air", ""}}},
  {GI_STONE_OF_AGONY, 
    {Text{"Itemfinder",    "Cherch’Objet",         ""}, 
    Text{"Crystal Shard",  "Fragment de cristal",  ""}, 
    Text{"Stone of Agony", "Pierre de souffrance", ""}}},
  {GI_DINS_FIRE, 
    {Text{"Hylia's Grace",   "Grâce d’Hylia",  ""}, 
    Text{"Crystal of Power", "Cristal de Din", ""}, 
    Text{"Eldin’s Fire",     "Feu d’Eldin",    ""}}},
  {GI_FARORES_WIND, 
    {Text{"Farore's Escape Dust", "Poudre d’escampette Farore", ""}, 
    Text{"Crystal of Courage",    "Cristal de Farore",          ""}, 
    Text{"Faron’s Wind",          "Vent de Firone",             ""}}},
  {GI_NAYRUS_LOVE, 
    {Text{"Zelda's Neutral Special", "Spécial neutre de Zelda", ""}, 
    Text{"Crystal of Wisdom",        "Cristal de Nayru",        ""}, 
    Text{"Lanayru’s Love",           "Amour de Lanelle",        ""}}},
  {GI_ARROW_FIRE, 
    {Text{"Candy Apple on a Stick", "Pomme confite",      ""}, 
    Text{"Ire Arrow",               "Flèche des flammes", ""}, 
    Text{"Fire Arrows",             "Flèches de feu",     ""}}},
  {GI_ARROW_ICE, 
    {Text{"Ice Trap Arrow", "Flèche de piège de glace", ""}, 
    Text{"Lice Arrow",      "Flèche des glaces",        ""}, 
    Text{"Ice Arrows",      "Flèches de glace",         ""}}},
  {GI_ARROW_LIGHT, 
    {Text{"Shock Arrows (10)", "Flèche électrique (10)", ""}, 
    Text{"Fight Arrow",        "Flèche des cieux",       ""}, 
    Text{"Light Arrows",       "Flèches de lumière",     ""}}},
  {GI_GERUDO_CARD, 
    {Text{"Gym Membership Card", "Abonnement Gerudo", ""}, 
    Text{"Goron Token",          "Carte Goron",       ""}, 
    Text{"Gerudo Card",          "Carte de Gerudo",   ""}}},
  {0xC9, 
    {Text{"Lots of Funky Beans", "Hari-clowns magiques", ""}, 
    Text{"Mystic Beans",         "Haricot mystique",     ""}, 
    Text{"Magic Bean",           "Haricot de magie",     ""}}},
  {0xB8, 
    {Text{"Diamond Hearts",      "Coeurs de diamant",   ""}, 
    Text{"Quadruple Defense",    "Défence quadruple",   ""}, 
    Text{"Defense Upgrade",      "Défence progressive", ""}}},
  {GI_CLAIM_CHECK, 
    {Text{"Goron Parchment",       "Parchemin rigide",    ""}, 
    Text{"Goron Diploma",          "Diplôme Goron",       ""}, 
    Text{"Biggoron’s Claim Check", "Certificat Grogoron", ""}}},
  {0x80, 
    {Text{"Hookshot, no strings attached", "Grappin sans attrape",      ""}, 
    Text{"Progressive Grappling Hook",     "Grappin-griffe progressif", ""}, 
    Text{"Hookshot Upgrade",               "Grappin (progressif)",      ""}}},
  {0x81, 
    {Text{"Bracelet of Friendship", "Bracelet d’amitié",              ""}, 
    Text{"Progressive Power Glove", "Mitaine de force progressive",   ""}, 
    Text{"Strength Upgrade",        "Bracelet de force (progressif)", ""}}},
  {0x82, 
    {Text{"Bob-Omb Sleeping Bag", "Sac à bonbons",              ""}, 
    Text{"Progressive Bomb Box",  "Sac de grenades progressif", ""}, 
    Text{"Bomb Bag Upgrade",      "Sac de bombes (progressif)", ""}}},
  {0x83, 
    {Text{"Regressive Quiver",       "Carquois régressif",       ""}, 
    Text{"Progressive Arrow Holder", "Truc à flèche progressif", ""},
    Text{"Quiver Upgrade",           "Carquois (progressif)",    ""}}},
  {0x84, 
    {Text{"Popcorn Bag",           "Sac à collation",             ""}, 
    Text{"Progressive Seed Pouch", "Sac de noisettes progressif", ""}, 
    Text{"Bullet Bag Upgrade",     "Sac de graines (progressif)", ""}}},
  {0x85, 
    {Text{"500 Rupees",           "Plein, plein de fric", ""}, 
    Text{"Progressive Rupee Bag", "Sacoche progressive",  ""}, 
    Text{"Wallet Upgrade",        "Bourse (progressive)", ""}}},
  {0x86, 
    {Text{"Bowling Ball Upgrade",    "Boule de bowling progressive", ""}, 
    Text{"Progressive Diving Scale", "Bulle progressive",            ""}, 
    Text{"Scale Upgrade",            "Écaille (progressive)",        ""}}},
  {0x8A, 
    {Text{"Green Fuel",           "Carburant vert",                 ""}, 
    Text{"Progressive Magic Oil", "Huile magique progressive",      ""}, 
    Text{"Magic Upgrade",         "Capacité magique (progressive)", ""}}},
  {0x8B, 
    {Text{"Duck Flute",         "Flûte à canard",         ""}, 
    Text{"Progressive Memento", "Clarinette progressive", ""}, 
    Text{"Ocarina Upgrade",     "Ocarina (progressif)",   ""}}},
  {0x0F, 
    {Text{"Empty fishbowl", "Bocal de verre", ""}, 
    Text{"Glass Bottle",    "Bouteille",      ""}, 
    Text{"Bottle",          "Flacon",         ""}}},
  {0x14, 
    {Text{"Bottle with Cooking Cream", "Flacon de crème à cuisson", ""}, 
    Text{"Bottle with Cow Milk",       "Flacon de lait de vache",   ""}, 
    Text{"Bottle of Milk",             "Lait en flacon",            ""}}},
  {0x8C, 
    {Text{"Bottle with 2nd Potion",  "Flacon de 2e potion",    ""}, 
    Text{"Bottle with Red Medicine", "Flacon d’élixir rouge",  ""}, 
    Text{"Bottle of Red Potion",     "Potion rouge en flacon", ""}}},
  {0x8D, 
    {Text{"Bottle with Vegetable Juice", "Flacon de jus de légumes", ""}, 
    Text{"Bottle with Green Medicine",   "Flacon d’élixir vert",     ""}, 
    Text{"Bottle of Green Potion",       "Potion verte en flacon",   ""}}},
  {0x8E, 
    {Text{"Bottle with Water",        "Flacon d’eau",           ""}, 
    Text{"Bottle with Blue Medicine", "Flacon d’élixir bleu",   ""}, 
    Text{"Bottle of Blue Potion",     "Potion bleue en flacon", ""}}},
  {0x8F, 
    {Text{"Bottle with Forest Firefly", "Flacon avec une luciole",   ""}, 
    Text{"Bottle with Faerie",          "Flacon de poudre féérique", ""}, 
    Text{"Bottled Fairy",               "Fée en flacon",             ""}}},
  {0x90, 
    {Text{"Bottle with Small Jabu-Jabu", "Flacon de mini Jabu-Jabu", ""}, 
    Text{"Bottle with Tasty Fish",       "Flacon aquarium",          ""}, 
    Text{"Bottled Fish",                 "Poisson en flacon",        ""}}},
  {0x91, 
    {Text{"Bottle with Will-O-Wisp", "Chauffe-eau portable",   ""}, 
    Text{"Bottle with Blue Flame",   "Lanterne bleue",         ""}, 
    Text{"Bottled Blue Fire",        "Flamme bleue en flacon", ""}}},
  {0x92, 
    {Text{"Bottle with Baby Tektites", "Flacon de bébé Araknon", ""}, 
    Text{"Bottle with Beetles",        "Flacon insectarium",     ""}, 
    Text{"Bottled Bugs",               "Insectes en flacon",     ""}}},
  {0x94, 
    {Text{"Bottle with Sad Ghoul", "Flacon de souvenirs", ""}, 
    Text{"Bottle with Ghost",      "Urne d’Esprit",       ""}, 
    Text{"Bottled Poe",            "Esprit en flacon",    ""}}},
  {0x15, 
    {Text{"Bottle with Letter to Mama", "Lettre pour maman en flacon", ""}, 
    Text{"Bottle with Note",            "Flacon avec une envelope",    ""}, 
    Text{"Bottled Ruto's Letter",       "Lettre de Ruto en flacon",    ""}}},
  {0x93, 
    {Text{"Bottle with Smelly Ghost", "Flacon avec chose puante", ""}, 
    Text{"Bottle with Big Ghost",     "Urne d’Âme",               ""}, 
    Text{"Bottled Big Poe",           "Âme en flacon",            ""}}},
  {0xC1, 
    {Text{"Zelda's Best Hits", "Réveille-matin de Zelda", ""}, 
    Text{"Zelda's Song",       "Chant de Zelda",          ""}, 
    Text{"Nocturne of Shadow", "Nocturne de l’ombre",     ""}}},
  {0xC2, 
    {Text{"Song of Cows",     "Chant des vaches",    ""}, 
    Text{"Epona's Ballad",    "Ballade d’Épona",     ""}, 
    Text{"Requiem of Spirit", "Requiem des esprits", ""}}},
  {0xC3, 
    {Text{"Saria's Remix Album", "Album medley de Saria", ""}, 
    Text{"Saria's Fugue",        "Fugue de Saria",        ""}, 
    Text{"Minuet of Forest",     "Menuet de la forêt",    ""}}},
  {0xC4, 
    {Text{"Salute the Sun's Song", "Chant des oreilles",    ""}, 
    Text{"Sun's Chimes",           "Matines du soleil",     ""}, 
    Text{"Prelude of Light",       "Prélude de la lumière", ""}}},
  {0xC5, 
    {Text{"Song of Passing Time", "Chant des horloges", ""}, 
    Text{"Canon of Time",         "Canons du temps",    ""}, 
    Text{"Serenade of Water",     "Sérénade de l’eau",  ""}}},
  {0xC6, 
    {Text{"Song of Happy Frogs", "Chant des crapauds",  ""}, 
    Text{"Sonata of Storms",     "Sonate des tempêtes", ""}, 
    Text{"Bolero of Fire",       "Boléro du feu",       ""}}},
  {0xBB, 
    {Text{"Saria's Karaoke",     "Karaoke de Saria",       ""}, 
    Text{"Minuet of the Meadow", "Menuet de la clairière", ""}, 
    Text{"Saria's Song",         "Chant de Saria",         ""}}},
  {0xBC, 
    {Text{"Darunia's Tango",     "Tango de Darunia",   ""}, 
    Text{"Bolero of the Crater", "Boléro du cratère",  ""}, 
    Text{"Epona's Song",         "Chant des tempêtes", ""}}},
  {0xBD, 
    {Text{"Ruto's Blues",        "Blues de Ruto",   ""}, 
    Text{"Serenade of the Lake", "Sérénade du lac", ""}, 
    Text{"Song of Storms",       "Chant du temps",  ""}}},
  {0xBE, 
    {Text{"Nabooru's Reggae",       "Reggae de Nabooru",  ""}, 
    Text{"Requiem of the Colossus", "Requiem du colosse", ""}, 
    Text{"Epona's Song",            "Chant d’Épona",      ""}}},
  {0xBF, 
    {Text{"Impa's Death Metal",       "Death métal d’Impa",    ""}, 
    Text{"Nocturme of the Graveyard", "Nocturne du cimetière", ""}, 
    Text{"Zelda's Lullaby",           "Berceuse de Zelda",     ""}}},
  {0xC0, 
    {Text{"Rauru's Sing-Along", "Chansonette de Rauru", ""}, 
    Text{"Prelude of Time",     "Prélude du temps",     ""}, 
    Text{"Sun's Song",          "Chant du soleil",      ""}}},
  {0xCB, 
    {Text{"Farore's Brooch",    "Bijou de Farore",      ""}, 
    Text{"Deku Tree's Emerald", "Émeraude Mojo",        ""}, 
    Text{"Kokiri's Emerald",    "Émeraude des Kokiris", ""}}},
  {0xCC, 
    {Text{"Din's Candied Rock", "Bonbon de Din",    ""}, 
    Text{"Gerudo's Ruby",       "Rubis Gerudo",     ""}, 
    Text{"Goron's Ruby",        "Rubis des Gorons", ""}}},
  {0xCD, 
    {Text{"Nayru's Mood Ring", "Épingle de Nayru", ""}, 
    Text{"Zola's Sapphire",    "Saphir Zola",      ""}, 
    Text{"Zora's Sapphire",    "Saphir des Zoras", ""}}},
  {0xCE, 
    {Text{"Bombos",             "Bombos",             ""}, 
    Text{"Saria's Medallion",   "Médaillon de Saria", ""}, 
    Text{"Medallion of Forest", "Médaillon de forêt", ""}}},
  {0xCF, 
    {Text{"Fire Emblem",        "La Fire Emblem",       ""}, 
    Text{"Darunia's Medallion", "Médaillon de Darunia", ""}, 
    Text{"Medallion of Fire",   "Médaillon de feu",     ""}}},
  {0xD0, 
    {Text{"Water Gym Badge",   "Badge du gym d’eau", ""}, 
    Text{"Ruto's Medallion",   "Médaillon de Ruto",  ""}, 
    Text{"Medallion of Water", "Médaillon d’eau",    ""}}},
  {0xD1, 
    {Text{"Gerudo Doubloon",    "Doublon Gerudo",       ""}, 
    Text{"Nabooru's Medallion", "Médaillon de Nabooru", ""}, 
    Text{"Medallion of Spirit", "Médaillon d’esprit",   ""}}},
  {0xD2, 
    {Text{"Hyrule Purple Coin", "Pièce mauve d’Hyrule", ""}, 
    Text{"Impa's Medallion",    "Médaillon d’Impa",     ""}, 
    Text{"Medallion of Shadow", "Médaillon d’ombre",    ""}}},
  {0xD3, 
    {Text{"Coins (50)",        "Pièces (50)",          ""}, 
    Text{"Rauru's Medallion",  "Médaillon de Rauru",   ""}, 
    Text{"Medallion of Light", "Médaillon de lumière", ""}}},
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
