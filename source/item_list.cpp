#include "item_list.hpp"

#include "logic.hpp"
#include "settings.hpp"
#include "../code/include/z3D/z3Ditem.h"
#include <vector>

using namespace Logic;
using namespace Settings;

// Effects to be run when an item is placed
bool none = false;

Item NoItem = Item("No Item", ITEMTYPE_EVENT,   GI_RUPEE_GREEN,   false, &none);
Item I_Triforce = Item("Triforce", ITEMTYPE_EVENT, GI_RUPEE_RED_LOSE, false, &none);

//Specific Advancement Items         // name              type           getItemId          advancement logic variable
Item I_KokiriSword              = Item("Kokiri Sword",    ITEMTYPE_ITEM, GI_SWORD_KOKIRI,   true,  &KokiriSword);
Item I_BiggoronSword            = Item("Biggoron Sword",  ITEMTYPE_ITEM, GI_SWORD_BGS,      true,  &none);
Item I_DekuShield               = Item("Deku Shield",     ITEMTYPE_ITEM, GI_SHIELD_DEKU,    false, &none);
Item I_HylianShield             = Item("Hylian Shield",   ITEMTYPE_ITEM, GI_SHIELD_HYLIAN,  false, &none);
Item I_MirrorShield             = Item("Mirror Shield",   ITEMTYPE_ITEM, GI_SHIELD_MIRROR,  true,  &MirrorShield);
Item I_Boomerang                = Item("Boomerang",       ITEMTYPE_ITEM, GI_BOOMERANG,      true,  &Boomerang);
Item I_ZeldasLetter             = Item("Zelda's Letter",  ITEMTYPE_ITEM, GI_LETTER_ZELDA,   true,  &ZeldasLetter);
Item I_WeirdEgg                 = Item("Weird Egg",       ITEMTYPE_ITEM, GI_WEIRD_EGG,      true,  &WeirdEgg);
Item I_LensOfTruth              = Item("Lens of Truth",   ITEMTYPE_ITEM, GI_LENS,           true,  &LensOfTruth);
Item I_MegatonHammer            = Item("Megaton Hammer",  ITEMTYPE_ITEM, GI_HAMMER,         true,  &Hammer);
Item I_IronBoots                = Item("Iron Boots",      ITEMTYPE_ITEM, GI_BOOTS_IRON,     true,  &IronBoots);
Item I_HoverBoots               = Item("Hover Boots",     ITEMTYPE_ITEM, GI_BOOTS_HOVER,    true,  &HoverBoots);
Item I_ShardOfAgony             = Item("Shard of Agony",  ITEMTYPE_ITEM, GI_STONE_OF_AGONY, true,  &ShardOfAgony);
Item I_DinsFire                 = Item("Din's Fire",      ITEMTYPE_ITEM, GI_DINS_FIRE,      true,  &DinsFire);
Item I_FaroresWind              = Item("Farore's Wind",   ITEMTYPE_ITEM, GI_FARORES_WIND,   true,  &FaroresWind);
Item I_NayrusLove               = Item("Nayru's Love",    ITEMTYPE_ITEM, GI_NAYRUS_LOVE,    true,  &NayrusLove);
Item I_FireArrows               = Item("Fire Arrows",     ITEMTYPE_ITEM, GI_ARROW_FIRE,     true,  &FireArrows);
Item I_IceArrows                = Item("Ice Arrows",      ITEMTYPE_ITEM, GI_ARROW_ICE,      true,  &IceArrows);
Item I_LightArrows              = Item("Light Arrows",    ITEMTYPE_ITEM, GI_ARROW_LIGHT,    true,  &LightArrows);
Item I_GoronTunic               = Item("Goron Tunic",     ITEMTYPE_ITEM, GI_TUNIC_GORON,    true,  &GoronTunic);
Item I_ZoraTunic                = Item("Zora Tunic",      ITEMTYPE_ITEM, GI_TUNIC_ZORA,     true,  &ZoraTunic);
Item I_GerudoToken              = Item("Gerudo Token",    ITEMTYPE_ITEM, GI_GERUDO_CARD,    true,  &GerudoToken);
Item I_MagicBean                = Item("Magic Bean",      ITEMTYPE_ITEM, GI_BEAN,           true,  &MagicBean);
Item I_MagicBeanPack            = Item("Magic Bean Pack", ITEMTYPE_ITEM, 0xC9,              true,  &MagicBeanPack);
Item I_DoubleDefense            = Item("Double Defense",  ITEMTYPE_ITEM, 0xB8,              true,  &none);

