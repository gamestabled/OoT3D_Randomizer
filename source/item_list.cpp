#include "item_list.hpp"

#include "logic.hpp"
#include "settings.hpp"
#include "hint_list.hpp"
#include "../code/include/z3D/z3Ditem.h"
#include <vector>

using namespace Logic;
using namespace Settings;

// Effects to be run when an item is placed
bool none = false;

Item NoItem     = Item("No Item",  ITEMTYPE_EVENT, GI_RUPEE_GREEN,    false, &none, &Hints::NoHintText);
Item I_Triforce = Item("Triforce", ITEMTYPE_EVENT, GI_RUPEE_RED_LOSE, false, &none, &Hints::NoHintText);

//Used as dummy placements for hint locations
Item NoHint     = Item("No Hint",  ITEMTYPE_EVENT, GI_RUPEE_BLUE_LOSE,false, &none, &Hints::NoHintText);
Item HasHint    = Item("Has Hint", ITEMTYPE_EVENT, GI_RUPEE_BLUE_LOSE,false, &none, &Hints::NoHintText);

//Specific Advancement Items         // name                   type            getItemId          advancement logic variable  hint text (hint_list.cpp)
Item I_KokiriSword              = Item("Kokiri Sword",         ITEMTYPE_ITEM,  GI_SWORD_KOKIRI,   true,       &KokiriSword,   &Hints::KokiriSword);
Item I_BiggoronSword            = Item("Biggoron Sword",       ITEMTYPE_ITEM,  GI_SWORD_BGS,      true,       &none,          &Hints::BiggoronSword);
Item I_DekuShield               = Item("Deku Shield",          ITEMTYPE_ITEM,  GI_SHIELD_DEKU,    false,      &none,          &Hints::DekuShield);
Item I_HylianShield             = Item("Hylian Shield",        ITEMTYPE_ITEM,  GI_SHIELD_HYLIAN,  false,      &none,          &Hints::HylianShield);
Item I_MirrorShield             = Item("Mirror Shield",        ITEMTYPE_ITEM,  GI_SHIELD_MIRROR,  true,       &MirrorShield,  &Hints::MirrorShield);
Item I_Boomerang                = Item("Boomerang",            ITEMTYPE_ITEM,  GI_BOOMERANG,      true,       &Boomerang,     &Hints::Boomerang);
Item I_ZeldasLetter             = Item("Zelda's Letter",       ITEMTYPE_ITEM,  GI_LETTER_ZELDA,   true,       &ZeldasLetter,  &Hints::ZeldasLetter);
Item I_WeirdEgg                 = Item("Weird Egg",            ITEMTYPE_ITEM,  GI_WEIRD_EGG,      true,       &WeirdEgg,      &Hints::WeirdEgg);
Item I_LensOfTruth              = Item("Lens of Truth",        ITEMTYPE_ITEM,  GI_LENS,           true,       &LensOfTruth,   &Hints::LensOfTruth);
Item I_MegatonHammer            = Item("Megaton Hammer",       ITEMTYPE_ITEM,  GI_HAMMER,         true,       &Hammer,        &Hints::MegatonHammer);
Item I_IronBoots                = Item("Iron Boots",           ITEMTYPE_ITEM,  GI_BOOTS_IRON,     true,       &IronBoots,     &Hints::IronBoots);
Item I_HoverBoots               = Item("Hover Boots",          ITEMTYPE_ITEM,  GI_BOOTS_HOVER,    true,       &HoverBoots,    &Hints::HoverBoots);
Item I_ShardOfAgony             = Item("Shard of Agony",       ITEMTYPE_ITEM,  GI_STONE_OF_AGONY, true,       &ShardOfAgony,  &Hints::ShardOfAgony);
Item I_DinsFire                 = Item("Din's Fire",           ITEMTYPE_ITEM,  GI_DINS_FIRE,      true,       &DinsFire,      &Hints::DinsFire);
Item I_FaroresWind              = Item("Farore's Wind",        ITEMTYPE_ITEM,  GI_FARORES_WIND,   true,       &FaroresWind,   &Hints::FaroresWind);
Item I_NayrusLove               = Item("Nayru's Love",         ITEMTYPE_ITEM,  GI_NAYRUS_LOVE,    true,       &NayrusLove,    &Hints::NayrusLove);
Item I_FireArrows               = Item("Fire Arrows",          ITEMTYPE_ITEM,  GI_ARROW_FIRE,     true,       &FireArrows,    &Hints::FireArrows);
Item I_IceArrows                = Item("Ice Arrows",           ITEMTYPE_ITEM,  GI_ARROW_ICE,      true,       &IceArrows,     &Hints::IceArrows);
Item I_LightArrows              = Item("Light Arrows",         ITEMTYPE_ITEM,  GI_ARROW_LIGHT,    true,       &LightArrows,   &Hints::LightArrows);
Item I_GoronTunic               = Item("Goron Tunic",          ITEMTYPE_ITEM,  GI_TUNIC_GORON,    true,       &GoronTunic,    &Hints::GoronTunic);
Item I_ZoraTunic                = Item("Zora Tunic",           ITEMTYPE_ITEM,  GI_TUNIC_ZORA,     true,       &ZoraTunic,     &Hints::ZoraTunic);
Item I_GerudoToken              = Item("Gerudo Token",         ITEMTYPE_ITEM,  GI_GERUDO_CARD,    true,       &GerudoToken,   &Hints::GerudoToken);
Item I_MagicBean                = Item("Magic Bean",           ITEMTYPE_ITEM,  GI_BEAN,           true,       &MagicBean,     &Hints::MagicBean);
Item I_MagicBeanPack            = Item("Magic Bean Pack",      ITEMTYPE_ITEM,  0xC9,              true,       &MagicBeanPack, &Hints::MagicBeanPack);
Item I_DoubleDefense            = Item("Double Defense",       ITEMTYPE_ITEM,  0xB8,              true,       &none,          &Hints::DoubleDefense);

