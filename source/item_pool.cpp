#include "item_pool.hpp"

#include "dungeon.hpp"
#include "fill.hpp"
#include "item_list.hpp"
#include "item_location.hpp"
#include "pool_functions.hpp"
#include "random.hpp"
#include "settings.hpp"
#include "spoiler_log.hpp"

using namespace Settings;
using namespace Dungeon;

std::vector<Item> ItemPool = {};
std::vector<Item> PendingJunkPool = {};
std::vector<Item> dungeonRewards = {
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
  AddElementsToPool(toPool, fromPool);
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

std::vector<Item> ShopItems; //Vector of all shop items, initialized to vanilla items in specific order but can be shuffled and items replaced
//Set vanilla shop item locations before potentially shuffling
void SetVanillaShopItems() {
  ShopItems = {
    //Vanilla KF 
    BuyDekuShield,
    BuyDekuNut5,
    BuyDekuNut10,
    BuyDekuStick1,
    BuyDekuSeeds30,
    BuyArrows10,
    BuyArrows30,
    BuyHeart,
    //Vanilla Kak Potion
    BuyDekuNut5,
    BuyFish,
    BuyRedPotion30,
    BuyGreenPotion,
    BuyBlueFire,
    BuyBottleBug,
    BuyPoe,
    BuyFairysSpirit,
    //Vanilla Bombchu
    BuyBombchu5,
    BuyBombchu10,
    BuyBombchu10,
    BuyBombchu10,
    BuyBombchu20,
    BuyBombchu20,
    BuyBombchu20,
    BuyBombchu20,
    //Vanilla MK Potion
    BuyGreenPotion,
    BuyBlueFire,
    BuyRedPotion30,
    BuyFairysSpirit,
    BuyDekuNut5,
    BuyBottleBug,
    BuyPoe,
    BuyFish,
    //Vanilla MK Bazaar
    BuyHylianShield,
    BuyBombs535,
    BuyDekuNut5,
    BuyHeart,
    BuyArrows10,
    BuyArrows50,
    BuyDekuStick1,
    BuyArrows30,
    //Vanilla Kak Bazaar
    BuyHylianShield,
    BuyBombs535,
    BuyDekuNut5,
    BuyHeart,
    BuyArrows10,
    BuyArrows50,
    BuyDekuStick1,
    BuyArrows30,
    //Vanilla ZD
    BuyZoraTunic,
    BuyArrows10,
    BuyHeart,
    BuyArrows30,
    BuyDekuNut5,
    BuyArrows50,
    BuyFish,
    BuyRedPotion50,
    //Vanilla GC Shop
    BuyBombs525,
    BuyBombs10,
    BuyBombs20,
    BuyBombs30,
    BuyGoronTunic,
    BuyHeart,
    BuyRedPotion40,
    BuyHeart,
  };
}

static void PlaceShopItems() {
  for (size_t i = 0; i < ShopLocationLists.size(); i++) {
    for (size_t j = 0; j < ShopLocationLists[i].size(); j++) {
      //Multiply i by 8 to get the correct shop
      PlaceShopItemInLocation(ShopLocationLists[i][j], ShopItems[i*8 + j], ShopItems[i*8 + j].GetPrice());
    }
  }
}

static int GetShopsanityReplaceAmount() {
  if (Settings::Shopsanity.Is(SHOPSANITY_ONE)) {
    return 1;
  } else if (Settings::Shopsanity.Is(SHOPSANITY_TWO)) {
    return 2;
  } else if (Settings::Shopsanity.Is(SHOPSANITY_THREE)) {
    return 3;
  } else if (Settings::Shopsanity.Is(SHOPSANITY_FOUR)) {
    return 4;
  } else { //Random
    return Random(1, 5);
  }
}

//OoTR uses a fancy betavariate function for a weighted distribution in [0, 300] in increments of 5... For now each price is just equally likely
static int GetRandomShopPrice() {
  return Random(0, 61) * 5;
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
    if (DekuTree.IsMQ()) {
      PlaceItemInLocation(&DekuTree_MQ_DekuScrub, I_DekuShield);
    }
    if (DodongosCavern.IsMQ()) {
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
    if (JabuJabusBelly.IsVanilla()) {
      PlaceItemInLocation(&JabuJabusBelly_DekuScrub, DekuNuts5);
    }
    if (GanonsCastle.IsMQ()) {
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
  for (auto dungeon : dungeonList) {
    dungeon->PlaceVanillaMap();
    dungeon->PlaceVanillaCompass();
  }
}

static void PlaceVanillaSmallKeys() {
  for (auto dungeon : dungeonList) {
    dungeon->PlaceVanillaSmallKeys();
  }
}

static void PlaceVanillaBossKeys() {
  for (auto dungeon : dungeonList) {
    dungeon->PlaceVanillaBossKey();
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

  if (JabuJabusBelly.IsMQ()) {
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

  //Fixed item locations
  PlaceItemInLocation(&HC_ZeldasLetter, I_ZeldasLetter);
  PlaceItemInLocation(&Ganon, I_Triforce); //The Triforce is only used to make sure Ganon is accessible
  PlaceItemInLocation(&MK_BombchuBowlingBombchus, I_BombchuDrop);

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
    if (JabuJabusBelly.IsMQ()) {
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
      if (loc->IsOverworld()) {
        PlaceItemInLocation(loc, GoldSkulltulaToken);
      } else {
        AddItemToMainPool(GoldSkulltulaToken);
      }
    }
  } else if (Tokensanity.Is(TOKENSANITY_OVERWORLD)) {
    for (auto& loc : GetLocations(allLocations, Category::cSkulltula)) {
      if (loc->IsDungeon()) {
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
  if (GerudoTrainingGrounds.IsVanilla()) {
    AddItemToMainPool(IceTrap);
  }
  if (GanonsCastle.IsVanilla()) {
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

  SetVanillaShopItems(); //Set ShopItems vector to default, vanilla values
  //Shopsanity
  if (Settings::Shopsanity.Is(SHOPSANITY_OFF)) {
    PlaceShopItems();
    if (BombchusInLogic) {
      // PlaceItemInLocation(&KF_ShopItem8,    &BuyBombchu5);
      // PlaceItemInLocation(&MK_BazaarItem4,  &BuyBombchu5);
      // PlaceItemInLocation(&Kak_BazaarItem4, &BuyBombchu5);
    }
    AddItemsToPool(ItemPool, normalRupees);
  } else {
    Shuffle(ShopItems); //Shuffle shop items amongst themselves
    PlaceShopItems(); //Place now-shuffled shop items
    if (Settings::Shopsanity.Is(SHOPSANITY_ZERO)) { //Shopsanity 0
      AddItemsToPool(ItemPool, normalRupees);
    } 
    else { //Shopsanity 1-4, random
      //Overwrite appropriate number of shop items
      const std::array<int, 4> indices = {7, 5, 8, 6}; //Indices from OoTR
      for (size_t i = 0; i < ShopLocationLists.size(); i++) {
        int num_to_replace = GetShopsanityReplaceAmount(); //1-4 shop items will be overwritten, depending on settings
        for(int j = 0; j < num_to_replace; j++) {
          ShopLocationLists[i][indices[j]-1]->SetPlacedShopItem(NoItem, GetRandomShopPrice()); //Clear item and put a random price
        }
      }
      AddItemsToPool(ItemPool, shopsanityRupees); //Shopsanity gets extra large rupees
    }
  }

  //scrubsanity
  if (Settings::Scrubsanity.IsNot(SCRUBSANITY_OFF)) {
    //Deku Tree
    if (DekuTree.IsMQ()) {
      AddItemToMainPool(I_DekuShield);
    }

    //Dodongos Cavern
    AddItemToMainPool(DekuStick1);
    AddItemToMainPool(I_DekuShield);
    if (DodongosCavern.IsMQ()) {
      AddItemToMainPool(RecoveryHeart);
    } else {
      AddItemToMainPool(DekuNuts5);
    }

    //Jabu Jabus Belly
    if (JabuJabusBelly.IsVanilla()) {
      AddItemToMainPool(DekuNuts5);
    }

    //Ganons Castle
    AddItemToMainPool(Bombs5);
    AddItemToMainPool(RecoveryHeart);
    AddItemToMainPool(BlueRupee);
    if (GanonsCastle.IsMQ()) {
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
  AddItemsToPool(ItemPool, dungeonRewards);

  //dungeon pools
  if (DekuTree.IsMQ()) {
    AddItemsToPool(ItemPool, DT_MQ);
  } else {
    AddItemsToPool(ItemPool, DT_Vanilla);
  }
  if (DodongosCavern.IsMQ()) {
    AddItemsToPool(ItemPool, DC_MQ);
  } else {
    AddItemsToPool(ItemPool, DC_Vanilla);
  }
  if (JabuJabusBelly.IsMQ()) {
    AddItemsToPool(ItemPool, JB_MQ);
  }
  if (ForestTemple.IsMQ()) {
    AddItemsToPool(ItemPool, FoT_MQ);
  } else {
    AddItemsToPool(ItemPool, FoT_Vanilla);
  }
  if (FireTemple.IsMQ()) {
    AddItemsToPool(ItemPool, FiT_MQ);
  } else {
    AddItemsToPool(ItemPool, FiT_Vanilla);
  }
  if (SpiritTemple.IsMQ()) {
    AddItemsToPool(ItemPool, SpT_MQ);
  } else {
    AddItemsToPool(ItemPool, SpT_Vanilla);
  }
  if (ShadowTemple.IsMQ()) {
    AddItemsToPool(ItemPool, ShT_MQ);
  } else {
    AddItemsToPool(ItemPool, ShT_Vanilla);
  }
  if (BottomOfTheWell.IsVanilla()) {
    AddItemsToPool(ItemPool, BW_Vanilla);
  }
  if (GerudoTrainingGrounds.IsMQ()) {
    AddItemsToPool(ItemPool, GTG_MQ);
  } else {
    AddItemsToPool(ItemPool, GTG_Vanilla);
  }
  if (GanonsCastle.IsMQ()) {
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

  //add extra songs only if song shuffle is anywhere
  AddItemsToPool(ItemPool, songList);
  if (ShuffleSongs.Is(SONGSHUFFLE_ANYWHERE) && ItemPoolValue.Is(ITEMPOOL_PLENTIFUL)) {
    AddItemsToPool(PendingJunkPool, songList);
  }

  //TODO: free scarecrow

  /*For item pool generation, dungeon items are either placed in their vanilla
  | location, or added to the pool now and filtered out later depending on when
  | they need to get placed or removed in fill.cpp. These items are kept in the
  | pool until removal because the filling algorithm needs to know all of the
  | advancement items that haven't been placed yet for placing higher priority
  | items like stones/medallions.*/

  if (MapsAndCompasses.Is(MAPSANDCOMPASSES_VANILLA)) {
    PlaceVanillaMapsAndCompasses();
  } else  {
    for (auto dungeon : dungeonList) {
      if (dungeon->GetMap() != NoItem) {
        AddItemToMainPool(dungeon->GetMap());
      }

      if (dungeon->GetCompass() != NoItem) {
        AddItemToMainPool(dungeon->GetCompass());
      }
    }
  }

  if (Keysanity.Is(KEYSANITY_VANILLA)) {
    PlaceVanillaSmallKeys();
  } else {
    for (auto dungeon : dungeonList) {
      if (dungeon->GetSmallKeyCount() > 0) {
        AddItemToMainPool(dungeon->GetSmallKey(), dungeon->GetSmallKeyCount());
      }
    }
  }

  if (BossKeysanity.Is(BOSSKEYSANITY_VANILLA)) {
    PlaceVanillaBossKeys();
  } else {
    AddItemToMainPool(ForestTemple_BossKey);
    AddItemToMainPool(FireTemple_BossKey);
    AddItemToMainPool(WaterTemple_BossKey);
    AddItemToMainPool(SpiritTemple_BossKey);
    AddItemToMainPool(ShadowTemple_BossKey);
  }

  if (GanonsBossKey.Value<u8>() >= GANONSBOSSKEY_LACS_VANILLA) {
    PlaceItemInLocation(&ToT_LightArrowCutscene, GanonsCastle_BossKey);
  } else if (GanonsBossKey.Is(GANONSBOSSKEY_VANILLA)) {
    PlaceItemInLocation(&GanonsCastle_BossKeyChest, GanonsCastle_BossKey);
  } else {
    AddItemToMainPool(GanonsCastle_BossKey);
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
