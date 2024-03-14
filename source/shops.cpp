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

static std::array<std::array<Text, 3>, 0xD5> trickNameTable; // Table of trick names for ice traps
bool initTrickNames = false; // Indicates if trick ice trap names have been initialized yet

// Set vanilla shop item locations before potentially shuffling
void PlaceVanillaShopItems() {
    // Loop to place vanilla items in each location
    for (size_t i = 0; i < ShopLocationLists.size(); i++) {
        for (size_t j = 0; j < ShopLocationLists[i].size(); j++) {
            Location(ShopLocationLists[i][j])->PlaceVanillaItem();
        }
    }
}

// These are the vanilla shop items, but in a priority order of importance
// However many shop item slots were cleared, this will return 64 minus that number of vanilla shop items to be placed
// with assumed fill The first 32 items here will always be present in shops Shopsanity 4 will only have the first 32,
// shopsanity 1 will have the first 56, etc. Shopsanity random will have anywhere from the first 32 to the first 56, so
// the order of items after 32 is relevant
std::vector<ItemKey> GetMinVanillaShopItems(int total_replaced) {
    std::vector<ItemKey> minShopItems = {
        BUY_DEKU_SHIELD, BUY_HYLIAN_SHIELD, BUY_GORON_TUNIC, BUY_ZORA_TUNIC, BUY_DEKU_NUT_5, BUY_DEKU_NUT_5,
        BUY_DEKU_NUT_10, BUY_DEKU_STICK_1, BUY_DEKU_STICK_1, BUY_DEKU_SEEDS_30, BUY_ARROWS_10, BUY_ARROWS_10,
        BUY_ARROWS_30, BUY_ARROWS_50, BUY_BOMBCHU_5, BUY_BOMBCHU_10, BUY_BOMBCHU_10, BUY_BOMBCHU_20, BUY_BOMBS_525,
        BUY_BOMBS_535, BUY_BOMBS_10, BUY_BOMBS_20, BUY_GREEN_POTION, BUY_RED_POTION_30, BUY_BLUE_FIRE,
        BUY_FAIRYS_SPIRIT, BUY_BOTTLE_BUG, BUY_FISH,
        //^First 28 items from OoTR
        BUY_HYLIAN_SHIELD, BUY_BOTTLE_BUG, BUY_DEKU_STICK_1, BUY_FAIRYS_SPIRIT,
        //^First 32 items: Always guaranteed
        BUY_BLUE_FIRE, BUY_FISH, BUY_BOMBCHU_10, BUY_DEKU_NUT_5, BUY_ARROWS_10, BUY_BOMBCHU_20, BUY_BOMBS_535,
        BUY_RED_POTION_30,
        //^First 40 items: Exist on shopsanity 3 or less
        BUY_BOMBS_30, BUY_BOMBCHU_20, BUY_DEKU_NUT_5, BUY_ARROWS_10, BUY_DEKU_NUT_5, BUY_ARROWS_30, BUY_RED_POTION_40,
        BUY_FISH,
        //^First 48 items: Exist on shopsanity 2 or less
        BUY_BOMBCHU_20, BUY_ARROWS_30, BUY_RED_POTION_50, BUY_ARROWS_30, BUY_DEKU_NUT_5, BUY_ARROWS_50, BUY_ARROWS_50,
        BUY_GREEN_POTION,
        //^First 56 items: Exist on shopsanity 1 or less
        BUY_POE, BUY_POE, BUY_HEART, BUY_HEART, BUY_HEART, BUY_HEART, BUY_HEART, BUY_HEART,
        //^All 64 items: Only exist with shopsanity 0
    };
    // Now delete however many items there are to replace
    for (int i = 0; i < total_replaced; i++) {
        minShopItems.pop_back();
    }
    return minShopItems;
}

// This table contains a cumulative probability for each possible shop price based on
//  a beta distribution with alpha = 1.5, beta = 2, and the result of the distribution, a float in [0.0, 1.0),
//  being mutliplied by 60, casted to an integer, then multiplied by 5 to give a value in range [0, 295] in increments
//  of 5. Meaning the first value is the probability of 0, the next value is the probability of 0 plus the probability
//  of 5, etc.
// Probabilities generated using a python script with 1 billion trials, so should hopefully be pretty good
// Average price ~126
//~38% chance of needing no wallet, ~45% chance of needing 1, ~17% chance of needing 2
static constexpr std::array<double, 60> ShopPriceProbability = {
    0.005326994, 0.014908518, 0.027114719, 0.041315285, 0.057136304, 0.074325887, 0.092667151, 0.112002061, 0.132198214,
    0.153125390, 0.174696150, 0.196810540, 0.219388148, 0.242361379, 0.265657012, 0.289205134, 0.312970402, 0.336877590,
    0.360881110, 0.384932772, 0.408976198, 0.432982176, 0.456902494, 0.480686053, 0.504313389, 0.527746488, 0.550938554,
    0.573856910, 0.596465330, 0.618736235, 0.640646600, 0.662162782, 0.683240432, 0.703859801, 0.724001242, 0.743631336,
    0.762722631, 0.781259986, 0.799198449, 0.816521905, 0.833208595, 0.849243398, 0.864579161, 0.879211177, 0.893112051,
    0.906263928, 0.918639420, 0.930222611, 0.940985829, 0.950914731, 0.959992180, 0.968187000, 0.975495390, 0.981884488,
    0.987344345, 0.991851853, 0.995389113, 0.997937921, 0.999481947, 1.000000000,
};
int GetRandomShopPrice() {
    double random = RandomDouble(); // Randomly generated probability value
    for (size_t i = 0; i < ShopPriceProbability.size(); i++) {
        if (random < ShopPriceProbability[i]) {
            // The randomly generated value has surpassed the total probability up to this point, so this is the
            // generated price
            return i * 5; // i in range [0, 59], output in range [0, 295] in increments of 5
        }
    }
    return -1; // Shouldn't happen
}

// Similar to above, beta distribution with alpha = 1, beta = 2,
//  multiplied by 20 instead of 60 to give values in rage [0, 95] in increments of 5
// Average price ~31
static constexpr std::array<double, 20> ScrubPriceProbability = {
    0.097500187, 0.190002748, 0.277509301, 0.360018376, 0.437522571, 0.510021715, 0.577520272,
    0.640029304, 0.697527584, 0.750024535, 0.797518749, 0.840011707, 0.877508776, 0.910010904,
    0.937504342, 0.960004661, 0.977502132, 0.989998967, 0.997500116, 1.000000000,
};
s16 GetRandomScrubPrice() {
    double random = RandomDouble();
    for (size_t i = 0; i < ScrubPriceProbability.size(); i++) {
        if (random < ScrubPriceProbability[i]) {
            return i * 5; // i in range [0, 19], output in range [0, 95] in increments of 5
        }
    }
    return -1;
}

// Get 1 to 4, or a random number from 1-4 depending on shopsanity setting
int GetShopsanityReplaceAmount() {
    if (Settings::Shopsanity.Is(SHOPSANITY_ONE)) {
        return 1;
    } else if (Settings::Shopsanity.Is(SHOPSANITY_TWO)) {
        return 2;
    } else if (Settings::Shopsanity.Is(SHOPSANITY_THREE)) {
        return 3;
    } else if (Settings::Shopsanity.Is(SHOPSANITY_FOUR)) {
        return 4;
    } else { // Random, get number in [1, 4]
        return Random(1, 5);
    }
}