Item I_PocketEgg                = Item("Pocket Egg",      ITEMTYPE_ITEM, GI_POCKET_EGG,     true, &PocketEgg);
Item I_PocketCucco              = Item("Pocket Cucco",    ITEMTYPE_ITEM, GI_POCKET_CUCCO,   true, &PocketCucco);
Item I_Cojiro                   = Item("Cojiro",          ITEMTYPE_ITEM, GI_COJIRO,         true, &Cojiro);
Item I_OddMushroom              = Item("Odd Mushroom",    ITEMTYPE_ITEM, GI_ODD_MUSHROOM,   true, &OddMushroom);
Item I_OddPoultice              = Item("Odd Poultice",    ITEMTYPE_ITEM, GI_ODD_POTION,     true, &OddPoultice);
Item I_PoachersSaw              = Item("Poachers Saw",    ITEMTYPE_ITEM, GI_SAW,            true, &PoachersSaw);
Item I_BrokenSword              = Item("Broken Sword",    ITEMTYPE_ITEM, GI_SWORD_BROKEN,   true, &BrokenSword);
Item I_Prescription             = Item("Prescription",    ITEMTYPE_ITEM, GI_PERSCRIPTION,   true, &Prescription);
Item I_EyeballFrog              = Item("Eyeball Frog",    ITEMTYPE_ITEM, GI_FROG,           true, &EyeballFrog);
Item I_Eyedrops                 = Item("Eyedrops",        ITEMTYPE_ITEM, GI_EYEDROPS,       true, &Eyedrops);
Item I_ClaimCheck               = Item("Claim Check",     ITEMTYPE_ITEM, GI_CLAIM_CHECK,    true, &ClaimCheck);

Item GoldSkulltulaToken         = Item("Gold Skulltula Token", ITEMTYPE_TOKEN, GI_SKULL_TOKEN, true, &GoldSkulltulaTokens);

//Progression Items
Item I_ProgressiveHookshot      = Item("Progressive Hookshot",       ITEMTYPE_ITEM,     0x80, true,  &ProgressiveHookshot);
Item I_ProgressiveStrength      = Item("Progressive Strength",       ITEMTYPE_ITEM,     0x81, true,  &ProgressiveStrength);
Item I_ProgressiveBombBag       = Item("Progressive Bomb Bag",       ITEMTYPE_ITEM,     0x82, true,  &ProgressiveBombBag);
Item I_ProgressiveBow           = Item("Progressive Bow",            ITEMTYPE_ITEM,     0x83, true,  &ProgressiveBow);
Item I_ProgressiveBulletBag     = Item("Progressive Bullet Bag",     ITEMTYPE_ITEM,     0x84, true,  &ProgressiveBulletBag);
Item I_ProgressiveWallet        = Item("Progressive Wallet",         ITEMTYPE_ITEM,     0x85, true,  &ProgressiveWallet);
Item I_ProgressiveScale         = Item("Progressive Scale",          ITEMTYPE_ITEM,     0x86, true,  &ProgressiveScale);
Item I_ProgressiveNutCapacity   = Item("Progressive Nut Upgrade",    ITEMTYPE_ITEM,     0x87, false, &none);
Item I_ProgressiveStickCapacity = Item("Progressive Stick Upgrade",  ITEMTYPE_ITEM,     0x88, false, &none);
Item I_ProgressiveBombchus      = Item("Progressive Bombchus",       ITEMTYPE_ITEM,     0x89, true,  &Bombchus);
Item I_ProgressiveMagic         = Item("Progressive Magic",          ITEMTYPE_ITEM,     0x8A, true,  &ProgressiveMagic);
Item I_ProgressiveOcarina       = Item("Progressive Ocarina",        ITEMTYPE_ITEM,     0x8B, true,  &ProgressiveOcarina);

