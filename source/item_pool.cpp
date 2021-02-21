#include "item_pool.hpp"
#include "random.hpp"
#include "spoiler_log.hpp"

using namespace Settings;

//The beginning pool of items, filled in by GenerateItemPool()
std::vector<Item> ItemPool = {};
std::vector<Item> PendingJunkPool = {};
const std::array<Item, 16> JunkPoolItems = {
  Bombs5,
  Bombs10,
  Bombs20,
  DekuNuts5,
  DekuStick1,
  DekuSeeds30,
  RecoveryHeart,
  Arrows5,
  Arrows10,
  Arrows30,
  BlueRupee,
  RedRupee,
  PurpleRupee,
  HugeRupee,
  DekuNuts10,
  IceTrap,
};
const std::array<Item, 59> alwaysItems = {
  I_BiggoronSword,
  I_Boomerang,
  I_LensOfTruth,
  I_MegatonHammer,
  I_IronBoots,
  I_GoronTunic,
  I_ZoraTunic,
  I_HoverBoots,
  I_MirrorShield,
  I_ShardOfAgony,
  I_FireArrows,
  I_IceArrows,
  I_LightArrows,
  I_DinsFire,
  I_FaroresWind,
  I_NayrusLove,
  GreenRupee,
  I_ProgressiveHookshot,  //2 progressive hookshots
  I_ProgressiveHookshot,
  I_DekuShield,
  I_HylianShield,
  I_ProgressiveStrength,  //3 progressive strength upgrades
  I_ProgressiveStrength,
  I_ProgressiveStrength,
  I_ProgressiveScale,     //2 progressive scales
  I_ProgressiveScale,
  I_ProgressiveBow,       //3 progressive Bows
  I_ProgressiveBow,
  I_ProgressiveBow,
  I_ProgressiveBulletBag, //3 progressive bullet bags
  I_ProgressiveBulletBag,
  I_ProgressiveBulletBag,
  I_ProgressiveBombBag,   //3 progressive bomb bags
  I_ProgressiveBombBag,
  I_ProgressiveBombBag,
  I_ProgressiveWallet, //2 progressive wallets
  I_ProgressiveWallet,
  I_ProgressiveMagic,  //2 progressive magic meters
  I_ProgressiveMagic,
  I_DoubleDefense,
  I_ProgressiveStickCapacity, //2 stick upgrades
  I_ProgressiveStickCapacity,
  I_ProgressiveNutCapacity,   //2 nut upgrades
  I_ProgressiveNutCapacity,
  RecoveryHeart,  //6 recovery hearts
  RecoveryHeart,
  RecoveryHeart,
  RecoveryHeart,
  RecoveryHeart,
  RecoveryHeart,
  Bombs5, //2
  Bombs5,
  Bombs10,
  Bombs20,
  Arrows5,
  Arrows10, //5
  Arrows10,
  Arrows10,
  TreasureGameHeart,
};
const std::array<Item, 43> easyItems = {
  I_BiggoronSword,
  I_KokiriSword,
  I_Boomerang,
  I_LensOfTruth,
  I_MegatonHammer,
  I_IronBoots,
  I_GoronTunic,
  I_ZoraTunic,
  I_HoverBoots,
  I_MirrorShield,
  I_FireArrows,
  I_LightArrows,
  I_DinsFire,
  I_ProgressiveHookshot,
  I_ProgressiveStrength,
  I_ProgressiveScale,
  I_ProgressiveWallet,
  I_ProgressiveMagic,
  I_ProgressiveStickCapacity,
  I_ProgressiveNutCapacity,
  I_ProgressiveBow,
  I_ProgressiveBulletBag,
  I_ProgressiveBombBag,
  I_DoubleDefense,
  HeartContainer, //16 Heart Containers
  HeartContainer,
  HeartContainer,
  HeartContainer,
  HeartContainer,
  HeartContainer,
  HeartContainer,
  HeartContainer,
  HeartContainer,
  HeartContainer,
  HeartContainer,
  HeartContainer,
  HeartContainer,
  HeartContainer,
  HeartContainer,
  HeartContainer,
  PieceOfHeart,   //3 heart pieces
  PieceOfHeart,
  PieceOfHeart,
};
const std::array<Item, 43> normalItems = {
  PieceOfHeart,   //35 pieces of heart
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  PieceOfHeart,
  HeartContainer, //8 heart containers
  HeartContainer,
  HeartContainer,
  HeartContainer,
  HeartContainer,
  HeartContainer,
  HeartContainer,
  HeartContainer,
};
const std::array<Item, 2> DT_Vanilla = {
  RecoveryHeart,
  RecoveryHeart,
};
const std::array<Item, 3> DT_MQ = {
  I_DekuShield,
  I_DekuShield,
  PurpleRupee,
};
const std::array<Item, 1> DC_Vanilla = {
  RedRupee,
};
const std::array<Item, 2> DC_MQ = {
  I_HylianShield,
  BlueRupee,
};
const std::array<Item, 7> JB_MQ = {
  DekuNuts5,
  DekuNuts5,
  DekuNuts5,
  DekuNuts5,
  RecoveryHeart,
  I_DekuShield,
  DekuStick1,
};
const std::array<Item, 3> FoT_Vanilla = {
  RecoveryHeart,
  Arrows10,
  Arrows30,
};
const std::array<Item, 1> FoT_MQ = {
  Arrows5,
};
const std::array<Item, 1> FiT_Vanilla = {
  HugeRupee,
};
const std::array<Item, 2> FiT_MQ = {
  Bombs20,
  I_HylianShield,
};
const std::array<Item, 4> SpT_Vanilla = {
  I_DekuShield,
  I_DekuShield,
  RecoveryHeart,
  Bombs20,
};
const std::array<Item, 3> SpT_MQ = {
  PurpleRupee,
  PurpleRupee,
  Arrows30,
};
const std::array<Item, 1> ShT_Vanilla = {
  Arrows30,
};
const std::array<Item, 3> ShT_MQ = {
  Arrows5,
  Arrows5,
  RedRupee,
};
const std::array<Item, 7> BW_Vanilla = {
  RecoveryHeart,
  Bombs10,
  HugeRupee,
  DekuNuts5,
  DekuNuts10,
  I_DekuShield,
  I_HylianShield,
};
const std::array<Item, 4> GTG_Vanilla = {
  Arrows30,
  Arrows30,
  Arrows30,
  HugeRupee,
};
const std::array<Item, 5> GTG_MQ = {
  TreasureGameGreenRupee,
  TreasureGameGreenRupee,
  Arrows10,
  GreenRupee,
  PurpleRupee,
};
const std::array<Item, 4> GC_Vanilla = {
  BlueRupee,
  BlueRupee,
  BlueRupee,
  Arrows30,
};
const std::array<Item, 5> GC_MQ = {
  Arrows10,
  Arrows10,
  Bombs5,
  RedRupee,
  RecoveryHeart,
};
const std::array<Item, 11> normalBottles = {
  I_EmptyBottle,
  I_MilkBottle,
  I_RedPotionBottle,
  I_GreenPotionBottle,
  I_BluePotionBottle,
  I_FairyBottle,
  I_FishBottle,
  I_BugsBottle,
  I_PoeBottle,
  I_BigPoeBottle,
  I_BlueFireBottle,
};
std::array<Item, 9> dungeonRewards = {
  I_KokiriEmerald,
  I_GoronRuby,
  I_ZoraSaphhire,
  I_ForestMedallion,
  I_FireMedallion,
  I_WaterMedallion,
  I_SpiritMedallion,
  I_ShadowMedallion,
  I_LightMedallion,
};
const std::array<Item, 20> dungeonItems = {
  DekuTree_Map,
  DodongosCavern_Map,
  JabuJabusBelly_Map,
  ForestTemple_Map,
  FireTemple_Map,
  WaterTemple_Map,
  SpiritTemple_Map,
  ShadowTemple_Map,
  IceCavern_Map,
  BottomOfTheWell_Map,

  DekuTree_Compass,
  DodongosCavern_Compass,
  JabuJabusBelly_Compass,
  ForestTemple_Compass,
  FireTemple_Compass,
  WaterTemple_Compass,
  SpiritTemple_Compass,
  ShadowTemple_Compass,
  IceCavern_Compass,
  BottomOfTheWell_Compass,
};
const std::array<Item, 28> normalRupees = {
  BlueRupee,
  BlueRupee,
  BlueRupee,
  BlueRupee,
  BlueRupee,
  BlueRupee,
  BlueRupee,
  BlueRupee,
  BlueRupee,
  BlueRupee,
  BlueRupee,
  BlueRupee,
  BlueRupee,
  RedRupee,
  RedRupee,
  RedRupee,
  RedRupee,
  RedRupee,
  PurpleRupee,
  PurpleRupee,
  PurpleRupee,
  PurpleRupee,
  PurpleRupee,
  PurpleRupee,
  PurpleRupee,
  HugeRupee,
  HugeRupee,
  HugeRupee,
};
const std::array<Item, 28> shopsanityRupees = {
  BlueRupee,
  BlueRupee,
  RedRupee,
  RedRupee,
  RedRupee,
  RedRupee,
  RedRupee,
  RedRupee,
  RedRupee,
  RedRupee,
  RedRupee,
  RedRupee,
  PurpleRupee,
  PurpleRupee,
  PurpleRupee,
  PurpleRupee,
  PurpleRupee,
  PurpleRupee,
  PurpleRupee,
  PurpleRupee,
  PurpleRupee,
  PurpleRupee,
  HugeRupee,
  HugeRupee,
  HugeRupee,
  HugeRupee,
  HugeRupee,
  I_ProgressiveWallet,
};
const std::array<Item, 28> minShopItems = {
  BuyDekuShield,
  BuyHylianShield,
  BuyGoronTunic,
  BuyZoraTunic,
  BuyDekuNut5,
  BuyDekuNut5,
  BuyDekuNut10,
  BuyDekuStick1,
  BuyDekuStick1,
  BuyDekuSeeds30,
  BuyArrows10,
  BuyArrows10,
  BuyArrows30,
  BuyArrows50,
  BuyBombchu5,
  BuyBombchu10,
  BuyBombchu10,
  BuyBombchu20,
  BuyBombs525,
  BuyBombs535,
  BuyBombs10,
  BuyBombs20,
  BuyGreenPotion,
  BuyRedPotion30,
  BuyBlueFire,
  BuyFairysSpirit,
  BuyBottleBug,
  BuyFish,
};
const std::array<Item, 19> dekuScrubItems = {
  DekuNuts5,
  DekuNuts5,
  DekuNuts5,
  DekuNuts5,
  DekuNuts5,
  DekuStick1,
  Bombs5,
  Bombs5,
  Bombs5,
  Bombs5,
  Bombs5,
  RecoveryHeart,
  RecoveryHeart,
  RecoveryHeart,
  RecoveryHeart,
  BlueRupee,
  BlueRupee,
  BlueRupee,
  BlueRupee,
};
const std::array<Item, 12> songList = {
  I_ZeldasLullaby,
  I_EponasSong,
  I_SunsSong,
  I_SariasSong,
  I_SongOfTime,
  I_SongOfStorms,
  I_MinuetOfForest,
  I_PreludeOfLight,
  I_BoleroOfFire,
  I_SerenadeOfWater,
  I_NocturneOfShadow,
  I_RequiemOfSpirit,
};
const std::array<Item, 10> tradeItems = {
  I_PocketEgg,
  I_PocketCucco,
  I_Cojiro,
  I_OddMushroom,
  I_PoachersSaw,
  I_BrokenSword,
  I_Prescription,
  I_EyeballFrog,
  I_Eyedrops,
  I_ClaimCheck,
};

