#include "item_list.hpp"

#include "logic.hpp"
#include "keys.hpp"
#include "settings.hpp"
#include "../code/include/z3D/z3Ditem.h"
#include <vector>
#include <unordered_map>

using namespace Logic;
using namespace Settings;

static std::unordered_map<u32, const Item> items = {
  {NONE,                   Item("No Item",              ITEMTYPE_EVENT, GI_RUPEE_GREEN,    false,      &noVariable,    NONE)},
  {KOKIRI_SWORD,           Item("Kokiri Sword",         ITEMTYPE_ITEM,  GI_SWORD_KOKIRI,   true,       &KokiriSword,   KOKIRI_SWORD)},
  //[MASTER_SWORD]
  //[GIANTS_KNIFE]
  {BIGGORON_SWORD,         Item("Biggoron Sword",       ITEMTYPE_ITEM,  GI_SWORD_BGS,      true,       &noVariable,    BIGGORON_SWORD)},
  {DEKU_SHIELD,            Item("Deku Shield",          ITEMTYPE_ITEM,  GI_SHIELD_DEKU,    false,      &noVariable,    DEKU_SHIELD)},
  {HYLIAN_SHIELD,          Item("Hylian Shield",        ITEMTYPE_ITEM,  GI_SHIELD_HYLIAN,  false,      &noVariable,    HYLIAN_SHIELD)},
  {MIRROR_SHIELD,          Item("Mirror Shield",        ITEMTYPE_ITEM,  GI_SHIELD_MIRROR,  true,       &MirrorShield,  MIRROR_SHIELD)},
  {GORON_TUNIC,            Item("Goron Tunic",          ITEMTYPE_ITEM,  GI_TUNIC_GORON,    true,       &GoronTunic,    GORON_TUNIC)},
  {ZORA_TUNIC,             Item("Zora Tunic",           ITEMTYPE_ITEM,  GI_TUNIC_ZORA,     true,       &ZoraTunic,     ZORA_TUNIC)},
  {IRON_BOOTS,             Item("Iron Boots",           ITEMTYPE_ITEM,  GI_BOOTS_IRON,     true,       &IronBoots,     IRON_BOOTS)},
  {HOVER_BOOTS,            Item("Hover Boots",          ITEMTYPE_ITEM,  GI_BOOTS_HOVER,    true,       &HoverBoots,    HOVER_BOOTS)},
  {WEIRD_EGG,              Item("Zelda's Letter",       ITEMTYPE_ITEM,  GI_LETTER_ZELDA,   true,       &ZeldasLetter,  ZELDAS_LETTER)},
  {ZELDAS_LETTER,          Item("Weird Egg",            ITEMTYPE_ITEM,  GI_WEIRD_EGG,      true,       &WeirdEgg,      WEIRD_EGG)},
  {BOOMERANG,              Item("Boomerang",            ITEMTYPE_ITEM,  GI_BOOMERANG,      true,       &Boomerang,     BOOMERANG)},
  {LENS_OF_TRUTH,          Item("Lens of Truth",        ITEMTYPE_ITEM,  GI_LENS,           true,       &LensOfTruth,   LENS_OF_TRUTH)},
  {MEGATON_HAMMER,         Item("Megaton Hammer",       ITEMTYPE_ITEM,  GI_HAMMER,         true,       &Hammer,        MEGATON_HAMMER)},
  {SHARD_OF_AGONY,         Item("Shard of Agony",       ITEMTYPE_ITEM,  GI_STONE_OF_AGONY, true,       &ShardOfAgony,  SHARD_OF_AGONY)},
  {DINS_FIRE,              Item("Din's Fire",           ITEMTYPE_ITEM,  GI_DINS_FIRE,      true,       &DinsFire,      DINS_FIRE)},
  {FARORES_WIND,           Item("Farore's Wind",        ITEMTYPE_ITEM,  GI_FARORES_WIND,   true,       &FaroresWind,   FARORES_WIND)},
  {NAYRUS_LOVE,            Item("Nayru's Love",         ITEMTYPE_ITEM,  GI_NAYRUS_LOVE,    true,       &NayrusLove,    NAYRUS_LOVE)},
  {FIRE_ARROWS,            Item("Fire Arrows",          ITEMTYPE_ITEM,  GI_ARROW_FIRE,     true,       &FireArrows,    FIRE_ARROWS)},
  {ICE_ARROWS,             Item("Ice Arrows",           ITEMTYPE_ITEM,  GI_ARROW_ICE,      true,       &IceArrows,     ICE_ARROWS)},
  {LIGHT_ARROWS,           Item("Light Arrows",         ITEMTYPE_ITEM,  GI_ARROW_LIGHT,    true,       &LightArrows,   LIGHT_ARROWS)},
};