//Bottles
Item I_EmptyBottle              = Item("Empty Bottle",               ITEMTYPE_ITEM,     0x0F, true, &HasBottle);
Item I_MilkBottle               = Item("Bottle with Milk",           ITEMTYPE_ITEM,     0x14, true, &HasBottle);
Item I_RedPotionBottle          = Item("Bottle with Red Potion",     ITEMTYPE_ITEM,     0x8C, true, &HasBottle);
Item I_GreenPotionBottle        = Item("Bottle with Green Potion",   ITEMTYPE_ITEM,     0x8D, true, &HasBottle);
Item I_BluePotionBottle         = Item("Bottle with Blue Potion",    ITEMTYPE_ITEM,     0x8E, true, &HasBottle);
Item I_FairyBottle              = Item("Bottle with Fairy",          ITEMTYPE_ITEM,     0x8F, true, &HasBottle);
Item I_FishBottle               = Item("Bottle with Fish",           ITEMTYPE_ITEM,     0x90, true, &HasBottle);
Item I_BlueFireBottle           = Item("Bottle with Blue Fire",      ITEMTYPE_ITEM,     0x91, true, &HasBottle);
Item I_BugsBottle               = Item("Bottle with Bugs",           ITEMTYPE_ITEM,     0x92, true, &HasBottle);
Item I_PoeBottle                = Item("Bottle with Poe",            ITEMTYPE_ITEM,     0x94, true, &HasBottle);

//Special bottles that can't immediately dump contents
Item I_RutosLetter              = Item("Rutos Letter",               ITEMTYPE_ITEM,     0x15, true, &RutosLetter);
Item I_BigPoeBottle             = Item("Bottle with Big Poe",        ITEMTYPE_ITEM,     0x93, true, &BottleWithBigPoe);

//Songs
Item I_ZeldasLullaby            = Item("Zelda's Lullaby",            ITEMTYPE_SONG,     0xC1, true, &ZeldasLullaby);
Item I_EponasSong               = Item("Epona's Song",               ITEMTYPE_SONG,     0xC2, true, &EponasSong);
Item I_SariasSong               = Item("Saria's Song",               ITEMTYPE_SONG,     0xC3, true, &SariasSong);
Item I_SunsSong                 = Item("Sun's Song",                 ITEMTYPE_SONG,     0xC4, true, &SunsSong);
Item I_SongOfTime               = Item("Song of Time",               ITEMTYPE_SONG,     0xC5, true, &SongOfTime);
Item I_SongOfStorms             = Item("Song of Storms",             ITEMTYPE_SONG,     0xC6, true, &SongOfStorms);
Item I_MinuetOfForest           = Item("Minuet of Forest",           ITEMTYPE_SONG,     0xBB, true, &MinuetOfForest);
Item I_BoleroOfFire             = Item("Bolero of Fire",             ITEMTYPE_SONG,     0xBC, true, &BoleroOfFire);
Item I_SerenadeOfWater          = Item("Serenade of Water",          ITEMTYPE_SONG,     0xBD, true, &SerenadeOfWater);
Item I_RequiemOfSpirit          = Item("Requiem of Spirit",          ITEMTYPE_SONG,     0xBE, true, &RequiemOfSpirit);
Item I_NocturneOfShadow         = Item("Nocturne of Shadow",         ITEMTYPE_SONG,     0xBF, true, &NocturneOfShadow);
Item I_PreludeOfLight           = Item("Prelude of Light",           ITEMTYPE_SONG,     0xC0, true, &PreludeOfLight);