static void AddItemToPool(std::vector<Item>& pool, const Item& item, size_t count = 1) {
  pool.resize(pool.size() + count, item);
}

static void AddItemToMainPool(const Item& item, size_t count = 1) {
  ItemPool.resize(ItemPool.size() + count, item);
}

template <size_t N>
static void JoinPools(std::vector<Item>& pool1, const std::array<Item, N>& pool2) {
  for (const Item item : pool2) {
    AddItemToPool(pool1, item);
  }
}

static void AddRandomBottle(std::vector<Item> bottlePool) {
  u32 idx = Random() % bottlePool.size();
  AddItemToMainPool(bottlePool[idx]);
  bottlePool.erase(bottlePool.begin() + idx);
}

static Item GetJunkItem() {
  if (IceTrapValue.Is(ICETRAPS_MAYHEM) || IceTrapValue.Is(ICETRAPS_ONSLAUGHT)) {
    return IceTrap;
  } else if (IceTrapValue.Is(ICETRAPS_EXTRA)) {
    u8 idx = Random() % (JunkPoolItems.size());
    return JunkPoolItems[idx];
  }
  //Ice Trap is the last item in JunkPoolItems, so subtract 1 to never hit that index
  u8 idx = Random() % (JunkPoolItems.size() - 1);
  return JunkPoolItems[idx];
}

static Item GetPendingJunkItem() {
  if (PendingJunkPool.empty()) {
    return GetJunkItem();
  }

  int idx = Random() % (PendingJunkPool.size());
  Item returnItem = PendingJunkPool[idx];
  PendingJunkPool.erase(PendingJunkPool.begin() + idx);
  return returnItem;
}

//Replace junk items in the pool with pending junk
static void ReplaceMaxItem(Item itemToReplace, int max) {
  int itemCount = 0;
  for (Item& item : ItemPool) {
    if (item == itemToReplace) {
      if (itemCount >= max) {
        item = GetJunkItem();
      }
      itemCount++;
    }
  }
}

void PlaceJunkInExcludedLocation(ItemLocation * il) {
  //place a non-advancement item in this location
  for (size_t i = 0; i < ItemPool.size(); i++) {
    if (!ItemPool[i].IsAdvancement()) {
      PlaceItemInLocation(il, ItemPool[i]);
      ItemPool.erase(ItemPool.begin() + i);
      return;
    }
  }
  printf("ERROR: No Junk to Place!!!\n");
}

static void PlaceVanillaShopItems() {
  PlaceItemInLocation(&KF_ShopItem1,        BuyDekuShield);
  PlaceItemInLocation(&KF_ShopItem2,        BuyDekuNut5);
  PlaceItemInLocation(&KF_ShopItem3,        BuyDekuNut10);
  PlaceItemInLocation(&KF_ShopItem4,        BuyDekuStick1);
  PlaceItemInLocation(&KF_ShopItem5,        BuyDekuSeeds30);
  PlaceItemInLocation(&KF_ShopItem6,        BuyArrows10);
  PlaceItemInLocation(&KF_ShopItem7,        BuyArrows30);
  PlaceItemInLocation(&KF_ShopItem8,        BuyHeart);
  PlaceItemInLocation(&Kak_PotionShopItem1, BuyDekuNut5);
  PlaceItemInLocation(&Kak_PotionShopItem2, BuyFish);
  PlaceItemInLocation(&Kak_PotionShopItem3, BuyRedPotion30);
  PlaceItemInLocation(&Kak_PotionShopItem4, BuyGreenPotion);
  PlaceItemInLocation(&Kak_PotionShopItem5, BuyBlueFire);
  PlaceItemInLocation(&Kak_PotionShopItem6, BuyBottleBug);
  PlaceItemInLocation(&Kak_PotionShopItem7, BuyPoe);
  PlaceItemInLocation(&Kak_PotionShopItem8, BuyFairysSpirit);
  PlaceItemInLocation(&MK_BombchuShopItem1, BuyBombchu5);
  PlaceItemInLocation(&MK_BombchuShopItem2, BuyBombchu10);
  PlaceItemInLocation(&MK_BombchuShopItem3, BuyBombchu10);
  PlaceItemInLocation(&MK_BombchuShopItem4, BuyBombchu10);
  PlaceItemInLocation(&MK_BombchuShopItem5, BuyBombchu20);
  PlaceItemInLocation(&MK_BombchuShopItem6, BuyBombchu20);
  PlaceItemInLocation(&MK_BombchuShopItem7, BuyBombchu20);
  PlaceItemInLocation(&MK_BombchuShopItem8, BuyBombchu20);
  PlaceItemInLocation(&MK_PotionShopItem1,  BuyGreenPotion);
  PlaceItemInLocation(&MK_PotionShopItem2,  BuyBlueFire);
  PlaceItemInLocation(&MK_PotionShopItem3,  BuyRedPotion30);
  PlaceItemInLocation(&MK_PotionShopItem4,  BuyFairysSpirit);
  PlaceItemInLocation(&MK_PotionShopItem5,  BuyDekuNut5);
  PlaceItemInLocation(&MK_PotionShopItem6,  BuyBottleBug);
  PlaceItemInLocation(&MK_PotionShopItem7,  BuyPoe);
  PlaceItemInLocation(&MK_PotionShopItem8,  BuyFish);
  PlaceItemInLocation(&MK_BazaarItem1,      BuyHylianShield);
  PlaceItemInLocation(&MK_BazaarItem2,      BuyBombs535);
  PlaceItemInLocation(&MK_BazaarItem3,      BuyDekuNut5);
  PlaceItemInLocation(&MK_BazaarItem4,      BuyHeart);
  PlaceItemInLocation(&MK_BazaarItem5,      BuyArrows10);
  PlaceItemInLocation(&MK_BazaarItem6,      BuyArrows50);
  PlaceItemInLocation(&MK_BazaarItem7,      BuyDekuStick1);
  PlaceItemInLocation(&MK_BazaarItem8,      BuyArrows30);
  PlaceItemInLocation(&Kak_BazaarItem1,     BuyHylianShield);
  PlaceItemInLocation(&Kak_BazaarItem2,     BuyBombs535);
  PlaceItemInLocation(&Kak_BazaarItem3,     BuyDekuNut5);
  PlaceItemInLocation(&Kak_BazaarItem4,     BuyHeart);
  PlaceItemInLocation(&Kak_BazaarItem5,     BuyArrows10);
  PlaceItemInLocation(&Kak_BazaarItem6,     BuyArrows50);
  PlaceItemInLocation(&Kak_BazaarItem7,     BuyDekuStick1);
  PlaceItemInLocation(&Kak_BazaarItem8,     BuyArrows30);
  PlaceItemInLocation(&ZD_ShopItem1,        BuyZoraTunic);
  PlaceItemInLocation(&ZD_ShopItem2,        BuyArrows10);
  PlaceItemInLocation(&ZD_ShopItem3,        BuyHeart);
  PlaceItemInLocation(&ZD_ShopItem4,        BuyArrows30);
  PlaceItemInLocation(&ZD_ShopItem5,        BuyDekuNut5);
  PlaceItemInLocation(&ZD_ShopItem6,        BuyArrows50);
  PlaceItemInLocation(&ZD_ShopItem7,        BuyFish);
  PlaceItemInLocation(&ZD_ShopItem8,        BuyRedPotion50);
  PlaceItemInLocation(&GC_ShopItem1,        BuyBombs525);
  PlaceItemInLocation(&GC_ShopItem2,        BuyBombs10);
  PlaceItemInLocation(&GC_ShopItem3,        BuyBombs20);
  PlaceItemInLocation(&GC_ShopItem4,        BuyBombs30);
  PlaceItemInLocation(&GC_ShopItem5,        BuyGoronTunic);
  PlaceItemInLocation(&GC_ShopItem6,        BuyHeart);
  PlaceItemInLocation(&GC_ShopItem7,        BuyRedPotion40);
  PlaceItemInLocation(&GC_ShopItem8,        BuyHeart);
}

