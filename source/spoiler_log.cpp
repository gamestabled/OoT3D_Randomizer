#include "spoiler_log.hpp"
#include "item_location.hpp"
#include "item_list.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include <set>
#include <cstring>
#include <vector>
#include <string>

int LONGEST_LINE = 53;

Result res = 0;
FS_Archive sdmcArchive = 0;
Handle spoilerlog;
Handle placementlog;
u32 bytesWritten = 0;
u32 totalRW = 0;

std::string logtxt = "";
std::string placementtxt = "";
std::vector<ItemLocation *> allLocations = {
  &KF_KokiriSwordChest,
  &KF_MidoTopLeftChest,
  &KF_MidoTopRightChest,
  &KF_MidoBottomLeftChest,
  &KF_MidoBottomRightChest,
  &KF_StormsGrottoChest,

  //Lost Woods
  &LW_SkullKid,
  &LW_OcarinaMemoryGame,
  &LW_TargetInWoods,
  //&LW_DekuScrubNearDekuTheaterRight,
  //&LW_DekuScrubNearDekuTheaterLeft,
  //&LW_DekuScrubNearBridge,
  //&LW_GSBeanPatchNearBridge,
  //&LW_GossipStone,
  &LW_NearShortcutsGrottoChest,
  //&LW_DekuScrubGrottoRear,
  //&LW_DekuScrubGrottoFront,
  &DekuTheater_SkullMask,
  &DekuTheater_MaskOfTruth,

  //Sacred Forest Meadow
  &SFM_WolfosGrottoChest,
  //&SFM_DekuScrubGrottoRear,
  //&SFM_DekuScrubGrottoFront,

  //Hyrule Field
  &HF_SoutheastGrottoChest,
  &HF_OpenGrottoChest,
  &HF_NearMarketGrottoChest,
  &HF_OcarinaOfTimeItem,
  &HF_TektiteGrottoFreestandingPoH,
  &HF_DekuScrubGrotto,

  //Lake Hylia
  &LH_ChildFishing,
  &LH_AdultFishing,
  &LH_LabDive,
  &LH_UnderwaterItem,
  &LH_Sun,
  &LH_FreestandingPoH,
  //&LH_DekuScrubGrottoLeft,
  //&LH_DekuScrubGrottoRight,
  //&LH_DekuScrubGrottoCenter,

  //Gerudo Valley
  &GV_Chest,
  &GV_WaterfallFreestandingPoH,
  &GV_CrateFreestandingPoH,
  //&GV_DekuScrubGrottoRear,
  //&GV_DekuScrubGrottoFront,

  //Gerudo Fortress
  &GF_Chest,
  &GF_HBA1000Points,
  &GF_HBA1500Points,
  &GF_NorthF1Carpenter,
  &GF_NorthF2Carpenter,
  &GF_SouthF1Carpenter,
  &GF_SouthF2Carpenter,
  &GF_GerudoToken,

  //Haunted Wasteland
  &HW_Chest,

  //Desert Colossus
  &Colossus_FreestandingPoH,
  //&Colossus_DekuScrubGrottoRear,
  //&Colossus_DekuScrubGrottoFront,

  //Market
  &MK_TreasureChestGameReward,
  //&MK_BombchuBowlingFirstPrize,
  //&MK_BombchuBowlingSecondPrize,
  &MK_LostDog,
  &MK_ShootingGalleryReward,
  //&MK_10BigPoes,

  //Hyrule Castle
  &HC_ZeldasLetter,
  &HC_MalonEgg,

  //Kakariko
  &Kak_RedeadGrottoChest,
  &Kak_OpenGrottoChest,
  &Kak_10GoldSkulltulaReward,
  &Kak_20GoldSkulltulaReward,
  &Kak_30GoldSkulltulaReward,
  &Kak_40GoldSkulltulaReward,
  &Kak_50GoldSkulltulaReward,
  &Kak_ManOnRoof,
  &Kak_ShootingGalleryReward,
  &Kak_AnjuAsChild,
  &Kak_AnjuAsAdult,
  &Kak_ImpasHouseFreestandingPoH,
  &Kak_WindmillFreestandingPoH,

  //Graveyard
  //&GY_HookshotChest,
  &GY_ShieldGraveChest,
  &GY_HeartPieceGraveChest,
  &GY_ComposersGraveChest,
  &GY_FreestandingPoH,
  &GY_DampeRaceFreestandingPoH,
  &GY_DampeGravediggingTour,

  //Death Mountain Trail
  &DMT_Chest,
  &DMT_StormsGrottoChest,
  &DMT_Biggoron,
  //&DMT_GreatFairyReward,
  &DMT_FreestandingPoH,

  //Goron City
  &GC_MazeLeftChest,
  &GC_MazeCenterChest,
  &GC_MazeRightChest,
  &GC_RollingGoronAsChild,
  &GC_RollingGoronAsAdult,
  &GC_DaruniasJoy,
  &GC_PotFreestandingPoH,
  //&GC_DekuScrubGrottoLeft,
  //&GC_DekuScrubGrottoRight,
  //&GC_DekuScrubGrottoCenter,

  //Death Mountain
  &DMC_UpperGrottoChest,
  &DMC_WallFreestandingPoH,
  &DMC_VolcanoFreestandingPoH,
  //&DMC_DekuScrubGrottoLeft,
  //&DMC_DekuScrubGrottoRight,
  //&DMC_DekuScrubGrottoCenter,

  //Zoras River
  &ZR_OpenGrottoChest,
  &ZR_MagicBeanSalesman,
  &ZR_FrogsOcarinaGame,
  &ZR_FrogsInTheRain,
  &ZR_NearOpenGrottoFreestandingPoH,
  &ZR_NearDomainFreestandingPoH,
  //&ZR_DekuScrubGrottoRear,
  //&ZR_DekuScrubGrottoFront,

  //Zoras Domain
  &ZD_Chest,
  &ZD_DivingMinigame,
  &ZD_KingZoraThawed,

  //Zoras Fountain
  &ZF_IcebergFreestandingPoH,
  &ZF_BottomFreestandingPoH,

  //Lon Lon Ranch
  &LLR_TalonsChickens,
  &LLR_FreestandingPoH,
  //&LLR_DekuScrubGrottoLeft,
  //&LLR_DekuScrubGrottoRight,
  //&LLR_DekuScrubGrottoCenter,

  //Deku Tree
  &DekuTree_MapChest,
  &DekuTree_CompassChest,
  &DekuTree_CompassRoomSideChest,
  &DekuTree_BasementChest,
  &DekuTree_SlingshotChest,
  &DekuTree_SlingshotRoomSideChest,

  //Dodongos Cavern
  &DodongosCavern_MapChest,
  &DodongosCavern_CompassChest,
  &DodongosCavern_BombFlowerPlatformChest,
  &DodongosCavern_BombBagChest,
  &DodongosCavern_EndOfBridgeChest,
  &DodongosCavern_BossRoomChest,

  //Jabu Jabus Belly
  &JabuJabusBelly_MapChest,
  &JabuJabusBelly_CompassChest,
  &JabuJabusBelly_BoomerangChest,

  //Forest Temple
  &ForestTemple_FirstRoomChest,
  &ForestTemple_FirstStalfosChest,
  &ForestTemple_RaisedIslandCourtyardChest,
  &ForestTemple_MapChest,
  &ForestTemple_WellChest,
  &ForestTemple_FallingCeilingRoomChest,
  &ForestTemple_EyeSwitchChest,
  &ForestTemple_BossKeyChest,
  &ForestTemple_FloormasterChest,
  &ForestTemple_BowChest,
  &ForestTemple_RedPoeChest,
  &ForestTemple_BluePoeChest,
  &ForestTemple_BasementChest,

  //Fire Temple
  &FireTemple_NearBossChest,
  &FireTemple_FlareDancerChest,
  &FireTemple_BossKeyChest,
  &FireTemple_BigLavaRoomBlockedDoorChest,
  &FireTemple_BigLavaRoomLowerOpenDoorChest,
  &FireTemple_BoulderMazeLowerChest,
  &FireTemple_BoulderMazeUpperChest,
  &FireTemple_BoulderMazeSideRoomChest,
  &FireTemple_BoulderMazeShortcutChest,
  &FireTemple_ScarecrowChest,
  &FireTemple_MapChest,
  &FireTemple_CompassChest,
  &FireTemple_HighestGoronChest,
  &FireTemple_MegatonHammerChest,

  //Water Temple
  &WaterTemple_MapChest,
  &WaterTemple_CompassChest,
  &WaterTemple_TorchesChest,
  &WaterTemple_DragonChest,
  &WaterTemple_CentralBowTargetChest,
  &WaterTemple_CentralPillarChest,
  &WaterTemple_CrackedWallChest,
  &WaterTemple_BossKeyChest,
  &WaterTemple_LongshotChest,
  &WaterTemple_RiverChest,

  //Spirit Temple
  &SpiritTemple_SilverGauntletsChest,
  &SpiritTemple_MirrorShieldChest,
  &SpiritTemple_ChildBridgeChest,
  &SpiritTemple_ChildEarlyTorchesChest,
  &SpiritTemple_CompassChest,
  &SpiritTemple_EarlyAdultRightChest,
  &SpiritTemple_FirstMirrorLeftChest,
  &SpiritTemple_FirstMirrorRightChest,
  &SpiritTemple_MapChest,
  &SpiritTemple_ChildClimbNorthChest,
  &SpiritTemple_ChildClimbEastChest,
  &SpiritTemple_SunBlockRoomChest,
  &SpiritTemple_StatueRoomHandChest,
  &SpiritTemple_StatueRoomNortheastChest,
  &SpiritTemple_NearFourArmosChest,
  &SpiritTemple_HallwayLeftInvisibleChest,
  &SpiritTemple_HallwayRightInvisibleChest,
  &SpiritTemple_BossKeyChest,
  &SpiritTemple_TopmostChest,

  //Shadow Temple
  &ShadowTemple_MapChest,
  &ShadowTemple_HoverBootsChest,
  &ShadowTemple_CompassChest,
  &ShadowTemple_EarlySilverRupeeChest,
  &ShadowTemple_InvisibleBladesVisibleChest,
  &ShadowTemple_InvisibleBladesInvisibleChest,
  &ShadowTemple_FallingSpikesLowerChest,
  &ShadowTemple_FallingSpikesUpperChest,
  &ShadowTemple_FallingSpikesSwitchChest,
  &ShadowTemple_InvisibleSpikesChest,
  &ShadowTemple_WindHintChest,
  &ShadowTemple_AfterWindEnemyChest,
  &ShadowTemple_AfterWindHiddenChest,
  &ShadowTemple_SpikeWallsLeftChest,
  &ShadowTemple_BossKeyChest,
  &ShadowTemple_InvisibleFloormasterChest,
  &ShadowTemple_FreestandingKey,

  //Bottom of the Well
  &BottomOfTheWell_FrontLeftFakeWallChest,
  &BottomOfTheWell_FrontCenterBombableChest,
  &BottomOfTheWell_RightBottomFakeWallChest,
  &BottomOfTheWell_CompassChest,
  &BottomOfTheWell_CenterSkulltulaChest,
  &BottomOfTheWell_BackLeftBombableChest,
  &BottomOfTheWell_LensOfTruthChest,
  &BottomOfTheWell_InvisibleChest,
  &BottomOfTheWell_UnderwaterFrontChest,
  &BottomOfTheWell_UnderwaterLeftChest,
  &BottomOfTheWell_MapChest,
  &BottomOfTheWell_FireKeeseChest,
  &BottomOfTheWell_LikeLikeChest,
  &BottomOfTheWell_FreestandingKey,

  //Ice Cavern
  &IceCavern_MapChest,
  &IceCavern_CompassChest,
  &IceCavern_IronBootsChest,
  &IceCavern_FreestandingPoH,

  //Gerudo Training Grounds
  &GerudoTrainingGrounds_LobbyLeftChest,
  &GerudoTrainingGrounds_LobbyRightChest,
  &GerudoTrainingGrounds_StalfosChest,
  &GerudoTrainingGrounds_BeamosChest,
  &GerudoTrainingGrounds_HiddenCeilingChest,
  &GerudoTrainingGrounds_MazePathFirstChest,
  &GerudoTrainingGrounds_MazePathSecondChest,
  &GerudoTrainingGrounds_MazePathThirdChest,
  &GerudoTrainingGrounds_MazePathFinalChest,
  &GerudoTrainingGrounds_MazeRightCentralChest,
  &GerudoTrainingGrounds_MazeRightSideChest,
  &GerudoTrainingGrounds_UnderwaterSilverRupeeChest,
  &GerudoTrainingGrounds_HammerRoomClearChest,
  &GerudoTrainingGrounds_HammerRoomSwitchChest,
  &GerudoTrainingGrounds_EyeStatueChest,
  &GerudoTrainingGrounds_NearScarecrowChest,
  &GerudoTrainingGrounds_BeforeHeavyBlockChest,
  &GerudoTrainingGrounds_HeavyBlockFirstChest,
  &GerudoTrainingGrounds_HeavyBlockSecondChest,
  &GerudoTrainingGrounds_HeavyBlockThirdChest,
  &GerudoTrainingGrounds_HeavyBlockFourthChest,
  &GerudoTrainingGrounds_FreestandingKey,

  //Ganon's Castle
  &GanonsCastle_ForestTrialChest,
  &GanonsCastle_WaterTrialLeftChest,
  &GanonsCastle_WaterTrialRightChest,
  &GanonsCastle_ShadowTrialFrontChest,
  &GanonsCastle_ShadowTrialGoldenGauntletsChest,
  &GanonsCastle_SpiritTrialCrystalSwitchChest,
  &GanonsCastle_SpiritTrialInvisibleChest,
  &GanonsCastle_LightTrialFirstLeftChest,
  &GanonsCastle_LightTrialSecondLeftChest,
  &GanonsCastle_LightTrialThirdLeftChest,
  &GanonsCastle_LightTrialFirstRightChest,
  &GanonsCastle_LightTrialSecondRightChest,
  &GanonsCastle_LightTrialThirdRightChest,
  &GanonsCastle_LightTrialInvisibleEnemiesChest,
  &GanonsCastle_LightTrialLullabyChest,
  &GanonsCastle_BossKeyChest,

  /*-------------------------------
     --- GOLD SKULLTULA TOKENS ---
    -------------------------------*/

  //Deku Tree
  &DekuTree_GS_BasementBackRoom,
  &DekuTree_GS_BasementGate,
  &DekuTree_GS_BasementVines,
  &DekuTree_GS_CompassRoom,

  //Dodongos Cavern
  &DodongosCavern_GS_VinesAboveStairs,
  &DodongosCavern_GS_Scarecrow,
  &DodongosCavern_GS_AlcoveAboveStairs,
  &DodongosCavern_GS_BackRoom,
  &DodongosCavern_GS_SideRoomNearLowerLizalfos,

  //Jabu Jabus Belly
  &JabuJabusBelly_GS_LobbyBasementLower,
  &JabuJabusBelly_GS_LobbyBasementUpper,
  &JabuJabusBelly_GS_NearBoss,
  &JabuJabusBelly_GS_WaterSwitchRoom,

  //Forest Temple
  &ForestTemple_GS_RaisedIslandCourtyard,
  &ForestTemple_GS_FirstRoom,
  &ForestTemple_GS_LevelIslandCourtyard,
  &ForestTemple_GS_Lobby,
  &ForestTemple_GS_Basement,

  //Fire Temple
  &FireTemple_GS_SongOfTimeRoom,
  &FireTemple_GS_BossKeyLoop,
  &FireTemple_GS_BoulderMaze,
  &FireTemple_GS_ScarecrowTop,
  &FireTemple_GS_ScarecrowClimb,

  //Water Temple
  &WaterTemple_GS_BehindGate,
  &WaterTemple_GS_FallingPlatformRoom,
  &WaterTemple_GS_CentralPillar,
  &WaterTemple_GS_NearBossKeyChest,
  &WaterTemple_GS_River,

  //Spirit Temple
  &SpiritTemple_GS_HallAfterSunBlockRoom,
  &SpiritTemple_GS_BoulderRoom,
  &SpiritTemple_GS_Lobby,
  &SpiritTemple_GS_SunOnFloorRoom,
  &SpiritTemple_GS_MetalFence,

  //Shadow Temple
  &ShadowTemple_GS_SingleGiantPot,
  &ShadowTemple_GS_FallingSpikesRoom,
  &ShadowTemple_GS_TripleGiantPot,
  &ShadowTemple_GS_LikeLikeRoom,
  &ShadowTemple_GS_NearShip,

  //Bottom of the Well
  &BottomOfTheWell_GS_LikeLikeCage,
  &BottomOfTheWell_GS_EastInnerRoom,
  &BottomOfTheWell_GS_WestInnerRoom,

  //Ice Cavern
  &IceCavern_GS_PushBlockRoom,
  &IceCavern_GS_SpinningScytheRoom,
  &IceCavern_GS_HeartPieceRoom,

  //Overworld
  &KF_GS_BeanPatch,
  &KF_GS_KnowItAllHouse,
  &KF_GS_HouseOfTwins,

  &LW_GS_BeanPatchNearBridge,
  &LW_GS_BeanPatchNearTheater,
  &LW_GS_AboveTheater,
  &SFM_GS,

  &HF_GS_CowGrotto,
  &HF_GS_NearKakGrotto,

  &LH_GS_BeanPatch,
  &LH_GS_SmallIsland,
  &LH_GS_LabWall,
  &LH_GS_LabCrate,
  &LH_GS_Tree,

  &GV_GS_BeanPatch,
  &GV_GS_SmallBridge,
  &GV_GS_Pillar,
  &GV_GS_BehindTent,

  &GF_GS_ArcheryRange,
  &GF_GS_TopFloor,

  &HW_GS,
  &Colossus_GS_BeanPatch,
  &Colossus_GS_Hill,
  &Colossus_GS_Tree,

  &OGC_GS,
  &HC_GS_StormsGrotto,
  &HC_GS_Tree,
  &MK_GS_GuardHouse,

  &Kak_GS_HouseUnderConstruction,
  &Kak_GS_SkulltulaHouse,
  &Kak_GS_GuardsHouse,
  &Kak_GS_Tree,
  &Kak_GS_Watchtower,
  &Kak_GS_AboveImpasHouse,

  &DMC_GS_BeanPatch,
  &DMC_GS_Crate,

  &DMT_GS_BeanPatch,
  &DMT_GS_NearKak,
  &DMT_GS_AboveDodongosCavern,
  &DMT_GS_FallingRocksPath,

  &GC_GS_CenterPlatform,
  &GC_GS_BoulderMaze,
  &GY_GS_Wall,
  &GY_GS_BeanPatch,

  &ZR_GS_Ladder,
  &ZR_GS_Tree,
  &ZR_GS_AboveBridge,
  &ZR_GS_NearRaisedGrottos,

  &ZD_GS_FrozenWaterfall,
  &ZF_GS_AboveTheLog,
  &ZF_GS_HiddenCave,
  &ZF_GS_Tree,

  &LLR_GS_BackWall,
  &LLR_GS_RainShed,
  &LLR_GS_HouseWindow,
  &LLR_GS_Tree,
};