//Maps and Compasses
Item DekuTree_Map               = Item("Deku Tree Map",              ITEMTYPE_MAP,      0xA5, false, &none);
Item DodongosCavern_Map         = Item("Dodongo's Cavern Map",       ITEMTYPE_MAP,      0xA6, false, &none);
Item JabuJabusBelly_Map         = Item("Jabu Jabu's Belly Map",      ITEMTYPE_MAP,      0xA7, false, &none);
Item ForestTemple_Map           = Item("Forest Temple Map",          ITEMTYPE_MAP,      0xA8, false, &none);
Item FireTemple_Map             = Item("Fire Temple Map",            ITEMTYPE_MAP,      0xA9, false, &none);
Item WaterTemple_Map            = Item("Water Temple Map",           ITEMTYPE_MAP,      0xAA, false, &none);
Item SpiritTemple_Map           = Item("Spirit Temple Map",          ITEMTYPE_MAP,      0xAB, false, &none);
Item ShadowTemple_Map           = Item("Shadow Temple Map",          ITEMTYPE_MAP,      0xAC, false, &none);
Item BottomOfTheWell_Map        = Item("Bottom of the Well Map",     ITEMTYPE_MAP,      0xAD, false, &none);
Item IceCavern_Map              = Item("Ice Cavern Map",             ITEMTYPE_MAP,      0xAE, false, &none);

Item DekuTree_Compass           = Item("Deku Tree Compass",          ITEMTYPE_COMPASS,  0x9B, false, &none);
Item DodongosCavern_Compass     = Item("Dodongo's Cavern Compass",   ITEMTYPE_COMPASS,  0x9C, false, &none);
Item JabuJabusBelly_Compass     = Item("Jabu Jabu's Belly Compass",  ITEMTYPE_COMPASS,  0x9D, false, &none);
Item ForestTemple_Compass       = Item("Forest Temple Compass",      ITEMTYPE_COMPASS,  0x9E, false, &none);
Item FireTemple_Compass         = Item("Fire Temple Compass",        ITEMTYPE_COMPASS,  0x9F, false, &none);
Item WaterTemple_Compass        = Item("Water Temple Compass",       ITEMTYPE_COMPASS,  0xA0, false, &none);
Item SpiritTemple_Compass       = Item("Spirit Temple Compass",      ITEMTYPE_COMPASS,  0xA1, false, &none);
Item ShadowTemple_Compass       = Item("Shadow Temple Compass",      ITEMTYPE_COMPASS,  0xA2, false, &none);
Item BottomOfTheWell_Compass    = Item("Bottom of the Well Compass", ITEMTYPE_COMPASS,  0xA3, false, &none);
Item IceCavern_Compass          = Item("Ice Cavern Compass",         ITEMTYPE_COMPASS,  0xA4, false, &none);

//Boss Keys
Item ForestTemple_BossKey       = Item("Forest Temple Boss Key",     ITEMTYPE_BOSSKEY,  0x95, true, &BossKeyForestTemple);
Item FireTemple_BossKey         = Item("Fire Temple Boss Key",       ITEMTYPE_BOSSKEY,  0x96, true, &BossKeyFireTemple);
Item WaterTemple_BossKey        = Item("Water Temple Boss Key",      ITEMTYPE_BOSSKEY,  0x97, true, &BossKeyWaterTemple);
Item SpiritTemple_BossKey       = Item("Spirit Temple Boss Key",     ITEMTYPE_BOSSKEY,  0x98, true, &BossKeySpiritTemple);
Item ShadowTemple_BossKey       = Item("Shadow Temple Boss Key",     ITEMTYPE_BOSSKEY,  0x99, true, &BossKeyShadowTemple);
Item GanonsCastle_BossKey       = Item("Ganon's Castle Boss Key",    ITEMTYPE_BOSSKEY,  0x9A, true, &BossKeyGanonsCastle);

