#include "settings.hpp"

namespace Settings {
                                                                                      //logic variable       setting name                 options
  u8 Logic                              = 0;     Option O_Logic               = Option(&Logic,               "Logic",                  {"Glitchless", "No Logic"});
  u8 OpenForest                         = 0;     Option O_OpenForest          = Option(&OpenForest,          "Forest",                 {"Open", "Closed"});
  u8 OpenKakariko                       = 0;     Option O_OpenKakariko        = Option(&OpenKakariko,        "Kakariko Gate",          {"Open", "Closed"}, 1);
  u8 Bridge                             = 0;     Option O_Bridge              = Option(&Bridge,              "Rainbow Bridge",         {"Open", "Vanilla", "Stones", "Medallions", "Dungeons"}, 1);
  u8 GerudoFortress                     = 0;     Option O_GerudoFortress      = Option(&GerudoFortress,      "Gerudo Fortress",        {"Normal", "Fast", "Open"});
  u8 DamageMultiplier                   = 0;     Option O_DamageMultiplier    = Option(&DamageMultiplier,    "Damage Multiplier",      {"Half", "Default", "Double", "Quadruple", "OHKO"}, 1);
  u8 ZorasFountain                      = 0;     Option O_ZorasFountain       = Option(&ZorasFountain,       "Zora's Fountain",        {"Normal", "Open"});
  u8 StartingAge                        = 0;     Option O_StartingAge         = Option(&StartingAge,         "Starting Age",           {"Adult", "Child"}, 1);
  u8 TimeOfDay                          = 0;     Option O_TimeOfDay           = Option(&TimeOfDay,           "Starting Time",          {"Day", "Night"});
  u8 Keysanity                          = 0;     Option O_Keysanity           = Option(&Keysanity,           "Small Keys",             {"Vanilla", "Dungeon Only", "All Locations"});
  u8 BossKeysanity                      = 0;     Option O_BossKeysanity       = Option(&BossKeysanity,       "Boss Keys",              {"Vanilla", "Dungeon Only", "All Locations"});
  u8 MapsAndCompasses                   = 0;     Option O_MapsAndCompasses    = Option(&MapsAndCompasses,    "Maps/Compasses",         {"Vanilla", "Dungeon Only", "All Locations"});
  u8 Skullsanity                        = 0;     Option O_Skullsanity         = Option(&Skullsanity,         "Tokensanity",            {"Vanilla",                 "All Locations"});
  u8 Scrubsanity                        = 0;     Option O_Scrubsanity         = Option(&Scrubsanity,         "Scrub Shuffle",          {"Off", "Affordable", "Expensive", "Random Prices"});
  u8 LACSCondition                      = 0;

  unsigned int seed                     = 0;

  bool HasNightStart                    = false;
  bool BombchusInLogic                  = false; Option O_BombchusInLogic     = Option(&BombchusInLogic,     "Bombchus in Logic",      {"Off", "On"});
  bool BombchuDrop                      = false;
  bool OpenDoorOfTime                   = false; Option O_DoorOfTime          = Option(&OpenDoorOfTime,      "Door of Time",           {"Closed", "Open"}, 1);
  bool SkippedTrials                    = false;
  bool ShuffleDungeonEntrances          = false;
  bool ShuffleOverworldEntrances        = false;
  bool ShuffleInteriorEntrances         = false;
  bool ShuffleSpecialIndoorEntrances    = false;
  bool ShuffleWeirdEgg                  = false; Option O_ShuffleWeirdEgg     = Option(&ShuffleWeirdEgg,     "Shuffle Weird Egg",      {"Off", "On"});
  bool ShuffleGerudoToken               = false; Option O_ShuffleGerudoToken  = Option(&ShuffleGerudoToken,  "Shuffle Gerudo Token",   {"Off", "On"});
  bool ShuffleKokiriSword               = false; Option O_ShuffleKokiriSword  = Option(&ShuffleKokiriSword,  "Shuffle Kokiri Sword",   {"Off", "On"});
  bool ShuffleSongs                     = false;
  bool Shopsanity                       = false;

  //Individual Options
  bool LogicGrottosWithoutAgony         = false;
  bool LogicVisibleCollision            = false;
  bool LogicFewerTunicRequirements      = false;
  bool LogicLostWoodsBridge             = false;
  bool LogicLostWoodsGSBean             = false;
  bool LogicLabDiving                   = false;
  bool LogicLabWallGS                   = false;
  bool LogicGraveyardPoH                = false;
  bool LogicChildDampeRacePoH           = false;
  bool LogicGerudoKitchen               = false;
  bool LogicLensWasteland               = false;
  bool LogicReverseWasteland            = false;
  bool LogicColossusGS                  = false;
  bool LogicManOnRoof                   = false;
  bool LogicKakarikoTowerGS             = false;
  bool LogicDMTBombable                 = false;
  bool LogicDMTSoilGS                   = false;
  bool LogicLinkGoronDins               = false;
  bool LogicGoronCityLeftMost           = false;
  bool LogicGoronCityPot                = false;
  bool LogicGoronCityPotWithStrength    = false;
  bool LogicChildRollingWithStrength    = false;
  bool LogicCraterUpperToLower          = false;
  bool LogicCraterBeanPoHWithHovers     = false;
  bool LogicBiggoronBolero              = false;
  bool LogicZoraWithHovers              = false;
  bool LogicZoraWithCucco               = false;
  bool LogicZoraRiverLower              = false;
  bool LogicZoraRiverUpper              = false;