static void PlaceVanillaDekuScrubItems() {
    PlaceItemInLocation(&ZR_DekuScrubGrottoRear,           BuyRedPotion30);
    PlaceItemInLocation(&ZR_DekuScrubGrottoFront,          BuyGreenPotion);
    PlaceItemInLocation(&SFM_DekuScrubGrottoRear,          BuyRedPotion30);
    PlaceItemInLocation(&SFM_DekuScrubGrottoFront,         BuyGreenPotion);
    PlaceItemInLocation(&LH_DekuScrubGrottoLeft,           BuyDekuNut5);
    PlaceItemInLocation(&LH_DekuScrubGrottoRight,          BuyBombs535);
    PlaceItemInLocation(&LH_DekuScrubGrottoCenter,         BuyArrows30);
    PlaceItemInLocation(&GV_DekuScrubGrottoRear,           BuyRedPotion30);
    PlaceItemInLocation(&GV_DekuScrubGrottoFront,          BuyGreenPotion);
    PlaceItemInLocation(&LW_DekuScrubNearDekuTheaterRight, BuyDekuNut5);
    PlaceItemInLocation(&LW_DekuScrubNearDekuTheaterLeft,  BuyDekuStick1);
    PlaceItemInLocation(&LW_DekuScrubGrottoRear,           BuyArrows30);
    PlaceItemInLocation(&Colossus_DekuScrubGrottoRear,     BuyRedPotion30);
    PlaceItemInLocation(&Colossus_DekuScrubGrottoFront,    BuyGreenPotion);
    PlaceItemInLocation(&DMC_DekuScrub,                    BuyBombs535);
    PlaceItemInLocation(&DMC_DekuScrubGrottoLeft,          BuyDekuNut5);
    PlaceItemInLocation(&DMC_DekuScrubGrottoRight,         BuyBombs535);
    PlaceItemInLocation(&DMC_DekuScrubGrottoCenter,        BuyArrows30);
    PlaceItemInLocation(&GC_DekuScrubGrottoLeft,           BuyDekuNut5);
    PlaceItemInLocation(&GC_DekuScrubGrottoRight,          BuyBombs535);
    PlaceItemInLocation(&GC_DekuScrubGrottoCenter,         BuyArrows30);
    PlaceItemInLocation(&LLR_DekuScrubGrottoLeft,          BuyDekuNut5);
    PlaceItemInLocation(&LLR_DekuScrubGrottoRight,         BuyBombs535);
    PlaceItemInLocation(&LLR_DekuScrubGrottoCenter,        BuyArrows30);

    //Dungeon Scrubs
    if (DekuTreeDungeonMode == DUNGEONMODE_MQ) {
      PlaceItemInLocation(&DekuTree_MQ_DekuScrub, BuyDekuShield);
    }
    if (DodongosCavernDungeonMode == DUNGEONMODE_MQ) {
      PlaceItemInLocation(&DodongosCavern_MQ_DekuScrubLobbyRear,                 BuyDekuStick1);
      PlaceItemInLocation(&DodongosCavern_MQ_DekuScrubLobbyFront,                BuyDekuSeeds30);
      PlaceItemInLocation(&DodongosCavern_MQ_DekuScrubStaircase,                 BuyDekuShield);
      PlaceItemInLocation(&DodongosCavern_MQ_DekuScrubSideRoomNearLowerLizalfos, BuyRedPotion30);
    } else {
      PlaceItemInLocation(&DodongosCavern_DekuScrubNearBombBagLeft,      BuyDekuNut5);
      PlaceItemInLocation(&DodongosCavern_DekuScrubSideRoomNearDodongos, BuyDekuStick1);
      PlaceItemInLocation(&DodongosCavern_DekuScrubNearBombBagRight,     BuyDekuSeeds30);
      PlaceItemInLocation(&DodongosCavern_DekuScrubLobby,                BuyDekuShield);
    }
    if (JabuJabusBellyDungeonMode == DUNGEONMODE_VANILLA) {
      PlaceItemInLocation(&JabuJabusBelly_DekuScrub, BuyDekuNut5);
    }
    if (GanonsCastleDungeonMode == DUNGEONMODE_MQ) {
      PlaceItemInLocation(&GanonsCastle_MQ_DekuScrubRight,       BuyDekuNut5);
      PlaceItemInLocation(&GanonsCastle_MQ_DekuScrubCenterLeft,  BuyDekuNut5);
      PlaceItemInLocation(&GanonsCastle_MQ_DekuScrubCenter,      BuyDekuNut5);
      PlaceItemInLocation(&GanonsCastle_MQ_DekuScrubCenterRight, BuyDekuNut5);
      PlaceItemInLocation(&GanonsCastle_MQ_DekuScrubLeft,        BuyDekuNut5);
    } else {
      PlaceItemInLocation(&GanonsCastle_DekuScrubCenterLeft,  BuyBombs535);
      PlaceItemInLocation(&GanonsCastle_DekuScrubCenterRight, BuyArrows30);
      PlaceItemInLocation(&GanonsCastle_DekuScrubRight,       BuyRedPotion30);
      PlaceItemInLocation(&GanonsCastle_DekuScrubLeft,        BuyGreenPotion);
    }


}

static void PlaceVanillaMapsAndCompasses() {
  //Maps
  PlaceItemInLocation(&DekuTree_MapChest,         DekuTree_Map);
  PlaceItemInLocation(&DodongosCavern_MapChest,   DodongosCavern_Map);
  PlaceItemInLocation(&JabuJabusBelly_MapChest,   JabuJabusBelly_Map);
  PlaceItemInLocation(&ForestTemple_MapChest,     ForestTemple_Map);
  PlaceItemInLocation(&FireTemple_MapChest,       FireTemple_Map);
  PlaceItemInLocation(&WaterTemple_MapChest,      WaterTemple_Map);
  PlaceItemInLocation(&SpiritTemple_MapChest,     SpiritTemple_Map);
  PlaceItemInLocation(&ShadowTemple_MapChest,     ShadowTemple_Map);
  PlaceItemInLocation(&BottomOfTheWell_MapChest,  BottomOfTheWell_Map);
  PlaceItemInLocation(&IceCavern_MapChest,        IceCavern_Map);

  //Compasses
  PlaceItemInLocation(&DekuTree_CompassChest,        DekuTree_Compass);
  PlaceItemInLocation(&DodongosCavern_CompassChest,  DodongosCavern_Compass);
  PlaceItemInLocation(&JabuJabusBelly_CompassChest,  JabuJabusBelly_Compass);
  PlaceItemInLocation(&ForestTemple_BluePoeChest,    ForestTemple_Compass);
  PlaceItemInLocation(&FireTemple_CompassChest,      FireTemple_Compass);
  PlaceItemInLocation(&WaterTemple_CompassChest,     WaterTemple_Compass);
  PlaceItemInLocation(&SpiritTemple_CompassChest,    SpiritTemple_Compass);
  PlaceItemInLocation(&ShadowTemple_CompassChest,    ShadowTemple_Compass);
  PlaceItemInLocation(&BottomOfTheWell_CompassChest, BottomOfTheWell_Compass);
  PlaceItemInLocation(&IceCavern_CompassChest,       IceCavern_Compass);
}

