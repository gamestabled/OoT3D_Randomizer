#include "item_list.hpp"
#include "logic.hpp"
#include "../code/include/z3D/z3Ditem.h"
#include <vector>

using namespace Logic;

//Effects to be run when an item is placed
static auto NoEffect = []{ return; };

//set the logic variable for this item to be true when it gets placed
static auto KokiriSwordEffect          = []{KokiriSword   = true;};
static auto DekuShieldEffect           = []{DekuShield    = true;};
static auto HylianShieldEffect         = []{HylianShield  = true;};
static auto MirrorShieldEffect         = []{MirrorShield  = true;};
static auto BoomerangEffect            = []{Boomerang     = true;};
static auto BombchuEffect              = []{Bombchus      = true;};
static auto ZeldasLetterEffect         = []{ZeldasLetter  = true;};
static auto WeirdEggEffect             = []{WeirdEgg      = true;};
static auto LensOfTruthEffect          = []{LensOfTruth   = true;};
static auto MegatonHammerEffect        = []{Hammer        = true;};
static auto IronBootsEffect            = []{IronBoots     = true;};
static auto HoverBootsEffect           = []{HoverBoots    = true;};
static auto ShardOfAgonyEffect         = []{ShardOfAgony  = true;};
static auto DinsFireEffect             = []{DinsFire      = true;};
static auto FaroresWindEffect          = []{FaroresWind   = true;};
static auto NayrusLoveEffect           = []{NayrusLove    = true;};
static auto FireArrowEffect            = []{FireArrows    = true;};
static auto IceArrowEffect             = []{IceArrows     = true;};
static auto LightArrowEffect           = []{LightArrows   = true;};
static auto GoronTunicEffect           = []{GoronTunic    = true;};
static auto ZoraTunicEffect            = []{ZoraTunic     = true;};
static auto GerudoTokenEffect          = []{GerudoToken   = true;};
static auto MagicBeanPackEffect        = []{MagicBeanPack = true;};

static auto ProgressiveHookshotEffect  = []{ProgressiveHookshot++; };
static auto ProgressiveBombBagEffect   = []{ProgressiveBombBag++;  };
static auto ProgressiveStrengthEffect  = []{ProgressiveStrength++; };
static auto ProgressiveScaleEffect     = []{ProgressiveScale++;    };
static auto ProgressiveBowEffect       = []{ProgressiveBow++;      };
static auto ProgressiveBulletBagEffect = []{ProgressiveBulletBag++;};
static auto ProgressiveWalletEffect    = []{ProgressiveWallet++;   };
static auto ProgressiveMagicEffect     = []{ProgressiveMagic++;    };
static auto ProgressiveOcarinaEffect   = []{ProgressiveOcarina++;  };

//Bottle Effects
static auto BottleEffect               = []{HasBottle   = true;      };
static auto RutosLetterEffect          = []{RutosLetter = true;      };
static auto BigPoeBottleEffect         = []{HasBigPoe   = true;      };

//Song Effects
static auto ZeldasLullabyEffect        = []{ZeldasLullaby    = true; };
static auto SariasSongEffect           = []{SariasSong       = true; };
static auto EponasSongEffect           = []{EponasSong       = true; };
static auto SunsSongEffect             = []{SunsSong         = true; };
static auto SongOfTimeEffect           = []{SongOfTime       = true; };
static auto SongOfStormsEffect         = []{SongOfStorms     = true; };

static auto MinuetOfForestEffect       = []{MinuetOfForest   = true; };
static auto BoleroOfFireEffect         = []{BoleroOfFire     = true; };
static auto SerenadeOfWaterEffect      = []{SerenadeOfWater  = true; };
static auto RequiemOfSpiritEffect      = []{RequiemOfSpirit  = true; };
static auto NocturneOfShadowEffect     = []{NocturneOfShadow = true; };
static auto PreludeOfLightEffect       = []{PreludeOfLight   = true; };

