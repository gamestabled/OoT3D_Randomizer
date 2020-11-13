#include "location_access.hpp"
#include "settings.hpp"
#include "logic.hpp"
#include "item_location.hpp"
#include "item_list.hpp"
#include <tuple>
#include <unistd.h>

using namespace Logic;
using namespace Settings;

bool DAY_NIGHT_CYCLE    = true;
bool NO_DAY_NIGHT_CYCLE = false;

//TODO: Update all advancement logic needs for every area
namespace Exits { //name, scene, hint, events, locations, exits, advancement items

  Exit Root = Exit("Root", "", "Link's Pocket", NO_DAY_NIGHT_CYCLE, []{
                  return true;
                }, {
                  //Locations
                  //ItemLocationPairing(&LinksPocket, []{return true;})
                }, {
                  //Exits
                  ExitPairing(&RootExits, []{return true;}) //is_starting_age || Time_Travel
  });

  Exit RootExits = Exit("Root Exits", "", "", NO_DAY_NIGHT_CYCLE, []{
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&KF_LinksHouse,    []{return IsChild;}),
                  ExitPairing(&ToT_Main,         []{return (CanPlay(PreludeOfLight)   && CanLeaveForest) || IsAdult;}),
                  ExitPairing(&SFM_Main,         []{return  CanPlay(MinuetOfForest);}),
                  ExitPairing(&DMC_CentralLocal, []{return  CanPlay(BoleroOfFire)     && CanLeaveForest;}),
                  ExitPairing(&LH_Main,          []{return  CanPlay(SerenadeOfWater)  && CanLeaveForest;}),
                  ExitPairing(&GY_WarpPadRegion, []{return  CanPlay(NocturneOfShadow) && CanLeaveForest;}),
                  ExitPairing(&Colossus_Main,    []{return  CanPlay(RequiemOfSpirit)  && CanLeaveForest;})
               }, {
                  //Advancement Needs
                  AdvancementPairing(A_ProgressiveOcarina, []{return AddedProgressiveOcarinas == 0;}),
                  AdvancementPairing(A_MinuetOfForest,     []{return CanLeaveForest && ProgressiveOcarina       >= 1 && !SFM_Main.BothAges();}),
                  AdvancementPairing(A_BoleroOfFire,       []{return CanLeaveForest && ProgressiveOcarina       >= 1;}),
                  AdvancementPairing(A_SerenadeOfWater,    []{return CanLeaveForest && ProgressiveOcarina       >= 1 && !LH_Main.BothAges();}),
                  AdvancementPairing(A_RequiemOfSpirit,    []{return CanLeaveForest && ProgressiveOcarina       >= 1;}),
                  AdvancementPairing(A_NocturneOfShadow,   []{return CanLeaveForest && ProgressiveOcarina       >= 1;}),
                  AdvancementPairing(A_PreludeOfLight,     []{return CanLeaveForest && ProgressiveOcarina       >= 1 && !ToT_Main.BothAges();}),
  });

  Exit KF_Main = Exit("Kokiri Forest", "Kokiri Forest", "Kokiri Forest", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  BeanPlantFairy           = BeanPlantFairy   || (KF_Main.CanPlantBean() && CanPlay(SongOfStorms));
                  GossipStoneFairy         = GossipStoneFairy || CanSummonGossipFairyWithoutSuns;
                  ShowedMidoSwordAndShield = OpenForest == "Open" || (IsChild && KokiriSword && DekuShield);
                  return ShowedMidoSwordAndShield && BeanPlantFairy && GossipStoneFairy;
                }, {
                  //Locations
                  ItemLocationPairing(&KF_KokiriSwordChest,  []{return IsChild;}),
                  ItemLocationPairing(&KF_GS_KnowItAllHouse, []{return IsChild && CanChildAttack && AtNight && (HasNightStart || CanLeaveForest || CanPlay(SunsSong));}),
                  ItemLocationPairing(&KF_GS_BeanPatch,      []{return CanPlantBugs && CanChildAttack;}),
                  ItemLocationPairing(&KF_GS_HouseOfTwins,   []{return IsAdult && AtNight && CanUse("Hookshot");}),
                }, {
                  //Exits
                  ExitPairing(&KF_LinksHouse,       []{return true;}),
                  ExitPairing(&KF_MidosHouse,       []{return true;}),
                  ExitPairing(&KF_SariasHouse,      []{return true;}),
                  ExitPairing(&KF_HouseOfTwins,     []{return true;}),
                  ExitPairing(&KF_KnowItAllHouse,   []{return true;}),
                  ExitPairing(&KF_KokiriShop,       []{return true;}),
                  ExitPairing(&KF_OutsideDekuTree,  []{return IsAdult || ShowedMidoSwordAndShield;}),
                  ExitPairing(&LW_Main,             []{return true;}),
                  ExitPairing(&LW_BridgeFromForest, []{return CanLeaveForest;}),
                  ExitPairing(&KF_StormsGrotto,     []{return CanOpenStormGrotto;})
               }, {
                  //Advancement Needs
                  AdvancementPairing(A_KokiriSword,        []{return IsChild;}),
                  AdvancementPairing(A_DekuShield,         []{return IsChild && Shopsanity && OpenForest != "Open";}),
                  AdvancementPairing(A_SongOfStorms,       []{return ProgressiveOcarina >= 1;}),
});

  Exit KF_OutsideDekuTree = Exit("KF Outside Deku Tree", "Kokiri Forest", "Kokiri Forest", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  DekuBabaSticks = DekuBabaSticks || ((IsAdult && !ShuffleDungeonEntrances) || KokiriSword || Boomerang);
                  DekuBabaNuts   = DekuBabaNuts   || ((IsAdult && !ShuffleDungeonEntrances) || KokiriSword || Slingshot || Sticks || HasExplosives || CanUse("Dins Fire"));
                  return DekuBabaSticks && DekuBabaNuts;
                }, {
                  //Locations
                  // ItemLocationPairing(&KF_DekuTreeGossipStoneLeft,  []{return true;}),
                  // ItemLocationPairing(&KF_DekuTreeGossipStoneRight, []{return true;})
                }, {
                  //Exits
                  ExitPairing(&DekuTree_Lobby, []{return IsChild || (ShuffleDungeonEntrances && ShowedMidoSwordAndShield);}),
                  ExitPairing(&KF_Main,        []{return true;}),
  });

  Exit KF_LinksHouse = Exit("KF Link's House", "", "", NO_DAY_NIGHT_CYCLE, []{
                  return true;
                }, {
                  //Locations
                  //ItemLocationPairing(&KF_LinksHouseCow, []{return IsAdult && CanPlay(EponasSong) && LinksCow;})
                }, {
                  //Exits
                  ExitPairing(&KF_Main, []{return true;})
  });

  Exit KF_MidosHouse = Exit("KF Mido's House", "", "", NO_DAY_NIGHT_CYCLE, []{
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&KF_MidoTopLeftChest,     []{return true;}),
                  ItemLocationPairing(&KF_MidoTopRightChest,    []{return true;}),
                  ItemLocationPairing(&KF_MidoBottomLeftChest,  []{return true;}),
                  ItemLocationPairing(&KF_MidoBottomRightChest, []{return true;}),
                }, {
                  //Exits
                  ExitPairing(&KF_Main, []{return true;}),
  });

  Exit KF_SariasHouse = Exit("KF Saria's House", "", "", NO_DAY_NIGHT_CYCLE, []{
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&KF_Main, []{return true;}),
  });

  Exit KF_HouseOfTwins = Exit("KF House of Twins", "", "", NO_DAY_NIGHT_CYCLE, []{
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&KF_Main, []{return true;}),
  });

  Exit KF_KnowItAllHouse = Exit("KF Know It All House", "", "", NO_DAY_NIGHT_CYCLE, []{
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&KF_Main, []{return true;}),
  });

  Exit KF_KokiriShop = Exit("KF Kokiri Shop", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  BuyDekuShield = true;
                  BuyDekuStick1 = true;
                  return true; //BuyDekuShield && BuyDekuStick1;
                }, {
                  //Locations
                  // ItemLocationPairing(&KF_KokiriShopItem1, []{return true;}),
                  // ItemLocationPairing(&KF_KokiriShopItem2, []{return true;}),
                  // ItemLocationPairing(&KF_KokiriShopItem3, []{return true;}),
                  // ItemLocationPairing(&KF_KokiriShopItem4, []{return true;}),
                  // ItemLocationPairing(&KF_KokiriShopItem5, []{return true;}),
                  // ItemLocationPairing(&KF_KokiriShopItem6, []{return true;}),
                  // ItemLocationPairing(&KF_KokiriShopItem7, []{return true;}),
                  // ItemLocationPairing(&KF_KokiriShopItem8, []{return true;})
                }, {
                  //Exits
                  ExitPairing(&KF_Main, []{return true;})
  });

  Exit KF_StormsGrotto = Exit("KF Storms Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  GenericGrottoChecks();
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&KF_StormsGrottoChest,       []{return true;})
                  // ItemLocationPairing(&KF_StormsGrottoGossipStone, []{return true;}),
                }, {
                  //Exits
                  ExitPairing(&KF_Main, []{return true;})
  });

  Exit LW_ForestExit = Exit("LW Forest Exit", "Lost Woods", "", NO_DAY_NIGHT_CYCLE, []{
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&KF_Main, []{return true;})
  });

  Exit LW_Main = Exit("Lost Woods", "Lost Woods", "the Lost Woods", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  //OddMushroomAccess
                  //PoachersSawAccess
                  GossipStoneFairy = GossipStoneFairy || CanSummonGossipFairyWithoutSuns;
                  BeanPlantFairy   = BeanPlantFairy   || CanPlay(SongOfStorms);
                  BugShrub         = IsChild && CanCutShrubs;
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&LW_SkullKid,               []{return IsChild && CanPlay(SariasSong);}),
                //ItemLocationPairing(&LW_OcarinaMemoryGame,      []{return IsChild && Ocarina;}),
                  ItemLocationPairing(&LW_TargetInWoods,          []{return CanUse("Slingshot");}),
                //ItemLocationPairing(&LW_DekuScrubNearBridge,    []{return IsChild && CanStunDeku;}),
                  ItemLocationPairing(&LW_GS_BeanPatchNearBridge, []{return CanPlantBugs && CanChildAttack;}),
                  //LW Gossip Stone
                }, {
                  //Exits
                  ExitPairing(&LW_ForestExit, []{return true;}),
                  ExitPairing(&GC_WoodsWarp,  []{return true;}),
                  ExitPairing(&LW_Bridge,     []{return IsAdult && (CanUse("Hover Boots") || CanUse("Longshot") || LW_Main.CanPlantBean() || LogicLostWoodsBridge);}),
                  ExitPairing(&ZR_Main,       []{return CanLeaveForest && (CanDive || CanUse("Iron Boots"));}),
                  ExitPairing(&LW_BeyondMido, []{return IsChild || CanPlay(SariasSong);}),
                  ExitPairing(&LW_NearShortcutsGrotto, []{return CanBlastOrSmash;})
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_ProgressiveBulletBag, []{return AddedProgressiveBulletBags == 0 && IsChild;}),
                  AdvancementPairing(A_ProgressiveBombBag,   []{return AddedProgressiveBombBags   == 0 && (IsChild || (IsAdult && !Hammer));}),
                  AdvancementPairing(A_ProgressiveScale,     []{return AddedProgressiveScales     == 0 && CanLeaveForest;}),
                  AdvancementPairing(A_SariasSong,           []{return ProgressiveOcarina         >= 1 && IsAdult;}),
                  AdvancementPairing(A_ProgressiveHookshot,  []{return AddedProgressiveHookshots  == 1 && IsAdult && !LogicLostWoodsBridge && !LW_Main.CanPlantBean() && !HoverBoots;}),
                  AdvancementPairing(A_HoverBoots,           []{return AddedProgressiveHookshots  <= 2 && IsAdult && !LogicLostWoodsBridge && !LW_Main.CanPlantBean();}),
                  AdvancementPairing(A_IronBoots,            []{return AddedProgressiveScales     == 0 && IsAdult;}),
                  AdvancementPairing(A_MegatonHammer,        []{return AddedProgressiveBombBags   == 0 && IsAdult;}),
  });

  Exit LW_BeyondMido = Exit("LW Beyond Mido", "Lost Woods", "Lost Woods", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  ButterflyFairy = ButterflyFairy || CanUse("Sticks");
                  return true;
                }, {
                  //Locations
                  //ItemLocationPairing(&LW_DekuScrubNearDekuTheaterRight, []{return IsChild && CanStunDeku;}),
                  //ItemLocationPairing(&LW_DekuScrubNearDekuTheaterLeft,  []{return IsChild && CanStunDeku;})
                  ItemLocationPairing(&LW_GS_AboveTheater,         []{return IsAdult && AtNight && (LW_BeyondMido.CanPlantBean() || (LogicLostWoodsGSBean && CanUse("Hookshot") && (CanUse("Longshot") || CanUse("Bow") || HasBombchus || CanUse("Dins Fire"))));}),
                  ItemLocationPairing(&LW_GS_BeanPatchNearTheater, []{return CanPlantBugs && (CanChildAttack || (Scrubsanity == "Off" && BuyDekuShield));}),
                }, {
                  //Exits
                  ExitPairing(&LW_ForestExit,   []{return true;}),
                  ExitPairing(&LW_Main,         []{return IsChild || CanPlay(SariasSong);}),
                  ExitPairing(&SFM_Entryway,    []{return true;}),
                  ExitPairing(&LW_DekuTheater,  []{return true;}),
                  ExitPairing(&LW_ScrubsGrotto, []{return CanBlastOrSmash;})
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_SariasSong,           []{return ProgressiveOcarina       >= 1 && IsAdult;}),
                  AdvancementPairing(A_ProgressiveBombBag,   []{return AddedProgressiveBombBags == 0 && (IsChild || (IsAdult && !Hammer));}),
                  AdvancementPairing(A_MegatonHammer,        []{return AddedProgressiveBombBags == 0 && IsAdult;}),

  });

  Exit LW_NearShortcutsGrotto = Exit("LW Near Shortcuts Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  GenericGrottoChecks();
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&LW_NearShortcutsGrottoChest, []{return true;})
                  //LW Near Shortcuts Grotto Gossip Stone
                }, {
                  //Exits
                  ExitPairing(&LW_Main, []{return true;})
  });

  Exit LW_DekuTheater = Exit("Deku Theater", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&DekuTheater_SkullMask,   []{return IsChild && SkullMask;}),
                  ItemLocationPairing(&DekuTheater_MaskOfTruth, []{return IsChild && MaskOfTruth;}),
                }, {
                  //Exits
                  ExitPairing(&LW_BeyondMido, []{return true;}),
  });

  Exit LW_ScrubsGrotto = Exit("LW Scrubs Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //ItemLocationPairing(&LW_DekuScrubGrottoRear,  []{return CanStunDeku;}),
                  //ItemLocationPairing(&LW_DekuScrubGrottoFront, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing(&LW_BeyondMido, []{return true;}),
  });

  Exit SFM_Entryway = Exit("SFM Entryway", "Sacred Forest Meadow", "Sacred Forest Meadow", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&LW_BeyondMido,    []{return true;}),
                  ExitPairing(&SFM_Main,         []{return IsAdult || Slingshot || Sticks || KokiriSword || CanUse("Dins Fire");}),
                  ExitPairing(&SFM_WolfosGrotto, []{return CanOpenBombGrotto;}),
                }, {
                  AdvancementPairing(A_ProgressiveBombBag,   []{return AddedProgressiveBombBags == 0;}),
                  AdvancementPairing(A_ProgressiveMagic,     []{return AddedProgressiveMagics   == 0 && !KokiriSword && !Sticks && !Slingshot && IsChild;}),
                  AdvancementPairing(A_DinsFire,             []{return ProgressiveMagic         >= 1 && !KokiriSword && !Sticks && !Slingshot && IsChild;}),
  });

  Exit SFM_Main = Exit("Sacred Forest Meadow", "Sacred Forest Meadow", "Sacred Forest Meadow", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  GossipStoneFairy = GossipStoneFairy || CanSummonGossipFairyWithoutSuns;
                  return true;
                }, {
                  //Locations
                  //Song from Saria
                  //Sheik in Forest
                  ItemLocationPairing(&SFM_GS, []{return CanUse("Hookshot") && AtNight;}),
                  //SFM Maze Gossip Stone (Lower)
                  //SFM Maze Gossip Stone (Upper)
                  //SFM Saria Gossip Stone
                }, {
                  //Exits
                  ExitPairing(&SFM_Entryway,       []{return true;}),
                  ExitPairing(&ForestTemple_Lobby, []{return CanUse("Hookshot");}),
                  ExitPairing(&SFM_FairyGrotto,    []{return true;}),
                  ExitPairing(&SFM_StormsGrotto,   []{return CanOpenStormGrotto;}),
                }, {
                  //advancement needs
                  AdvancementPairing(A_ProgressiveHookshot,  []{return AddedProgressiveHookshots == 0 && IsAdult;}),
                  AdvancementPairing(A_SongOfStorms,         []{return ProgressiveOcarina        >= 1;}),

  });

  Exit SFM_FairyGrotto = Exit("SFM Fairy Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  FreeFairies = true;
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&SFM_Main, []{return true;}),
  });

  Exit SFM_WolfosGrotto = Exit("SFM Wolfos Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&SFM_WolfosGrottoChest, []{return IsAdult || Slingshot || Sticks || KokiriSword || CanUse("Dins Fire");})
                }, {
                  //Exits
                  ExitPairing(&SFM_Main, []{return true;}),
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_KokiriSword,          []{return !Sticks && !Slingshot && !DinsFire && IsChild;}),
                  AdvancementPairing(A_ProgressiveBulletBag, []{return AddedProgressiveBulletBags == 0 && !KokiriSword && !Sticks && !MagicMeter && IsChild;}),
                  AdvancementPairing(A_ProgressiveMagic,     []{return AddedProgressiveMagics     == 0 && !KokiriSword && !Sticks && !Slingshot  && IsChild;}),
                  AdvancementPairing(A_DinsFire,             []{return ProgressiveMagic           >= 1 && !KokiriSword && !Sticks && !Slingshot  && IsChild;}),

  });

  Exit SFM_StormsGrotto = Exit("SFM Storms Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //ItemLocationPairing(&SFM_DekuScrubGrottoRear,  []{return CanStunDeku;}),
                  //ItemLocationPairing(&SFM_DekuScrubGrottoFront, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing(&SFM_Main, []{return true;})
  });

  Exit LW_BridgeFromForest = Exit("LW Bridge From Forest", "Lost Woods", "the Lost Woods", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  // ItemLocationPairing(&LW_GiftFromSaria, []{return true;})
                }, {
                  //Exits
                  ExitPairing(&LW_Bridge, []{return true;})
  });

  Exit LW_Bridge = Exit("LW Bridge", "Lost Woods", "the Lost Woods", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&KF_Main, []{return true;}),
                  ExitPairing(&HF_Main, []{return true;}),
                  ExitPairing(&LW_Main, []{return CanUse("Longshot");})
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_ProgressiveHookshot,  []{return AddedProgressiveHookshots == 1 && IsAdult;}),
  });

  Exit HF_Main = Exit("Hyrule Field", "Hyrule Field", "Hyrule Field", DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&HF_OcarinaOfTimeItem, []{return IsChild && HasAllStones;}),
                  //Song from Ocarina of Time
                  //Big Poe Kill
                }, {
                  //Exits
                  ExitPairing(&LW_Bridge,            []{return true;}),
                  ExitPairing(&LH_Main,              []{return true;}),
                  ExitPairing(&GV_Main,              []{return true;}),
                  ExitPairing(&MK_Entrance,          []{return true;}),
                  ExitPairing(&Kak_Main,             []{return true;}),
                  ExitPairing(&ZR_Front,             []{return true;}),
                  ExitPairing(&LLR_Main,             []{return true;}),
                  ExitPairing(&HF_SoutheastGrotto,   []{return CanBlastOrSmash;}),
                  ExitPairing(&HF_OpenGrotto,        []{return true;}),
                  ExitPairing(&HF_InsideFenceGrotto, []{return CanOpenBombGrotto;}),
                  ExitPairing(&HF_CowGrotto,         []{return (CanUse("Hammer") || IsChild) && CanOpenBombGrotto;}),
                  ExitPairing(&HF_NearMarketGrotto,  []{return CanBlastOrSmash;}),
                  ExitPairing(&HF_FairyGrotto,       []{return CanBlastOrSmash;}),
                  ExitPairing(&HF_NearKakGrotto,     []{return CanOpenBombGrotto;}),
                  ExitPairing(&HF_TektiteGrotto,     []{return CanOpenBombGrotto;})
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_ProgressiveBombBag, []{return AddedProgressiveBombBags == 0;}),
                  AdvancementPairing(A_MegatonHammer,      []{return AddedProgressiveBombBags == 0 && IsAdult && !Hammer;}),
  });

  Exit HF_SoutheastGrotto = Exit("HF Southeast Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  GenericGrottoChecks();
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&HF_SoutheastGrottoChest, []{return true;})
                  //HF Open Grotto Gossip Stone
                }, {
                  //Exits
                  ExitPairing(&HF_Main, []{return true;})
  });

  Exit HF_OpenGrotto = Exit("HF Open Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  GenericGrottoChecks();
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&HF_OpenGrottoChest, []{return true;})
                  //HF Open Grotto Gossip Stone
                }, {
                  //Exits
                  ExitPairing(&HF_Main, []{return true;})
  });

  Exit HF_InsideFenceGrotto = Exit("HF Inside Fence Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&HF_DekuScrubGrotto, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing(&HF_Main, []{return true;})
  });

  Exit HF_CowGrotto = Exit("HF Cow Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  GenericGrottoChecks();
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&HF_GS_CowGrotto, []{return HasFireSource && HookshotOrBoomerang;}),
                  //HF Cow Grotto Cow
                  //HF Open Grotto Gossip Stone
                }, {
                  //Exits
                  ExitPairing(&HF_Main, []{return true;})
  });

  Exit HF_NearMarketGrotto = Exit("HF Near Market Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  GenericGrottoChecks();
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&HF_NearMarketGrottoChest, []{return true;})
                  //HF Open Grotto Gossip Stone
                }, {
                  //Exits
                  ExitPairing(&HF_Main, []{return true;})
  });

  Exit HF_FairyGrotto = Exit("HF Fairy Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  FreeFairies = true;
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&HF_Main, []{return true;})
  });

  Exit HF_NearKakGrotto = Exit("HF Near Kak Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&HF_GS_NearKakGrotto, []{return HookshotOrBoomerang;}),
                }, {
                  //Exits
                  ExitPairing(&HF_Main, []{return true;})
  });

  Exit HF_TektiteGrotto = Exit("HF Tektite Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&HF_TektiteGrottoFreestandingPoH, []{return ProgressiveScale >= 2 || CanUse("Iron Boots");}),
                }, {
                  //Exits
                  ExitPairing(&HF_Main, []{return true;}),
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_ProgressiveScale, []{return AddedProgressiveScales == 0;}),
                  AdvancementPairing(A_ProgressiveScale, []{return AddedProgressiveScales == 1;}),
                  AdvancementPairing(A_IronBoots,        []{return IsAdult && AddedProgressiveScales < 2;}),
  });

  Exit LH_Main = Exit("Lake Hylia", "Lake Hylia", "Lake Hylia", DAY_NIGHT_CYCLE, []{
                  //Events
                  GossipStoneFairy = GossipStoneFairy || CanSummonGossipFairy;
                  BeanPlantFairy   = BeanPlantFairy   || (LH_Main.CanPlantBean() && CanPlay(SongOfStorms));
                  ButterflyFairy   = ButterflyFairy   || CanUse("Sticks");
                  BugShrub         = BugShrub         || (IsChild && CanCutShrubs);
                  ScarecrowSong    = ScarecrowSong    || (Ocarina && LH_Main.BothAges());
                  return ScarecrowSong;
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
                  ExitPairing(&HF_Main,           []{return true;}),
                  ExitPairing(&ZD_Main,           []{return IsChild && CanDive;}),
                  ExitPairing(&LH_OwlFlight,      []{return IsChild;}),
                  ExitPairing(&LH_Lab,            []{return true;}),
                  ExitPairing(&LH_FishingHole,    []{return IsChild || CanUse("Scarecrow") || LH_Main.CanPlantBean() || WaterTempleClear;}),
                  ExitPairing(&WaterTemple_Lobby, []{return CanUse("Hookshot") && (CanUse("Iron Boots") || ((CanUse("Longshot") || LogicWaterHookshotEntry) && ProgressiveScale >= 2));}),
                  ExitPairing(&LH_Grotto,         []{return true;})
                }, {
                  AdvancementPairing(A_ProgressiveScale,     []{return AddedProgressiveScales     == 0 && IsChild;}),
                  AdvancementPairing(A_ProgressiveScale,     []{return AddedProgressiveScales     == 1 && IsAdult;}),
                  AdvancementPairing(A_ProgressiveHookshot,  []{return AddedProgressiveHookshots  == 0 && IsAdult;}),
                  AdvancementPairing(A_ProgressiveHookshot,  []{return AddedProgressiveHookshots  == 1 && IsAdult;}),
                  AdvancementPairing(A_ZoraTunic,            []{return IsAdult && !LogicFewerTunicRequirements;}),
                  AdvancementPairing(A_IronBoots,            []{return IsAdult;}),
  });

  Exit LH_OwlFlight = Exit("LH Owl Flight", "Lake Hylia", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&HF_Main, []{return true;})
  });

  Exit LH_Lab = Exit("LH Lab", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  //EyedropsAccess
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&LH_LabDive,     []{return ProgressiveScale >= 2 || (LogicLabDiving && IronBoots && CanUse("Hookshot"));}),
                  ItemLocationPairing(&LH_GS_LabCrate, []{return IronBoots && CanUse("Hookshot");}),
                }, {
                  //Exits
                  ExitPairing(&LH_Main, []{return true;})
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_ProgressiveHookshot,  []{return AddedProgressiveHookshots == 0 && IsAdult;}),
                  AdvancementPairing(A_ProgressiveScale,     []{return AddedProgressiveScales    == 0;}),
                  AdvancementPairing(A_ProgressiveScale,     []{return AddedProgressiveScales    == 1;}),
                  AdvancementPairing(A_IronBoots,            []{return IsAdult;}),
  });

  Exit LH_FishingHole = Exit("LH Fishing Hole", "", "", DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&LH_ChildFishing, []{return IsChild;}),
                  ItemLocationPairing(&LH_AdultFishing, []{return IsAdult;})
                }, {
                  //Exits
                  ExitPairing(&LH_Main, []{return true;})
  });

  Exit LH_Grotto = Exit("LH Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //ItemLocationPairing(&LH_DekuScrubGrottoLeft,   []{return CanStunDeku;}),
                  //ItemLocationPairing(&LH_DekuScrubGrottoRight,  []{return CanStunDeku;}),
                  //ItemLocationPairing(&LH_DekuScrubGrottoCenter, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing(&LH_Main, []{return true;})
  });

  Exit GV_Main = Exit("Gerudo Valley", "Gerudo Valley", "Gerudo Valley", DAY_NIGHT_CYCLE, []{
                  //Events
                  //time passes here
                  return true;
                }, {
                  //Locations
                  //GV GS Small Bridge
                  ItemLocationPairing(&GV_GS_SmallBridge, []{return CanUse("Boomerang") && AtNight;}),
                  //Bug Rock
                }, {
                  //Exits
                  ExitPairing(&HF_Main,          []{return true;}),
                  ExitPairing(&GV_Stream,        []{return true;}),
                  ExitPairing(&GV_CrateLedge,    []{return IsChild || CanUse("Longshot");}),
                  ExitPairing(&GV_OctorokGrotto, []{return CanUse("Silver Gauntlets");}),
                  ExitPairing(&GV_FortressSide,  []{return IsAdult && (CanRideEpona || CanUse("Longshot") || GerudoFortress == "Open" || CarpenterRescue);})
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_ProgressiveHookshot,  []{return AddedProgressiveHookshots  == 0 && IsAdult;}),
                  AdvancementPairing(A_ProgressiveHookshot,  []{return AddedProgressiveHookshots  == 1 && IsAdult;}),

  });

  Exit GV_Stream = Exit("GV Stream", "Gerudo Valley", "Gerudo Valley", DAY_NIGHT_CYCLE, []{
                  //Events
                  GossipStoneFairy = GossipStoneFairy || CanSummonGossipFairy;
                  BeanPlantFairy   = BeanPlantFairy   || (GV_Stream.CanPlantBean() && CanPlay(SongOfStorms));
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&GV_WaterfallFreestandingPoH, []{return true;}),
                  ItemLocationPairing(&GV_GS_BeanPatch,             []{return CanPlantBugs && CanChildAttack;}),
                  //GV Cow
                  //GV Gossip Stone
                }, {
                  //Exits
                  ExitPairing(&LH_Main, []{return true;})
  });

  Exit GV_CrateLedge = Exit("GV Crate Ledge", "Gerudo Valley", "Gerudo Valley", DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&GV_CrateFreestandingPoH, []{return true;}),
                }, {
                  //Exits
  });

  Exit GV_FortressSide = Exit("GV Fortress Side", "Gerudo Valley", "Gerudo Valley", DAY_NIGHT_CYCLE, []{
                  //Events
                  //BrokenSwordAccess
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&GV_Chest,         []{return CanUse("Hammer");}),
                  ItemLocationPairing(&GV_GS_BehindTent, []{return CanUse("Hookshot") && AtNight;}),
                  ItemLocationPairing(&GV_GS_Pillar,     []{return CanUse("Hookshot") && AtNight;}),
                }, {
                  //Exits
                  ExitPairing(&GF_Main,          []{return true;}),
                  ExitPairing(&GV_Stream,        []{return true;}),
                  ExitPairing(&GV_Main,          []{return IsChild || CanRideEpona || CanUse("Longshot") || GerudoFortress == "Open" || CarpenterRescue;}),
                  ExitPairing(&GV_CarpenterTent, []{return IsAdult;}),
                  ExitPairing(&GV_StormsGrotto,  []{return IsAdult && CanOpenStormGrotto;})
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_ProgressiveHookshot,  []{return AddedProgressiveHookshots == 0 && IsAdult;}),
                  AdvancementPairing(A_ProgressiveHookshot,  []{return AddedProgressiveHookshots == 1 && IsAdult;}),
                  AdvancementPairing(A_MegatonHammer,        []{return IsAdult;}),
  });

  Exit GV_CarpenterTent = Exit("GV Carpenter Tent", "", "", NO_DAY_NIGHT_CYCLE, []{
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&GV_Main, []{return true;})
  });

  Exit GV_OctorokGrotto = Exit("GV Octorok Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&GV_Main, []{return true;})
  });

  Exit GV_StormsGrotto = Exit("GV Storms Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //ItemLocationPairing(&GV_DekuScrubGrottoRear,  []{return CanStunDeku;}),
                  //ItemLocationPairing(&GV_DekuScrubGrottoFront, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing(&GV_FortressSide, []{return true;})
  });

  Exit GF_Main = Exit("Gerudo Fortress", "Gerudo Fortress", "Gerudo's Fortress", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  //CarpenterRescue = CanFinishGerudoFortress;
                  GF_GateOpen     = IsAdult && GerudoToken;
                  return /*CarpenterRescue &&*/ GF_GateOpen;
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
                  ExitPairing(&GV_FortressSide,             []{return true;}),
                  ExitPairing(&GF_OutsideGate,              []{return GF_GateOpen;}),
                  ExitPairing(&GerudoTrainingGrounds_Lobby, []{return IsAdult && GerudoToken;}),
                  ExitPairing(&GF_StormsGrotto,             []{return IsAdult && CanOpenStormGrotto;})
                }, {
                  AdvancementPairing(A_KokiriSword,           []{return IsChild;}),
                  AdvancementPairing(A_HoverBoots,            []{return IsAdult && AddedProgressiveBows == 0 && AddedProgressiveHookshots == 0;}),
                  AdvancementPairing(A_ProgressiveBow,        []{return IsAdult && AddedProgressiveBows == 0 && AddedProgressiveHookshots == 0 && !HoverBoots;}),
                  AdvancementPairing(A_ProgressiveHookshot,   []{return IsAdult && AddedProgressiveBows == 0 && AddedProgressiveHookshots == 0 && !HoverBoots;}),
                  AdvancementPairing(GerudoFortress_SmallKey, []{return true;}, 4),
  });

  Exit GF_OutsideGate = Exit("GF Outside Gate", "Gerudo Fortress", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  GF_GateOpen = IsAdult && GerudoToken && (ShuffleGerudoToken || ShuffleOverworldEntrances || ShuffleSpecialIndoorEntrances);
                  return GF_GateOpen;
                }, {}, {
                  //Exits
                  ExitPairing(&GF_Main,         []{return IsAdult || (ShuffleOverworldEntrances && GF_GateOpen);}),
                  ExitPairing(&HW_NearFortress, []{return true;})
  });

  Exit GF_StormsGrotto = Exit("GF Storms Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  FreeFairies = true;
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&GF_Main, []{return true;})
  });

  Exit HW_NearFortress = Exit("Wasteland Near Fortress", "Haunted Wasteland", "Haunted Wasteland", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&GF_OutsideGate, []{return true;}),
                  ExitPairing(&HW_Main,        []{return CanUse("Hover Boots") || CanUse("Longshot");}),
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_HoverBoots,           []{return IsAdult && AddedProgressiveHookshots < 2;}),
                  AdvancementPairing(A_ProgressiveHookshot,  []{return AddedProgressiveHookshots  == 0 && IsAdult && !HoverBoots;}),
                  AdvancementPairing(A_ProgressiveHookshot,  []{return AddedProgressiveHookshots  == 1 && IsAdult && !HoverBoots;}),
  });

  Exit HW_Main = Exit("Haunted Wasteland", "Haunted Wasteland", "Haunted Wasteland", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  FairyPot = true;
                  NutPot   = true;
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&HW_Chest, []{return HasFireSource;}),
                  //Wasteland Bombchu Salesman
                  ItemLocationPairing(&HW_GS,    []{return HookshotOrBoomerang;}),
                }, {
                  //Exits
                  ExitPairing(&HW_NearColossus, []{return LogicLensWasteland || CanUse("Lens of Truth");}),
                  ExitPairing(&HW_NearFortress, []{return CanUse("Hover Boots") || CanUse("Longshot");}),
                }, {
                  AdvancementPairing(A_ProgressiveMagic,    []{return AddedProgressiveMagics    == 0 && !LogicLensWasteland;}),
                  AdvancementPairing(A_LensOfTruth,         []{return ProgressiveMagic          >= 1 && !LogicLensWasteland;}),
                  AdvancementPairing(A_HoverBoots,          []{return AddedProgressiveHookshots == 0;}),
                  AdvancementPairing(A_ProgressiveHookshot, []{return AddedProgressiveHookshots == 1 && !HoverBoots;}),
                  AdvancementPairing(A_DinsFire,            []{return ProgressiveMagic          >= 1 && !FireArrows;}),
                  AdvancementPairing(A_FireArrows,          []{return ProgressiveMagic          >= 1 && ProgressiveBow >= 1 && !DinsFire;}),
  });

  Exit HW_NearColossus = Exit("Wasteland Near Colossus", "Haunted Wasteland", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&Colossus_Main, []{return true;}),
                  ExitPairing(&HW_Main,       []{return LogicReverseWasteland;})
  });

  Exit Colossus_Main = Exit("Desert Colossus", "Desert Colossus", "Desert Colossus", DAY_NIGHT_CYCLE, []{
                  //Events
                  FairyPond = FairyPond || CanPlay(SongOfStorms);
                  BugRock   = true;
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&Colossus_FreestandingPoH, []{return IsAdult && Colossus_Main.CanPlantBean();}),
                  //Sheik at Colossus
                  ItemLocationPairing(&Colossus_GS_BeanPatch,    []{return CanPlantBugs && CanChildAttack;}),
                  ItemLocationPairing(&Colossus_GS_Tree,         []{return CanUse("Hookshot") && AtNight;}),
                  ItemLocationPairing(&Colossus_GS_Hill,         []{return IsAdult && AtNight && (Colossus_Main.CanPlantBean() || CanUse("Longshot") || (LogicColossusGS && CanUse("Hookshot")));})
                  //Colossus Gossip Stone
                }, {
                  //Exits
                  ExitPairing(&Colossus_GreatFairyFountain, []{return HasExplosives;}),
                  ExitPairing(&SpiritTemple_Lobby,          []{return true;}),
                  ExitPairing(&HW_NearColossus,             []{return true;}),
                  ExitPairing(&Colossus_Grotto,             []{return CanUse("Silver Gauntlets");})
                }, {
                  AdvancementPairing(A_MagicBeanPack,       []{return Colossus_Main.BothAges();}),
                  AdvancementPairing(A_ProgressiveStrength, []{return AddedProgressiveStrengths == 1 && IsAdult;}),
                  AdvancementPairing(A_ProgressiveBombchus, []{return AddedProgressiveBombBags  == 0;}),
                  AdvancementPairing(A_ProgressiveBombBag,  []{return AddedProgressiveBombBags  == 0;}),
  });

  Exit Colossus_GreatFairyFountain = Exit("Colossus Great Fairy Fountain", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //Colossus Great Fairy Reward
                }, {
                  //Exits
                  ExitPairing(&Colossus_Main, []{return true;})
  });

  Exit Colossus_Grotto = Exit("Colossus Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //ItemLocationPairing(&Colossus_DekuScrubGrottoRear,  []{return CanStunDeku;}),
                  //ItemLocationPairing(&Colossus_DekuScrubGrottoFront, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing(&Colossus_Main, []{return true;})
  });

  Exit MK_Entrance = Exit("Market Entrance", "Market Entrance", "the Market", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&HF_Main, []{return IsAdult || AtDay;}, "Day"),
                  ExitPairing(&MK_Main, []{return true;}),
                  ExitPairing(&MK_GuardHouse, []{return true;})
  });

  Exit MK_Main = Exit("Market", "Market", "Market", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&MK_Entrance,          []{return true;}),
                  ExitPairing(&ToT_Entrance,         []{return true;}),
                  ExitPairing(&CastleGrounds,        []{return true;}),
                  ExitPairing(&MK_Bazaar,            []{return IsChild && AtDay;}, "Day"),
                  ExitPairing(&MK_MaskShop,          []{return IsChild && AtDay;}, "Day"),
                  ExitPairing(&MK_ShootingGallery,   []{return IsChild && AtDay;}, "Day"),
                  ExitPairing(&MK_BombchuBowling,    []{return IsChild;}),
                  ExitPairing(&MK_TreasureChestGame, []{return IsChild && AtNight;}, "Night"),
                  ExitPairing(&MK_PotionShop,        []{return IsChild && AtDay;}, "Day"),
                  ExitPairing(&MK_BombchuShop,       []{return IsChild && AtNight;}, "Night"),
                  ExitPairing(&MK_DogLadyHouse,      []{return IsChild;}),
                  ExitPairing(&MK_ManInGreenHouse,   []{return IsChild && AtNight;}, "Night")
  });

  Exit ToT_Entrance = Exit("ToT Entrance", "ToT Entrance", "the Market", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  GossipStoneFairy = GossipStoneFairy || CanSummonGossipFairyWithoutSuns;
                  return true;
                }, {
                  //Locations
                  //ToT Gossip Stone (Left)
                  //ToT Gossip Stone (Left-Center)
                  //ToT Gossip Stone (Right)
                  //ToT Gossip Stone (Right-Center)
                }, {
                  //Exits
                  ExitPairing(&MK_Main,  []{return true;}),
                  ExitPairing(&ToT_Main, []{return true;})
  });

  Exit ToT_Main = Exit("Temple of Time", "", "Temple of Time", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //ToT Light Arrow Cutscene
                }, {
                  //Exits
                  ExitPairing(&ToT_Entrance,         []{return true;}),
                  ExitPairing(&ToT_BeyondDoorOfTime, []{return CanPlay(SongOfTime) || OpenDoorOfTime;})
                }, {
                  AdvancementPairing(A_SongOfTime, []{return !OpenDoorOfTime;}),
  });

  Exit ToT_BeyondDoorOfTime = Exit("Beyond Door of Time", "", "Temple of Time", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  if (ToT_BeyondDoorOfTime.Child() && !ToT_BeyondDoorOfTime.Adult()) {
                    Root.dayAdult   = ToT_BeyondDoorOfTime.dayChild;
                    Root.nightAdult = ToT_BeyondDoorOfTime.nightChild;
                  } else if (!ToT_BeyondDoorOfTime.Child() && ToT_BeyondDoorOfTime.Adult()){
                    Root.dayChild   = ToT_BeyondDoorOfTime.dayAdult;
                    Root.nightChild = ToT_BeyondDoorOfTime.nightAdult;
                  }

                  return true;
                }, {
                  //Locations
                  //Master Sword Pedestal
                  //Sheik at Temple
                }, {
                  //Exits
                  ExitPairing(&ToT_Main, []{return true;})
  });

  Exit CastleGrounds = Exit("Castle Grounds", "Castle Grounds", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&MK_Main,     []{return true;}),
                  ExitPairing(&HC_Grounds,  []{return IsChild;}),
                  ExitPairing(&OGC_Grounds, []{return IsAdult;})
  });

  Exit HC_Grounds = Exit("Hyrule Castle Grounds", "Castle Grounds", "Hyrule Castle", DAY_NIGHT_CYCLE, []{
                  //Events
                  GossipStoneFairy = GossipStoneFairy || CanSummonGossipFairy;
                  ButterflyFairy   = ButterflyFairy   || CanUse("Sticks");
                  BugRock          = true;
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&HC_MalonEgg, []{return true;}),
                  ItemLocationPairing(&HC_GS_Tree,  []{return CanChildAttack;}),
                  //HC Malon Gossip Stone
                  //HC HC Rock Wall Gossip Stone
                }, {
                  //Exits
                  ExitPairing(&CastleGrounds,         []{return true;}),
                  ExitPairing(&HC_Garden,             []{return WeirdEgg || !ShuffleWeirdEgg;}),
                  ExitPairing(&HC_GreatFairyFountain, []{return HasExplosives;}),
                  ExitPairing(&HC_StormsGrotto,       []{return CanOpenStormGrotto;})
                }, {
                  AdvancementPairing(A_WeirdEgg,            []{return true;}),
                  AdvancementPairing(A_ProgressiveBombBag,  []{return IsChild && AddedProgressiveBombBags == 0;}),
                  AdvancementPairing(A_ProgressiveBombchus, []{return IsChild && AddedProgressiveBombBags == 0;}),
                  AdvancementPairing(A_SongOfStorms,        []{return IsChild && ProgressiveOcarina       >= 1;}),
  });

  Exit HC_Garden = Exit("HC Garden", "Castle Grounds", "Hyrule Castle", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  ZeldasLullaby = true;
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&HC_ZeldasLetter, []{return true;})
                  //Song From Impa
                }, {
                  //Exits
                  ExitPairing(&HC_Grounds, []{return true;})
  });

  Exit HC_GreatFairyFountain = Exit("HC Great Fairy Fountain", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //HC Great Fairy Reward
                }, {
                  //Exits
                  ExitPairing(&HC_Grounds, []{return true;})
  });

  Exit HC_StormsGrotto = Exit("HC Storms Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  NutPot           = NutPot           || CanBlastOrSmash;
                  GossipStoneFairy = GossipStoneFairy || (CanBlastOrSmash && CanSummonGossipFairy);
                  WanderingBugs    = WanderingBugs    || CanBlastOrSmash;
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&HC_GS_StormsGrotto, []{return CanBlastOrSmash && HookshotOrBoomerang;}),
                  //HC Storms Grotto Gossip Stone
                }, {
                  //Exits
                  ExitPairing(&HC_Grounds, []{return true;})
  });

  Exit OGC_Grounds = Exit("Ganon's Castle Grounds", "Castle Grounds", "outside Ganon's Castle", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&OGC_GS, []{return true;}),
                }, {
                  //Exits
                  ExitPairing(&CastleGrounds,          []{return AtNight;}, "Night"),
                  ExitPairing(&OGC_GreatFairyFountain, []{return CanUse("Golden Gauntlets") && AtNight;}, "Night"),
                  ExitPairing(&GanonsCastle_Lobby,     []{return CanBuildRainbowBridge;})
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_ProgressiveStrength, []{return IsAdult && AddedProgressiveStrengths == 0;}),
                  AdvancementPairing(A_ProgressiveStrength, []{return IsAdult && AddedProgressiveStrengths == 1;}),
                  AdvancementPairing(A_ProgressiveStrength, []{return IsAdult && AddedProgressiveStrengths == 2;}),
  });

  Exit OGC_GreatFairyFountain = Exit("OGC Great Fairy Fountain", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //OGC Great Fairy Reward
                }, {
                  //Exits
                  ExitPairing(&CastleGrounds, []{return true;}),
  });

  Exit MK_GuardHouse = Exit("Market Guard House", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  //Sell Big Poe
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&MK_10BigPoes,     []{return IsAdult && (BigPoe);}), //Needs additional logic
                  ItemLocationPairing(&MK_GS_GuardHouse, []{return IsChild;}),
                }, {
                  //Exits
                  ExitPairing(&MK_Entrance, []{return true;})
  });

  Exit MK_Bazaar = Exit("Market Bazaar", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //Market Bazaar Item 1
                  //Market Bazaar Item 2
                  //Market Bazaar Item 3
                  //Market Bazaar Item 4
                  //Market Bazaar Item 5
                  //Market Bazaar Item 6
                  //Market Bazaar Item 7
                  //Market Bazaar Item 8
                }, {
                  //Exits
                  ExitPairing(&MK_Main, []{return true;})
  });

  Exit MK_MaskShop = Exit("Market Mask Shop", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  //Skull Mask
                  //Mask Of Truth
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&MK_Main, []{return true;})
  });

  Exit MK_ShootingGallery = Exit("Market Shooting Gallery", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&MK_ShootingGalleryReward, []{return IsChild;})
                }, {
                  //Exits
                  ExitPairing(&MK_Main, []{return true;})
  });

  Exit MK_BombchuBowling = Exit("Market Bombchu Bowling", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //ItemLocationPairing(&MK_BombchuBowlingFirstPrize,  []{return FoundBombchus;}),
                  //ItemLocationPairing(&MK_BombchuBowlingSecondPrize, []{return FoundBombchus;})
                  //Market Bombchu Bowling Bombchus
                }, {
                  //Exits
                  ExitPairing(&MK_Main, []{return true;})
  });

  Exit MK_PotionShop = Exit("Market Potion Shop", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //Market Potion Shop Item 1
                  //Market Potion Shop Item 2
                  //Market Potion Shop Item 3
                  //Market Potion Shop Item 4
                  //Market Potion Shop Item 5
                  //Market Potion Shop Item 6
                  //Market Potion Shop Item 7
                  //Market Potion Shop Item 8
                }, {
                  //Exits
                  ExitPairing(&MK_Main, []{return true;})
  });

  Exit MK_TreasureChestGame = Exit("Market Treasure Chest Game", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&MK_TreasureChestGameReward, []{return CanUse("Lens of Truth");})
                }, {
                  //Exits
                  ExitPairing(&MK_Main, []{return true;})
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_LensOfTruth,      []{return IsChild && ProgressiveMagic       >= 1;}),
                  AdvancementPairing(A_ProgressiveMagic, []{return IsChild && AddedProgressiveMagics == 0;}),
  });

  Exit MK_BombchuShop = Exit("Market Bombchu Shop", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  if (GoronsRuby) {
                    BuyBombchus10 = true;
                    BuyBombchus20 = true;
                  }
                  return BuyBombchus10 && BuyBombchus20;
                }, {
                  //Locations
                  //Market Bombchu Shop Item 1
                  //Market Bombchu Shop Item 2
                  //Market Bombchu Shop Item 3
                  //Market Bombchu Shop Item 4
                  //Market Bombchu Shop Item 5
                  //Market Bombchu Shop Item 6
                  //Market Bombchu Shop Item 7
                  //Market Bombchu Shop Item 8
                }, {
                  //Exits
                  ExitPairing(&MK_Main, []{return true;})
  });

  Exit MK_DogLadyHouse = Exit("Market Dog Lady House", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&MK_LostDog, []{return AtNight;})
                }, {
                  //Exits
                  ExitPairing(&MK_Main, []{return true;})
  });

  Exit MK_ManInGreenHouse = Exit("Market Man in Green House", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                }, {
                  //Exits
                  ExitPairing(&MK_Main, []{return true;})
  });

  Exit Kak_Main = Exit("Kakariko Village", "Kakariko Village", "Kakariko Village", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  BugRock = true;
                  //Cojiro Access
                  //Kakariko Village Gate Open
                  KakarikoVillageGateOpen = ZeldasLetter;
                  return KakarikoVillageGateOpen;
                }, {
                  //Locations
                  //Sheik in Kakariko
                  ItemLocationPairing(&Kak_AnjuAsChild,               []{return IsChild && AtDay;}),
                  ItemLocationPairing(&Kak_AnjuAsAdult,               []{return IsAdult && AtDay;}),
                  ItemLocationPairing(&Kak_GS_HouseUnderConstruction, []{return IsChild && AtNight;}),
                  ItemLocationPairing(&Kak_GS_SkulltulaHouse,         []{return IsChild && AtNight;}),
                  ItemLocationPairing(&Kak_GS_GuardsHouse,            []{return IsChild && AtNight;}),
                  ItemLocationPairing(&Kak_GS_Tree,                   []{return IsChild && AtNight;}),
                  ItemLocationPairing(&Kak_GS_Watchtower,             []{return IsChild && (Slingshot || HasBombchus || (LogicKakarikoTowerGS && (Sticks || KokiriSword) && (DamageMultiplier != "OHKO" || Fairy || CanUse("Nayrus Love")))) && AtNight;}),
                  ItemLocationPairing(&Kak_GS_AboveImpasHouse,        []{return CanUse("Hookshot") && AtNight;}),
                }, {
                  //Exits
                  ExitPairing(&HF_Main,                []{return true;}),
                  ExitPairing(&Kak_CarpenterBossHouse, []{return true;}),
                  ExitPairing(&Kak_HouseOfSkulltula,   []{return true;}),
                  ExitPairing(&Kak_ImpasHouse,         []{return true;}),
                  ExitPairing(&Kak_Windmill,           []{return true;}),
                  ExitPairing(&Kak_Bazaar,             []{return IsAdult && AtDay;}, "Day"),
                  ExitPairing(&Kak_ShootingGallery,    []{return IsAdult && AtDay;}, "Day"),
                  ExitPairing(&BottomOfTheWell,        []{return DrainWell && (IsChild || ShuffleDungeonEntrances);}),
                  ExitPairing(&Kak_PotionShopFront,    []{return AtDay;}, "Day"),
                  ExitPairing(&Kak_PotionShopFront,    []{return IsChild;}),
                  ExitPairing(&Kak_RedeadGrotto,       []{return CanOpenBombGrotto;}),
                  ExitPairing(&Kak_ImpasLedge,         []{return (IsAdult && LogicVisibleCollision);}),
                  ExitPairing(&Kak_ImpasLedge,         []{return (IsChild && AtDay);}, "Day"),
                  ExitPairing(&Kak_Rooftop,            []{return CanUse("Hookshot") || (LogicManOnRoof && (IsAdult || Slingshot || HasBombchus || (LogicKakarikoTowerGS && (Sticks || KokiriSword) && (DamageMultiplier != "OHKO" || Fairy || CanUse("Nayrus Love")))));}),
                  ExitPairing(&Kak_Rooftop,            []{return LogicManOnRoof && AtDay;}, "Day"),
                  ExitPairing(&GY_Main,                []{return true;}),
                  ExitPairing(&Kak_BehindGate,         []{return true;})
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_ProgressiveBombBag,   []{return AddedProgressiveBombBags == 0;}),
                  AdvancementPairing(A_ZeldasLetter,         []{return IsChild;}),
                  AdvancementPairing(A_MegatonHammer,        []{return IsAdult;}),
                  AdvancementPairing(A_ProgressiveHookshot,  []{return IsAdult && AddedProgressiveHookshots == 0;}),
                  AdvancementPairing(A_ProgressiveBulletBag, []{return IsChild && AtNight && AddedProgressiveBulletBags == 0;})
  });

  Exit Kak_ImpasLedge = Exit("Kak Impas Ledge", "Kakariko Village", "Kakariko Village", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&Kak_ImpasHouseBack, []{return true;}),
                  ExitPairing(&Kak_Main,           []{return true;})
  });

  Exit Kak_Rooftop = Exit("Kak Rooftop", "Kakariko VIllage", "Kakariko Village", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&Kak_ManOnRoof, []{return true;})
                }, {
                  //Exits
                  ExitPairing(&Kak_Backyard, []{return true;})
  });

  Exit Kak_Backyard = Exit("Kak Backyard", "Kakariko Village", "Kakariko Village", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&Kak_Main, []{return true;}),
                  ExitPairing(&Kak_OpenGrotto, []{return true;}),
                  ExitPairing(&Kak_OddMedicineBuilding, []{return IsAdult;}),
                  ExitPairing(&Kak_PotionShopBack, []{return IsAdult && AtDay;}, "Day")
  });

  Exit Kak_CarpenterBossHouse = Exit("Kak Carpenter Boss House", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  //wake up adult talon
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&Kak_Main, []{return true;})
  });

  Exit Kak_HouseOfSkulltula = Exit("Kak House of Skulltula", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&Kak_10GoldSkulltulaReward, []{return GoldSkulltulaTokens >= 10;}),
                  ItemLocationPairing(&Kak_20GoldSkulltulaReward, []{return GoldSkulltulaTokens >= 20;}),
                  ItemLocationPairing(&Kak_30GoldSkulltulaReward, []{return GoldSkulltulaTokens >= 30;}),
                  ItemLocationPairing(&Kak_40GoldSkulltulaReward, []{return GoldSkulltulaTokens >= 40;}),
                  ItemLocationPairing(&Kak_50GoldSkulltulaReward, []{return GoldSkulltulaTokens >= 50;}),
                }, {
                  //Exits
                  ExitPairing(&Kak_Main, []{return true;})
                }, {
                  AdvancementPairing(GoldSkulltulaToken, []{return CurAccessibleLocations > 10 && Skullsanity == "All Locations" && TokensInPool < 10;}, 50)
  });

  Exit Kak_ImpasHouse = Exit("Kak Impas House", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&Kak_ImpasHouseNearCow, []{return true;}),
                  ExitPairing(&Kak_Main,              []{return true;})
  });

  Exit Kak_ImpasHouseBack = Exit("Kak Impas House Back", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&Kak_ImpasHouseFreestandingPoH, []{return true;}),
                }, {
                  //Exits
                  ExitPairing(&Kak_ImpasLedge,        []{return true;}),
                  ExitPairing(&Kak_ImpasHouseNearCow, []{return true;})
  });

  Exit Kak_ImpasHouseNearCow = Exit("Kak Impas House Near Cow", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //Kak Impas House Cow
                }, {
                  //Exits
                  ExitPairing(&Kak_ImpasHouseBack, []{return false;})
  });

  Exit Kak_Windmill = Exit("Kak Windmill", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  DrainWell = DrainWell || (IsChild && CanPlay(SongOfStorms));
                  return DrainWell;
                }, {
                  //Locations
                  ItemLocationPairing(&Kak_WindmillFreestandingPoH, []{return CanUse("Boomerang") || DampesWindmillAccess;}),
                  //Song from Windmill
                }, {
                  //Exits
                  ExitPairing(&Kak_Main, []{return true;})
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_Boomerang,          []{return IsChild && !DampesWindmillAccess;}),
                  AdvancementPairing(A_SongOfStorms,       []{return ProgressiveOcarina >= 1 && IsAdult;}),
  });

  Exit Kak_Bazaar = Exit("Kak Bazaar", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //Kak Bazaar Item 1
                  //Kak Bazaar Item 2
                  //Kak Bazaar Item 3
                  //Kak Bazaar Item 4
                  //Kak Bazaar Item 5
                  //Kak Bazaar Item 6
                  //Kak Bazaar Item 7
                  //Kak Bazaar Item 8
                }, {
                  //Exits
                  ExitPairing(&Kak_Main, []{return true;})
  });

  Exit Kak_ShootingGallery = Exit("Kak Shooting Gallery", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //Kak Shooting Gallery Reward
                }, {
                  //Exits
                  ExitPairing(&Kak_Main, []{return true;})
  });

  Exit Kak_PotionShopFront = Exit("Kak Potion Shop Front", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //Kak Potion Shop Item 1
                  //Kak Potion Shop Item 2
                  //Kak Potion Shop Item 3
                  //Kak Potion Shop Item 4
                  //Kak Potion Shop Item 5
                  //Kak Potion Shop Item 6
                  //Kak Potion Shop Item 7
                  //Kak Potion Shop Item 8
                }, {
                  //Exits
                  ExitPairing(&Kak_Main,           []{return true;}),
                  ExitPairing(&Kak_PotionShopBack, []{return IsAdult;})
  });

  Exit Kak_PotionShopBack = Exit("Kak Potion Shop Back", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&Kak_Backyard,        []{return IsAdult;}),
                  ExitPairing(&Kak_PotionShopFront, []{return true;})
  });

  Exit Kak_OddMedicineBuilding = Exit("Kak Odd Medicine Building", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  //Odd Poultice Access
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&Kak_Backyard, []{return true;})
  });

  Exit Kak_RedeadGrotto = Exit("Kak Redead Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&Kak_RedeadGrottoChest, []{return IsAdult || (Sticks || KokiriSword || CanUse("Dins Fire"));})
                }, {
                  //Exits
                  ExitPairing(&Kak_Main, []{return true;})
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_DinsFire,         []{return ProgressiveMagic       >= 1;}),
                  AdvancementPairing(A_ProgressiveMagic, []{return AddedProgressiveMagics == 0;}),
                  AdvancementPairing(A_KokiriSword,      []{return IsChild;})
                  //Sticks
  });

  Exit Kak_OpenGrotto = Exit("Kak Open Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  GenericGrottoChecks();
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&Kak_OpenGrottoChest, []{return true;})
                  //Kak Open Grotto Gossip Stone
                }, {
                  //Exits
                  ExitPairing(&Kak_Backyard, []{return true;})
  });

  Exit GY_Main = Exit("Graveyard", "Graveyard", "the Graveyard", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  ButterflyFairy = ButterflyFairy || (CanUse("Sticks") && AtDay);
                  BeanPlantFairy = BeanPlantFairy || (GY_Main.CanPlantBean() && CanPlay(SongOfStorms));
                  BugRock = true;
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&GY_FreestandingPoH,       []{return (IsAdult && (GY_Main.CanPlantBean() || CanUse("Longshot"))) || (LogicGraveyardPoH && CanUse("Boomerang"));}),
                  ItemLocationPairing(&GY_DampeGravediggingTour, []{return IsChild && AtNight;}), //This needs to change
                  ItemLocationPairing(&GY_GS_Wall,               []{return CanUse("Boomerang") && AtNight;}),
                  ItemLocationPairing(&GY_GS_BeanPatch,          []{return CanPlantBugs && CanChildAttack;}),
                }, {
                  //Exits
                  ExitPairing(&GY_ShieldGrave,     []{return IsAdult;}),
                  ExitPairing(&GY_ShieldGrave,     []{return AtNight;}, "Night"),
                  ExitPairing(&GY_ComposersGrave,  []{return CanPlay(ZeldasLullaby);}),
                  ExitPairing(&GY_HeartPieceGrave, []{return IsAdult;}),
                  ExitPairing(&GY_HeartPieceGrave, []{return AtNight;}, "Night"),
                  ExitPairing(&GY_DampesGrave,     []{return IsAdult;}),
                  ExitPairing(&GY_DampesHouse,     []{return IsAdult || AtDampeTime;}), //This needs to be handled
                  ExitPairing(&Kak_Main,           []{return true;})
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_ProgressiveHookshot,  []{return AddedProgressiveHookshots == 0 && IsAdult;}),
                  AdvancementPairing(A_ProgressiveHookshot,  []{return AddedProgressiveHookshots == 1 && IsAdult;}),
                  AdvancementPairing(A_ZeldasLullaby,        []{return ProgressiveOcarina        >= 1;}),
                  AdvancementPairing(A_Boomerang,            []{return IsChild && AtNight;}),
  });

  Exit GY_ShieldGrave = Exit("GY Shield Grave", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&GY_ShieldGraveChest, []{return true;})
                  //Free Fairies
                }, {
                  //Exits
                  ExitPairing(&GY_Main, []{return true;})
  });

  Exit GY_HeartPieceGrave = Exit("GY Heart Piece Grave", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&GY_HeartPieceGraveChest, []{return CanPlay(SunsSong);})
                }, {
                  //Exits
                  ExitPairing(&GY_Main, []{return true;})
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_SunsSong, []{return ProgressiveOcarina >= 1;})
  });

  Exit GY_ComposersGrave = Exit("GY Composers Grave", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&GY_ComposersGraveChest, []{return HasFireSource;})
                  //Song From Composers Grave
                }, {
                  //Exits
                  ExitPairing(&GY_Main, []{return true;})
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_DinsFire,         []{return ProgressiveMagic       >= 1 && !FireArrows;}),
                  AdvancementPairing(A_FireArrows,       []{return ProgressiveMagic       >= 1 && !DinsFire && ProgressiveBow >= 1 && IsAdult;}),
                  AdvancementPairing(A_ProgressiveMagic, []{return AddedProgressiveMagics == 0;}),
                  AdvancementPairing(A_ProgressiveBow,   []{return AddedProgressiveBows   == 0 && IsAdult;}),
  });

  Exit GY_DampesGrave = Exit("GY Dampes Grave", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  DekuNutDrop = true;
                  DampesWindmillAccess = DampesWindmillAccess || (IsAdult && CanPlay(SongOfTime));
                  return DampesWindmillAccess;
                }, {
                  //Locations
                //ItemLocationPairing(&GY_HookshotChest,            []{return true;}),
                  ItemLocationPairing(&GY_DampeRaceFreestandingPoH, []{return IsAdult || LogicChildDampeRacePoH;}),
                }, {
                  //Exits
                  ExitPairing(&GY_Main,      []{return true;}),
                  ExitPairing(&Kak_Windmill, []{return IsAdult && CanPlay(SongOfTime);})
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_SongOfTime, []{return ProgressiveOcarina >= 1 && IsAdult;}),
  });

  Exit GY_DampesHouse = Exit("GY Dampes House", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&GY_Main, []{return true;})
  });

  Exit GY_WarpPadRegion = Exit("GY Warp Pad Region", "Graveyard", "the Graveyard", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  GossipStoneFairy = GossipStoneFairy || CanSummonGossipFairyWithoutSuns;
                  return true;
                }, {
                  //Locations
                  //GY Gossip Stone
                }, {
                  //Exits
                  ExitPairing(&GY_Main,               []{return true;}),
                  ExitPairing(&ShadowTemple_Entryway, []{return CanUse("Dins Fire") || (LogicShadowFireArrowEntry && CanUse("Fire Arrows"));}),
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_ProgressiveMagic, []{return AddedProgressiveMagics == 0;}),
                  AdvancementPairing(A_DinsFire,         []{return ProgressiveMagic       >= 1;}),
                  AdvancementPairing(A_FireArrows,       []{return ProgressiveMagic       >= 1 && ProgressiveBow >= 1 && LogicShadowFireArrowEntry;}),
  });

  Exit Kak_BehindGate = Exit("Kak Behind Gate", "Kakariko Village", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&Kak_Main, []{return IsAdult || LogicVisibleCollision || KakarikoVillageGateOpen || OpenKakariko == "Open";}),
                  ExitPairing(&DMT_Main, []{return true;})
  });

  Exit DMT_Main = Exit("Death Mountain", "Death Mountain", "Death Mountain Trail", DAY_NIGHT_CYCLE, []{
                  //Events
                  //time passes here
                  BeanPlantFairy = BeanPlantFairy || (DMT_Main.CanPlantBean() && CanPlay(SongOfStorms) && (HasExplosives || GoronBracelet));
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&DMT_Chest,                  []{return CanBlastOrSmash || (LogicDMTBombable && IsChild && GoronBracelet);}),
                  ItemLocationPairing(&DMT_FreestandingPoH,        []{return (DamageMultiplier != "OHKO") || CanUse("Nayrus Love") || Fairy || CanUse("Hover Boots") || (IsAdult && DMT_Main.CanPlantBean() && (HasExplosives || GoronBracelet));}),
                  ItemLocationPairing(&DMT_GS_BeanPatch,           []{return CanPlantBugs && (HasExplosives || GoronBracelet || (LogicDMTSoilGS && CanUse("Boomerang")));}),
                  ItemLocationPairing(&DMT_GS_NearKak,             []{return CanBlastOrSmash;}),
                  ItemLocationPairing(&DMT_GS_AboveDodongosCavern, []{return IsAdult && AtNight && CanUse("Hammer");})
                }, {
                  //Exits
                  ExitPairing(&Kak_BehindGate,          []{return true;}),
                  ExitPairing(&GC_Main,                 []{return true;}),
                  ExitPairing(&DMT_Summit,              []{return CanBlastOrSmash || (IsAdult && (DMT_Main.CanPlantBean() && GoronBracelet));}),
                  ExitPairing(&DodongosCavern_Entryway, []{return HasExplosives || GoronBracelet || IsAdult;}),
                  ExitPairing(&DMT_StormsGrotto,        []{return CanOpenStormGrotto;})
                }, {
                  AdvancementPairing(A_ProgressiveBombBag,  []{return AddedProgressiveBombBags  == 0;}),
                  AdvancementPairing(A_SongOfStorms,        []{return ProgressiveOcarina        >= 1;}),
                  AdvancementPairing(A_ProgressiveStrength, []{return AddedProgressiveStrengths == 0;}),
  });

  Exit DMT_Summit = Exit("Death Mountain Summit", "Death Mountain", "Death Mountain", DAY_NIGHT_CYCLE, []{
                  //Events
                  //Perscription Access
                  GossipStoneFairy = GossipStoneFairy || CanSummonGossipFairy;
                  BugRock          = true;
                  return true;
                }, {
                  //Locations
                  //ItemLocationPairing(&DMT_Biggoron, []{return IsAdult && (ClaimCheck || (GuaranteeTradePath && (EyedropsAccess || (Eyedrops && DisableTradeRevert))));}),
                  ItemLocationPairing(&DMT_GS_FallingRocksPath, []{return IsAdult && AtNight && CanUse("Hammer");}),
                  //DMT Gossip Stone
                }, {
                  //Exits
                  ExitPairing(&DMT_Main,               []{return true;}),
                  ExitPairing(&DMC_UpperLocal,         []{return true;}),
                  ExitPairing(&DMT_OwlFlight,          []{return IsChild;}),
                  ExitPairing(&DMT_CowGrotto,          []{return CanBlastOrSmash;}),
                  ExitPairing(&DMT_GreatFairyFountain, []{return CanBlastOrSmash;})
                }, {
                  AdvancementPairing(A_ProgressiveBombBag,  []{return AddedProgressiveBombBags == 0 && (IsChild || (IsAdult && !Hammer));}),
                  AdvancementPairing(A_MegatonHammer,       []{return AddedProgressiveBombBags == 0 && IsAdult;}),
                  AdvancementPairing(A_ProgressiveBombchus, []{return AddedProgressiveBombBags == 0;}),
  });

  Exit DMT_OwlFlight = Exit("DMT Owl Flight", "Death Mountain", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&Kak_ImpasLedge, []{return true;})
  });

  Exit DodongosCavern_Entryway = Exit("Dodongos Cavern Entryway", "Death Mountain", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&DodongosCavern_Beginning, []{return true;}),
                  ExitPairing(&DMT_Main,                 []{return true;})
  });

  Exit DMT_CowGrotto = Exit("DMT Cow Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //DMT Cow Grotto Cow
                }, {
                  //Exits
                  ExitPairing(&DMT_Main,     []{return true;})

  });

  Exit DMT_StormsGrotto = Exit("DMT Storms Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  GenericGrottoChecks();
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&DMT_StormsGrottoChest, []{return true;}),
                  //DMT Storms Grotto Gossip Stone
                }, {
                  //Exits
                  ExitPairing(&DMT_Main, []{return true;})
  });

  Exit DMT_GreatFairyFountain = Exit("DMT Great Fairy Fountain", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //ItemLocationPairing(&DMT_GreatFairyReward, []{return CanPlay(ZeldasLullaby);})
                }, {
                  //Exits
                  ExitPairing(&DMT_Summit, []{return true;})
                }, {
  });

  Exit GC_Main = Exit("Goron City", "Goron City", "Goron City", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  GossipStoneFairy = GossipStoneFairy || CanSummonGossipFairyWithoutSuns;
                  StickPot         = StickPot         || IsChild;
                  BugRock          = true;
                  GoronCityChildFire        = GoronCityChildFire        || (IsChild && CanUse("Dins Fire"));
                  GCWoodsWarpOpen           = GCWoodsWarpOpen           || (CanBlastOrSmash || CanUse("Dins Fire") || CanUse("Bow") || GoronBracelet || GoronCityChildFire);
                  StopGCRollingGoronAsAdult = StopGCRollingGoronAsAdult || (IsAdult && (GoronBracelet || HasExplosives || Bow || (LogicLinkGoronDins && CanUse("Dins Fire"))));
                  return GoronCityChildFire && GCWoodsWarpOpen && StopGCRollingGoronAsAdult;
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
                  ExitPairing(&DMT_Main,           []{return true;}),
                  ExitPairing(&GC_WoodsWarp,       []{return GCWoodsWarpOpen;}),
                  ExitPairing(&GC_Shop,            []{return (IsAdult && StopGCRollingGoronAsAdult) || (IsChild && (HasExplosives || GoronBracelet || GoronCityChildFire));}),
                  ExitPairing(&GC_DaruniasChamber, []{return (IsAdult && StopGCRollingGoronAsAdult) || (IsChild && CanPlay(ZeldasLullaby));}),
                  ExitPairing(&GC_Grotto,          []{return IsAdult && ((CanPlay(SongOfTime) && ((DamageMultiplier != "OHKO" && DamageMultiplier != "Quadruple") || CanUse("Goron Tunic") || CanUse("Longshot") || CanUse("Nayrus Love"))) || (DamageMultiplier != "OHKO" && CanUse("Goron Tunic") && CanUse("Hookshot")) ||(CanUse("Nayrus Love") && CanUse("Hookshot")));}),
                }, {
                  //AdvancementNeeds
                  AdvancementPairing(A_ProgressiveBombBag,  []{return AddedProgressiveBombBags  == 0;}),
                  AdvancementPairing(A_ProgressiveBombchus, []{return AddedProgressiveBombBags  == 0;}),
                  AdvancementPairing(A_MegatonHammer,       []{return IsAdult;}),
                  AdvancementPairing(A_ProgressiveStrength, []{return AddedProgressiveStrengths == 0;}),
                  AdvancementPairing(A_ProgressiveStrength, []{return AddedProgressiveStrengths == 1 && IsAdult;}),
                  AdvancementPairing(A_ProgressiveBow,      []{return AddedProgressiveBows      == 0 && IsAdult;}),
                  AdvancementPairing(A_GoronTunic,          []{return IsAdult;}),
                  AdvancementPairing(A_ProgressiveMagic,    []{return AddedProgressiveMagics    == 0;}),
                  AdvancementPairing(A_DinsFire,            []{return ProgressiveMagic          >= 1;}),
  });

  Exit GC_WoodsWarp = Exit("GC Woods Warp", "Goron City", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  GCWoodsWarpOpen = GCWoodsWarpOpen || (CanBlastOrSmash || CanUse("Dins Fire"));
                  return GCWoodsWarpOpen;
                }, {}, {
                  //Exits
                  ExitPairing(&GC_Main, []{return CanLeaveForest && GCWoodsWarpOpen;}),
                  ExitPairing(&LW_Main, []{return true;})
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_ProgressiveBombBag,  []{return AddedProgressiveBombBags == 0;}),
                  AdvancementPairing(A_ProgressiveBombchus, []{return AddedProgressiveBombBags == 0;}),
                  AdvancementPairing(A_MegatonHammer,       []{return IsAdult;}),
                  AdvancementPairing(A_ProgressiveMagic,    []{return AddedProgressiveMagics   == 0;}),
                  AdvancementPairing(A_DinsFire,            []{return ProgressiveMagic         >= 1;}),
  });

  Exit GC_DaruniasChamber = Exit("GC Darunias Chamber", "Goron City", "Goron City", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  GoronCityChildFire = GoronCityChildFire || (CanUse("Sticks"));
                  return GoronCityChildFire && GoronBracelet;
                }, {
                  //Locations
                  ItemLocationPairing(&GC_DaruniasJoy, []{return IsChild && CanPlay(SariasSong);})
                }, {
                  //Exits
                  ExitPairing(&GC_Main,        []{return true;}),
                  ExitPairing(&DMC_LowerLocal, []{return IsAdult;})
                }, {
                  AdvancementPairing(A_SariasSong,         []{return IsChild && ProgressiveOcarina       >= 1;})
  });

  Exit GC_Shop = Exit("GC Shop", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //GC Shop Item 1
                  //GC Shop Item 2
                  //GC Shop Item 3
                  //GC Shop Item 4
                  //GC Shop Item 5
                  //GC Shop Item 6
                  //GC Shop Item 7
                  //GC Shop Item 8
                }, {
                  //Exits
                  ExitPairing(&GC_Main, []{return true;})
  });

  Exit GC_Grotto = Exit("GC Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //ItemLocationPairing(&GC_DekuScrubGrottoLeft,   []{return CanStunDeku;}),
                  //ItemLocationPairing(&GC_DekuScrubGrottoRight,  []{return CanStunDeku;}),
                  //ItemLocationPairing(&GC_DekuScrubGrottoCenter, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing(&GC_Main, []{return true;})
  });

  Exit DMC_UpperNearby = Exit("DMC Upper Nearby", "Death Mountain Crater", "Death Mountain Crater", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&DMC_UpperLocal,  []{return CanUse("Goron Tunic");}),
                  ExitPairing(&DMT_Summit,      []{return true;}),
                  ExitPairing(&DMC_UpperGrotto, []{return CanBlastOrSmash;})
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_ProgressiveBombBag,  []{return AddedProgressiveBombBags == 0;}),
                  AdvancementPairing(A_ProgressiveBombchus, []{return AddedProgressiveBombBags == 0;}),
                  AdvancementPairing(A_MegatonHammer,       []{return IsAdult;}),
                  AdvancementPairing(A_GoronTunic,          []{return IsAdult;}),
  });

  Exit DMC_UpperLocal = Exit("DMC Upper Local", "Death Mountain Crater", "Death Mountain Crater", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  GossipStoneFairy = GossipStoneFairy || (HasExplosives && CanSummonGossipFairyWithoutSuns);
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&DMC_WallFreestandingPoH, []{return true;}),
                  ItemLocationPairing(&DMC_GS_Crate,            []{return IsChild && CanChildAttack;}),
                  //DMC Gossip Stone
                }, {
                  //Exits
                  ExitPairing(&DMC_UpperNearby,      []{return true;}),
                  ExitPairing(&DMC_LadderAreaNearby, []{return true;}),
                  ExitPairing(&DMC_CentralNearby,    []{return CanUse("Goron Tunic") && CanUse("Longshot") && ((DamageMultiplier != "OHKO" && DamageMultiplier != "Quadruple") || (Fairy && !ShuffleDungeonEntrances) || CanUse("Nayrus Love"));})
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_GoronTunic,          []{return IsAdult;}),
                  AdvancementPairing(A_ProgressiveHookshot, []{return IsAdult && AddedProgressiveHookshots == 0;}),
                  AdvancementPairing(A_ProgressiveHookshot, []{return IsAdult && AddedProgressiveHookshots == 1;}),
  });

  Exit DMC_LadderAreaNearby = Exit("DMC Ladder Area Nearby", "Death Mountain Crater", "Death Mountain Crater", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //DMC Deku Scrub
                }, {
                  //Exits
                  ExitPairing(&DMC_UpperNearby, []{return IsAdult;}),
                  ExitPairing(&DMC_LowerNearby, []{return CanUse("Hover Boots") || (LogicCraterUpperToLower && CanUse("Hammer"));})
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_HoverBoots,    []{return IsAdult;}),
                  AdvancementPairing(A_MegatonHammer, []{return IsAdult;}),
  });

  Exit DMC_LowerNearby = Exit("DMC Lower Nearby", "Death Mountain Crater", "Death Mountain Crater", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&DMC_LowerLocal,         []{return CanUse("Goron Tunic");}),
                  ExitPairing(&GC_DaruniasChamber,     []{return true;}),
                  ExitPairing(&DMC_GreatFairyFountain, []{return CanUse("Hammer");}),
                  ExitPairing(&DMC_HammerGrotto,       []{return CanUse("Hammer");})
                }, {
                  AdvancementPairing(A_MegatonHammer, []{return IsAdult;}),
                  AdvancementPairing(A_GoronTunic,    []{return IsAdult;}),
  });

  Exit DMC_LowerLocal = Exit("DMC Lower Local", "Death Mountain Crater", "Death Mountain Crater", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&DMC_LowerNearby,      []{return true;}),
                  ExitPairing(&DMC_LadderAreaNearby, []{return true;}),
                  ExitPairing(&DMC_CentralNearby,    []{return CanUse("Hover Boots") || CanUse("Hookshot");}),
                  ExitPairing(&FireTemple_Entrance,  []{return (CanUse("Hover Boots") || CanUse("Hookshot")) && (LogicFewerTunicRequirements || CanUse("Goron Tunic"));}),
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_HoverBoots,          []{return IsAdult;}),
                  AdvancementPairing(A_ProgressiveHookshot, []{return IsAdult && AddedProgressiveHookshots == 0;}),
  });

  Exit DMC_CentralNearby = Exit("DMC Central Nearby", "Death Mountain Crater", "Death Mountain Crater", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&DMC_VolcanoFreestandingPoH, []{return IsAdult && (DMC_CentralLocal.CanPlantBean() || (LogicCraterBeanPoHWithHovers && HoverBoots));}),
                  //Sheik in Crater
                }, {
                  //Exits
                  ExitPairing(&DMC_CentralLocal, []{return CanUse("Goron Tunic");})
                }, {
                  AdvancementPairing(A_MagicBeanPack, []{return DMC_CentralLocal.BothAges();}),
                  AdvancementPairing(A_HoverBoots,    []{return IsAdult && LogicCraterBeanPoHWithHovers;}),

  });

  Exit DMC_CentralLocal = Exit("DMC Central Local", "Death Mountain Crater", "Death Mountain Crater", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  BeanPlantFairy = BeanPlantFairy || (DMC_CentralLocal.CanPlantBean() && CanPlay(SongOfStorms));
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&DMC_GS_BeanPatch, []{return CanPlantBugs && CanChildAttack;}),
                }, {
                  //Exits
                  ExitPairing(&DMC_CentralNearby,   []{return true;}),
                  ExitPairing(&DMC_LowerNearby,     []{return IsAdult && (CanUse("Hover Boots") || CanUse("Hookshot") || DMC_CentralLocal.CanPlantBean());}),
                  ExitPairing(&DMC_UpperNearby,     []{return IsAdult && DMC_CentralLocal.CanPlantBean();}),
                  ExitPairing(&FireTemple_Entrance, []{return (IsChild && ShuffleDungeonEntrances) || (IsAdult && (LogicFewerTunicRequirements || CanUse("Goron Tunic")));}),
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_HoverBoots,          []{return IsAdult && AddedProgressiveHookshots == 0;}),
                  AdvancementPairing(A_ProgressiveHookshot, []{return IsAdult && AddedProgressiveHookshots == 0 && !HoverBoots;}),
  });

  Exit FireTemple_Entrance = Exit("Fire Temple Entrance", "Death Mountain Crater", "Death Mountain Crater", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {}, {
                  //Exits
                    ExitPairing(&FireTemple_Lower, []{return true;}),
  });

  Exit DMC_GreatFairyFountain = Exit("DMC Great Fairy Fountain", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //ItemLocationPairing(&DMC_GreatFairyFountainReward, []{return CanPlay(ZeldasLullaby);})
                }, {
                  //Exits
                  ExitPairing(&DMC_LowerLocal, []{return true;})
  });

  Exit DMC_UpperGrotto = Exit("DMC Upper Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  GenericGrottoChecks();
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&DMC_UpperGrottoChest, []{return true;})
                  //DMC Upper Grotto Gossip Stone
                }, {
                  //Exits
                  ExitPairing(&DMC_UpperLocal, []{return true;})
  });

  Exit DMC_HammerGrotto = Exit("DMC Hammer Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //ItemLocationPairing(&DMC_DekuScrubGrottoLeft,   []{return CanStunDeku;}),
                  //ItemLocationPairing(&DMC_DekuScrubGrottoRight,  []{return CanStunDeku;}),
                  //ItemLocationPairing(&DMC_DekuScrubGrottoCenter, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing(&DMC_LowerLocal, []{return true;})
  });

  Exit ZR_Front = Exit("ZR Front", "Zora River", "Zora's River", DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&ZR_GS_Tree, []{return IsChild && CanChildAttack;}),
                }, {
                  //Exits
                  ExitPairing(&ZR_Main, []{return IsAdult || HasExplosives;}),
                  ExitPairing(&HF_Main, []{return true;})
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_ProgressiveBombBag,  []{return IsChild && AddedProgressiveBombBags == 0;}),
                  AdvancementPairing(A_ProgressiveBombchus, []{return IsChild && AddedProgressiveBombBags == 0;}),
  });

  Exit ZR_Main = Exit("Zora River", "Zora River", "Zora's River", DAY_NIGHT_CYCLE, []{
                  //Events
                  GossipStoneFairy = GossipStoneFairy || CanSummonGossipFairy;
                  BeanPlantFairy   = BeanPlantFairy   || (ZR_Main.CanPlantBean() && CanPlay(SongOfStorms));
                  ButterflyFairy   = ButterflyFairy   || CanUse("Sticks");
                  BugShrub         = BugShrub         || CanCutShrubs;
                  return true;
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
                  ExitPairing(&ZR_Front,           []{return true;}),
                  ExitPairing(&ZR_OpenGrotto,      []{return true;}),
                  ExitPairing(&ZR_FairyGrotto,     []{return CanBlastOrSmash;}),
                  ExitPairing(&LW_Main,            []{return CanDive || CanUse("Iron Boots");}),
                  ExitPairing(&ZR_StormsGrotto,    []{return CanOpenStormGrotto;}),
                  ExitPairing(&ZR_BehindWaterfall, []{return CanPlay(ZeldasLullaby);})
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_SongOfStorms,       []{return ProgressiveOcarina       >= 1;}),
                  AdvancementPairing(A_IronBoots,          []{return IsAdult;}),
                  AdvancementPairing(A_ProgressiveScale,   []{return AddedProgressiveScales   == 0;})
  });

  Exit ZR_BehindWaterfall = Exit("ZR Behind Waterfall", "Zora River", "", DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&ZR_Main, []{return true;}),
                  ExitPairing(&ZD_Main, []{return true;})
  });

  Exit ZR_OpenGrotto = Exit("ZR Open Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  GenericGrottoChecks();
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&ZR_OpenGrottoChest, []{return true;})
                  //ZR Open Grotto Gossip Stone
                }, {
                  //Exits
                  ExitPairing(&ZR_Main, []{return true;})
  });

  Exit ZR_FairyGrotto = Exit("ZR Fairy Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  FreeFairies = true;
                  return true;
                }, {
                  //Locations
                }, {
                  //Exits
                  ExitPairing(&ZR_Main, []{return true;})
  });

  Exit ZR_StormsGrotto = Exit("ZR Storms Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //ItemLocationPairing(&ZR_DekuScrubGrottoRear,  []{return CanStunDeku;}),
                  //ItemLocationPairing(&ZR_DekuScrubGrottoFront, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing(&ZR_Main, []{return true;})
  });

  Exit ZD_Main = Exit("Zoras Domain", "Zoras Domain", "Zora's Domain", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  GossipStoneFairy = GossipStoneFairy || CanSummonGossipFairyWithoutSuns;
                  NutPot           = true;
                  StickPot         = StickPot         || IsChild;
                  FishGroup        = FishGroup        || IsChild;
                  KingZoraThawed   = KingZoraThawed   || (IsAdult   && BlueFire);
                  DeliverLetter    = DeliverLetter    || (RutosLetter && IsChild && ZorasFountain != "Open");
                  //Eyeball Frog Access
                  return KingZoraThawed && DeliverLetter/*&& EyeballFrogAccess*/;
                }, {
                  //Locations
                  ItemLocationPairing(&ZD_DivingMinigame,     []{return IsChild;}),
                  ItemLocationPairing(&ZD_Chest,              []{return CanUse("Sticks");}),
                  ItemLocationPairing(&ZD_KingZoraThawed,     []{return KingZoraThawed;}),
                  ItemLocationPairing(&ZD_GS_FrozenWaterfall, []{return IsAdult && AtNight && (Hookshot || Bow || MagicMeter);}),
                  //ZD Gossip Stone
                }, {
                  //Exits
                  ExitPairing(&ZR_BehindWaterfall, []{return true;}),
                  ExitPairing(&LH_Main,            []{return IsChild && CanDive;}),
                  ExitPairing(&ZD_BehindKingZora,  []{return DeliverLetter || ZorasFountain == "Open" || (ZorasFountain == "Adult" && IsAdult);}),
                  ExitPairing(&ZD_Shop,            []{return IsChild || BlueFire;}),
                  ExitPairing(&ZD_StormsGrotto,    []{return CanOpenStormGrotto;})
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_RutosLetter,      []{return IsChild && CanDive;}),
                  AdvancementPairing(A_ProgressiveScale, []{return IsChild && AddedProgressiveScales == 0;}),
  });

  Exit ZD_BehindKingZora = Exit("ZD Behind King Zora", "Zoras Domain", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {}, {
                  //Exits
                  ExitPairing(&ZD_Main, []{return DeliverLetter || ZorasFountain == "Open" || (ZorasFountain == "Adult" && IsAdult);}),
                  ExitPairing(&ZF_Main, []{return true;})
  });

  Exit ZD_Shop = Exit("ZD Shop", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //ZD Shop Item 1
                  //ZD Shop Item 2
                  //ZD Shop Item 3
                  //ZD Shop Item 4
                  //ZD Shop Item 5
                  //ZD Shop Item 6
                  //ZD Shop Item 7
                  //ZD Shop Item 8
                }, {
                  //Exits
                  ExitPairing(&ZD_Main, []{return true;})
  });

  Exit ZD_StormsGrotto = Exit("ZD Storms Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //Free Fairies
                }, {
                  //Exits
                  ExitPairing(&ZD_Main, []{return true;})
  });

  Exit ZF_Main = Exit("Zoras Fountain", "Zoras Fountain", "Zora's Fountain", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  GossipStoneFairy = GossipStoneFairy || CanSummonGossipFairyWithoutSuns;
                  ButterflyFairy   = ButterflyFairy   || (CanUse("Sticks") && AtDay);
                  return true;
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
                  ExitPairing(&ZD_BehindKingZora,        []{return true;}),
                  ExitPairing(&JabuJabusBelly_Beginning, []{return IsChild && FishAccess;}),
                  ExitPairing(&IceCavern_Beginning,      []{return IsAdult;}),
                  ExitPairing(&ZF_GreatFairyFountain,    []{return HasExplosives;})
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_EmptyBottle, []{return IsChild && !HasBottle;}),
                  AdvancementPairing(A_ZoraTunic,   []{return IsAdult && !LogicFewerTunicRequirements;}),
  });

  Exit ZF_GreatFairyFountain = Exit("ZF Great Fairy Fountain", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //ZF Great Fairy Reward
                }, {
                  //Exits
                  ExitPairing(&ZF_Main, []{return true;})
  });

  Exit LLR_Main = Exit("Lon Lon Ranch", "Lon Lon Ranch", "Lon Lon Ranch", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  Epona    = CanPlay(EponasSong) && IsAdult && AtDay;
                  LinksCow = CanPlay(EponasSong) && IsAdult && AtDay;
                  return Epona && LinksCow;
                }, {
                  //Locations
                  //Song from Malon
                  ItemLocationPairing(&LLR_GS_Tree,        []{return IsChild;}),
                  ItemLocationPairing(&LLR_GS_RainShed,    []{return IsChild && AtNight;}),
                  ItemLocationPairing(&LLR_GS_HouseWindow, []{return CanUse("Boomerang") && AtNight;}),
                  ItemLocationPairing(&LLR_GS_BackWall,    []{return CanUse("Boomerang") && AtNight;}),
                }, {
                  //Exits
                  ExitPairing(&HF_Main,         []{return true;}),
                  ExitPairing(&LLR_TalonsHouse, []{return true;}),
                  ExitPairing(&LLR_Stables,     []{return true;}),
                  ExitPairing(&LLR_Tower,       []{return true;}),
                  ExitPairing(&LLR_Grotto,      []{return IsChild;})
                }, {
                  AdvancementPairing(A_EponasSong,         []{return ProgressiveOcarina       >= 1  && AtDay   && IsAdult;}),
                  AdvancementPairing(A_Boomerang,          []{return GoldSkulltulaTokens      <= 50 && AtNight && IsChild;}),

  });

  Exit LLR_TalonsHouse = Exit("LLR Talons House", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&LLR_TalonsChickens, []{return IsChild && AtDay && ZeldasLetter;})
                }, {
                  //Exits
                  ExitPairing(&LLR_Main, []{return true;})
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_ZeldasLetter, []{return IsChild;}),
  });

  Exit LLR_Stables = Exit("LLR Stables", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //LLR Stables Left Cow
                  //LLR Stables Right Cow
                }, {
                  //Exits
                  ExitPairing(&LLR_Main, []{return true;})
  });

  Exit LLR_Tower = Exit("LLR Tower", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&LLR_FreestandingPoH, []{return IsChild;}),
                  //LLR Tower Left Cow
                  //LLR Tower Right Cow
                }, {
                  //Exits
                  ExitPairing(&LLR_Main, []{return true;})
  });

  Exit LLR_Grotto = Exit("LLR Grotto", "", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  //ItemLocationPairing(&LLR_DekuScrubGrottoLeft,   []{return CanStunDeku;}),
                  //ItemLocationPairing(&LLR_DekuScrubGrottoRight,  []{return CanStunDeku;}),
                  //ItemLocationPairing(&LLR_DekuScrubGrottoCenter, []{return CanStunDeku;}),
                }, {
                  //Exits
                  ExitPairing(&LLR_Main, []{return true;})
  });

  Exit DekuTree_Lobby = Exit("Deku Tree Lobby", "Deku Tree", "Deku Tree", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  DekuBabaSticksCheck();
                  DekuBabaNutsCheck();
                  return true;
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
                  ExitPairing(&KF_OutsideDekuTree,       []{return true;}),
                  ExitPairing(&DekuTree_SlingshotRoom,   []{return HasShield;}),
                  ExitPairing(&DekuTree_BossRoom,        []{return (HasFireSourceWithTorch || (LogicDekuB1WebsWithBow && CanUse("Bow"))) && (LogicDekuB1Skip || (IsAdult || CanUse("Slingshot")));})
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_ProgressiveBulletBag, []{return IsChild && AddedProgressiveBulletBags == 0;}),
                  AdvancementPairing(A_DekuShield,           []{return IsChild;}),
                  AdvancementPairing(A_HylianShield,         []{return IsAdult;}),
  });

  Exit DekuTree_SlingshotRoom = Exit("Deku Tree Slingshot Room", "Deku Tree", "Deku Tree", NO_DAY_NIGHT_CYCLE, []{
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&DekuTree_SlingshotChest,         []{return true;}),
                  ItemLocationPairing(&DekuTree_SlingshotRoomSideChest, []{return true;})
                }, {
                  //Exits
                  ExitPairing(&DekuTree_Lobby, []{return true;})
  });

  Exit DekuTree_BossRoom = Exit("Deku Tree Boss Room", "Deku Tree", "Deku Tree", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  DekuTreeClear = HasShield && (IsAdult || KokiriSword || Sticks);
                  KokirisEmerald = KokirisEmerald || DekuTreeClear;
                  return DekuTreeClear;
                }, {
                  //Locations
                  // ItemLocationPairing(&DekuTree_QueenGohma,               []{return HasShield && (IsAdult || KokiriSword || Sticks);}),
                  // ItemLocationPairing(&DekuTree_QueenGohmaHeartContainer, []{return HasShield && (IsAdult || KokiriSword || Sticks);}),
                }, {
                  //Exits
                  ExitPairing(&DekuTree_Lobby, []{return true;})
                }, {
                  //Advancement Needs
                  AdvancementPairing(A_KokiriSword,  []{return IsChild;}),
                  AdvancementPairing(A_DekuShield,   []{return IsChild;}),
                  AdvancementPairing(A_HylianShield, []{return IsAdult;}),
  });

  Exit DodongosCavern_Beginning = Exit("Dodongos Cavern Beginning", "Dodongos Cavern", "", NO_DAY_NIGHT_CYCLE, []{
                    return true;
                  }, {}, {
                    //Exits
                    ExitPairing(&DodongosCavern_Entryway, []{return true;}),
                    ExitPairing(&DodongosCavern_Lobby,    []{return CanBlastOrSmash || GoronBracelet;})
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_ProgressiveBombBag,  []{return AddedProgressiveBombBags  == 0;}),
                    AdvancementPairing(A_ProgressiveBombchus, []{return AddedProgressiveBombBags  == 0;}),
                    AdvancementPairing(A_MegatonHammer,       []{return IsAdult;}),
                    AdvancementPairing(A_ProgressiveStrength, []{return AddedProgressiveStrengths == 0;}),
  });

  Exit DodongosCavern_Lobby = Exit("Dodongos Cavern Lobby", "Dodongos Cavern", "", NO_DAY_NIGHT_CYCLE, []{
                    GossipStoneFairy = GossipStoneFairy || CanSummonGossipFairy;
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&DodongosCavern_MapChest,                     []{return true;}),
                    ItemLocationPairing(&DodongosCavern_CompassChest,                 []{return IsAdult || Sticks || (CanUse("Dins Fire") && (Slingshot || HasExplosives || KokiriSword));}),
                    ItemLocationPairing(&DodongosCavern_GS_SideRoomNearLowerLizalfos, []{return HasExplosives || IsAdult || Slingshot || Boomerang || Sticks || KokiriSword;}),
                    ItemLocationPairing(&DodongosCavern_GS_Scarecrow,                 []{return CanUse("Scarecrow") || CanUse("Longshot") || (LogicDCScarecrowGS && (IsAdult || CanChildAttack));}),
                    //Dodongos Cavern Deku Scrub Side Room Near Dodongos
                    //Dodongos Cavern Deku Scrub Lobby
                    //Dodongos Cavern Gossip Stone
                  }, {
                    //Exits
                    ExitPairing(&DodongosCavern_Beginning, []{return true;}),
                    ExitPairing(&DodongosCavern_Climb,     []{return (IsAdult || ((Sticks || CanUse("Dins Fire")) && (Slingshot || Sticks || HasExplosives || KokiriSword))) && (HasExplosives || GoronBracelet || CanUse("Dins Fire") ||(LogicDCStaircase && CanUse("Bow")));})
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_ProgressiveBombBag,  []{return AddedProgressiveBombBags  == 0;}),
                    AdvancementPairing(A_ProgressiveBombchus, []{return AddedProgressiveBombBags  == 0;}),
                    AdvancementPairing(A_ProgressiveStrength, []{return AddedProgressiveStrengths == 0;}),
                    AdvancementPairing(A_DinsFire,            []{return ProgressiveMagic          >= 1;}),
                    AdvancementPairing(A_ProgressiveMagic,    []{return AddedProgressiveMagics    == 0;}),
  });

  Exit DodongosCavern_Climb = Exit("Dodongos Cavern Climb", "Dodongos Cavern", "", NO_DAY_NIGHT_CYCLE, []{
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&DodongosCavern_BombFlowerPlatformChest, []{return true;}),
                    ItemLocationPairing(&DodongosCavern_GS_VinesAboveStairs,     []{return true;}),
                    //Dodongos Cavern Deku Scrub Near Bomb Bag Right
                    //Dodongos cavern Deku Scrub Near Bomb Bag Left
                  }, {
                    //Exits
                    ExitPairing(&DodongosCavern_Lobby,     []{return true;}),
                    ExitPairing(&DodongosCavern_FarBridge, []{return (IsChild && (Slingshot || (LogicDCSlingshotSkip && (Sticks || HasExplosives || KokiriSword)))) || (IsAdult && (Bow || HoverBoots || CanUse("Longshot") || LogicDCJump));})
  });

  Exit DodongosCavern_FarBridge = Exit("Dodongos Cavern Far Bridge", "Dodongos Cavern", "", NO_DAY_NIGHT_CYCLE, []{
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&DodongosCavern_BombBagChest,         []{return true;}),
                    ItemLocationPairing(&DodongosCavern_EndOfBridgeChest,     []{return CanBlastOrSmash;}),
                    ItemLocationPairing(&DodongosCavern_GS_AlcoveAboveStairs, []{return HookshotOrBoomerang;}),
                  }, {
                    //Exits
                    ExitPairing(&DodongosCavern_BossArea, []{return HasExplosives;}),
                    ExitPairing(&DodongosCavern_Lobby,    []{return true;})
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_ProgressiveBombBag,  []{return AddedProgressiveBombBags == 0;}),
                    AdvancementPairing(A_ProgressiveBombchus, []{return AddedProgressiveBombBags == 0;}),
                    AdvancementPairing(A_MegatonHammer,       []{return AddedProgressiveBombBags == 0 && IsAdult;}),
  });

  Exit DodongosCavern_BossArea = Exit("Dodongos Cavern Boss Area", "Dodongos Cavern", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    FairyPot = true;
                    GoronsRuby = GoronsRuby || ((Bombs || GoronBracelet) && (IsAdult || Sticks || KokiriSword));
                    return GoronsRuby;
                  }, {
                    //Locations
                    ItemLocationPairing(&DodongosCavern_BossRoomChest, []{return true;}),
                    //Dodongos Cavern King Dodongo Heart
                    //King Dodongo
                    ItemLocationPairing(&DodongosCavern_GS_BackRoom, []{return true;}),
                  }, {
                    //Exits
                    ExitPairing(&DodongosCavern_Lobby, []{return true;})
  });

  Exit JabuJabusBelly_Beginning = Exit("Jabu Jabus Belly Beginning", "Jabu Jabus Belly", "", NO_DAY_NIGHT_CYCLE, []{
                    return true;
                  }, {}, {
                    //Exits
                    ExitPairing(&ZF_Main,             []{return true;}),
                    ExitPairing(&JabuJabusBelly_Main, []{return CanUseProjectile;})
                  }, {
                    AdvancementPairing(A_Boomerang,            []{return IsChild;}),
                    AdvancementPairing(A_ProgressiveBulletBag, []{return IsChild && AddedProgressiveBulletBags == 0;}),
                    AdvancementPairing(A_ProgressiveBow,       []{return IsAdult && AddedProgressiveBows       == 0;}),
                    AdvancementPairing(A_ProgressiveHookshot,  []{return IsAdult && AddedProgressiveHookshots  == 0;}),
  });

  Exit JabuJabusBelly_Main = Exit("Jabu Jabus Belly Main", "Jabu Jabus Belly", "", NO_DAY_NIGHT_CYCLE, []{
                    FairyPot = true;
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&JabuJabusBelly_BoomerangChest,        []{return true;}),
                    ItemLocationPairing(&JabuJabusBelly_GS_WaterSwitchRoom,    []{return true;}),
                    ItemLocationPairing(&JabuJabusBelly_GS_LobbyBasementLower, []{return HookshotOrBoomerang;}),
                    ItemLocationPairing(&JabuJabusBelly_GS_LobbyBasementUpper, []{return HookshotOrBoomerang;}),
                    //Jabu Jabus Belly Deku Scrub
                  }, {
                    //Exits
                    ExitPairing(&JabuJabusBelly_Beginning, []{return true;}),
                    ExitPairing(&JabuJabusBelly_Depths,    []{return CanUse("Boomerang");}),
                    ExitPairing(&JabuJabusBelly_BossArea,  []{return LogicJabuBossGSAdult && CanUse("Hover Boots");})
                  }, {
                    AdvancementPairing(A_Boomerang, []{return IsChild;}),
  });

  Exit JabuJabusBelly_Depths = Exit("Jabu Jabus Belly Depths", "Jabu Jabus Belly", "", NO_DAY_NIGHT_CYCLE, []{
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&JabuJabusBelly_MapChest,     []{return true;}),
                    ItemLocationPairing(&JabuJabusBelly_CompassChest, []{return true;})
                  }, {
                    //Exits
                    ExitPairing(&JabuJabusBelly_Main,     []{return true;}),
                    ExitPairing(&JabuJabusBelly_BossArea, []{return Sticks || KokiriSword;})
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_KokiriSword, []{return IsChild;}),
  });

  Exit JabuJabusBelly_BossArea = Exit("Jabu Jabus Belly Boss Area", "Jabu Jabus Belly", "", NO_DAY_NIGHT_CYCLE, []{
                    NutPot = true;
                    ZorasSapphire = ZorasSapphire || CanUse("Boomerang");
                    return ZorasSapphire;
                  }, {
                    //Locations
                    //Jabu Jabus Belly Barinade Heart
                    //Barinade
                    ItemLocationPairing(&JabuJabusBelly_GS_NearBoss, []{return true;}),
                  }, {
                    //Exits
                    ExitPairing(&JabuJabusBelly_Main, []{return true;})
  });

  Exit ForestTemple_Lobby = Exit("Forest Temple Lobby", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&ForestTemple_FirstRoomChest,    []{return true;}),
                    ItemLocationPairing(&ForestTemple_FirstStalfosChest, []{return IsAdult || KokiriSword;}),
                    ItemLocationPairing(&ForestTemple_GS_FirstRoom,      []{return CanUse("Dins Fire") || CanUseProjectile;}),
                    ItemLocationPairing(&ForestTemple_GS_Lobby,          []{return HookshotOrBoomerang;}),
                  }, {
                    //Exits
                    ExitPairing(&SFM_Main,                   []{return true;}),
                    ExitPairing(&ForestTemple_NWOutdoors,    []{return CanPlay(SongOfTime) || IsChild;}),
                    ExitPairing(&ForestTemple_NEOutdoors,    []{return CanUse("Bow") || CanUse("Slingshot");}),
                    ExitPairing(&ForestTemple_BlockPushRoom, []{return SmallKeys(ForestTempleKeys, 1);}),
                    ExitPairing(&ForestTemple_BossRegion,    []{return ForestTempleJoAndBeth && ForestTempleAmyAndMeg;})
                  }, {
                    //Advancement Needs
                    AdvancementPairing(ForestTemple_SmallKey,  []{return true;}, 1),
                    AdvancementPairing(A_SongOfTime,           []{return IsAdult && ProgressiveOcarina         >= 1;}),
                    AdvancementPairing(A_ProgressiveBow,       []{return IsAdult && AddedProgressiveBows       == 0;}),
                    AdvancementPairing(A_ProgressiveBulletBag, []{return IsChild && AddedProgressiveBulletBags == 0;}),
  });

  Exit ForestTemple_NWOutdoors = Exit("Forest Temple NW Outdoors", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    DekuBabaSticksCheck();
                    DekuBabaNutsCheck();
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&ForestTemple_GS_LevelIslandCourtyard, []{return CanUse("Longshot") || ((ForestTemple_OutsideUpperLedge.dayAdult || ForestTemple_OutsideUpperLedge.nightAdult) && CanUse("Hookshot"));}),
                  }, {
                    //Exits
                    ExitPairing(&ForestTemple_OutdoorsHighBalconies, []{return IsAdult || (HasExplosives || ((CanUse("Boomerang") || Nuts || BuyDekuShield) && (Sticks || KokiriSword || CanUse("Slingshot"))));})
  });

  Exit ForestTemple_NEOutdoors = Exit("Forest Temple NE Outdoors", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    DekuBabaSticksCheck();
                    DekuBabaNutsCheck();
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&ForestTemple_RaisedIslandCourtyardChest, []{return CanUse("Hookshot");}),
                    ItemLocationPairing(&ForestTemple_GS_RaisedIslandCourtyard,   []{return CanUse("Hookshot") || (LogicForestOutdoorEastGS && CanUse("Boomerang"));}),
                  }, {
                    //Exits
                    ExitPairing(&ForestTemple_OutdoorsHighBalconies, []{return CanUse("Longshot")   || (LogicForestVines && CanUse("Hookshot"));}),
                    ExitPairing(&ForestTemple_NWOutdoors,            []{return CanUse("Iron Boots") || ProgressiveScale >= 2;}),
                    ExitPairing(&ForestTemple_Lobby,                 []{return true;})
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_ProgressiveHookshot,  []{return AddedProgressiveHookshots  == 0 && IsAdult;}),
                    AdvancementPairing(A_ProgressiveHookshot,  []{return AddedProgressiveHookshots  == 1 && IsAdult;}),
                    AdvancementPairing(A_ProgressiveScale,     []{return AddedProgressiveScales     == 0;}),
                    AdvancementPairing(A_ProgressiveScale,     []{return AddedProgressiveScales     == 1;}),
                    AdvancementPairing(A_IronBoots,            []{return IsAdult;}),
  });

  Exit ForestTemple_OutdoorsHighBalconies = Exit("Forest Temple Outdoors High Balconies", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&ForestTemple_WellChest, []{return true;}),
                    ItemLocationPairing(&ForestTemple_MapChest,  []{return true;})
                  }, {
                    //Exits
                    ExitPairing(&ForestTemple_NWOutdoors,  []{return true;}),
                    ExitPairing(&ForestTemple_NEOutdoors,  []{return true;}),
                    ExitPairing(&ForestTemple_FallingRoom, []{return LogicForestScarecrow && CanUse("Hover Boots") && CanUse("Scarecrow");})
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_HoverBoots,          []{return IsAdult && LogicForestScarecrow;}),
                    AdvancementPairing(A_ProgressiveHookshot, []{return IsAdult && LogicForestScarecrow && AddedProgressiveHookshots == 0;}),
  });

  Exit ForestTemple_FallingRoom = Exit("Forest Temple Falling Room", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    ForestTempleAmyAndMeg = ForestTempleAmyAndMeg || CanUse("Bow");
                    return ForestTempleAmyAndMeg;
                  }, {
                    //Locations
                    ItemLocationPairing(&ForestTemple_FallingCeilingRoomChest, []{return true;})
                  }, {
                    //Exits
                    ExitPairing(&ForestTemple_NEOutdoors, []{return true;})
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_ProgressiveBow, []{return IsAdult && AddedProgressiveBows == 0;}),
  });

  Exit ForestTemple_BlockPushRoom = Exit("Forest Temple Block Push Room", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&ForestTemple_EyeSwitchChest, []{return GoronBracelet && (CanUse("Bow") || CanUse("Slingshot"));})
                  }, {
                    //Exits
                    ExitPairing(&ForestTemple_OutsideUpperLedge, []{return CanUse("Hover Boots") || (LogicForestOutsideBackdoor && IsAdult && GoronBracelet);}),
                    ExitPairing(&ForestTemple_BowRegion,         []{return GoronBracelet && SmallKeys(ForestTempleKeys, 3) && IsAdult;}),
                    ExitPairing(&ForestTemple_StraightenedHall,  []{return GoronBracelet && SmallKeys(ForestTempleKeys, 2) && CanUse("Bow") && IsAdult;})
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_ProgressiveBow,      []{return IsAdult && AddedProgressiveBows == 0;}),
                    AdvancementPairing(A_HoverBoots,          []{return IsAdult;}),
                    AdvancementPairing(ForestTemple_SmallKey, []{return true;}, 3),
  });

  Exit ForestTemple_StraightenedHall = Exit("Forest Temple Straightened Hall", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&ForestTemple_BossKeyChest, []{return true;})
                  }, {
                    //Exits
                    ExitPairing(&ForestTemple_OutsideUpperLedge, []{return true;})
  });

  Exit ForestTemple_OutsideUpperLedge = Exit("Forest Temple Outside Upper Ledge", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&ForestTemple_FloormasterChest, []{return true;})
                  }, {
                    //Exits
                    ExitPairing(&ForestTemple_NWOutdoors, []{return true;})
  });

  Exit ForestTemple_BowRegion = Exit("Forest Temple Bow Region", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    ForestTempleJoAndBeth = ForestTempleJoAndBeth || CanUse("Bow");
                    return ForestTempleJoAndBeth;
                  }, {
                    //Locations
                    ItemLocationPairing(&ForestTemple_BowChest,     []{return true;}),
                    ItemLocationPairing(&ForestTemple_RedPoeChest,  []{return CanUse("Bow");}),
                    ItemLocationPairing(&ForestTemple_BluePoeChest, []{return CanUse("Bow");})
                  }, {
                    //Exits
                    ExitPairing(&ForestTemple_FallingRoom, []{return SmallKeys(ForestTempleKeys, 5) && (Bow || CanUse("Dins Fire"));})
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_ProgressiveBow,      []{return IsAdult && AddedProgressiveBows   == 0;}),
                    AdvancementPairing(A_DinsFire,            []{return IsAdult && ProgressiveMagic       >= 1;}),
                    AdvancementPairing(A_ProgressiveMagic,    []{return IsAdult && AddedProgressiveMagics == 0;}),
                    AdvancementPairing(ForestTemple_SmallKey, []{return true;}, 5),
  });

  Exit ForestTemple_BossRegion = Exit("Forest Temple Boss Region", "Forest Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    ForestMedallion = ForestMedallion || (BossKeyForestTemple);
                    return ForestMedallion;
                  }, {
                    //Locations
                    ItemLocationPairing(&ForestTemple_BasementChest, []{return true;}),
                    //Forest Temple Phantom Ganon Heart
                    //Phantom Ganon
                    ItemLocationPairing(&ForestTemple_GS_Basement, []{return HookshotOrBoomerang;}),
                  }, {}, {
                    //Advancement Needs
                    AdvancementPairing(ForestTemple_BossKey, []{return true;}),
  });

  Exit FireTemple_Lower = Exit("Fire Temple Lower", "Fire Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    FairyPot      = FairyPot      || ((CanUse("Hover Boots") || CanUse("Hookshot")) && (LogicFewerTunicRequirements || CanUse("Goron Tunic")));
                    FireMedallion = FireMedallion || (CanUse("Goron Tunic") && CanUse("Hammer") && BossKeyFireTemple && (LogicFireBossDoorJump || HoverBoots || CanPlay(SongOfTime) || HasExplosives)); //Fix this
                    return FireMedallion;
                  }, {
                    //Locations
                    ItemLocationPairing(&FireTemple_NearBossChest,    []{return LogicFewerTunicRequirements || CanUse("Goron Tunic");}),
                    ItemLocationPairing(&FireTemple_FlareDancerChest, []{return /*SmallKeys(FireTempleKeys, 8) &&*/ CanUse("Hammer");}),
                    ItemLocationPairing(&FireTemple_BossKeyChest,     []{return /*SmallKeys(FireTempleKeys, 8) &&*/ CanUse("Hammer");}),
                  //ItemLocationPairing(&FireTemple_VolvagiaHeart),
                  //Volvagia
                    ItemLocationPairing(&FireTemple_GS_BossKeyLoop,   []{return /*SmallKeys(FireTempleKeys, 8) &&*/ CanUse("Hammer");}),
                  }, {
                    //Exits
                    ExitPairing(&FireTemple_Entrance,    []{return true;}),
                    ExitPairing(&FireTemple_BigLavaRoom, []{return SmallKeys(FireTempleKeys, 1) && (LogicFewerTunicRequirements || CanUse("Goron Tunic"));}),
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_MegatonHammer,     []{return IsAdult;}),
                    AdvancementPairing(A_HoverBoots,        []{return IsAdult;}),
                    AdvancementPairing(A_GoronTunic,        []{return IsAdult && !LogicFewerTunicRequirements;}),
                    AdvancementPairing(FireTemple_SmallKey, []{return true;}, 1),
                    AdvancementPairing(FireTemple_BossKey,  []{return true;}),
  });

  Exit FireTemple_BigLavaRoom = Exit("Fire Temple Big Lava Room", "Fire Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&FireTemple_BigLavaRoomLowerOpenDoorChest, []{return true;}),
                    ItemLocationPairing(&FireTemple_BigLavaRoomBlockedDoorChest,   []{return IsAdult && HasExplosives;}),
                    ItemLocationPairing(&FireTemple_GS_SongOfTimeRoom,             []{return IsAdult && (CanPlay(SongOfTime) || LogicFireSongOfTime);}),
                  }, {
                    //Exits
                    ExitPairing(&FireTemple_Lower,  []{return true;}),
                    ExitPairing(&FireTemple_Middle, []{return CanUse("Goron Tunic") && SmallKeys(FireTempleKeys, 4) && (GoronBracelet || LogicFireStrength) && (HasExplosives || Bow || Hookshot);}),
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_ProgressiveBombBag,  []{return AddedProgressiveBombBags  == 0;}),
                    AdvancementPairing(A_ProgressiveBombchus, []{return AddedProgressiveBombBags  == 0;}),
                    AdvancementPairing(A_ProgressiveStrength, []{return AddedProgressiveStrengths == 0;}),
                    AdvancementPairing(A_ProgressiveBow,      []{return AddedProgressiveBows      == 0 && IsAdult;}),
                    AdvancementPairing(A_ProgressiveHookshot, []{return AddedProgressiveHookshots == 0 && IsAdult;}),
                    AdvancementPairing(A_SongOfTime,          []{return ProgressiveOcarina        >= 1 && IsAdult;}),
                    AdvancementPairing(FireTemple_SmallKey,   []{return true;}, 4),

  });

  Exit FireTemple_Middle = Exit("Fire Temple Middle", "Fire Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&FireTemple_BoulderMazeLowerChest,    []{return true;}),
                    ItemLocationPairing(&FireTemple_BoulderMazeUpperChest,    []{return SmallKeys(FireTempleKeys, 6);}),
                    ItemLocationPairing(&FireTemple_BoulderMazeSideRoomChest, []{return true;}),
                    ItemLocationPairing(&FireTemple_BoulderMazeShortcutChest, []{return SmallKeys(FireTempleKeys, 6) && HasExplosives;}),
                    ItemLocationPairing(&FireTemple_ScarecrowChest,           []{return SmallKeys(FireTempleKeys, 6) && (CanUse("Scarecrow") || (LogicFireScarecrow && CanUse("Longshot")));}),
                    ItemLocationPairing(&FireTemple_MapChest,                 []{return SmallKeys(FireTempleKeys, 6) || (SmallKeys(FireTempleKeys, 5) && CanUse("Bow"));}),
                    ItemLocationPairing(&FireTemple_CompassChest,             []{return SmallKeys(FireTempleKeys, 6);}),
                    ItemLocationPairing(&FireTemple_GS_BoulderMaze,           []{return SmallKeys(FireTempleKeys, 4) && HasExplosives;}),
                    ItemLocationPairing(&FireTemple_GS_ScarecrowClimb,        []{return SmallKeys(FireTempleKeys, 6) && (CanUse("Scarecrow") || (LogicFireScarecrow && CanUse("Longshot")));}),
                    ItemLocationPairing(&FireTemple_GS_ScarecrowTop,          []{return SmallKeys(FireTempleKeys, 6) && (CanUse("Scarecrow") || (LogicFireScarecrow && CanUse("Longshot")));}),
                  }, {
                    //Exits
                    ExitPairing(&FireTemple_Upper, []{return SmallKeys(FireTempleKeys, 8) || (SmallKeys(FireTempleKeys, 7) && ((CanUse("HoverBoots") && CanUse("Hammer")) || LogicFireFlameMaze));})
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_ProgressiveBombBag,  []{return AddedProgressiveBombBags  == 0;}),
                    AdvancementPairing(A_ProgressiveBombchus, []{return AddedProgressiveBombBags  == 0;}),
                    AdvancementPairing(A_ProgressiveBow,      []{return AddedProgressiveBows      == 0 && IsAdult && SmallKeys(FireTempleKeys, 5);}),
                    AdvancementPairing(A_ProgressiveHookshot, []{return AddedProgressiveHookshots == 0 && IsAdult && CanPlay(ScarecrowSong);}),
                    AdvancementPairing(A_ProgressiveHookshot, []{return AddedProgressiveHookshots == 1 && IsAdult && LogicFireScarecrow;}),
                    AdvancementPairing(A_MegatonHammer,       []{return IsAdult && !LogicFireFlameMaze && SmallKeys(FireTempleKeys, 7);}),
                    AdvancementPairing(A_HoverBoots,          []{return IsAdult && !LogicFireFlameMaze && SmallKeys(FireTempleKeys, 7);}),
                    AdvancementPairing(FireTemple_SmallKey,   []{return true;}, 8),
  });

  Exit FireTemple_Upper = Exit("Fire Temple Upper", "Fire Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&FireTemple_HighestGoronChest,  []{return CanUse("Hammer") && CanPlay(SongOfTime);}),
                    ItemLocationPairing(&FireTemple_MegatonHammerChest, []{return HasExplosives;}),
                  }, {}, {
                    //Advancement Needs
                    AdvancementPairing(A_SongOfTime, []{return ProgressiveOcarina       >= 1 && IsAdult;}),
  });

  Exit WaterTemple_Lobby = Exit("Water Temple Lobby", "Water Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    ChildWaterTemple = IsChild;
                    return true;
                  }, {}, {
                    //Exits
                    ExitPairing(&LH_Main,                       []{return true;}),
                    ExitPairing(&WaterTemple_HighestWaterLevel, []{return IsAdult;}),
                  }, {
  });

  Exit WaterTemple_HighestWaterLevel = Exit("Water Temple Highest Water Level", "Water Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    FairyPot = FairyPot || CanUse("Longshot");
                    WaterTempleClear = BossKeyWaterTemple && CanUse("Longshot");
                    WaterMedallion = WaterMedallion || (WaterTempleClear);
                    return WaterTempleClear;
                  }, {
                    //Locations
                  //Morpha
                  //Water Temple Morpha Heart
                  }, {
                    //Exits
                    ExitPairing(&WaterTemple_DarkLinkRegion, []{return SmallKeys(WaterTempleKeys, 5) && CanUse("Hookshot");}),
                    ExitPairing(&WaterTemple_Dive,           []{return (CanUse("Zora Tunic") || LogicFewerTunicRequirements) && ((LogicWaterTempleTorchLongshot && CanUse("Longshot")) || IronBoots);}),
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_ZoraTunic,            []{return IsAdult && !LogicFewerTunicRequirements;}),
                    AdvancementPairing(A_IronBoots,            []{return IsAdult;}),
                    AdvancementPairing(WaterTemple_SmallKey,   []{return true;}, 5),
                    AdvancementPairing(WaterTemple_BossKey,    []{return true;}),
  });

  Exit WaterTemple_Dive = Exit("Water Temple Dive", "Water Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&WaterTemple_MapChest,              []{return CanUse("Hover Boots") || CanUse("Hookshot") || CanUse("Bow");}),
                    ItemLocationPairing(&WaterTemple_CompassChest,          []{return (CanPlay(ZeldasLullaby) || IronBoots) && CanUse("Hookshot");}),
                    ItemLocationPairing(&WaterTemple_TorchesChest,          []{return (Bow || CanUse("Dins Fire") || (ChildWaterTemple && Sticks && KokiriSword && MagicMeter)) && CanPlay(ZeldasLullaby);}),
                    ItemLocationPairing(&WaterTemple_CentralBowTargetChest, []{return GoronBracelet && CanPlay(ZeldasLullaby) && ((Bow && (LogicWaterCentralBow || HoverBoots || CanUse("Longshot"))));}),
                    ItemLocationPairing(&WaterTemple_GS_BehindGate,         []{return (CanUse("Hookshot") || CanUse("Hover Boots")) && (HasExplosives && CanPlay(ZeldasLullaby)) && (CanUse("Iron Boots") || CanDive);}),
                  }, {
                    //Exits
                    ExitPairing(&WaterTemple_CrackedWall,      []{return CanPlay(ZeldasLullaby) && (CanUse("Hookshot") || CanUse("Hover Boots")) && (LogicWaterCrackedWallNothing || (LogicWaterCrackedWallHovers && CanUse("Hover Boots")));}),
                    ExitPairing(&WaterTemple_MiddleWaterLevel, []{return (Bow || CanUse("Dins Fire") || (SmallKeys(WaterTempleKeys, 6) && CanUse("Hookshot")) || (ChildWaterTemple && Sticks)) && CanPlay(ZeldasLullaby);}),
                    ExitPairing(&WaterTemple_NorthBasement,    []{return SmallKeys(WaterTempleKeys, 5) && (CanUse("Longshot") || (LogicWaterBossKeyRegion && CanUse("Hover Boots"))) && (CanUse("Iron Boots") || CanPlay(ZeldasLullaby));}),
                    ExitPairing(&WaterTemple_DragonStatue,     []{return CanPlay(ZeldasLullaby) && GoronBracelet && ((IronBoots && CanUse("Hookshot")) || (LogicWaterDragonBombchu && HasBombchus && CanDive));}),
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_HoverBoots,          []{return IsAdult;}),
                    AdvancementPairing(A_ProgressiveHookshot, []{return IsAdult && AddedProgressiveHookshots == 0;}),
                    AdvancementPairing(A_ProgressiveHookshot, []{return IsAdult && AddedProgressiveHookshots == 1;}),
                    AdvancementPairing(A_ProgressiveBow,      []{return IsAdult && AddedProgressiveBows      == 0;}),
                    AdvancementPairing(A_ZeldasLullaby,       []{return IsAdult && ProgressiveOcarina        >= 1;}),
                    AdvancementPairing(A_ProgressiveStrength, []{return IsAdult && AddedProgressiveStrengths == 0;}),
                    AdvancementPairing(A_DinsFire,            []{return IsAdult && ProgressiveMagic          >= 1 && AddedProgressiveBows == 0;}),
                    AdvancementPairing(A_ProgressiveMagic,    []{return IsAdult && AddedProgressiveMagics    == 0;}),
                    AdvancementPairing(A_ProgressiveBombchus, []{return LogicWaterDragonBombchu;}),
                    AdvancementPairing(WaterTemple_SmallKey,  []{return true;}, 6),
  });

  Exit WaterTemple_NorthBasement = Exit("Water Temple North Basement", "Water Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    FairyPot = FairyPot || (SmallKeys(WaterTempleKeys, 6) && (LogicWaterBKJumpDive || CanUse("Iron Boots")) && ((LogicWaterBKChest && IronBoots) || LogicWaterNorthBasementLedgeJump || (HasExplosives && GoronBracelet) || HoverBoots));
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&WaterTemple_BossKeyChest, []{return SmallKeys(WaterTempleKeys, 6) && (LogicWaterBKJumpDive || CanUse("Iron Boots")) && ((LogicWaterBKChest && IronBoots) || LogicWaterNorthBasementLedgeJump || (HasExplosives && GoronBracelet) || HoverBoots);}),
                    ItemLocationPairing(&WaterTemple_GS_NearBossKeyChest, []{return true;}),
                  }, {
                    //Exits
                  }, {
                    //Advancement Needs
                    AdvancementPairing(WaterTemple_SmallKey,  []{return true;}, 6),

  });

  Exit WaterTemple_CrackedWall = Exit("Water Temple Cracked Wall", "Water Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&WaterTemple_CrackedWallChest, []{return HasExplosives;}),
                  }, {}, {
                    //Advancement Needs
                    AdvancementPairing(A_ProgressiveBombBag,  []{return AddedProgressiveBombBags == 0;}),
  });

  Exit WaterTemple_DragonStatue = Exit("Water Temple Dragon Statue", "Water Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&WaterTemple_DragonChest, []{return true;}),
                  }, {}, {
  });

  Exit WaterTemple_MiddleWaterLevel = Exit("Water Temple Middle Water Level", "Water Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&WaterTemple_CentralPillarChest, []{return CanUse("Zora Tunic") && CanUse("Hookshot") && ((SmallKeys(WaterTempleKeys, 6) || CanUse("Bow") || CanUse("Dins Fire")));}),
                    ItemLocationPairing(&WaterTemple_GS_CentralPillar,   []{return ((CanUse("Longshot") || (CanUse("Farores Wind") && CanUse("Hookshot"))) && (SmallKeys(WaterTempleKeys, 6) || CanUse("Bow") || CanUse("Dins Fire"))) || (ChildWaterTemple && Boomerang && CanUse("Farores Wind") && (CanUse("Dins Fire") || Sticks));}),
                  }, {
                    //Exits
                    ExitPairing(&WaterTemple_CrackedWall, []{return true;}),
                  }, {
                    //Advancement Needs
                    AdvancementPairing(WaterTemple_SmallKey,  []{return true;}, 6),
  });

  Exit WaterTemple_DarkLinkRegion = Exit("Water Temple Dark Link Region", "Water Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    FairyPot = FairyPot || (SmallKeys(WaterTempleKeys, 6) && CanPlay(SongOfTime));
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&WaterTemple_LongshotChest,          []{return SmallKeys(WaterTempleKeys, 6);}),
                    ItemLocationPairing(&WaterTemple_RiverChest,             []{return SmallKeys(WaterTempleKeys, 6) && CanPlay(SongOfTime) && Bow;}),
                    ItemLocationPairing(&WaterTemple_GS_River,               []{return CanPlay(SongOfTime) && SmallKeys(WaterTempleKeys, 6) && (IronBoots || (LogicWaterRiverGS && CanUse("Longshot") && (Bow || HasBombchus)));}),
                    ItemLocationPairing(&WaterTemple_GS_FallingPlatformRoom, []{return CanUse("Longshot") || (LogicWaterFallingPlatformGS && CanUse("Hookshot"));}),
                  }, {
                    //Exits
                    ExitPairing(&WaterTemple_DragonStatue, []{return SmallKeys(WaterTempleKeys, 6) && CanPlay(SongOfTime) && Bow && ((IronBoots && (CanUse("Zora Tunic") || LogicFewerTunicRequirements)) || LogicWaterDragonJumpDive || (LogicWaterDragonBombchu && HasBombchus && CanDive));}),
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_SongOfTime,         []{return ProgressiveOcarina >= 1;}),
                    AdvancementPairing(WaterTemple_SmallKey, []{return true;}, 6),
  });

  Exit SpiritTemple_Lobby = Exit("Spirit Temple Lobby", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    return true;
                  }, {}, {
                    //Exits
                    ExitPairing(&Colossus_Main,           []{return true;}),
                    ExitPairing(&SpiritTemple_Child,      []{return IsChild;}),
                    ExitPairing(&SpiritTemple_EarlyAdult, []{return CanUse("Silver Gauntlets");}),
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_ProgressiveStrength, []{return IsAdult && AddedProgressiveStrengths == 0;}),
                    AdvancementPairing(A_ProgressiveStrength, []{return IsAdult && AddedProgressiveStrengths == 1;}),
  });

  Exit SpiritTemple_Child = Exit("Child Spirit Temple", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    NutCrate = true;
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&SpiritTemple_ChildBridgeChest,       []{return (Boomerang || Slingshot || (HasExplosives && LogicSpiritChildBombchu)) && (Sticks || HasExplosives || ((Nuts || Boomerang) && (KokiriSword || Slingshot)));}),
                    ItemLocationPairing(&SpiritTemple_ChildEarlyTorchesChest, []{return (Boomerang || Slingshot || (HasExplosives && LogicSpiritChildBombchu)) && (Sticks || HasExplosives || ((Nuts || Boomerang) && (KokiriSword || Slingshot))) && (Sticks || CanUse("Dins Fire"));}),
                    ItemLocationPairing(&SpiritTemple_GS_MetalFence,          []{return (Boomerang || Slingshot || (HasExplosives && LogicSpiritChildBombchu)) && (Sticks || HasExplosives || ((Nuts || Boomerang) && (KokiriSword || Slingshot)));}),
                  }, {
                    //Exits
                    ExitPairing(&SpiritTemple_ChildClimb, []{return SmallKeys(SpiritTempleKeys, 1);}),
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_Boomerang,            []{return !Slingshot || (!HasExplosives && LogicSpiritChildBombchu);}),
                    AdvancementPairing(A_ProgressiveBulletBag, []{return (!Boomerang || (!HasExplosives && LogicSpiritChildBombchu)) && AddedProgressiveBulletBags == 0;}),
                    AdvancementPairing(A_KokiriSword,          []{return !Slingshot;}),
                    AdvancementPairing(A_ProgressiveMagic,     []{return AddedProgressiveMagics   == 0 && !Sticks;}),
                    AdvancementPairing(A_DinsFire,             []{return AddedProgressiveMagics   >= 1 && !Sticks;}),
                    AdvancementPairing(A_ProgressiveBombchus,  []{return AddedProgressiveBombBags == 0;}),
                    AdvancementPairing(A_ProgressiveBombBag,   []{return AddedProgressiveBombBags == 0;}),
                    AdvancementPairing(SpiritTemple_SmallKey,  []{return true;}),
  });

  Exit SpiritTemple_ChildClimb = Exit("Child Spirit Temple Climb", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&SpiritTemple_ChildClimbNorthChest, []{return HasProjectile("Both") || ((SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && !ShuffleDungeonEntrances)) && CanUse("Silver Gauntlets") && HasProjectile("Adult")) || (SmallKeys(SpiritTempleKeys, 5) && IsChild && HasProjectile("Child"));}),
                    ItemLocationPairing(&SpiritTemple_ChildClimbEastChest,  []{return HasProjectile("Both") || ((SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && !ShuffleDungeonEntrances)) && CanUse("Silver Gauntlets") && HasProjectile("Adult")) || (SmallKeys(SpiritTempleKeys, 5) && IsChild && HasProjectile("Child"));}),
                    ItemLocationPairing(&SpiritTemple_GS_SunOnFloorRoom,    []{return HasProjectile("Both") || CanUse("Dins Fire") || ((DamageMultiplier != "OHKO" || Fairy || CanUse("Nayrus Love")) && (Sticks || KokiriSword || HasProjectile("Child"))) || (IsChild && SmallKeys(SpiritTempleKeys, 5) && HasProjectile("Child")) || ((SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && !ShuffleDungeonEntrances)) && CanUse("Silver Gauntlets") && (HasProjectile("Adult") || DamageMultiplier != "OHKO" || Fairy || CanUse("Nayrus Love")));}),
                  }, {
                    //Exits
                    ExitPairing(&SpiritTemple_CentralChamber, []{return HasExplosives;}),
                  }, {
                    //Advancement Needs
                    AdvancementPairing(SpiritTemple_SmallKey, []{return true;}, 5),
  });

  Exit SpiritTemple_EarlyAdult = Exit("Early Adult Spirit Temple", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&SpiritTemple_CompassChest,          []{return CanUse("Hookshot") && CanPlay(ZeldasLullaby);}),
                    ItemLocationPairing(&SpiritTemple_EarlyAdultRightChest,  []{return Bow || Hookshot || HasBombchus || (Bombs && LogicSpiritLowerAdultSwitch);}),
                    ItemLocationPairing(&SpiritTemple_FirstMirrorLeftChest,  []{return SmallKeys(SpiritTempleKeys, 3);}),
                    ItemLocationPairing(&SpiritTemple_FirstMirrorRightChest, []{return SmallKeys(SpiritTempleKeys, 3);}),
                    ItemLocationPairing(&SpiritTemple_GS_BoulderRoom,        []{return CanPlay(SongOfTime) && (Bow || Hookshot || HasBombchus || (Bombs && LogicSpiritLowerAdultSwitch));}),
                  }, {
                    //Exits
                    ExitPairing(&SpiritTemple_CentralChamber, []{return SmallKeys(SpiritTempleKeys, 1);}),
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_ZeldasLullaby,       []{return ProgressiveOcarina        >= 1;}),
                    AdvancementPairing(A_ProgressiveHookshot, []{return IsAdult && AddedProgressiveHookshots == 0;}),
                    AdvancementPairing(A_ProgressiveBow,      []{return IsAdult && AddedProgressiveHookshots == 0 && AddedProgressiveBows == 0;}),
                    AdvancementPairing(A_ProgressiveBombchus, []{return AddedProgressiveBombBags  == 0;}),
                    AdvancementPairing(A_ProgressiveBombBag,  []{return AddedProgressiveBombBags  == 0;}),
                    AdvancementPairing(SpiritTemple_SmallKey, []{return true;}, 3),
  });

  Exit SpiritTemple_CentralChamber = Exit("Spirit Temple Central Chamber", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, []{

                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&SpiritTemple_MapChest,                 []{return ((HasExplosives || SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && !ShuffleDungeonEntrances)) && (CanUse("Dins Fire") || (((MagicMeter && FireArrows) || LogicSpiritMapChest) && Bow && Sticks))) || (SmallKeys(SpiritTempleKeys, 5) && HasExplosives && CanUse("Sticks")) || (SmallKeys(SpiritTempleKeys, 3) && (CanUse("Fire Arrows") || (LogicSpiritMapChest && Bow)) && CanUse("Silver Gauntlets"));}),
                    ItemLocationPairing(&SpiritTemple_SunBlockRoomChest,        []{return ((HasExplosives || SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && !ShuffleDungeonEntrances)) && (CanUse("Dins Fire") || (((MagicMeter && FireArrows) || LogicSpiritMapChest) && Bow && Sticks))) || (SmallKeys(SpiritTempleKeys, 5) && HasExplosives && CanUse("Sticks")) || (SmallKeys(SpiritTempleKeys, 3) && (CanUse("Fire Arrows") || (LogicSpiritMapChest && Bow)) && CanUse("Silver Gauntlets"));}),
                    ItemLocationPairing(&SpiritTemple_StatueRoomHandChest,      []{return SmallKeys(SpiritTempleKeys, 3) && CanUse("Silver Gauntlets") && CanPlay(ZeldasLullaby);}),
                    ItemLocationPairing(&SpiritTemple_StatueRoomNortheastChest, []{return SmallKeys(SpiritTempleKeys, 3) && CanUse("Silver Gauntlets") && CanPlay(ZeldasLullaby) && (Hookshot || HoverBoots);}),
                    ItemLocationPairing(&SpiritTemple_GS_HallAfterSunBlockRoom, []{return (HasExplosives && Boomerang && Hookshot) || (CanUse("Boomerang") && SmallKeys(SpiritTempleKeys, 5) && HasExplosives) || (Hookshot && CanUse("Silver Gauntlets") && (SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && Boomerang && BombchusInLogic && !ShuffleDungeonEntrances)));}),
                    ItemLocationPairing(&SpiritTemple_GS_Lobby,                 []{return ((HasExplosives || SmallKeys(SpiritTempleKeys, 3) || (SmallKeys(SpiritTempleKeys, 2) && BombchusInLogic && !ShuffleDungeonEntrances)) && LogicSpiritLobbyGS && Boomerang && (Hookshot || HoverBoots)) || (LogicSpiritLobbyGS && SmallKeys(SpiritTempleKeys, 5) && HasExplosives && CanUse("Boomerang")) || (SmallKeys(SpiritTempleKeys, 3) && CanUse("Silver Gauntlets") && (Hookshot || HoverBoots));}),
                  }, {
                    //Exits
                    ExitPairing(&SpiritTemple_OutdoorHands,            []{return true;}),
                    ExitPairing(&SpiritTemple_BeyondCentralLockedDoor, []{return SmallKeys(SpiritTempleKeys, 4) && CanUse("Silver Gauntlets");}),
                    ExitPairing(&SpiritTemple_ChildClimb,              []{return true;}),
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_FireArrows, []{return IsAdult && AddedProgressiveBows >= 1 && LogicSpiritMapChest;}),
  });

  Exit SpiritTemple_OutdoorHands = Exit("Spirit Temple Outdoor Hands", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&SpiritTemple_SilverGauntletsChest, []{return (SmallKeys(SpiritTempleKeys, 3) && Longshot && HasExplosives) || SmallKeys(SpiritTempleKeys, 5);}),
                    ItemLocationPairing(&SpiritTemple_MirrorShieldChest,    []{return SmallKeys(SpiritTempleKeys, 4) && CanUse("Silver Gauntlets") && HasExplosives;}),
                  }, {
                    //Exits
                    ExitPairing(&Colossus_Main, []{return (IsChild && SmallKeys(SpiritTempleKeys, 5)) || (CanUse("Silver Gauntlets") && ((SmallKeys(SpiritTempleKeys, 3) && HasExplosives) || SmallKeys(SpiritTempleKeys, 5)));}),
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_ProgressiveHookshot, []{return IsAdult && AddedProgressiveHookshots == 1;}),
                    AdvancementPairing(SpiritTemple_SmallKey, []{return true;}, 5),
  });

  Exit SpiritTemple_BeyondCentralLockedDoor = Exit("Spirit Temple Beyond Central Locked Door", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&SpiritTemple_NearFourArmosChest,         []{return MirrorShield && HasExplosives;}),
                    ItemLocationPairing(&SpiritTemple_HallwayLeftInvisibleChest,  []{return (LogicLensSpirit || CanUse("Lens of Truth")) && HasExplosives;}),
                    ItemLocationPairing(&SpiritTemple_HallwayRightInvisibleChest, []{return (LogicLensSpirit || CanUse("Lens of Truth")) && HasExplosives;}),
                  }, {
                    //Exits
                    ExitPairing(&SpiritTemple_BeyondFinalLockedDoor, []{return SmallKeys(SpiritTempleKeys, 5) && (LogicSpiritWall || CanUse("Longshot") || HasBombchus || ((Bombs || Nuts || CanUse("Dins Fire")) && (Bow || CanUse("Hookshot") || Hammer)));}),
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_MirrorShield, []{return IsAdult;}),
                    AdvancementPairing(A_LensOfTruth,  []{return AddedProgressiveMagics >= 1 && !LogicLensSpirit;}),
  });

  Exit SpiritTemple_BeyondFinalLockedDoor = Exit("Spirit Temple Beyond Final Locked Door", "Spirit Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    SpiritMedallion = SpiritMedallion || (MirrorShield && HasExplosives && Hookshot && BossKeySpiritTemple);
                    return SpiritMedallion;
                  }, {
                    //Locations
                    ItemLocationPairing(&SpiritTemple_BossKeyChest, []{return CanPlay(ZeldasLullaby) && Bow && Hookshot;}),
                    ItemLocationPairing(&SpiritTemple_TopmostChest, []{return MirrorShield;})
                    //Twinrova Heart
                    //Twinrova
                  }, {
                    //Exits
                  }, {
                    //Advancement Needs
                    AdvancementPairing(SpiritTemple_BossKey, []{return true;}),
  });

  Exit ShadowTemple_Entryway = Exit("Shadow Temple Entryway", "Shadow Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    return true;
                  }, {}, {
                    //Exits
                    ExitPairing(&GY_WarpPadRegion,       []{return true;}),
                    ExitPairing(&ShadowTemple_Beginning, []{return (LogicLensShadow || CanUse("Lens of Truth")) && (CanUse("Hover Boots") || CanUse("Hookshot"));}),
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_ProgressiveMagic,    []{return IsAdult && AddedProgressiveMagics    == 0 && LogicLensShadow;}),
                    AdvancementPairing(A_LensOfTruth,         []{return IsAdult && AddedProgressiveMagics    >= 1 && LogicLensShadow;}),
                    AdvancementPairing(A_ProgressiveHookshot, []{return IsAdult && AddedProgressiveHookshots == 0 && !HoverBoots;}),
                    AdvancementPairing(A_HoverBoots,          []{return IsAdult && AddedProgressiveHookshots == 0;}),
  });

  Exit ShadowTemple_Beginning = Exit("Shadow Temple Beginning", "Shadow Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    NutPot = true;
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&ShadowTemple_MapChest,        []{return true;}),
                    ItemLocationPairing(&ShadowTemple_HoverBootsChest, []{return true;}),
                  }, {
                    //Exits
                    ExitPairing(&ShadowTemple_Entryway,    []{return true;}),
                    ExitPairing(&ShadowTemple_FirstBeamos, []{return HoverBoots;}),
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_HoverBoots, []{return true;}),
  });

  Exit ShadowTemple_FirstBeamos = Exit("Shadow Temple First Beamos", "Shadow Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    FairyPot = true;
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&ShadowTemple_CompassChest,          []{return true;}),
                    ItemLocationPairing(&ShadowTemple_EarlySilverRupeeChest, []{return true;}),
                  }, {
                    //Exits
                    ExitPairing(&ShadowTemple_HugePit, []{return HasExplosives && SmallKeys(ShadowTempleKeys, 1);})
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_ProgressiveBombchus, []{return AddedProgressiveBombBags == 0;}),
                    AdvancementPairing(A_ProgressiveBombBag,  []{return AddedProgressiveBombBags == 0;}),
                    AdvancementPairing(ShadowTemple_SmallKey, []{return true;}, 1),
  });

  Exit ShadowTemple_HugePit = Exit("Shadow Temple Huge Pit", "Shadow Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    return true;
                  }, {
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
                    ExitPairing(&ShadowTemple_WindTunnel, []{return (LogicLensShadowBack || CanUse("Lens of Truth")) && Hookshot && SmallKeys(ShadowTempleKeys, 3);}),
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_ProgressiveMagic,    []{return IsAdult && AddedProgressiveMagics    == 1 && LogicLensShadowBack;}),
                    AdvancementPairing(A_LensOfTruth,         []{return IsAdult && AddedProgressiveMagics    >= 1 && LogicLensShadowBack;}),
                    AdvancementPairing(A_ProgressiveHookshot, []{return IsAdult && AddedProgressiveHookshots == 0;}),
                    AdvancementPairing(A_ProgressiveStrength, []{return AddedProgressiveStrengths == 0 && (!HasExplosives || !LogicShadowUmbrella);}),
                    AdvancementPairing(ShadowTemple_SmallKey, []{return true;}, 2),
  });

  Exit ShadowTemple_WindTunnel = Exit("Shadow Temple Wind Tunnel", "Shadow Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&ShadowTemple_WindHintChest,        []{return true;}),
                    ItemLocationPairing(&ShadowTemple_AfterWindEnemyChest,  []{return true;}),
                    ItemLocationPairing(&ShadowTemple_AfterWindHiddenChest, []{return true;}),
                    ItemLocationPairing(&ShadowTemple_GS_NearShip,          []{return CanUse("Longshot") && SmallKeys(ShadowTempleKeys, 4);}),
                  }, {
                    //Exits
                    ExitPairing(&ShadowTemple_BeyondBoat, []{return CanPlay(ZeldasLullaby) && SmallKeys(ShadowTempleKeys, 4);}),
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_ZeldasLullaby,       []{return ProgressiveOcarina       >= 1;}),
                    AdvancementPairing(ShadowTemple_SmallKey, []{return true;}, 4),
  });

  Exit ShadowTemple_BeyondBoat = Exit("Shadow Temple Beyond Boat", "Shadow Temple", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    ShadowMedallion = ShadowMedallion || (SmallKeys(ShadowTempleKeys, 5) && BossKeyShadowTemple && (Bow || CanUse("Distant Scarecrow") || (LogicShadowStatue && HasBombchus)));
                    return ShadowMedallion;
                  }, {
                    //Locations
                    ItemLocationPairing(&ShadowTemple_SpikeWallsLeftChest,       []{return CanUse("Dins Fire");}),
                    ItemLocationPairing(&ShadowTemple_BossKeyChest,              []{return CanUse("Dins Fire");}),
                    ItemLocationPairing(&ShadowTemple_InvisibleFloormasterChest, []{return true;}),
                    //Bongo Bongo Heart
                    //Bongo Bongo
                    ItemLocationPairing(&ShadowTemple_GS_TripleGiantPot,         []{return true;}),
                  }, {}, {
                    //Advancement Needs
                    AdvancementPairing(A_ProgressiveMagic,    []{return AddedProgressiveMagics == 0;}),
                    AdvancementPairing(A_DinsFire,            []{return AddedProgressiveMagics >= 1;}),
                    AdvancementPairing(ShadowTemple_SmallKey, []{return true;}, 5),
  });

  Exit BottomOfTheWell = Exit("Bottom of the Well", "Bottom of the Well", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    return true;
                  }, {}, {
                    //Exits
                    ExitPairing(&Kak_Main,                 []{return true;}),
                    ExitPairing(&BottomOfTheWell_MainArea, []{return IsChild && (CanChildAttack || Nuts);}),
                  }, {
                    //Advancement Needs
  });

  Exit BottomOfTheWell_MainArea = Exit("Bottom of the Well Main Area", "Bottom of the Well", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    StickPot = true;
                    NutPot   = true;
                    return true;
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
                    ItemLocationPairing(&BottomOfTheWell_GS_LikeLikeCage,          []{return SmallKeys(BottomOfTheWellKeys, 3) && (LogicLensBotw || CanUse("Lens of Truth")) && (Boomerang || (LogicBotwCageGS && CanChildAttack));}),
                  }, {
                    //Exits
                    ExitPairing(&BottomOfTheWell, []{return true;}),
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_LensOfTruth,            []{return !LogicLensBotw;}),
                    AdvancementPairing(A_ProgressiveBombchus,    []{return AddedProgressiveBombBags == 0;}),
                    AdvancementPairing(A_ProgressiveBombBag,     []{return AddedProgressiveBombBags == 0;}),
                    AdvancementPairing(A_ZeldasLullaby,          []{return ProgressiveOcarina       >= 1;}),
                    AdvancementPairing(A_ProgressiveMagic,       []{return AddedProgressiveMagics   == 0;}),
                    AdvancementPairing(A_DinsFire,               []{return AddedProgressiveMagics   >= 1;}),
                    AdvancementPairing(A_ProgressiveStrength,    []{return AddedProgressiveBombBags == 0 && AddedProgressiveStrengths == 0;}),
                    AdvancementPairing(BottomOfTheWell_SmallKey, []{return true;}, 3),
  });

  Exit IceCavern_Beginning = Exit("Ice Cavern Beginning", "Ice Cavern", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    return true;
                  }, {}, {
                    //Exits
                    ExitPairing(&ZF_Main,        []{return true;}),
                    ExitPairing(&IceCavern_Main, []{return IsAdult || HasExplosives || CanUse("Dins Fire");}),
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_ProgressiveBombchus, []{return IsChild && AddedProgressiveBombBags == 0 && AddedProgressiveMagics == 0;}),
                    AdvancementPairing(A_ProgressiveBombBag,  []{return IsChild && AddedProgressiveBombBags == 0 && AddedProgressiveMagics == 0;}),
                    AdvancementPairing(A_ProgressiveMagic,    []{return IsChild && AddedProgressiveBombBags == 0 && AddedProgressiveMagics == 0;}),
                    AdvancementPairing(A_DinsFire,            []{return IsChild && AddedProgressiveBombBags == 0 && AddedProgressiveMagics >= 1;}),
  });

  Exit IceCavern_Main = Exit("Ice Cavern", "Ice Cavern", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    BlueFireAccess = BlueFireAccess || (IsAdult && HasBottle);
                    return BlueFireAccess;
                  }, {
                    //Locations
                    ItemLocationPairing(&IceCavern_MapChest,        []{return BlueFire && IsAdult;}),
                    ItemLocationPairing(&IceCavern_CompassChest,    []{return BlueFire;}),
                    ItemLocationPairing(&IceCavern_IronBootsChest,  []{return BlueFire && (IsAdult || Slingshot || Sticks || KokiriSword || CanUse("Dins Fire"));}),
                    //Sheik in Ice Cavern
                    ItemLocationPairing(&IceCavern_FreestandingPoH,       []{return BlueFire;}),
                    ItemLocationPairing(&IceCavern_GS_SpinningScytheRoom, []{return HookshotOrBoomerang;}),
                    ItemLocationPairing(&IceCavern_GS_HeartPieceRoom,     []{return BlueFire && HookshotOrBoomerang;}),
                    ItemLocationPairing(&IceCavern_GS_PushBlockRoom,      []{return BlueFire && HookshotOrBoomerang;}),
                  }, {}, {
                    //Advancement Needs
                    AdvancementPairing(A_EmptyBottle,          []{return !HasBottle;}),
                    AdvancementPairing(A_ProgressiveBulletBag, []{return AddedProgressiveBulletBags == 0 && !Sticks && !KokiriSword && AddedProgressiveMagics == 0;}),
                    AdvancementPairing(A_KokiriSword,          []{return AddedProgressiveBulletBags == 0 && !Sticks && !KokiriSword && AddedProgressiveMagics == 0;}),
                    AdvancementPairing(A_ProgressiveMagic,     []{return AddedProgressiveBulletBags == 0 && !Sticks && !KokiriSword && AddedProgressiveMagics == 0;}),
                    AdvancementPairing(A_DinsFire,             []{return AddedProgressiveBulletBags == 0 && !Sticks && !KokiriSword && AddedProgressiveMagics >= 1;}),
  });

  Exit GerudoTrainingGrounds_Lobby = Exit ("Gerudo Training Grounds Lobby", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&GerudoTrainingGrounds_LobbyLeftChest,  []{return CanUse("Bow") || CanUse("Slingshot");}),
                    ItemLocationPairing(&GerudoTrainingGrounds_LobbyRightChest, []{return CanUse("Bow") || CanUse("Slingshot");}),
                    ItemLocationPairing(&GerudoTrainingGrounds_StalfosChest,    []{return IsAdult || KokiriSword;}),
                    ItemLocationPairing(&GerudoTrainingGrounds_BeamosChest,     []{return HasExplosives && (IsAdult || KokiriSword);}),
                  }, {
                    //Exits
                    ExitPairing(&GF_Main,                              []{return true;}),
                    ExitPairing(&GerudoTrainingGrounds_HeavyBlockRoom, []{return (IsAdult || KokiriSword) && (CanUse("Hookshot") || LogicGtgWithoutHookshot);}),
                    ExitPairing(&GerudoTrainingGrounds_LavaRoom,       []{return (IsAdult || KokiriSword) && HasExplosives;}),
                    ExitPairing(&GerudoTrainingGrounds_CentralMaze,    []{return true;}),
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_ProgressiveBulletBag, []{return IsChild && AddedProgressiveBulletBags == 0;}),
                    AdvancementPairing(A_ProgressiveBow,       []{return IsAdult && AddedProgressiveBows       == 0;}),
                    AdvancementPairing(A_KokiriSword,          []{return IsChild;}),
                    AdvancementPairing(A_ProgressiveBombchus,  []{return AddedProgressiveBombBags  == 0;}),
                    AdvancementPairing(A_ProgressiveBombBag,   []{return AddedProgressiveBombBags  == 0;}),
                    AdvancementPairing(A_ProgressiveHookshot,  []{return AddedProgressiveHookshots == 0 && !LogicGtgWithoutHookshot;}),
  });

  Exit GerudoTrainingGrounds_CentralMaze = Exit ("Gerudo Training Grounds Central Maze", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&GerudoTrainingGrounds_HiddenCeilingChest,  []{return SmallKeys(GerudoTrainingGroundsKeys, 3) && (LogicLensGtg || CanUse("Lens of Truth"));}),
                    ItemLocationPairing(&GerudoTrainingGrounds_MazePathFirstChest,  []{return SmallKeys(GerudoTrainingGroundsKeys, 4);}),
                    ItemLocationPairing(&GerudoTrainingGrounds_MazePathSecondChest, []{return SmallKeys(GerudoTrainingGroundsKeys, 6);}),
                    ItemLocationPairing(&GerudoTrainingGrounds_MazePathThirdChest,  []{return SmallKeys(GerudoTrainingGroundsKeys, 7);}),
                    ItemLocationPairing(&GerudoTrainingGrounds_MazePathFinalChest,  []{return SmallKeys(GerudoTrainingGroundsKeys, 9);}),
                  }, {
                    //Exits
                    ExitPairing(&GerudoTrainingGrounds_CentralMazeRight, []{return SmallKeys(GerudoTrainingGroundsKeys, 9);}),
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_ProgressiveMagic,             []{return AddedProgressiveMagics == 0 && !LogicLensGtg;}),
                    AdvancementPairing(A_LensOfTruth,                  []{return ProgressiveMagic       >= 1 && !LogicLensGtg;}),
                    AdvancementPairing(GerudoTrainingGrounds_SmallKey, []{return true;}, 9)
  });

  Exit GerudoTrainingGrounds_CentralMazeRight = Exit("Gerudo Training Grounds Central Maze Right", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&GerudoTrainingGrounds_MazeRightCentralChest, []{return true;}),
                    ItemLocationPairing(&GerudoTrainingGrounds_MazeRightSideChest,    []{return true;}),
                    ItemLocationPairing(&GerudoTrainingGrounds_FreestandingKey,       []{return true;}),
                  }, {
                    //Exits
                    ExitPairing(&GerudoTrainingGrounds_HammerRoom, []{return CanUse("Hookshot");}),
                    ExitPairing(&GerudoTrainingGrounds_LavaRoom,   []{return true;}),
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_ProgressiveHookshot,  []{return IsAdult;}),
  });

  Exit GerudoTrainingGrounds_LavaRoom = Exit("Gerudo Training Grounds Lava Room", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&GerudoTrainingGrounds_UnderwaterSilverRupeeChest, []{return CanUse("Hookshot") && CanPlay(SongOfTime) && IronBoots && (LogicFewerTunicRequirements || CanUse("Zora Tunic"));}),
                  }, {
                    //Exits
                    ExitPairing(&GerudoTrainingGrounds_CentralMazeRight, []{return CanPlay(SongOfTime) || IsChild;}),
                    ExitPairing(&GerudoTrainingGrounds_HammerRoom,       []{return CanUse("Longshot")  || (CanUse("Hover Boots") && CanUse("Hookshot"));}),
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_SongOfTime,          []{return IsAdult && ProgressiveOcarina        >= 1;}),
                    AdvancementPairing(A_IronBoots,           []{return IsAdult;}),
                    AdvancementPairing(A_ZoraTunic,           []{return IsAdult &&!LogicFewerTunicRequirements;}),
                    AdvancementPairing(A_ProgressiveHookshot, []{return IsAdult && AddedProgressiveHookshots == 0;}),
                    AdvancementPairing(A_HoverBoots,          []{return IsAdult && AddedProgressiveHookshots <= 1;}),
                    AdvancementPairing(A_ProgressiveHookshot, []{return IsAdult && AddedProgressiveHookshots == 1 && !HoverBoots;}),
  });

  Exit GerudoTrainingGrounds_HammerRoom = Exit("Gerudo Training Grounds Hammer Room", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&GerudoTrainingGrounds_HammerRoomClearChest,  []{return true;}),
                    ItemLocationPairing(&GerudoTrainingGrounds_HammerRoomSwitchChest, []{return CanUse("Hammer");})
                  }, {
                    //Exits
                    ExitPairing(&GerudoTrainingGrounds_EyeStatueLower, []{return CanUse("Hammer") && Bow;}),
                    ExitPairing(&GerudoTrainingGrounds_LavaRoom,       []{return true;}),
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_MegatonHammer,  []{return true;}),
                    AdvancementPairing(A_ProgressiveBow, []{return AddedProgressiveBows == 0;}),
  });

  Exit GerudoTrainingGrounds_EyeStatueLower = Exit("Gerudo Training Grounds Eye Statue Lower", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&GerudoTrainingGrounds_EyeStatueChest, []{return CanUse("Bow");}),
                  }, {
                    //Exits
                    ExitPairing(&GerudoTrainingGrounds_HammerRoom, []{return true;}),
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_ProgressiveBow, []{return AddedProgressiveBows == 0;}),
  });

  Exit GerudoTrainingGrounds_EyeStatueUpper = Exit("Gerudo Training Grounds Eye Statue Upper", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&GerudoTrainingGrounds_NearScarecrowChest, []{return CanUse("Bow");})
                  }, {
                    //Exits
                    ExitPairing(&GerudoTrainingGrounds_EyeStatueLower, []{return true;}),
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_ProgressiveBow, []{return AddedProgressiveBows == 0;}),
  });

  Exit GerudoTrainingGrounds_HeavyBlockRoom = Exit("Gerudo Training Grounds Heavy Block Room", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&GerudoTrainingGrounds_BeforeHeavyBlockChest, []{return true;})
                  }, {
                    //Exits
                    ExitPairing(&GerudoTrainingGrounds_EyeStatueUpper, []{return (LogicLensGtg || CanUse("Lens of Truth")) && (CanUse("Hookshot") || (LogicGtgFakeWall && CanUse("Hover Boots")));}),
                    ExitPairing(&GerudoTrainingGrounds_LikeLikeRoom,   []{return (LogicLensGtg || CanUse("Lens of Truth")) && (CanUse("Hookshot") || (LogicGtgFakeWall && CanUse("Hover Boots"))) && CanUse("Silver Gauntlets");}),
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_ProgressiveMagic,       []{return AddedProgressiveMagics    == 0 && !LogicLensGtg;}),
                    AdvancementPairing(A_LensOfTruth,            []{return ProgressiveMagic          >= 1 && !LogicLensGtg;}),
                    AdvancementPairing(A_ProgressiveHookshot,    []{return AddedProgressiveHookshots == 0;}),
                    AdvancementPairing(A_ProgressiveStrength,    []{return AddedProgressiveStrengths == 0;}),
                    AdvancementPairing(A_ProgressiveStrength,    []{return AddedProgressiveStrengths == 1;}),
                    AdvancementPairing(A_HoverBoots,             []{return LogicGtgFakeWall;}),
  });

  Exit GerudoTrainingGrounds_LikeLikeRoom = Exit("Gerudo Training Grounds Like Like Room", "Gerudo Training Grounds", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    return true;
                  }, {
                    //Locations
                    ItemLocationPairing(&GerudoTrainingGrounds_HeavyBlockFirstChest,  []{return true;}),
                    ItemLocationPairing(&GerudoTrainingGrounds_HeavyBlockSecondChest, []{return true;}),
                    ItemLocationPairing(&GerudoTrainingGrounds_HeavyBlockThirdChest,  []{return true;}),
                    ItemLocationPairing(&GerudoTrainingGrounds_HeavyBlockFourthChest, []{return true;}),
                  }, {}, {
  });

  Exit GanonsCastle_Lobby = Exit("Ganon's Castle Lobby", "Ganon's Castle", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    return true;
                  }, {}, {
                    //Exits
                    ExitPairing(&OGC_Grounds,              []{return true;}),
                    ExitPairing(&GanonsCastle_ForestTrial, []{return true;}),
                    ExitPairing(&GanonsCastle_FireTrial,   []{return true;}),
                    ExitPairing(&GanonsCastle_WaterTrial,  []{return true;}),
                    ExitPairing(&GanonsCastle_ShadowTrial, []{return true;}),
                    ExitPairing(&GanonsCastle_SpiritTrial, []{return true;}),
                    ExitPairing(&GanonsCastle_LightTrial,  []{return CanUse("Golden Gauntlets");}),
                    ExitPairing(&GanonsCastle_Tower,       []{return SkippedTrials || (ForestTrialClear && FireTrialClear && WaterTrialClear && ShadowTrialClear && SpiritTrialClear && LightTrialClear);}),
                    ExitPairing(&GanonsCastle_DekuScrubs,  []{return LogicLensCastle || CanUse("Lens of Truth");}),
                  }, {
                    //Advancement Needs
                    AdvancementPairing(A_ProgressiveStrength, []{return AddedProgressiveStrengths == 0;}),
                    AdvancementPairing(A_ProgressiveStrength, []{return AddedProgressiveStrengths == 1;}),
                    AdvancementPairing(A_ProgressiveStrength, []{return AddedProgressiveStrengths == 2;}),
                    AdvancementPairing(A_ProgressiveMagic,    []{return AddedProgressiveMagics    == 0 && !LogicLensCastle;}),
                    AdvancementPairing(A_LensOfTruth,         []{return ProgressiveMagic          >= 1 && !LogicLensCastle;}),
  });

  Exit GanonsCastle_DekuScrubs = Exit("Ganon's Castle Deku Scrubs", "Ganon's Castle", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    FreeFairies = true;
                    return true;
                  }, {
                    //Locations
                    //Ganons Castle Deku Scrub Center Left
                    //Ganons Castle Deku Scrub Center Right
                    //Ganons Castle Deku Scrub Right
                    //Ganons Castle Deku Scrub Left
                  }, {}, {
                    //Advancement Needs
  });

  Exit GanonsCastle_ForestTrial = Exit("Ganon's Castle Forest Trial", "Ganon's Castle", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    ForestTrialClear = CanUse("Light Arrows") && (FireArrows || DinsFire);
                    return ForestTrialClear;
                  }, {
                    //Locations
                    ItemLocationPairing(&GanonsCastle_ForestTrialChest, []{return true;}),
                  }, {}, {
                    //Advancement Needs
                    AdvancementPairing(A_ProgressiveMagic, []{return AddedProgressiveMagics == 0;}),
                    AdvancementPairing(A_DinsFire,         []{return AddedProgressiveMagics >= 1 && !FireArrows;}),
                    AdvancementPairing(A_ProgressiveBow,   []{return AddedProgressiveBows   == 0 && !DinsFire;}),
                    AdvancementPairing(A_FireArrows,       []{return ProgressiveBow         >= 1 && ProgressiveMagic >= 1 && !DinsFire;}),
                    AdvancementPairing(A_LightArrows,      []{return ProgressiveBow         >= 1 && ProgressiveMagic >= 1;}),
  });

  Exit GanonsCastle_FireTrial = Exit("Ganon's Castle Fire Trial", "Ganon's Castle", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    FireTrialClear = CanUse("Goron Tunic") && CanUse("Golden Gauntlets") && CanUse("Light Arrows") && CanUse("Longshot");
                    return FireTrialClear;
                  }, {}, {}, {
                    //Advancement Needs
                    AdvancementPairing(A_ProgressiveBow,   []{return AddedProgressiveBows   == 0;}),
                    AdvancementPairing(A_ProgressiveMagic, []{return AddedProgressiveMagics == 0;}),
                    AdvancementPairing(A_LightArrows,      []{return ProgressiveBow         >= 1 && ProgressiveMagic >= 1;}),
  });

  Exit GanonsCastle_WaterTrial = Exit("Ganon's Castle Water Trial", "Ganon's Castle", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    BlueFireAccess  = true;
                    FairyPot        = FairyPot || BlueFire;
                    WaterTrialClear = BlueFire && Hammer && CanUse("Light Arrows");
                    return WaterTrialClear;
                  }, {
                    //Locations
                    ItemLocationPairing(&GanonsCastle_WaterTrialLeftChest,  []{return true;}),
                    ItemLocationPairing(&GanonsCastle_WaterTrialRightChest, []{return true;}),
                  }, {}, {
                    //Advancement Needs
                    AdvancementPairing(A_EmptyBottle,      []{return true;}),
                    AdvancementPairing(A_MegatonHammer,    []{return IsAdult;}),
                    AdvancementPairing(A_ProgressiveBow,   []{return AddedProgressiveBows   == 0;}),
                    AdvancementPairing(A_ProgressiveMagic, []{return AddedProgressiveMagics == 0;}),
                    AdvancementPairing(A_LightArrows,      []{return ProgressiveBow         >= 1 && ProgressiveMagic >= 1;}),
  });

  Exit GanonsCastle_ShadowTrial = Exit("Ganon's Castle Shadow Trial", "Ganon's Castle", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    ShadowTrialClear = CanUse("Light Arrows") && Hammer && ((FireArrows && (LogicLensCastle || CanUse("Lens of Truth"))) || (CanUse("Longshot") && (HoverBoots || (DinsFire && (LogicLensCastle || CanUse("Lens of Truth"))))));
                    return ShadowTrialClear;
                  }, {
                    //Locations
                    ItemLocationPairing(&GanonsCastle_ShadowTrialFrontChest,           []{return CanUse("Fire Arrows") || Hookshot || HoverBoots || CanPlay(SongOfTime);}),
                    ItemLocationPairing(&GanonsCastle_ShadowTrialGoldenGauntletsChest, []{return CanUse("Fire Arrows") || (CanUse("Longshot") && (HoverBoots || CanUse("Dins Fire")));}),
                  }, {}, {
                    //Advancement Needs
                    AdvancementPairing(A_ProgressiveBow,   []{return AddedProgressiveBows   == 0;}),
                    AdvancementPairing(A_ProgressiveMagic, []{return AddedProgressiveMagics == 0;}),
                    AdvancementPairing(A_LightArrows,      []{return ProgressiveBow         >= 1 && ProgressiveMagic >= 1;}),
  });

  Exit GanonsCastle_SpiritTrial = Exit("Ganon's Castle Spirit Trial", "Ganon's Castle", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    NutPot = NutPot || ((LogicSpiritTrialHookshot || Hookshot) && HasBombchus && Bow && MirrorShield);
                    SpiritTrialClear = CanUse("Light Arrows")  && MirrorShield && HasBombchus && (LogicSpiritTrialHookshot || Hookshot);
                    return SpiritTrialClear;
                  }, {
                    //Locations
                    ItemLocationPairing(&GanonsCastle_SpiritTrialCrystalSwitchChest, []{return LogicSpiritTrialHookshot || Hookshot;}),
                    ItemLocationPairing(&GanonsCastle_SpiritTrialInvisibleChest,     []{return (LogicSpiritTrialHookshot || Hookshot) && HasBombchus && (LogicLensCastle || CanUse("Lens of Truth"));}),
                  }, {}, {
                    //Advancement Needs
                    AdvancementPairing(A_ProgressiveBow,   []{return AddedProgressiveBows   == 0;}),
                    AdvancementPairing(A_ProgressiveMagic, []{return AddedProgressiveMagics == 0;}),
                    AdvancementPairing(A_LightArrows,      []{return ProgressiveBow         >= 1 && ProgressiveMagic >= 1;}),
  });

  Exit GanonsCastle_LightTrial = Exit("Ganon's Castle Light Trial", "Ganon's Castle", "", NO_DAY_NIGHT_CYCLE, []{
                    //Events
                    LightTrialClear = CanUse("Light Arrows") && Hookshot && SmallKeys(GanonsCastleKeys, 2) && (LogicLensCastle || CanUse("Lens of Truth"));
                    return LightTrialClear;
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
                  }, {}, {
                    //Advancement Needs
                    AdvancementPairing(A_LensOfTruth,         []{return ProgressiveMagic         >= 1 && !LogicLensCastle;}),
                    AdvancementPairing(A_ZeldasLullaby,       []{return ProgressiveOcarina       >= 1;}),
                    AdvancementPairing(A_ProgressiveBow,      []{return AddedProgressiveBows     == 0;}),
                    AdvancementPairing(A_ProgressiveMagic,    []{return AddedProgressiveMagics   == 0;}),
                    AdvancementPairing(A_LightArrows,         []{return ProgressiveBow           >= 1 && ProgressiveMagic >= 1;}),
                    AdvancementPairing(GanonsCastle_SmallKey, []{return true;}, 2),
  });

  Exit GanonsCastle_Tower = Exit("Ganon's Castle Tower", "Ganons Castle", "", NO_DAY_NIGHT_CYCLE, []{
                  //Events
                  return true;
                }, {
                  //Locations
                  ItemLocationPairing(&GanonsCastle_BossKeyChest, []{return true;}),
                  //Ganondorf Hint
                  //Ganon
                }, {}, {
                  //Advancement Needs
                  AdvancementPairing(GanonsCastle_BossKey, []{return true;}),
  });

  /*
  //Events
  return true;
}, {
  //Locations

}, {
  //Exits
}, {
  //Advancement Needs

*/

  std::vector<Exit *> ExitPool = {};
}
