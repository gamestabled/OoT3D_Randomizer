#include "settings.hpp"

namespace Settings {
  std::string Logic             = ""; Option O_Logic            = Option(&Logic,             "Logic",             {"Glitchless", "No Logic"});
  std::string OpenForest        = ""; Option O_OpenForest       = Option(&OpenForest,        "Forest",            {"Open", "Closed"});
  std::string OpenKakariko      = ""; Option O_OpenKakariko     = Option(&OpenKakariko,      "Kakariko Gate",     {"Open", "Closed"});
  std::string OpenDoorOfTimeStr = ""; Option O_DoorOfTime       = Option(&OpenDoorOfTimeStr, "Door of Time",      {"Open", "Closed"});
  std::string Bridge            = ""; Option O_Bridge           = Option(&Bridge,            "Rainbow Bridge",    {"Open", "Vanilla", "Stones", "Medallions", "Dungeons"});
  std::string GerudoFortress    = ""; Option O_GerudoFortress   = Option(&GerudoFortress,    "Gerudo Fortress",   {"Default", "Open"});
  std::string DamageMultiplier  = ""; Option O_DamageMultiplier = Option(&DamageMultiplier,  "Damage Multiplier", {"Default", "Double", "Quadruple", "OHKO", "Half"});
  std::string ZorasFountain     = ""; Option O_ZorasFountain    = Option(&ZorasFountain,     "Zora's Fountain",   {"Default", "Open"});
  std::string StartingAge       = ""; Option O_StartingAge      = Option(&StartingAge,       "Starting Age",      {"Child", "Adult"});
  std::string TimeOfDay         = ""; Option O_TimeOfDay        = Option(&TimeOfDay,         "Starting Time",     {"Day", "Night"});
  std::string Keysanity         = ""; Option O_Keysanity        = Option(&Keysanity,         "Small Keys",        {"Vanilla", "Dungeon Only", "All Locations"});
  std::string BossKeysanity     = ""; Option O_BossKeysanity    = Option(&BossKeysanity,     "Boss Keys",         {"Vanilla", "Dungeon Only", "All Locations"});
  std::string MapsAndCompasses  = ""; Option O_MapsAndCompasses = Option(&MapsAndCompasses,  "Maps/Compasses",    {"Vanilla", "Dungeon Only", "All Locations"});
  std::string Skullsanity       = ""; Option O_Skullsanity      = Option(&Skullsanity,       "Tokensanity",       {"Vanilla",                 "All Locations"});
  std::string Scrubsanity       = ""; Option O_Scrubsanity      = Option(&Scrubsanity,       "Scrub Shuffle",     {"Off", "Affordable", "Expensive", "Random Prices"});
  std::string BombchusLogicStr  = ""; Option O_BombchusInLogic  = Option(&BombchusLogicStr,  "Bombchus in Logic", {"Off", "On"});
  std::string LACSCondition     = "";

  bool HasNightStart                 = false;
  bool BombchusInLogic               = false;
  bool BombchuDrop                   = false;
  bool OpenDoorOfTime                = false;
  bool SkippedTrials                 = false;
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
    LogicDekuB1Skip = true;

    if (OpenDoorOfTimeStr == "Open")  OpenDoorOfTime  = true;
    if (BombchusLogicStr  == "On")    BombchusInLogic = true;
    if (TimeOfDay         == "Night") HasNightStart   = true;



    // OpenForest = "Closed";
    // Bridge = "Medallions";
    LACSCondition = "Medallions";
    //DamageMultiplier = "1x";
    //StartingAge = "Child";
    // Keysanity = "Dungeon Only";
    // BossKeysanity = "Dungeon Only";
    // Skullsanity = "Vanilla";
    // MapsAndCompasses = "Dungeon Only";
    //GerudoFortress = "Normal";
  }

  std::vector<Option *> Options = {
    &O_Logic,
    &O_OpenForest,
    &O_OpenKakariko,
    &O_DoorOfTime,
    &O_Bridge,
    &O_GerudoFortress,
    &O_DamageMultiplier,
    &O_ZorasFountain,
    &O_StartingAge,
    &O_TimeOfDay,
    &O_Keysanity,
    &O_BossKeysanity,
    &O_MapsAndCompasses,
    &O_Skullsanity,
    &O_Scrubsanity,
    &O_BombchusInLogic,
  };

  std::vector<Option *> variousOptions = {
    &O_OpenForest,
    &O_OpenKakariko,
    &O_DoorOfTime,
    &O_ZorasFountain,
    &O_GerudoFortress,
    &O_Bridge,
    &O_BombchusInLogic,
  }

  Menu various = Menu("Various", variousOptions);

  std::vector<Menu> mainMenu = {
    various,
  }
}