//Small Key Effects
static auto ForestTempleSmallKeyEffect          = []{ForestTempleKeys++;          };
static auto FireTempleSmallKeyEffect            = []{FireTempleKeys++;            };
static auto WaterTempleSmallKeyEffect           = []{WaterTempleKeys++;           };
static auto SpiritTempleSmallKeyEffect          = []{SpiritTempleKeys++;          };
static auto ShadowTempleSmallKeyEffect          = []{ShadowTempleKeys++;          };
static auto BottomOfTheWellSmallKeyEffect       = []{BottomOfTheWellKeys++;       };
static auto GerudoTrainingGroundsSmallKeyEffect = []{GerudoTrainingGroundsKeys++; };
static auto GerudoFortressSmallKeyEffect        = []{GerudoFortressKeys++;        };
static auto GanonsCastleSmallKeyEffect          = []{GanonsCastleKeys++;          };

static auto ForestTempleBossKeyEffect           = []{BossKeyForestTemple = true;};
static auto FireTempleBossKeyEffect             = []{BossKeyFireTemple   = true;};
static auto WaterTempleBossKeyEffect            = []{BossKeyWaterTemple  = true;};
static auto SpiritTempleBossKeyEffect           = []{BossKeySpiritTemple = true;};
static auto ShadowTempleBossKeyEffect           = []{BossKeyShadowTemple = true;};
static auto GanonsCastleBossKeyEffect           = []{BossKeyGanonsCastle = true;};

Item NoItem = Item("No Item", ITEMTYPE_ITEM,   GI_RUPEE_GREEN,   false, false, NoEffect);

//Specific Advancement Items         // name              type           getItemId          progressive advancement effect
Item A_KokiriSword              = Item("Kokiri Sword",    ITEMTYPE_ITEM, GI_SWORD_KOKIRI,   false, false, KokiriSwordEffect);
Item A_BiggoronSword            = Item("Biggoron Sword",  ITEMTYPE_ITEM, GI_SWORD_BGS,      false, false, NoEffect);
Item A_DekuShield               = Item("Deku Shield",     ITEMTYPE_ITEM, GI_SHIELD_DEKU,    false, false, DekuShieldEffect);
Item A_HylianShield             = Item("Hylian Shield",   ITEMTYPE_ITEM, GI_SHIELD_HYLIAN,  false, false, HylianShieldEffect);
Item A_MirrorShield             = Item("Mirror Shield",   ITEMTYPE_ITEM, GI_SHIELD_MIRROR,  false, false, MirrorShieldEffect);
Item A_Boomerang                = Item("Boomerang",       ITEMTYPE_ITEM, GI_BOOMERANG,      false, false, BoomerangEffect);
Item A_ZeldasLetter             = Item("Zelda's Letter",  ITEMTYPE_ITEM, GI_LETTER_ZELDA,   false, false, ZeldasLetterEffect);
Item A_WeirdEgg                 = Item("Weird Egg",       ITEMTYPE_ITEM, GI_WEIRD_EGG,      false, false, WeirdEggEffect);
Item A_LensOfTruth              = Item("Lens of Truth",   ITEMTYPE_ITEM, GI_LENS,           false, false, LensOfTruthEffect);
Item A_MegatonHammer            = Item("Megaton Hammer",  ITEMTYPE_ITEM, GI_HAMMER,         false, false, MegatonHammerEffect);
Item A_IronBoots                = Item("Iron Boots",      ITEMTYPE_ITEM, GI_BOOTS_IRON,     false, false, IronBootsEffect);
Item A_HoverBoots               = Item("Hover Boots",     ITEMTYPE_ITEM, GI_BOOTS_HOVER,    false, false, HoverBootsEffect);
Item A_ShardOfAgony             = Item("Shard of Agony",  ITEMTYPE_ITEM, GI_STONE_OF_AGONY, false, false, ShardOfAgonyEffect);
Item A_DinsFire                 = Item("Din's Fire",      ITEMTYPE_ITEM, GI_DINS_FIRE,      false, false, DinsFireEffect);
Item A_FaroresWind              = Item("Farore's Wind",   ITEMTYPE_ITEM, GI_FARORES_WIND,   false, false, FaroresWindEffect);
Item A_NayrusLove               = Item("Nayru's Love",    ITEMTYPE_ITEM, GI_NAYRUS_LOVE,    false, false, NayrusLoveEffect);
Item A_FireArrows               = Item("Fire Arrows",     ITEMTYPE_ITEM, GI_ARROW_FIRE,     false, false, FireArrowEffect);
Item A_IceArrows                = Item("Ice Arrows",      ITEMTYPE_ITEM, GI_ARROW_ICE,      false, false, IceArrowEffect);
Item A_LightArrows              = Item("Light Arrows",    ITEMTYPE_ITEM, GI_ARROW_LIGHT,    false, false, LightArrowEffect);
Item A_GoronTunic               = Item("Goron Tunic",     ITEMTYPE_ITEM, GI_TUNIC_GORON,    false, false, GoronTunicEffect);
Item A_ZoraTunic                = Item("Zora Tunic",      ITEMTYPE_ITEM, GI_TUNIC_ZORA,     false, false, ZoraTunicEffect);
Item A_GerudoToken              = Item("Gerudo Token",    ITEMTYPE_ITEM, GI_GERUDO_CARD,    false, false, GerudoTokenEffect);
Item A_MagicBeanPack            = Item("Magic Bean Pack", ITEMTYPE_ITEM, 0xC9,              false, false, MagicBeanPackEffect);

