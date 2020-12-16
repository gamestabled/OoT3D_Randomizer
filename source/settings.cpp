#include "settings.hpp"
#include "random.hpp"

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
  u8 GanonsBossKey                      = 0;     Option O_GanonsBossKey       = Option(&GanonsBossKey,       "Ganon's Boss Key",       {"Vanilla", "Dungeon Only", "All Locations", "LACS: Vanilla", "LACS: Medallions", "LACS: Stones", "LACS: Dungeons"});
  u8 MapsAndCompasses                   = 0;     Option O_MapsAndCompasses    = Option(&MapsAndCompasses,    "Maps/Compasses",         {"Start With", "Vanilla", "Dungeon Only", "All Locations"}, 1);
  u8 Skullsanity                        = 0;     Option O_Skullsanity         = Option(&Skullsanity,         "Tokensanity",            {"Vanilla",                 "All Locations"});
  u8 Scrubsanity                        = 0;     Option O_Scrubsanity         = Option(&Scrubsanity,         "Scrub Shuffle",          {"Off", "Affordable", "Expensive", "Random Prices"});
  u8 BigPoeTargetCount                  = 0;     Option O_BigPoeTargetCount   = Option(&BigPoeTargetCount,   "Big Poe Target Count",   {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"});
  u8 ItemPoolValue                      = 0;     Option O_ItemPoolValue       = Option(&ItemPoolValue,       "Item Pool",              {"Plentiful", "Balanced", "Scarce", "Minimal"}, 1);
  u8 BoomerangAsAdult                   = 0;     Option O_BoomerangAsAdult    = Option(&BoomerangAsAdult,    "Enable Adult Boomerang", {"No", "Yes"});
  u8 HammerAsChild                      = 0;     Option O_HammerAsChild       = Option(&HammerAsChild,       "Enable Child Hammer",    {"No", "Yes"});
  u8 LACSCondition                      = 0;
  u8 SkipChildStealth                   = 0;     Option O_SkipChildStealth    = Option(&SkipChildStealth,    "Skip Child Sealth",      {"Don't Skip", "Skip"});

  std::string seed                      = "";

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
  bool ShuffleMagicBeans                = false; Option O_ShuffleMagicBeans   = Option(&ShuffleMagicBeans,   "Shuffle Magic Beans",    {"Off", "On"});
  bool ShuffleOcarinas                  = false; Option O_ShuffleOcarinas     = Option(&ShuffleOcarinas,     "Shuffle Ocarinas",       {"Off", "On"});
  bool ShuffleSongs                     = false;
  bool Shopsanity                       = false;
  bool FourPoesCutscene                 = false; Option O_FourPoesCutscene    = Option(&FourPoesCutscene,    "Four Poes Cutscene",   {"Skip Cutscene", "Don't Skip"});
  bool RandomMQDungeons                 = false; Option O_RandomMQDungeons    = Option(&RandomMQDungeons,    "Random MQ Dungeons",   {"Off", "On"});
  bool DekuTreeDungeonMode              = false;
  bool DodongosCavernDungeonMode        = false;
  bool JabuJabusBellyDungeonMode        = false;
  bool ForestTempleDungeonMode          = false;
  bool FireTempleDungeonMode            = false;
  bool WaterTempleDungeonMode           = false;
  bool SpiritTempleDungeonMode          = false;
  bool ShadowTempleDungeonMode          = false;
  bool BottomOfTheWellDungeonMode       = false;
  bool GerudoTrainingGroundsDungeonMode = false;
  bool GanonsCastleDungeonMode          = false;

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
  bool LogicJabuScrubJumpDive           = false;
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

  u32 LinksPocketRewardBitMask = 0;
  std::array<u32, 9> rDungeonRewardOverrides{};

  std::vector<Option *> Options = {
    //&O_TimeOfDay,
  };

  std::vector<Option *> variousOptions = {
    &O_DamageMultiplier,
    &O_Logic,
    &O_OpenForest,
    //&O_OpenKakariko,
    &O_DoorOfTime,
    &O_ZorasFountain,
    //&O_GerudoFortress,
    &O_Bridge,
    &O_BombchusInLogic,
    &O_SkipChildStealth,
  };
  std::vector<Option *> worldOptions = {
    &O_StartingAge,
    //&O_RandomMQDungeons,
  };
  std::vector<Option *> shuffleOptions = {
    &O_Skullsanity,
    &O_Scrubsanity,
    &O_ShuffleWeirdEgg,
    &O_ShuffleGerudoToken,
    &O_ShuffleKokiriSword,
    &O_ShuffleMagicBeans,
    &O_ShuffleOcarinas,
  };
  std::vector<Option *> shuffleDungeonItemOptions = {
    &O_Keysanity,
    &O_BossKeysanity,
    &O_GanonsBossKey,
    &O_MapsAndCompasses,
  };
  std::vector<Option *> timesaverOptions = {
    &O_BigPoeTargetCount,
    &O_FourPoesCutscene,
  };
  std::vector<Option *> advancedGlitchedOptions = {
    &O_BoomerangAsAdult,
    &O_HammerAsChild,
  };

  Menu various             = Menu("Various Settings",      variousOptions);
  Menu world               = Menu("World Settings",        worldOptions);
  Menu shuffle             = Menu("Shuffle Settings",      shuffleOptions);
  Menu shuffleDungeonItems = Menu("Shuffle Dungeon Items", shuffleDungeonItemOptions);
  Menu timesaverSettings   = Menu("Timesaver Settings",    timesaverOptions);
  Menu advancedGlitchedSettings = Menu("Advanced Glitched Settings", advancedGlitchedOptions);

  //adding a menu with no options crashes, might fix later
  std::vector<Menu *> mainMenu = {
    &various,
    &world,
    &shuffle,
    &shuffleDungeonItems,
    &timesaverSettings,
    &advancedGlitchedSettings,
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
    ctx.skipChildStealth = SkipChildStealth;

    ctx.openDoorOfTime      = (OpenDoorOfTime)    ? 1 : 0;
    ctx.shuffleBeanSalesman = (ShuffleMagicBeans) ? 1 : 0;
    ctx.shuffleOcarinas     = (ShuffleOcarinas)   ? 1 : 0;
    ctx.fourPoesCutscene    = (FourPoesCutscene)  ? 1 : 0;

    ctx.bigPoeTargetCount = BigPoeTargetCount + 1;
    
    ctx.boomerangAsAdult = BoomerangAsAdult;
    ctx.hammerAsChild    = HammerAsChild;

    ctx.dekuTreeDungeonMode              = (DekuTreeDungeonMode)              ? 1 : 0;
    ctx.dodongosCavernDungeonMode        = (DodongosCavernDungeonMode)        ? 1 : 0;
    ctx.jabuJabusBellyDungeonMode        = (JabuJabusBellyDungeonMode)        ? 1 : 0;
    ctx.forestTempleDungeonMode          = (ForestTempleDungeonMode)          ? 1 : 0;
    ctx.fireTempleDungeonMode            = (FireTempleDungeonMode)            ? 1 : 0;
    ctx.waterTempleDungeonMode           = (WaterTempleDungeonMode)           ? 1 : 0;
    ctx.spiritTempleDungeonMode          = (SpiritTempleDungeonMode)          ? 1 : 0;
    ctx.shadowTempleDungeonMode          = (ShadowTempleDungeonMode)          ? 1 : 0;
    ctx.bottomOfTheWellDungeonMode       = (BottomOfTheWellDungeonMode)       ? 1 : 0;
    ctx.gerudoTrainingGroundsDungeonMode = (GerudoTrainingGroundsDungeonMode) ? 1 : 0;
    ctx.ganonsCastleDungeonMode          = (GanonsCastleDungeonMode)          ? 1 : 0;

    ctx.dungeonRewardBitMask = LinksPocketRewardBitMask;
    return ctx;
  }

  //Function to set flags depending on settings
  void UpdateSettings() {
    LogicGrottosWithoutAgony = true;
    LogicFewerTunicRequirements = true;
    LogicBiggoronBolero = true;
    LogicManOnRoof = true;
    LogicDekuB1Skip = true;

    if (RandomMQDungeons) {
      DekuTreeDungeonMode              = Random() % 2;
      DodongosCavernDungeonMode        = Random() % 2;
      JabuJabusBellyDungeonMode        = Random() % 2;
      ForestTempleDungeonMode          = Random() % 2;
      FireTempleDungeonMode            = Random() % 2;
      WaterTempleDungeonMode           = Random() % 2;
      SpiritTempleDungeonMode          = Random() % 2;
      ShadowTempleDungeonMode          = Random() % 2;
      BottomOfTheWellDungeonMode       = Random() % 2;
      GerudoTrainingGroundsDungeonMode = Random() % 2;
      GanonsCastleDungeonMode          = Random() % 2;
    }

    if (TimeOfDay == STARTINGTIME_NIGHT)
      HasNightStart = true;

    if (GanonsBossKey == GANONSBOSSKEY_LACS_MEDALLIONS) {
      LACSCondition = LACSCONDITION_MEDALLIONS;
    } else if (GanonsBossKey == GANONSBOSSKEY_LACS_STONES) {
      LACSCondition = LACSCONDITION_STONES;
    } else if (GanonsBossKey == GANONSBOSSKEY_LACS_DUNGEONS) {
      LACSCondition = LACSCONDITION_DUNGEONS;
    } else {
      LACSCondition = LACSCONDITION_VANILLA;
    }

  }

  void PrintSettings() {

  }


}
