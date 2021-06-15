#include "item_list.hpp"

#include "logic.hpp"
#include "../code/include/z3D/z3Ditem.h"
#include <array>

using namespace Logic;

static std::array<Item, KEY_ENUM_MAX> itemTable;

void ItemTable_Init() {                                   //English name      French           Spanish           Item Type       getItemID    advancement     logic       hint key
    itemTable[NONE]                              = Item(Text{"No Item",      "Sin objeto",  "Pas d'objet"},   ITEMTYPE_EVENT, GI_RUPEE_GREEN,    false,    &noVariable,  NONE);
    itemTable[KOKIRI_SWORD]                      = Item(Text{"Kokiri Sword", "Épée Kokiri", "Espada Kokiri"}, ITEMTYPE_ITEM,  GI_SWORD_KOKIRI,   true,     &KokiriSword, KOKIRI_SWORD);
  //[MASTER_SWORD]
  //[GIANTS_KNIFE]
    itemTable[BIGGORON_SWORD]                    = Item(Text{"Biggoron's Sword", "Épée de Grogoron",       "Espada de Biggoron"},    ITEMTYPE_ITEM,  GI_SWORD_BGS,      true,       &noVariable,    BIGGORON_SWORD);
    itemTable[DEKU_SHIELD]                       = Item(Text{"Deku Shield",      "Bouclier Mojo",          "Escudo deku"},           ITEMTYPE_ITEM,  GI_SHIELD_DEKU,    false,      &noVariable,    DEKU_SHIELD);
    itemTable[HYLIAN_SHIELD]                     = Item(Text{"Hylian Shield",    "Bouclier Hylien",        "Escudo hyliano"},        ITEMTYPE_ITEM,  GI_SHIELD_HYLIAN,  false,      &noVariable,    HYLIAN_SHIELD);
    itemTable[MIRROR_SHIELD]                     = Item(Text{"Mirror Shield",    "Bouclier miroir",        "Escudo espejo"},         ITEMTYPE_ITEM,  GI_SHIELD_MIRROR,  true,       &MirrorShield,  MIRROR_SHIELD);
    itemTable[GORON_TUNIC]                       = Item(Text{"Goron Tunic",      "Tunique Goron",          "Sayo goron"},            ITEMTYPE_ITEM,  GI_TUNIC_GORON,    true,       &GoronTunic,    GORON_TUNIC);
    itemTable[ZORA_TUNIC]                        = Item(Text{"Zora Tunic",       "Tunique Zora",           "Sayo zora"},             ITEMTYPE_ITEM,  GI_TUNIC_ZORA,     true,       &ZoraTunic,     ZORA_TUNIC);
    itemTable[IRON_BOOTS]                        = Item(Text{"Iron Boots",       "Bottes de plomb",        "Botas de hierro"},       ITEMTYPE_ITEM,  GI_BOOTS_IRON,     true,       &IronBoots,     IRON_BOOTS);
    itemTable[HOVER_BOOTS]                       = Item(Text{"Hover Boots",      "Bottes des airs",        "Botas voladoras"},       ITEMTYPE_ITEM,  GI_BOOTS_HOVER,    true,       &HoverBoots,    HOVER_BOOTS);
    itemTable[WEIRD_EGG]                         = Item(Text{"Weird Egg",        "Oeuf curieux",           "Huevo extraño"},         ITEMTYPE_ITEM,  GI_WEIRD_EGG,      true,       &WeirdEgg,      WEIRD_EGG);
    itemTable[ZELDAS_LETTER]                     = Item(Text{"Zelda's Letter",   "",                       "Carta de Zelda"},        ITEMTYPE_ITEM,  GI_LETTER_ZELDA,   true,       &ZeldasLetter,  ZELDAS_LETTER);
    itemTable[BOOMERANG]                         = Item(Text{"Boomerang",        "Boomerang",              "Bumerán"},               ITEMTYPE_ITEM,  GI_BOOMERANG,      true,       &Boomerang,     BOOMERANG);
    itemTable[LENS_OF_TRUTH]                     = Item(Text{"Lens of Truth",    "Loupe de vérité",        "Lupa de la Verdad"},     ITEMTYPE_ITEM,  GI_LENS,           true,       &LensOfTruth,   LENS_OF_TRUTH);
    itemTable[MEGATON_HAMMER]                    = Item(Text{"Megaton Hammer",   "Masse des titans",       "Martillo Megatón"},      ITEMTYPE_ITEM,  GI_HAMMER,         true,       &Hammer,        MEGATON_HAMMER);
    itemTable[SHARD_OF_AGONY]                    = Item(Text{"Shard of Agony",   "Fragment de souffrance", "Piedra de la Agonía"},   ITEMTYPE_ITEM,  GI_STONE_OF_AGONY, true,       &ShardOfAgony,  SHARD_OF_AGONY);
    itemTable[DINS_FIRE]                         = Item(Text{"Din's Fire",       "Feu de Din",             "Fuego de Din"},          ITEMTYPE_ITEM,  GI_DINS_FIRE,      true,       &DinsFire,      DINS_FIRE);
    itemTable[FARORES_WIND]                      = Item(Text{"Farore's Wind",    "Vent de Farore",         "Viento de Farore"},      ITEMTYPE_ITEM,  GI_FARORES_WIND,   true,       &FaroresWind,   FARORES_WIND);
    itemTable[NAYRUS_LOVE]                       = Item(Text{"Nayru's Love",     "Amour de Nayru",         "Amor de Nayru"},         ITEMTYPE_ITEM,  GI_NAYRUS_LOVE,    true,       &NayrusLove,    NAYRUS_LOVE);
    itemTable[FIRE_ARROWS]                       = Item(Text{"Fire Arrows",      "Flèche de feu",          "Flecha de fuego"},       ITEMTYPE_ITEM,  GI_ARROW_FIRE,     true,       &FireArrows,    FIRE_ARROWS);
    itemTable[ICE_ARROWS]                        = Item(Text{"Ice Arrows",       "Flèche de glace",        "Flecha de hielo"},       ITEMTYPE_ITEM,  GI_ARROW_ICE,      true,       &IceArrows,     ICE_ARROWS);
    itemTable[LIGHT_ARROWS]                      = Item(Text{"Light Arrows",     "Flèche de lumière",      "Flecha de luz"},         ITEMTYPE_ITEM,  GI_ARROW_LIGHT,    true,       &LightArrows,   LIGHT_ARROWS);
    itemTable[GERUDO_TOKEN]                      = Item(Text{"Gerudo Token",     "Carte Gerudo",           "Pase de socio gerudo"},  ITEMTYPE_ITEM,  GI_GERUDO_CARD,    true,       &GerudoToken,   GERUDO_TOKEN);
    itemTable[MAGIC_BEAN]                        = Item(Text{"Magic Bean",       "Haricot magique",        "Habichuelas mágicas"},   ITEMTYPE_ITEM,  GI_BEAN,           true,       &MagicBean,     MAGIC_BEAN);
    itemTable[MAGIC_BEAN_PACK]                   = Item(Text{"Magic Bean Pack",  "Haricot magique",        "Habichuelas mágicas"},   ITEMTYPE_ITEM,  0xC9,              true,       &MagicBeanPack, MAGIC_BEAN_PACK);
    itemTable[DOUBLE_DEFENSE]                    = Item(Text{"Double Defense",   "Double défence",         "Doble poder defensivo"}, ITEMTYPE_ITEM,  0xB8,              true,       &noVariable,    DOUBLE_DEFENSE);

    itemTable[POCKET_EGG]                        = Item(Text{"Pocket Egg",   "",           "Huevo de bolsillo"},     ITEMTYPE_ITEM,  GI_POCKET_EGG,     true,       &PocketEgg,     POCKET_EGG);
    itemTable[POCKET_CUCCO]                      = Item(Text{"Pocket Cucco", "",           "Cuco de bolsillo"},      ITEMTYPE_ITEM,  GI_POCKET_CUCCO,   true,       &PocketCucco,   POCKET_CUCCO);
    itemTable[COJIRO]                            = Item(Text{"Cojiro",       "",           "Cojiro"},                ITEMTYPE_ITEM,  GI_COJIRO,         true,       &Cojiro,        COJIRO);
    itemTable[ODD_MUSHROOM]                      = Item(Text{"Odd Mushroom", "",           "Champiñón extraño"},     ITEMTYPE_ITEM,  GI_ODD_MUSHROOM,   true,       &OddMushroom,   ODD_MUSHROOM);
    itemTable[ODD_POULTICE]                      = Item(Text{"Odd Poultice", "",           "Medicina rara"},         ITEMTYPE_ITEM,  GI_ODD_POTION,     true,       &OddPoultice,   ODD_POULTICE);
    itemTable[POACHERS_SAW]                      = Item(Text{"Poachers Saw", "",           "Sierra del furtivo"},    ITEMTYPE_ITEM,  GI_SAW,            true,       &PoachersSaw,   POACHERS_SAW);
    itemTable[BROKEN_SWORD]                      = Item(Text{"Broken Sword", "",           "Espada goron rota"},     ITEMTYPE_ITEM,  GI_SWORD_BROKEN,   true,       &BrokenSword,   BROKEN_SWORD);
    itemTable[PRESCRIPTION]                      = Item(Text{"Prescription", "",           "Receta"},                ITEMTYPE_ITEM,  GI_PERSCRIPTION,   true,       &Prescription,  PRESCRIPTION);
    itemTable[EYEBALL_FROG]                      = Item(Text{"Eyeball Frog", "",           "Rana de ojos saltones"}, ITEMTYPE_ITEM,  GI_FROG,           true,       &EyeballFrog,   EYEBALL_FROG);
    itemTable[EYEDROPS]                          = Item(Text{"Eyedrops",     "",           "Supergotas oculares"},   ITEMTYPE_ITEM,  GI_EYEDROPS,       true,       &Eyedrops,      EYEDROPS);
    itemTable[CLAIM_CHECK]                       = Item(Text{"Claim Check",  "Certificat", "Recibo"},                ITEMTYPE_ITEM,  GI_CLAIM_CHECK,    true,       &ClaimCheck,    CLAIM_CHECK);

    itemTable[GOLD_SKULLTULA_TOKEN]              = Item(Text{"Gold Skulltula Token", "", "Símbolo de skulltula dorada"}, ITEMTYPE_TOKEN, GI_SKULL_TOKEN,    true,       &GoldSkulltulaTokens, GOLD_SKULLTULA_TOKEN);

    //Progression Items
    itemTable[PROGRESSIVE_HOOKSHOT]              = Item(Text{"Progressive Hookshot",      "Grappin progressif",            "Gancho progresivo"},                   ITEMTYPE_ITEM,     0x80, true,  &ProgressiveHookshot,  PROGRESSIVE_HOOKSHOT);
    itemTable[PROGRESSIVE_STRENGTH]              = Item(Text{"Progressive Strength",      "Bracelet de force progressif",  "Fuerza progresiva"},                   ITEMTYPE_ITEM,     0x81, true,  &ProgressiveStrength,  PROGRESSIVE_STRENGTH);
    itemTable[PROGRESSIVE_BOMB_BAG]              = Item(Text{"Progressive Bomb Bag",      "Sac de bombes progressif",      "Saco de bombas progresivo"},           ITEMTYPE_ITEM,     0x82, true,  &ProgressiveBombBag,   PROGRESSIVE_BOMB_BAG);
    itemTable[PROGRESSIVE_BOW]                   = Item(Text{"Progressive Bow",           "Carquois progressif",           "Carcaj progresivo"},                   ITEMTYPE_ITEM,     0x83, true,  &ProgressiveBow,       PROGRESSIVE_BOW);
    itemTable[PROGRESSIVE_SLINGSHOT]             = Item(Text{"Progressive Slingshot",     "Sac de graines progressif",     "Bolsa de semillas deku progresiva"},   ITEMTYPE_ITEM,     0x84, true,  &ProgressiveBulletBag, PROGRESSIVE_SLINGSHOT);
    itemTable[PROGRESSIVE_WALLET]                = Item(Text{"Progressive Wallet",        "Bourse progressive",            "Bolsa de rupias progresiva"},          ITEMTYPE_ITEM,     0x85, true,  &ProgressiveWallet,    PROGRESSIVE_WALLET);
    itemTable[PROGRESSIVE_SCALE]                 = Item(Text{"Progressive Scale",         "Écaille progressive",           "Escama progresiva"},                   ITEMTYPE_ITEM,     0x86, true,  &ProgressiveScale,     PROGRESSIVE_SCALE);
    itemTable[PROGRESSIVE_NUT_UPGRADE]           = Item(Text{"Progressive Nut Upgrade",   "Paquet de noix progressif",     "Capacidad de nueces deku progresiva"}, ITEMTYPE_ITEM,     0x87, false, &noVariable,           PROGRESSIVE_NUT_UPGRADE);
    itemTable[PROGRESSIVE_STICK_UPGRADE]         = Item(Text{"Progressive Stick Upgrade", "Paquet de bâtons progressif",   "Capacidad de palos deku progresiva"},  ITEMTYPE_ITEM,     0x88, false, &noVariable,           PROGRESSIVE_STICK_UPGRADE);
    itemTable[PROGRESSIVE_BOMBCHUS]              = Item(Text{"Progressive Bombchus",      "Paquet de Bombchus progressif", "Bombchus progresivos"},                ITEMTYPE_ITEM,     0x89, true,  &Bombchus,             PROGRESSIVE_BOMBCHUS);
    itemTable[PROGRESSIVE_MAGIC_METER]           = Item(Text{"Progressive Magic",         "Capacité magique progressive",  "Poder mágico progresivo"},             ITEMTYPE_ITEM,     0x8A, true,  &ProgressiveMagic,     PROGRESSIVE_MAGIC_METER);
    itemTable[PROGRESSIVE_OCARINA]               = Item(Text{"Progressive Ocarina",       "Ocarina progressif",            "Ocarina progresiva"},                  ITEMTYPE_ITEM,     0x8B, true,  &ProgressiveOcarina,   PROGRESSIVE_OCARINA);

    //Bottles
    itemTable[EMPTY_BOTTLE]                      = Item(Text{"Empty Bottle",             "Flacon vide",            "Botella vacía"},           ITEMTYPE_ITEM,     0x0F, true, &HasBottle, EMPTY_BOTTLE);
    itemTable[BOTTLE_WITH_MILK]                  = Item(Text{"Bottle with Milk",         "Flacon de lait",         "Botella de leche"},        ITEMTYPE_ITEM,     0x14, true, &HasBottle, BOTTLE_WITH_MILK);
    itemTable[BOTTLE_WITH_RED_POTION]            = Item(Text{"Bottle with Red Potion",   "Flacon de potion rouge", "Botella de poción roja"},  ITEMTYPE_ITEM,     0x8C, true, &HasBottle, BOTTLE_WITH_RED_POTION);
    itemTable[BOTTLE_WITH_GREEN_POTION]          = Item(Text{"Bottle with Green Potion", "Flacon de potion verte", "Botella de poción verde"}, ITEMTYPE_ITEM,     0x8D, true, &HasBottle, BOTTLE_WITH_GREEN_POTION);
    itemTable[BOTTLE_WITH_BLUE_POTION]           = Item(Text{"Bottle with Blue Potion",  "Flacon de potion bleue", "Botella de poción azul"},  ITEMTYPE_ITEM,     0x8E, true, &HasBottle, BOTTLE_WITH_BLUE_POTION);
    itemTable[BOTTLE_WITH_FAIRY]                 = Item(Text{"Bottle with Fairy",        "Flacon avec une fée",    "Hada en una botella"},     ITEMTYPE_ITEM,     0x8F, true, &HasBottle, BOTTLE_WITH_FAIRY);
    itemTable[BOTTLE_WITH_FISH]                  = Item(Text{"Bottle with Fish",         "Flacon avec un poisson", "Pez en una botella"},      ITEMTYPE_ITEM,     0x90, true, &HasBottle, BOTTLE_WITH_FISH);
    itemTable[BOTTLE_WITH_BLUE_FIRE]             = Item(Text{"Bottle with Blue Fire",    "Flacon de flamme bleue", "Botella de fuego azul"},   ITEMTYPE_ITEM,     0x91, true, &HasBottle, BOTTLE_WITH_BLUE_FIRE);
    itemTable[BOTTLE_WITH_BUGS]                  = Item(Text{"Bottle with Bugs",         "Flacon d'insectes",      "Insectos en una botella"}, ITEMTYPE_ITEM,     0x92, true, &HasBottle, BOTTLE_WITH_BUGS);
    itemTable[BOTTLE_WITH_POE]                   = Item(Text{"Bottle with Poe",          "Flacon avec un Esprit",  "Poe en una botella"},      ITEMTYPE_ITEM,     0x94, true, &HasBottle, BOTTLE_WITH_POE);

    //Special bottles that can't immediately dump contents
    itemTable[RUTOS_LETTER]                      = Item(Text{"Ruto's Letter",       "Flacon avec une lettre", "Carta de Ruto"},           ITEMTYPE_ITEM,     0x15, true, &RutosLetter,      RUTOS_LETTER);
    itemTable[BOTTLE_WITH_BIG_POE]               = Item(Text{"Bottle with Big Poe", "Flacon avec une Âme",    "Gran Poe en una botella"}, ITEMTYPE_ITEM,     0x93, true, &BottleWithBigPoe, BOTTLE_WITH_BIG_POE);

    //Songs
    itemTable[ZELDAS_LULLABY]                    = Item(Text{"Zelda's Lullaby",    "Berceuse de Zelda",     "Nana de Zelda"},          ITEMTYPE_SONG,     0xC1, true, &ZeldasLullaby,    ZELDAS_LULLABY);
    itemTable[EPONAS_SONG]                       = Item(Text{"Epona's Song",       "Chant d'Épona",         "Canción de Epona"},       ITEMTYPE_SONG,     0xC2, true, &EponasSong,       EPONAS_SONG);
    itemTable[SARIAS_SONG]                       = Item(Text{"Saria's Song",       "Chant de Saria",        "Canción de Saria"},       ITEMTYPE_SONG,     0xC3, true, &SariasSong,       SARIAS_SONG);
    itemTable[SUNS_SONG]                         = Item(Text{"Sun's Song",         "Chant du soleil",       "Canción del Sol"},        ITEMTYPE_SONG,     0xC4, true, &SunsSong,         SUNS_SONG);
    itemTable[SONG_OF_TIME]                      = Item(Text{"Song of Time",       "Chant du temps",        "Canción del tiempo"},     ITEMTYPE_SONG,     0xC5, true, &SongOfTime,       SONG_OF_TIME);
    itemTable[SONG_OF_STORMS]                    = Item(Text{"Song of Storms",     "Chant des tempêtes",    "Canción de la tormenta"}, ITEMTYPE_SONG,     0xC6, true, &SongOfStorms,     SONG_OF_STORMS);
    itemTable[MINUET_OF_FOREST]                  = Item(Text{"Minuet of Forest",   "Menuet de la forêt",    "Minueto del bosque"},     ITEMTYPE_SONG,     0xBB, true, &MinuetOfForest,   MINUET_OF_FOREST);
    itemTable[BOLERO_OF_FIRE]                    = Item(Text{"Bolero of Fire",     "Boléro du feu",         "Bolero del fuego"},       ITEMTYPE_SONG,     0xBC, true, &BoleroOfFire,     BOLERO_OF_FIRE);
    itemTable[SERENADE_OF_WATER]                 = Item(Text{"Serenade of Water",  "Sérénade de l'eau",     "Serenata del agua"},      ITEMTYPE_SONG,     0xBD, true, &SerenadeOfWater,  SERENADE_OF_WATER);
    itemTable[REQUIEM_OF_SPIRIT]                 = Item(Text{"Requiem of Spirit",  "Requiem des esprits",   "Réquiem del espíritu"},   ITEMTYPE_SONG,     0xBE, true, &RequiemOfSpirit,  REQUIEM_OF_SPIRIT);
    itemTable[NOCTURNE_OF_SHADOW]                = Item(Text{"Nocturne of Shadow", "Nocturne de l'ombre",   "Nocturno de la sombra"},  ITEMTYPE_SONG,     0xBF, true, &NocturneOfShadow, NOCTURNE_OF_SHADOW);
    itemTable[PRELUDE_OF_LIGHT]                  = Item(Text{"Prelude of Light",   "Prélude de la lumière", "Preludio de la luz"},     ITEMTYPE_SONG,     0xC0, true, &PreludeOfLight,   PRELUDE_OF_LIGHT);

    //Maps and Compasses
    itemTable[DEKU_TREE_MAP]                     = Item(Text{"Deku Tree Map",          "Carte de l'arbre Mojo",        "Mapa del Gran Árbol Deku"},         ITEMTYPE_MAP,      0xA5, false, &noVariable, MAP);
    itemTable[DODONGOS_CAVERN_MAP]               = Item(Text{"Dodongo's Cavern Map",   "Carte de la caverne Dodongo",  "Mapa de la cueva de los Dodongos"}, ITEMTYPE_MAP,      0xA6, false, &noVariable, MAP);
    itemTable[JABU_JABUS_BELLY_MAP]              = Item(Text{"Jabu Jabu's Belly Map",  "Carte du ventre de Jabu-Jabu", "Mapa de la tripa de Jabu-Jabu"},    ITEMTYPE_MAP,      0xA7, false, &noVariable, MAP);
    itemTable[FOREST_TEMPLE_MAP]                 = Item(Text{"Forest Temple Map",      "Carte du temple de la forêt",  "Mapa del Templo del Bosque"},       ITEMTYPE_MAP,      0xA8, false, &noVariable, MAP);
    itemTable[FIRE_TEMPLE_MAP]                   = Item(Text{"Fire Temple Map",        "Carte du temple du feu",       "Mapa del Templo del Fuego"},        ITEMTYPE_MAP,      0xA9, false, &noVariable, MAP);
    itemTable[WATER_TEMPLE_MAP]                  = Item(Text{"Water Temple Map",       "Carte du temple de l'eau",     "Mapa del Templo del Agua"},         ITEMTYPE_MAP,      0xAA, false, &noVariable, MAP);
    itemTable[SPIRIT_TEMPLE_MAP]                 = Item(Text{"Spirit Temple Map",      "Carte du temple de l'esprit",  "Mapa del Templo del Espíritu"},     ITEMTYPE_MAP,      0xAB, false, &noVariable, MAP);
    itemTable[SHADOW_TEMPLE_MAP]                 = Item(Text{"Shadow Temple Map",      "Carte du temple de l'ombre",   "Mapa del Templo de las Sombras"},   ITEMTYPE_MAP,      0xAC, false, &noVariable, MAP);
    itemTable[BOTTOM_OF_THE_WELL_MAP]            = Item(Text{"Bottom of the Well Map", "Carte du fond du puits",       "Mapa del fondo del pozo"},          ITEMTYPE_MAP,      0xAD, false, &noVariable, MAP);
    itemTable[ICE_CAVERN_MAP]                    = Item(Text{"Ice Cavern Map",         "Carte de la caverne polaire",  "Mapa de la caverna de hielo"},      ITEMTYPE_MAP,      0xAE, false, &noVariable, MAP);

    itemTable[DEKU_TREE_COMPASS]                 = Item(Text{"Deku Tree Compass",          "Boussole de l'arbre Mojo",        "Brújula del Gran Árbol Deku"},         ITEMTYPE_COMPASS,  0x9B, false, &noVariable, COMPASS);
    itemTable[DODONGOS_CAVERN_COMPASS]           = Item(Text{"Dodongo's Cavern Compass",   "Boussole de la caverne Dodongo",  "Brújula de la cueva de los Dodongos"}, ITEMTYPE_COMPASS,  0x9C, false, &noVariable, COMPASS);
    itemTable[JABU_JABUS_BELLY_COMPASS]          = Item(Text{"Jabu Jabu's Belly Compass",  "Boussole du ventre de Jabu-Jabu", "Brújula de la tripa de Jabu-Jabu"},    ITEMTYPE_COMPASS,  0x9D, false, &noVariable, COMPASS);
    itemTable[FOREST_TEMPLE_COMPASS]             = Item(Text{"Forest Temple Compass",      "Boussole du temple de la forêt",  "Brújula del Templo del Bosque"},       ITEMTYPE_COMPASS,  0x9E, false, &noVariable, COMPASS);
    itemTable[FIRE_TEMPLE_COMPASS]               = Item(Text{"Fire Temple Compass",        "Boussole du temple du feu",       "Brújula del Templo del Fuego"},        ITEMTYPE_COMPASS,  0x9F, false, &noVariable, COMPASS);
    itemTable[WATER_TEMPLE_COMPASS]              = Item(Text{"Water Temple Compass",       "Boussole du temple de l'eau",     "Brújula del Templo del Agua"},         ITEMTYPE_COMPASS,  0xA0, false, &noVariable, COMPASS);
    itemTable[SPIRIT_TEMPLE_COMPASS]             = Item(Text{"Spirit Temple Compass",      "Boussole du temple de l'esprit",  "Brújula del Templo del Espíritu"},     ITEMTYPE_COMPASS,  0xA1, false, &noVariable, COMPASS);
    itemTable[SHADOW_TEMPLE_COMPASS]             = Item(Text{"Shadow Temple Compass",      "Boussole du temple de l'ombre",   "Brújula del Templo de las Sombras"},   ITEMTYPE_COMPASS,  0xA2, false, &noVariable, COMPASS);
    itemTable[BOTTOM_OF_THE_WELL_COMPASS]        = Item(Text{"Bottom of the Well Compass", "Boussole du fond du puits",       "Brújula del fondo del pozo"},          ITEMTYPE_COMPASS,  0xA3, false, &noVariable, COMPASS);
    itemTable[ICE_CAVERN_COMPASS]                = Item(Text{"Ice Cavern Compass",         "Boussole de la caverne polaire",  "Brújula de la caverna de hielo"},      ITEMTYPE_COMPASS,  0xA4, false, &noVariable, COMPASS);

    //Boss Keys
    itemTable[FOREST_TEMPLE_BOSS_KEY]            = Item(Text{"Forest Temple Boss Key",  "Clé d'or du temple de la forêt", "Gran llave del Templo del Bosque"},     ITEMTYPE_BOSSKEY,  0x95, true, &BossKeyForestTemple, BOSS_KEY);
    itemTable[FIRE_TEMPLE_BOSS_KEY]              = Item(Text{"Fire Temple Boss Key",    "Clé d'or du temple du feu",      "Gran llave del Templo del Fuego"},      ITEMTYPE_BOSSKEY,  0x96, true, &BossKeyFireTemple,   BOSS_KEY);
    itemTable[WATER_TEMPLE_BOSS_KEY]             = Item(Text{"Water Temple Boss Key",   "Clé d'or du temple de l'eau",    "Gran llave del Templo del Agua"},       ITEMTYPE_BOSSKEY,  0x97, true, &BossKeyWaterTemple,  BOSS_KEY);
    itemTable[SPIRIT_TEMPLE_BOSS_KEY]            = Item(Text{"Spirit Temple Boss Key",  "Clé d'or du temple de l'esprit", "Gran llave del Templo del Espíritu"},   ITEMTYPE_BOSSKEY,  0x98, true, &BossKeySpiritTemple, BOSS_KEY);
    itemTable[SHADOW_TEMPLE_BOSS_KEY]            = Item(Text{"Shadow Temple Boss Key",  "Clé d'or du temple de l'ombre",  "Gran llave del Templo de las Sombras"}, ITEMTYPE_BOSSKEY,  0x99, true, &BossKeyShadowTemple, BOSS_KEY);
    itemTable[GANONS_CASTLE_BOSS_KEY]            = Item(Text{"Ganon's Castle Boss Key", "Clé d'or du château de Ganon",   "Gran llave del Castillo de Ganon"},     ITEMTYPE_BOSSKEY,  0x9A, true, &BossKeyGanonsCastle, GANONS_CASTLE_BOSS_KEY);

    //Small Keys
    itemTable[FOREST_TEMPLE_SMALL_KEY]           = Item(Text{"Forest Temple Small Key",           "Petite clé du temple de la forêt",   "Llave pequeña del Templo del Bosque"},            ITEMTYPE_SMALLKEY,          0xAF, true, &ForestTempleKeys,          SMALL_KEY);
    itemTable[FIRE_TEMPLE_SMALL_KEY]             = Item(Text{"Fire Temple Small Key",             "Petite clé du temple du feu",        "Llave pequeña del Templo del Fuego"},             ITEMTYPE_SMALLKEY,          0xB0, true, &FireTempleKeys,            SMALL_KEY);
    itemTable[WATER_TEMPLE_SMALL_KEY]            = Item(Text{"Water Temple Small Key",            "Petite clé du temple de l'eau",      "Llave pequeña del Templo del Agua"},              ITEMTYPE_SMALLKEY,          0xB1, true, &WaterTempleKeys,           SMALL_KEY);
    itemTable[SPIRIT_TEMPLE_SMALL_KEY]           = Item(Text{"Spirit Temple Small Key",           "Petite clé du temple de l'esprit",   "Llave pequeña del Templo del Espíritu"},          ITEMTYPE_SMALLKEY,          0xB2, true, &SpiritTempleKeys,          SMALL_KEY);
    itemTable[SHADOW_TEMPLE_SMALL_KEY]           = Item(Text{"Shadow Temple Small Key",           "Petite clé du temple de l'ombre",    "Llave pequeña del Templo de la Sombras"},         ITEMTYPE_SMALLKEY,          0xB3, true, &ShadowTempleKeys,          SMALL_KEY);
    itemTable[BOTTOM_OF_THE_WELL_SMALL_KEY]      = Item(Text{"Bottom of the Well Small Key",      "Petite clé du fond du puits",        "Llave pequeña del fondo del pozo"},               ITEMTYPE_SMALLKEY,          0xB4, true, &BottomOfTheWellKeys,       SMALL_KEY);
    itemTable[GERUDO_TRAINING_GROUNDS_SMALL_KEY] = Item(Text{"Gerudo Training Grounds Small Key", "Petite clé du gymnase Gerudo",       "Llave del Centro de Instrucción Gerudo"}, ITEMTYPE_SMALLKEY,          0xB5, true, &GerudoTrainingGroundsKeys, SMALL_KEY);
    itemTable[GERUDO_FORTRESS_SMALL_KEY]         = Item(Text{"Gerudo Fortress Small Key",         "Petite clé de la forteresse Gerudo", "Llave pequeña de la Fortaleza Gerudo"},           ITEMTYPE_FORTRESS_SMALLKEY, 0xB6, true, &GerudoFortressKeys,        GERUDO_FORTRESS_SMALL_KEY);
    itemTable[GANONS_CASTLE_SMALL_KEY]           = Item(Text{"Ganon's Castle Small Key",          "Petite clé du château de Ganon",     "Llave pequeña del Castillo de Ganon"},            ITEMTYPE_SMALLKEY,          0xB7, true, &GanonsCastleKeys,          SMALL_KEY);

    //Stones and Medallions
    itemTable[KOKIRI_EMERALD]                    = Item(Text{"Kokiri's Emerald", "Émeraude Kokiri",         "Esmeralda de los Kokiri"}, ITEMTYPE_DUNGEONREWARD, 0xCB,  true, &KokiriEmerald,   KOKIRI_EMERALD);
    itemTable[GORON_RUBY]                        = Item(Text{"Goron's Ruby",     "Rubis Goron",             "Rubí de los Goron"},       ITEMTYPE_DUNGEONREWARD, 0xCC,  true, &GoronRuby,       GORON_RUBY);
    itemTable[ZORA_SAPPHIRE]                     = Item(Text{"Zora's Sapphire",  "Saphir Zora",             "Zafiro de los Zora"},      ITEMTYPE_DUNGEONREWARD, 0xCD,  true, &ZoraSapphire,    ZORA_SAPPHIRE);
    itemTable[FOREST_MEDALLION]                  = Item(Text{"Forest Medallion", "Médaillon de la forêt",   "Medallón del Bosque"},     ITEMTYPE_DUNGEONREWARD, 0xCE,  true, &ForestMedallion, FOREST_MEDALLION);
    itemTable[FIRE_MEDALLION]                    = Item(Text{"Fire Medallion",   "Médaillon du feu",        "Medallón del Fuego"},      ITEMTYPE_DUNGEONREWARD, 0xCF,  true, &FireMedallion,   FIRE_MEDALLION);
    itemTable[WATER_MEDALLION]                   = Item(Text{"Water Medallion",  "Médaillon de l'eau",      "Medallón del Agua"},       ITEMTYPE_DUNGEONREWARD, 0xD0,  true, &WaterMedallion,  WATER_MEDALLION);
    itemTable[SPIRIT_MEDALLION]                  = Item(Text{"Spirit Medallion", "Médaillon de l'esprit",   "Medallón del Espíritu"},   ITEMTYPE_DUNGEONREWARD, 0xD1,  true, &SpiritMedallion, SPIRIT_MEDALLION);
    itemTable[SHADOW_MEDALLION]                  = Item(Text{"Shadow Medallion", "Médaillon de l'ombre",    "Medallón de la Sombra"},   ITEMTYPE_DUNGEONREWARD, 0xD2,  true, &ShadowMedallion, SHADOW_MEDALLION);
    itemTable[LIGHT_MEDALLION]                   = Item(Text{"Light Medallion",  "Médaillon de la lumière", "Medallón de la Luz"},      ITEMTYPE_DUNGEONREWARD, 0xD3,  true, &LightMedallion,  LIGHT_MEDALLION);

    //Generic Items
    itemTable[RECOVERY_HEART]                    = Item(Text{"Recovery Heart",  "Cœur d'énergie",      "Corazón"},               ITEMTYPE_ITEM, GI_HEART,             false, &noVariable, RECOVERY_HEART);
    itemTable[GREEN_RUPEE]                       = Item(Text{"Green Rupee",     "Rubis vert",          "Rupia verde"},           ITEMTYPE_ITEM, GI_RUPEE_GREEN,       false, &noVariable, GREEN_RUPEE);
    itemTable[BLUE_RUPEE]                        = Item(Text{"Blue Rupee",      "Rubis bleu",          "Rupia azul"},            ITEMTYPE_ITEM, GI_RUPEE_BLUE,        false, &noVariable, BLUE_RUPEE);
    itemTable[RED_RUPEE]                         = Item(Text{"Red Rupee",       "Rubis rouge",         "Rupia roja"},            ITEMTYPE_ITEM, GI_RUPEE_RED,         false, &noVariable, RED_RUPEE);
    itemTable[PURPLE_RUPEE]                      = Item(Text{"Purple Rupee",    "Rubis pourpre",       "Rupia morada"},          ITEMTYPE_ITEM, GI_RUPEE_PURPLE,      false, &noVariable, PURPLE_RUPEE);
    itemTable[HUGE_RUPEE]                        = Item(Text{"Huge Rupee",      "Rubis géant",         "Rupia gigante"},         ITEMTYPE_ITEM, GI_RUPEE_GOLD,        false, &noVariable, HUGE_RUPEE);
    itemTable[PIECE_OF_HEART]                    = Item(Text{"Piece of Heart",  "Quart de coeur",      "Pieza de corazón"},      ITEMTYPE_ITEM, GI_HEART_PIECE,       false, &noVariable, PIECE_OF_HEART);
    itemTable[HEART_CONTAINER]                   = Item(Text{"Heart Container", "Réceptacle de coeur", "Contenedor de corazón"}, ITEMTYPE_ITEM, GI_HEART_CONTAINER_2, false, &noVariable, HEART_CONTAINER);
    itemTable[ICE_TRAP]                          = Item(Text{"Ice Trap",        "Piège de glace",      "Trampa de hielo"},       ITEMTYPE_ITEM, GI_ICE_TRAP,          false, &noVariable, ICE_TRAP);
    itemTable[MILK]                              = Item(Text{"Milk",            "Lait",                "Leche Lon Lon"},         ITEMTYPE_ITEM, GI_MILK,              false, &noVariable, NONE);

    //Refills
    itemTable[BOMBS_5]                           = Item(Text{"Bombs (5)",           "Bombes (5)",        "Bombas (5)"},              ITEMTYPE_REFILL, GI_BOMBS_5,        false, &noVariable,  BOMBS_5);
    itemTable[BOMBS_10]                          = Item(Text{"Bombs (10)",          "Bombes (10)",       "Bombas (10)"},             ITEMTYPE_REFILL, GI_BOMBS_10,       false, &noVariable,  BOMBS_10);
    itemTable[BOMBS_20]                          = Item(Text{"Bombs (20)",          "Bombes (20)",       "Bombas (20)"},             ITEMTYPE_REFILL, GI_BOMBS_20,       false, &noVariable,  BOMBS_20);
    itemTable[BOMBCHU_5]                         = Item(Text{"Bombchu (5)",         "Bombchus (5)",      "Bombchus (5)"},            ITEMTYPE_REFILL, GI_BOMBCHUS_5,     true,  &Bombchus5,   BOMBCHU_5);
    itemTable[BOMBCHU_10]                        = Item(Text{"Bombchu (10)",        "Bombchus (10)",     "Bombchus (10)"},           ITEMTYPE_REFILL, GI_BOMBCHUS_10,    true,  &Bombchus10,  BOMBCHU_10);
    itemTable[BOMBCHU_20]                        = Item(Text{"Bombchu (20)",        "Bombchus (20)",     "Bombchus (20)"},           ITEMTYPE_REFILL, GI_BOMBCHUS_20,    true,  &Bombchus20,  BOMBCHU_20);
    itemTable[BOMBCHU_DROP]                      = Item(Text{"Bombchu Drop",        "Bombchus",          "Bombchus"},                ITEMTYPE_DROP,   GI_BOMBCHUS_10,    true,  &BombchuDrop, NONE);
    itemTable[ARROWS_5]                          = Item(Text{"Arrows (5)",          "Flèches (5)",       "Flechas (5)"},             ITEMTYPE_REFILL, GI_ARROWS_SMALL,   false, &noVariable,  ARROWS_5);
    itemTable[ARROWS_10]                         = Item(Text{"Arrows (10)",         "Flèches (10)",      "Flechas (10)"},            ITEMTYPE_REFILL, GI_ARROWS_MEDIUM,  false, &noVariable,  ARROWS_10);
    itemTable[ARROWS_30]                         = Item(Text{"Arrows (30)",         "Flèches (30)",      "Flechas (30)"},            ITEMTYPE_REFILL, GI_ARROWS_LARGE,   false, &noVariable,  ARROWS_30);
    itemTable[DEKU_NUTS_5]                       = Item(Text{"Deku Nuts (5)",       "Noix Mojo (5)",     "Nueces deku (5)"},         ITEMTYPE_REFILL, GI_NUTS_5,         false, &noVariable,  DEKU_NUTS_5);
    itemTable[DEKU_NUTS_10]                      = Item(Text{"Deku Nuts (10)",      "Noix Mojo (10)",    "Nueces deku (10)"},        ITEMTYPE_REFILL, GI_NUTS_10,        false, &noVariable,  DEKU_NUTS_10);
    itemTable[DEKU_SEEDS_30]                     = Item(Text{"Deku Seeds (30)",     "Graines Mojo (30)", "Semillas deku (30)"},      ITEMTYPE_REFILL, GI_SEEDS_30,       false, &noVariable,  DEKU_SEEDS_30);
    itemTable[DEKU_STICK_1]                      = Item(Text{"Deku Stick (1)",      "Bâton Mojo (1)",    "Palo deku (1)"},           ITEMTYPE_REFILL, GI_STICKS_1,       false, &noVariable,  DEKU_STICK_1);
    itemTable[RED_POTION_REFILL]                 = Item(Text{"Red Potion Refill",   "Potion rouge",      "Recarga de poción roja"},  ITEMTYPE_REFILL, GI_POTION_RED,     false, &noVariable,  NONE);
    itemTable[GREEN_POTION_REFILL]               = Item(Text{"Green Potion Refill", "Potion verte",      "Recarga de poción verde"}, ITEMTYPE_REFILL, GI_POTION_GREEN,   false, &noVariable,  NONE);
    itemTable[BLUE_POTION_REFILL]                = Item(Text{"Blue Potion Refill",  "Potion bleue",      "Recarga de poción azul"},  ITEMTYPE_REFILL, GI_POTION_BLUE,    false, &noVariable,  NONE);

    //Treasure Game
    itemTable[TREASURE_GAME_HEART]               = Item(Text{"Piece of Heart (Treasure Chest Minigame)", "Quart de cœur (Chasse-aux-trésors)", "Pieza de corazón (Cofre del Tesoro)"}, ITEMTYPE_ITEM, GI_HEART_PIECE_WIN,  false, &noVariable, TREASURE_GAME_HEART);
    itemTable[TREASURE_GAME_GREEN_RUPEE]         = Item(Text{"Green Rupee (Treasure Chest Minigame)",    "Rubis vert (Chasse-aux-trésors)",    "Rupia Verde (Cofre del Tesoro)"},      ITEMTYPE_ITEM, GI_RUPEE_GREEN_LOSE, false, &noVariable, TREASURE_GAME_GREEN_RUPEE);

    //Shop Items                                                                                                                                                                                                       price
    itemTable[BUY_DEKU_NUT_5]                    = Item(Text{"Buy Deku Nut (5)",    "Acheter: Noix Mojo (5)",      "Comprar nueces deku (5)"},    ITEMTYPE_SHOP, 0x00, true,  &Nuts,           DEKU_NUTS_5,            15);
    itemTable[BUY_ARROWS_30]                     = Item(Text{"Buy Arrows (30)",     "Acheter: Flèches (30)",       "Comprar flechas (30)"},       ITEMTYPE_SHOP, 0x01, false, &noVariable,     ARROWS_30,              60);
    itemTable[BUY_ARROWS_50]                     = Item(Text{"Buy Arrows (50)",     "Acheter: Flèches (50)",       "Comprar flechas (50)"},       ITEMTYPE_SHOP, 0x02, false, &noVariable,     ARROWS_30,              90);
    itemTable[BUY_BOMBS_525]                     = Item(Text{"Buy Bombs (5) [25]",  "Acheter: Bombes (5) [25]",    "Comprar bombas (5) [25]"},    ITEMTYPE_SHOP, 0x03, false, &noVariable,     BOMBS_5,                25);
    itemTable[BUY_DEKU_NUT_10]                   = Item(Text{"Buy Deku Nut (10)",   "Acheter: Noix Mojo (10)",     "Comprar Nueces deku (10)"},   ITEMTYPE_SHOP, 0x04, true,  &Nuts,           DEKU_NUTS_10,           30);
    itemTable[BUY_DEKU_STICK_1]                  = Item(Text{"Buy Deku Stick (1)",  "Acheter: Bâton Mojo (1)",     "Comprar palos deku (1)"},     ITEMTYPE_SHOP, 0x05, true,  &Sticks,         DEKU_STICK_1,           10);
    itemTable[BUY_BOMBS_10]                      = Item(Text{"Buy Bombs (10)",      "Acheter: Bombes (10)",        "Comprar Bombas (10)"},        ITEMTYPE_SHOP, 0x06, false, &noVariable,     BOMBS_10,               50);
    itemTable[BUY_FISH]                          = Item(Text{"Buy Fish",            "Acheter: Poisson",            "Comprar pez"},                ITEMTYPE_SHOP, 0x07, true,  &FishAccess,     BOTTLE_WITH_FISH,      200);
    itemTable[BUY_RED_POTION_30]                 = Item(Text{"Buy Red Potion [30]", "Acheter: Potion rouge [30]",  "Comprar poción roja [30]"},   ITEMTYPE_SHOP, 0x08, false, &noVariable,     NONE,                   30);
    itemTable[BUY_GREEN_POTION]                  = Item(Text{"Buy Green Potion",    "Acheter: Potion verte",       "Comprar poción verde"},       ITEMTYPE_SHOP, 0x09, false, &noVariable,     NONE,                   30);
    itemTable[BUY_BLUE_POTION]                   = Item(Text{"Buy Blue Potion",     "Acheter: Potion bleue",       "Comprar poción azul"},        ITEMTYPE_SHOP, 0x0A, false, &noVariable,     NONE,                  100);
    itemTable[BUY_HYLIAN_SHIELD]                 = Item(Text{"Buy Hylian Shield",   "Acheter: Bouclier Hylien",    "Comprar escudo hyliano"},     ITEMTYPE_SHOP, 0x0C, true,  &HylianShield,   HYLIAN_SHIELD,          80);
    itemTable[BUY_DEKU_SHIELD]                   = Item(Text{"Buy Deku Shield",     "Acheter: Bouclier Mojo",      "Comprar escudo deku"},        ITEMTYPE_SHOP, 0x0D, true,  &DekuShield,     DEKU_SHIELD,            40);
    itemTable[BUY_GORON_TUNIC]                   = Item(Text{"Buy Goron Tunic",     "Acheter: Tunique Goron",      "Comprar sayo goron"},         ITEMTYPE_SHOP, 0x0E, true,  &GoronTunic,     GORON_TUNIC,           200);
    itemTable[BUY_ZORA_TUNIC]                    = Item(Text{"Buy Zora Tunic",      "Acheter: Tunique Zora",       "Comprar sayo zora"},          ITEMTYPE_SHOP, 0x0F, true,  &ZoraTunic,      ZORA_TUNIC,            300);
    itemTable[BUY_HEART]                         = Item(Text{"Buy Heart",           "Acheter: Coeur d'énergie",    "Comprar corazón"},            ITEMTYPE_SHOP, 0x10, false, &noVariable,     RECOVERY_HEART,         10);
    itemTable[BUY_BOMBCHU_10]                    = Item(Text{"Buy Bombchu (10)",    "Acheter: Bombchus (10)",      "Comprar bombchus (10)"},      ITEMTYPE_SHOP, 0x15, true,  &BuyBombchus10,  BOMBCHU_10,             99);
    itemTable[BUY_BOMBCHU_20]                    = Item(Text{"Buy Bombchu (20)",    "Acheter: Bombchus (20)",      "Comprar bombchus (20)"},      ITEMTYPE_SHOP, 0x16, true,  &BuyBombchus20,  BOMBCHU_20,            180);
    itemTable[BUY_BOMBCHU_5]                     = Item(Text{"Buy Bombchu (5)",     "Acheter: Bombchus (5)",       "Comprar bombchus (5)"},       ITEMTYPE_SHOP, 0x18, true,  &BuyBombchus5,   BOMBCHU_5,              60);
    itemTable[BUY_DEKU_SEEDS_30]                 = Item(Text{"Buy Deku Seeds (30)", "Acheter: Graines Mojo (30)",  "Comprar semillas deku (30)"}, ITEMTYPE_SHOP, 0x1D, false, &noVariable,     DEKU_SEEDS_30,          30);
    itemTable[SOLD_OUT]                          = Item(Text{"Sold Out",            "Vendu",                       "Vendido"},                    ITEMTYPE_SHOP, 0x26, false, &noVariable,     NONE,                    0);
    itemTable[BUY_BLUE_FIRE]                     = Item(Text{"Buy Blue Fire",       "Acheter: Flamme bleue",       "Comprar fuego azul"},         ITEMTYPE_SHOP, 0x27, true,  &BlueFireAccess, BOTTLE_WITH_BLUE_FIRE, 300);
    itemTable[BUY_BOTTLE_BUG]                    = Item(Text{"Buy Bottle Bug",      "Acheter: Insectes en flacon", "Comprar bichos"},             ITEMTYPE_SHOP, 0x28, true,  &BugsAccess,     BOTTLE_WITH_BUGS,       50);
    itemTable[BUY_POE]                           = Item(Text{"Buy Poe",             "Acheter: Esprit",             "Comprar Poe"},                ITEMTYPE_SHOP, 0x2A, false, &noVariable,     BOTTLE_WITH_BIG_POE,    30);
    itemTable[BUY_FAIRYS_SPIRIT]                 = Item(Text{"Buy Fairy's Spirit",  "Acheter: Fée",                "Comprar hada"},               ITEMTYPE_SHOP, 0x2B, true,  &FairyAccess,    BOTTLE_WITH_FAIRY,      50);
    itemTable[BUY_ARROWS_10]                     = Item(Text{"Buy Arrows (10)",     "Acheter: Flèches (10)",       "Comprar flechas (10)"},       ITEMTYPE_SHOP, 0x2C, false, &noVariable,     ARROWS_10,              20);
    itemTable[BUY_BOMBS_20]                      = Item(Text{"Buy Bombs (20)",      "Acheter: Flèches (20)",       "Comprar bombas (20)"},        ITEMTYPE_SHOP, 0x2D, false, &noVariable,     BOMBS_20,               80);
    itemTable[BUY_BOMBS_30]                      = Item(Text{"Buy Bombs (30)",      "Acheter: Flèches (30)",       "Comprar bombas (30)"},        ITEMTYPE_SHOP, 0x2E, false, &noVariable,     BOMBS_20,              120);
    itemTable[BUY_BOMBS_535]                     = Item(Text{"Buy Bombs (5) [35]",  "Acheter: Bombes (5) [35]",    "Comprar bombas (5) [35]"},    ITEMTYPE_SHOP, 0x2F, false, &noVariable,     BOMBS_5,                35);
    itemTable[BUY_RED_POTION_40]                 = Item(Text{"Buy Red Potion [40]", "Acheter: Potion rouge [40]",  "Comprar poción roja [40]"},   ITEMTYPE_SHOP, 0x30, false, &noVariable,     NONE,                   40);
    itemTable[BUY_RED_POTION_50]                 = Item(Text{"Buy Red Potion [50]", "Acheter: Potion rouge [50]",  "Comprar poción roja [50]"},   ITEMTYPE_SHOP, 0x31, false, &noVariable,     NONE,                   50);

    itemTable[TRIFORCE]                          = Item(Text{"Triforce", "Triforce", "Trifuerza"}, ITEMTYPE_EVENT, GI_RUPEE_RED_LOSE,  false, &noVariable, NONE);
    itemTable[HINT]                              = Item(Text{"Hint",     "Indice",   "Pista"},     ITEMTYPE_EVENT, GI_RUPEE_BLUE_LOSE, false, &noVariable, NONE);
}

Item& ItemTable(const ItemKey itemKey) {
    return itemTable[itemKey];
}

//This function should only be used to place items containing hint text
//at gossip stone locations.
void NewItem(const ItemKey itemKey, const Item item) {
    if (itemKey <= BUY_RED_POTION_50) {
      printf("\x1b[25;0HWARNING: ATTEMPTED TO OVERWRITE ITEM %lu\n", itemKey);
      return;
    }

    itemTable[itemKey] = item;
}