Item NoItem     = Item("No Item",  ITEMTYPE_EVENT, GI_RUPEE_GREEN,    false, &noVariable, NONE);
Item I_Triforce = Item("Triforce", ITEMTYPE_EVENT, GI_RUPEE_RED_LOSE, false, &noVariable, NONE);

//Specific Advancement Items         // name                   type            getItemId          advancement logic variable  hint text (hint_list.cpp)
Item I_KokiriSword              = Item("Kokiri Sword",         ITEMTYPE_ITEM,  GI_SWORD_KOKIRI,   true,       &KokiriSword,   KOKIRI_SWORD);
//Master Sword
//Giant's Knife
Item I_BiggoronSword            = Item("Biggoron Sword",       ITEMTYPE_ITEM,  GI_SWORD_BGS,      true,       &noVariable,    BIGGORON_SWORD);
Item I_DekuShield               = Item("Deku Shield",          ITEMTYPE_ITEM,  GI_SHIELD_DEKU,    false,      &noVariable,    DEKU_SHIELD);
Item I_HylianShield             = Item("Hylian Shield",        ITEMTYPE_ITEM,  GI_SHIELD_HYLIAN,  false,      &noVariable,    HYLIAN_SHIELD);
Item I_MirrorShield             = Item("Mirror Shield",        ITEMTYPE_ITEM,  GI_SHIELD_MIRROR,  true,       &MirrorShield,  MIRROR_SHIELD);
Item I_GoronTunic               = Item("Goron Tunic",          ITEMTYPE_ITEM,  GI_TUNIC_GORON,    true,       &GoronTunic,    GORON_TUNIC);
Item I_ZoraTunic                = Item("Zora Tunic",           ITEMTYPE_ITEM,  GI_TUNIC_ZORA,     true,       &ZoraTunic,     ZORA_TUNIC);
Item I_IronBoots                = Item("Iron Boots",           ITEMTYPE_ITEM,  GI_BOOTS_IRON,     true,       &IronBoots,     IRON_BOOTS);
Item I_HoverBoots               = Item("Hover Boots",          ITEMTYPE_ITEM,  GI_BOOTS_HOVER,    true,       &HoverBoots,    HOVER_BOOTS);
Item I_ZeldasLetter             = Item("Zelda's Letter",       ITEMTYPE_ITEM,  GI_LETTER_ZELDA,   true,       &ZeldasLetter,  ZELDAS_LETTER);
Item I_WeirdEgg                 = Item("Weird Egg",            ITEMTYPE_ITEM,  GI_WEIRD_EGG,      true,       &WeirdEgg,      WEIRD_EGG);
Item I_Boomerang                = Item("Boomerang",            ITEMTYPE_ITEM,  GI_BOOMERANG,      true,       &Boomerang,     BOOMERANG);
Item I_LensOfTruth              = Item("Lens of Truth",        ITEMTYPE_ITEM,  GI_LENS,           true,       &LensOfTruth,   LENS_OF_TRUTH);
Item I_MegatonHammer            = Item("Megaton Hammer",       ITEMTYPE_ITEM,  GI_HAMMER,         true,       &Hammer,        MEGATON_HAMMER);
Item I_ShardOfAgony             = Item("Shard of Agony",       ITEMTYPE_ITEM,  GI_STONE_OF_AGONY, true,       &ShardOfAgony,  SHARD_OF_AGONY);
Item I_DinsFire                 = Item("Din's Fire",           ITEMTYPE_ITEM,  GI_DINS_FIRE,      true,       &DinsFire,      DINS_FIRE);
Item I_FaroresWind              = Item("Farore's Wind",        ITEMTYPE_ITEM,  GI_FARORES_WIND,   true,       &FaroresWind,   FARORES_WIND);
Item I_NayrusLove               = Item("Nayru's Love",         ITEMTYPE_ITEM,  GI_NAYRUS_LOVE,    true,       &NayrusLove,    NAYRUS_LOVE);
Item I_FireArrows               = Item("Fire Arrows",          ITEMTYPE_ITEM,  GI_ARROW_FIRE,     true,       &FireArrows,    FIRE_ARROWS);
Item I_IceArrows                = Item("Ice Arrows",           ITEMTYPE_ITEM,  GI_ARROW_ICE,      true,       &IceArrows,     ICE_ARROWS);
Item I_LightArrows              = Item("Light Arrows",         ITEMTYPE_ITEM,  GI_ARROW_LIGHT,    true,       &LightArrows,   LIGHT_ARROWS);