Item I_PocketEgg                = Item("Pocket Egg",           ITEMTYPE_ITEM,  GI_POCKET_EGG,     true,       &PocketEgg,     &Hints::PocketEgg);
Item I_PocketCucco              = Item("Pocket Cucco",         ITEMTYPE_ITEM,  GI_POCKET_CUCCO,   true,       &PocketCucco,   &Hints::PocketCucco);
Item I_Cojiro                   = Item("Cojiro",               ITEMTYPE_ITEM,  GI_COJIRO,         true,       &Cojiro,        &Hints::Cojiro);
Item I_OddMushroom              = Item("Odd Mushroom",         ITEMTYPE_ITEM,  GI_ODD_MUSHROOM,   true,       &OddMushroom,   &Hints::OddMushroom);
Item I_OddPoultice              = Item("Odd Poultice",         ITEMTYPE_ITEM,  GI_ODD_POTION,     true,       &OddPoultice,   &Hints::OddPoultice);
Item I_PoachersSaw              = Item("Poachers Saw",         ITEMTYPE_ITEM,  GI_SAW,            true,       &PoachersSaw,   &Hints::PoachersSaw);
Item I_BrokenSword              = Item("Broken Sword",         ITEMTYPE_ITEM,  GI_SWORD_BROKEN,   true,       &BrokenSword,   &Hints::BrokenSword);
Item I_Prescription             = Item("Prescription",         ITEMTYPE_ITEM,  GI_PERSCRIPTION,   true,       &Prescription,  &Hints::Prescription);
Item I_EyeballFrog              = Item("Eyeball Frog",         ITEMTYPE_ITEM,  GI_FROG,           true,       &EyeballFrog,   &Hints::EyeballFrog);
Item I_Eyedrops                 = Item("Eyedrops",             ITEMTYPE_ITEM,  GI_EYEDROPS,       true,       &Eyedrops,      &Hints::Eyedrops);
Item I_ClaimCheck               = Item("Claim Check",          ITEMTYPE_ITEM,  GI_CLAIM_CHECK,    true,       &ClaimCheck,    &Hints::ClaimCheck);

Item GoldSkulltulaToken         = Item("Gold Skulltula Token", ITEMTYPE_TOKEN, GI_SKULL_TOKEN,    true,       &GoldSkulltulaTokens, &Hints::GoldSkulltulaToken);

