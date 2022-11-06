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

static std::array<std::array<Text, 3>, 0xD5> trickNameTable; //Table of trick names for ice traps
bool initTrickNames = false; //Indicates if trick ice trap names have been initialized yet

//Set vanilla shop item locations before potentially shuffling
void PlaceVanillaShopItems() {
  //Loop to place vanilla items in each location
  for (size_t i = 0; i < ShopLocationLists.size(); i++) {
    for (size_t j = 0; j < ShopLocationLists[i].size(); j++) {
      Location(ShopLocationLists[i][j])->PlaceVanillaItem();
    }
  }
}

//These are the vanilla shop items, but in a priority order of importance
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

//Initialize the table of trick names with an easy, medium, and hard name for each language
void InitTrickNames() {
  trickNameTable[GI_SWORD_KOKIRI] = {
     Text{"Korok Sword", "Épée Korok", "Espada Korok", "Spada dei Korogu", "Deutsch"},
     Text{"Hero's Sword", "Épée du héros", "Espada del héroe", "Spada dell'eroe", "Deutsch"},
     Text{"Razor Sword", "Lame rasoir", "Espada de esmeril", "Fendipiuma", "Deutsch"}};
  trickNameTable[GI_SWORD_MASTER] = {
     Text{"Goddess Sword", "Épée de la déesse", "Espada Divina", "Spada della dea", "Deutsch"},
     Text{"Gilded Sword", "Excalibur", "Espada de los Sabios", "Spada aurea", "Deutsch"},
     Text{"Magical Sword", "Lame dorée", "Fay", "Spada magica", "Deutsch"}};
  trickNameTable[GI_SWORD_KNIFE] = {
     Text{"Big Goron's Sword", "Épée de gros Goron", "Espada de Big Goron", "Coltello di Grande Goron", "Deutsch"},
     Text{"Fierce Deity's Sword", "Épée du dieu démon", "Espada de la Fiera Deidad", "Spada della furia divina", "Deutsch"},
     Text{"Biggoron's Knife", "Lame de Grogoron", "Daga de Biggoron", "Spada del Grande Goron", "Deutsch"}};
  trickNameTable[GI_SWORD_BGS] = {
     Text{"Big Goron's Sword", "Épée de gros Goron", "Espada de Big Goron", "Coltello di Grande Goron", "Deutsch"},
     Text{"Fierce Deity's Sword", "Épée du dieu démon", "Espada de la Fiera Deidad", "Spada della furia divina", "Deutsch"},
     Text{"Biggoron's Knife", "Lame de Grogoron", "Daga de Biggoron", "Spada del Grande Goron", "Deutsch"}};
  trickNameTable[GI_SHIELD_DEKU] = {
     Text{"Boko Shield", "Bouclier Boko", "Escudo Boko", "Scudo boblin", "Deutsch"},
     Text{"Ordon Shield", "Bouclier de Toal", "Escudo de Ordon", "Scudo di Tauro", "Deutsch"},
     Text{"Wooden Shield", "Bouclier de bois", "Escudo de madera", "Scudo di legno", "Deutsch"}};
  trickNameTable[GI_SHIELD_HYLIAN] = {
     Text{"Hyrule Shield", "Bouclier d'Hyrule", "Escudo Hylian", "Scudo Hyrule", "Deutsch"},
     Text{"Goddess Shield", "Bouclier sacré", "Escudo Divino", "Scudo della dea", "Deutsch"},
     Text{"Hero's Shield", "Bouclier du héros", "Escudo del héroe", "Scudo dell'eroe", "Deutsch"}};
  trickNameTable[GI_SHIELD_MIRROR] = {
     Text{"Magic Mirror", "Miroir magique", "Escudo mágico", "Specchio magico", "Deutsch"},
     Text{"Magical Shield", "Bouclier magique", "Escudo arcano", "Scudo magico", "Deutsch"},
     Text{"Mirror of Twilight", "Miroir des ombres", "Espejo del Crepúsculo", "Specchio oscuro", "Deutsch"}};
  trickNameTable[GI_TUNIC_GORON] = {
     Text{"Gerudo Tunic", "Tunique Gerudo", "Sayo gerudo", "Veste dei Gerudo", "Deutsch"},
     Text{"Magic Armor", "Armure magique", "Túnica Goron", "Armatura magica", "Deutsch"},
     Text{"Red Mail", "Habits rouges", "Ropas rojas", "Tunica rossa", "Deutsch"}};
  trickNameTable[GI_TUNIC_ZORA] = {
     Text{"Rito Tunic", "Tunique Rito", "Sayo rito", "Veste dei Rito", "Deutsch"},
     Text{"Zora Armor", "Armure Zora", "Túnica Zora", "Armatura Zora", "Deutsch"},
     Text{"Blue Mail", "Habits bleus", "Ropas azules", "Tunica blu", "Deutsch"}};
  trickNameTable[GI_BOOTS_IRON] = {
     Text{"Iron Hoofs", "Patins de plomb", "Botas férreas", "Stivali di fermio", "Deutsch"},
     Text{"Snow Boots", "Bottes de neige", "Botas de nieve", "Stivali da neve", "Deutsch"},
     Text{"Boots of Power", "Bottes de puissance", "Botas de plomo", "Stivali di piombo", "Deutsch"}};
  trickNameTable[GI_BOOTS_HOVER] = {
     Text{"Hover Hoofs", "Patins des airs", "Botas flotadoras", "Stivali volanti", "Deutsch"},
     Text{"Pegasus Boots", "Bottes pégase", "Botas de Pegaso", "Calzari di Pegaso", "Deutsch"},
     Text{"Boots of Speed", "Bottes de vitesse", "Botas del desierto", "Stivali placcati", "Deutsch"}};
  trickNameTable[GI_WEIRD_EGG] = {
     Text{"Poached Egg", "Œuf à la coque", "Huevo pasado", "Uovo sodo", "Deutsch"},
     Text{"Lon Lon Egg", "Œuf Lon Lon", "Huevo Lon Lon", "Uovo Lon Lon", "Deutsch"},
     Text{"Zora Egg", "Œuf Zora", "Huevo Zora", "Uovo di Zora", "Deutsch"}};
  trickNameTable[GI_LETTER_ZELDA] = {
     Text{"Ruto's Letter", "Lettre de Ruto", "Carta de Ruto", "Lettera di Ruto", "Deutsch"},
     Text{"Royal Letter", "Lettre royale", "Carta para Kafei", "Lettera della principessa", "Deutsch"},
     Text{"Zelda's Business Card", "Carte d'affaires de Zelda", "Carta", "Biglietto da visita di Zelda", "Deutsch"}};
  trickNameTable[GI_BOOMERANG] = {
     Text{"Prank Fetch Toy", "Inséparable bâtonnet", "Bumerang", "Giocattolo da riporto", "Deutsch"},
     Text{"Gale Boomerang", "Boomerang tornade", "Bumerán tornado", "Boomerang ciclone", "Deutsch"},
     Text{"Magic Boomerang", "Boomerang magique", "Bumerán mágico", "Boomerang magico", "Deutsch"}};
  trickNameTable[GI_LENS] = {
     Text{"Sheikah-leidoscope", "Sheikah-léidoscope", "Monóculo de la Verdad", "Sheikah-leidoscopio", "Deutsch"},
     Text{"Sheikah Sensor", "Sonar Sheikah", "Sensor Sheikah", "Sensore Sheikah", "Deutsch"},
     Text{"Magnifying Lens", "Loupe", "Lente Aumentadora", "Lente di ingrandimento", "Deutsch"}};
  trickNameTable[GI_HAMMER] = {
     Text{"Goron Gavel", "Masse perforatrice", "Mazo Goron", "Mazza Goron", "Deutsch"},
     Text{"Magic Hammer", "Marteau magique", "Martillo mágico", "Martello Magico", "Deutsch"},
     Text{"Skull Hammer", "Maillet ressort", "Martillo de hierro", "Martello", "Deutsch"}};
  trickNameTable[GI_STONE_OF_AGONY] = {
     Text{"Shard of Agahnim", "Fragment d'agonie", "Piedra de Agahnim", "Diapason", "Deutsch"},
     Text{"Stone of Agony", "Fragment de cristal", "Fragmento de la Agonía", "Cristallo dell'agonia", "Deutsch"},
     Text{"Pirate's Charm", "Pierre de souffrance", "Amuleto Pirata", "Amuleto Pirata", "Deutsch"}};
  trickNameTable[GI_DINS_FIRE] = {
     Text{"Eldin's Fire", "Feu d'Eldin", "Fuego de Eldin", "Fuoco di Oldin", "Deutsch"},
     Text{"Din's Blaze", "Flamme de Din", "Poder de Din", "Fiamma di Din", "Deutsch"},
     Text{"Din's Pearl", "Perle de Din", "Orbe de Din", "Perla di Din", "Deutsch"}};
  trickNameTable[GI_FARORES_WIND] = {
     Text{"Faron's Wind", "Vent de Firone", "Viento de Farone", "Vento di Firone", "Deutsch"},
     Text{"Farore's Windfall", "Zéphyr de Farore", "Valor de Farore", "Polly Molly", "Deutsch"},
     Text{"Farore's Pearl", "Perle de Farore", "Orbe de Farore", "Perla di Farore", "Deutsch"}};
  trickNameTable[GI_NAYRUS_LOVE] = {
     Text{"Lanayru's Love", "Amour de Lanelle", "Amor de Lanayru", "Amore di Ranel", "Deutsch"},
     Text{"Nayru's Passion", "Passion de Nayru", "Sabiduría de Nayru", "Passione di Nayru", "Deutsch"},
     Text{"Nayru's Pearl", "Perle de Nayru", "Orbe de Nayru", "Perla di Nayru", "Deutsch"}};
  trickNameTable[GI_ARROW_FIRE] = {
     Text{"Soul Arrow", "Flèche des esprits", "Flecha del Espíritu", "Freccia dello spirito", "Deutsch"},
     Text{"Bomb Arrow", "Flèche-bombe", "Flecha bomba", "Freccia bomba", "Deutsch"},
     Text{"Fire Candy", "Bonbon de feu", "Cetro de fuego", "Fragola di fuoco", "Deutsch"}};
  trickNameTable[GI_ARROW_ICE] = {
     Text{"Shadow Arrow", "Flèche d'ombre", "Flecha de las Sombras", "Freccia dell'ombra", "Deutsch"},
     Text{"Ancient Arrow", "Flèche archéonique", "Flecha ancestral", "Freccia ancestrale", "Deutsch"},
     Text{"Ice Trap Arrow", "Flèche de piège de glace", "Cetro de hielo", "Frecciata di ghiaccio", "Deutsch"}};
  trickNameTable[GI_ARROW_LIGHT] = {
     Text{"Wind Arrow", "Flèche de vent", "Flecha del Viento", "Freccia del vento", "Deutsch"},
     Text{"Shock Arrow", "Flèches électriques", "Flecha eléctrica", "Freccia elettrica", "Deutsch"},
     Text{"Silver Arrow", "Flèches d'argent", "Flecha de plata", "Freccia d'argento", "Deutsch"}};
  trickNameTable[GI_GERUDO_CARD] = {
     Text{"Desert Title Deed", "Abonnement Gerudo", "Escritura del desierto", "Proprietà nel deserto", "Deutsch"},
     Text{"Gerudo's Card", "Carte Goron", "Tóken Gerudo", "Goron Card", "Deutsch"},
     Text{"Gerudo's Membership Card", "Autographe de Nabooru", "Tarjeta Gerudo", "Gerudo Pass", "Deutsch"}};

  trickNameTable[0xC9] = {
     Text{"Funky Bean Pack", "Paquet de fèves magiques", "Lote de frijoles mágicos", "Pacco di legumi magici", "Deutsch"},
     Text{"Crenel Bean Pack", "Paquet de haricots Gonggle", "Lote de alubias mágicas", "Pacco di fagioli borlotti", "Deutsch"},
     Text{"Mystic Bean Pack", "Paquet de haricots mystiques", "Lote de porotos mágicos", "Pacco di fagioli mistici", "Deutsch"}};
  trickNameTable[0xB8] = {
     Text{"Diamond Hearts", "Cœurs de diamant", "Contenedor de diamante", "Asso di cuori", "Deutsch"},
     Text{"Double Damage", "Double souffrance", "Doble daño receptivo", "Doppio danno", "Deutsch"},
     Text{"Quadruple Defence", "Quadruple défence", "Defensa cuádruple", "Quadrupla Difesa", "Deutsch"}};

  trickNameTable[GI_POCKET_EGG] = {
     Text{"Poached Egg", "Œuf à la coque", "Huevo pasado", "Uovo sodo", "Deutsch"},
     Text{"Lon Lon Egg", "Œuf Lon Lon", "Huevo Lon Lon", "Uovo Lon Lon", "Deutsch"},
     Text{"Zora Egg", "Œuf Zora", "Huevo del Pez Viento", "Uovo di Zora", "Deutsch"}};
  trickNameTable[GI_POCKET_CUCCO] = {
     Text{"D.I.Y. Alarm Clock", "Réveille-matin improvisé", "Alarma emplumada portátil", "Sveglia fai da te", "Deutsch"},
     Text{"Kakariko Cucco", "Cocotte Cocorico", "Cuco de Kakariko", "Coccò di Calbarico", "Deutsch"},
     Text{"Hatched Cucco", "Cocotte éclose", "Pollo de bolsillo", "Pollo tascabile", "Deutsch"}};
  trickNameTable[GI_COJIRO] = {
     Text{"Blucco", "Chair-Qui-Poule", "Cucazul", "Coccoblù", "Deutsch"},
     Text{"Grog's Cucco", "Cocotte de Grog", "Cuco de Grog", "Coccò di Grog", "Deutsch"},
     Text{"Corijo", "Cojiro", "Corijo", "Cojiro", "Deutsch"}};
  trickNameTable[GI_ODD_MUSHROOM] = {
     Text{"Magic Mushroom", "Champignon magique", "Champiñón mágico", "Fungo magico", "Deutsch"},
     Text{"Endura Shroom", "Champi Vigueur", "Champiñón del bosque", "Gagliardello", "Deutsch"},
     Text{"Mushroom", "Champignon", "Seta", "Fungo", "Deutsch"}};
  trickNameTable[GI_ODD_POTION] = {
     Text{"Odd Medicine", "Élixir suspect", "Poción rara", "Poltiglia strana", "Deutsch"},
     Text{"Granny's Poultice", "Mixture de Granny", "Medicina de la abuela", "Medicina della nonna", "Deutsch"},
     Text{"Mushroom Poultice", "Mixture de champignon", "Medicina de champiñones", "Medicina di funghi", "Deutsch"}};
  trickNameTable[GI_SAW] = {
     Text{"Carpenter's Saw", "Scie du charpentier", "Sierra del carpintero", "Sega del carpentiere", "Deutsch"},
     Text{"Poacher's Sword", "Hache du chasseur", "Espada del capataz", "Spada del bracconiere", "Deutsch"},
     Text{"Grog's Saw", "Scie de Grog", "Sierra del Cazador Furtivo", "Sega di Grog", "Deutsch"}};
  trickNameTable[GI_SWORD_BROKEN] = {
     Text{"Broken Biggoron's Sword", "Épée brisée de Grogoron", "Espada de Biggoron rota", "Spada rotta di Grande Goron", "Deutsch"},
     Text{"Broken Giant's Knife", "Lame des géants brisée", "Daga gigante rota", "Spada del gigante (rotta)", "Deutsch"},
     Text{"Biggoron's Sword", "Épée de Grogoron", "Espada de Biggoron", "Spada di Grande Goron", "Deutsch"}};
  trickNameTable[GI_PERSCRIPTION] = {
     Text{"Biggoron's Prescription", "Ordonnance de Grogoron", "Receta de Biggoron", "Ricetta per Grande Goron", "Deutsch"},
     Text{"Eyedrop Prescription", "Ordonnance de gouttes", "Receta ocular", "Ricetta per collirio", "Deutsch"},
     Text{"Urgent Prescription", "Ordonnance urgente", "Prescripción", "Ricetta medica", "Deutsch"}};
  trickNameTable[GI_FROG] = {
     Text{"Don Gero", "Don Gero", "Don Gero", "Don Gero", "Deutsch"},
     Text{"Eyedrop Frog", "Grenouille-qui-louche", "Globo Ocular de Rana", "Rana oculare", "Deutsch"},
     Text{"Frog", "Crapaud", "Rana", "Rana", "Deutsch"}};
  trickNameTable[GI_EYEDROPS] = {
     Text{"Biggoron's Eyedrops", "Gouttes de Grogoron", "Gotas de Biggoron", "Collirio di Grande Goron", "Deutsch"},
     Text{"Hyrule's Finest Eyedrops", "Eau du lac Hylia", "Gotas oculares", "Miglior collirio di Hyrule", "Deutsch"},
     Text{"Zora Perfume", "Parfum Zora", "Perfume Zora", "Profumo Zora", "Deutsch"}};
  trickNameTable[GI_CLAIM_CHECK] = {
     Text{"Clay Check", "Certificat Grogoron", "Comprobante de Reclamación", "Buonissimo", "Deutsch"},
     Text{"Sheikah Slate", "Tablette Sheikah", "Piedra Sheikah", "Tavoletta Sheikah", "Deutsch"},
     Text{"Cyclone Slate", "Ardoise des tornades", "Pizarra de los Torbellinos", "Lavagna di Gorgo", "Deutsch"}};

  trickNameTable[GI_SKULL_TOKEN] = {
     Text{"Skulltula Token", "Bon de Skulltula dorée", "Símbolo de Skulltula", "Simbolo di Aracnula d'oro", "Deutsch"},
     Text{"Golden Skulltula Spirit", "Pièce de Skulltula dorée", "Tóken de Skulltula Dorada", "Teschio maledetto", "Deutsch"},
     Text{"Gold Walltula Token", "Jeton de Walltula dorée", "Skulltula dorada", "Cranio d'oro", "Deutsch"}};

  trickNameTable[0x80] = {
     Text{"Progressive Grappling Hook", "Lance-chaîne (prog.)", "Garra progresiva", "Rampino progressivo", "Deutsch"},
     Text{"Progressive Clawshot", "Grappin-griffe (prog.)", "Zarpa progresiva", "Artiglio progressivo", "Deutsch"},
     Text{"Progressive Gripshot", "Grappince (prog.)", "Enganchador progresivo", "Gancio progressivo", "Deutsch"}};
  trickNameTable[0x81] = {
     Text{"Progressive Glove", "Gant de puissance (prog.)", "Guanteletes progresivos", "Guanti di forza progressivi", "Deutsch"},
     Text{"Progressive Power Bracelet", "Bracelet de force (prog.)", "Brasaletes progresivos", "Superbracciale progressivo", "Deutsch"},
     Text{"Progressive Magic Bracelet", "Bracelet magique (prog.)", "Manoplas progresivas", "Bracciale di forza progressivo", "Deutsch"}};
  trickNameTable[0x82] = {
     Text{"Progressive Bomb Capacity", "Capacité de bombes (prog.)", "Mayor capacidad de bombas", "Borsa di bombe progressiva", "Deutsch"},
     Text{"Progressive Bomb Pack", "Paquet de bombes (prog.)", "Zurrón de bombas progresivo", "Portaboom progressivo", "Deutsch"},
     Text{"Progressive Bomb Box", "Boîte à bombes (prog.)", "Bolsa de bombas progresiva", "Sacco di bombe progressivo", "Deutsch"}};
  trickNameTable[0x83] = {
     Text{"Progressive Arrow Capacity", "Capacité de flèches (prog.)", "Mayor capacidad de flechas", "Faretra progressiva", "Deutsch"},
     Text{"Progressive Hero's Bow", "Arc du héros (prog.)", "Arco del héroe progresivo", "Arco dell'eroe progressivo", "Deutsch"},
     Text{"Progressive Arrow Holder", "Arbalète (prog.)", "Ballesta progresiva", "Balestra progressiva", "Deutsch"}};
  trickNameTable[0x84] = {
     Text{"Progressive Seed Capacity", "Capacité de graines (prog.)", "Mayor capacidad de semillas", "Portasemi progressivo", "Deutsch"},
     Text{"Progressive Scattershot", "Lance-pierre rafale (prog.)", "Resortera múltiple progresiva", "Fionda multiprogressiva", "Deutsch"},
     Text{"Progressive Seed Satchel", "Sac de graines (prog.)", "Bolsa de semillas progresiva", "Sacco dei semi progressivo", "Deutsch"}};
  trickNameTable[0x85] = {
     Text{"Progressive Rupee Capacity", "Capacité de rubis (prog.)", "Mayor capacidad de rupias", "Espansione per rupie progressiva", "Deutsch"},
     Text{"Progressive Purse", "Sacoche (prog.)", "Cartera de rupias progresiva", "Portamonete progressivo", "Deutsch"},
     Text{"Progressive Rupee Bag", "Sac à rubis (prog.)", "Zurrón de rupias progresivo", "Sacco di rupie progressivo", "Deutsch"}};
  trickNameTable[0x86] = {
     Text{"Progressive Diving Ability", "Plongée (prog.)", "Buceo progresivo", "Capacità di immersione progressiva", "Deutsch"},
     Text{"Progressive Pearl", "Perle (prog.)", "Perla progresiva", "Perla progressiva", "Deutsch"},
     Text{"Progressive Scute", "Bulle (prog.)", "Fragmento Zora progresivo", "Bolla progressiva", "Deutsch"}};
  trickNameTable[0x87] = {
     Text{"Progressive Nut Pack", "Paquet de noix (prog.)", "Mayor capacidad de semillas", "Espansione per semi Deku progressiva", "Deutsch"},
     Text{"Progressive Nut Bag", "Sac de noix (prog.)", "Bolsa de nueces progresiva", "Portanoci Deku progressivo", "Deutsch"},
     Text{"Progressive Husk Capacity", "Capacité de noisettes (prog.)", "Mayor capacidad de castañas", "Espansione per bombe Deku progressiva", "Deutsch"}};
  trickNameTable[0x88] = {
     Text{"Progressive Stick Pack", "Paquet de bâtons Mojo (prog.)", "Mayor capacidad de bastones", "Espansione per bastoni Deku progressiva", "Deutsch"},
     Text{"Progressive Stick Bag", "Sac de bâtons (prog.)", "Mayor capacidad de ramas deku", "Portarami Deku progressivo", "Deutsch"},
     Text{"Progressive Rod Capacity", "Capacité de tiges (prog.)", "Mayor capacidad de cetros deku", "Espansione per gambi Deku progressiva", "Deutsch"}};
  trickNameTable[0x89] = {
     Text{"Progressive Bomblings", "Bombinsectes (prog.)", "Bombinsectos progresivos", "Bomboli progressivi", "Deutsch"},
     Text{"Progressive Missiles", "Missiles (prog.)", "Misiles progresivos", "Bombchu progressivi", "Deutsch"},
     Text{"Progressive Bombchu Bag", "Sac à Bombchu (prog.)", "Bombachus progresivos", "Portaradiomine progressivo", "Deutsch"}};
  trickNameTable[0x8A] = {
     Text{"Progressive Stamina Meter", "Jauge d'endurance (prog.)", "Medidor de vigor progresivo", "Barra del vigore progressiva", "Deutsch"},
     Text{"Progressive Energy Meter", "Jauge d'énergie (prog.)", "Medidor de energía progresivo", "Barra dell'energia progressiva", "Deutsch"},
     Text{"Progressive Magic Powder", "Poudre magique (prog.)", "Medidor de carga progresivo", "Giara magica progressiva", "Deutsch"}};
  trickNameTable[0x8B] = {
     Text{"Progressive Memento", "Souvenir (prog.)", "Silbato progresivo", "Ocherella progressiva", "Deutsch"},
     Text{"Progressive Flute", "Flûte (prog.)", "Flauta progresiva", "Flauto progressivo", "Deutsch"},
     Text{"Progressive Recorder", "Harmonica (prog.)", "Armónica progresiva", "Piffero progressivo", "Deutsch"}};
  trickNameTable[0xD4] = {
     Text{"Progressive Titan Blade", "Lame des Titans (prog.)", "Hoja del Titán progresiva", "Lama dei Titani progressiva", "Deutsch"},
     Text{"Progressive Goron Knife", "Lame Goron (prog.)", "Daga Goron progresiva", "Coltello Goron progressivo", "Deutsch"},
     Text{"Progressive Giant Sword", "Épée géante (prog.)", "Espada gigante progresiva", "Spada gigante progressiva", "Deutsch"}};

  trickNameTable[0x0F] = {
     Text{"Magic Bottle", "Flacon magique", "Frasco feérico", "Ampolla per fate", "Deutsch"},
     Text{"Glass Bottle", "Flacon de verre", "Botella de cristal", "Ampolla di vetro", "Deutsch"},
     Text{"Bottle with Water", "Flacon d'eau", "Botella Tingle", "Aria in bottiglia", "Deutsch"}};
  trickNameTable[0x14] = {
     Text{"Bottle with Chateau Romani", "Flacon de cuvée Romani", "Botella de Reserva Romani", "Ampolla di Gran Riserva Romanì", "Deutsch"},
     Text{"Bottle with Fresh Milk", "Flacon de lait frais", "Botella de leche fresca", "Ampolla di latte fresco", "Deutsch"},
     Text{"Bottle with Mystery Milk", "Flacon de lait grand cru", "Botella de leche extra", "Ampolla di latte strano", "Deutsch"}};
  trickNameTable[0x8C] = {
     Text{"Bottle with Red Chu Jelly", "Flacon de gelée Chuchu rouge", "Jugo de Chuchu Rojo", "Ampolla di gelatina ChuChu rossa", "Deutsch"},
     Text{"Bottle with Medicine of Life", "Flacon d'élixir rouge", "Botella de medicina de la vida", "Ampolla di pozione rossa", "Deutsch"},
     Text{"Bottle with Heart Potion", "Flacon de potion de soin", "Botella de poción de salud", "Ampolla di pozione Scaldacuore", "Deutsch"}};
  trickNameTable[0x8D] = {
     Text{"Bottle with Green Chu Jelly", "Flacon de gelée Chuchu verte", "Jugo de Chuchu Verde", "Ampolla di gelatina ChuChu verde", "Deutsch"},
     Text{"Bottle with Medicine of Magic", "Flacon d'élixir vert", "Botella de medicina mágica", "Ampolla di pozione verde", "Deutsch"},
     Text{"Bottle with Stamina Potion", "Flacon d'Endurol", "Botella de elixir vigorizante", "Ampolla di pozione Levafatica", "Deutsch"}};
  trickNameTable[0x8E] = {
     Text{"Bottle with Blue Chu Jelly", "Flacon de gelée Chuchu bleue", "Jugo de Chuchu Azul", "Ampolla di gelatina ChuChu blu", "Deutsch"},
     Text{"Bottle with Water of Life", "Flacon d'élixir bleu", "Botella de agua de la vida", "Ampolla di pozione blu", "Deutsch"},
     Text{"Bottle with Air Potion", "Flacon de potion d'oxygène", "Botella de oxígeno", "Ampolla di Ossigeno Liquido", "Deutsch"}};
  trickNameTable[0x8F] = {
     Text{"Bottle with Forest Firefly", "Flacon avec une luciole", "Luciérnaga del bosque", "Lucciola dei Boschi in un'ampolla", "Deutsch"},
     Text{"Bottle with Faerie", "Flacon de poudre féérique", "Gran Hada embotellada", "Fatina in un'ampolla", "Deutsch"},
     Text{"Bottle with Stray Fairy", "Flacon avec une fée perdue", "Hada perdida en una botella", "Fata sperduta in un'ampolla", "Deutsch"}};
  trickNameTable[0x90] = {
     Text{"Bottle with Small Jabu-Jabu", "Flacon avec mini Jabu-Jabu", "Lord Chapu-Chapu embotellado", "Chapu Chapu in un'ampolla", "Deutsch"},
     Text{"Bottle with Hyrule Bass", "Flacon avec perche d'Hyrule", "Locha de Hyrule embotellada", "Aspio Hyrule in un'ampolla", "Deutsch"},
     Text{"Bottle with Hyrule Loach", "Flacon avec loche d'Hyrule", "Perca de Términa embotellada", "Luccio Hylia in un'ampolla", "Deutsch"}};
  trickNameTable[0x91] = {
     Text{"Bottle with Will-O-Wisp", "Flacon avec feu follet", "Botella de llama azul", "Fuoco fatuo in un'ampolla", "Deutsch"},
     Text{"Bottle with Ancient Flame", "Flacon de flamme ancienne", "Botella de fuego ancestral", "Ampolla di fuoco ancestrale", "Deutsch"},
     Text{"Bottle with Nayru's Flame", "Flacon de flamme de Nayru", "Botella de llamas de Nayru", "Fiamma di Nayru in un'ampolla", "Deutsch"}};
  trickNameTable[0x92] = {
     Text{"Bottle with Baby Tektites", "Flacon de bébé Araknon", "Tektites en una botella", "Cuccioli di Tektite in un'ampolla", "Deutsch"},
     Text{"Bottle with Lanayru Ants", "Flacon de fourmis de Lanelle", "Celestarabajo embotellado", "Sabbiormiche in un'ampolla", "Deutsch"},
     Text{"Bottle with Insects", "Flacon de bibittes", "Saltabosques embotellados", "Artropodi in un'ampolla", "Deutsch"}};
  trickNameTable[0x94] = {
     Text{"Bottle with Ghini", "Flacon avec Ghini", "Ghini en una botella", "Ghini in un'ampolla", "Deutsch"},
     Text{"Bottle with Imp Poe", "Flacon avec Spectre", "Espectro en una botella", "Anima di spettro in un'ampolla", "Deutsch"},
     Text{"Bottle with Anti-Fairy", "Flacon avec Tetdoss", "Whisp en una botella", "Anti-fata in un'ampolla", "Deutsch"}};

  trickNameTable[0x15] = {
     Text{"Bottle with Maggie's Letter", "Flacon avec lettre de Maggy", "Carta de Dolores", "Lettera di Maggy in un'ampolla", "Deutsch"},
     Text{"Bottle with Letter to Kafei", "Flacon avec lettre pour Kafei", "Carta para Kafei", "Lettera per Kafei in un'ampolla", "Deutsch"},
     Text{"Bottle with Zelda's Letter", "Flacon avec lettre de Zelda", "Carta náutica", "Messaggio in bottiglia", "Deutsch"}};
  trickNameTable[0x93] = {
     Text{"Bottle with Composer Brother", "Flacon avec un compositeur", "Hermana Poe embotellada", "Mortaldi in un'ampolla", "Deutsch"},
     Text{"Bottle with Jalhalla", "Flacon avec Jalhalla", "Yaihalla embotellado", "Jay-Harla in un'ampolla", "Deutsch"},
     Text{"Bottle with Grim Repoe", "Flacon avec le Faucheur", "Bubble en una botella", "Cupoo mietitore in un'ampolla", "Deutsch"}};

  trickNameTable[0xC1] = {
     Text{"Ballad of the Goddess", "Chant de la déesse", "Cántico de la Diosa", "Melodia della Dea", "Deutsch"},
     Text{"Song of Healing", "Chant de l'apaisement", "Canción de curación", "Melodia del ristoro", "Deutsch"},
     Text{"Bolero of Fire", "Boléro du feu", "Bolero del fuego", "Bolero del fuoco", "Deutsch"}};
  trickNameTable[0xC2] = {
     Text{"Earth God's Lyric", "Hymne du dieu de la terre", "Melodía del Espíritu de la Tierra", "Inno della Terra", "Deutsch"},
     Text{"Song of Soaring", "Chant de l'envol", "Canción del viento", "Melodia del volo", "Deutsch"},
     Text{"Requiem of Spirit", "Requiem des esprits", "Réquiem del espíritu", "Requiem dello spirito", "Deutsch"}};
  trickNameTable[0xC3] = {
     Text{"Wind God's Aria", "Hymne du dieu du vent", "Melodía del Espíritu del Viento", "Inno del Vento", "Deutsch"},
     Text{"Wind's Requiem", "Mélodie du vent", "Melodía del Viento", "Canzone del Vento", "Deutsch"},
     Text{"Minuet of Forest", "Menuet de la forêt", "Minueto del bosque", "Minuetto della foresta", "Deutsch"}};
  trickNameTable[0xC4] = {
     Text{"Song of Passing", "Mambo de Manbo", "Melodía del transcurrir", "Sonata in Dì Notturno", "Deutsch"},
     Text{"Command Melody", "Air du marionnettiste", "Cara al Sol", "Canto del Burattino", "Deutsch"},
     Text{"Prelude of Light", "Prélude de la lumière", "Preludio de la luz", "Preludio della luce", "Deutsch"}};
  trickNameTable[0xC5] = {
     Text{"Song of Double Time", "Chant accéléré", "Canción del doble tiempo", "Canzone del tempo accelerato", "Deutsch"},
     Text{"Inverted Song of Time", "Chant du temps inversé", "Canción del tiempo invertida", "Canzone del tempo rallentato", "Deutsch"},
     Text{"Serenade of Water", "Sérénade de l'eau", "Serenata del agua", "Serenata dell'acqua", "Deutsch"}};
  trickNameTable[0xC6] = {
     Text{"Ballad of Gales", "Requiem de la tornade", "Melodía del Tornado", "Melodia del Tifone", "Deutsch"},
     Text{"Frog's Song of Soul", "Rap des grenouilles", "Canción del alma de la rana", "Soul della rana", "Deutsch"},
     Text{"Nocturne of Shadow", "Nocturne de l'ombre", "Nocturno de la sombra", "Notturno delle ombre", "Deutsch"}};
  trickNameTable[0xBB] = {
     Text{"Saria's Karaoke", "Karaoké de Saria", "Dueto del bosque", "Minuetto della fortuna", "Deutsch"},
     Text{"Sonata of Awakening", "Sonate de l'éveil", "Sonata del despertar", "Sonata del risveglio", "Deutsch"},
     Text{"Saria's Song", "Chant de Saria", "Canción de Saria", "Canzone di Saria", "Deutsch"}};
  trickNameTable[0xBC] = {
     Text{"Darunia's Tango", "Tango de Darunia", "Coro del fuego", "Bolero del fosco", "Deutsch"},
     Text{"Goron Lullaby", "Berceuse des Gorons", "Nana goron", "Ninna nanna Goron", "Deutsch"},
     Text{"Zelda's Lullaby", "Berceuse de Zelda", "Nana de Zelda", "Ninna nanna di Zelda", "Deutsch"}};
  trickNameTable[0xBD] = {
     Text{"Ruto's Blues", "Blues de Ruto", "Sonata del agua", "Serenata dell'aceto", "Deutsch"},
     Text{"New Wave Bossa Nova", "Bossa-nova des flots", "Bossanova de las olas", "Bossa nova marina", "Deutsch"},
     Text{"Song of Time", "Chant du temps", "Canción del tiempo", "Canzone del tempo", "Deutsch"}};
  trickNameTable[0xBE] = {
     Text{"Nabooru's Reggae", "Reggae de Nabooru", "Reggae del espíritu", "Requiem dello spiritoso", "Deutsch"},
     Text{"Elegy of Emptiness", "Hymne du vide", "Elegía al vacío", "Elegia delle statue", "Deutsch"},
     Text{"Epona's Song", "Chant d'Épona", "Canción de Epona", "Canzone di Epona", "Deutsch"}};
  trickNameTable[0xBF] = {
     Text{"Impa's Death Metal", "Death métal d'Impa", "Diurno de la sombra", "Notturno delle orbe", "Deutsch"},
     Text{"Oath to Order", "Ode de l'appel", "Oda al orden", "Ode alla promessa", "Deutsch"},
     Text{"Song of Storms", "Chant des tempêtes", "Canción de la tormenta", "Canzone della tempesta", "Deutsch"}};
  trickNameTable[0xC0] = {
     Text{"Rauru's Sing-Along", "Chansonnette de Rauru", "Predulio de luz", "Preludio della lode", "Deutsch"},
     Text{"Ballad of the Wind Fish", "Ballade sur Poisson-Rêve", "Balada del Piez Viento", "Ballata del Pesce Vento", "Deutsch"},
     Text{"Sun's Song", "Chant du soleil", "Canción del Sol", "Canto del sole", "Deutsch"}};

  trickNameTable[0xCB] = {
     Text{"Pendant of Courage", "Pendentif du courage", "Colgante del valor", "Amuleto del coraggio", "Deutsch"},
     Text{"Farore's Emerald", "Émeraude de Farore", "Esmeralda de Farore", "Smeraldo di Farore", "Deutsch"},
     Text{"Kokiri's Peridot", "Péridot Kokiri", "Ágata de los Kokiri", "Olivina dei Kokiri", "Deutsch"}};
  trickNameTable[0xCC] = {
     Text{"Pendant of Power", "Pendentif de la force", "Colgante del poder", "Amuleto della forza", "Deutsch"},
     Text{"Din's Ruby", "Rubis de Din", "Rubí de Din", "Rubino di Din", "Deutsch"},
     Text{"Goron's Garnet", "Grenat Goron", "Topacio de los Goron", "Granato dei Goron", "Deutsch"}};
  trickNameTable[0xCD] = {
     Text{"Pendant of Wisdom", "Pendentif de la sagesse", "Colgante de la sabiduría", "Amuleto della saggezza", "Deutsch"},
     Text{"Nayru's Sapphire", "Saphir de Nayru", "Zafiro de Nayru", "Zaffiro di Nayru", "Deutsch"},
     Text{"Zora's Aquamarine", "Aquamarine Zora", "Lapislázuli de los Zora", "Acquamarina degli Zora", "Deutsch"}};
  trickNameTable[0xCE] = {
     Text{"Wind Medallion", "Médaillon du vent", "Medallón del Viento", "Medaglione del Vento", "Deutsch"},
     Text{"Saria's Medallion", "Médaillon de Saria", "Medallón de Saria", "Medaglione di Saria", "Deutsch"},
     Text{"Medallion of Forest", "Médaillon du temple de la forêt", "Medalla del Bosque", "Medaglione Forestale", "Deutsch"}};
  trickNameTable[0xCF] = {
     Text{"Bombos Medallion", "Médaillon des flammes", "Medallón del Temblor", "Medaglione Fiamma", "Deutsch"},
     Text{"Darunia's Medallion", "Médaillon de Darunia", "Medallón de Darunia", "Medaglione di Darunia", "Deutsch"},
     Text{"Medallion of Fire", "Médaillon du temple du feu", "Medalla del Fuego", "Medaglione Focoso", "Deutsch"}};
  trickNameTable[0xD0] = {
     Text{"Ice Medallion", "Médaillon de glace", "Medallón Helado", "Medaglione del Ghiaccio", "Deutsch"},
     Text{"Ruto's Medallion", "Médaillon de Ruto", "Medallón de Ruto", "Medaglione di Ruto", "Deutsch"},
     Text{"Medallion of Water", "Médaillon du temple de l'eau", "Medalla del Agua", "Medaglione Acquoso", "Deutsch"}};
  trickNameTable[0xD1] = {
     Text{"Quake Medallion", "Médaillon des secousses", "Medallón Llamarada", "Medaglione Sisma", "Deutsch"},
     Text{"Nabooru's Medallion", "Médaillon de Nabooru", "Medallón de Nabooru", "Medaglione di Naburu", "Deutsch"},
     Text{"Medallion of Spirit", "Médaillon du temple de l'esprit", "Medalla del Espíritu", "Medaglione Spiritoso", "Deutsch"}};
  trickNameTable[0xD2] = {
     Text{"Travel Medallion", "Amulette de téléportation", "Medallón Maligno", "Amuleto del teletrasporto", "Deutsch"},
     Text{"Impa's Medallion", "Médaillon d'Impa", "Medallón de Impa", "Medaglione di Impa", "Deutsch"},
     Text{"Medallion of Shadow", "Médaillon du temple de l'ombre", "Medalla de la Sombra", "Medaglione Oscuro", "Deutsch"}};
  trickNameTable[0xD3] = {
     Text{"Ether Medallion", "Médaillon d'éther", "Medallón de Tesoro", "Medaglione Etere", "Deutsch"},
     Text{"Rauru's Medallion", "Médaillon de Rauru", "Medallón de Rauru", "Medaglione di Rauru", "Deutsch"},
     Text{"Medallion of Light", "Médaillon du temple de lumière", "Medalla de la Luz", "Medaglione Lucente", "Deutsch"}};

  trickNameTable[GI_HEART] = {
     Text{"Love", "Bisou", "Te amo", "Amore", "Deutsch"},
     Text{"Heart Container", "Réceptacle de cœur", "Contenedor de corazón", "Portacuori", "Deutsch"},
     Text{"Piece of Heart", "Quart de cœur", "Pieza de corazón", "Frammento di cuore", "Deutsch"}};
  trickNameTable[GI_RUPEE_GREEN] = {
     Text{"Green Rupy", "Rupee vert", "Rubia verde", "Bugia verde", "Deutsch"},
     Text{"One Rupee", "Un rubis", "Guaraní hyliano", "Una rupia", "Deutsch"},
     Text{"Rupee (1)", "Rubis (1)", "Peso hyliano", "Rupia (1)", "Deutsch"}};
  trickNameTable[GI_RUPEE_BLUE] = {
     Text{"Blue Rupy", "Rupee bleu", "Rubia azul", "Bugia blu", "Deutsch"},
     Text{"Five Rupees", "Cinq rubis", "Bolívar hyliano", "Cinque rupie", "Deutsch"},
     Text{"Rupee (5)", "Rubis (5)", "Peso hyliano", "Rupie (5)", "Deutsch"}};
  trickNameTable[GI_RUPEE_RED] = {
     Text{"Red Rupy", "Rupee rouge", "Rubia roja", "Bugia rossa", "Deutsch"},
     Text{"Twenty Rupees", "Vingt rubis", "Colon hyliano", "Venti rupie", "Deutsch"},
     Text{"Rupee (20)", "Rubis (20)", "Peso hyliano", "Rupie (20)", "Deutsch"}};
  trickNameTable[GI_RUPEE_PURPLE] = {
     Text{"Purple Rupy", "Rupee pourpre", "Rubia morada", "Bugia viola", "Deutsch"},
     Text{"Fifty Rupees", "Cinquante rubis", "Balboa hyliano", "Cinquanta rupie", "Deutsch"},
     Text{"Rupee (50)", "Rubis (50)", "Peso hyliano", "Rupie (50)", "Deutsch"}};
  trickNameTable[GI_RUPEE_GOLD] = {
     Text{"Huge Rupy", "Énorme Rupee", "Rubia gigante", "Bugia gigante", "Deutsch"},
     Text{"Two Hundred Rupees", "Deux cent rubis", "Euro hyliano", "Duecento rupie", "Deutsch"},
     Text{"Rupee (200)", "Rubis (200)", "Dólar hyliano", "Rupie (200)", "Deutsch"}};
  trickNameTable[GI_HEART_PIECE] = {
     Text{"Piece of Health", "Quart d'énergie", "Pieza de amor", "Frammento di portacuori", "Deutsch"},
     Text{"Recovery Heart", "Cœur d'énergie", "Corazón", "Cuore", "Deutsch"},
     Text{"Heart Container", "Réceptacle de cœur", "Contenedor de corazón", "Portacuori", "Deutsch"}};
  trickNameTable[GI_HEART_CONTAINER_2] = {
     Text{"Health Container", "Réceptacle d'énergie", "Contenedor de amor", "Portacure", "Deutsch"},
     Text{"Recovery Heart", "Quart de cœur", "Corazón", "Cuore", "Deutsch"},
     Text{"Piece of Heart", "Cœur d'énergie", "Pieza de corazón", "Frammento di cuore", "Deutsch"}};

/*
  //Names for individual upgrades, in case progressive names are replaced
  trickNameTable[GI_HOOKSHOT] = {
     Text{"Grappling Hook", "Grappin-griffe", "Gancho lanzable"},
     Text{"Clawshot", "Lance-chaîne", "Zarpa"},
     Text{"Gripshot", "Grappince", "Enganchador"}};
  trickNameTable[GI_LONGSHOT] = {
	 Text{"Longshot, no strings attached", "Grappin sans attrape", "Gancho lanzable más largo"},
     Text{"Double Clawshot", "Double-grappin", "Superzarpa"},
     Text{"Switch Hook", "Great grappin", "Gancho chulo"}};
  trickNameTable[GI_BOMB_BAG_1] = {
	 Text{"Bomb Capacity (20)", "Capacité de bombes (20)", "Bolsa de bombas (contiene 20)"},
     Text{"Bronze Bomb Bag", "Sac de bombes de bronze", "Saco de bronce de bombas"},
     Text{"Small Bomb Bag", "Petit sac de bombes", "Zurrón de bombas pequeño"}};
  trickNameTable[GI_BOMB_BAG_2] = {
	 Text{"Bomb Capacity (30)", "Capacité de bombes (30)", "Bolsa de bombas (contiene 30)"},
     Text{"Silver Bomb Bag", "Sac de bombes d'argent", "Saco plateado de bombas"},
     Text{"Medium Bomb Bag", "Sac de bombes moyen", "Zurrón de bombas mediano"}};
  trickNameTable[GI_BOMB_BAG_3] = {
	 Text{"Bomb Capacity (40)", "Capacité de bombes (40)", "Bolsa de bombas (contiene 40)"},
     Text{"Golden Bomb Bag", "Sac de bombes d'or", "Saco dorado de bombas"},
     Text{"Large Bomb Bag", "Gros sac de bombes", "Zurrón de bombas grande"}};
  trickNameTable[GI_BOW_1] = {
	 Text{"Bow", "Arc", "Arco del Hada"},
     Text{"Hero's Bow", "Arc du héros", "Arco del héroe"},
     Text{"Small Quiver", "Petit carquois", "Saco de flechas pequeño"}};
  trickNameTable[GI_BOW_2] = {
	 Text{"Arrow Capacity (40)", "Capacité de flèches (40)", "Capacidad de flechas (40)"},
     Text{"Silver Quiver", "Carquois d'argent", "Carcaj plateado"},
     Text{"Medium Quiver", "Carquois moyen", "Saco de flechas mediano"}};
  trickNameTable[GI_BOW_3] = {
	 Text{"Arrow Capacity (50)", "Capacité de flèches (50)", "Capacidad de flechas (50)"},
     Text{"Golden Quiver", "Carquois d'or", "Carcaj dorado"},
     Text{"Large Quiver", "Gros carquois", "Saco de flechas grande"}};
  trickNameTable[GI_SLINGSHOT_1] = {
	 Text{"Slingshot", "Lance-pierre", "Tirachinas del Hada"},
     Text{"Scattershot", "Lance-pierre rafale", "Tirachinas múltiple"},
     Text{"Small Seed Satchel", "Petit sac de graines", "Bolsa de semillas pequeña"}};
  trickNameTable[GI_SLINGSHOT_2] = {
	 Text{"Deku Seed Capacity (40)", "Capacité de graines (40)", "Capacidad de semillas (40)"},
     Text{"Silver Deku Seed Bullet Bag", "Sac de graines d'argent", "Bolsa de balas (contiene 40)"},
     Text{"Medium Seed Satchel", "Sac de graines moyen", "Bolsa de semillas mediana"}};
  trickNameTable[GI_SLINGSHOT_3] = {
	 Text{"Deku Seed Capacity (50)", "Capacité de graines (50)", "Capacidad de semillas (50)"},
     Text{"Golden Deku Seed Bullet Bag", "Sac de graines d'or", "Bolsa de balas (contiene 50)"},
     Text{"Large Seed Satchel", "Gros sac de graines", "Bolsa de semillas grande"}};
  trickNameTable[GI_STRENGTH_1] = {
	 Text{"Goron's Gauntlet", "Gantelet Goron", "Brazalete amarillo"},
     Text{"Power Bracelet", "Bracelet de force", "Brazalete de fuerza"},
     Text{"Magic Bracelet", "Bracelet de Lavio", "Brazalete de Ravio"}};
  trickNameTable[GI_STRENGTH_2] = {
	 Text{"Silver Bracelets", "Bracelets d'argent", "Guantes Moguma"},
     Text{"Power Gloves", "Gant de puissance", "Guante del Poder"},
     Text{"Magic Gauntlets", "Gantelet magique", "Guante mágico"}};
  trickNameTable[GI_STRENGTH_3] = {
	 Text{"Golden Bracelets", "Bracelets d'or", "Guantelete de Thanos"},
     Text{"Titan's Mitts", "Moufle de titan", "Guantes de Titán"},
     Text{"Magnetic Gloves", "Magnéto-gants", "Guantes de fuego"}};
  trickNameTable[GI_SCALE_1] = {
	 Text{"Silver Pearl", "Perle d'argent", "Perla de Plata progresiva"},
     Text{"Adult Scale", "Écaille d'adulte", "Bola de bolos zora"},
     Text{"Zora Scale", "Écaille Zora", "Escama de Zora"}};
  trickNameTable[GI_SCALE_2] = {
	 Text{"Golden Pearl", "Perle d'or", "Perla de Oro progresiva"},
     Text{"Giant Scale", "Écaille de géant", "Escama de Faren"},
     Text{"Water Dragon Scale", "Écaille du dragon de l'eau", "Escama de dragón acuático"}};
  trickNameTable[GI_WALLET_1] = {
	 Text{"Rupee Capacity (200)", "Capacité de rubis (200)", "Capacidad de rupias (200)"},
     Text{"Silver Wallet", "Bourse d'argent", "Cartera de rupias de adulto"},
     Text{"Medium Wallet", "Bourse moyenne", "Zurrón de rupias mediano"}};
  trickNameTable[GI_WALLET_2] = {
	 Text{"Rupee Capacity (500)", "Capacité de rubis (500)", "Capacidad de rupias (500)"},
     Text{"Golden Wallet", "Bourse d'or", "Cartera de rupias gigante"},
     Text{"Large Wallet", "Grosse bourse", "Zurrón de rupias grande"}};
  trickNameTable[GI_WALLET_3] = {
	 Text{"Rupee Capacity (999)", "Capacité de rubis (999)", "Capacidad de rupias (999)"},
     Text{"Golden Wallet", "Bourse d'or", "Cartera de ricachón"},
     Text{"Large Wallet", "Grosse bourse", "Zurrón de rupias gigante"}};
  trickNameTable[GI_DEKU_NUT_UPGRADE_1] = {
	 Text{"Deku Bomb Capacity (30)", "Capacité de bombes Mojo (30)", "Capacidad de semillas deku (40)"},
     Text{"Baba Nut Capacity (30)", "Capacité de noix Baba (30)", "Capacidad de nueces baba (40)"},
     Text{"Deku Nut Pack (30)", "Paquet de noix Mojo (30)", "Capacidad de nueces mojo (40)"}};
  trickNameTable[GI_DEKU_NUT_UPGRADE_2] = {
	 Text{"Deku Bomb Capacity (40)", "Capacité de bombes Mojo (40)", "Capacidad de semillas deku (50)"},
     Text{"Baba Nut Capacity (40)", "Capacité de noix Baba (40)", "Capacidad de nueces baba (50)"},
     Text{"Deku Nut Pack (40)", "Paquet de noix Mojo (40)", "Capacidad de nueces mojo (50)"}};
  trickNameTable[GI_DEKU_STICK_UPGRADE_1] = {
	 Text{"Deku Rod Capacity (20)", "Capacité de tiges Mojo (20)", "Capacidad de palos mojo (20)"},
     Text{"Boko Stick Capacity (20)", "Capacité de bâtons Boko (20)", "Capacidad de palos boko (20)"},
     Text{"Deku Stick Pack (20)", "Paquet de bâtons Mojo (20)", "Capacidad de bastones deku (20)"}};
  trickNameTable[GI_DEKU_STICK_UPGRADE_2] = {
	 Text{"Deku Rod Capacity (30)", "Capacité de tiges Mojo (30)", "Capacidad de palos mojo (30)"},
     Text{"Boko Stick Capacity (30)", "Capacité de bâtons Boko (30)", "Capacidad de palos boko (30)"},
     Text{"Deku Stick Pack (30)", "Paquet de bâtons Mojo (30)", "Capacidad de bastones deku (30)"}};
  trickNameTable[GI_MAGIC_1] = {
	 Text{"Stamina Meter", "Jauge d'endurance", "Medidor de vigor"},
     Text{"Energy Meter", "Jauge d'énergie", "Medidor de energía"},
     Text{"Magic Powder", "Poudre magique", "Medidor de carga"}};
  trickNameTable[GI_MAGIC_2] = {
	 Text{"Enhanced Stamina Meter", "Jauge d'endurance améliorée", "Medidor de vigor mejorado"},
     Text{"Enhanced Energy Meter", "Jauge d'énergie améliorée", "Medidor de energía mejorado"},
     Text{"Enhanced Magic Powder", "Poudre magique améliorée", "Medidor de carga mejorado"}};
  trickNameTable[GI_OCARINA_1] = {
	 Text{"Ocarina", "Ocarina", "Ocarina"},
     Text{"Saria's Ocarina", "Ocarina de Saria", "Ocarina de Saria"},
     Text{"Wood Ocarina", "Ocarina de bois", "Ocarina del Hada"}};
  trickNameTable[GI_OCARINA_2] = {
	 Text{"Flute", "Flûte", "Flauta"},
     Text{"Zelda's Ocarina", "Ocarina de Zelda", "Ocarina de Zelda"},
     Text{"Ocarina of Winds", "Ocarina des vents", "Ocarina del Viento"}};
  trickNameTable[GI_CUCCO] = {
	 Text{"D.I.Y. Alarm Clock", "Réveille-matin improvisé", "Alarma emplumada"},
     Text{"Kakariko Cucco", "Cocotte Cocorico", "Cuco de Kakariko"},
     Text{"Hatched Cucco", "Cocotte éclose", "Pollo"}};
  trickNameTable[GI_MASK_KEATON] = {
	 Text{"Kee... Something Mask", "Masque de Quiche", "Máscara Kealgo"},
     Text{"Kitsune Mask", "Masque de Kitsune", "Máscara Kitsune"},
     Text{"Kafei's Mask", "Masque de Kafei", "Máscara de Kafei"}};
  trickNameTable[GI_MASK_SKULL] = {
	 Text{"Skull Kid's Mask", "Masque de Skull Kid", "Máscara de Skull Kid"},
     Text{"Stalfos Mask", "Masque de squelette", "Máscara de Stalfos"},
     Text{"Captain's Hat", "Heaume du capitaine", "Casco del capitán"}};
  trickNameTable[GI_MASK_SPOOKY] = {
	 Text{"Skrik Mask", "Masque Skrik", "Máscara Escalofriante"},
     Text{"ReDead Mask", "Masque de Remort", "Máscara de ReDead"},
     Text{"Gibdo Mask", "Masque de Gibdo", "Careta de Gibdo"}};
  trickNameTable[GI_MASK_BUNNY] = {
	 Text{"Peppy Mask", "Masque de Peppy", "Capucha de Pascua"},
     Text{"Bunny Ears", "Oreilles de lapin", "Orejas de conejo"},
     Text{"Postman's Hat", "Casquette du facteur", "Gorra de cartero"}};
  trickNameTable[GI_MASK_GORON] = {
	 Text{"Goro Mask", "Masque Goro", "Máscara Goro"},
     Text{"Mask of Goron", "Masque des Gorons", "Máscara de los Goron"},
     Text{"Darunia Mask", "Masque de Darunia", "Máscara de Darmani"}};
  trickNameTable[GI_MASK_ZORA] = {
	 Text{"Zola Mask", "Masque Zola", "Máscara Zola"},
     Text{"Mask of Zora", "Masque des Zoras", "Máscara de los Zora"},
     Text{"Ruto Mask", "Masque de Ruto", "Máscara de Mikau"}};
  trickNameTable[GI_MASK_GERUDO] = {
	 Text{"Ganguro Mask", "Masque de Ganguro", "Máscara Canguro"},
     Text{"Mask of Gerudo", "Masque des Gerudos", "Máscara de las Gerudo"},
     Text{"Nabooru Mask", "Masque de Nabooru", "Máscara de Nabooru"}};
  trickNameTable[GI_MASK_TRUTH] = {
	 Text{"Sheikah Mask", "Masque Sheikah", "Máscara Sheikah"},
     Text{"Mask of Gossip", "Masque de potins", "Máscara chismosa"},
     Text{"Eye of Truth", "Œil de vérité", "Ojo de la Verdad"}};*/
}

//Generate a fake name for the ice trap based on the item it's displayed as
Text GetIceTrapName(u8 id) {
  //If the trick names table has not been initialized, do so
  if (!initTrickNames) {
    InitTrickNames();
    initTrickNames = true;
  }
  //Randomly get the easy, medium, or hard name for the given item id
  return RandomElement(trickNameTable[id]);
}

//Get shop index based on a given location
static std::map<std::string_view, int> ShopNameToNum = {{"KF Shop", 0},   {"Kak Potion Shop", 1}, {"MK Bombchu Shop", 2}, {"MK Potion Shop", 3},
                                                        {"MK Bazaar", 4}, {"Kak Bazaar", 5},      {"ZD Shop", 6},         {"GC Shop", 7}};
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