Item I_GerudoToken              = Item("Gerudo Token",         ITEMTYPE_ITEM,  GI_GERUDO_CARD,    true,       &GerudoToken,   GERUDO_TOKEN);
Item I_MagicBean                = Item("Magic Bean",           ITEMTYPE_ITEM,  GI_BEAN,           true,       &MagicBean,     MAGIC_BEAN);
Item I_MagicBeanPack            = Item("Magic Bean Pack",      ITEMTYPE_ITEM,  0xC9,              true,       &MagicBeanPack, MAGIC_BEAN_PACK);
Item I_DoubleDefense            = Item("Double Defense",       ITEMTYPE_ITEM,  0xB8,              true,       &noVariable,    DOUBLE_DEFENSE);

Item I_PocketEgg                = Item("Pocket Egg",           ITEMTYPE_ITEM,  GI_POCKET_EGG,     true,       &PocketEgg,     POCKET_EGG);
Item I_PocketCucco              = Item("Pocket Cucco",         ITEMTYPE_ITEM,  GI_POCKET_CUCCO,   true,       &PocketCucco,   POCKET_CUCCO);
Item I_Cojiro                   = Item("Cojiro",               ITEMTYPE_ITEM,  GI_COJIRO,         true,       &Cojiro,        COJIRO);
Item I_OddMushroom              = Item("Odd Mushroom",         ITEMTYPE_ITEM,  GI_ODD_MUSHROOM,   true,       &OddMushroom,   ODD_MUSHROOM);
Item I_OddPoultice              = Item("Odd Poultice",         ITEMTYPE_ITEM,  GI_ODD_POTION,     true,       &OddPoultice,   ODD_POULTICE);
Item I_PoachersSaw              = Item("Poachers Saw",         ITEMTYPE_ITEM,  GI_SAW,            true,       &PoachersSaw,   POACHERS_SAW);
Item I_BrokenSword              = Item("Broken Sword",         ITEMTYPE_ITEM,  GI_SWORD_BROKEN,   true,       &BrokenSword,   BROKEN_SWORD);
Item I_Prescription             = Item("Prescription",         ITEMTYPE_ITEM,  GI_PERSCRIPTION,   true,       &Prescription,  PRESCRIPTION);
Item I_EyeballFrog              = Item("Eyeball Frog",         ITEMTYPE_ITEM,  GI_FROG,           true,       &EyeballFrog,   EYEBALL_FROG);
Item I_Eyedrops                 = Item("Eyedrops",             ITEMTYPE_ITEM,  GI_EYEDROPS,       true,       &Eyedrops,      EYEDROPS);
Item I_ClaimCheck               = Item("Claim Check",          ITEMTYPE_ITEM,  GI_CLAIM_CHECK,    true,       &ClaimCheck,    CLAIM_CHECK);

Item GoldSkulltulaToken         = Item("Gold Skulltula Token", ITEMTYPE_TOKEN, GI_SKULL_TOKEN,    true,       &GoldSkulltulaTokens, GOLD_SKULLTULA_TOKEN);

//Progression Items
Item I_ProgressiveHookshot      = Item("Progressive Hookshot",       ITEMTYPE_ITEM,     0x80, true,  &ProgressiveHookshot,  PROGRESSIVE_HOOKSHOT);
Item I_ProgressiveStrength      = Item("Progressive Strength",       ITEMTYPE_ITEM,     0x81, true,  &ProgressiveStrength,  PROGRESSIVE_STRENGTH);
Item I_ProgressiveBombBag       = Item("Progressive Bomb Bag",       ITEMTYPE_ITEM,     0x82, true,  &ProgressiveBombBag,   PROGRESSIVE_BOMB_BAG);
Item I_ProgressiveBow           = Item("Progressive Bow",            ITEMTYPE_ITEM,     0x83, true,  &ProgressiveBow,       PROGRESSIVE_BOW);
Item I_ProgressiveBulletBag     = Item("Progressive Slingshot",      ITEMTYPE_ITEM,     0x84, true,  &ProgressiveBulletBag, PROGRESSIVE_SLINGSHOT);
Item I_ProgressiveWallet        = Item("Progressive Wallet",         ITEMTYPE_ITEM,     0x85, true,  &ProgressiveWallet,    PROGRESSIVE_WALLET);
Item I_ProgressiveScale         = Item("Progressive Scale",          ITEMTYPE_ITEM,     0x86, true,  &ProgressiveScale,     PROGRESSIVE_SCALE);
Item I_ProgressiveNutCapacity   = Item("Progressive Nut Upgrade",    ITEMTYPE_ITEM,     0x87, false, &noVariable,           PROGRESSIVE_NUT_UPGRADE);
Item I_ProgressiveStickCapacity = Item("Progressive Stick Upgrade",  ITEMTYPE_ITEM,     0x88, false, &noVariable,           PROGRESSIVE_STICK_UPGRADE);
Item I_ProgressiveBombchus      = Item("Progressive Bombchus",       ITEMTYPE_ITEM,     0x89, true,  &Bombchus,             PROGRESSIVE_BOMBCHUS);
Item I_ProgressiveMagic         = Item("Progressive Magic",          ITEMTYPE_ITEM,     0x8A, true,  &ProgressiveMagic,     PROGRESSIVE_MAGIC_METER);
Item I_ProgressiveOcarina       = Item("Progressive Ocarina",        ITEMTYPE_ITEM,     0x8B, true,  &ProgressiveOcarina,   PROGRESSIVE_OCARINA);

