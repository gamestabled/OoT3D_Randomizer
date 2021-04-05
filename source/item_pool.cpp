#include "item_pool.hpp"
#include "random.hpp"
#include "spoiler_log.hpp"
#include "fill.hpp"

using namespace Settings;

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

void AddItemToPool(std::vector<Item>& pool, const Item& item, size_t count /*= 1*/) {
  pool.insert(pool.end(), count, item);
}

template <typename FromPool>
static void AddItemsToPool(std::vector<Item>& toPool, const FromPool& fromPool) {
  toPool.insert(toPool.end(), std::cbegin(fromPool), std::cend(fromPool));
}

static void AddItemToMainPool(const Item& item, size_t count = 1) {
  ItemPool.insert(ItemPool.end(), count, item);
}

static void AddRandomBottle(std::vector<Item>& bottlePool) {
  AddItemToMainPool(RandomElement(bottlePool, true));
}

Item GetJunkItem() {
  if (IceTrapValue.Is(ICETRAPS_MAYHEM) || IceTrapValue.Is(ICETRAPS_ONSLAUGHT)) {
    return IceTrap;
  } else if (IceTrapValue.Is(ICETRAPS_EXTRA)) {
      return RandomElement(JunkPoolItems);
  }
  //Ice Trap is the last item in JunkPoolItems, so subtract 1 to never hit that index
  u8 idx = Random(0, JunkPoolItems.size() - 1);
  return JunkPoolItems[idx];
}

static Item GetPendingJunkItem() {
  if (PendingJunkPool.empty()) {
    return GetJunkItem();
  }

  return RandomElement(PendingJunkPool, true);
}

//Replace junk items in the pool with pending junk
static void ReplaceMaxItem(const Item& itemToReplace, int max) {
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
    PlaceItemInLocation(&ZR_DekuScrubGrottoRear,           RedPotionRefill);
    PlaceItemInLocation(&ZR_DekuScrubGrottoFront,          GreenPotionRefill);
    PlaceItemInLocation(&SFM_DekuScrubGrottoRear,          RedPotionRefill);
    PlaceItemInLocation(&SFM_DekuScrubGrottoFront,         GreenPotionRefill);
    PlaceItemInLocation(&LH_DekuScrubGrottoLeft,           DekuNuts5);
    PlaceItemInLocation(&LH_DekuScrubGrottoRight,          Bombs5);
    PlaceItemInLocation(&LH_DekuScrubGrottoCenter,         Arrows30);
    PlaceItemInLocation(&GV_DekuScrubGrottoRear,           RedPotionRefill);
    PlaceItemInLocation(&GV_DekuScrubGrottoFront,          GreenPotionRefill);
    PlaceItemInLocation(&LW_DekuScrubNearDekuTheaterRight, DekuNuts5);
    PlaceItemInLocation(&LW_DekuScrubNearDekuTheaterLeft,  DekuStick1);
    PlaceItemInLocation(&LW_DekuScrubGrottoRear,           Arrows30);
    PlaceItemInLocation(&Colossus_DekuScrubGrottoRear,     RedPotionRefill);
    PlaceItemInLocation(&Colossus_DekuScrubGrottoFront,    GreenPotionRefill);
    PlaceItemInLocation(&DMC_DekuScrub,                    Bombs5);
    PlaceItemInLocation(&DMC_DekuScrubGrottoLeft,          DekuNuts5);
    PlaceItemInLocation(&DMC_DekuScrubGrottoRight,         Bombs5);
    PlaceItemInLocation(&DMC_DekuScrubGrottoCenter,        Arrows30);
    PlaceItemInLocation(&GC_DekuScrubGrottoLeft,           DekuNuts5);
    PlaceItemInLocation(&GC_DekuScrubGrottoRight,          Bombs5);
    PlaceItemInLocation(&GC_DekuScrubGrottoCenter,         Arrows30);
    PlaceItemInLocation(&LLR_DekuScrubGrottoLeft,          DekuNuts5);
    PlaceItemInLocation(&LLR_DekuScrubGrottoRight,         Bombs5);
    PlaceItemInLocation(&LLR_DekuScrubGrottoCenter,        Arrows30);

    //Dungeon Scrubs
    if (DekuTreeDungeonMode == DUNGEONMODE_MQ) {
      PlaceItemInLocation(&DekuTree_MQ_DekuScrub, I_DekuShield);
    }
    if (DodongosCavernDungeonMode == DUNGEONMODE_MQ) {
      PlaceItemInLocation(&DodongosCavern_MQ_DekuScrubLobbyRear,                 DekuStick1);
      PlaceItemInLocation(&DodongosCavern_MQ_DekuScrubLobbyFront,                DekuSeeds30);
      PlaceItemInLocation(&DodongosCavern_MQ_DekuScrubStaircase,                 I_DekuShield);
      PlaceItemInLocation(&DodongosCavern_MQ_DekuScrubSideRoomNearLowerLizalfos, RedPotionRefill);
    } else {
      PlaceItemInLocation(&DodongosCavern_DekuScrubNearBombBagLeft,      DekuNuts5);
      PlaceItemInLocation(&DodongosCavern_DekuScrubSideRoomNearDodongos, DekuStick1);
      PlaceItemInLocation(&DodongosCavern_DekuScrubNearBombBagRight,     DekuSeeds30);
      PlaceItemInLocation(&DodongosCavern_DekuScrubLobby,                I_DekuShield);
    }
    if (JabuJabusBellyDungeonMode == DUNGEONMODE_VANILLA) {
      PlaceItemInLocation(&JabuJabusBelly_DekuScrub, DekuNuts5);
    }
    if (GanonsCastleDungeonMode == DUNGEONMODE_MQ) {
      PlaceItemInLocation(&GanonsCastle_MQ_DekuScrubRight,       DekuNuts5);
      PlaceItemInLocation(&GanonsCastle_MQ_DekuScrubCenterLeft,  DekuNuts5);
      PlaceItemInLocation(&GanonsCastle_MQ_DekuScrubCenter,      DekuNuts5);
      PlaceItemInLocation(&GanonsCastle_MQ_DekuScrubCenterRight, DekuNuts5);
      PlaceItemInLocation(&GanonsCastle_MQ_DekuScrubLeft,        DekuNuts5);
    } else {
      PlaceItemInLocation(&GanonsCastle_DekuScrubCenterLeft,  Bombs5);
      PlaceItemInLocation(&GanonsCastle_DekuScrubCenterRight, Arrows30);
      PlaceItemInLocation(&GanonsCastle_DekuScrubRight,       RedPotionRefill);
      PlaceItemInLocation(&GanonsCastle_DekuScrubLeft,        GreenPotionRefill);
    }


}