void SpoilerLog_SaveLocation(const char *loc, const char *item) {
  logtxt += loc;
  logtxt += ": ";

  //formatting for spoiler log (there's probably an easier way to do this)
  u8 remainingSpaces = LONGEST_LINE - (strlen(loc));
  for (u8 i = 0; i < remainingSpaces; i++) {
    logtxt += " ";
  }

  logtxt += item;
  logtxt += "\n";
}

bool SpoilerLog_Write() {
  for (auto loc = allLocations.begin(); loc != allLocations.end(); loc++) {
    SpoilerLog_SaveLocation((*loc)->getName(), (*loc)->placedItem.getName());
  }

  //Open SD archive
  if (!R_SUCCEEDED(res = FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) return false;
  //Open spoilerlog.txt
  if (!R_SUCCEEDED(res = FSUSER_OpenFile(&spoilerlog, sdmcArchive, fsMakePath(PATH_ASCII, "/3ds/spoilerlog.txt"), FS_OPEN_WRITE | FS_OPEN_CREATE, 0))) return false;
  //write to spoilerlog.txt
  if (!R_SUCCEEDED(res = FSFILE_Write(spoilerlog, &bytesWritten, totalRW, logtxt.c_str(), strlen(logtxt.c_str()), FS_WRITE_FLUSH))) return false;
  return true;
}

void PlacementLog_Msg(const char *msg) {
  placementtxt += msg;
}

bool PlacementLog_Write() {
  //Open SD archive
  if (!R_SUCCEEDED(res = FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) return false;
  //Open placementlog.txt
  if (!R_SUCCEEDED(res = FSUSER_OpenFile(&placementlog, sdmcArchive, fsMakePath(PATH_ASCII, "/3ds/placementlog.txt"), FS_OPEN_WRITE | FS_OPEN_CREATE, 0))) return false;
  //write to placementlog.txt
  if (!R_SUCCEEDED(res = FSFILE_Write(placementlog, &bytesWritten, totalRW, placementtxt.c_str(), strlen(placementtxt.c_str()), FS_WRITE_FLUSH))) return false;
  return true;
}