//Bottles
Item I_EmptyBottle              = Item("Empty Bottle",               ITEMTYPE_ITEM,     0x0F, true, &HasBottle, EMPTY_BOTTLE);
Item I_MilkBottle               = Item("Bottle with Milk",           ITEMTYPE_ITEM,     0x14, true, &HasBottle, BOTTLE_WITH_MILK);
Item I_RedPotionBottle          = Item("Bottle with Red Potion",     ITEMTYPE_ITEM,     0x8C, true, &HasBottle, BOTTLE_WITH_RED_POTION);
Item I_GreenPotionBottle        = Item("Bottle with Green Potion",   ITEMTYPE_ITEM,     0x8D, true, &HasBottle, BOTTLE_WITH_GREEN_POTION);
Item I_BluePotionBottle         = Item("Bottle with Blue Potion",    ITEMTYPE_ITEM,     0x8E, true, &HasBottle, BOTTLE_WITH_BLUE_POTION);
Item I_FairyBottle              = Item("Bottle with Fairy",          ITEMTYPE_ITEM,     0x8F, true, &HasBottle, BOTTLE_WITH_FAIRY);
Item I_FishBottle               = Item("Bottle with Fish",           ITEMTYPE_ITEM,     0x90, true, &HasBottle, BOTTLE_WITH_FISH);
Item I_BlueFireBottle           = Item("Bottle with Blue Fire",      ITEMTYPE_ITEM,     0x91, true, &HasBottle, BOTTLE_WITH_BLUE_FIRE);
Item I_BugsBottle               = Item("Bottle with Bugs",           ITEMTYPE_ITEM,     0x92, true, &HasBottle, BOTTLE_WITH_BUGS);
Item I_PoeBottle                = Item("Bottle with Poe",            ITEMTYPE_ITEM,     0x94, true, &HasBottle, BOTTLE_WITH_POE);

//Special bottles that can't immediately dump contents
Item I_RutosLetter              = Item("Rutos Letter",               ITEMTYPE_ITEM,     0x15, true, &RutosLetter,      RUTOS_LETTER);
Item I_BigPoeBottle             = Item("Bottle with Big Poe",        ITEMTYPE_ITEM,     0x93, true, &BottleWithBigPoe, BOTTLE_WITH_BIG_POE);

//Songs
Item I_ZeldasLullaby            = Item("Zelda's Lullaby",            ITEMTYPE_SONG,     0xC1, true, &ZeldasLullaby,    ZELDAS_LULLABY);
Item I_EponasSong               = Item("Epona's Song",               ITEMTYPE_SONG,     0xC2, true, &EponasSong,       EPONAS_SONG);
Item I_SariasSong               = Item("Saria's Song",               ITEMTYPE_SONG,     0xC3, true, &SariasSong,       SARIAS_SONG);
Item I_SunsSong                 = Item("Sun's Song",                 ITEMTYPE_SONG,     0xC4, true, &SunsSong,         SUNS_SONG);
Item I_SongOfTime               = Item("Song of Time",               ITEMTYPE_SONG,     0xC5, true, &SongOfTime,       SONG_OF_TIME);
Item I_SongOfStorms             = Item("Song of Storms",             ITEMTYPE_SONG,     0xC6, true, &SongOfStorms,     SONG_OF_STORMS);
Item I_MinuetOfForest           = Item("Minuet of Forest",           ITEMTYPE_SONG,     0xBB, true, &MinuetOfForest,   MINUET_OF_FOREST);
Item I_BoleroOfFire             = Item("Bolero of Fire",             ITEMTYPE_SONG,     0xBC, true, &BoleroOfFire,     BOLERO_OF_FIRE);
Item I_SerenadeOfWater          = Item("Serenade of Water",          ITEMTYPE_SONG,     0xBD, true, &SerenadeOfWater,  SERENADE_OF_WATER);
Item I_RequiemOfSpirit          = Item("Requiem of Spirit",          ITEMTYPE_SONG,     0xBE, true, &RequiemOfSpirit,  REQUIEM_OF_SPIRIT);
Item I_NocturneOfShadow         = Item("Nocturne of Shadow",         ITEMTYPE_SONG,     0xBF, true, &NocturneOfShadow, NOCTURNE_OF_SHADOW);
Item I_PreludeOfLight           = Item("Prelude of Light",           ITEMTYPE_SONG,     0xC0, true, &PreludeOfLight,   PRELUDE_OF_LIGHT);