static void PlaceVanillaMapsAndCompasses() {
  //Maps
  if (DekuTreeDungeonMode == DUNGEONMODE_MQ) {
    PlaceItemInLocation(&DekuTree_MQ_MapChest,     DekuTree_Map);
    PlaceItemInLocation(&DekuTree_MQ_CompassChest, DekuTree_Compass);
  } else {
    PlaceItemInLocation(&DekuTree_MapChest,     DekuTree_Map);
    PlaceItemInLocation(&DekuTree_CompassChest, DekuTree_Compass);
  }

  if (DodongosCavernDungeonMode == DUNGEONMODE_MQ) {
    PlaceItemInLocation(&DodongosCavern_MQ_MapChest,     DodongosCavern_Map);
    PlaceItemInLocation(&DodongosCavern_MQ_CompassChest, DodongosCavern_Compass);
  } else {
    PlaceItemInLocation(&DodongosCavern_MapChest,     DodongosCavern_Map);
    PlaceItemInLocation(&DodongosCavern_CompassChest, DodongosCavern_Compass);
  }

  if (JabuJabusBellyDungeonMode == DUNGEONMODE_MQ) {
    PlaceItemInLocation(&JabuJabusBelly_MQ_MapChest,     JabuJabusBelly_Map);
    PlaceItemInLocation(&JabuJabusBelly_MQ_CompassChest, JabuJabusBelly_Compass);
  } else {
    PlaceItemInLocation(&JabuJabusBelly_MapChest,     JabuJabusBelly_Map);
    PlaceItemInLocation(&JabuJabusBelly_CompassChest, JabuJabusBelly_Compass);
  }

  if (ForestTempleDungeonMode == DUNGEONMODE_MQ) {
    PlaceItemInLocation(&ForestTemple_MQ_MapChest,     ForestTemple_Map);
    PlaceItemInLocation(&ForestTemple_MQ_CompassChest, ForestTemple_Compass);
  } else {
    PlaceItemInLocation(&ForestTemple_MapChest,     ForestTemple_Map);
    PlaceItemInLocation(&ForestTemple_BluePoeChest, ForestTemple_Compass);
  }

  if (FireTempleDungeonMode == DUNGEONMODE_MQ) {
    PlaceItemInLocation(&FireTemple_MQ_MapChest,     FireTemple_Map);
    PlaceItemInLocation(&FireTemple_MQ_CompassChest, FireTemple_Compass);
  } else {
    PlaceItemInLocation(&FireTemple_MapChest,     FireTemple_Map);
    PlaceItemInLocation(&FireTemple_CompassChest, FireTemple_Compass);
  }

  if (WaterTempleDungeonMode == DUNGEONMODE_MQ) {
    PlaceItemInLocation(&WaterTemple_MQ_MapChest,     WaterTemple_Map);
    PlaceItemInLocation(&WaterTemple_MQ_CompassChest, WaterTemple_Compass);
  } else {
    PlaceItemInLocation(&WaterTemple_MapChest,     WaterTemple_Map);
    PlaceItemInLocation(&WaterTemple_CompassChest, WaterTemple_Compass);
  }

  if (SpiritTempleDungeonMode == DUNGEONMODE_MQ) {
    PlaceItemInLocation(&SpiritTemple_MQ_MapChest,     SpiritTemple_Map);
    PlaceItemInLocation(&SpiritTemple_MQ_CompassChest, SpiritTemple_Compass);
  } else {
    PlaceItemInLocation(&SpiritTemple_MapChest,     SpiritTemple_Map);
    PlaceItemInLocation(&SpiritTemple_CompassChest, SpiritTemple_Compass);
  }

  if (ShadowTempleDungeonMode == DUNGEONMODE_MQ) {
    PlaceItemInLocation(&ShadowTemple_MQ_MapChest,     ShadowTemple_Map);
    PlaceItemInLocation(&ShadowTemple_MQ_CompassChest, ShadowTemple_Compass);
  } else {
    PlaceItemInLocation(&ShadowTemple_MapChest,     ShadowTemple_Map);
    PlaceItemInLocation(&ShadowTemple_CompassChest, ShadowTemple_Compass);
  }

  if (BottomOfTheWellDungeonMode == DUNGEONMODE_MQ) {
    PlaceItemInLocation(&BottomOfTheWell_MQ_MapChest,     BottomOfTheWell_Map);
    PlaceItemInLocation(&BottomOfTheWell_MQ_CompassChest, BottomOfTheWell_Compass);
  } else {
    PlaceItemInLocation(&BottomOfTheWell_MapChest,     BottomOfTheWell_Map);
    PlaceItemInLocation(&BottomOfTheWell_CompassChest, BottomOfTheWell_Compass);
  }

  if (IceCavernDungeonMode == DUNGEONMODE_MQ) {
    PlaceItemInLocation(&IceCavern_MQ_MapChest,     IceCavern_Map);
    PlaceItemInLocation(&IceCavern_MQ_CompassChest, IceCavern_Compass);
  } else {
    PlaceItemInLocation(&IceCavern_MapChest,     IceCavern_Map);
    PlaceItemInLocation(&IceCavern_CompassChest, IceCavern_Compass);
  }
}

