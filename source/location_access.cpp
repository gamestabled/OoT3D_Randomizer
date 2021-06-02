#include "location_access.hpp"

#include "dungeon.hpp"
#include "item_list.hpp"
#include "item_location.hpp"
#include "item_pool.hpp"
#include "logic.hpp"
#include "settings.hpp"
#include "spoiler_log.hpp"
#include "trial.hpp"

#include <unistd.h>
#include <vector>

using namespace Logic;
using namespace Settings;

bool DAY_NIGHT_CYCLE    = true;
bool NO_DAY_NIGHT_CYCLE = false;

//generic grotto event list
std::vector<EventPairing> grottoEvents = {
  EventPairing(&GossipStoneFairy, []{return GossipStoneFairy || CanSummonGossipFairy;}),
  EventPairing(&ButterflyFairy,   []{return ButterflyFairy   || (CanUse(CanUseItem::Sticks));}),
  EventPairing(&BugShrub,         []{return CanCutShrubs;}),
  EventPairing(&LoneFish,         []{return true;}),
};

bool ItemLocationPairing::IsLocationUsed() const {
  return Location(location)->IsUsed();
}

bool ItemLocationPairing::CanBuy() const {
  //Not a shop location, don't need to check if buyable
  if (!(Location(location)->IsCategory(Category::cShop))) {
    return true;
  }

  //Check if wallet is large enough to buy item
  bool SufficientWallet = true;
  if (Location(location)->GetPrice() > 500) {
    SufficientWallet = Logic::ProgressiveWallet >= 3;
  } else if (Location(location)->GetPrice() > 200) {
    SufficientWallet = Logic::ProgressiveWallet >= 2;
  } else if (Location(location)->GetPrice() > 99) {
    SufficientWallet = Logic::ProgressiveWallet >= 1;
  }

  bool OtherCondition = true;
  u32 placed = Location(location)->GetPlacedItemKey();
  //Need bottle to buy bottle items, only logically relevant bottle items included here
  if (placed == BUY_BLUE_FIRE || placed == BUY_BOTTLE_BUG || placed == BUY_FISH || placed == BUY_FAIRYS_SPIRIT) {
    OtherCondition = Logic::HasBottle;
  }
  //Need explosives to be able to buy bombchus
  else if (placed == BUY_BOMBCHU_5 || placed == BUY_BOMBCHU_10 || placed == BUY_BOMBCHU_20) {
    OtherCondition = Logic::HasExplosives;
  }

  return SufficientWallet && OtherCondition;
}

Exit::Exit(std::string regionName_, std::string scene_, u32 hintKey_,
         bool timePass_,
         std::vector<EventPairing> events_,
         std::vector<ItemLocationPairing> locations_,
         std::vector<ExitPairing> exits_)
  : regionName(std::move(regionName_)),
    scene(std::move(scene_)),
    hintKey(hintKey_),
    timePass(timePass_),
    events(std::move(events_)),
    locations(std::move(locations_)),
    exits(std::move(exits_)) {}

Exit::~Exit() = default;

void Exit::UpdateEvents() {
  if (timePass) {
    if (Logic::Age == AGE_CHILD) {
      dayChild = true;
      nightChild = true;
    } else {
      dayAdult = true;
      nightAdult = true;
    }
  }

  for (EventPairing& eventPair : events) {
    if (eventPair.ConditionsMet()) {
      eventPair.EventOccurred();
    }
  }
}

bool Exit::CanPlantBean() const {
  return (Logic::MagicBean || Logic::MagicBeanPack) && BothAges();
}

bool Exit::AllAccountedFor() const {
  for (const EventPairing& event : events) {
    if (!event.ConditionsMet() || !event.GetEvent()) {
      return false;
    }
  }

  for (const ItemLocationPairing loc : locations) {
    if (!loc.ConditionsMet() || !(Location(loc.GetLocation())->IsAddedToPool())) {
      return false;
    }
  }

  for (const ExitPairing& exit : exits) {
    if (!exit.ConditionsMet() || !exit.GetExit()->AllAccess()) {
      return false;
    }
  }

  return AllAccess();
}

namespace Exits { //name, scene, hint text, events, locations, exits

  Exit NoExit = Exit("", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {});