//Progression Items
Item A_ProgressiveHookshot      = Item("Progressive Hookshot",       ITEMTYPE_ITEM,     0x80, true,  false, ProgressiveHookshotEffect);
Item A_ProgressiveStrength      = Item("Progressive Strength",       ITEMTYPE_ITEM,     0x81, true,  false, ProgressiveStrengthEffect);
Item A_ProgressiveBombBag       = Item("Progressive Bomb Bag",       ITEMTYPE_ITEM,     0x82, true,  false, ProgressiveBombBagEffect);
Item A_ProgressiveBow           = Item("Progressive Bow",            ITEMTYPE_ITEM,     0x83, true,  false, ProgressiveBowEffect);
Item A_ProgressiveBulletBag     = Item("Progressive Bullet Bag",     ITEMTYPE_ITEM,     0x84, true,  false, ProgressiveBulletBagEffect);
Item A_ProgressiveWallet        = Item("Progressive Wallet",         ITEMTYPE_ITEM,     0x85, true,  false, ProgressiveWalletEffect);
Item A_ProgressiveScale         = Item("Progressive Scale",          ITEMTYPE_ITEM,     0x86, true,  false, ProgressiveScaleEffect);
Item A_ProgressiveNutCapacity   = Item("Progressive Nut Upgrade",    ITEMTYPE_ITEM,     0x87, true,  false, NoEffect);
Item A_ProgressiveStickCapacity = Item("Progressive Stick Upgrade",  ITEMTYPE_ITEM,     0x88, true,  false, NoEffect);
Item A_ProgressiveBombchus      = Item("Progressive Bombchus",       ITEMTYPE_ITEM,     0x89, true,  false, BombchuEffect);
Item A_ProgressiveMagic         = Item("Progressive Magic",          ITEMTYPE_ITEM,     0x8A, true,  false, ProgressiveMagicEffect);
Item A_ProgressiveOcarina       = Item("Progressive Ocarina",        ITEMTYPE_ITEM,     0x8B, true,  false, ProgressiveOcarinaEffect);

//Bottles
Item A_EmptyBottle              = Item("Empty Bottle",               ITEMTYPE_ITEM,     0x0F, false, false, BottleEffect);
Item A_MilkBottle               = Item("Bottle with Milk",           ITEMTYPE_ITEM,     0x14, false, false, BottleEffect);
Item A_RedPotionBottle          = Item("Bottle with Red Potion",     ITEMTYPE_ITEM,     0x8C, false, false, BottleEffect);
Item A_GreenPotionBottle        = Item("Bottle with Green Potion",   ITEMTYPE_ITEM,     0x8D, false, false, BottleEffect);
Item A_BluePotionBottle         = Item("Bottle with Blue Potion",    ITEMTYPE_ITEM,     0x8E, false, false, BottleEffect);
Item A_FairyBottle              = Item("Bottle with Fairy",          ITEMTYPE_ITEM,     0x8F, false, false, BottleEffect);
Item A_FishBottle               = Item("Bottle with Fish",           ITEMTYPE_ITEM,     0x90, false, false, BottleEffect);
Item A_BlueFireBottle           = Item("Bottle with Blue Fire",      ITEMTYPE_ITEM,     0x91, false, false, BottleEffect);
Item A_BugsBottle               = Item("Bottle with Bugs",           ITEMTYPE_ITEM,     0x92, false, false, BottleEffect);
Item A_PoeBottle                = Item("Bottle with Poe",            ITEMTYPE_ITEM,     0x94, false, false, BottleEffect);