static void PlaceVanillaSmallKeys() {
    //Forest Temple
    PlaceItemInLocation(&ForestTemple_FirstRoomChest,    ForestTemple_SmallKey);
    PlaceItemInLocation(&ForestTemple_FirstStalfosChest, ForestTemple_SmallKey);
    PlaceItemInLocation(&ForestTemple_FloormasterChest,  ForestTemple_SmallKey);
    PlaceItemInLocation(&ForestTemple_RedPoeChest,       ForestTemple_SmallKey);
    PlaceItemInLocation(&ForestTemple_WellChest,         ForestTemple_SmallKey);

    //Fire Temple
    PlaceItemInLocation(&FireTemple_NearBossChest,                 FireTemple_SmallKey);
    PlaceItemInLocation(&FireTemple_BigLavaRoomBlockedDoorChest,   FireTemple_SmallKey);
    PlaceItemInLocation(&FireTemple_BigLavaRoomLowerOpenDoorChest, FireTemple_SmallKey);
    PlaceItemInLocation(&FireTemple_BoulderMazeLowerChest,         FireTemple_SmallKey);
    PlaceItemInLocation(&FireTemple_BoulderMazeUpperChest,         FireTemple_SmallKey);
    PlaceItemInLocation(&FireTemple_BoulderMazeShortcutChest,      FireTemple_SmallKey);
    PlaceItemInLocation(&FireTemple_BoulderMazeSideRoomChest,      FireTemple_SmallKey);
    PlaceItemInLocation(&FireTemple_HighestGoronChest,             FireTemple_SmallKey);

    //Water Temple
    PlaceItemInLocation(&WaterTemple_TorchesChest,          WaterTemple_SmallKey);
    PlaceItemInLocation(&WaterTemple_RiverChest,            WaterTemple_SmallKey);
    PlaceItemInLocation(&WaterTemple_DragonChest,           WaterTemple_SmallKey);
    PlaceItemInLocation(&WaterTemple_CrackedWallChest,      WaterTemple_SmallKey);
    PlaceItemInLocation(&WaterTemple_CentralPillarChest,    WaterTemple_SmallKey);
    PlaceItemInLocation(&WaterTemple_CentralBowTargetChest, WaterTemple_SmallKey);

    //Spirit Temple
    PlaceItemInLocation(&SpiritTemple_ChildEarlyTorchesChest, SpiritTemple_SmallKey);
    PlaceItemInLocation(&SpiritTemple_EarlyAdultRightChest,   SpiritTemple_SmallKey);
    PlaceItemInLocation(&SpiritTemple_NearFourArmosChest,     SpiritTemple_SmallKey);
    PlaceItemInLocation(&SpiritTemple_StatueRoomHandChest,    SpiritTemple_SmallKey);
    PlaceItemInLocation(&SpiritTemple_SunBlockRoomChest,      SpiritTemple_SmallKey);

    //Shadow Temple
    PlaceItemInLocation(&ShadowTemple_EarlySilverRupeeChest,     ShadowTemple_SmallKey);
    PlaceItemInLocation(&ShadowTemple_FallingSpikesSwitchChest,  ShadowTemple_SmallKey);
    PlaceItemInLocation(&ShadowTemple_InvisibleFloormasterChest, ShadowTemple_SmallKey);
    PlaceItemInLocation(&ShadowTemple_AfterWindHiddenChest,      ShadowTemple_SmallKey);
    PlaceItemInLocation(&ShadowTemple_FreestandingKey,           ShadowTemple_SmallKey);

    //Bottom of the Well
    PlaceItemInLocation(&BottomOfTheWell_FrontLeftFakeWallChest,   BottomOfTheWell_SmallKey);
    PlaceItemInLocation(&BottomOfTheWell_RightBottomFakeWallChest, BottomOfTheWell_SmallKey);
    PlaceItemInLocation(&BottomOfTheWell_FreestandingKey,          BottomOfTheWell_SmallKey);

    //Gerudo Training Grounds
    PlaceItemInLocation(&GerudoTrainingGrounds_BeamosChest,                GerudoTrainingGrounds_SmallKey);
    PlaceItemInLocation(&GerudoTrainingGrounds_EyeStatueChest,             GerudoTrainingGrounds_SmallKey);
    PlaceItemInLocation(&GerudoTrainingGrounds_HammerRoomSwitchChest,      GerudoTrainingGrounds_SmallKey);
    PlaceItemInLocation(&GerudoTrainingGrounds_HeavyBlockThirdChest,       GerudoTrainingGrounds_SmallKey);
    PlaceItemInLocation(&GerudoTrainingGrounds_HiddenCeilingChest,         GerudoTrainingGrounds_SmallKey);
    PlaceItemInLocation(&GerudoTrainingGrounds_NearScarecrowChest,         GerudoTrainingGrounds_SmallKey);
    PlaceItemInLocation(&GerudoTrainingGrounds_StalfosChest,               GerudoTrainingGrounds_SmallKey);
    PlaceItemInLocation(&GerudoTrainingGrounds_UnderwaterSilverRupeeChest, GerudoTrainingGrounds_SmallKey);
    PlaceItemInLocation(&GerudoTrainingGrounds_FreestandingKey,            GerudoTrainingGrounds_SmallKey);

    //Ganon's Castle
    PlaceItemInLocation(&GanonsCastle_LightTrialInvisibleEnemiesChest, GanonsCastle_SmallKey);
    PlaceItemInLocation(&GanonsCastle_LightTrialLullabyChest,          GanonsCastle_SmallKey);
}

static void PlaceVanillaBossKeys() {
  PlaceItemInLocation(&ForestTemple_BossKeyChest, ForestTemple_BossKey);
  PlaceItemInLocation(&FireTemple_BossKeyChest,   FireTemple_BossKey);
  PlaceItemInLocation(&WaterTemple_BossKeyChest,  WaterTemple_BossKey);
  PlaceItemInLocation(&SpiritTemple_BossKeyChest, SpiritTemple_BossKey);
  PlaceItemInLocation(&ShadowTemple_BossKeyChest, ShadowTemple_BossKey);
}