// Initialize the table of trick names with an easy, medium, and hard name for each language
void InitTrickNames() {
    trickNameTable[GI_SWORD_KOKIRI] = {
        Text{ "Korok Sword", "Épée Korok", "Espada Korok", "Spada dei Korogu", "Korok-Schwert" },
        Text{ "Hero's Sword", "Épée du héros", "Espada del héroe", "Spada dell'eroe", "Heroenschwert" },
        Text{ "Razor Sword", "Lame rasoir", "Espada de esmeril", "Fendipiuma", "Elfenschwert" }
    };
    trickNameTable[GI_SWORD_MASTER] = {
        Text{ "Goddess Sword", "Épée de la déesse", "Espada Divina", "Spada della dea", "Schwert der Göttin" },
        Text{ "Gilded Sword", "Excalibur", "Espada de los Sabios", "Spada aurea", "Schmirgelklinge" },
        Text{ "Magical Sword", "Lame dorée", "Fay", "Spada magica", "Magisches Schwert" }
    };
    trickNameTable[GI_SWORD_KNIFE] = { Text{ "Big Goron's Sword", "Épée de gros Goron", "Espada de Big Goron",
                                             "Coltello di Grande Goron", "Bigorgon-Schwert" },
                                       Text{ "Fierce Deity's Sword", "Épée du dieu démon", "Espada de la Fiera Deidad",
                                             "Spada della furia divina", "Schwert der grimmischen Gottheit" },
                                       Text{ "Biggoron's Knife", "Lame de Grogoron", "Daga de Biggoron",
                                             "Spada del Grande Goron", "Biggoron-Messer" } };
    trickNameTable[GI_SWORD_BGS]   = { Text{ "Big Goron's Sword", "Épée de gros Goron", "Espada de Big Goron",
                                           "Coltello di Grande Goron", "Bigorgon-Schwert" },
                                       Text{ "Fierce Deity's Sword", "Épée du dieu démon", "Espada de la Fiera Deidad",
                                           "Spada della furia divina", "Schwert der grimmischen Gottheit" },
                                       Text{ "Biggoron's Knife", "Lame de Grogoron", "Daga de Biggoron",
                                           "Spada del Grande Goron", "Biggoron-Messer" } };
    trickNameTable[GI_SHIELD_DEKU] = {
        Text{ "Boko Shield", "Bouclier Boko", "Escudo Boko", "Scudo boblin", "Bokschild" },
        Text{ "Ordon Shield", "Bouclier de Toal", "Escudo de Ordon", "Scudo di Tauro", "Ordon-Schild" },
        Text{ "Wooden Shield", "Bouclier de bois", "Escudo de madera", "Scudo di legno", "Holzschild" }
    };
    trickNameTable[GI_SHIELD_HYLIAN] = {
        Text{ "Hyrule Shield", "Bouclier d'Hyrule", "Escudo Hylian", "Scudo Hyrule", "Hyrule-Schild" },
        Text{ "Goddess Shield", "Bouclier sacré", "Escudo Divino", "Scudo della dea", "Göttlicher Schild" },
        Text{ "Hero's Shield", "Bouclier du héros", "Escudo del héroe", "Scudo dell'eroe", "Heroenschild" }
    };
    trickNameTable[GI_SHIELD_MIRROR] = {
        Text{ "Magic Mirror", "Miroir magique", "Escudo mágico", "Specchio magico", "Magiespiegel" },
        Text{ "Magical Shield", "Bouclier magique", "Escudo arcano", "Scudo magico", "Magischer Schild" },
        Text{ "Mirror of Twilight", "Miroir des ombres", "Espejo del Crepúsculo", "Specchio oscuro", "Schattenspiegel" }
    };
    trickNameTable[GI_TUNIC_GORON] = {
        Text{ "Gerudo Tunic", "Tunique Gerudo", "Sayo gerudo", "Veste dei Gerudo", "Damengewand" },
        Text{ "Magic Armor", "Armure magique", "Túnica Goron", "Armatura magica", "Magie-Rüstung" },
        Text{ "Red Mail", "Habits rouges", "Ropas rojas", "Tunica rossa", "Rotes Gewand" }
    };
    trickNameTable[GI_TUNIC_ZORA] = {
        Text{ "Rito Tunic", "Tunique Rito", "Sayo rito", "Veste dei Rito", "Orni-Gewand" },
        Text{ "Zora Armor", "Armure Zora", "Túnica Zora", "Armatura Zora", "Zora-Panzer" },
        Text{ "Blue Mail", "Habits bleus", "Ropas azules", "Tunica blu", "Blaues Gewand" }
    };
    trickNameTable[GI_BOOTS_IRON] = {
        Text{ "Iron Hoofs", "Patins de plomb", "Botas férreas", "Stivali di fermio", "Eisenhufe" },
        Text{ "Snow Boots", "Bottes de neige", "Botas de nieve", "Stivali da neve", "Schneestiefel" },
        Text{ "Boots of Power", "Bottes de puissance", "Botas de plomo", "Stivali di piombo", "Stärkestiefel" }
    };
    trickNameTable[GI_BOOTS_HOVER] = {
        Text{ "Hover Hoofs", "Patins des airs", "Botas flotadoras", "Stivali volanti", "Gleithufe" },
        Text{ "Pegasus Boots", "Bottes pégase", "Botas de Pegaso", "Calzari di Pegaso", "Pegasus-Stiefel" },
        Text{ "Boots of Speed", "Bottes de vitesse", "Botas del desierto", "Stivali placcati", "Tempostiefel" }
    };
    trickNameTable[GI_WEIRD_EGG] = { Text{ "Poached Egg", "Œuf à la coque", "Huevo pasado", "Uovo sodo", "Spiegelei" },
                                     Text{ "Lon Lon Egg", "Œuf Lon Lon", "Huevo Lon Lon", "Uovo Lon Lon",
                                           "Lon Lon-Ei" },
                                     Text{ "Zora Egg", "Œuf Zora", "Huevo Zora", "Uovo di Zora", "Zora-Ei" } };
    trickNameTable[GI_LETTER_ZELDA] = {
        Text{ "Ruto's Letter", "Lettre de Ruto", "Carta de Ruto", "Lettera di Ruto", "Rutos Brief" },
        Text{ "Royal Letter", "Lettre royale", "Carta para Kafei", "Lettera della principessa", "Hoheitlicher Brief" },
        Text{ "Zelda's Business Card", "Carte d'affaires de Zelda", "Carta", "Biglietto da visita di Zelda",
              "Zeldas Visitenkarte" }
    };
    trickNameTable[GI_BOOMERANG] = {
        Text{ "Prank Fetch Toy", "Inséparable bâtonnet", "Bumerang", "Giocattolo da riporto", "Boomerang" },
        Text{ "Gale Boomerang", "Boomerang tornade", "Bumerán tornado", "Boomerang ciclone", "Sturmbumerang" },
        Text{ "Magic Boomerang", "Boomerang magique", "Bumerán mágico", "Boomerang magico", "Magie-Bumerang" }
    };
    trickNameTable[GI_LENS] = {
        Text{ "Sheikah-leidoscope", "Sheikah-léidoscope", "Monóculo de la Verdad", "Sheikah-leidoscopio",
              "Shiekah-leidoskop" },
        Text{ "Sheikah Sensor", "Sonar Sheikah", "Sensor Sheikah", "Sensore Sheikah", "Shiekah-Sensor" },
        Text{ "Magnifying Lens", "Loupe", "Lente Aumentadora", "Lente di ingrandimento", "Magische Lupe" }
    };
    trickNameTable[GI_HAMMER] = {
        Text{ "Goron Gavel", "Masse perforatrice", "Mazo Goron", "Mazza Goron", "Goronen-Hammer" },
        Text{ "Magic Hammer", "Marteau magique", "Martillo mágico", "Martello Magico", "Magischer Hammer" },
        Text{ "Skull Hammer", "Maillet ressort", "Martillo de hierro", "Martello", "Schädel-Hammer" }
    };
    trickNameTable[GI_STONE_OF_AGONY] = {
        Text{ "Shard of Agahnim", "Fragment d'agonie", "Piedra de Agahnim", "Diapason", "Splitter des Agahnim" },
        Text{ "Stone of Agony", "Fragment de cristal", "Fragmento de la Agonía", "Cristallo dell'agonia",
              "Stein der Weisen" },
        Text{ "Pirate's Charm", "Pierre de souffrance", "Amuleto Pirata", "Amuleto Pirata", "Links Talisman" }
    };
    trickNameTable[GI_DINS_FIRE] = {
        Text{ "Eldin's Fire", "Feu d'Eldin", "Fuego de Eldin", "Fuoco di Oldin", "Eldins Feuerinferno" },
        Text{ "Din's Blaze", "Flamme de Din", "Poder de Din", "Fiamma di Din", "Dins Flammen" },
        Text{ "Din's Pearl", "Perle de Din", "Orbe de Din", "Perla di Din", "Dins Deamont" }
    };
    trickNameTable[GI_FARORES_WIND] = {
        Text{ "Faron's Wind", "Vent de Firone", "Viento de Farone", "Vento di Firone", "Phirones Donnersturm" },
        Text{ "Farore's Windfall", "Zéphyr de Farore", "Valor de Farore", "Polly Molly", "Farores Wind" },
        Text{ "Farore's Pearl", "Perle de Farore", "Orbe de Farore", "Perla di Farore", "Farores Deamont" }
    };
    trickNameTable[GI_NAYRUS_LOVE] = {
        Text{ "Lanayru's Love", "Amour de Lanelle", "Amor de Lanayru", "Amore di Ranel", "Ranelles Umarmung" },
        Text{ "Nayru's Passion", "Passion de Nayru", "Sabiduría de Nayru", "Passione di Nayru", "Nayrus Hingabe" },
        Text{ "Nayru's Pearl", "Perle de Nayru", "Orbe de Nayru", "Perla di Nayru", "Nayrus Deamont" }
    };
    trickNameTable[GI_ARROW_FIRE] = {
        Text{ "Soul Arrow", "Flèche des esprits", "Flecha del Espíritu", "Freccia dello spirito", "Seelen-Pfeile" },
        Text{ "Bomb Arrow", "Flèche-bombe", "Flecha bomba", "Freccia bomba", "Bomben-Pfeile" },
        Text{ "Fire Candy", "Bonbon de feu", "Cetro de fuego", "Fragola di fuoco", "Feuer-Praline" }
    };
    trickNameTable[GI_ARROW_ICE] = {
        Text{ "Shadow Arrow", "Flèche d'ombre", "Flecha de las Sombras", "Freccia dell'ombra", "Schatten-Pfeile" },
        Text{ "Ancient Arrow", "Flèche archéonique", "Flecha ancestral", "Freccia ancestrale", "Antike Pfeile" },
        Text{ "Ice Trap Arrow", "Flèche de piège de glace", "Cetro de hielo", "Frecciata di ghiaccio",
              "Eisfallen-Pfeile" }
    };
    trickNameTable[GI_ARROW_LIGHT] = {
        Text{ "Wind Arrow", "Flèche de vent", "Flecha del Viento", "Freccia del vento", "Wind-Pfeile" },
        Text{ "Shock Arrow", "Flèches électriques", "Flecha eléctrica", "Freccia elettrica", "Elektro-Pfeile" },
        Text{ "Silver Arrow", "Flèches d'argent", "Flecha de plata", "Freccia d'argento", "Silber-Pfeile" }
    };
    trickNameTable[GI_GERUDO_CARD] = { Text{ "Desert Title Deed", "Abonnement Gerudo", "Escritura del desierto",
                                             "Proprietà nel deserto", "Wüsten-Urkunde" },
                                       Text{ "Gerudo's Card", "Carte Goron", "Tóken Gerudo", "Goron Card",
                                             "Gerudo-Symbol" },
                                       Text{ "Gerudo's Membership Card", "Autographe de Nabooru", "Tarjeta Gerudo",
                                             "Gerudo Pass", "Gerudo-Mitgliedskarte" } };

    trickNameTable[0xC9] = { Text{ "Funky Bean Pack", "Paquet de fèves magiques", "Lote de frijoles mágicos",
                                   "Pacco di legumi magici", "Wunderbohnen-Bündel" },
                             Text{ "Crenel Bean Pack", "Paquet de haricots Gonggle", "Lote de alubias mágicas",
                                   "Pacco di fagioli borlotti", "Supererbsen-Bündel" },
                             Text{ "Mystic Bean Pack", "Paquet de haricots mystiques", "Lote de porotos mágicos",
                                   "Pacco di fagioli mistici", "Magische Bohnen-Bündel" } };
    trickNameTable[0xB8] = {
        Text{ "Diamond Hearts", "Cœurs de diamant", "Contenedor de diamante", "Asso di cuori", "Diamantenherz" },
        Text{ "Double Damage", "Double souffrance", "Doble daño receptivo", "Doppio danno", "Doppelte Angriffskraft" },
        Text{ "Quadruple Defence", "Quadruple défence", "Defensa cuádruple", "Quadrupla Difesa",
              "Vierfache Abwehrkraft" }
    };

    trickNameTable[GI_POCKET_EGG] = {
        Text{ "Poached Egg", "Œuf à la coque", "Huevo pasado", "Uovo sodo", "Spiegelei" },
        Text{ "Lon Lon Egg", "Œuf Lon Lon", "Huevo Lon Lon", "Uovo Lon Lon", "Lon Lon-Ei" },
        Text{ "Zora Egg", "Œuf Zora", "Huevo del Pez Viento", "Uovo di Zora", "Zora-Ei" }
    };
    trickNameTable[GI_POCKET_CUCCO] = {
        Text{ "D.I.Y. Alarm Clock", "Réveille-matin improvisé", "Alarma emplumada portátil", "Sveglia fai da te",
              "Improvisierter Wecker" },
        Text{ "Kakariko Cucco", "Cocotte Cocorico", "Cuco de Kakariko", "Coccò di Calbarico", "Kakariko-Huhn" },
        Text{ "Hatched Cucco", "Cocotte éclose", "Pollo de bolsillo", "Pollo tascabile", "Geschlüpftes Küken" }
    };
    trickNameTable[GI_COJIRO]       = { Text{ "Blucco", "Chair-Qui-Poule", "Cucazul", "Coccoblù", "Blenni" },
                                        Text{ "Grog's Cucco", "Cocotte de Grog", "Cuco de Grog", "Coccò di Grog",
                                        "Grogs Huhn" },
                                        Text{ "Corijo", "Cojiro", "Corijo", "Cojiro", "Cojiro" } };
    trickNameTable[GI_ODD_MUSHROOM] = {
        Text{ "Magic Mushroom", "Champignon magique", "Champiñón mágico", "Fungo magico", "Magischer Pilz" },
        Text{ "Endura Shroom", "Champi Vigueur", "Champiñón del bosque", "Gagliardello", "Fittling" },
        Text{ "Mushroom", "Champignon", "Seta", "Fungo", "Schlummermorchel" }
    };
    trickNameTable[GI_ODD_POTION] = { Text{ "Odd Medicine", "Élixir suspect", "Poción rara", "Poltiglia strana",
                                            "Moderpaket" },
                                      Text{ "Granny's Poultice", "Mixture de Granny", "Medicina de la abuela",
                                            "Medicina della nonna", "Omas Mixtur" },
                                      Text{ "Mushroom Poultice", "Mixture de champignon", "Medicina de champiñones",
                                            "Medicina di funghi", "Pilzumschlag" } };
    trickNameTable[GI_SAW]        = {
               Text{ "Carpenter's Saw", "Scie du charpentier", "Sierra del carpintero", "Sega del carpentiere",
              "Zimmermannssäge" },
               Text{ "Poacher's Sword", "Hache du chasseur", "Espada del capataz", "Spada del bracconiere", "Nervensäge" },
               Text{ "Grog's Saw", "Scie de Grog", "Sierra del Cazador Furtivo", "Sega di Grog", "Grogs Säge" }
    };
    trickNameTable[GI_SWORD_BROKEN] = { Text{ "Broken Biggoron's Sword", "Épée brisée de Grogoron",
                                              "Espada de Biggoron rota", "Spada rotta di Grande Goron",
                                              "Zerbrochenes Biggoron-Schwert" },
                                        Text{ "Broken Giant's Knife", "Lame des géants brisée", "Daga gigante rota",
                                              "Spada del gigante (rotta)", "Zerbrochenes Langschwert" },
                                        Text{ "Biggoron's Sword", "Épée de Grogoron", "Espada de Biggoron",
                                              "Spada di Grande Goron", "Biggoron-Schwert" } };
    trickNameTable[GI_PERSCRIPTION] = { Text{ "Biggoron's Prescription", "Ordonnance de Grogoron", "Receta de Biggoron",
                                              "Ricetta per Grande Goron", "Biggorons Rezept" },
                                        Text{ "Eyedrop Prescription", "Ordonnance de gouttes", "Receta ocular",
                                              "Ricetta per collirio", "Augentropfen-Rezept" },
                                        Text{ "Urgent Prescription", "Ordonnance urgente", "Prescripción",
                                              "Ricetta medica", "Eilmeldung" } };
    trickNameTable[GI_FROG]         = { Text{ "Don Gero", "Don Gero", "Don Gero", "Don Gero", "Don Gero" },
                                        Text{ "Eyedrop Frog", "Grenouille-qui-louche", "Globo Ocular de Rana", "Rana oculare",
                                      "Augentropfen-Frosch" },
                                        Text{ "Frog", "Crapaud", "Rana", "Rana", "Frosch" } };
    trickNameTable[GI_EYEDROPS]     = { Text{ "Biggoron's Eyedrops", "Gouttes de Grogoron", "Gotas de Biggoron",
                                          "Collirio di Grande Goron", "Biggorons Augentropfen" },
                                        Text{ "Hyrule's Finest Eyedrops", "Eau du lac Hylia", "Gotas oculares",
                                          "Miglior collirio di Hyrule", "Hyrules beste Augentropfen" },
                                        Text{ "Zora Perfume", "Parfum Zora", "Perfume Zora", "Profumo Zora",
                                          "Zora-Parfüm" } };
    trickNameTable[GI_CLAIM_CHECK]  = {
         Text{ "Clay Check", "Certificat Grogoron", "Comprobante de Reclamación", "Buonissimo", "Berg-Urkunde" },
         Text{ "Sheikah Slate", "Tablette Sheikah", "Piedra Sheikah", "Tavoletta Sheikah", "Shiekah-Stein" },
         Text{ "Cyclone Slate", "Ardoise des tornades", "Pizarra de los Torbellinos", "Lavagna di Gorgo",
              "Froschkompass" }
    };

    trickNameTable[GI_SKULL_TOKEN] = { Text{ "Skulltula Token", "Bon de Skulltula dorée", "Símbolo de Skulltula",
                                             "Simbolo di Aracnula d'oro", "Skulltula-Beweis" },
                                       Text{ "Golden Skulltula Spirit", "Pièce de Skulltula dorée",
                                             "Tóken de Skulltula Dorada", "Teschio maledetto", "Skulltula-Seele" },
                                       Text{ "Gold Walltula Token", "Jeton de Walltula dorée", "Skulltula dorada",
                                             "Cranio d'oro", "Walltula-Symbol" } };

    trickNameTable[0x80] = { Text{ "Progressive Grappling Hook", "Lance-chaîne (prog.)", "Garra progresiva",
                                   "Rampino progressivo", "Enterhaken Aufwertung" },
                             Text{ "Progressive Clawshot", "Grappin-griffe (prog.)", "Zarpa progresiva",
                                   "Artiglio progressivo", "Greifhaken Aufwertung" },
                             Text{ "Progressive Gripshot", "Grappince (prog.)", "Enganchador progresivo",
                                   "Gancio progressivo", "Tauschhaken Aufwertung" } };
    trickNameTable[0x81] = { Text{ "Progressive Glove", "Gant de puissance (prog.)", "Guanteletes progresivos",
                                   "Guanti di forza progressivi", "Handschuh Aufwertung" },
                             Text{ "Progressive Power Bracelet", "Bracelet de force (prog.)", "Brasaletes progresivos",
                                   "Superbracciale progressivo", "Kraftarmband Aufwertung" },
                             Text{ "Progressive Magic Bracelet", "Bracelet magique (prog.)", "Manoplas progresivas",
                                   "Bracciale di forza progressivo", "Magiearmband Aufwertung" } };
    trickNameTable[0x82] = { Text{ "Progressive Bomb Capacity", "Capacité de bombes (prog.)",
                                   "Mayor capacidad de bombas", "Borsa di bombe progressiva",
                                   "Bomben-Kapazität Aufwertung" },
                             Text{ "Progressive Bomb Pack", "Paquet de bombes (prog.)", "Zurrón de bombas progresivo",
                                   "Portaboom progressivo", "Bombenrucksack Aufwertung" },
                             Text{ "Progressive Bomb Box", "Boîte à bombes (prog.)", "Bolsa de bombas progresiva",
                                   "Sacco di bombe progressivo", "Bombenschachtel Aufwertung" } };
    trickNameTable[0x83] = { Text{ "Progressive Arrow Capacity", "Capacité de flèches (prog.)",
                                   "Mayor capacidad de flechas", "Faretra progressiva", "Pfeil-Kapazität Aufwertung" },
                             Text{ "Progressive Hero's Bow", "Arc du héros (prog.)", "Arco del héroe progresivo",
                                   "Arco dell'eroe progressivo", "Heroenbogen Aufwertung" },
                             Text{ "Progressive Arrow Holder", "Arbalète (prog.)", "Ballesta progresiva",
                                   "Balestra progressiva", "Köcher Aufwertung" } };
    trickNameTable[0x84] = { Text{ "Progressive Seed Capacity", "Capacité de graines (prog.)",
                                   "Mayor capacidad de semillas", "Portasemi progressivo",
                                   "Kern-Kapazität Aufwertung" },
                             Text{ "Progressive Scattershot", "Lance-pierre rafale (prog.)",
                                   "Resortera múltiple progresiva", "Fionda multiprogressiva", "Zwillen Aufwertung" },
                             Text{ "Progressive Seed Satchel", "Sac de graines (prog.)", "Bolsa de semillas progresiva",
                                   "Sacco dei semi progressivo", "Saatbeutel Aufwertung" } };
    trickNameTable[0x85] = { Text{ "Progressive Rupee Capacity", "Capacité de rubis (prog.)",
                                   "Mayor capacidad de rupias", "Espansione per rupie progressiva",
                                   "Rubin-Kapazität Aufwertung" },
                             Text{ "Progressive Purse", "Sacoche (prog.)", "Cartera de rupias progresiva",
                                   "Portamonete progressivo", "Portemonnaie Aufwertung" },
                             Text{ "Progressive Rupee Bag", "Sac à rubis (prog.)", "Zurrón de rupias progresivo",
                                   "Sacco di rupie progressivo", "Rubintaschen Aufwertung" } };
    trickNameTable[0x86] = { Text{ "Progressive Diving Ability", "Plongée (prog.)", "Buceo progresivo",
                                   "Capacità di immersione progressiva", "Tauchfähigkeit Aufwertung" },
                             Text{ "Progressive Pearl", "Perle (prog.)", "Perla progresiva", "Perla progressiva",
                                   "Perlen Aufwertung" },
                             Text{ "Progressive Scute", "Bulle (prog.)", "Fragmento Zora progresivo",
                                   "Bolla progressiva", "Schuppen Aufwertung" } };
    trickNameTable[0x87] = { Text{ "Progressive Nut Pack", "Paquet de noix (prog.)", "Mayor capacidad de semillas",
                                   "Espansione per semi Deku progressiva", "Nussrucksack Aufwertung" },
                             Text{ "Progressive Nut Bag", "Sac de noix (prog.)", "Bolsa de nueces progresiva",
                                   "Portanoci Deku progressivo", "Nussbeutel Aufwertung" },
                             Text{ "Progressive Husk Capacity", "Capacité de noisettes (prog.)",
                                   "Mayor capacidad de castañas", "Espansione per bombe Deku progressiva",
                                   "Schalen-Kapazität Aufwertung" } };
    trickNameTable[0x88] = {
        Text{ "Progressive Stick Pack", "Paquet de bâtons Mojo (prog.)", "Mayor capacidad de bastones",
              "Espansione per bastoni Deku progressiva", "Stabrucksack Aufwertung" },
        Text{ "Progressive Stick Bag", "Sac de bâtons (prog.)", "Mayor capacidad de ramas deku",
              "Portarami Deku progressivo", "Stabbeutel Aufwertung" },
        Text{ "Progressive Rod Capacity", "Capacité de tiges (prog.)", "Mayor capacidad de cetros deku",
              "Espansione per gambi Deku progressiva", "Stock-Kapazität Aufwertung" }
    };
    trickNameTable[0x89] = { Text{ "Progressive Bomblings", "Bombinsectes (prog.)", "Bombinsectos progresivos",
                                   "Bomboli progressivi", "Bombenmaus Aufwertung" },
                             Text{ "Progressive Missiles", "Missiles (prog.)", "Misiles progresivos",
                                   "Bombchu progressivi", "Missile Aufwertung" },
                             Text{ "Progressive Bombchu Bag", "Sac à Bombchu (prog.)", "Bombachus progresivos",
                                   "Portaradiomine progressivo", "Krabbelminenbeutel Aufwertung" } };
    trickNameTable[0x8A] = {
        Text{ "Progressive Stamina Meter", "Jauge d'endurance (prog.)", "Medidor de vigor progresivo",
              "Barra del vigore progressiva", "Ausdauer Aufwertung" },
        Text{ "Progressive Energy Meter", "Jauge d'énergie (prog.)", "Medidor de energía progresivo",
              "Barra dell'energia progressiva", "Energie Aufwertung" },
        Text{ "Progressive Magic Powder", "Poudre magique (prog.)", "Medidor de carga progresivo",
              "Giara magica progressiva", "Zauberpulver Aufwertung" }
    };
    trickNameTable[0x8B] = { Text{ "Progressive Memento", "Souvenir (prog.)", "Silbato progresivo",
                                   "Ocherella progressiva", "Pfeifen Aufwertung" },
                             Text{ "Progressive Flute", "Flûte (prog.)", "Flauta progresiva", "Flauto progressivo",
                                   "Flöten Aufwertung" },
                             Text{ "Progressive Recorder", "Harmonica (prog.)", "Armónica progresiva",
                                   "Piffero progressivo", "Recorder Aufwertung" } };
    trickNameTable[0xD4] = { Text{ "Progressive Titan Blade", "Lame des Titans (prog.)", "Hoja del Titán progresiva",
                                   "Lama dei Titani progressiva", "Titanenklingen Aufwertung" },
                             Text{ "Progressive Goron Knife", "Lame Goron (prog.)", "Daga Goron progresiva",
                                   "Coltello Goron progressivo", "Goronen-Messer Aufwertung" },
                             Text{ "Progressive Giant Sword", "Épée géante (prog.)", "Espada gigante progresiva",
                                   "Spada gigante progressiva", "Riesenschwert Aufwertung" } };

    trickNameTable[0x0F] = {
        Text{ "Magic Bottle", "Flacon magique", "Frasco feérico", "Ampolla per fate", "Magische Flasche" },
        Text{ "Glass Bottle", "Flacon de verre", "Botella de cristal", "Ampolla di vetro", "Glasflasche" },
        Text{ "Bottle with Water", "Flacon d'eau", "Botella Tingle", "Aria in bottiglia", "Flasche (Wasser)" }
    };
    trickNameTable[0x14] = { Text{ "Bottle with Chateau Romani", "Flacon de cuvée Romani", "Botella de Reserva Romani",
                                   "Ampolla di Gran Riserva Romanì", "Flasche (Chateau Romani)" },
                             Text{ "Bottle with Fresh Milk", "Flacon de lait frais", "Botella de leche fresca",
                                   "Ampolla di latte fresco", "Flasche (Frische Milch)" },
                             Text{ "Bottle with Mystery Milk", "Flacon de lait grand cru", "Botella de leche extra",
                                   "Ampolla di latte strano", "Flasche (Verdächtige Milch)" } };
    trickNameTable[0x8C] = { Text{ "Bottle with Red Chu Jelly", "Flacon de gelée Chuchu rouge", "Jugo de Chuchu Rojo",
                                   "Ampolla di gelatina ChuChu rossa", "Flasche (Rotes Schleim-Gelee)" },
                             Text{ "Bottle with Medicine of Life", "Flacon d'élixir rouge",
                                   "Botella de medicina de la vida", "Ampolla di pozione rossa",
                                   "Flasche (Roter Trank)" },
                             Text{ "Bottle with Heart Potion", "Flacon de potion de soin", "Botella de poción de salud",
                                   "Ampolla di pozione Scaldacuore", "Flasche (Herztrank)" } };
    trickNameTable[0x8D] = { Text{ "Bottle with Green Chu Jelly", "Flacon de gelée Chuchu verte",
                                   "Jugo de Chuchu Verde", "Ampolla di gelatina ChuChu verde",
                                   "Flasche (Grünes Schleim-Gelee)" },
                             Text{ "Bottle with Medicine of Magic", "Flacon d'élixir vert",
                                   "Botella de medicina mágica", "Ampolla di pozione verde", "Flasche (Grüner Trank)" },
                             Text{ "Bottle with Stamina Potion", "Flacon d'Endurol", "Botella de elixir vigorizante",
                                   "Ampolla di pozione Levafatica", "Flasche (Ausdauertrank)" } };
    trickNameTable[0x8E] = { Text{ "Bottle with Blue Chu Jelly", "Flacon de gelée Chuchu bleue", "Jugo de Chuchu Azul",
                                   "Ampolla di gelatina ChuChu blu", "Flasche (Blaues Schleim-Gelee)" },
                             Text{ "Bottle with Water of Life", "Flacon d'élixir bleu", "Botella de agua de la vida",
                                   "Ampolla di pozione blu", "Flasche (Blauer Trank)" },
                             Text{ "Bottle with Air Potion", "Flacon de potion d'oxygène", "Botella de oxígeno",
                                   "Ampolla di Ossigeno Liquido", "Flasche (Lufttrank)" } };
    trickNameTable[0x8F] = { Text{ "Bottle with Forest Firefly", "Flacon avec une luciole", "Luciérnaga del bosque",
                                   "Lucciola dei Boschi in un'ampolla", "Flasche (Glühwürmchen)" },
                             Text{ "Bottle with Faerie", "Flacon de poudre féérique", "Gran Hada embotellada",
                                   "Fatina in un'ampolla", "Falsche (Fee)" },
                             Text{ "Bottle with Stray Fairy", "Flacon avec une fée perdue",
                                   "Hada perdida en una botella", "Fata sperduta in un'ampolla",
                                   "Flasche (Verirrte Fee)" } };
    trickNameTable[0x90] = {
        Text{ "Bottle with Small Jabu-Jabu", "Flacon avec mini Jabu-Jabu", "Lord Chapu-Chapu embotellado",
              "Chapu Chapu in un'ampolla", "Flasche (Baby Jabu)" },
        Text{ "Bottle with Hyrule Bass", "Flacon avec perche d'Hyrule", "Locha de Hyrule embotellada",
              "Aspio Hyrule in un'ampolla", "Flasche (Hyrulebarsch)" },
        Text{ "Bottle with Hyrule Loach", "Flacon avec loche d'Hyrule", "Perca de Términa embotellada",
              "Luccio Hylia in un'ampolla", "Flasche (Hyrulegrundel)" }
    };
    trickNameTable[0x91] = {
        Text{ "Bottle with Will-O-Wisp", "Flacon avec feu follet", "Botella de llama azul", "Fuoco fatuo in un'ampolla",
              "Flasche (Rotes Feuer)" },
        Text{ "Bottle with Ancient Flame", "Flacon de flamme ancienne", "Botella de fuego ancestral",
              "Ampolla di fuoco ancestrale", "Flasche (Antike Flamme)" },
        Text{ "Bottle with Nayru's Flame", "Flacon de flamme de Nayru", "Botella de llamas de Nayru",
              "Fiamma di Nayru in un'ampolla", "Flasche (Nayrus Flamme)" }
    };
    trickNameTable[0x92] = { Text{ "Bottle with Baby Tektites", "Flacon de bébé Araknon", "Tektites en una botella",
                                   "Cuccioli di Tektite in un'ampolla", "Flasche (Baby Tektite)" },
                             Text{ "Bottle with Lanayru Ants", "Flacon de fourmis de Lanelle",
                                   "Celestarabajo embotellado", "Sabbiormiche in un'ampolla",
                                   "Flasche (Ranelle-Ameise)" },
                             Text{ "Bottle with Insects", "Flacon de bibittes", "Saltabosques embotellados",
                                   "Artropodi in un'ampolla", "Flasche (Insekt)" } };
    trickNameTable[0x94] = { Text{ "Bottle with Ghini", "Flacon avec Ghini", "Ghini en una botella",
                                   "Ghini in un'ampolla", "Flasche (Ghini)" },
                             Text{ "Bottle with Imp Poe", "Flacon avec Spectre", "Espectro en una botella",
                                   "Anima di spettro in un'ampolla", "Flasche (Geist)" },
                             Text{ "Bottle with Anti-Fairy", "Flacon avec Tetdoss", "Whisp en una botella",
                                   "Anti-fata in un'ampolla", "Flasche (Knochenfratze)" } };

    trickNameTable[0x15] = { Text{ "Bottle with Maggie's Letter", "Flacon avec lettre de Maggy", "Carta de Dolores",
                                   "Lettera di Maggy in un'ampolla", "Flasche (Dolores Brief)" },
                             Text{ "Bottle with Letter to Kafei", "Flacon avec lettre pour Kafei", "Carta para Kafei",
                                   "Lettera per Kafei in un'ampolla", "Flasche (Brief an Kafei)" },
                             Text{ "Bottle with Zelda's Letter", "Flacon avec lettre de Zelda", "Carta náutica",
                                   "Messaggio in bottiglia", "Flasche (Zeldas Brief)" } };
    trickNameTable[0x93] = { Text{ "Bottle with Composer Brother", "Flacon avec un compositeur",
                                   "Hermana Poe embotellada", "Mortaldi in un'ampolla", "Flasche (Ludwig Brahmstein)" },
                             Text{ "Bottle with Jalhalla", "Flacon avec Jalhalla", "Yaihalla embotellado",
                                   "Jay-Harla in un'ampolla", "Flasche (Jalhalla)" },
                             Text{ "Bottle with Grim Repoe", "Flacon avec le Faucheur", "Bubble en una botella",
                                   "Cupoo mietitore in un'ampolla", "Flasche (Tagschwärmer)" } };

    trickNameTable[0xC1] = { Text{ "Ballad of the Goddess", "Chant de la déesse", "Cántico de la Diosa",
                                   "Melodia della Dea", "Hymne der Göttin" },
                             Text{ "Song of Healing", "Chant de l'apaisement", "Canción de curación",
                                   "Melodia del ristoro", "Lied der Befreiung" },
                             Text{ "Bolero of Fire", "Boléro du feu", "Bolero del fuego", "Bolero del fuoco",
                                   "Bolero des Feuers" } };
    trickNameTable[0xC2] = { Text{ "Earth God's Lyric", "Hymne du dieu de la terre",
                                   "Melodía del Espíritu de la Tierra", "Inno della Terra", "Hymne des Terragottes" },
                             Text{ "Song of Soaring", "Chant de l'envol", "Canción del viento", "Melodia del volo",
                                   "Lied der Schwingen" },
                             Text{ "Requiem of Spirit", "Requiem des esprits", "Réquiem del espíritu",
                                   "Requiem dello spirito", "Requiem der Geister" } };
    trickNameTable[0xC3] = { Text{ "Wind God's Aria", "Hymne du dieu du vent", "Melodía del Espíritu del Viento",
                                   "Inno del Vento", "Hymne des Zephirgottes" },
                             Text{ "Wind's Requiem", "Mélodie du vent", "Melodía del Viento", "Canzone del Vento",
                                   "Lied des Windes" },
                             Text{ "Minuet of Forest", "Menuet de la forêt", "Minueto del bosque",
                                   "Minuetto della foresta", "Menuett des Waldes" } };
    trickNameTable[0xC4] = { Text{ "Song of Passing", "Mambo de Manbo", "Melodía del transcurrir",
                                   "Sonata in Dì Notturno", "Kleine Tag- und Nachtmusik" },
                             Text{ "Command Melody", "Air du marionnettiste", "Cara al Sol", "Canto del Burattino",
                                   "Sonate des Puppenspielers" },
                             Text{ "Prelude of Light", "Prélude de la lumière", "Preludio de la luz",
                                   "Preludio della luce", "Kantate des Lichts" } };
    trickNameTable[0xC5] = { Text{ "Song of Double Time", "Chant accéléré", "Canción del doble tiempo",
                                   "Canzone del tempo accelerato", "Thema der Zeit im Wind" },
                             Text{ "Inverted Song of Time", "Chant du temps inversé", "Canción del tiempo invertida",
                                   "Canzone del tempo rallentato", "Ballade des Kronos" },
                             Text{ "Serenade of Water", "Sérénade de l'eau", "Serenata del agua", "Serenata dell'acqua",
                                   "Serenade des Wassers" } };
    trickNameTable[0xC6] = { Text{ "Ballad of Gales", "Requiem de la tornade", "Melodía del Tornado",
                                   "Melodia del Tifone", "Kanon des Sturmes" },
                             Text{ "Frog's Song of Soul", "Rap des grenouilles", "Canción del alma de la rana",
                                   "Soul della rana", "Krötenrap" },
                             Text{ "Nocturne of Shadow", "Nocturne de l'ombre", "Nocturno de la sombra",
                                   "Notturno delle ombre", "Nocturne des Schattens" } };
    trickNameTable[0xBB] = {
        Text{ "Saria's Karaoke", "Karaoké de Saria", "Dueto del bosque", "Minuetto della fortuna", "Salias Karaoke" },
        Text{ "Sonata of Awakening", "Sonate de l'éveil", "Sonata del despertar", "Sonata del risveglio",
              "Sonate des Erwachens" },
        Text{ "Saria's Song", "Chant de Saria", "Canción de Saria", "Canzone di Saria", "Salias Lied" }
    };
    trickNameTable[0xBC] = {
        Text{ "Darunia's Tango", "Tango de Darunia", "Coro del fuego", "Bolero del fosco", "Darunias Tango" },
        Text{ "Goron Lullaby", "Berceuse des Gorons", "Nana goron", "Ninna nanna Goron", "Goronisches Schlummerlied" },
        Text{ "Zelda's Lullaby", "Berceuse de Zelda", "Nana de Zelda", "Ninna nanna di Zelda", "Zeldas Wiegenlied" }
    };
    trickNameTable[0xBD] = {
        Text{ "Ruto's Blues", "Blues de Ruto", "Sonata del agua", "Serenata dell'aceto", "Rutos Blues" },
        Text{ "New Wave Bossa Nova", "Bossa-nova des flots", "Bossanova de las olas", "Bossa nova marina",
              "Bossa Nova der Kaskaden" },
        Text{ "Song of Time", "Chant du temps", "Canción del tiempo", "Canzone del tempo", "Hymne der Zeit" }
    };
    trickNameTable[0xBE] = { Text{ "Nabooru's Reggae", "Reggae de Nabooru", "Reggae del espíritu",
                                   "Requiem dello spiritoso", "Naborus Reggae" },
                             Text{ "Elegy of Emptiness", "Hymne du vide", "Elegía al vacío", "Elegia delle statue",
                                   "Elegie des leeren Herzens" },
                             Text{ "Epona's Song", "Chant d'Épona", "Canción de Epona", "Canzone di Epona",
                                   "Eponas Lied" } };
    trickNameTable[0xBF] = { Text{ "Impa's Death Metal", "Death métal d'Impa", "Diurno de la sombra",
                                   "Notturno delle orbe", "Impas Death Metal" },
                             Text{ "Oath to Order", "Ode de l'appel", "Oda al orden", "Ode alla promessa",
                                   "Gesang des Himmels" },
                             Text{ "Song of Storms", "Chant des tempêtes", "Canción de la tormenta",
                                   "Canzone della tempesta", "Hymne des Sturms" } };
    trickNameTable[0xC0] = { Text{ "Rauru's Sing-Along", "Chansonnette de Rauru", "Predulio de luz",
                                   "Preludio della lode", "Raurus Singalong" },
                             Text{ "Ballad of the Wind Fish", "Ballade sur Poisson-Rêve", "Balada del Piez Viento",
                                   "Ballata del Pesce Vento", "Ballade vom Windfisch" },
                             Text{ "Sun's Song", "Chant du soleil", "Canción del Sol", "Canto del sole",
                                   "Hymne der Sonne" } };

    trickNameTable[0xCB] = {
        Text{ "Pendant of Courage", "Pendentif du courage", "Colgante del valor", "Amuleto del coraggio",
              "Amulett des Mutes" },
        Text{ "Farore's Emerald", "Émeraude de Farore", "Esmeralda de Farore", "Smeraldo di Farore", "Farore-Smaragd" },
        Text{ "Kokiri's Peridot", "Péridot Kokiri", "Ágata de los Kokiri", "Olivina dei Kokiri", "Kokiri-Peridot" }
    };
    trickNameTable[0xCC] = { Text{ "Pendant of Power", "Pendentif de la force", "Colgante del poder",
                                   "Amuleto della forza", "Amulett der Stärke" },
                             Text{ "Din's Ruby", "Rubis de Din", "Rubí de Din", "Rubino di Din", "Din-Rubin" },
                             Text{ "Goron's Garnet", "Grenat Goron", "Topacio de los Goron", "Granato dei Goron",
                                   "Goronen-Granat" } };
    trickNameTable[0xCD] = { Text{ "Pendant of Wisdom", "Pendentif de la sagesse", "Colgante de la sabiduría",
                                   "Amuleto della saggezza", "Amulett der Weisheit" },
                             Text{ "Nayru's Sapphire", "Saphir de Nayru", "Zafiro de Nayru", "Zaffiro di Nayru",
                                   "Nayru-Saphir" },
                             Text{ "Zora's Aquamarine", "Aquamarine Zora", "Lapislázuli de los Zora",
                                   "Acquamarina degli Zora", "Zora-Aquamarin" } };
    trickNameTable[0xCE] = {
        Text{ "Wind Medallion", "Médaillon du vent", "Medallón del Viento", "Medaglione del Vento", "Wind-Medaillon" },
        Text{ "Saria's Medallion", "Médaillon de Saria", "Medallón de Saria", "Medaglione di Saria", "Salia-Amulett" },
        Text{ "Medallion of Forest", "Médaillon du temple de la forêt", "Medalla del Bosque", "Medaglione Forestale",
              "Medaillon des Waldes" }
    };
    trickNameTable[0xCF] = { Text{ "Bombos Medallion", "Médaillon des flammes", "Medallón del Temblor",
                                   "Medaglione Fiamma", "Feuer-Medaillon" },
                             Text{ "Darunia's Medallion", "Médaillon de Darunia", "Medallón de Darunia",
                                   "Medaglione di Darunia", "Darunia-Amulett" },
                             Text{ "Medallion of Fire", "Médaillon du temple du feu", "Medalla del Fuego",
                                   "Medaglione Focoso", "Medaillon des Feuers" } };
    trickNameTable[0xD0] = {
        Text{ "Ice Medallion", "Médaillon de glace", "Medallón Helado", "Medaglione del Ghiaccio", "Eis-Medaillon" },
        Text{ "Ruto's Medallion", "Médaillon de Ruto", "Medallón de Ruto", "Medaglione di Ruto", "Ruto-Amulett" },
        Text{ "Medallion of Water", "Médaillon du temple de l'eau", "Medalla del Agua", "Medaglione Acquoso",
              "Medaillon des Wassers" }
    };
    trickNameTable[0xD1] = { Text{ "Quake Medallion", "Médaillon des secousses", "Medallón Llamarada",
                                   "Medaglione Sisma", "Erd-Medaillon" },
                             Text{ "Nabooru's Medallion", "Médaillon de Nabooru", "Medallón de Nabooru",
                                   "Medaglione di Naburu", "Naboru-Amulett" },
                             Text{ "Medallion of Spirit", "Médaillon du temple de l'esprit", "Medalla del Espíritu",
                                   "Medaglione Spiritoso", "Medaillon der Geister" } };
    trickNameTable[0xD2] = { Text{ "Travel Medallion", "Amulette de téléportation", "Medallón Maligno",
                                   "Amuleto del teletrasporto", "Teleport-Medaillon" },
                             Text{ "Impa's Medallion", "Médaillon d'Impa", "Medallón de Impa", "Medaglione di Impa",
                                   "Impa-Amulett" },
                             Text{ "Medallion of Shadow", "Médaillon du temple de l'ombre", "Medalla de la Sombra",
                                   "Medaglione Oscuro", "Medaillon des Schattens" } };
    trickNameTable[0xD3] = {
        Text{ "Ether Medallion", "Médaillon d'éther", "Medallón de Tesoro", "Medaglione Etere", "Luft-Medaillon" },
        Text{ "Rauru's Medallion", "Médaillon de Rauru", "Medallón de Rauru", "Medaglione di Rauru", "Rauru-Amulett" },
        Text{ "Medallion of Light", "Médaillon du temple de lumière", "Medalla de la Luz", "Medaglione Lucente",
              "Medaillon des Lichts" }
    };

    trickNameTable[GI_HEART] = {
        Text{ "Love", "Bisou", "Te amo", "Amore", "Liebe" },
        Text{ "Heart Container", "Réceptacle de cœur", "Contenedor de corazón", "Portacuori", "Herzcontainer" },
        Text{ "Piece of Heart", "Quart de cœur", "Pieza de corazón", "Frammento di cuore", "Herzteil" }
    };
    trickNameTable[GI_RUPEE_GREEN] = { Text{ "Green Rupy", "Rupee vert", "Rubia verde", "Bugia verde", "Grüner Ruby" },
                                       Text{ "One Rupee", "Un rubis", "Guaraní hyliano", "Una rupia", "Ein Rubin" },
                                       Text{ "Rupee (1)", "Rubis (1)", "Peso hyliano", "Rupia (1)", "Rubin (1)" } };
    trickNameTable[GI_RUPEE_BLUE]  = { Text{ "Blue Rupy", "Rupee bleu", "Rubia azul", "Bugia blu", "Blauer Ruby" },
                                       Text{ "Five Rupees", "Cinq rubis", "Bolívar hyliano", "Cinque rupie",
                                            "Fünf Rubine" },
                                       Text{ "Rupee (5)", "Rubis (5)", "Peso hyliano", "Rupie (5)", "Rubin (5)" } };
    trickNameTable[GI_RUPEE_RED]   = { Text{ "Red Rupy", "Rupee rouge", "Rubia roja", "Bugia rossa", "Roter Ruby" },
                                       Text{ "Twenty Rupees", "Vingt rubis", "Colon hyliano", "Venti rupie",
                                           "Zwanzig Rubine" },
                                       Text{ "Rupee (20)", "Rubis (20)", "Peso hyliano", "Rupie (20)", "Rubin (20)" } };
    trickNameTable[GI_RUPEE_PURPLE] = {
        Text{ "Purple Rupy", "Rupee pourpre", "Rubia morada", "Bugia viola", "Violetter Ruby" },
        Text{ "Fifty Rupees", "Cinquante rubis", "Balboa hyliano", "Cinquanta rupie", "Fünfzig Rubine" },
        Text{ "Rupee (50)", "Rubis (50)", "Peso hyliano", "Rupie (50)", "Rubin (50)" }
    };
    trickNameTable[GI_RUPEE_GOLD] = {
        Text{ "Huge Rupy", "Énorme Rupee", "Rubia gigante", "Bugia gigante", "Goldener Ruby" },
        Text{ "Two Hundred Rupees", "Deux cent rubis", "Euro hyliano", "Duecento rupie", "Zweihundert Rubine" },
        Text{ "Rupee (200)", "Rubis (200)", "Dólar hyliano", "Rupie (200)", "Rubin (200)" }
    };
    trickNameTable[GI_HEART_PIECE] = {
        Text{ "Piece of Health", "Quart d'énergie", "Pieza de amor", "Frammento di portacuori", "Harzteil" },
        Text{ "Recovery Heart", "Cœur d'énergie", "Corazón", "Cuore", "Herz" },
        Text{ "Heart Container", "Réceptacle de cœur", "Contenedor de corazón", "Portacuori", "Herzcontainer" }
    };
    trickNameTable[GI_HEART_CONTAINER_2] = {
        Text{ "Health Container", "Réceptacle d'énergie", "Contenedor de amor", "Portacure", "Harzcontainer" },
        Text{ "Recovery Heart", "Quart de cœur", "Corazón", "Cuore", "Herz" },
        Text{ "Piece of Heart", "Cœur d'énergie", "Pieza de corazón", "Frammento di cuore", "Herzteil" }
    };
    trickNameTable[GI_TRIFORCE_PIECE] = {
        Text{ "Piece of Cheese", "Morceau de Fromage", "Fragmento de queso", "Frammento di Formaggio", "Stück Käse" },
        Text{ "Triforce Shard", "Éclat de Triforce", "Pedazo de la Trifuerza", "Pezzo della Triforza",
              "Triforce-Scherbe" },
        Text{ "Shiny Rock", "Caiiloux Brillant", "Piedra brillante", "Oro 24K", "Glitzernden Stein" }
    };

    /*
      //Names for individual upgrades, in case progressive names are replaced
      trickNameTable[GI_HOOKSHOT] = {
         Text{"Grappling Hook", "Grappin-griffe", "Gancho lanzable", "Italiano", "Enterhaken"},
         Text{"Clawshot", "Lance-chaîne", "Zarpa", "Italiano", "Greifhaken"},
         Text{"Gripshot", "Grappince", "Enganchador", "Italiano", "Tauschhaken"}};
      trickNameTable[GI_LONGSHOT] = {
             Text{"Longshot, no strings attached", "Grappin sans attrape", "Gancho lanzable más largo", "Italiano",
      "Enterhaken, Umtausch ausgeschlossen"}, Text{"Double Clawshot", "Double-grappin", "Superzarpa", "Italiano",
      "Doppelhaken"}, Text{"Switch Hook", "Great grappin", "Gancho chulo", "Italiano", "Tauschhaken"}};
      trickNameTable[GI_BOMB_BAG_1] = {
             Text{"Bomb Capacity (20)", "Capacité de bombes (20)", "Bolsa de bombas (contiene 20)", "Italiano",
      "Bomben-Kapazität (20)"}, Text{"Bronze Bomb Bag", "Sac de bombes de bronze", "Saco de bronce de bombas",
      "Italiano", "Bronzene Bombentasche"}, Text{"Small Bomb Bag", "Petit sac de bombes", "Zurrón de bombas pequeño",
      "Italiano", "Kleine Bombentasche"}}; trickNameTable[GI_BOMB_BAG_2] = { Text{"Bomb Capacity (30)", "Capacité de
      bombes (30)", "Bolsa de bombas (contiene 30)", "Italiano", "Bomben-Kapazität (30)"}, Text{"Silver Bomb Bag", "Sac
      de bombes d'argent", "Saco plateado de bombas", "Italiano", "Silberne Bombentasche"}, Text{"Medium Bomb Bag", "Sac
      de bombes moyen", "Zurrón de bombas mediano", "Italiano", "Mittlere Bombentasche"}}; trickNameTable[GI_BOMB_BAG_3]
      = { Text{"Bomb Capacity (40)", "Capacité de bombes (40)", "Bolsa de bombas (contiene 40)", "Italiano",
      "Bomben-Kapazität (40)"}, Text{"Golden Bomb Bag", "Sac de bombes d'or", "Saco dorado de bombas", "Italiano",
      "Goldene Bombentasche"}, Text{"Large Bomb Bag", "Gros sac de bombes", "Zurrón de bombas grande", "Italiano",
      "Gigantische Bombentasche"}}; trickNameTable[GI_BOW_1] = { Text{"Bow", "Arc", "Arco del Hada", "Italiano",
      "Bogen"}, Text{"Hero's Bow", "Arc du héros", "Arco del héroe", "Italiano", "Heroenbogen"}, Text{"Small Quiver",
      "Petit carquois", "Saco de flechas pequeño", "Italiano", "Kleiner Köcher"}}; trickNameTable[GI_BOW_2] = {
             Text{"Arrow Capacity (40)", "Capacité de flèches (40)", "Capacidad de flechas (40)", "Italiano",
      "Pfeil-Kapazität (40)"}, Text{"Silver Quiver", "Carquois d'argent", "Carcaj plateado", "Italiano", "Silberner
      Köcher"}, Text{"Medium Quiver", "Carquois moyen", "Saco de flechas mediano", "Italiano", "Mittlerer Köcher"}};
      trickNameTable[GI_BOW_3] = {
             Text{"Arrow Capacity (50)", "Capacité de flèches (50)", "Capacidad de flechas (50)", "Italiano",
      "Pfeil-Kapazität (50)"}, Text{"Golden Quiver", "Carquois d'or", "Carcaj dorado", "Italiano", "Goldener Köcher"},
         Text{"Large Quiver", "Gros carquois", "Saco de flechas grande", "Italiano", "Gigantischer Köcher"}};
      trickNameTable[GI_SLINGSHOT_1] = {
             Text{"Slingshot", "Lance-pierre", "Tirachinas del Hada", "Italiano", "Schleuder"},
         Text{"Scattershot", "Lance-pierre rafale", "Tirachinas múltiple", "Italiano", "Zwille"},
         Text{"Small Seed Satchel", "Petit sac de graines", "Bolsa de semillas pequeña", "Italiano", "Kleiner
      Saatbeutel"}}; trickNameTable[GI_SLINGSHOT_2] = { Text{"Deku Seed Capacity (40)", "Capacité de graines (40)",
      "Capacidad de semillas (40)", "Italiano", "Deku-Kern-Kapazität (40)"}, Text{"Silver Deku Seed Bullet Bag", "Sac de
      graines d'argent", "Bolsa de balas (contiene 40)", "Italiano", "Silberner Saatbeutel"}, Text{"Medium Seed
      Satchel", "Sac de graines moyen", "Bolsa de semillas mediana", "Italiano", "Mittlerer Saatbeutel"}};
      trickNameTable[GI_SLINGSHOT_3] = {
             Text{"Deku Seed Capacity (50)", "Capacité de graines (50)", "Capacidad de semillas (50)", "Italiano",
      "Deku-Kern-Kapazität (50)"}, Text{"Golden Deku Seed Bullet Bag", "Sac de graines d'or", "Bolsa de balas (contiene
      50)", "Italiano", "Goldener Saatbeutel"}, Text{"Large Seed Satchel", "Gros sac de graines", "Bolsa de semillas
      grande", "Italiano", "Gigantischer Saatbeutel"}}; trickNameTable[GI_STRENGTH_1] = { Text{"Goron's Gauntlet",
      "Gantelet Goron", "Brazalete amarillo", "Italiano", "Goronen-Handschuhe"}, Text{"Power Bracelet", "Bracelet de
      force", "Brazalete de fuerza", "Italiano", "Kraftarmband"}, Text{"Magic Bracelet", "Bracelet de Lavio", "Brazalete
      de Ravio", "Italiano", "Magisches Armband"}}; trickNameTable[GI_STRENGTH_2] = { Text{"Silver Bracelets",
      "Bracelets d'argent", "Guantes Moguma", "Italiano", "Silberarmband"}, Text{"Power Gloves", "Gant de puissance",
      "Guante del Poder", "Italiano", "Krafthandschuhe"}, Text{"Magic Gauntlets", "Gantelet magique", "Guante mágico",
      "Italiano", "Magische Handschuhe"}}; trickNameTable[GI_STRENGTH_3] = { Text{"Golden Bracelets", "Bracelets d'or",
      "Guantelete de Thanos", "Italiano", "Goldarmband"}, Text{"Titan's Mitts", "Moufle de titan", "Guantes de Titán",
      "Italiano", "Titanenhandschuhe"}, Text{"Magnetic Gloves", "Magnéto-gants", "Guantes de fuego", "Italiano",
      "Magnethandschuhe"}}; trickNameTable[GI_SCALE_1] = { Text{"Silver Pearl", "Perle d'argent", "Perla de Plata
      progresiva", "Italiano", "Silberne Perle"}, Text{"Adult Scale", "Écaille d'adulte", "Bola de bolos zora",
      "Italiano", "Große Schuppe"}, Text{"Zora Scale", "Écaille Zora", "Escama de Zora", "Italiano", "Zora-Schuppe"}};
      trickNameTable[GI_SCALE_2] = {
             Text{"Golden Pearl", "Perle d'or", "Perla de Oro progresiva", "Italiano", "Goldene Perle"},
         Text{"Giant Scale", "Écaille de géant", "Escama de Faren", "Italiano", "Riesenschuppe"},
         Text{"Water Dragon Scale", "Écaille du dragon de l'eau", "Escama de dragón acuático", "Italiano",
      "Wasserdrachenschuppe"}}; trickNameTable[GI_WALLET_1] = { Text{"Rupee Capacity (200)", "Capacité de rubis (200)",
      "Capacidad de rupias (200)", "Italiano", "Rubin-Kapazität (200)"}, Text{"Silver Wallet", "Bourse d'argent",
      "Cartera de rupias de adulto", "Italiano", "Silberne Börse"}, Text{"Medium Wallet", "Bourse moyenne", "Zurrón de
      rupias mediano", "Italiano", "Mittlere Börse"}}; trickNameTable[GI_WALLET_2] = { Text{"Rupee Capacity (500)",
      "Capacité de rubis (500)", "Capacidad de rupias (500)", "Italiano", "Rubin-Kapazität (500)"}, Text{"Golden
      Wallet", "Bourse d'or", "Cartera de rupias gigante", "Italiano", "Goldene Börse"}, Text{"Large Wallet", "Grosse
      bourse", "Zurrón de rupias grande", "Italiano", "Gigantische Börse"}}; trickNameTable[GI_WALLET_3] = { Text{"Rupee
      Capacity (999)", "Capacité de rubis (999)", "Capacidad de rupias (999)", "Italiano", "Rubin-Kapazität (999)"},
         Text{"Golden Wallet", "Bourse d'or", "Cartera de ricachón", "Italiano", "Goldene Börse"},
         Text{"Large Wallet", "Grosse bourse", "Zurrón de rupias gigante", "Italiano", "Gigantische Börse"}};
      trickNameTable[GI_DEKU_NUT_UPGRADE_1] = {
             Text{"Deku Bomb Capacity (30)", "Capacité de bombes Mojo (30)", "Capacidad de semillas deku (40)",
      "Italiano", "Deku-Bomben-Kapazität (30)"}, Text{"Baba Nut Capacity (30)", "Capacité de noix Baba (30)", "Capacidad
      de nueces baba (40)", "Italiano", "Ranha-Nuss-Kapazität (30)"}, Text{"Deku Nut Pack (30)", "Paquet de noix Mojo
      (30)", "Capacidad de nueces mojo (40)", "Italiano", "Deku-Nussrucksack (30)"}};
      trickNameTable[GI_DEKU_NUT_UPGRADE_2] = {
             Text{"Deku Bomb Capacity (40)", "Capacité de bombes Mojo (40)", "Capacidad de semillas deku (50)",
      "Italiano", "Deku-Bomben-Kapazität (40)"}, Text{"Baba Nut Capacity (40)", "Capacité de noix Baba (40)", "Capacidad
      de nueces baba (50)", "Italiano", "Ranha-Nuss-Kapazität (40)"}, Text{"Deku Nut Pack (40)", "Paquet de noix Mojo
      (40)", "Capacidad de nueces mojo (50)", "Italiano", "Deku-Nussrucksack (40)"}};
      trickNameTable[GI_DEKU_STICK_UPGRADE_1] = {
             Text{"Deku Rod Capacity (20)", "Capacité de tiges Mojo (20)", "Capacidad de palos mojo (20)", "Italiano",
      "Deku-Stock-Kapazität (20)"}, Text{"Boko Stick Capacity (20)", "Capacité de bâtons Boko (20)", "Capacidad de palos
      boko (20)", "Italiano", "Ranha-Stab-Kapazität (20)"}, Text{"Deku Stick Pack (20)", "Paquet de bâtons Mojo (20)",
      "Capacidad de bastones deku (20)", "Italiano", "Deku-Stabrucksack (20)"}}; trickNameTable[GI_DEKU_STICK_UPGRADE_2]
      = { Text{"Deku Rod Capacity (30)", "Capacité de tiges Mojo (30)", "Capacidad de palos mojo (30)", "Italiano",
      "Deku-Stock-Kapazität (30)"}, Text{"Boko Stick Capacity (30)", "Capacité de bâtons Boko (30)", "Capacidad de palos
      boko (30)", "Italiano", "Ranha-Stab-Kapazität (30)"}, Text{"Deku Stick Pack (30)", "Paquet de bâtons Mojo (30)",
      "Capacidad de bastones deku (30)", "Italiano", "Deku-Stabrucksack (30)"}}; trickNameTable[GI_MAGIC_1] = {
             Text{"Stamina Meter", "Jauge d'endurance", "Medidor de vigor", "Italiano", "Ausdauerleiste"},
         Text{"Energy Meter", "Jauge d'énergie", "Medidor de energía", "Italiano", "Energieleiste"},
         Text{"Magic Powder", "Poudre magique", "Medidor de carga", "Italiano", "Zauberpulver"}};
      trickNameTable[GI_MAGIC_2] = {
             Text{"Enhanced Stamina Meter", "Jauge d'endurance améliorée", "Medidor de vigor mejorado", "Italiano",
      "Verbesserte Ausdauerleiste"}, Text{"Enhanced Energy Meter", "Jauge d'énergie améliorée", "Medidor de energía
      mejorado", "Italiano", "Verbesserte Energieleiste"}, Text{"Enhanced Magic Powder", "Poudre magique améliorée",
      "Medidor de carga mejorado", "Italiano", "Verbessertes Zauberpulver"}}; trickNameTable[GI_OCARINA_1] = {
             Text{"Ocarina", "Ocarina", "Ocarina", "Italiano", "Okarina"},
         Text{"Saria's Ocarina", "Ocarina de Saria", "Ocarina de Saria", "Italiano", "Salias Okarina"},
         Text{"Wood Ocarina", "Ocarina de bois", "Ocarina del Hada", "Italiano", "Holzokarina"}};
      trickNameTable[GI_OCARINA_2] = {
             Text{"Flute", "Flûte", "Flauta", "Italiano", "Flöte"},
         Text{"Zelda's Ocarina", "Ocarina de Zelda", "Ocarina de Zelda", "Italiano", "Zeldas Okarina"},
         Text{"Ocarina of Winds", "Ocarina des vents", "Ocarina del Viento", "Italiano", "Okarina des Windes"}};
      trickNameTable[GI_CUCCO] = {
             Text{"D.I.Y. Alarm Clock", "Réveille-matin improvisé", "Alarma emplumada", "Italiano", "Improvisierter
      Wecker"}, Text{"Kakariko Cucco", "Cocotte Cocorico", "Cuco de Kakariko", "Italiano", "Kakariko Huhn"},
         Text{"Hatched Cucco", "Cocotte éclose", "Pollo", "Italiano", "Geschlüpftes Küken"}};
      trickNameTable[GI_MASK_KEATON] = {
             Text{"Kee... Something Mask", "Masque de Quiche", "Máscara Kealgo", "Italiano", "Keaton-Maske"},
         Text{"Kitsune Mask", "Masque de Kitsune", "Máscara Kitsune", "Italiano", "Kitsune-Maske"},
         Text{"Kafei's Mask", "Masque de Kafei", "Máscara de Kafei", "Italiano", "Kafeis Maske"}};
      trickNameTable[GI_MASK_SKULL] = {
             Text{"Skull Kid's Mask", "Masque de Skull Kid", "Máscara de Skull Kid", "Italiano", "Horror-Kids-Maske"},
         Text{"Stalfos Mask", "Masque de squelette", "Máscara de Stalfos", "Italiano", "Stalfos-Maske"},
         Text{"Captain's Hat", "Heaume du capitaine", "Casco del capitán", "Italiano", "Helm des Hauptmanns"}};
      trickNameTable[GI_MASK_SPOOKY] = {
             Text{"Skrik Mask", "Masque Skrik", "Máscara Escalofriante", "Italiano", "Grusel-Maske"},
         Text{"ReDead Mask", "Masque de Remort", "Máscara de ReDead", "Italiano", "Zombie-Maske"},
         Text{"Gibdo Mask", "Masque de Gibdo", "Careta de Gibdo", "Italiano", "Gibdo-Maske"}};
      trickNameTable[GI_MASK_BUNNY] = {
             Text{"Peppy Mask", "Masque de Peppy", "Capucha de Pascua", "Italiano", "Peppy-Maske"},
         Text{"Bunny Ears", "Oreilles de lapin", "Orejas de conejo", "Italiano", "Ohrlöffel"},
         Text{"Postman's Hat", "Casquette du facteur", "Gorra de cartero", "Italiano", "Mütze des Postboten"}};
      trickNameTable[GI_MASK_GORON] = {
             Text{"Goro Mask", "Masque Goro", "Máscara Goro", "Italiano", "Garos Maske"},
         Text{"Mask of Goron", "Masque des Gorons", "Máscara de los Goron", "Italiano", "Goronen-Haut"},
         Text{"Darunia Mask", "Masque de Darunia", "Máscara de Darmani", "Italiano", "Darunias Maske"}};
      trickNameTable[GI_MASK_ZORA] = {
             Text{"Zola Mask", "Masque Zola", "Máscara Zola", "Italiano", "Zola-Maske"},
         Text{"Mask of Zora", "Masque des Zoras", "Máscara de los Zora", "Italiano", "Zora-Schuppen"},
         Text{"Ruto Mask", "Masque de Ruto", "Máscara de Mikau", "Italiano", "Rutos Maske"}};
      trickNameTable[GI_MASK_GERUDO] = {
             Text{"Ganguro Mask", "Masque de Ganguro", "Máscara Canguro", "Italiano", "Ganguro-Maske"},
         Text{"Mask of Gerudo", "Masque des Gerudos", "Máscara de las Gerudo", "Italiano", "Gerudo-Perücke"},
         Text{"Nabooru Mask", "Masque de Nabooru", "Máscara de Nabooru", "Italiano", "Naborus Maske"}};
      trickNameTable[GI_MASK_TRUTH] = {
             Text{"Sheikah Mask", "Masque Sheikah", "Máscara Sheikah", "Italiano", "Shiekah-Maske"},
         Text{"Mask of Gossip", "Masque de potins", "Máscara chismosa", "Italiano", "Maske der Mythen"},
         Text{"Eye of Truth", "Œil de vérité", "Ojo de la Verdad", "Italiano", "Auge der Wahrheit"}};*/
}