//Special bottles that can't immediately dump contents
Item A_RutosLetter              = Item("Rutos Letter",               ITEMTYPE_ITEM,     0x15, false, false, RutosLetterEffect);
Item A_BigPoeBottle             = Item("Bottle with Big Poe",        ITEMTYPE_ITEM,     0x93, false, false, BigPoeBottleEffect);

//Songs
Item A_ZeldasLullaby            = Item("Zelda's Lullaby",            ITEMTYPE_SONG,     0xC1, false, false, ZeldasLullabyEffect);
Item A_EponasSong               = Item("Epona's Song",               ITEMTYPE_SONG,     0xC2, false, false, EponasSongEffect);
Item A_SariasSong               = Item("Saria's Song",               ITEMTYPE_SONG,     0xC3, false, false, SariasSongEffect);
Item A_SunsSong                 = Item("Sun's Song",                 ITEMTYPE_SONG,     0xC4, false, false, SunsSongEffect);
Item A_SongOfTime               = Item("Song of Time",               ITEMTYPE_SONG,     0xC5, false, false, SongOfTimeEffect);
Item A_SongOfStorms             = Item("Song of Storms",             ITEMTYPE_SONG,     0xC6, false, false, SongOfStormsEffect);
Item A_MinuetOfForest           = Item("Minuet of Forest",           ITEMTYPE_SONG,     0xBB, false, false, MinuetOfForestEffect);
Item A_BoleroOfFire             = Item("Bolero of Fire",             ITEMTYPE_SONG,     0xBC, false, false, BoleroOfFireEffect);
Item A_SerenadeOfWater          = Item("Serenade of Water",          ITEMTYPE_SONG,     0xBD, false, false, SerenadeOfWaterEffect);
Item A_RequiemOfSpirit          = Item("Requiem of Spirit",          ITEMTYPE_SONG,     0xBE, false, false, RequiemOfSpiritEffect);
Item A_NocturneOfShadow         = Item("Nocturne of Shadow",         ITEMTYPE_SONG,     0xBF, false, false, NocturneOfShadowEffect);
Item A_PreludeOfLight           = Item("Prelude of Light",           ITEMTYPE_SONG,     0xC0, false, false, PreludeOfLightEffect);

//Maps and Compasses
Item DekuTree_Map               = Item("Deku Tree Map",              ITEMTYPE_MAP,      0xA5, false, false, NoEffect);
Item DodongosCavern_Map         = Item("Dodongo's Cavern Map",       ITEMTYPE_MAP,      0xA6, false, false, NoEffect);
Item JabuJabusBelly_Map         = Item("Jabu Jabu's Belly Map",      ITEMTYPE_MAP,      0xA7, false, false, NoEffect);
Item ForestTemple_Map           = Item("Forest Temple Map",          ITEMTYPE_MAP,      0xA8, false, false, NoEffect);
Item FireTemple_Map             = Item("Fire Temple Map",            ITEMTYPE_MAP,      0xA9, false, false, NoEffect);
Item WaterTemple_Map            = Item("Water Temple Map",           ITEMTYPE_MAP,      0xAA, false, false, NoEffect);
Item SpiritTemple_Map           = Item("Spirit Temple Map",          ITEMTYPE_MAP,      0xAB, false, false, NoEffect);
Item ShadowTemple_Map           = Item("Shadow Temple Map",          ITEMTYPE_MAP,      0xAC, false, false, NoEffect);
Item BottomOfTheWell_Map        = Item("Bottom of the Well Map",     ITEMTYPE_MAP,      0xAD, false, false, NoEffect);
Item IceCavern_Map              = Item("Ice Cavern Map",             ITEMTYPE_MAP,      0xAE, false, false, NoEffect);