static void PlaceVanillaSkulltulaTokens() {
    PlaceItemInLocation(&KF_GS_BeanPatch,               GoldSkulltulaToken);
    PlaceItemInLocation(&KF_GS_KnowItAllHouse,          GoldSkulltulaToken);
    PlaceItemInLocation(&KF_GS_HouseOfTwins,            GoldSkulltulaToken);
    PlaceItemInLocation(&LW_GS_BeanPatchNearBridge,     GoldSkulltulaToken);
    PlaceItemInLocation(&LW_GS_BeanPatchNearTheater,    GoldSkulltulaToken);
    PlaceItemInLocation(&LW_GS_AboveTheater,            GoldSkulltulaToken);
    PlaceItemInLocation(&SFM_GS,                        GoldSkulltulaToken);
    PlaceItemInLocation(&HF_GS_NearKakGrotto,           GoldSkulltulaToken);
    PlaceItemInLocation(&HF_GS_CowGrotto,               GoldSkulltulaToken);
    PlaceItemInLocation(&MK_GS_GuardHouse,              GoldSkulltulaToken);
    PlaceItemInLocation(&HC_GS_Tree,                    GoldSkulltulaToken);
    PlaceItemInLocation(&HC_GS_StormsGrotto,            GoldSkulltulaToken);
    PlaceItemInLocation(&OGC_GS,                        GoldSkulltulaToken);
    PlaceItemInLocation(&LLR_GS_Tree,                   GoldSkulltulaToken);
    PlaceItemInLocation(&LLR_GS_RainShed,               GoldSkulltulaToken);
    PlaceItemInLocation(&LLR_GS_HouseWindow,            GoldSkulltulaToken);
    PlaceItemInLocation(&LLR_GS_BackWall,               GoldSkulltulaToken);
    PlaceItemInLocation(&Kak_GS_HouseUnderConstruction, GoldSkulltulaToken);
    PlaceItemInLocation(&Kak_GS_SkulltulaHouse,         GoldSkulltulaToken);
    PlaceItemInLocation(&Kak_GS_GuardsHouse,            GoldSkulltulaToken);
    PlaceItemInLocation(&Kak_GS_Tree,                   GoldSkulltulaToken);
    PlaceItemInLocation(&Kak_GS_Watchtower,             GoldSkulltulaToken);
    PlaceItemInLocation(&Kak_GS_AboveImpasHouse,        GoldSkulltulaToken);
    PlaceItemInLocation(&GY_GS_Wall,                    GoldSkulltulaToken);
    PlaceItemInLocation(&GY_GS_BeanPatch,               GoldSkulltulaToken);
    PlaceItemInLocation(&DMT_GS_BeanPatch,              GoldSkulltulaToken);
    PlaceItemInLocation(&DMT_GS_NearKak,                GoldSkulltulaToken);
    PlaceItemInLocation(&DMT_GS_FallingRocksPath,       GoldSkulltulaToken);
    PlaceItemInLocation(&DMT_GS_AboveDodongosCavern,    GoldSkulltulaToken);
    PlaceItemInLocation(&GC_GS_BoulderMaze,             GoldSkulltulaToken);
    PlaceItemInLocation(&GC_GS_CenterPlatform,          GoldSkulltulaToken);
    PlaceItemInLocation(&DMC_GS_Crate,                  GoldSkulltulaToken);
    PlaceItemInLocation(&DMC_GS_BeanPatch,              GoldSkulltulaToken);
    PlaceItemInLocation(&ZR_GS_Ladder,                  GoldSkulltulaToken);
    PlaceItemInLocation(&ZR_GS_Tree,                    GoldSkulltulaToken);
    PlaceItemInLocation(&ZR_GS_NearRaisedGrottos,       GoldSkulltulaToken);
    PlaceItemInLocation(&ZR_GS_AboveBridge,             GoldSkulltulaToken);
    PlaceItemInLocation(&ZD_GS_FrozenWaterfall,         GoldSkulltulaToken);
    PlaceItemInLocation(&ZF_GS_Tree,                    GoldSkulltulaToken);
    PlaceItemInLocation(&ZF_GS_AboveTheLog,             GoldSkulltulaToken);
    PlaceItemInLocation(&ZF_GS_HiddenCave,              GoldSkulltulaToken);
    PlaceItemInLocation(&LH_GS_BeanPatch,               GoldSkulltulaToken);
    PlaceItemInLocation(&LH_GS_LabWall,                 GoldSkulltulaToken);
    PlaceItemInLocation(&LH_GS_SmallIsland,             GoldSkulltulaToken);
    PlaceItemInLocation(&LH_GS_Tree,                    GoldSkulltulaToken);
    PlaceItemInLocation(&LH_GS_LabCrate,                GoldSkulltulaToken);
    PlaceItemInLocation(&GV_GS_SmallBridge,             GoldSkulltulaToken);
    PlaceItemInLocation(&GV_GS_BeanPatch,               GoldSkulltulaToken);
    PlaceItemInLocation(&GV_GS_BehindTent,              GoldSkulltulaToken);
    PlaceItemInLocation(&GV_GS_Pillar,                  GoldSkulltulaToken);
    PlaceItemInLocation(&GF_GS_ArcheryRange,            GoldSkulltulaToken);
    PlaceItemInLocation(&GF_GS_TopFloor,                GoldSkulltulaToken);
    PlaceItemInLocation(&HW_GS,                         GoldSkulltulaToken);
    PlaceItemInLocation(&Colossus_GS_BeanPatch,         GoldSkulltulaToken);
    PlaceItemInLocation(&Colossus_GS_Tree,              GoldSkulltulaToken);
    PlaceItemInLocation(&Colossus_GS_Hill,              GoldSkulltulaToken);

    //Dungeons
    PlaceItemInLocation(&DekuTree_GS_CompassRoom,                     GoldSkulltulaToken);
    PlaceItemInLocation(&DekuTree_GS_BasementVines,                   GoldSkulltulaToken);
    PlaceItemInLocation(&DekuTree_GS_BasementGate,                    GoldSkulltulaToken);
    PlaceItemInLocation(&DekuTree_GS_BasementBackRoom,                GoldSkulltulaToken);

    PlaceItemInLocation(&DodongosCavern_GS_SideRoomNearLowerLizalfos, GoldSkulltulaToken);
    PlaceItemInLocation(&DodongosCavern_GS_VinesAboveStairs,          GoldSkulltulaToken);
    PlaceItemInLocation(&DodongosCavern_GS_BackRoom,                  GoldSkulltulaToken);
    PlaceItemInLocation(&DodongosCavern_GS_AlcoveAboveStairs,         GoldSkulltulaToken);
    PlaceItemInLocation(&DodongosCavern_GS_Scarecrow,                 GoldSkulltulaToken);

    PlaceItemInLocation(&JabuJabusBelly_GS_WaterSwitchRoom,           GoldSkulltulaToken);
    PlaceItemInLocation(&JabuJabusBelly_GS_LobbyBasementLower,        GoldSkulltulaToken);
    PlaceItemInLocation(&JabuJabusBelly_GS_LobbyBasementUpper,        GoldSkulltulaToken);
    PlaceItemInLocation(&JabuJabusBelly_GS_NearBoss,                  GoldSkulltulaToken);

    PlaceItemInLocation(&ForestTemple_GS_FirstRoom,                   GoldSkulltulaToken);
    PlaceItemInLocation(&ForestTemple_GS_Lobby,                       GoldSkulltulaToken);
    PlaceItemInLocation(&ForestTemple_GS_RaisedIslandCourtyard,       GoldSkulltulaToken);
    PlaceItemInLocation(&ForestTemple_GS_LevelIslandCourtyard,        GoldSkulltulaToken);
    PlaceItemInLocation(&ForestTemple_GS_Basement,                    GoldSkulltulaToken);

    PlaceItemInLocation(&FireTemple_GS_SongOfTimeRoom,                GoldSkulltulaToken);
    PlaceItemInLocation(&FireTemple_GS_BoulderMaze,                   GoldSkulltulaToken);
    PlaceItemInLocation(&FireTemple_GS_ScarecrowClimb,                GoldSkulltulaToken);
    PlaceItemInLocation(&FireTemple_GS_ScarecrowTop,                  GoldSkulltulaToken);
    PlaceItemInLocation(&FireTemple_GS_BossKeyLoop,                   GoldSkulltulaToken);

    PlaceItemInLocation(&WaterTemple_GS_BehindGate,                   GoldSkulltulaToken);
    PlaceItemInLocation(&WaterTemple_GS_River,                        GoldSkulltulaToken);
    PlaceItemInLocation(&WaterTemple_GS_FallingPlatformRoom,          GoldSkulltulaToken);
    PlaceItemInLocation(&WaterTemple_GS_CentralPillar,                GoldSkulltulaToken);
    PlaceItemInLocation(&WaterTemple_GS_NearBossKeyChest,             GoldSkulltulaToken);

    PlaceItemInLocation(&SpiritTemple_GS_MetalFence,                  GoldSkulltulaToken);
    PlaceItemInLocation(&SpiritTemple_GS_SunOnFloorRoom,              GoldSkulltulaToken);
    PlaceItemInLocation(&SpiritTemple_GS_HallAfterSunBlockRoom,       GoldSkulltulaToken);
    PlaceItemInLocation(&SpiritTemple_GS_BoulderRoom,                 GoldSkulltulaToken);
    PlaceItemInLocation(&SpiritTemple_GS_Lobby,                       GoldSkulltulaToken);

    PlaceItemInLocation(&ShadowTemple_GS_LikeLikeRoom,                GoldSkulltulaToken);
    PlaceItemInLocation(&ShadowTemple_GS_FallingSpikesRoom,           GoldSkulltulaToken);
    PlaceItemInLocation(&ShadowTemple_GS_SingleGiantPot,              GoldSkulltulaToken);
    PlaceItemInLocation(&ShadowTemple_GS_NearShip,                    GoldSkulltulaToken);
    PlaceItemInLocation(&ShadowTemple_GS_TripleGiantPot,              GoldSkulltulaToken);

    PlaceItemInLocation(&BottomOfTheWell_GS_WestInnerRoom,            GoldSkulltulaToken);
    PlaceItemInLocation(&BottomOfTheWell_GS_EastInnerRoom,            GoldSkulltulaToken);
    PlaceItemInLocation(&BottomOfTheWell_GS_LikeLikeCage,             GoldSkulltulaToken);

    PlaceItemInLocation(&IceCavern_GS_SpinningScytheRoom,             GoldSkulltulaToken);
    PlaceItemInLocation(&IceCavern_GS_HeartPieceRoom,                 GoldSkulltulaToken);
    PlaceItemInLocation(&IceCavern_GS_PushBlockRoom,                  GoldSkulltulaToken);
}