  bool LogicDekuB1WebsWithBow           = false;
  bool LogicDekuB1Skip                  = false;
  bool LogicDekuBasementGS              = false;
  bool LogicDCStaircase                 = false;
  bool LogicDCJump                      = false;
  bool LogicDCSlingshotSkip             = false;
  bool LogicDCScarecrowGS               = false;
  bool LogicJabuBossGSAdult             = false;
  bool LogicForestOutsideBackdoor       = false;
  bool LogicForestScarecrow             = false;
  bool LogicForestVines                 = false;
  bool LogicForestOutdoorEastGS         = false;
  bool LogicFireBossDoorJump            = false;
  bool LogicFireStrength                = false;
  bool LogicFireScarecrow               = false;
  bool LogicFireFlameMaze               = false;
  bool LogicFireSongOfTime              = false;
  bool LogicWaterHookshotEntry          = false;
  bool LogicWaterTempleTorchLongshot    = false;
  bool LogicWaterCentralBow             = false;
  bool LogicWaterCrackedWallNothing     = false;
  bool LogicWaterCrackedWallHovers      = false;
  bool LogicWaterBossKeyRegion          = false;
  bool LogicWaterDragonBombchu          = false;
  bool LogicWaterBKJumpDive             = false;
  bool LogicWaterNorthBasementLedgeJump = false;
  bool LogicWaterBKChest                = false;
  bool LogicWaterDragonJumpDive         = false;
  bool LogicWaterRiverGS                = false;
  bool LogicWaterFallingPlatformGS      = false;
  bool LogicSpiritLowerAdultSwitch      = false;
  bool LogicSpiritChildBombchu          = false;
  bool LogicSpiritWall                  = false;
  bool LogicSpiritLobbyGS               = false;
  bool LogicSpiritMapChest              = false;
  bool LogicSpiritSunChest              = false;
  bool LogicShadowFireArrowEntry        = false;
  bool LogicShadowUmbrella              = false;
  bool LogicShadowFreestandingKey       = false;
  bool LogicShadowStatue                = false;
  bool LogicBotwCageGS                  = false;
  bool LogicChildDeadhand               = false;
  bool LogicGtgWithoutHookshot          = false;
  bool LogicGtgFakeWall                 = false;
  bool LogicLensSpirit                  = false;
  bool LogicLensShadow                  = false;
  bool LogicLensShadowBack              = false;
  bool LogicLensBotw                    = false;
  bool LogicLensGtg                     = false;
  bool LogicLensCastle                  = false;
  bool LogicSpiritTrialHookshot         = false;

  std::vector<Option *> Options = {
    //&O_DamageMultiplier,
    //&O_TimeOfDay,
  };

  std::vector<Option *> variousOptions = {
    &O_Logic,
    //&O_OpenForest,
    //&O_OpenKakariko,
    &O_DoorOfTime,
    //&O_ZorasFountain,
    //&O_GerudoFortress,
    &O_Bridge,
    &O_BombchusInLogic,
  };
  std::vector<Option *> worldOptions = {
    &O_StartingAge,
  };
  std::vector<Option *> shuffleOptions = {
    &O_Skullsanity,
    //&O_Scrubsanity,
    &O_ShuffleWeirdEgg,
    &O_ShuffleGerudoToken,
    &O_ShuffleKokiriSword,
  };
  std::vector<Option *> shuffleDungeonItemOptions = {
    &O_Keysanity,
    &O_BossKeysanity,
    &O_MapsAndCompasses,
  };

  Menu various             = Menu("Various Settings",      variousOptions);
  Menu world               = Menu("World Settings",        worldOptions);
  Menu shuffle             = Menu("Shuffle Settings",      shuffleOptions);
  Menu shuffleDungeonItems = Menu("Shuffle Dungeon Items", shuffleDungeonItemOptions);

  //adding a menu with no options crashes, will fix later
  std::vector<Menu *> mainMenu = {
    &various,
    &world,
    &shuffle,
    &shuffleDungeonItems,
  };

  SettingsContext FillContext() {
    SettingsContext ctx = {};
    ctx.openForest       = OpenForest;
    ctx.openKakariko     = OpenKakariko;
    ctx.rainbowBridge    = Bridge;
    ctx.gerudoFortress   = GerudoFortress;
    ctx.damageMultiplier = DamageMultiplier;
    ctx.zorasFountain    = ZorasFountain;
    ctx.startingAge      = StartingAge;
    ctx.timeOfDay        = TimeOfDay;
    ctx.scrubsanity      = Scrubsanity;
    ctx.lacsCondition    = LACSCondition;

    ctx.openDoorOfTime = (OpenDoorOfTime) ? 1 : 0;

    ctx.dungeonRewardBitMask = 0x00000020; //light medallion
    return ctx;
  }

  //Function to set flags depending on settings
  void UpdateSettings() {
    LogicGrottosWithoutAgony = true;
    LogicFewerTunicRequirements = true;
    LogicBiggoronBolero = true;
    LogicManOnRoof = true;
    LogicDekuB1Skip = true;

    if (TimeOfDay == STARTINGTIME_NIGHT)
      HasNightStart = true;

    LACSCondition = LACSCONDITION_MEDALLIONS;

  }

  void PrintSettings() {

  }


}