Item DekuTree_Compass           = Item("Deku Tree Compass",          ITEMTYPE_COMPASS,  0xA5, false, false, NoEffect);
Item DodongosCavern_Compass     = Item("Dodongo's Cavern Compass",   ITEMTYPE_COMPASS,  0xA6, false, false, NoEffect);
Item JabuJabusBelly_Compass     = Item("Jabu Jabu's Belly Compass",  ITEMTYPE_COMPASS,  0xA7, false, false, NoEffect);
Item ForestTemple_Compass       = Item("Forest Temple Compass",      ITEMTYPE_COMPASS,  0xA8, false, false, NoEffect);
Item FireTemple_Compass         = Item("Fire Temple Compass",        ITEMTYPE_COMPASS,  0xA9, false, false, NoEffect);
Item WaterTemple_Compass        = Item("Water Temple Compass",       ITEMTYPE_COMPASS,  0xAA, false, false, NoEffect);
Item SpiritTemple_Compass       = Item("Spirit Temple Compass",      ITEMTYPE_COMPASS,  0xAB, false, false, NoEffect);
Item ShadowTemple_Compass       = Item("Shadow Temple Compass",      ITEMTYPE_COMPASS,  0xAC, false, false, NoEffect);
Item BottomOfTheWell_Compass    = Item("Bottom of the Well Compass", ITEMTYPE_COMPASS,  0xAD, false, false, NoEffect);
Item IceCavern_Compass          = Item("Ice Cavern Compass",         ITEMTYPE_COMPASS,  0xAE, false, false, NoEffect);

//Boss Keys
Item ForestTemple_BossKey       = Item("Forest Temple Boss Key",     ITEMTYPE_BOSSKEY,  0x95, false, false, ForestTempleBossKeyEffect);
Item FireTemple_BossKey         = Item("Fire Temple Boss Key",       ITEMTYPE_BOSSKEY,  0x96, false, false, FireTempleBossKeyEffect);
Item WaterTemple_BossKey        = Item("Water Temple Boss Key",      ITEMTYPE_BOSSKEY,  0x97, false, false, WaterTempleBossKeyEffect);
Item SpiritTemple_BossKey       = Item("Spirit Temple Boss Key",     ITEMTYPE_BOSSKEY,  0x98, false, false, SpiritTempleBossKeyEffect);
Item ShadowTemple_BossKey       = Item("Shadow Temple Boss Key",     ITEMTYPE_BOSSKEY,  0x99, false, false, ShadowTempleBossKeyEffect);
Item GanonsCastle_BossKey       = Item("Ganon's Castle Boss Key",    ITEMTYPE_BOSSKEY,  0x9A, false, false, GanonsCastleBossKeyEffect);

//Small Keys
Item ForestTemple_SmallKey          = Item("Forest Temple Small Key",           ITEMTYPE_SMALLKEY,          0xAF, false, false, ForestTempleSmallKeyEffect);
Item FireTemple_SmallKey            = Item("Fire Temple Small Key",             ITEMTYPE_SMALLKEY,          0xB0, false, false, FireTempleSmallKeyEffect);
Item WaterTemple_SmallKey           = Item("Water Temple Small Key",            ITEMTYPE_SMALLKEY,          0xB1, false, false, WaterTempleSmallKeyEffect);
Item SpiritTemple_SmallKey          = Item("Spirit Temple Small Key",           ITEMTYPE_SMALLKEY,          0xB2, false, false, SpiritTempleSmallKeyEffect);
Item ShadowTemple_SmallKey          = Item("Shadow Temple Small Key",           ITEMTYPE_SMALLKEY,          0xB3, false, false, ShadowTempleSmallKeyEffect);
Item BottomOfTheWell_SmallKey       = Item("Bottom of the Well Small Key",      ITEMTYPE_SMALLKEY,          0xB4, false, false, BottomOfTheWellSmallKeyEffect);
Item GerudoTrainingGrounds_SmallKey = Item("Gerudo Training Grounds Small Key", ITEMTYPE_SMALLKEY,          0xB5, false, false, GerudoTrainingGroundsSmallKeyEffect);
Item GerudoFortress_SmallKey        = Item("Gerudo Fortress Small Key",         ITEMTYPE_FORTRESS_SMALLKEY, 0xB6, false, false, GerudoFortressSmallKeyEffect);
Item GanonsCastle_SmallKey          = Item("Ganon's Castle Small Key",          ITEMTYPE_SMALLKEY,          0xB7, false, false, GanonsCastleSmallKeyEffect);