static void PlaceVanillaCowMilk() {
  PlaceItemInLocation(&KF_LinksHouseCow,    Milk);
  PlaceItemInLocation(&HF_CowGrottoCow,     Milk);
  PlaceItemInLocation(&GV_Cow,              Milk);
  PlaceItemInLocation(&Kak_ImpasHouseCow,   Milk);
  PlaceItemInLocation(&DMT_CowGrottoCow,    Milk);
  PlaceItemInLocation(&LLR_StablesLeftCow,  Milk);
  PlaceItemInLocation(&LLR_StablesRightCow, Milk);
  PlaceItemInLocation(&LLR_TowerLeftCow,    Milk);
  PlaceItemInLocation(&LLR_TowerRightCow,   Milk);

  if (JabuJabusBellyDungeonMode == DUNGEONMODE_MQ) {
    PlaceItemInLocation(&JabuJabusBelly_MQ_Cow, Milk);
  }
}

static void SetScarceItemPool() {
  ReplaceMaxItem(I_ProgressiveBombchus, 3);
  ReplaceMaxItem(Bombchu5, 1);
  ReplaceMaxItem(Bombchu10, 2);
  ReplaceMaxItem(Bombchu20, 0);
  ReplaceMaxItem(I_ProgressiveMagic, 1);
  ReplaceMaxItem(I_DoubleDefense, 0);
  ReplaceMaxItem(I_ProgressiveStickCapacity, 1);
  ReplaceMaxItem(I_ProgressiveNutCapacity, 1);
  ReplaceMaxItem(I_ProgressiveBow, 2);
  ReplaceMaxItem(I_ProgressiveBulletBag, 2);
  ReplaceMaxItem(I_ProgressiveBombBag, 2);
  ReplaceMaxItem(HeartContainer, 0);
}

static void SetMinimalItemPool() {
  ReplaceMaxItem(I_ProgressiveBombchus, 1);
  ReplaceMaxItem(Bombchu5, 1);
  ReplaceMaxItem(Bombchu10, 0);
  ReplaceMaxItem(Bombchu20, 0);
  ReplaceMaxItem(I_NayrusLove, 0);
  ReplaceMaxItem(I_ProgressiveMagic, 1);
  ReplaceMaxItem(I_DoubleDefense, 0);
  ReplaceMaxItem(I_ProgressiveStickCapacity, 0);
  ReplaceMaxItem(I_ProgressiveNutCapacity, 0);
  ReplaceMaxItem(I_ProgressiveBow, 1);
  ReplaceMaxItem(I_ProgressiveBulletBag, 1);
  ReplaceMaxItem(I_ProgressiveBombBag, 1);
  ReplaceMaxItem(PieceOfHeart, 0);
  ReplaceMaxItem(HeartContainer, 0);
}

//Randomizes dungeon keys for the "Own Dungeon" setting
template <typename Container>
static void RandomizeDungeonKeys(const Container& KeyRequirements, Item smallKeyItem, u8 maxKeys) {
  for (size_t i = 0; i < maxKeys; i++) {
    std::vector<ItemLocation *> dungeonPool;
    for (const ItemLocationKeyPairing& ilkp : KeyRequirements) {
      if (ilkp.keysRequired <= i && ilkp.loc->GetPlacedItemName() == "No Item") {
        dungeonPool.push_back(ilkp.loc);
      }
    }
    const u32 locIdx = Random() % dungeonPool.size();
    PlaceItemInLocation(dungeonPool[locIdx], smallKeyItem);
  }
}

//Randomizes Maps/Compasses/Boss Keys for the "Own Dungeon" settings
template <typename Container>
static void RandomizeDungeonItem(const Container& dungeonLocations, Item item) {
  std::vector<ItemLocation *> dungeonPool;
  for (const ItemLocationKeyPairing& ilkp : dungeonLocations) {

    //don't allow boss keys to be placed at Heart Container spots in glitchless logic
    if (item.GetName().rfind("Boss Key") != std::string::npos &&
        ilkp.loc->GetName().rfind("Heart Container") != std::string::npos &&
        Settings::Logic.Is(LOGIC_GLITCHLESS)) {
          continue;
    }

    if (ilkp.loc->GetPlacedItemName() == "No Item") {
      dungeonPool.push_back(ilkp.loc);
    }
  }
  const u32 locIdx = Random() % dungeonPool.size();
  PlaceItemInLocation(dungeonPool[locIdx], item);
}

