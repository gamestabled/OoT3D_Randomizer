#include "settings.hpp"
#include "random.hpp"

namespace Settings {
  std::string seed;

  //                                        Setting name               Options
  //Open Settings
  Option Logic               = Option::U8  ("Logic",                  {"Glitchless", "No Logic"});
  Option OpenForest          = Option::U8  ("Forest",                 {"Open", "Closed"});
  Option OpenKakariko        = Option::U8  ("Kakariko Gate",          {"Open", "Closed"}, 1);
  Option OpenDoorOfTime      = Option::Bool("Door of Time",           {"Closed", "Open"}, true);
  Option ZorasFountain       = Option::U8  ("Zora's Fountain",        {"Normal", "Open"});
  Option GerudoFortress      = Option::U8  ("Gerudo Fortress",        {"Normal", "Fast", "Open"});
  Option Bridge              = Option::U8  ("Rainbow Bridge",         {"Open", "Vanilla", "Stones", "Medallions", "Dungeons"}, 1);
  std::vector<Option *> openOptions = {
    &Logic,
    &OpenForest,
    //&OpenKakariko,
    &OpenDoorOfTime,
    &ZorasFountain,
    &GerudoFortress,
    &Bridge,
  };

  //World Settings
  Option StartingAge         = Option::U8  ("Starting Age",           {"Adult", "Child"}, 1);
  Option BombchusInLogic     = Option::Bool("Bombchus in Logic",      {"Off", "On"});
  Option RandomMQDungeons    = Option::Bool("Random MQ Dungeons",     {"Off", "On"});
  std::vector<Option *> worldOptions = {
    &StartingAge,
    &BombchusInLogic,
    //&RandomMQDungeons,
  };

  //Shuffle Settings
  Option Skullsanity         = Option::U8  ("Tokensanity",            {"Vanilla", "All Locations"});
  Option Scrubsanity         = Option::U8  ("Scrub Shuffle",          {"Off", "Affordable", "Expensive", "Random Prices"});
  Option ShuffleKokiriSword  = Option::Bool("Shuffle Kokiri Sword",   {"Off", "On"});
  Option ShuffleOcarinas     = Option::Bool("Shuffle Ocarinas",       {"Off", "On"});
  Option ShuffleWeirdEgg     = Option::Bool("Shuffle Weird Egg",      {"Off", "On"});
  Option ShuffleGerudoToken  = Option::Bool("Shuffle Gerudo Token",   {"Off", "On"});
  Option ShuffleMagicBeans   = Option::Bool("Shuffle Magic Beans",    {"Off", "On"});
  //TODO: Medigoron and Carpet Salesman
  std::vector<Option *> shuffleOptions = {
    &Skullsanity,
    &Scrubsanity,
    &ShuffleKokiriSword,
    &ShuffleOcarinas,
    &ShuffleWeirdEgg,
    &ShuffleGerudoToken,
    &ShuffleMagicBeans,
    //TODO: Medigoron and Carpet Salesman
  };

  //Shuffle Dungeon Items
  Option Keysanity           = Option::U8  ("Small Keys",             {"Vanilla", "Own Dungeon", "All Locations"});
  Option BossKeysanity       = Option::U8  ("Boss Keys",              {"Vanilla", "Own Dungeon", "All Locations"});
  Option GanonsBossKey       = Option::U8  ("Ganon's Boss Key",       {"Vanilla", "Own Dungeon", "All Locations", "LACS: Vanilla", "LACS: Medallions", "LACS: Stones", "LACS: Dungeons"});
  Option MapsAndCompasses    = Option::U8  ("Maps/Compasses",         {"Start With", "Vanilla", "Own Dungeon", "All Locations"}, 1);
  u8 LACSCondition           = 0;
  std::vector<Option *> shuffleDungeonItemOptions = {
    &Keysanity,
    &BossKeysanity,
    &GanonsBossKey,
    &MapsAndCompasses,
  };