//Generic Items
Item Heart                 = Item("Recovery Heart",  ITEMTYPE_ITEM,   GI_HEART,         false, false, NoEffect);
Item GreenRupee            = Item("Green Rupee",     ITEMTYPE_ITEM,   GI_RUPEE_GREEN,   false, false, NoEffect);
Item BlueRupee             = Item("Blue Rupee",      ITEMTYPE_ITEM,   GI_RUPEE_BLUE,    false, false, NoEffect);
Item RedRupee              = Item("Red Rupee",       ITEMTYPE_ITEM,   GI_RUPEE_RED,     false, false, NoEffect);
Item PurpleRupee           = Item("Purple Rupee",    ITEMTYPE_ITEM,   GI_RUPEE_PURPLE,  false, false, NoEffect);
Item HugeRupee             = Item("Huge Rupee",      ITEMTYPE_ITEM,   GI_RUPEE_GOLD,    false, false, NoEffect);
Item PieceOfHeart          = Item("Piece of Heart",  ITEMTYPE_ITEM,   GI_HEART_PIECE,   false, false, NoEffect);
Item IceTrap               = Item("Ice Trap",        ITEMTYPE_ITEM,   GI_ICE_TRAP,      false, false, NoEffect);

//Refills
Item BombRefill5           = Item("Bomb Refill 5",   ITEMTYPE_REFILL, GI_BOMBS_5,       false, false, NoEffect);
Item BombRefill10          = Item("Bomb Refill 10",  ITEMTYPE_REFILL, GI_BOMBS_10,      false, false, NoEffect);
Item BombRefill20          = Item("Bomb Refill 20",  ITEMTYPE_REFILL, GI_BOMBS_20,      false, false, NoEffect);
Item ArrowRefill5          = Item("Arrow Refill 5",  ITEMTYPE_REFILL, GI_ARROWS_SMALL,  false, false, NoEffect);
Item ArrowRefill10         = Item("Arrow Refill 10", ITEMTYPE_REFILL, GI_ARROWS_MEDIUM, false, false, NoEffect);

Item DekuNutsRefill5       = Item("Deku Nuts 5",     ITEMTYPE_REFILL, GI_NUTS_5,        false, false, NoEffect);
Item DekuSeedsRefill30     = Item("Deku Seeds 30",   ITEMTYPE_REFILL, GI_SEEDS_30,      false, false, NoEffect);

Item DekuStick1            = Item("Deku Stick",      ITEMTYPE_REFILL, GI_STICKS_1,      false, false, NoEffect);

//This pool will be used to give placement priority for items that can advance location access
std::vector<Item> AdvancementItemPool = {};

//The beginning pool of items
std::vector<Item> ItemPool = {
  A_BiggoronSword,
  A_Boomerang,
  A_LensOfTruth,
  A_MegatonHammer,
  A_IronBoots,
  A_GoronTunic,
  A_ZoraTunic,
  A_HoverBoots,
  A_MirrorShield,
  A_ShardOfAgony,
  A_FireArrows,
  A_IceArrows,
  A_LightArrows,
  A_DinsFire,
  A_FaroresWind,
  A_NayrusLove,
  GreenRupee,
  A_DekuShield,
  A_HylianShield,
  A_MagicBeanPack,

  A_ProgressiveHookshot,      A_ProgressiveHookshot,
  A_ProgressiveStrength,      A_ProgressiveStrength,      A_ProgressiveStrength,
  A_ProgressiveScale,         A_ProgressiveScale,
  A_ProgressiveBow,           A_ProgressiveBow,           A_ProgressiveBow,
  A_ProgressiveBulletBag,     A_ProgressiveBulletBag,     A_ProgressiveBulletBag,
  A_ProgressiveBombBag,       A_ProgressiveBombBag,       A_ProgressiveBombBag,
  A_ProgressiveOcarina,       A_ProgressiveOcarina,
  A_ProgressiveWallet,        A_ProgressiveWallet,
  A_ProgressiveMagic,         A_ProgressiveMagic,
  A_ProgressiveNutCapacity,   A_ProgressiveNutCapacity,
  A_ProgressiveStickCapacity, A_ProgressiveStickCapacity,

  BombRefill5,
  BombRefill10,
  BombRefill20,
  ArrowRefill5,
  ArrowRefill10, ArrowRefill10, ArrowRefill10, ArrowRefill10, ArrowRefill10,
  Heart, Heart, Heart, Heart, Heart, Heart,

  A_EmptyBottle,
  A_RedPotionBottle,
  A_BlueFireBottle,
  A_RutosLetter,
  A_SongOfStorms,
  A_SongOfTime,
  A_SariasSong,
  A_SunsSong,
  A_MinuetOfForest,
  A_BoleroOfFire,
  A_SerenadeOfWater,
  A_NocturneOfShadow,
  A_RequiemOfSpirit,
  A_PreludeOfLight,

};