//Small Keys
Item ForestTemple_SmallKey          = Item("Forest Temple Small Key",           ITEMTYPE_SMALLKEY,          0xAF, true, &ForestTempleKeys);
Item FireTemple_SmallKey            = Item("Fire Temple Small Key",             ITEMTYPE_SMALLKEY,          0xB0, true, &FireTempleKeys);
Item WaterTemple_SmallKey           = Item("Water Temple Small Key",            ITEMTYPE_SMALLKEY,          0xB1, true, &WaterTempleKeys);
Item SpiritTemple_SmallKey          = Item("Spirit Temple Small Key",           ITEMTYPE_SMALLKEY,          0xB2, true, &SpiritTempleKeys);
Item ShadowTemple_SmallKey          = Item("Shadow Temple Small Key",           ITEMTYPE_SMALLKEY,          0xB3, true, &ShadowTempleKeys);
Item BottomOfTheWell_SmallKey       = Item("Bottom of the Well Small Key",      ITEMTYPE_SMALLKEY,          0xB4, true, &BottomOfTheWellKeys);
Item GerudoTrainingGrounds_SmallKey = Item("Gerudo Training Grounds Small Key", ITEMTYPE_SMALLKEY,          0xB5, true, &GerudoTrainingGroundsKeys);
Item GerudoFortress_SmallKey        = Item("Gerudo Fortress Small Key",         ITEMTYPE_FORTRESS_SMALLKEY, 0xB6, true, &GerudoFortressKeys);
Item GanonsCastle_SmallKey          = Item("Ganon's Castle Small Key",          ITEMTYPE_SMALLKEY,          0xB7, true, &GanonsCastleKeys);

//Stones and Medallions
Item I_KokiriEmerald            = Item("Kokiri Emerald",   ITEMTYPE_DUNGEONREWARD, 0xCB,  true, &KokiriEmerald);
Item I_GoronRuby                = Item("Goron Ruby",       ITEMTYPE_DUNGEONREWARD, 0xCC,  true, &GoronRuby);
Item I_ZoraSaphhire             = Item("Zora Sapphire",    ITEMTYPE_DUNGEONREWARD, 0xCD,  true, &ZoraSapphire);
Item I_ForestMedallion          = Item("Forest Medallion", ITEMTYPE_DUNGEONREWARD, 0xCE,  true, &ForestMedallion);
Item I_FireMedallion            = Item("Fire Medallion",   ITEMTYPE_DUNGEONREWARD, 0xCF,  true, &FireMedallion);
Item I_WaterMedallion           = Item("Water Medallion",  ITEMTYPE_DUNGEONREWARD, 0xD0,  true, &WaterMedallion);
Item I_SpiritMedallion          = Item("Spirit Medallion", ITEMTYPE_DUNGEONREWARD, 0xD1,  true, &SpiritMedallion);
Item I_ShadowMedallion          = Item("Shadow Medallion", ITEMTYPE_DUNGEONREWARD, 0xD2,  true, &ShadowMedallion);
Item I_LightMedallion           = Item("Light Medallion",  ITEMTYPE_DUNGEONREWARD, 0xD3,  true, &LightMedallion);

//Generic Items
Item RecoveryHeart              = Item("Recovery Heart",   ITEMTYPE_ITEM, GI_HEART,             false, &none);
Item GreenRupee                 = Item("Green Rupee",      ITEMTYPE_ITEM, GI_RUPEE_GREEN,       false, &none);
Item BlueRupee                  = Item("Blue Rupee",       ITEMTYPE_ITEM, GI_RUPEE_BLUE,        false, &none);
Item RedRupee                   = Item("Red Rupee",        ITEMTYPE_ITEM, GI_RUPEE_RED,         false, &none);
Item PurpleRupee                = Item("Purple Rupee",     ITEMTYPE_ITEM, GI_RUPEE_PURPLE,      false, &none);
Item HugeRupee                  = Item("Huge Rupee",       ITEMTYPE_ITEM, GI_RUPEE_GOLD,        false, &none);
Item PieceOfHeart               = Item("Piece of Heart",   ITEMTYPE_ITEM, GI_HEART_PIECE,       false, &none);
Item HeartContainer             = Item("Heart Container",  ITEMTYPE_ITEM, GI_HEART_CONTAINER_2, false, &none);
Item IceTrap                    = Item("Ice Trap",         ITEMTYPE_ITEM, GI_ICE_TRAP,          false, &none);
Item Milk                       = Item("Milk",             ITEMTYPE_ITEM, GI_MILK,              false, &none);