//Progression Items
Item I_ProgressiveHookshot      = Item("Progressive Hookshot",       ITEMTYPE_ITEM,     0x80, true,  &ProgressiveHookshot,  &Hints::ProgressiveHookshot);
Item I_ProgressiveStrength      = Item("Progressive Strength",       ITEMTYPE_ITEM,     0x81, true,  &ProgressiveStrength,  &Hints::ProgressiveStrength);
Item I_ProgressiveBombBag       = Item("Progressive Bomb Bag",       ITEMTYPE_ITEM,     0x82, true,  &ProgressiveBombBag,   &Hints::ProgressiveBombBag);
Item I_ProgressiveBow           = Item("Progressive Bow",            ITEMTYPE_ITEM,     0x83, true,  &ProgressiveBow,       &Hints::ProgressiveBow);
Item I_ProgressiveBulletBag     = Item("Progressive Bullet Bag",     ITEMTYPE_ITEM,     0x84, true,  &ProgressiveBulletBag, &Hints::ProgressiveBulletBag);
Item I_ProgressiveWallet        = Item("Progressive Wallet",         ITEMTYPE_ITEM,     0x85, true,  &ProgressiveWallet,    &Hints::ProgressiveWallet);
Item I_ProgressiveScale         = Item("Progressive Scale",          ITEMTYPE_ITEM,     0x86, true,  &ProgressiveScale,     &Hints::ProgressiveScale);
Item I_ProgressiveNutCapacity   = Item("Progressive Nut Upgrade",    ITEMTYPE_ITEM,     0x87, false, &none,                 &Hints::ProgressiveNutCapacity);
Item I_ProgressiveStickCapacity = Item("Progressive Stick Upgrade",  ITEMTYPE_ITEM,     0x88, false, &none,                 &Hints::ProgressiveStickCapacity);
Item I_ProgressiveBombchus      = Item("Progressive Bombchus",       ITEMTYPE_ITEM,     0x89, true,  &Bombchus,             &Hints::ProgressiveBombchus);
Item I_ProgressiveMagic         = Item("Progressive Magic",          ITEMTYPE_ITEM,     0x8A, true,  &ProgressiveMagic,     &Hints::ProgressiveMagic);
Item I_ProgressiveOcarina       = Item("Progressive Ocarina",        ITEMTYPE_ITEM,     0x8B, true,  &ProgressiveOcarina,   &Hints::ProgressiveOcarina);

//Bottles
Item I_EmptyBottle              = Item("Empty Bottle",               ITEMTYPE_ITEM,     0x0F, true, &HasBottle, &Hints::EmptyBottle);
Item I_MilkBottle               = Item("Bottle with Milk",           ITEMTYPE_ITEM,     0x14, true, &HasBottle, &Hints::BottleWithMilk);
Item I_RedPotionBottle          = Item("Bottle with Red Potion",     ITEMTYPE_ITEM,     0x8C, true, &HasBottle, &Hints::BottleWithRedPotion);
Item I_GreenPotionBottle        = Item("Bottle with Green Potion",   ITEMTYPE_ITEM,     0x8D, true, &HasBottle, &Hints::BottleWithGreenPotion);
Item I_BluePotionBottle         = Item("Bottle with Blue Potion",    ITEMTYPE_ITEM,     0x8E, true, &HasBottle, &Hints::BottleWithBluePotion);
Item I_FairyBottle              = Item("Bottle with Fairy",          ITEMTYPE_ITEM,     0x8F, true, &HasBottle, &Hints::BottleWithFairy);
Item I_FishBottle               = Item("Bottle with Fish",           ITEMTYPE_ITEM,     0x90, true, &HasBottle, &Hints::BottleWithFish);
Item I_BlueFireBottle           = Item("Bottle with Blue Fire",      ITEMTYPE_ITEM,     0x91, true, &HasBottle, &Hints::BottleWithBlueFire);
Item I_BugsBottle               = Item("Bottle with Bugs",           ITEMTYPE_ITEM,     0x92, true, &HasBottle, &Hints::BottleWithBugs);
Item I_PoeBottle                = Item("Bottle with Poe",            ITEMTYPE_ITEM,     0x94, true, &HasBottle, &Hints::BottleWithPoe);

//Special bottles that can't immediately dump contents
Item I_RutosLetter              = Item("Rutos Letter",               ITEMTYPE_ITEM,     0x15, true, &RutosLetter,      &Hints::RutosLetter);
Item I_BigPoeBottle             = Item("Bottle with Big Poe",        ITEMTYPE_ITEM,     0x93, true, &BottleWithBigPoe, &Hints::BottleWithBigPoe);

