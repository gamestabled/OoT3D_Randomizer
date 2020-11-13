#include "settings.hpp"
#include <string>

namespace Settings {

  bool HasNightStart         = false;
  bool BombchusInLogic       = false;
  bool BombchuDrop           = false;
  bool OpenDoorOfTime        = false;
  bool SkippedTrials         = false;
  std::string OpenForest       = "";
  std::string OpenKakariko     = "";
  std::string Bridge           = "";
  std::string LACSCondition    = "";
  std::string GerudoFortress   = "";
  std::string DamageMultiplier = "";
  std::string ZorasFountain    = "";
  std::string StartingAge      = "";
  std::string TimeOfDay        = "";
  std::string Keysanity        = "";
  std::string BossKeysanity    = "";
  std::string MapsAndCompasses = "";
  std::string Skullsanity      = "";
  std::string Scrubsanity      = "";
  bool ShuffleDungeonEntrances       = false;
  bool ShuffleOverworldEntrances     = false;
  bool ShuffleInteriorEntrances      = false;
  bool ShuffleSpecialIndoorEntrances = false;
  bool ShuffleWeirdEgg               = false;
  bool ShuffleGerudoToken            = false;
  bool ShuffleZeldasLetter           = false;
  bool ShuffleKokiriSword            = false;
  bool ShuffleSongs                  = false;
  bool Shopsanity                    = false;

  //Individual Options
  bool LogicGrottosWithoutAgony      = false;
  bool LogicVisibleCollision         = false;
  bool LogicFewerTunicRequirements   = false;

  bool LogicLostWoodsBridge          = false;
  bool LogicLostWoodsGSBean          = false;
  bool LogicLabDiving                = false;
  bool LogicLabWallGS                = false;
  bool LogicGraveyardPoH             = false;
  bool LogicChildDampeRacePoH        = false;
  bool LogicGerudoKitchen            = false;
  bool LogicLensWasteland            = false;
  bool LogicReverseWasteland         = false;
  bool LogicColossusGS               = false;
  bool LogicManOnRoof                = false;
  bool LogicKakarikoTowerGS          = false;
  bool LogicDMTBombable              = false;
  bool LogicDMTSoilGS                = false;
  bool LogicLinkGoronDins            = false;
  bool LogicGoronCityLeftMost        = false;
  bool LogicGoronCityPot             = false;
  bool LogicGoronCityPotWithStrength = false;
  bool LogicChildRollingWithStrength = false;
  bool LogicCraterUpperToLower       = false;
  bool LogicCraterBeanPoHWithHovers  = false;
  bool LogicBiggoronBolero           = false;
  bool LogicZoraWithHovers           = false;
  bool LogicZoraWithCucco            = false;
  bool LogicZoraRiverLower           = false;
  bool LogicZoraRiverUpper           = false;

  bool LogicDekuB1WebsWithBow        = false;
  bool LogicDekuB1Skip               = false;
  bool LogicDekuBasementGS           = false;
  bool LogicDCStaircase              = false;
  bool LogicDCJump                   = false;
  bool LogicDCSlingshotSkip          = false;
  bool LogicDCScarecrowGS            = false;
  bool LogicJabuBossGSAdult          = false;
  bool LogicForestOutsideBackdoor    = false;
  bool LogicForestScarecrow          = false;
  bool LogicForestVines              = false;
  bool LogicForestOutdoorEastGS      = false;
  bool LogicFireBossDoorJump         = false;
  bool LogicFireStrength             = false;
  bool LogicFireScarecrow            = false;
  bool LogicFireFlameMaze            = false;
  bool LogicFireSongOfTime           = false;
  bool LogicWaterHookshotEntry       = false;
  bool LogicWaterTempleTorchLongshot = false;
  bool LogicWaterCentralBow          = false;
  bool LogicWaterCrackedWallNothing  = false;
  bool LogicWaterCrackedWallHovers   = false;
  bool LogicWaterBossKeyRegion       = false;
  bool LogicWaterDragonBombchu       = false;
  bool LogicWaterBKJumpDive          = false;
  bool LogicWaterNorthBasementLedgeJump = false;
  bool LogicWaterBKChest             = false;
  bool LogicWaterDragonJumpDive      = false;
  bool LogicWaterRiverGS             = false;
  bool LogicWaterFallingPlatformGS   = false;
  bool LogicSpiritLowerAdultSwitch   = false;
  bool LogicSpiritChildBombchu       = false;
  bool LogicSpiritWall               = false;
  bool LogicSpiritLobbyGS            = false;
  bool LogicSpiritMapChest           = false;
  bool LogicSpiritSunChest           = false;
  bool LogicShadowFireArrowEntry     = false;
  bool LogicShadowUmbrella           = false;
  bool LogicShadowFreestandingKey    = false;
  bool LogicShadowStatue             = false;
  bool LogicBotwCageGS               = false;
  bool LogicChildDeadhand            = false;
  bool LogicGtgWithoutHookshot       = false;
  bool LogicGtgFakeWall              = false;
  bool LogicLensSpirit               = false;
  bool LogicLensShadow               = false;
  bool LogicLensShadowBack           = false;
  bool LogicLensBotw                 = false;
  bool LogicLensGtg                  = false;
  bool LogicLensCastle               = false;
  bool LogicSpiritTrialHookshot      = false;

  //Function to set flags depending on settings
  void UpdateSettings() {
    LogicGrottosWithoutAgony = true;
    LogicFewerTunicRequirements = true;
    LogicBiggoronBolero = true;
    LogicManOnRoof = true;
    BombchusInLogic = true;
    LogicDekuB1Skip = true;
    OpenDoorOfTime = true;

    OpenForest = "Closed";
    Bridge = "Medallions";
    LACSCondition = "Medallions";
    DamageMultiplier = "1x";
    StartingAge = "Child";
    Keysanity = "Dungeon Only";
    BossKeysanity = "Dungeon Only";
    Skullsanity = "Vanilla";
    MapsAndCompasses = "Dungeon Only";
    GerudoFortress = "Normal";
  }
}