// Generate a fake name for the ice trap based on the item it's displayed as
Text GetIceTrapName(u8 id) {
    // If the trick names table has not been initialized, do so
    if (!initTrickNames) {
        InitTrickNames();
        initTrickNames = true;
    }
    // Randomly get the easy, medium, or hard name for the given item id
    return RandomElement(trickNameTable[id]);
}

// Get shop index based on a given location
static std::map<std::string_view, int> ShopNameToNum = { { "KF Shop", 0 },         { "Kak Potion Shop", 1 },
                                                         { "MK Bombchu Shop", 2 }, { "MK Potion Shop", 3 },
                                                         { "MK Bazaar", 4 },       { "Kak Bazaar", 5 },
                                                         { "ZD Shop", 6 },         { "GC Shop", 7 } };
int GetShopIndex(LocationKey loc) {
    // Kind of hacky, but extract the shop and item position from the name
    const std::string& name(Location(loc)->GetName());
    int split = name.find(" Item ");
    std::string_view shop(name.c_str(), split);
    int pos     = std::stoi(name.substr(split + 6, 1)) - 1;
    int shopnum = ShopNameToNum[shop];
    return shopnum * 8 + pos;
}

// Without this transformed index, shop-related tables and arrays would need 64 entries- But only half of that is needed
// for shopsanity So we use this transformation to map only important indices to an array with 32 entries in the
// following manner: Shop index:  4  5  6  7 12 13 14 15 20 21 22 23... Transformed: 0  1  2  3  4  5  6  7  8  9
// 10 11... So we first divide the shop index by 4, then by 2 which basically tells us the index of the shop it's in,
// then multiply by 4 since there are 4 items per shop
// And finally we use a modulo by 4 to get the index within the "shop" of 4 items, and add
int TransformShopIndex(int index) {
    return 4 * ((index / 4) / 2) + index % 4;
}