//Songs
Item I_ZeldasLullaby            = Item("Zelda's Lullaby",            ITEMTYPE_SONG,     0xC1, true, &ZeldasLullaby,    &Hints::ZeldasLullaby);
Item I_EponasSong               = Item("Epona's Song",               ITEMTYPE_SONG,     0xC2, true, &EponasSong,       &Hints::EponasSong);
Item I_SariasSong               = Item("Saria's Song",               ITEMTYPE_SONG,     0xC3, true, &SariasSong,       &Hints::SariasSong);
Item I_SunsSong                 = Item("Sun's Song",                 ITEMTYPE_SONG,     0xC4, true, &SunsSong,         &Hints::SunsSong);
Item I_SongOfTime               = Item("Song of Time",               ITEMTYPE_SONG,     0xC5, true, &SongOfTime,       &Hints::SongOfTime);
Item I_SongOfStorms             = Item("Song of Storms",             ITEMTYPE_SONG,     0xC6, true, &SongOfStorms,     &Hints::SongOfStorms);
Item I_MinuetOfForest           = Item("Minuet of Forest",           ITEMTYPE_SONG,     0xBB, true, &MinuetOfForest,   &Hints::MinuetOfForest);
Item I_BoleroOfFire             = Item("Bolero of Fire",             ITEMTYPE_SONG,     0xBC, true, &BoleroOfFire,     &Hints::BoleroOfFire);
Item I_SerenadeOfWater          = Item("Serenade of Water",          ITEMTYPE_SONG,     0xBD, true, &SerenadeOfWater,  &Hints::SerenadeOfWater);
Item I_RequiemOfSpirit          = Item("Requiem of Spirit",          ITEMTYPE_SONG,     0xBE, true, &RequiemOfSpirit,  &Hints::RequiemOfSpirit);
Item I_NocturneOfShadow         = Item("Nocturne of Shadow",         ITEMTYPE_SONG,     0xBF, true, &NocturneOfShadow, &Hints::NocturneOfShadow);
Item I_PreludeOfLight           = Item("Prelude of Light",           ITEMTYPE_SONG,     0xC0, true, &PreludeOfLight,   &Hints::PreludeOfLight);

//Maps and Compasses
Item DekuTree_Map               = Item("Deku Tree Map",              ITEMTYPE_MAP,      0xA5, false, &none, &Hints::Map);
Item DodongosCavern_Map         = Item("Dodongo's Cavern Map",       ITEMTYPE_MAP,      0xA6, false, &none, &Hints::Map);
Item JabuJabusBelly_Map         = Item("Jabu Jabu's Belly Map",      ITEMTYPE_MAP,      0xA7, false, &none, &Hints::Map);
Item ForestTemple_Map           = Item("Forest Temple Map",          ITEMTYPE_MAP,      0xA8, false, &none, &Hints::Map);
Item FireTemple_Map             = Item("Fire Temple Map",            ITEMTYPE_MAP,      0xA9, false, &none, &Hints::Map);
Item WaterTemple_Map            = Item("Water Temple Map",           ITEMTYPE_MAP,      0xAA, false, &none, &Hints::Map);
Item SpiritTemple_Map           = Item("Spirit Temple Map",          ITEMTYPE_MAP,      0xAB, false, &none, &Hints::Map);
Item ShadowTemple_Map           = Item("Shadow Temple Map",          ITEMTYPE_MAP,      0xAC, false, &none, &Hints::Map);
Item BottomOfTheWell_Map        = Item("Bottom of the Well Map",     ITEMTYPE_MAP,      0xAD, false, &none, &Hints::Map);
Item IceCavern_Map              = Item("Ice Cavern Map",             ITEMTYPE_MAP,      0xAE, false, &none, &Hints::Map);

