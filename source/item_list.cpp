#include "item_list.hpp"

#include "logic.hpp"
#include "keys.hpp"
#include "settings.hpp"
#include "../code/include/z3D/z3Ditem.h"
#include <vector>
#include <array>

using namespace Logic;
using namespace Settings;

static std::array<Item, KEY_ENUM_MAX> itemTable;

void ItemTable_Init() {                               //Name                    Item Type       getItemID          advancement logic           hint key
    itemTable[NONE]                              = Item("No Item",              ITEMTYPE_EVENT, GI_RUPEE_GREEN,    false,      &noVariable,    NONE);
    itemTable[KOKIRI_SWORD]                      = Item("Kokiri Sword",         ITEMTYPE_ITEM,  GI_SWORD_KOKIRI,   true,       &KokiriSword,   KOKIRI_SWORD);
  //[MASTER_SWORD]
  //[GIANTS_KNIFE]
    itemTable[BIGGORON_SWORD]                    = Item("Biggoron Sword",       ITEMTYPE_ITEM,  GI_SWORD_BGS,      true,       &noVariable,    BIGGORON_SWORD);
    itemTable[DEKU_SHIELD]                       = Item("Deku Shield",          ITEMTYPE_ITEM,  GI_SHIELD_DEKU,    false,      &noVariable,    DEKU_SHIELD);
    itemTable[HYLIAN_SHIELD]                     = Item("Hylian Shield",        ITEMTYPE_ITEM,  GI_SHIELD_HYLIAN,  false,      &noVariable,    HYLIAN_SHIELD);
    itemTable[MIRROR_SHIELD]                     = Item("Mirror Shield",        ITEMTYPE_ITEM,  GI_SHIELD_MIRROR,  true,       &MirrorShield,  MIRROR_SHIELD);
    itemTable[GORON_TUNIC]                       = Item("Goron Tunic",          ITEMTYPE_ITEM,  GI_TUNIC_GORON,    true,       &GoronTunic,    GORON_TUNIC);
    itemTable[ZORA_TUNIC]                        = Item("Zora Tunic",           ITEMTYPE_ITEM,  GI_TUNIC_ZORA,     true,       &ZoraTunic,     ZORA_TUNIC);
    itemTable[IRON_BOOTS]                        = Item("Iron Boots",           ITEMTYPE_ITEM,  GI_BOOTS_IRON,     true,       &IronBoots,     IRON_BOOTS);
    itemTable[HOVER_BOOTS]                       = Item("Hover Boots",          ITEMTYPE_ITEM,  GI_BOOTS_HOVER,    true,       &HoverBoots,    HOVER_BOOTS);
    itemTable[WEIRD_EGG]                         = Item("Weird Egg",            ITEMTYPE_ITEM,  GI_WEIRD_EGG,      true,       &WeirdEgg,      WEIRD_EGG);
    itemTable[ZELDAS_LETTER]                     = Item("Zelda's Letter",       ITEMTYPE_ITEM,  GI_LETTER_ZELDA,   true,       &ZeldasLetter,  ZELDAS_LETTER);
    itemTable[BOOMERANG]                         = Item("Boomerang",            ITEMTYPE_ITEM,  GI_BOOMERANG,      true,       &Boomerang,     BOOMERANG);
    itemTable[LENS_OF_TRUTH]                     = Item("Lens of Truth",        ITEMTYPE_ITEM,  GI_LENS,           true,       &LensOfTruth,   LENS_OF_TRUTH);
    itemTable[MEGATON_HAMMER]                    = Item("Megaton Hammer",       ITEMTYPE_ITEM,  GI_HAMMER,         true,       &Hammer,        MEGATON_HAMMER);
    itemTable[SHARD_OF_AGONY]                    = Item("Shard of Agony",       ITEMTYPE_ITEM,  GI_STONE_OF_AGONY, true,       &ShardOfAgony,  SHARD_OF_AGONY);
    itemTable[DINS_FIRE]                         = Item("Din's Fire",           ITEMTYPE_ITEM,  GI_DINS_FIRE,      true,       &DinsFire,      DINS_FIRE);
    itemTable[FARORES_WIND]                      = Item("Farore's Wind",        ITEMTYPE_ITEM,  GI_FARORES_WIND,   true,       &FaroresWind,   FARORES_WIND);
    itemTable[NAYRUS_LOVE]                       = Item("Nayru's Love",         ITEMTYPE_ITEM,  GI_NAYRUS_LOVE,    true,       &NayrusLove,    NAYRUS_LOVE);
    itemTable[FIRE_ARROWS]                       = Item("Fire Arrows",          ITEMTYPE_ITEM,  GI_ARROW_FIRE,     true,       &FireArrows,    FIRE_ARROWS);
    itemTable[ICE_ARROWS]                        = Item("Ice Arrows",           ITEMTYPE_ITEM,  GI_ARROW_ICE,      true,       &IceArrows,     ICE_ARROWS);
    itemTable[LIGHT_ARROWS]                      = Item("Light Arrows",         ITEMTYPE_ITEM,  GI_ARROW_LIGHT,    true,       &LightArrows,   LIGHT_ARROWS);
    itemTable[GERUDO_TOKEN]                      = Item("Gerudo Token",         ITEMTYPE_ITEM,  GI_GERUDO_CARD,    true,       &GerudoToken,   GERUDO_TOKEN);
    itemTable[MAGIC_BEAN]                        = Item("Magic Bean",           ITEMTYPE_ITEM,  GI_BEAN,           true,       &MagicBean,     MAGIC_BEAN);
    itemTable[MAGIC_BEAN_PACK]                   = Item("Magic Bean Pack",      ITEMTYPE_ITEM,  0xC9,              true,       &MagicBeanPack, MAGIC_BEAN_PACK);
    itemTable[DOUBLE_DEFENSE]                    = Item("Double Defense",       ITEMTYPE_ITEM,  0xB8,              true,       &noVariable,    DOUBLE_DEFENSE);

    itemTable[POCKET_EGG]                        = Item("Pocket Egg",           ITEMTYPE_ITEM,  GI_POCKET_EGG,     true,       &PocketEgg,     POCKET_EGG);
    itemTable[POCKET_CUCCO]                      = Item("Pocket Cucco",         ITEMTYPE_ITEM,  GI_POCKET_CUCCO,   true,       &PocketCucco,   POCKET_CUCCO);
    itemTable[COJIRO]                            = Item("Cojiro",               ITEMTYPE_ITEM,  GI_COJIRO,         true,       &Cojiro,        COJIRO);
    itemTable[ODD_MUSHROOM]                      = Item("Odd Mushroom",         ITEMTYPE_ITEM,  GI_ODD_MUSHROOM,   true,       &OddMushroom,   ODD_MUSHROOM);
    itemTable[ODD_POULTICE]                      = Item("Odd Poultice",         ITEMTYPE_ITEM,  GI_ODD_POTION,     true,       &OddPoultice,   ODD_POULTICE);
    itemTable[POACHERS_SAW]                      = Item("Poachers Saw",         ITEMTYPE_ITEM,  GI_SAW,            true,       &PoachersSaw,   POACHERS_SAW);
    itemTable[BROKEN_SWORD]                      = Item("Broken Sword",         ITEMTYPE_ITEM,  GI_SWORD_BROKEN,   true,       &BrokenSword,   BROKEN_SWORD);
    itemTable[PRESCRIPTION]                      = Item("Prescription",         ITEMTYPE_ITEM,  GI_PERSCRIPTION,   true,       &Prescription,  PRESCRIPTION);
    itemTable[EYEBALL_FROG]                      = Item("Eyeball Frog",         ITEMTYPE_ITEM,  GI_FROG,           true,       &EyeballFrog,   EYEBALL_FROG);
    itemTable[EYEDROPS]                          = Item("Eyedrops",             ITEMTYPE_ITEM,  GI_EYEDROPS,       true,       &Eyedrops,      EYEDROPS);
    itemTable[CLAIM_CHECK]                       = Item("Claim Check",          ITEMTYPE_ITEM,  GI_CLAIM_CHECK,    true,       &ClaimCheck,    CLAIM_CHECK);

    itemTable[GOLD_SKULLTULA_TOKEN]              = Item("Gold Skulltula Token", ITEMTYPE_TOKEN, GI_SKULL_TOKEN,    true,       &GoldSkulltulaTokens, GOLD_SKULLTULA_TOKEN);

    //Progression Items
    itemTable[PROGRESSIVE_HOOKSHOT]              = Item("Progressive Hookshot",       ITEMTYPE_ITEM,     0x80, true,  &ProgressiveHookshot,  PROGRESSIVE_HOOKSHOT);
    itemTable[PROGRESSIVE_STRENGTH]              = Item("Progressive Strength",       ITEMTYPE_ITEM,     0x81, true,  &ProgressiveStrength,  PROGRESSIVE_STRENGTH);
    itemTable[PROGRESSIVE_BOMB_BAG]              = Item("Progressive Bomb Bag",       ITEMTYPE_ITEM,     0x82, true,  &ProgressiveBombBag,   PROGRESSIVE_BOMB_BAG);
    itemTable[PROGRESSIVE_BOW]                   = Item("Progressive Bow",            ITEMTYPE_ITEM,     0x83, true,  &ProgressiveBow,       PROGRESSIVE_BOW);
    itemTable[PROGRESSIVE_SLINGSHOT]             = Item("Progressive Slingshot",      ITEMTYPE_ITEM,     0x84, true,  &ProgressiveBulletBag, PROGRESSIVE_SLINGSHOT);
    itemTable[PROGRESSIVE_WALLET]                = Item("Progressive Wallet",         ITEMTYPE_ITEM,     0x85, true,  &ProgressiveWallet,    PROGRESSIVE_WALLET);
    itemTable[PROGRESSIVE_SCALE]                 = Item("Progressive Scale",          ITEMTYPE_ITEM,     0x86, true,  &ProgressiveScale,     PROGRESSIVE_SCALE);
    itemTable[PROGRESSIVE_NUT_UPGRADE]           = Item("Progressive Nut Upgrade",    ITEMTYPE_ITEM,     0x87, false, &noVariable,           PROGRESSIVE_NUT_UPGRADE);
    itemTable[PROGRESSIVE_STICK_UPGRADE]         = Item("Progressive Stick Upgrade",  ITEMTYPE_ITEM,     0x88, false, &noVariable,           PROGRESSIVE_STICK_UPGRADE);
    itemTable[PROGRESSIVE_BOMBCHUS]              = Item("Progressive Bombchus",       ITEMTYPE_ITEM,     0x89, true,  &Bombchus,             PROGRESSIVE_BOMBCHUS);
    itemTable[PROGRESSIVE_MAGIC_METER]           = Item("Progressive Magic",          ITEMTYPE_ITEM,     0x8A, true,  &ProgressiveMagic,     PROGRESSIVE_MAGIC_METER);
    itemTable[PROGRESSIVE_OCARINA]               = Item("Progressive Ocarina",        ITEMTYPE_ITEM,     0x8B, true,  &ProgressiveOcarina,   PROGRESSIVE_OCARINA);

    //Bottles
    itemTable[EMPTY_BOTTLE]                      = Item("Empty Bottle",               ITEMTYPE_ITEM,     0x0F, true, &HasBottle, EMPTY_BOTTLE);
    itemTable[BOTTLE_WITH_MILK]                  = Item("Bottle with Milk",           ITEMTYPE_ITEM,     0x14, true, &HasBottle, BOTTLE_WITH_MILK);
    itemTable[BOTTLE_WITH_RED_POTION]            = Item("Bottle with Red Potion",     ITEMTYPE_ITEM,     0x8C, true, &HasBottle, BOTTLE_WITH_RED_POTION);
    itemTable[BOTTLE_WITH_GREEN_POTION]          = Item("Bottle with Green Potion",   ITEMTYPE_ITEM,     0x8D, true, &HasBottle, BOTTLE_WITH_GREEN_POTION);
    itemTable[BOTTLE_WITH_BLUE_POTION]           = Item("Bottle with Blue Potion",    ITEMTYPE_ITEM,     0x8E, true, &HasBottle, BOTTLE_WITH_BLUE_POTION);
    itemTable[BOTTLE_WITH_FAIRY]                 = Item("Bottle with Fairy",          ITEMTYPE_ITEM,     0x8F, true, &HasBottle, BOTTLE_WITH_FAIRY);
    itemTable[BOTTLE_WITH_FISH]                  = Item("Bottle with Fish",           ITEMTYPE_ITEM,     0x90, true, &HasBottle, BOTTLE_WITH_FISH);
    itemTable[BOTTLE_WITH_BLUE_FIRE]             = Item("Bottle with Blue Fire",      ITEMTYPE_ITEM,     0x91, true, &HasBottle, BOTTLE_WITH_BLUE_FIRE);
    itemTable[BOTTLE_WITH_BUGS]                  = Item("Bottle with Bugs",           ITEMTYPE_ITEM,     0x92, true, &HasBottle, BOTTLE_WITH_BUGS);
    itemTable[BOTTLE_WITH_POE]                   = Item("Bottle with Poe",            ITEMTYPE_ITEM,     0x94, true, &HasBottle, BOTTLE_WITH_POE);

    //Special bottles that can't immediately dump contents
    itemTable[RUTOS_LETTER]                      = Item("Rutos Letter",               ITEMTYPE_ITEM,     0x15, true, &RutosLetter,      RUTOS_LETTER);
    itemTable[BOTTLE_WITH_BIG_POE]               = Item("Bottle with Big Poe",        ITEMTYPE_ITEM,     0x93, true, &BottleWithBigPoe, BOTTLE_WITH_BIG_POE);

    //Songs
    itemTable[ZELDAS_LULLABY]                    = Item("Zelda's Lullaby",            ITEMTYPE_SONG,     0xC1, true, &ZeldasLullaby,    ZELDAS_LULLABY);
    itemTable[EPONAS_SONG]                       = Item("Epona's Song",               ITEMTYPE_SONG,     0xC2, true, &EponasSong,       EPONAS_SONG);
    itemTable[SARIAS_SONG]                       = Item("Saria's Song",               ITEMTYPE_SONG,     0xC3, true, &SariasSong,       SARIAS_SONG);
    itemTable[SUNS_SONG]                         = Item("Sun's Song",                 ITEMTYPE_SONG,     0xC4, true, &SunsSong,         SUNS_SONG);
    itemTable[SONG_OF_TIME]                      = Item("Song of Time",               ITEMTYPE_SONG,     0xC5, true, &SongOfTime,       SONG_OF_TIME);
    itemTable[SONG_OF_STORMS]                    = Item("Song of Storms",             ITEMTYPE_SONG,     0xC6, true, &SongOfStorms,     SONG_OF_STORMS);
    itemTable[MINUET_OF_FOREST]                  = Item("Minuet of Forest",           ITEMTYPE_SONG,     0xBB, true, &MinuetOfForest,   MINUET_OF_FOREST);
    itemTable[BOLERO_OF_FIRE]                    = Item("Bolero of Fire",             ITEMTYPE_SONG,     0xBC, true, &BoleroOfFire,     BOLERO_OF_FIRE);
    itemTable[SERENADE_OF_WATER]                 = Item("Serenade of Water",          ITEMTYPE_SONG,     0xBD, true, &SerenadeOfWater,  SERENADE_OF_WATER);
    itemTable[REQUIEM_OF_SPIRIT]                 = Item("Requiem of Spirit",          ITEMTYPE_SONG,     0xBE, true, &RequiemOfSpirit,  REQUIEM_OF_SPIRIT);
    itemTable[NOCTURNE_OF_SHADOW]                = Item("Nocturne of Shadow",         ITEMTYPE_SONG,     0xBF, true, &NocturneOfShadow, NOCTURNE_OF_SHADOW);
    itemTable[PRELUDE_OF_LIGHT]                  = Item("Prelude of Light",           ITEMTYPE_SONG,     0xC0, true, &PreludeOfLight,   PRELUDE_OF_LIGHT);

    //Maps and Compasses
    itemTable[DEKU_TREE_MAP]                     = Item("Deku Tree Map",              ITEMTYPE_MAP,      0xA5, false, &noVariable, MAP);
    itemTable[DODONGOS_CAVERN_MAP]               = Item("Dodongo's Cavern Map",       ITEMTYPE_MAP,      0xA6, false, &noVariable, MAP);
    itemTable[JABU_JABUS_BELLY_MAP]              = Item("Jabu Jabu's Belly Map",      ITEMTYPE_MAP,      0xA7, false, &noVariable, MAP);
    itemTable[FOREST_TEMPLE_MAP]                 = Item("Forest Temple Map",          ITEMTYPE_MAP,      0xA8, false, &noVariable, MAP);
    itemTable[FIRE_TEMPLE_MAP]                   = Item("Fire Temple Map",            ITEMTYPE_MAP,      0xA9, false, &noVariable, MAP);
    itemTable[WATER_TEMPLE_MAP]                  = Item("Water Temple Map",           ITEMTYPE_MAP,      0xAA, false, &noVariable, MAP);
    itemTable[SPIRIT_TEMPLE_MAP]                 = Item("Spirit Temple Map",          ITEMTYPE_MAP,      0xAB, false, &noVariable, MAP);
    itemTable[SHADOW_TEMPLE_MAP]                 = Item("Shadow Temple Map",          ITEMTYPE_MAP,      0xAC, false, &noVariable, MAP);
    itemTable[BOTTOM_OF_THE_WELL_MAP]            = Item("Bottom of the Well Map",     ITEMTYPE_MAP,      0xAD, false, &noVariable, MAP);
    itemTable[ICE_CAVERN_MAP]                    = Item("Ice Cavern Map",             ITEMTYPE_MAP,      0xAE, false, &noVariable, MAP);

    itemTable[DEKU_TREE_COMPASS]                 = Item("Deku Tree Compass",          ITEMTYPE_COMPASS,  0x9B, false, &noVariable, COMPASS);
    itemTable[DODONGOS_CAVERN_COMPASS]           = Item("Dodongo's Cavern Compass",   ITEMTYPE_COMPASS,  0x9C, false, &noVariable, COMPASS);
    itemTable[JABU_JABUS_BELLY_COMPASS]          = Item("Jabu Jabu's Belly Compass",  ITEMTYPE_COMPASS,  0x9D, false, &noVariable, COMPASS);
    itemTable[FOREST_TEMPLE_COMPASS]             = Item("Forest Temple Compass",      ITEMTYPE_COMPASS,  0x9E, false, &noVariable, COMPASS);
    itemTable[FIRE_TEMPLE_COMPASS]               = Item("Fire Temple Compass",        ITEMTYPE_COMPASS,  0x9F, false, &noVariable, COMPASS);
    itemTable[WATER_TEMPLE_COMPASS]              = Item("Water Temple Compass",       ITEMTYPE_COMPASS,  0xA0, false, &noVariable, COMPASS);
    itemTable[SPIRIT_TEMPLE_COMPASS]             = Item("Spirit Temple Compass",      ITEMTYPE_COMPASS,  0xA1, false, &noVariable, COMPASS);
    itemTable[SHADOW_TEMPLE_COMPASS]             = Item("Shadow Temple Compass",      ITEMTYPE_COMPASS,  0xA2, false, &noVariable, COMPASS);
    itemTable[BOTTOM_OF_THE_WELL_COMPASS]        = Item("Bottom of the Well Compass", ITEMTYPE_COMPASS,  0xA3, false, &noVariable, COMPASS);
    itemTable[ICE_CAVERN_COMPASS]                = Item("Ice Cavern Compass",         ITEMTYPE_COMPASS,  0xA4, false, &noVariable, COMPASS);

    //Boss Keys
    itemTable[FOREST_TEMPLE_BOSS_KEY]            = Item("Forest Temple Boss Key",     ITEMTYPE_BOSSKEY,  0x95, true, &BossKeyForestTemple, BOSS_KEY);
    itemTable[FIRE_TEMPLE_BOSS_KEY]              = Item("Fire Temple Boss Key",       ITEMTYPE_BOSSKEY,  0x96, true, &BossKeyFireTemple,   BOSS_KEY);
    itemTable[WATER_TEMPLE_BOSS_KEY]             = Item("Water Temple Boss Key",      ITEMTYPE_BOSSKEY,  0x97, true, &BossKeyWaterTemple,  BOSS_KEY);
    itemTable[SPIRIT_TEMPLE_BOSS_KEY]            = Item("Spirit Temple Boss Key",     ITEMTYPE_BOSSKEY,  0x98, true, &BossKeySpiritTemple, BOSS_KEY);
    itemTable[SHADOW_TEMPLE_BOSS_KEY]            = Item("Shadow Temple Boss Key",     ITEMTYPE_BOSSKEY,  0x99, true, &BossKeyShadowTemple, BOSS_KEY);
    itemTable[GANONS_CASTLE_BOSS_KEY]            = Item("Ganon's Castle Boss Key",    ITEMTYPE_BOSSKEY,  0x9A, true, &BossKeyGanonsCastle, GANONS_CASTLE_BOSS_KEY);

    //Small Keys
    itemTable[FOREST_TEMPLE_SMALL_KEY]           = Item("Forest Temple Small Key",           ITEMTYPE_SMALLKEY,          0xAF, true, &ForestTempleKeys,          SMALL_KEY);
    itemTable[FIRE_TEMPLE_SMALL_KEY]             = Item("Fire Temple Small Key",             ITEMTYPE_SMALLKEY,          0xB0, true, &FireTempleKeys,            SMALL_KEY);
    itemTable[WATER_TEMPLE_SMALL_KEY]            = Item("Water Temple Small Key",            ITEMTYPE_SMALLKEY,          0xB1, true, &WaterTempleKeys,           SMALL_KEY);
    itemTable[SPIRIT_TEMPLE_SMALL_KEY]           = Item("Spirit Temple Small Key",           ITEMTYPE_SMALLKEY,          0xB2, true, &SpiritTempleKeys,          SMALL_KEY);
    itemTable[SHADOW_TEMPLE_SMALL_KEY]           = Item("Shadow Temple Small Key",           ITEMTYPE_SMALLKEY,          0xB3, true, &ShadowTempleKeys,          SMALL_KEY);
    itemTable[BOTTOM_OF_THE_WELL_SMALL_KEY]      = Item("Bottom of the Well Small Key",      ITEMTYPE_SMALLKEY,          0xB4, true, &BottomOfTheWellKeys,       SMALL_KEY);
    itemTable[GERUDO_TRAINING_GROUNDS_SMALL_KEY] = Item("Gerudo Training Grounds Small Key", ITEMTYPE_SMALLKEY,          0xB5, true, &GerudoTrainingGroundsKeys, SMALL_KEY);
    itemTable[GERUDO_FORTRESS_SMALL_KEY]         = Item("Gerudo Fortress Small Key",         ITEMTYPE_FORTRESS_SMALLKEY, 0xB6, true, &GerudoFortressKeys,        GERUDO_FORTRESS_SMALL_KEY);
    itemTable[GANONS_CASTLE_SMALL_KEY]           = Item("Ganon's Castle Small Key",          ITEMTYPE_SMALLKEY,          0xB7, true, &GanonsCastleKeys,          SMALL_KEY);

    //Stones and Medallions
    itemTable[KOKIRI_EMERALD]                    = Item("Kokiri Emerald",   ITEMTYPE_DUNGEONREWARD, 0xCB,  true, &KokiriEmerald,   KOKIRI_EMERALD);
    itemTable[GORON_RUBY]                        = Item("Goron Ruby",       ITEMTYPE_DUNGEONREWARD, 0xCC,  true, &GoronRuby,       GORON_RUBY);
    itemTable[ZORA_SAPPHIRE]                     = Item("Zora Sapphire",    ITEMTYPE_DUNGEONREWARD, 0xCD,  true, &ZoraSapphire,    ZORA_SAPPHIRE);
    itemTable[FOREST_MEDALLION]                  = Item("Forest Medallion", ITEMTYPE_DUNGEONREWARD, 0xCE,  true, &ForestMedallion, FOREST_MEDALLION);
    itemTable[FIRE_MEDALLION]                    = Item("Fire Medallion",   ITEMTYPE_DUNGEONREWARD, 0xCF,  true, &FireMedallion,   FIRE_MEDALLION);
    itemTable[WATER_MEDALLION]                   = Item("Water Medallion",  ITEMTYPE_DUNGEONREWARD, 0xD0,  true, &WaterMedallion,  WATER_MEDALLION);
    itemTable[SPIRIT_MEDALLION]                  = Item("Spirit Medallion", ITEMTYPE_DUNGEONREWARD, 0xD1,  true, &SpiritMedallion, SPIRIT_MEDALLION);
    itemTable[SHADOW_MEDALLION]                  = Item("Shadow Medallion", ITEMTYPE_DUNGEONREWARD, 0xD2,  true, &ShadowMedallion, SHADOW_MEDALLION);
    itemTable[LIGHT_MEDALLION]                   = Item("Light Medallion",  ITEMTYPE_DUNGEONREWARD, 0xD3,  true, &LightMedallion,  LIGHT_MEDALLION);

    //Generic Items
    itemTable[RECOVERY_HEART]                    = Item("Recovery Heart",   ITEMTYPE_ITEM, GI_HEART,             false, &noVariable, RECOVERY_HEART);
    itemTable[GREEN_RUPEE]                       = Item("Green Rupee",      ITEMTYPE_ITEM, GI_RUPEE_GREEN,       false, &noVariable, GREEN_RUPEE);
    itemTable[BLUE_RUPEE]                        = Item("Blue Rupee",       ITEMTYPE_ITEM, GI_RUPEE_BLUE,        false, &noVariable, BLUE_RUPEE);
    itemTable[RED_RUPEE]                         = Item("Red Rupee",        ITEMTYPE_ITEM, GI_RUPEE_RED,         false, &noVariable, RED_RUPEE);
    itemTable[PURPLE_RUPEE]                      = Item("Purple Rupee",     ITEMTYPE_ITEM, GI_RUPEE_PURPLE,      false, &noVariable, PURPLE_RUPEE);
    itemTable[HUGE_RUPEE]                        = Item("Huge Rupee",       ITEMTYPE_ITEM, GI_RUPEE_GOLD,        false, &noVariable, HUGE_RUPEE);
    itemTable[PIECE_OF_HEART]                    = Item("Piece of Heart",   ITEMTYPE_ITEM, GI_HEART_PIECE,       false, &noVariable, PIECE_OF_HEART);
    itemTable[HEART_CONTAINER]                   = Item("Heart Container",  ITEMTYPE_ITEM, GI_HEART_CONTAINER_2, false, &noVariable, HEART_CONTAINER);
    itemTable[ICE_TRAP]                          = Item("Ice Trap",         ITEMTYPE_ITEM, GI_ICE_TRAP,          false, &noVariable, ICE_TRAP);
    itemTable[MILK]                              = Item("Milk",             ITEMTYPE_ITEM, GI_MILK,              false, &noVariable, NONE);

    //Refills
    itemTable[BOMBS_5]                           = Item("Bombs (5)",           ITEMTYPE_ITEM, GI_BOMBS_5,        false, &noVariable,  BOMBS_5);
    itemTable[BOMBS_10]                          = Item("Bombs (10)",          ITEMTYPE_ITEM, GI_BOMBS_10,       false, &noVariable,  BOMBS_10);
    itemTable[BOMBS_20]                          = Item("Bombs (20)",          ITEMTYPE_ITEM, GI_BOMBS_20,       false, &noVariable,  BOMBS_20);
    itemTable[BOMBCHU_5]                         = Item("Bombchu (5)",         ITEMTYPE_ITEM, GI_BOMBCHUS_5,     true,  &Bombchus5,   BOMBCHU_5);
    itemTable[BOMBCHU_10]                        = Item("Bombchu (10)",        ITEMTYPE_ITEM, GI_BOMBCHUS_10,    true,  &Bombchus10,  BOMBCHU_10);
    itemTable[BOMBCHU_20]                        = Item("Bombchu (20)",        ITEMTYPE_ITEM, GI_BOMBCHUS_20,    true,  &Bombchus20,  BOMBCHU_20);
    itemTable[BOMBCHU_DROP]                      = Item("Bombchu Drop",        ITEMTYPE_DROP, GI_BOMBCHUS_10,    true,  &BombchuDrop, NONE);
    itemTable[ARROWS_5]                          = Item("Arrows (5)",          ITEMTYPE_ITEM, GI_ARROWS_SMALL,   false, &noVariable,  ARROWS_5);
    itemTable[ARROWS_10]                         = Item("Arrows (10)",         ITEMTYPE_ITEM, GI_ARROWS_MEDIUM,  false, &noVariable,  ARROWS_10);
    itemTable[ARROWS_30]                         = Item("Arrows (30)",         ITEMTYPE_ITEM, GI_ARROWS_LARGE,   false, &noVariable,  ARROWS_30);
    itemTable[DEKU_NUTS_5]                       = Item("Deku Nuts (5)",       ITEMTYPE_ITEM, GI_NUTS_5,         false, &noVariable,  DEKU_NUTS_5);
    itemTable[DEKU_NUTS_10]                      = Item("Deku Nuts (10)",      ITEMTYPE_ITEM, GI_NUTS_10,        false, &noVariable,  DEKU_NUTS_10);
    itemTable[DEKU_SEEDS_30]                     = Item("Deku Seeds (30)",     ITEMTYPE_ITEM, GI_SEEDS_30,       false, &noVariable,  DEKU_SEEDS_30);
    itemTable[DEKU_STICK_1]                      = Item("Deku Stick (1)",      ITEMTYPE_ITEM, GI_STICKS_1,       false, &noVariable,  DEKU_STICK_1);
    itemTable[RED_POTION_REFILL]                 = Item("Red Potion Refill",   ITEMTYPE_ITEM, GI_POTION_RED,     false, &noVariable,  NONE);
    itemTable[GREEN_POTION_REFILL]               = Item("Green Potion Refill", ITEMTYPE_ITEM, GI_POTION_GREEN,   false, &noVariable,  NONE);
    itemTable[BLUE_POTION_REFILL]                = Item("Blue Potion Refill",  ITEMTYPE_ITEM, GI_POTION_BLUE,    false, &noVariable,  NONE);

    //Treasure Game
    itemTable[TREASURE_GAME_HEART]               = Item("Piece of Heart (Treasure Chest Minigame)", ITEMTYPE_ITEM, GI_HEART_PIECE_WIN,  false, &noVariable, TREASURE_GAME_HEART);
    itemTable[TREASURE_GAME_GREEN_RUPEE]         = Item("Green Rupee (Treasure Chest Minigame)",    ITEMTYPE_ITEM, GI_RUPEE_GREEN_LOSE, false, &noVariable, TREASURE_GAME_GREEN_RUPEE);

    //Shop Items                                                                                                                                    price
    itemTable[BUY_DEKU_NUT_5]                    = Item("Buy Deku Nut (5)",    ITEMTYPE_SHOP, 0x00, true,  &Nuts,           DEKU_NUTS_5,            15);
    itemTable[BUY_ARROWS_30]                     = Item("Buy Arrows (30)",     ITEMTYPE_SHOP, 0x01, false, &noVariable,     ARROWS_30,              60);
    itemTable[BUY_ARROWS_50]                     = Item("Buy Arrows (50)",     ITEMTYPE_SHOP, 0x02, false, &noVariable,     ARROWS_30,              90);
    itemTable[BUY_BOMBS_525]                     = Item("Buy Bombs (5) [25]",  ITEMTYPE_SHOP, 0x03, false, &noVariable,     BOMBS_5,                25);
    itemTable[BUY_DEKU_NUT_10]                   = Item("Buy Deku Nut (10)",   ITEMTYPE_SHOP, 0x04, true,  &Nuts,           DEKU_NUTS_10,           30);
    itemTable[BUY_DEKU_STICK_1]                  = Item("Buy Deku Stick (1)",  ITEMTYPE_SHOP, 0x05, true,  &Sticks,         DEKU_STICK_1,           10);
    itemTable[BUY_BOMBS_10]                      = Item("Buy Bombs (10)",      ITEMTYPE_SHOP, 0x06, false, &noVariable,     BOMBS_10,               50);
    itemTable[BUY_FISH]                          = Item("Buy Fish",            ITEMTYPE_SHOP, 0x07, true,  &FishAccess,     BOTTLE_WITH_FISH,      200);
    itemTable[BUY_RED_POTION_30]                 = Item("Buy Red Potion [30]", ITEMTYPE_SHOP, 0x08, false, &noVariable,     NONE,                   30);
    itemTable[BUY_GREEN_POTION]                  = Item("Buy Green Potion",    ITEMTYPE_SHOP, 0x09, false, &noVariable,     NONE,                   30);
    itemTable[BUY_BLUE_POTION]                   = Item("Buy Blue Potion",     ITEMTYPE_SHOP, 0x0A, false, &noVariable,     NONE,                  100);
    itemTable[BUY_HYLIAN_SHIELD]                 = Item("Buy Hylian Shield",   ITEMTYPE_SHOP, 0x0C, true,  &HylianShield,   HYLIAN_SHIELD,          80);
    itemTable[BUY_DEKU_SHIELD]                   = Item("Buy Deku Shield",     ITEMTYPE_SHOP, 0x0D, true,  &DekuShield,     DEKU_SHIELD,            40);
    itemTable[BUY_GORON_TUNIC]                   = Item("Buy Goron Tunic",     ITEMTYPE_SHOP, 0x0E, true,  &GoronTunic,     GORON_TUNIC,           200);
    itemTable[BUY_ZORA_TUNIC]                    = Item("Buy Zora Tunic",      ITEMTYPE_SHOP, 0x0F, true,  &ZoraTunic,      ZORA_TUNIC,            300);
    itemTable[BUY_HEART]                         = Item("Buy Heart",           ITEMTYPE_SHOP, 0x10, false, &noVariable,     RECOVERY_HEART,         10);
    itemTable[BUY_BOMBCHU_10]                    = Item("Buy Bombchu (10)",    ITEMTYPE_SHOP, 0x15, true,  &BuyBombchus10,  BOMBCHU_10,             99);
    itemTable[BUY_BOMBCHU_20]                    = Item("Buy Bombchu (20)",    ITEMTYPE_SHOP, 0x16, true,  &BuyBombchus20,  BOMBCHU_20,            180);
    itemTable[BUY_BOMBCHU_5]                     = Item("Buy Bombchu (5)",     ITEMTYPE_SHOP, 0x18, true,  &BuyBombchus5,   BOMBCHU_5,              60);
    itemTable[BUY_DEKU_SEEDS_30]                 = Item("Buy Deku Seeds (30)", ITEMTYPE_SHOP, 0x1D, false, &noVariable,     DEKU_SEEDS_30,          30);
    itemTable[SOLD_OUT]                          = Item("Sold Out",            ITEMTYPE_SHOP, 0x26, false, &noVariable,     NONE,                    0);
    itemTable[BUY_BLUE_FIRE]                     = Item("Buy Blue Fire",       ITEMTYPE_SHOP, 0x27, true,  &BlueFireAccess, BOTTLE_WITH_BLUE_FIRE, 300);
    itemTable[BUY_BOTTLE_BUG]                    = Item("Buy Bottle Bug",      ITEMTYPE_SHOP, 0x28, true,  &BugsAccess,     BOTTLE_WITH_BUGS,       50);
    itemTable[BUY_POE]                           = Item("Buy Poe",             ITEMTYPE_SHOP, 0x2A, false, &noVariable,     BOTTLE_WITH_BIG_POE,    30);
    itemTable[BUY_FAIRYS_SPIRIT]                 = Item("Buy Fairy's Spirit",  ITEMTYPE_SHOP, 0x2B, true,  &FairyAccess,    BOTTLE_WITH_FAIRY,      50);
    itemTable[BUY_ARROWS_10]                     = Item("Buy Arrows (10)",     ITEMTYPE_SHOP, 0x2C, false, &noVariable,     ARROWS_10,              20);
    itemTable[BUY_BOMBS_20]                      = Item("Buy Bombs (20)",      ITEMTYPE_SHOP, 0x2D, false, &noVariable,     BOMBS_20,               80);
    itemTable[BUY_BOMBS_30]                      = Item("Buy Bombs (30)",      ITEMTYPE_SHOP, 0x2E, false, &noVariable,     BOMBS_20,              120);
    itemTable[BUY_BOMBS_535]                     = Item("Buy Bombs (5) [35]",  ITEMTYPE_SHOP, 0x2F, false, &noVariable,     BOMBS_5,                35);
    itemTable[BUY_RED_POTION_40]                 = Item("Buy Red Potion [40]", ITEMTYPE_SHOP, 0x30, false, &noVariable,     NONE,                   40);
    itemTable[BUY_RED_POTION_50]                 = Item("Buy Red Potion [50]", ITEMTYPE_SHOP, 0x31, false, &noVariable,     NONE,                   50);

    itemTable[TRIFORCE]                          = Item("Triforce", ITEMTYPE_EVENT, GI_RUPEE_RED_LOSE, false, &noVariable, NONE);
    itemTable[HINT]                              = Item("Hint",     ITEMTYPE_EVENT, GI_RUPEE_BLUE_LOSE, false, &noVariable, NONE);
}

Item& ItemTable(u32 itemKey) {
    return itemTable[itemKey];
}