//Maps and Compasses
Item DekuTree_Map               = Item("Deku Tree Map",              ITEMTYPE_MAP,      0xA5, false, &noVariable, MAP);
Item DodongosCavern_Map         = Item("Dodongo's Cavern Map",       ITEMTYPE_MAP,      0xA6, false, &noVariable, MAP);
Item JabuJabusBelly_Map         = Item("Jabu Jabu's Belly Map",      ITEMTYPE_MAP,      0xA7, false, &noVariable, MAP);
Item ForestTemple_Map           = Item("Forest Temple Map",          ITEMTYPE_MAP,      0xA8, false, &noVariable, MAP);
Item FireTemple_Map             = Item("Fire Temple Map",            ITEMTYPE_MAP,      0xA9, false, &noVariable, MAP);
Item WaterTemple_Map            = Item("Water Temple Map",           ITEMTYPE_MAP,      0xAA, false, &noVariable, MAP);
Item SpiritTemple_Map           = Item("Spirit Temple Map",          ITEMTYPE_MAP,      0xAB, false, &noVariable, MAP);
Item ShadowTemple_Map           = Item("Shadow Temple Map",          ITEMTYPE_MAP,      0xAC, false, &noVariable, MAP);
Item BottomOfTheWell_Map        = Item("Bottom of the Well Map",     ITEMTYPE_MAP,      0xAD, false, &noVariable, MAP);
Item IceCavern_Map              = Item("Ice Cavern Map",             ITEMTYPE_MAP,      0xAE, false, &noVariable, MAP);

Item DekuTree_Compass           = Item("Deku Tree Compass",          ITEMTYPE_COMPASS,  0x9B, false, &noVariable, COMPASS);
Item DodongosCavern_Compass     = Item("Dodongo's Cavern Compass",   ITEMTYPE_COMPASS,  0x9C, false, &noVariable, COMPASS);
Item JabuJabusBelly_Compass     = Item("Jabu Jabu's Belly Compass",  ITEMTYPE_COMPASS,  0x9D, false, &noVariable, COMPASS);
Item ForestTemple_Compass       = Item("Forest Temple Compass",      ITEMTYPE_COMPASS,  0x9E, false, &noVariable, COMPASS);
Item FireTemple_Compass         = Item("Fire Temple Compass",        ITEMTYPE_COMPASS,  0x9F, false, &noVariable, COMPASS);
Item WaterTemple_Compass        = Item("Water Temple Compass",       ITEMTYPE_COMPASS,  0xA0, false, &noVariable, COMPASS);
Item SpiritTemple_Compass       = Item("Spirit Temple Compass",      ITEMTYPE_COMPASS,  0xA1, false, &noVariable, COMPASS);
Item ShadowTemple_Compass       = Item("Shadow Temple Compass",      ITEMTYPE_COMPASS,  0xA2, false, &noVariable, COMPASS);
Item BottomOfTheWell_Compass    = Item("Bottom of the Well Compass", ITEMTYPE_COMPASS,  0xA3, false, &noVariable, COMPASS);
Item IceCavern_Compass          = Item("Ice Cavern Compass",         ITEMTYPE_COMPASS,  0xA4, false, &noVariable, COMPASS);

//Boss Keys
Item ForestTemple_BossKey       = Item("Forest Temple Boss Key",     ITEMTYPE_BOSSKEY,  0x95, true, &BossKeyForestTemple, BOSS_KEY);
Item FireTemple_BossKey         = Item("Fire Temple Boss Key",       ITEMTYPE_BOSSKEY,  0x96, true, &BossKeyFireTemple,   BOSS_KEY);
Item WaterTemple_BossKey        = Item("Water Temple Boss Key",      ITEMTYPE_BOSSKEY,  0x97, true, &BossKeyWaterTemple,  BOSS_KEY);
Item SpiritTemple_BossKey       = Item("Spirit Temple Boss Key",     ITEMTYPE_BOSSKEY,  0x98, true, &BossKeySpiritTemple, BOSS_KEY);
Item ShadowTemple_BossKey       = Item("Shadow Temple Boss Key",     ITEMTYPE_BOSSKEY,  0x99, true, &BossKeyShadowTemple, BOSS_KEY);
Item GanonsCastle_BossKey       = Item("Ganon's Castle Boss Key",    ITEMTYPE_BOSSKEY,  0x9A, true, &BossKeyGanonsCastle, GANONS_CASTLE_BOSS_KEY);