Item DekuTree_Compass           = Item("Deku Tree Compass",          ITEMTYPE_COMPASS,  0x9B, false, &none, &Hints::Compass);
Item DodongosCavern_Compass     = Item("Dodongo's Cavern Compass",   ITEMTYPE_COMPASS,  0x9C, false, &none, &Hints::Compass);
Item JabuJabusBelly_Compass     = Item("Jabu Jabu's Belly Compass",  ITEMTYPE_COMPASS,  0x9D, false, &none, &Hints::Compass);
Item ForestTemple_Compass       = Item("Forest Temple Compass",      ITEMTYPE_COMPASS,  0x9E, false, &none, &Hints::Compass);
Item FireTemple_Compass         = Item("Fire Temple Compass",        ITEMTYPE_COMPASS,  0x9F, false, &none, &Hints::Compass);
Item WaterTemple_Compass        = Item("Water Temple Compass",       ITEMTYPE_COMPASS,  0xA0, false, &none, &Hints::Compass);
Item SpiritTemple_Compass       = Item("Spirit Temple Compass",      ITEMTYPE_COMPASS,  0xA1, false, &none, &Hints::Compass);
Item ShadowTemple_Compass       = Item("Shadow Temple Compass",      ITEMTYPE_COMPASS,  0xA2, false, &none, &Hints::Compass);
Item BottomOfTheWell_Compass    = Item("Bottom of the Well Compass", ITEMTYPE_COMPASS,  0xA3, false, &none, &Hints::Compass);
Item IceCavern_Compass          = Item("Ice Cavern Compass",         ITEMTYPE_COMPASS,  0xA4, false, &none, &Hints::Compass);

//Boss Keys
Item ForestTemple_BossKey       = Item("Forest Temple Boss Key",     ITEMTYPE_BOSSKEY,  0x95, true, &BossKeyForestTemple, &Hints::BossKey);
Item FireTemple_BossKey         = Item("Fire Temple Boss Key",       ITEMTYPE_BOSSKEY,  0x96, true, &BossKeyFireTemple,   &Hints::BossKey);
Item WaterTemple_BossKey        = Item("Water Temple Boss Key",      ITEMTYPE_BOSSKEY,  0x97, true, &BossKeyWaterTemple,  &Hints::BossKey);
Item SpiritTemple_BossKey       = Item("Spirit Temple Boss Key",     ITEMTYPE_BOSSKEY,  0x98, true, &BossKeySpiritTemple, &Hints::BossKey);
Item ShadowTemple_BossKey       = Item("Shadow Temple Boss Key",     ITEMTYPE_BOSSKEY,  0x99, true, &BossKeyShadowTemple, &Hints::BossKey);
Item GanonsCastle_BossKey       = Item("Ganon's Castle Boss Key",    ITEMTYPE_BOSSKEY,  0x9A, true, &BossKeyGanonsCastle, &Hints::BossKey);

//Small Keys
Item ForestTemple_SmallKey          = Item("Forest Temple Small Key",           ITEMTYPE_SMALLKEY,          0xAF, true, &ForestTempleKeys,          &Hints::SmallKey);
Item FireTemple_SmallKey            = Item("Fire Temple Small Key",             ITEMTYPE_SMALLKEY,          0xB0, true, &FireTempleKeys,            &Hints::SmallKey);
Item WaterTemple_SmallKey           = Item("Water Temple Small Key",            ITEMTYPE_SMALLKEY,          0xB1, true, &WaterTempleKeys,           &Hints::SmallKey);
Item SpiritTemple_SmallKey          = Item("Spirit Temple Small Key",           ITEMTYPE_SMALLKEY,          0xB2, true, &SpiritTempleKeys,          &Hints::SmallKey);
Item ShadowTemple_SmallKey          = Item("Shadow Temple Small Key",           ITEMTYPE_SMALLKEY,          0xB3, true, &ShadowTempleKeys,          &Hints::SmallKey);
Item BottomOfTheWell_SmallKey       = Item("Bottom of the Well Small Key",      ITEMTYPE_SMALLKEY,          0xB4, true, &BottomOfTheWellKeys,       &Hints::SmallKey);
Item GerudoTrainingGrounds_SmallKey = Item("Gerudo Training Grounds Small Key", ITEMTYPE_SMALLKEY,          0xB5, true, &GerudoTrainingGroundsKeys, &Hints::SmallKey);
Item GerudoFortress_SmallKey        = Item("Gerudo Fortress Small Key",         ITEMTYPE_FORTRESS_SMALLKEY, 0xB6, true, &GerudoFortressKeys,        &Hints::FortressSmallKey);
Item GanonsCastle_SmallKey          = Item("Ganon's Castle Small Key",          ITEMTYPE_SMALLKEY,          0xB7, true, &GanonsCastleKeys,          &Hints::SmallKey);