  //Timesaver Settings
  Option SkipChildStealth    = Option::U8  ("Skip Child Sealth",      {"Don't Skip", "Skip"});
  Option FourPoesCutscene    = Option::Bool("Four Poes Cutscene",     {"Skip Cutscene", "Don't Skip"});
  Option BigPoeTargetCount   = Option::U8  ("Big Poe Target Count",   {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"});
  std::vector<Option *> timesaverOptions = {
    &SkipChildStealth,
    &FourPoesCutscene,
    &BigPoeTargetCount,
  };

  //Misc Settings
  Option DamageMultiplier    = Option::U8  ("Damage Multiplier",      {"Half", "Default", "Double", "Quadruple", "OHKO"}, 1);
  Option StartingTime        = Option::U8  ("Starting Time",          {"Day", "Night"});
  bool HasNightStart         = false;
  std::vector<Option *> miscOptions = {
    &DamageMultiplier,
    &StartingTime,
  };

  //Advanced Glitch Settings
  Option BoomerangAsAdult    = Option::U8  ("Enable Adult Boomerang", {"No", "Yes"});
  Option HammerAsChild       = Option::U8  ("Enable Child Hammer",    {"No", "Yes"});
  std::vector<Option *> advancedGlitchedOptions = {
    &BoomerangAsAdult,
    &HammerAsChild,
  };

  //Item Pool Settings
  Option ItemPoolValue       = Option::U8  ("Item Pool",              {"Plentiful", "Balanced", "Scarce", "Minimal"}, 1);
  //TODO: Ice Traps

  //Excluded Locations (definitions made in ItemLocation class)
  std::vector<Option *> excludeLocationsOptions = {};

  Menu open                     = Menu("Open Settings",              &openOptions);
  Menu world                    = Menu("World Settings",             &worldOptions);
  Menu shuffle                  = Menu("Shuffle Settings",           &shuffleOptions);
  Menu shuffleDungeonItems      = Menu("Shuffle Dungeon Items",      &shuffleDungeonItemOptions);
  Menu excludeLocations         = Menu("Exclude Locations",          &excludeLocationsOptions);
  Menu timesaverSettings        = Menu("Timesaver Settings",         &timesaverOptions);
  Menu miscSettings             = Menu("Misc Settings",              &miscOptions);
  Menu advancedGlitchedSettings = Menu("Advanced Glitched Settings", &advancedGlitchedOptions);

  //adding a menu with no options crashes, might fix later
  std::vector<Menu *> mainMenu = {
    &open,
    &world,
    &shuffle,
    &shuffleDungeonItems,
    &timesaverSettings,
    &excludeLocations,
    &miscSettings,
    &advancedGlitchedSettings,
  };

  u32 LinksPocketRewardBitMask = 0;
  std::array<u32, 9> rDungeonRewardOverrides{};

  SettingsContext FillContext() {
    SettingsContext ctx = {};
    ctx.openForest       = OpenForest.Value<u8>();
    ctx.openKakariko     = OpenKakariko.Value<u8>();
    ctx.rainbowBridge    = Bridge.Value<u8>();
    ctx.gerudoFortress   = GerudoFortress.Value<u8>();
    ctx.damageMultiplier = DamageMultiplier.Value<u8>();
    ctx.zorasFountain    = ZorasFountain.Value<u8>();
    ctx.startingAge      = StartingAge.Value<u8>();
    ctx.startingTime     = StartingTime.Value<u8>();
    ctx.mapsAndCompasses = MapsAndCompasses.Value<u8>();
    ctx.scrubsanity      = Scrubsanity.Value<u8>();
    ctx.lacsCondition    = LACSCondition;
    ctx.skipChildStealth = SkipChildStealth.Value<u8>();
    ctx.bombchusInLogic  = BombchusInLogic.Value<bool>();

    ctx.openDoorOfTime      = (OpenDoorOfTime)    ? 1 : 0;
    ctx.shuffleBeanSalesman = (ShuffleMagicBeans) ? 1 : 0;
    ctx.shuffleOcarinas     = (ShuffleOcarinas)   ? 1 : 0;
    ctx.fourPoesCutscene    = (FourPoesCutscene)  ? 1 : 0;

    ctx.bigPoeTargetCount = BigPoeTargetCount.Value<u8>() + 1;

    ctx.boomerangAsAdult = BoomerangAsAdult.Value<u8>();
    ctx.hammerAsChild    = HammerAsChild.Value<u8>();

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

  bool BombchuDrop                      = false;
  bool SkippedTrials                    = false;
  bool ShuffleDungeonEntrances          = false;
  bool ShuffleOverworldEntrances        = false;
  bool ShuffleInteriorEntrances         = false;
  bool ShuffleSpecialIndoorEntrances    = false;
  bool ShuffleSongs                     = false;
  bool Shopsanity                       = false;
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

    if (StartingTime.Is(STARTINGTIME_NIGHT))
      HasNightStart = true;

    if (GanonsBossKey.Is(GANONSBOSSKEY_LACS_MEDALLIONS)) {
      LACSCondition = LACSCONDITION_MEDALLIONS;
    } else if (GanonsBossKey.Is(GANONSBOSSKEY_LACS_STONES)) {
      LACSCondition = LACSCONDITION_STONES;
    } else if (GanonsBossKey.Is(GANONSBOSSKEY_LACS_DUNGEONS)) {
      LACSCondition = LACSCONDITION_DUNGEONS;
    } else {
      LACSCondition = LACSCONDITION_VANILLA;
    }

  }
}