//Refills
Item Bombs5                     = Item("Bombs (5)",           ITEMTYPE_ITEM, GI_BOMBS_5,        false, &none);
Item Bombs10                    = Item("Bombs (10)",          ITEMTYPE_ITEM, GI_BOMBS_10,       false, &none);
Item Bombs20                    = Item("Bombs (20)",          ITEMTYPE_ITEM, GI_BOMBS_20,       false, &none);
Item Bombs30                    = Item("Bombs (30)",          ITEMTYPE_ITEM, GI_BOMBS_30,       false, &none);
Item Bombchu5                   = Item("Bombchu (5)",         ITEMTYPE_ITEM, GI_BOMBCHUS_5,     true,  &Bombchus5);
Item Bombchu10                  = Item("Bombchu (10)",        ITEMTYPE_ITEM, GI_BOMBCHUS_10,    true,  &Bombchus10);
Item Bombchu20                  = Item("Bombchu (20)",        ITEMTYPE_ITEM, GI_BOMBCHUS_20,    true,  &Bombchus20);
Item I_BombchuDrop              = Item("Bombchu Drop",        ITEMTYPE_DROP, GI_BOMBCHUS_10,    true,  &BombchuDrop);
Item Arrows5                    = Item("Arrows (5)",          ITEMTYPE_ITEM, GI_ARROWS_SMALL,   false, &none);
Item Arrows10                   = Item("Arrows (10)",         ITEMTYPE_ITEM, GI_ARROWS_MEDIUM,  false, &none);
Item Arrows30                   = Item("Arrows (30)",         ITEMTYPE_ITEM, GI_ARROWS_LARGE,   false, &none);
Item DekuNuts5                  = Item("Deku Nuts (5)",       ITEMTYPE_ITEM, GI_NUTS_5,         false, &none);
Item DekuNuts10                 = Item("Deku Nuts (10)",      ITEMTYPE_ITEM, GI_NUTS_10,        false, &none);
Item DekuSeeds30                = Item("Deku Seeds (30)",     ITEMTYPE_ITEM, GI_SEEDS_30,       false, &none);
Item DekuStick1                 = Item("Deku Stick (1)",      ITEMTYPE_ITEM, GI_STICKS_1,       false, &none);
Item RedPotionRefill            = Item("Red Potion Refill",   ITEMTYPE_ITEM, GI_POTION_RED,     false, &none);
Item GreenPotionRefill          = Item("Green Potion Refill", ITEMTYPE_ITEM, GI_POTION_GREEN,   false, &none);
Item BluePotionRefill           = Item("Blue Potion Refill",  ITEMTYPE_ITEM, GI_POTION_BLUE,    false, &none);


//Treasure Game
Item TreasureGameHeart          = Item("Piece of Heart (Treasure Chest Minigame)", ITEMTYPE_ITEM, GI_HEART_PIECE_WIN, false, &none);
Item TreasureGameGreenRupee     = Item("Green Rupee (Treasure Chest Minigame)",    ITEMTYPE_ITEM, GI_RUPEE_GREEN_LOSE, false, &none);