//Stones and Medallions
Item I_KokiriEmerald            = Item("Kokiri Emerald",   ITEMTYPE_DUNGEONREWARD, 0xCB,  true, &KokiriEmerald,   &Hints::KokiriEmerald);
Item I_GoronRuby                = Item("Goron Ruby",       ITEMTYPE_DUNGEONREWARD, 0xCC,  true, &GoronRuby,       &Hints::GoronRuby);
Item I_ZoraSaphhire             = Item("Zora Sapphire",    ITEMTYPE_DUNGEONREWARD, 0xCD,  true, &ZoraSapphire,    &Hints::ZoraSapphire);
Item I_ForestMedallion          = Item("Forest Medallion", ITEMTYPE_DUNGEONREWARD, 0xCE,  true, &ForestMedallion, &Hints::ForestMedallion);
Item I_FireMedallion            = Item("Fire Medallion",   ITEMTYPE_DUNGEONREWARD, 0xCF,  true, &FireMedallion,   &Hints::FireMedallion);
Item I_WaterMedallion           = Item("Water Medallion",  ITEMTYPE_DUNGEONREWARD, 0xD0,  true, &WaterMedallion,  &Hints::WaterMedallion);
Item I_SpiritMedallion          = Item("Spirit Medallion", ITEMTYPE_DUNGEONREWARD, 0xD1,  true, &SpiritMedallion, &Hints::SpiritMedallion);
Item I_ShadowMedallion          = Item("Shadow Medallion", ITEMTYPE_DUNGEONREWARD, 0xD2,  true, &ShadowMedallion, &Hints::ShadowMedallion);
Item I_LightMedallion           = Item("Light Medallion",  ITEMTYPE_DUNGEONREWARD, 0xD3,  true, &LightMedallion,  &Hints::LightMedallion);

//Generic Items
Item RecoveryHeart              = Item("Recovery Heart",   ITEMTYPE_ITEM, GI_HEART,             false, &none, &Hints::RecoveryHeart);
Item GreenRupee                 = Item("Green Rupee",      ITEMTYPE_ITEM, GI_RUPEE_GREEN,       false, &none, &Hints::GreenRupee);
Item BlueRupee                  = Item("Blue Rupee",       ITEMTYPE_ITEM, GI_RUPEE_BLUE,        false, &none, &Hints::BlueRupee);
Item RedRupee                   = Item("Red Rupee",        ITEMTYPE_ITEM, GI_RUPEE_RED,         false, &none, &Hints::RedRupee);
Item PurpleRupee                = Item("Purple Rupee",     ITEMTYPE_ITEM, GI_RUPEE_PURPLE,      false, &none, &Hints::PurpleRupee);
Item HugeRupee                  = Item("Huge Rupee",       ITEMTYPE_ITEM, GI_RUPEE_GOLD,        false, &none, &Hints::HugeRupee);
Item PieceOfHeart               = Item("Piece of Heart",   ITEMTYPE_ITEM, GI_HEART_PIECE,       false, &none, &Hints::PieceOfHeart);
Item HeartContainer             = Item("Heart Container",  ITEMTYPE_ITEM, GI_HEART_CONTAINER_2, false, &none, &Hints::HeartContainer);
Item IceTrap                    = Item("Ice Trap",         ITEMTYPE_ITEM, GI_ICE_TRAP,          false, &none, &Hints::IceTrap);
Item Milk                       = Item("Milk",             ITEMTYPE_ITEM, GI_MILK,              false, &none, &Hints::NoHintText);

