#include "location_access.hpp"
#include "settings.hpp"
#include "logic.hpp"
#include "item_location.hpp"
#include "item_list.hpp"
#include <unistd.h>
#include <vector>

using namespace Logic;
using namespace Settings;

bool DAY_NIGHT_CYCLE    = true;
bool NO_DAY_NIGHT_CYCLE = false;

//generic grotto event list
std::vector<EventPairing> grottoEvents = {
  EventPairing(&GossipStoneFairy, []{return GossipStoneFairy || CanSummonGossipFairy;}),
  EventPairing(&ButterflyFairy,   []{return ButterflyFairy   || (CanUse("Sticks"));}),
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
                  ItemLocationPairing(&KF_GS_KnowItAllHouse, []{return IsChild && CanChildAttack && AtNight && (HasNightStart || CanLeaveForest || CanPlay(SunsSong));}),
                  ItemLocationPairing(&KF_GS_BeanPatch,      []{return CanPlantBugs && CanChildAttack;}),
                  ItemLocationPairing(&KF_GS_HouseOfTwins,   []{return IsAdult && AtNight && CanUse("Hookshot");}),
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
                  EventPairing(&DekuBabaNuts,   []{return DekuBabaNuts   || ((IsAdult && !ShuffleDungeonEntrances) || KokiriSword || Slingshot || Sticks || HasExplosives || CanUse("Dins Fire"));}),
                }, {
                  //Locations
                  // ItemLocationPairing(&KF_DekuTreeGossipStoneLeft,  []{return true;}),
                  // ItemLocationPairing(&KF_DekuTreeGossipStoneRight, []{return true;})
                }, {
                  //Exits
                  ExitPairing::Both(&DekuTree_Lobby, []{return IsChild || (ShuffleDungeonEntrances && ShowedMidoSwordAndShield);}),
                  ExitPairing::Both(&KF_Main,        []{return true;}),
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
                  ItemLocationPairing(&LW_TargetInWoods,          []{return CanUse("Slingshot");}),
                  ItemLocationPairing(&LW_DekuScrubNearBridge,    []{return IsChild && CanStunDeku;}),
                  ItemLocationPairing(&LW_GS_BeanPatchNearBridge, []{return CanPlantBugs && CanChildAttack;}),
                  //LW Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&LW_ForestExit,          []{return true;}),
                  ExitPairing::Both(&GC_WoodsWarp,           []{return true;}),
                  ExitPairing::Both(&LW_Bridge,              []{return IsAdult && (CanUse("Hover Boots") || CanUse("Longshot") || LW_Main.CanPlantBean());}),
                  ExitPairing::Both(&ZR_Main,                []{return CanLeaveForest && (CanDive || CanUse("Iron Boots"));}),
                  ExitPairing::Both(&LW_BeyondMido,          []{return IsChild || CanPlay(SariasSong);}),
                  ExitPairing::Both(&LW_NearShortcutsGrotto, []{return CanBlastOrSmash;})
  });

  Exit LW_BeyondMido = Exit("LW Beyond Mido", "Lost Woods", "Lost Woods", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&ButterflyFairy, []{return ButterflyFairy || CanUse("Sticks");}),
                }, {
                  //Locations
                  ItemLocationPairing(&LW_DekuScrubNearDekuTheaterRight, []{return IsChild && CanStunDeku;}),
                  ItemLocationPairing(&LW_DekuScrubNearDekuTheaterLeft,  []{return IsChild && CanStunDeku;}),
                  ItemLocationPairing(&LW_GS_AboveTheater,               []{return IsAdult && AtNight && (LW_BeyondMido.CanPlantBean() || (LogicLostWoodsGSBean && CanUse("Hookshot") && (CanUse("Longshot") || CanUse("Bow") || HasBombchus || CanUse("Dins Fire"))));}),
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
                  ExitPairing::Both(&SFM_Main,         []{return IsAdult || Slingshot || Sticks || KokiriSword || CanUse("Dins Fire");}),
                  ExitPairing::Both(&SFM_WolfosGrotto, []{return CanOpenBombGrotto;}),
  });

  Exit SFM_Main = Exit("Sacred Forest Meadow", "Sacred Forest Meadow", "Sacred Forest Meadow", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GossipStoneFairy, []{return GossipStoneFairy || CanSummonGossipFairyWithoutSuns;})
                }, {
                  //Locations
                  ItemLocationPairing(&SongFromSaria, []{return IsChild && ZeldasLetter;}),
                  ItemLocationPairing(&SheikInForest, []{return IsAdult;}),
                  ItemLocationPairing(&SFM_GS,        []{return CanUse("Hookshot") && AtNight;}),
                  //SFM Maze Gossip Stone (Lower)
                  //SFM Maze Gossip Stone (Upper)
                  //SFM Saria Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&SFM_Entryway,       []{return true;}),
                  ExitPairing::Both(&ForestTemple_Lobby, []{return CanUse("Hookshot");}),
                  ExitPairing::Both(&SFM_FairyGrotto,    []{return true;}),
                  ExitPairing::Both(&SFM_StormsGrotto,   []{return CanOpenStormGrotto;}),
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
                  ItemLocationPairing(&SFM_WolfosGrottoChest, []{return IsAdult || Slingshot || Sticks || KokiriSword || CanUse("Dins Fire");})
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
                  ExitPairing::Both(&LW_Main, []{return CanUse("Longshot");})
  });

  Exit HF_Main = Exit("Hyrule Field", "Hyrule Field", "Hyrule Field", DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&BigPoeKill, []{return CanUse("Bow") && CanRideEpona && HasBottle;}),
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
                  ExitPairing::Both(&HF_CowGrotto,         []{return (CanUse("Hammer") || IsChild) && CanOpenBombGrotto;}),
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
                  ItemLocationPairing(&HF_TektiteGrottoFreestandingPoH, []{return ProgressiveScale >= 2 || CanUse("Iron Boots");}),
                }, {
                  //Exits
                  ExitPairing::Both(&HF_Main, []{return true;}),
  });

  Exit LH_Main = Exit("Lake Hylia", "Lake Hylia", "Lake Hylia", DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GossipStoneFairy, []{return GossipStoneFairy || CanSummonGossipFairy;}),
                  EventPairing(&BeanPlantFairy,   []{return BeanPlantFairy   || (LH_Main.CanPlantBean() && CanPlay(SongOfStorms));}),
                  EventPairing(&ButterflyFairy,   []{return ButterflyFairy   || CanUse("Sticks");}),
                  EventPairing(&BugShrub,         []{return BugShrub         || (IsChild && CanCutShrubs);}),
                  EventPairing(&ScarecrowSong,    []{return ScarecrowSong    || (Ocarina && LH_Main.BothAges());}),
                }, {
                  //Locations
                  ItemLocationPairing(&LH_UnderwaterItem,  []{return IsChild && CanDive;}),
                  ItemLocationPairing(&LH_Sun,             []{return IsAdult && (CanUse("Distant Scarecrow") || WaterTempleClear) && CanUse("Bow");}),
                  ItemLocationPairing(&LH_FreestandingPoH, []{return IsAdult && (CanUse("Scarecrow") || LH_Main.CanPlantBean());}),
                  ItemLocationPairing(&LH_GS_BeanPatch,    []{return CanPlantBugs && CanChildAttack;}),
                  ItemLocationPairing(&LH_GS_LabWall,      []{return IsChild && (Boomerang || (LogicLabWallGS && (Sticks || KokiriSword))) && AtNight;}),
                  ItemLocationPairing(&LH_GS_SmallIsland,  []{return IsChild && CanChildAttack && AtNight;}),
                  ItemLocationPairing(&LH_GS_Tree,         []{return CanUse("Longshot") && AtNight;}),
                  //LH Gossip Stone (Southeast)
                  //LH Gossip Stone (Southwest)
                }, {
                  //Exits
                  ExitPairing::Both(&HF_Main,           []{return true;}),
                  ExitPairing::Both(&ZD_Main,           []{return IsChild && CanDive;}),
                  ExitPairing::Both(&LH_OwlFlight,      []{return IsChild;}),
                  ExitPairing::Both(&LH_Lab,            []{return true;}),
                  ExitPairing::Both(&LH_FishingHole,    []{return IsChild || CanUse("Scarecrow") || LH_Main.CanPlantBean() || WaterTempleClear;}),
                  ExitPairing::Both(&WaterTemple_Lobby, []{return CanUse("Hookshot") && (CanUse("Iron Boots") || ((CanUse("Longshot")) && ProgressiveScale >= 2));}),
                  ExitPairing::Both(&LH_Grotto,         []{return true;})
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
                  ItemLocationPairing(&LH_LabDive,     []{return ProgressiveScale >= 2 || (LogicLabDiving && IronBoots && CanUse("Hookshot"));}),
                  ItemLocationPairing(&LH_GS_LabCrate, []{return IronBoots && CanUse("Hookshot");}),
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
                  ItemLocationPairing(&GV_GS_SmallBridge, []{return CanUse("Boomerang") && AtNight;}),
                }, {
                  //Exits
                  ExitPairing::Both(&HF_Main,          []{return true;}),
                  ExitPairing::Both(&GV_Stream,        []{return true;}),
                  ExitPairing::Both(&GV_CrateLedge,    []{return IsChild || CanUse("Longshot");}),
                  ExitPairing::Both(&GV_OctorokGrotto, []{return CanUse("Silver Gauntlets");}),
                  ExitPairing::Both(&GV_FortressSide,  []{return IsAdult && (CanRideEpona || CanUse("Longshot") || GerudoFortress.Is(GERUDOFORTRESS_OPEN) || CarpenterRescue);})
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
                  ItemLocationPairing(&GV_Chest,         []{return CanUse("Hammer");}),
                  ItemLocationPairing(&GV_GS_BehindTent, []{return CanUse("Hookshot") && AtNight;}),
                  ItemLocationPairing(&GV_GS_Pillar,     []{return CanUse("Hookshot") && AtNight;}),
                }, {
                  //Exits
                  ExitPairing::Both(&GF_Main,          []{return true;}),
                  ExitPairing::Both(&GV_Stream,        []{return true;}),
                  ExitPairing::Both(&GV_Main,          []{return IsChild || CanRideEpona || CanUse("Longshot") || GerudoFortress.Is(GERUDOFORTRESS_OPEN) || CarpenterRescue;}),
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
                  ItemLocationPairing(&GF_Chest,            []{return CanUse("Hover Boots") || CanUse("Scarecrow") || CanUse("Longshot");}),
                  ItemLocationPairing(&GF_HBA1000Points,    []{return GerudoToken && CanRideEpona && Bow && AtDay;}),
                  ItemLocationPairing(&GF_HBA1500Points,    []{return GerudoToken && CanRideEpona && Bow && AtDay;}),
                  ItemLocationPairing(&GF_NorthF1Carpenter, []{return  IsAdult || KokiriSword;}),
                  ItemLocationPairing(&GF_NorthF2Carpenter, []{return (IsAdult || KokiriSword) && (GerudoToken || CanUse("Bow") || CanUse("Hookshot") || CanUse("Hover Boots") || LogicGerudoKitchen);}),
                  ItemLocationPairing(&GF_SouthF1Carpenter, []{return  IsAdult || KokiriSword;}),
                  ItemLocationPairing(&GF_SouthF2Carpenter, []{return  IsAdult || KokiriSword;}),
                  ItemLocationPairing(&GF_GerudoToken,      []{return CanFinishGerudoFortress;}),
                  ItemLocationPairing(&GF_GS_ArcheryRange,  []{return CanUse("Hookshot") && GerudoToken && AtNight;}),
                  ItemLocationPairing(&GF_GS_TopFloor,      []{return IsAdult && AtNight && (GerudoToken || CanUse("Bow") || CanUse("Hookshot") || CanUse("Hover Boots") || LogicGerudoKitchen);})
                }, {
                  //Exits
                  ExitPairing::Both(&GV_FortressSide,             []{return true;}),
                  ExitPairing::Both(&GF_OutsideGate,              []{return GF_GateOpen;}),
                  ExitPairing::Both(&GerudoTrainingGrounds_Lobby, []{return IsAdult && GerudoToken;}),
                  ExitPairing::Both(&GF_StormsGrotto,             []{return IsAdult && CanOpenStormGrotto;})
  });

  Exit GF_OutsideGate = Exit("GF Outside Gate", "Gerudo Fortress", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GF_GateOpen, []{return IsAdult && GerudoToken && (ShuffleGerudoToken || ShuffleOverworldEntrances || ShuffleSpecialIndoorEntrances);}),
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
                  ExitPairing::Both(&HW_Main,        []{return CanUse("Hover Boots") || CanUse("Longshot");}),
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
                  ExitPairing::Both(&HW_NearColossus, []{return LogicLensWasteland || CanUse("Lens of Truth");}),
                  ExitPairing::Both(&HW_NearFortress, []{return CanUse("Hover Boots") || CanUse("Longshot");}),
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
                  ItemLocationPairing(&Colossus_GS_Tree,         []{return CanUse("Hookshot") && AtNight;}),
                  ItemLocationPairing(&Colossus_GS_Hill,         []{return IsAdult && AtNight && (Colossus_Main.CanPlantBean() || CanUse("Longshot") || (LogicColossusGS && CanUse("Hookshot")));})
                  //Colossus Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&Colossus_GreatFairyFountain, []{return HasExplosives;}),
                  ExitPairing::Both(&SpiritTemple_Lobby,          []{return true;}),
                  ExitPairing::Both(&HW_NearColossus,             []{return true;}),
                  ExitPairing::Both(&Colossus_Grotto,             []{return CanUse("Silver Gauntlets");})
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
                  ExitPairing::Both(&MK_Entrance,          []{return true;}),
                  ExitPairing::Both(&ToT_Entrance,         []{return true;}),
                  ExitPairing::Both(&CastleGrounds,        []{return true;}),
                  ExitPairing::Day(&MK_Bazaar,            []{return IsChild && AtDay;}),
                  ExitPairing::Day(&MK_MaskShop,          []{return IsChild && AtDay;}),
                  ExitPairing::Day(&MK_ShootingGallery,   []{return IsChild && AtDay;}),
                  ExitPairing::Both(&MK_BombchuBowling,    []{return IsChild;}),
                  ExitPairing::Night(&MK_TreasureChestGame, []{return IsChild && AtNight;}),
                  ExitPairing::Day(&MK_PotionShop,        []{return IsChild && AtDay;}),
                  ExitPairing::Night(&MK_BombchuShop,       []{return IsChild && AtNight;}),
                  ExitPairing::Both(&MK_DogLadyHouse,      []{return IsChild;}),
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

  Exit ToT_BeyondDoorOfTime = Exit("Beyond Door of Time", "", "Temple of Time", NO_DAY_NIGHT_CYCLE, {}, {
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
                  EventPairing(&ButterflyFairy,   []{return ButterflyFairy   || CanUse("Sticks");}),
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
                  ItemLocationPairing(&OGC_GS, []{return HasExplosives || (IsAdult && (LogicOutsideGanonsGS || Bow || Hookshot || CanUse("Dins Fire")));}),
                }, {
                  //Exits
                  ExitPairing::Night(&CastleGrounds,          []{return AtNight;}),
                  ExitPairing::Night(&OGC_GreatFairyFountain, []{return CanUse("Golden Gauntlets") && AtNight;}),
                  ExitPairing::Both(&GanonsCastle_Lobby,      []{return CanBuildRainbowBridge;})
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
                  //Market Bombchu Bowling Bombchus
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
                  ItemLocationPairing(&MK_TreasureChestGameReward, []{return CanUse("Lens of Truth");})
                }, {
                  //Exits
                  ExitPairing::Both(&MK_Main, []{return true;})
  });

  Exit MK_BombchuShop = Exit("Market Bombchu Shop", "", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&BuyBombchus10, []{return GoronRuby;}),
                  EventPairing(&BuyBombchus20, []{return GoronRuby;}),
                }, {
                  //Locations
                  ItemLocationPairing(&MK_BombchuShopItem1, []{return true;}),
                  ItemLocationPairing(&MK_BombchuShopItem2, []{return true;}),
                  ItemLocationPairing(&MK_BombchuShopItem3, []{return true;}),
                  ItemLocationPairing(&MK_BombchuShopItem4, []{return true;}),
                  ItemLocationPairing(&MK_BombchuShopItem5, []{return true;}),
                  ItemLocationPairing(&MK_BombchuShopItem6, []{return true;}),
                  ItemLocationPairing(&MK_BombchuShopItem7, []{return true;}),
                  ItemLocationPairing(&MK_BombchuShopItem8, []{return true;}),
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
                  ItemLocationPairing(&Kak_GS_HouseUnderConstruction, []{return IsChild && AtNight;}),
                  ItemLocationPairing(&Kak_GS_SkulltulaHouse,         []{return IsChild && AtNight;}),
                  ItemLocationPairing(&Kak_GS_GuardsHouse,            []{return IsChild && AtNight;}),
                  ItemLocationPairing(&Kak_GS_Tree,                   []{return IsChild && AtNight;}),
                  ItemLocationPairing(&Kak_GS_Watchtower,             []{return IsChild && (Slingshot || HasBombchus) && AtNight;}),
                  ItemLocationPairing(&Kak_GS_AboveImpasHouse,        []{return CanUse("Hookshot") && AtNight;}),
                }, {
                  //Exits
                  ExitPairing::Both(&HF_Main,                []{return true;}),
                  ExitPairing::Both(&Kak_CarpenterBossHouse, []{return true;}),
                  ExitPairing::Both(&Kak_HouseOfSkulltula,   []{return true;}),
                  ExitPairing::Both(&Kak_ImpasHouse,         []{return true;}),
                  ExitPairing::Both(&Kak_Windmill,           []{return true;}),
                  ExitPairing::Day(&Kak_Bazaar,              []{return IsAdult && AtDay;}),
                  ExitPairing::Day(&Kak_ShootingGallery,     []{return IsAdult && AtDay;}),
                  ExitPairing::Both(&BottomOfTheWell,        []{return DrainWell && (IsChild || ShuffleDungeonEntrances);}),
                  ExitPairing::Day(&Kak_PotionShopFront,     []{return AtDay;}),
                  ExitPairing::Both(&Kak_PotionShopFront,    []{return IsChild;}),
                  ExitPairing::Both(&Kak_RedeadGrotto,       []{return CanOpenBombGrotto;}),
                  ExitPairing::Both(&Kak_ImpasLedge,         []{return (IsAdult && LogicVisibleCollision);}),
                  ExitPairing::Day(&Kak_ImpasLedge,          []{return (IsChild && AtDay);}),
                  ExitPairing::Both(&Kak_Rooftop,            []{return CanUse("Hookshot") || (LogicManOnRoof && (IsAdult || Slingshot || HasBombchus));}),
                  ExitPairing::Day(&Kak_Rooftop,             []{return LogicManOnRoof && AtDay;}),
                  ExitPairing::Both(&GY_Main,                []{return true;}),
                  ExitPairing::Both(&Kak_BehindGate,         []{return true;})
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
                  ItemLocationPairing(&Kak_WindmillFreestandingPoH, []{return CanUse("Boomerang") || DampesWindmillAccess;}),
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
                  ItemLocationPairing(&Kak_RedeadGrottoChest, []{return IsAdult || (Sticks || KokiriSword || CanUse("Dins Fire"));})
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
                  EventPairing(&ButterflyFairy, []{return ButterflyFairy || (CanUse("Sticks") && AtDay);}),
                  EventPairing(&BeanPlantFairy, []{return BeanPlantFairy || (GY_Main.CanPlantBean() && CanPlay(SongOfStorms));}),
                  EventPairing(&BugRock,        []{return true;}),
                }, {
                  //Locations
                  ItemLocationPairing(&GY_FreestandingPoH,       []{return (IsAdult && (GY_Main.CanPlantBean() || CanUse("Longshot"))) || (LogicGraveyardPoH && CanUse("Boomerang"));}),
                  ItemLocationPairing(&GY_DampeGravediggingTour, []{return IsChild && AtNight;}), //This needs to change
                  ItemLocationPairing(&GY_GS_Wall,               []{return CanUse("Boomerang") && AtNight;}),
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
                  ExitPairing::Both(&GY_Main,               []{return true;}),
                  ExitPairing::Both(&ShadowTemple_Entryway, []{return CanUse("Dins Fire") || (LogicShadowFireArrowEntry && CanUse("Fire Arrows"));}),
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
                  ItemLocationPairing(&DMT_FreestandingPoH,        []{return (DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO)) || CanUse("Nayrus Love") || Fairy || CanUse("Hover Boots") || (IsAdult && DMT_Main.CanPlantBean() && (HasExplosives || GoronBracelet));}),
                  ItemLocationPairing(&DMT_GS_BeanPatch,           []{return CanPlantBugs && (HasExplosives || GoronBracelet || (LogicDMTSoilGS && CanUse("Boomerang")));}),
                  ItemLocationPairing(&DMT_GS_NearKak,             []{return CanBlastOrSmash;}),
                  ItemLocationPairing(&DMT_GS_AboveDodongosCavern, []{return IsAdult && AtNight && CanUse("Hammer");})
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
                  ItemLocationPairing(&DMT_GS_FallingRocksPath, []{return IsAdult && AtNight && CanUse("Hammer");}),
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
                  ExitPairing::Both(&DodongosCavern_Beginning, []{return true;}),
                  ExitPairing::Both(&DMT_Main,                 []{return true;})
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
                  EventPairing(&GoronCityChildFire,        []{return GoronCityChildFire        || (IsChild && CanUse("Dins Fire"));}),
                  EventPairing(&GCWoodsWarpOpen,           []{return GCWoodsWarpOpen           || (CanBlastOrSmash || CanUse("Dins Fire") || CanUse("Bow") || GoronBracelet || GoronCityChildFire);}),
                  EventPairing(&StopGCRollingGoronAsAdult, []{return StopGCRollingGoronAsAdult || (IsAdult && (GoronBracelet || HasExplosives || Bow || (LogicLinkGoronDins && CanUse("Dins Fire"))));}),
                }, {
                  //Locations
                  ItemLocationPairing(&GC_MazeLeftChest,       []{return CanUse("Hammer") || CanUse("Silver Gauntlets") || (LogicGoronCityLeftMost && HasExplosives && CanUse("Hover Boots"));}),
                  ItemLocationPairing(&GC_MazeCenterChest,     []{return CanBlastOrSmash  || CanUse("Silver Gauntlets");}),
                  ItemLocationPairing(&GC_MazeRightChest,      []{return CanBlastOrSmash  || CanUse("Silver Gauntlets");}),
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
                  ExitPairing::Both(&GC_Grotto,          []{return IsAdult && ((CanPlay(SongOfTime) && ((DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_QUADRUPLE)) || CanUse("Goron Tunic") || CanUse("Longshot") || CanUse("Nayrus Love"))) || (DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO) && CanUse("Goron Tunic") && CanUse("Hookshot")) ||(CanUse("Nayrus Love") && CanUse("Hookshot")));}),
  });

  Exit GC_WoodsWarp = Exit("GC Woods Warp", "Goron City", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GCWoodsWarpOpen, []{return GCWoodsWarpOpen || (CanBlastOrSmash || CanUse("Dins Fire"));}),
                }, {}, {
                  //Exits
                  ExitPairing::Both(&GC_Main, []{return CanLeaveForest && GCWoodsWarpOpen;}),
                  ExitPairing::Both(&LW_Main, []{return true;})
  });

  Exit GC_DaruniasChamber = Exit("GC Darunias Chamber", "Goron City", "Goron City", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&GoronCityChildFire, []{return GoronCityChildFire || (CanUse("Sticks"));}),
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
                  ExitPairing::Both(&DMC_UpperLocal,  []{return CanUse("Goron Tunic");}),
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
                  ExitPairing::Both(&DMC_CentralNearby,    []{return CanUse("Goron Tunic") && CanUse("Longshot") && ((DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO) && DamageMultiplier.IsNot(DAMAGEMULTIPLIER_QUADRUPLE)) || (Fairy && !ShuffleDungeonEntrances) || CanUse("Nayrus Love"));})
  });

  Exit DMC_LadderAreaNearby = Exit("DMC Ladder Area Nearby", "Death Mountain Crater", "Death Mountain Crater", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&DMC_DekuScrub, []{return IsChild && CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing::Both(&DMC_UpperNearby, []{return IsAdult;}),
                  ExitPairing::Both(&DMC_LowerNearby, []{return CanUse("Hover Boots") || (LogicCraterUpperToLower && CanUse("Hammer"));})
  });

  Exit DMC_LowerNearby = Exit("DMC Lower Nearby", "Death Mountain Crater", "Death Mountain Crater", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&DMC_LowerLocal,         []{return CanUse("Goron Tunic");}),
                  ExitPairing::Both(&GC_DaruniasChamber,     []{return true;}),
                  ExitPairing::Both(&DMC_GreatFairyFountain, []{return CanUse("Hammer");}),
                  ExitPairing::Both(&DMC_HammerGrotto,       []{return CanUse("Hammer");})
  });

  Exit DMC_LowerLocal = Exit("DMC Lower Local", "Death Mountain Crater", "Death Mountain Crater", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&DMC_LowerNearby,      []{return true;}),
                  ExitPairing::Both(&DMC_LadderAreaNearby, []{return true;}),
                  ExitPairing::Both(&DMC_CentralNearby,    []{return CanUse("Hover Boots") || CanUse("Hookshot");}),
                  ExitPairing::Both(&FireTemple_Entrance,  []{return (CanUse("Hover Boots") || CanUse("Hookshot")) && (LogicFewerTunicRequirements || CanUse("Goron Tunic"));}),
  });

  Exit DMC_CentralNearby = Exit("DMC Central Nearby", "Death Mountain Crater", "Death Mountain Crater", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&DMC_VolcanoFreestandingPoH, []{return IsAdult && (DMC_CentralLocal.CanPlantBean() || (LogicCraterBeanPoHWithHovers && HoverBoots));}),
                  ItemLocationPairing(&SheikInCrater,              []{return IsAdult;}),
                }, {
                  //Exits
                  ExitPairing::Both(&DMC_CentralLocal, []{return CanUse("Goron Tunic");})
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
                  ExitPairing::Both(&DMC_LowerNearby,     []{return IsAdult && (CanUse("Hover Boots") || CanUse("Hookshot") || DMC_CentralLocal.CanPlantBean());}),
                  ExitPairing::Both(&DMC_UpperNearby,     []{return IsAdult && DMC_CentralLocal.CanPlantBean();}),
                  ExitPairing::Both(&FireTemple_Entrance, []{return (IsChild && ShuffleDungeonEntrances) || (IsAdult && (LogicFewerTunicRequirements || CanUse("Goron Tunic")));}),
  });

  Exit FireTemple_Entrance = Exit("Fire Temple Entrance", "Death Mountain Crater", "Death Mountain Crater", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                    ExitPairing::Both(&FireTemple_Lower, []{return true;}),
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
                  EventPairing(&ButterflyFairy,   []{return ButterflyFairy   || CanUse("Sticks");}),
                  EventPairing(&BugShrub,         []{return BugShrub         || CanCutShrubs;}),
                }, {
                  //Locations
                  ItemLocationPairing(&ZR_MagicBeanSalesman,             []{return IsChild;}),
                  ItemLocationPairing(&ZR_FrogsOcarinaGame,              []{return IsChild && CanPlay(ZeldasLullaby) && CanPlay(SariasSong) && CanPlay(SunsSong) && CanPlay(EponasSong) && CanPlay(SongOfTime) && CanPlay(SongOfStorms);}),
                  ItemLocationPairing(&ZR_FrogsInTheRain,                []{return IsChild && CanPlay(SongOfStorms);}),
                  ItemLocationPairing(&ZR_NearOpenGrottoFreestandingPoH, []{return IsChild || CanUse("Hover Boots") || (IsAdult && LogicZoraRiverLower);}),
                  ItemLocationPairing(&ZR_NearDomainFreestandingPoH,     []{return IsChild || CanUse("Hover Boots") || (IsAdult && LogicZoraRiverUpper);}),
                  ItemLocationPairing(&ZR_GS_Ladder,                     []{return IsChild && AtNight && CanChildAttack;}),
                  ItemLocationPairing(&ZR_GS_NearRaisedGrottos,          []{return CanUse("Hookshot") && AtNight;}),
                  ItemLocationPairing(&ZR_GS_AboveBridge,                []{return CanUse("Hookshot") && AtNight;}),
                  //ZR Near Grottos Gossip Stone
                  //ZR Near Domain Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&ZR_Front,           []{return true;}),
                  ExitPairing::Both(&ZR_OpenGrotto,      []{return true;}),
                  ExitPairing::Both(&ZR_FairyGrotto,     []{return CanBlastOrSmash;}),
                  ExitPairing::Both(&LW_Main,            []{return CanDive || CanUse("Iron Boots");}),
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
                  ItemLocationPairing(&ZD_Chest,              []{return CanUse("Sticks");}),
                  ItemLocationPairing(&ZD_KingZoraThawed,     []{return KingZoraThawed;}),
                  ItemLocationPairing(&ZD_GS_FrozenWaterfall, []{return IsAdult && AtNight && (Hookshot || Bow || MagicMeter);}),
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
                  EventPairing(&ButterflyFairy,   []{return ButterflyFairy   || (CanUse("Sticks") && AtDay);}),
                }, {
                  //Locations
                  ItemLocationPairing(&ZF_IcebergFreestandingPoH, []{return IsAdult;}),
                  ItemLocationPairing(&ZF_BottomFreestandingPoH,  []{return IsAdult && IronBoots && (LogicFewerTunicRequirements || CanUse("Zora Tunic"));}),
                  ItemLocationPairing(&ZF_GS_Tree,                []{return IsChild;}),
                  ItemLocationPairing(&ZF_GS_AboveTheLog,         []{return CanUse("Boomerang") && AtNight;}),
                  ItemLocationPairing(&ZF_GS_HiddenCave,          []{return CanUse("Silver Gauntlets") && CanBlastOrSmash && CanUse("Hookshot") && AtNight;}),
                  //ZF Fairy Gossip Stone
                  //ZF Jabu Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&ZD_BehindKingZora,        []{return true;}),
                  ExitPairing::Both(&JabuJabusBelly_Beginning, []{return IsChild && FishAccess;}),
                  ExitPairing::Both(&IceCavern_Beginning,      []{return IsAdult;}),
                  ExitPairing::Both(&ZF_GreatFairyFountain,    []{return HasExplosives;})
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
                  ItemLocationPairing(&LLR_GS_RainShed,    []{return IsChild && AtNight;}),
                  ItemLocationPairing(&LLR_GS_HouseWindow, []{return CanUse("Boomerang") && AtNight;}),
                  ItemLocationPairing(&LLR_GS_BackWall,    []{return CanUse("Boomerang") && AtNight;}),
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
                  EventPairing(&DekuBabaNuts,   []{return DekuBabaNuts   || (IsAdult || KokiriSword || Slingshot || Sticks || HasExplosives || CanUse("Dins Fire"));}),
                }, {
                  //Locations
                  ItemLocationPairing(&DekuTree_MapChest,             []{return true;}),
                  ItemLocationPairing(&DekuTree_CompassChest,         []{return true;}),
                  ItemLocationPairing(&DekuTree_CompassRoomSideChest, []{return true;}),
                  ItemLocationPairing(&DekuTree_BasementChest,        []{return IsAdult || CanChildAttack || Nuts;}),
                  ItemLocationPairing(&DekuTree_GS_CompassRoom,       []{return IsAdult || CanChildAttack;}),
                  ItemLocationPairing(&DekuTree_GS_BasementVines,     []{return CanUseProjectile || CanUse("Dins Fire") || (LogicDekuBasementGS && (IsAdult || Sticks || KokiriSword));}),
                  ItemLocationPairing(&DekuTree_GS_BasementGate,      []{return IsAdult || CanChildAttack;}),
                  ItemLocationPairing(&DekuTree_GS_BasementBackRoom,  []{return ((HasFireSourceWithTorch || (LogicDekuB1WebsWithBow && CanUse("Bow"))) && (CanUse("Slingshot") || CanUse("Bow")) && CanBlastOrSmash && HookshotOrBoomerang) || ((LogicDekuB1Skip || IsAdult) && IsChild && HasExplosives && CanUse("Boomerang") && (Sticks || CanUse("Dins Fire")));}),
                }, {
                  //Exits
                  ExitPairing::Both(&KF_OutsideDekuTree,       []{return true;}),
                  ExitPairing::Both(&DekuTree_SlingshotRoom,   []{return HasShield;}),
                  ExitPairing::Both(&DekuTree_BossRoom,        []{return (HasFireSourceWithTorch || (LogicDekuB1WebsWithBow && CanUse("Bow"))) && (LogicDekuB1Skip || (IsAdult || CanUse("Slingshot")));})
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
                  ItemLocationPairing(&DodongosCavern_CompassChest,                  []{return IsAdult || Sticks || (CanUse("Dins Fire") && (Slingshot || HasExplosives || KokiriSword));}),
                  ItemLocationPairing(&DodongosCavern_GS_SideRoomNearLowerLizalfos,  []{return HasExplosives || IsAdult || Slingshot || Boomerang || Sticks || KokiriSword;}),
                  ItemLocationPairing(&DodongosCavern_GS_Scarecrow,                  []{return CanUse("Scarecrow") || CanUse("Longshot") || (LogicDCScarecrowGS && (IsAdult || CanChildAttack));}),
                  ItemLocationPairing(&DodongosCavern_DekuScrubSideRoomNearDodongos, []{return IsAdult || Slingshot || Sticks || HasExplosives || KokiriSword;}),
                  ItemLocationPairing(&DodongosCavern_DekuScrubLobby,                []{return true;}),
                  //Dodongos Cavern Gossip Stone
                }, {
                  //Exits
                  ExitPairing::Both(&DodongosCavern_Beginning, []{return true;}),
                  ExitPairing::Both(&DodongosCavern_Climb,     []{return (IsAdult || ((Sticks || CanUse("Dins Fire")) && (Slingshot || Sticks || HasExplosives || KokiriSword))) && (HasExplosives || GoronBracelet || CanUse("Dins Fire") ||(LogicDCStaircase && CanUse("Bow")));})
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
                  ExitPairing::Both(&DodongosCavern_FarBridge, []{return (IsChild && (Slingshot || (LogicDCSlingshotSkip && (Sticks || HasExplosives || KokiriSword)))) || (IsAdult && (Bow || HoverBoots || CanUse("Longshot") || LogicDCJump));})
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
                  EventPairing(&FairyPot, []{return true;}),
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
                  ItemLocationPairing(&JabuJabusBelly_DekuScrub,             []{return CanDive || IsChild || LogicJabuScrubJumpDive || CanUse("Iron Boots");}),
                }, {
                  //Exits
                  ExitPairing::Both(&JabuJabusBelly_Beginning, []{return true;}),
                  ExitPairing::Both(&JabuJabusBelly_Depths,    []{return CanUse("Boomerang");}),
                  ExitPairing::Both(&JabuJabusBelly_BossArea,  []{return LogicJabuBossGSAdult && CanUse("Hover Boots");}),
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
                  EventPairing(&NutPot, []{return true;}),
                }, {
                  //Locations
                  ItemLocationPairing(&JabuJabusBelly_BarinadeHeart, []{return CanUse("Boomerang");}),
                  ItemLocationPairing(&Barinade,                     []{return CanUse("Boomerang");}),
                  ItemLocationPairing(&JabuJabusBelly_GS_NearBoss,   []{return true;}),
                }, {
                  //Exits
                  ExitPairing::Both(&JabuJabusBelly_Main, []{return true;}),
  });

  Exit ForestTemple_Lobby = Exit("Forest Temple Lobby", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&ForestTemple_FirstRoomChest,    []{return true;}),
                  ItemLocationPairing(&ForestTemple_FirstStalfosChest, []{return IsAdult || KokiriSword;}),
                  ItemLocationPairing(&ForestTemple_GS_FirstRoom,      []{return CanUse("Dins Fire") || CanUseProjectile;}),
                  ItemLocationPairing(&ForestTemple_GS_Lobby,          []{return HookshotOrBoomerang;}),
                }, {
                  //Exits
                  ExitPairing::Both(&SFM_Main,                   []{return true;}),
                  ExitPairing::Both(&ForestTemple_NWOutdoors,    []{return CanPlay(SongOfTime) || IsChild;}),
                  ExitPairing::Both(&ForestTemple_NEOutdoors,    []{return CanUse("Bow") || CanUse("Slingshot");}),
                  ExitPairing::Both(&ForestTemple_BlockPushRoom, []{return SmallKeys(ForestTempleKeys, 1);}),
                  ExitPairing::Both(&ForestTemple_BossRegion,    []{return ForestTempleJoAndBeth && ForestTempleAmyAndMeg;})
  });

  Exit ForestTemple_NWOutdoors = Exit("Forest Temple NW Outdoors", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&DekuBabaSticks, []{return DekuBabaSticks || (IsAdult || KokiriSword || Boomerang);}),
                  EventPairing(&DekuBabaNuts,   []{return DekuBabaNuts   || (IsAdult || KokiriSword || Slingshot || Sticks || HasExplosives || CanUse("Dins Fire"));}),
                }, {
                  //Locations
                  ItemLocationPairing(&ForestTemple_GS_LevelIslandCourtyard, []{return CanUse("Longshot") || ((ForestTemple_OutsideUpperLedge.dayAdult || ForestTemple_OutsideUpperLedge.nightAdult) && CanUse("Hookshot"));}),
                }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_OutdoorsHighBalconies, []{return IsAdult || (HasExplosives || ((CanUse("Boomerang") || Nuts || DekuShield) && (Sticks || KokiriSword || CanUse("Slingshot"))));})
  });

  Exit ForestTemple_NEOutdoors = Exit("Forest Temple NE Outdoors", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&DekuBabaSticks, []{return DekuBabaSticks || (IsAdult || KokiriSword || Boomerang);}),
                  EventPairing(&DekuBabaNuts,   []{return DekuBabaNuts   || (IsAdult || KokiriSword || Slingshot || Sticks || HasExplosives || CanUse("Dins Fire"));}),
                }, {
                  //Locations
                  ItemLocationPairing(&ForestTemple_RaisedIslandCourtyardChest, []{return CanUse("Hookshot");}),
                  ItemLocationPairing(&ForestTemple_GS_RaisedIslandCourtyard,   []{return CanUse("Hookshot") || (LogicForestOutdoorEastGS && CanUse("Boomerang"));}),
                }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_OutdoorsHighBalconies, []{return CanUse("Longshot");}),
                  ExitPairing::Both(&ForestTemple_NWOutdoors,            []{return CanUse("Iron Boots") || ProgressiveScale >= 2;}),
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
                  ExitPairing::Both(&ForestTemple_FallingRoom, []{return LogicForestDoorFrame && CanUse("Hover Boots") && CanUse("Scarecrow");})
  });

  Exit ForestTemple_FallingRoom = Exit("Forest Temple Falling Room", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&ForestTempleAmyAndMeg, []{return ForestTempleAmyAndMeg || CanUse("Bow");}),
                }, {
                  //Locations
                  ItemLocationPairing(&ForestTemple_FallingCeilingRoomChest, []{return true;})
                }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_NEOutdoors, []{return true;})
  });

  Exit ForestTemple_BlockPushRoom = Exit("Forest Temple Block Push Room", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&ForestTemple_EyeSwitchChest, []{return GoronBracelet && (CanUse("Bow") || CanUse("Slingshot"));})
                }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_OutsideUpperLedge, []{return CanUse("Hover Boots") || (LogicForestOutsideBackdoor && IsAdult && GoronBracelet);}),
                  ExitPairing::Both(&ForestTemple_BowRegion,         []{return GoronBracelet && SmallKeys(ForestTempleKeys, 3) && IsAdult;}),
                  ExitPairing::Both(&ForestTemple_StraightenedHall,  []{return GoronBracelet && SmallKeys(ForestTempleKeys, 2) && CanUse("Bow") && IsAdult;})
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
                  EventPairing(&ForestTempleJoAndBeth, []{return ForestTempleJoAndBeth || CanUse("Bow");}),
                }, {
                  //Locations
                  ItemLocationPairing(&ForestTemple_BowChest,     []{return true;}),
                  ItemLocationPairing(&ForestTemple_RedPoeChest,  []{return CanUse("Bow");}),
                  ItemLocationPairing(&ForestTemple_BluePoeChest, []{return CanUse("Bow");})
                }, {
                  //Exits
                  ExitPairing::Both(&ForestTemple_FallingRoom, []{return SmallKeys(ForestTempleKeys, 5) && (Bow || CanUse("Dins Fire"));})
  });

  Exit ForestTemple_BossRegion = Exit("Forest Temple Boss Region", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&ForestTemple_BasementChest,     []{return true;}),
                  ItemLocationPairing(&ForestTemple_PhantomGanonHeart, []{return BossKeyForestTemple;}),
                  ItemLocationPairing(&PhantomGanon,                   []{return BossKeyForestTemple;}),
                  ItemLocationPairing(&ForestTemple_GS_Basement,       []{return HookshotOrBoomerang;}),
  }, {});

  //Fire Temple logic currently assumes that the lowest locked door is unlocked from the start
  Exit FireTemple_Lower = Exit("Fire Temple Lower", "Fire Temple", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPot, []{return FairyPot || ((CanUse("Hover Boots") || CanUse("Hookshot")) && (LogicFewerTunicRequirements || CanUse("Goron Tunic")));}),
                }, {
                  //Locations
                  ItemLocationPairing(&FireTemple_NearBossChest,    []{return LogicFewerTunicRequirements || CanUse("Goron Tunic");}),
                  ItemLocationPairing(&FireTemple_FlareDancerChest, []{return /*SmallKeys(FireTempleKeys, 8) &&*/ CanUse("Hammer");}),
                  ItemLocationPairing(&FireTemple_BossKeyChest,     []{return /*SmallKeys(FireTempleKeys, 8) &&*/ CanUse("Hammer");}),
                  ItemLocationPairing(&FireTemple_VolvagiaHeart,    []{return CanUse("Goron Tunic") && CanUse("Hammer") && BossKeyFireTemple && (LogicFireBossDoorJump || HoverBoots || CanPlay(SongOfTime) || HasExplosives);}),
                  ItemLocationPairing(&Volvagia,                    []{return CanUse("Goron Tunic") && CanUse("Hammer") && BossKeyFireTemple && (LogicFireBossDoorJump || HoverBoots || CanPlay(SongOfTime) || HasExplosives);}),
                  ItemLocationPairing(&FireTemple_GS_BossKeyLoop,   []{return /*SmallKeys(FireTempleKeys, 8) &&*/ CanUse("Hammer");}),
                }, {
                  //Exits
                  ExitPairing::Both(&FireTemple_Entrance,    []{return true;}),
                  ExitPairing::Both(&FireTemple_BigLavaRoom, []{return SmallKeys(FireTempleKeys, 1) && (LogicFewerTunicRequirements || CanUse("Goron Tunic"));}),
  });

  Exit FireTemple_BigLavaRoom = Exit("Fire Temple Big Lava Room", "Fire Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&FireTemple_BigLavaRoomLowerOpenDoorChest, []{return true;}),
                  ItemLocationPairing(&FireTemple_BigLavaRoomBlockedDoorChest,   []{return IsAdult && HasExplosives;}),
                  ItemLocationPairing(&FireTemple_GS_SongOfTimeRoom,             []{return IsAdult && (CanPlay(SongOfTime) || LogicFireSongOfTime);}),
                }, {
                  //Exits
                  ExitPairing::Both(&FireTemple_Lower,  []{return true;}),
                  ExitPairing::Both(&FireTemple_Middle, []{return CanUse("Goron Tunic") && SmallKeys(FireTempleKeys, 3) && (GoronBracelet || LogicFireStrength) && (HasExplosives || Bow || Hookshot);}),
  });

  Exit FireTemple_Middle = Exit("Fire Temple Middle", "Fire Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&FireTemple_BoulderMazeLowerChest,    []{return true;}),
                  ItemLocationPairing(&FireTemple_BoulderMazeUpperChest,    []{return SmallKeys(FireTempleKeys, 5);}),
                  ItemLocationPairing(&FireTemple_BoulderMazeSideRoomChest, []{return true;}),
                  ItemLocationPairing(&FireTemple_BoulderMazeShortcutChest, []{return SmallKeys(FireTempleKeys, 5) && HasExplosives;}),
                  ItemLocationPairing(&FireTemple_ScarecrowChest,           []{return SmallKeys(FireTempleKeys, 5) && (CanUse("Scarecrow") || (LogicFireScarecrow && CanUse("Longshot")));}),
                  ItemLocationPairing(&FireTemple_MapChest,                 []{return SmallKeys(FireTempleKeys, 5) || (SmallKeys(FireTempleKeys, 4) && CanUse("Bow"));}),
                  ItemLocationPairing(&FireTemple_CompassChest,             []{return SmallKeys(FireTempleKeys, 5);}),
                  ItemLocationPairing(&FireTemple_GS_BoulderMaze,           []{return SmallKeys(FireTempleKeys, 4) && HasExplosives;}),
                  ItemLocationPairing(&FireTemple_GS_ScarecrowClimb,        []{return SmallKeys(FireTempleKeys, 5) && (CanUse("Scarecrow") || (LogicFireScarecrow && CanUse("Longshot")));}),
                  ItemLocationPairing(&FireTemple_GS_ScarecrowTop,          []{return SmallKeys(FireTempleKeys, 5) && (CanUse("Scarecrow") || (LogicFireScarecrow && CanUse("Longshot")));}),
                }, {
                  //Exits
                  ExitPairing::Both(&FireTemple_Upper, []{return SmallKeys(FireTempleKeys, 7) || (SmallKeys(FireTempleKeys, 6) && ((CanUse("Hover Boots") && CanUse("Hammer")) || LogicFireFlameMaze));})
  });

  Exit FireTemple_Upper = Exit("Fire Temple Upper", "Fire Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&FireTemple_HighestGoronChest,  []{return CanUse("Hammer") && CanPlay(SongOfTime);}),
                  ItemLocationPairing(&FireTemple_MegatonHammerChest, []{return HasExplosives;}),
  }, {});

  //Water Temple logic currently assumes that the locked door leading to the upper water raising location is unlocked from the start
  Exit WaterTemple_Lobby = Exit("Water Temple Lobby", "Water Temple", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&ChildWaterTemple, []{return IsChild;}),
                  EventPairing(&RaiseWaterLevel,  []{return (IsAdult && (Hookshot || HoverBoots || Bow)) || (HasFireSourceWithTorch && CanUseProjectile);}),
                }, {}, {
                  //Exits
                  ExitPairing::Both(&LH_Main,                       []{return true;}),
                  ExitPairing::Both(&WaterTemple_HighestWaterLevel, []{return RaiseWaterLevel;}),
                  ExitPairing::Both(&WaterTemple_Dive,              []{return (CanUse("Zora Tunic") || LogicFewerTunicRequirements) && ((LogicWaterTempleTorchLongshot && CanUse("Longshot")) || CanUse("Iron Boots"));}),
  });

  Exit WaterTemple_HighestWaterLevel = Exit("Water Temple Highest Water Level", "Water Temple", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPot,         []{return FairyPot           || CanUse("Longshot");}),
                  EventPairing(&WaterTempleClear, []{return BossKeyWaterTemple && CanUse("Longshot");})
                }, {
                  //Locations
                  ItemLocationPairing(&Morpha,                  []{return BossKeyWaterTemple && CanUse("Longshot");}),
                  ItemLocationPairing(&WaterTemple_MorphaHeart, []{return BossKeyWaterTemple && CanUse("Longshot");}),
                }, {
                  //Exits
                  ExitPairing::Both(&WaterTemple_FallingPlatformRoom, []{return SmallKeys(WaterTempleKeys, 4);}),

  });

  Exit WaterTemple_Dive = Exit("Water Temple Dive", "Water Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&WaterTemple_MapChest,              []{return RaiseWaterLevel;}),
                  ItemLocationPairing(&WaterTemple_CompassChest,          []{return (CanPlay(ZeldasLullaby) || IronBoots) && CanUse("Hookshot");}),
                  ItemLocationPairing(&WaterTemple_TorchesChest,          []{return (Bow || CanUse("Dins Fire") || (ChildWaterTemple && Sticks && KokiriSword && MagicMeter)) && CanPlay(ZeldasLullaby);}),
                  ItemLocationPairing(&WaterTemple_CentralBowTargetChest, []{return GoronBracelet && CanPlay(ZeldasLullaby) && ((Bow && (LogicWaterCentralBow || HoverBoots || CanUse("Longshot"))));}),
                  ItemLocationPairing(&WaterTemple_GS_BehindGate,         []{return (CanUse("Hookshot") || CanUse("Hover Boots")) && (HasExplosives && CanPlay(ZeldasLullaby)) && (CanUse("Iron Boots") || CanDive);}),
                  ItemLocationPairing(&WaterTemple_GS_CentralPillar,      []{return CanPlay(ZeldasLullaby) &&
                                                                                      (((CanUse("Longshot") || (LogicWaterCentralGSFW && CanUse("Hookshot") && CanUse("Farores Wind"))) &&
                                                                                        (SmallKeys(WaterTempleKeys, 5) || CanUse("Bow") || CanUse("Dins Fire"))) ||
                                                                                      (LogicWaterCentralGSFW && ChildWaterTemple && Boomerang && CanUse("Farores Wind") &&
                                                                                        (Sticks || CanUse("Dins Fire") ||
                                                                                        (SmallKeys(WaterTempleKeys, 5) && (CanUse("Hover Boots") || CanUse("Bow"))))));}),
                }, {
                  //Exits
                  ExitPairing::Both(&WaterTemple_CrackedWall,      []{return CanPlay(ZeldasLullaby) && (CanUse("Hookshot") || CanUse("Hover Boots")) && (LogicWaterCrackedWallNothing || (LogicWaterCrackedWallHovers && CanUse("Hover Boots")));}),
                  ExitPairing::Both(&WaterTemple_MiddleWaterLevel, []{return (Bow || CanUse("Dins Fire") || (SmallKeys(WaterTempleKeys, 5) && CanUse("Hookshot")) || (ChildWaterTemple && Sticks)) && CanPlay(ZeldasLullaby);}),
                  ExitPairing::Both(&WaterTemple_NorthBasement,    []{return SmallKeys(WaterTempleKeys, 5) && (CanUse("Longshot") || (LogicWaterBossKeyRegion && CanUse("Hover Boots"))) && (CanUse("Iron Boots") || CanPlay(ZeldasLullaby));}),
                  ExitPairing::Both(&WaterTemple_DragonStatue,     []{return CanPlay(ZeldasLullaby) && GoronBracelet &&
                                                                                ((IronBoots && CanUse("Hookshot")) ||
                                                                                (LogicWaterDragonAdult && (HasBombchus || CanUse("Bow") || CanUse("Hookshot")) && (CanDive || IronBoots)));}),
  });

  Exit WaterTemple_NorthBasement = Exit("Water Temple North Basement", "Water Temple", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPot, []{return FairyPot || (SmallKeys(WaterTempleKeys, 5) && (LogicWaterBKJumpDive || CanUse("Iron Boots")) && (LogicWaterNorthBasementLedgeJump || (HasExplosives && GoronBracelet) || HoverBoots));}),
                }, {
                  //Locations
                  ItemLocationPairing(&WaterTemple_BossKeyChest,        []{return SmallKeys(WaterTempleKeys, 5) && (LogicWaterBKJumpDive || CanUse("Iron Boots")) && (LogicWaterNorthBasementLedgeJump || (HasExplosives && GoronBracelet) || HoverBoots);}),
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
                  ItemLocationPairing(&WaterTemple_CentralPillarChest, []{return CanUse("Zora Tunic") && CanUse("Hookshot") && ((SmallKeys(WaterTempleKeys, 5) || CanUse("Bow") || CanUse("Dins Fire")));}),
                }, {
                  //Exits
                  ExitPairing::Both(&WaterTemple_CrackedWall, []{return true;}),
  });

  Exit WaterTemple_FallingPlatformRoom = Exit("Water Temple Falling Platform Room", "Water Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&WaterTemple_GS_FallingPlatformRoom, []{return CanUse("Longshot") || (LogicWaterFallingPlatformGS && CanUse("Hookshot"));}),
                }, {
                  //Exits
                  ExitPairing::Both(&WaterTemple_DarkLinkRegion, []{return SmallKeys(WaterTempleKeys, 5) && CanUse("Hookshot");}),
  });

  Exit WaterTemple_DarkLinkRegion = Exit("Water Temple Dark Link Region", "Water Temple", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FairyPot, []{return FairyPot || (SmallKeys(WaterTempleKeys, 5) && CanPlay(SongOfTime));}),
                }, {
                  //Locations
                  ItemLocationPairing(&WaterTemple_LongshotChest,          []{return SmallKeys(WaterTempleKeys, 5);}),
                  ItemLocationPairing(&WaterTemple_RiverChest,             []{return SmallKeys(WaterTempleKeys, 5) && CanPlay(SongOfTime) && Bow;}),
                  ItemLocationPairing(&WaterTemple_GS_River,               []{return CanPlay(SongOfTime) && SmallKeys(WaterTempleKeys, 5) && (IronBoots || (LogicWaterRiverGS && CanUse("Longshot") && (Bow || HasBombchus)));}),
                }, {
                  //Exits
                  ExitPairing::Both(&WaterTemple_DragonStatue, []{return (CanUse("Zora Tunic") || LogicFewerTunicRequirements) &&
                                                                         CanPlay(SongOfTime) && Bow &&
                                                                         (IronBoots || LogicWaterDragonJumpDive || LogicWaterDragonAdult);}),
  });

  Exit SpiritTemple_Lobby = Exit("Spirit Temple Lobby", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&Colossus_Main,           []{return true;}),
                  ExitPairing::Both(&SpiritTemple_Child,      []{return IsChild;}),
                  ExitPairing::Both(&SpiritTemple_EarlyAdult, []{return CanUse("Silver Gauntlets");}),
  });

  Exit SpiritTemple_Child = Exit("Child Spirit Temple", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&NutCrate, []{return true;}),
                }, {
                  //Locations
                  ItemLocationPairing(&SpiritTemple_ChildBridgeChest,       []{return (Boomerang || Slingshot || (HasExplosives && LogicSpiritChildBombchu)) && (Sticks || HasExplosives || ((Nuts || Boomerang) && (KokiriSword || Slingshot)));}),
                  ItemLocationPairing(&SpiritTemple_ChildEarlyTorchesChest, []{return (Boomerang || Slingshot || (HasExplosives && LogicSpiritChildBombchu)) && (Sticks || HasExplosives || ((Nuts || Boomerang) && (KokiriSword || Slingshot))) && (Sticks || CanUse("Dins Fire"));}),
                  ItemLocationPairing(&SpiritTemple_GS_MetalFence,          []{return (Boomerang || Slingshot || (HasExplosives && LogicSpiritChildBombchu)) && (Sticks || HasExplosives || ((Nuts || Boomerang) && (KokiriSword || Slingshot)));}),
                }, {
                  //Exits
                  ExitPairing::Both(&SpiritTemple_ChildClimb, []{return SmallKeys(SpiritTempleKeys, 1);}),
  });

  Exit SpiritTemple_ChildClimb = Exit("Child Spirit Temple Climb", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&SpiritTemple_ChildClimbNorthChest, []{return HasProjectile("Both") || ((SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && !ShuffleDungeonEntrances)) && CanUse("Silver Gauntlets") && HasProjectile("Adult")) || (SmallKeys(SpiritTempleKeys, 5) && IsChild && HasProjectile("Child"));}),
                  ItemLocationPairing(&SpiritTemple_ChildClimbEastChest,  []{return HasProjectile("Both") || ((SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && !ShuffleDungeonEntrances)) && CanUse("Silver Gauntlets") && HasProjectile("Adult")) || (SmallKeys(SpiritTempleKeys, 5) && IsChild && HasProjectile("Child"));}),
                  ItemLocationPairing(&SpiritTemple_GS_SunOnFloorRoom,    []{return HasProjectile("Both") || CanUse("Dins Fire") || ((DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO) || Fairy || CanUse("Nayrus Love")) && (Sticks || KokiriSword || HasProjectile("Child"))) || (IsChild && SmallKeys(SpiritTempleKeys, 5) && HasProjectile("Child")) || ((SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && !ShuffleDungeonEntrances)) && CanUse("Silver Gauntlets") && (HasProjectile("Adult") || DamageMultiplier.IsNot(DAMAGEMULTIPLIER_OHKO) || Fairy || CanUse("Nayrus Love")));}),
                }, {
                  //Exits
                  ExitPairing::Both(&SpiritTemple_CentralChamber, []{return HasExplosives;}),
  });

  Exit SpiritTemple_EarlyAdult = Exit("Early Adult Spirit Temple", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&SpiritTemple_CompassChest,          []{return CanUse("Hookshot") && CanPlay(ZeldasLullaby);}),
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
                  ItemLocationPairing(&SpiritTemple_MapChest,                 []{return ((HasExplosives || SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && !ShuffleDungeonEntrances)) && (CanUse("Dins Fire") || (((MagicMeter && FireArrows) || LogicSpiritMapChest) && Bow && Sticks))) || (SmallKeys(SpiritTempleKeys, 5) && HasExplosives && CanUse("Sticks")) || (SmallKeys(SpiritTempleKeys, 3) && (CanUse("Fire Arrows") || (LogicSpiritMapChest && Bow)) && CanUse("Silver Gauntlets"));}),
                  ItemLocationPairing(&SpiritTemple_SunBlockRoomChest,        []{return ((HasExplosives || SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && !ShuffleDungeonEntrances)) && (CanUse("Dins Fire") || (((MagicMeter && FireArrows) || LogicSpiritMapChest) && Bow && Sticks))) || (SmallKeys(SpiritTempleKeys, 5) && HasExplosives && CanUse("Sticks")) || (SmallKeys(SpiritTempleKeys, 3) && (CanUse("Fire Arrows") || (LogicSpiritMapChest && Bow)) && CanUse("Silver Gauntlets"));}),
                  ItemLocationPairing(&SpiritTemple_StatueRoomHandChest,      []{return SmallKeys(SpiritTempleKeys, 3) && CanUse("Silver Gauntlets") && CanPlay(ZeldasLullaby);}),
                  ItemLocationPairing(&SpiritTemple_StatueRoomNortheastChest, []{return SmallKeys(SpiritTempleKeys, 3) && CanUse("Silver Gauntlets") && CanPlay(ZeldasLullaby) && (Hookshot || HoverBoots);}),
                  ItemLocationPairing(&SpiritTemple_GS_HallAfterSunBlockRoom, []{return (HasExplosives && Boomerang && Hookshot) || (CanUse("Boomerang") && SmallKeys(SpiritTempleKeys, 5) && HasExplosives) || (Hookshot && CanUse("Silver Gauntlets") && (SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && Boomerang && BombchusInLogic && !ShuffleDungeonEntrances)));}),
                  ItemLocationPairing(&SpiritTemple_GS_Lobby,                 []{return ((HasExplosives || SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && !ShuffleDungeonEntrances)) && LogicSpiritLobbyGS && Boomerang && (Hookshot || HoverBoots)) || (LogicSpiritLobbyGS && SmallKeys(SpiritTempleKeys, 5) && HasExplosives && CanUse("Boomerang")) || (SmallKeys(SpiritTempleKeys, 3) && CanUse("Silver Gauntlets") && (Hookshot || HoverBoots));}),
                }, {
                  //Exits
                  ExitPairing::Both(&SpiritTemple_OutdoorHands,            []{return true;}),
                  ExitPairing::Both(&SpiritTemple_BeyondCentralLockedDoor, []{return SmallKeys(SpiritTempleKeys, 4) && CanUse("Silver Gauntlets");}),
                  ExitPairing::Both(&SpiritTemple_ChildClimb,              []{return true;}),
  });

  Exit SpiritTemple_OutdoorHands = Exit("Spirit Temple Outdoor Hands", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&SpiritTemple_SilverGauntletsChest, []{return (SmallKeys(SpiritTempleKeys, 3) && Longshot && HasExplosives) || SmallKeys(SpiritTempleKeys, 5);}),
                  ItemLocationPairing(&SpiritTemple_MirrorShieldChest,    []{return SmallKeys(SpiritTempleKeys, 4) && CanUse("Silver Gauntlets") && HasExplosives;}),
                }, {
                  //Exits
                  ExitPairing::Both(&Colossus_Main, []{return (IsChild && SmallKeys(SpiritTempleKeys, 5)) || (CanUse("Silver Gauntlets") && ((SmallKeys(SpiritTempleKeys, 3) && HasExplosives) || SmallKeys(SpiritTempleKeys, 5)));}),
  });

  Exit SpiritTemple_BeyondCentralLockedDoor = Exit("Spirit Temple Beyond Central Locked Door", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&SpiritTemple_NearFourArmosChest,         []{return MirrorShield && HasExplosives;}),
                  ItemLocationPairing(&SpiritTemple_HallwayLeftInvisibleChest,  []{return (LogicLensSpirit || CanUse("Lens of Truth")) && HasExplosives;}),
                  ItemLocationPairing(&SpiritTemple_HallwayRightInvisibleChest, []{return (LogicLensSpirit || CanUse("Lens of Truth")) && HasExplosives;}),
                }, {
                  //Exits
                  ExitPairing::Both(&SpiritTemple_BeyondFinalLockedDoor, []{return SmallKeys(SpiritTempleKeys, 5) && (LogicSpiritWall || CanUse("Longshot") || HasBombchus || ((Bombs || Nuts || CanUse("Dins Fire")) && (Bow || CanUse("Hookshot") || Hammer)));}),
  });

  Exit SpiritTemple_BeyondFinalLockedDoor = Exit("Spirit Temple Beyond Final Locked Door", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&SpiritTemple_BossKeyChest,  []{return CanPlay(ZeldasLullaby) && Bow && Hookshot;}),
                  ItemLocationPairing(&SpiritTemple_TopmostChest,  []{return MirrorShield;}),
                  ItemLocationPairing(&SpiritTemple_TwinrovaHeart, []{return MirrorShield && HasExplosives && Hookshot && BossKeySpiritTemple;}),
                  ItemLocationPairing(&Twinrova,                   []{return MirrorShield && HasExplosives && Hookshot && BossKeySpiritTemple;}),
  }, {});

  Exit ShadowTemple_Entryway = Exit("Shadow Temple Entryway", "Shadow Temple", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&GY_WarpPadRegion,       []{return true;}),
                  ExitPairing::Both(&ShadowTemple_Beginning, []{return (LogicLensShadow || CanUse("Lens of Truth")) && (CanUse("Hover Boots") || CanUse("Hookshot"));}),
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
                  ItemLocationPairing(&ShadowTemple_InvisibleSpikesChest,          []{return SmallKeys(ShadowTempleKeys, 2) && (LogicLensShadowBack || CanUse("Lens of Truth"));}),
                  ItemLocationPairing(&ShadowTemple_FreestandingKey,               []{return SmallKeys(ShadowTempleKeys, 2) && (LogicLensShadowBack || CanUse("Lens of Truth")) && Hookshot && (Bombs || GoronBracelet || (LogicShadowFreestandingKey && HasBombchus));}),
                  ItemLocationPairing(&ShadowTemple_GS_LikeLikeRoom,               []{return true;}),
                  ItemLocationPairing(&ShadowTemple_GS_FallingSpikesRoom,          []{return Hookshot;}),
                  ItemLocationPairing(&ShadowTemple_GS_SingleGiantPot,             []{return SmallKeys(ShadowTempleKeys, 2) && (LogicLensShadowBack || CanUse("Lens of Truth")) && Hookshot;}),
                }, {
                  //Exits
                  ExitPairing::Both(&ShadowTemple_WindTunnel, []{return (LogicLensShadowBack || CanUse("Lens of Truth")) && Hookshot && SmallKeys(ShadowTempleKeys, 3);}),
  });

  Exit ShadowTemple_WindTunnel = Exit("Shadow Temple Wind Tunnel", "Shadow Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&ShadowTemple_WindHintChest,        []{return true;}),
                  ItemLocationPairing(&ShadowTemple_AfterWindEnemyChest,  []{return true;}),
                  ItemLocationPairing(&ShadowTemple_AfterWindHiddenChest, []{return true;}),
                  ItemLocationPairing(&ShadowTemple_GS_NearShip,          []{return CanUse("Longshot") && SmallKeys(ShadowTempleKeys, 4);}),
                }, {
                  //Exits
                  ExitPairing::Both(&ShadowTemple_BeyondBoat, []{return CanPlay(ZeldasLullaby) && SmallKeys(ShadowTempleKeys, 4);}),
  });

  Exit ShadowTemple_BeyondBoat = Exit("Shadow Temple Beyond Boat", "Shadow Temple", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&ShadowTemple_SpikeWallsLeftChest,       []{return CanUse("Dins Fire");}),
                  ItemLocationPairing(&ShadowTemple_BossKeyChest,              []{return CanUse("Dins Fire");}),
                  ItemLocationPairing(&ShadowTemple_InvisibleFloormasterChest, []{return true;}),
                  ItemLocationPairing(&ShadowTemple_BongoBongoHeart,           []{return SmallKeys(ShadowTempleKeys, 5) && BossKeyShadowTemple && (Bow || CanUse("Distant Scarecrow") || (LogicShadowStatue && HasBombchus));}),
                  ItemLocationPairing(&BongoBongo,                             []{return SmallKeys(ShadowTempleKeys, 5) && BossKeyShadowTemple && (Bow || CanUse("Distant Scarecrow") || (LogicShadowStatue && HasBombchus));}),
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
                  ItemLocationPairing(&BottomOfTheWell_FrontLeftFakeWallChest,   []{return LogicLensBotw || CanUse("Lens of Truth");}),
                  ItemLocationPairing(&BottomOfTheWell_FrontCenterBombableChest, []{return HasExplosives;}),
                  ItemLocationPairing(&BottomOfTheWell_RightBottomFakeWallChest, []{return LogicLensBotw || CanUse("Lens of Truth");}),
                  ItemLocationPairing(&BottomOfTheWell_CompassChest,             []{return LogicLensBotw || CanUse("Lens of Truth");}),
                  ItemLocationPairing(&BottomOfTheWell_CenterSkulltulaChest,     []{return LogicLensBotw || CanUse("Lens of Truth");}),
                  ItemLocationPairing(&BottomOfTheWell_BackLeftBombableChest,    []{return (LogicLensBotw || CanUse("Lens of Truth")) && HasExplosives;}),
                  ItemLocationPairing(&BottomOfTheWell_FreestandingKey,          []{return Sticks || CanUse("Dins Fire");}),
                  ItemLocationPairing(&BottomOfTheWell_LensOfTruthChest,         []{return CanPlay(ZeldasLullaby) && (KokiriSword || (Sticks && LogicChildDeadhand));}),
                  ItemLocationPairing(&BottomOfTheWell_InvisibleChest,           []{return CanPlay(ZeldasLullaby) && (LogicLensBotw || CanUse("Lens of Truth"));}),
                  ItemLocationPairing(&BottomOfTheWell_UnderwaterFrontChest,     []{return CanPlay(ZeldasLullaby);}),
                  ItemLocationPairing(&BottomOfTheWell_UnderwaterLeftChest,      []{return CanPlay(ZeldasLullaby);}),
                  ItemLocationPairing(&BottomOfTheWell_MapChest,                 []{return HasExplosives || (((SmallKeys(BottomOfTheWellKeys, 3) && (LogicLensBotw || CanUse("Lens of Truth"))) || CanUse("Dins Fire")) && GoronBracelet);}),
                  ItemLocationPairing(&BottomOfTheWell_FireKeeseChest,           []{return SmallKeys(BottomOfTheWellKeys, 3) && (LogicLensBotw || CanUse("Lens of Truth"));}),
                  ItemLocationPairing(&BottomOfTheWell_LikeLikeChest,            []{return SmallKeys(BottomOfTheWellKeys, 3) && (LogicLensBotw || CanUse("Lens of Truth"));}),
                  ItemLocationPairing(&BottomOfTheWell_GS_WestInnerRoom,         []{return Boomerang && (LogicLensBotw || CanUse("Lens of Truth")) && SmallKeys(BottomOfTheWellKeys, 3);}),
                  ItemLocationPairing(&BottomOfTheWell_GS_EastInnerRoom,         []{return Boomerang && (LogicLensBotw || CanUse("Lens of Truth")) && SmallKeys(BottomOfTheWellKeys, 3);}),
                  ItemLocationPairing(&BottomOfTheWell_GS_LikeLikeCage,          []{return SmallKeys(BottomOfTheWellKeys, 3) && (LogicLensBotw || CanUse("Lens of Truth")) && Boomerang;}),
                }, {
                  //Exits
                  ExitPairing::Both(&BottomOfTheWell, []{return true;}),
  });

  Exit IceCavern_Beginning = Exit("Ice Cavern Beginning", "Ice Cavern", "", NO_DAY_NIGHT_CYCLE, {}, {}, {
                  //Exits
                  ExitPairing::Both(&ZF_Main,        []{return true;}),
                  ExitPairing::Both(&IceCavern_Main, []{return IsAdult || HasExplosives || CanUse("Dins Fire");}),
  });

  Exit IceCavern_Main = Exit("Ice Cavern", "Ice Cavern", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&BlueFireAccess, []{return BlueFireAccess || (IsAdult && HasBottle);}),
                }, {
                  //Locations
                  ItemLocationPairing(&IceCavern_MapChest,              []{return BlueFire && IsAdult;}),
                  ItemLocationPairing(&IceCavern_CompassChest,          []{return BlueFire;}),
                  ItemLocationPairing(&IceCavern_IronBootsChest,        []{return BlueFire && (IsAdult || Slingshot || Sticks || KokiriSword || CanUse("Dins Fire"));}),
                  ItemLocationPairing(&SheikInIceCavern,                []{return BlueFire && (IsAdult || Slingshot || Sticks || KokiriSword || CanUse("Dins Fire"));}),
                  ItemLocationPairing(&IceCavern_FreestandingPoH,       []{return BlueFire;}),
                  ItemLocationPairing(&IceCavern_GS_SpinningScytheRoom, []{return HookshotOrBoomerang;}),
                  ItemLocationPairing(&IceCavern_GS_HeartPieceRoom,     []{return BlueFire && HookshotOrBoomerang;}),
                  ItemLocationPairing(&IceCavern_GS_PushBlockRoom,      []{return BlueFire && HookshotOrBoomerang;}),
  }, {});

  Exit GerudoTrainingGrounds_Lobby = Exit ("Gerudo Training Grounds Lobby", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&GerudoTrainingGrounds_LobbyLeftChest,  []{return CanUse("Bow") || CanUse("Slingshot");}),
                  ItemLocationPairing(&GerudoTrainingGrounds_LobbyRightChest, []{return CanUse("Bow") || CanUse("Slingshot");}),
                  ItemLocationPairing(&GerudoTrainingGrounds_StalfosChest,    []{return IsAdult || KokiriSword;}),
                  ItemLocationPairing(&GerudoTrainingGrounds_BeamosChest,     []{return HasExplosives && (IsAdult || KokiriSword);}),
                }, {
                  //Exits
                  ExitPairing::Both(&GF_Main,                              []{return true;}),
                  ExitPairing::Both(&GerudoTrainingGrounds_HeavyBlockRoom, []{return (IsAdult || KokiriSword) && (CanUse("Hookshot") || LogicGtgWithoutHookshot);}),
                  ExitPairing::Both(&GerudoTrainingGrounds_LavaRoom,       []{return (IsAdult || KokiriSword) && HasExplosives;}),
                  ExitPairing::Both(&GerudoTrainingGrounds_CentralMaze,    []{return true;}),
  });

  Exit GerudoTrainingGrounds_CentralMaze = Exit ("Gerudo Training Grounds Central Maze", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&GerudoTrainingGrounds_HiddenCeilingChest,  []{return SmallKeys(GerudoTrainingGroundsKeys, 3) && (LogicLensGtg || CanUse("Lens of Truth"));}),
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
                  ExitPairing::Both(&GerudoTrainingGrounds_HammerRoom, []{return CanUse("Hookshot");}),
                  ExitPairing::Both(&GerudoTrainingGrounds_LavaRoom,   []{return true;}),
  });

  Exit GerudoTrainingGrounds_LavaRoom = Exit("Gerudo Training Grounds Lava Room", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&GerudoTrainingGrounds_UnderwaterSilverRupeeChest, []{return CanUse("Hookshot") && CanPlay(SongOfTime) && IronBoots && (LogicFewerTunicRequirements || CanUse("Zora Tunic"));}),
                }, {
                  //Exits
                  ExitPairing::Both(&GerudoTrainingGrounds_CentralMazeRight, []{return CanPlay(SongOfTime) || IsChild;}),
                  ExitPairing::Both(&GerudoTrainingGrounds_HammerRoom,       []{return CanUse("Longshot")  || (CanUse("Hover Boots") && CanUse("Hookshot"));}),
  });

  Exit GerudoTrainingGrounds_HammerRoom = Exit("Gerudo Training Grounds Hammer Room", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&GerudoTrainingGrounds_HammerRoomClearChest,  []{return true;}),
                  ItemLocationPairing(&GerudoTrainingGrounds_HammerRoomSwitchChest, []{return CanUse("Hammer");})
                }, {
                  //Exits
                  ExitPairing::Both(&GerudoTrainingGrounds_EyeStatueLower, []{return CanUse("Hammer") && Bow;}),
                  ExitPairing::Both(&GerudoTrainingGrounds_LavaRoom,       []{return true;}),
  });

  Exit GerudoTrainingGrounds_EyeStatueLower = Exit("Gerudo Training Grounds Eye Statue Lower", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&GerudoTrainingGrounds_EyeStatueChest, []{return CanUse("Bow");}),
                }, {
                  //Exits
                  ExitPairing::Both(&GerudoTrainingGrounds_HammerRoom, []{return true;}),
  });

  Exit GerudoTrainingGrounds_EyeStatueUpper = Exit("Gerudo Training Grounds Eye Statue Upper", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&GerudoTrainingGrounds_NearScarecrowChest, []{return CanUse("Bow");})
                }, {
                  //Exits
                  ExitPairing::Both(&GerudoTrainingGrounds_EyeStatueLower, []{return true;}),
  });

  Exit GerudoTrainingGrounds_HeavyBlockRoom = Exit("Gerudo Training Grounds Heavy Block Room", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&GerudoTrainingGrounds_BeforeHeavyBlockChest, []{return true;})
                }, {
                  //Exits
                  ExitPairing::Both(&GerudoTrainingGrounds_EyeStatueUpper, []{return (LogicLensGtg || CanUse("Lens of Truth")) && (CanUse("Hookshot") || (LogicGtgFakeWall && CanUse("Hover Boots")));}),
                  ExitPairing::Both(&GerudoTrainingGrounds_LikeLikeRoom,   []{return (LogicLensGtg || CanUse("Lens of Truth")) && (CanUse("Hookshot") || (LogicGtgFakeWall && CanUse("Hover Boots"))) && CanUse("Silver Gauntlets");}),
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
                  ExitPairing::Both(&GanonsCastle_LightTrial,  []{return CanUse("Golden Gauntlets");}),
                  ExitPairing::Both(&GanonsCastle_Tower,       []{return SkippedTrials || (ForestTrialClear && FireTrialClear && WaterTrialClear && ShadowTrialClear && SpiritTrialClear && LightTrialClear);}),
                  ExitPairing::Both(&GanonsCastle_DekuScrubs,  []{return LogicLensCastle || CanUse("Lens of Truth");}),
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
                  EventPairing(&ForestTrialClear, []{return CanUse("Light Arrows") && (FireArrows || DinsFire);}),
                }, {
                  //Locations
                  ItemLocationPairing(&GanonsCastle_ForestTrialChest, []{return true;}),
  }, {});

  Exit GanonsCastle_FireTrial = Exit("Ganon's Castle Fire Trial", "Ganon's Castle", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&FireTrialClear, []{return CanUse("Goron Tunic") && CanUse("Golden Gauntlets") && CanUse("Light Arrows") && CanUse("Longshot");}),
  }, {}, {});

  Exit GanonsCastle_WaterTrial = Exit("Ganon's Castle Water Trial", "Ganon's Castle", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&BlueFireAccess,  []{return true;}),
                  EventPairing(&FairyPot,        []{return FairyPot || BlueFire;}),
                  EventPairing(&WaterTrialClear, []{return BlueFire && Hammer && CanUse("Light Arrows");}),
                }, {
                  //Locations
                  ItemLocationPairing(&GanonsCastle_WaterTrialLeftChest,  []{return true;}),
                  ItemLocationPairing(&GanonsCastle_WaterTrialRightChest, []{return true;}),
  }, {});

  Exit GanonsCastle_ShadowTrial = Exit("Ganon's Castle Shadow Trial", "Ganon's Castle", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&ShadowTrialClear, []{return CanUse("Light Arrows") && Hammer && ((FireArrows && (LogicLensCastle || CanUse("Lens of Truth"))) || (CanUse("Longshot") && (HoverBoots || (DinsFire && (LogicLensCastle || CanUse("Lens of Truth"))))));}),
                }, {
                  //Locations
                  ItemLocationPairing(&GanonsCastle_ShadowTrialFrontChest,           []{return CanUse("Fire Arrows") || Hookshot || HoverBoots || CanPlay(SongOfTime);}),
                  ItemLocationPairing(&GanonsCastle_ShadowTrialGoldenGauntletsChest, []{return CanUse("Fire Arrows") || (CanUse("Longshot") && (HoverBoots || CanUse("Dins Fire")));}),
  }, {});

  Exit GanonsCastle_SpiritTrial = Exit("Ganon's Castle Spirit Trial", "Ganon's Castle", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&NutPot,           []{return NutPot || ((LogicSpiritTrialHookshot || Hookshot) && HasBombchus && Bow && MirrorShield);}),
                  EventPairing(&SpiritTrialClear, []{return CanUse("Light Arrows")  && MirrorShield && HasBombchus && (LogicSpiritTrialHookshot || Hookshot);}),
                }, {
                  //Locations
                  ItemLocationPairing(&GanonsCastle_SpiritTrialCrystalSwitchChest, []{return LogicSpiritTrialHookshot || Hookshot;}),
                  ItemLocationPairing(&GanonsCastle_SpiritTrialInvisibleChest,     []{return (LogicSpiritTrialHookshot || Hookshot) && HasBombchus && (LogicLensCastle || CanUse("Lens of Truth"));}),
  }, {});

  Exit GanonsCastle_LightTrial = Exit("Ganon's Castle Light Trial", "Ganon's Castle", "", NO_DAY_NIGHT_CYCLE, {
                  //Events
                  EventPairing(&LightTrialClear, []{return CanUse("Light Arrows") && Hookshot && SmallKeys(GanonsCastleKeys, 2) && (LogicLensCastle || CanUse("Lens of Truth"));}),
                }, {
                  //Locations
                  ItemLocationPairing(&GanonsCastle_LightTrialFirstLeftChest,        []{return true;}),
                  ItemLocationPairing(&GanonsCastle_LightTrialSecondLeftChest,       []{return true;}),
                  ItemLocationPairing(&GanonsCastle_LightTrialThirdLeftChest,        []{return true;}),
                  ItemLocationPairing(&GanonsCastle_LightTrialFirstRightChest,       []{return true;}),
                  ItemLocationPairing(&GanonsCastle_LightTrialSecondRightChest,      []{return true;}),
                  ItemLocationPairing(&GanonsCastle_LightTrialThirdRightChest,       []{return true;}),
                  ItemLocationPairing(&GanonsCastle_LightTrialInvisibleEnemiesChest, []{return LogicLensCastle || CanUse("Lens of Truth");}),
                  ItemLocationPairing(&GanonsCastle_LightTrialLullabyChest,          []{return CanPlay(ZeldasLullaby) && SmallKeys(GanonsCastleKeys, 1);}),
  }, {});

  Exit GanonsCastle_Tower = Exit("Ganon's Castle Tower", "Ganons Castle", "", NO_DAY_NIGHT_CYCLE, {}, {
                  //Locations
                  ItemLocationPairing(&GanonsCastle_BossKeyChest, []{return true;}),
                  //Ganondorf Hint
                  ItemLocationPairing(&Ganon, []{return BossKeyGanonsCastle && CanUse("Light Arrows");}),
  }, {});

  /*---------------------------
  |   MASTER QUEST DUNGEONS   |
  ---------------------------*/

  Exit DekuTree_MQ_Lobby = Exit("Deku Tree MQ Lobby", "Deku Tree", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&DekuBabaSticks, []{return DekuBabaSticks || (IsAdult || KokiriSword || Boomerang);}),
    EventPairing(&DekuBabaNuts,   []{return DekuBabaNuts   || (IsAdult || KokiriSword || Slingshot || Sticks || HasExplosives || CanUse("Dins Fire"));}),
  }, {
    //Locations
    ItemLocationPairing(&DekuTree_MQ_MapChest,               []{return true;}),
    ItemLocationPairing(&DekuTree_MQ_SlingshotChest,         []{return IsAdult || CanChildAttack;}),
    ItemLocationPairing(&DekuTree_MQ_SlingshotRoomBackChest, []{return HasFireSourceWithTorch || CanUse("Bow");}),
    ItemLocationPairing(&DekuTree_MQ_BasementChest,          []{return HasFireSourceWithTorch || CanUse("Bow");}),
    ItemLocationPairing(&DekuTree_MQ_GS_Lobby,               []{return IsAdult || CanChildAttack;}),
  }, {
    //Exits
    ExitPairing(&KF_OutsideDekuTree,            []{return true;}),
    ExitPairing(&DekuTree_MQ_CompassRoom,       []{return (CanUse("Slingshot") || CanUse("Bow")) && (HasFireSourceWithTorch || CanUse("Bow"));}),
    ExitPairing(&DekuTree_MQ_BasementWaterRoom, []{return (CanUse("Slingshot") || CanUse("Bow")) && HasFireSourceWithTorch;}),
    ExitPairing(&DekuTree_MQ_BasementLedge,     []{return LogicDekuB1Skip || IsAdult;}),
  });

  Exit DekuTree_MQ_CompassRoom = Exit("Deku Tree MQ Compass Room", "Deku Tree", "", NO_DAY_NIGHT_CYCLE, {}, {
    //Locations
    ItemLocationPairing(&DekuTree_MQ_CompassChest, []{return true;}),
    ItemLocationPairing(&DekuTree_MQ_GS_CompassRoom, []{return (CanUse("Hookshot") || CanUse("Boomerang")) && (HasBombchus || (Bombs && (IsAdult || CanPlay(SongOfTime))));}),
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
    ItemLocationPairing(&DekuTree_MQ_GS_BasementGravesRoom, []{return CanUse("Longshot") || (CanPlay(SongOfTime) && HookshotOrBoomerang);}),
    ItemLocationPairing(&DekuTree_MQ_GS_BasementBackRoom,   []{return HasFireSourceWithTorch && HookshotOrBoomerang;})
  }, {
    //Exits
    ExitPairing(&DekuTree_MQ_BasementLedge,     []{return IsChild;}),
    ExitPairing(&DekuTree_MQ_BasementWaterRoom, []{return CanUse("Kokiri Sword") || CanUseProjectile || (Nuts && CanUse("Sticks"));}),
  });

  Exit DekuTree_MQ_BasementLedge = Exit("Deku Tree MQ Basement Ledge", "Deku Tree", "", NO_DAY_NIGHT_CYCLE, {
    //Events
    EventPairing(&DekuTreeClear, []{return HasFireSourceWithTorch && HasShield && (IsAdult || KokiriSword || Sticks);}),
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

  //TODO: Rest of MQ Dungeons

  /*
  //Events
}, {
  //Locations
}, {
  //Exits
*/

  std::array<Exit *, 213> allExits = {

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
  };

  void AccessReset() {
    for (Exit* exit : allExits) {
      exit->ResetVariables();
    }

    if(Settings::HasNightStart) {
        if(Settings::StartingAge.Is(AGE_CHILD)) {
          Exits::Root.nightChild = true;
        } else {
          Exits::Root.nightAdult = true;
        }
      } else {
        if(Settings::StartingAge.Is(AGE_CHILD)) {
          Exits::Root.dayChild = true;
        } else {
          Exits::Root.dayAdult = true;
        }
    }
  }
}