void AddItemToPool(Item item, u8 count = 1) {
  for(u8 i = 0; i < count; i++) {
    ItemPool.push_back(item);
  }
}
/*Adds extra shuffled items to the item Pool
  Checks must also be implemented in Playthrough::PlacedSetItem()
  if the item has a specific location it needs to be (i.e. Zeldas Letter)
*/
void UpdateSetItems() {
  if (ShuffleKokiriSword) {
    ItemPool.push_back(A_KokiriSword);
  }

  if (ShuffleWeirdEgg) {
    ItemPool.push_back(A_WeirdEgg);
  }

  if (ShuffleZeldasLetter) {
    ItemPool.push_back(A_ZeldasLetter);
  }

  if (BombchusInLogic) {
    ItemPool.push_back(A_ProgressiveBombchus);
  }

  if (ShuffleGerudoToken) {
    ItemPool.push_back(A_GerudoToken);
  }

  if (Keysanity == "All Locations") {
    AddItemToPool(ForestTemple_SmallKey, 5);
    AddItemToPool(FireTemple_SmallKey, 8);
    AddItemToPool(WaterTemple_SmallKey, 6);
    AddItemToPool(SpiritTemple_SmallKey, 5);
    AddItemToPool(ShadowTemple_SmallKey, 5);
    AddItemToPool(BottomOfTheWell_SmallKey, 3);
    AddItemToPool(GerudoFortress_SmallKey, 4);
    AddItemToPool(GerudoTrainingGrounds_SmallKey, 9);
    AddItemToPool(GanonsCastle_SmallKey, 2);
  }

  if (BossKeysanity == "All Locations") {
    AddItemToPool(ForestTemple_BossKey);
    AddItemToPool(FireTemple_BossKey);
    AddItemToPool(WaterTemple_BossKey);
    AddItemToPool(SpiritTemple_BossKey);
    AddItemToPool(ShadowTemple_BossKey);
  }

  if (MapsAndCompasses == "All Locations") {
    AddItemToPool(DekuTree_Map);
    AddItemToPool(DodongosCavern_Map);
    AddItemToPool(JabuJabusBelly_Map);
    AddItemToPool(ForestTemple_Map);
    AddItemToPool(FireTemple_Map);
    AddItemToPool(WaterTemple_Map);
    AddItemToPool(SpiritTemple_Map);
    AddItemToPool(ShadowTemple_Map);
    AddItemToPool(BottomOfTheWell_Map);
    AddItemToPool(IceCavern_Map);

    AddItemToPool(DekuTree_Compass);
    AddItemToPool(DodongosCavern_Compass);
    AddItemToPool(JabuJabusBelly_Compass);
    AddItemToPool(ForestTemple_Compass);
    AddItemToPool(FireTemple_Compass);
    AddItemToPool(WaterTemple_Compass);
    AddItemToPool(SpiritTemple_Compass);
    AddItemToPool(ShadowTemple_Compass);
    AddItemToPool(BottomOfTheWell_Compass);
    AddItemToPool(IceCavern_Compass);
  }
}

void AddHeartPiece() {
  ItemPool.push_back(PieceOfHeart);
}