//Shop Items                                                                                               price
Item BuyDekuNut5                = Item("Buy Deku Nut (5)",    ITEMTYPE_SHOP, 0x00, true,  &Nuts,            15);
Item BuyArrows30                = Item("Buy Arrows (30)",     ITEMTYPE_SHOP, 0x01, false, &none,            60);
Item BuyArrows50                = Item("Buy Arrows (50)",     ITEMTYPE_SHOP, 0x02, false, &none,            90);
Item BuyBombs525                = Item("Buy Bombs (5) [25]",  ITEMTYPE_SHOP, 0x03, false, &none,            25);
Item BuyDekuNut10               = Item("Buy Deku Nut (10)",   ITEMTYPE_SHOP, 0x04, true,  &Nuts,            30);
Item BuyDekuStick1              = Item("Buy Deku Stick (1)",  ITEMTYPE_SHOP, 0x05, true,  &Sticks,          10);
Item BuyBombs10                 = Item("Buy Bombs (10)",      ITEMTYPE_SHOP, 0x06, false, &none,            50);
Item BuyFish                    = Item("Buy Fish",            ITEMTYPE_SHOP, 0x07, true,  &FishAccess,     200);
Item BuyRedPotion30             = Item("Buy Red Potion [30]", ITEMTYPE_SHOP, 0x08, false, &none,            30);
Item BuyGreenPotion             = Item("Buy Green Potion",    ITEMTYPE_SHOP, 0x09, false, &none,            30);
Item BuyBluePotion              = Item("Buy Blue Potion",     ITEMTYPE_SHOP, 0x0A, false, &none,           100);
Item BuyHylianShield            = Item("Buy Hylian Shield",   ITEMTYPE_SHOP, 0x0C, true,  &HylianShield,    80);
Item BuyDekuShield              = Item("Buy Deku Shield",     ITEMTYPE_SHOP, 0x0D, true,  &DekuShield,      40);
Item BuyGoronTunic              = Item("Buy Goron Tunic",     ITEMTYPE_SHOP, 0x0E, true,  &GoronTunic,     200);
Item BuyZoraTunic               = Item("Buy Zora Tunic",      ITEMTYPE_SHOP, 0x0F, true,  &ZoraTunic,      300);
Item BuyHeart                   = Item("Buy Heart",           ITEMTYPE_SHOP, 0x10, false, &none,            10);
Item BuyBombchu10               = Item("Buy Bombchu (10)",    ITEMTYPE_SHOP, 0x15, true,  &BuyBombchus10,   99);
Item BuyBombchu20               = Item("Buy Bombchu (20)",    ITEMTYPE_SHOP, 0x16, true,  &BuyBombchus20,  180);
Item BuyBombchu5                = Item("Buy Bombchu (5)",     ITEMTYPE_SHOP, 0x18, true,  &BuyBombchus5,    60);
Item BuyDekuSeeds30             = Item("Buy Deku Seeds (30)", ITEMTYPE_SHOP, 0x1D, false, &none,            30);
Item SoldOut                    = Item("Sold Out",            ITEMTYPE_SHOP, 0x26, false, &none,             0);
Item BuyBlueFire                = Item("Buy Blue Fire",       ITEMTYPE_SHOP, 0x27, true,  &BlueFireAccess, 300);
Item BuyBottleBug               = Item("Buy Bottle Bug",      ITEMTYPE_SHOP, 0x28, true,  &BugsAccess,      50);
Item BuyPoe                     = Item("Buy Poe",             ITEMTYPE_SHOP, 0x2A, false, &none,            30);
Item BuyFairysSpirit            = Item("Buy Fairy's Spirit",  ITEMTYPE_SHOP, 0x2B, true,  &FairyAccess,     50);
Item BuyArrows10                = Item("Buy Arrows (10)",     ITEMTYPE_SHOP, 0x2C, false, &none,            20);
Item BuyBombs20                 = Item("Buy Bombs (20)",      ITEMTYPE_SHOP, 0x2D, false, &none,            80);
Item BuyBombs30                 = Item("Buy Bombs (30)",      ITEMTYPE_SHOP, 0x2E, false, &none,           120);
Item BuyBombs535                = Item("Buy Bombs (5) [35]",  ITEMTYPE_SHOP, 0x2F, false, &none,            35);
Item BuyRedPotion40             = Item("Buy Red Potion [40]", ITEMTYPE_SHOP, 0x30, false, &none,            40);
Item BuyRedPotion50             = Item("Buy Red Potion [50]", ITEMTYPE_SHOP, 0x31, false, &none,            50);