static void PlaceVanillaSmallKeys() {
    //Forest Temple
    if (ForestTempleDungeonMode == DUNGEONMODE_MQ) {
      PlaceItemInLocation(&ForestTemple_MQ_WolfosChest,                     ForestTemple_SmallKey);
      PlaceItemInLocation(&ForestTemple_MQ_FirstRoomChest,                  ForestTemple_SmallKey);
      PlaceItemInLocation(&ForestTemple_MQ_RaisedIslandCourtyardLowerChest, ForestTemple_SmallKey);
      PlaceItemInLocation(&ForestTemple_MQ_RaisedIslandCourtyardUpperChest, ForestTemple_SmallKey);
      PlaceItemInLocation(&ForestTemple_MQ_RedeadChest,                     ForestTemple_SmallKey);
      PlaceItemInLocation(&ForestTemple_MQ_WellChest,                       ForestTemple_SmallKey);
    } else {
      PlaceItemInLocation(&ForestTemple_FirstRoomChest,    ForestTemple_SmallKey);
      PlaceItemInLocation(&ForestTemple_FirstStalfosChest, ForestTemple_SmallKey);
      PlaceItemInLocation(&ForestTemple_FloormasterChest,  ForestTemple_SmallKey);
      PlaceItemInLocation(&ForestTemple_RedPoeChest,       ForestTemple_SmallKey);
      PlaceItemInLocation(&ForestTemple_WellChest,         ForestTemple_SmallKey);
    }

    //Fire Temple
    if (FireTempleDungeonMode == DUNGEONMODE_MQ) {
      PlaceItemInLocation(&FireTemple_MQ_BigLavaRoomBlockedDoorChest, FireTemple_SmallKey);
      PlaceItemInLocation(&FireTemple_MQ_NearBossChest,               FireTemple_SmallKey);
      PlaceItemInLocation(&FireTemple_MQ_LizalfosMazeSideRoomChest,   FireTemple_SmallKey);
      PlaceItemInLocation(&FireTemple_MQ_ChestOnFire,                 FireTemple_SmallKey);
      PlaceItemInLocation(&FireTemple_MQ_FreestandingKey,             FireTemple_SmallKey);
    } else {
      PlaceItemInLocation(&FireTemple_NearBossChest,                 FireTemple_SmallKey);
      PlaceItemInLocation(&FireTemple_BigLavaRoomBlockedDoorChest,   FireTemple_SmallKey);
      PlaceItemInLocation(&FireTemple_BigLavaRoomLowerOpenDoorChest, FireTemple_SmallKey);
      PlaceItemInLocation(&FireTemple_BoulderMazeLowerChest,         FireTemple_SmallKey);
      PlaceItemInLocation(&FireTemple_BoulderMazeUpperChest,         FireTemple_SmallKey);
      PlaceItemInLocation(&FireTemple_BoulderMazeShortcutChest,      FireTemple_SmallKey);
      PlaceItemInLocation(&FireTemple_BoulderMazeSideRoomChest,      FireTemple_SmallKey);
      PlaceItemInLocation(&FireTemple_HighestGoronChest,             FireTemple_SmallKey);
    }

    //Water Temple
    if (WaterTempleDungeonMode == DUNGEONMODE_MQ) {
      PlaceItemInLocation(&WaterTemple_MQ_CentralPillarChest, WaterTemple_SmallKey);
      PlaceItemInLocation(&WaterTemple_MQ_FreestandingKey,    WaterTemple_SmallKey);
    } else {
      PlaceItemInLocation(&WaterTemple_TorchesChest,          WaterTemple_SmallKey);
      PlaceItemInLocation(&WaterTemple_RiverChest,            WaterTemple_SmallKey);
      PlaceItemInLocation(&WaterTemple_DragonChest,           WaterTemple_SmallKey);
      PlaceItemInLocation(&WaterTemple_CrackedWallChest,      WaterTemple_SmallKey);
      PlaceItemInLocation(&WaterTemple_CentralPillarChest,    WaterTemple_SmallKey);
      PlaceItemInLocation(&WaterTemple_CentralBowTargetChest, WaterTemple_SmallKey);
    }

    //Spirit Temple
    if (SpiritTempleDungeonMode == DUNGEONMODE_MQ) {
      PlaceItemInLocation(&SpiritTemple_MQ_ChildHammerSwitchChest,     SpiritTemple_SmallKey);
      PlaceItemInLocation(&SpiritTemple_MQ_ChildClimbSouthChest,       SpiritTemple_SmallKey);
      PlaceItemInLocation(&SpiritTemple_MQ_MapRoomEnemyChest,          SpiritTemple_SmallKey);
      PlaceItemInLocation(&SpiritTemple_MQ_EntranceBackLeftChest,      SpiritTemple_SmallKey);
      PlaceItemInLocation(&SpiritTemple_MQ_EntranceFrontRightChest,    SpiritTemple_SmallKey);
      PlaceItemInLocation(&SpiritTemple_MQ_MirrorPuzzleInvisibleChest, SpiritTemple_SmallKey);
      PlaceItemInLocation(&SpiritTemple_MQ_SilverBlockHallwayChest,    SpiritTemple_SmallKey);
    } else {
      PlaceItemInLocation(&SpiritTemple_ChildEarlyTorchesChest, SpiritTemple_SmallKey);
      PlaceItemInLocation(&SpiritTemple_EarlyAdultRightChest,   SpiritTemple_SmallKey);
      PlaceItemInLocation(&SpiritTemple_NearFourArmosChest,     SpiritTemple_SmallKey);
      PlaceItemInLocation(&SpiritTemple_StatueRoomHandChest,    SpiritTemple_SmallKey);
      PlaceItemInLocation(&SpiritTemple_SunBlockRoomChest,      SpiritTemple_SmallKey);
    }

    //Shadow Temple
    if (ShadowTempleDungeonMode == DUNGEONMODE_MQ) {
      PlaceItemInLocation(&ShadowTemple_MQ_FallingSpikesSwitchChest,      ShadowTemple_SmallKey);
      PlaceItemInLocation(&ShadowTemple_MQ_InvisibleBladesInvisibleChest, ShadowTemple_SmallKey);
      PlaceItemInLocation(&ShadowTemple_MQ_EarlyGibdosChest,              ShadowTemple_SmallKey);
      PlaceItemInLocation(&ShadowTemple_MQ_NearShipInvisibleChest,        ShadowTemple_SmallKey);
      PlaceItemInLocation(&ShadowTemple_MQ_WindHintChest,                 ShadowTemple_SmallKey);
      PlaceItemInLocation(&ShadowTemple_MQ_FreestandingKey,               ShadowTemple_SmallKey);
    } else {
      PlaceItemInLocation(&ShadowTemple_EarlySilverRupeeChest,     ShadowTemple_SmallKey);
      PlaceItemInLocation(&ShadowTemple_FallingSpikesSwitchChest,  ShadowTemple_SmallKey);
      PlaceItemInLocation(&ShadowTemple_InvisibleFloormasterChest, ShadowTemple_SmallKey);
      PlaceItemInLocation(&ShadowTemple_AfterWindHiddenChest,      ShadowTemple_SmallKey);
      PlaceItemInLocation(&ShadowTemple_FreestandingKey,           ShadowTemple_SmallKey);
    }

    //Bottom of the Well
    if (BottomOfTheWellDungeonMode == DUNGEONMODE_MQ) {
      PlaceItemInLocation(&BottomOfTheWell_MQ_DeadHandFreestandingKey,      BottomOfTheWell_SmallKey);
      PlaceItemInLocation(&BottomOfTheWell_MQ_EastInnerRoomFreestandingKey, BottomOfTheWell_SmallKey);
    } else {
      PlaceItemInLocation(&BottomOfTheWell_FrontLeftFakeWallChest,   BottomOfTheWell_SmallKey);
      PlaceItemInLocation(&BottomOfTheWell_RightBottomFakeWallChest, BottomOfTheWell_SmallKey);
      PlaceItemInLocation(&BottomOfTheWell_FreestandingKey,          BottomOfTheWell_SmallKey);
    }

    //Gerudo Training Grounds
    if (GerudoTrainingGroundsDungeonMode == DUNGEONMODE_MQ) {
      PlaceItemInLocation(&GerudoTrainingGrounds_MQ_DinalfosChest,              GerudoTrainingGrounds_SmallKey);
      PlaceItemInLocation(&GerudoTrainingGrounds_MQ_FlameCircleChest,           GerudoTrainingGrounds_SmallKey);
      PlaceItemInLocation(&GerudoTrainingGrounds_MQ_UnderwaterSilverRupeeChest, GerudoTrainingGrounds_SmallKey);
    } else {
      PlaceItemInLocation(&GerudoTrainingGrounds_BeamosChest,                GerudoTrainingGrounds_SmallKey);
      PlaceItemInLocation(&GerudoTrainingGrounds_EyeStatueChest,             GerudoTrainingGrounds_SmallKey);
      PlaceItemInLocation(&GerudoTrainingGrounds_HammerRoomSwitchChest,      GerudoTrainingGrounds_SmallKey);
      PlaceItemInLocation(&GerudoTrainingGrounds_HeavyBlockThirdChest,       GerudoTrainingGrounds_SmallKey);
      PlaceItemInLocation(&GerudoTrainingGrounds_HiddenCeilingChest,         GerudoTrainingGrounds_SmallKey);
      PlaceItemInLocation(&GerudoTrainingGrounds_NearScarecrowChest,         GerudoTrainingGrounds_SmallKey);
      PlaceItemInLocation(&GerudoTrainingGrounds_StalfosChest,               GerudoTrainingGrounds_SmallKey);
      PlaceItemInLocation(&GerudoTrainingGrounds_UnderwaterSilverRupeeChest, GerudoTrainingGrounds_SmallKey);
      PlaceItemInLocation(&GerudoTrainingGrounds_FreestandingKey,            GerudoTrainingGrounds_SmallKey);
    }

    //Ganon's Castle
    if (GanonsCastleDungeonMode == DUNGEONMODE_MQ) {
      PlaceItemInLocation(&GanonsCastle_MQ_ShadowTrialEyeSwitchChest,   GanonsCastle_SmallKey);
      PlaceItemInLocation(&GanonsCastle_MQ_SpiritTrialSunBackLeftChest, GanonsCastle_SmallKey);
      PlaceItemInLocation(&GanonsCastle_MQ_ForestTrialFreestandingKey,  GanonsCastle_SmallKey);
    } else {
      PlaceItemInLocation(&GanonsCastle_LightTrialInvisibleEnemiesChest, GanonsCastle_SmallKey);
      PlaceItemInLocation(&GanonsCastle_LightTrialLullabyChest,          GanonsCastle_SmallKey);
    }
}

