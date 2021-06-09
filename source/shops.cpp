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
    {Text{"Butter Knife",  "Couteau à fromage Kokiri", "Cuchillo de untar"},      //Easy
    Text{"Kokiri Knife",   "Épée Mojo",                "Espada Koquiri"},         //Medium
    Text{"Kokiri's Sword", "Épée de Kokiri",           "Espada de los Kokiri"}}}, //Hard
  {GI_SWORD_BGS, 
    {Text{"Goron's Not-Broken Sword", "Épée pas brisée de Goron", "Espada irrompible goron"}, 
    Text{"Big Goron Sword",           "Épée de gros Goron",       "Espada de Big Goron"}, 
    Text{"Biggoron's Sword",          "Épée Grogoron",            "Espada Biggoron"}}},
  {GI_SHIELD_MIRROR, 
    {Text{"Not the 1.0 OoT Shield", "Miroir magique",   "Escudo de la 1.0"}, 
    Text{"Magic Shield",            "Bouclier magique", "Escudo gerudo"}, 
    Text{"Mirror Sheild",           "Bouclier-miroir",  "Escudo reflector"}}},
  {GI_BOOMERANG, 
    {Text{"Prank Fetch Toy", "Inséparable bâtonnet", "Plátano volador"}, 
    Text{"Magic Boomerang",  "Boomerang magique",    "Bumerán de las hadas"}, 
    Text{"Fairy Boomerang",  "Boomerang des fées",   "Bumerang"}}},
  {GI_WEIRD_EGG, 
    {Text{"D.I.Y. Alarm Clock", "Réveille-matin improvisé", "Despertador Lon Lon"}, 
    Text{"Lon Lon Egg",         "Oeuf Lon Lon",             "Huevo Lon Lon"}, 
    Text{"Egg",                 "Oeuf",                     "Huevo de bolsillo"}}},
  {GI_LENS, 
    {Text{"Sheikah-leidoscope", "Sheikah-léidoscope", "Monóculo de la Verdad"}, 
    Text{"Eye of Truth",        "Oeil de vérité",     "Ojo de la Verdad"}, 
    Text{"Lens o’ Truth",       "Loupe de la vérité", "Lentes de la Verdad"}}},
  {GI_HAMMER, 
    {Text{"Goron Gavel",        "Marteau de juge",    "Martillo Goron"}, 
    Text{"Magic Hammer",        "Marteau des titans", "Mazo Megatón"}, 
    Text{"Metagon Hammer",      "Masse de titan",     "Martillo Megaton"}}},
  {GI_BOOTS_IRON, 
    {Text{"Toe Shields", "Couvre-orteils",  "Botas voladoras"}, 
    Text{"Steel Boots",  "Bottes plombées", "Botas de plomo"}, 
    Text{"Hover Boots",  "Bottes de fer",   "Botas pesadas"}}},
  {GI_BOOTS_HOVER, 
    {Text{"Rito Slippers", "Pantoufles Rito", "Botas de hierro"}, 
    Text{"Pegasus Boots",  "Bottes pégase",   "Botas de Pegaso"}, 
    Text{"Iron Boots",     "Bottes de l’air", "Botas resbaladizas"}}},
  {GI_STONE_OF_AGONY, 
    {Text{"Itemfinder",    "Cherch’Objet",         "Trozo de la Agonía"}, 
    Text{"Crystal Shard",  "Fragment de cristal",  "Fragmento de la Agonía"}, 
    Text{"Stone of Agony", "Pierre de souffrance", "Piedra de la Agonia"}}},
  {GI_DINS_FIRE, 
    {Text{"Hylia's Grace",   "Grâce d’Hylia",  "Orbe de Din"}, 
    Text{"Crystal of Power", "Cristal de Din", "Llamas de Din"}, 
    Text{"Eldin’s Fire",     "Feu d’Eldin",    "Fuego de Din (Magia infinita)"}}},
  {GI_FARORES_WIND, 
    {Text{"Farore's Escape Dust", "Poudre d’escampette Farore", "Orbe de Farore"}, 
    Text{"Crystal of Courage",    "Cristal de Farore",          "Teletransporte de Farore"}, 
    Text{"Faron’s Wind",          "Vent de Firone",             "Viento de Farore (Magia infinita)"}}},
  {GI_NAYRUS_LOVE, 
    {Text{"Zelda's Neutral Special", "Spécial neutre de Zelda", "Orbe de Nayru"}, 
    Text{"Crystal of Wisdom",        "Cristal de Nayru",        "Bendición de Nayru"}, 
    Text{"Lanayru’s Love",           "Amour de Lanelle",        "Amor de Nayru (Magia infinita)"}}},
  {GI_ARROW_FIRE, 
    {Text{"Candy Apple on a Stick", "Pomme confite",      "Rupia roja voladora"}, 
    Text{"Ire Arrow",               "Flèche des flammes", "Flechas ígneas"}, 
    Text{"Fire Arrows",             "Flèches de feu",     "Flechas de Fuego"}}},
  {GI_ARROW_ICE, 
    {Text{"Ice Trap Arrow", "Flèche de piège de glace", "Rupia azul voladora"}, 
    Text{"Lice Arrow",      "Flèche des glaces",        "Flechas gélidas"}, 
    Text{"Ice Arrows",      "Flèches de glace",         "Flechas de Hielo"}}},
  {GI_ARROW_LIGHT, 
    {Text{"Shock Arrows (10)", "Flèche électrique (10)", "Rupia amarilla voladora"}, 
    Text{"Fight Arrow",        "Flèche des cieux",       "Arco de la Luz"}, 
    Text{"Light Arrows",       "Flèches de lumière",     "Flechas de Luz"}}},
  {GI_GERUDO_CARD, 
    {Text{"Gym Membership Card", "Abonnement Gerudo", "Pase de socio goron"}, 
    Text{"Goron Token",          "Carte Goron",       "Tóken Gerudo"}, 
    Text{"Gerudo Card",          "Carte de Gerudo",   "Pase Gerudo"}}},
  {0xC9, 
    {Text{"Lots of Funky Beans", "Hari-clowns magiques", "Frijoles mágicos"}, 
    Text{"Mystic Beans",         "Haricot mystique",     "Habichuelas místicas"}, 
    Text{"Magic Bean",           "Haricot de magie",     "Judías Mágicas"}}},
  {0xB8, 
    {Text{"Diamond Hearts",      "Coeurs de diamant",   "Contenedor de corazón (2x1)"}, 
    Text{"Quadruple Defense",    "Défence quadruple",   "Defensa cuádruple"}, 
    Text{"Defense Upgrade",      "Défence progressive", "Mejora de Defensa"}}},
  {GI_CLAIM_CHECK, 
    {Text{"Goron Parchment",       "Parchemin rigide",    "Molde goron"}, 
    Text{"Goron Diploma",          "Diplôme Goron",       "Albarán goron"}, 
    Text{"Biggoron’s Claim Check", "Certificat Grogoron", "Recibo goron"}}},
  {0x80, 
    {Text{"Hookshot, no strings attached", "Grappin sans attrape",      "Gancho garra"}, 
    Text{"Progressive Grappling Hook",     "Grappin-griffe progressif", "Gancho de Dampé"}, 
    Text{"Hookshot Upgrade",               "Grappin (progressif)",      "Gancho (mayor longitud)"}}},
  {0x81, 
    {Text{"Bracelet of Friendship", "Bracelet d’amitié",              "Brazalete de la amistad"}, 
    Text{"Progressive Power Glove", "Mitaine de force progressive",   "Guanteletes de fuerza"}, 
    Text{"Strength Upgrade",        "Bracelet de force (progressif)", "Mejora de Fuerza"}}},
  {0x82, 
    {Text{"Bob-Omb Sleeping Bag", "Sac à bonbons",              "Saco de dormir explosivo"}, 
    Text{"Progressive Bomb Box",  "Sac de grenades progressif", "Zurrón de bombas"}, 
    Text{"Bomb Bag Upgrade",      "Sac de bombes (progressif)", "Saco de bombas descomunal"}}},
  {0x83, 
    {Text{"Regressive Quiver",       "Carquois régressif",       "Arco Kokiri (Carcaj de 20 flechas)"}, 
    Text{"Progressive Arrow Holder", "Truc à flèche progressif", "Arco (Carcag enorme)"},
    Text{"Quiver Upgrade",           "Carquois (progressif)",    "Arco de las hadas (Más flechas)"}}},
  {0x84, 
    {Text{"Popcorn Bag",           "Sac à collation",             "Tirachinas (Bolsa de 20 nueces)"}, 
    Text{"Progressive Seed Pouch", "Sac de noisettes progressif", "Resortera (Bolsa enorme de semillas)"}, 
    Text{"Bullet Bag Upgrade",     "Sac de graines (progressif)", "Resortera de las hadas (Más semillas)"}}},
  {0x85, 
    {Text{"500 Rupees",           "Plein, plein de fric", "Bolsa de rupias (400)"}, 
    Text{"Progressive Rupee Bag", "Sacoche progressive",  "Saco de rupias enorme"}, 
    Text{"Wallet Upgrade",        "Bourse (progressive)", "Bolsa de rupias descomunal"}}},
  {0x86, 
    {Text{"Bowling Ball Upgrade",    "Boule de bowling progressive", "Bola de bolos zora"}, 
    Text{"Progressive Diving Scale", "Bulle progressive",            "Fragmento zora"}, 
    Text{"Scale Upgrade",            "Écaille (progressive)",        "Escama zora (más profundidad)"}}},
  {0x8A, 
    {Text{"Green Fuel",           "Carburant vert",                 "Barra de estámina"}, 
    Text{"Progressive Magic Oil", "Huile magique progressive",      "Barra de maná"}, 
    Text{"Magic Upgrade",         "Capacité magique (progressive)", "Barra de energía mágica"}}},
  {0x8B, 
    {Text{"Duck Flute",         "Flûte à canard",         "Flauta del Tiempo"}, 
    Text{"Progressive Memento", "Clarinette progressive", "Ocarani del Tiempo"}, 
    Text{"Ocarina Upgrade",     "Ocarina (progressif)",   "Mejora de la ocarina"}}},
  {0x0F, 
    {Text{"Empty fishbowl", "Bocal de verre", "Cantina transparente"}, 
    Text{"Glass Bottle",    "Bouteille",      "Frasco vacío"}, 
    Text{"Bottle",          "Flacon",         "Botella"}}},
  {0x14, 
    {Text{"Bottle with Cooking Cream", "Flacon de crème à cuisson", "Botella de jugo Lon Lon"}, 
    Text{"Bottle with Cow Milk",       "Flacon de lait de vache",   "Botella de leche de vaca"}, 
    Text{"Bottle of Milk",             "Lait en flacon",            "Leche"}}},
  {0x8C, 
    {Text{"Bottle with 2nd Potion",  "Flacon de 2e potion",    "Botella con sangre de Ganon"}, 
    Text{"Bottle with Red Medicine", "Flacon d’élixir rouge",  "Botella de medicina roja"}, 
    Text{"Bottle of Red Potion",     "Potion rouge en flacon", "Poción roja"}}},
  {0x8D, 
    {Text{"Bottle with Vegetable Juice", "Flacon de jus de légumes", "Botella de jugo vegetal"}, 
    Text{"Bottle with Green Medicine",   "Flacon d’élixir vert",     "Botella de medicina verde"}, 
    Text{"Bottle of Green Potion",       "Potion verte en flacon",   "Poción verde"}}},
  {0x8E, 
    {Text{"Bottle with Water",        "Flacon d’eau",           "Botella de agua fresca"}, 
    Text{"Bottle with Blue Medicine", "Flacon d’élixir bleu",   "Botella de medicina azul"}, 
    Text{"Bottle of Blue Potion",     "Potion bleue en flacon", "Poción azul"}}},
  {0x8F, 
    {Text{"Bottle with Forest Firefly", "Flacon avec une luciole",   "Hada de las rupias"}, 
    Text{"Bottle with Faerie",          "Flacon de poudre féérique", "Botella de la hada"}, 
    Text{"Bottled Fairy",               "Fée en flacon",             "Hada"}}},
  {0x90, 
    {Text{"Bottle with Small Jabu-Jabu", "Flacon de mini Jabu-Jabu", "Mini Jabu-Jabu"}, 
    Text{"Bottle with Tasty Fish",       "Flacon aquarium",          "Botella con un pez"}, 
    Text{"Bottled Fish",                 "Poisson en flacon",        "Pez"}}},
  {0x91, 
    {Text{"Bottle with Will-O-Wisp", "Chauffe-eau portable",   "Botella de fuego zora"}, 
    Text{"Bottle with Blue Flame",   "Lanterne bleue",         "Botella de llamas azules"}, 
    Text{"Bottled Blue Fire",        "Flamme bleue en flacon", "Fuego azul"}}},
  {0x92, 
    {Text{"Bottle with Baby Tektites", "Flacon de bébé Araknon", "Bebés Tektites"}, 
    Text{"Bottle with Beetles",        "Flacon insectarium",     "Botella con skulltulas"}, 
    Text{"Bottled Bugs",               "Insectes en flacon",     "Insectos"}}},
  {0x94, 
    {Text{"Bottle with Sad Ghoul", "Flacon de souvenirs", "Botella con un fantasma"}, 
    Text{"Bottle with Ghost",      "Urne d’Esprit",       "Botella con poe"}, 
    Text{"Bottled Poe",            "Esprit en flacon",    "Gran Poe"}}},
  {0x15, 
    {Text{"Bottle with Letter to Mama", "Lettre pour maman en flacon", "Mensaje naufragado"}, 
    Text{"Bottle with Note",            "Flacon avec une envelope",    "Nota de Ruto"}, 
    Text{"Bottled Ruto's Letter",       "Lettre de Ruto en flacon",    "Carta de Ruto embotellada"}}},
  {0x93, 
    {Text{"Bottle with Smelly Ghost", "Flacon avec chose puante", "Botella con espectro apesotoso"}, 
    Text{"Bottle with Big Ghost",     "Urne d’Âme",               "Botella con gran poe"}, 
    Text{"Bottled Big Poe",           "Âme en flacon",            "Poe"}}},
  {0xC1, 
    {Text{"Zelda's Best Hits", "Réveille-matin de Zelda", "Temazo de Zelda"}, 
    Text{"Zelda's Song",       "Chant de Zelda",          "Canción de Zelda"}, 
    Text{"Nocturne of Shadow", "Nocturne de l’ombre",     "Nocturno de la sombra"}}},
  {0xC2, 
    {Text{"Song of Cows",     "Chant des vaches",    "Aullido de las vacas"}, 
    Text{"Epona's Ballad",    "Ballade d’Épona",     "Nana de Epona"}, 
    Text{"Requiem of Spirit", "Requiem des esprits", "Réquiem del espíritu"}}},
  {0xC3, 
    {Text{"Saria's Remix Album", "Album medley de Saria", "Remezclas del Bosque Perdido"}, 
    Text{"Saria's Fugue",        "Fugue de Saria",        "Salsa de Saria"}, 
    Text{"Minuet of Forest",     "Menuet de la forêt",    "Minueto del bosque"}}},
  {0xC4, 
    {Text{"Salute the Sun's Song", "Chant des oreilles",    "Himno al Sol"}, 
    Text{"Sun's Chimes",           "Matines du soleil",     "Elegía al Sol"}, 
    Text{"Prelude of Light",       "Prélude de la lumière", "Preludio de la luz"}}},
  {0xC5, 
    {Text{"Song of Passing Time", "Chant des horloges", "Canción del despertar"}, 
    Text{"Canon of Time",         "Canons du temps",    "Canon del Tiempo"}, 
    Text{"Serenade of Water",     "Sérénade de l’eau",  "Serenata del agua"}}},
  {0xC6, 
    {Text{"Song of Happy Frogs", "Chant des crapauds",  "Croar de las ranas"}, 
    Text{"Sonata of Storms",     "Sonate des tempêtes", "Serenata de la Tormenta"}, 
    Text{"Bolero of Fire",       "Boléro du feu",       "Bolero del fuego"}}},
  {0xBB, 
    {Text{"Saria's Karaoke",     "Karaoke de Saria",       "Karaoke de Saria"}, 
    Text{"Minuet of the Meadow", "Menuet de la clairière", "Cuarteto del Bosque"}, 
    Text{"Saria's Song",         "Chant de Saria",         "Canción de Saria"}}},
  {0xBC, 
    {Text{"Darunia's Tango",     "Tango de Darunia",   "Cumbiá de Darunia"}, 
    Text{"Bolero of the Crater", "Boléro du cratère",  "Coro del Fuego"}, 
    Text{"Epona's Song",         "Chant des tempêtes", "Canción de Epona"}}},
  {0xBD, 
    {Text{"Ruto's Blues",        "Blues de Ruto",   "Vals de Ruto"}, 
    Text{"Serenade of the Lake", "Sérénade du lac", "Sonata del Agua"}, 
    Text{"Song of Storms",       "Chant du temps",  "Canción de la tormenta"}}},
  {0xBE, 
    {Text{"Nabooru's Reggae",       "Reggae de Nabooru",  "Reggae de Nabooru"}, 
    Text{"Requiem of the Colossus", "Requiem du colosse", "Réquiem del Coloso"}, 
    Text{"Epona's Song",            "Chant d’Épona",      "Canción de Epona"}}},
  {0xBF, 
    {Text{"Impa's Death Metal",       "Death métal d’Impa",    "Death Metal de Impa"}, 
    Text{"Nocturme of the Graveyard", "Nocturne du cimetière", "Diurno de la Sombra"}, 
    Text{"Zelda's Lullaby",           "Berceuse de Zelda",     "Nana de Zelda"}}},
  {0xC0, 
    {Text{"Rauru's Sing-Along", "Chansonette de Rauru", "Balada de Rauru"}, 
    Text{"Prelude of Time",     "Prélude du temps",     "Predulio de la Luz"}, 
    Text{"Sun's Song",          "Chant du soleil",      "Canción del Sol"}}},
  {0xCB, 
    {Text{"Farore's Brooch",    "Bijou de Farore",      "Gema de Farore"}, 
    Text{"Deku Tree's Emerald", "Émeraude Mojo",        "Esmeralda del Gran Árbol Deku"}, 
    Text{"Kokiri's Emerald",    "Émeraude des Kokiris", "Esmeralda Kokiri"}}},
  {0xCC, 
    {Text{"Din's Candied Rock", "Bonbon de Din",    "Gema de Din"}, 
    Text{"Gerudo's Ruby",       "Rubis Gerudo",     "Rubí de los Dodongos"}, 
    Text{"Goron's Ruby",        "Rubis des Gorons", "Rubí Goron"}}},
  {0xCD, 
    {Text{"Nayru's Mood Ring", "Épingle de Nayru", "Gema de Nayru"}, 
    Text{"Zola's Sapphire",    "Saphir Zola",      "Zafiro de Ruto"}, 
    Text{"Zora's Sapphire",    "Saphir des Zoras", "Zafiro Zora"}}},
  {0xCE, 
    {Text{"Bombos",             "Bombos",             "Medallón del Temblor"}, 
    Text{"Saria's Medallion",   "Médaillon de Saria", "Medallón de Saria"}, 
    Text{"Medallion of Forest", "Médaillon de forêt", "Medallon del Bosque"}}},
  {0xCF, 
    {Text{"Fire Emblem",        "La Fire Emblem",       "Emblema de Fuego"}, 
    Text{"Darunia's Medallion", "Médaillon de Darunia", "Medallón de Darunia"}, 
    Text{"Medallion of Fire",   "Médaillon de feu",     "Medallon del Fuego"}}},
  {0xD0, 
    {Text{"Water Gym Badge",   "Badge du gym d’eau", "Medalla de Gimnasio Tipo Agua"}, 
    Text{"Ruto's Medallion",   "Médaillon de Ruto",  "Medallón de Ruto"}, 
    Text{"Medallion of Water", "Médaillon d’eau",    "Medallon del Agua"}}},
  {0xD1, 
    {Text{"Gerudo Doubloon",    "Doublon Gerudo",       "Doblón Gerudo"}, 
    Text{"Nabooru's Medallion", "Médaillon de Nabooru", "Medallón de Nabooru"}, 
    Text{"Medallion of Spirit", "Médaillon d’esprit",   "Medallon del Espíritu"}}},
  {0xD2, 
    {Text{"Hyrule Purple Coin", "Pièce mauve d’Hyrule", "Moneda morada del Galaxy"}, 
    Text{"Impa's Medallion",    "Médaillon d’Impa",     "Medallón de Impa"}, 
    Text{"Medallion of Shadow", "Médaillon d’ombre",    "Medallon de la Sombra"}}},
  {0xD3, 
    {Text{"Coins (50)",        "Pièces (50)",          "Dogecoin"}, 
    Text{"Rauru's Medallion",  "Médaillon de Rauru",   "Medallón de Rauru"}, 
    Text{"Medallion of Light", "Médaillon de lumière", "Medallon de la Luz"}}},
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