//Refills
Item Bombs5                     = Item("Bombs (5)",           ITEMTYPE_ITEM, GI_BOMBS_5,        false, &none,        &Hints::Bombs5);
Item Bombs10                    = Item("Bombs (10)",          ITEMTYPE_ITEM, GI_BOMBS_10,       false, &none,        &Hints::Bombs10);
Item Bombs20                    = Item("Bombs (20)",          ITEMTYPE_ITEM, GI_BOMBS_20,       false, &none,        &Hints::Bombs20);
Item Bombchu5                   = Item("Bombchu (5)",         ITEMTYPE_ITEM, GI_BOMBCHUS_5,     true,  &Bombchus5,   &Hints::Bombchus5);
Item Bombchu10                  = Item("Bombchu (10)",        ITEMTYPE_ITEM, GI_BOMBCHUS_10,    true,  &Bombchus10,  &Hints::Bombchus10);
Item Bombchu20                  = Item("Bombchu (20)",        ITEMTYPE_ITEM, GI_BOMBCHUS_20,    true,  &Bombchus20,  &Hints::Bombchus20);
Item I_BombchuDrop              = Item("Bombchu Drop",        ITEMTYPE_DROP, GI_BOMBCHUS_10,    true,  &BombchuDrop, &Hints::NoHintText);
Item Arrows5                    = Item("Arrows (5)",          ITEMTYPE_ITEM, GI_ARROWS_SMALL,   false, &none,        &Hints::Arrows5);
Item Arrows10                   = Item("Arrows (10)",         ITEMTYPE_ITEM, GI_ARROWS_MEDIUM,  false, &none,        &Hints::Arrows10);
Item Arrows30                   = Item("Arrows (30)",         ITEMTYPE_ITEM, GI_ARROWS_LARGE,   false, &none,        &Hints::Arrows30);
Item DekuNuts5                  = Item("Deku Nuts (5)",       ITEMTYPE_ITEM, GI_NUTS_5,         false, &none,        &Hints::DekuNuts5);
Item DekuNuts10                 = Item("Deku Nuts (10)",      ITEMTYPE_ITEM, GI_NUTS_10,        false, &none,        &Hints::DekuNuts10);
Item DekuSeeds30                = Item("Deku Seeds (30)",     ITEMTYPE_ITEM, GI_SEEDS_30,       false, &none,        &Hints::DekuSeeds30);
Item DekuStick1                 = Item("Deku Stick (1)",      ITEMTYPE_ITEM, GI_STICKS_1,       false, &none,        &Hints::DekuStick1);
Item RedPotionRefill            = Item("Red Potion Refill",   ITEMTYPE_ITEM, GI_POTION_RED,     false, &none,        &Hints::NoHintText);
Item GreenPotionRefill          = Item("Green Potion Refill", ITEMTYPE_ITEM, GI_POTION_GREEN,   false, &none,        &Hints::NoHintText);
Item BluePotionRefill           = Item("Blue Potion Refill",  ITEMTYPE_ITEM, GI_POTION_BLUE,    false, &none,        &Hints::NoHintText);


//Treasure Game
Item TreasureGameHeart          = Item("Piece of Heart (Treasure Chest Minigame)", ITEMTYPE_ITEM, GI_HEART_PIECE_WIN,  false, &none, &Hints::TreasureGameHeart);
Item TreasureGameGreenRupee     = Item("Green Rupee (Treasure Chest Minigame)",    ITEMTYPE_ITEM, GI_RUPEE_GREEN_LOSE, false, &none, &Hints::TreasureGameGreenRupee);