static void PlaceVanillaBossKeys() {

  //Forest Temple
  if (ForestTempleDungeonMode == DUNGEONMODE_MQ) {
    PlaceItemInLocation(&ForestTemple_MQ_BossKeyChest, ForestTemple_BossKey);
  } else {
    PlaceItemInLocation(&ForestTemple_BossKeyChest, ForestTemple_BossKey);
  }

  //Fire Temple
  if (FireTempleDungeonMode == DUNGEONMODE_MQ) {
    PlaceItemInLocation(&FireTemple_MQ_BossKeyChest, FireTemple_BossKey);
  } else {
    PlaceItemInLocation(&FireTemple_BossKeyChest, FireTemple_BossKey);
  }

  //Water Temple
  if (WaterTempleDungeonMode == DUNGEONMODE_MQ) {
    PlaceItemInLocation(&WaterTemple_MQ_BossKeyChest,  WaterTemple_BossKey);
  } else {
    PlaceItemInLocation(&WaterTemple_BossKeyChest,  WaterTemple_BossKey);
  }

  //Spirit Temple
  if (SpiritTempleDungeonMode == DUNGEONMODE_MQ) {
    PlaceItemInLocation(&SpiritTemple_MQ_BossKeyChest, SpiritTemple_BossKey);
  } else {
    PlaceItemInLocation(&SpiritTemple_BossKeyChest, SpiritTemple_BossKey);
  }

  //Shadow Temple
  if (ShadowTempleDungeonMode == DUNGEONMODE_MQ) {
    PlaceItemInLocation(&ShadowTemple_MQ_BossKeyChest, ShadowTemple_BossKey);
  } else {
    PlaceItemInLocation(&ShadowTemple_BossKeyChest, ShadowTemple_BossKey);
  }
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

void GenerateItemPool() {

  ItemPool.clear();

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

  if (Tokensanity.Is(TOKENSANITY_OFF)) {
    for (auto& loc : GetLocations(allLocations, Category::cSkulltula)) {
      PlaceItemInLocation(loc, GoldSkulltulaToken);
    }
  } else if (Tokensanity.Is(TOKENSANITY_DUNGEONS)) {
    for (auto& loc : GetLocations(allLocations, Category::cSkulltula)) {
      if (loc->GetScene() >= 0x0A) {
        PlaceItemInLocation(loc, GoldSkulltulaToken);
      } else {
        AddItemToMainPool(GoldSkulltulaToken);
      }
    }
  } else if (Tokensanity.Is(TOKENSANITY_OVERWORLD)) {
    for (auto& loc : GetLocations(allLocations, Category::cSkulltula)) {
      if (loc->GetScene() < 0x0A) {
        PlaceItemInLocation(loc, GoldSkulltulaToken);
      } else {
        AddItemToMainPool(GoldSkulltulaToken);
      }
    }
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
    AddItemsToPool(ItemPool, normalRupees);
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
    AddItemsToPool(ItemPool, dekuScrubItems);

    //I'm not sure what this is for, but it was in ootr so I copied it
    for (u8 i = 0; i < 7; i++) {
      if (Random(0, 3)) {
        AddItemToMainPool(Arrows30);
      } else {
        AddItemToMainPool(DekuSeeds30);
      }
    }
  } else {
    PlaceVanillaDekuScrubItems();
  }

  AddItemsToPool(ItemPool, alwaysItems);

  //dungeon pools
  if (DekuTreeDungeonMode == DUNGEONMODE_MQ) {
    AddItemsToPool(ItemPool, DT_MQ);
  } else {
    AddItemsToPool(ItemPool, DT_Vanilla);
  }
  if (DodongosCavernDungeonMode == DUNGEONMODE_MQ) {
    AddItemsToPool(ItemPool, DC_MQ);
  } else {
    AddItemsToPool(ItemPool, DC_Vanilla);
  }
  if (JabuJabusBellyDungeonMode == DUNGEONMODE_MQ) {
    AddItemsToPool(ItemPool, JB_MQ);
  }
  if (ForestTempleDungeonMode == DUNGEONMODE_MQ) {
    AddItemsToPool(ItemPool, FoT_MQ);
  } else {
    AddItemsToPool(ItemPool, FoT_Vanilla);
  }
  if (FireTempleDungeonMode == DUNGEONMODE_MQ) {
    AddItemsToPool(ItemPool, FiT_MQ);
  } else {
    AddItemsToPool(ItemPool, FiT_Vanilla);
  }
  if (SpiritTempleDungeonMode == DUNGEONMODE_MQ) {
    AddItemsToPool(ItemPool, SpT_MQ);
  } else {
    AddItemsToPool(ItemPool, SpT_Vanilla);
  }
  if (ShadowTempleDungeonMode == DUNGEONMODE_MQ) {
    AddItemsToPool(ItemPool, ShT_MQ);
  } else {
    AddItemsToPool(ItemPool, ShT_Vanilla);
  }
  if (BottomOfTheWellDungeonMode == DUNGEONMODE_VANILLA) {
    AddItemsToPool(ItemPool, BW_Vanilla);
  }
  if (GerudoTrainingGroundsDungeonMode == DUNGEONMODE_MQ) {
    AddItemsToPool(ItemPool, GTG_MQ);
  } else {
    AddItemsToPool(ItemPool, GTG_Vanilla);
  }
  if (GanonsCastleDungeonMode == DUNGEONMODE_MQ) {
    AddItemsToPool(ItemPool, GC_MQ);
  } else {
    AddItemsToPool(ItemPool, GC_Vanilla);
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
  AddItemsToPool(ItemPool, songList);
  if (ShuffleSongs && ItemPoolValue.Is(ITEMPOOL_PLENTIFUL) && !ShuffleSongs.Is(SONGSHUFFLE_DUNGEON_REWARDS)) {
    AddItemsToPool(PendingJunkPool, songList);
  }

  //TODO: free scarecrow

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

  //all locations placements
  if (Keysanity.Is(KEYSANITY_ANYWHERE)) {
    AddItemToMainPool(ForestTemple_SmallKey, 5);
    AddItemToMainPool(FireTemple_SmallKey, 8);
    AddItemToMainPool(WaterTemple_SmallKey, 6);
    AddItemToMainPool(SpiritTemple_SmallKey, 5);
    AddItemToMainPool(ShadowTemple_SmallKey, 4); //SHOULD BE 5, CHANGE WHEN CRASH IS FIXED
    AddItemToMainPool(BottomOfTheWell_SmallKey, 3);
    AddItemToMainPool(GerudoTrainingGrounds_SmallKey, 8); //SHOULD BE 9, CHANGE WHEN CRASH IS FIXED
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
    AddItemsToPool(ItemPool, easyItems);
  } else {
    AddItemsToPool(ItemPool, normalItems);
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