//Small Keys
Item ForestTemple_SmallKey          = Item("Forest Temple Small Key",           ITEMTYPE_SMALLKEY,          0xAF, true, &ForestTempleKeys,          SMALL_KEY);
Item FireTemple_SmallKey            = Item("Fire Temple Small Key",             ITEMTYPE_SMALLKEY,          0xB0, true, &FireTempleKeys,            SMALL_KEY);
Item WaterTemple_SmallKey           = Item("Water Temple Small Key",            ITEMTYPE_SMALLKEY,          0xB1, true, &WaterTempleKeys,           SMALL_KEY);
Item SpiritTemple_SmallKey          = Item("Spirit Temple Small Key",           ITEMTYPE_SMALLKEY,          0xB2, true, &SpiritTempleKeys,          SMALL_KEY);
Item ShadowTemple_SmallKey          = Item("Shadow Temple Small Key",           ITEMTYPE_SMALLKEY,          0xB3, true, &ShadowTempleKeys,          SMALL_KEY);
Item BottomOfTheWell_SmallKey       = Item("Bottom of the Well Small Key",      ITEMTYPE_SMALLKEY,          0xB4, true, &BottomOfTheWellKeys,       SMALL_KEY);
Item GerudoTrainingGrounds_SmallKey = Item("Gerudo Training Grounds Small Key", ITEMTYPE_SMALLKEY,          0xB5, true, &GerudoTrainingGroundsKeys, SMALL_KEY);
Item GerudoFortress_SmallKey        = Item("Gerudo Fortress Small Key",         ITEMTYPE_FORTRESS_SMALLKEY, 0xB6, true, &GerudoFortressKeys,        GERUDO_FORTRESS_SMALL_KEY);
Item GanonsCastle_SmallKey          = Item("Ganon's Castle Small Key",          ITEMTYPE_SMALLKEY,          0xB7, true, &GanonsCastleKeys,          SMALL_KEY);

//Stones and Medallions
Item I_KokiriEmerald            = Item("Kokiri Emerald",   ITEMTYPE_DUNGEONREWARD, 0xCB,  true, &KokiriEmerald,   KOKIRI_EMERALD);
Item I_GoronRuby                = Item("Goron Ruby",       ITEMTYPE_DUNGEONREWARD, 0xCC,  true, &GoronRuby,       GORON_RUBY);
Item I_ZoraSaphhire             = Item("Zora Sapphire",    ITEMTYPE_DUNGEONREWARD, 0xCD,  true, &ZoraSapphire,    ZORA_SAPPHIRE);
Item I_ForestMedallion          = Item("Forest Medallion", ITEMTYPE_DUNGEONREWARD, 0xCE,  true, &ForestMedallion, FOREST_MEDALLION);
Item I_FireMedallion            = Item("Fire Medallion",   ITEMTYPE_DUNGEONREWARD, 0xCF,  true, &FireMedallion,   FIRE_MEDALLION);
Item I_WaterMedallion           = Item("Water Medallion",  ITEMTYPE_DUNGEONREWARD, 0xD0,  true, &WaterMedallion,  WATER_MEDALLION);
Item I_SpiritMedallion          = Item("Spirit Medallion", ITEMTYPE_DUNGEONREWARD, 0xD1,  true, &SpiritMedallion, SPIRIT_MEDALLION);
Item I_ShadowMedallion          = Item("Shadow Medallion", ITEMTYPE_DUNGEONREWARD, 0xD2,  true, &ShadowMedallion, SHADOW_MEDALLION);
Item I_LightMedallion           = Item("Light Medallion",  ITEMTYPE_DUNGEONREWARD, 0xD3,  true, &LightMedallion,  LIGHT_MEDALLION);

//Generic Items
Item RecoveryHeart              = Item("Recovery Heart",   ITEMTYPE_ITEM, GI_HEART,             false, &noVariable, RECOVERY_HEART);
Item GreenRupee                 = Item("Green Rupee",      ITEMTYPE_ITEM, GI_RUPEE_GREEN,       false, &noVariable, GREEN_RUPEE);
Item BlueRupee                  = Item("Blue Rupee",       ITEMTYPE_ITEM, GI_RUPEE_BLUE,        false, &noVariable, BLUE_RUPEE);
Item RedRupee                   = Item("Red Rupee",        ITEMTYPE_ITEM, GI_RUPEE_RED,         false, &noVariable, RED_RUPEE);
Item PurpleRupee                = Item("Purple Rupee",     ITEMTYPE_ITEM, GI_RUPEE_PURPLE,      false, &noVariable, PURPLE_RUPEE);
Item HugeRupee                  = Item("Huge Rupee",       ITEMTYPE_ITEM, GI_RUPEE_GOLD,        false, &noVariable, HUGE_RUPEE);
Item PieceOfHeart               = Item("Piece of Heart",   ITEMTYPE_ITEM, GI_HEART_PIECE,       false, &noVariable, PIECE_OF_HEART);
Item HeartContainer             = Item("Heart Container",  ITEMTYPE_ITEM, GI_HEART_CONTAINER_2, false, &noVariable, HEART_CONTAINER);
Item IceTrap                    = Item("Ice Trap",         ITEMTYPE_ITEM, GI_ICE_TRAP,          false, &noVariable, ICE_TRAP);
Item Milk                       = Item("Milk",             ITEMTYPE_ITEM, GI_MILK,              false, &noVariable, NONE);