  Exit Root = Exit("Root", "", LINKS_POCKET, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(LINKS_POCKET, []{return true;})
                }, {
                  //Exits      ToD
                  ExitPairing::Both(&RootExits, []{return true;})
  });

  Exit RootExits = Exit("Root Exits", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits      ToD
                  ExitPairing::Both(&KF_LinksHouse,    []{return IsChild;}),
                  ExitPairing::Both(&ToT_Main,         []{return (CanPlay(PreludeOfLight)   && CanLeaveForest) || IsAdult;}),
                  ExitPairing::Both(&SFM_Main,         []{return  CanPlay(MinuetOfForest);}),
                  ExitPairing::Both(&DMC_CentralLocal, []{return  CanPlay(BoleroOfFire)     && CanLeaveForest;}),
                  ExitPairing::Both(&LH_Main,          []{return  CanPlay(SerenadeOfWater)  && CanLeaveForest;}),
                  ExitPairing::Both(&GY_WarpPadRegion, []{return  CanPlay(NocturneOfShadow) && CanLeaveForest;}),
                  ExitPairing::Both(&Colossus_Main,    []{return  CanPlay(RequiemOfSpirit)  && CanLeaveForest;})
  });

  Exit KF_Main = Exit("Kokiri Forest", "Kokiri Forest", KOKIRI_FOREST, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&BeanPlantFairy,           []{return BeanPlantFairy   || (KF_Main.CanPlantBean() && CanPlay(SongOfStorms));}),
                  EventPairing(&GossipStoneFairy,         []{return GossipStoneFairy || CanSummonGossipFairyWithoutSuns;}),
                  EventPairing(&ShowedMidoSwordAndShield, []{return OpenForest.Is(OPENFOREST_OPEN) || (IsChild && KokiriSword && DekuShield);}),
                }, {
                  //Locations
                  ItemLocationPairing(KF_KOKIRI_SWORD_CHEST,   []{return IsChild;}),
                  ItemLocationPairing(KF_GS_KNOW_IT_ALL_HOUSE, []{return IsChild && CanChildAttack && AtNight && (HasNightStart || CanLeaveForest || CanPlay(SunsSong)) && CanGetNightTimeGS;}),
                  ItemLocationPairing(KF_GS_BEAN_PATCH,        []{return CanPlantBugs && CanChildAttack;}),
                  ItemLocationPairing(KF_GS_HOUSE_OF_TWINS,    []{return IsAdult && AtNight && CanUse(CanUseItem::Hookshot) && CanGetNightTimeGS;}),
                  ItemLocationPairing(KF_GOSSIP_STONE,         []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&KF_LinksHouse,       []{return true;}),
                  ExitPairing::Both(&KF_MidosHouse,       []{return true;}),
                  ExitPairing::Both(&KF_SariasHouse,      []{return true;}),
                  ExitPairing::Both(&KF_HouseOfTwins,     []{return true;}),
                  ExitPairing::Both(&KF_KnowItAllHouse,   []{return true;}),
                  ExitPairing::Both(&KF_KokiriShop,       []{return true;}),
                  ExitPairing::Both(&KF_OutsideDekuTree,  []{return IsAdult || ShowedMidoSwordAndShield;}),
                  ExitPairing::Both(&LW_Main,             []{return true;}),
                  ExitPairing::Both(&LW_BridgeFromForest, []{return CanLeaveForest;}),
                  ExitPairing::Both(&KF_StormsGrotto,     []{return CanOpenStormGrotto;})
  });

  Exit KF_OutsideDekuTree = Exit("KF Outside Deku Tree", "Kokiri Forest", KOKIRI_FOREST, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&DekuBabaSticks, []{return DekuBabaSticks || ((IsAdult && !ShuffleDungeonEntrances) || KokiriSword || Boomerang);}),
                  EventPairing(&DekuBabaNuts,   []{return DekuBabaNuts   || ((IsAdult && !ShuffleDungeonEntrances) || KokiriSword || Slingshot || Sticks || HasExplosives || CanUse(CanUseItem::Dins_Fire));}),
                }, {
                  //Locations
                  ItemLocationPairing(KF_DEKU_TREE_GOSSIP_STONE_LEFT,  []{return true;}),
                  ItemLocationPairing(KF_DEKU_TREE_GOSSIP_STONE_RIGHT, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&DekuTree_Lobby,    []{return Dungeon::DekuTree.IsVanilla() && (IsChild || (ShuffleDungeonEntrances && ShowedMidoSwordAndShield));}),
                  ExitPairing::Both(&DekuTree_MQ_Lobby, []{return Dungeon::DekuTree.IsMQ()      && (IsChild || (ShuffleDungeonEntrances && ShowedMidoSwordAndShield));}),
                  ExitPairing::Both(&KF_Main,           []{return true;}),
  });

  Exit KF_LinksHouse = Exit("KF Link's House", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(KF_LINKS_HOUSE_COW, []{return IsAdult && CanPlay(EponasSong) && LinksCow;}),
                }, {
                  //Exits
                  ExitPairing::Both(&KF_Main, []{return true;})
  });

  Exit KF_MidosHouse = Exit("KF Mido's House", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(KF_MIDOS_TOP_LEFT_CHEST,     []{return true;}),
                  ItemLocationPairing(KF_MIDOS_TOP_RIGHT_CHEST,    []{return true;}),
                  ItemLocationPairing(KF_MIDOS_BOTTOM_LEFT_CHEST,  []{return true;}),
                  ItemLocationPairing(KF_MIDOS_BOTTOM_RIGHT_CHEST, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&KF_Main, []{return true;}),
  });

  Exit KF_SariasHouse = Exit("KF Saria's House", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&KF_Main, []{return true;}),
  });

  Exit KF_HouseOfTwins = Exit("KF House of Twins", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&KF_Main, []{return true;}),
  });

  Exit KF_KnowItAllHouse = Exit("KF Know It All House", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&KF_Main, []{return true;}),
  });

  Exit KF_KokiriShop = Exit("KF Kokiri Shop", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(KF_SHOP_ITEM_1, []{return true;}),
                  ItemLocationPairing(KF_SHOP_ITEM_2, []{return true;}),
                  ItemLocationPairing(KF_SHOP_ITEM_3, []{return true;}),
                  ItemLocationPairing(KF_SHOP_ITEM_4, []{return true;}),
                  ItemLocationPairing(KF_SHOP_ITEM_5, []{return true;}),
                  ItemLocationPairing(KF_SHOP_ITEM_6, []{return true;}),
                  ItemLocationPairing(KF_SHOP_ITEM_7, []{return true;}),
                  ItemLocationPairing(KF_SHOP_ITEM_8, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&KF_Main, []{return true;}),
  });

  Exit KF_StormsGrotto = Exit("KF Storms Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  ItemLocationPairing(KF_STORMS_GROTTO_CHEST,        []{return true;}),
                  ItemLocationPairing(KF_STORMS_GROTTO_GOSSIP_STONE, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&KF_Main, []{return true;})
  });

  Exit LW_ForestExit = Exit("LW Forest Exit", "Lost Woods", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&KF_Main, []{return true;})
  });

  Exit LW_Main = Exit("Lost Woods", "Lost Woods", THE_LOST_WOODS, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&OddMushroomAccess, []{return OddMushroomAccess || (IsAdult && (CojiroAccess || Cojiro));}),
                  EventPairing(&PoachersSawAccess, []{return PoachersSawAccess || (IsAdult && OddPoulticeAccess);}),
                  EventPairing(&GossipStoneFairy,  []{return GossipStoneFairy  || CanSummonGossipFairyWithoutSuns;}),
                  EventPairing(&BeanPlantFairy,    []{return BeanPlantFairy    || CanPlay(SongOfStorms);}),
                  EventPairing(&BugShrub,          []{return IsChild && CanCutShrubs;}),
                }, {
                  //Locations
                  ItemLocationPairing(LW_SKULL_KID,                 []{return IsChild && CanPlay(SariasSong);}),
                  ItemLocationPairing(LW_OCARINA_MEMORY_GAME,       []{return IsChild && Ocarina;}),
                  ItemLocationPairing(LW_TARGET_IN_WOODS,           []{return CanUse(CanUseItem::Slingshot);}),
                  ItemLocationPairing(LW_DEKU_SCRUB_NEAR_BRIDGE,    []{return IsChild && CanStunDeku;}),
                  ItemLocationPairing(LW_GS_BEAN_PATCH_NEAR_BRIDGE, []{return CanPlantBugs && CanChildAttack;}),
                  ItemLocationPairing(LW_GOSSIP_STONE,              []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&LW_ForestExit,          []{return true;}),
                  ExitPairing::Both(&GC_WoodsWarp,           []{return true;}),
                  ExitPairing::Both(&LW_Bridge,              []{return IsAdult && (CanUse(CanUseItem::Hover_Boots) || CanUse(CanUseItem::Longshot) || LW_Main.CanPlantBean());}),
                  ExitPairing::Both(&ZR_Main,                []{return CanLeaveForest && (CanDive || CanUse(CanUseItem::Iron_Boots));}),
                  ExitPairing::Both(&LW_BeyondMido,          []{return IsChild || CanPlay(SariasSong);}),
                  ExitPairing::Both(&LW_NearShortcutsGrotto, []{return LW_Main.Here([]{return CanBlastOrSmash;});})
  });

  Exit LW_BeyondMido = Exit("LW Beyond Mido", "Lost Woods", THE_LOST_WOODS, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&ButterflyFairy, []{return ButterflyFairy || CanUse(CanUseItem::Sticks);}),
                }, {
                  //Locations
                  ItemLocationPairing(LW_DEKU_SCRUB_NEAR_DEKU_THEATER_RIGHT, []{return IsChild && CanStunDeku;}),
                  ItemLocationPairing(LW_DEKU_SCRUB_NEAR_DEKU_THEATER_LEFT,  []{return IsChild && CanStunDeku;}),
                  ItemLocationPairing(LW_GS_ABOVE_THEATER,                   []{return IsAdult && AtNight && (LW_BeyondMido.CanPlantBean() || (LogicLostWoodsGSBean && CanUse(CanUseItem::Hookshot) && (CanUse(CanUseItem::Longshot) || CanUse(CanUseItem::Bow) || HasBombchus || CanUse(CanUseItem::Dins_Fire)))) && CanGetNightTimeGS;}),
                  ItemLocationPairing(LW_GS_BEAN_PATCH_NEAR_THEATER,         []{return CanPlantBugs && (CanChildAttack || (Scrubsanity.Is(SCRUBSANITY_OFF) && DekuShield));}),
                }, {
                  //Exits
                  ExitPairing::Both(&LW_ForestExit,   []{return true;}),
                  ExitPairing::Both(&LW_Main,         []{return IsChild || CanPlay(SariasSong);}),
                  ExitPairing::Both(&SFM_Entryway,    []{return true;}),
                  ExitPairing::Both(&LW_DekuTheater,  []{return true;}),
                  ExitPairing::Both(&LW_ScrubsGrotto, []{return LW_BeyondMido.Here([]{return CanBlastOrSmash;});})
  });

  Exit LW_NearShortcutsGrotto = Exit("LW Near Shortcuts Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  ItemLocationPairing(LW_NEAR_SHORTCUTS_GROTTO_CHEST,        []{return true;}),
                  ItemLocationPairing(LW_NEAR_SHORTCUTS_GROTTO_GOSSIP_STONE, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&LW_Main, []{return true;})
  });

  Exit LW_DekuTheater = Exit("Deku Theater", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(DEKU_THEATER_SKULL_MASK,    []{return IsChild && SkullMask;}),
                  ItemLocationPairing(DEKU_THEATER_MASK_OF_TRUTH, []{return IsChild && MaskOfTruth;}),
                }, {
                  //Exits
                  ExitPairing::Both(&LW_BeyondMido, []{return true;}),
  });

  Exit LW_ScrubsGrotto = Exit("LW Scrubs Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(LW_DEKU_SCRUB_GROTTO_REAR,  []{return CanStunDeku;}),
                  ItemLocationPairing(LW_DEKU_SCRUB_GROTTO_FRONT, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing::Both(&LW_BeyondMido, []{return true;}),
  });

  Exit SFM_Entryway = Exit("SFM Entryway", "Sacred Forest Meadow", SACRED_FOREST_MEADOW, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&LW_BeyondMido,    []{return true;}),
                  ExitPairing::Both(&SFM_Main,         []{return IsAdult || Slingshot || Sticks || KokiriSword || CanUse(CanUseItem::Dins_Fire);}),
                  ExitPairing::Both(&SFM_WolfosGrotto, []{return CanOpenBombGrotto;}),
  });

  Exit SFM_Main = Exit("Sacred Forest Meadow", "Sacred Forest Meadow", SACRED_FOREST_MEADOW, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GossipStoneFairy, []{return GossipStoneFairy || CanSummonGossipFairyWithoutSuns;})
                }, {
                  //Locations
                  ItemLocationPairing(SONG_FROM_SARIA,             []{return IsChild && ZeldasLetter;}),
                  ItemLocationPairing(SHEIK_IN_FOREST,             []{return IsAdult;}),
                  ItemLocationPairing(SFM_GS,                      []{return CanUse(CanUseItem::Hookshot) && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(SFM_MAZE_GOSSIP_STONE_LOWER, []{return true;}),
                  ItemLocationPairing(SFM_MAZE_GOSSIP_STONE_UPPER, []{return true;}),
                  ItemLocationPairing(SFM_SARIA_GOSSIP_STONE,      []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&SFM_Entryway,          []{return true;}),
                  ExitPairing::Both(&ForestTemple_Lobby,    []{return Dungeon::ForestTemple.IsVanilla() && CanUse(CanUseItem::Hookshot);}),
                  ExitPairing::Both(&ForestTemple_MQ_Lobby, []{return Dungeon::ForestTemple.IsMQ()      && CanUse(CanUseItem::Hookshot);}),
                  ExitPairing::Both(&SFM_FairyGrotto,       []{return true;}),
                  ExitPairing::Both(&SFM_StormsGrotto,      []{return CanOpenStormGrotto;}),
  });

  Exit SFM_FairyGrotto = Exit("SFM Fairy Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FreeFairies, []{return true;})
                }, {}, {
                  //Exits
                  ExitPairing::Both(&SFM_Main, []{return true;}),
  });

  Exit SFM_WolfosGrotto = Exit("SFM Wolfos Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(SFM_WOLFOS_GROTTO_CHEST, []{return IsAdult || Slingshot || Sticks || KokiriSword || CanUse(CanUseItem::Dins_Fire);})
                }, {
                  //Exits
                  ExitPairing::Both(&SFM_Main, []{return true;}),
  });

  Exit SFM_StormsGrotto = Exit("SFM Storms Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(SFM_DEKU_SCRUB_GROTTO_REAR,  []{return CanStunDeku;}),
                  ItemLocationPairing(SFM_DEKU_SCRUB_GROTTO_FRONT, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing::Both(&SFM_Main, []{return true;})
  });

  Exit LW_BridgeFromForest = Exit("LW Bridge From Forest", "Lost Woods", THE_LOST_WOODS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(LW_GIFT_FROM_SARIA, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&LW_Bridge, []{return true;})
  });

  Exit LW_Bridge = Exit("LW Bridge", "Lost Woods", THE_LOST_WOODS, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&KF_Main, []{return true;}),
                  ExitPairing::Both(&HF_Main, []{return true;}),
                  ExitPairing::Both(&LW_Main, []{return CanUse(CanUseItem::Longshot);})
  });

  Exit HF_Main = Exit("Hyrule Field", "Hyrule Field", HYRULE_FIELD, DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&BigPoeKill, []{return CanUse(CanUseItem::Bow) && CanRideEpona && HasBottle;}),
                }, {
                  //Locations
                  ItemLocationPairing(HF_OCARINA_OF_TIME_ITEM,   []{return IsChild && HasAllStones;}),
                  ItemLocationPairing(SONG_FROM_OCARINA_OF_TIME, []{return IsChild && HasAllStones;}),
                }, {
                  //Exits
                  ExitPairing::Both(&LW_Bridge,            []{return true;}),
                  ExitPairing::Both(&LH_Main,              []{return true;}),
                  ExitPairing::Both(&GV_Main,              []{return true;}),
                  ExitPairing::Both(&MK_Entrance,          []{return true;}),
                  ExitPairing::Both(&Kak_Main,             []{return true;}),
                  ExitPairing::Both(&ZR_Front,             []{return true;}),
                  ExitPairing::Both(&LLR_Main,             []{return true;}),
                  ExitPairing::Both(&HF_SoutheastGrotto,   []{return HF_Main.Here([]{return CanBlastOrSmash;});}),
                  ExitPairing::Both(&HF_OpenGrotto,        []{return true;}),
                  ExitPairing::Both(&HF_InsideFenceGrotto, []{return CanOpenBombGrotto;}),
                  ExitPairing::Both(&HF_CowGrotto,         []{return (CanUse(CanUseItem::Hammer) || IsChild) && CanOpenBombGrotto;}),
                  ExitPairing::Both(&HF_NearMarketGrotto,  []{return HF_Main.Here([]{return CanBlastOrSmash;});}),
                  ExitPairing::Both(&HF_FairyGrotto,       []{return HF_Main.Here([]{return CanBlastOrSmash;});}),
                  ExitPairing::Both(&HF_NearKakGrotto,     []{return CanOpenBombGrotto;}),
                  ExitPairing::Both(&HF_TektiteGrotto,     []{return CanOpenBombGrotto;})
  });

  Exit HF_SoutheastGrotto = Exit("HF Southeast Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  ItemLocationPairing(HF_SOUTHEAST_GROTTO_CHEST,        []{return true;}),
                  ItemLocationPairing(HF_SOUTHEAST_GROTTO_GOSSIP_STONE, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&HF_Main, []{return true;})
  });

  Exit HF_OpenGrotto = Exit("HF Open Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  ItemLocationPairing(HF_OPEN_GROTTO_CHEST,        []{return true;}),
                  ItemLocationPairing(HF_OPEN_GROTTO_GOSSIP_STONE, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&HF_Main, []{return true;})
  });

  Exit HF_InsideFenceGrotto = Exit("HF Inside Fence Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(HF_DEKU_SCRUB_GROTTO, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing::Both(&HF_Main, []{return true;})
  });

  Exit HF_CowGrotto = Exit("HF Cow Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  ItemLocationPairing(HF_GS_COW_GROTTO,           []{return HasFireSource && HookshotOrBoomerang;}),
                  ItemLocationPairing(HF_COW_GROTTO_COW,          []{return HasFireSource && CanPlay(EponasSong);}),
                  ItemLocationPairing(HF_COW_GROTTO_GOSSIP_STONE, []{return HasFireSource;}),
                }, {
                  //Exits
                  ExitPairing::Both(&HF_Main, []{return true;})
  });

  Exit HF_NearMarketGrotto = Exit("HF Near Market Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  ItemLocationPairing(HF_NEAR_MARKET_GROTTO_CHEST,        []{return true;}),
                  ItemLocationPairing(HF_NEAR_MARKET_GROTTO_GOSSIP_STONE, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&HF_Main, []{return true;})
  });

  Exit HF_FairyGrotto = Exit("HF Fairy Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FreeFairies, []{return true;})
                }, {}, {
                  //Exits
                  ExitPairing::Both(&HF_Main, []{return true;})
  });

  Exit HF_NearKakGrotto = Exit("HF Near Kak Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(HF_GS_NEAR_KAK_GROTTO, []{return HookshotOrBoomerang;}),
                }, {
                  //Exits
                  ExitPairing::Both(&HF_Main, []{return true;})
  });

  Exit HF_TektiteGrotto = Exit("HF Tektite Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(HF_TEKTITE_GROTTO_FREESTANDING_POH, []{return ProgressiveScale >= 2 || CanUse(CanUseItem::Iron_Boots);}),
                }, {
                  //Exits
                  ExitPairing::Both(&HF_Main, []{return true;}),
  });

  Exit LH_Main = Exit("Lake Hylia", "Lake Hylia", LAKE_HYLIA, DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GossipStoneFairy, []{return GossipStoneFairy || CanSummonGossipFairy;}),
                  EventPairing(&BeanPlantFairy,   []{return BeanPlantFairy   || (LH_Main.CanPlantBean() && CanPlay(SongOfStorms));}),
                  EventPairing(&ButterflyFairy,   []{return ButterflyFairy   || CanUse(CanUseItem::Sticks);}),
                  EventPairing(&BugShrub,         []{return BugShrub         || (IsChild && CanCutShrubs);}),
                  EventPairing(&ScarecrowSong,    []{return ScarecrowSong    || (Ocarina && LH_Main.BothAges());}),
                }, {
                  //Locations
                  ItemLocationPairing(LH_UNDERWATER_ITEM,        []{return IsChild && CanDive;}),
                  ItemLocationPairing(LH_SUN,                    []{return IsAdult && WaterTempleClear && CanUse(CanUseItem::Bow);}),
                  ItemLocationPairing(LH_FREESTANDING_POH,       []{return IsAdult && (CanUse(CanUseItem::Scarecrow) || LH_Main.CanPlantBean());}),
                  ItemLocationPairing(LH_GS_BEAN_PATCH,          []{return CanPlantBugs && CanChildAttack;}),
                  ItemLocationPairing(LH_GS_LAB_WALL,            []{return IsChild && (Boomerang || (LogicLabWallGS && (Sticks || KokiriSword))) && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(LH_GS_SMALL_ISLAND,        []{return IsChild && CanChildAttack && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(LH_GS_TREE,                []{return CanUse(CanUseItem::Longshot) && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(LH_LAB_GOSSIP_STONE,       []{return true;}),
                  ItemLocationPairing(LH_GOSSIP_STONE_SOUTHEAST, []{return true;}),
                  ItemLocationPairing(LH_GOSSIP_STONE_SOUTHWEST, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&HF_Main,              []{return true;}),
                  ExitPairing::Both(&ZD_Main,              []{return IsChild && CanDive;}),
                  ExitPairing::Both(&LH_OwlFlight,         []{return IsChild;}),
                  ExitPairing::Both(&LH_Lab,               []{return true;}),
                  ExitPairing::Both(&LH_FishingHole,       []{return IsChild || CanUse(CanUseItem::Scarecrow) || LH_Main.CanPlantBean() || WaterTempleClear;}),
                  ExitPairing::Both(&WaterTemple_Lobby,    []{return Dungeon::WaterTemple.IsVanilla() && CanUse(CanUseItem::Hookshot) && (CanUse(CanUseItem::Iron_Boots) || ((CanUse(CanUseItem::Longshot)) && ProgressiveScale >= 2));}),
                  ExitPairing::Both(&WaterTemple_MQ_Lobby, []{return Dungeon::WaterTemple.IsMQ()      && CanUse(CanUseItem::Hookshot) && (CanUse(CanUseItem::Iron_Boots) || ((CanUse(CanUseItem::Longshot)) && ProgressiveScale >= 2));}),
                  ExitPairing::Both(&LH_Grotto,            []{return true;})
  });

  Exit LH_OwlFlight = Exit("LH Owl Flight", "Lake Hylia", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&HF_Main, []{return true;})
  });

  Exit LH_Lab = Exit("LH Lab", "", NONE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&EyedropsAccess, []{return EyedropsAccess || (IsAdult && (EyeballFrogAccess || (EyeballFrog && DisableTradeRevert)));}),
                }, {
                  //Locations
                  ItemLocationPairing(LH_LAB_DIVE,     []{return ProgressiveScale >= 2 || (LogicLabDiving && IronBoots && CanUse(CanUseItem::Hookshot));}),
                  ItemLocationPairing(LH_GS_LAB_CRATE, []{return IronBoots && CanUse(CanUseItem::Hookshot);}),
                }, {
                  //Exits
                  ExitPairing::Both(&LH_Main, []{return true;})
  });

  Exit LH_FishingHole = Exit("LH Fishing Hole", "", NONE, DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(LH_CHILD_FISHING, []{return IsChild;}),
                  ItemLocationPairing(LH_ADULT_FISHING, []{return IsAdult;})
                }, {
                  //Exits
                  ExitPairing::Both(&LH_Main, []{return true;})
  });

  Exit LH_Grotto = Exit("LH Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(LH_DEKU_SCRUB_GROTTO_LEFT,   []{return CanStunDeku;}),
                  ItemLocationPairing(LH_DEKU_SCRUB_GROTTO_RIGHT,  []{return CanStunDeku;}),
                  ItemLocationPairing(LH_DEKU_SCRUB_GROTTO_CENTER, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing::Both(&LH_Main, []{return true;})
  });

  Exit GV_Main = Exit("Gerudo Valley", "Gerudo Valley", GERUDO_VALLEY, DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&BugRock, []{return IsChild && HasBottle;}),
                }, {
                  //Locations
                  ItemLocationPairing(GV_GS_SMALL_BRIDGE, []{return CanUse(CanUseItem::Boomerang) && AtNight && CanGetNightTimeGS;}),
                }, {
                  //Exits
                  ExitPairing::Both(&HF_Main,          []{return true;}),
                  ExitPairing::Both(&GV_Stream,        []{return true;}),
                  ExitPairing::Both(&GV_CrateLedge,    []{return IsChild || CanUse(CanUseItem::Longshot);}),
                  ExitPairing::Both(&GV_OctorokGrotto, []{return CanUse(CanUseItem::Silver_Gauntlets);}),
                  ExitPairing::Both(&GV_FortressSide,  []{return IsAdult && (CanRideEpona || CanUse(CanUseItem::Longshot) || GerudoFortress.Is(GERUDOFORTRESS_OPEN) || CarpenterRescue);})
  });

  Exit GV_Stream = Exit("GV Stream", "Gerudo Valley", GERUDO_VALLEY, DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GossipStoneFairy, []{return GossipStoneFairy || CanSummonGossipFairy;}),
                  EventPairing(&BeanPlantFairy,   []{return BeanPlantFairy   || (GV_Stream.CanPlantBean() && CanPlay(SongOfStorms));}),
                }, {
                  //Locations
                  ItemLocationPairing(GV_WATERFALL_FREESTANDING_POH, []{return true;}),
                  ItemLocationPairing(GV_GS_BEAN_PATCH,              []{return CanPlantBugs && CanChildAttack;}),
                  ItemLocationPairing(GV_COW,                        []{return IsChild && CanPlay(EponasSong);}),
                  ItemLocationPairing(GV_GOSSIP_STONE,               []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&LH_Main, []{return true;})
  });

  Exit GV_CrateLedge = Exit("GV Crate Ledge", "Gerudo Valley", GERUDO_VALLEY, DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(GV_CRATE_FREESTANDING_POH, []{return true;}),
                }, {
                  //Exits
  });

  Exit GV_FortressSide = Exit("GV Fortress Side", "Gerudo Valley", GERUDO_VALLEY, DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&BrokenSwordAccess, []{return IsAdult && (PoachersSawAccess || PoachersSaw);}),
                }, {
                  //Locations
                  ItemLocationPairing(GV_CHEST,          []{return CanUse(CanUseItem::Hammer);}),
                  ItemLocationPairing(GV_GS_BEHIND_TENT, []{return CanUse(CanUseItem::Hookshot) && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(GV_GS_PILLAR,      []{return CanUse(CanUseItem::Hookshot) && AtNight && CanGetNightTimeGS;}),
                }, {
                  //Exits
                  ExitPairing::Both(&GF_Main,          []{return true;}),
                  ExitPairing::Both(&GV_Stream,        []{return true;}),
                  ExitPairing::Both(&GV_Main,          []{return IsChild || CanRideEpona || CanUse(CanUseItem::Longshot) || GerudoFortress.Is(GERUDOFORTRESS_OPEN) || CarpenterRescue;}),
                  ExitPairing::Both(&GV_CarpenterTent, []{return IsAdult;}),
                  ExitPairing::Both(&GV_StormsGrotto,  []{return IsAdult && CanOpenStormGrotto;})
  });

  Exit GV_CarpenterTent = Exit("GV Carpenter Tent", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&GV_Main, []{return true;})
  });

  Exit GV_OctorokGrotto = Exit("GV Octorok Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&GV_Main, []{return true;})
  });

  Exit GV_StormsGrotto = Exit("GV Storms Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(GV_DEKU_SCRUB_GROTTO_REAR,  []{return CanStunDeku;}),
                  ItemLocationPairing(GV_DEKU_SCRUB_GROTTO_FRONT, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing::Both(&GV_FortressSide, []{return true;})
  });

  Exit GF_Main = Exit("Gerudo Fortress", "Gerudo Fortress", GERUDO_FORTRESS, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&CarpenterRescue, []{return CanFinishGerudoFortress;}),
                  EventPairing(&GF_GateOpen,     []{return IsAdult && GerudoToken;}),
                }, {
                  //Locations
                  ItemLocationPairing(GF_CHEST,              []{return CanUse(CanUseItem::Hover_Boots) || CanUse(CanUseItem::Scarecrow) || CanUse(CanUseItem::Longshot);}),
                  ItemLocationPairing(GF_HBA_1000_POINTS,    []{return GerudoToken && CanRideEpona && Bow && AtDay;}),
                  ItemLocationPairing(GF_HBA_1500_POINTS,    []{return GerudoToken && CanRideEpona && Bow && AtDay;}),
                  ItemLocationPairing(GF_NORTH_F1_CARPENTER, []{return  IsAdult || KokiriSword;}),
                  ItemLocationPairing(GF_NORTH_F2_CARPENTER, []{return (IsAdult || KokiriSword) && (GerudoToken || CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Hookshot) || CanUse(CanUseItem::Hover_Boots) || LogicGerudoKitchen);}),
                  ItemLocationPairing(GF_SOUTH_F1_CARPENTER, []{return  IsAdult || KokiriSword;}),
                  ItemLocationPairing(GF_SOUTH_F2_CARPENTER, []{return  IsAdult || KokiriSword;}),
                  ItemLocationPairing(GF_GERUDO_TOKEN,       []{return CanFinishGerudoFortress;}),
                  ItemLocationPairing(GF_GS_ARCHERY_RANGE,   []{return CanUse(CanUseItem::Hookshot) && GerudoToken && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(GF_GS_TOP_FLOOR,       []{return IsAdult && AtNight && (GerudoToken || CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Hookshot) || CanUse(CanUseItem::Hover_Boots) || LogicGerudoKitchen) && CanGetNightTimeGS;})
                }, {
                  //Exits
                  ExitPairing::Both(&GV_FortressSide,                []{return true;}),
                  ExitPairing::Both(&GF_OutsideGate,                 []{return GF_GateOpen;}),
                  ExitPairing::Both(&GerudoTrainingGrounds_Lobby,    []{return Dungeon::GerudoTrainingGrounds.IsVanilla() && IsAdult && GerudoToken;}),
                  ExitPairing::Both(&GerudoTrainingGrounds_MQ_Lobby, []{return Dungeon::GerudoTrainingGrounds.IsMQ()      && IsAdult && GerudoToken;}),
                  ExitPairing::Both(&GF_StormsGrotto,                []{return IsAdult && CanOpenStormGrotto;})
  });

  Exit GF_OutsideGate = Exit("GF Outside Gate", "Gerudo Fortress", NONE, NO_DAY_NIGHT_CYCLE, {
                  //Events                                                      //no guard on the other side of the gate yet
                  //EventPairing(&GF_GateOpen, []{return IsAdult && GerudoToken && (ShuffleGerudoToken || ShuffleOverworldEntrances || ShuffleSpecialIndoorEntrances);}),
                }, {}, {
                  //Exits
                  ExitPairing::Both(&GF_Main,         []{return IsAdult || (ShuffleOverworldEntrances && GF_GateOpen);}),
                  ExitPairing::Both(&HW_NearFortress, []{return true;})
  });

  Exit GF_StormsGrotto = Exit("GF Storms Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FreeFairies, []{return true;}),
                }, {}, {
                  //Exits
                  ExitPairing::Both(&GF_Main, []{return true;})
  });

  Exit HW_NearFortress = Exit("Wasteland Near Fortress", "Haunted Wasteland", HAUNTED_WASTELAND, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&GF_OutsideGate, []{return true;}),
                  ExitPairing::Both(&HW_Main,        []{return CanUse(CanUseItem::Hover_Boots) || CanUse(CanUseItem::Longshot);}),
  });

  Exit HW_Main = Exit("Haunted Wasteland", "Haunted Wasteland", HAUNTED_WASTELAND, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPot, []{return true;}),
                  EventPairing(&NutPot,   []{return true;}),
                }, {
                  //Locations
                  ItemLocationPairing(WASTELAND_CHEST, []{return HasFireSource;}),
                  //TODO: Wasteland Bombchu Salesman
                  ItemLocationPairing(WASTELAND_GS,    []{return HookshotOrBoomerang;}),
                }, {
                  //Exits
                  ExitPairing::Both(&HW_NearColossus, []{return LogicLensWasteland || CanUse(CanUseItem::Lens_of_Truth);}),
                  ExitPairing::Both(&HW_NearFortress, []{return CanUse(CanUseItem::Hover_Boots) || CanUse(CanUseItem::Longshot);}),
  });

  Exit HW_NearColossus = Exit("Wasteland Near Colossus", "Haunted Wasteland", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&Colossus_Main, []{return true;}),
                  ExitPairing::Both(&HW_Main,       []{return LogicReverseWasteland || false;})
  });

  Exit Colossus_Main = Exit("Desert Colossus", "Desert Colossus", DESERT_COLOSSUS, DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPond, []{return FairyPond || CanPlay(SongOfStorms);}),
                  EventPairing(&BugRock,   []{return true;}),
                }, {
                  //Locations
                  ItemLocationPairing(COLOSSUS_FREESTANDING_POH, []{return IsAdult && Colossus_Main.CanPlantBean();}),
                  ItemLocationPairing(SHEIK_AT_COLOSSUS,         []{return true;}),
                  ItemLocationPairing(COLOSSUS_GS_BEAN_PATCH,    []{return CanPlantBugs && CanChildAttack;}),
                  ItemLocationPairing(COLOSSUS_GS_TREE,          []{return CanUse(CanUseItem::Hookshot) && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(COLOSSUS_GS_HILL,          []{return IsAdult && AtNight && (Colossus_Main.CanPlantBean() || CanUse(CanUseItem::Longshot) || (LogicColossusGS && CanUse(CanUseItem::Hookshot))) && CanGetNightTimeGS;}),
                  ItemLocationPairing(COLOSSUS_GOSSIP_STONE,     []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&Colossus_GreatFairyFountain, []{return HasExplosives;}),
                  ExitPairing::Both(&SpiritTemple_Lobby,          []{return Dungeon::SpiritTemple.IsVanilla();}),
                  ExitPairing::Both(&SpiritTemple_MQ_Lobby,       []{return Dungeon::SpiritTemple.IsMQ();}),
                  ExitPairing::Both(&HW_NearColossus,             []{return true;}),
                  ExitPairing::Both(&Colossus_Grotto,             []{return CanUse(CanUseItem::Silver_Gauntlets);})
  });

  Exit Colossus_GreatFairyFountain = Exit("Colossus Great Fairy Fountain", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(COLOSSUS_GREAT_FAIRY_REWARD, []{return CanPlay(ZeldasLullaby);}),
                }, {
                  //Exits
                  ExitPairing::Both(&Colossus_Main, []{return true;})
  });

  Exit Colossus_Grotto = Exit("Colossus Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(COLOSSUS_DEKU_SCRUB_GROTTO_REAR,  []{return CanStunDeku;}),
                  ItemLocationPairing(COLOSSUS_DEKU_SCRUB_GROTTO_FRONT, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing::Both(&Colossus_Main, []{return true;})
  });

  Exit MK_Entrance = Exit("Market Entrance", "Market Entrance", THE_MARKET, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Day(&HF_Main, []{return IsAdult || AtDay;}),
                  ExitPairing::Both(&MK_Main, []{return true;}),
                  ExitPairing::Both(&MK_GuardHouse, []{return true;})
  });

  Exit MK_Main = Exit("Market", "Market", THE_MARKET, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&MK_Entrance,           []{return true;}),
                  ExitPairing::Both(&ToT_Entrance,          []{return true;}),
                  ExitPairing::Both(&CastleGrounds,         []{return true;}),
                  ExitPairing::Day(&MK_Bazaar,              []{return IsChild && AtDay;}),
                  ExitPairing::Day(&MK_MaskShop,            []{return IsChild && AtDay;}),
                  ExitPairing::Day(&MK_ShootingGallery,     []{return IsChild && AtDay;}),
                  ExitPairing::Both(&MK_BombchuBowling,     []{return IsChild;}),
                  ExitPairing::Night(&MK_TreasureChestGame, []{return IsChild && AtNight;}),
                  ExitPairing::Day(&MK_PotionShop,          []{return IsChild && AtDay;}),
                  ExitPairing::Night(&MK_BombchuShop,       []{return IsChild && AtNight;}),
                  ExitPairing::Both(&MK_DogLadyHouse,       []{return IsChild;}),
                  ExitPairing::Night(&MK_ManInGreenHouse,   []{return IsChild && AtNight;})
  });

  Exit ToT_Entrance = Exit("ToT Entrance", "ToT Entrance", THE_MARKET, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GossipStoneFairy, []{return GossipStoneFairy || CanSummonGossipFairyWithoutSuns;}),
                }, {
                  //Locations
                  ItemLocationPairing(TOT_GOSSIP_STONE_LEFT,         []{return true;}),
                  ItemLocationPairing(TOT_GOSSIP_STONE_LEFT_CENTER,  []{return true;}),
                  ItemLocationPairing(TOT_GOSSIP_STONE_RIGHT_CENTER, []{return true;}),
                  ItemLocationPairing(TOT_GOSSIP_STONE_RIGHT,        []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&MK_Main,  []{return true;}),
                  ExitPairing::Both(&ToT_Main, []{return true;})
  });

  Exit ToT_Main = Exit("Temple of Time", "", TEMPLE_OF_TIME, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(TOT_LIGHT_ARROWS_CUTSCENE, []{return IsAdult && CanTriggerLACS;}),
                }, {
                  //Exits
                  ExitPairing::Both(&ToT_Entrance,         []{return true;}),
                  ExitPairing::Both(&ToT_BeyondDoorOfTime, []{return CanPlay(SongOfTime) || OpenDoorOfTime;}),
  });

  Exit ToT_BeyondDoorOfTime = Exit("Beyond Door of Time", "", TEMPLE_OF_TIME, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  //EventPairing(&TimeTravel, []{return true;}),
                }, {
                  //Locations
                  ItemLocationPairing(SHEIK_AT_TEMPLE, []{return ForestMedallion && IsAdult;}),
                }, {
                  //Exits
                  ExitPairing::Both(&ToT_Main, []{return true;})
  });

  Exit CastleGrounds = Exit("Castle Grounds", "Castle Grounds", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&MK_Main,     []{return true;}),
                  ExitPairing::Both(&HC_Grounds,  []{return IsChild;}),
                  ExitPairing::Both(&OGC_Grounds, []{return IsAdult;})
  });

  Exit HC_Grounds = Exit("Hyrule Castle Grounds", "Castle Grounds", HYRULE_CASTLE, DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GossipStoneFairy, []{return GossipStoneFairy || CanSummonGossipFairy;}),
                  EventPairing(&ButterflyFairy,   []{return ButterflyFairy   || CanUse(CanUseItem::Sticks);}),
                  EventPairing(&BugRock,          []{return true;}),
                }, {
                  //Locations
                  ItemLocationPairing(HC_MALON_EGG,              []{return true;}),
                  ItemLocationPairing(HC_GS_TREE,                []{return CanChildAttack;}),
                  ItemLocationPairing(HC_MALON_GOSSIP_STONE,     []{return true;}),
                  ItemLocationPairing(HC_ROCK_WALL_GOSSIP_STONE, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&CastleGrounds,         []{return true;}),
                  ExitPairing::Both(&HC_Garden,             []{return WeirdEgg || !ShuffleWeirdEgg;}),
                  ExitPairing::Both(&HC_GreatFairyFountain, []{return HasExplosives;}),
                  ExitPairing::Both(&HC_StormsGrotto,       []{return CanOpenStormGrotto;})
  });

  Exit HC_Garden = Exit("HC Garden", "Castle Grounds", HYRULE_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                }, {
                  //Locations
                  ItemLocationPairing(HC_ZELDAS_LETTER, []{return true;}),
                  ItemLocationPairing(SONG_FROM_IMPA,   []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&HC_Grounds, []{return true;})
  });

  Exit HC_GreatFairyFountain = Exit("HC Great Fairy Fountain", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(HC_GREAT_FAIRY_REWARD, []{return CanPlay(ZeldasLullaby);}),
                }, {
                  //Exits
                  ExitPairing::Both(&HC_Grounds, []{return true;})
  });

  Exit HC_StormsGrotto = Exit("HC Storms Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&NutPot,           []{return NutPot           || CanBlastOrSmash;}),
                  EventPairing(&GossipStoneFairy, []{return GossipStoneFairy || (CanBlastOrSmash && CanSummonGossipFairy);}),
                  EventPairing(&WanderingBugs,    []{return WanderingBugs    || CanBlastOrSmash;}),
                }, {
                  //Locations
                  ItemLocationPairing(HC_GS_STORMS_GROTTO,           []{return CanBlastOrSmash && HookshotOrBoomerang;}),
                  ItemLocationPairing(HC_STORMS_GROTTO_GOSSIP_STONE, []{return CanBlastOrSmash;}),
                }, {
                  //Exits
                  ExitPairing::Both(&HC_Grounds, []{return true;})
  });

  Exit OGC_Grounds = Exit("Ganon's Castle Grounds", "Castle Grounds", OUTSIDE_GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations                                   //the terrain was lowered such that you can't get this GS with a simple sword slash
                  ItemLocationPairing(OGC_GS, []{return HasExplosives || (IsAdult && (LogicOutsideGanonsGS || Bow || Hookshot || CanUse(CanUseItem::Dins_Fire)));}),
                }, {
                  //Exits
                  ExitPairing::Night(&CastleGrounds,          []{return AtNight;}),
                  ExitPairing::Night(&OGC_GreatFairyFountain, []{return CanUse(CanUseItem::Golden_Gauntlets) && AtNight;}),
                  ExitPairing::Both(&GanonsCastle_Lobby,      []{return Dungeon::GanonsCastle.IsVanilla() && CanBuildRainbowBridge;}),
                  ExitPairing::Both(&GanonsCastle_MQ_Lobby,   []{return Dungeon::GanonsCastle.IsMQ()      && CanBuildRainbowBridge;}),
  });

  Exit OGC_GreatFairyFountain = Exit("OGC Great Fairy Fountain", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(OGC_GREAT_FAIRY_REWARD, []{return CanPlay(ZeldasLullaby);}),
                }, {
                  //Exits
                  ExitPairing::Both(&CastleGrounds, []{return true;}),
  });

  Exit MK_GuardHouse = Exit("Market Guard House", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(MARKET_10_BIG_POES,    []{return IsAdult && BigPoeKill;}),
                  ItemLocationPairing(MARKET_GS_GUARD_HOUSE, []{return IsChild;}),
                }, {
                  //Exits
                  ExitPairing::Both(&MK_Entrance, []{return true;})
  });

  Exit MK_Bazaar = Exit("Market Bazaar", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(MARKET_BAZAAR_ITEM_1, []{return true;}),
                  ItemLocationPairing(MARKET_BAZAAR_ITEM_2, []{return true;}),
                  ItemLocationPairing(MARKET_BAZAAR_ITEM_3, []{return true;}),
                  ItemLocationPairing(MARKET_BAZAAR_ITEM_4, []{return true;}),
                  ItemLocationPairing(MARKET_BAZAAR_ITEM_5, []{return true;}),
                  ItemLocationPairing(MARKET_BAZAAR_ITEM_6, []{return true;}),
                  ItemLocationPairing(MARKET_BAZAAR_ITEM_7, []{return true;}),
                  ItemLocationPairing(MARKET_BAZAAR_ITEM_8, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&MK_Main, []{return true;})
  });

  Exit MK_MaskShop = Exit("Market Mask Shop", "", NONE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&SkullMask,   []{return SkullMask   || (ZeldasLetter && Kak_Main.Child());}),
                  EventPairing(&MaskOfTruth, []{return MaskOfTruth || (SkullMask && (LW_Main.Child() && CanPlay(SariasSong) && GY_Main.dayChild && HF_Main.Child() && HasAllStones));}),
                }, {}, {
                  //Exits
                  ExitPairing::Both(&MK_Main, []{return true;})
  });

  Exit MK_ShootingGallery = Exit("Market Shooting Gallery", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(MARKET_SHOOTING_GALLERY_REWARD, []{return IsChild;})
                }, {
                  //Exits
                  ExitPairing::Both(&MK_Main, []{return true;})
  });

  Exit MK_BombchuBowling = Exit("Market Bombchu Bowling", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(MARKET_BOMBCHU_BOWLING_FIRST_PRIZE,  []{return FoundBombchus;}),
                  ItemLocationPairing(MARKET_BOMBCHU_BOWLING_SECOND_PRIZE, []{return FoundBombchus;}),
                  ItemLocationPairing(MARKET_BOMBCHU_BOWLING_BOMBCHUS,     []{return FoundBombchus;}),
                }, {
                  //Exits
                  ExitPairing::Both(&MK_Main, []{return true;})
  });

  Exit MK_PotionShop = Exit("Market Potion Shop", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(MARKET_POTION_SHOP_ITEM_1, []{return true;}),
                  ItemLocationPairing(MARKET_POTION_SHOP_ITEM_2, []{return true;}),
                  ItemLocationPairing(MARKET_POTION_SHOP_ITEM_3, []{return true;}),
                  ItemLocationPairing(MARKET_POTION_SHOP_ITEM_4, []{return true;}),
                  ItemLocationPairing(MARKET_POTION_SHOP_ITEM_5, []{return true;}),
                  ItemLocationPairing(MARKET_POTION_SHOP_ITEM_6, []{return true;}),
                  ItemLocationPairing(MARKET_POTION_SHOP_ITEM_7, []{return true;}),
                  ItemLocationPairing(MARKET_POTION_SHOP_ITEM_8, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&MK_Main, []{return true;})
  });

  Exit MK_TreasureChestGame = Exit("Market Treasure Chest Game", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(MARKET_TREASURE_CHEST_GAME_REWARD, []{return CanUse(CanUseItem::Lens_of_Truth);})
                }, {
                  //Exits
                  ExitPairing::Both(&MK_Main, []{return true;})
  });

  Exit MK_BombchuShop = Exit("Market Bombchu Shop", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(MARKET_BOMBCHU_SHOP_ITEM_1, []{return true;}),
                  ItemLocationPairing(MARKET_BOMBCHU_SHOP_ITEM_2, []{return true;}),
                  ItemLocationPairing(MARKET_BOMBCHU_SHOP_ITEM_3, []{return true;}),
                  ItemLocationPairing(MARKET_BOMBCHU_SHOP_ITEM_4, []{return true;}),
                  ItemLocationPairing(MARKET_BOMBCHU_SHOP_ITEM_5, []{return true;}),
                  ItemLocationPairing(MARKET_BOMBCHU_SHOP_ITEM_6, []{return true;}),
                  ItemLocationPairing(MARKET_BOMBCHU_SHOP_ITEM_7, []{return true;}),
                  ItemLocationPairing(MARKET_BOMBCHU_SHOP_ITEM_8, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&MK_Main, []{return true;})
  });

  Exit MK_DogLadyHouse = Exit("Market Dog Lady House", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(MARKET_LOST_DOG, []{return AtNight;})
                }, {
                  //Exits
                  ExitPairing::Both(&MK_Main, []{return true;})
  });

  Exit MK_ManInGreenHouse = Exit("Market Man in Green House", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                }, {
                  //Exits
                  ExitPairing::Both(&MK_Main, []{return true;})
  });

  Exit Kak_Main = Exit("Kakariko Village", "Kakariko Village", KAKARIKO_VILLAGE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&CojiroAccess,            []{return CojiroAccess || (IsAdult && WakeUpAdultTalon);}),
                  EventPairing(&BugRock,                 []{return true;}),
                  EventPairing(&KakarikoVillageGateOpen, []{return KakarikoVillageGateOpen || (IsChild && (ZeldasLetter || OpenKakariko.Is(OPENKAKARIKO_OPEN)));}),
                }, {
                  //Locations
                  ItemLocationPairing(SHEIK_IN_KAKARIKO,               []{return IsAdult && ForestMedallion && FireMedallion && WaterMedallion;}),
                  ItemLocationPairing(KAK_ANJU_AS_CHILD,               []{return IsChild && AtDay;}),
                  ItemLocationPairing(KAK_ANJU_AS_ADULT,               []{return IsAdult && AtDay;}),
                  ItemLocationPairing(KAK_GS_HOUSE_UNDER_CONSTRUCTION, []{return IsChild && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(KAK_GS_SKULLTULA_HOUSE,          []{return IsChild && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(KAK_GS_GUARDS_HOUSE,             []{return IsChild && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(KAK_GS_TREE,                     []{return IsChild && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(KAK_GS_WATCHTOWER,               []{return IsChild && (Slingshot || HasBombchus) && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(KAK_GS_ABOVE_IMPAS_HOUSE,        []{return CanUse(CanUseItem::Hookshot) && AtNight && CanGetNightTimeGS;}),
                }, {
                  //Exits
                  ExitPairing::Both(&HF_Main,                []{return true;}),
                  ExitPairing::Both(&Kak_CarpenterBossHouse, []{return true;}),
                  ExitPairing::Both(&Kak_HouseOfSkulltula,   []{return true;}),
                  ExitPairing::Both(&Kak_ImpasHouse,         []{return true;}),
                  ExitPairing::Both(&Kak_Windmill,           []{return true;}),
                  ExitPairing::Day(&Kak_Bazaar,              []{return IsAdult && AtDay;}),
                  ExitPairing::Day(&Kak_ShootingGallery,     []{return IsAdult && AtDay;}),
                  ExitPairing::Both(&BottomOfTheWell,        []{return Dungeon::BottomOfTheWell.IsVanilla() && DrainWell && (IsChild || ShuffleDungeonEntrances);}),
                  ExitPairing::Both(&BottomOfTheWell_MQ,     []{return Dungeon::BottomOfTheWell.IsMQ()      && DrainWell && (IsChild || ShuffleDungeonEntrances);}),
                  ExitPairing::Day(&Kak_PotionShopFront,     []{return AtDay;}),
                  ExitPairing::Both(&Kak_PotionShopFront,    []{return IsChild;}),
                  ExitPairing::Both(&Kak_RedeadGrotto,       []{return CanOpenBombGrotto;}),
                  ExitPairing::Both(&Kak_ImpasLedge,         []{return (IsAdult && LogicVisibleCollision);}),
                  ExitPairing::Day(&Kak_ImpasLedge,          []{return (IsChild && AtDay);}),
                  ExitPairing::Both(&Kak_Rooftop,            []{return CanUse(CanUseItem::Hookshot) || (LogicManOnRoof && (IsAdult || Slingshot || HasBombchus));}),
                  ExitPairing::Day(&Kak_Rooftop,             []{return LogicManOnRoof && AtDay;}),
                  ExitPairing::Both(&GY_Main,                []{return true;}),
                  ExitPairing::Both(&Kak_BehindGate,         []{return IsAdult || (KakarikoVillageGateOpen);})
  });

  Exit Kak_ImpasLedge = Exit("Kak Impas Ledge", "Kakariko Village", KAKARIKO_VILLAGE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&Kak_ImpasHouseBack, []{return true;}),
                  ExitPairing::Both(&Kak_Main,           []{return true;})
  });

  Exit Kak_Rooftop = Exit("Kak Rooftop", "Kakariko VIllage", KAKARIKO_VILLAGE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(KAK_MAN_ON_ROOF, []{return true;})
                }, {
                  //Exits
                  ExitPairing::Both(&Kak_Backyard, []{return true;})
  });

  Exit Kak_Backyard = Exit("Kak Backyard", "Kakariko Village", KAKARIKO_VILLAGE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&Kak_Main,                []{return true;}),
                  ExitPairing::Both(&Kak_OpenGrotto,          []{return true;}),
                  ExitPairing::Both(&Kak_OddMedicineBuilding, []{return IsAdult;}),
                  ExitPairing::Day(&Kak_PotionShopBack,       []{return IsAdult && AtDay;})
  });

  Exit Kak_CarpenterBossHouse = Exit("Kak Carpenter Boss House", "", NONE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&WakeUpAdultTalon, []{return WakeUpAdultTalon || (IsAdult && (PocketEgg || PocketCucco));}),
                }, {}, {
                  //Exits
                  ExitPairing::Both(&Kak_Main, []{return true;})
  });

  Exit Kak_HouseOfSkulltula = Exit("Kak House of Skulltula", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(KAK_10_GOLD_SKULLTULA_REWARD, []{return GoldSkulltulaTokens >= 10;}),
                  ItemLocationPairing(KAK_20_GOLD_SKULLTULA_REWARD, []{return GoldSkulltulaTokens >= 20;}),
                  ItemLocationPairing(KAK_30_GOLD_SKULLTULA_REWARD, []{return GoldSkulltulaTokens >= 30;}),
                  ItemLocationPairing(KAK_40_GOLD_SKULLTULA_REWARD, []{return GoldSkulltulaTokens >= 40;}),
                  ItemLocationPairing(KAK_50_GOLD_SKULLTULA_REWARD, []{return GoldSkulltulaTokens >= 50;}),
                }, {
                  //Exits
                  ExitPairing::Both(&Kak_Main, []{return true;})
  });

  Exit Kak_ImpasHouse = Exit("Kak Impas House", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&Kak_ImpasHouseNearCow, []{return true;}),
                  ExitPairing::Both(&Kak_Main,              []{return true;})
  });

  Exit Kak_ImpasHouseBack = Exit("Kak Impas House Back", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(KAK_IMPAS_HOUSE_FREESTANDING_POH, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&Kak_ImpasLedge,        []{return true;}),
                  ExitPairing::Both(&Kak_ImpasHouseNearCow, []{return true;})
  });

  Exit Kak_ImpasHouseNearCow = Exit("Kak Impas House Near Cow", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(KAK_IMPAS_HOUSE_COW, []{return CanPlay(EponasSong);}),
                }, {
                  //Exits
                  ExitPairing::Both(&Kak_ImpasHouseBack, []{return false;})
  });

  Exit Kak_Windmill = Exit("Kak Windmill", "", NONE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&DrainWell, []{return DrainWell || (IsChild && CanPlay(SongOfStorms));}),
                }, {
                  //Locations
                  ItemLocationPairing(KAK_WINDMILL_FREESTANDING_POH, []{return CanUse(CanUseItem::Boomerang) || DampesWindmillAccess;}),
                  ItemLocationPairing(SONG_FROM_WINDMILL,            []{return IsAdult && Ocarina;}),
                }, {
                  //Exits
                  ExitPairing::Both(&Kak_Main, []{return true;})
  });

  Exit Kak_Bazaar = Exit("Kak Bazaar", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(KAK_BAZAAR_ITEM_1, []{return true;}),
                  ItemLocationPairing(KAK_BAZAAR_ITEM_2, []{return true;}),
                  ItemLocationPairing(KAK_BAZAAR_ITEM_3, []{return true;}),
                  ItemLocationPairing(KAK_BAZAAR_ITEM_4, []{return true;}),
                  ItemLocationPairing(KAK_BAZAAR_ITEM_5, []{return true;}),
                  ItemLocationPairing(KAK_BAZAAR_ITEM_6, []{return true;}),
                  ItemLocationPairing(KAK_BAZAAR_ITEM_7, []{return true;}),
                  ItemLocationPairing(KAK_BAZAAR_ITEM_8, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&Kak_Main, []{return true;})
  });

  Exit Kak_ShootingGallery = Exit("Kak Shooting Gallery", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(KAK_SHOOTING_GALLERY_REWARD, []{return IsAdult && Bow;}),
                }, {
                  //Exits
                  ExitPairing::Both(&Kak_Main, []{return true;})
  });

  Exit Kak_PotionShopFront = Exit("Kak Potion Shop Front", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(KAK_POTION_SHOP_ITEM_1, []{return true;}),
                  ItemLocationPairing(KAK_POTION_SHOP_ITEM_2, []{return true;}),
                  ItemLocationPairing(KAK_POTION_SHOP_ITEM_3, []{return true;}),
                  ItemLocationPairing(KAK_POTION_SHOP_ITEM_4, []{return true;}),
                  ItemLocationPairing(KAK_POTION_SHOP_ITEM_5, []{return true;}),
                  ItemLocationPairing(KAK_POTION_SHOP_ITEM_6, []{return true;}),
                  ItemLocationPairing(KAK_POTION_SHOP_ITEM_7, []{return true;}),
                  ItemLocationPairing(KAK_POTION_SHOP_ITEM_8, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&Kak_Main,           []{return true;}),
                  ExitPairing::Both(&Kak_PotionShopBack, []{return IsAdult;})
  });

  Exit Kak_PotionShopBack = Exit("Kak Potion Shop Back", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&Kak_Backyard,        []{return IsAdult;}),
                  ExitPairing::Both(&Kak_PotionShopFront, []{return true;})
  });

  Exit Kak_OddMedicineBuilding = Exit("Kak Odd Medicine Building", "", NONE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&OddPoulticeAccess, []{return OddPoulticeAccess || (IsAdult && (OddMushroomAccess || (OddMushroom && DisableTradeRevert)));}),
                }, {}, {
                  //Exits
                  ExitPairing::Both(&Kak_Backyard, []{return true;})
  });

  Exit Kak_RedeadGrotto = Exit("Kak Redead Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(KAK_REDEAD_GROTTO_CHEST, []{return IsAdult || (Sticks || KokiriSword || CanUse(CanUseItem::Dins_Fire));})
                }, {
                  //Exits
                  ExitPairing::Both(&Kak_Main, []{return true;})
  });

  Exit Kak_OpenGrotto = Exit("Kak Open Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  ItemLocationPairing(KAK_OPEN_GROTTO_CHEST,        []{return true;}),
                  ItemLocationPairing(KAK_OPEN_GROTTO_GOSSIP_STONE, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&Kak_Backyard, []{return true;})
  });

  Exit GY_Main = Exit("Graveyard", "Graveyard", THE_GRAVEYARD, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&ButterflyFairy, []{return ButterflyFairy || (CanUse(CanUseItem::Sticks) && AtDay);}),
                  EventPairing(&BeanPlantFairy, []{return BeanPlantFairy || (GY_Main.CanPlantBean() && CanPlay(SongOfStorms));}),
                  EventPairing(&BugRock,        []{return true;}),
                }, {
                  //Locations
                  ItemLocationPairing(GRAVEYARD_FREESTANDING_POH,        []{return (IsAdult && (GY_Main.CanPlantBean() || CanUse(CanUseItem::Longshot))) || (LogicGraveyardPoH && CanUse(CanUseItem::Boomerang));}),
                  ItemLocationPairing(GRAVEYARD_DAMPE_GRAVEDIGGING_TOUR, []{return IsChild && AtNight;}), //This needs to change
                  ItemLocationPairing(GRAVEYARD_GS_WALL,                 []{return CanUse(CanUseItem::Boomerang) && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(GRAVEYARD_GS_BEAN_PATCH,           []{return CanPlantBugs && CanChildAttack;}),
                }, {
                  //Exits
                  ExitPairing::Both(&GY_ShieldGrave,      []{return IsAdult;}),
                  ExitPairing::Night(&GY_ShieldGrave,     []{return AtNight;}),
                  ExitPairing::Both(&GY_ComposersGrave,   []{return CanPlay(ZeldasLullaby);}),
                  ExitPairing::Both(&GY_HeartPieceGrave,  []{return IsAdult;}),
                  ExitPairing::Night(&GY_HeartPieceGrave, []{return AtNight;}),
                  ExitPairing::Both(&GY_DampesGrave,      []{return IsAdult;}),
                  ExitPairing::Both(&GY_DampesHouse,      []{return IsAdult || AtDampeTime;}), //TODO: This needs to be handled
                  ExitPairing::Both(&Kak_Main,            []{return true;})
  });

  Exit GY_ShieldGrave = Exit("GY Shield Grave", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(GRAVEYARD_SHIELD_GRAVE_CHEST, []{return true;})
                  //Free Fairies
                }, {
                  //Exits
                  ExitPairing::Both(&GY_Main, []{return true;})
  });

  Exit GY_HeartPieceGrave = Exit("GY Heart Piece Grave", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(GRAVEYARD_HEART_PIECE_GRAVE_CHEST, []{return CanPlay(SunsSong);})
                }, {
                  //Exits
                  ExitPairing::Both(&GY_Main, []{return true;})
  });

  Exit GY_ComposersGrave = Exit("GY Composers Grave", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(GRAVEYARD_COMPOSERS_GRAVE_CHEST, []{return HasFireSource;}),
                  ItemLocationPairing(SONG_FROM_COMPOSERS_GRAVE,       []{return IsAdult || (Slingshot || Boomerang || Sticks || HasExplosives || KokiriSword);}),
                }, {
                  //Exits
                  ExitPairing::Both(&GY_Main, []{return true;}),
  });

  Exit GY_DampesGrave = Exit("GY Dampes Grave", "", NONE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&DekuNutDrop,          []{return true;}),
                  EventPairing(&DampesWindmillAccess, []{return DampesWindmillAccess || (IsAdult && CanPlay(SongOfTime));}),
                }, {
                  //Locations
                  ItemLocationPairing(GRAVEYARD_HOOKSHOT_CHEST,              []{return true;}),
                  ItemLocationPairing(GRAVEYARD_DAMPE_RACE_FREESTANDING_POH, []{return IsAdult || LogicChildDampeRacePoH;}),
                }, {
                  //Exits
                  ExitPairing::Both(&GY_Main,      []{return true;}),
                  ExitPairing::Both(&Kak_Windmill, []{return IsAdult && CanPlay(SongOfTime);})
  });

  Exit GY_DampesHouse = Exit("GY Dampes House", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&GY_Main, []{return true;})
  });

  Exit GY_WarpPadRegion = Exit("GY Warp Pad Region", "Graveyard", THE_GRAVEYARD, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GossipStoneFairy, []{return GossipStoneFairy || CanSummonGossipFairyWithoutSuns;}),
                }, {
                  //Locations
                  ItemLocationPairing(GRAVEYARD_GOSSIP_STONE, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&GY_Main,                  []{return true;}),
                  ExitPairing::Both(&ShadowTemple_Entryway,    []{return Dungeon::ShadowTemple.IsVanilla() && (CanUse(CanUseItem::Dins_Fire) || (LogicShadowFireArrowEntry && CanUse(CanUseItem::Fire_Arrows)));}),
                  ExitPairing::Both(&ShadowTemple_MQ_Entryway, []{return Dungeon::ShadowTemple.IsMQ()      && (CanUse(CanUseItem::Dins_Fire) || (LogicShadowFireArrowEntry && CanUse(CanUseItem::Fire_Arrows)));}),
  });

  Exit Kak_BehindGate = Exit("Kak Behind Gate", "Kakariko Village", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&Kak_Main, []{return IsAdult || LogicVisibleCollision || KakarikoVillageGateOpen || OpenKakariko.Is(OPENKAKARIKO_OPEN);}),
                  ExitPairing::Both(&DMT_Main, []{return true;})
  });

  Exit DMT_Main = Exit("Death Mountain", "Death Mountain", DEATH_MOUNTAIN_TRAIL, DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&BeanPlantFairy, []{return BeanPlantFairy || (DMT_Main.CanPlantBean() && CanPlay(SongOfStorms) && (HasExplosives || GoronBracelet));}),
                }, {
                  //Locations
                  ItemLocationPairing(DMT_CHEST,                    []{return CanBlastOrSmash || (LogicDMTBombable && IsChild && GoronBracelet);}),
                  ItemLocationPairing(DMT_FREESTANDING_POH,         []{return CanTakeDamage || CanUse(CanUseItem::Hover_Boots) || (IsAdult && DMT_Main.CanPlantBean() && (HasExplosives || GoronBracelet));}),
                  ItemLocationPairing(DMT_GS_BEAN_PATCH,            []{return CanPlantBugs && (HasExplosives || GoronBracelet || (LogicDMTSoilGS && CanUse(CanUseItem::Boomerang)));}),
                  ItemLocationPairing(DMT_GS_NEAR_KAK,              []{return CanBlastOrSmash;}),
                  ItemLocationPairing(DMT_GS_ABOVE_DODONGOS_CAVERN, []{return IsAdult && AtNight && CanUse(CanUseItem::Hammer) && CanGetNightTimeGS;})
                }, {
                  //Exits
                  ExitPairing::Both(&Kak_BehindGate,          []{return true;}),
                  ExitPairing::Both(&GC_Main,                 []{return true;}),
                  ExitPairing::Both(&DMT_Summit,              []{return CanBlastOrSmash || (DMT_Main.Adult() && Hammer) || (IsAdult && (DMT_Main.CanPlantBean() && GoronBracelet));}),
                  ExitPairing::Both(&DodongosCavern_Entryway, []{return HasExplosives || GoronBracelet || IsAdult;}),
                  ExitPairing::Both(&DMT_StormsGrotto,        []{return CanOpenStormGrotto;})
  });

  Exit DMT_Summit = Exit("Death Mountain Summit", "Death Mountain", DEATH_MOUNTAIN_TRAIL, DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&PrescriptionAccess, []{return PrescriptionAccess || (IsAdult && (BrokenSwordAccess || BrokenSword));}),
                  EventPairing(&GossipStoneFairy,   []{return GossipStoneFairy   || CanSummonGossipFairy;}),
                  EventPairing(&BugRock,            []{return true;}),
                }, {
                  //Locations
                  ItemLocationPairing(DMT_BIGGORON,              []{return IsAdult && (ClaimCheck || (GuaranteeTradePath && (EyedropsAccess || (Eyedrops && DisableTradeRevert))));}),
                  ItemLocationPairing(DMT_GS_FALLING_ROCKS_PATH, []{return IsAdult && AtNight && CanUse(CanUseItem::Hammer) && CanGetNightTimeGS;}),
                  ItemLocationPairing(DMT_GOSSIP_STONE,          []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&DMT_Main,               []{return true;}),
                  ExitPairing::Both(&DMC_UpperLocal,         []{return true;}),
                  ExitPairing::Both(&DMT_OwlFlight,          []{return IsChild;}),
                  ExitPairing::Both(&DMT_CowGrotto,          []{return DMT_Summit.Here([]{return CanBlastOrSmash;});}),
                  ExitPairing::Both(&DMT_GreatFairyFountain, []{return DMT_Summit.Here([]{return CanBlastOrSmash;});}),
  });

  Exit DMT_OwlFlight = Exit("DMT Owl Flight", "Death Mountain", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&Kak_ImpasLedge, []{return true;})
  });

  Exit DodongosCavern_Entryway = Exit("Dodongos Cavern Entryway", "Death Mountain", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&DodongosCavern_Beginning,    []{return Dungeon::DodongosCavern.IsVanilla();}),
                  ExitPairing::Both(&DodongosCavern_MQ_Beginning, []{return Dungeon::DodongosCavern.IsMQ();}),
                  ExitPairing::Both(&DMT_Main,                    []{return true;}),
  });

  Exit DMT_CowGrotto = Exit("DMT Cow Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(DMT_COW_GROTTO_COW, []{return CanPlay(EponasSong);}),
                }, {
                  //Exits
                  ExitPairing::Both(&DMT_Main, []{return true;})

  });

  Exit DMT_StormsGrotto = Exit("DMT Storms Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  ItemLocationPairing(DMT_STORMS_GROTTO_CHEST,        []{return true;}),
                  ItemLocationPairing(DMT_STORMS_GROTTO_GOSSIP_STONE, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&DMT_Main, []{return true;})
  });

  Exit DMT_GreatFairyFountain = Exit("DMT Great Fairy Fountain", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(DMT_GREAT_FAIRY_REWARD, []{return CanPlay(ZeldasLullaby);}),
                }, {
                  //Exits
                  ExitPairing::Both(&DMT_Summit, []{return true;})
  });

  Exit GC_Main = Exit("Goron City", "Goron City", GORON_CITY, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GossipStoneFairy,          []{return GossipStoneFairy          || CanSummonGossipFairyWithoutSuns;}),
                  EventPairing(&StickPot,                  []{return StickPot                  || IsChild;}),
                  EventPairing(&BugRock,                   []{return true;}),
                  EventPairing(&GoronCityChildFire,        []{return GoronCityChildFire        || (IsChild && CanUse(CanUseItem::Dins_Fire));}),
                  EventPairing(&GCWoodsWarpOpen,           []{return GCWoodsWarpOpen           || (CanBlastOrSmash || CanUse(CanUseItem::Dins_Fire) || CanUse(CanUseItem::Bow) || GoronBracelet || GoronCityChildFire);}),
                  EventPairing(&StopGCRollingGoronAsAdult, []{return StopGCRollingGoronAsAdult || (IsAdult && (GoronBracelet || HasExplosives || Bow || (LogicLinkGoronDins && CanUse(CanUseItem::Dins_Fire))));}),
                }, {
                  //Locations
                  ItemLocationPairing(GC_MAZE_LEFT_CHEST,        []{return CanUse(CanUseItem::Hammer) || CanUse(CanUseItem::Silver_Gauntlets) || (LogicGoronCityLeftMost && HasExplosives && CanUse(CanUseItem::Hover_Boots));}),
                  ItemLocationPairing(GC_MAZE_CENTER_CHEST,      []{return CanBlastOrSmash  || CanUse(CanUseItem::Silver_Gauntlets);}),
                  ItemLocationPairing(GC_MAZE_RIGHT_CHEST,       []{return CanBlastOrSmash  || CanUse(CanUseItem::Silver_Gauntlets);}),
                  ItemLocationPairing(GC_POT_FREESTANDING_POH,   []{return IsChild && GoronCityChildFire && (Bombs || (GoronBracelet && LogicGoronCityPotWithStrength) || (HasBombchus && LogicGoronCityPot));}),
                  ItemLocationPairing(GC_ROLLING_GORON_AS_CHILD, []{return IsChild && (HasExplosives || (GoronBracelet && LogicChildRollingWithStrength));}),
                  ItemLocationPairing(GC_ROLLING_GORON_AS_ADULT, []{return StopGCRollingGoronAsAdult;}),
                  ItemLocationPairing(GC_GS_BOULDER_MAZE,        []{return IsChild && HasExplosives;}),
                  ItemLocationPairing(GC_GS_CENTER_PLATFORM,     []{return IsAdult;}),
                  ItemLocationPairing(GC_MAZE_GOSSIP_STONE,      []{return CanBlastOrSmash || CanUse(CanUseItem::Silver_Gauntlets);}),
                  ItemLocationPairing(GC_MEDIGORON_GOSSIP_STONE, []{return CanBlastOrSmash || GoronBracelet;}),
                }, {
                  //Exits
                  ExitPairing::Both(&DMT_Main,           []{return true;}),
                  ExitPairing::Both(&GC_WoodsWarp,       []{return GCWoodsWarpOpen;}),
                  ExitPairing::Both(&GC_Shop,            []{return (IsAdult && StopGCRollingGoronAsAdult) || (IsChild && (HasExplosives || GoronBracelet || GoronCityChildFire));}),
                  ExitPairing::Both(&GC_DaruniasChamber, []{return (IsAdult && StopGCRollingGoronAsAdult) || (IsChild && CanPlay(ZeldasLullaby));}),
                  ExitPairing::Both(&GC_Grotto,          []{return IsAdult && ((CanPlay(SongOfTime) && ((DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_QUADRUPLE)) || CanUse(CanUseItem::Goron_Tunic) || CanUse(CanUseItem::Longshot) || CanUse(CanUseItem::Nayrus_Love))) || (DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO) && CanUse(CanUseItem::Goron_Tunic) && CanUse(CanUseItem::Hookshot)) ||(CanUse(CanUseItem::Nayrus_Love) && CanUse(CanUseItem::Hookshot)));}),
  });

  Exit GC_WoodsWarp = Exit("GC Woods Warp", "Goron City", NONE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GCWoodsWarpOpen, []{return GCWoodsWarpOpen || (CanBlastOrSmash || CanUse(CanUseItem::Dins_Fire));}),
                }, {}, {
                  //Exits
                  ExitPairing::Both(&GC_Main, []{return CanLeaveForest && GCWoodsWarpOpen;}),
                  ExitPairing::Both(&LW_Main, []{return true;})
  });

  Exit GC_DaruniasChamber = Exit("GC Darunias Chamber", "Goron City", GORON_CITY, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GoronCityChildFire, []{return GoronCityChildFire || (CanUse(CanUseItem::Sticks));}),
                }, {
                  //Locations
                  ItemLocationPairing(GC_DARUNIAS_JOY, []{return IsChild && CanPlay(SariasSong);})
                }, {
                  //Exits
                  ExitPairing::Both(&GC_Main,        []{return true;}),
                  ExitPairing::Both(&DMC_LowerLocal, []{return IsAdult;})
  });

  Exit GC_Shop = Exit("GC Shop", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(GC_SHOP_ITEM_1, []{return true;}),
                  ItemLocationPairing(GC_SHOP_ITEM_2, []{return true;}),
                  ItemLocationPairing(GC_SHOP_ITEM_3, []{return true;}),
                  ItemLocationPairing(GC_SHOP_ITEM_4, []{return true;}),
                  ItemLocationPairing(GC_SHOP_ITEM_5, []{return true;}),
                  ItemLocationPairing(GC_SHOP_ITEM_6, []{return true;}),
                  ItemLocationPairing(GC_SHOP_ITEM_7, []{return true;}),
                  ItemLocationPairing(GC_SHOP_ITEM_8, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&GC_Main, []{return true;})
  });

  Exit GC_Grotto = Exit("GC Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(GC_DEKU_SCRUB_GROTTO_LEFT,   []{return CanStunDeku;}),
                  ItemLocationPairing(GC_DEKU_SCRUB_GROTTO_RIGHT,  []{return CanStunDeku;}),
                  ItemLocationPairing(GC_DEKU_SCRUB_GROTTO_CENTER, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing::Both(&GC_Main, []{return true;})
  });

  Exit DMC_UpperNearby = Exit("DMC Upper Nearby", "Death Mountain Crater", DEATH_MOUNTAIN_CRATER, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&DMC_UpperLocal,  []{return CanUse(CanUseItem::Goron_Tunic);}),
                  ExitPairing::Both(&DMT_Summit,      []{return true;}),
                  ExitPairing::Both(&DMC_UpperGrotto, []{return DMC_UpperNearby.Here([]{return CanBlastOrSmash;});})
  });

  Exit DMC_UpperLocal = Exit("DMC Upper Local", "Death Mountain Crater", DEATH_MOUNTAIN_CRATER, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GossipStoneFairy, []{return GossipStoneFairy || (HasExplosives && CanSummonGossipFairyWithoutSuns);}),
                }, {
                  //Locations
                  ItemLocationPairing(DMC_WALL_FREESTANDING_POH, []{return true;}),
                  ItemLocationPairing(DMC_GS_CRATE,              []{return IsChild && CanChildAttack;}),
                  ItemLocationPairing(DMC_GOSSIP_STONE,          []{return HasExplosives;}),
                }, {
                  //Exits
                  ExitPairing::Both(&DMC_UpperNearby,      []{return true;}),
                  ExitPairing::Both(&DMC_LadderAreaNearby, []{return true;}),
                  ExitPairing::Both(&DMC_CentralNearby,    []{return CanUse(CanUseItem::Goron_Tunic) && CanUse(CanUseItem::Longshot) && ((DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_QUADRUPLE)) || (Fairy && !ShuffleDungeonEntrances) || CanUse(CanUseItem::Nayrus_Love));})
  });

  Exit DMC_LadderAreaNearby = Exit("DMC Ladder Area Nearby", "Death Mountain Crater", DEATH_MOUNTAIN_CRATER, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(DMC_DEKU_SCRUB, []{return IsChild && CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing::Both(&DMC_UpperNearby, []{return IsAdult;}),
                  ExitPairing::Both(&DMC_LowerNearby, []{return CanUse(CanUseItem::Hover_Boots) || (LogicCraterUpperToLower && CanUse(CanUseItem::Hammer));})
  });

  Exit DMC_LowerNearby = Exit("DMC Lower Nearby", "Death Mountain Crater", DEATH_MOUNTAIN_CRATER, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&DMC_LowerLocal,         []{return CanUse(CanUseItem::Goron_Tunic);}),
                  ExitPairing::Both(&GC_DaruniasChamber,     []{return true;}),
                  ExitPairing::Both(&DMC_GreatFairyFountain, []{return CanUse(CanUseItem::Hammer);}),
                  ExitPairing::Both(&DMC_HammerGrotto,       []{return CanUse(CanUseItem::Hammer);})
  });

  Exit DMC_LowerLocal = Exit("DMC Lower Local", "Death Mountain Crater", DEATH_MOUNTAIN_CRATER, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&DMC_LowerNearby,      []{return true;}),
                  ExitPairing::Both(&DMC_LadderAreaNearby, []{return true;}),
                  ExitPairing::Both(&DMC_CentralNearby,    []{return CanUse(CanUseItem::Hover_Boots) || CanUse(CanUseItem::Hookshot);}),
                  ExitPairing::Both(&FireTemple_Entrance,  []{return (CanUse(CanUseItem::Hover_Boots) || CanUse(CanUseItem::Hookshot)) && (LogicFewerTunicRequirements || CanUse(CanUseItem::Goron_Tunic));}),
  });

  Exit DMC_CentralNearby = Exit("DMC Central Nearby", "Death Mountain Crater", DEATH_MOUNTAIN_CRATER, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(DMC_VOLCANO_FREESTANDING_POH, []{return IsAdult && (DMC_CentralLocal.CanPlantBean() || (LogicCraterBeanPoHWithHovers && HoverBoots));}),
                  ItemLocationPairing(SHEIK_IN_CRATER,              []{return IsAdult;}),
                }, {
                  //Exits
                  ExitPairing::Both(&DMC_CentralLocal, []{return CanUse(CanUseItem::Goron_Tunic);})
  });

  Exit DMC_CentralLocal = Exit("DMC Central Local", "Death Mountain Crater", DEATH_MOUNTAIN_CRATER, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&BeanPlantFairy, []{return BeanPlantFairy || (DMC_CentralLocal.CanPlantBean() && CanPlay(SongOfStorms));}),
                }, {
                  //Locations
                  ItemLocationPairing(DMC_GS_BEAN_PATCH, []{return CanPlantBugs && CanChildAttack;}),
                }, {
                  //Exits
                  ExitPairing::Both(&DMC_CentralNearby,   []{return true;}),
                  ExitPairing::Both(&DMC_LowerNearby,     []{return IsAdult && (CanUse(CanUseItem::Hover_Boots) || CanUse(CanUseItem::Hookshot) || DMC_CentralLocal.CanPlantBean());}),
                  ExitPairing::Both(&DMC_UpperNearby,     []{return IsAdult && DMC_CentralLocal.CanPlantBean();}),
                  ExitPairing::Both(&FireTemple_Entrance, []{return (IsChild && ShuffleDungeonEntrances) || (IsAdult && (LogicFewerTunicRequirements || CanUse(CanUseItem::Goron_Tunic)));}),
  });

  Exit FireTemple_Entrance = Exit("Fire Temple Entrance", "Death Mountain Crater", DEATH_MOUNTAIN_CRATER, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                    ExitPairing::Both(&FireTemple_Lower,    []{return Dungeon::FireTemple.IsVanilla();}),
                    ExitPairing::Both(&FireTemple_MQ_Lower, []{return Dungeon::FireTemple.IsMQ();}),
  });

  Exit DMC_GreatFairyFountain = Exit("DMC Great Fairy Fountain", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(DMC_GREAT_FAIRY_REWARD, []{return CanPlay(ZeldasLullaby);}),
                }, {
                  //Exits
                  ExitPairing::Both(&DMC_LowerLocal, []{return true;})
  });

  Exit DMC_UpperGrotto = Exit("DMC Upper Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  ItemLocationPairing(DMC_UPPER_GROTTO_CHEST,        []{return true;}),
                  ItemLocationPairing(DMC_UPPER_GROTTO_GOSSIP_STONE, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&DMC_UpperLocal, []{return true;})
  });

  Exit DMC_HammerGrotto = Exit("DMC Hammer Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(DMC_DEKU_SCRUB_GROTTO_LEFT,   []{return CanStunDeku;}),
                  ItemLocationPairing(DMC_DEKU_SCRUB_GROTTO_RIGHT,  []{return CanStunDeku;}),
                  ItemLocationPairing(DMC_DEKU_SCRUB_GROTTO_CENTER, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing::Both(&DMC_LowerLocal, []{return true;})
  });

  Exit ZR_Front = Exit("ZR Front", "Zora River", ZORAS_RIVER, DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(ZR_GS_TREE, []{return IsChild && CanChildAttack;}),
                }, {
                  //Exits
                  ExitPairing::Both(&ZR_Main, []{return IsAdult || HasExplosives;}),
                  ExitPairing::Both(&HF_Main, []{return true;})
  });

  Exit ZR_Main = Exit("Zora River", "Zora River", ZORAS_RIVER, DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GossipStoneFairy, []{return GossipStoneFairy || CanSummonGossipFairy;}),
                  EventPairing(&BeanPlantFairy,   []{return BeanPlantFairy   || (ZR_Main.CanPlantBean() && CanPlay(SongOfStorms));}),
                  EventPairing(&ButterflyFairy,   []{return ButterflyFairy   || CanUse(CanUseItem::Sticks);}),
                  EventPairing(&BugShrub,         []{return BugShrub         || CanCutShrubs;}),
                }, {
                  //Locations
                  ItemLocationPairing(ZR_MAGIC_BEAN_SALESMAN,               []{return IsChild;}),
                  ItemLocationPairing(ZR_FROGS_OCARINA_GAME,                []{return IsChild && CanPlay(ZeldasLullaby) && CanPlay(SariasSong) && CanPlay(SunsSong) && CanPlay(EponasSong) && CanPlay(SongOfTime) && CanPlay(SongOfStorms);}),
                  ItemLocationPairing(ZR_FROGS_IN_THE_RAIN,                 []{return IsChild && CanPlay(SongOfStorms);}),
                  ItemLocationPairing(ZR_NEAR_OPEN_GROTTO_FREESTANDING_POH, []{return IsChild || CanUse(CanUseItem::Hover_Boots) || (IsAdult && LogicZoraRiverLower);}),
                  ItemLocationPairing(ZR_NEAR_DOMAIN_FREESTANDING_POH,      []{return IsChild || CanUse(CanUseItem::Hover_Boots) || (IsAdult && LogicZoraRiverUpper);}),
                  ItemLocationPairing(ZR_GS_LADDER,                         []{return IsChild && AtNight && CanChildAttack && CanGetNightTimeGS;}),
                  ItemLocationPairing(ZR_GS_NEAR_RAISED_GROTTOS,            []{return CanUse(CanUseItem::Hookshot) && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(ZR_GS_ABOVE_BRIDGE,                   []{return CanUse(CanUseItem::Hookshot) && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(ZR_NEAR_GROTTOS_GOSSIP_STONE,         []{return true;}),
                  ItemLocationPairing(ZR_NEAR_DOMAIN_GOSSIP_STONE,          []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&ZR_Front,           []{return true;}),
                  ExitPairing::Both(&ZR_OpenGrotto,      []{return true;}),
                  ExitPairing::Both(&ZR_FairyGrotto,     []{return ZR_Main.Here([]{return CanBlastOrSmash;});}),
                  ExitPairing::Both(&LW_Main,            []{return CanDive || CanUse(CanUseItem::Iron_Boots);}),
                  ExitPairing::Both(&ZR_StormsGrotto,    []{return CanOpenStormGrotto;}),
                  ExitPairing::Both(&ZR_BehindWaterfall, []{return CanPlay(ZeldasLullaby);})
  });

  Exit ZR_BehindWaterfall = Exit("ZR Behind Waterfall", "Zora River", NONE, DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&ZR_Main, []{return true;}),
                  ExitPairing::Both(&ZD_Main, []{return true;})
  });

  Exit ZR_OpenGrotto = Exit("ZR Open Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  ItemLocationPairing(ZR_OPEN_GROTTO_CHEST,        []{return true;}),
                  ItemLocationPairing(ZR_OPEN_GROTTO_GOSSIP_STONE, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&ZR_Main, []{return true;})
  });

  Exit ZR_FairyGrotto = Exit("ZR Fairy Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {
                  //Event
                  EventPairing(&FreeFairies, []{return true;}),
                }, {}, {
                  //Exits
                  ExitPairing::Both(&ZR_Main, []{return true;})
  });

  Exit ZR_StormsGrotto = Exit("ZR Storms Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(ZR_DEKU_SCRUB_GROTTO_REAR,  []{return CanStunDeku;}),
                  ItemLocationPairing(ZR_DEKU_SCRUB_GROTTO_FRONT, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing::Both(&ZR_Main, []{return true;})
  });

  Exit ZD_Main = Exit("Zoras Domain", "Zoras Domain", ZORAS_DOMAIN, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&EyeballFrogAccess, []{return EyeballFrogAccess || (IsAdult && KingZoraThawed && (Eyedrops || EyeballFrog || Prescription || PrescriptionAccess));}),
                  EventPairing(&GossipStoneFairy,  []{return GossipStoneFairy  || CanSummonGossipFairyWithoutSuns;}),
                  EventPairing(&NutPot,            []{return true;}),
                  EventPairing(&StickPot,          []{return StickPot          || IsChild;}),
                  EventPairing(&FishGroup,         []{return FishGroup         || IsChild;}),
                  EventPairing(&KingZoraThawed,    []{return KingZoraThawed    || (IsAdult   && BlueFire);}),
                  EventPairing(&DeliverLetter,     []{return DeliverLetter     || (RutosLetter && IsChild && ZorasFountain.IsNot(ZORASFOUNTAIN_OPEN));}),
                }, {
                  //Locations
                  ItemLocationPairing(ZD_DIVING_MINIGAME,     []{return IsChild;}),
                  ItemLocationPairing(ZD_CHEST,               []{return CanUse(CanUseItem::Sticks);}),
                  ItemLocationPairing(ZD_KING_ZORA_THAWED,    []{return KingZoraThawed;}),
                  ItemLocationPairing(ZD_GS_FROZEN_WATERFALL, []{return IsAdult && AtNight && (Hookshot || Bow || MagicMeter) && CanGetNightTimeGS;}),
                  ItemLocationPairing(ZD_GOSSIP_STONE,        []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&ZR_BehindWaterfall, []{return true;}),
                  ExitPairing::Both(&LH_Main,            []{return IsChild && CanDive;}),
                  ExitPairing::Both(&ZD_BehindKingZora,  []{return DeliverLetter || ZorasFountain.Is(ZORASFOUNTAIN_OPEN) || (ZorasFountain.Is(ZORASFOUNTAIN_ADULT) && IsAdult);}),
                  ExitPairing::Both(&ZD_Shop,            []{return IsChild || BlueFire;}),
                  ExitPairing::Both(&ZD_StormsGrotto,    []{return CanOpenStormGrotto;})
  });

  Exit ZD_BehindKingZora = Exit("ZD Behind King Zora", "Zoras Domain", NONE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&ZD_Main, []{return DeliverLetter || ZorasFountain.Is(ZORASFOUNTAIN_OPEN) || (ZorasFountain.Is(ZORASFOUNTAIN_ADULT) && IsAdult);}),
                  ExitPairing::Both(&ZF_Main, []{return true;})
  });

  Exit ZD_Shop = Exit("ZD Shop", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(ZD_SHOP_ITEM_1, []{return true;}),
                  ItemLocationPairing(ZD_SHOP_ITEM_2, []{return true;}),
                  ItemLocationPairing(ZD_SHOP_ITEM_3, []{return true;}),
                  ItemLocationPairing(ZD_SHOP_ITEM_4, []{return true;}),
                  ItemLocationPairing(ZD_SHOP_ITEM_5, []{return true;}),
                  ItemLocationPairing(ZD_SHOP_ITEM_6, []{return true;}),
                  ItemLocationPairing(ZD_SHOP_ITEM_7, []{return true;}),
                  ItemLocationPairing(ZD_SHOP_ITEM_8, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&ZD_Main, []{return true;})
  });

  Exit ZD_StormsGrotto = Exit("ZD Storms Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FreeFairies, []{return true;}),
                }, {}, {
                  //Exits
                  ExitPairing::Both(&ZD_Main, []{return true;}),
  });

  Exit ZF_Main = Exit("Zoras Fountain", "Zoras Fountain", ZORAS_FOUNTAIN, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GossipStoneFairy, []{return GossipStoneFairy || CanSummonGossipFairyWithoutSuns;}),
                  EventPairing(&ButterflyFairy,   []{return ButterflyFairy   || (CanUse(CanUseItem::Sticks) && AtDay);}),
                }, {
                  //Locations
                  ItemLocationPairing(ZF_ICEBERG_FREESTANDING_POH, []{return IsAdult;}),
                  ItemLocationPairing(ZF_BOTTOM_FREESTANDING_POH,  []{return IsAdult && IronBoots && (LogicFewerTunicRequirements || CanUse(CanUseItem::Zora_Tunic));}),
                  ItemLocationPairing(ZF_GS_TREE,                  []{return IsChild;}),
                  ItemLocationPairing(ZF_GS_ABOVE_THE_LOG,         []{return CanUse(CanUseItem::Boomerang) && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(ZF_GS_HIDDEN_CAVE,           []{return CanUse(CanUseItem::Silver_Gauntlets) && CanBlastOrSmash && CanUse(CanUseItem::Hookshot) && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(ZF_FAIRY_GOSSIP_STONE,       []{return true;}),
                  ItemLocationPairing(ZF_JABU_GOSSIP_STONE,        []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&ZD_BehindKingZora,           []{return true;}),
                  ExitPairing::Both(&JabuJabusBelly_Beginning,    []{return Dungeon::JabuJabusBelly.IsVanilla() && (IsChild && Fish);}),
                  ExitPairing::Both(&JabuJabusBelly_MQ_Beginning, []{return Dungeon::JabuJabusBelly.IsMQ()      && (IsChild && Fish);}),
                  ExitPairing::Both(&IceCavern_Beginning,         []{return Dungeon::IceCavern.IsVanilla() && IsAdult;}),
                  ExitPairing::Both(&IceCavern_MQ_Beginning,      []{return Dungeon::IceCavern.IsMQ()      && IsAdult;}),
                  ExitPairing::Both(&ZF_GreatFairyFountain,       []{return HasExplosives;})
  });

  Exit ZF_GreatFairyFountain = Exit("ZF Great Fairy Fountain", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(ZF_GREAT_FAIRY_REWARD, []{return CanPlay(ZeldasLullaby);}),
                }, {
                  //Exits
                  ExitPairing::Both(&ZF_Main, []{return true;})
  });

  Exit LLR_Main = Exit("Lon Lon Ranch", "Lon Lon Ranch", LON_LON_RANCH, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&Epona,    []{return Epona    || (CanPlay(EponasSong) && IsAdult && AtDay);}),
                  EventPairing(&LinksCow, []{return LinksCow || (CanPlay(EponasSong) && IsAdult && AtDay);}),
                }, {
                  //Locations
                  ItemLocationPairing(SONG_FROM_MALON,     []{return IsChild && ZeldasLetter && Ocarina && AtDay;}),
                  ItemLocationPairing(LLR_GS_TREE,         []{return IsChild;}),
                  ItemLocationPairing(LLR_GS_RAIN_SHED,    []{return IsChild && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(LLR_GS_HOUSE_WINDOW, []{return CanUse(CanUseItem::Boomerang) && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(LLR_GS_BACK_WALL,    []{return CanUse(CanUseItem::Boomerang) && AtNight && CanGetNightTimeGS;}),
                }, {
                  //Exits
                  ExitPairing::Both(&HF_Main,         []{return true;}),
                  ExitPairing::Both(&LLR_TalonsHouse, []{return true;}),
                  ExitPairing::Both(&LLR_Stables,     []{return true;}),
                  ExitPairing::Both(&LLR_Tower,       []{return true;}),
                  ExitPairing::Both(&LLR_Grotto,      []{return IsChild;})
  });

  Exit LLR_TalonsHouse = Exit("LLR Talons House", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(LLR_TALONS_CHICKENS, []{return IsChild && AtDay && ZeldasLetter;})
                }, {
                  //Exits
                  ExitPairing::Both(&LLR_Main, []{return true;})
  });

  Exit LLR_Stables = Exit("LLR Stables", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(LLR_STABLES_LEFT_COW,  []{return CanPlay(EponasSong);}),
                  ItemLocationPairing(LLR_STABLES_RIGHT_COW, []{return CanPlay(EponasSong);}),
                }, {
                  //Exits
                  ExitPairing::Both(&LLR_Main, []{return true;})
  });

  Exit LLR_Tower = Exit("LLR Tower", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(LLR_FREESTANDING_POH, []{return IsChild;}),
                  ItemLocationPairing(LLR_TOWER_LEFT_COW,   []{return CanPlay(EponasSong);}),
                  ItemLocationPairing(LLR_TOWER_RIGHT_COW,  []{return CanPlay(EponasSong);}),
                }, {
                  //Exits
                  ExitPairing::Both(&LLR_Main, []{return true;}),
  });

  Exit LLR_Grotto = Exit("LLR Grotto", "", NONE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(LLR_DEKU_SCRUB_GROTTO_LEFT,   []{return CanStunDeku;}),
                  ItemLocationPairing(LLR_DEKU_SCRUB_GROTTO_RIGHT,  []{return CanStunDeku;}),
                  ItemLocationPairing(LLR_DEKU_SCRUB_GROTTO_CENTER, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing::Both(&LLR_Main, []{return true;}),
  });

  /*--------------------------
  |    VANILLA DUNGEONS     |
  ---------------------------*/

  Exit DekuTree_Lobby = Exit("Deku Tree Lobby", "Deku Tree", DEKU_TREE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&DekuBabaSticks, []{return DekuBabaSticks || (IsAdult || KokiriSword || Boomerang);}),
                  EventPairing(&DekuBabaNuts,   []{return DekuBabaNuts   || (IsAdult || KokiriSword || Slingshot || Sticks || HasExplosives || CanUse(CanUseItem::Dins_Fire));}),
                }, {
                  //Locations
                  ItemLocationPairing(DEKU_TREE_MAP_CHEST,               []{return true;}),
                  ItemLocationPairing(DEKU_TREE_COMPASS_CHEST,           []{return true;}),
                  ItemLocationPairing(DEKU_TREE_COMPASS_ROOM_SIDE_CHEST, []{return true;}),
                  ItemLocationPairing(DEKU_TREE_BASEMENT_CHEST,          []{return IsAdult || CanChildAttack || Nuts;}),
                  ItemLocationPairing(DEKU_TREE_GS_COMPASS_ROOM,         []{return IsAdult || CanChildAttack;}),
                  ItemLocationPairing(DEKU_TREE_GS_BASEMENT_VINES,       []{return CanUseProjectile || CanUse(CanUseItem::Dins_Fire) || (LogicDekuBasementGS && (IsAdult || Sticks || KokiriSword));}),
                  ItemLocationPairing(DEKU_TREE_GS_BASEMENT_GATE,        []{return IsAdult || CanChildAttack;}),
                }, {
                  //Exits
                  ExitPairing::Both(&KF_OutsideDekuTree,        []{return true;}),
                  ExitPairing::Both(&DekuTree_SlingshotRoom,    []{return DekuTree_Lobby.Here([]{return HasShield;});}),
                  ExitPairing::Both(&DekuTree_BasementBackRoom, []{return (DekuTree_Lobby.Here([]{return HasFireSourceWithTorch || CanUse(CanUseItem::Bow);}) &&
                                                                            DekuTree_Lobby.Here([]{return CanUse(CanUseItem::Slingshot) || CanUse(CanUseItem::Bow);})) ||
                                                                            (IsChild && (LogicDekuB1Skip || DekuTree_Lobby.Here([]{return IsAdult;})));}),
                  ExitPairing::Both(&DekuTree_BossRoom,         []{return DekuTree_Lobby.Here([]{return HasFireSourceWithTorch || (LogicDekuB1WebsWithBow && CanUse(CanUseItem::Bow));}) &&
                                                                            (LogicDekuB1Skip || DekuTree_Lobby.Here([]{return IsAdult || CanUse(CanUseItem::Slingshot);}));}),
  });

  Exit DekuTree_SlingshotRoom = Exit("Deku Tree Slingshot Room", "Deku Tree", DEKU_TREE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(DEKU_TREE_SLINGSHOT_CHEST,           []{return true;}),
                  ItemLocationPairing(DEKU_TREE_SLINGSHOT_ROOM_SIDE_CHEST, []{return true;})
                }, {
                  //Exits
                  ExitPairing::Both(&DekuTree_Lobby, []{return true;})
  });

  Exit DekuTree_BasementBackRoom = Exit("Deku Tree Basement Backroom", "Deku Tree", DEKU_TREE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(DEKU_TREE_GS_BASEMENT_BACK_ROOM,  []{return DekuTree_BasementBackRoom.Here([]{return HasFireSourceWithTorch || CanUse(CanUseItem::Bow);}) &&
                                                                                  DekuTree_BasementBackRoom.Here([]{return CanBlastOrSmash;}) &&
                                                                                    HookshotOrBoomerang;}),
                }, {
                  //Exits
                  ExitPairing::Both(&DekuTree_Lobby, []{return true;}),

  });

  Exit DekuTree_BossRoom = Exit("Deku Tree Boss Room", "Deku Tree", DEKU_TREE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&DekuTreeClear, []{return DekuTreeClear || (DekuTree_BossRoom.Here([]{return HasShield;}) && (IsAdult || KokiriSword || Sticks));})
                }, {
                  //Locations
                  ItemLocationPairing(QUEEN_GOHMA,                 []{return DekuTree_BossRoom.Here([]{return HasShield;}) && (IsAdult || KokiriSword || Sticks);}),
                  ItemLocationPairing(DEKU_TREE_QUEEN_GOHMA_HEART, []{return DekuTree_BossRoom.Here([]{return HasShield;}) && (IsAdult || KokiriSword || Sticks);}),
                }, {
                  //Exits
                  ExitPairing::Both(&DekuTree_Lobby, []{return true;})
  });

  Exit DodongosCavern_Beginning = Exit("Dodongos Cavern Beginning", "Dodongos Cavern", DODONGOS_CAVERN, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&DodongosCavern_Entryway, []{return true;}),
                  ExitPairing::Both(&DodongosCavern_Lobby,    []{return DodongosCavern_Beginning.Here([]{return CanBlastOrSmash || GoronBracelet;});}),
  });

  Exit DodongosCavern_Lobby = Exit("Dodongos Cavern Lobby", "Dodongos Cavern", DODONGOS_CAVERN, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GossipStoneFairy, []{return GossipStoneFairy || CanSummonGossipFairy;}),
                }, {
                  //Locations
                  ItemLocationPairing(DODONGOS_CAVERN_MAP_CHEST,                          []{return true;}),
                  ItemLocationPairing(DODONGOS_CAVERN_COMPASS_CHEST,                      []{return IsAdult || Sticks || (CanUse(CanUseItem::Dins_Fire) && (Slingshot || HasExplosives || KokiriSword));}),
                  ItemLocationPairing(DODONGOS_CAVERN_GS_SIDE_ROOM_NEAR_LOWER_LIZALFOS,   []{return HasExplosives || IsAdult || Slingshot || Boomerang || Sticks || KokiriSword;}),
                  ItemLocationPairing(DODONGOS_CAVERN_GS_SCARECROW,                       []{return CanUse(CanUseItem::Scarecrow) || CanUse(CanUseItem::Longshot) || (LogicDCScarecrowGS && (IsAdult || CanChildAttack));}),
                  ItemLocationPairing(DODONGOS_CAVERN_DEKU_SCRUB_SIDE_ROOM_NEAR_DODONGOS, []{return IsAdult || Slingshot || Sticks || HasExplosives || KokiriSword;}),
                  ItemLocationPairing(DODONGOS_CAVERN_DEKU_SCRUB_LOBBY,                   []{return true;}),
                  ItemLocationPairing(DODONGOS_CAVERN_GOSSIP_STONE,                       []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&DodongosCavern_Beginning, []{return true;}),
                  ExitPairing::Both(&DodongosCavern_Climb,     []{return DodongosCavern_Lobby.Here([]{return IsAdult || ((Sticks || CanUse(CanUseItem::Dins_Fire)) && (Slingshot || Sticks || HasExplosives || KokiriSword));}) && (HasExplosives || GoronBracelet || CanUse(CanUseItem::Dins_Fire) ||(LogicDCStaircase && CanUse(CanUseItem::Bow)));}),
                  ExitPairing::Both(&DodongosCavern_FarBridge, []{return DodongosCavern_FarBridge.HasAccess();}),
  });

  Exit DodongosCavern_Climb = Exit("Dodongos Cavern Climb", "Dodongos Cavern", DODONGOS_CAVERN, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(DODONGOS_CAVERN_BOMB_FLOWER_PLATFORM_CHEST,     []{return true;}),
                  ItemLocationPairing(DODONGOS_CAVERN_GS_VINES_ABOVE_STAIRS,          []{return true;}),
                  ItemLocationPairing(DODONGOS_CAVERN_DEKU_SCRUB_NEAR_BOMB_BAG_RIGHT, []{return CanBlastOrSmash;}),
                  ItemLocationPairing(DODONGOS_CAVERN_DEKU_SCRUB_NEAR_BOMB_BAG_LEFT,  []{return CanBlastOrSmash;}),
                }, {
                  //Exits
                  ExitPairing::Both(&DodongosCavern_Lobby,     []{return true;}),
                  ExitPairing::Both(&DodongosCavern_FarBridge, []{return (IsChild && (Slingshot || (LogicDCSlingshotSkip && (Sticks || HasExplosives || KokiriSword)))) || (IsAdult && (Bow || HoverBoots || CanUse(CanUseItem::Longshot) || LogicDCJump));})
  });

  Exit DodongosCavern_FarBridge = Exit("Dodongos Cavern Far Bridge", "Dodongos Cavern", DODONGOS_CAVERN, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(DODONGOS_CAVERN_BOMB_BAG_CHEST,         []{return true;}),
                  ItemLocationPairing(DODONGOS_CAVERN_END_OF_BRIDGE_CHEST,    []{return CanBlastOrSmash;}),
                  ItemLocationPairing(DODONGOS_CAVERN_GS_ALCOVE_ABOVE_STAIRS, []{return HookshotOrBoomerang;}),
                }, {
                  //Exits
                  ExitPairing::Both(&DodongosCavern_BossArea, []{return HasExplosives;}),
                  ExitPairing::Both(&DodongosCavern_Lobby,    []{return true;})
  });

  Exit DodongosCavern_BossArea = Exit("Dodongos Cavern Boss Area", "Dodongos Cavern", DODONGOS_CAVERN, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPot,            []{return true;}),
                  EventPairing(&DodongosCavernClear, []{return DodongosCavernClear || ((Bombs || GoronBracelet) && (IsAdult || Sticks || KokiriSword));})
                }, {
                  //Locations
                  ItemLocationPairing(DODONGOS_CAVERN_BOSS_ROOM_CHEST,    []{return true;}),
                  ItemLocationPairing(DODONGOS_CAVERN_KING_DODONGO_HEART, []{return (Bombs || GoronBracelet) && (IsAdult || Sticks || KokiriSword);}),
                  ItemLocationPairing(KING_DODONGO,                       []{return (Bombs || GoronBracelet) && (IsAdult || Sticks || KokiriSword);}),
                  ItemLocationPairing(DODONGOS_CAVERN_GS_BACK_ROOM,       []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&DodongosCavern_Lobby, []{return true;})
  });

  Exit JabuJabusBelly_Beginning = Exit("Jabu Jabus Belly Beginning", "Jabu Jabus Belly", JABU_JABUS_BELLY, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&ZF_Main,             []{return true;}),
                  ExitPairing::Both(&JabuJabusBelly_Main, []{return CanUseProjectile;})
  });

  Exit JabuJabusBelly_Main = Exit("Jabu Jabus Belly Main", "Jabu Jabus Belly", JABU_JABUS_BELLY, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPot, []{return true;}),
                }, {
                  //Locations
                  ItemLocationPairing(JABU_JABUS_BELLY_BOOMERANG_CHEST,         []{return true;}),
                  ItemLocationPairing(JABU_JABUS_BELLY_GS_WATER_SWITCH_ROOM,    []{return true;}),
                  ItemLocationPairing(JABU_JABUS_BELLY_GS_LOBBY_BASEMENT_LOWER, []{return HookshotOrBoomerang;}),
                  ItemLocationPairing(JABU_JABUS_BELLY_GS_LOBBY_BASEMENT_UPPER, []{return HookshotOrBoomerang;}),
                  ItemLocationPairing(JABU_JABUS_BELLY_DEKU_SCRUB,              []{return CanDive || IsChild || LogicJabuScrubJumpDive || CanUse(CanUseItem::Iron_Boots);}),
                }, {
                  //Exits
                  ExitPairing::Both(&JabuJabusBelly_Beginning, []{return true;}),
                  ExitPairing::Both(&JabuJabusBelly_Depths,    []{return CanUse(CanUseItem::Boomerang);}),
                  ExitPairing::Both(&JabuJabusBelly_BossArea,  []{return LogicJabuBossGSAdult && CanUse(CanUseItem::Hover_Boots);}),
  });

  Exit JabuJabusBelly_Depths = Exit("Jabu Jabus Belly Depths", "Jabu Jabus Belly", JABU_JABUS_BELLY, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(JABU_JABUS_BELLY_MAP_CHEST,     []{return true;}),
                  ItemLocationPairing(JABU_JABUS_BELLY_COMPASS_CHEST, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&JabuJabusBelly_Main,     []{return true;}),
                  ExitPairing::Both(&JabuJabusBelly_BossArea, []{return Sticks || KokiriSword;}),
  });

  Exit JabuJabusBelly_BossArea = Exit("Jabu Jabus Belly Boss Area", "Jabu Jabus Belly", JABU_JABUS_BELLY, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&NutPot,              []{return true;}),
                  EventPairing(&JabuJabusBellyClear, []{return JabuJabusBellyClear || CanUse(CanUseItem::Boomerang);}),
                }, {
                  //Locations
                  ItemLocationPairing(JABU_JABUS_BELLY_BARINADE_HEART, []{return CanUse(CanUseItem::Boomerang);}),
                  ItemLocationPairing(BARINADE,                        []{return CanUse(CanUseItem::Boomerang);}),
                  ItemLocationPairing(JABU_JABUS_BELLY_GS_NEAR_BOSS,   []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&JabuJabusBelly_Main, []{return true;}),
  });

  Exit ForestTemple_Lobby = Exit("Forest Temple Lobby", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(FOREST_TEMPLE_FIRST_ROOM_CHEST,    []{return true;}),
                  ItemLocationPairing(FOREST_TEMPLE_FIRST_STALFOS_CHEST, []{return IsAdult || KokiriSword;}),
                  ItemLocationPairing(FOREST_TEMPLE_GS_FIRST_ROOM,       []{return (IsAdult && (Hookshot || Bow || Bombs)) || (IsChild && (Boomerang || Slingshot)) || HasBombchus || CanUse(CanUseItem::Dins_Fire);}),
                  ItemLocationPairing(FOREST_TEMPLE_GS_LOBBY,            []{return HookshotOrBoomerang;}),
                }, {
                  //Exits
                  ExitPairing::Both(&SFM_Main,                   []{return true;}),
                  ExitPairing::Both(&ForestTemple_NWOutdoors,    []{return CanPlay(SongOfTime) || IsChild;}),
                  ExitPairing::Both(&ForestTemple_NEOutdoors,    []{return CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Slingshot);}),
                  ExitPairing::Both(&ForestTemple_BlockPushRoom, []{return SmallKeys(ForestTempleKeys, 1);}),
                  ExitPairing::Both(&ForestTemple_BossRegion,    []{return ForestTempleJoAndBeth && ForestTempleAmyAndMeg;})
  });

  Exit ForestTemple_NWOutdoors = Exit("Forest Temple NW Outdoors", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&DekuBabaSticks, []{return DekuBabaSticks || (IsAdult || KokiriSword || Boomerang);}),
                  EventPairing(&DekuBabaNuts,   []{return DekuBabaNuts   || (IsAdult || KokiriSword || Slingshot || Sticks || HasExplosives || CanUse(CanUseItem::Dins_Fire));}),
                }, {
                  //Locations
                  ItemLocationPairing(FOREST_TEMPLE_GS_LEVEL_ISLAND_COURTYARD, []{return CanUse(CanUseItem::Longshot) || ForestTemple_OutsideUpperLedge.Here([]{return CanUse(CanUseItem::Hookshot);});}),
                }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_NEOutdoors,            []{return GoldScale;}),
                  ExitPairing::Both(&ForestTemple_OutdoorsHighBalconies, []{return ForestTemple_NWOutdoors.Here([]{return IsAdult || (HasExplosives || ((CanUse(CanUseItem::Boomerang) || Nuts || DekuShield) && (Sticks || KokiriSword || CanUse(CanUseItem::Slingshot))));});}),
  });

  Exit ForestTemple_NEOutdoors = Exit("Forest Temple NE Outdoors", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&DekuBabaSticks, []{return DekuBabaSticks || (IsAdult || KokiriSword || Boomerang);}),
                  EventPairing(&DekuBabaNuts,   []{return DekuBabaNuts   || (IsAdult || KokiriSword || Slingshot || Sticks || HasExplosives || CanUse(CanUseItem::Dins_Fire));}),
                }, {
                  //Locations
                  ItemLocationPairing(FOREST_TEMPLE_RAISED_ISLAND_COURTYARD_CHEST, []{return CanUse(CanUseItem::Hookshot) || ForestTemple_FallingRoom.HasAccess();}),
                  ItemLocationPairing(FOREST_TEMPLE_GS_RAISED_ISLAND_COURTYARD,    []{return CanUse(CanUseItem::Hookshot) ||
                                                                                          (LogicForestOutdoorEastGS && CanUse(CanUseItem::Boomerang)) ||
                                                                                          ForestTemple_FallingRoom.Here([]{return CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Dins_Fire) || HasExplosives;});}),
                }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_OutdoorsHighBalconies, []{return CanUse(CanUseItem::Longshot);}),
                  ExitPairing::Both(&ForestTemple_NWOutdoors,            []{return CanUse(CanUseItem::Iron_Boots) || ProgressiveScale >= 2;}),
                  ExitPairing::Both(&ForestTemple_Lobby,                 []{return true;})
  });

  Exit ForestTemple_OutdoorsHighBalconies = Exit("Forest Temple Outdoors High Balconies", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(FOREST_TEMPLE_WELL_CHEST, []{return true;}),
                  ItemLocationPairing(FOREST_TEMPLE_MAP_CHEST,  []{return true;})
                }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_NWOutdoors,  []{return true;}),
                  ExitPairing::Both(&ForestTemple_NEOutdoors,  []{return true;}),
                  ExitPairing::Both(&ForestTemple_FallingRoom, []{return LogicForestDoorFrame && CanUse(CanUseItem::Hover_Boots) && CanUse(CanUseItem::Scarecrow);})
  });

  Exit ForestTemple_FallingRoom = Exit("Forest Temple Falling Room", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&ForestTempleAmyAndMeg, []{return ForestTempleAmyAndMeg || CanUse(CanUseItem::Bow);}),
                }, {
                  //Locations
                  ItemLocationPairing(FOREST_TEMPLE_FALLING_CEILING_ROOM_CHEST, []{return true;})
                }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_NEOutdoors, []{return true;})
  });

  Exit ForestTemple_BlockPushRoom = Exit("Forest Temple Block Push Room", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(FOREST_TEMPLE_EYE_SWITCH_CHEST, []{return GoronBracelet && (CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Slingshot));})
                }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_OutsideUpperLedge, []{return CanUse(CanUseItem::Hover_Boots) || (LogicForestOutsideBackdoor && IsAdult && GoronBracelet);}),
                  ExitPairing::Both(&ForestTemple_BowRegion,         []{return GoronBracelet && SmallKeys(ForestTempleKeys, 3) && IsAdult;}),
                  ExitPairing::Both(&ForestTemple_StraightenedHall,  []{return GoronBracelet && SmallKeys(ForestTempleKeys, 2) && CanUse(CanUseItem::Bow) && IsAdult;})
  });

  Exit ForestTemple_StraightenedHall = Exit("Forest Temple Straightened Hall", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(FOREST_TEMPLE_BOSS_KEY_CHEST, []{return true;})
                }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_OutsideUpperLedge, []{return true;})
  });

  Exit ForestTemple_OutsideUpperLedge = Exit("Forest Temple Outside Upper Ledge", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(FOREST_TEMPLE_FLOORMASTER_CHEST, []{return true;})
                }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_NWOutdoors, []{return true;})
  });

  Exit ForestTemple_BowRegion = Exit("Forest Temple Bow Region", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&ForestTempleJoAndBeth, []{return ForestTempleJoAndBeth || CanUse(CanUseItem::Bow);}),
                }, {
                  //Locations
                  ItemLocationPairing(FOREST_TEMPLE_BOW_CHEST,      []{return true;}),
                  ItemLocationPairing(FOREST_TEMPLE_RED_POE_CHEST,  []{return CanUse(CanUseItem::Bow);}),
                  ItemLocationPairing(FOREST_TEMPLE_BLUE_POE_CHEST, []{return CanUse(CanUseItem::Bow);})
                }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_FallingRoom, []{return SmallKeys(ForestTempleKeys, 5) && (Bow || CanUse(CanUseItem::Dins_Fire));})
  });

  Exit ForestTemple_BossRegion = Exit("Forest Temple Boss Region", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&ForestTempleClear, []{return ForestTempleClear || (BossKeyForestTemple);}),
  }, {
                  //Locations
                  ItemLocationPairing(FOREST_TEMPLE_BASEMENT_CHEST,      []{return true;}),
                  ItemLocationPairing(FOREST_TEMPLE_PHANTOM_GANON_HEART, []{return BossKeyForestTemple;}),
                  ItemLocationPairing(PHANTOM_GANON,                     []{return BossKeyForestTemple;}),
                  ItemLocationPairing(FOREST_TEMPLE_GS_BASEMENT,         []{return HookshotOrBoomerang;}),
  }, {});

  //Fire Temple logic currently assumes that the lowest locked door is unlocked from the start
  Exit FireTemple_Lower = Exit("Fire Temple Lower", "Fire Temple", FIRE_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPot,        []{return FairyPot || ((CanUse(CanUseItem::Hover_Boots) || CanUse(CanUseItem::Hookshot)) && (LogicFewerTunicRequirements || CanUse(CanUseItem::Goron_Tunic)));}),
                  EventPairing(&FireTempleClear, []{return FireTempleClear || (CanUse(CanUseItem::Goron_Tunic) && CanUse(CanUseItem::Hammer) && BossKeyFireTemple &&
                                                                                (LogicFireBossDoorJump || HoverBoots ||
                                                                                  (FireTemple_Upper.Adult() && (CanPlay(SongOfTime) || HasExplosives))));})
                }, {
                  //Locations
                  ItemLocationPairing(FIRE_TEMPLE_NEAR_BOSS_CHEST,    []{return LogicFewerTunicRequirements || CanUse(CanUseItem::Goron_Tunic);}),
                  ItemLocationPairing(FIRE_TEMPLE_FLARE_DANCER_CHEST, []{return /*SmallKeys(FireTempleKeys, 8) &&*/ CanUse(CanUseItem::Hammer);}),
                  ItemLocationPairing(FIRE_TEMPLE_BOSS_KEY_CHEST,     []{return /*SmallKeys(FireTempleKeys, 8) &&*/ CanUse(CanUseItem::Hammer);}),
                  ItemLocationPairing(FIRE_TEMPLE_VOLVAGIA_HEART,     []{return CanUse(CanUseItem::Goron_Tunic) && CanUse(CanUseItem::Hammer) && BossKeyFireTemple &&
                                                                                (LogicFireBossDoorJump || HoverBoots ||
                                                                                  (FireTemple_Upper.Adult() && (CanPlay(SongOfTime) || HasExplosives)));}),
                  ItemLocationPairing(VOLVAGIA,                       []{return CanUse(CanUseItem::Goron_Tunic) && CanUse(CanUseItem::Hammer) && BossKeyFireTemple &&
                                                                                (LogicFireBossDoorJump || HoverBoots ||
                                                                                  (FireTemple_Upper.Adult() && (CanPlay(SongOfTime) || HasExplosives)));}),
                  ItemLocationPairing(FIRE_TEMPLE_GS_BOSS_KEY_LOOP,   []{return /*SmallKeys(FireTempleKeys, 8) &&*/ CanUse(CanUseItem::Hammer);}),
                }, {
                  //Exits
                  ExitPairing::Both(&FireTemple_Entrance,    []{return true;}),
                  ExitPairing::Both(&FireTemple_BigLavaRoom, []{return SmallKeys(FireTempleKeys, 1) && (LogicFewerTunicRequirements || CanUse(CanUseItem::Goron_Tunic));}),
  });

  Exit FireTemple_BigLavaRoom = Exit("Fire Temple Big Lava Room", "Fire Temple", FIRE_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(FIRE_TEMPLE_BIG_LAVA_ROOM_LOWER_OPEN_DOOR_CHEST, []{return true;}),
                  ItemLocationPairing(FIRE_TEMPLE_BIG_LAVA_ROOM_BLOCKED_DOOR_CHEST,    []{return IsAdult && HasExplosives;}),
                  ItemLocationPairing(FIRE_TEMPLE_GS_SONG_OF_TIME_ROOM,                []{return IsAdult && (CanPlay(SongOfTime) || LogicFireSongOfTime);}),
                }, {
                  //Exits
                  ExitPairing::Both(&FireTemple_Lower,  []{return true;}),
                  ExitPairing::Both(&FireTemple_Middle, []{return CanUse(CanUseItem::Goron_Tunic) && SmallKeys(FireTempleKeys, 3) && (GoronBracelet || LogicFireStrength) && (HasExplosives || Bow || Hookshot);}),
  });

  Exit FireTemple_Middle = Exit("Fire Temple Middle", "Fire Temple", FIRE_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(FIRE_TEMPLE_BOULDER_MAZE_LOWER_CHEST,     []{return true;}),
                  ItemLocationPairing(FIRE_TEMPLE_BOULDER_MAZE_UPPER_CHEST,     []{return SmallKeys(FireTempleKeys, 5);}),
                  ItemLocationPairing(FIRE_TEMPLE_BOULDER_MAZE_SIDE_ROOM_CHEST, []{return true;}),
                  ItemLocationPairing(FIRE_TEMPLE_BOULDER_MAZE_SHORTCUT_CHEST,  []{return SmallKeys(FireTempleKeys, 5) && HasExplosives;}),
                  ItemLocationPairing(FIRE_TEMPLE_SCARECROW_CHEST,              []{return SmallKeys(FireTempleKeys, 5) && (CanUse(CanUseItem::Scarecrow) || (LogicFireScarecrow && CanUse(CanUseItem::Longshot)));}),
                  ItemLocationPairing(FIRE_TEMPLE_MAP_CHEST,                    []{return SmallKeys(FireTempleKeys, 5) || (SmallKeys(FireTempleKeys, 4) && CanUse(CanUseItem::Bow));}),
                  ItemLocationPairing(FIRE_TEMPLE_COMPASS_CHEST,                []{return SmallKeys(FireTempleKeys, 6);}),
                  ItemLocationPairing(FIRE_TEMPLE_GS_BOULDER_MAZE,              []{return SmallKeys(FireTempleKeys, 4) && HasExplosives;}),
                  ItemLocationPairing(FIRE_TEMPLE_GS_SCARECROW_CLIMB,           []{return SmallKeys(FireTempleKeys, 5) && (CanUse(CanUseItem::Scarecrow) || (LogicFireScarecrow && CanUse(CanUseItem::Longshot)));}),
                  ItemLocationPairing(FIRE_TEMPLE_GS_SCARECROW_TOP,             []{return SmallKeys(FireTempleKeys, 5) && (CanUse(CanUseItem::Scarecrow) || (LogicFireScarecrow && CanUse(CanUseItem::Longshot)));}),
                }, {
                  //Exits
                  ExitPairing::Both(&FireTemple_Upper, []{return SmallKeys(FireTempleKeys, 7) || (SmallKeys(FireTempleKeys, 6) && ((CanUse(CanUseItem::Hover_Boots) && CanUse(CanUseItem::Hammer)) || LogicFireFlameMaze));})
  });

  Exit FireTemple_Upper = Exit("Fire Temple Upper", "Fire Temple", FIRE_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(FIRE_TEMPLE_HIGHEST_GORON_CHEST,  []{return CanUse(CanUseItem::Hammer) && CanPlay(SongOfTime);}),
                  ItemLocationPairing(FIRE_TEMPLE_MEGATON_HAMMER_CHEST, []{return HasExplosives;}),
  }, {});

  //Water Temple logic currently assumes that the locked door leading to the upper water raising location is unlocked from the start
  Exit WaterTemple_Lobby = Exit("Water Temple Lobby", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&ChildWaterTemple, []{return IsChild;}),
                  EventPairing(&RaiseWaterLevel,  []{return (IsAdult && ((Hookshot && (LogicWaterTempleUpperBoost && Bombs && CanTakeDamage)) || HoverBoots || Bow)) || (HasFireSourceWithTorch && CanUseProjectile);}),
                }, {}, {
                  //Exits
                  ExitPairing::Both(&LH_Main,                       []{return true;}),
                  ExitPairing::Both(&WaterTemple_HighestWaterLevel, []{return RaiseWaterLevel;}),
                  ExitPairing::Both(&WaterTemple_Dive,              []{return (CanUse(CanUseItem::Zora_Tunic) || LogicFewerTunicRequirements) && ((LogicWaterTempleTorchLongshot && CanUse(CanUseItem::Longshot)) || CanUse(CanUseItem::Iron_Boots));}),
  });

  Exit WaterTemple_HighestWaterLevel = Exit("Water Temple Highest Water Level", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPot,         []{return FairyPot         || CanUse(CanUseItem::Longshot);}),
                  EventPairing(&WaterTempleClear, []{return WaterTempleClear || (BossKeyWaterTemple && CanUse(CanUseItem::Longshot));})
                }, {
                  //Locations
                  ItemLocationPairing(MORPHA,                    []{return BossKeyWaterTemple && CanUse(CanUseItem::Longshot);}),
                  ItemLocationPairing(WATER_TEMPLE_MORPHA_HEART, []{return BossKeyWaterTemple && CanUse(CanUseItem::Longshot);}),
                }, {
                  //Exits
                  ExitPairing::Both(&WaterTemple_FallingPlatformRoom, []{return SmallKeys(WaterTempleKeys, 4);}),

  });

  Exit WaterTemple_Dive = Exit("Water Temple Dive", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(WATER_TEMPLE_MAP_CHEST,                []{return RaiseWaterLevel;}),
                  ItemLocationPairing(WATER_TEMPLE_COMPASS_CHEST,            []{return (CanPlay(ZeldasLullaby) || IronBoots) && CanUse(CanUseItem::Hookshot);}),
                  ItemLocationPairing(WATER_TEMPLE_TORCHES_CHEST,            []{return (Bow || CanUse(CanUseItem::Dins_Fire) || (ChildWaterTemple && Sticks && KokiriSword && MagicMeter)) && CanPlay(ZeldasLullaby);}),
                  ItemLocationPairing(WATER_TEMPLE_CENTRAL_BOW_TARGET_CHEST, []{return GoronBracelet && CanPlay(ZeldasLullaby) &&
                                                                                    ((Bow && (LogicWaterCentralBow || HoverBoots || CanUse(CanUseItem::Longshot))) ||
                                                                                      (LogicWaterCentralBow && ChildWaterTemple && Slingshot && WaterTemple_MiddleWaterLevel.HasAccess()));}),
                  ItemLocationPairing(WATER_TEMPLE_GS_BEHIND_GATE,           []{return (CanUse(CanUseItem::Hookshot) || CanUse(CanUseItem::Hover_Boots)) &&
                                                                                    (HasExplosives && CanPlay(ZeldasLullaby)) &&
                                                                                    (CanUse(CanUseItem::Iron_Boots) || CanDive);}),
                  ItemLocationPairing(WATER_TEMPLE_GS_CENTRAL_PILLAR,        []{return CanPlay(ZeldasLullaby) &&
                                                                                      (((CanUse(CanUseItem::Longshot) || (LogicWaterCentralGSFW && CanUse(CanUseItem::Hookshot) && CanUse(CanUseItem::Farores_Wind))) &&
                                                                                        (SmallKeys(WaterTempleKeys, 5) || CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Dins_Fire))) ||
                                                                                      (LogicWaterCentralGSFW && ChildWaterTemple && Boomerang && CanUse(CanUseItem::Farores_Wind) &&
                                                                                        (Sticks || CanUse(CanUseItem::Dins_Fire) ||
                                                                                        (SmallKeys(WaterTempleKeys, 5) && (CanUse(CanUseItem::Hover_Boots) || CanUse(CanUseItem::Bow))))));}),
                }, {
                  //Exits
                  ExitPairing::Both(&WaterTemple_CrackedWall,      []{return CanPlay(ZeldasLullaby) && (CanUse(CanUseItem::Hookshot) || CanUse(CanUseItem::Hover_Boots)) && (LogicWaterCrackedWallNothing || (LogicWaterCrackedWallHovers && CanUse(CanUseItem::Hover_Boots)));}),
                  ExitPairing::Both(&WaterTemple_MiddleWaterLevel, []{return (Bow || CanUse(CanUseItem::Dins_Fire) || (SmallKeys(WaterTempleKeys, 5) && CanUse(CanUseItem::Hookshot)) || (ChildWaterTemple && Sticks)) && CanPlay(ZeldasLullaby);}),
                  ExitPairing::Both(&WaterTemple_NorthBasement,    []{return SmallKeys(WaterTempleKeys, 5) && (CanUse(CanUseItem::Longshot) || (LogicWaterBossKeyRegion && CanUse(CanUseItem::Hover_Boots))) && (CanUse(CanUseItem::Iron_Boots) || CanPlay(ZeldasLullaby));}),
                  ExitPairing::Both(&WaterTemple_DragonStatue,     []{return CanPlay(ZeldasLullaby) && GoronBracelet &&
                                                                                ((IronBoots && CanUse(CanUseItem::Hookshot)) ||
                                                                                (LogicWaterDragonAdult && (HasBombchus || CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Hookshot)) && (CanDive || IronBoots)));}),
  });

  Exit WaterTemple_NorthBasement = Exit("Water Temple North Basement", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPot, []{return FairyPot || (SmallKeys(WaterTempleKeys, 5) && (LogicWaterBKJumpDive || CanUse(CanUseItem::Iron_Boots)) && (LogicWaterNorthBasementLedgeJump || (HasExplosives && GoronBracelet) || HoverBoots));}),
                }, {
                  //Locations
                  ItemLocationPairing(WATER_TEMPLE_BOSS_KEY_CHEST,         []{return SmallKeys(WaterTempleKeys, 5) && (LogicWaterBKJumpDive || CanUse(CanUseItem::Iron_Boots)) && (LogicWaterNorthBasementLedgeJump || (HasExplosives && GoronBracelet) || HoverBoots);}),
                  ItemLocationPairing(WATER_TEMPLE_GS_NEAR_BOSS_KEY_CHEST, []{return true;}),
  }, {});

  Exit WaterTemple_CrackedWall = Exit("Water Temple Cracked Wall", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(WATER_TEMPLE_CRACKED_WALL_CHEST, []{return HasExplosives;}),
  }, {});

  Exit WaterTemple_DragonStatue = Exit("Water Temple Dragon Statue", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(WATER_TEMPLE_DRAGON_CHEST, []{return true;}),
  }, {});

  Exit WaterTemple_MiddleWaterLevel = Exit("Water Temple Middle Water Level", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(WATER_TEMPLE_CENTRAL_PILLAR_CHEST, []{return CanUse(CanUseItem::Zora_Tunic) && CanUse(CanUseItem::Hookshot) && ((SmallKeys(WaterTempleKeys, 5) || CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Dins_Fire)));}),
                }, {
                  //Exits
                  ExitPairing::Both(&WaterTemple_CrackedWall, []{return true;}),
  });

  Exit WaterTemple_FallingPlatformRoom = Exit("Water Temple Falling Platform Room", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(WATER_TEMPLE_GS_FALLING_PLATFORM_ROOM, []{return CanUse(CanUseItem::Longshot) || (LogicWaterFallingPlatformGS && CanUse(CanUseItem::Hookshot));}),
                }, {
                  //Exits
                  ExitPairing::Both(&WaterTemple_DarkLinkRegion, []{return SmallKeys(WaterTempleKeys, 5) && CanUse(CanUseItem::Hookshot);}),
  });

  Exit WaterTemple_DarkLinkRegion = Exit("Water Temple Dark Link Region", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPot, []{return FairyPot || (SmallKeys(WaterTempleKeys, 5) && CanPlay(SongOfTime));}),
                }, {
                  //Locations
                  ItemLocationPairing(WATER_TEMPLE_LONGSHOT_CHEST, []{return SmallKeys(WaterTempleKeys, 5);}),
                  ItemLocationPairing(WATER_TEMPLE_RIVER_CHEST,    []{return SmallKeys(WaterTempleKeys, 5) && CanPlay(SongOfTime) && Bow;}),
                  ItemLocationPairing(WATER_TEMPLE_GS_RIVER,       []{return CanPlay(SongOfTime) && SmallKeys(WaterTempleKeys, 5) && (IronBoots || (LogicWaterRiverGS && CanUse(CanUseItem::Longshot) && (Bow || HasBombchus)));}),
                }, {
                  //Exits
                  ExitPairing::Both(&WaterTemple_DragonStatue, []{return (CanUse(CanUseItem::Zora_Tunic) || LogicFewerTunicRequirements) &&
                                                                         CanPlay(SongOfTime) && Bow &&
                                                                         (IronBoots || LogicWaterDragonJumpDive || LogicWaterDragonAdult);}),
  });

  Exit SpiritTemple_Lobby = Exit("Spirit Temple Lobby", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&Colossus_Main,           []{return true;}),
                  ExitPairing::Both(&SpiritTemple_Child,      []{return IsChild;}),
                  ExitPairing::Both(&SpiritTemple_EarlyAdult, []{return CanUse(CanUseItem::Silver_Gauntlets);}),
  });

  Exit SpiritTemple_Child = Exit("Child Spirit Temple", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&NutCrate, []{return true;}),
                }, {
                  //Locations
                  ItemLocationPairing(SPIRIT_TEMPLE_CHILD_BRIDGE_CHEST,        []{return (Boomerang || Slingshot || (HasExplosives && LogicSpiritChildBombchu)) && (Sticks || HasExplosives || ((Nuts || Boomerang) && (KokiriSword || Slingshot)));}),
                  ItemLocationPairing(SPIRIT_TEMPLE_CHILD_EARLY_TORCHES_CHEST, []{return (Boomerang || Slingshot || (HasExplosives && LogicSpiritChildBombchu)) && (Sticks || HasExplosives || ((Nuts || Boomerang) && (KokiriSword || Slingshot))) && (Sticks || CanUse(CanUseItem::Dins_Fire));}),
                  ItemLocationPairing(SPIRIT_TEMPLE_GS_METAL_FENCE,            []{return (Boomerang || Slingshot || (HasExplosives && LogicSpiritChildBombchu)) && (Sticks || HasExplosives || ((Nuts || Boomerang) && (KokiriSword || Slingshot)));}),
                }, {
                  //Exits
                  ExitPairing::Both(&SpiritTemple_ChildClimb, []{return SmallKeys(SpiritTempleKeys, 1);}),
  });

  Exit SpiritTemple_ChildClimb = Exit("Child Spirit Temple Climb", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(SPIRIT_TEMPLE_CHILD_CLIMB_NORTH_CHEST, []{return HasProjectile(HasProjectileAge::Both) || ((SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && !ShuffleDungeonEntrances)) && CanUse(CanUseItem::Silver_Gauntlets) && HasProjectile(HasProjectileAge::Adult)) || (SmallKeys(SpiritTempleKeys, 5) && IsChild && HasProjectile(HasProjectileAge::Child));}),
                  ItemLocationPairing(SPIRIT_TEMPLE_CHILD_CLIMB_EAST_CHEST,  []{return HasProjectile(HasProjectileAge::Both) || ((SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && !ShuffleDungeonEntrances)) && CanUse(CanUseItem::Silver_Gauntlets) && HasProjectile(HasProjectileAge::Adult)) || (SmallKeys(SpiritTempleKeys, 5) && IsChild && HasProjectile(HasProjectileAge::Child));}),
                  ItemLocationPairing(SPIRIT_TEMPLE_GS_SUN_ON_FLOOR_ROOM,    []{return HasProjectile(HasProjectileAge::Both) || CanUse(CanUseItem::Dins_Fire) ||
                                                                                      (CanTakeDamage && (Sticks || KokiriSword || HasProjectile(HasProjectileAge::Child))) ||
                                                                                        (IsChild && SmallKeys(SpiritTempleKeys, 5) && HasProjectile(HasProjectileAge::Child)) ||
                                                                                          ((SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && !ShuffleDungeonEntrances)) && CanUse(CanUseItem::Silver_Gauntlets) && (HasProjectile(HasProjectileAge::Adult) || CanTakeDamage));}),
                }, {
                  //Exits
                  ExitPairing::Both(&SpiritTemple_CentralChamber, []{return HasExplosives;}),
  });

  Exit SpiritTemple_EarlyAdult = Exit("Early Adult Spirit Temple", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(SPIRIT_TEMPLE_COMPASS_CHEST,            []{return CanUse(CanUseItem::Hookshot) && CanPlay(ZeldasLullaby);}),
                  ItemLocationPairing(SPIRIT_TEMPLE_EARLY_ADULT_RIGHT_CHEST,  []{return Bow || Hookshot || HasBombchus || (Bombs && LogicSpiritLowerAdultSwitch);}),
                  ItemLocationPairing(SPIRIT_TEMPLE_FIRST_MIRROR_LEFT_CHEST,  []{return SmallKeys(SpiritTempleKeys, 3);}),
                  ItemLocationPairing(SPIRIT_TEMPLE_FIRST_MIRROR_RIGHT_CHEST, []{return SmallKeys(SpiritTempleKeys, 3);}),
                  ItemLocationPairing(SPIRIT_TEMPLE_GS_BOULDER_ROOM,          []{return CanPlay(SongOfTime) && (Bow || Hookshot || HasBombchus || (Bombs && LogicSpiritLowerAdultSwitch));}),
                }, {
                  //Exits
                  ExitPairing::Both(&SpiritTemple_CentralChamber, []{return SmallKeys(SpiritTempleKeys, 1);}),
  });

  Exit SpiritTemple_CentralChamber = Exit("Spirit Temple Central Chamber", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(SPIRIT_TEMPLE_MAP_CHEST,                    []{return ((HasExplosives || SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && !ShuffleDungeonEntrances)) &&
                                                                                                (CanUse(CanUseItem::Dins_Fire) ||
                                                                                                    (((MagicMeter && FireArrows) || LogicSpiritMapChest) && Bow && Sticks))) ||
                                                                                            (SmallKeys(SpiritTempleKeys, 5) && HasExplosives &&
                                                                                                CanUse(CanUseItem::Sticks)) ||
                                                                                            (SmallKeys(SpiritTempleKeys, 3) &&
                                                                                                (CanUse(CanUseItem::Fire_Arrows) || (LogicSpiritMapChest && Bow)) &&
                                                                                                CanUse(CanUseItem::Silver_Gauntlets));}),
                  ItemLocationPairing(SPIRIT_TEMPLE_SUN_BLOCK_ROOM_CHEST,         []{return ((HasExplosives || SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && !ShuffleDungeonEntrances)) &&
                                                                                                (CanUse(CanUseItem::Dins_Fire) ||
                                                                                                    (((MagicMeter && FireArrows) || LogicSpiritMapChest) && Bow && Sticks))) ||
                                                                                            (SmallKeys(SpiritTempleKeys, 5) && HasExplosives &&
                                                                                                CanUse(CanUseItem::Sticks)) ||
                                                                                            (SmallKeys(SpiritTempleKeys, 3) &&
                                                                                                (CanUse(CanUseItem::Fire_Arrows) || (LogicSpiritMapChest && Bow)) &&
                                                                                                CanUse(CanUseItem::Silver_Gauntlets));}),
                  ItemLocationPairing(SPIRIT_TEMPLE_STATUE_ROOM_HAND_CHEST,       []{return SmallKeys(SpiritTempleKeys, 3) && CanUse(CanUseItem::Silver_Gauntlets) && CanPlay(ZeldasLullaby);}),
                  ItemLocationPairing(SPIRIT_TEMPLE_STATUE_ROOM_NORTHEAST_CHEST,  []{return SmallKeys(SpiritTempleKeys, 3) && CanUse(CanUseItem::Silver_Gauntlets) && CanPlay(ZeldasLullaby) && (Hookshot || HoverBoots);}),
                  ItemLocationPairing(SPIRIT_TEMPLE_GS_HALL_AFTER_SUN_BLOCK_ROOM, []{return (HasExplosives && Boomerang && Hookshot) ||
                                                                                            (CanUse(CanUseItem::Boomerang) && SmallKeys(SpiritTempleKeys, 5) && HasExplosives) ||
                                                                                            (Hookshot && CanUse(CanUseItem::Silver_Gauntlets) &&
                                                                                                (SmallKeys(SpiritTempleKeys, 3) ||
                                                                                                    (SmallKeys(SpiritTempleKeys, 2) && Boomerang && BombchusInLogic && !ShuffleDungeonEntrances)));}),
                  ItemLocationPairing(SPIRIT_TEMPLE_GS_LOBBY,                     []{return ((HasExplosives || SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && !ShuffleDungeonEntrances)) &&
                                                                                                LogicSpiritLobbyGS && Boomerang && (Hookshot || HoverBoots)) ||
                                                                                            (LogicSpiritLobbyGS && SmallKeys(SpiritTempleKeys, 5) && HasExplosives && CanUse(CanUseItem::Boomerang)) ||
                                                                                            (SmallKeys(SpiritTempleKeys, 3) && CanUse(CanUseItem::Silver_Gauntlets) && (Hookshot || HoverBoots));}),
                }, {
                  //Exits
                  ExitPairing::Both(&SpiritTemple_OutdoorHands,            []{return true;}),
                  ExitPairing::Both(&SpiritTemple_BeyondCentralLockedDoor, []{return SmallKeys(SpiritTempleKeys, 4) && CanUse(CanUseItem::Silver_Gauntlets);}),
                  ExitPairing::Both(&SpiritTemple_ChildClimb,              []{return true;}),
  });

  Exit SpiritTemple_OutdoorHands = Exit("Spirit Temple Outdoor Hands", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(SPIRIT_TEMPLE_SILVER_GAUNTLETS_CHEST, []{return (SmallKeys(SpiritTempleKeys, 3) && Longshot && HasExplosives) || SmallKeys(SpiritTempleKeys, 5);}),
                  ItemLocationPairing(SPIRIT_TEMPLE_MIRROR_SHIELD_CHEST,    []{return SmallKeys(SpiritTempleKeys, 4) && CanUse(CanUseItem::Silver_Gauntlets) && HasExplosives;}),
                }, {
                  //Exits
                  ExitPairing::Both(&Colossus_Main, []{return (IsChild && SmallKeys(SpiritTempleKeys, 5)) || (CanUse(CanUseItem::Silver_Gauntlets) && ((SmallKeys(SpiritTempleKeys, 3) && HasExplosives) || SmallKeys(SpiritTempleKeys, 5)));}),
  });

  Exit SpiritTemple_BeyondCentralLockedDoor = Exit("Spirit Temple Beyond Central Locked Door", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(SPIRIT_TEMPLE_NEAR_FOUR_ARMOS_CHEST,         []{return MirrorShield && HasExplosives;}),
                  ItemLocationPairing(SPIRIT_TEMPLE_HALLWAY_LEFT_INVISIBLE_CHEST,  []{return (LogicLensSpirit || CanUse(CanUseItem::Lens_of_Truth)) && HasExplosives;}),
                  ItemLocationPairing(SPIRIT_TEMPLE_HALLWAY_RIGHT_INVISIBLE_CHEST, []{return (LogicLensSpirit || CanUse(CanUseItem::Lens_of_Truth)) && HasExplosives;}),
                }, {
                  //Exits
                  ExitPairing::Both(&SpiritTemple_BeyondFinalLockedDoor, []{return SmallKeys(SpiritTempleKeys, 5) && (LogicSpiritWall || CanUse(CanUseItem::Longshot) || HasBombchus || ((Bombs || Nuts || CanUse(CanUseItem::Dins_Fire)) && (Bow || CanUse(CanUseItem::Hookshot) || Hammer)));}),
  });

  Exit SpiritTemple_BeyondFinalLockedDoor = Exit("Spirit Temple Beyond Final Locked Door", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&SpiritTempleClear, []{return SpiritTempleClear || (MirrorShield && HasExplosives && Hookshot && BossKeySpiritTemple);}),
  }, {
                  //Locations
                  ItemLocationPairing(SPIRIT_TEMPLE_BOSS_KEY_CHEST, []{return CanPlay(ZeldasLullaby) && Bow && Hookshot;}),
                  ItemLocationPairing(SPIRIT_TEMPLE_TOPMOST_CHEST,  []{return MirrorShield;}),
                  ItemLocationPairing(SPIRIT_TEMPLE_TWINROVA_HEART, []{return MirrorShield && HasExplosives && Hookshot && BossKeySpiritTemple;}),
                  ItemLocationPairing(TWINROVA,                     []{return MirrorShield && HasExplosives && Hookshot && BossKeySpiritTemple;}),
  }, {});

  Exit ShadowTemple_Entryway = Exit("Shadow Temple Entryway", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&GY_WarpPadRegion,       []{return true;}),
                  ExitPairing::Both(&ShadowTemple_Beginning, []{return (LogicLensShadow || CanUse(CanUseItem::Lens_of_Truth)) && (CanUse(CanUseItem::Hover_Boots) || CanUse(CanUseItem::Hookshot));}),
  });

  Exit ShadowTemple_Beginning = Exit("Shadow Temple Beginning", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&NutPot, []{return true;}),
                }, {
                  //Locations
                  ItemLocationPairing(SHADOW_TEMPLE_MAP_CHEST,         []{return true;}),
                  ItemLocationPairing(SHADOW_TEMPLE_HOVER_BOOTS_CHEST, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&ShadowTemple_Entryway,    []{return true;}),
                  ExitPairing::Both(&ShadowTemple_FirstBeamos, []{return HoverBoots;}),
  });

  Exit ShadowTemple_FirstBeamos = Exit("Shadow Temple First Beamos", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPot, []{return true;}), //This fairy pot is only on 3DS
                }, {
                  //Locations
                  ItemLocationPairing(SHADOW_TEMPLE_COMPASS_CHEST,            []{return true;}),
                  ItemLocationPairing(SHADOW_TEMPLE_EARLY_SILVER_RUPEE_CHEST, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&ShadowTemple_HugePit, []{return HasExplosives && SmallKeys(ShadowTempleKeys, 1);})
  });

  Exit ShadowTemple_HugePit = Exit("Shadow Temple Huge Pit", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(SHADOW_TEMPLE_INVISIBLE_BLADES_VISIBLE_CHEST,   []{return true;}),
                  ItemLocationPairing(SHADOW_TEMPLE_INVISIBLE_BLADES_INVISIBLE_CHEST, []{return true;}),
                  ItemLocationPairing(SHADOW_TEMPLE_FALLING_SPIKES_LOWER_CHEST,       []{return true;}),
                  ItemLocationPairing(SHADOW_TEMPLE_FALLING_SPIKES_UPPER_CHEST,       []{return LogicShadowUmbrella || GoronBracelet;}),
                  ItemLocationPairing(SHADOW_TEMPLE_FALLING_SPIKES_SWITCH_CHEST,      []{return LogicShadowUmbrella || GoronBracelet;}),
                  ItemLocationPairing(SHADOW_TEMPLE_INVISIBLE_SPIKES_CHEST,           []{return SmallKeys(ShadowTempleKeys, 2) && (LogicLensShadowBack || CanUse(CanUseItem::Lens_of_Truth));}),
                  ItemLocationPairing(SHADOW_TEMPLE_FREESTANDING_KEY,                 []{return SmallKeys(ShadowTempleKeys, 2) && (LogicLensShadowBack || CanUse(CanUseItem::Lens_of_Truth)) && Hookshot && (Bombs || GoronBracelet || (LogicShadowFreestandingKey && HasBombchus));}),
                  ItemLocationPairing(SHADOW_TEMPLE_GS_LIKE_LIKE_ROOM,                []{return true;}),
                  ItemLocationPairing(SHADOW_TEMPLE_GS_FALLING_SPIKES_ROOM,           []{return Hookshot;}),
                  ItemLocationPairing(SHADOW_TEMPLE_GS_SINGLE_GIANT_POT,              []{return SmallKeys(ShadowTempleKeys, 2) && (LogicLensShadowBack || CanUse(CanUseItem::Lens_of_Truth)) && Hookshot;}),
                }, {
                  //Exits
                  ExitPairing::Both(&ShadowTemple_WindTunnel, []{return (LogicLensShadowBack || CanUse(CanUseItem::Lens_of_Truth)) && Hookshot && SmallKeys(ShadowTempleKeys, 3);}),
  });

  Exit ShadowTemple_WindTunnel = Exit("Shadow Temple Wind Tunnel", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(SHADOW_TEMPLE_WIND_HINT_CHEST,         []{return true;}),
                  ItemLocationPairing(SHADOW_TEMPLE_AFTER_WIND_ENEMY_CHEST,  []{return true;}),
                  ItemLocationPairing(SHADOW_TEMPLE_AFTER_WIND_HIDDEN_CHEST, []{return true;}),
                  ItemLocationPairing(SHADOW_TEMPLE_GS_NEAR_SHIP,            []{return CanUse(CanUseItem::Longshot) && SmallKeys(ShadowTempleKeys, 4);}),
                }, {
                  //Exits
                  ExitPairing::Both(&ShadowTemple_BeyondBoat, []{return CanPlay(ZeldasLullaby) && SmallKeys(ShadowTempleKeys, 4);}),
  });

  Exit ShadowTemple_BeyondBoat = Exit("Shadow Temple Beyond Boat", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&ShadowTempleClear, []{return ShadowTempleClear || (SmallKeys(ShadowTempleKeys, 5) && BossKeyShadowTemple && (Bow || CanUse(CanUseItem::Distant_Scarecrow) || (LogicShadowStatue && HasBombchus)));}),
  }, {
                  //Locations
                  ItemLocationPairing(SHADOW_TEMPLE_SPIKE_WALLS_LEFT_CHEST,      []{return CanUse(CanUseItem::Dins_Fire);}),
                  ItemLocationPairing(SHADOW_TEMPLE_BOSS_KEY_CHEST,              []{return CanUse(CanUseItem::Dins_Fire);}),
                  ItemLocationPairing(SHADOW_TEMPLE_INVISIBLE_FLOORMASTER_CHEST, []{return true;}),
                  ItemLocationPairing(SHADOW_TEMPLE_BONGO_BONGO_HEART,           []{return SmallKeys(ShadowTempleKeys, 5) && BossKeyShadowTemple && (Bow || CanUse(CanUseItem::Distant_Scarecrow) || (LogicShadowStatue && HasBombchus));}),
                  ItemLocationPairing(BONGO_BONGO,                               []{return SmallKeys(ShadowTempleKeys, 5) && BossKeyShadowTemple && (Bow || CanUse(CanUseItem::Distant_Scarecrow) || (LogicShadowStatue && HasBombchus));}),
                  ItemLocationPairing(SHADOW_TEMPLE_GS_TRIPLE_GIANT_POT,         []{return true;}),
  }, {});

  Exit BottomOfTheWell = Exit("Bottom of the Well", "Bottom of the Well", BOTTOM_OF_THE_WELL, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&Kak_Main,                 []{return true;}),
                  ExitPairing::Both(&BottomOfTheWell_MainArea, []{return IsChild && (CanChildAttack || Nuts);}),
  });

  Exit BottomOfTheWell_MainArea = Exit("Bottom of the Well Main Area", "Bottom of the Well", BOTTOM_OF_THE_WELL, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&StickPot, []{return true;}),
                  EventPairing(&NutPot,   []{return true;}),
                }, {
                  //Locations
                  ItemLocationPairing(BOTTOM_OF_THE_WELL_FRONT_LEFT_FAKE_WALL_CHEST,   []{return LogicLensBotw || CanUse(CanUseItem::Lens_of_Truth);}),
                  ItemLocationPairing(BOTTOM_OF_THE_WELL_FRONT_CENTER_BOMBABLE_CHEST,  []{return HasExplosives;}),
                  ItemLocationPairing(BOTTOM_OF_THE_WELL_RIGHT_BOTTOM_FAKE_WALL_CHEST, []{return LogicLensBotw || CanUse(CanUseItem::Lens_of_Truth);}),
                  ItemLocationPairing(BOTTOM_OF_THE_WELL_COMPASS_CHEST,                []{return LogicLensBotw || CanUse(CanUseItem::Lens_of_Truth);}),
                  ItemLocationPairing(BOTTOM_OF_THE_WELL_CENTER_SKULLTULA_CHEST,       []{return LogicLensBotw || CanUse(CanUseItem::Lens_of_Truth);}),
                  ItemLocationPairing(BOTTOM_OF_THE_WELL_BACK_LEFT_BOMBABLE_CHEST,     []{return (LogicLensBotw || CanUse(CanUseItem::Lens_of_Truth)) && HasExplosives;}),
                  ItemLocationPairing(BOTTOM_OF_THE_WELL_FREESTANDING_KEY,             []{return Sticks || CanUse(CanUseItem::Dins_Fire);}),
                  ItemLocationPairing(BOTTOM_OF_THE_WELL_LENS_OF_TRUTH_CHEST,          []{return CanPlay(ZeldasLullaby) && (KokiriSword || (Sticks && LogicChildDeadhand));}),
                  ItemLocationPairing(BOTTOM_OF_THE_WELL_INVISIBLE_CHEST,              []{return CanPlay(ZeldasLullaby) && (LogicLensBotw || CanUse(CanUseItem::Lens_of_Truth));}),
                  ItemLocationPairing(BOTTOM_OF_THE_WELL_UNDERWATER_FRONT_CHEST,       []{return CanPlay(ZeldasLullaby);}),
                  ItemLocationPairing(BOTTOM_OF_THE_WELL_UNDERWATER_LEFT_CHEST,        []{return CanPlay(ZeldasLullaby);}),
                  ItemLocationPairing(BOTTOM_OF_THE_WELL_MAP_CHEST,                    []{return HasExplosives || (((SmallKeys(BottomOfTheWellKeys, 3) && (LogicLensBotw || CanUse(CanUseItem::Lens_of_Truth))) || CanUse(CanUseItem::Dins_Fire)) && GoronBracelet);}),
                  ItemLocationPairing(BOTTOM_OF_THE_WELL_FIRE_KEESE_CHEST,             []{return SmallKeys(BottomOfTheWellKeys, 3) && (LogicLensBotw || CanUse(CanUseItem::Lens_of_Truth));}),
                  ItemLocationPairing(BOTTOM_OF_THE_WELL_LIKE_LIKE_CHEST,              []{return SmallKeys(BottomOfTheWellKeys, 3) && (LogicLensBotw || CanUse(CanUseItem::Lens_of_Truth));}),
                  ItemLocationPairing(BOTTOM_OF_THE_WELL_GS_WEST_INNER_ROOM,           []{return Boomerang && (LogicLensBotw || CanUse(CanUseItem::Lens_of_Truth)) && SmallKeys(BottomOfTheWellKeys, 3);}),
                  ItemLocationPairing(BOTTOM_OF_THE_WELL_GS_EAST_INNER_ROOM,           []{return Boomerang && (LogicLensBotw || CanUse(CanUseItem::Lens_of_Truth)) && SmallKeys(BottomOfTheWellKeys, 3);}),
                  ItemLocationPairing(BOTTOM_OF_THE_WELL_GS_LIKE_LIKE_CAGE,            []{return SmallKeys(BottomOfTheWellKeys, 3) && (LogicLensBotw || CanUse(CanUseItem::Lens_of_Truth)) && Boomerang;}),
                }, {
                  //Exits
                  ExitPairing::Both(&BottomOfTheWell, []{return true;}),
  });

  Exit IceCavern_Beginning = Exit("Ice Cavern Beginning", "Ice Cavern", ICE_CAVERN, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&ZF_Main,        []{return true;}),
                  ExitPairing::Both(&IceCavern_Main, []{return IceCavern_Beginning.Here([]{return IsAdult || HasExplosives || CanUse(CanUseItem::Dins_Fire);});}),
  });

  Exit IceCavern_Main = Exit("Ice Cavern", "Ice Cavern", ICE_CAVERN, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&BlueFireAccess, []{return BlueFireAccess || (IsAdult && HasBottle);}),
                }, {
                  //Locations
                  ItemLocationPairing(ICE_CAVERN_MAP_CHEST,               []{return BlueFire && IsAdult;}),
                  ItemLocationPairing(ICE_CAVERN_COMPASS_CHEST,           []{return BlueFire;}),
                  ItemLocationPairing(ICE_CAVERN_IRON_BOOTS_CHEST,        []{return BlueFire && (IsAdult || Slingshot || Sticks || KokiriSword || CanUse(CanUseItem::Dins_Fire));}),
                  ItemLocationPairing(SHEIK_IN_ICE_CAVERN,                []{return BlueFire && (IsAdult || Slingshot || Sticks || KokiriSword || CanUse(CanUseItem::Dins_Fire));}),
                  ItemLocationPairing(ICE_CAVERN_FREESTANDING_POH,        []{return BlueFire;}),
                  ItemLocationPairing(ICE_CAVERN_GS_SPINNING_SCYTHE_ROOM, []{return HookshotOrBoomerang;}),
                  ItemLocationPairing(ICE_CAVERN_GS_HEART_PIECE_ROOM,     []{return BlueFire && HookshotOrBoomerang;}),
                  ItemLocationPairing(ICE_CAVERN_GS_PUSH_BLOCK_ROOM,      []{return BlueFire && HookshotOrBoomerang;}),
  }, {});

  Exit GerudoTrainingGrounds_Lobby = Exit ("Gerudo Training Grounds Lobby", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_LOBBY_LEFT_CHEST,  []{return CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Slingshot);}),
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_LOBBY_RIGHT_CHEST, []{return CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Slingshot);}),
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_STALFOS_CHEST,    []{return IsAdult || KokiriSword;}),
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_BEAMOS_CHEST,     []{return HasExplosives && (IsAdult || KokiriSword);}),
                }, {
                  //Exits
                  ExitPairing::Both(&GF_Main,                              []{return true;}),
                  ExitPairing::Both(&GerudoTrainingGrounds_HeavyBlockRoom, []{return (IsAdult || KokiriSword) && (CanUse(CanUseItem::Hookshot) || LogicGtgWithoutHookshot);}),
                  ExitPairing::Both(&GerudoTrainingGrounds_LavaRoom,       []{return GerudoTrainingGrounds_Lobby.Here([]{return (IsAdult || KokiriSword) && HasExplosives;});}),
                  ExitPairing::Both(&GerudoTrainingGrounds_CentralMaze,    []{return true;}),
  });

  Exit GerudoTrainingGrounds_CentralMaze = Exit ("Gerudo Training Grounds Central Maze", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_HIDDEN_CEILING_CHEST,   []{return SmallKeys(GerudoTrainingGroundsKeys, 3) && (LogicLensGtg || CanUse(CanUseItem::Lens_of_Truth));}),
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_MAZE_PATH_FIRST_CHEST,  []{return SmallKeys(GerudoTrainingGroundsKeys, 4);}),
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_MAZE_PATH_SECOND_CHEST, []{return SmallKeys(GerudoTrainingGroundsKeys, 6);}),
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_MAZE_PATH_THIRD_CHEST,  []{return SmallKeys(GerudoTrainingGroundsKeys, 7);}),
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_MAZE_PATH_FINAL_CHEST,  []{return SmallKeys(GerudoTrainingGroundsKeys, 9);}),
                }, {
                  //Exits
                  ExitPairing::Both(&GerudoTrainingGrounds_CentralMazeRight, []{return SmallKeys(GerudoTrainingGroundsKeys, 9);}),
  });

  Exit GerudoTrainingGrounds_CentralMazeRight = Exit("Gerudo Training Grounds Central Maze Right", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_MAZE_RIGHT_CENTRAL_CHEST, []{return true;}),
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_MAZE_RIGHT_SIDE_CHEST,    []{return true;}),
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_FREESTANDING_KEY,         []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&GerudoTrainingGrounds_HammerRoom, []{return CanUse(CanUseItem::Hookshot);}),
                  ExitPairing::Both(&GerudoTrainingGrounds_LavaRoom,   []{return true;}),
  });

  Exit GerudoTrainingGrounds_LavaRoom = Exit("Gerudo Training Grounds Lava Room", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_UNDERWATER_SILVER_RUPEE_CHEST, []{return CanUse(CanUseItem::Hookshot) && CanPlay(SongOfTime) && IronBoots && (LogicFewerTunicRequirements || CanUse(CanUseItem::Zora_Tunic));}),
                }, {
                  //Exits
                  ExitPairing::Both(&GerudoTrainingGrounds_CentralMazeRight, []{return CanPlay(SongOfTime) || IsChild;}),
                  ExitPairing::Both(&GerudoTrainingGrounds_HammerRoom,       []{return CanUse(CanUseItem::Longshot)  || (CanUse(CanUseItem::Hover_Boots) && CanUse(CanUseItem::Hookshot));}),
  });

  Exit GerudoTrainingGrounds_HammerRoom = Exit("Gerudo Training Grounds Hammer Room", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_HAMMER_ROOM_CLEAR_CHEST,  []{return true;}),
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_HAMMER_ROOM_SWITCH_CHEST, []{return CanUse(CanUseItem::Hammer);})
                }, {
                  //Exits
                  ExitPairing::Both(&GerudoTrainingGrounds_EyeStatueLower, []{return CanUse(CanUseItem::Hammer) && Bow;}),
                  ExitPairing::Both(&GerudoTrainingGrounds_LavaRoom,       []{return true;}),
  });

  Exit GerudoTrainingGrounds_EyeStatueLower = Exit("Gerudo Training Grounds Eye Statue Lower", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_EYE_STATUE_CHEST, []{return CanUse(CanUseItem::Bow);}),
                }, {
                  //Exits
                  ExitPairing::Both(&GerudoTrainingGrounds_HammerRoom, []{return true;}),
  });

  Exit GerudoTrainingGrounds_EyeStatueUpper = Exit("Gerudo Training Grounds Eye Statue Upper", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_NEAR_SCARECROW_CHEST, []{return CanUse(CanUseItem::Bow);})
                }, {
                  //Exits
                  ExitPairing::Both(&GerudoTrainingGrounds_EyeStatueLower, []{return true;}),
  });

  Exit GerudoTrainingGrounds_HeavyBlockRoom = Exit("Gerudo Training Grounds Heavy Block Room", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_BEFORE_HEAVY_BLOCK_CHEST, []{return true;})
                }, {
                  //Exits
                  ExitPairing::Both(&GerudoTrainingGrounds_EyeStatueUpper, []{return (LogicLensGtg || CanUse(CanUseItem::Lens_of_Truth)) && (CanUse(CanUseItem::Hookshot) || (LogicGtgFakeWall && CanUse(CanUseItem::Hover_Boots)));}),
                  ExitPairing::Both(&GerudoTrainingGrounds_LikeLikeRoom,   []{return (LogicLensGtg || CanUse(CanUseItem::Lens_of_Truth)) && (CanUse(CanUseItem::Hookshot) || (LogicGtgFakeWall && CanUse(CanUseItem::Hover_Boots))) && CanUse(CanUseItem::Silver_Gauntlets);}),
  });

  Exit GerudoTrainingGrounds_LikeLikeRoom = Exit("Gerudo Training Grounds Like Like Room", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_FIRST_CHEST,  []{return true;}),
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_SECOND_CHEST, []{return true;}),
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_THIRD_CHEST,  []{return true;}),
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_HEAVY_BLOCK_FOURTH_CHEST, []{return true;}),
  }, {});

  Exit GanonsCastle_Lobby = Exit("Ganon's Castle Lobby", "Ganon's Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&OGC_Grounds,              []{return true;}),
                  ExitPairing::Both(&GanonsCastle_ForestTrial, []{return true;}),
                  ExitPairing::Both(&GanonsCastle_FireTrial,   []{return true;}),
                  ExitPairing::Both(&GanonsCastle_WaterTrial,  []{return true;}),
                  ExitPairing::Both(&GanonsCastle_ShadowTrial, []{return true;}),
                  ExitPairing::Both(&GanonsCastle_SpiritTrial, []{return true;}),
                  ExitPairing::Both(&GanonsCastle_LightTrial,  []{return CanUse(CanUseItem::Golden_Gauntlets);}),
                  ExitPairing::Both(&GanonsCastle_Tower,       []{return (ForestTrialClear || Trial::ForestTrial.IsSkipped()) &&
                                                                         (FireTrialClear   || Trial::FireTrial.IsSkipped())   &&
                                                                         (WaterTrialClear  || Trial::WaterTrial.IsSkipped())  &&
                                                                         (ShadowTrialClear || Trial::ShadowTrial.IsSkipped()) &&
                                                                         (SpiritTrialClear || Trial::SpiritTrial.IsSkipped()) &&
                                                                         (LightTrialClear  || Trial::LightTrial.IsSkipped());}),
                  ExitPairing::Both(&GanonsCastle_DekuScrubs,  []{return LogicLensCastle || CanUse(CanUseItem::Lens_of_Truth);}),
  });

  Exit GanonsCastle_DekuScrubs = Exit("Ganon's Castle Deku Scrubs", "Ganon's Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FreeFairies, []{return true;}),
                }, {
                  //Locations
                  ItemLocationPairing(GANONS_CASTLE_DEKU_SCRUB_CENTER_LEFT,  []{return true;}),
                  ItemLocationPairing(GANONS_CASTLE_DEKU_SCRUB_CENTER_RIGHT, []{return true;}),
                  ItemLocationPairing(GANONS_CASTLE_DEKU_SCRUB_RIGHT,        []{return true;}),
                  ItemLocationPairing(GANONS_CASTLE_DEKU_SCRUB_LEFT,         []{return true;}),
  }, {});

  Exit GanonsCastle_ForestTrial = Exit("Ganon's Castle Forest Trial", "Ganon's Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&ForestTrialClear, []{return CanUse(CanUseItem::Light_Arrows) && (FireArrows || DinsFire);}),
                }, {
                  //Locations
                  ItemLocationPairing(GANONS_CASTLE_FOREST_TRIAL_CHEST, []{return true;}),
  }, {});

  Exit GanonsCastle_FireTrial = Exit("Ganon's Castle Fire Trial", "Ganon's Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FireTrialClear, []{return CanUse(CanUseItem::Goron_Tunic) && CanUse(CanUseItem::Golden_Gauntlets) && CanUse(CanUseItem::Light_Arrows) && CanUse(CanUseItem::Longshot);}),
  }, {}, {});

  Exit GanonsCastle_WaterTrial = Exit("Ganon's Castle Water Trial", "Ganon's Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&BlueFireAccess,  []{return BlueFireAccess || HasBottle;}),
                  EventPairing(&FairyPot,        []{return FairyPot || BlueFire;}),
                  EventPairing(&WaterTrialClear, []{return BlueFire && Hammer && CanUse(CanUseItem::Light_Arrows);}),
                }, {
                  //Locations
                  ItemLocationPairing(GANONS_CASTLE_WATER_TRIAL_LEFT_CHEST,  []{return true;}),
                  ItemLocationPairing(GANONS_CASTLE_WATER_TRIAL_RIGHT_CHEST, []{return true;}),
  }, {});

  Exit GanonsCastle_ShadowTrial = Exit("Ganon's Castle Shadow Trial", "Ganon's Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&ShadowTrialClear, []{return CanUse(CanUseItem::Light_Arrows) && Hammer && ((FireArrows && (LogicLensCastle || CanUse(CanUseItem::Lens_of_Truth))) || (CanUse(CanUseItem::Longshot) && (HoverBoots || (DinsFire && (LogicLensCastle || CanUse(CanUseItem::Lens_of_Truth))))));}),
                }, {
                  //Locations
                  ItemLocationPairing(GANONS_CASTLE_SHADOW_TRIAL_FRONT_CHEST,            []{return CanUse(CanUseItem::Fire_Arrows) || Hookshot || HoverBoots || CanPlay(SongOfTime);}),
                  ItemLocationPairing(GANONS_CASTLE_SHADOW_TRIAL_GOLDEN_GAUNTLETS_CHEST, []{return CanUse(CanUseItem::Fire_Arrows) || (CanUse(CanUseItem::Longshot) && (HoverBoots || CanUse(CanUseItem::Dins_Fire)));}),
  }, {});

  Exit GanonsCastle_SpiritTrial = Exit("Ganon's Castle Spirit Trial", "Ganon's Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&NutPot,           []{return NutPot || ((LogicSpiritTrialHookshot || Hookshot) && HasBombchus && Bow && MirrorShield);}),
                  EventPairing(&SpiritTrialClear, []{return CanUse(CanUseItem::Light_Arrows)  && MirrorShield && HasBombchus && (LogicSpiritTrialHookshot || Hookshot);}),
                }, {
                  //Locations
                  ItemLocationPairing(GANONS_CASTLE_SPIRIT_TRIAL_CRYSTAL_SWITCH_CHEST, []{return LogicSpiritTrialHookshot || Hookshot;}),
                  ItemLocationPairing(GANONS_CASTLE_SPIRIT_TRIAL_INVISIBLE_CHEST,      []{return (LogicSpiritTrialHookshot || Hookshot) && HasBombchus && (LogicLensCastle || CanUse(CanUseItem::Lens_of_Truth));}),
  }, {});

  Exit GanonsCastle_LightTrial = Exit("Ganon's Castle Light Trial", "Ganon's Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&LightTrialClear, []{return CanUse(CanUseItem::Light_Arrows) && Hookshot && SmallKeys(GanonsCastleKeys, 2) && (LogicLensCastle || CanUse(CanUseItem::Lens_of_Truth));}),
                }, {
                  //Locations
                  ItemLocationPairing(GANONS_CASTLE_LIGHT_TRIAL_FIRST_LEFT_CHEST,        []{return true;}),
                  ItemLocationPairing(GANONS_CASTLE_LIGHT_TRIAL_SECOND_LEFT_CHEST,       []{return true;}),
                  ItemLocationPairing(GANONS_CASTLE_LIGHT_TRIAL_THIRD_LEFT_CHEST,        []{return true;}),
                  ItemLocationPairing(GANONS_CASTLE_LIGHT_TRIAL_FIRST_RIGHT_CHEST,       []{return true;}),
                  ItemLocationPairing(GANONS_CASTLE_LIGHT_TRIAL_SECOND_RIGHT_CHEST,      []{return true;}),
                  ItemLocationPairing(GANONS_CASTLE_LIGHT_TRIAL_THIRD_RIGHT_CHEST,       []{return true;}),
                  ItemLocationPairing(GANONS_CASTLE_LIGHT_TRIAL_INVISIBLE_ENEMIES_CHEST, []{return LogicLensCastle || CanUse(CanUseItem::Lens_of_Truth);}),
                  ItemLocationPairing(GANONS_CASTLE_LIGHT_TRIAL_LULLABY_CHEST,           []{return CanPlay(ZeldasLullaby) && SmallKeys(GanonsCastleKeys, 1);}),
  }, {});

  Exit GanonsCastle_Tower = Exit("Ganon's Castle Tower", "Ganons Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(GANONS_TOWER_BOSS_KEY_CHEST, []{return true;}),
                  ItemLocationPairing(GANONDORF_HINT,              []{return BossKeyGanonsCastle;}),
                  ItemLocationPairing(GANON,                       []{return BossKeyGanonsCastle && CanUse(CanUseItem::Light_Arrows);}),
  }, {});

  /*---------------------------
  |   MASTER QUEST DUNGEONS   |
  ---------------------------*/

  Exit DekuTree_MQ_Lobby = Exit("Deku Tree MQ Lobby", "Deku Tree", DEKU_TREE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&DekuBabaSticks, []{return DekuBabaSticks || (IsAdult || KokiriSword || Boomerang);}),
                  EventPairing(&DekuBabaNuts,   []{return DekuBabaNuts   || (IsAdult || KokiriSword || Slingshot || Sticks || HasExplosives || CanUse(CanUseItem::Dins_Fire));}),
  }, {
                  //Locations
                  ItemLocationPairing(DEKU_TREE_MQ_MAP_CHEST,                 []{return true;}),
                  ItemLocationPairing(DEKU_TREE_MQ_SLINGSHOT_CHEST,           []{return IsAdult || CanChildAttack;}),
                  ItemLocationPairing(DEKU_TREE_MQ_SLINGSHOT_ROOM_BACK_CHEST, []{return HasFireSourceWithTorch || CanUse(CanUseItem::Bow);}),
                  ItemLocationPairing(DEKU_TREE_MQ_BASEMENT_CHEST,            []{return HasFireSourceWithTorch || CanUse(CanUseItem::Bow);}),
                  ItemLocationPairing(DEKU_TREE_MQ_GS_LOBBY,                  []{return IsAdult || CanChildAttack;}),
  }, {
                  //Exits
                  ExitPairing(&KF_OutsideDekuTree,                 []{return true;}),
                  ExitPairing(&DekuTree_MQ_CompassRoom,            []{return DekuTree_MQ_Lobby.Here([]{return CanUse(CanUseItem::Slingshot) || CanUse(CanUseItem::Bow);}) &&
                                                                               DekuTree_MQ_Lobby.Here([]{return HasFireSourceWithTorch || CanUse(CanUseItem::Bow);});}),
                  ExitPairing(&DekuTree_MQ_BasementWaterRoomFront, []{return DekuTree_MQ_Lobby.Here([]{return CanUse(CanUseItem::Slingshot) || CanUse(CanUseItem::Bow);}) &&
                                                                               DekuTree_MQ_Lobby.Here([]{return HasFireSourceWithTorch;});}),
                  ExitPairing(&DekuTree_MQ_BasementLedge,          []{return LogicDekuB1Skip || DekuTree_MQ_Lobby.Here([]{return IsAdult;});}),
  });

  Exit DekuTree_MQ_CompassRoom = Exit("Deku Tree MQ Compass Room", "Deku Tree", DEKU_TREE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(DEKU_TREE_MQ_COMPASS_CHEST,   []{return true;}),
                  ItemLocationPairing(DEKU_TREE_MQ_GS_COMPASS_ROOM, []{return HookshotOrBoomerang &&
                                                                               DekuTree_MQ_CompassRoom.Here([]{return HasBombchus ||
                                                                               (Bombs && (CanPlay(SongOfTime) || IsAdult)) ||
                                                                               (CanUse(CanUseItem::Hammer) && (CanPlay(SongOfTime) /*|| LogicDekuMQCompassGS*/));});}),
  }, {
                  //Exits
                  ExitPairing(&DekuTree_MQ_Lobby, []{return true;}),
  });

  Exit DekuTree_MQ_BasementWaterRoomFront = Exit("Deku Tree MQ Basement Water Room Front", "Deku Tree", DEKU_TREE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(DEKU_TREE_MQ_BEFORE_SPINNING_LOG_CHEST, []{return true;}),
  }, {
                  //Exits
                  ExitPairing(&DekuTree_MQ_BasementWaterRoomBack, []{return /*LogicDekuMQLog || */ (IsChild && (DekuShield || HylianShield)) ||
                                                                             CanUse(CanUseItem::Longshot) || (CanUse(CanUseItem::Hookshot) && CanUse(CanUseItem::Iron_Boots));}),
                  ExitPairing(&DekuTree_MQ_Lobby,                  []{return true;}),
  });

  Exit DekuTree_MQ_BasementWaterRoomBack = Exit("Deku Tree MQ Basement Water Room Front", "Deku Tree", DEKU_TREE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(DEKU_TREE_MQ_AFTER_SPINNING_LOG_CHEST, []{return CanPlay(SongOfTime);}),
  }, {
                  //Exits
                  ExitPairing(&DekuTree_MQ_BasementBackRoom,       []{return DekuTree_MQ_BasementWaterRoomBack.Here([]{return CanUse(CanUseItem::Sticks) || CanUse(CanUseItem::Dins_Fire) ||
                                                                               DekuTree_MQ_BasementWaterRoomFront.Here([]{return CanUse(CanUseItem::Fire_Arrows);});}) &&
                                                                                 DekuTree_MQ_BasementWaterRoomBack.Here([]{return IsAdult || KokiriSword || CanUseProjectile || (Nuts && Sticks);});}),
                  ExitPairing(&DekuTree_MQ_BasementWaterRoomFront, []{return true;}),
  });

  Exit DekuTree_MQ_BasementBackRoom = Exit("Deku Tree MQ Basement Back Room", "Deku Tree", DEKU_TREE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(DEKU_TREE_MQ_GS_BASEMENT_GRAVES_ROOM, []{return CanUse(CanUseItem::Longshot) || (CanPlay(SongOfTime) && HookshotOrBoomerang);}),
                  ItemLocationPairing(DEKU_TREE_MQ_GS_BASEMENT_BACK_ROOM,   []{return HasFireSourceWithTorch && HookshotOrBoomerang;})
  }, {
                  //Exits
                  ExitPairing(&DekuTree_MQ_BasementLedge,         []{return IsChild;}),
                  ExitPairing(&DekuTree_MQ_BasementWaterRoomBack, []{return CanUse(CanUseItem::Kokiri_Sword) || CanUseProjectile || (Nuts && CanUse(CanUseItem::Sticks));}),
  });

  Exit DekuTree_MQ_BasementLedge = Exit("Deku Tree MQ Basement Ledge", "Deku Tree", DEKU_TREE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&DekuTreeClear, []{return DekuTreeClear || (DekuTree_MQ_BasementLedge.Here([]{return HasFireSourceWithTorch;}) &&
                                                                           DekuTree_MQ_BasementLedge.Here([]{return HasShield;})  &&
                                                                           (IsAdult || KokiriSword || Sticks));}),
  }, {
                  //Locations
                  ItemLocationPairing(DEKU_TREE_MQ_DEKU_SCRUB,     []{return CanStunDeku;}),
                  ItemLocationPairing(DEKU_TREE_QUEEN_GOHMA_HEART, []{return HasFireSourceWithTorch && HasShield && (IsAdult || KokiriSword || Sticks);}),
                  ItemLocationPairing(QUEEN_GOHMA,                 []{return HasFireSourceWithTorch && HasShield && (IsAdult || KokiriSword || Sticks);}),
  }, {
                  //Exits
                  ExitPairing(&DekuTree_MQ_BasementBackRoom, []{return IsChild;}),
                  ExitPairing(&DekuTree_MQ_Lobby,            []{return true;}),
  });

  Exit DodongosCavern_MQ_Beginning = Exit("Dodongos Cavern MQ Beginning", "Dodongos Cavern", DODONGOS_CAVERN, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&DodongosCavern_Entryway, []{return true;}),
                  ExitPairing::Both(&DodongosCavern_MQ_Lobby, []{return DodongosCavern_MQ_Beginning.Here([]{return CanBlastOrSmash || GoronBracelet;});}),
  });

  Exit DodongosCavern_MQ_Lobby = Exit("Dodongos Cavern MQ Lobby", "Dodongos Cavern", DODONGOS_CAVERN, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&DekuBabaSticks,   []{return DekuBabaSticks || (IsAdult || KokiriSword || Boomerang);}),
                  EventPairing(&GossipStoneFairy, []{return GossipStoneFairy || CanSummonGossipFairy;}),
  }, {
                  //Locations
                  ItemLocationPairing(DODONGOS_CAVERN_MQ_MAP_CHEST,                  []{return true;}),
                  ItemLocationPairing(DODONGOS_CAVERN_MQ_COMPASS_CHEST,              []{return IsAdult || CanChildAttack || Nuts;}),
                  ItemLocationPairing(DODONGOS_CAVERN_MQ_LARVAE_ROOM_CHEST,          []{return CanUse(CanUseItem::Sticks) || HasFireSource;}),
                  ItemLocationPairing(DODONGOS_CAVERN_MQ_TORCH_PUZZLE_ROOM_CHEST,    []{return CanBlastOrSmash || CanUse(CanUseItem::Sticks) || CanUse(CanUseItem::Dins_Fire) || (IsAdult && (LogicDCJump || HoverBoots || Hookshot));}),
                  ItemLocationPairing(DODONGOS_CAVERN_MQ_GS_SONG_OF_TIME_BLOCK_ROOM, []{return CanPlay(SongOfTime) && (CanChildAttack || IsAdult);}),
                  ItemLocationPairing(DODONGOS_CAVERN_MQ_GS_LARVAE_ROOM,             []{return CanUse(CanUseItem::Sticks) || HasFireSource;}),
                  ItemLocationPairing(DODONGOS_CAVERN_MQ_GS_LIZALFOS_ROOM,           []{return CanBlastOrSmash;}),
                  ItemLocationPairing(DODONGOS_CAVERN_MQ_DEKU_SCRUB_LOBBY_REAR,      []{return CanStunDeku;}),
                  ItemLocationPairing(DODONGOS_CAVERN_MQ_DEKU_SCRUB_LOBBY_FRONT,     []{return CanStunDeku;}),
                  ItemLocationPairing(DODONGOS_CAVERN_MQ_DEKU_SCRUB_STAIRCASE,       []{return CanStunDeku;}),
                  ItemLocationPairing(DODONGOS_CAVERN_GOSSIP_STONE,                  []{return true;}),
  }, {
                  //Exits
                  ExitPairing::Both(&DodongosCavern_MQ_LowerRightSide,  []{return DodongosCavern_MQ_Lobby.Here([]{return CanBlastOrSmash || ((CanUse(CanUseItem::Sticks) || CanUse(CanUseItem::Dins_Fire)) && CanTakeDamage);});}),
                  ExitPairing::Both(&DodongosCavern_MQ_BombBagArea,     []{return IsAdult || (DodongosCavern_MQ_Lobby.Here([]{return IsAdult;}) && HasExplosives);}),
                    //Trick: IsAdult || HasExplosives || (LogicDCMQChildBombs && (KokiriSword || Sticks) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO))
                  ExitPairing::Both(&DodongosCavern_MQ_BossArea,        []{return HasExplosives;}),
                    //Trick: HasExplosives || (LogicDCMQEyes && GoronBracelet && (IsAdult || LogicDCMQChildBack) && (CanUse(CanUseItem::Sticks) || CanUse(CanUseItem::Dins_Fire) || (IsAdult && (LogicDCJump || Hammer || HoverBoots || Hookshot))))
  });

  Exit DodongosCavern_MQ_LowerRightSide = Exit("Dodongos Cavern MQ Lower Right Side", "Dodongos Cavern", DODONGOS_CAVERN, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(DODONGOS_CAVERN_MQ_DEKU_SCRUB_SIDE_ROOM_NEAR_LOWER_LIZALFOS, []{return CanStunDeku;}),
  }, {
                  //Exits
                  ExitPairing::Both(&DodongosCavern_MQ_BombBagArea, []{return (DodongosCavern_MQ_LowerRightSide.Here([]{return CanUse(CanUseItem::Bow);}) || GoronBracelet ||
                                                                                CanUse(CanUseItem::Dins_Fire) || HasExplosives) &&
                                                                                CanUse(CanUseItem::Slingshot);}),
  });

  Exit DodongosCavern_MQ_BombBagArea = Exit("Dodongos Cavern MQ Bomb Bag Area", "Dodongos Cavern", DODONGOS_CAVERN, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(DODONGOS_CAVERN_MQ_BOMB_BAG_CHEST, []{return true;}),
                  ItemLocationPairing(DODONGOS_CAVERN_MQ_GS_SCRUB_ROOM,  []{return (DodongosCavern_MQ_BombBagArea.Here([]{return CanUse(CanUseItem::Bow);}) ||  GoronBracelet || CanUse(CanUseItem::Dins_Fire) || HasExplosives) && (CanUse(CanUseItem::Hookshot) || CanUse(CanUseItem::Boomerang));}),
  }, {
                  //Exits
                  ExitPairing::Both(&DodongosCavern_MQ_LowerRightSide, []{return true;}),
  });

  Exit DodongosCavern_MQ_BossArea = Exit("Dodongos Cavern MQ BossArea", "Dodongos Cavern", DODONGOS_CAVERN, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPot,            []{return true;}),
                  EventPairing(&DodongosCavernClear, []{return DodongosCavernClear || (CanBlastOrSmash && (Bombs || GoronBracelet) && (IsAdult || Sticks || KokiriSword));}),
  }, {
                  //Locations
                  ItemLocationPairing(DODONGOS_CAVERN_MQ_UNDER_GRAVE_CHEST, []{return true;}),
                  ItemLocationPairing(DODONGOS_CAVERN_BOSS_ROOM_CHEST,      []{return true;}),
                  ItemLocationPairing(DODONGOS_CAVERN_KING_DODONGO_HEART,   []{return CanBlastOrSmash && (Bombs || GoronBracelet) && (IsAdult || Sticks || KokiriSword);}),
                  ItemLocationPairing(KING_DODONGO,                         []{return CanBlastOrSmash && (Bombs || GoronBracelet) && (IsAdult || Sticks || KokiriSword);}),
                  ItemLocationPairing(DODONGOS_CAVERN_MQ_GS_BACK_AREA,      []{return true;}),
  }, {});

  Exit JabuJabusBelly_MQ_Beginning = Exit("Jabu Jabus Belly MQ Beginning", "Jabu Jabus Belly", JABU_JABUS_BELLY, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&NutPot, []{return true;}),
  }, {
                  //Locations
                  ItemLocationPairing(JABU_JABUS_BELLY_MQ_MAP_CHEST,           []{return CanBlastOrSmash;}),
                  ItemLocationPairing(JABU_JABUS_BELLY_MQ_FIRST_ROOM_SIDE_CHEST, []{return CanUse(CanUseItem::Slingshot);}),
  }, {
                  //Exits
                  ExitPairing::Both(&ZF_Main,                []{return true;}),
                  ExitPairing::Both(&JabuJabusBelly_MQ_Main, []{return JabuJabusBelly_MQ_Beginning.Here([]{return IsChild && CanUse(CanUseItem::Slingshot);});}),
  });

  Exit JabuJabusBelly_MQ_Main = Exit("Jabu Jabus Belly MQ Main", "Jabu Jabus Belly", JABU_JABUS_BELLY, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(JABU_JABUS_BELLY_MQ_SECOND_ROOM_LOWER_CHEST,      []{return true;}),
                  ItemLocationPairing(JABU_JABUS_BELLY_MQ_SECOND_ROOM_UPPER_CHEST,      []{return CanUse(CanUseItem::Hover_Boots) || CanUse(CanUseItem::Hookshot) || JabuJabusBelly_MQ_BossArea.Child();}),
                  ItemLocationPairing(JABU_JABUS_BELLY_MQ_COMPASS_CHEST,                []{return true;}),
                  ItemLocationPairing(JABU_JABUS_BELLY_MQ_BASEMENT_NEAR_VINES_CHEST,    []{return true;}),
                  ItemLocationPairing(JABU_JABUS_BELLY_MQ_BASEMENT_NEAR_SWITCHES_CHEST, []{return true;}),
                  ItemLocationPairing(JABU_JABUS_BELLY_MQ_BOOMERANG_ROOM_SMALL_CHEST,   []{return true;}),
                  ItemLocationPairing(JABU_JABUS_BELLY_MQ_BOOMERANG_CHEST,              []{return true;}),
                  ItemLocationPairing(JABU_JABUS_BELLY_MQ_GS_BOOMERANG_CHEST_ROOM,      []{return CanPlay(SongOfTime);}),
                    //Trick: CanPlay(SongOfTime) || (LogicJabuMQSoTGS && CanUse(CanUseItem::Boomerang))
  }, {
                  //Exits
                  ExitPairing::Both(&JabuJabusBelly_MQ_Beginning, []{return true;}),
                  ExitPairing::Both(&JabuJabusBelly_MQ_Depths,    []{return HasExplosives && CanUse(CanUseItem::Boomerang);}),
  });

  Exit JabuJabusBelly_MQ_Depths = Exit("Jabu Jabus Belly MQ Depths", "Jabu Jabus Belly", JABU_JABUS_BELLY, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(JABU_JABUS_BELLY_MQ_FALLING_LIKE_LIKE_ROOM_CHEST, []{return true;}),
                  ItemLocationPairing(JABU_JABUS_BELLY_MQ_GS_TAILPASARAN_ROOM,          []{return Sticks || CanUse(CanUseItem::Dins_Fire);}),
                  ItemLocationPairing(JABU_JABUS_BELLY_MQ_GS_INVISIBLE_ENEMIES_ROOM,    []{return (LogicLensJabuMQ || CanUse(CanUseItem::Lens_of_Truth)) || JabuJabusBelly_MQ_Main.Here([]{return CanUse(CanUseItem::Hover_Boots) && CanUse(CanUseItem::Hookshot);});}),
  }, {
                  //Exits
                  ExitPairing::Both(&JabuJabusBelly_MQ_Main,     []{return true;}),
                  ExitPairing::Both(&JabuJabusBelly_MQ_BossArea, []{return Sticks || (CanUse(CanUseItem::Dins_Fire) && KokiriSword);}),
  });

  Exit JabuJabusBelly_MQ_BossArea = Exit("Jabu Jabus Belly MQ Boss Area", "Jabu Jabus Belly", JABU_JABUS_BELLY, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPot,            []{return true;}),
                  EventPairing(&JabuJabusBellyClear, []{return true;}),
  }, {
                  //Locations
                  ItemLocationPairing(JABU_JABUS_BELLY_MQ_COW,             []{return CanPlay(EponasSong);}),
                  ItemLocationPairing(JABU_JABUS_BELLY_MQ_NEAR_BOSS_CHEST, []{return true;}),
                  ItemLocationPairing(JABU_JABUS_BELLY_BARINADE_HEART,     []{return true;}),
                  ItemLocationPairing(BARINADE,                            []{return true;}),
                  ItemLocationPairing(JABU_JABUS_BELLY_MQ_GS_NEAR_BOSS,    []{return true;}),
  }, {
                  //Exits
                  ExitPairing::Both(&JabuJabusBelly_MQ_Main, []{return true;}),
  });

  Exit ForestTemple_MQ_Lobby = Exit("Forest Temple MQ Lobby", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(FOREST_TEMPLE_MQ_FIRST_ROOM_CHEST, []{return IsAdult || Bombs || CanUse(CanUseItem::Sticks) || Nuts || CanUse(CanUseItem::Boomerang) || CanUse(CanUseItem::Dins_Fire) || KokiriSword || CanUse(CanUseItem::Slingshot);}),
                  ItemLocationPairing(FOREST_TEMPLE_MQ_GS_FIRST_HALLWAY, []{return CanUse(CanUseItem::Hookshot) || CanUse(CanUseItem::Boomerang);}),
  }, {
                  //Exits
                  ExitPairing::Both(&SFM_Main,                    []{return true;}),
                  ExitPairing::Both(&ForestTemple_MQ_CentralArea, []{return SmallKeys(ForestTempleKeys, 1) && (IsAdult || CanChildAttack || Nuts);}),
  });

  Exit ForestTemple_MQ_CentralArea = Exit("Forest Temple MQ Central Area", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPot, []{return true;}),
  }, {
                  //Locations
                  ItemLocationPairing(FOREST_TEMPLE_MQ_WOLFOS_CHEST,       []{return (CanPlay(SongOfTime) || IsChild) && (IsAdult || CanUse(CanUseItem::Dins_Fire) || CanUse(CanUseItem::Sticks) || CanUse(CanUseItem::Slingshot) || KokiriSword);}),
                  ItemLocationPairing(FOREST_TEMPLE_MQ_GS_BLOCK_PUSH_ROOM, []{return IsAdult || KokiriSword;}),
  }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_MQ_NWOutdoors,       []{return CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Slingshot);}),
                  ExitPairing::Both(&ForestTemple_MQ_NEOutdoors,       []{return CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Slingshot);}), //This is as far as child can get
                  ExitPairing::Both(&ForestTemple_MQ_AfterBlockPuzzle, []{return IsAdult && GoronBracelet;}),
                    //Trick: IsAdult && (GoronBracelet || (LogicForestMQBlockPuzzle && HasBombchus && CanUse(CanUseItem::Hookshot)))
                  ExitPairing::Both(&ForestTemple_MQ_OutdoorLedge,     []{return false;}),
                    //Trick: (LogicForestMQHallwaySwitchJumpslash && CanUse(CanUseItem::Hover_Boots)) || (LogicForestMQHallwaySwitchHookshot && CanUse(CanUseItem::Hookshot))
                  ExitPairing::Both(&ForestTemple_MQ_BossRegion,       []{return ForestTempleJoAndBeth && ForestTempleAmyAndMeg;}),
  });

  Exit ForestTemple_MQ_AfterBlockPuzzle = Exit("Forest Temple MQ After Block Puzzle", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(FOREST_TEMPLE_MQ_BOSS_KEY_CHEST, []{return SmallKeys(ForestTempleKeys, 3);}),
  }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_MQ_BowRegion,    []{return SmallKeys(ForestTempleKeys, 4);}),
                  ExitPairing::Both(&ForestTemple_MQ_OutdoorLedge, []{return SmallKeys(ForestTempleKeys, 3);}),
                    //Trick: SmallKeys(ForestTempleKeys, 3) || (LogicForestMQHallwaySwitchJumpslash && (CanUse(CanUseItem::Hookshot) || LogicForestOutsideBackdoor))
                  ExitPairing::Both(&ForestTemple_MQ_NWOutdoors,   []{return SmallKeys(ForestTempleKeys, 2);}),
  });

  Exit ForestTemple_MQ_OutdoorLedge = Exit("Forest Temple MQ Outdoor Ledge", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(FOREST_TEMPLE_MQ_REDEAD_CHEST, []{return true;}),
  }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_MQ_NWOutdoors, []{return true;}),
  });

  Exit ForestTemple_MQ_NWOutdoors = Exit("Forest Temple MQ NW Outdoors", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(FOREST_TEMPLE_MQ_GS_LEVEL_ISLAND_COURTYARD, []{return true;}),
  }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_MQ_NEOutdoors,        []{return CanUse(CanUseItem::Iron_Boots) || CanUse(CanUseItem::Longshot) || ProgressiveScale >= 2;}),
                    //Trick: CanUse(CanUseItem::Iron_Boots) || CanUse(CanUseItem::Longshot) || ProgressiveScale >= 2 || (LogicForestMQWellSwim && CanUse(CanUseItem::Hookshot))
                  ExitPairing::Both(&ForestTemple_MQ_OutdoorsTopLedges, []{return CanUse(CanUseItem::Fire_Arrows);}),
  });

  Exit ForestTemple_MQ_NEOutdoors = Exit("Forest Temple MQ NE Outdoors", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&DekuBabaSticks, []{return DekuBabaSticks || (IsAdult || KokiriSword || Boomerang);}),
                  EventPairing(&DekuBabaNuts,   []{return DekuBabaNuts   || (IsAdult || KokiriSword || Slingshot || Sticks || HasExplosives || CanUse(CanUseItem::Dins_Fire));}),
  }, {
                  //Locations
                  ItemLocationPairing(FOREST_TEMPLE_MQ_WELL_CHEST,                 []{return CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Slingshot);}),
                  ItemLocationPairing(FOREST_TEMPLE_MQ_GS_RAISED_ISLAND_COURTYARD, []{return CanUse(CanUseItem::Hookshot) || CanUse(CanUseItem::Boomerang) || (CanUse(CanUseItem::Fire_Arrows) && (CanPlay(SongOfTime) || (CanUse(CanUseItem::Hover_Boots) && LogicForestDoorFrame)));}),
                  ItemLocationPairing(FOREST_TEMPLE_MQ_GS_WELL,                    []{return (CanUse(CanUseItem::Iron_Boots) && CanUse(CanUseItem::Hookshot)) || CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Slingshot);}),
  }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_MQ_OutdoorsTopLedges, []{return CanUse(CanUseItem::Hookshot) && (CanUse(CanUseItem::Longshot) || CanUse(CanUseItem::Hover_Boots) || CanPlay(SongOfTime));}),
                  ExitPairing::Both(&ForestTemple_MQ_NEOutdoorsLedge,   []{return CanUse(CanUseItem::Longshot);}),
  });

  Exit ForestTemple_MQ_OutdoorsTopLedges = Exit("Forest Temple MQ Outdoors Top Ledges", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(FOREST_TEMPLE_MQ_RAISED_ISLAND_COURTYARD_UPPER_CHEST, []{return true;}),
  }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_MQ_NEOutdoors,      []{return true;}),
                  ExitPairing::Both(&ForestTemple_MQ_NEOutdoorsLedge, []{return false;}),
                    //Trick: LogicForestOutdoorsLedge && CanUse(CanUseItem::Hover_Boots)
  });

  Exit ForestTemple_MQ_NEOutdoorsLedge = Exit("Forest Temple MQ NE Outdoors Ledge", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(FOREST_TEMPLE_MQ_RAISED_ISLAND_COURTYARD_LOWER_CHEST, []{return true;}),
  }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_MQ_NEOutdoors,  []{return true;}),
                  ExitPairing::Both(&ForestTemple_MQ_FallingRoom, []{return CanPlay(SongOfTime);}),
  });

  Exit ForestTemple_MQ_BowRegion = Exit("Forest Temple MQ Bow Region", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&ForestTempleJoAndBeth, []{return ForestTempleJoAndBeth || CanUse(CanUseItem::Bow);}),
  }, {
                  //Locations
                  ItemLocationPairing(FOREST_TEMPLE_MQ_BOW_CHEST,     []{return true;}),
                  ItemLocationPairing(FOREST_TEMPLE_MQ_MAP_CHEST,     []{return CanUse(CanUseItem::Bow);}),
                  ItemLocationPairing(FOREST_TEMPLE_MQ_COMPASS_CHEST, []{return CanUse(CanUseItem::Bow);}),
  }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_MQ_FallingRoom, []{return SmallKeys(ForestTempleKeys, 5) && (CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Dins_Fire));}),
  });

  Exit ForestTemple_MQ_FallingRoom = Exit("Forest Temple MQ Falling Room", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&ForestTempleAmyAndMeg, []{return ForestTempleAmyAndMeg || (CanUse(CanUseItem::Bow) && SmallKeys(ForestTempleKeys, 6));}),
  }, {
                  //Locations
                  ItemLocationPairing(FOREST_TEMPLE_MQ_FALLING_CEILING_ROOM_CHEST, []{return true;}),
  }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_MQ_NEOutdoorsLedge, []{return true;}),
  });

  Exit ForestTemple_MQ_BossRegion = Exit("Forest Temple MQ Boss Region", "Forest Temple", FOREST_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&ForestTempleClear, []{return ForestTempleClear || BossKeyForestTemple;}),
  }, {
                  //Locations
                  ItemLocationPairing(FOREST_TEMPLE_MQ_BASEMENT_CHEST,   []{return true;}),
                  ItemLocationPairing(FOREST_TEMPLE_PHANTOM_GANON_HEART, []{return BossKeyForestTemple;}),
                  ItemLocationPairing(PHANTOM_GANON,                     []{return BossKeyForestTemple;}),
  }, {});

  Exit FireTemple_MQ_Lower = Exit("Fire Temple MQ Lower", "Fire Temple", FIRE_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(FIRE_TEMPLE_MQ_MAP_ROOM_SIDE_CHEST, []{return IsAdult || KokiriSword || Sticks || Slingshot || Bombs || CanUse(CanUseItem::Dins_Fire);}),
                  ItemLocationPairing(FIRE_TEMPLE_MQ_NEAR_BOSS_CHEST,     []{return (LogicFewerTunicRequirements || CanUse(CanUseItem::Goron_Tunic)) && (CanUse(CanUseItem::Hover_Boots) || (CanUse(CanUseItem::Hookshot) && (CanUse(CanUseItem::Fire_Arrows) || (CanUse(CanUseItem::Dins_Fire) && ((DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_QUADRUPLE)) || CanUse(CanUseItem::Goron_Tunic) || CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Longshot))))));}),
                    //Trick: (LogicFewerTunicRequirements || CanUse(CanUseItem::Goron_Tunic)) && (((CanUse(CanUseItem::Hover_Boots) || (LogicFireMQNearBoss && CanUse(CanUseItem::Bow))) && HasFireSource) || (CanUse(CanUseItem::Hookshot) && CanUse(CanUseItem::Fire_Arrows) || (CanUse(CanUseItem::Dins_Fire) && ((DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_QUADRUPLE)) || CanUse(CanUseItem::Goron_Tunic) || CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Longshot)))))
  }, {
                  //Exits
                  ExitPairing::Both(&FireTemple_Entrance,           []{return true;}),
                  ExitPairing::Both(&FireTemple_MQ_BossRoom,        []{return CanUse(CanUseItem::Goron_Tunic) && CanUse(CanUseItem::Hammer) && BossKeyFireTemple && ((HasFireSource && (LogicFireBossDoorJump || HoverBoots)) || FireTemple_MQ_Upper.HasAccess());}),
                  ExitPairing::Both(&FireTemple_MQ_LowerLockedDoor, []{return SmallKeys(FireTempleKeys, 5) && (IsAdult || KokiriSword);}),
                  ExitPairing::Both(&FireTemple_MQ_BigLavaRoom,     []{return (LogicFewerTunicRequirements || CanUse(CanUseItem::Goron_Tunic)) && CanUse(CanUseItem::Hammer);}),
  });

  Exit FireTemple_MQ_LowerLockedDoor = Exit("Fire Temple MQ Lower Locked Door", "Fire Temple", FIRE_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPot, []{return true;}),
  }, {
                  //Locations
                  ItemLocationPairing(FIRE_TEMPLE_MQ_MEGATON_HAMMER_CHEST, []{return IsAdult && (HasExplosives || Hammer || Hookshot);}),
                  ItemLocationPairing(FIRE_TEMPLE_MQ_MAP_CHEST,            []{return CanUse(CanUseItem::Hammer);}),
  }, {});

  Exit FireTemple_MQ_BigLavaRoom = Exit("Fire Temple MQ Big Lava Room", "Fire Temple", FIRE_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPot, []{return FairyPot || (HasFireSource && Bow && (CanUse(CanUseItem::Hookshot) || LogicFireSongOfTime));}),
                    //Trick: HasFireSource && (Bow || LogicFireMQBKChest) && (CanUse(CanUseItem::Hookshot) || LogicFireSongOfTime)
  }, {
                  //Locations
                  ItemLocationPairing(FIRE_TEMPLE_MQ_BOSS_KEY_CHEST,                   []{return HasFireSource && Bow && CanUse(CanUseItem::Hookshot);}),
                    //Trick: HasFireSource && (Bow || LogicFireMQBKChest) && CanUse(CanUseItem::Hookshot)
                  ItemLocationPairing(FIRE_TEMPLE_MQ_BIG_LAVA_ROOM_BLOCKED_DOOR_CHEST, []{return HasFireSource && HasExplosives && CanUse(CanUseItem::Hookshot);}),
                    //Trick: HasFireSource && HasExplosives && (CanUse(CanUseItem::Hookshot) || LogicFireMQBlockedChest)
                  ItemLocationPairing(FIRE_TEMPLE_MQ_GS_BIG_LAVA_ROOM_OPEN_DOOR,       []{return true;}),
  }, {
                  //Exits
                  ExitPairing::Both(&FireTemple_MQ_LowerMaze, []{return CanUse(CanUseItem::Goron_Tunic) && SmallKeys(FireTempleKeys, 2) && HasFireSource;}),
                    //Trick: CanUse(CanUseItem::Goron_Tunic) && SmallKeys(FireTempleKeys, 2) && (HasFireSource || (LogicFireMQClimb && HoverBoots))
  });

  Exit FireTemple_MQ_LowerMaze = Exit("Fire Temple MQ Lower Maze", "Fire Temple", FIRE_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(FIRE_TEMPLE_MQ_LIZALFOS_MAZE_LOWER_CHEST,     []{return true;}),
                  ItemLocationPairing(FIRE_TEMPLE_MQ_LIZALFOS_MAZE_SIDE_ROOM_CHEST, []{return HasExplosives && FireTemple_MQ_UpperMaze.HasAccess();}),
                    //Trick: HasExplosives && (LogicFireMQMazeSideRoom || FireTemple_MQ_UpperMaze.Adult())
   }, {
                  //Exits
                  ExitPairing::Both(&FireTemple_MQ_UpperMaze, []{return HasExplosives && CanUse(CanUseItem::Hookshot);}),
                    //Trick: (HasExplosives && CanUse(CanUseItem::Hookshot)) || (LogicFireMQMazeHovers && CanUse(CanUseItem::Hover_Boots)) || LogicFireMQMazeJump
  });

  Exit FireTemple_MQ_UpperMaze = Exit("Fire Temple MQ Upper Maze", "Fire Temple", FIRE_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  //EventPairing(&WallFairy, []{return WallFairy || ((CanPlay(SongOfTime) && CanUse(CanUseItem::Hookshot) && HasExplosives) || CanUse(CanUseItem::Longshot));}),
                  EventPairing(&FairyPot,  []{return SmallKeys(FireTempleKeys, 3);}),
  }, {
                  //Locations
                  ItemLocationPairing(FIRE_TEMPLE_MQ_LIZALFOS_MAZE_UPPER_CHEST, []{return true;}),
                  ItemLocationPairing(FIRE_TEMPLE_MQ_COMPASS_CHEST,             []{return HasExplosives;}),
                  ItemLocationPairing(FIRE_TEMPLE_MQ_GS_SKULL_ON_FIRE,          []{return (CanPlay(SongOfTime) && CanUse(CanUseItem::Hookshot) && HasExplosives) || CanUse(CanUseItem::Longshot);}),
  }, {
                  //Exits
                  ExitPairing::Both(&FireTemple_MQ_Upper, []{return SmallKeys(FireTempleKeys, 3) && ((CanUse(CanUseItem::Bow) && CanUse(CanUseItem::Hookshot)) || CanUse(CanUseItem::Fire_Arrows));}),
  });

  Exit FireTemple_MQ_Upper = Exit("Fire Temple MQ Upper", "Fire Temple", FIRE_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(FIRE_TEMPLE_MQ_FREESTANDING_KEY,            []{return CanUse(CanUseItem::Hookshot);}),
                    //Trick: CanUse(CanUseItem::Hookshot) || LogicFireMQFlameMaze
                  ItemLocationPairing(FIRE_TEMPLE_MQ_CHEST_ON_FIRE,               []{return CanUse(CanUseItem::Hookshot) && SmallKeys(FireTempleKeys, 4);}),
                    //Trick: (CanUse(CanUseItem::Hookshot) || LogicFireMQFlameMaze) && SmallKeys(FireTempleKeys, 4)
                  ItemLocationPairing(FIRE_TEMPLE_MQ_GS_FIRE_WALL_MAZE_SIDE_ROOM, []{return CanPlay(SongOfTime) || HoverBoots;}),
                    //Trick: CanPlay(SongOfTime) || HoverBoots || LogicFireMQFlameMaze
                  ItemLocationPairing(FIRE_TEMPLE_MQ_GS_FIRE_WALL_MAZE_CENTER,    []{return HasExplosives;}),
                  ItemLocationPairing(FIRE_TEMPLE_MQ_GS_ABOVE_FIRE_WALL_MAZE,     []{return CanUse(CanUseItem::Hookshot) && SmallKeys(FireTempleKeys, 5);}),
                    //Trick: (CanUse(CanUseItem::Hookshot) && SmallKeys(FireTempleKeys, 5)) || (LogicFireMQAboveMazeGS && CanUse(CanUseItem::Longshot))
  }, {});

  Exit FireTemple_MQ_BossRoom = Exit("Fire Temple MQ Boss Room", "Fire Temple", FIRE_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FireTempleClear, []{return true;}),
  }, {
                  //Locations
                  ItemLocationPairing(FIRE_TEMPLE_VOLVAGIA_HEART, []{return true;}),
                  ItemLocationPairing(VOLVAGIA, []{return true;}),
  }, {});

  Exit WaterTemple_MQ_Lobby = Exit("Water Temple MQ Lobby", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&WaterTempleClear, []{return BossKeyWaterTemple && CanUse(CanUseItem::Longshot);}),
  }, {
                  //Locations
                  ItemLocationPairing(WATER_TEMPLE_MORPHA_HEART, []{return BossKeyWaterTemple && CanUse(CanUseItem::Longshot);}),
                  ItemLocationPairing(MORPHA,                    []{return BossKeyWaterTemple && CanUse(CanUseItem::Longshot);}),
  }, {
                  //Exits
                  ExitPairing::Both(&LH_Main,                       []{return true;}),
                  ExitPairing::Both(&WaterTemple_MQ_Dive,           []{return (CanUse(CanUseItem::Zora_Tunic) || LogicFewerTunicRequirements) && CanUse(CanUseItem::Iron_Boots);}),
                  ExitPairing::Both(&WaterTemple_MQ_DarkLinkRegion, []{return SmallKeys(WaterTempleKeys, 1) && CanUse(CanUseItem::Longshot);}),
  });

  Exit WaterTemple_MQ_Dive = Exit("Water Temple MQ Dive", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(WATER_TEMPLE_MQ_MAP_CHEST,            []{return HasFireSource && CanUse(CanUseItem::Hookshot);}),
                  ItemLocationPairing(WATER_TEMPLE_MQ_CENTRAL_PILLAR_CHEST, []{return CanUse(CanUseItem::Zora_Tunic) && CanUse(CanUseItem::Hookshot) && (CanUse(CanUseItem::Dins_Fire) && CanPlay(SongOfTime));}),
                    //Trick: CanUse(CanUseItem::Zora_Tunic) && CanUse(CanUseItem::Hookshot) && ((LogicWaterMQCentralPillar && CanUse(CanUseItem::Fire_Arrows)) || (CanUse(CanUseItem::Dins_Fire) && CanPlay(SongOfTime)))
  }, {
                  //Exits
                  ExitPairing::Both(&WaterTemple_MQ_LoweredWaterLevels, []{return CanPlay(ZeldasLullaby);}),
  });

  Exit WaterTemple_MQ_LoweredWaterLevels = Exit("Water Temple MQ Lowered Water Levels", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(WATER_TEMPLE_MQ_COMPASS_CHEST,                []{return CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Dins_Fire) || WaterTemple_MQ_Lobby.Here([]{return CanUse(CanUseItem::Sticks) && HasExplosives;});}),
                  ItemLocationPairing(WATER_TEMPLE_MQ_LONGSHOT_CHEST,               []{return CanUse(CanUseItem::Hookshot);}),
                  ItemLocationPairing(WATER_TEMPLE_MQ_GS_LIZALFOS_HALLWAY,          []{return CanUse(CanUseItem::Dins_Fire);}),
                  ItemLocationPairing(WATER_TEMPLE_MQ_GS_BEFORE_UPPER_WATER_SWITCH, []{return CanUse(CanUseItem::Longshot);}),
  }, {});

  Exit WaterTemple_MQ_DarkLinkRegion = Exit("Water Temple MQ Dark Link Region", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPot, []{return true;}),
                  EventPairing(&NutPot,   []{return true;}),
  }, {
                  //Locations
                  ItemLocationPairing(WATER_TEMPLE_MQ_BOSS_KEY_CHEST, []{return (CanUse(CanUseItem::Zora_Tunic) || LogicFewerTunicRequirements) && CanUse(CanUseItem::Dins_Fire) && (LogicWaterDragonJumpDive || CanDive || CanUse(CanUseItem::Iron_Boots));}),
                  ItemLocationPairing(WATER_TEMPLE_MQ_GS_RIVER,       []{return true;}),
  }, {
                  //Exits
                  ExitPairing::Both(&WaterTemple_MQ_BasementGatedAreas, []{return (CanUse(CanUseItem::Zora_Tunic) || LogicFewerTunicRequirements) && CanUse(CanUseItem::Dins_Fire) && CanUse(CanUseItem::Iron_Boots);}),
  });

  Exit WaterTemple_MQ_BasementGatedAreas = Exit("Water Temple MQ Basement Gated Areas", "Water Temple", WATER_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(WATER_TEMPLE_MQ_FREESTANDING_KEY,         []{return HoverBoots || CanUse(CanUseItem::Scarecrow) || LogicWaterNorthBasementLedgeJump;}),
                  ItemLocationPairing(WATER_TEMPLE_MQ_GS_TRIPLE_WALL_TORCH,     []{return CanUse(CanUseItem::Fire_Arrows) && (HoverBoots || CanUse(CanUseItem::Scarecrow));}),
                  ItemLocationPairing(WATER_TEMPLE_MQ_GS_FREESTANDING_KEY_AREA, []{return SmallKeys(WaterTempleKeys, 2) && (HoverBoots || CanUse(CanUseItem::Scarecrow) || LogicWaterNorthBasementLedgeJump);}),
                    //Trick: LogicWaterMQLockedGS || (SmallKeys(WaterTempleKeys, 2) && (HoverBoots || CanUse(CanUseItem::Scarecrow) || LogicWaterNorthBasementLedgeJump))
  }, {});

  Exit SpiritTemple_MQ_Lobby = Exit("Spirit Temple MQ Lobby", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(SPIRIT_TEMPLE_MQ_ENTRANCE_FRONT_LEFT_CHEST, []{return true;}),
                  ItemLocationPairing(SPIRIT_TEMPLE_MQ_ENTRANCE_BACK_LEFT_CHEST,  []{return SpiritTemple_MQ_Lobby.Here([]{return CanBlastOrSmash;}) && (CanUse(CanUseItem::Slingshot) || CanUse(CanUseItem::Bow));}),
                  ItemLocationPairing(SPIRIT_TEMPLE_MQ_ENTRANCE_BACK_RIGHT_CHEST, []{return HasBombchus || CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Hookshot) || CanUse(CanUseItem::Slingshot) || CanUse(CanUseItem::Boomerang);}),
  }, {
                  //Exits
                  ExitPairing::Both(&Colossus_Main,         []{return true;}),
                  ExitPairing::Both(&SpiritTemple_MQ_Child, []{return IsChild;}),
                  ExitPairing::Both(&SpiritTemple_MQ_Adult, []{return HasBombchus && CanUse(CanUseItem::Longshot) && CanUse(CanUseItem::Silver_Gauntlets);}),
  });

  Exit SpiritTemple_MQ_Child = Exit("Spirit Temple MQ Child", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPot, []{return FairyPot || ((Sticks || KokiriSword) && HasBombchus && Slingshot);}),
  }, {
                  //Locations
                  ItemLocationPairing(SPIRIT_TEMPLE_MQ_CHILD_HAMMER_SWITCH_CHEST,  []{return SpiritTemple_MQ_Adult.Here([]{return SmallKeys(SpiritTempleKeys, 7) && Hammer;});}),
                  ItemLocationPairing(SPIRIT_TEMPLE_MQ_MAP_ROOM_ENEMY_CHEST,       []{return (Sticks || KokiriSword) && HasBombchus && Slingshot && CanUse(CanUseItem::Dins_Fire);}),
                  ItemLocationPairing(SPIRIT_TEMPLE_MQ_MAP_CHEST,                  []{return Sticks || KokiriSword || Bombs;}),
                  ItemLocationPairing(SPIRIT_TEMPLE_MQ_SILVER_BLOCK_HALLWAY_CHEST, []{return HasBombchus && SmallKeys(SpiritTempleKeys, 7) && Slingshot && (CanUse(CanUseItem::Dins_Fire) || (SpiritTemple_MQ_Adult.Here([]{return CanUse(CanUseItem::Fire_Arrows);})));}),
                    //Trick: HasBombchus && SmallKeys(SpiritTempleKeys, 7) && Slingshot && (CanUse(CanUseItem::Dins_Fire) || (SpiritTemple_MQ_Adult.Adult() && (CanUse(CanUseItem::Fire_Arrows) || (LogicSpiritMQFrozenEye && CanUse(CanUseItem::Bow) && CanPlay(SongOfTime)))))
  }, {
                  //Exits
                  ExitPairing::Both(&SpiritTemple_MQ_Shared, []{return HasBombchus && SmallKeys(SpiritTempleKeys, 2);}),
  });

  Exit SpiritTemple_MQ_Adult = Exit("Spirit Temple MQ Adult", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(SPIRIT_TEMPLE_MQ_CHILD_CLIMB_SOUTH_CHEST,     []{return SmallKeys(SpiritTempleKeys, 7);}),
                  ItemLocationPairing(SPIRIT_TEMPLE_MQ_STATUE_ROOM_LULLABY_CHEST,   []{return CanPlay(ZeldasLullaby);}),
                  ItemLocationPairing(SPIRIT_TEMPLE_MQ_STATUE_ROOM_INVISIBLE_CHEST, []{return (LogicLensSpiritMQ || CanUse(CanUseItem::Lens_of_Truth));}),
                  ItemLocationPairing(SPIRIT_TEMPLE_MQ_BEAMOS_ROOM_CHEST,           []{return SmallKeys(SpiritTempleKeys, 5);}),
                  ItemLocationPairing(SPIRIT_TEMPLE_MQ_CHEST_SWITCH_CHEST,          []{return SmallKeys(SpiritTempleKeys, 5) && CanPlay(SongOfTime);}),
                  ItemLocationPairing(SPIRIT_TEMPLE_MQ_BOSS_KEY_CHEST,              []{return SmallKeys(SpiritTempleKeys, 5) && CanPlay(SongOfTime) && MirrorShield;}),
                  ItemLocationPairing(SPIRIT_TEMPLE_MQ_GS_NINE_THRONES_ROOM_WEST,   []{return SmallKeys(SpiritTempleKeys, 7);}),
                  ItemLocationPairing(SPIRIT_TEMPLE_MQ_GS_NINE_THRONES_ROOM_NORTH,  []{return SmallKeys(SpiritTempleKeys, 7);}),
  }, {
                  //Exits
                  ExitPairing::Both(&SpiritTemple_MQ_LowerAdult,       []{return MirrorShield && CanUse(CanUseItem::Fire_Arrows);}),
                    //Trick: MirrorShield && (CanUse(CanUseItem::Fire_Arrows) || (LogicSpiritMQLowerAdult && CanUse(CanUseItem::Dins_Fire) && Bow))
                  ExitPairing::Both(&SpiritTemple_MQ_Shared,           []{return true;}),
                  ExitPairing::Both(&SpiritTemple_MQ_BossArea,         []{return SmallKeys(SpiritTempleKeys, 6) && CanPlay(ZeldasLullaby) && Hammer;}),
                  ExitPairing::Both(&SpiritTemple_MQ_MirrorShieldHand, []{return SmallKeys(SpiritTempleKeys, 5) && CanPlay(SongOfTime) && (LogicLensSpiritMQ || CanUse(CanUseItem::Lens_of_Truth));}),
  });

  Exit SpiritTemple_MQ_Shared = Exit("Spirit Temple MQ Shared", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(SPIRIT_TEMPLE_MQ_CHILD_CLIMB_NORTH_CHEST, []{return SmallKeys(SpiritTempleKeys, 6);}),
                  ItemLocationPairing(SPIRIT_TEMPLE_MQ_COMPASS_CHEST,           []{return (CanUse(CanUseItem::Slingshot) && SmallKeys(SpiritTempleKeys, 7)) || CanUse(CanUseItem::Bow) || (Bow && Slingshot);}),
                  ItemLocationPairing(SPIRIT_TEMPLE_MQ_SUN_BLOCK_ROOM_CHEST,    []{return CanPlay(SongOfTime) || IsAdult;}),
                    //Trick: CanPlay(SongOfTime) || LogicSpiritMQSunBlockSoT || IsAdult
                  ItemLocationPairing(SPIRIT_TEMPLE_MQ_GS_SUN_BLOCK_ROOM,       []{return IsAdult;}),
                    //Trick: (LogicSpiritMQSunBlockGS && Boomerange && (CanPlay(SongOfTime) || LogicSpiritMQSunBlockSoT)) || IsAdult
   }, {
                  //Exits
                  ExitPairing::Both(&SpiritTemple_MQ_SilverGauntletsHand, []{return (SmallKeys(SpiritTempleKeys, 7) && (CanPlay(SongOfTime) || IsAdult)) || (SmallKeys(SpiritTempleKeys, 4) && CanPlay(SongOfTime) && (LogicLensSpiritMQ || CanUse(CanUseItem::Lens_of_Truth)));}),
                    //Trick: (SmallKeys(SpiritTempleKeys, 7) && (CanPlay(SongOfTime) || LogicSpiritMQSunBlockSoT || IsAdult)) || (SmallKeys(SpiritTempleKeys, 4) && CanPlay(SongOfTime) && (LogicLensSpiritMQ || CanUse(CanUseItem::Lens_of_Truth)))
                  ExitPairing::Both(&Colossus_Main,                       []{return (SmallKeys(SpiritTempleKeys, 7) && (CanPlay(SongOfTime) || IsAdult)) || (SmallKeys(SpiritTempleKeys, 4) && CanPlay(SongOfTime) && (LogicLensSpiritMQ || CanUse(CanUseItem::Lens_of_Truth)) && IsAdult);}),
                    //Trick: (SmallKeys(SpiritTempleKeys, 7) && (CanPlay(SongOfTime) || LogicSpiritMQSunBlockSoT || IsAdult)) || (SmallKeys(SpiritTempleKeys, 4) && CanPlay(SongOfTime) && (LogicLensSpiritMQ || CanUse(CanUseItem::Lens_of_Truth)) && IsAdult)
  });

  Exit SpiritTemple_MQ_LowerAdult = Exit("Spirit Temple MQ Lower Adult", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(SPIRIT_TEMPLE_MQ_LEEVER_ROOM_CHEST,          []{return true;}),
                  ItemLocationPairing(SPIRIT_TEMPLE_MQ_SYMPHONY_ROOM_CHEST,        []{return SmallKeys(SpiritTempleKeys, 7) && Hammer && Ocarina && SongOfTime && EponasSong && SunsSong && SongOfStorms && ZeldasLullaby;}),
                  ItemLocationPairing(SPIRIT_TEMPLE_MQ_ENTRANCE_FRONT_RIGHT_CHEST, []{return Hammer;}),
                  ItemLocationPairing(SPIRIT_TEMPLE_MQ_GS_LEEVER_ROOM,             []{return true;}),
                  ItemLocationPairing(SPIRIT_TEMPLE_MQ_GS_SYMPHONY_ROOM,           []{return SmallKeys(SpiritTempleKeys, 7) && Hammer && Ocarina && SongOfTime && EponasSong && SunsSong && SongOfStorms && ZeldasLullaby;}),
  }, {});

  Exit SpiritTemple_MQ_BossArea = Exit("Spirit Temple MQ Boss Area", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&SpiritTempleClear, []{return SpiritTempleClear || (MirrorShield && BossKeySpiritTemple);})
  }, {
                  //Locations
                  ItemLocationPairing(SPIRIT_TEMPLE_MQ_MIRROR_PUZZLE_INVISIBLE_CHEST, []{return LogicLensSpiritMQ || CanUse(CanUseItem::Lens_of_Truth);}),
                  ItemLocationPairing(SPIRIT_TEMPLE_TWINROVA_HEART,                   []{return MirrorShield && BossKeySpiritTemple;}),
                  ItemLocationPairing(TWINROVA,                                       []{return MirrorShield && BossKeySpiritTemple;}),
  }, {});

  Exit SpiritTemple_MQ_MirrorShieldHand = Exit("Spirit Temple MQ Mirror Shield Hand", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(SPIRIT_TEMPLE_MIRROR_SHIELD_CHEST, []{return true;}),
  }, {});

  Exit SpiritTemple_MQ_SilverGauntletsHand = Exit("Spirit Temple MQ Silver Gauntlets Hand", "Spirit Temple", SPIRIT_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(SPIRIT_TEMPLE_SILVER_GAUNTLETS_CHEST, []{return true;}),
  }, {});

  Exit ShadowTemple_MQ_Entryway = Exit("Shadow Temple MQ Entryway", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&GY_WarpPadRegion,          []{return true;}),
                  ExitPairing::Both(&ShadowTemple_MQ_Beginning, []{return (LogicLensShadowMQ || CanUse(CanUseItem::Lens_of_Truth)) && (CanUse(CanUseItem::Hover_Boots) || CanUse(CanUseItem::Hookshot));}),
  });

  Exit ShadowTemple_MQ_Beginning = Exit("Shadow Temple MQ Beginning", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&ShadowTemple_MQ_Entryway,     []{return true;}),
                  ExitPairing::Both(&ShadowTemple_MQ_FirstBeamos,  []{return CanUse(CanUseItem::Fire_Arrows) || HoverBoots;}),
                    //Trick: CanUse(CanUseItem::Fire_Arrows) || HoverBoots || (LogicShadowMQGap && CanUse(CanUseItem::Longshot))
                  ExitPairing::Both(&ShadowTemple_MQ_DeadHandArea, []{return HasExplosives && SmallKeys(ShadowTempleKeys, 6);}),
  });

  Exit ShadowTemple_MQ_DeadHandArea = Exit("Shadow Temple MQ Dead Hand Area", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(SHADOW_TEMPLE_MQ_COMPASS_CHEST,     []{return true;}),
                  ItemLocationPairing(SHADOW_TEMPLE_MQ_HOVER_BOOTS_CHEST, []{return CanPlay(SongOfTime) && Bow;}),
  }, {});

  Exit ShadowTemple_MQ_FirstBeamos = Exit("Shadow Temple MQ First Beamos", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(SHADOW_TEMPLE_MQ_MAP_CHEST,                 []{return true;}),
                  ItemLocationPairing(SHADOW_TEMPLE_MQ_EARLY_GIBDOS_CHEST,        []{return true;}),
                  ItemLocationPairing(SHADOW_TEMPLE_MQ_NEAR_SHIP_INVISIBLE_CHEST, []{return true;}),
  }, {
                  //Exits
                  ExitPairing::Both(&ShadowTemple_MQ_UpperHugePit, []{return HasExplosives && SmallKeys(ShadowTempleKeys, 2);}),
  });

  Exit ShadowTemple_MQ_UpperHugePit = Exit("Shadow Temple MQ Upper Huge Pit", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(SHADOW_TEMPLE_MQ_INVISIBLE_BLADES_VISIBLE_CHEST,   []{return CanPlay(SongOfTime);}),
                    //Trick: CanPlay(SongOfTime) || (LogicShadowMQInvisibleBlades && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO))
                  ItemLocationPairing(SHADOW_TEMPLE_MQ_INVISIBLE_BLADES_INVISIBLE_CHEST, []{return CanPlay(SongOfTime);}),
                    //Trick: CanPlay(SongOfTime) || (LogicShadowMQInvisibleBlades && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO))
  }, {
                  //Exits
                  ExitPairing::Both(&ShadowTemple_MQ_LowerHugePit, []{return HasFireSource;}),
                    //Trick: HasFireSource || LogicShadowMQHugePit
  });

  Exit ShadowTemple_MQ_LowerHugePit = Exit("Shadow Temple MQ Lower Huge Pit", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(SHADOW_TEMPLE_MQ_BEAMOS_SILVER_RUPEES_CHEST,  []{return CanUse(CanUseItem::Longshot);}),
                  ItemLocationPairing(SHADOW_TEMPLE_MQ_FALLING_SPIKES_LOWER_CHEST,  []{return true;}),
                  ItemLocationPairing(SHADOW_TEMPLE_MQ_FALLING_SPIKES_UPPER_CHEST,  []{return (LogicShadowUmbrella && HoverBoots) || GoronBracelet;}),
                  ItemLocationPairing(SHADOW_TEMPLE_MQ_FALLING_SPIKES_SWITCH_CHEST, []{return (LogicShadowUmbrella && HoverBoots) || GoronBracelet;}),
                  ItemLocationPairing(SHADOW_TEMPLE_MQ_INVISIBLE_SPIKES_CHEST,      []{return HoverBoots && SmallKeys(ShadowTempleKeys, 3) && (LogicLensShadowMQBack || CanUse(CanUseItem::Lens_of_Truth));}),
                  ItemLocationPairing(SHADOW_TEMPLE_MQ_STALFOS_ROOM_CHEST,          []{return HoverBoots && SmallKeys(ShadowTempleKeys, 3) && Hookshot && (LogicLensShadowMQBack || CanUse(CanUseItem::Lens_of_Truth));}),
                  ItemLocationPairing(SHADOW_TEMPLE_MQ_GS_FALLING_SPIKES_ROOM,      []{return Hookshot;}),
  }, {
                  //Exits
                  ExitPairing::Both(&ShadowTemple_MQ_WindTunnel, []{return HoverBoots && (LogicLensShadowMQBack || CanUse(CanUseItem::Lens_of_Truth)) && Hookshot && SmallKeys(ShadowTempleKeys, 4);}),
  });

  Exit ShadowTemple_MQ_WindTunnel = Exit("Shadow Temple MQ Wind Tunnel", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&NutPot, []{return true;}),
  }, {
                  //Locations
                  ItemLocationPairing(SHADOW_TEMPLE_MQ_WIND_HINT_CHEST,         []{return true;}),
                  ItemLocationPairing(SHADOW_TEMPLE_MQ_AFTER_WIND_ENEMY_CHEST,  []{return true;}),
                  ItemLocationPairing(SHADOW_TEMPLE_MQ_AFTER_WIND_HIDDEN_CHEST, []{return true;}),
                  ItemLocationPairing(SHADOW_TEMPLE_MQ_GS_WIND_HINT_ROOM,       []{return true;}),
                  ItemLocationPairing(SHADOW_TEMPLE_MQ_GS_AFTER_WIND,           []{return true;}),
  }, {
                  //Exits
                  ExitPairing::Both(&ShadowTemple_MQ_BeyondBoat, []{return CanPlay(ZeldasLullaby) && SmallKeys(ShadowTempleKeys, 5);}),
  });

  Exit ShadowTemple_MQ_BeyondBoat = Exit("Shadow Temple MQ Beyond Boat", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&ShadowTempleClear, []{return ShadowTempleClear || ((Bow || (LogicShadowStatue && HasBombchus)) && BossKeyShadowTemple);})
  }, {
                  //Locations
                  ItemLocationPairing(SHADOW_TEMPLE_BONGO_BONGO_HEART, []{return (Bow || (LogicShadowStatue && HasBombchus)) && BossKeyShadowTemple;}),
                  ItemLocationPairing(BONGO_BONGO,                     []{return (Bow || (LogicShadowStatue && HasBombchus)) && BossKeyShadowTemple;}),
                  ItemLocationPairing(SHADOW_TEMPLE_MQ_GS_AFTER_SHIP,  []{return true;}),
                  ItemLocationPairing(SHADOW_TEMPLE_MQ_GS_NEAR_BOSS,   []{return Bow || (LogicShadowStatue && HasBombchus);}),
  }, {
                  //Exits
                  ExitPairing::Both(&ShadowTemple_MQ_InvisibleMaze, []{return Bow && CanPlay(SongOfTime) && CanUse(CanUseItem::Longshot);}),
  });

  Exit ShadowTemple_MQ_InvisibleMaze = Exit("Shadow Temple MQ Invisible Maze", "Shadow Temple", SHADOW_TEMPLE, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(SHADOW_TEMPLE_MQ_SPIKE_WALLS_LEFT_CHEST, []{return CanUse(CanUseItem::Dins_Fire) && SmallKeys(ShadowTempleKeys, 6);}),
                  ItemLocationPairing(SHADOW_TEMPLE_MQ_BOSS_KEY_CHEST,         []{return CanUse(CanUseItem::Dins_Fire) && SmallKeys(ShadowTempleKeys, 6);}),
                  ItemLocationPairing(SHADOW_TEMPLE_MQ_BOMB_FLOWER_CHEST,      []{return true;}),
                  ItemLocationPairing(SHADOW_TEMPLE_MQ_FREESTANDING_KEY,       []{return true;}),
  }, {});

  Exit BottomOfTheWell_MQ = Exit("Bottom of the Well MQ", "Bottom of the Well", BOTTOM_OF_THE_WELL, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&Kak_Main,                     []{return true;}),
                  ExitPairing::Both(&BottomOfTheWell_MQ_Perimeter, []{return IsChild;}),
  });

  Exit BottomOfTheWell_MQ_Perimeter = Exit("Bottom of the Well MQ Perimeter", "Bottom of the Well", BOTTOM_OF_THE_WELL, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  //EventPairing(&WallFairy, []{return WallFairy || Slingshot;}),
  }, {
                  //Locations
                  ItemLocationPairing(BOTTOM_OF_THE_WELL_MQ_COMPASS_CHEST,              []{return KokiriSword || (Sticks && LogicChildDeadhand);}),
                  ItemLocationPairing(BOTTOM_OF_THE_WELL_MQ_DEAD_HAND_FREESTANDING_KEY, []{return HasExplosives;}),
                    //Trick: HasExplosives || (LogicBotWMQDeadHandKey && Boomerang)
                  ItemLocationPairing(BOTTOM_OF_THE_WELL_MQ_GS_BASEMENT,                []{return CanChildAttack;}),
                  ItemLocationPairing(BOTTOM_OF_THE_WELL_MQ_GS_COFFIN_ROOM,             []{return CanChildAttack && SmallKeys(BottomOfTheWellKeys, 2);}),
  }, {
                  //Exits
                  ExitPairing::Both(&BottomOfTheWell_MQ,        []{return true;}),
                  ExitPairing::Both(&BottomOfTheWell_MQ_Middle, []{return CanPlay(ZeldasLullaby);}),
                    //Trick: CanPlay(ZeldasLullaby) || (LogicBotWMQPits && HasExplosives)
  });

  Exit BottomOfTheWell_MQ_Middle = Exit("Bottom of the Well MQ Middle", "Bottom of the Well", BOTTOM_OF_THE_WELL, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(BOTTOM_OF_THE_WELL_MQ_MAP_CHEST,                        []{return true;}),
                  ItemLocationPairing(BOTTOM_OF_THE_WELL_MQ_LENS_OF_TRUTH_CHEST,              []{return HasExplosives && SmallKeys(BottomOfTheWellKeys, 2);}),
                  ItemLocationPairing(BOTTOM_OF_THE_WELL_MQ_EAST_INNER_ROOM_FREESTANDING_KEY, []{return true;}),
                  ItemLocationPairing(BOTTOM_OF_THE_WELL_MQ_GS_WEST_INNER_ROOM,               []{return CanChildAttack && HasExplosives;}),
                    //Trick: CanChildAttack && (LogicBotWMQPits || HasExplosives)
  }, {
                  //Exits
                  ExitPairing::Both(&BottomOfTheWell_MQ_Perimeter, []{return true;}),
  });

  Exit IceCavern_MQ_Beginning = Exit("Ice Cavern MQ Beginning", "Ice Cavern", ICE_CAVERN, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPot, []{return true;}),
  }, {}, {
                  //Exits
                  ExitPairing::Both(&ZF_Main,                      []{return true;}),
                  ExitPairing::Both(&IceCavern_MQ_MapRoom,         []{return IsAdult || CanUse(CanUseItem::Dins_Fire) || (HasExplosives && (CanUse(CanUseItem::Sticks) || CanUse(CanUseItem::Slingshot) || KokiriSword));}),
                  ExitPairing::Both(&IceCavern_MQ_CompassRoom,     []{return IsAdult && BlueFire;}),
                  ExitPairing::Both(&IceCavern_MQ_IronBootsRegion, []{return BlueFire;}),
  });

  Exit IceCavern_MQ_MapRoom = Exit("Ice Cavern MQ Map Room", "Ice Cavern", ICE_CAVERN, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&BlueFireAccess,  []{return BlueFireAccess || HasBottle;}),
  }, {
                  //Locations
                  ItemLocationPairing(ICE_CAVERN_MQ_MAP_CHEST, []{return BlueFire && (IsAdult || CanUse(CanUseItem::Sticks) || KokiriSword || CanUseProjectile);}),
  }, {});

  Exit IceCavern_MQ_IronBootsRegion = Exit("Ice Cavern MQ Iron Boots Region", "Ice Cavern", ICE_CAVERN, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(ICE_CAVERN_MQ_IRON_BOOTS_CHEST, []{return IsAdult;}),
                  ItemLocationPairing(SHEIK_IN_ICE_CAVERN,            []{return IsAdult;}),
                  ItemLocationPairing(ICE_CAVERN_MQ_GS_ICE_BLOCK,     []{return IsAdult || CanChildAttack;}),
                  ItemLocationPairing(ICE_CAVERN_MQ_GS_SCARECROW,     []{return CanUse(CanUseItem::Scarecrow) || (HoverBoots && CanUse(CanUseItem::Longshot));}),
                    //Tricks: CanUse(CanUseItem::Scarecrow) || (HoverBoots && CanUse(CanUseItem::Longshot)) || (LogicIceMQScarecrow && IsAdult)
  }, {});

  Exit IceCavern_MQ_CompassRoom = Exit("Ice Cavern MQ Compass Room", "Ice Cavern", ICE_CAVERN, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(ICE_CAVERN_MQ_COMPASS_CHEST,    []{return true;}),
                  ItemLocationPairing(ICE_CAVERN_MQ_FREESTANDING_POH, []{return HasExplosives;}),
                  ItemLocationPairing(ICE_CAVERN_MQ_GS_RED_ICE,       []{return CanPlay(SongOfTime);}),
                    //Trick: CanPlay(SongOfTime) || LogicIceMQRedIceGS
  }, {});

  Exit GerudoTrainingGrounds_MQ_Lobby = Exit("Gerudo Training Grounds MQ Lobby", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_MQ_LOBBY_LEFT_CHEST,       []{return true;}),
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_MQ_LOBBY_RIGHT_CHEST,      []{return true;}),
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_MQ_HIDDEN_CEILING_CHEST,   []{return LogicLensGtgMQ || CanUse(CanUseItem::Lens_of_Truth);}),
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_MQ_MAZE_PATH_FIRST_CHEST,  []{return true;}),
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_MQ_MAZE_PATH_SECOND_CHEST, []{return true;}),
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_MQ_MAZE_PATH_THIRD_CHEST,  []{return SmallKeys(GerudoTrainingGroundsKeys, 1);}),
  }, {
                  //Exits
                  ExitPairing::Both(&GF_Main,                            []{return true;}),
                  ExitPairing::Both(&GerudoTrainingGrounds_MQ_LeftSide,  []{return GerudoTrainingGrounds_MQ_Lobby.Here([]{return HasFireSource;});}),
                  ExitPairing::Both(&GerudoTrainingGrounds_MQ_RightSide, []{return GerudoTrainingGrounds_MQ_Lobby.Here([]{return CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Slingshot);});}),
  });

  Exit GerudoTrainingGrounds_MQ_RightSide = Exit("Gerudo Training Grounds MQ Right Side", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  //EventPairing(&WallFairy, []{return WallFairy || CanUse(CanUseItem::Bow);}),
  }, {
                  //Locations
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_MQ_DINOLFOS_CHEST, []{return IsAdult;}),
  }, {
                  //Exits
                  ExitPairing::Both(&GerudoTrainingGrounds_MQ_Underwater, []{return (Bow || CanUse(CanUseItem::Longshot)) && CanUse(CanUseItem::Hover_Boots);}),
  });

  Exit GerudoTrainingGrounds_MQ_Underwater = Exit("Gerudo Training Grounds MQ Underwater", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_MQ_UNDERWATER_SILVER_RUPEE_CHEST, []{return HasFireSource && CanUse(CanUseItem::Iron_Boots) && (LogicFewerTunicRequirements || CanUse(CanUseItem::Zora_Tunic)) && CanTakeDamage;}),
  }, {});

  Exit GerudoTrainingGrounds_MQ_LeftSide = Exit("Gerudo Training Grounds MQ Left Side", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_MQ_FIRST_IRON_KNUCKLE_CHEST, []{return IsAdult || KokiriSword || HasExplosives;}),
  }, {
                  //Exits
                  ExitPairing::Both(&GerudoTrainingGrounds_MQ_StalfosRoom, []{return CanUse(CanUseItem::Longshot);}),
                    //Trick: CanUse(CanUseItem::Longshot) || LogicGtgMQWithoutHookshot || (LogicGtgMQWithHookshot && CanUse(CanUseItem::Hookshot))
  });

  Exit GerudoTrainingGrounds_MQ_StalfosRoom = Exit("Gerudo Training Grounds MQ Stalfos Room", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&BlueFireAccess,  []{return BlueFireAccess || HasBottle;}),
  }, {
                  //Locations
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_MQ_BEFORE_HEAVY_BLOCK_CHEST, []{return IsAdult;}),
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_MQ_HEAVY_BLOCK_CHEST,        []{return CanUse(CanUseItem::Silver_Gauntlets);}),
  }, {
                  //Exits
                  ExitPairing::Both(&GerudoTrainingGrounds_MQ_BackAreas, []{return IsAdult && (LogicLensGtgMQ || CanUse(CanUseItem::Lens_of_Truth)) && BlueFire && CanPlay(SongOfTime);}),
                    //Trick: IsAdult && (LogicLensGtgMQ || CanUse(CanUseItem::Lens_of_Truth)) && BlueFire && (CanPlay(SongOfTime) || (LogicGtgFakeWall && CanUse(CanUseItem::Hover_Boots)))
  });

  Exit GerudoTrainingGrounds_MQ_BackAreas = Exit("Gerudo Training Grounds MQ Back Areas", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_MQ_EYE_STATUE_CHEST,          []{return Bow;}),
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_MQ_SECOND_IRON_KNUCKLE_CHEST, []{return true;}),
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_MQ_FLAME_CIRCLE_CHEST,        []{return CanUse(CanUseItem::Hookshot) || Bow || HasExplosives;}),
  }, {
                  //Exits
                  ExitPairing::Both(&GerudoTrainingGrounds_MQ_CentralMazeRight, []{return Hammer;}),
                  ExitPairing::Both(&GerudoTrainingGrounds_MQ_RightSide,        []{return CanUse(CanUseItem::Longshot);}),
  });

  Exit GerudoTrainingGrounds_MQ_CentralMazeRight = Exit("Gerudo Training Grounds MQ Central Maze Right", "Gerudo Training Grounds", GERUDO_TRAINING_GROUNDS, NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_MQ_MAZE_RIGHT_CENTRAL_CHEST, []{return true;}),
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_MQ_MAZE_RIGHT_SIDE_CHEST,    []{return true;}),
                  ItemLocationPairing(GERUDO_TRAINING_GROUNDS_MQ_ICE_ARROWS_CHEST,         []{return SmallKeys(GerudoTrainingGroundsKeys, 3);}),
  }, {
                  //Exits
                  ExitPairing::Both(&GerudoTrainingGrounds_MQ_Underwater, []{return CanUse(CanUseItem::Longshot) || (CanUse(CanUseItem::Hookshot) && Bow);}),
                  ExitPairing::Both(&GerudoTrainingGrounds_MQ_RightSide,  []{return CanUse(CanUseItem::Hookshot);}),
  });

  Exit GanonsCastle_MQ_Lobby = Exit("Ganon's Castle MQ Lobby", "Ganons Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&OGC_Grounds,                 []{return true;}),
                  ExitPairing::Both(&GanonsCastle_MQ_ForestTrial, []{return true;}),
                  ExitPairing::Both(&GanonsCastle_MQ_FireTrial,   []{return true;}),
                  ExitPairing::Both(&GanonsCastle_MQ_WaterTrial,  []{return true;}),
                  ExitPairing::Both(&GanonsCastle_MQ_ShadowTrial, []{return true;}),
                  ExitPairing::Both(&GanonsCastle_MQ_SpiritTrial, []{return true;}),
                  ExitPairing::Both(&GanonsCastle_MQ_LightTrial,  []{return CanUse(CanUseItem::Golden_Gauntlets);}),
                  ExitPairing::Both(&GanonsCastle_Tower,          []{return (ForestTrialClear || Trial::ForestTrial.IsSkipped()) &&
                                                                            (FireTrialClear   || Trial::FireTrial.IsSkipped())   &&
                                                                            (WaterTrialClear  || Trial::WaterTrial.IsSkipped())  &&
                                                                            (ShadowTrialClear || Trial::ShadowTrial.IsSkipped()) &&
                                                                            (SpiritTrialClear || Trial::SpiritTrial.IsSkipped()) &&
                                                                            (LightTrialClear  || Trial::LightTrial.IsSkipped());}),
                  ExitPairing::Both(&GanonsCastle_MQ_DekuScrubs,  []{return LogicLensCastleMQ || CanUse(CanUseItem::Lens_of_Truth);}),
  });

  Exit GanonsCastle_MQ_DekuScrubs = Exit("Ganon's Castle MQ Deku Scrubs", "Ganon's Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FreeFairies, []{return true;}),
  }, {
                  //Locations
                  ItemLocationPairing(GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER_LEFT,  []{return true;}),
                  ItemLocationPairing(GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER,       []{return true;}),
                  ItemLocationPairing(GANONS_CASTLE_MQ_DEKU_SCRUB_CENTER_RIGHT, []{return true;}),
                  ItemLocationPairing(GANONS_CASTLE_MQ_DEKU_SCRUB_LEFT,         []{return true;}),
                  ItemLocationPairing(GANONS_CASTLE_MQ_DEKU_SCRUB_RIGHT,        []{return true;}),
  }, {});

  Exit GanonsCastle_MQ_ForestTrial = Exit("Ganon's Castle MQ Forest Trial", "Ganons Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&ForestTrialClear, []{return CanUse(CanUseItem::Light_Arrows) && CanPlay(SongOfTime);}),
  }, {
                  //Locations
                  ItemLocationPairing(GANONS_CASTLE_MQ_FOREST_TRIAL_EYE_SWITCH_CHEST,        []{return Bow;}),
                  ItemLocationPairing(GANONS_CASTLE_MQ_FOREST_TRIAL_FROZEN_EYE_SWITCH_CHEST, []{return HasFireSource;}),
                  ItemLocationPairing(GANONS_CASTLE_MQ_FOREST_TRIAL_FREESTANDING_KEY,        []{return Hookshot;}),
  }, {});

  Exit GanonsCastle_MQ_FireTrial = Exit("Ganon's Castle MQ Fire Trial", "Ganons Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FireTrialClear, []{return CanUse(CanUseItem::Goron_Tunic) && CanUse(CanUseItem::Golden_Gauntlets) && CanUse(CanUseItem::Light_Arrows) && (CanUse(CanUseItem::Longshot) || HoverBoots);}),
                    //Trick: CanUse(CanUseItem::Goron_Tunic) && CanUse(CanUseItem::Golden_Gauntlets) && CanUse(CanUseItem::Light_Arrows) && (CanUse(CanUseItem::Longshot) || HoverBoots || (LogicFireTrialMQ && CanUse(CanUseItem::Hookshot)))
  }, {}, {});

  Exit GanonsCastle_MQ_WaterTrial = Exit("Ganon's Castle MQ Water Trial", "Ganons Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&WaterTrialClear, []{return BlueFire && CanUse(CanUseItem::Light_Arrows) && SmallKeys(GanonsCastleKeys, 3);}),
                  EventPairing(&BlueFireAccess,  []{return BlueFireAccess || HasBottle;}),
  }, {
                  //Locations
                  ItemLocationPairing(GANONS_CASTLE_MQ_WATER_TRIAL_CHEST, []{return BlueFire;}),
  }, {});

  Exit GanonsCastle_MQ_ShadowTrial = Exit("Ganon's Castle MQ Shadow Trial", "Ganons Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&ShadowTrialClear, []{return CanUse(CanUseItem::Light_Arrows) && (LogicLensCastleMQ || CanUse(CanUseItem::Lens_of_Truth)) && (HoverBoots || (Hookshot && HasFireSource));}),
                    //Trick: CanUse(CanUseItem::Light_Arrows) && (LogicLensCastleMQ || CanUse(CanUseItem::Lens_of_Truth)) && (HoverBoots || (Hookshot && (HasFireSource || LogicShadowTrialMQ)))
  }, {
                  //Locations
                  ItemLocationPairing(GANONS_CASTLE_MQ_SHADOW_TRIAL_BOMB_FLOWER_CHEST, []{return (Bow && (Hookshot || HoverBoots)) || (HoverBoots && (LogicLensCastleMQ || CanUse(CanUseItem::Lens_of_Truth)) && (HasExplosives || GoronBracelet || CanUse(CanUseItem::Dins_Fire)));}),
                  ItemLocationPairing(GANONS_CASTLE_MQ_SHADOW_TRIAL_EYE_SWITCH_CHEST,  []{return Bow && (LogicLensCastleMQ || CanUse(CanUseItem::Lens_of_Truth)) && (HoverBoots || (Hookshot && HasFireSource));}),
                    //Trick: Bow && (LogicLensCastleMQ || CanUse(CanUseItem::Lens_of_Truth)) && (HoverBoots || (Hookshot && (HasFireSource || LogicShadowTrialMQ)))
  }, {});

  Exit GanonsCastle_MQ_SpiritTrial = Exit("Ganon's Castle MQ Spirit Castle", "Ganons Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&SpiritTrialClear, []{return CanUse(CanUseItem::Light_Arrows) && Hammer && HasBombchus && FireArrows && MirrorShield;}),
                  EventPairing(&NutPot,           []{return NutPot || (Hammer && HasBombchus && CanUse(CanUseItem::Fire_Arrows) && MirrorShield);}),
  }, {
                  //Locations
                  ItemLocationPairing(GANONS_CASTLE_MQ_SPIRIT_TRIAL_FIRST_CHEST,             []{return Bow && Hammer;}),
                  ItemLocationPairing(GANONS_CASTLE_MQ_SPIRIT_TRIAL_INVISIBLE_CHEST,         []{return Bow && Hammer && HasBombchus && (LogicLensCastleMQ || CanUse(CanUseItem::Lens_of_Truth));}),
                  ItemLocationPairing(GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_FRONT_LEFT_CHEST,    []{return Hammer && HasBombchus && CanUse(CanUseItem::Fire_Arrows) && MirrorShield;}),
                  ItemLocationPairing(GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_BACK_LEFT_CHEST,     []{return Hammer && HasBombchus && CanUse(CanUseItem::Fire_Arrows) && MirrorShield;}),
                  ItemLocationPairing(GANONS_CASTLE_MQ_SPIRIT_TRIAL_GOLDEN_GAUNTLETS_CHEST,  []{return Hammer && HasBombchus && CanUse(CanUseItem::Fire_Arrows) && MirrorShield;}),
                  ItemLocationPairing(GANONS_CASTLE_MQ_SPIRIT_TRIAL_SUN_BACK_RIGHT_CHEST,    []{return Hammer && HasBombchus && CanUse(CanUseItem::Fire_Arrows) && MirrorShield;}),
  }, {});

  Exit GanonsCastle_MQ_LightTrial = Exit("Ganon's Castle MQ Light Trial", "Ganons Castle", GANONS_CASTLE, NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&LightTrialClear, []{return CanUse(CanUseItem::Light_Arrows) && SmallKeys(GanonsCastleKeys, 3) && (LogicLensCastleMQ || CanUse(CanUseItem::Lens_of_Truth)) && Hookshot;}),
                    //Trick: CanUse(CanUseItem::Light_Arrows) && SmallKeys(GanonsCastleKeys, 3) && (LogicLensCastleMQ || CanUse(CanUseItem::Lens_of_Truth)) && (Hookshot || LogicLightTrialMQ)
  }, {
                  //Locations
                  ItemLocationPairing(GANONS_CASTLE_MQ_LIGHT_TRIAL_LULLABY_CHEST, []{return CanPlay(ZeldasLullaby);}),
  }, {});

  /*
  //Events
}, {
  //Locations
}, {
  //Exits
*/

  std::array<Exit *, 291> allExits = {

    &Root,
    &RootExits,
    &KF_Main,
    &KF_LinksHouse,
    &KF_MidosHouse,
    &KF_SariasHouse,
    &KF_HouseOfTwins,
    &KF_KnowItAllHouse,
    &KF_KokiriShop,
    &KF_OutsideDekuTree,
    &KF_StormsGrotto,
    &LW_Main,
    &LW_BridgeFromForest,
    &LW_Bridge,
    &LW_ForestExit,
    &LW_BeyondMido,
    &LW_NearShortcutsGrotto,
    &LW_DekuTheater,
    &LW_ScrubsGrotto,
    &SFM_Entryway,
    &SFM_Main,
    &SFM_WolfosGrotto,
    &SFM_FairyGrotto,
    &SFM_StormsGrotto,
    &HF_Main,
    &HF_SoutheastGrotto,
    &HF_OpenGrotto,
    &HF_InsideFenceGrotto,
    &HF_CowGrotto,
    &HF_NearMarketGrotto,
    &HF_NearKakGrotto,
    &HF_FairyGrotto,
    &HF_NearKakGrotto,
    &HF_TektiteGrotto,
    &LH_Main,
    &LH_OwlFlight,
    &LH_Lab,
    &LH_FishingHole,
    &LH_Grotto,
    &GV_Main,
    &GV_Stream,
    &GV_CrateLedge,
    &GV_OctorokGrotto,
    &GV_FortressSide,
    &GV_CarpenterTent,
    &GV_StormsGrotto,
    &GF_Main,
    &GF_OutsideGate,
    &GF_StormsGrotto,
    &HW_NearFortress,
    &HW_Main,
    &HW_NearColossus,
    &Colossus_Main,
    &Colossus_GreatFairyFountain,
    &Colossus_Grotto,
    &MK_Entrance,
    &MK_Main,
    &MK_GuardHouse,
    &MK_Bazaar,
    &MK_MaskShop,
    &MK_ShootingGallery,
    &MK_BombchuBowling,
    &MK_TreasureChestGame,
    &MK_PotionShop,
    &MK_BombchuShop,
    &MK_DogLadyHouse,
    &MK_ManInGreenHouse,
    &ToT_Entrance,
    &ToT_Main,
    &ToT_BeyondDoorOfTime,
    &CastleGrounds,
    &HC_Grounds,
    &HC_Garden,
    &HC_GreatFairyFountain,
    &HC_StormsGrotto,
    &OGC_Grounds,
    &OGC_GreatFairyFountain,
    &Kak_Main,
    &Kak_CarpenterBossHouse,
    &Kak_HouseOfSkulltula,
    &Kak_ImpasHouse,
    &Kak_ImpasLedge,
    &Kak_ImpasHouseBack,
    &Kak_ImpasHouseNearCow,
    &Kak_Windmill,
    &Kak_Bazaar,
    &Kak_ShootingGallery,
    &Kak_PotionShopFront,
    &Kak_PotionShopBack,
    &Kak_Rooftop,
    &Kak_BehindGate,
    &Kak_Backyard,
    &Kak_OddMedicineBuilding,
    &Kak_RedeadGrotto,
    &Kak_OpenGrotto,
    &GY_Main,
    &GY_DampesGrave,
    &GY_DampesHouse,
    &GY_ShieldGrave,
    &GY_ComposersGrave,
    &GY_HeartPieceGrave,
    &GY_WarpPadRegion,
    &DMT_Main,
    &DMT_Summit,
    &DMT_OwlFlight,
    &DMT_GreatFairyFountain,
    &DMT_CowGrotto,
    &DMT_StormsGrotto,
    &GC_Main,
    &GC_WoodsWarp,
    &GC_DaruniasChamber,
    &GC_Shop,
    &GC_Grotto,
    &DMC_UpperLocal,
    &DMC_CentralLocal,
    &DMC_LowerLocal,
    &DMC_LowerNearby,
    &DMC_UpperNearby,
    &DMC_CentralNearby,
    &DMC_LadderAreaNearby,
    &DMC_UpperGrotto,
    &DMC_HammerGrotto,
    &DMC_GreatFairyFountain,
    &ZR_Front,
    &ZR_Main,
    &ZR_BehindWaterfall,
    &ZR_OpenGrotto,
    &ZR_FairyGrotto,
    &ZR_StormsGrotto,
    &ZD_Main,
    &ZD_BehindKingZora,
    &ZD_Shop,
    &ZD_StormsGrotto,
    &ZF_Main,
    &ZF_GreatFairyFountain,
    &LLR_Main,
    &LLR_TalonsHouse,
    &LLR_Stables,
    &LLR_Tower,
    &LLR_Grotto,
    &DekuTree_Lobby,
    &DekuTree_SlingshotRoom,
    &DekuTree_BasementBackRoom,
    &DekuTree_BossRoom,
    &DodongosCavern_Entryway,
    &DodongosCavern_Beginning,
    &DodongosCavern_Lobby,
    &DodongosCavern_Climb,
    &DodongosCavern_FarBridge,
    &DodongosCavern_BossArea,
    &JabuJabusBelly_Beginning,
    &JabuJabusBelly_Main,
    &JabuJabusBelly_Depths,
    &JabuJabusBelly_BossArea,
    &ForestTemple_Lobby,
    &ForestTemple_NWOutdoors,
    &ForestTemple_NEOutdoors,
    &ForestTemple_OutdoorsHighBalconies,
    &ForestTemple_FallingRoom,
    &ForestTemple_BlockPushRoom,
    &ForestTemple_StraightenedHall,
    &ForestTemple_OutsideUpperLedge,
    &ForestTemple_BowRegion,
    &ForestTemple_BossRegion,
    &FireTemple_Entrance,
    &FireTemple_Lower,
    &FireTemple_BigLavaRoom,
    &FireTemple_Middle,
    &FireTemple_Upper,
    &WaterTemple_Lobby,
    &WaterTemple_HighestWaterLevel,
    &WaterTemple_Dive,
    &WaterTemple_CrackedWall,
    &WaterTemple_NorthBasement,
    &WaterTemple_DragonStatue,
    &WaterTemple_MiddleWaterLevel,
    &WaterTemple_FallingPlatformRoom,
    &WaterTemple_DarkLinkRegion,
    &SpiritTemple_Lobby,
    &SpiritTemple_Child,
    &SpiritTemple_ChildClimb,
    &SpiritTemple_EarlyAdult,
    &SpiritTemple_CentralChamber,
    &SpiritTemple_OutdoorHands,
    &SpiritTemple_BeyondCentralLockedDoor,
    &SpiritTemple_BeyondFinalLockedDoor,
    &ShadowTemple_Entryway,
    &ShadowTemple_Beginning,
    &ShadowTemple_FirstBeamos,
    &ShadowTemple_HugePit,
    &ShadowTemple_WindTunnel,
    &ShadowTemple_BeyondBoat,
    &BottomOfTheWell,
    &BottomOfTheWell_MainArea,
    &IceCavern_Beginning,
    &IceCavern_Main,
    &GerudoTrainingGrounds_Lobby,
    &GerudoTrainingGrounds_CentralMaze,
    &GerudoTrainingGrounds_CentralMazeRight,
    &GerudoTrainingGrounds_LavaRoom,
    &GerudoTrainingGrounds_HammerRoom,
    &GerudoTrainingGrounds_EyeStatueLower,
    &GerudoTrainingGrounds_EyeStatueUpper,
    &GerudoTrainingGrounds_HeavyBlockRoom,
    &GerudoTrainingGrounds_LikeLikeRoom,
    &GanonsCastle_Lobby,
    &GanonsCastle_DekuScrubs,
    &GanonsCastle_ForestTrial,
    &GanonsCastle_FireTrial,
    &GanonsCastle_WaterTrial,
    &GanonsCastle_ShadowTrial,
    &GanonsCastle_SpiritTrial,
    &GanonsCastle_LightTrial,
    &GanonsCastle_Tower,
    &DekuTree_MQ_Lobby,
    &DekuTree_MQ_CompassRoom,
    &DekuTree_MQ_BasementWaterRoomFront,
    &DekuTree_MQ_BasementWaterRoomBack,
    &DekuTree_MQ_BasementBackRoom,
    &DekuTree_MQ_BasementLedge,
    &DodongosCavern_MQ_Beginning,
    &DodongosCavern_MQ_Lobby,
    &DodongosCavern_MQ_LowerRightSide,
    &DodongosCavern_MQ_BombBagArea,
    &DodongosCavern_MQ_BossArea,
    &JabuJabusBelly_MQ_Beginning,
    &JabuJabusBelly_MQ_Main,
    &JabuJabusBelly_MQ_Depths,
    &JabuJabusBelly_MQ_BossArea,
    &ForestTemple_MQ_Lobby,
    &ForestTemple_MQ_CentralArea,
    &ForestTemple_MQ_AfterBlockPuzzle,
    &ForestTemple_MQ_OutdoorLedge,
    &ForestTemple_MQ_NWOutdoors,
    &ForestTemple_MQ_NEOutdoors,
    &ForestTemple_MQ_OutdoorsTopLedges,
    &ForestTemple_MQ_NEOutdoorsLedge,
    &ForestTemple_MQ_BowRegion,
    &ForestTemple_MQ_FallingRoom,
    &ForestTemple_MQ_BossRegion,
    &FireTemple_MQ_Lower,
    &FireTemple_MQ_LowerLockedDoor,
    &FireTemple_MQ_BigLavaRoom,
    &FireTemple_MQ_LowerMaze,
    &FireTemple_MQ_UpperMaze,
    &FireTemple_MQ_Upper,
    &FireTemple_MQ_BossRoom,
    &WaterTemple_MQ_Lobby,
    &WaterTemple_MQ_Dive,
    &WaterTemple_MQ_LoweredWaterLevels,
    &WaterTemple_MQ_DarkLinkRegion,
    &WaterTemple_MQ_BasementGatedAreas,
    &SpiritTemple_MQ_Lobby,
    &SpiritTemple_MQ_Child,
    &SpiritTemple_MQ_Adult,
    &SpiritTemple_MQ_Shared,
    &SpiritTemple_MQ_LowerAdult,
    &SpiritTemple_MQ_BossArea,
    &SpiritTemple_MQ_MirrorShieldHand,
    &SpiritTemple_MQ_SilverGauntletsHand,
    &ShadowTemple_MQ_Entryway,
    &ShadowTemple_MQ_Beginning,
    &ShadowTemple_MQ_DeadHandArea,
    &ShadowTemple_MQ_FirstBeamos,
    &ShadowTemple_MQ_UpperHugePit,
    &ShadowTemple_MQ_LowerHugePit,
    &ShadowTemple_MQ_WindTunnel,
    &ShadowTemple_MQ_BeyondBoat,
    &ShadowTemple_MQ_InvisibleMaze,
    &BottomOfTheWell_MQ,
    &BottomOfTheWell_MQ_Perimeter,
    &BottomOfTheWell_MQ_Middle,
    &IceCavern_MQ_Beginning,
    &IceCavern_MQ_MapRoom,
    &IceCavern_MQ_IronBootsRegion,
    &IceCavern_MQ_CompassRoom,
    &GerudoTrainingGrounds_MQ_Lobby,
    &GerudoTrainingGrounds_MQ_RightSide,
    &GerudoTrainingGrounds_MQ_Underwater,
    &GerudoTrainingGrounds_MQ_LeftSide,
    &GerudoTrainingGrounds_MQ_StalfosRoom,
    &GerudoTrainingGrounds_MQ_BackAreas,
    &GerudoTrainingGrounds_MQ_CentralMazeRight,
    &GanonsCastle_MQ_Lobby,
    &GanonsCastle_MQ_DekuScrubs,
    &GanonsCastle_MQ_ForestTrial,
    &GanonsCastle_MQ_FireTrial,
    &GanonsCastle_MQ_WaterTrial,
    &GanonsCastle_MQ_ShadowTrial,
    &GanonsCastle_MQ_SpiritTrial,
    &GanonsCastle_MQ_LightTrial,
  };

  void AccessReset() {
    for (Exit* exit : allExits) {
      exit->ResetVariables();
    }

    if(Settings::HasNightStart) {
        if(Settings::ResolvedStartingAge == AGE_CHILD) {
          Exits::Root.nightChild = true;
        } else {
          Exits::Root.nightAdult = true;
        }
      } else {
        if(Settings::ResolvedStartingAge == AGE_CHILD) {
          Exits::Root.dayChild = true;
        } else {
          Exits::Root.dayAdult = true;
        }
    }
  }

  //Reset exits and clear items from locations
  void ResetAllLocations() {
    for (Exit* exit : allExits) {
      exit->ResetVariables();
      //Erase item from every location in this exit
      for (ItemLocationPairing& locPair : exit->locations) {
          u32 location = locPair.GetLocation();
          Location(location)->ResetVariables();
      }
    }

    if(Settings::HasNightStart) {
        if(Settings::ResolvedStartingAge == AGE_CHILD) {
          Exits::Root.nightChild = true;
        } else {
          Exits::Root.nightAdult = true;
        }
      } else {
        if(Settings::ResolvedStartingAge == AGE_CHILD) {
          Exits::Root.dayChild = true;
        } else {
          Exits::Root.dayAdult = true;
        }
    }
  }

  //We initially tried setting parent regions in the constructor of each exit.
  //For some reason this was causing bad builds of the application on linux systems,
  //so for now we're putting it into this function which runs when the app starts up
  void SetParentRegions() {
    for (Exit* exit : allExits) {
      //Set parent region for every exit's locations
      for (ItemLocationPairing& locPair : exit->locations) {
          u32 location = locPair.GetLocation();
          Location(location)->SetParentRegion(exit);
      }
    }
  }
}