//Shop Items                                                                                                                            price
Item BuyDekuNut5                = Item("Buy Deku Nut (5)",    ITEMTYPE_SHOP, 0x00, true,  &Nuts,           &Hints::DekuNuts5,           15);
Item BuyArrows30                = Item("Buy Arrows (30)",     ITEMTYPE_SHOP, 0x01, false, &none,           &Hints::Arrows30,            60);
Item BuyArrows50                = Item("Buy Arrows (50)",     ITEMTYPE_SHOP, 0x02, false, &none,           &Hints::Arrows30,            90);
Item BuyBombs525                = Item("Buy Bombs (5) [25]",  ITEMTYPE_SHOP, 0x03, false, &none,           &Hints::Bombs5,              25);
Item BuyDekuNut10               = Item("Buy Deku Nut (10)",   ITEMTYPE_SHOP, 0x04, true,  &Nuts,           &Hints::DekuNuts10,          30);
Item BuyDekuStick1              = Item("Buy Deku Stick (1)",  ITEMTYPE_SHOP, 0x05, true,  &Sticks,         &Hints::DekuStick1,          10);
Item BuyBombs10                 = Item("Buy Bombs (10)",      ITEMTYPE_SHOP, 0x06, false, &none,           &Hints::Bombs10,             50);
Item BuyFish                    = Item("Buy Fish",            ITEMTYPE_SHOP, 0x07, true,  &FishAccess,     &Hints::BottleWithFish,     200);
Item BuyRedPotion30             = Item("Buy Red Potion [30]", ITEMTYPE_SHOP, 0x08, false, &none,           &Hints::NoHintText,          30);
Item BuyGreenPotion             = Item("Buy Green Potion",    ITEMTYPE_SHOP, 0x09, false, &none,           &Hints::NoHintText,          30);
Item BuyBluePotion              = Item("Buy Blue Potion",     ITEMTYPE_SHOP, 0x0A, false, &none,           &Hints::NoHintText,         100);
Item BuyHylianShield            = Item("Buy Hylian Shield",   ITEMTYPE_SHOP, 0x0C, true,  &HylianShield,   &Hints::HylianShield,        80);
Item BuyDekuShield              = Item("Buy Deku Shield",     ITEMTYPE_SHOP, 0x0D, true,  &DekuShield,     &Hints::DekuShield,          40);
Item BuyGoronTunic              = Item("Buy Goron Tunic",     ITEMTYPE_SHOP, 0x0E, true,  &GoronTunic,     &Hints::GoronTunic,         200);
Item BuyZoraTunic               = Item("Buy Zora Tunic",      ITEMTYPE_SHOP, 0x0F, true,  &ZoraTunic,      &Hints::ZoraTunic,          300);
Item BuyHeart                   = Item("Buy Heart",           ITEMTYPE_SHOP, 0x10, false, &none,           &Hints::RecoveryHeart,       10);
Item BuyBombchu10               = Item("Buy Bombchu (10)",    ITEMTYPE_SHOP, 0x15, true,  &BuyBombchus10,  &Hints::Bombchus10,          99);
Item BuyBombchu20               = Item("Buy Bombchu (20)",    ITEMTYPE_SHOP, 0x16, true,  &BuyBombchus20,  &Hints::Bombchus20,         180);
Item BuyBombchu5                = Item("Buy Bombchu (5)",     ITEMTYPE_SHOP, 0x18, true,  &BuyBombchus5,   &Hints::Bombchus5,           60);
Item BuyDekuSeeds30             = Item("Buy Deku Seeds (30)", ITEMTYPE_SHOP, 0x1D, false, &none,           &Hints::DekuSeeds30,         30);
Item SoldOut                    = Item("Sold Out",            ITEMTYPE_SHOP, 0x26, false, &none,           &Hints::NoHintText,           0);
Item BuyBlueFire                = Item("Buy Blue Fire",       ITEMTYPE_SHOP, 0x27, true,  &BlueFireAccess, &Hints::BottleWithBlueFire, 300);
Item BuyBottleBug               = Item("Buy Bottle Bug",      ITEMTYPE_SHOP, 0x28, true,  &BugsAccess,     &Hints::BottleWithBugs,      50);
Item BuyPoe                     = Item("Buy Poe",             ITEMTYPE_SHOP, 0x2A, false, &none,           &Hints::BottleWithPoe,       30);
Item BuyFairysSpirit            = Item("Buy Fairy's Spirit",  ITEMTYPE_SHOP, 0x2B, true,  &FairyAccess,    &Hints::BottleWithFairy,     50);
Item BuyArrows10                = Item("Buy Arrows (10)",     ITEMTYPE_SHOP, 0x2C, false, &none,           &Hints::Arrows10,            20);
Item BuyBombs20                 = Item("Buy Bombs (20)",      ITEMTYPE_SHOP, 0x2D, false, &none,           &Hints::Bombs20,             80);
Item BuyBombs30                 = Item("Buy Bombs (30)",      ITEMTYPE_SHOP, 0x2E, false, &none,           &Hints::Bombs20,            120);
Item BuyBombs535                = Item("Buy Bombs (5) [35]",  ITEMTYPE_SHOP, 0x2F, false, &none,           &Hints::Bombs5,              35);
Item BuyRedPotion40             = Item("Buy Red Potion [40]", ITEMTYPE_SHOP, 0x30, false, &none,           &Hints::NoHintText,          40);
Item BuyRedPotion50             = Item("Buy Red Potion [50]", ITEMTYPE_SHOP, 0x31, false, &none,           &Hints::NoHintText,          50);