//Refills
Item Bombs5                     = Item("Bombs (5)",           ITEMTYPE_ITEM, GI_BOMBS_5,        false, &noVariable,  BOMBS_5);
Item Bombs10                    = Item("Bombs (10)",          ITEMTYPE_ITEM, GI_BOMBS_10,       false, &noVariable,  BOMBS_10);
Item Bombs20                    = Item("Bombs (20)",          ITEMTYPE_ITEM, GI_BOMBS_20,       false, &noVariable,  BOMBS_20);
Item Bombchu5                   = Item("Bombchu (5)",         ITEMTYPE_ITEM, GI_BOMBCHUS_5,     true,  &Bombchus5,   BOMBCHU_5);
Item Bombchu10                  = Item("Bombchu (10)",        ITEMTYPE_ITEM, GI_BOMBCHUS_10,    true,  &Bombchus10,  BOMBCHU_10);
Item Bombchu20                  = Item("Bombchu (20)",        ITEMTYPE_ITEM, GI_BOMBCHUS_20,    true,  &Bombchus20,  BOMBCHU_20);
Item I_BombchuDrop              = Item("Bombchu Drop",        ITEMTYPE_DROP, GI_BOMBCHUS_10,    true,  &BombchuDrop, NONE);
Item Arrows5                    = Item("Arrows (5)",          ITEMTYPE_ITEM, GI_ARROWS_SMALL,   false, &noVariable,  ARROWS_5);
Item Arrows10                   = Item("Arrows (10)",         ITEMTYPE_ITEM, GI_ARROWS_MEDIUM,  false, &noVariable,  ARROWS_10);
Item Arrows30                   = Item("Arrows (30)",         ITEMTYPE_ITEM, GI_ARROWS_LARGE,   false, &noVariable,  ARROWS_30);
Item DekuNuts5                  = Item("Deku Nuts (5)",       ITEMTYPE_ITEM, GI_NUTS_5,         false, &noVariable,  DEKU_NUTS_5);
Item DekuNuts10                 = Item("Deku Nuts (10)",      ITEMTYPE_ITEM, GI_NUTS_10,        false, &noVariable,  DEKU_NUTS_10);
Item DekuSeeds30                = Item("Deku Seeds (30)",     ITEMTYPE_ITEM, GI_SEEDS_30,       false, &noVariable,  DEKU_SEEDS_30);
Item DekuStick1                 = Item("Deku Stick (1)",      ITEMTYPE_ITEM, GI_STICKS_1,       false, &noVariable,  DEKU_STICK_1);
Item RedPotionRefill            = Item("Red Potion Refill",   ITEMTYPE_ITEM, GI_POTION_RED,     false, &noVariable,  NONE);
Item GreenPotionRefill          = Item("Green Potion Refill", ITEMTYPE_ITEM, GI_POTION_GREEN,   false, &noVariable,  NONE);
Item BluePotionRefill           = Item("Blue Potion Refill",  ITEMTYPE_ITEM, GI_POTION_BLUE,    false, &noVariable,  NONE);


//Treasure Game
Item TreasureGameHeart          = Item("Piece of Heart (Treasure Chest Minigame)", ITEMTYPE_ITEM, GI_HEART_PIECE_WIN,  false, &noVariable, TREASURE_GAME_HEART);
Item TreasureGameGreenRupee     = Item("Green Rupee (Treasure Chest Minigame)",    ITEMTYPE_ITEM, GI_RUPEE_GREEN_LOSE, false, &noVariable, TREASURE_GAME_GREEN_RUPEE);

