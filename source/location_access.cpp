#include "location_access.hpp"
#include "settings.hpp"
#include "logic.hpp"
#include "item_location.hpp"
#include "item_list.hpp"
#include "dungeon.hpp"
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


namespace Exits { //name, scene, hint, events, locations, exits

  Exit Root = Exit("Root", "", "Link's Pocket", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&LinksPocket, []{return true;})
                }, {
                  //Exits      Age
                  ExitPairing::Both(&RootExits, []{return true;})
  });

  Exit RootExits = Exit("Root Exits", "", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits      Age
                  ExitPairing::Both(&KF_LinksHouse,    []{return IsChild;}),
                  ExitPairing::Both(&ToT_Main,         []{return (CanPlay(PreludeOfLight)   && CanLeaveForest) || IsAdult;}),
                  ExitPairing::Both(&SFM_Main,         []{return  CanPlay(MinuetOfForest);}),
                  ExitPairing::Both(&DMC_CentralLocal, []{return  CanPlay(BoleroOfFire)     && CanLeaveForest;}),
                  ExitPairing::Both(&LH_Main,          []{return  CanPlay(SerenadeOfWater)  && CanLeaveForest;}),
                  ExitPairing::Both(&GY_WarpPadRegion, []{return  CanPlay(NocturneOfShadow) && CanLeaveForest;}),
                  ExitPairing::Both(&Colossus_Main,    []{return  CanPlay(RequiemOfSpirit)  && CanLeaveForest;})
  });

  Exit KF_Main = Exit("Kokiri Forest", "Kokiri Forest", "Kokiri Forest", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&BeanPlantFairy,           []{return BeanPlantFairy   || (KF_Main.CanPlantBean() && CanPlay(SongOfStorms));}),
                  EventPairing(&GossipStoneFairy,         []{return GossipStoneFairy || CanSummonGossipFairyWithoutSuns;}),
                  EventPairing(&ShowedMidoSwordAndShield, []{return OpenForest.Is(OPENFOREST_OPEN) || (IsChild && KokiriSword && DekuShield);}),
                }, {
                  //Locations
                  ItemLocationPairing(&KF_KokiriSwordChest,  []{return IsChild;}),
                  ItemLocationPairing(&KF_GS_KnowItAllHouse, []{return IsChild && CanChildAttack && AtNight && (HasNightStart || CanLeaveForest || CanPlay(SunsSong)) && CanGetNightTimeGS;}),
                  ItemLocationPairing(&KF_GS_BeanPatch,      []{return CanPlantBugs && CanChildAttack;}),
                  ItemLocationPairing(&KF_GS_HouseOfTwins,   []{return IsAdult && AtNight && CanUse(CanUseItem::Hookshot) && CanGetNightTimeGS;}),
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

  Exit KF_OutsideDekuTree = Exit("KF Outside Deku Tree", "Kokiri Forest", "Kokiri Forest", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&DekuBabaSticks, []{return DekuBabaSticks || ((IsAdult && !ShuffleDungeonEntrances) || KokiriSword || Boomerang);}),
                  EventPairing(&DekuBabaNuts,   []{return DekuBabaNuts   || ((IsAdult && !ShuffleDungeonEntrances) || KokiriSword || Slingshot || Sticks || HasExplosives || CanUse(CanUseItem::Dins_Fire));}),
                }, {
                  //Locations
                  // ItemLocationPairing(&KF_DekuTreeGossipStoneLeft,  []{return true;}),
                  // ItemLocationPairing(&KF_DekuTreeGossipStoneRight, []{return true;})
                }, {
                  //Exits
                  ExitPairing::Both(&DekuTree_Lobby,    []{return Dungeon::DekuTree.IsVanilla() && (IsChild || (ShuffleDungeonEntrances && ShowedMidoSwordAndShield));}),
                  ExitPairing::Both(&DekuTree_MQ_Lobby, []{return Dungeon::DekuTree.IsMQ()      && (IsChild || (ShuffleDungeonEntrances && ShowedMidoSwordAndShield));}),
                  ExitPairing::Both(&KF_Main,           []{return true;}),
  });

  Exit KF_LinksHouse = Exit("KF Link's House", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&KF_LinksHouseCow, []{return IsAdult && CanPlay(EponasSong) && LinksCow;}),
                }, {
                  //Exits
                  ExitPairing::Both(&KF_Main, []{return true;})
  });

  Exit KF_MidosHouse = Exit("KF Mido's House", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&KF_MidoTopLeftChest,     []{return true;}),
                  ItemLocationPairing(&KF_MidoTopRightChest,    []{return true;}),
                  ItemLocationPairing(&KF_MidoBottomLeftChest,  []{return true;}),
                  ItemLocationPairing(&KF_MidoBottomRightChest, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&KF_Main, []{return true;}),
  });

  Exit KF_SariasHouse = Exit("KF Saria's House", "", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&KF_Main, []{return true;}),
  });

  Exit KF_HouseOfTwins = Exit("KF House of Twins", "", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&KF_Main, []{return true;}),
  });

  Exit KF_KnowItAllHouse = Exit("KF Know It All House", "", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&KF_Main, []{return true;}),
  });

  Exit KF_KokiriShop = Exit("KF Kokiri Shop", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&KF_ShopItem1, []{return true;}),
                  ItemLocationPairing(&KF_ShopItem2, []{return true;}),
                  ItemLocationPairing(&KF_ShopItem3, []{return true;}),
                  ItemLocationPairing(&KF_ShopItem4, []{return true;}),
                  ItemLocationPairing(&KF_ShopItem5, []{return true;}),
                  ItemLocationPairing(&KF_ShopItem6, []{return true;}),
                  ItemLocationPairing(&KF_ShopItem7, []{return true;}),
                  ItemLocationPairing(&KF_ShopItem8, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&KF_Main, []{return true;}),
  });

  Exit KF_StormsGrotto = Exit("KF Storms Grotto", "", "", NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  ItemLocationPairing(&KF_StormsGrottoChest,       []{return true;})
                  // ItemLocationPairing(&KF_StormsGrottoGossipStone, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&KF_Main, []{return true;})
  });

  Exit LW_ForestExit = Exit("LW Forest Exit", "Lost Woods", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&KF_Main, []{return true;})
  });

  Exit LW_Main = Exit("Lost Woods", "Lost Woods", "the Lost Woods", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&OddMushroomAccess, []{return OddMushroomAccess || (IsAdult && (CojiroAccess || Cojiro));}),
                  EventPairing(&PoachersSawAccess, []{return PoachersSawAccess || (IsAdult && OddPoulticeAccess);}),
                  EventPairing(&GossipStoneFairy,  []{return GossipStoneFairy  || CanSummonGossipFairyWithoutSuns;}),
                  EventPairing(&BeanPlantFairy,    []{return BeanPlantFairy    || CanPlay(SongOfStorms);}),
                  EventPairing(&BugShrub,          []{return IsChild && CanCutShrubs;}),
                }, {
                  //Locations
                  ItemLocationPairing(&LW_SkullKid,               []{return IsChild && CanPlay(SariasSong);}),
                  ItemLocationPairing(&LW_OcarinaMemoryGame,      []{return IsChild && Ocarina;}),
                  ItemLocationPairing(&LW_TargetInWoods,          []{return CanUse(CanUseItem::Slingshot);}),
                  ItemLocationPairing(&LW_DekuScrubNearBridge,    []{return IsChild && CanStunDeku;}),
                  ItemLocationPairing(&LW_GS_BeanPatchNearBridge, []{return CanPlantBugs && CanChildAttack;}),
                  //LW Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&LW_ForestExit,          []{return true;}),
                  ExitPairing::Both(&GC_WoodsWarp,           []{return true;}),
                  ExitPairing::Both(&LW_Bridge,              []{return IsAdult && (CanUse(CanUseItem::Hover_Boots) || CanUse(CanUseItem::Longshot) || LW_Main.CanPlantBean());}),
                  ExitPairing::Both(&ZR_Main,                []{return CanLeaveForest && (CanDive || CanUse(CanUseItem::Iron_Boots));}),
                  ExitPairing::Both(&LW_BeyondMido,          []{return IsChild || CanPlay(SariasSong);}),
                  ExitPairing::Both(&LW_NearShortcutsGrotto, []{return CanBlastOrSmash;})
  });

  Exit LW_BeyondMido = Exit("LW Beyond Mido", "Lost Woods", "Lost Woods", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&ButterflyFairy, []{return ButterflyFairy || CanUse(CanUseItem::Sticks);}),
                }, {
                  //Locations
                  ItemLocationPairing(&LW_DekuScrubNearDekuTheaterRight, []{return IsChild && CanStunDeku;}),
                  ItemLocationPairing(&LW_DekuScrubNearDekuTheaterLeft,  []{return IsChild && CanStunDeku;}),
                  ItemLocationPairing(&LW_GS_AboveTheater,               []{return IsAdult && AtNight && (LW_BeyondMido.CanPlantBean() || (LogicLostWoodsGSBean && CanUse(CanUseItem::Hookshot) && (CanUse(CanUseItem::Longshot) || CanUse(CanUseItem::Bow) || HasBombchus || CanUse(CanUseItem::Dins_Fire)))) && CanGetNightTimeGS;}),
                  ItemLocationPairing(&LW_GS_BeanPatchNearTheater,       []{return CanPlantBugs && (CanChildAttack || (Scrubsanity.Is(SCRUBSANITY_OFF) && DekuShield));}),
                }, {
                  //Exits
                  ExitPairing::Both(&LW_ForestExit,   []{return true;}),
                  ExitPairing::Both(&LW_Main,         []{return IsChild || CanPlay(SariasSong);}),
                  ExitPairing::Both(&SFM_Entryway,    []{return true;}),
                  ExitPairing::Both(&LW_DekuTheater,  []{return true;}),
                  ExitPairing::Both(&LW_ScrubsGrotto, []{return CanBlastOrSmash;})
  });

  Exit LW_NearShortcutsGrotto = Exit("LW Near Shortcuts Grotto", "", "", NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  ItemLocationPairing(&LW_NearShortcutsGrottoChest, []{return true;})
                  //LW Near Shortcuts Grotto Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&LW_Main, []{return true;})
  });

  Exit LW_DekuTheater = Exit("Deku Theater", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&DekuTheater_SkullMask,   []{return IsChild && SkullMask;}),
                  ItemLocationPairing(&DekuTheater_MaskOfTruth, []{return IsChild && MaskOfTruth;}),
                }, {
                  //Exits
                  ExitPairing::Both(&LW_BeyondMido, []{return true;}),
  });

  Exit LW_ScrubsGrotto = Exit("LW Scrubs Grotto", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&LW_DekuScrubGrottoRear,  []{return CanStunDeku;}),
                  ItemLocationPairing(&LW_DekuScrubGrottoFront, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing::Both(&LW_BeyondMido, []{return true;}),
  });

  Exit SFM_Entryway = Exit("SFM Entryway", "Sacred Forest Meadow", "Sacred Forest Meadow", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&LW_BeyondMido,    []{return true;}),
                  ExitPairing::Both(&SFM_Main,         []{return IsAdult || Slingshot || Sticks || KokiriSword || CanUse(CanUseItem::Dins_Fire);}),
                  ExitPairing::Both(&SFM_WolfosGrotto, []{return CanOpenBombGrotto;}),
  });

  Exit SFM_Main = Exit("Sacred Forest Meadow", "Sacred Forest Meadow", "Sacred Forest Meadow", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GossipStoneFairy, []{return GossipStoneFairy || CanSummonGossipFairyWithoutSuns;})
                }, {
                  //Locations
                  ItemLocationPairing(&SongFromSaria, []{return IsChild && ZeldasLetter;}),
                  ItemLocationPairing(&SheikInForest, []{return IsAdult;}),
                  ItemLocationPairing(&SFM_GS,        []{return CanUse(CanUseItem::Hookshot) && AtNight && CanGetNightTimeGS;}),
                  //SFM Maze Gossip Stone (Lower)
                  //SFM Maze Gossip Stone (Upper)
                  //SFM Saria Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&SFM_Entryway,          []{return true;}),
                  ExitPairing::Both(&ForestTemple_Lobby,    []{return Dungeon::ForestTemple.IsVanilla() && CanUse(CanUseItem::Hookshot);}),
                  ExitPairing::Both(&ForestTemple_MQ_Lobby, []{return Dungeon::ForestTemple.IsMQ()      && CanUse(CanUseItem::Hookshot);}),
                  ExitPairing::Both(&SFM_FairyGrotto,       []{return true;}),
                  ExitPairing::Both(&SFM_StormsGrotto,      []{return CanOpenStormGrotto;}),
  });

  Exit SFM_FairyGrotto = Exit("SFM Fairy Grotto", "", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FreeFairies, []{return true;})
                }, {}, {
                  //Exits
                  ExitPairing::Both(&SFM_Main, []{return true;}),
  });

  Exit SFM_WolfosGrotto = Exit("SFM Wolfos Grotto", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&SFM_WolfosGrottoChest, []{return IsAdult || Slingshot || Sticks || KokiriSword || CanUse(CanUseItem::Dins_Fire);})
                }, {
                  //Exits
                  ExitPairing::Both(&SFM_Main, []{return true;}),
  });

  Exit SFM_StormsGrotto = Exit("SFM Storms Grotto", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&SFM_DekuScrubGrottoRear,  []{return CanStunDeku;}),
                  ItemLocationPairing(&SFM_DekuScrubGrottoFront, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing::Both(&SFM_Main, []{return true;})
  });

  Exit LW_BridgeFromForest = Exit("LW Bridge From Forest", "Lost Woods", "the Lost Woods", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&LW_GiftFromSaria, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&LW_Bridge, []{return true;})
  });

  Exit LW_Bridge = Exit("LW Bridge", "Lost Woods", "the Lost Woods", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&KF_Main, []{return true;}),
                  ExitPairing::Both(&HF_Main, []{return true;}),
                  ExitPairing::Both(&LW_Main, []{return CanUse(CanUseItem::Longshot);})
  });

  Exit HF_Main = Exit("Hyrule Field", "Hyrule Field", "Hyrule Field", DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&BigPoeKill, []{return CanUse(CanUseItem::Bow) && CanRideEpona && HasBottle;}),
                }, {
                  //Locations
                  ItemLocationPairing(&HF_OcarinaOfTimeItem,  []{return IsChild && HasAllStones;}),
                  ItemLocationPairing(&SongFromOcarinaOfTime, []{return IsChild && HasAllStones;}),
                }, {
                  //Exits
                  ExitPairing::Both(&LW_Bridge,            []{return true;}),
                  ExitPairing::Both(&LH_Main,              []{return true;}),
                  ExitPairing::Both(&GV_Main,              []{return true;}),
                  ExitPairing::Both(&MK_Entrance,          []{return true;}),
                  ExitPairing::Both(&Kak_Main,             []{return true;}),
                  ExitPairing::Both(&ZR_Front,             []{return true;}),
                  ExitPairing::Both(&LLR_Main,             []{return true;}),
                  ExitPairing::Both(&HF_SoutheastGrotto,   []{return CanBlastOrSmash;}),
                  ExitPairing::Both(&HF_OpenGrotto,        []{return true;}),
                  ExitPairing::Both(&HF_InsideFenceGrotto, []{return CanOpenBombGrotto;}),
                  ExitPairing::Both(&HF_CowGrotto,         []{return (CanUse(CanUseItem::Hammer) || IsChild) && CanOpenBombGrotto;}),
                  ExitPairing::Both(&HF_NearMarketGrotto,  []{return CanBlastOrSmash;}),
                  ExitPairing::Both(&HF_FairyGrotto,       []{return CanBlastOrSmash;}),
                  ExitPairing::Both(&HF_NearKakGrotto,     []{return CanOpenBombGrotto;}),
                  ExitPairing::Both(&HF_TektiteGrotto,     []{return CanOpenBombGrotto;})
  });

  Exit HF_SoutheastGrotto = Exit("HF Southeast Grotto", "", "", NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  ItemLocationPairing(&HF_SoutheastGrottoChest, []{return true;})
                  //HF Open Grotto Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&HF_Main, []{return true;})
  });

  Exit HF_OpenGrotto = Exit("HF Open Grotto", "", "", NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  ItemLocationPairing(&HF_OpenGrottoChest, []{return true;})
                  //HF Open Grotto Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&HF_Main, []{return true;})
  });

  Exit HF_InsideFenceGrotto = Exit("HF Inside Fence Grotto", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&HF_DekuScrubGrotto, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing::Both(&HF_Main, []{return true;})
  });

  Exit HF_CowGrotto = Exit("HF Cow Grotto", "", "", NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  ItemLocationPairing(&HF_GS_CowGrotto, []{return HasFireSource && HookshotOrBoomerang;}),
                  ItemLocationPairing(&HF_CowGrottoCow, []{return HasFireSource && CanPlay(EponasSong);}),
                  //HF Open Grotto Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&HF_Main, []{return true;})
  });

  Exit HF_NearMarketGrotto = Exit("HF Near Market Grotto", "", "", NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  ItemLocationPairing(&HF_NearMarketGrottoChest, []{return true;})
                  //HF Open Grotto Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&HF_Main, []{return true;})
  });

  Exit HF_FairyGrotto = Exit("HF Fairy Grotto", "", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FreeFairies, []{return true;})
                }, {}, {
                  //Exits
                  ExitPairing::Both(&HF_Main, []{return true;})
  });

  Exit HF_NearKakGrotto = Exit("HF Near Kak Grotto", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&HF_GS_NearKakGrotto, []{return HookshotOrBoomerang;}),
                }, {
                  //Exits
                  ExitPairing::Both(&HF_Main, []{return true;})
  });

  Exit HF_TektiteGrotto = Exit("HF Tektite Grotto", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&HF_TektiteGrottoFreestandingPoH, []{return ProgressiveScale >= 2 || CanUse(CanUseItem::Iron_Boots);}),
                }, {
                  //Exits
                  ExitPairing::Both(&HF_Main, []{return true;}),
  });

  Exit LH_Main = Exit("Lake Hylia", "Lake Hylia", "Lake Hylia", DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GossipStoneFairy, []{return GossipStoneFairy || CanSummonGossipFairy;}),
                  EventPairing(&BeanPlantFairy,   []{return BeanPlantFairy   || (LH_Main.CanPlantBean() && CanPlay(SongOfStorms));}),
                  EventPairing(&ButterflyFairy,   []{return ButterflyFairy   || CanUse(CanUseItem::Sticks);}),
                  EventPairing(&BugShrub,         []{return BugShrub         || (IsChild && CanCutShrubs);}),
                  EventPairing(&ScarecrowSong,    []{return ScarecrowSong    || (Ocarina && LH_Main.BothAges());}),
                }, {
                  //Locations
                  ItemLocationPairing(&LH_UnderwaterItem,  []{return IsChild && CanDive;}),
                  ItemLocationPairing(&LH_Sun,             []{return IsAdult && WaterTempleClear && CanUse(CanUseItem::Bow);}),
                  ItemLocationPairing(&LH_FreestandingPoH, []{return IsAdult && (CanUse(CanUseItem::Scarecrow) || LH_Main.CanPlantBean());}),
                  ItemLocationPairing(&LH_GS_BeanPatch,    []{return CanPlantBugs && CanChildAttack;}),
                  ItemLocationPairing(&LH_GS_LabWall,      []{return IsChild && (Boomerang || (LogicLabWallGS && (Sticks || KokiriSword))) && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(&LH_GS_SmallIsland,  []{return IsChild && CanChildAttack && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(&LH_GS_Tree,         []{return CanUse(CanUseItem::Longshot) && AtNight && CanGetNightTimeGS;}),
                  //LH Gossip Stone (Southeast)
                  //LH Gossip Stone (Southwest)
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

  Exit LH_OwlFlight = Exit("LH Owl Flight", "Lake Hylia", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&HF_Main, []{return true;})
  });

  Exit LH_Lab = Exit("LH Lab", "", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&EyedropsAccess, []{return EyedropsAccess || (IsAdult && (EyeballFrogAccess || (EyeballFrog && DisableTradeRevert)));}),
                }, {
                  //Locations
                  ItemLocationPairing(&LH_LabDive,     []{return ProgressiveScale >= 2 || (LogicLabDiving && IronBoots && CanUse(CanUseItem::Hookshot));}),
                  ItemLocationPairing(&LH_GS_LabCrate, []{return IronBoots && CanUse(CanUseItem::Hookshot);}),
                }, {
                  //Exits
                  ExitPairing::Both(&LH_Main, []{return true;})
  });

  Exit LH_FishingHole = Exit("LH Fishing Hole", "", "", DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&LH_ChildFishing, []{return IsChild;}),
                  ItemLocationPairing(&LH_AdultFishing, []{return IsAdult;})
                }, {
                  //Exits
                  ExitPairing::Both(&LH_Main, []{return true;})
  });

  Exit LH_Grotto = Exit("LH Grotto", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&LH_DekuScrubGrottoLeft,   []{return CanStunDeku;}),
                  ItemLocationPairing(&LH_DekuScrubGrottoRight,  []{return CanStunDeku;}),
                  ItemLocationPairing(&LH_DekuScrubGrottoCenter, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing::Both(&LH_Main, []{return true;})
  });

  Exit GV_Main = Exit("Gerudo Valley", "Gerudo Valley", "Gerudo Valley", DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&BugRock, []{return IsChild && HasBottle;}),
                }, {
                  //Locations
                  ItemLocationPairing(&GV_GS_SmallBridge, []{return CanUse(CanUseItem::Boomerang) && AtNight && CanGetNightTimeGS;}),
                }, {
                  //Exits
                  ExitPairing::Both(&HF_Main,          []{return true;}),
                  ExitPairing::Both(&GV_Stream,        []{return true;}),
                  ExitPairing::Both(&GV_CrateLedge,    []{return IsChild || CanUse(CanUseItem::Longshot);}),
                  ExitPairing::Both(&GV_OctorokGrotto, []{return CanUse(CanUseItem::Silver_Gauntlets);}),
                  ExitPairing::Both(&GV_FortressSide,  []{return IsAdult && (CanRideEpona || CanUse(CanUseItem::Longshot) || GerudoFortress.Is(GERUDOFORTRESS_OPEN) || CarpenterRescue);})
  });

  Exit GV_Stream = Exit("GV Stream", "Gerudo Valley", "Gerudo Valley", DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GossipStoneFairy, []{return GossipStoneFairy || CanSummonGossipFairy;}),
                  EventPairing(&BeanPlantFairy,   []{return BeanPlantFairy   || (GV_Stream.CanPlantBean() && CanPlay(SongOfStorms));}),
                }, {
                  //Locations
                  ItemLocationPairing(&GV_WaterfallFreestandingPoH, []{return true;}),
                  ItemLocationPairing(&GV_GS_BeanPatch,             []{return CanPlantBugs && CanChildAttack;}),
                  ItemLocationPairing(&GV_Cow,                      []{return IsChild && CanPlay(EponasSong);}),
                  //GV Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&LH_Main, []{return true;})
  });

  Exit GV_CrateLedge = Exit("GV Crate Ledge", "Gerudo Valley", "Gerudo Valley", DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&GV_CrateFreestandingPoH, []{return true;}),
                }, {
                  //Exits
  });

  Exit GV_FortressSide = Exit("GV Fortress Side", "Gerudo Valley", "Gerudo Valley", DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&BrokenSwordAccess, []{return IsAdult && (PoachersSawAccess || PoachersSaw);}),
                }, {
                  //Locations
                  ItemLocationPairing(&GV_Chest,         []{return CanUse(CanUseItem::Hammer);}),
                  ItemLocationPairing(&GV_GS_BehindTent, []{return CanUse(CanUseItem::Hookshot) && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(&GV_GS_Pillar,     []{return CanUse(CanUseItem::Hookshot) && AtNight && CanGetNightTimeGS;}),
                }, {
                  //Exits
                  ExitPairing::Both(&GF_Main,          []{return true;}),
                  ExitPairing::Both(&GV_Stream,        []{return true;}),
                  ExitPairing::Both(&GV_Main,          []{return IsChild || CanRideEpona || CanUse(CanUseItem::Longshot) || GerudoFortress.Is(GERUDOFORTRESS_OPEN) || CarpenterRescue;}),
                  ExitPairing::Both(&GV_CarpenterTent, []{return IsAdult;}),
                  ExitPairing::Both(&GV_StormsGrotto,  []{return IsAdult && CanOpenStormGrotto;})
  });

  Exit GV_CarpenterTent = Exit("GV Carpenter Tent", "", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&GV_Main, []{return true;})
  });

  Exit GV_OctorokGrotto = Exit("GV Octorok Grotto", "", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&GV_Main, []{return true;})
  });

  Exit GV_StormsGrotto = Exit("GV Storms Grotto", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&GV_DekuScrubGrottoRear,  []{return CanStunDeku;}),
                  ItemLocationPairing(&GV_DekuScrubGrottoFront, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing::Both(&GV_FortressSide, []{return true;})
  });

  Exit GF_Main = Exit("Gerudo Fortress", "Gerudo Fortress", "Gerudo's Fortress", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&CarpenterRescue, []{return CanFinishGerudoFortress;}),
                  EventPairing(&GF_GateOpen,     []{return IsAdult && GerudoToken;}),
                }, {
                  //Locations
                  ItemLocationPairing(&GF_Chest,            []{return CanUse(CanUseItem::Hover_Boots) || CanUse(CanUseItem::Scarecrow) || CanUse(CanUseItem::Longshot);}),
                  ItemLocationPairing(&GF_HBA1000Points,    []{return GerudoToken && CanRideEpona && Bow && AtDay;}),
                  ItemLocationPairing(&GF_HBA1500Points,    []{return GerudoToken && CanRideEpona && Bow && AtDay;}),
                  ItemLocationPairing(&GF_NorthF1Carpenter, []{return  IsAdult || KokiriSword;}),
                  ItemLocationPairing(&GF_NorthF2Carpenter, []{return (IsAdult || KokiriSword) && (GerudoToken || CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Hookshot) || CanUse(CanUseItem::Hover_Boots) || LogicGerudoKitchen);}),
                  ItemLocationPairing(&GF_SouthF1Carpenter, []{return  IsAdult || KokiriSword;}),
                  ItemLocationPairing(&GF_SouthF2Carpenter, []{return  IsAdult || KokiriSword;}),
                  ItemLocationPairing(&GF_GerudoToken,      []{return CanFinishGerudoFortress;}),
                  ItemLocationPairing(&GF_GS_ArcheryRange,  []{return CanUse(CanUseItem::Hookshot) && GerudoToken && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(&GF_GS_TopFloor,      []{return IsAdult && AtNight && (GerudoToken || CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Hookshot) || CanUse(CanUseItem::Hover_Boots) || LogicGerudoKitchen) && CanGetNightTimeGS;})
                }, {
                  //Exits
                  ExitPairing::Both(&GV_FortressSide,                []{return true;}),
                  ExitPairing::Both(&GF_OutsideGate,                 []{return GF_GateOpen;}),
                  ExitPairing::Both(&GerudoTrainingGrounds_Lobby,    []{return Dungeon::GerudoTrainingGrounds.IsVanilla() && IsAdult && GerudoToken;}),
                  ExitPairing::Both(&GerudoTrainingGrounds_MQ_Lobby, []{return Dungeon::GerudoTrainingGrounds.IsMQ()      && IsAdult && GerudoToken;}),
                  ExitPairing::Both(&GF_StormsGrotto,                []{return IsAdult && CanOpenStormGrotto;})
  });

  Exit GF_OutsideGate = Exit("GF Outside Gate", "Gerudo Fortress", "", NO_DAY_NIGHT_CYCLE, {
                  //Events                                                      //no guard on the other side of the gate yet
                  //EventPairing(&GF_GateOpen, []{return IsAdult && GerudoToken && (ShuffleGerudoToken || ShuffleOverworldEntrances || ShuffleSpecialIndoorEntrances);}),
                }, {}, {
                  //Exits
                  ExitPairing::Both(&GF_Main,         []{return IsAdult || (ShuffleOverworldEntrances && GF_GateOpen);}),
                  ExitPairing::Both(&HW_NearFortress, []{return true;})
  });

  Exit GF_StormsGrotto = Exit("GF Storms Grotto", "", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FreeFairies, []{return true;}),
                }, {}, {
                  //Exits
                  ExitPairing::Both(&GF_Main, []{return true;})
  });

  Exit HW_NearFortress = Exit("Wasteland Near Fortress", "Haunted Wasteland", "Haunted Wasteland", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&GF_OutsideGate, []{return true;}),
                  ExitPairing::Both(&HW_Main,        []{return CanUse(CanUseItem::Hover_Boots) || CanUse(CanUseItem::Longshot);}),
  });

  Exit HW_Main = Exit("Haunted Wasteland", "Haunted Wasteland", "Haunted Wasteland", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPot, []{return true;}),
                  EventPairing(&NutPot,   []{return true;}),
                }, {
                  //Locations
                  ItemLocationPairing(&HW_Chest, []{return HasFireSource;}),
                  //Wasteland Bombchu Salesman
                  ItemLocationPairing(&HW_GS,    []{return HookshotOrBoomerang;}),
                }, {
                  //Exits
                  ExitPairing::Both(&HW_NearColossus, []{return LogicLensWasteland || CanUse(CanUseItem::Lens_of_Truth);}),
                  ExitPairing::Both(&HW_NearFortress, []{return CanUse(CanUseItem::Hover_Boots) || CanUse(CanUseItem::Longshot);}),
  });

  Exit HW_NearColossus = Exit("Wasteland Near Colossus", "Haunted Wasteland", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&Colossus_Main, []{return true;}),
                  ExitPairing::Both(&HW_Main,       []{return LogicReverseWasteland || false;})
  });

  Exit Colossus_Main = Exit("Desert Colossus", "Desert Colossus", "Desert Colossus", DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPond, []{return FairyPond || CanPlay(SongOfStorms);}),
                  EventPairing(&BugRock,   []{return true;}),
                }, {
                  //Locations
                  ItemLocationPairing(&Colossus_FreestandingPoH, []{return IsAdult && Colossus_Main.CanPlantBean();}),
                  ItemLocationPairing(&SheikAtColossus,          []{return true;}),
                  ItemLocationPairing(&Colossus_GS_BeanPatch,    []{return CanPlantBugs && CanChildAttack;}),
                  ItemLocationPairing(&Colossus_GS_Tree,         []{return CanUse(CanUseItem::Hookshot) && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(&Colossus_GS_Hill,         []{return IsAdult && AtNight && (Colossus_Main.CanPlantBean() || CanUse(CanUseItem::Longshot) || (LogicColossusGS && CanUse(CanUseItem::Hookshot))) && CanGetNightTimeGS;})
                  //Colossus Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&Colossus_GreatFairyFountain, []{return HasExplosives;}),
                  ExitPairing::Both(&SpiritTemple_Lobby,          []{return Dungeon::SpiritTemple.IsVanilla();}),
                  ExitPairing::Both(&SpiritTemple_MQ_Lobby,       []{return Dungeon::SpiritTemple.IsMQ();}),
                  ExitPairing::Both(&HW_NearColossus,             []{return true;}),
                  ExitPairing::Both(&Colossus_Grotto,             []{return CanUse(CanUseItem::Silver_Gauntlets);})
  });

  Exit Colossus_GreatFairyFountain = Exit("Colossus Great Fairy Fountain", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&Colossus_GreatFairyReward, []{return CanPlay(ZeldasLullaby);}),
                }, {
                  //Exits
                  ExitPairing::Both(&Colossus_Main, []{return true;})
  });

  Exit Colossus_Grotto = Exit("Colossus Grotto", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&Colossus_DekuScrubGrottoRear,  []{return CanStunDeku;}),
                  ItemLocationPairing(&Colossus_DekuScrubGrottoFront, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing::Both(&Colossus_Main, []{return true;})
  });

  Exit MK_Entrance = Exit("Market Entrance", "Market Entrance", "the Market", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Day(&HF_Main, []{return IsAdult || AtDay;}),
                  ExitPairing::Both(&MK_Main, []{return true;}),
                  ExitPairing::Both(&MK_GuardHouse, []{return true;})
  });

  Exit MK_Main = Exit("Market", "Market", "Market", NO_DAY_NIGHT_CYCLE, {}, {}, {
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

  Exit ToT_Entrance = Exit("ToT Entrance", "ToT Entrance", "the Market", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GossipStoneFairy, []{return GossipStoneFairy || CanSummonGossipFairyWithoutSuns;}),
                }, {
                  //Locations
                  //ToT Gossip Stone (Left)
                  //ToT Gossip Stone (Left-Center)
                  //ToT Gossip Stone (Right)
                  //ToT Gossip Stone (Right-Center)
                }, {
                  //Exits
                  ExitPairing::Both(&MK_Main,  []{return true;}),
                  ExitPairing::Both(&ToT_Main, []{return true;})
  });

  Exit ToT_Main = Exit("Temple of Time", "", "Temple of Time", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&ToT_LightArrowCutscene, []{return IsAdult && CanTriggerLACS;}),
                }, {
                  //Exits
                  ExitPairing::Both(&ToT_Entrance,         []{return true;}),
                  ExitPairing::Both(&ToT_BeyondDoorOfTime, []{return CanPlay(SongOfTime) || OpenDoorOfTime;}),
  });

  Exit ToT_BeyondDoorOfTime = Exit("Beyond Door of Time", "", "Temple of Time", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  //EventPairing(&TimeTravel, []{return true;}),
                }, {
                  //Locations
                  ItemLocationPairing(&SheikAtTemple, []{return ForestMedallion && IsAdult;}),
                }, {
                  //Exits
                  ExitPairing::Both(&ToT_Main, []{return true;})
  });

  Exit CastleGrounds = Exit("Castle Grounds", "Castle Grounds", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&MK_Main,     []{return true;}),
                  ExitPairing::Both(&HC_Grounds,  []{return IsChild;}),
                  ExitPairing::Both(&OGC_Grounds, []{return IsAdult;})
  });

  Exit HC_Grounds = Exit("Hyrule Castle Grounds", "Castle Grounds", "Hyrule Castle", DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GossipStoneFairy, []{return GossipStoneFairy || CanSummonGossipFairy;}),
                  EventPairing(&ButterflyFairy,   []{return ButterflyFairy   || CanUse(CanUseItem::Sticks);}),
                  EventPairing(&BugRock,          []{return true;}),
                }, {
                  //Locations
                  ItemLocationPairing(&HC_MalonEgg, []{return true;}),
                  ItemLocationPairing(&HC_GS_Tree,  []{return CanChildAttack;}),
                  //HC Malon Gossip Stone
                  //HC HC Rock Wall Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&CastleGrounds,         []{return true;}),
                  ExitPairing::Both(&HC_Garden,             []{return WeirdEgg || !ShuffleWeirdEgg;}),
                  ExitPairing::Both(&HC_GreatFairyFountain, []{return HasExplosives;}),
                  ExitPairing::Both(&HC_StormsGrotto,       []{return CanOpenStormGrotto;})
  });

  Exit HC_Garden = Exit("HC Garden", "Castle Grounds", "Hyrule Castle", NO_DAY_NIGHT_CYCLE, {
                  //Events
                }, {
                  //Locations
                  ItemLocationPairing(&HC_ZeldasLetter, []{return true;}),
                  ItemLocationPairing(&SongFromImpa,    []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&HC_Grounds, []{return true;})
  });

  Exit HC_GreatFairyFountain = Exit("HC Great Fairy Fountain", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&HC_GreatFairyReward, []{return CanPlay(ZeldasLullaby);}),
                }, {
                  //Exits
                  ExitPairing::Both(&HC_Grounds, []{return true;})
  });

  Exit HC_StormsGrotto = Exit("HC Storms Grotto", "", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&NutPot,           []{return NutPot           || CanBlastOrSmash;}),
                  EventPairing(&GossipStoneFairy, []{return GossipStoneFairy || (CanBlastOrSmash && CanSummonGossipFairy);}),
                  EventPairing(&WanderingBugs,    []{return WanderingBugs    || CanBlastOrSmash;}),
                }, {
                  //Locations
                  ItemLocationPairing(&HC_GS_StormsGrotto, []{return CanBlastOrSmash && HookshotOrBoomerang;}),
                  //HC Storms Grotto Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&HC_Grounds, []{return true;})
  });

  Exit OGC_Grounds = Exit("Ganon's Castle Grounds", "Castle Grounds", "outside Ganon's Castle", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations                     //the terrain was lowered such that you can't get this GS with a simple sword slash
                  ItemLocationPairing(&OGC_GS, []{return HasExplosives || (IsAdult && (LogicOutsideGanonsGS || Bow || Hookshot || CanUse(CanUseItem::Dins_Fire)));}),
                }, {
                  //Exits
                  ExitPairing::Night(&CastleGrounds,          []{return AtNight;}),
                  ExitPairing::Night(&OGC_GreatFairyFountain, []{return CanUse(CanUseItem::Golden_Gauntlets) && AtNight;}),
                  ExitPairing::Both(&GanonsCastle_Lobby,      []{return Dungeon::GanonsCastle.IsVanilla() && CanBuildRainbowBridge;}),
                  ExitPairing::Both(&GanonsCastle_MQ_Lobby,   []{return Dungeon::GanonsCastle.IsMQ()      && CanBuildRainbowBridge;}),
  });

  Exit OGC_GreatFairyFountain = Exit("OGC Great Fairy Fountain", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&OGC_GreatFairyReward, []{return CanPlay(ZeldasLullaby);}),
                }, {
                  //Exits
                  ExitPairing::Both(&CastleGrounds, []{return true;}),
  });

  Exit MK_GuardHouse = Exit("Market Guard House", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&MK_10BigPoes,     []{return IsAdult && BigPoeKill;}),
                  ItemLocationPairing(&MK_GS_GuardHouse, []{return IsChild;}),
                }, {
                  //Exits
                  ExitPairing::Both(&MK_Entrance, []{return true;})
  });

  Exit MK_Bazaar = Exit("Market Bazaar", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&MK_BazaarItem1, []{return true;}),
                  ItemLocationPairing(&MK_BazaarItem2, []{return true;}),
                  ItemLocationPairing(&MK_BazaarItem3, []{return true;}),
                  ItemLocationPairing(&MK_BazaarItem4, []{return true;}),
                  ItemLocationPairing(&MK_BazaarItem5, []{return true;}),
                  ItemLocationPairing(&MK_BazaarItem6, []{return true;}),
                  ItemLocationPairing(&MK_BazaarItem7, []{return true;}),
                  ItemLocationPairing(&MK_BazaarItem8, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&MK_Main, []{return true;})
  });

  Exit MK_MaskShop = Exit("Market Mask Shop", "", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&SkullMask,   []{return SkullMask   || (ZeldasLetter && Kak_Main.Child());}),
                  EventPairing(&MaskOfTruth, []{return MaskOfTruth || (SkullMask && (LW_Main.Child() && CanPlay(SariasSong) && GY_Main.dayChild && HF_Main.Child() && HasAllStones));}),
                }, {}, {
                  //Exits
                  ExitPairing::Both(&MK_Main, []{return true;})
  });

  Exit MK_ShootingGallery = Exit("Market Shooting Gallery", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&MK_ShootingGalleryReward, []{return IsChild;})
                }, {
                  //Exits
                  ExitPairing::Both(&MK_Main, []{return true;})
  });

  Exit MK_BombchuBowling = Exit("Market Bombchu Bowling", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&MK_BombchuBowlingFirstPrize,  []{return FoundBombchus;}),
                  ItemLocationPairing(&MK_BombchuBowlingSecondPrize, []{return FoundBombchus;}),
                  ItemLocationPairing(&MK_BombchuBowlingBombchus,    []{return FoundBombchus;}),
                }, {
                  //Exits
                  ExitPairing::Both(&MK_Main, []{return true;})
  });

  Exit MK_PotionShop = Exit("Market Potion Shop", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&MK_PotionShopItem1, []{return true;}),
                  ItemLocationPairing(&MK_PotionShopItem2, []{return true;}),
                  ItemLocationPairing(&MK_PotionShopItem3, []{return true;}),
                  ItemLocationPairing(&MK_PotionShopItem4, []{return true;}),
                  ItemLocationPairing(&MK_PotionShopItem5, []{return true;}),
                  ItemLocationPairing(&MK_PotionShopItem6, []{return true;}),
                  ItemLocationPairing(&MK_PotionShopItem7, []{return true;}),
                  ItemLocationPairing(&MK_PotionShopItem8, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&MK_Main, []{return true;})
  });

  Exit MK_TreasureChestGame = Exit("Market Treasure Chest Game", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&MK_TreasureChestGameReward, []{return CanUse(CanUseItem::Lens_of_Truth);})
                }, {
                  //Exits
                  ExitPairing::Both(&MK_Main, []{return true;})
  });

  Exit MK_BombchuShop = Exit("Market Bombchu Shop", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&MK_BombchuShopItem1, []{return HasExplosives;}),
                  ItemLocationPairing(&MK_BombchuShopItem2, []{return HasExplosives;}),
                  ItemLocationPairing(&MK_BombchuShopItem3, []{return HasExplosives;}),
                  ItemLocationPairing(&MK_BombchuShopItem4, []{return HasExplosives;}),
                  ItemLocationPairing(&MK_BombchuShopItem5, []{return HasExplosives;}),
                  ItemLocationPairing(&MK_BombchuShopItem6, []{return HasExplosives;}),
                  ItemLocationPairing(&MK_BombchuShopItem7, []{return HasExplosives;}),
                  ItemLocationPairing(&MK_BombchuShopItem8, []{return HasExplosives;}),
                }, {
                  //Exits
                  ExitPairing::Both(&MK_Main, []{return true;})
  });

  Exit MK_DogLadyHouse = Exit("Market Dog Lady House", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&MK_LostDog, []{return AtNight;})
                }, {
                  //Exits
                  ExitPairing::Both(&MK_Main, []{return true;})
  });

  Exit MK_ManInGreenHouse = Exit("Market Man in Green House", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                }, {
                  //Exits
                  ExitPairing::Both(&MK_Main, []{return true;})
  });

  Exit Kak_Main = Exit("Kakariko Village", "Kakariko Village", "Kakariko Village", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&CojiroAccess,            []{return CojiroAccess || (IsAdult && WakeUpAdultTalon);}),
                  EventPairing(&BugRock,                 []{return true;}),
                  EventPairing(&KakarikoVillageGateOpen, []{return KakarikoVillageGateOpen || (IsChild && (ZeldasLetter || OpenKakariko.Is(OPENKAKARIKO_OPEN)));}),
                }, {
                  //Locations
                  ItemLocationPairing(&SheikInKakariko,               []{return IsAdult && ForestMedallion && FireMedallion && WaterMedallion;}),
                  ItemLocationPairing(&Kak_AnjuAsChild,               []{return IsChild && AtDay;}),
                  ItemLocationPairing(&Kak_AnjuAsAdult,               []{return IsAdult && AtDay;}),
                  ItemLocationPairing(&Kak_GS_HouseUnderConstruction, []{return IsChild && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(&Kak_GS_SkulltulaHouse,         []{return IsChild && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(&Kak_GS_GuardsHouse,            []{return IsChild && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(&Kak_GS_Tree,                   []{return IsChild && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(&Kak_GS_Watchtower,             []{return IsChild && (Slingshot || HasBombchus) && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(&Kak_GS_AboveImpasHouse,        []{return CanUse(CanUseItem::Hookshot) && AtNight && CanGetNightTimeGS;}),
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

  Exit Kak_ImpasLedge = Exit("Kak Impas Ledge", "Kakariko Village", "Kakariko Village", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&Kak_ImpasHouseBack, []{return true;}),
                  ExitPairing::Both(&Kak_Main,           []{return true;})
  });

  Exit Kak_Rooftop = Exit("Kak Rooftop", "Kakariko VIllage", "Kakariko Village", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&Kak_ManOnRoof, []{return true;})
                }, {
                  //Exits
                  ExitPairing::Both(&Kak_Backyard, []{return true;})
  });

  Exit Kak_Backyard = Exit("Kak Backyard", "Kakariko Village", "Kakariko Village", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&Kak_Main,                []{return true;}),
                  ExitPairing::Both(&Kak_OpenGrotto,          []{return true;}),
                  ExitPairing::Both(&Kak_OddMedicineBuilding, []{return IsAdult;}),
                  ExitPairing::Day(&Kak_PotionShopBack,       []{return IsAdult && AtDay;})
  });

  Exit Kak_CarpenterBossHouse = Exit("Kak Carpenter Boss House", "", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&WakeUpAdultTalon, []{return WakeUpAdultTalon || (IsAdult && (PocketEgg || PocketCucco));}),
                }, {}, {
                  //Exits
                  ExitPairing::Both(&Kak_Main, []{return true;})
  });

  Exit Kak_HouseOfSkulltula = Exit("Kak House of Skulltula", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&Kak_10GoldSkulltulaReward, []{return GoldSkulltulaTokens >= 10;}),
                  ItemLocationPairing(&Kak_20GoldSkulltulaReward, []{return GoldSkulltulaTokens >= 20;}),
                  ItemLocationPairing(&Kak_30GoldSkulltulaReward, []{return GoldSkulltulaTokens >= 30;}),
                  ItemLocationPairing(&Kak_40GoldSkulltulaReward, []{return GoldSkulltulaTokens >= 40;}),
                  ItemLocationPairing(&Kak_50GoldSkulltulaReward, []{return GoldSkulltulaTokens >= 50;}),
                }, {
                  //Exits
                  ExitPairing::Both(&Kak_Main, []{return true;})
  });

  Exit Kak_ImpasHouse = Exit("Kak Impas House", "", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&Kak_ImpasHouseNearCow, []{return true;}),
                  ExitPairing::Both(&Kak_Main,              []{return true;})
  });

  Exit Kak_ImpasHouseBack = Exit("Kak Impas House Back", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&Kak_ImpasHouseFreestandingPoH, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&Kak_ImpasLedge,        []{return true;}),
                  ExitPairing::Both(&Kak_ImpasHouseNearCow, []{return true;})
  });

  Exit Kak_ImpasHouseNearCow = Exit("Kak Impas House Near Cow", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&Kak_ImpasHouseCow, []{return CanPlay(EponasSong);}),
                }, {
                  //Exits
                  ExitPairing::Both(&Kak_ImpasHouseBack, []{return false;})
  });

  Exit Kak_Windmill = Exit("Kak Windmill", "", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&DrainWell, []{return DrainWell || (IsChild && CanPlay(SongOfStorms));}),
                }, {
                  //Locations
                  ItemLocationPairing(&Kak_WindmillFreestandingPoH, []{return CanUse(CanUseItem::Boomerang) || DampesWindmillAccess;}),
                  ItemLocationPairing(&SongFromWindmill,            []{return IsAdult && Ocarina;}),
                }, {
                  //Exits
                  ExitPairing::Both(&Kak_Main, []{return true;})
  });

  Exit Kak_Bazaar = Exit("Kak Bazaar", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&Kak_BazaarItem1, []{return true;}),
                  ItemLocationPairing(&Kak_BazaarItem2, []{return true;}),
                  ItemLocationPairing(&Kak_BazaarItem3, []{return true;}),
                  ItemLocationPairing(&Kak_BazaarItem4, []{return true;}),
                  ItemLocationPairing(&Kak_BazaarItem5, []{return true;}),
                  ItemLocationPairing(&Kak_BazaarItem6, []{return true;}),
                  ItemLocationPairing(&Kak_BazaarItem7, []{return true;}),
                  ItemLocationPairing(&Kak_BazaarItem8, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&Kak_Main, []{return true;})
  });

  Exit Kak_ShootingGallery = Exit("Kak Shooting Gallery", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&Kak_ShootingGalleryReward, []{return IsAdult && Bow;}),
                }, {
                  //Exits
                  ExitPairing::Both(&Kak_Main, []{return true;})
  });

  Exit Kak_PotionShopFront = Exit("Kak Potion Shop Front", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&Kak_PotionShopItem1, []{return true;}),
                  ItemLocationPairing(&Kak_PotionShopItem2, []{return true;}),
                  ItemLocationPairing(&Kak_PotionShopItem3, []{return true;}),
                  ItemLocationPairing(&Kak_PotionShopItem4, []{return true;}),
                  ItemLocationPairing(&Kak_PotionShopItem5, []{return true;}),
                  ItemLocationPairing(&Kak_PotionShopItem6, []{return true;}),
                  ItemLocationPairing(&Kak_PotionShopItem7, []{return true;}),
                  ItemLocationPairing(&Kak_PotionShopItem8, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&Kak_Main,           []{return true;}),
                  ExitPairing::Both(&Kak_PotionShopBack, []{return IsAdult;})
  });

  Exit Kak_PotionShopBack = Exit("Kak Potion Shop Back", "", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&Kak_Backyard,        []{return IsAdult;}),
                  ExitPairing::Both(&Kak_PotionShopFront, []{return true;})
  });

  Exit Kak_OddMedicineBuilding = Exit("Kak Odd Medicine Building", "", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&OddPoulticeAccess, []{return OddPoulticeAccess || (IsAdult && (OddMushroomAccess || (OddMushroom && DisableTradeRevert)));}),
                }, {}, {
                  //Exits
                  ExitPairing::Both(&Kak_Backyard, []{return true;})
  });

  Exit Kak_RedeadGrotto = Exit("Kak Redead Grotto", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&Kak_RedeadGrottoChest, []{return IsAdult || (Sticks || KokiriSword || CanUse(CanUseItem::Dins_Fire));})
                }, {
                  //Exits
                  ExitPairing::Both(&Kak_Main, []{return true;})
  });

  Exit Kak_OpenGrotto = Exit("Kak Open Grotto", "", "", NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  ItemLocationPairing(&Kak_OpenGrottoChest, []{return true;})
                  //Kak Open Grotto Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&Kak_Backyard, []{return true;})
  });

  Exit GY_Main = Exit("Graveyard", "Graveyard", "the Graveyard", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&ButterflyFairy, []{return ButterflyFairy || (CanUse(CanUseItem::Sticks) && AtDay);}),
                  EventPairing(&BeanPlantFairy, []{return BeanPlantFairy || (GY_Main.CanPlantBean() && CanPlay(SongOfStorms));}),
                  EventPairing(&BugRock,        []{return true;}),
                }, {
                  //Locations
                  ItemLocationPairing(&GY_FreestandingPoH,       []{return (IsAdult && (GY_Main.CanPlantBean() || CanUse(CanUseItem::Longshot))) || (LogicGraveyardPoH && CanUse(CanUseItem::Boomerang));}),
                  ItemLocationPairing(&GY_DampeGravediggingTour, []{return IsChild && AtNight;}), //This needs to change
                  ItemLocationPairing(&GY_GS_Wall,               []{return CanUse(CanUseItem::Boomerang) && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(&GY_GS_BeanPatch,          []{return CanPlantBugs && CanChildAttack;}),
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

  Exit GY_ShieldGrave = Exit("GY Shield Grave", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&GY_ShieldGraveChest, []{return true;})
                  //Free Fairies
                }, {
                  //Exits
                  ExitPairing::Both(&GY_Main, []{return true;})
  });

  Exit GY_HeartPieceGrave = Exit("GY Heart Piece Grave", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&GY_HeartPieceGraveChest, []{return CanPlay(SunsSong);})
                }, {
                  //Exits
                  ExitPairing::Both(&GY_Main, []{return true;})
  });

  Exit GY_ComposersGrave = Exit("GY Composers Grave", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&GY_ComposersGraveChest, []{return HasFireSource;}),
                  ItemLocationPairing(&SongFromComposersGrave, []{return IsAdult || (Slingshot || Boomerang || Sticks || HasExplosives || KokiriSword);}),
                }, {
                  //Exits
                  ExitPairing::Both(&GY_Main, []{return true;}),
  });

  Exit GY_DampesGrave = Exit("GY Dampes Grave", "", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&DekuNutDrop,          []{return true;}),
                  EventPairing(&DampesWindmillAccess, []{return DampesWindmillAccess || (IsAdult && CanPlay(SongOfTime));}),
                }, {
                  //Locations
                  ItemLocationPairing(&GY_HookshotChest,            []{return true;}),
                  ItemLocationPairing(&GY_DampeRaceFreestandingPoH, []{return IsAdult || LogicChildDampeRacePoH;}),
                }, {
                  //Exits
                  ExitPairing::Both(&GY_Main,      []{return true;}),
                  ExitPairing::Both(&Kak_Windmill, []{return IsAdult && CanPlay(SongOfTime);})
  });

  Exit GY_DampesHouse = Exit("GY Dampes House", "", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&GY_Main, []{return true;})
  });

  Exit GY_WarpPadRegion = Exit("GY Warp Pad Region", "Graveyard", "the Graveyard", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GossipStoneFairy, []{return GossipStoneFairy || CanSummonGossipFairyWithoutSuns;}),
                }, {
                  //Locations
                  //GY Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&GY_Main,                  []{return true;}),
                  ExitPairing::Both(&ShadowTemple_Entryway,    []{return Dungeon::ShadowTemple.IsVanilla() && (CanUse(CanUseItem::Dins_Fire) || (LogicShadowFireArrowEntry && CanUse(CanUseItem::Fire_Arrows)));}),
                  ExitPairing::Both(&ShadowTemple_MQ_Entryway, []{return Dungeon::ShadowTemple.IsMQ()      && (CanUse(CanUseItem::Dins_Fire) || (LogicShadowFireArrowEntry && CanUse(CanUseItem::Fire_Arrows)));}),
  });

  Exit Kak_BehindGate = Exit("Kak Behind Gate", "Kakariko Village", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&Kak_Main, []{return IsAdult || LogicVisibleCollision || KakarikoVillageGateOpen || OpenKakariko.Is(OPENKAKARIKO_OPEN);}),
                  ExitPairing::Both(&DMT_Main, []{return true;})
  });

  Exit DMT_Main = Exit("Death Mountain", "Death Mountain", "Death Mountain Trail", DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&BeanPlantFairy, []{return BeanPlantFairy || (DMT_Main.CanPlantBean() && CanPlay(SongOfStorms) && (HasExplosives || GoronBracelet));}),
                }, {
                  //Locations
                  ItemLocationPairing(&DMT_Chest,                  []{return CanBlastOrSmash || (LogicDMTBombable && IsChild && GoronBracelet);}),
                  ItemLocationPairing(&DMT_FreestandingPoH,        []{return (DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO)) || CanUse(CanUseItem::Nayrus_Love) || Fairy || CanUse(CanUseItem::Hover_Boots) || (IsAdult && DMT_Main.CanPlantBean() && (HasExplosives || GoronBracelet));}),
                  ItemLocationPairing(&DMT_GS_BeanPatch,           []{return CanPlantBugs && (HasExplosives || GoronBracelet || (LogicDMTSoilGS && CanUse(CanUseItem::Boomerang)));}),
                  ItemLocationPairing(&DMT_GS_NearKak,             []{return CanBlastOrSmash;}),
                  ItemLocationPairing(&DMT_GS_AboveDodongosCavern, []{return IsAdult && AtNight && CanUse(CanUseItem::Hammer) && CanGetNightTimeGS;})
                }, {
                  //Exits
                  ExitPairing::Both(&Kak_BehindGate,          []{return true;}),
                  ExitPairing::Both(&GC_Main,                 []{return true;}),
                  ExitPairing::Both(&DMT_Summit,              []{return CanBlastOrSmash || (IsAdult && (DMT_Main.CanPlantBean() && GoronBracelet));}),
                  ExitPairing::Both(&DodongosCavern_Entryway, []{return HasExplosives || GoronBracelet || IsAdult;}),
                  ExitPairing::Both(&DMT_StormsGrotto,        []{return CanOpenStormGrotto;})
  });

  Exit DMT_Summit = Exit("Death Mountain Summit", "Death Mountain", "Death Mountain", DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&PrescriptionAccess, []{return PrescriptionAccess || (IsAdult && (BrokenSwordAccess || BrokenSword));}),
                  EventPairing(&GossipStoneFairy,   []{return GossipStoneFairy   || CanSummonGossipFairy;}),
                  EventPairing(&BugRock,            []{return true;}),
                }, {
                  //Locations
                  ItemLocationPairing(&DMT_Biggoron,            []{return IsAdult && (ClaimCheck || (GuaranteeTradePath && (EyedropsAccess || (Eyedrops && DisableTradeRevert))));}),
                  ItemLocationPairing(&DMT_GS_FallingRocksPath, []{return IsAdult && AtNight && CanUse(CanUseItem::Hammer) && CanGetNightTimeGS;}),
                  //DMT Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&DMT_Main,               []{return true;}),
                  ExitPairing::Both(&DMC_UpperLocal,         []{return true;}),
                  ExitPairing::Both(&DMT_OwlFlight,          []{return IsChild;}),
                  ExitPairing::Both(&DMT_CowGrotto,          []{return CanBlastOrSmash;}),
                  ExitPairing::Both(&DMT_GreatFairyFountain, []{return CanBlastOrSmash;}),
  });

  Exit DMT_OwlFlight = Exit("DMT Owl Flight", "Death Mountain", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&Kak_ImpasLedge, []{return true;})
  });

  Exit DodongosCavern_Entryway = Exit("Dodongos Cavern Entryway", "Death Mountain", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&DodongosCavern_Beginning,    []{return Dungeon::DodongosCavern.IsVanilla();}),
                  ExitPairing::Both(&DodongosCavern_MQ_Beginning, []{return Dungeon::DodongosCavern.IsMQ();}),
                  ExitPairing::Both(&DMT_Main,                    []{return true;}),
  });

  Exit DMT_CowGrotto = Exit("DMT Cow Grotto", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&DMT_CowGrottoCow, []{return CanPlay(EponasSong);}),
                }, {
                  //Exits
                  ExitPairing::Both(&DMT_Main, []{return true;})

  });

  Exit DMT_StormsGrotto = Exit("DMT Storms Grotto", "", "", NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  ItemLocationPairing(&DMT_StormsGrottoChest, []{return true;}),
                  //DMT Storms Grotto Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&DMT_Main, []{return true;})
  });

  Exit DMT_GreatFairyFountain = Exit("DMT Great Fairy Fountain", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&DMT_GreatFairyReward, []{return CanPlay(ZeldasLullaby);}),
                }, {
                  //Exits
                  ExitPairing::Both(&DMT_Summit, []{return true;})
  });

  Exit GC_Main = Exit("Goron City", "Goron City", "Goron City", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GossipStoneFairy,          []{return GossipStoneFairy          || CanSummonGossipFairyWithoutSuns;}),
                  EventPairing(&StickPot,                  []{return StickPot                  || IsChild;}),
                  EventPairing(&BugRock,                   []{return true;}),
                  EventPairing(&GoronCityChildFire,        []{return GoronCityChildFire        || (IsChild && CanUse(CanUseItem::Dins_Fire));}),
                  EventPairing(&GCWoodsWarpOpen,           []{return GCWoodsWarpOpen           || (CanBlastOrSmash || CanUse(CanUseItem::Dins_Fire) || CanUse(CanUseItem::Bow) || GoronBracelet || GoronCityChildFire);}),
                  EventPairing(&StopGCRollingGoronAsAdult, []{return StopGCRollingGoronAsAdult || (IsAdult && (GoronBracelet || HasExplosives || Bow || (LogicLinkGoronDins && CanUse(CanUseItem::Dins_Fire))));}),
                }, {
                  //Locations
                  ItemLocationPairing(&GC_MazeLeftChest,       []{return CanUse(CanUseItem::Hammer) || CanUse(CanUseItem::Silver_Gauntlets) || (LogicGoronCityLeftMost && HasExplosives && CanUse(CanUseItem::Hover_Boots));}),
                  ItemLocationPairing(&GC_MazeCenterChest,     []{return CanBlastOrSmash  || CanUse(CanUseItem::Silver_Gauntlets);}),
                  ItemLocationPairing(&GC_MazeRightChest,      []{return CanBlastOrSmash  || CanUse(CanUseItem::Silver_Gauntlets);}),
                  ItemLocationPairing(&GC_PotFreestandingPoH,  []{return IsChild && GoronCityChildFire && (Bombs || (GoronBracelet && LogicGoronCityPotWithStrength) || (HasBombchus && LogicGoronCityPot));}),
                  ItemLocationPairing(&GC_RollingGoronAsChild, []{return IsChild && (HasExplosives || (GoronBracelet && LogicChildRollingWithStrength));}),
                  ItemLocationPairing(&GC_RollingGoronAsAdult, []{return StopGCRollingGoronAsAdult;}),
                  ItemLocationPairing(&GC_GS_BoulderMaze,      []{return IsChild && HasExplosives;}),
                  ItemLocationPairing(&GC_GS_CenterPlatform,   []{return IsAdult;}),
                  //GC Maze Gossip Stone
                  //GC MediGoron Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&DMT_Main,           []{return true;}),
                  ExitPairing::Both(&GC_WoodsWarp,       []{return GCWoodsWarpOpen;}),
                  ExitPairing::Both(&GC_Shop,            []{return (IsAdult && StopGCRollingGoronAsAdult) || (IsChild && (HasExplosives || GoronBracelet || GoronCityChildFire));}),
                  ExitPairing::Both(&GC_DaruniasChamber, []{return (IsAdult && StopGCRollingGoronAsAdult) || (IsChild && CanPlay(ZeldasLullaby));}),
                  ExitPairing::Both(&GC_Grotto,          []{return IsAdult && ((CanPlay(SongOfTime) && ((DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_QUADRUPLE)) || CanUse(CanUseItem::Goron_Tunic) || CanUse(CanUseItem::Longshot) || CanUse(CanUseItem::Nayrus_Love))) || (DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO) && CanUse(CanUseItem::Goron_Tunic) && CanUse(CanUseItem::Hookshot)) ||(CanUse(CanUseItem::Nayrus_Love) && CanUse(CanUseItem::Hookshot)));}),
  });

  Exit GC_WoodsWarp = Exit("GC Woods Warp", "Goron City", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GCWoodsWarpOpen, []{return GCWoodsWarpOpen || (CanBlastOrSmash || CanUse(CanUseItem::Dins_Fire));}),
                }, {}, {
                  //Exits
                  ExitPairing::Both(&GC_Main, []{return CanLeaveForest && GCWoodsWarpOpen;}),
                  ExitPairing::Both(&LW_Main, []{return true;})
  });

  Exit GC_DaruniasChamber = Exit("GC Darunias Chamber", "Goron City", "Goron City", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GoronCityChildFire, []{return GoronCityChildFire || (CanUse(CanUseItem::Sticks));}),
                }, {
                  //Locations
                  ItemLocationPairing(&GC_DaruniasJoy, []{return IsChild && CanPlay(SariasSong);})
                }, {
                  //Exits
                  ExitPairing::Both(&GC_Main,        []{return true;}),
                  ExitPairing::Both(&DMC_LowerLocal, []{return IsAdult;})
  });

  Exit GC_Shop = Exit("GC Shop", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&GC_ShopItem1, []{return true;}),
                  ItemLocationPairing(&GC_ShopItem2, []{return true;}),
                  ItemLocationPairing(&GC_ShopItem3, []{return true;}),
                  ItemLocationPairing(&GC_ShopItem4, []{return true;}),
                  ItemLocationPairing(&GC_ShopItem5, []{return true;}),
                  ItemLocationPairing(&GC_ShopItem6, []{return true;}),
                  ItemLocationPairing(&GC_ShopItem7, []{return true;}),
                  ItemLocationPairing(&GC_ShopItem8, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&GC_Main, []{return true;})
  });

  Exit GC_Grotto = Exit("GC Grotto", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&GC_DekuScrubGrottoLeft,   []{return CanStunDeku;}),
                  ItemLocationPairing(&GC_DekuScrubGrottoRight,  []{return CanStunDeku;}),
                  ItemLocationPairing(&GC_DekuScrubGrottoCenter, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing::Both(&GC_Main, []{return true;})
  });

  Exit DMC_UpperNearby = Exit("DMC Upper Nearby", "Death Mountain Crater", "Death Mountain Crater", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&DMC_UpperLocal,  []{return CanUse(CanUseItem::Goron_Tunic);}),
                  ExitPairing::Both(&DMT_Summit,      []{return true;}),
                  ExitPairing::Both(&DMC_UpperGrotto, []{return CanBlastOrSmash;})
  });

  Exit DMC_UpperLocal = Exit("DMC Upper Local", "Death Mountain Crater", "Death Mountain Crater", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GossipStoneFairy, []{return GossipStoneFairy || (HasExplosives && CanSummonGossipFairyWithoutSuns);}),
                }, {
                  //Locations
                  ItemLocationPairing(&DMC_WallFreestandingPoH, []{return true;}),
                  ItemLocationPairing(&DMC_GS_Crate,            []{return IsChild && CanChildAttack;}),
                  //DMC Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&DMC_UpperNearby,      []{return true;}),
                  ExitPairing::Both(&DMC_LadderAreaNearby, []{return true;}),
                  ExitPairing::Both(&DMC_CentralNearby,    []{return CanUse(CanUseItem::Goron_Tunic) && CanUse(CanUseItem::Longshot) && ((DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_QUADRUPLE)) || (Fairy && !ShuffleDungeonEntrances) || CanUse(CanUseItem::Nayrus_Love));})
  });

  Exit DMC_LadderAreaNearby = Exit("DMC Ladder Area Nearby", "Death Mountain Crater", "Death Mountain Crater", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&DMC_DekuScrub, []{return IsChild && CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing::Both(&DMC_UpperNearby, []{return IsAdult;}),
                  ExitPairing::Both(&DMC_LowerNearby, []{return CanUse(CanUseItem::Hover_Boots) || (LogicCraterUpperToLower && CanUse(CanUseItem::Hammer));})
  });

  Exit DMC_LowerNearby = Exit("DMC Lower Nearby", "Death Mountain Crater", "Death Mountain Crater", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&DMC_LowerLocal,         []{return CanUse(CanUseItem::Goron_Tunic);}),
                  ExitPairing::Both(&GC_DaruniasChamber,     []{return true;}),
                  ExitPairing::Both(&DMC_GreatFairyFountain, []{return CanUse(CanUseItem::Hammer);}),
                  ExitPairing::Both(&DMC_HammerGrotto,       []{return CanUse(CanUseItem::Hammer);})
  });

  Exit DMC_LowerLocal = Exit("DMC Lower Local", "Death Mountain Crater", "Death Mountain Crater", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&DMC_LowerNearby,      []{return true;}),
                  ExitPairing::Both(&DMC_LadderAreaNearby, []{return true;}),
                  ExitPairing::Both(&DMC_CentralNearby,    []{return CanUse(CanUseItem::Hover_Boots) || CanUse(CanUseItem::Hookshot);}),
                  ExitPairing::Both(&FireTemple_Entrance,  []{return (CanUse(CanUseItem::Hover_Boots) || CanUse(CanUseItem::Hookshot)) && (LogicFewerTunicRequirements || CanUse(CanUseItem::Goron_Tunic));}),
  });

  Exit DMC_CentralNearby = Exit("DMC Central Nearby", "Death Mountain Crater", "Death Mountain Crater", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&DMC_VolcanoFreestandingPoH, []{return IsAdult && (DMC_CentralLocal.CanPlantBean() || (LogicCraterBeanPoHWithHovers && HoverBoots));}),
                  ItemLocationPairing(&SheikInCrater,              []{return IsAdult;}),
                }, {
                  //Exits
                  ExitPairing::Both(&DMC_CentralLocal, []{return CanUse(CanUseItem::Goron_Tunic);})
  });

  Exit DMC_CentralLocal = Exit("DMC Central Local", "Death Mountain Crater", "Death Mountain Crater", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&BeanPlantFairy, []{return BeanPlantFairy || (DMC_CentralLocal.CanPlantBean() && CanPlay(SongOfStorms));}),
                }, {
                  //Locations
                  ItemLocationPairing(&DMC_GS_BeanPatch, []{return CanPlantBugs && CanChildAttack;}),
                }, {
                  //Exits
                  ExitPairing::Both(&DMC_CentralNearby,   []{return true;}),
                  ExitPairing::Both(&DMC_LowerNearby,     []{return IsAdult && (CanUse(CanUseItem::Hover_Boots) || CanUse(CanUseItem::Hookshot) || DMC_CentralLocal.CanPlantBean());}),
                  ExitPairing::Both(&DMC_UpperNearby,     []{return IsAdult && DMC_CentralLocal.CanPlantBean();}),
                  ExitPairing::Both(&FireTemple_Entrance, []{return (IsChild && ShuffleDungeonEntrances) || (IsAdult && (LogicFewerTunicRequirements || CanUse(CanUseItem::Goron_Tunic)));}),
  });

  Exit FireTemple_Entrance = Exit("Fire Temple Entrance", "Death Mountain Crater", "Death Mountain Crater", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                    ExitPairing::Both(&FireTemple_Lower,    []{return Dungeon::FireTemple.IsVanilla();}),
                    ExitPairing::Both(&FireTemple_MQ_Lower, []{return Dungeon::FireTemple.IsMQ();}),
  });

  Exit DMC_GreatFairyFountain = Exit("DMC Great Fairy Fountain", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&DMC_GreatFairyReward, []{return CanPlay(ZeldasLullaby);}),
                }, {
                  //Exits
                  ExitPairing::Both(&DMC_LowerLocal, []{return true;})
  });

  Exit DMC_UpperGrotto = Exit("DMC Upper Grotto", "", "", NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  ItemLocationPairing(&DMC_UpperGrottoChest, []{return true;})
                  //DMC Upper Grotto Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&DMC_UpperLocal, []{return true;})
  });

  Exit DMC_HammerGrotto = Exit("DMC Hammer Grotto", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&DMC_DekuScrubGrottoLeft,   []{return CanStunDeku;}),
                  ItemLocationPairing(&DMC_DekuScrubGrottoRight,  []{return CanStunDeku;}),
                  ItemLocationPairing(&DMC_DekuScrubGrottoCenter, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing::Both(&DMC_LowerLocal, []{return true;})
  });

  Exit ZR_Front = Exit("ZR Front", "Zora River", "Zora's River", DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&ZR_GS_Tree, []{return IsChild && CanChildAttack;}),
                }, {
                  //Exits
                  ExitPairing::Both(&ZR_Main, []{return IsAdult || HasExplosives;}),
                  ExitPairing::Both(&HF_Main, []{return true;})
  });

  Exit ZR_Main = Exit("Zora River", "Zora River", "Zora's River", DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GossipStoneFairy, []{return GossipStoneFairy || CanSummonGossipFairy;}),
                  EventPairing(&BeanPlantFairy,   []{return BeanPlantFairy   || (ZR_Main.CanPlantBean() && CanPlay(SongOfStorms));}),
                  EventPairing(&ButterflyFairy,   []{return ButterflyFairy   || CanUse(CanUseItem::Sticks);}),
                  EventPairing(&BugShrub,         []{return BugShrub         || CanCutShrubs;}),
                }, {
                  //Locations
                  ItemLocationPairing(&ZR_MagicBeanSalesman,             []{return IsChild;}),
                  ItemLocationPairing(&ZR_FrogsOcarinaGame,              []{return IsChild && CanPlay(ZeldasLullaby) && CanPlay(SariasSong) && CanPlay(SunsSong) && CanPlay(EponasSong) && CanPlay(SongOfTime) && CanPlay(SongOfStorms);}),
                  ItemLocationPairing(&ZR_FrogsInTheRain,                []{return IsChild && CanPlay(SongOfStorms);}),
                  ItemLocationPairing(&ZR_NearOpenGrottoFreestandingPoH, []{return IsChild || CanUse(CanUseItem::Hover_Boots) || (IsAdult && LogicZoraRiverLower);}),
                  ItemLocationPairing(&ZR_NearDomainFreestandingPoH,     []{return IsChild || CanUse(CanUseItem::Hover_Boots) || (IsAdult && LogicZoraRiverUpper);}),
                  ItemLocationPairing(&ZR_GS_Ladder,                     []{return IsChild && AtNight && CanChildAttack && CanGetNightTimeGS;}),
                  ItemLocationPairing(&ZR_GS_NearRaisedGrottos,          []{return CanUse(CanUseItem::Hookshot) && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(&ZR_GS_AboveBridge,                []{return CanUse(CanUseItem::Hookshot) && AtNight && CanGetNightTimeGS;}),
                  //ZR Near Grottos Gossip Stone
                  //ZR Near Domain Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&ZR_Front,           []{return true;}),
                  ExitPairing::Both(&ZR_OpenGrotto,      []{return true;}),
                  ExitPairing::Both(&ZR_FairyGrotto,     []{return CanBlastOrSmash;}),
                  ExitPairing::Both(&LW_Main,            []{return CanDive || CanUse(CanUseItem::Iron_Boots);}),
                  ExitPairing::Both(&ZR_StormsGrotto,    []{return CanOpenStormGrotto;}),
                  ExitPairing::Both(&ZR_BehindWaterfall, []{return CanPlay(ZeldasLullaby);})
  });

  Exit ZR_BehindWaterfall = Exit("ZR Behind Waterfall", "Zora River", "", DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&ZR_Main, []{return true;}),
                  ExitPairing::Both(&ZD_Main, []{return true;})
  });

  Exit ZR_OpenGrotto = Exit("ZR Open Grotto", "", "", NO_DAY_NIGHT_CYCLE, grottoEvents, {
                  //Locations
                  ItemLocationPairing(&ZR_OpenGrottoChest, []{return true;})
                  //ZR Open Grotto Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&ZR_Main, []{return true;})
  });

  Exit ZR_FairyGrotto = Exit("ZR Fairy Grotto", "", "", NO_DAY_NIGHT_CYCLE, {
                  //Event
                  EventPairing(&FreeFairies, []{return true;}),
                }, {}, {
                  //Exits
                  ExitPairing::Both(&ZR_Main, []{return true;})
  });

  Exit ZR_StormsGrotto = Exit("ZR Storms Grotto", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&ZR_DekuScrubGrottoRear,  []{return CanStunDeku;}),
                  ItemLocationPairing(&ZR_DekuScrubGrottoFront, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing::Both(&ZR_Main, []{return true;})
  });

  Exit ZD_Main = Exit("Zoras Domain", "Zoras Domain", "Zora's Domain", NO_DAY_NIGHT_CYCLE, {
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
                  ItemLocationPairing(&ZD_DivingMinigame,     []{return IsChild;}),
                  ItemLocationPairing(&ZD_Chest,              []{return CanUse(CanUseItem::Sticks);}),
                  ItemLocationPairing(&ZD_KingZoraThawed,     []{return KingZoraThawed;}),
                  ItemLocationPairing(&ZD_GS_FrozenWaterfall, []{return IsAdult && AtNight && (Hookshot || Bow || MagicMeter) && CanGetNightTimeGS;}),
                  //ZD Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&ZR_BehindWaterfall, []{return true;}),
                  ExitPairing::Both(&LH_Main,            []{return IsChild && CanDive;}),
                  ExitPairing::Both(&ZD_BehindKingZora,  []{return DeliverLetter || ZorasFountain.Is(ZORASFOUNTAIN_OPEN) || (ZorasFountain.Is(ZORASFOUNTAIN_ADULT) && IsAdult);}),
                  ExitPairing::Both(&ZD_Shop,            []{return IsChild || BlueFire;}),
                  ExitPairing::Both(&ZD_StormsGrotto,    []{return CanOpenStormGrotto;})
  });

  Exit ZD_BehindKingZora = Exit("ZD Behind King Zora", "Zoras Domain", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&ZD_Main, []{return DeliverLetter || ZorasFountain.Is(ZORASFOUNTAIN_OPEN) || (ZorasFountain.Is(ZORASFOUNTAIN_ADULT) && IsAdult);}),
                  ExitPairing::Both(&ZF_Main, []{return true;})
  });

  Exit ZD_Shop = Exit("ZD Shop", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&ZD_ShopItem1, []{return true;}),
                  ItemLocationPairing(&ZD_ShopItem2, []{return true;}),
                  ItemLocationPairing(&ZD_ShopItem3, []{return true;}),
                  ItemLocationPairing(&ZD_ShopItem4, []{return true;}),
                  ItemLocationPairing(&ZD_ShopItem5, []{return true;}),
                  ItemLocationPairing(&ZD_ShopItem6, []{return true;}),
                  ItemLocationPairing(&ZD_ShopItem7, []{return true;}),
                  ItemLocationPairing(&ZD_ShopItem8, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&ZD_Main, []{return true;})
  });

  Exit ZD_StormsGrotto = Exit("ZD Storms Grotto", "", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FreeFairies, []{return true;}),
                }, {}, {
                  //Exits
                  ExitPairing::Both(&ZD_Main, []{return true;}),
  });

  Exit ZF_Main = Exit("Zoras Fountain", "Zoras Fountain", "Zora's Fountain", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GossipStoneFairy, []{return GossipStoneFairy || CanSummonGossipFairyWithoutSuns;}),
                  EventPairing(&ButterflyFairy,   []{return ButterflyFairy   || (CanUse(CanUseItem::Sticks) && AtDay);}),
                }, {
                  //Locations
                  ItemLocationPairing(&ZF_IcebergFreestandingPoH, []{return IsAdult;}),
                  ItemLocationPairing(&ZF_BottomFreestandingPoH,  []{return IsAdult && IronBoots && (LogicFewerTunicRequirements || CanUse(CanUseItem::Zora_Tunic));}),
                  ItemLocationPairing(&ZF_GS_Tree,                []{return IsChild;}),
                  ItemLocationPairing(&ZF_GS_AboveTheLog,         []{return CanUse(CanUseItem::Boomerang) && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(&ZF_GS_HiddenCave,          []{return CanUse(CanUseItem::Silver_Gauntlets) && CanBlastOrSmash && CanUse(CanUseItem::Hookshot) && AtNight && CanGetNightTimeGS;}),
                  //ZF Fairy Gossip Stone
                  //ZF Jabu Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&ZD_BehindKingZora,           []{return true;}),
                  ExitPairing::Both(&JabuJabusBelly_Beginning,    []{return Dungeon::JabuJabusBelly.IsVanilla() && (IsChild && Fish);}),
                  ExitPairing::Both(&JabuJabusBelly_MQ_Beginning, []{return Dungeon::JabuJabusBelly.IsMQ()      && (IsChild && Fish);}),
                  ExitPairing::Both(&IceCavern_Beginning,         []{return Dungeon::IceCavern.IsVanilla() && IsAdult;}),
                  ExitPairing::Both(&IceCavern_MQ_Beginning,      []{return Dungeon::IceCavern.IsMQ()      && IsAdult;}),
                  ExitPairing::Both(&ZF_GreatFairyFountain,       []{return HasExplosives;})
  });

  Exit ZF_GreatFairyFountain = Exit("ZF Great Fairy Fountain", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&ZF_GreatFairyReward, []{return CanPlay(ZeldasLullaby);}),
                }, {
                  //Exits
                  ExitPairing::Both(&ZF_Main, []{return true;})
  });

  Exit LLR_Main = Exit("Lon Lon Ranch", "Lon Lon Ranch", "Lon Lon Ranch", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&Epona,    []{return Epona    || (CanPlay(EponasSong) && IsAdult && AtDay);}),
                  EventPairing(&LinksCow, []{return LinksCow || (CanPlay(EponasSong) && IsAdult && AtDay);}),
                }, {
                  //Locations
                  ItemLocationPairing(&SongFromMalon,      []{return IsChild && ZeldasLetter && Ocarina && AtDay;}),
                  ItemLocationPairing(&LLR_GS_Tree,        []{return IsChild;}),
                  ItemLocationPairing(&LLR_GS_RainShed,    []{return IsChild && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(&LLR_GS_HouseWindow, []{return CanUse(CanUseItem::Boomerang) && AtNight && CanGetNightTimeGS;}),
                  ItemLocationPairing(&LLR_GS_BackWall,    []{return CanUse(CanUseItem::Boomerang) && AtNight && CanGetNightTimeGS;}),
                }, {
                  //Exits
                  ExitPairing::Both(&HF_Main,         []{return true;}),
                  ExitPairing::Both(&LLR_TalonsHouse, []{return true;}),
                  ExitPairing::Both(&LLR_Stables,     []{return true;}),
                  ExitPairing::Both(&LLR_Tower,       []{return true;}),
                  ExitPairing::Both(&LLR_Grotto,      []{return IsChild;})
  });

  Exit LLR_TalonsHouse = Exit("LLR Talons House", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&LLR_TalonsChickens, []{return IsChild && AtDay && ZeldasLetter;})
                }, {
                  //Exits
                  ExitPairing::Both(&LLR_Main, []{return true;})
  });

  Exit LLR_Stables = Exit("LLR Stables", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&LLR_StablesLeftCow,  []{return CanPlay(EponasSong);}),
                  ItemLocationPairing(&LLR_StablesRightCow, []{return CanPlay(EponasSong);}),
                }, {
                  //Exits
                  ExitPairing::Both(&LLR_Main, []{return true;})
  });

  Exit LLR_Tower = Exit("LLR Tower", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&LLR_FreestandingPoH, []{return IsChild;}),
                  ItemLocationPairing(&LLR_TowerLeftCow,  []{return CanPlay(EponasSong);}),
                  ItemLocationPairing(&LLR_TowerRightCow, []{return CanPlay(EponasSong);}),
                }, {
                  //Exits
                  ExitPairing::Both(&LLR_Main, []{return true;}),
  });

  Exit LLR_Grotto = Exit("LLR Grotto", "", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&LLR_DekuScrubGrottoLeft,   []{return CanStunDeku;}),
                  ItemLocationPairing(&LLR_DekuScrubGrottoRight,  []{return CanStunDeku;}),
                  ItemLocationPairing(&LLR_DekuScrubGrottoCenter, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing::Both(&LLR_Main, []{return true;}),
  });

  /*--------------------------
  |    VANILLA DUNGEONS     |
  ---------------------------*/

  Exit DekuTree_Lobby = Exit("Deku Tree Lobby", "Deku Tree", "Deku Tree", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&DekuBabaSticks, []{return DekuBabaSticks || (IsAdult || KokiriSword || Boomerang);}),
                  EventPairing(&DekuBabaNuts,   []{return DekuBabaNuts   || (IsAdult || KokiriSword || Slingshot || Sticks || HasExplosives || CanUse(CanUseItem::Dins_Fire));}),
                }, {
                  //Locations
                  ItemLocationPairing(&DekuTree_MapChest,             []{return true;}),
                  ItemLocationPairing(&DekuTree_CompassChest,         []{return true;}),
                  ItemLocationPairing(&DekuTree_CompassRoomSideChest, []{return true;}),
                  ItemLocationPairing(&DekuTree_BasementChest,        []{return IsAdult || CanChildAttack || Nuts;}),
                  ItemLocationPairing(&DekuTree_GS_CompassRoom,       []{return IsAdult || CanChildAttack;}),
                  ItemLocationPairing(&DekuTree_GS_BasementVines,     []{return CanUseProjectile || CanUse(CanUseItem::Dins_Fire) || (LogicDekuBasementGS && (IsAdult || Sticks || KokiriSword));}),
                  ItemLocationPairing(&DekuTree_GS_BasementGate,      []{return IsAdult || CanChildAttack;}),
                  ItemLocationPairing(&DekuTree_GS_BasementBackRoom,  []{return ((HasFireSourceWithTorch || (LogicDekuB1WebsWithBow && CanUse(CanUseItem::Bow))) && (CanUse(CanUseItem::Slingshot) || CanUse(CanUseItem::Bow)) && CanBlastOrSmash && HookshotOrBoomerang) || ((LogicDekuB1Skip || IsAdult) && IsChild && HasExplosives && CanUse(CanUseItem::Boomerang) && (Sticks || CanUse(CanUseItem::Dins_Fire)));}),
                }, {
                  //Exits
                  ExitPairing::Both(&KF_OutsideDekuTree,       []{return true;}),
                  ExitPairing::Both(&DekuTree_SlingshotRoom,   []{return HasShield;}),
                  ExitPairing::Both(&DekuTree_BossRoom,        []{return (HasFireSourceWithTorch || (LogicDekuB1WebsWithBow && CanUse(CanUseItem::Bow))) && (LogicDekuB1Skip || (IsAdult || CanUse(CanUseItem::Slingshot)));})
  });

  Exit DekuTree_SlingshotRoom = Exit("Deku Tree Slingshot Room", "Deku Tree", "Deku Tree", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&DekuTree_SlingshotChest,         []{return true;}),
                  ItemLocationPairing(&DekuTree_SlingshotRoomSideChest, []{return true;})
                }, {
                  //Exits
                  ExitPairing::Both(&DekuTree_Lobby, []{return true;})
  });

  Exit DekuTree_BossRoom = Exit("Deku Tree Boss Room", "Deku Tree", "Deku Tree", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&DekuTreeClear, []{return DekuTreeClear || (HasShield && (IsAdult || KokiriSword || Sticks));})
                }, {
                  //Locations
                  ItemLocationPairing(&QueenGohma,               []{return HasShield && (IsAdult || KokiriSword || Sticks);}),
                  ItemLocationPairing(&DekuTree_QueenGohmaHeart, []{return HasShield && (IsAdult || KokiriSword || Sticks);}),
                }, {
                  //Exits
                  ExitPairing::Both(&DekuTree_Lobby, []{return true;})
  });

  Exit DodongosCavern_Beginning = Exit("Dodongos Cavern Beginning", "Dodongos Cavern", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&DodongosCavern_Entryway, []{return true;}),
                  ExitPairing::Both(&DodongosCavern_Lobby,    []{return CanBlastOrSmash || GoronBracelet;})
  });

  Exit DodongosCavern_Lobby = Exit("Dodongos Cavern Lobby", "Dodongos Cavern", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GossipStoneFairy, []{return GossipStoneFairy || CanSummonGossipFairy;}),
                }, {
                  //Locations
                  ItemLocationPairing(&DodongosCavern_MapChest,                      []{return true;}),
                  ItemLocationPairing(&DodongosCavern_CompassChest,                  []{return IsAdult || Sticks || (CanUse(CanUseItem::Dins_Fire) && (Slingshot || HasExplosives || KokiriSword));}),
                  ItemLocationPairing(&DodongosCavern_GS_SideRoomNearLowerLizalfos,  []{return HasExplosives || IsAdult || Slingshot || Boomerang || Sticks || KokiriSword;}),
                  ItemLocationPairing(&DodongosCavern_GS_Scarecrow,                  []{return CanUse(CanUseItem::Scarecrow) || CanUse(CanUseItem::Longshot) || (LogicDCScarecrowGS && (IsAdult || CanChildAttack));}),
                  ItemLocationPairing(&DodongosCavern_DekuScrubSideRoomNearDodongos, []{return IsAdult || Slingshot || Sticks || HasExplosives || KokiriSword;}),
                  ItemLocationPairing(&DodongosCavern_DekuScrubLobby,                []{return true;}),
                  //Dodongos Cavern Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&DodongosCavern_Beginning, []{return true;}),
                  ExitPairing::Both(&DodongosCavern_Climb,     []{return (IsAdult || ((Sticks || CanUse(CanUseItem::Dins_Fire)) && (Slingshot || Sticks || HasExplosives || KokiriSword))) && (HasExplosives || GoronBracelet || CanUse(CanUseItem::Dins_Fire) ||(LogicDCStaircase && CanUse(CanUseItem::Bow)));})
  });

  Exit DodongosCavern_Climb = Exit("Dodongos Cavern Climb", "Dodongos Cavern", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&DodongosCavern_BombFlowerPlatformChest,   []{return true;}),
                  ItemLocationPairing(&DodongosCavern_GS_VinesAboveStairs,       []{return true;}),
                  ItemLocationPairing(&DodongosCavern_DekuScrubNearBombBagRight, []{return CanBlastOrSmash;}),
                  ItemLocationPairing(&DodongosCavern_DekuScrubNearBombBagLeft,  []{return CanBlastOrSmash;}),
                }, {
                  //Exits
                  ExitPairing::Both(&DodongosCavern_Lobby,     []{return true;}),
                  ExitPairing::Both(&DodongosCavern_FarBridge, []{return (IsChild && (Slingshot || (LogicDCSlingshotSkip && (Sticks || HasExplosives || KokiriSword)))) || (IsAdult && (Bow || HoverBoots || CanUse(CanUseItem::Longshot) || LogicDCJump));})
  });

  Exit DodongosCavern_FarBridge = Exit("Dodongos Cavern Far Bridge", "Dodongos Cavern", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&DodongosCavern_BombBagChest,         []{return true;}),
                  ItemLocationPairing(&DodongosCavern_EndOfBridgeChest,     []{return CanBlastOrSmash;}),
                  ItemLocationPairing(&DodongosCavern_GS_AlcoveAboveStairs, []{return HookshotOrBoomerang;}),
                }, {
                  //Exits
                  ExitPairing::Both(&DodongosCavern_BossArea, []{return HasExplosives;}),
                  ExitPairing::Both(&DodongosCavern_Lobby,    []{return true;})
  });

  Exit DodongosCavern_BossArea = Exit("Dodongos Cavern Boss Area", "Dodongos Cavern", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPot,            []{return true;}),
                  EventPairing(&DodongosCavernClear, []{return DodongosCavernClear || ((Bombs || GoronBracelet) && (IsAdult || Sticks || KokiriSword));})
                }, {
                  //Locations
                  ItemLocationPairing(&DodongosCavern_BossRoomChest,    []{return true;}),
                  ItemLocationPairing(&DodongosCavern_KingDodongoHeart, []{return (Bombs || GoronBracelet) && (IsAdult || Sticks || KokiriSword);}),
                  ItemLocationPairing(&KingDodongo,                     []{return (Bombs || GoronBracelet) && (IsAdult || Sticks || KokiriSword);}),
                  ItemLocationPairing(&DodongosCavern_GS_BackRoom,      []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&DodongosCavern_Lobby, []{return true;})
  });

  Exit JabuJabusBelly_Beginning = Exit("Jabu Jabus Belly Beginning", "Jabu Jabus Belly", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&ZF_Main,             []{return true;}),
                  ExitPairing::Both(&JabuJabusBelly_Main, []{return CanUseProjectile;})
  });

  Exit JabuJabusBelly_Main = Exit("Jabu Jabus Belly Main", "Jabu Jabus Belly", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPot, []{return true;}),
                }, {
                  //Locations
                  ItemLocationPairing(&JabuJabusBelly_BoomerangChest,        []{return true;}),
                  ItemLocationPairing(&JabuJabusBelly_GS_WaterSwitchRoom,    []{return true;}),
                  ItemLocationPairing(&JabuJabusBelly_GS_LobbyBasementLower, []{return HookshotOrBoomerang;}),
                  ItemLocationPairing(&JabuJabusBelly_GS_LobbyBasementUpper, []{return HookshotOrBoomerang;}),
                  ItemLocationPairing(&JabuJabusBelly_DekuScrub,             []{return CanDive || IsChild || LogicJabuScrubJumpDive || CanUse(CanUseItem::Iron_Boots);}),
                }, {
                  //Exits
                  ExitPairing::Both(&JabuJabusBelly_Beginning, []{return true;}),
                  ExitPairing::Both(&JabuJabusBelly_Depths,    []{return CanUse(CanUseItem::Boomerang);}),
                  ExitPairing::Both(&JabuJabusBelly_BossArea,  []{return LogicJabuBossGSAdult && CanUse(CanUseItem::Hover_Boots);}),
  });

  Exit JabuJabusBelly_Depths = Exit("Jabu Jabus Belly Depths", "Jabu Jabus Belly", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&JabuJabusBelly_MapChest,     []{return true;}),
                  ItemLocationPairing(&JabuJabusBelly_CompassChest, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&JabuJabusBelly_Main,     []{return true;}),
                  ExitPairing::Both(&JabuJabusBelly_BossArea, []{return Sticks || KokiriSword;}),
  });

  Exit JabuJabusBelly_BossArea = Exit("Jabu Jabus Belly Boss Area", "Jabu Jabus Belly", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&NutPot,              []{return true;}),
                  EventPairing(&JabuJabusBellyClear, []{return JabuJabusBellyClear || CanUse(CanUseItem::Boomerang);}),
                }, {
                  //Locations
                  ItemLocationPairing(&JabuJabusBelly_BarinadeHeart, []{return CanUse(CanUseItem::Boomerang);}),
                  ItemLocationPairing(&Barinade,                     []{return CanUse(CanUseItem::Boomerang);}),
                  ItemLocationPairing(&JabuJabusBelly_GS_NearBoss,   []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&JabuJabusBelly_Main, []{return true;}),
  });

  Exit ForestTemple_Lobby = Exit("Forest Temple Lobby", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&ForestTemple_FirstRoomChest,    []{return true;}),
                  ItemLocationPairing(&ForestTemple_FirstStalfosChest, []{return IsAdult || KokiriSword;}),
                  ItemLocationPairing(&ForestTemple_GS_FirstRoom,      []{return CanUse(CanUseItem::Dins_Fire) || CanUseProjectile;}),
                  ItemLocationPairing(&ForestTemple_GS_Lobby,          []{return HookshotOrBoomerang;}),
                }, {
                  //Exits
                  ExitPairing::Both(&SFM_Main,                   []{return true;}),
                  ExitPairing::Both(&ForestTemple_NWOutdoors,    []{return CanPlay(SongOfTime) || IsChild;}),
                  ExitPairing::Both(&ForestTemple_NEOutdoors,    []{return CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Slingshot);}),
                  ExitPairing::Both(&ForestTemple_BlockPushRoom, []{return SmallKeys(ForestTempleKeys, 1);}),
                  ExitPairing::Both(&ForestTemple_BossRegion,    []{return ForestTempleJoAndBeth && ForestTempleAmyAndMeg;})
  });

  Exit ForestTemple_NWOutdoors = Exit("Forest Temple NW Outdoors", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&DekuBabaSticks, []{return DekuBabaSticks || (IsAdult || KokiriSword || Boomerang);}),
                  EventPairing(&DekuBabaNuts,   []{return DekuBabaNuts   || (IsAdult || KokiriSword || Slingshot || Sticks || HasExplosives || CanUse(CanUseItem::Dins_Fire));}),
                }, {
                  //Locations
                  ItemLocationPairing(&ForestTemple_GS_LevelIslandCourtyard, []{return CanUse(CanUseItem::Longshot) || ((ForestTemple_OutsideUpperLedge.dayAdult || ForestTemple_OutsideUpperLedge.nightAdult) && CanUse(CanUseItem::Hookshot));}),
                }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_OutdoorsHighBalconies, []{return IsAdult || (HasExplosives || ((CanUse(CanUseItem::Boomerang) || Nuts || DekuShield) && (Sticks || KokiriSword || CanUse(CanUseItem::Slingshot))));})
  });

  Exit ForestTemple_NEOutdoors = Exit("Forest Temple NE Outdoors", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&DekuBabaSticks, []{return DekuBabaSticks || (IsAdult || KokiriSword || Boomerang);}),
                  EventPairing(&DekuBabaNuts,   []{return DekuBabaNuts   || (IsAdult || KokiriSword || Slingshot || Sticks || HasExplosives || CanUse(CanUseItem::Dins_Fire));}),
                }, {
                  //Locations
                  ItemLocationPairing(&ForestTemple_RaisedIslandCourtyardChest, []{return CanUse(CanUseItem::Hookshot);}),
                  ItemLocationPairing(&ForestTemple_GS_RaisedIslandCourtyard,   []{return CanUse(CanUseItem::Hookshot) || (LogicForestOutdoorEastGS && CanUse(CanUseItem::Boomerang));}),
                }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_OutdoorsHighBalconies, []{return CanUse(CanUseItem::Longshot);}),
                  ExitPairing::Both(&ForestTemple_NWOutdoors,            []{return CanUse(CanUseItem::Iron_Boots) || ProgressiveScale >= 2;}),
                  ExitPairing::Both(&ForestTemple_Lobby,                 []{return true;})
  });

  Exit ForestTemple_OutdoorsHighBalconies = Exit("Forest Temple Outdoors High Balconies", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&ForestTemple_WellChest, []{return true;}),
                  ItemLocationPairing(&ForestTemple_MapChest,  []{return true;})
                }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_NWOutdoors,  []{return true;}),
                  ExitPairing::Both(&ForestTemple_NEOutdoors,  []{return true;}),
                  ExitPairing::Both(&ForestTemple_FallingRoom, []{return LogicForestDoorFrame && CanUse(CanUseItem::Hover_Boots) && CanUse(CanUseItem::Scarecrow);})
  });

  Exit ForestTemple_FallingRoom = Exit("Forest Temple Falling Room", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&ForestTempleAmyAndMeg, []{return ForestTempleAmyAndMeg || CanUse(CanUseItem::Bow);}),
                }, {
                  //Locations
                  ItemLocationPairing(&ForestTemple_FallingCeilingRoomChest, []{return true;})
                }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_NEOutdoors, []{return true;})
  });

  Exit ForestTemple_BlockPushRoom = Exit("Forest Temple Block Push Room", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&ForestTemple_EyeSwitchChest, []{return GoronBracelet && (CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Slingshot));})
                }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_OutsideUpperLedge, []{return CanUse(CanUseItem::Hover_Boots) || (LogicForestOutsideBackdoor && IsAdult && GoronBracelet);}),
                  ExitPairing::Both(&ForestTemple_BowRegion,         []{return GoronBracelet && SmallKeys(ForestTempleKeys, 3) && IsAdult;}),
                  ExitPairing::Both(&ForestTemple_StraightenedHall,  []{return GoronBracelet && SmallKeys(ForestTempleKeys, 2) && CanUse(CanUseItem::Bow) && IsAdult;})
  });

  Exit ForestTemple_StraightenedHall = Exit("Forest Temple Straightened Hall", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&ForestTemple_BossKeyChest, []{return true;})
                }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_OutsideUpperLedge, []{return true;})
  });

  Exit ForestTemple_OutsideUpperLedge = Exit("Forest Temple Outside Upper Ledge", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&ForestTemple_FloormasterChest, []{return true;})
                }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_NWOutdoors, []{return true;})
  });

  Exit ForestTemple_BowRegion = Exit("Forest Temple Bow Region", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&ForestTempleJoAndBeth, []{return ForestTempleJoAndBeth || CanUse(CanUseItem::Bow);}),
                }, {
                  //Locations
                  ItemLocationPairing(&ForestTemple_BowChest,     []{return true;}),
                  ItemLocationPairing(&ForestTemple_RedPoeChest,  []{return CanUse(CanUseItem::Bow);}),
                  ItemLocationPairing(&ForestTemple_BluePoeChest, []{return CanUse(CanUseItem::Bow);})
                }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_FallingRoom, []{return SmallKeys(ForestTempleKeys, 5) && (Bow || CanUse(CanUseItem::Dins_Fire));})
  });

  Exit ForestTemple_BossRegion = Exit("Forest Temple Boss Region", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&ForestTempleClear, []{return ForestTempleClear || (BossKeyForestTemple);}),
  }, {
                  //Locations
                  ItemLocationPairing(&ForestTemple_BasementChest,     []{return true;}),
                  ItemLocationPairing(&ForestTemple_PhantomGanonHeart, []{return BossKeyForestTemple;}),
                  ItemLocationPairing(&PhantomGanon,                   []{return BossKeyForestTemple;}),
                  ItemLocationPairing(&ForestTemple_GS_Basement,       []{return HookshotOrBoomerang;}),
  }, {});

  //Fire Temple logic currently assumes that the lowest locked door is unlocked from the start
  Exit FireTemple_Lower = Exit("Fire Temple Lower", "Fire Temple", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPot,        []{return FairyPot || ((CanUse(CanUseItem::Hover_Boots) || CanUse(CanUseItem::Hookshot)) && (LogicFewerTunicRequirements || CanUse(CanUseItem::Goron_Tunic)));}),
                  EventPairing(&FireTempleClear, []{return FireTempleClear || (CanUse(CanUseItem::Goron_Tunic) && CanUse(CanUseItem::Hammer) && BossKeyFireTemple &&
                                                                                (LogicFireBossDoorJump || HoverBoots ||
                                                                                  (FireTemple_Upper.Adult() && (CanPlay(SongOfTime) || HasExplosives))));})
                }, {
                  //Locations
                  ItemLocationPairing(&FireTemple_NearBossChest,    []{return LogicFewerTunicRequirements || CanUse(CanUseItem::Goron_Tunic);}),
                  ItemLocationPairing(&FireTemple_FlareDancerChest, []{return /*SmallKeys(FireTempleKeys, 8) &&*/ CanUse(CanUseItem::Hammer);}),
                  ItemLocationPairing(&FireTemple_BossKeyChest,     []{return /*SmallKeys(FireTempleKeys, 8) &&*/ CanUse(CanUseItem::Hammer);}),
                  ItemLocationPairing(&FireTemple_VolvagiaHeart,    []{return CanUse(CanUseItem::Goron_Tunic) && CanUse(CanUseItem::Hammer) && BossKeyFireTemple &&
                                                                                (LogicFireBossDoorJump || HoverBoots ||
                                                                                  (FireTemple_Upper.Adult() && (CanPlay(SongOfTime) || HasExplosives)));}),
                  ItemLocationPairing(&Volvagia,                    []{return CanUse(CanUseItem::Goron_Tunic) && CanUse(CanUseItem::Hammer) && BossKeyFireTemple &&
                                                                                (LogicFireBossDoorJump || HoverBoots ||
                                                                                  (FireTemple_Upper.Adult() && (CanPlay(SongOfTime) || HasExplosives)));}),
                  ItemLocationPairing(&FireTemple_GS_BossKeyLoop,   []{return /*SmallKeys(FireTempleKeys, 8) &&*/ CanUse(CanUseItem::Hammer);}),
                }, {
                  //Exits
                  ExitPairing::Both(&FireTemple_Entrance,    []{return true;}),
                  ExitPairing::Both(&FireTemple_BigLavaRoom, []{return SmallKeys(FireTempleKeys, 1) && (LogicFewerTunicRequirements || CanUse(CanUseItem::Goron_Tunic));}),
  });

  Exit FireTemple_BigLavaRoom = Exit("Fire Temple Big Lava Room", "Fire Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&FireTemple_BigLavaRoomLowerOpenDoorChest, []{return true;}),
                  ItemLocationPairing(&FireTemple_BigLavaRoomBlockedDoorChest,   []{return IsAdult && HasExplosives;}),
                  ItemLocationPairing(&FireTemple_GS_SongOfTimeRoom,             []{return IsAdult && (CanPlay(SongOfTime) || LogicFireSongOfTime);}),
                }, {
                  //Exits
                  ExitPairing::Both(&FireTemple_Lower,  []{return true;}),
                  ExitPairing::Both(&FireTemple_Middle, []{return CanUse(CanUseItem::Goron_Tunic) && SmallKeys(FireTempleKeys, 3) && (GoronBracelet || LogicFireStrength) && (HasExplosives || Bow || Hookshot);}),
  });

  Exit FireTemple_Middle = Exit("Fire Temple Middle", "Fire Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&FireTemple_BoulderMazeLowerChest,    []{return true;}),
                  ItemLocationPairing(&FireTemple_BoulderMazeUpperChest,    []{return SmallKeys(FireTempleKeys, 5);}),
                  ItemLocationPairing(&FireTemple_BoulderMazeSideRoomChest, []{return true;}),
                  ItemLocationPairing(&FireTemple_BoulderMazeShortcutChest, []{return SmallKeys(FireTempleKeys, 5) && HasExplosives;}),
                  ItemLocationPairing(&FireTemple_ScarecrowChest,           []{return SmallKeys(FireTempleKeys, 5) && (CanUse(CanUseItem::Scarecrow) || (LogicFireScarecrow && CanUse(CanUseItem::Longshot)));}),
                  ItemLocationPairing(&FireTemple_MapChest,                 []{return SmallKeys(FireTempleKeys, 5) || (SmallKeys(FireTempleKeys, 4) && CanUse(CanUseItem::Bow));}),
                  ItemLocationPairing(&FireTemple_CompassChest,             []{return SmallKeys(FireTempleKeys, 6);}),
                  ItemLocationPairing(&FireTemple_GS_BoulderMaze,           []{return SmallKeys(FireTempleKeys, 4) && HasExplosives;}),
                  ItemLocationPairing(&FireTemple_GS_ScarecrowClimb,        []{return SmallKeys(FireTempleKeys, 5) && (CanUse(CanUseItem::Scarecrow) || (LogicFireScarecrow && CanUse(CanUseItem::Longshot)));}),
                  ItemLocationPairing(&FireTemple_GS_ScarecrowTop,          []{return SmallKeys(FireTempleKeys, 5) && (CanUse(CanUseItem::Scarecrow) || (LogicFireScarecrow && CanUse(CanUseItem::Longshot)));}),
                }, {
                  //Exits
                  ExitPairing::Both(&FireTemple_Upper, []{return SmallKeys(FireTempleKeys, 7) || (SmallKeys(FireTempleKeys, 6) && ((CanUse(CanUseItem::Hover_Boots) && CanUse(CanUseItem::Hammer)) || LogicFireFlameMaze));})
  });

  Exit FireTemple_Upper = Exit("Fire Temple Upper", "Fire Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&FireTemple_HighestGoronChest,  []{return CanUse(CanUseItem::Hammer) && CanPlay(SongOfTime);}),
                  ItemLocationPairing(&FireTemple_MegatonHammerChest, []{return HasExplosives;}),
  }, {});

  //Water Temple logic currently assumes that the locked door leading to the upper water raising location is unlocked from the start
  Exit WaterTemple_Lobby = Exit("Water Temple Lobby", "Water Temple", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&ChildWaterTemple, []{return IsChild;}),
                  EventPairing(&RaiseWaterLevel,  []{return (IsAdult && ((Hookshot && (LogicWaterTempleUpperBoost && Bombs && (CanUse(CanUseItem::Nayrus_Love) || DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO)))) || HoverBoots || Bow)) || (HasFireSourceWithTorch && CanUseProjectile);}),
                }, {}, {
                  //Exits
                  ExitPairing::Both(&LH_Main,                       []{return true;}),
                  ExitPairing::Both(&WaterTemple_HighestWaterLevel, []{return RaiseWaterLevel;}),
                  ExitPairing::Both(&WaterTemple_Dive,              []{return (CanUse(CanUseItem::Zora_Tunic) || LogicFewerTunicRequirements) && ((LogicWaterTempleTorchLongshot && CanUse(CanUseItem::Longshot)) || CanUse(CanUseItem::Iron_Boots));}),
  });

  Exit WaterTemple_HighestWaterLevel = Exit("Water Temple Highest Water Level", "Water Temple", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPot,         []{return FairyPot         || CanUse(CanUseItem::Longshot);}),
                  EventPairing(&WaterTempleClear, []{return WaterTempleClear || (BossKeyWaterTemple && CanUse(CanUseItem::Longshot));})
                }, {
                  //Locations
                  ItemLocationPairing(&Morpha,                  []{return BossKeyWaterTemple && CanUse(CanUseItem::Longshot);}),
                  ItemLocationPairing(&WaterTemple_MorphaHeart, []{return BossKeyWaterTemple && CanUse(CanUseItem::Longshot);}),
                }, {
                  //Exits
                  ExitPairing::Both(&WaterTemple_FallingPlatformRoom, []{return SmallKeys(WaterTempleKeys, 4);}),

  });

  Exit WaterTemple_Dive = Exit("Water Temple Dive", "Water Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&WaterTemple_MapChest,              []{return RaiseWaterLevel;}),
                  ItemLocationPairing(&WaterTemple_CompassChest,          []{return (CanPlay(ZeldasLullaby) || IronBoots) && CanUse(CanUseItem::Hookshot);}),
                  ItemLocationPairing(&WaterTemple_TorchesChest,          []{return (Bow || CanUse(CanUseItem::Dins_Fire) || (ChildWaterTemple && Sticks && KokiriSword && MagicMeter)) && CanPlay(ZeldasLullaby);}),
                  ItemLocationPairing(&WaterTemple_CentralBowTargetChest, []{return GoronBracelet && CanPlay(ZeldasLullaby) && ((Bow && (LogicWaterCentralBow || HoverBoots || CanUse(CanUseItem::Longshot))));}),
                  ItemLocationPairing(&WaterTemple_GS_BehindGate,         []{return (CanUse(CanUseItem::Hookshot) || CanUse(CanUseItem::Hover_Boots)) && (HasExplosives && CanPlay(ZeldasLullaby)) && (CanUse(CanUseItem::Iron_Boots) || CanDive);}),
                  ItemLocationPairing(&WaterTemple_GS_CentralPillar,      []{return CanPlay(ZeldasLullaby) &&
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

  Exit WaterTemple_NorthBasement = Exit("Water Temple North Basement", "Water Temple", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPot, []{return FairyPot || (SmallKeys(WaterTempleKeys, 5) && (LogicWaterBKJumpDive || CanUse(CanUseItem::Iron_Boots)) && (LogicWaterNorthBasementLedgeJump || (HasExplosives && GoronBracelet) || HoverBoots));}),
                }, {
                  //Locations
                  ItemLocationPairing(&WaterTemple_BossKeyChest,        []{return SmallKeys(WaterTempleKeys, 5) && (LogicWaterBKJumpDive || CanUse(CanUseItem::Iron_Boots)) && (LogicWaterNorthBasementLedgeJump || (HasExplosives && GoronBracelet) || HoverBoots);}),
                  ItemLocationPairing(&WaterTemple_GS_NearBossKeyChest, []{return true;}),
  }, {});

  Exit WaterTemple_CrackedWall = Exit("Water Temple Cracked Wall", "Water Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&WaterTemple_CrackedWallChest, []{return HasExplosives;}),
  }, {});

  Exit WaterTemple_DragonStatue = Exit("Water Temple Dragon Statue", "Water Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&WaterTemple_DragonChest, []{return true;}),
  }, {});

  Exit WaterTemple_MiddleWaterLevel = Exit("Water Temple Middle Water Level", "Water Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&WaterTemple_CentralPillarChest, []{return CanUse(CanUseItem::Zora_Tunic) && CanUse(CanUseItem::Hookshot) && ((SmallKeys(WaterTempleKeys, 5) || CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Dins_Fire)));}),
                }, {
                  //Exits
                  ExitPairing::Both(&WaterTemple_CrackedWall, []{return true;}),
  });

  Exit WaterTemple_FallingPlatformRoom = Exit("Water Temple Falling Platform Room", "Water Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&WaterTemple_GS_FallingPlatformRoom, []{return CanUse(CanUseItem::Longshot) || (LogicWaterFallingPlatformGS && CanUse(CanUseItem::Hookshot));}),
                }, {
                  //Exits
                  ExitPairing::Both(&WaterTemple_DarkLinkRegion, []{return SmallKeys(WaterTempleKeys, 5) && CanUse(CanUseItem::Hookshot);}),
  });

  Exit WaterTemple_DarkLinkRegion = Exit("Water Temple Dark Link Region", "Water Temple", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPot, []{return FairyPot || (SmallKeys(WaterTempleKeys, 5) && CanPlay(SongOfTime));}),
                }, {
                  //Locations
                  ItemLocationPairing(&WaterTemple_LongshotChest,          []{return SmallKeys(WaterTempleKeys, 5);}),
                  ItemLocationPairing(&WaterTemple_RiverChest,             []{return SmallKeys(WaterTempleKeys, 5) && CanPlay(SongOfTime) && Bow;}),
                  ItemLocationPairing(&WaterTemple_GS_River,               []{return CanPlay(SongOfTime) && SmallKeys(WaterTempleKeys, 5) && (IronBoots || (LogicWaterRiverGS && CanUse(CanUseItem::Longshot) && (Bow || HasBombchus)));}),
                }, {
                  //Exits
                  ExitPairing::Both(&WaterTemple_DragonStatue, []{return (CanUse(CanUseItem::Zora_Tunic) || LogicFewerTunicRequirements) &&
                                                                         CanPlay(SongOfTime) && Bow &&
                                                                         (IronBoots || LogicWaterDragonJumpDive || LogicWaterDragonAdult);}),
  });

  Exit SpiritTemple_Lobby = Exit("Spirit Temple Lobby", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&Colossus_Main,           []{return true;}),
                  ExitPairing::Both(&SpiritTemple_Child,      []{return IsChild;}),
                  ExitPairing::Both(&SpiritTemple_EarlyAdult, []{return CanUse(CanUseItem::Silver_Gauntlets);}),
  });

  Exit SpiritTemple_Child = Exit("Child Spirit Temple", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&NutCrate, []{return true;}),
                }, {
                  //Locations
                  ItemLocationPairing(&SpiritTemple_ChildBridgeChest,       []{return (Boomerang || Slingshot || (HasExplosives && LogicSpiritChildBombchu)) && (Sticks || HasExplosives || ((Nuts || Boomerang) && (KokiriSword || Slingshot)));}),
                  ItemLocationPairing(&SpiritTemple_ChildEarlyTorchesChest, []{return (Boomerang || Slingshot || (HasExplosives && LogicSpiritChildBombchu)) && (Sticks || HasExplosives || ((Nuts || Boomerang) && (KokiriSword || Slingshot))) && (Sticks || CanUse(CanUseItem::Dins_Fire));}),
                  ItemLocationPairing(&SpiritTemple_GS_MetalFence,          []{return (Boomerang || Slingshot || (HasExplosives && LogicSpiritChildBombchu)) && (Sticks || HasExplosives || ((Nuts || Boomerang) && (KokiriSword || Slingshot)));}),
                }, {
                  //Exits
                  ExitPairing::Both(&SpiritTemple_ChildClimb, []{return SmallKeys(SpiritTempleKeys, 1);}),
  });

  Exit SpiritTemple_ChildClimb = Exit("Child Spirit Temple Climb", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&SpiritTemple_ChildClimbNorthChest, []{return HasProjectile(HasProjectileAge::Both) || ((SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && !ShuffleDungeonEntrances)) && CanUse(CanUseItem::Silver_Gauntlets) && HasProjectile(HasProjectileAge::Adult)) || (SmallKeys(SpiritTempleKeys, 5) && IsChild && HasProjectile(HasProjectileAge::Child));}),
                  ItemLocationPairing(&SpiritTemple_ChildClimbEastChest,  []{return HasProjectile(HasProjectileAge::Both) || ((SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && !ShuffleDungeonEntrances)) && CanUse(CanUseItem::Silver_Gauntlets) && HasProjectile(HasProjectileAge::Adult)) || (SmallKeys(SpiritTempleKeys, 5) && IsChild && HasProjectile(HasProjectileAge::Child));}),
                  ItemLocationPairing(&SpiritTemple_GS_SunOnFloorRoom,    []{return HasProjectile(HasProjectileAge::Both) || CanUse(CanUseItem::Dins_Fire) ||
                                                                                      ((DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO) || Fairy || CanUse(CanUseItem::Nayrus_Love)) && (Sticks || KokiriSword || HasProjectile(HasProjectileAge::Child))) ||
                                                                                        (IsChild && SmallKeys(SpiritTempleKeys, 5) && HasProjectile(HasProjectileAge::Child)) ||
                                                                                          ((SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && !ShuffleDungeonEntrances)) && CanUse(CanUseItem::Silver_Gauntlets) && (HasProjectile(HasProjectileAge::Adult) || DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO) || Fairy || CanUse(CanUseItem::Nayrus_Love)));}),
                }, {
                  //Exits
                  ExitPairing::Both(&SpiritTemple_CentralChamber, []{return HasExplosives;}),
  });

  Exit SpiritTemple_EarlyAdult = Exit("Early Adult Spirit Temple", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&SpiritTemple_CompassChest,          []{return CanUse(CanUseItem::Hookshot) && CanPlay(ZeldasLullaby);}),
                  ItemLocationPairing(&SpiritTemple_EarlyAdultRightChest,  []{return Bow || Hookshot || HasBombchus || (Bombs && LogicSpiritLowerAdultSwitch);}),
                  ItemLocationPairing(&SpiritTemple_FirstMirrorLeftChest,  []{return SmallKeys(SpiritTempleKeys, 3);}),
                  ItemLocationPairing(&SpiritTemple_FirstMirrorRightChest, []{return SmallKeys(SpiritTempleKeys, 3);}),
                  ItemLocationPairing(&SpiritTemple_GS_BoulderRoom,        []{return CanPlay(SongOfTime) && (Bow || Hookshot || HasBombchus || (Bombs && LogicSpiritLowerAdultSwitch));}),
                }, {
                  //Exits
                  ExitPairing::Both(&SpiritTemple_CentralChamber, []{return SmallKeys(SpiritTempleKeys, 1);}),
  });

  Exit SpiritTemple_CentralChamber = Exit("Spirit Temple Central Chamber", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&SpiritTemple_MapChest,                 []{return ((HasExplosives || SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && !ShuffleDungeonEntrances)) && (CanUse(CanUseItem::Dins_Fire) || (((MagicMeter && FireArrows) || LogicSpiritMapChest) && Bow && Sticks))) || (SmallKeys(SpiritTempleKeys, 5) && HasExplosives && CanUse(CanUseItem::Sticks)) || (SmallKeys(SpiritTempleKeys, 3) && (CanUse(CanUseItem::Fire_Arrows) || (LogicSpiritMapChest && Bow)) && CanUse(CanUseItem::Silver_Gauntlets));}),
                  ItemLocationPairing(&SpiritTemple_SunBlockRoomChest,        []{return ((HasExplosives || SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && !ShuffleDungeonEntrances)) && (CanUse(CanUseItem::Dins_Fire) || (((MagicMeter && FireArrows) || LogicSpiritMapChest) && Bow && Sticks))) || (SmallKeys(SpiritTempleKeys, 5) && HasExplosives && CanUse(CanUseItem::Sticks)) || (SmallKeys(SpiritTempleKeys, 3) && (CanUse(CanUseItem::Fire_Arrows) || (LogicSpiritMapChest && Bow)) && CanUse(CanUseItem::Silver_Gauntlets));}),
                  ItemLocationPairing(&SpiritTemple_StatueRoomHandChest,      []{return SmallKeys(SpiritTempleKeys, 3) && CanUse(CanUseItem::Silver_Gauntlets) && CanPlay(ZeldasLullaby);}),
                  ItemLocationPairing(&SpiritTemple_StatueRoomNortheastChest, []{return SmallKeys(SpiritTempleKeys, 3) && CanUse(CanUseItem::Silver_Gauntlets) && CanPlay(ZeldasLullaby) && (Hookshot || HoverBoots);}),
                  ItemLocationPairing(&SpiritTemple_GS_HallAfterSunBlockRoom, []{return (HasExplosives && Boomerang && Hookshot) || (CanUse(CanUseItem::Boomerang) && SmallKeys(SpiritTempleKeys, 5) && HasExplosives) || (Hookshot && CanUse(CanUseItem::Silver_Gauntlets) && (SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && Boomerang && BombchusInLogic && !ShuffleDungeonEntrances)));}),
                  ItemLocationPairing(&SpiritTemple_GS_Lobby,                 []{return ((HasExplosives || SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && !ShuffleDungeonEntrances)) && LogicSpiritLobbyGS && Boomerang && (Hookshot || HoverBoots)) || (LogicSpiritLobbyGS && SmallKeys(SpiritTempleKeys, 5) && HasExplosives && CanUse(CanUseItem::Boomerang)) || (SmallKeys(SpiritTempleKeys, 3) && CanUse(CanUseItem::Silver_Gauntlets) && (Hookshot || HoverBoots));}),
                }, {
                  //Exits
                  ExitPairing::Both(&SpiritTemple_OutdoorHands,            []{return true;}),
                  ExitPairing::Both(&SpiritTemple_BeyondCentralLockedDoor, []{return SmallKeys(SpiritTempleKeys, 4) && CanUse(CanUseItem::Silver_Gauntlets);}),
                  ExitPairing::Both(&SpiritTemple_ChildClimb,              []{return true;}),
  });

  Exit SpiritTemple_OutdoorHands = Exit("Spirit Temple Outdoor Hands", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&SpiritTemple_SilverGauntletsChest, []{return (SmallKeys(SpiritTempleKeys, 3) && Longshot && HasExplosives) || SmallKeys(SpiritTempleKeys, 5);}),
                  ItemLocationPairing(&SpiritTemple_MirrorShieldChest,    []{return SmallKeys(SpiritTempleKeys, 4) && CanUse(CanUseItem::Silver_Gauntlets) && HasExplosives;}),
                }, {
                  //Exits
                  ExitPairing::Both(&Colossus_Main, []{return (IsChild && SmallKeys(SpiritTempleKeys, 5)) || (CanUse(CanUseItem::Silver_Gauntlets) && ((SmallKeys(SpiritTempleKeys, 3) && HasExplosives) || SmallKeys(SpiritTempleKeys, 5)));}),
  });

  Exit SpiritTemple_BeyondCentralLockedDoor = Exit("Spirit Temple Beyond Central Locked Door", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&SpiritTemple_NearFourArmosChest,         []{return MirrorShield && HasExplosives;}),
                  ItemLocationPairing(&SpiritTemple_HallwayLeftInvisibleChest,  []{return (LogicLensSpirit || CanUse(CanUseItem::Lens_of_Truth)) && HasExplosives;}),
                  ItemLocationPairing(&SpiritTemple_HallwayRightInvisibleChest, []{return (LogicLensSpirit || CanUse(CanUseItem::Lens_of_Truth)) && HasExplosives;}),
                }, {
                  //Exits
                  ExitPairing::Both(&SpiritTemple_BeyondFinalLockedDoor, []{return SmallKeys(SpiritTempleKeys, 5) && (LogicSpiritWall || CanUse(CanUseItem::Longshot) || HasBombchus || ((Bombs || Nuts || CanUse(CanUseItem::Dins_Fire)) && (Bow || CanUse(CanUseItem::Hookshot) || Hammer)));}),
  });

  Exit SpiritTemple_BeyondFinalLockedDoor = Exit("Spirit Temple Beyond Final Locked Door", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&SpiritTempleClear, []{return SpiritTempleClear || (MirrorShield && HasExplosives && Hookshot && BossKeySpiritTemple);}),
  }, {
                  //Locations
                  ItemLocationPairing(&SpiritTemple_BossKeyChest,  []{return CanPlay(ZeldasLullaby) && Bow && Hookshot;}),
                  ItemLocationPairing(&SpiritTemple_TopmostChest,  []{return MirrorShield;}),
                  ItemLocationPairing(&SpiritTemple_TwinrovaHeart, []{return MirrorShield && HasExplosives && Hookshot && BossKeySpiritTemple;}),
                  ItemLocationPairing(&Twinrova,                   []{return MirrorShield && HasExplosives && Hookshot && BossKeySpiritTemple;}),
  }, {});

  Exit ShadowTemple_Entryway = Exit("Shadow Temple Entryway", "Shadow Temple", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&GY_WarpPadRegion,       []{return true;}),
                  ExitPairing::Both(&ShadowTemple_Beginning, []{return (LogicLensShadow || CanUse(CanUseItem::Lens_of_Truth)) && (CanUse(CanUseItem::Hover_Boots) || CanUse(CanUseItem::Hookshot));}),
  });

  Exit ShadowTemple_Beginning = Exit("Shadow Temple Beginning", "Shadow Temple", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&NutPot, []{return true;}),
                }, {
                  //Locations
                  ItemLocationPairing(&ShadowTemple_MapChest,        []{return true;}),
                  ItemLocationPairing(&ShadowTemple_HoverBootsChest, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&ShadowTemple_Entryway,    []{return true;}),
                  ExitPairing::Both(&ShadowTemple_FirstBeamos, []{return HoverBoots;}),
  });

  Exit ShadowTemple_FirstBeamos = Exit("Shadow Temple First Beamos", "Shadow Temple", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPot, []{return true;}), //This fairy pot is only on 3DS
                }, {
                  //Locations
                  ItemLocationPairing(&ShadowTemple_CompassChest,          []{return true;}),
                  ItemLocationPairing(&ShadowTemple_EarlySilverRupeeChest, []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&ShadowTemple_HugePit, []{return HasExplosives && SmallKeys(ShadowTempleKeys, 1);})
  });

  Exit ShadowTemple_HugePit = Exit("Shadow Temple Huge Pit", "Shadow Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&ShadowTemple_InvisibleBladesVisibleChest,   []{return true;}),
                  ItemLocationPairing(&ShadowTemple_InvisibleBladesInvisibleChest, []{return true;}),
                  ItemLocationPairing(&ShadowTemple_FallingSpikesLowerChest,       []{return true;}),
                  ItemLocationPairing(&ShadowTemple_FallingSpikesUpperChest,       []{return LogicShadowUmbrella || GoronBracelet;}),
                  ItemLocationPairing(&ShadowTemple_FallingSpikesSwitchChest,      []{return LogicShadowUmbrella || GoronBracelet;}),
                  ItemLocationPairing(&ShadowTemple_InvisibleSpikesChest,          []{return SmallKeys(ShadowTempleKeys, 2) && (LogicLensShadowBack || CanUse(CanUseItem::Lens_of_Truth));}),
                  ItemLocationPairing(&ShadowTemple_FreestandingKey,               []{return SmallKeys(ShadowTempleKeys, 2) && (LogicLensShadowBack || CanUse(CanUseItem::Lens_of_Truth)) && Hookshot && (Bombs || GoronBracelet || (LogicShadowFreestandingKey && HasBombchus));}),
                  ItemLocationPairing(&ShadowTemple_GS_LikeLikeRoom,               []{return true;}),
                  ItemLocationPairing(&ShadowTemple_GS_FallingSpikesRoom,          []{return Hookshot;}),
                  ItemLocationPairing(&ShadowTemple_GS_SingleGiantPot,             []{return SmallKeys(ShadowTempleKeys, 2) && (LogicLensShadowBack || CanUse(CanUseItem::Lens_of_Truth)) && Hookshot;}),
                }, {
                  //Exits
                  ExitPairing::Both(&ShadowTemple_WindTunnel, []{return (LogicLensShadowBack || CanUse(CanUseItem::Lens_of_Truth)) && Hookshot && SmallKeys(ShadowTempleKeys, 3);}),
  });

  Exit ShadowTemple_WindTunnel = Exit("Shadow Temple Wind Tunnel", "Shadow Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&ShadowTemple_WindHintChest,        []{return true;}),
                  ItemLocationPairing(&ShadowTemple_AfterWindEnemyChest,  []{return true;}),
                  ItemLocationPairing(&ShadowTemple_AfterWindHiddenChest, []{return true;}),
                  ItemLocationPairing(&ShadowTemple_GS_NearShip,          []{return CanUse(CanUseItem::Longshot) && SmallKeys(ShadowTempleKeys, 4);}),
                }, {
                  //Exits
                  ExitPairing::Both(&ShadowTemple_BeyondBoat, []{return CanPlay(ZeldasLullaby) && SmallKeys(ShadowTempleKeys, 4);}),
  });

  Exit ShadowTemple_BeyondBoat = Exit("Shadow Temple Beyond Boat", "Shadow Temple", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&ShadowTempleClear, []{return ShadowTempleClear || (SmallKeys(ShadowTempleKeys, 5) && BossKeyShadowTemple && (Bow || CanUse(CanUseItem::Distant_Scarecrow) || (LogicShadowStatue && HasBombchus)));}),
  }, {
                  //Locations
                  ItemLocationPairing(&ShadowTemple_SpikeWallsLeftChest,       []{return CanUse(CanUseItem::Dins_Fire);}),
                  ItemLocationPairing(&ShadowTemple_BossKeyChest,              []{return CanUse(CanUseItem::Dins_Fire);}),
                  ItemLocationPairing(&ShadowTemple_InvisibleFloormasterChest, []{return true;}),
                  ItemLocationPairing(&ShadowTemple_BongoBongoHeart,           []{return SmallKeys(ShadowTempleKeys, 5) && BossKeyShadowTemple && (Bow || CanUse(CanUseItem::Distant_Scarecrow) || (LogicShadowStatue && HasBombchus));}),
                  ItemLocationPairing(&BongoBongo,                             []{return SmallKeys(ShadowTempleKeys, 5) && BossKeyShadowTemple && (Bow || CanUse(CanUseItem::Distant_Scarecrow) || (LogicShadowStatue && HasBombchus));}),
                  ItemLocationPairing(&ShadowTemple_GS_TripleGiantPot,         []{return true;}),
  }, {});

  Exit BottomOfTheWell = Exit("Bottom of the Well", "Bottom of the Well", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&Kak_Main,                 []{return true;}),
                  ExitPairing::Both(&BottomOfTheWell_MainArea, []{return IsChild && (CanChildAttack || Nuts);}),
  });

  Exit BottomOfTheWell_MainArea = Exit("Bottom of the Well Main Area", "Bottom of the Well", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&StickPot, []{return true;}),
                  EventPairing(&NutPot,   []{return true;}),
                }, {
                  //Locations
                  ItemLocationPairing(&BottomOfTheWell_FrontLeftFakeWallChest,   []{return LogicLensBotw || CanUse(CanUseItem::Lens_of_Truth);}),
                  ItemLocationPairing(&BottomOfTheWell_FrontCenterBombableChest, []{return HasExplosives;}),
                  ItemLocationPairing(&BottomOfTheWell_RightBottomFakeWallChest, []{return LogicLensBotw || CanUse(CanUseItem::Lens_of_Truth);}),
                  ItemLocationPairing(&BottomOfTheWell_CompassChest,             []{return LogicLensBotw || CanUse(CanUseItem::Lens_of_Truth);}),
                  ItemLocationPairing(&BottomOfTheWell_CenterSkulltulaChest,     []{return LogicLensBotw || CanUse(CanUseItem::Lens_of_Truth);}),
                  ItemLocationPairing(&BottomOfTheWell_BackLeftBombableChest,    []{return (LogicLensBotw || CanUse(CanUseItem::Lens_of_Truth)) && HasExplosives;}),
                  ItemLocationPairing(&BottomOfTheWell_FreestandingKey,          []{return Sticks || CanUse(CanUseItem::Dins_Fire);}),
                  ItemLocationPairing(&BottomOfTheWell_LensOfTruthChest,         []{return CanPlay(ZeldasLullaby) && (KokiriSword || (Sticks && LogicChildDeadhand));}),
                  ItemLocationPairing(&BottomOfTheWell_InvisibleChest,           []{return CanPlay(ZeldasLullaby) && (LogicLensBotw || CanUse(CanUseItem::Lens_of_Truth));}),
                  ItemLocationPairing(&BottomOfTheWell_UnderwaterFrontChest,     []{return CanPlay(ZeldasLullaby);}),
                  ItemLocationPairing(&BottomOfTheWell_UnderwaterLeftChest,      []{return CanPlay(ZeldasLullaby);}),
                  ItemLocationPairing(&BottomOfTheWell_MapChest,                 []{return HasExplosives || (((SmallKeys(BottomOfTheWellKeys, 3) && (LogicLensBotw || CanUse(CanUseItem::Lens_of_Truth))) || CanUse(CanUseItem::Dins_Fire)) && GoronBracelet);}),
                  ItemLocationPairing(&BottomOfTheWell_FireKeeseChest,           []{return SmallKeys(BottomOfTheWellKeys, 3) && (LogicLensBotw || CanUse(CanUseItem::Lens_of_Truth));}),
                  ItemLocationPairing(&BottomOfTheWell_LikeLikeChest,            []{return SmallKeys(BottomOfTheWellKeys, 3) && (LogicLensBotw || CanUse(CanUseItem::Lens_of_Truth));}),
                  ItemLocationPairing(&BottomOfTheWell_GS_WestInnerRoom,         []{return Boomerang && (LogicLensBotw || CanUse(CanUseItem::Lens_of_Truth)) && SmallKeys(BottomOfTheWellKeys, 3);}),
                  ItemLocationPairing(&BottomOfTheWell_GS_EastInnerRoom,         []{return Boomerang && (LogicLensBotw || CanUse(CanUseItem::Lens_of_Truth)) && SmallKeys(BottomOfTheWellKeys, 3);}),
                  ItemLocationPairing(&BottomOfTheWell_GS_LikeLikeCage,          []{return SmallKeys(BottomOfTheWellKeys, 3) && (LogicLensBotw || CanUse(CanUseItem::Lens_of_Truth)) && Boomerang;}),
                }, {
                  //Exits
                  ExitPairing::Both(&BottomOfTheWell, []{return true;}),
  });

  Exit IceCavern_Beginning = Exit("Ice Cavern Beginning", "Ice Cavern", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&ZF_Main,        []{return true;}),
                  ExitPairing::Both(&IceCavern_Main, []{return IsAdult || HasExplosives || CanUse(CanUseItem::Dins_Fire);}),
  });

  Exit IceCavern_Main = Exit("Ice Cavern", "Ice Cavern", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&BlueFireAccess, []{return BlueFireAccess || (IsAdult && HasBottle);}),
                }, {
                  //Locations
                  ItemLocationPairing(&IceCavern_MapChest,              []{return BlueFire && IsAdult;}),
                  ItemLocationPairing(&IceCavern_CompassChest,          []{return BlueFire;}),
                  ItemLocationPairing(&IceCavern_IronBootsChest,        []{return BlueFire && (IsAdult || Slingshot || Sticks || KokiriSword || CanUse(CanUseItem::Dins_Fire));}),
                  ItemLocationPairing(&SheikInIceCavern,                []{return BlueFire && (IsAdult || Slingshot || Sticks || KokiriSword || CanUse(CanUseItem::Dins_Fire));}),
                  ItemLocationPairing(&IceCavern_FreestandingPoH,       []{return BlueFire;}),
                  ItemLocationPairing(&IceCavern_GS_SpinningScytheRoom, []{return HookshotOrBoomerang;}),
                  ItemLocationPairing(&IceCavern_GS_HeartPieceRoom,     []{return BlueFire && HookshotOrBoomerang;}),
                  ItemLocationPairing(&IceCavern_GS_PushBlockRoom,      []{return BlueFire && HookshotOrBoomerang;}),
  }, {});

  Exit GerudoTrainingGrounds_Lobby = Exit ("Gerudo Training Grounds Lobby", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&GerudoTrainingGrounds_LobbyLeftChest,  []{return CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Slingshot);}),
                  ItemLocationPairing(&GerudoTrainingGrounds_LobbyRightChest, []{return CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Slingshot);}),
                  ItemLocationPairing(&GerudoTrainingGrounds_StalfosChest,    []{return IsAdult || KokiriSword;}),
                  ItemLocationPairing(&GerudoTrainingGrounds_BeamosChest,     []{return HasExplosives && (IsAdult || KokiriSword);}),
                }, {
                  //Exits
                  ExitPairing::Both(&GF_Main,                              []{return true;}),
                  ExitPairing::Both(&GerudoTrainingGrounds_HeavyBlockRoom, []{return (IsAdult || KokiriSword) && (CanUse(CanUseItem::Hookshot) || LogicGtgWithoutHookshot);}),
                  ExitPairing::Both(&GerudoTrainingGrounds_LavaRoom,       []{return (IsAdult || KokiriSword) && HasExplosives;}),
                  ExitPairing::Both(&GerudoTrainingGrounds_CentralMaze,    []{return true;}),
  });

  Exit GerudoTrainingGrounds_CentralMaze = Exit ("Gerudo Training Grounds Central Maze", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&GerudoTrainingGrounds_HiddenCeilingChest,  []{return SmallKeys(GerudoTrainingGroundsKeys, 3) && (LogicLensGtg || CanUse(CanUseItem::Lens_of_Truth));}),
                  ItemLocationPairing(&GerudoTrainingGrounds_MazePathFirstChest,  []{return SmallKeys(GerudoTrainingGroundsKeys, 4);}),
                  ItemLocationPairing(&GerudoTrainingGrounds_MazePathSecondChest, []{return SmallKeys(GerudoTrainingGroundsKeys, 6);}),
                  ItemLocationPairing(&GerudoTrainingGrounds_MazePathThirdChest,  []{return SmallKeys(GerudoTrainingGroundsKeys, 7);}),
                  ItemLocationPairing(&GerudoTrainingGrounds_MazePathFinalChest,  []{return SmallKeys(GerudoTrainingGroundsKeys, 9);}),
                }, {
                  //Exits
                  ExitPairing::Both(&GerudoTrainingGrounds_CentralMazeRight, []{return SmallKeys(GerudoTrainingGroundsKeys, 9);}),
  });

  Exit GerudoTrainingGrounds_CentralMazeRight = Exit("Gerudo Training Grounds Central Maze Right", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&GerudoTrainingGrounds_MazeRightCentralChest, []{return true;}),
                  ItemLocationPairing(&GerudoTrainingGrounds_MazeRightSideChest,    []{return true;}),
                  ItemLocationPairing(&GerudoTrainingGrounds_FreestandingKey,       []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&GerudoTrainingGrounds_HammerRoom, []{return CanUse(CanUseItem::Hookshot);}),
                  ExitPairing::Both(&GerudoTrainingGrounds_LavaRoom,   []{return true;}),
  });

  Exit GerudoTrainingGrounds_LavaRoom = Exit("Gerudo Training Grounds Lava Room", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&GerudoTrainingGrounds_UnderwaterSilverRupeeChest, []{return CanUse(CanUseItem::Hookshot) && CanPlay(SongOfTime) && IronBoots && (LogicFewerTunicRequirements || CanUse(CanUseItem::Zora_Tunic));}),
                }, {
                  //Exits
                  ExitPairing::Both(&GerudoTrainingGrounds_CentralMazeRight, []{return CanPlay(SongOfTime) || IsChild;}),
                  ExitPairing::Both(&GerudoTrainingGrounds_HammerRoom,       []{return CanUse(CanUseItem::Longshot)  || (CanUse(CanUseItem::Hover_Boots) && CanUse(CanUseItem::Hookshot));}),
  });

  Exit GerudoTrainingGrounds_HammerRoom = Exit("Gerudo Training Grounds Hammer Room", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&GerudoTrainingGrounds_HammerRoomClearChest,  []{return true;}),
                  ItemLocationPairing(&GerudoTrainingGrounds_HammerRoomSwitchChest, []{return CanUse(CanUseItem::Hammer);})
                }, {
                  //Exits
                  ExitPairing::Both(&GerudoTrainingGrounds_EyeStatueLower, []{return CanUse(CanUseItem::Hammer) && Bow;}),
                  ExitPairing::Both(&GerudoTrainingGrounds_LavaRoom,       []{return true;}),
  });

  Exit GerudoTrainingGrounds_EyeStatueLower = Exit("Gerudo Training Grounds Eye Statue Lower", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&GerudoTrainingGrounds_EyeStatueChest, []{return CanUse(CanUseItem::Bow);}),
                }, {
                  //Exits
                  ExitPairing::Both(&GerudoTrainingGrounds_HammerRoom, []{return true;}),
  });

  Exit GerudoTrainingGrounds_EyeStatueUpper = Exit("Gerudo Training Grounds Eye Statue Upper", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&GerudoTrainingGrounds_NearScarecrowChest, []{return CanUse(CanUseItem::Bow);})
                }, {
                  //Exits
                  ExitPairing::Both(&GerudoTrainingGrounds_EyeStatueLower, []{return true;}),
  });

  Exit GerudoTrainingGrounds_HeavyBlockRoom = Exit("Gerudo Training Grounds Heavy Block Room", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&GerudoTrainingGrounds_BeforeHeavyBlockChest, []{return true;})
                }, {
                  //Exits
                  ExitPairing::Both(&GerudoTrainingGrounds_EyeStatueUpper, []{return (LogicLensGtg || CanUse(CanUseItem::Lens_of_Truth)) && (CanUse(CanUseItem::Hookshot) || (LogicGtgFakeWall && CanUse(CanUseItem::Hover_Boots)));}),
                  ExitPairing::Both(&GerudoTrainingGrounds_LikeLikeRoom,   []{return (LogicLensGtg || CanUse(CanUseItem::Lens_of_Truth)) && (CanUse(CanUseItem::Hookshot) || (LogicGtgFakeWall && CanUse(CanUseItem::Hover_Boots))) && CanUse(CanUseItem::Silver_Gauntlets);}),
  });

  Exit GerudoTrainingGrounds_LikeLikeRoom = Exit("Gerudo Training Grounds Like Like Room", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&GerudoTrainingGrounds_HeavyBlockFirstChest,  []{return true;}),
                  ItemLocationPairing(&GerudoTrainingGrounds_HeavyBlockSecondChest, []{return true;}),
                  ItemLocationPairing(&GerudoTrainingGrounds_HeavyBlockThirdChest,  []{return true;}),
                  ItemLocationPairing(&GerudoTrainingGrounds_HeavyBlockFourthChest, []{return true;}),
  }, {});

  Exit GanonsCastle_Lobby = Exit("Ganon's Castle Lobby", "Ganon's Castle", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&OGC_Grounds,              []{return true;}),
                  ExitPairing::Both(&GanonsCastle_ForestTrial, []{return true;}),
                  ExitPairing::Both(&GanonsCastle_FireTrial,   []{return true;}),
                  ExitPairing::Both(&GanonsCastle_WaterTrial,  []{return true;}),
                  ExitPairing::Both(&GanonsCastle_ShadowTrial, []{return true;}),
                  ExitPairing::Both(&GanonsCastle_SpiritTrial, []{return true;}),
                  ExitPairing::Both(&GanonsCastle_LightTrial,  []{return CanUse(CanUseItem::Golden_Gauntlets);}),
                  ExitPairing::Both(&GanonsCastle_Tower,       []{return (ForestTrialClear || ForestTrialSkip) &&
                                                                         (FireTrialClear   || FireTrialSkip)   &&
                                                                         (WaterTrialClear  || WaterTrialSkip)  &&
                                                                         (ShadowTrialClear || ShadowTrialSkip) &&
                                                                         (SpiritTrialClear || SpiritTrialSkip) &&
                                                                         (LightTrialClear  || LightTrialSkip);}),
                  ExitPairing::Both(&GanonsCastle_DekuScrubs,  []{return LogicLensCastle || CanUse(CanUseItem::Lens_of_Truth);}),
  });

  Exit GanonsCastle_DekuScrubs = Exit("Ganon's Castle Deku Scrubs", "Ganon's Castle", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FreeFairies, []{return true;}),
                }, {
                  //Locations
                  ItemLocationPairing(&GanonsCastle_DekuScrubCenterLeft, []{return true;}),
                  ItemLocationPairing(&GanonsCastle_DekuScrubCenterRight, []{return true;}),
                  ItemLocationPairing(&GanonsCastle_DekuScrubRight, []{return true;}),
                  ItemLocationPairing(&GanonsCastle_DekuScrubLeft, []{return true;}),
  }, {});

  Exit GanonsCastle_ForestTrial = Exit("Ganon's Castle Forest Trial", "Ganon's Castle", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&ForestTrialClear, []{return CanUse(CanUseItem::Light_Arrows) && (FireArrows || DinsFire);}),
                }, {
                  //Locations
                  ItemLocationPairing(&GanonsCastle_ForestTrialChest, []{return true;}),
  }, {});

  Exit GanonsCastle_FireTrial = Exit("Ganon's Castle Fire Trial", "Ganon's Castle", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FireTrialClear, []{return CanUse(CanUseItem::Goron_Tunic) && CanUse(CanUseItem::Golden_Gauntlets) && CanUse(CanUseItem::Light_Arrows) && CanUse(CanUseItem::Longshot);}),
  }, {}, {});

  Exit GanonsCastle_WaterTrial = Exit("Ganon's Castle Water Trial", "Ganon's Castle", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&BlueFireAccess,  []{return BlueFireAccess || HasBottle;}),
                  EventPairing(&FairyPot,        []{return FairyPot || BlueFire;}),
                  EventPairing(&WaterTrialClear, []{return BlueFire && Hammer && CanUse(CanUseItem::Light_Arrows);}),
                }, {
                  //Locations
                  ItemLocationPairing(&GanonsCastle_WaterTrialLeftChest,  []{return true;}),
                  ItemLocationPairing(&GanonsCastle_WaterTrialRightChest, []{return true;}),
  }, {});

  Exit GanonsCastle_ShadowTrial = Exit("Ganon's Castle Shadow Trial", "Ganon's Castle", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&ShadowTrialClear, []{return CanUse(CanUseItem::Light_Arrows) && Hammer && ((FireArrows && (LogicLensCastle || CanUse(CanUseItem::Lens_of_Truth))) || (CanUse(CanUseItem::Longshot) && (HoverBoots || (DinsFire && (LogicLensCastle || CanUse(CanUseItem::Lens_of_Truth))))));}),
                }, {
                  //Locations
                  ItemLocationPairing(&GanonsCastle_ShadowTrialFrontChest,           []{return CanUse(CanUseItem::Fire_Arrows) || Hookshot || HoverBoots || CanPlay(SongOfTime);}),
                  ItemLocationPairing(&GanonsCastle_ShadowTrialGoldenGauntletsChest, []{return CanUse(CanUseItem::Fire_Arrows) || (CanUse(CanUseItem::Longshot) && (HoverBoots || CanUse(CanUseItem::Dins_Fire)));}),
  }, {});

  Exit GanonsCastle_SpiritTrial = Exit("Ganon's Castle Spirit Trial", "Ganon's Castle", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&NutPot,           []{return NutPot || ((LogicSpiritTrialHookshot || Hookshot) && HasBombchus && Bow && MirrorShield);}),
                  EventPairing(&SpiritTrialClear, []{return CanUse(CanUseItem::Light_Arrows)  && MirrorShield && HasBombchus && (LogicSpiritTrialHookshot || Hookshot);}),
                }, {
                  //Locations
                  ItemLocationPairing(&GanonsCastle_SpiritTrialCrystalSwitchChest, []{return LogicSpiritTrialHookshot || Hookshot;}),
                  ItemLocationPairing(&GanonsCastle_SpiritTrialInvisibleChest,     []{return (LogicSpiritTrialHookshot || Hookshot) && HasBombchus && (LogicLensCastle || CanUse(CanUseItem::Lens_of_Truth));}),
  }, {});

  Exit GanonsCastle_LightTrial = Exit("Ganon's Castle Light Trial", "Ganon's Castle", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&LightTrialClear, []{return CanUse(CanUseItem::Light_Arrows) && Hookshot && SmallKeys(GanonsCastleKeys, 2) && (LogicLensCastle || CanUse(CanUseItem::Lens_of_Truth));}),
                }, {
                  //Locations
                  ItemLocationPairing(&GanonsCastle_LightTrialFirstLeftChest,        []{return true;}),
                  ItemLocationPairing(&GanonsCastle_LightTrialSecondLeftChest,       []{return true;}),
                  ItemLocationPairing(&GanonsCastle_LightTrialThirdLeftChest,        []{return true;}),
                  ItemLocationPairing(&GanonsCastle_LightTrialFirstRightChest,       []{return true;}),
                  ItemLocationPairing(&GanonsCastle_LightTrialSecondRightChest,      []{return true;}),
                  ItemLocationPairing(&GanonsCastle_LightTrialThirdRightChest,       []{return true;}),
                  ItemLocationPairing(&GanonsCastle_LightTrialInvisibleEnemiesChest, []{return LogicLensCastle || CanUse(CanUseItem::Lens_of_Truth);}),
                  ItemLocationPairing(&GanonsCastle_LightTrialLullabyChest,          []{return CanPlay(ZeldasLullaby) && SmallKeys(GanonsCastleKeys, 1);}),
  }, {});

  Exit GanonsCastle_Tower = Exit("Ganon's Castle Tower", "Ganons Castle", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&GanonsCastle_BossKeyChest, []{return true;}),
                  //Ganondorf Hint
                  ItemLocationPairing(&Ganon, []{return BossKeyGanonsCastle && CanUse(CanUseItem::Light_Arrows);}),
  }, {});

  /*---------------------------
  |   MASTER QUEST DUNGEONS   |
  ---------------------------*/

  Exit DekuTree_MQ_Lobby = Exit("Deku Tree MQ Lobby", "Deku Tree", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&DekuBabaSticks, []{return DekuBabaSticks || (IsAdult || KokiriSword || Boomerang);}),
    EventPairing(&DekuBabaNuts,   []{return DekuBabaNuts   || (IsAdult || KokiriSword || Slingshot || Sticks || HasExplosives || CanUse(CanUseItem::Dins_Fire));}),
  }, {
    //Locations
    ItemLocationPairing(&DekuTree_MQ_MapChest,               []{return true;}),
    ItemLocationPairing(&DekuTree_MQ_SlingshotChest,         []{return IsAdult || CanChildAttack;}),
    ItemLocationPairing(&DekuTree_MQ_SlingshotRoomBackChest, []{return HasFireSourceWithTorch || CanUse(CanUseItem::Bow);}),
    ItemLocationPairing(&DekuTree_MQ_BasementChest,          []{return HasFireSourceWithTorch || CanUse(CanUseItem::Bow);}),
    ItemLocationPairing(&DekuTree_MQ_GS_Lobby,               []{return IsAdult || CanChildAttack;}),
  }, {
    //Exits
    ExitPairing(&KF_OutsideDekuTree,            []{return true;}),
    ExitPairing(&DekuTree_MQ_CompassRoom,       []{return (CanUse(CanUseItem::Slingshot) || CanUse(CanUseItem::Bow)) && (HasFireSourceWithTorch || CanUse(CanUseItem::Bow));}),
    ExitPairing(&DekuTree_MQ_BasementWaterRoom, []{return (CanUse(CanUseItem::Slingshot) || CanUse(CanUseItem::Bow)) && HasFireSourceWithTorch;}),
    ExitPairing(&DekuTree_MQ_BasementLedge,     []{return LogicDekuB1Skip || IsAdult;}),
  });

  Exit DekuTree_MQ_CompassRoom = Exit("Deku Tree MQ Compass Room", "Deku Tree", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&DekuTree_MQ_CompassChest, []{return true;}),
    ItemLocationPairing(&DekuTree_MQ_GS_CompassRoom, []{return (CanUse(CanUseItem::Hookshot) || CanUse(CanUseItem::Boomerang)) && (HasBombchus || (Bombs && (IsAdult || CanPlay(SongOfTime))));}),
  }, {
    //Exits
    ExitPairing(&DekuTree_MQ_Lobby, []{return true;}),
  });

  Exit DekuTree_MQ_BasementWaterRoom = Exit("Deku Tree MQ Basement Water Room", "Deku Tree", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&DekuTree_MQ_BeforeSpinningLogChest, []{return true;}),
    ItemLocationPairing(&DekuTree_MQ_AfterSpinningLowChest,  []{return true;}),
  }, {
    //Exits
    ExitPairing(&DekuTree_MQ_BasementBackRoom, []{return true;}),
    ExitPairing(&DekuTree_MQ_Lobby,            []{return true;}),
  });

  Exit DekuTree_MQ_BasementBackRoom = Exit("Deku Tree MQ Basement Back Room", "Deku Tree", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&DekuTree_MQ_GS_BasementGravesRoom, []{return CanUse(CanUseItem::Longshot) || (CanPlay(SongOfTime) && HookshotOrBoomerang);}),
    ItemLocationPairing(&DekuTree_MQ_GS_BasementBackRoom,   []{return HasFireSourceWithTorch && HookshotOrBoomerang;})
  }, {
    //Exits
    ExitPairing(&DekuTree_MQ_BasementLedge,     []{return IsChild;}),
    ExitPairing(&DekuTree_MQ_BasementWaterRoom, []{return CanUse(CanUseItem::Kokiri_Sword) || CanUseProjectile || (Nuts && CanUse(CanUseItem::Sticks));}),
  });

  Exit DekuTree_MQ_BasementLedge = Exit("Deku Tree MQ Basement Ledge", "Deku Tree", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&DekuTreeClear, []{return DekuTreeClear || (HasFireSourceWithTorch && HasShield && (IsAdult || KokiriSword || Sticks));}),
  }, {
    //Locations
    ItemLocationPairing(&DekuTree_MQ_DekuScrub,    []{return CanStunDeku;}),
    ItemLocationPairing(&DekuTree_QueenGohmaHeart, []{return HasFireSourceWithTorch && HasShield && (IsAdult || KokiriSword || Sticks);}),
    ItemLocationPairing(&QueenGohma,               []{return HasFireSourceWithTorch && HasShield && (IsAdult || KokiriSword || Sticks);}),
  }, {
    //Exits
    ExitPairing(&DekuTree_MQ_BasementBackRoom, []{return IsChild;}),
    ExitPairing(&DekuTree_MQ_Lobby,            []{return true;}),
  });

  Exit DodongosCavern_MQ_Beginning = Exit("Dodongos Cavern MQ Beginning", "Dodongos Cavern", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
    //Exits
    ExitPairing::Both(&DodongosCavern_Entryway, []{return true;}),
    ExitPairing::Both(&DodongosCavern_MQ_Lobby, []{return CanBlastOrSmash || GoronBracelet;})
  });

  Exit DodongosCavern_MQ_Lobby = Exit("Dodongos Cavern MQ Lobby", "Dodongos Cavern", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&DekuBabaSticks,   []{return DekuBabaSticks || (IsAdult || KokiriSword || Boomerang);}),
    EventPairing(&GossipStoneFairy, []{return GossipStoneFairy || CanSummonGossipFairy;}),
  }, {
    //Locations
    ItemLocationPairing(&DodongosCavern_MQ_MapChest,               []{return true;}),
    ItemLocationPairing(&DodongosCavern_MQ_CompassChest,           []{return IsAdult || CanChildAttack || Nuts;}),
    ItemLocationPairing(&DodongosCavern_MQ_LarvaeRoomChest,        []{return CanUse(CanUseItem::Sticks) || HasFireSource;}),
    ItemLocationPairing(&DodongosCavern_MQ_TorchPuzzleRoomChest,   []{return CanBlastOrSmash || CanUse(CanUseItem::Sticks) || CanUse(CanUseItem::Dins_Fire) || (IsAdult && (LogicDCJump || HoverBoots || Hookshot));}),
    ItemLocationPairing(&DodongosCavern_MQ_GS_SongOfTimeBlockRoom, []{return CanPlay(SongOfTime) && (CanChildAttack || IsAdult);}),
    ItemLocationPairing(&DodongosCavern_MQ_GS_LarvaeRoom,          []{return CanUse(CanUseItem::Sticks) || HasFireSource;}),
    ItemLocationPairing(&DodongosCavern_MQ_GS_LizalfosRoom,        []{return CanBlastOrSmash;}),
    ItemLocationPairing(&DodongosCavern_MQ_DekuScrubLobbyRear,     []{return CanStunDeku;}),
    ItemLocationPairing(&DodongosCavern_MQ_DekuScrubLobbyFront,    []{return CanStunDeku;}),
    ItemLocationPairing(&DodongosCavern_MQ_DekuScrubStaircase,     []{return CanStunDeku;}),
    //Dodongos Cavern Gossip Stone
  }, {
    //Exits
    ExitPairing::Both(&DodongosCavern_MQ_LowerRightSide,  []{return CanBlastOrSmash || ((CanUse(CanUseItem::Sticks) || CanUse(CanUseItem::Dins_Fire)) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO));}),
    ExitPairing::Both(&DodongosCavern_MQ_BombBagArea,     []{return IsAdult || HasExplosives;}),
      //Trick: IsAdult || HasExplosives || (LogicDCMQChildBombs && (KokiriSword || Sticks) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO))
    ExitPairing::Both(&DodongosCavern_MQ_BossArea,        []{return HasExplosives;}),
      //Trick: HasExplosives || (LogicDCMQEyes && GoronBracelet && (IsAdult || LogicDCMQChildBack) && (CanUse(CanUseItem::Sticks) || CanUse(CanUseItem::Dins_Fire) || (IsAdult && (LogicDCJump || Hammer || HoverBoots || Hookshot))))
  });

  Exit DodongosCavern_MQ_LowerRightSide = Exit("Dodongos Cavern MQ Lower Right Side", "Dodongos Cavern", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&DodongosCavern_MQ_DekuScrubSideRoomNearLowerLizalfos, []{return CanStunDeku;}),
  }, {
    //Exits
    ExitPairing::Both(&DodongosCavern_MQ_BombBagArea, []{return (CanUse(CanUseItem::Bow) || GoronBracelet || CanUse(CanUseItem::Dins_Fire) || HasExplosives) && CanUse(CanUseItem::Slingshot);}),
  });

  Exit DodongosCavern_MQ_BombBagArea = Exit("Dodongos Cavern MQ Bomb Bag Area", "Dodongos Cavern", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&DodongosCavern_MQ_BombBagChest, []{return true;}),
    ItemLocationPairing(&DodongosCavern_MQ_GS_ScrubRoom, []{return (CanUse(CanUseItem::Bow) ||  GoronBracelet || CanUse(CanUseItem::Dins_Fire) || HasExplosives) && (CanUse(CanUseItem::Hookshot) || CanUse(CanUseItem::Boomerang));}),
  }, {
    //Exits
    ExitPairing::Both(&DodongosCavern_MQ_LowerRightSide, []{return true;}),
  });

  Exit DodongosCavern_MQ_BossArea = Exit("Dodongos Cavern MQ BossArea", "Dodongos Cavern", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&FairyPot,            []{return true;}),
    EventPairing(&DodongosCavernClear, []{return DodongosCavernClear || (CanBlastOrSmash && (Bombs || GoronBracelet) && (IsAdult || Sticks || KokiriSword));}),
  }, {
    //Locations
    ItemLocationPairing(&DodongosCavern_MQ_UnderGraveChest, []{return true;}),
    ItemLocationPairing(&DodongosCavern_BossRoomChest,      []{return true;}),
    ItemLocationPairing(&DodongosCavern_KingDodongoHeart,   []{return CanBlastOrSmash && (Bombs || GoronBracelet) && (IsAdult || Sticks || KokiriSword);}),
    ItemLocationPairing(&KingDodongo,                       []{return CanBlastOrSmash && (Bombs || GoronBracelet) && (IsAdult || Sticks || KokiriSword);}),
    ItemLocationPairing(&DodongosCavern_MQ_GS_BackRoom,     []{return true;}),
  }, {});

  Exit JabuJabusBelly_MQ_Beginning = Exit("Jabu Jabus Belly MQ Beginning", "Jabu Jabus Belly", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&NutPot, []{return true;}),
  }, {
    //Locations
    ItemLocationPairing(&JabuJabusBelly_MQ_MapChest,           []{return CanBlastOrSmash;}),
    ItemLocationPairing(&JabuJabusBelly_MQ_FirstRoomSideChest, []{return CanUse(CanUseItem::Slingshot);}),
  }, {
    //Exits
    ExitPairing::Both(&ZF_Main,                []{return true;}),
    ExitPairing::Both(&JabuJabusBelly_MQ_Main, []{return IsChild && CanUse(CanUseItem::Slingshot);}),
  });

  Exit JabuJabusBelly_MQ_Main = Exit("Jabu Jabus Belly MQ Main", "Jabu Jabus Belly", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&JabuJabusBelly_MQ_SecondRoomLowerChest,      []{return true;}),
    ItemLocationPairing(&JabuJabusBelly_MQ_SecondRoomUpperChest,      []{return CanUse(CanUseItem::Hover_Boots) || CanUse(CanUseItem::Hookshot) || JabuJabusBelly_MQ_BossArea.Child();}),
    ItemLocationPairing(&JabuJabusBelly_MQ_CompassChest,              []{return true;}),
    ItemLocationPairing(&JabuJabusBelly_MQ_BasementNearVinesChest,    []{return true;}),
    ItemLocationPairing(&JabuJabusBelly_MQ_BasementNearSwitchesChest, []{return true;}),
    ItemLocationPairing(&JabuJabusBelly_MQ_BoomerangRoomSmallChest,   []{return true;}),
    ItemLocationPairing(&JabuJabusBelly_MQ_BoomerangChest,            []{return true;}),
    ItemLocationPairing(&JabuJabusBelly_MQ_GS_BoomerangChestRoom,     []{return CanPlay(SongOfTime);}),
      //Trick: CanPlay(SongOfTime) || (LogicJabuMQSoTGS && CanUse(CanUseItem::Boomerang))
  }, {
    //Exits
    ExitPairing::Both(&JabuJabusBelly_MQ_Beginning, []{return true;}),
    ExitPairing::Both(&JabuJabusBelly_MQ_Depths,    []{return HasExplosives && CanUse(CanUseItem::Boomerang);}),
  });

  Exit JabuJabusBelly_MQ_Depths = Exit("Jabu Jabus Belly MQ Depths", "Jabu Jabus Belly", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&JabuJabusBelly_MQ_FallingLikeLikeRoomChest, []{return true;}),
    ItemLocationPairing(&JabuJabusBelly_MQ_GS_TailPasaranRoom,       []{return Sticks || CanUse(CanUseItem::Dins_Fire);}),
    ItemLocationPairing(&JabuJabusBelly_MQ_GS_InvisibleEnemiesRoom,  []{return (LogicLensJabuMQ || CanUse(CanUseItem::Lens_of_Truth)) || (JabuJabusBelly_MQ_Main.Adult() && CanUse(CanUseItem::Hover_Boots) && CanUse(CanUseItem::Hookshot));}),
  }, {
    //Exits
    ExitPairing::Both(&JabuJabusBelly_MQ_Main,     []{return true;}),
    ExitPairing::Both(&JabuJabusBelly_MQ_BossArea, []{return Sticks || (CanUse(CanUseItem::Dins_Fire) && KokiriSword);}),
  });

  Exit JabuJabusBelly_MQ_BossArea = Exit("Jabu Jabus Belly MQ Boss Area", "Jabu Jabus Belly", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&FairyPot,            []{return true;}),
    EventPairing(&JabuJabusBellyClear, []{return true;}),
  }, {
    //Locations
    ItemLocationPairing(&JabuJabusBelly_MQ_Cow,           []{return CanPlay(EponasSong);}),
    ItemLocationPairing(&JabuJabusBelly_MQ_NearBossChest, []{return true;}),
    ItemLocationPairing(&JabuJabusBelly_BarinadeHeart,    []{return true;}),
    ItemLocationPairing(&Barinade,                        []{return true;}),
    ItemLocationPairing(&JabuJabusBelly_MQ_GS_NearBoss,   []{return true;}),
  }, {
    //Exits
    ExitPairing::Both(&JabuJabusBelly_MQ_Main, []{return true;}),
  });

  Exit ForestTemple_MQ_Lobby = Exit("Forest Temple MQ Lobby", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&ForestTemple_MQ_FirstRoomChest,  []{return IsAdult || Bombs || CanUse(CanUseItem::Sticks) || Nuts || CanUse(CanUseItem::Boomerang) || CanUse(CanUseItem::Dins_Fire) || KokiriSword || CanUse(CanUseItem::Slingshot);}),
    ItemLocationPairing(&ForestTemple_MQ_GS_FirstHallway, []{return CanUse(CanUseItem::Hookshot) || CanUse(CanUseItem::Boomerang);}),
  }, {
    //Exits
    ExitPairing::Both(&SFM_Main,                    []{return true;}),
    ExitPairing::Both(&ForestTemple_MQ_CentralArea, []{return SmallKeys(ForestTempleKeys, 1) && (IsAdult || CanChildAttack || Nuts);}),
  });

  Exit ForestTemple_MQ_CentralArea = Exit("Forest Temple MQ Central Area", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&FairyPot, []{return true;}),
  }, {
    //Locations
    ItemLocationPairing(&ForestTemple_MQ_WolfosChest,      []{return (CanPlay(SongOfTime) || IsChild) && (IsAdult || CanUse(CanUseItem::Dins_Fire) || CanUse(CanUseItem::Sticks) || CanUse(CanUseItem::Slingshot) || KokiriSword);}),
    ItemLocationPairing(&ForestTemple_MQ_GS_BlockPushRoom, []{return IsAdult || KokiriSword;}),
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

  Exit ForestTemple_MQ_AfterBlockPuzzle = Exit("Forest Temple MQ After Block Puzzle", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&ForestTemple_MQ_BossKeyChest, []{return SmallKeys(ForestTempleKeys, 3);}),
  }, {
    //Exits
    ExitPairing::Both(&ForestTemple_MQ_BowRegion,    []{return SmallKeys(ForestTempleKeys, 4);}),
    ExitPairing::Both(&ForestTemple_MQ_OutdoorLedge, []{return SmallKeys(ForestTempleKeys, 3);}),
      //Trick: SmallKeys(ForestTempleKeys, 3) || (LogicForestMQHallwaySwitchJumpslash && (CanUse(CanUseItem::Hookshot) || LogicForestOutsideBackdoor))
    ExitPairing::Both(&ForestTemple_MQ_NWOutdoors,   []{return SmallKeys(ForestTempleKeys, 2);}),
  });

  Exit ForestTemple_MQ_OutdoorLedge = Exit("Forest Temple MQ Outdoor Ledge", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&ForestTemple_MQ_RedeadChest, []{return true;}),
  }, {
    //Exits
    ExitPairing::Both(&ForestTemple_MQ_NWOutdoors, []{return true;}),
  });

  Exit ForestTemple_MQ_NWOutdoors = Exit("Forest Temple MQ NW Outdoors", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&ForestTemple_MQ_GS_LevelIslandCourtyard, []{return true;}),
  }, {
    //Exits
    ExitPairing::Both(&ForestTemple_MQ_NEOutdoors,        []{return CanUse(CanUseItem::Iron_Boots) || CanUse(CanUseItem::Longshot) || ProgressiveScale >= 2;}),
      //Trick: CanUse(CanUseItem::Iron_Boots) || CanUse(CanUseItem::Longshot) || ProgressiveScale >= 2 || (LogicForestMQWellSwim && CanUse(CanUseItem::Hookshot))
    ExitPairing::Both(&ForestTemple_MQ_OutdoorsTopLedges, []{return CanUse(CanUseItem::Fire_Arrows);}),
  });

  Exit ForestTemple_MQ_NEOutdoors = Exit("Forest Temple MQ NE Outdoors", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&DekuBabaSticks, []{return DekuBabaSticks || (IsAdult || KokiriSword || Boomerang);}),
    EventPairing(&DekuBabaNuts,   []{return DekuBabaNuts   || (IsAdult || KokiriSword || Slingshot || Sticks || HasExplosives || CanUse(CanUseItem::Dins_Fire));}),
  }, {
    //Locations
    ItemLocationPairing(&ForestTemple_MQ_WellChest,                []{return CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Slingshot);}),
    ItemLocationPairing(&ForestTemple_MQ_GS_RaisedIslandCourtyard, []{return CanUse(CanUseItem::Hookshot) || CanUse(CanUseItem::Boomerang) || (CanUse(CanUseItem::Fire_Arrows) && (CanPlay(SongOfTime) || (CanUse(CanUseItem::Hover_Boots) && LogicForestDoorFrame)));}),
    ItemLocationPairing(&ForestTemple_MQ_GS_Well,                  []{return (CanUse(CanUseItem::Iron_Boots) && CanUse(CanUseItem::Hookshot)) || CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Slingshot);}),
  }, {
    //Exits
    ExitPairing::Both(&ForestTemple_MQ_OutdoorsTopLedges, []{return CanUse(CanUseItem::Hookshot) && (CanUse(CanUseItem::Longshot) || CanUse(CanUseItem::Hover_Boots) || CanPlay(SongOfTime));}),
    ExitPairing::Both(&ForestTemple_MQ_NEOutdoorsLedge,   []{return CanUse(CanUseItem::Longshot);}),
  });

  Exit ForestTemple_MQ_OutdoorsTopLedges = Exit("Forest Temple MQ Outdoors Top Ledges", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&ForestTemple_MQ_RaisedIslandCourtyardUpperChest, []{return true;}),
  }, {
    //Exits
    ExitPairing::Both(&ForestTemple_MQ_NEOutdoors,      []{return true;}),
    ExitPairing::Both(&ForestTemple_MQ_NEOutdoorsLedge, []{return false;}),
      //Trick: LogicForestOutdoorsLedge && CanUse(CanUseItem::Hover_Boots)
  });

  Exit ForestTemple_MQ_NEOutdoorsLedge = Exit("Forest Temple MQ NE Outdoors Ledge", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&ForestTemple_MQ_RaisedIslandCourtyardLowerChest, []{return true;}),
  }, {
    //Exits
    ExitPairing::Both(&ForestTemple_MQ_NEOutdoors,  []{return true;}),
    ExitPairing::Both(&ForestTemple_MQ_FallingRoom, []{return CanPlay(SongOfTime);}),
  });

  Exit ForestTemple_MQ_BowRegion = Exit("Forest Temple MQ Bow Region", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&ForestTempleJoAndBeth, []{return ForestTempleJoAndBeth || CanUse(CanUseItem::Bow);}),
  }, {
    //Locations
    ItemLocationPairing(&ForestTemple_MQ_BowChest,     []{return true;}),
    ItemLocationPairing(&ForestTemple_MQ_MapChest,     []{return CanUse(CanUseItem::Bow);}),
    ItemLocationPairing(&ForestTemple_MQ_CompassChest, []{return CanUse(CanUseItem::Bow);}),
  }, {
    //Exits
    ExitPairing::Both(&ForestTemple_MQ_FallingRoom, []{return SmallKeys(ForestTempleKeys, 5) && (CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Dins_Fire));}),
  });

  Exit ForestTemple_MQ_FallingRoom = Exit("Forest Temple MQ Falling Room", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&ForestTempleAmyAndMeg, []{return ForestTempleAmyAndMeg || (CanUse(CanUseItem::Bow) && SmallKeys(ForestTempleKeys, 6));}),
  }, {
    //Locations
    ItemLocationPairing(&ForestTemple_MQ_FallingCeilingRoomChest, []{return true;}),
  }, {
    //Exits
    ExitPairing::Both(&ForestTemple_MQ_NEOutdoorsLedge, []{return true;}),
  });

  Exit ForestTemple_MQ_BossRegion = Exit("Forest Temple MQ Boss Region", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&ForestTempleClear, []{return ForestTempleClear || BossKeyForestTemple;}),
  }, {
    //Locations
    ItemLocationPairing(&ForestTemple_MQ_BasementChest,  []{return true;}),
    ItemLocationPairing(&ForestTemple_PhantomGanonHeart, []{return BossKeyForestTemple;}),
    ItemLocationPairing(&PhantomGanon,                   []{return BossKeyForestTemple;}),
  }, {});

  Exit FireTemple_MQ_Lower = Exit("Fire Temple MQ Lower", "Fire Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&FireTemple_MQ_MapRoomSideChest, []{return IsAdult || KokiriSword || Sticks || Slingshot || Bombs || CanUse(CanUseItem::Dins_Fire);}),
    ItemLocationPairing(&FireTemple_MQ_NearBossChest,    []{return (LogicFewerTunicRequirements || CanUse(CanUseItem::Goron_Tunic)) && (CanUse(CanUseItem::Hover_Boots) || (CanUse(CanUseItem::Hookshot) && (CanUse(CanUseItem::Fire_Arrows) || (CanUse(CanUseItem::Dins_Fire) && ((DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_QUADRUPLE)) || CanUse(CanUseItem::Goron_Tunic) || CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Longshot))))));}),
      //Trick: (LogicFewerTunicRequirements || CanUse(CanUseItem::Goron_Tunic)) && (((CanUse(CanUseItem::Hover_Boots) || (LogicFireMQNearBoss && CanUse(CanUseItem::Bow))) && HasFireSource) || (CanUse(CanUseItem::Hookshot) && CanUse(CanUseItem::Fire_Arrows) || (CanUse(CanUseItem::Dins_Fire) && ((DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_QUADRUPLE)) || CanUse(CanUseItem::Goron_Tunic) || CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Longshot)))))
  }, {
    //Exits
    ExitPairing::Both(&FireTemple_Entrance,           []{return true;}),
    ExitPairing::Both(&FireTemple_MQ_BossRoom,        []{return CanUse(CanUseItem::Goron_Tunic) && CanUse(CanUseItem::Hammer) && BossKeyFireTemple && ((HasFireSource && (LogicFireBossDoorJump || HoverBoots)) || FireTemple_MQ_Upper.Adult());}),
    ExitPairing::Both(&FireTemple_MQ_LowerLockedDoor, []{return SmallKeys(FireTempleKeys, 5) && (IsAdult || KokiriSword);}),
    ExitPairing::Both(&FireTemple_MQ_BigLavaRoom,     []{return (LogicFewerTunicRequirements || CanUse(CanUseItem::Goron_Tunic)) && CanUse(CanUseItem::Hammer);}),
  });

  Exit FireTemple_MQ_LowerLockedDoor = Exit("Fire Temple MQ Lower Locked Door", "Fire Temple", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&FairyPot, []{return true;}),
  }, {
    //Locations
    ItemLocationPairing(&FireTemple_MQ_MegatonHammerChest, []{return IsAdult && (HasExplosives || Hammer || Hookshot);}),
    ItemLocationPairing(&FireTemple_MQ_MapChest,           []{return CanUse(CanUseItem::Hammer);}),
  }, {});

  Exit FireTemple_MQ_BigLavaRoom = Exit("Fire Temple MQ Big Lava Room", "Fire Temple", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&FairyPot, []{return FairyPot || (HasFireSource && Bow && (CanUse(CanUseItem::Hookshot) || LogicFireSongOfTime));}),
      //Trick: HasFireSource && (Bow || LogicFireMQBKChest) && (CanUse(CanUseItem::Hookshot) || LogicFireSongOfTime)
  }, {
    //Locations
    ItemLocationPairing(&FireTemple_MQ_BossKeyChest,                []{return HasFireSource && Bow && CanUse(CanUseItem::Hookshot);}),
      //Trick: HasFireSource && (Bow || LogicFireMQBKChest) && CanUse(CanUseItem::Hookshot)
    ItemLocationPairing(&FireTemple_MQ_BigLavaRoomBlockedDoorChest, []{return HasFireSource && HasExplosives && CanUse(CanUseItem::Hookshot);}),
      //Trick: HasFireSource && HasExplosives && (CanUse(CanUseItem::Hookshot) || LogicFireMQBlockedChest)
    ItemLocationPairing(&FireTemple_MQ_GS_BigLavaRoomOpenDoor,      []{return true;}),
  }, {
    //Exits
    ExitPairing::Both(&FireTemple_MQ_LowerMaze, []{return CanUse(CanUseItem::Goron_Tunic) && SmallKeys(FireTempleKeys, 2) && HasFireSource;}),
      //Trick: CanUse(CanUseItem::Goron_Tunic) && SmallKeys(FireTempleKeys, 2) && (HasFireSource || (LogicFireMQClimb && HoverBoots))
  });

  Exit FireTemple_MQ_LowerMaze = Exit("Fire Temple MQ Lower Maze", "Fire Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&FireTemple_MQ_LizalfosMazeLowerChest,    []{return true;}),
    ItemLocationPairing(&FireTemple_MQ_LizalfosMazeSideRoomChest, []{return HasExplosives && FireTemple_MQ_UpperMaze.Adult();}),
      //Trick: HasExplosives && (LogicFireMQMazeSideRoom || FireTemple_MQ_UpperMaze.Adult())
   }, {
    //Exits
    ExitPairing::Both(&FireTemple_MQ_UpperMaze, []{return HasExplosives && CanUse(CanUseItem::Hookshot);}),
      //Trick: (HasExplosives && CanUse(CanUseItem::Hookshot)) || (LogicFireMQMazeHovers && CanUse(CanUseItem::Hover_Boots)) || LogicFireMQMazeJump
  });

  Exit FireTemple_MQ_UpperMaze = Exit("Fire Temple MQ Upper Maze", "Fire Temple", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    //EventPairing(&WallFairy, []{return WallFairy || ((CanPlay(SongOfTime) && CanUse(CanUseItem::Hookshot) && HasExplosives) || CanUse(CanUseItem::Longshot));}),
    EventPairing(&FairyPot,  []{return SmallKeys(FireTempleKeys, 3);}),
  }, {
    //Locations
    ItemLocationPairing(&FireTemple_MQ_LizalfosMazeUpperChest, []{return true;}),
    ItemLocationPairing(&FireTemple_MQ_CompassChest,           []{return HasExplosives;}),
    ItemLocationPairing(&FireTemple_MQ_GS_SkullOnFire,         []{return (CanPlay(SongOfTime) && CanUse(CanUseItem::Hookshot) && HasExplosives) || CanUse(CanUseItem::Longshot);}),
  }, {
    //Exits
    ExitPairing::Both(&FireTemple_MQ_Upper, []{return SmallKeys(FireTempleKeys, 3) && ((CanUse(CanUseItem::Bow) && CanUse(CanUseItem::Hookshot)) || CanUse(CanUseItem::Fire_Arrows));}),
  });

  Exit FireTemple_MQ_Upper = Exit("Fire Temple MQ Upper", "Fire Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&FireTemple_MQ_FreestandingKey,         []{return CanUse(CanUseItem::Hookshot);}),
      //Trick: CanUse(CanUseItem::Hookshot) || LogicFireMQFlameMaze
    ItemLocationPairing(&FireTemple_MQ_ChestOnFire,             []{return CanUse(CanUseItem::Hookshot) && SmallKeys(FireTempleKeys, 4);}),
      //Trick: (CanUse(CanUseItem::Hookshot) || LogicFireMQFlameMaze) && SmallKeys(FireTempleKeys, 4)
    ItemLocationPairing(&FireTemple_MQ_GS_FireWallMazeSideRoom, []{return CanPlay(SongOfTime) || HoverBoots;}),
      //Trick: CanPlay(SongOfTime) || HoverBoots || LogicFireMQFlameMaze
    ItemLocationPairing(&FireTemple_MQ_GS_FireWallMazeCenter,   []{return HasExplosives;}),
    ItemLocationPairing(&FireTemple_MQ_GS_AboveFireWallMaze,    []{return CanUse(CanUseItem::Hookshot) && SmallKeys(FireTempleKeys, 5);}),
      //Trick: (CanUse(CanUseItem::Hookshot) && SmallKeys(FireTempleKeys, 5)) || (LogicFireMQAboveMazeGS && CanUse(CanUseItem::Longshot))
  }, {});

  Exit FireTemple_MQ_BossRoom = Exit("Fire Temple MQ Boss Room", "Fire Temple", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&FireTempleClear, []{return true;}),
  }, {
    //Locations
    ItemLocationPairing(&FireTemple_VolvagiaHeart, []{return true;}),
    ItemLocationPairing(&Volvagia, []{return true;}),
  }, {});

  Exit WaterTemple_MQ_Lobby = Exit("Water Temple MQ Lobby", "Water Temple", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&WaterTempleClear, []{return BossKeyWaterTemple && CanUse(CanUseItem::Longshot);}),
  }, {
    //Locations
    ItemLocationPairing(&WaterTemple_MorphaHeart, []{return BossKeyWaterTemple && CanUse(CanUseItem::Longshot);}),
    ItemLocationPairing(&Morpha,                  []{return BossKeyWaterTemple && CanUse(CanUseItem::Longshot);}),
  }, {
    //Exits
    ExitPairing::Both(&LH_Main,                       []{return true;}),
    ExitPairing::Both(&WaterTemple_MQ_Dive,           []{return (CanUse(CanUseItem::Zora_Tunic) || LogicFewerTunicRequirements) && CanUse(CanUseItem::Iron_Boots);}),
    ExitPairing::Both(&WaterTemple_MQ_DarkLinkRegion, []{return SmallKeys(WaterTempleKeys, 1) && CanUse(CanUseItem::Longshot);}),
  });

  Exit WaterTemple_MQ_Dive = Exit("Water Temple MQ Dive", "Water Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&WaterTemple_MQ_MapChest,           []{return HasFireSource && CanUse(CanUseItem::Hookshot);}),
    ItemLocationPairing(&WaterTemple_MQ_CentralPillarChest, []{return CanUse(CanUseItem::Zora_Tunic) && CanUse(CanUseItem::Hookshot) && (CanUse(CanUseItem::Dins_Fire) && CanPlay(SongOfTime));}),
      //Trick: CanUse(CanUseItem::Zora_Tunic) && CanUse(CanUseItem::Hookshot) && ((LogicWaterMQCentralPillar && CanUse(CanUseItem::Fire_Arrows)) || (CanUse(CanUseItem::Dins_Fire) && CanPlay(SongOfTime)))
  }, {
    //Exits
    ExitPairing::Both(&WaterTemple_MQ_LoweredWaterLevels, []{return CanPlay(ZeldasLullaby);}),
  });

  Exit WaterTemple_MQ_LoweredWaterLevels = Exit("Water Temple MQ Lowered Water Levels", "Water Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&WaterTemple_MQ_CompassChest,              []{return CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Dins_Fire) || (WaterTemple_MQ_Lobby.Child() && CanUse(CanUseItem::Sticks) && HasExplosives);}),
    ItemLocationPairing(&WaterTemple_MQ_LongshotChest,             []{return CanUse(CanUseItem::Hookshot);}),
    ItemLocationPairing(&WaterTemple_MQ_GS_LizalfosHallway,        []{return CanUse(CanUseItem::Dins_Fire);}),
    ItemLocationPairing(&WaterTemple_MQ_GS_BeforeUpperWaterSwitch, []{return CanUse(CanUseItem::Longshot);}),
  }, {});

  Exit WaterTemple_MQ_DarkLinkRegion = Exit("Water Temple MQ Dark Link Region", "Water Temple", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&FairyPot, []{return true;}),
    EventPairing(&NutPot,   []{return true;}),
  }, {
    //Locations
    ItemLocationPairing(&WaterTemple_MQ_BossKeyChest, []{return (CanUse(CanUseItem::Zora_Tunic) || LogicFewerTunicRequirements) && CanUse(CanUseItem::Dins_Fire) && (LogicWaterDragonJumpDive || CanDive || CanUse(CanUseItem::Iron_Boots));}),
    ItemLocationPairing(&WaterTemple_MQ_GS_River,     []{return true;}),
  }, {
    //Exits
    ExitPairing::Both(&WaterTemple_MQ_BasementGatedAreas, []{return (CanUse(CanUseItem::Zora_Tunic) || LogicFewerTunicRequirements) && CanUse(CanUseItem::Dins_Fire) && CanUse(CanUseItem::Iron_Boots);}),
  });

  Exit WaterTemple_MQ_BasementGatedAreas = Exit("Water Temple MQ Basement Gated Areas", "Water Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&WaterTemple_MQ_FreestandingKey,        []{return HoverBoots || CanUse(CanUseItem::Scarecrow) || LogicWaterNorthBasementLedgeJump;}),
    ItemLocationPairing(&WaterTemple_MQ_GS_TripleWallTorch,     []{return CanUse(CanUseItem::Fire_Arrows) && (HoverBoots || CanUse(CanUseItem::Scarecrow));}),
    ItemLocationPairing(&WaterTemple_MQ_GS_FreestandingKeyArea, []{return SmallKeys(WaterTempleKeys, 2) && (HoverBoots || CanUse(CanUseItem::Scarecrow) || LogicWaterNorthBasementLedgeJump);}),
      //Trick: LogicWaterMQLockedGS || (SmallKeys(WaterTempleKeys, 2) && (HoverBoots || CanUse(CanUseItem::Scarecrow) || LogicWaterNorthBasementLedgeJump))
  }, {});

  Exit SpiritTemple_MQ_Lobby = Exit("Spirit Temple MQ Lobby", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&SpiritTemple_MQ_EntranceFrontLeftChest, []{return true;}),
    ItemLocationPairing(&SpiritTemple_MQ_EntranceBackLeftChest,  []{return CanBlastOrSmash && (CanUse(CanUseItem::Slingshot) || CanUse(CanUseItem::Bow));}),
    ItemLocationPairing(&SpiritTemple_MQ_EntranceBackRightChest, []{return HasBombchus || CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Hookshot) || CanUse(CanUseItem::Slingshot) || CanUse(CanUseItem::Boomerang);}),
  }, {
    //Exits
    ExitPairing::Both(&Colossus_Main,         []{return true;}),
    ExitPairing::Both(&SpiritTemple_MQ_Child, []{return IsChild;}),
    ExitPairing::Both(&SpiritTemple_MQ_Adult, []{return HasBombchus && CanUse(CanUseItem::Longshot) && CanUse(CanUseItem::Silver_Gauntlets);}),
  });

  Exit SpiritTemple_MQ_Child = Exit("Spirit Temple MQ Child", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&FairyPot, []{return FairyPot || ((Sticks || KokiriSword) && HasBombchus && Slingshot);}),
  }, {
    //Locations
    ItemLocationPairing(&SpiritTemple_MQ_ChildHammerSwitchChest, []{return SpiritTemple_MQ_Adult.Adult() && SmallKeys(SpiritTempleKeys, 7) && Hammer;}),
    ItemLocationPairing(&SpiritTemple_MQ_MapRoomEnemyChest, []{return (Sticks || KokiriSword) && HasBombchus && Slingshot && CanUse(CanUseItem::Dins_Fire);}),
    ItemLocationPairing(&SpiritTemple_MQ_MapChest, []{return Sticks || KokiriSword || Bombs;}),
    ItemLocationPairing(&SpiritTemple_MQ_SilverBlockHallwayChest, []{return HasBombchus && SmallKeys(SpiritTempleKeys, 7) && Slingshot && (CanUse(CanUseItem::Dins_Fire) || (SpiritTemple_MQ_Adult.Adult() && CanUse(CanUseItem::Fire_Arrows)));}),
      //Trick: HasBombchus && SmallKeys(SpiritTempleKeys, 7) && Slingshot && (CanUse(CanUseItem::Dins_Fire) || (SpiritTemple_MQ_Adult.Adult() && (CanUse(CanUseItem::Fire_Arrows) || (LogicSpiritMQFrozenEye && CanUse(CanUseItem::Bow) && CanPlay(SongOfTime)))))
  }, {
    //Exits
    ExitPairing::Both(&SpiritTemple_MQ_Shared, []{return HasBombchus && SmallKeys(SpiritTempleKeys, 2);}),
  });

  Exit SpiritTemple_MQ_Adult = Exit("Spirit Temple MQ Adult", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&SpiritTemple_MQ_ChildClimbSouthChest,     []{return SmallKeys(SpiritTempleKeys, 7);}),
    ItemLocationPairing(&SpiritTemple_MQ_StatueRoomLullabyChest,   []{return CanPlay(ZeldasLullaby);}),
    ItemLocationPairing(&SpiritTemple_MQ_StatueRoomInvisibleChest, []{return (LogicLensSpiritMQ || CanUse(CanUseItem::Lens_of_Truth));}),
    ItemLocationPairing(&SpiritTemple_MQ_BeamosRoomChest,          []{return SmallKeys(SpiritTempleKeys, 5);}),
    ItemLocationPairing(&SpiritTemple_MQ_ChestSwitchChest,         []{return SmallKeys(SpiritTempleKeys, 5) && CanPlay(SongOfTime);}),
    ItemLocationPairing(&SpiritTemple_MQ_BossKeyChest,             []{return SmallKeys(SpiritTempleKeys, 5) && CanPlay(SongOfTime) && MirrorShield;}),
    ItemLocationPairing(&SpiritTemple_MQ_GS_NineThronesRoomWest,   []{return SmallKeys(SpiritTempleKeys, 7);}),
    ItemLocationPairing(&SpiritTemple_MQ_GS_NineThronesRoomNorth,  []{return SmallKeys(SpiritTempleKeys, 7);}),
  }, {
    //Exits
    ExitPairing::Both(&SpiritTemple_MQ_LowerAdult,       []{return MirrorShield && CanUse(CanUseItem::Fire_Arrows);}),
      //Trick: MirrorShield && (CanUse(CanUseItem::Fire_Arrows) || (LogicSpiritMQLowerAdult && CanUse(CanUseItem::Dins_Fire) && Bow))
    ExitPairing::Both(&SpiritTemple_MQ_Shared,           []{return true;}),
    ExitPairing::Both(&SpiritTemple_MQ_BossArea,         []{return SmallKeys(SpiritTempleKeys, 6) && CanPlay(ZeldasLullaby) && Hammer;}),
    ExitPairing::Both(&SpiritTemple_MQ_MirrorShieldHand, []{return SmallKeys(SpiritTempleKeys, 5) && CanPlay(SongOfTime) && (LogicLensSpiritMQ || CanUse(CanUseItem::Lens_of_Truth));}),
  });

  Exit SpiritTemple_MQ_Shared = Exit("Spirit Temple MQ Shared", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&SpiritTemple_MQ_ChildClimbNorthChest, []{return SmallKeys(SpiritTempleKeys, 6);}),
    ItemLocationPairing(&SpiritTemple_MQ_CompassChest,         []{return (CanUse(CanUseItem::Slingshot) && SmallKeys(SpiritTempleKeys, 7)) || CanUse(CanUseItem::Bow) || (Bow && Slingshot);}),
    ItemLocationPairing(&SpiritTemple_MQ_SunBlockRoomChest,    []{return CanPlay(SongOfTime) || IsAdult;}),
      //Trick: CanPlay(SongOfTime) || LogicSpiritMQSunBlockSoT || IsAdult
    ItemLocationPairing(&SpiritTemple_MQ_GS_SunBlockRoom,      []{return IsAdult;}),
      //Trick: (LogicSpiritMQSunBlockGS && Boomerange && (CanPlay(SongOfTime) || LogicSpiritMQSunBlockSoT)) || IsAdult
   }, {
    //Exits
    ExitPairing::Both(&SpiritTemple_MQ_SilverGauntletsHand, []{return (SmallKeys(SpiritTempleKeys, 7) && (CanPlay(SongOfTime) || IsAdult)) || (SmallKeys(SpiritTempleKeys, 4) && CanPlay(SongOfTime) && (LogicLensSpiritMQ || CanUse(CanUseItem::Lens_of_Truth)));}),
      //Trick: (SmallKeys(SpiritTempleKeys, 7) && (CanPlay(SongOfTime) || LogicSpiritMQSunBlockSoT || IsAdult)) || (SmallKeys(SpiritTempleKeys, 4) && CanPlay(SongOfTime) && (LogicLensSpiritMQ || CanUse(CanUseItem::Lens_of_Truth)))
    ExitPairing::Both(&Colossus_Main,                       []{return (SmallKeys(SpiritTempleKeys, 7) && (CanPlay(SongOfTime) || IsAdult)) || (SmallKeys(SpiritTempleKeys, 4) && CanPlay(SongOfTime) && (LogicLensSpiritMQ || CanUse(CanUseItem::Lens_of_Truth)) && IsAdult);}),
      //Trick: (SmallKeys(SpiritTempleKeys, 7) && (CanPlay(SongOfTime) || LogicSpiritMQSunBlockSoT || IsAdult)) || (SmallKeys(SpiritTempleKeys, 4) && CanPlay(SongOfTime) && (LogicLensSpiritMQ || CanUse(CanUseItem::Lens_of_Truth)) && IsAdult)
  });

  Exit SpiritTemple_MQ_LowerAdult = Exit("Spirit Temple MQ Lower Adult", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&SpiritTemple_MQ_LeeverRoomChest,         []{return true;}),
    ItemLocationPairing(&SpiritTemple_MQ_SymphonyRoomChest,       []{return SmallKeys(SpiritTempleKeys, 7) && Hammer && Ocarina && SongOfTime && EponasSong && SunsSong && SongOfStorms && ZeldasLullaby;}),
    ItemLocationPairing(&SpiritTemple_MQ_EntranceFrontRightChest, []{return Hammer;}),
    ItemLocationPairing(&SpiritTemple_MQ_GS_LeeverRoom,           []{return true;}),
    ItemLocationPairing(&SpiritTemple_MQ_GS_SymphonyRoom,         []{return SmallKeys(SpiritTempleKeys, 7) && Hammer && Ocarina && SongOfTime && EponasSong && SunsSong && SongOfStorms && ZeldasLullaby;}),
  }, {});

  Exit SpiritTemple_MQ_BossArea = Exit("Spirit Temple MQ Boss Area", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&SpiritTempleClear, []{return SpiritTempleClear || (MirrorShield && BossKeySpiritTemple);})
  }, {
    //Locations
    ItemLocationPairing(&SpiritTemple_MQ_MirrorPuzzleInvisibleChest, []{return LogicLensSpiritMQ || CanUse(CanUseItem::Lens_of_Truth);}),
    ItemLocationPairing(&SpiritTemple_TwinrovaHeart,                 []{return MirrorShield && BossKeySpiritTemple;}),
    ItemLocationPairing(&Twinrova,                                   []{return MirrorShield && BossKeySpiritTemple;}),
  }, {});

  Exit SpiritTemple_MQ_MirrorShieldHand = Exit("Spirit Temple MQ Mirror Shield Hand", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&SpiritTemple_MirrorShieldChest, []{return true;}),
  }, {});

  Exit SpiritTemple_MQ_SilverGauntletsHand = Exit("Spirit Temple MQ Silver Gauntlets Hand", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&SpiritTemple_SilverGauntletsChest, []{return true;}),
  }, {});

  Exit ShadowTemple_MQ_Entryway = Exit("Shadow Temple MQ Entryway", "Shadow Temple", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
    //Exits
    ExitPairing::Both(&GY_WarpPadRegion,          []{return true;}),
    ExitPairing::Both(&ShadowTemple_MQ_Beginning, []{return (LogicLensShadowMQ || CanUse(CanUseItem::Lens_of_Truth)) && (CanUse(CanUseItem::Hover_Boots) || CanUse(CanUseItem::Hookshot));}),
  });

  Exit ShadowTemple_MQ_Beginning = Exit("Shadow Temple MQ Beginning", "Shadow Temple", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
    //Exits
    ExitPairing::Both(&ShadowTemple_MQ_Entryway,     []{return true;}),
    ExitPairing::Both(&ShadowTemple_MQ_FirstBeamos,  []{return CanUse(CanUseItem::Fire_Arrows) || HoverBoots;}),
      //Trick: CanUse(CanUseItem::Fire_Arrows) || HoverBoots || (LogicShadowMQGap && CanUse(CanUseItem::Longshot))
    ExitPairing::Both(&ShadowTemple_MQ_DeadHandArea, []{return HasExplosives && SmallKeys(ShadowTempleKeys, 6);}),
  });

  Exit ShadowTemple_MQ_DeadHandArea = Exit("Shadow Temple MQ Dead Hand Area", "Shadow Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&ShadowTemple_MQ_CompassChest,    []{return true;}),
    ItemLocationPairing(&ShadowTemple_MQ_HoverBootsChest, []{return CanPlay(SongOfTime) && Bow;}),
  }, {});

  Exit ShadowTemple_MQ_FirstBeamos = Exit("Shadow Temple MQ First Beamos", "Shadow Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&ShadowTemple_MQ_MapChest,               []{return true;}),
    ItemLocationPairing(&ShadowTemple_MQ_EarlyGibdosChest,       []{return true;}),
    ItemLocationPairing(&ShadowTemple_MQ_NearShipInvisibleChest, []{return true;}),
  }, {
    //Exits
    ExitPairing::Both(&ShadowTemple_MQ_UpperHugePit, []{return HasExplosives && SmallKeys(ShadowTempleKeys, 2);}),
  });

  Exit ShadowTemple_MQ_UpperHugePit = Exit("Shadow Temple MQ Upper Huge Pit", "Shadow Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&ShadowTemple_MQ_InvisibleBladesVisibleChest,   []{return CanPlay(SongOfTime);}),
      //Trick: CanPlay(SongOfTime) || (LogicShadowMQInvisibleBlades && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO))
    ItemLocationPairing(&ShadowTemple_MQ_InvisibleBladesInvisibleChest, []{return CanPlay(SongOfTime);}),
      //Trick: CanPlay(SongOfTime) || (LogicShadowMQInvisibleBlades && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO))
  }, {
    //Exits
    ExitPairing::Both(&ShadowTemple_MQ_LowerHugePit, []{return HasFireSource;}),
      //Trick: HasFireSource || LogicShadowMQHugePit
  });

  Exit ShadowTemple_MQ_LowerHugePit = Exit("Shadow Temple MQ Lower Huge Pit", "Shadow Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&ShadowTemple_MQ_BeamosSilverRupeesChest,  []{return CanUse(CanUseItem::Longshot);}),
    ItemLocationPairing(&ShadowTemple_MQ_FallingSpikesLowerChest,  []{return true;}),
    ItemLocationPairing(&ShadowTemple_MQ_FallingSpikesUpperChest,  []{return (LogicShadowUmbrella && HoverBoots) || GoronBracelet;}),
    ItemLocationPairing(&ShadowTemple_MQ_FallingSpikesSwitchChest, []{return (LogicShadowUmbrella && HoverBoots) || GoronBracelet;}),
    ItemLocationPairing(&ShadowTemple_MQ_InvisibleSpikesChest,     []{return HoverBoots && SmallKeys(ShadowTempleKeys, 3) && (LogicLensShadowMQBack || CanUse(CanUseItem::Lens_of_Truth));}),
    ItemLocationPairing(&ShadowTemple_MQ_StalfosRoomChest,         []{return HoverBoots && SmallKeys(ShadowTempleKeys, 3) && Hookshot && (LogicLensShadowMQBack || CanUse(CanUseItem::Lens_of_Truth));}),
    ItemLocationPairing(&ShadowTemple_MQ_GS_FallingSpikesRoom,     []{return Hookshot;}),
  }, {
    //Exits
    ExitPairing::Both(&ShadowTemple_MQ_WindTunnel, []{return HoverBoots && (LogicLensShadowMQBack || CanUse(CanUseItem::Lens_of_Truth)) && Hookshot && SmallKeys(ShadowTempleKeys, 4);}),
  });

  Exit ShadowTemple_MQ_WindTunnel = Exit("Shadow Temple MQ Wind Tunnel", "Shadow Temple", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&NutPot, []{return true;}),
  }, {
    //Locations
    ItemLocationPairing(&ShadowTemple_MQ_WindHintChest,        []{return true;}),
    ItemLocationPairing(&ShadowTemple_MQ_AfterWindEnemyChest,  []{return true;}),
    ItemLocationPairing(&ShadowTemple_MQ_AfterWindHiddenChest, []{return true;}),
    ItemLocationPairing(&ShadowTemple_MQ_GS_WindHintRoom,      []{return true;}),
    ItemLocationPairing(&ShadowTemple_MQ_GS_AfterWind,         []{return true;}),
  }, {
    //Exits
    ExitPairing::Both(&ShadowTemple_MQ_BeyondBoat, []{return CanPlay(ZeldasLullaby) && SmallKeys(ShadowTempleKeys, 5);}),
  });

  Exit ShadowTemple_MQ_BeyondBoat = Exit("Shadow Temple MQ Beyond Boat", "Shadow Temple", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&ShadowTempleClear, []{return ShadowTempleClear || ((Bow || (LogicShadowStatue && HasBombchus)) && BossKeyShadowTemple);})
  }, {
    //Locations
    ItemLocationPairing(&ShadowTemple_BongoBongoHeart, []{return (Bow || (LogicShadowStatue && HasBombchus)) && BossKeyShadowTemple;}),
    ItemLocationPairing(&BongoBongo,                   []{return (Bow || (LogicShadowStatue && HasBombchus)) && BossKeyShadowTemple;}),
    ItemLocationPairing(&ShadowTemple_MQ_GS_AfterShip, []{return true;}),
    ItemLocationPairing(&ShadowTemple_MQ_GS_NearBoss,  []{return Bow || (LogicShadowStatue && HasBombchus);}),
  }, {
    //Exits
    ExitPairing::Both(&ShadowTemple_MQ_InvisibleMaze, []{return Bow && CanPlay(SongOfTime) && CanUse(CanUseItem::Longshot);}),
  });

  Exit ShadowTemple_MQ_InvisibleMaze = Exit("Shadow Temple MQ Invisible Maze", "Shadow Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&ShadowTemple_MQ_SpikeWallsLeftChest, []{return CanUse(CanUseItem::Dins_Fire) && SmallKeys(ShadowTempleKeys, 6);}),
    ItemLocationPairing(&ShadowTemple_MQ_BossKeyChest,        []{return CanUse(CanUseItem::Dins_Fire) && SmallKeys(ShadowTempleKeys, 6);}),
    ItemLocationPairing(&ShadowTemple_MQ_BombFlowerChest,     []{return true;}),
    ItemLocationPairing(&ShadowTemple_MQ_FreestandingKey,     []{return true;}),
  }, {});

  Exit BottomOfTheWell_MQ = Exit("Bottom of the Well MQ", "Bottom of the Well", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
    //Exits
    ExitPairing::Both(&Kak_Main,                     []{return true;}),
    ExitPairing::Both(&BottomOfTheWell_MQ_Perimeter, []{return IsChild;}),
  });

  Exit BottomOfTheWell_MQ_Perimeter = Exit("Bottom of the Well MQ Perimeter", "Bottom of the Well", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    //EventPairing(&WallFairy, []{return WallFairy || Slingshot;}),
  }, {
    //Locations
    ItemLocationPairing(&BottomOfTheWell_MQ_CompassChest,            []{return KokiriSword || (Sticks && LogicChildDeadhand);}),
    ItemLocationPairing(&BottomOfTheWell_MQ_DeadHandFreestandingKey, []{return HasExplosives;}),
      //Trick: HasExplosives || (LogicBotWMQDeadHandKey && Boomerang)
    ItemLocationPairing(&BottomOfTheWell_MQ_GS_Basement,             []{return CanChildAttack;}),
    ItemLocationPairing(&BottomOfTheWell_MQ_GS_CoffinRoom,           []{return CanChildAttack && SmallKeys(BottomOfTheWellKeys, 2);}),
  }, {
    //Exits
    ExitPairing::Both(&BottomOfTheWell_MQ,        []{return true;}),
    ExitPairing::Both(&BottomOfTheWell_MQ_Middle, []{return CanPlay(ZeldasLullaby);}),
      //Trick: CanPlay(ZeldasLullaby) || (LogicBotWMQPits && HasExplosives)
  });

  Exit BottomOfTheWell_MQ_Middle = Exit("Bottom of the Well MQ Middle", "Bottom of the Well", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&BottomOfTheWell_MQ_MapChest,                     []{return true;}),
    ItemLocationPairing(&BottomOfTheWell_MQ_LensOfTruthChest,             []{return HasExplosives && SmallKeys(BottomOfTheWellKeys, 2);}),
    ItemLocationPairing(&BottomOfTheWell_MQ_EastInnerRoomFreestandingKey, []{return true;}),
    ItemLocationPairing(&BottomOfTheWell_MQ_GS_WestInnerRoom,             []{return CanChildAttack && HasExplosives;}),
      //Trick: CanChildAttack && (LogicBotWMQPits || HasExplosives)
  }, {
    //Exits
    ExitPairing::Both(&BottomOfTheWell_MQ_Perimeter, []{return true;}),
  });

  Exit IceCavern_MQ_Beginning = Exit("Ice Cavern MQ Beginning", "Ice Cavern", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&FairyPot, []{return true;}),
  }, {}, {
    //Exits
    ExitPairing::Both(&ZF_Main,                      []{return true;}),
    ExitPairing::Both(&IceCavern_MQ_MapRoom,         []{return IsAdult || CanUse(CanUseItem::Dins_Fire) || (HasExplosives && (CanUse(CanUseItem::Sticks) || CanUse(CanUseItem::Slingshot) || KokiriSword));}),
    ExitPairing::Both(&IceCavern_MQ_CompassRoom,     []{return IsAdult && BlueFire;}),
    ExitPairing::Both(&IceCavern_MQ_IronBootsRegion, []{return BlueFire;}),
  });

  Exit IceCavern_MQ_MapRoom = Exit("Ice Cavern MQ Map Room", "Ice Cavern", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&BlueFireAccess,  []{return BlueFireAccess || HasBottle;}),
  }, {
    //Locations
    ItemLocationPairing(&IceCavern_MQ_MapChest, []{return BlueFire && (IsAdult || CanUse(CanUseItem::Sticks) || KokiriSword || CanUseProjectile);}),
  }, {});

  Exit IceCavern_MQ_IronBootsRegion = Exit("Ice Cavern MQ Iron Boots Region", "Ice Cavern", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&IceCavern_MQ_IronBootsChest, []{return IsAdult;}),
    ItemLocationPairing(&SheikInIceCavern,            []{return IsAdult;}),
    ItemLocationPairing(&IceCavern_MQ_GS_IceBlock,    []{return IsAdult || CanChildAttack;}),
    ItemLocationPairing(&IceCavern_MQ_GS_Scarecrow,   []{return CanUse(CanUseItem::Scarecrow) || (HoverBoots && CanUse(CanUseItem::Longshot));}),
      //Tricks: CanUse(CanUseItem::Scarecrow) || (HoverBoots && CanUse(CanUseItem::Longshot)) || (LogicIceMQScarecrow && IsAdult)
  }, {});

  Exit IceCavern_MQ_CompassRoom = Exit("Ice Cavern MQ Compass Room", "Ice Cavern", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&IceCavern_MQ_CompassChest,    []{return true;}),
    ItemLocationPairing(&IceCavern_MQ_FreestandingPoH, []{return HasExplosives;}),
    ItemLocationPairing(&IceCavern_MQ_GS_RedIce,       []{return CanPlay(SongOfTime);}),
      //Trick: CanPlay(SongOfTime) || LogicIceMQRedIceGS
  }, {});

  Exit GerudoTrainingGrounds_MQ_Lobby = Exit("Gerudo Training Grounds MQ Lobby", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&GerudoTrainingGrounds_MQ_LobbyLeftChest,      []{return true;}),
    ItemLocationPairing(&GerudoTrainingGrounds_MQ_LobbyRightChest,     []{return true;}),
    ItemLocationPairing(&GerudoTrainingGrounds_MQ_HiddenCeilingChest,  []{return LogicLensGtgMQ || CanUse(CanUseItem::Lens_of_Truth);}),
    ItemLocationPairing(&GerudoTrainingGrounds_MQ_MazePathFirstChest,  []{return true;}),
    ItemLocationPairing(&GerudoTrainingGrounds_MQ_MazePathSecondChest, []{return true;}),
    ItemLocationPairing(&GerudoTrainingGrounds_MQ_MazePathThirdChest,  []{return SmallKeys(GerudoTrainingGroundsKeys, 1);}),
  }, {
    //Exits
    ExitPairing::Both(&GF_Main,                            []{return true;}),
    ExitPairing::Both(&GerudoTrainingGrounds_MQ_LeftSide,  []{return HasFireSource;}),
    ExitPairing::Both(&GerudoTrainingGrounds_MQ_RightSide, []{return CanUse(CanUseItem::Bow) || CanUse(CanUseItem::Slingshot);}),
  });

  Exit GerudoTrainingGrounds_MQ_RightSide = Exit("Gerudo Training Grounds MQ Right Side", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    //EventPairing(&WallFairy, []{return WallFairy || CanUse(CanUseItem::Bow);}),
  }, {
    //Locations
    ItemLocationPairing(&GerudoTrainingGrounds_MQ_DinolfosChest, []{return IsAdult;}),
  }, {
    //Exits
    ExitPairing::Both(&GerudoTrainingGrounds_MQ_Underwater, []{return (Bow || CanUse(CanUseItem::Longshot)) && CanUse(CanUseItem::Hover_Boots);}),
  });

  Exit GerudoTrainingGrounds_MQ_Underwater = Exit("Gerudo Training Grounds MQ Underwater", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&GerudoTrainingGrounds_MQ_UnderwaterSilverRupeeChest, []{return HasFireSource && CanUse(CanUseItem::Iron_Boots) && (LogicFewerTunicRequirements || CanUse(CanUseItem::Zora_Tunic)) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO);}),
  }, {});

  Exit GerudoTrainingGrounds_MQ_LeftSide = Exit("Gerudo Training Grounds MQ Left Side", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&GerudoTrainingGrounds_MQ_FirstIronKnuckleChest, []{return IsAdult || KokiriSword || HasExplosives;}),
  }, {
    //Exits
    ExitPairing::Both(&GerudoTrainingGrounds_MQ_StalfosRoom, []{return CanUse(CanUseItem::Longshot);}),
      //Trick: CanUse(CanUseItem::Longshot) || LogicGtgMQWithoutHookshot || (LogicGtgMQWithHookshot && CanUse(CanUseItem::Hookshot))
  });

  Exit GerudoTrainingGrounds_MQ_StalfosRoom = Exit("Gerudo Training Grounds MQ Stalfos Room", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&BlueFireAccess,  []{return BlueFireAccess || HasBottle;}),
  }, {
    //Locations
    ItemLocationPairing(&GerudoTrainingGrounds_MQ_BeforeHeavyBlockChest, []{return IsAdult;}),
    ItemLocationPairing(&GerudoTrainingGrounds_MQ_HeavyBlockChest,       []{return CanUse(CanUseItem::Silver_Gauntlets);}),
  }, {
    //Exits
    ExitPairing::Both(&GerudoTrainingGrounds_MQ_BackAreas, []{return IsAdult && (LogicLensGtgMQ || CanUse(CanUseItem::Lens_of_Truth)) && BlueFire && CanPlay(SongOfTime);}),
      //Trick: IsAdult && (LogicLensGtgMQ || CanUse(CanUseItem::Lens_of_Truth)) && BlueFire && (CanPlay(SongOfTime) || (LogicGtgFakeWall && CanUse(CanUseItem::Hover_Boots)))
  });

  Exit GerudoTrainingGrounds_MQ_BackAreas = Exit("Gerudo Training Grounds MQ Back Areas", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&GerudoTrainingGrounds_MQ_EyeStatueChest,         []{return Bow;}),
    ItemLocationPairing(&GerudoTrainingGrounds_MQ_SecondIronKnuckleChest, []{return true;}),
    ItemLocationPairing(&GerudoTrainingGrounds_MQ_FlameCircleChest,       []{return CanUse(CanUseItem::Hookshot) || Bow || HasExplosives;}),
  }, {
    //Exits
    ExitPairing::Both(&GerudoTrainingGrounds_MQ_CentralMazeRight, []{return Hammer;}),
    ExitPairing::Both(&GerudoTrainingGrounds_MQ_RightSide,        []{return CanUse(CanUseItem::Longshot);}),
  });

  Exit GerudoTrainingGrounds_MQ_CentralMazeRight = Exit("Gerudo Training Grounds MQ Central Maze Right", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&GerudoTrainingGrounds_MQ_MazeRightCentralChest, []{return true;}),
    ItemLocationPairing(&GerudoTrainingGrounds_MQ_MazeRightSideChest,    []{return true;}),
    ItemLocationPairing(&GerudoTrainingGrounds_MQ_IceArrowsChest,        []{return SmallKeys(GerudoTrainingGroundsKeys, 3);}),
  }, {
    //Exits
    ExitPairing::Both(&GerudoTrainingGrounds_MQ_Underwater, []{return CanUse(CanUseItem::Longshot) || (CanUse(CanUseItem::Hookshot) && Bow);}),
    ExitPairing::Both(&GerudoTrainingGrounds_MQ_RightSide,  []{return CanUse(CanUseItem::Hookshot);}),
  });

  Exit GanonsCastle_MQ_Lobby = Exit("Ganon's Castle MQ Lobby", "Ganons Castle", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
    //Exits
    ExitPairing::Both(&OGC_Grounds,                 []{return true;}),
    ExitPairing::Both(&GanonsCastle_MQ_ForestTrial, []{return true;}),
    ExitPairing::Both(&GanonsCastle_MQ_FireTrial,   []{return true;}),
    ExitPairing::Both(&GanonsCastle_MQ_WaterTrial,  []{return true;}),
    ExitPairing::Both(&GanonsCastle_MQ_ShadowTrial, []{return true;}),
    ExitPairing::Both(&GanonsCastle_MQ_SpiritTrial, []{return true;}),
    ExitPairing::Both(&GanonsCastle_MQ_LightTrial,  []{return CanUse(CanUseItem::Golden_Gauntlets);}),
    ExitPairing::Both(&GanonsCastle_Tower,          []{return (ForestTrialClear || ForestTrialSkip) &&
                                                              (FireTrialClear   || FireTrialSkip)   &&
                                                              (WaterTrialClear  || WaterTrialSkip)  &&
                                                              (ShadowTrialClear || ShadowTrialSkip) &&
                                                              (SpiritTrialClear || SpiritTrialSkip) &&
                                                              (LightTrialClear  || LightTrialSkip);}),
    ExitPairing::Both(&GanonsCastle_MQ_DekuScrubs,  []{return LogicLensCastleMQ || CanUse(CanUseItem::Lens_of_Truth);}),
  });

  Exit GanonsCastle_MQ_DekuScrubs = Exit("Ganon's Castle MQ Deku Scrubs", "Ganon's Castle", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&FreeFairies, []{return true;}),
  }, {
    //Locations
    ItemLocationPairing(&GanonsCastle_MQ_DekuScrubCenterLeft,  []{return true;}),
    ItemLocationPairing(&GanonsCastle_MQ_DekuScrubCenter,      []{return true;}),
    ItemLocationPairing(&GanonsCastle_MQ_DekuScrubCenterRight, []{return true;}),
    ItemLocationPairing(&GanonsCastle_MQ_DekuScrubLeft,        []{return true;}),
    ItemLocationPairing(&GanonsCastle_MQ_DekuScrubRight,       []{return true;}),
  }, {});

  Exit GanonsCastle_MQ_ForestTrial = Exit("Ganon's Castle MQ Forest Trial", "Ganons Castle", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&ForestTrialClear, []{return CanUse(CanUseItem::Light_Arrows) && CanPlay(SongOfTime);}),
  }, {
    //Locations
    ItemLocationPairing(&GanonsCastle_MQ_ForestTrialEyeSwitchChest,       []{return Bow;}),
    ItemLocationPairing(&GanonsCastle_MQ_ForestTrialFrozenEyeSwitchChest, []{return HasFireSource;}),
    ItemLocationPairing(&GanonsCastle_MQ_ForestTrialFreestandingKey,      []{return Hookshot;}),
  }, {});

  Exit GanonsCastle_MQ_FireTrial = Exit("Ganon's Castle MQ Fire Trial", "Ganons Castle", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&FireTrialClear, []{return CanUse(CanUseItem::Goron_Tunic) && CanUse(CanUseItem::Golden_Gauntlets) && CanUse(CanUseItem::Light_Arrows) && (CanUse(CanUseItem::Longshot) || HoverBoots);}),
      //Trick: CanUse(CanUseItem::Goron_Tunic) && CanUse(CanUseItem::Golden_Gauntlets) && CanUse(CanUseItem::Light_Arrows) && (CanUse(CanUseItem::Longshot) || HoverBoots || (LogicFireTrialMQ && CanUse(CanUseItem::Hookshot)))
  }, {}, {});

  Exit GanonsCastle_MQ_WaterTrial = Exit("Ganon's Castle MQ Water Trial", "Ganons Castle", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&WaterTrialClear, []{return BlueFire && CanUse(CanUseItem::Light_Arrows) && SmallKeys(GanonsCastleKeys, 3);}),
    EventPairing(&BlueFireAccess,  []{return BlueFireAccess || HasBottle;}),
  }, {
    //Locations
    ItemLocationPairing(&GanonsCastle_MQ_WaterTrialChest, []{return BlueFire;}),
  }, {});

  Exit GanonsCastle_MQ_ShadowTrial = Exit("Ganon's Castle MQ Shadow Trial", "Ganons Castle", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&ShadowTrialClear, []{return CanUse(CanUseItem::Light_Arrows) && (LogicLensCastleMQ || CanUse(CanUseItem::Lens_of_Truth)) && (HoverBoots || (Hookshot && HasFireSource));}),
      //Trick: CanUse(CanUseItem::Light_Arrows) && (LogicLensCastleMQ || CanUse(CanUseItem::Lens_of_Truth)) && (HoverBoots || (Hookshot && (HasFireSource || LogicShadowTrialMQ)))
  }, {
    //Locations
    ItemLocationPairing(&GanonsCastle_MQ_ShadowTrialBombFlowerChest, []{return (Bow && (Hookshot || HoverBoots)) || (HoverBoots && (LogicLensCastleMQ || CanUse(CanUseItem::Lens_of_Truth)) && (HasExplosives || GoronBracelet || CanUse(CanUseItem::Dins_Fire)));}),
    ItemLocationPairing(&GanonsCastle_MQ_ShadowTrialEyeSwitchChest,  []{return Bow && (LogicLensCastleMQ || CanUse(CanUseItem::Lens_of_Truth)) && (HoverBoots || (Hookshot && HasFireSource));}),
      //Trick: Bow && (LogicLensCastleMQ || CanUse(CanUseItem::Lens_of_Truth)) && (HoverBoots || (Hookshot && (HasFireSource || LogicShadowTrialMQ)))
  }, {});

  Exit GanonsCastle_MQ_SpiritTrial = Exit("Ganon's Castle MQ Spirit Castle", "Ganons Castle", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&SpiritTrialClear, []{return CanUse(CanUseItem::Light_Arrows) && Hammer && HasBombchus && FireArrows && MirrorShield;}),
    EventPairing(&NutPot,           []{return NutPot || (Hammer && HasBombchus && CanUse(CanUseItem::Fire_Arrows) && MirrorShield);}),
  }, {
    //Locations
    ItemLocationPairing(&GanonsCastle_MQ_SpiritTrialFirstChest,           []{return Bow && Hammer;}),
    ItemLocationPairing(&GanonsCastle_MQ_SpiritTrialInvisibleChest,       []{return Bow && Hammer && HasBombchus && (LogicLensCastleMQ || CanUse(CanUseItem::Lens_of_Truth));}),
    ItemLocationPairing(&GanonsCastle_MQ_SpiritTrialSunFrontLeftChest,    []{return Hammer && HasBombchus && CanUse(CanUseItem::Fire_Arrows) && MirrorShield;}),
    ItemLocationPairing(&GanonsCastle_MQ_SpiritTrialSunBackLeftChest,     []{return Hammer && HasBombchus && CanUse(CanUseItem::Fire_Arrows) && MirrorShield;}),
    ItemLocationPairing(&GanonsCastle_MQ_SpiritTrialGoldenGauntletsChest, []{return Hammer && HasBombchus && CanUse(CanUseItem::Fire_Arrows) && MirrorShield;}),
    ItemLocationPairing(&GanonsCastle_MQ_SpiritTrialSunBackRightChest,    []{return Hammer && HasBombchus && CanUse(CanUseItem::Fire_Arrows) && MirrorShield;}),
  }, {});

  Exit GanonsCastle_MQ_LightTrial = Exit("Ganon's Castle MQ Light Trial", "Ganons Castle", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&LightTrialClear, []{return CanUse(CanUseItem::Light_Arrows) && SmallKeys(GanonsCastleKeys, 3) && (LogicLensCastleMQ || CanUse(CanUseItem::Lens_of_Truth)) && Hookshot;}),
      //Trick: CanUse(CanUseItem::Light_Arrows) && SmallKeys(GanonsCastleKeys, 3) && (LogicLensCastleMQ || CanUse(CanUseItem::Lens_of_Truth)) && (Hookshot || LogicLightTrialMQ)
  }, {
    //Locations
    ItemLocationPairing(&GanonsCastle_MQ_LightTrialLullabyChest, []{return CanPlay(ZeldasLullaby);}),
  }, {});

  /*
  //Events
}, {
  //Locations
}, {
  //Exits
*/

  std::array<Exit *, 289> allExits = {

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
    &DekuTree_MQ_BasementWaterRoom,
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
          ItemLocation* location = locPair.GetLocation();
          location->ResetVariables();
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
}