void GenerateItemPool() {

  ItemPool = {};

  PlaceItemInLocation(&HC_ZeldasLetter, I_ZeldasLetter);
  PlaceItemInLocation(&Ganon, I_Triforce); //The Triforce is only used to make sure Ganon is accessible

  if (ShuffleKokiriSword) {
    AddItemToMainPool(I_KokiriSword);
  } else {
    PlaceItemInLocation(&KF_KokiriSwordChest, I_KokiriSword);
  }

  if (ShuffleWeirdEgg) {
    AddItemToMainPool(I_WeirdEgg);
  } else {
    PlaceItemInLocation(&HC_MalonEgg, I_WeirdEgg);
  }

  if (ShuffleOcarinas) {
    AddItemToMainPool(I_ProgressiveOcarina, 2);
    if (ItemPoolValue.Is(ITEMPOOL_PLENTIFUL)) {
      AddItemToPool(PendingJunkPool, I_ProgressiveOcarina);
    }
  } else {
    PlaceItemInLocation(&LW_GiftFromSaria, I_ProgressiveOcarina);
    PlaceItemInLocation(&HF_OcarinaOfTimeItem, I_ProgressiveOcarina);
  }

  if (ShuffleCows) {
    //9 total cow locations
    for (u8 i = 0; i < 9; i++) {
      AddItemToMainPool(GetJunkItem());
    }
    //extra location for Jabu MQ
    if (JabuJabusBellyDungeonMode == DUNGEONMODE_MQ) {
      AddItemToMainPool(GetJunkItem());
    }
  } else {
    PlaceVanillaCowMilk();
  }

  if (ShuffleMagicBeans) {
    AddItemToMainPool(I_MagicBeanPack);
    if (ItemPoolValue.Is(ITEMPOOL_PLENTIFUL)) {
      AddItemToPool(PendingJunkPool, I_MagicBeanPack);
    }
  } else {
    PlaceItemInLocation(&ZR_MagicBeanSalesman, I_MagicBean);
  }

  //TODO: sort between mq and vanilla dungeon skulltulas

  if (Tokensanity.Is(TOKENSANITY_VANILLA)) {
    PlaceVanillaSkulltulaTokens();
  } else {
    AddItemToMainPool(GoldSkulltulaToken, 100);
  }

  if (BombchusInLogic) {
    AddItemToMainPool(I_ProgressiveBombchus, 5);
  } else {
    AddItemToMainPool(Bombchu5);
    AddItemToMainPool(Bombchu10, 3);
    AddItemToMainPool(Bombchu20);
  }

  //Ice Traps
  AddItemToMainPool(IceTrap);
  if (GerudoTrainingGroundsDungeonMode == DUNGEONMODE_VANILLA) {
    AddItemToMainPool(IceTrap);
  }
  if (GanonsCastleDungeonMode == DUNGEONMODE_VANILLA) {
    AddItemToMainPool(IceTrap, 4);
  }

  //Gerudo Fortress
  if (GerudoFortress.Is(GERUDOFORTRESS_OPEN)) {
    PlaceItemInLocation(&GF_NorthF1Carpenter, RecoveryHeart);
    PlaceItemInLocation(&GF_NorthF2Carpenter, RecoveryHeart);
    PlaceItemInLocation(&GF_SouthF1Carpenter, RecoveryHeart);
    PlaceItemInLocation(&GF_SouthF2Carpenter, RecoveryHeart);
  } else if (GerudoKeys.IsNot(GERUDOKEYS_VANILLA)) {
    if (GerudoFortress.Is(GERUDOFORTRESS_FAST)) {
      AddItemToMainPool(GerudoFortress_SmallKey);
      PlaceItemInLocation(&GF_NorthF2Carpenter, RecoveryHeart);
      PlaceItemInLocation(&GF_SouthF1Carpenter, RecoveryHeart);
      PlaceItemInLocation(&GF_SouthF2Carpenter, RecoveryHeart);
    } else {
      AddItemToMainPool(GerudoFortress_SmallKey, 4);
    }
    if (ItemPoolValue.Is(ITEMPOOL_PLENTIFUL)) {
      AddItemToPool(PendingJunkPool, GerudoFortress_SmallKey);
    }
  } else {
    if (GerudoFortress.Is(GERUDOFORTRESS_FAST)) {
      PlaceItemInLocation(&GF_NorthF1Carpenter, GerudoFortress_SmallKey);
      PlaceItemInLocation(&GF_NorthF2Carpenter, RecoveryHeart);
      PlaceItemInLocation(&GF_SouthF1Carpenter, RecoveryHeart);
      PlaceItemInLocation(&GF_SouthF2Carpenter, RecoveryHeart);
    } else {
      PlaceItemInLocation(&GF_NorthF1Carpenter, GerudoFortress_SmallKey);
      PlaceItemInLocation(&GF_NorthF2Carpenter, GerudoFortress_SmallKey);
      PlaceItemInLocation(&GF_SouthF1Carpenter, GerudoFortress_SmallKey);
      PlaceItemInLocation(&GF_SouthF2Carpenter, GerudoFortress_SmallKey);
    }
  }

  //Gerudo Token
  if (ShuffleGerudoToken && GerudoFortress.IsNot(GERUDOFORTRESS_OPEN)) {
    AddItemToMainPool(I_GerudoToken);
  } else if (ShuffleGerudoToken) {
    AddItemToPool(PendingJunkPool, I_GerudoToken);
    PlaceItemInLocation(&GF_GerudoToken, IceTrap);
  } else {
    PlaceItemInLocation(&GF_GerudoToken, I_GerudoToken);
  }

  if (ItemPoolValue.Is(ITEMPOOL_PLENTIFUL)) {
    if (ShuffleGerudoToken) {
      AddItemToPool(PendingJunkPool, I_GerudoToken);
    }

    // Plentiful small keys
    if (Keysanity.Is(KEYSANITY_ANYWHERE)) {
      AddItemToPool(PendingJunkPool, BottomOfTheWell_SmallKey);
      AddItemToPool(PendingJunkPool, ForestTemple_SmallKey);
      AddItemToPool(PendingJunkPool, FireTemple_SmallKey);
      AddItemToPool(PendingJunkPool, WaterTemple_SmallKey);
      AddItemToPool(PendingJunkPool, SpiritTemple_SmallKey);
      AddItemToPool(PendingJunkPool, ShadowTemple_SmallKey);
      AddItemToPool(PendingJunkPool, GerudoTrainingGrounds_SmallKey);
      AddItemToPool(PendingJunkPool, GanonsCastle_SmallKey);
    }

    if (BossKeysanity.Is(BOSSKEYSANITY_ANYWHERE)) {
      AddItemToPool(PendingJunkPool, ForestTemple_BossKey);
      AddItemToPool(PendingJunkPool, FireTemple_BossKey);
      AddItemToPool(PendingJunkPool, WaterTemple_BossKey);
      AddItemToPool(PendingJunkPool, SpiritTemple_BossKey);
      AddItemToPool(PendingJunkPool, ShadowTemple_BossKey);
    }

    if (GanonsBossKey.Is(GANONSBOSSKEY_ANYWHERE)) {
      AddItemToPool(PendingJunkPool, GanonsCastle_BossKey);
    }
  }

  //Shopsanity
  if (!Settings::Shopsanity) {
    PlaceVanillaShopItems();
    if (BombchusInLogic) {
      // PlaceItemInLocation(&KF_ShopItem8,    &BuyBombchu5);
      // PlaceItemInLocation(&MK_BazaarItem4,  &BuyBombchu5);
      // PlaceItemInLocation(&Kak_BazaarItem4, &BuyBombchu5);
    }
    JoinPools(ItemPool, normalRupees);
  } else {
    //shopsanity settings
  }

  //scrubsanity
  if (Settings::Scrubsanity.IsNot(SCRUBSANITY_OFF)) {
    //Deku Tree
    if (DekuTreeDungeonMode == DUNGEONMODE_MQ) {
      AddItemToMainPool(I_DekuShield);
    }

    //Dodongos Cavern
    AddItemToMainPool(DekuStick1);
    AddItemToMainPool(I_DekuShield);
    if (DodongosCavernDungeonMode == DUNGEONMODE_MQ) {
      AddItemToMainPool(RecoveryHeart);
    } else {
      AddItemToMainPool(DekuNuts5);
    }

    //Jabu Jabus Belly
    if (JabuJabusBellyDungeonMode == DUNGEONMODE_VANILLA) {
      AddItemToMainPool(DekuNuts5);
    }

    //Ganons Castle
    AddItemToMainPool(Bombs5);
    AddItemToMainPool(RecoveryHeart);
    AddItemToMainPool(BlueRupee);
    if (GanonsCastleDungeonMode == DUNGEONMODE_MQ) {
      AddItemToMainPool(DekuNuts5);
    }

    //Overworld Scrubs
    JoinPools(ItemPool, dekuScrubItems);

    //I'm not sure what this is for, but it was in ootr so I copied it
    for (u8 i = 0; i < 7; i++) {
      if (Random() % 3) {
        AddItemToMainPool(Arrows30);
      } else {
        AddItemToMainPool(DekuSeeds30);
      }
    }
  } else {
    PlaceVanillaDekuScrubItems();
  }

  JoinPools(ItemPool, alwaysItems);

  //dungeon pools
  if (DekuTreeDungeonMode == DUNGEONMODE_MQ) {
    JoinPools(ItemPool, DT_MQ);
  } else {
    JoinPools(ItemPool, DT_Vanilla);
  }
  if (DodongosCavernDungeonMode == DUNGEONMODE_MQ) {
    JoinPools(ItemPool, DC_MQ);
  } else {
    JoinPools(ItemPool, DC_Vanilla);
  }
  if (JabuJabusBellyDungeonMode == DUNGEONMODE_MQ) {
    JoinPools(ItemPool, JB_MQ);
  }
  if (ForestTempleDungeonMode == DUNGEONMODE_MQ) {
    JoinPools(ItemPool, FoT_MQ);
  } else {
    JoinPools(ItemPool, FoT_Vanilla);
  }
  if (FireTempleDungeonMode == DUNGEONMODE_MQ) {
    JoinPools(ItemPool, FiT_MQ);
  } else {
    JoinPools(ItemPool, FiT_Vanilla);
  }
  if (SpiritTempleDungeonMode == DUNGEONMODE_MQ) {
    JoinPools(ItemPool, SpT_MQ);
  } else {
    JoinPools(ItemPool, SpT_Vanilla);
  }
  if (ShadowTempleDungeonMode == DUNGEONMODE_MQ) {
    JoinPools(ItemPool, ShT_MQ);
  } else {
    JoinPools(ItemPool, ShT_Vanilla);
  }
  if (BottomOfTheWellDungeonMode == DUNGEONMODE_VANILLA) {
    JoinPools(ItemPool, BW_Vanilla);
  }
  if (GerudoTrainingGroundsDungeonMode == DUNGEONMODE_MQ) {
    JoinPools(ItemPool, GTG_MQ);
  } else {
    JoinPools(ItemPool, GTG_Vanilla);
  }
  if (GanonsCastleDungeonMode == DUNGEONMODE_MQ) {
    JoinPools(ItemPool, GC_MQ);
  } else {
    JoinPools(ItemPool, GC_Vanilla);
  }

  u8 rutoBottles = 1;
  if (ZorasFountain.Is(ZORASFOUNTAIN_OPEN)) {
    rutoBottles = 0;
  }

  //Add 4 total bottles
  u8 bottleCount = 4;
  std::vector<Item> bottles;
  bottles.assign(normalBottles.begin(), normalBottles.end());

  for (u8 i = 0; i < bottleCount; i++) {
    if (i >= rutoBottles) {
      AddRandomBottle(bottles);
    } else {
      AddItemToMainPool(I_RutosLetter);
    }
  }

  //TODO: trade item logic
  AddItemToMainPool(I_ClaimCheck);

  //add songs
  JoinPools(ItemPool, songList);
  if (ShuffleSongs && ItemPoolValue.Is(ITEMPOOL_PLENTIFUL)) {
    JoinPools(PendingJunkPool, songList);
  }

  //TODO: free scarecrow

  //TODO: no epona race

  if (MapsAndCompasses.Is(MAPSANDCOMPASSES_START_WITH)) {
    //10 maps + 10 compasses = 20 items
    for (u8 i = 0; i < 20; i++) {
      AddItemToMainPool(GetJunkItem());
    }
  }

  //Vanilla Dungeon Placements
  if (MapsAndCompasses.Is(MAPSANDCOMPASSES_VANILLA)) {
    PlaceVanillaMapsAndCompasses();
  }

  if (Keysanity.Is(KEYSANITY_VANILLA)) {
    PlaceVanillaSmallKeys();
  }

  if (BossKeysanity.Is(BOSSKEYSANITY_VANILLA)) {
    PlaceVanillaBossKeys();
  }

  if (GanonsBossKey.Value<u8>() >= GANONSBOSSKEY_LACS_VANILLA) {
    PlaceItemInLocation(&ToT_LightArrowCutscene, GanonsCastle_BossKey);
  } else if (GanonsBossKey.Is(GANONSBOSSKEY_VANILLA)) {
    PlaceItemInLocation(&GanonsCastle_BossKeyChest, GanonsCastle_BossKey);
  }

  //dungeon only dungeon placements
  if (Keysanity.Is(KEYSANITY_OWN_DUNGEON)) {
    RandomizeDungeonKeys(ForestTempleKeyRequirements,          ForestTemple_SmallKey,          5);
    RandomizeDungeonKeys(FireTempleKeyRequirements,            FireTemple_SmallKey,            8);
    RandomizeDungeonKeys(WaterTempleKeyRequirements,           WaterTemple_SmallKey,           6);
    RandomizeDungeonKeys(SpiritTempleKeyRequirements,          SpiritTemple_SmallKey,          5);
    RandomizeDungeonKeys(ShadowTempleKeyRequirements,          ShadowTemple_SmallKey,          5);
    RandomizeDungeonKeys(BottomOfTheWellKeyRequirements,       BottomOfTheWell_SmallKey,       3);
    RandomizeDungeonKeys(GerudoTrainingGroundsKeyRequirements, GerudoTrainingGrounds_SmallKey, 9);
    RandomizeDungeonKeys(GanonsCastleKeyRequirements,          GanonsCastle_SmallKey,          2);
  }

  if (BossKeysanity.Is(BOSSKEYSANITY_OWN_DUNGEON)) {
    RandomizeDungeonItem(ForestTempleKeyRequirements, ForestTemple_BossKey);
    RandomizeDungeonItem(FireTempleKeyRequirements,   FireTemple_BossKey);
    RandomizeDungeonItem(WaterTempleKeyRequirements,  WaterTemple_BossKey);
    RandomizeDungeonItem(SpiritTempleKeyRequirements, SpiritTemple_BossKey);
    RandomizeDungeonItem(ShadowTempleKeyRequirements, ShadowTemple_BossKey);
  }

  if (MapsAndCompasses.Is(MAPSANDCOMPASSES_OWN_DUNGEON)) {
    RandomizeDungeonItem(DekuTreeKeyRequirements,        DekuTree_Map);
    RandomizeDungeonItem(DodongosCavernKeyRequirements,  DodongosCavern_Map);
    RandomizeDungeonItem(JabuJabusBellyKeyRequirements,  JabuJabusBelly_Map);
    RandomizeDungeonItem(ForestTempleKeyRequirements,    ForestTemple_Map);
    RandomizeDungeonItem(FireTempleKeyRequirements,      FireTemple_Map);
    RandomizeDungeonItem(WaterTempleKeyRequirements,     WaterTemple_Map);
    RandomizeDungeonItem(SpiritTempleKeyRequirements,    SpiritTemple_Map);
    RandomizeDungeonItem(ShadowTempleKeyRequirements,    ShadowTemple_Map);
    RandomizeDungeonItem(BottomOfTheWellKeyRequirements, BottomOfTheWell_Map);
    RandomizeDungeonItem(IceCavernKeyRequirements,       IceCavern_Map);

    RandomizeDungeonItem(DekuTreeKeyRequirements,        DekuTree_Compass);
    RandomizeDungeonItem(DodongosCavernKeyRequirements,  DodongosCavern_Compass);
    RandomizeDungeonItem(JabuJabusBellyKeyRequirements,  JabuJabusBelly_Compass);
    RandomizeDungeonItem(ForestTempleKeyRequirements,    ForestTemple_Compass);
    RandomizeDungeonItem(FireTempleKeyRequirements,      FireTemple_Compass);
    RandomizeDungeonItem(WaterTempleKeyRequirements,     WaterTemple_Compass);
    RandomizeDungeonItem(SpiritTempleKeyRequirements,    SpiritTemple_Compass);
    RandomizeDungeonItem(ShadowTempleKeyRequirements,    ShadowTemple_Compass);
    RandomizeDungeonItem(BottomOfTheWellKeyRequirements, BottomOfTheWell_Compass);
    RandomizeDungeonItem(IceCavernKeyRequirements,       IceCavern_Compass);
  }

  if(GanonsBossKey.Is(GANONSBOSSKEY_OWN_DUNGEON)) {
    RandomizeDungeonItem(GanonsCastleKeyRequirements, GanonsCastle_BossKey);
  }

  //all locations placements
  if (Keysanity.Is(KEYSANITY_ANYWHERE)) {
    AddItemToMainPool(ForestTemple_SmallKey, 5);
    AddItemToMainPool(FireTemple_SmallKey, 8);
    AddItemToMainPool(WaterTemple_SmallKey, 6);
    AddItemToMainPool(SpiritTemple_SmallKey, 5);
    AddItemToMainPool(ShadowTemple_SmallKey, 5);
    AddItemToMainPool(BottomOfTheWell_SmallKey, 3);
    AddItemToMainPool(GerudoTrainingGrounds_SmallKey, 9);
    AddItemToMainPool(GanonsCastle_SmallKey, 2);
  }

  if (BossKeysanity.Is(BOSSKEYSANITY_ANYWHERE)) {
    AddItemToMainPool(ForestTemple_BossKey);
    AddItemToMainPool(FireTemple_BossKey);
    AddItemToMainPool(WaterTemple_BossKey);
    AddItemToMainPool(SpiritTemple_BossKey);
    AddItemToMainPool(ShadowTemple_BossKey);
  }

  if (GanonsBossKey.Is(GANONSBOSSKEY_ANYWHERE)) {
    AddItemToMainPool(GanonsCastle_BossKey);
  }

  if (MapsAndCompasses.Is(MAPSANDCOMPASSES_ANYWHERE)) {
    AddItemToMainPool(DekuTree_Map);
    AddItemToMainPool(DodongosCavern_Map);
    AddItemToMainPool(JabuJabusBelly_Map);
    AddItemToMainPool(ForestTemple_Map);
    AddItemToMainPool(FireTemple_Map);
    AddItemToMainPool(WaterTemple_Map);
    AddItemToMainPool(SpiritTemple_Map);
    AddItemToMainPool(ShadowTemple_Map);
    AddItemToMainPool(BottomOfTheWell_Map);
    AddItemToMainPool(IceCavern_Map);

    AddItemToMainPool(DekuTree_Compass);
    AddItemToMainPool(DodongosCavern_Compass);
    AddItemToMainPool(JabuJabusBelly_Compass);
    AddItemToMainPool(ForestTemple_Compass);
    AddItemToMainPool(FireTemple_Compass);
    AddItemToMainPool(WaterTemple_Compass);
    AddItemToMainPool(SpiritTemple_Compass);
    AddItemToMainPool(ShadowTemple_Compass);
    AddItemToMainPool(BottomOfTheWell_Compass);
    AddItemToMainPool(IceCavern_Compass);
  }

  if (ItemPoolValue.Is(ITEMPOOL_PLENTIFUL)) {
    JoinPools(ItemPool, easyItems);
  } else {
    JoinPools(ItemPool, normalItems);
  }

  if (!ShuffleKokiriSword) {
    ReplaceMaxItem(I_KokiriSword, 0);
  }

  //Replace ice traps with junk from the pending junk pool if necessary
  if (IceTrapValue.Is(ICETRAPS_OFF)) {
    ReplaceMaxItem(IceTrap, 0);
  }
  //Replace all junk items with ice traps for onslaught mode
  else if (IceTrapValue.Is(ICETRAPS_ONSLAUGHT)) {
    for (u8 i = 0; i < JunkPoolItems.size() - 3; i++) { // -3 Omits Huge Rupees and Deku Nuts 10
      ReplaceMaxItem(JunkPoolItems[i], 0);
    }
  }

  if (ItemPoolValue.Is(ITEMPOOL_SCARCE)) {
    SetScarceItemPool();
  } else if (ItemPoolValue.Is(ITEMPOOL_MINIMAL)) {
    SetMinimalItemPool();
  }

  //this feels ugly and there's probably a better way, but
  //it replaces random junk with pending junk.
  bool junkSet;
  for (Item pendingJunk : PendingJunkPool) {
    junkSet = false;
    for (Item& item : ItemPool) {
      for (const Item& junk : JunkPoolItems) {
        if (item == junk && item != HugeRupee && item != DekuNuts10) {
          item = pendingJunk;
          junkSet = true;
          break;
        }
      }
      if (junkSet) break;
    }
  }
}

void AddJunk() {
  PlacementLog_Msg("HAD TO PLACE EXTRA JUNK ");
  AddItemToMainPool(GetPendingJunkItem());
}