//Shop Items                                                                                                                            price
Item BuyDekuNut5                = Item("Buy Deku Nut (5)",    ITEMTYPE_SHOP, 0x00, true,  &Nuts,           DEKU_NUTS_5,            15);
Item BuyArrows30                = Item("Buy Arrows (30)",     ITEMTYPE_SHOP, 0x01, false, &noVariable,     ARROWS_30,              60);
Item BuyArrows50                = Item("Buy Arrows (50)",     ITEMTYPE_SHOP, 0x02, false, &noVariable,     ARROWS_30,              90);
Item BuyBombs525                = Item("Buy Bombs (5) [25]",  ITEMTYPE_SHOP, 0x03, false, &noVariable,     BOMBS_5,                25);
Item BuyDekuNut10               = Item("Buy Deku Nut (10)",   ITEMTYPE_SHOP, 0x04, true,  &Nuts,           DEKU_NUTS_10,           30);
Item BuyDekuStick1              = Item("Buy Deku Stick (1)",  ITEMTYPE_SHOP, 0x05, true,  &Sticks,         DEKU_STICK_1,           10);
Item BuyBombs10                 = Item("Buy Bombs (10)",      ITEMTYPE_SHOP, 0x06, false, &noVariable,     BOMBS_10,               50);
Item BuyFish                    = Item("Buy Fish",            ITEMTYPE_SHOP, 0x07, true,  &FishAccess,     BOTTLE_WITH_FISH,      200);
Item BuyRedPotion30             = Item("Buy Red Potion [30]", ITEMTYPE_SHOP, 0x08, false, &noVariable,     NONE,                   30);
Item BuyGreenPotion             = Item("Buy Green Potion",    ITEMTYPE_SHOP, 0x09, false, &noVariable,     NONE,                   30);
Item BuyBluePotion              = Item("Buy Blue Potion",     ITEMTYPE_SHOP, 0x0A, false, &noVariable,     NONE,                  100);
Item BuyHylianShield            = Item("Buy Hylian Shield",   ITEMTYPE_SHOP, 0x0C, true,  &HylianShield,   HYLIAN_SHIELD,          80);
Item BuyDekuShield              = Item("Buy Deku Shield",     ITEMTYPE_SHOP, 0x0D, true,  &DekuShield,     DEKU_SHIELD,            40);
Item BuyGoronTunic              = Item("Buy Goron Tunic",     ITEMTYPE_SHOP, 0x0E, true,  &GoronTunic,     GORON_TUNIC,           200);
Item BuyZoraTunic               = Item("Buy Zora Tunic",      ITEMTYPE_SHOP, 0x0F, true,  &ZoraTunic,      ZORA_TUNIC,            300);
Item BuyHeart                   = Item("Buy Heart",           ITEMTYPE_SHOP, 0x10, false, &noVariable,     RECOVERY_HEART,         10);
Item BuyBombchu10               = Item("Buy Bombchu (10)",    ITEMTYPE_SHOP, 0x15, true,  &BuyBombchus10,  BOMBCHU_10,            99);
Item BuyBombchu20               = Item("Buy Bombchu (20)",    ITEMTYPE_SHOP, 0x16, true,  &BuyBombchus20,  BOMBCHU_20,           180);
Item BuyBombchu5                = Item("Buy Bombchu (5)",     ITEMTYPE_SHOP, 0x18, true,  &BuyBombchus5,   BOMBCHU_5,             60);
Item BuyDekuSeeds30             = Item("Buy Deku Seeds (30)", ITEMTYPE_SHOP, 0x1D, false, &noVariable,     DEKU_SEEDS_30,          30);
Item SoldOut                    = Item("Sold Out",            ITEMTYPE_SHOP, 0x26, false, &noVariable,     NONE,                    0);
Item BuyBlueFire                = Item("Buy Blue Fire",       ITEMTYPE_SHOP, 0x27, true,  &BlueFireAccess, BOTTLE_WITH_BLUE_FIRE, 300);
Item BuyBottleBug               = Item("Buy Bottle Bug",      ITEMTYPE_SHOP, 0x28, true,  &BugsAccess,     BOTTLE_WITH_BUGS,       50);
Item BuyPoe                     = Item("Buy Poe",             ITEMTYPE_SHOP, 0x2A, false, &noVariable,     BOTTLE_WITH_BIG_POE,    30);
Item BuyFairysSpirit            = Item("Buy Fairy's Spirit",  ITEMTYPE_SHOP, 0x2B, true,  &FairyAccess,    BOTTLE_WITH_FAIRY,      50);
Item BuyArrows10                = Item("Buy Arrows (10)",     ITEMTYPE_SHOP, 0x2C, false, &noVariable,     ARROWS_10,              20);
Item BuyBombs20                 = Item("Buy Bombs (20)",      ITEMTYPE_SHOP, 0x2D, false, &noVariable,     BOMBS_20,               80);
Item BuyBombs30                 = Item("Buy Bombs (30)",      ITEMTYPE_SHOP, 0x2E, false, &noVariable,     BOMBS_20,              120);
Item BuyBombs535                = Item("Buy Bombs (5) [35]",  ITEMTYPE_SHOP, 0x2F, false, &noVariable,     BOMBS_5,                35);
Item BuyRedPotion40             = Item("Buy Red Potion [40]", ITEMTYPE_SHOP, 0x30, false, &noVariable,     NONE,                   40);
Item BuyRedPotion50             = Item("Buy Red Potion [50]", ITEMTYPE_SHOP, 0x31, false, &noVariable,     NONE,                   50);
