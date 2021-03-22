#include <unistd.h>

#include "settings.hpp"
#include "setting_descriptions.hpp"
#include "item_location.hpp"
#include "random.hpp"
#include "fill.hpp"

namespace Settings {
  std::string seed;
  std::array<u8, 5> hashIconIndexes;

  //                                        Setting name,              Options,                                                Setting Descriptions (assigned in setting_descriptions.cpp)
  //Open Settings
  Option Logic               = Option::U8  ("Logic",                  {"Glitchless", "No Logic"},                              {logicGlitchless, logicNoLogic});
  Option OpenForest          = Option::U8  ("Forest",                 {"Closed", "Open"},                                      {forestClosed, forestOpen});
  Option OpenKakariko        = Option::U8  ("Kakariko Gate",          {"Closed", "Open"},                                      {kakGateClosed, kakGateOpen});
  Option OpenDoorOfTime      = Option::Bool("Door of Time",           {"Closed", "Open"},                                      {doorOfTimeDesc, doorOfTimeDesc});
  Option ZorasFountain       = Option::U8  ("Zora's Fountain",        {"Normal", "Adult", "Open"},                             {fountainNormal, fountainAdult, fountainOpen});
  Option GerudoFortress      = Option::U8  ("Gerudo Fortress",        {"Normal", "Fast", "Open"},                              {gerudoNormal, gerudoFast, gerudoOpen});
  Option Bridge              = Option::U8  ("Rainbow Bridge",         {"Open", "Vanilla", "Stones", "Medallions", "Dungeons", "Tokens"},
                                                                      {bridgeOpen, bridgeVanilla, bridgeStones, bridgeMedallions, bridgeDungeons, bridgeTokens});
  Option BridgeTokenCount    = Option::U8  ("  Token Count",          {/*Options 0-100 defined in SetDefaultOptions()*/},      std::vector<std::string_view>{101, bridgeTokenCountDesc});
  Option RandomGanonsTrials  = Option::Bool("Random Ganon's Trials",  {"Off", "On"},                                           {randomGanonsTrialsDesc, randomGanonsTrialsDesc});
  Option GanonsTrialsCount   = Option::U8  ("  Trial Count",          {"0", "1", "2", "3", "4", "5", "6"},                     std::vector<std::string_view>{7, ganonsTrialCountDesc});
  std::vector<Option *> openOptions = {
    &Logic,
    &OpenForest,
    //&OpenKakariko,
    &OpenDoorOfTime,
    &ZorasFountain,
    &GerudoFortress,
    &Bridge,
    &BridgeTokenCount,
    &RandomGanonsTrials,
    &GanonsTrialsCount,
  };

  //World Settings
  Option StartingAge         = Option::U8  ("Starting Age",           {"Adult", "Child"},                                      {ageDesc, ageDesc});
  Option BombchusInLogic     = Option::Bool("Bombchus in Logic",      {"Off", "On"},                                           {bombchuLogicDesc, bombchuLogicDesc});
  Option BombchuDrops        = Option::Bool("Bombchu Drops",          {"Off", "On"},                                           {bombchuDropDesc, bombchuDropDesc});
  Option RandomMQDungeons    = Option::Bool("Random MQ Dungeons",     {"Off", "On"},                                           {randomMQDungeonsDesc, randomMQDungeonsDesc});
  Option MQDungeonCount      = Option::U8  ("  MQ Dungeon Count",     {"0","1","2","3","4","5","6","7","8","9","10","11","12"},std::vector<std::string_view>{13, mqDungeonCountDesc});
  Option MirrorWorld         = Option::Bool("Mirror World",           {"Off", "On"},                                           {mirrorWorldDesc, mirrorWorldDesc});
  std::vector<Option *> worldOptions = {
    &StartingAge,
    &BombchusInLogic,
    &BombchuDrops,
    //&RandomMQDungeons, TODO: Finish MQ logic before enabling this
    &MirrorWorld,
  };

  //Shuffle Settings
  Option ShuffleSongs        = Option::U8  ("Shuffle Songs",          {"Song Locations", "Dungeon Rewards", "Anywhere"},       {songsSongLocations, songsDungeonRewards, songsAllLocations});
  Option Tokensanity         = Option::U8  ("Tokensanity",            {"Off", "Dungeons", "Overworld", "All Tokens"},          {tokensOff, tokensDungeon, tokensOverworld, tokensAllTokens});
  Option Scrubsanity         = Option::U8  ("Scrub Shuffle",          {"Off", "Affordable", "Expensive", "Random Prices"},     {scrubsOff, scrubsAffordable, scrubsExpensive, scrubsRandomPrices});
  Option ShuffleCows         = Option::Bool("Shuffle Cows",           {"Off", "On"},                                           {shuffleCowsDesc, shuffleCowsDesc});
  Option ShuffleKokiriSword  = Option::Bool("Shuffle Kokiri Sword",   {"Off", "On"},                                           {kokiriSwordDesc, kokiriSwordDesc});
  Option ShuffleOcarinas     = Option::Bool("Shuffle Ocarinas",       {"Off", "On"},                                           {ocarinasDesc, ocarinasDesc});
  Option ShuffleWeirdEgg     = Option::Bool("Shuffle Weird Egg",      {"Off", "On"},                                           {weirdEggDesc, weirdEggDesc});
  Option ShuffleGerudoToken  = Option::Bool("Shuffle Gerudo Token",   {"Off", "On"},                                           {gerudoTokenDesc, gerudoTokenDesc});
  Option ShuffleMagicBeans   = Option::Bool("Shuffle Magic Beans",    {"Off", "On"},                                           {magicBeansDesc, magicBeansDesc});
  //TODO: Medigoron and Carpet Salesman
  std::vector<Option *> shuffleOptions = {
    &ShuffleSongs,
    &Tokensanity,
    &Scrubsanity,
    &ShuffleCows,
    &ShuffleKokiriSword,
    &ShuffleOcarinas,
    &ShuffleWeirdEgg,
    &ShuffleGerudoToken,
    &ShuffleMagicBeans,
    //TODO: Medigoron and Carpet Salesman
  };

  //Shuffle Dungeon Items
  Option MapsAndCompasses    = Option::U8  ("Maps/Compasses",         {"Start With", "Vanilla", "Own Dungeon", "Anywhere"},    {mapCompassStartWith, mapCompassVanilla, mapCompassOwnDungeon, mapCompassAnywhere});
  Option Keysanity           = Option::U8  ("Small Keys",             {"Start With", "Vanilla", "Own Dungeon", "Anywhere"},    {smallKeyStartWith, smallKeyVanilla, smallKeyOwnDungeon, smallKeyAnywhere});
  Option GerudoKeys          = Option::U8  ("Gerudo Fortress Keys",   {"Vanilla", "Anywhere"},                                 {gerudoKeysVanilla, gerudoKeysAnywhere});
  Option BossKeysanity       = Option::U8  ("Boss Keys",              {"Start With", "Vanilla", "Own Dungeon", "Anywhere"},    {bossKeyStartWith, bossKeyVanilla, bossKeyOwnDungeon, bossKeyAnywhere});
  Option GanonsBossKey       = Option::U8  ("Ganon's Boss Key",       {"Start With", "Vanilla", "Own Dungeon", "Anywhere", "LACS-Vanilla", "LACS-Medallions", "LACS-Stones", "LACS-Dungeons"},
                                                                      {ganonKeyStartWith, ganonKeyVanilla, ganonKeyOwnDungeon, ganonKeyAnywhere, ganonKeyLACS, ganonKeyLACS, ganonKeyLACS, ganonKeyLACS});
  u8 LACSCondition           = 0;
  std::vector<Option *> shuffleDungeonItemOptions = {
    &MapsAndCompasses,
    &Keysanity,
    &GerudoKeys,
    &BossKeysanity,
    &GanonsBossKey,
  };

  //Timesaver Settings
  Option SkipChildStealth    = Option::Bool("Skip Child Stealth",     {"Don't Skip", "Skip"},                                  {childStealthDesc, childStealthDesc});
  Option SkipTowerEscape     = Option::Bool("Skip Tower Escape",      {"Don't Skip", "Skip"},                                  {skipTowerEscapeDesc, skipTowerEscapeDesc});
  Option SkipEponaRace       = Option::Bool("Skip Epona Race",        {"Don't Skip", "Skip"},                                  {skipEponaRaceDesc, skipEponaRaceDesc});
  Option FourPoesCutscene    = Option::Bool("Four Poes Cutscene",     {"Don't Skip", "Skip"},                                  {fourPoesDesc, fourPoesDesc});
  Option TempleOfTimeIntro   = Option::Bool("Temple of Time Intro",   {"Don't Skip", "Skip"},                                  {templeOfTimeIntroDesc, templeOfTimeIntroDesc});
  Option BigPoeTargetCount   = Option::U8  ("Big Poe Target Count",   {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"},     std::vector<std::string_view>{10, bigPoeTargetCountDesc});
  Option NumRequiredCuccos   = Option::U8  ("Cuccos to return",       {"0", "1", "2", "3", "4", "5", "6", "7"},                std::vector<std::string_view>{8, numRequiredCuccosDesc});
  std::vector<Option *> timesaverOptions = {
    &SkipChildStealth,
    &SkipTowerEscape,
    &SkipEponaRace,
    &FourPoesCutscene,
    &TempleOfTimeIntro,
    &BigPoeTargetCount,
    &NumRequiredCuccos,
  };

  //Misc Settings
  Option DamageMultiplier    = Option::U8  ("Damage Multiplier",      {"Half", "Default", "Double", "Quadruple", "OHKO"},      std::vector<std::string_view>{5, damageMultiDesc});
  Option StartingTime        = Option::U8  ("Starting Time",          {"Day", "Night"},                                        {startingTimeDesc, startingTimeDesc});
  Option GenerateSpoilerLog  = Option::Bool("Generate Spoiler Log",   {"No", "Yes"},                                           {"", ""});
  bool HasNightStart         = false;
  std::vector<Option *> miscOptions = {
    &DamageMultiplier,
    &StartingTime,
    &GenerateSpoilerLog,
  };

  //Item Usability Settings
  Option StickAsAdult        = Option::Bool("Adult Deku Stick",       {"Disable", "Enable"},                                   {adultStickDesc, adultStickDesc});
  Option BoomerangAsAdult    = Option::Bool("Adult Boomerang",        {"Disable", "Enable"},                                   {adultBoomerangDesc, adultBoomerangDesc});
  Option HammerAsChild       = Option::Bool("Child Hammer",           {"Disable", "Enable"},                                   {childHammerDesc, childHammerDesc});
  std::vector<Option *> itemUsabilityOptions = {
    &StickAsAdult,
    &BoomerangAsAdult,
    &HammerAsChild,
  };

  //Item Pool Settings
  Option ItemPoolValue       = Option::U8  ("Item Pool",              {"Plentiful", "Balanced", "Scarce", "Minimal"},          {itemPoolPlentiful, itemPoolBalanced, itemPoolScarce, itemPoolMinimal});
  Option IceTrapValue        = Option::U8  ("Ice Traps",              {"Off", "Normal", "Extra", "Mayhem", "Onslaught"},       {iceTrapsOff, iceTrapsNormal, iceTrapsExtra, iceTrapsMayhem, iceTrapsOnslaught});
  std::vector<Option *> itemPoolOptions = {
    &ItemPoolValue,
    &IceTrapValue,
  };

  //Excluded Locations (Individual definitions made in ItemLocation class)
  std::vector<Option *> excludeLocationsOptions = {};

  //Function to make defining logic tricks easier to read
  Option LogicTrick(std::string setting, std::string_view description) {
    return Option::Bool(setting, {"Disable", "Enable"}, std::vector<std::string_view>{2, description});
  }

  //Detailed Logic Tricks                               ---------------------
  Option ToggleAllDetailedLogic           = LogicTrick("All Tricks",                                      ToggleAllDetailedLogicDesc);
  Option LogicGrottosWithoutAgony         = LogicTrick("Grottos Without Agony",                           LogicGrottosWithoutAgonyDesc);
  Option LogicVisibleCollision            = LogicTrick("Pass Through Visible\n One-Way Collisions",       LogicVisibleCollisionDesc);
  Option LogicFewerTunicRequirements      = LogicTrick("Fewer Tunic\n Requirements",                      LogicFewerTunicRequirementsDesc);
  Option LogicLostWoodsGSBean             = LogicTrick("Lost Woods Adult GS\n without Bean",              LogicLostWoodsGSBeanDesc);
  Option LogicLabDiving                   = LogicTrick("Lake Hylia Lab Dive\n without Gold Scale",        LogicLabDivingDesc);
  Option LogicLabWallGS                   = LogicTrick("Lake Hylia Lab Wall\n GS with Jump Slash",        LogicLabWallGSDesc);
  Option LogicGraveyardPoH                = LogicTrick("Graveyard Freestanding\n PoH with Boomerang",     LogicGraveyardPoHDesc);
  Option LogicChildDampeRacePoH           = LogicTrick("Second Dampe Race as\n Child",                    LogicChildDampeRacePoHDesc);
  Option LogicGerudoKitchen               = LogicTrick("Gerudo Fortress\n Kitchen with No Items",         LogicGerudoKitchenDesc);
  Option LogicLensWasteland               = LogicTrick("Lensless Wasteland",                              LogicLensWastelandDesc);
  Option LogicReverseWasteland            = LogicTrick("Reverse Wasteland",                               LogicReverseWastelandDesc);
  Option LogicColossusGS                  = LogicTrick("Colossus Hill GS\n with Hookshot",                LogicColossusGSDesc);
  Option LogicOutsideGanonsGS             = LogicTrick("OGC GS with No Items",                            LogicOutsideGanonsGSDesc);
  Option LogicManOnRoof                   = LogicTrick("Man on Roof without\n Hookshot",                  LogicManOnRoofDesc);
  Option LogicDMTBombable                 = LogicTrick("Death Mountain Trail\n Chest with Strength",      LogicDMTBombableDesc);
  Option LogicDMTSoilGS                   = LogicTrick("DMT Soil GS without\n Destroying Boulder",        LogicDMTSoilGSDesc);
  Option LogicLinkGoronDins               = LogicTrick("Stop Link the Goron\n with Din's Fire",           LogicLinkGoronDinsDesc);
  Option LogicGoronCityLeftMost           = LogicTrick("Goron City Maze Left\n Chest with Hover Boots",   LogicGoronCityLeftMostDesc);
  Option LogicGoronCityPot                = LogicTrick("Goron City Spinning\n Pot PoH with Bombchu",      LogicGoronCityPotDesc); //Needs Testing
  Option LogicGoronCityPotWithStrength    = LogicTrick("Goron City Spinning\n Pot PoH with Strength",     LogicGoronCityPotWithStrengthDesc);
  Option LogicChildRollingWithStrength    = LogicTrick("Rolling Goron as\n Child with Strength",          LogicChildRollingWithStrengthDesc);
  Option LogicCraterUpperToLower          = LogicTrick("Crater Upper to Lower\n with Hammer",             LogicCraterUpperToLowerDesc); //Needs Testing
  Option LogicCraterBeanPoHWithHovers     = LogicTrick("Crater's Bean PoH\n with Hover Boots",            LogicCraterBeanPoHWithHoversDesc);
  Option LogicBiggoronBolero              = LogicTrick("Deliver Eye Drops\n with Bolero of Fire",         LogicBiggoronBoleroDesc);
  Option LogicZoraRiverLower              = LogicTrick("Zora's River Lower\n PoH with Nothing",           LogicZoraRiverLowerDesc);
  Option LogicZoraRiverUpper              = LogicTrick("Zora's River Upper\n PoH with Nothing",           LogicZoraRiverUpperDesc);
  Option LogicDekuB1WebsWithBow           = LogicTrick("Deku Tree Basement\n Web with Bow",               LogicDekuB1WebsWithBowDesc);
  Option LogicDekuB1Skip                  = LogicTrick("Deku Tree Basement\n without Slingshot",          LogicDekuB1SkipDesc);
  Option LogicDekuBasementGS              = LogicTrick("Deku Tree Basement\n Vines GS w/ Jump Slash",     LogicDekuBasementGSDesc);
  Option LogicDCStaircase                 = LogicTrick("Dodongo's Cavern\n Staircase with Bow",           LogicDCStaircaseDesc);
  Option LogicDCJump                      = LogicTrick("DC Spike Trap room\n Jump w/o Hover Boots",       LogicDCJumpDesc);
  Option LogicDCSlingshotSkip             = LogicTrick("DC Child Slingshot\n Skips",                      LogicDCSlingshotSkipDesc);
  Option LogicDCScarecrowGS               = LogicTrick("DC Scarecrow GS with\n Armos Statue",             LogicDCScarecrowGSDesc);
  Option LogicJabuBossGSAdult             = LogicTrick("Jabu Near Boss GS as\n Adult w/o Boomerang",      LogicJabuBossGSAdultDesc); //Needs Testing
  Option LogicJabuScrubJumpDive           = LogicTrick("Jabu Scrub as Adult\n w/ Jump Dive",              LogicJabuScrubJumpDiveDesc); //Needs Testing
  Option LogicForestOutsideBackdoor       = LogicTrick("FoT Outisde Backdoor\n w/ Jump Slash",            LogicForestOutsideBackdoorDesc); //Needs Testing
  Option LogicForestDoorFrame             = LogicTrick("FoT East Courtyard\n Door Frame w/ Hover Boots",  LogicForestDoorFrameDesc); //Needs Testing
  Option LogicForestOutdoorEastGS         = LogicTrick("FoT East Courtyard GS\n with Boomerang",          LogicForestOutdoorEastGSDesc);
  Option LogicFireBossDoorJump            = LogicTrick("FiT Boss Door without\n Hover Boots or Pillar",   LogicFireBossDoorJumpDesc);
  Option LogicFireStrength                = LogicTrick("FiT Climb without\n Strength",                    LogicFireStrengthDesc);
  Option LogicFireScarecrow               = LogicTrick("FiT East Tower w/o\n Scarecrow\'s Song",          LogicFireScarecrowDesc);
  Option LogicFireFlameMaze               = LogicTrick("FiT Flame Wall Maze\n Skip",                      LogicFireFlameMazeDesc);
  Option LogicFireSongOfTime              = LogicTrick("FiT Song of Time Room\n GS w/o Song of Time",     LogicFireSongOfTimeDesc);
  Option LogicWaterTempleTorchLongshot    = LogicTrick("WaT Torch Longshot",                              LogicWaterTempleTorchLongshotDesc);
  Option LogicWaterTempleUpperBoost       = LogicTrick("WaT Upper Ledge Jump\n with Bombs",               LogicWaterTempleUpperBoostDesc);
  Option LogicWaterCentralBow             = LogicTrick("WaT Bow Target w/o\n Longshot or Hover Boots",    LogicWaterCentralBowDesc);
  Option LogicWaterCentralGSFW            = LogicTrick("WaT Central Pillar GS\n with Farore's Wind",      LogicWaterCentralGSFWDesc);
  Option LogicWaterCrackedWallNothing     = LogicTrick("WaT Cracked Wall with\n No Additional Items",     LogicWaterCrackedWallNothingDesc);
  Option LogicWaterCrackedWallHovers      = LogicTrick("WaT Cracked Wall with\n Hover Boots",             LogicWaterCrackedWallHoversDesc);
  Option LogicWaterBossKeyRegion          = LogicTrick("WaT Boss Key Region\n with Hover Boots",          LogicWaterBossKeyRegionDesc);
  Option LogicWaterBKJumpDive             = LogicTrick("WaT Boss Key Jump\n Dive",                        LogicWaterBKJumpDiveDesc);
  Option LogicWaterNorthBasementLedgeJump = LogicTrick("WaT North Basement\n Ledge with Precise Jump",    LogicWaterNorthBasementLedgeJumpDesc);
  Option LogicWaterDragonAdult            = LogicTrick("WaT Dragon Statue\n Jump Dive",                   LogicWaterDragonAdultDesc);
  Option LogicWaterDragonJumpDive         = LogicTrick("WaT Dragon Statue\n Switch Above as Adult",       LogicWaterDragonJumpDiveDesc);
  Option LogicWaterRiverGS                = LogicTrick("WaT River GS without\n Iron Boots",               LogicWaterRiverGSDesc);
  Option LogicWaterFallingPlatformGS      = LogicTrick("WaT Falling Platform\n Room GS with Hookshot",    LogicWaterFallingPlatformGSDesc);
  Option LogicSpiritLowerAdultSwitch      = LogicTrick("SpT Lower Adult\n Switch with Bombs",             LogicSpiritLowerAdultSwitchDesc);
  Option LogicSpiritChildBombchu          = LogicTrick("SpT Child Side Bridge\n with Bombchu",            LogicSpiritChildBombchuDesc);
  Option LogicSpiritWall                  = LogicTrick("SpT Shifting Wall w/\n No Additional Items",      LogicSpiritWallDesc);
  Option LogicSpiritLobbyGS               = LogicTrick("SpT Main Room GS with\n Boomerang",               LogicSpiritLobbyGSDesc);
  Option LogicSpiritMapChest              = LogicTrick("SpT Map Chest with\n Bow",                        LogicSpiritMapChestDesc);
  Option LogicSpiritSunChest              = LogicTrick("SpT Sun Block Room\n Chest with Bow",             LogicSpiritSunChestDesc); //Needs Testing
  Option LogicShadowFireArrowEntry        = LogicTrick("ShT Entry with Fire\n Arrows",                    LogicShadowFireArrowEntryDesc); //Needs Testing
  Option LogicShadowUmbrella              = LogicTrick("ShT Stone Umbrella\n Skip",                       LogicShadowUmbrellaDesc);
  Option LogicShadowFreestandingKey       = LogicTrick("ShT Freestanding Key\n with Bombchu",             LogicShadowFreestandingKeyDesc);
  Option LogicShadowStatue                = LogicTrick("ShT River Statue with\n Bombchu",                 LogicShadowStatueDesc);
  Option LogicChildDeadhand               = LogicTrick("Child Deadhand w/o\n Kokiri Sword",               LogicChildDeadhandDesc);
  Option LogicGtgWithoutHookshot          = LogicTrick("GTG Left Side Silver\n Rupees w/o Hookshot",      LogicGtgWithoutHookshotDesc);
  Option LogicGtgFakeWall                 = LogicTrick("GTG Fake Wall Ledge\n with Hover Boots",          LogicGtgFakeWallDesc);
  Option LogicLensSpirit                  = LogicTrick("SpT without Lens of\n Truth",                     LogicLensSpiritDesc);
  Option LogicLensShadow                  = LogicTrick("ShT before Invisible\n Moving Platform w/o Lens", LogicLensShadowDesc);
  Option LogicLensShadowBack              = LogicTrick("ShT beyond Invisible\n Moving Platform w/o Lens", LogicLensShadowBackDesc);
  Option LogicLensBotw                    = LogicTrick("BotW without Lens of\n Truth",                    LogicLensBotwDesc);
  Option LogicLensGtg                     = LogicTrick("GTG without Lens of\n Truth",                     LogicLensGtgDesc);
  Option LogicLensCastle                  = LogicTrick("Ganon's Castle w/o\n Lens of Truth",              LogicLensCastleDesc);
  Option LogicSpiritTrialHookshot         = LogicTrick("Spirit Trial without\n Hookshot",                 LogicSpiritTrialHookshotDesc);
  std::vector<Option *> detailedLogicOptions = {
    &ToggleAllDetailedLogic,
    &LogicGrottosWithoutAgony,
    &LogicVisibleCollision,
    &LogicFewerTunicRequirements,
    &LogicLostWoodsGSBean,
    &LogicLabDiving,
    &LogicLabWallGS,
    &LogicGraveyardPoH,
    &LogicChildDampeRacePoH,
    &LogicGerudoKitchen,
    &LogicLensWasteland,
    &LogicReverseWasteland,
    &LogicColossusGS,
    &LogicOutsideGanonsGS,
    &LogicManOnRoof,
    &LogicDMTBombable,
    //&LogicDMTSoilGS, Needs Testing
    &LogicLinkGoronDins,
    &LogicGoronCityLeftMost,
    //&LogicGoronCityPot, Needs Testing
    &LogicGoronCityPotWithStrength,
    &LogicChildRollingWithStrength,
    //&LogicCraterUpperToLower, Needs Testing
    &LogicCraterBeanPoHWithHovers,
    &LogicBiggoronBolero,
    &LogicZoraRiverLower,
    &LogicZoraRiverUpper,
    &LogicDekuB1WebsWithBow,
    &LogicDekuB1Skip,
    &LogicDekuBasementGS,
    &LogicDCStaircase,
    &LogicDCJump,
    &LogicDCSlingshotSkip,
    &LogicDCScarecrowGS,
    //&LogicJabuBossGSAdult, Needs Testing
    //&LogicJabuScrubJumpDive, Needs Testing
    //&LogicForestOutsideBackdoor, Needs Testing
    //&LogicForestDoorFrame, Needs Testing
    &LogicForestOutdoorEastGS,
    &LogicFireBossDoorJump,
    &LogicFireStrength,
    &LogicFireScarecrow,
    &LogicFireFlameMaze,
    &LogicFireSongOfTime,
    &LogicWaterTempleTorchLongshot,
    &LogicWaterTempleUpperBoost,
    &LogicWaterCentralBow,
    &LogicWaterCentralGSFW,
    &LogicWaterCrackedWallNothing,
    &LogicWaterCrackedWallHovers,
    &LogicWaterBossKeyRegion,
    &LogicWaterBKJumpDive,
    &LogicWaterNorthBasementLedgeJump,
    &LogicWaterDragonJumpDive,
    &LogicWaterDragonAdult,
    &LogicWaterRiverGS,
    &LogicWaterFallingPlatformGS,
    &LogicSpiritLowerAdultSwitch,
    &LogicSpiritChildBombchu,
    &LogicSpiritWall,
    &LogicSpiritLobbyGS,
    &LogicSpiritMapChest,
    //&LogicSpiritSunChest, Needs Testing
    //&LogicShadowFireArrowEntry, Needs Testing
    &LogicShadowUmbrella,
    &LogicShadowFreestandingKey,
    &LogicShadowStatue,
    &LogicChildDeadhand,
    &LogicGtgWithoutHookshot,
    &LogicGtgFakeWall,
    &LogicLensSpirit,
    &LogicLensShadow,
    &LogicLensShadowBack,
    &LogicLensBotw,
    &LogicLensGtg,
    &LogicLensCastle,
    &LogicSpiritTrialHookshot,
  };

  MenuItem open                     = MenuItem::SubMenu("Open Settings",              &openOptions);
  MenuItem world                    = MenuItem::SubMenu("World Settings",             &worldOptions);
  MenuItem shuffle                  = MenuItem::SubMenu("Shuffle Settings",           &shuffleOptions);
  MenuItem shuffleDungeonItems      = MenuItem::SubMenu("Shuffle Dungeon Items",      &shuffleDungeonItemOptions);
  MenuItem excludeLocations         = MenuItem::SubMenu("Exclude Locations",          &excludeLocationsOptions);
  MenuItem detailedLogic            = MenuItem::SubMenu("Detailed Logic Settings",    &detailedLogicOptions);
  MenuItem timesaverSettings        = MenuItem::SubMenu("Timesaver Settings",         &timesaverOptions);
  MenuItem miscSettings             = MenuItem::SubMenu("Misc Settings",              &miscOptions);
  MenuItem itemPoolSettings         = MenuItem::SubMenu("Item Pool Settings",         &itemPoolOptions);
  MenuItem itemUsabilitySettings    = MenuItem::SubMenu("Item Usability Settings",    &itemUsabilityOptions);
  MenuItem loadSettingsPreset       = MenuItem::Action ("Load Settings Preset",       LOAD_PRESET);
  MenuItem saveSettingsPreset       = MenuItem::Action ("Save Settings Preset",       SAVE_PRESET);
  MenuItem generateRandomizer       = MenuItem::Action ("Generate Randomizer",        GENERATE_MODE);

  //adding a menu with no options crashes, might fix later
  std::vector<MenuItem *> mainMenu = {
    &open,
    &world,
    &shuffle,
    &shuffleDungeonItems,
    &timesaverSettings,
    &excludeLocations,
    &detailedLogic,
    &miscSettings,
    &itemPoolSettings,
    &itemUsabilitySettings,
    &loadSettingsPreset,
    &saveSettingsPreset,
    &generateRandomizer,
  };

  //declared here, set in fill.cpp
  u32 LinksPocketRewardBitMask = 0;
  std::array<u32, 9> rDungeonRewardOverrides{};

  //declared here, set in menu.cpp
  u8 PlayOption;

  //Fills a SettingsContext struct which is sent to the patch
  SettingsContext FillContext() {
    SettingsContext ctx = {};
    ctx.hashIndexes[0] = hashIconIndexes[0];
    ctx.hashIndexes[1] = hashIconIndexes[1];
    ctx.hashIndexes[2] = hashIconIndexes[2];
    ctx.hashIndexes[3] = hashIconIndexes[3];
    ctx.hashIndexes[4] = hashIconIndexes[4];

    ctx.logic              = Logic.Value<u8>();
    ctx.openForest         = OpenForest.Value<u8>();
    ctx.openKakariko       = OpenKakariko.Value<u8>();
    ctx.openDoorOfTime     = (OpenDoorOfTime) ? 1 : 0;
    ctx.zorasFountain      = ZorasFountain.Value<u8>();
    ctx.gerudoFortress     = GerudoFortress.Value<u8>();
    ctx.rainbowBridge      = Bridge.Value<u8>();
    ctx.bridgeTokenCount   = BridgeTokenCount.Value<u8>();
    ctx.randomGanonsTrials = (RandomGanonsTrials) ? 1 : 0;
    ctx.ganonsTrialsCount  = GanonsTrialsCount.Value<u8>();

    ctx.startingAge        = StartingAge.Value<u8>();
    ctx.bombchusInLogic    = (BombchusInLogic) ? 1 : 0;
    ctx.bombchuDrops       = (BombchuDrops) ? 1 : 0;
    ctx.randomMQDungeons   = (RandomMQDungeons) ? 1 : 0;
    ctx.mqDungeonCount     = MQDungeonCount.Value<u8>();
    ctx.mirrorWorld        = (MirrorWorld) ? 1 : 0;

    ctx.shuffleSongs       = ShuffleSongs.Value<u8>();
    ctx.tokensanity        = Tokensanity.Value<u8>();
    ctx.scrubsanity        = Scrubsanity.Value<u8>();
    ctx.shuffleCows        = (ShuffleCows) ? 1 : 0;
    ctx.shuffleKokiriSword = (ShuffleKokiriSword) ? 1 : 0;
    ctx.shuffleOcarinas    = (ShuffleOcarinas) ? 1 : 0;
    ctx.shuffleWeirdEgg    = (ShuffleWeirdEgg) ? 1 : 0;
    ctx.shuffleGerudoToken = (ShuffleGerudoToken) ? 1 : 0;
    ctx.shuffleMagicBeans  = (ShuffleMagicBeans) ? 1 : 0;

    ctx.mapsAndCompasses   = MapsAndCompasses.Value<u8>();
    ctx.keysanity          = Keysanity.Value<u8>();
    ctx.gerudoKeys         = GerudoKeys.Value<u8>();
    ctx.bossKeysanity      = BossKeysanity.Value<u8>();
    ctx.ganonsBossKey      = GanonsBossKey.Value<u8>();
    ctx.lacsCondition      = LACSCondition;

    ctx.skipChildStealth   = (SkipChildStealth) ? 1 : 0;
    ctx.skipTowerEscape    = (SkipTowerEscape) ? 1 : 0;
    ctx.skipEponaRace      = (SkipEponaRace) ? 1 : 0;
    ctx.fourPoesCutscene   = (FourPoesCutscene) ? 1 : 0;
    ctx.templeOfTimeIntro  = (TempleOfTimeIntro) ? 1 : 0;
    ctx.bigPoeTargetCount  = BigPoeTargetCount.Value<u8>() + 1;
    ctx.numRequiredCuccos  = NumRequiredCuccos.Value<u8>();

    ctx.damageMultiplier   = DamageMultiplier.Value<u8>();
    ctx.startingTime       = StartingTime.Value<u8>();
    ctx.generateSpoilerLog = (GenerateSpoilerLog) ? 1 : 0;

    ctx.stickAsAdult       = (StickAsAdult) ? 1 : 0;
    ctx.boomerangAsAdult   = (BoomerangAsAdult) ? 1 : 0;
    ctx.hammerAsChild      = (HammerAsChild) ? 1 : 0;

    ctx.itemPoolValue      = ItemPoolValue.Value<u8>();
    ctx.iceTrapValue       = IceTrapValue.Value<u8>();

    ctx.dekuTreeDungeonMode              = (DekuTreeDungeonMode)              ? 1 : 0;
    ctx.dodongosCavernDungeonMode        = (DodongosCavernDungeonMode)        ? 1 : 0;
    ctx.jabuJabusBellyDungeonMode        = (JabuJabusBellyDungeonMode)        ? 1 : 0;
    ctx.forestTempleDungeonMode          = (ForestTempleDungeonMode)          ? 1 : 0;
    ctx.fireTempleDungeonMode            = (FireTempleDungeonMode)            ? 1 : 0;
    ctx.waterTempleDungeonMode           = (WaterTempleDungeonMode)           ? 1 : 0;
    ctx.spiritTempleDungeonMode          = (SpiritTempleDungeonMode)          ? 1 : 0;
    ctx.shadowTempleDungeonMode          = (ShadowTempleDungeonMode)          ? 1 : 0;
    ctx.bottomOfTheWellDungeonMode       = (BottomOfTheWellDungeonMode)       ? 1 : 0;
    ctx.iceCavernDungeonMode             = (IceCavernDungeonMode)             ? 1 : 0;
    ctx.gerudoTrainingGroundsDungeonMode = (GerudoTrainingGroundsDungeonMode) ? 1 : 0;
    ctx.ganonsCastleDungeonMode          = (GanonsCastleDungeonMode)          ? 1 : 0;

    ctx.forestTrialSkip = (ForestTrialSkip) ? 1 : 0;
    ctx.fireTrialSkip   = (FireTrialSkip)   ? 1 : 0;
    ctx.waterTrialSkip  = (WaterTrialSkip)  ? 1 : 0;
    ctx.spiritTrialSkip = (SpiritTrialSkip) ? 1 : 0;
    ctx.shadowTrialSkip = (ShadowTrialSkip) ? 1 : 0;
    ctx.lightTrialSkip  = (LightTrialSkip)  ? 1 : 0;

    ctx.dungeonRewardBitMask = LinksPocketRewardBitMask;

    //Filling detailed logic
    for (u16 i = 0; i < detailedLogicOptions.size(); i++) {
      ctx.detailedLogic[i] = detailedLogicOptions[i]->GetSelectedOptionIndex();
    }

    //Filling excluded locations
    for (u16 i = 0; i < excludeLocationsOptions.size(); i++) {
      ctx.excludeLocations[i] = excludeLocationsOptions[i]->GetSelectedOptionIndex();
    }
    return ctx;
  }

  //Takes a SettingsContext to use for the current settings
  void FillSettings(SettingsContext ctx) {
    Logic.SetSelectedIndex(ctx.logic);
    OpenForest.SetSelectedIndex(ctx.openForest);
    OpenKakariko.SetSelectedIndex(ctx.openKakariko);
    OpenDoorOfTime.SetSelectedIndex(ctx.openDoorOfTime);
    ZorasFountain.SetSelectedIndex(ctx.zorasFountain);
    GerudoFortress.SetSelectedIndex(ctx.gerudoFortress);
    Bridge.SetSelectedIndex(ctx.rainbowBridge);
    BridgeTokenCount.SetSelectedIndex(ctx.bridgeTokenCount);
    RandomGanonsTrials.SetSelectedIndex(ctx.randomGanonsTrials);
    GanonsTrialsCount.SetSelectedIndex(ctx.ganonsTrialsCount);

    StartingAge.SetSelectedIndex(ctx.startingAge);
    BombchusInLogic.SetSelectedIndex(ctx.bombchusInLogic);
    BombchuDrops.SetSelectedIndex(ctx.bombchuDrops);
    RandomMQDungeons.SetSelectedIndex(ctx.randomMQDungeons);
    MQDungeonCount.SetSelectedIndex(ctx.mqDungeonCount);
    MirrorWorld.SetSelectedIndex(ctx.mirrorWorld);

    ShuffleSongs.SetSelectedIndex(ctx.shuffleSongs);
    Tokensanity.SetSelectedIndex(ctx.tokensanity);
    Scrubsanity.SetSelectedIndex(ctx.scrubsanity);
    ShuffleCows.SetSelectedIndex(ctx.shuffleCows);
    ShuffleKokiriSword.SetSelectedIndex(ctx.shuffleKokiriSword);
    ShuffleOcarinas.SetSelectedIndex(ctx.shuffleOcarinas);
    ShuffleWeirdEgg.SetSelectedIndex(ctx.shuffleWeirdEgg);
    ShuffleGerudoToken.SetSelectedIndex(ctx.shuffleGerudoToken);
    ShuffleMagicBeans.SetSelectedIndex(ctx.shuffleMagicBeans);

    MapsAndCompasses.SetSelectedIndex(ctx.mapsAndCompasses);
    Keysanity.SetSelectedIndex(ctx.keysanity);
    GerudoKeys.SetSelectedIndex(ctx.gerudoKeys);
    BossKeysanity.SetSelectedIndex(ctx.bossKeysanity);
    GanonsBossKey.SetSelectedIndex(ctx.ganonsBossKey);

    SkipChildStealth.SetSelectedIndex(ctx.skipChildStealth);
    SkipTowerEscape.SetSelectedIndex(ctx.skipTowerEscape);
    SkipEponaRace.SetSelectedIndex(ctx.skipEponaRace);
    FourPoesCutscene.SetSelectedIndex(ctx.fourPoesCutscene);
    TempleOfTimeIntro.SetSelectedIndex(ctx.templeOfTimeIntro);
    BigPoeTargetCount.SetSelectedIndex(ctx.bigPoeTargetCount - 1);
    NumRequiredCuccos.SetSelectedIndex(ctx.numRequiredCuccos);

    DamageMultiplier.SetSelectedIndex(ctx.damageMultiplier);
    StartingTime.SetSelectedIndex(ctx.startingTime);
    GenerateSpoilerLog.SetSelectedIndex(ctx.generateSpoilerLog);

    StickAsAdult.SetSelectedIndex(ctx.stickAsAdult);
    BoomerangAsAdult.SetSelectedIndex(ctx.boomerangAsAdult);
    HammerAsChild.SetSelectedIndex(ctx.hammerAsChild);

    ItemPoolValue.SetSelectedIndex(ctx.itemPoolValue);
    IceTrapValue.SetSelectedIndex(ctx.iceTrapValue);

    for (u16 i = 0; i < detailedLogicOptions.size(); i++) {
      detailedLogicOptions[i]->SetSelectedIndex(ctx.detailedLogic[i]);
    }

    for (u16 i = 0; i < excludeLocationsOptions.size(); i++) {
      excludeLocationsOptions[i]->SetSelectedIndex(ctx.excludeLocations[i]);
    }
  }

  //Set default settings for all settings where the default is not the first option
  void SetDefaultSettings() {
    OpenForest.SetSelectedIndex(OPENFOREST_OPEN);
    OpenDoorOfTime.SetSelectedIndex(1); //1 is Open, 0 is Closed
    Bridge.SetSelectedIndex(RAINBOWBRIDGE_VANILLA);
    BridgeTokenCount.Hide();
    RandomGanonsTrials.SetSelectedIndex(ON);
    GanonsTrialsCount.Hide();

    std::vector<std::string> bridgeTokenOptions = {};
    for (int i = 0; i <= 100; i++) {
      bridgeTokenOptions.push_back(std::to_string(i));
    }
    BridgeTokenCount.SetOptions(bridgeTokenOptions);
    BridgeTokenCount.SetSelectedIndex(1);

    StartingAge.SetSelectedIndex(AGE_CHILD);

    MapsAndCompasses.SetSelectedIndex(MAPSANDCOMPASSES_VANILLA);
    Keysanity.SetSelectedIndex(KEYSANITY_VANILLA);
    BossKeysanity.SetSelectedIndex(BOSSKEYSANITY_VANILLA);
    GanonsBossKey.SetSelectedIndex(GANONSBOSSKEY_VANILLA);

    AddExcludedOptions();
    HC_ZeldasLetter.GetExcludedOption()->Hide(); //don't let users change this location

    DamageMultiplier.SetSelectedIndex(DAMAGEMULTIPLIER_DEFAULT);
    GenerateSpoilerLog.SetSelectedIndex(1); //true

    ItemPoolValue.SetSelectedIndex(ITEMPOOL_BALANCED);
    IceTrapValue.SetSelectedIndex(ICETRAPS_NORMAL);
  }

  //Include and Lock the desired locations
  void IncludeAndHide(std::vector<ItemLocation*> locations) {
    for (auto& loc : locations) {
      loc->GetExcludedOption()->SetSelectedIndex(INCLUDE);
      loc->GetExcludedOption()->Hide();
    }
  }

  //Unlock the desired locations
  void Unhide(std::vector<ItemLocation*> locations) {
    for (auto& loc : locations) {
      loc->GetExcludedOption()->Unhide();
    }
  }

  //Lock required locations based on current settings
  void ResolveExcludedLocationConflicts() {

    //Force include shops if shopsanity is off
    std::vector<ItemLocation*> shopLocations = GetLocations(everyPossibleLocation, Category::cShop);
    if (Shopsanity) {
      Unhide(shopLocations);
    } else {
      IncludeAndHide(shopLocations);
    }

    //Force include song locations
    std::vector<ItemLocation*> songLocations = GetLocations(everyPossibleLocation, Category::cSong);
    std::vector<ItemLocation*> songDungeonRewards = GetLocations(everyPossibleLocation, Category::cSongDungeonReward);

    //Unhide all song locations, then lock necessary ones
    Unhide(songLocations);
    Unhide(songDungeonRewards);

    if (ShuffleSongs.Is(SONGSHUFFLE_SONG_LOCATIONS)) {
      IncludeAndHide(songLocations);
    } else if (ShuffleSongs.Is(SONGSHUFFLE_DUNGEON_REWARDS)) {
      IncludeAndHide(songDungeonRewards);
    }

    //Force Include Vanilla Skulltula locations
    std::vector<ItemLocation*> skulltulaLocations = GetLocations(everyPossibleLocation, Category::cSkulltula);
    Unhide(skulltulaLocations);
    if (Tokensanity.IsNot(TOKENSANITY_ALL_TOKENS)) {
      if (Tokensanity.Is(TOKENSANITY_OVERWORLD)) {
        //filter overworld skulls so we're just left with dungeons
        FilterAndEraseFromPool(skulltulaLocations, [](ItemLocation* loc){return loc->GetScene() > 0x0A;});
      } else if (Tokensanity.Is(TOKENSANITY_DUNGEONS)) {
        //filter dungeon skulls so we're just left with overworld
        FilterAndEraseFromPool(skulltulaLocations, [](ItemLocation* loc){return loc->GetScene() <= 0x0A;});
      }
      IncludeAndHide(skulltulaLocations);
    }

    //Force Include scrubs if Scrubsanity is Off
    std::vector<ItemLocation*> scrubLocations = GetLocations(everyPossibleLocation, Category::cDekuScrub);
    if (Scrubsanity.Is(OFF)) {
      IncludeAndHide(scrubLocations);
    } else {
      Unhide(scrubLocations);
    }

    //Force include Cows if Shuffle Cows is Off
    std::vector<ItemLocation*> cowLocations = GetLocations(everyPossibleLocation, Category::cCow);
    if (ShuffleCows) {
      Unhide(cowLocations);
    } else {
      IncludeAndHide(cowLocations);
    }

    //Force include the Kokiri Sword Chest if Shuffle Kokiri Sword is Off
    if (ShuffleKokiriSword) {
      Unhide({&KF_KokiriSwordChest});
    } else {
      IncludeAndHide({&KF_KokiriSwordChest});
    }

    //Force include the ocarina locations if Shuffle Ocarinas is Off
    std::vector<ItemLocation*> ocarinaLocations = {&LW_GiftFromSaria, &HF_OcarinaOfTimeItem};
    if (ShuffleOcarinas) {
      Unhide(ocarinaLocations);
    } else {
      IncludeAndHide(ocarinaLocations);
    }

    //Force include Malon if Shuffle Weird Egg is Off
    if (ShuffleWeirdEgg) {
      Unhide({&HC_MalonEgg});
    } else {
      IncludeAndHide({&HC_MalonEgg});
    }

    //Gerudo Card is handled in item_pool.cpp

    //Force include Magic Bean salesman if Shuffle Magic Beans is off
    if (ShuffleMagicBeans) {
      Unhide({&ZR_MagicBeanSalesman});
    } else {
      IncludeAndHide({&ZR_MagicBeanSalesman});
    }

    //Force include Map and Compass Chests when Vanilla
    std::vector<ItemLocation*> mapChests = GetLocations(everyPossibleLocation, Category::cVanillaMap);
    std::vector<ItemLocation*> compassChests = GetLocations(everyPossibleLocation, Category::cVanillaCompass);
    if (MapsAndCompasses.Is(MAPSANDCOMPASSES_VANILLA)) {
      IncludeAndHide(mapChests);
      IncludeAndHide(compassChests);
    } else {
      Unhide(mapChests);
      Unhide(compassChests);
    }

    //Force include Vanilla Small Key Locations (except gerudo Fortress) on Vanilla Keys
    std::vector<ItemLocation*> smallKeyChests = GetLocations(everyPossibleLocation, Category::cVanillaSmallKey);
    if (Keysanity.Is(KEYSANITY_VANILLA)) {
      IncludeAndHide(smallKeyChests);
    } else {
      Unhide(smallKeyChests);
    }

    //Force include Boss Key Chests if Boss Keys are Vanilla
    std::vector<ItemLocation*> bossKeyChests = GetLocations(everyPossibleLocation, Category::cVanillaBossKey);
    if (BossKeysanity.Is(BOSSKEYSANITY_VANILLA)) {
      IncludeAndHide(bossKeyChests);
    } else {
      Unhide(bossKeyChests);
    }

    //Force include Ganons Boss Key Chest if ganons boss key has to be there
    if (GanonsBossKey.Is(GANONSBOSSKEY_VANILLA)) {
      IncludeAndHide({&GanonsCastle_BossKeyChest});
    } else {
      Unhide({&GanonsCastle_BossKeyChest});
    }

    //Force include Light Arrow item if ganons boss key has to be there
    if (GanonsBossKey.Value<u8>() >= GANONSBOSSKEY_LACS_VANILLA) {
      IncludeAndHide({&ToT_LightArrowCutscene});
    } else {
      Unhide({&ToT_LightArrowCutscene});
    }
  }

  //Make any forcible setting changes when certain settings change
  void ForceChange(u32 kDown, Option* currentSetting) {

    //Adult is not compatible with Closed Forest
    if (OpenForest.Is(OPENFOREST_CLOSED)) {
      StartingAge.SetSelectedIndex(AGE_CHILD);
      StartingAge.Lock();
    } else {
      StartingAge.Unlock();
    }

    //Only show token count option if Tokens is selected
    if (Bridge.Is(RAINBOWBRIDGE_TOKENS)) {
      BridgeTokenCount.Unhide();
    } else {
      BridgeTokenCount.Hide();
      BridgeTokenCount.SetSelectedIndex(1);
    }

    //Only show Trial Count option if Random Trial Count is off
    if (RandomGanonsTrials) {
      GanonsTrialsCount.Hide();
      GanonsTrialsCount.SetSelectedIndex(6);
    } else {
      GanonsTrialsCount.Unhide();
    }

    //Bombchus in Logic forces Bombchu Drops
    if (BombchusInLogic) {
      BombchuDrops.SetSelectedIndex(ON);
      BombchuDrops.Lock();
    } else {
      BombchuDrops.Unlock();
    }

    //Only show MQ Dungeon Count if Random MQ Dungeons is off
    if (RandomMQDungeons) {
      MQDungeonCount.Hide();
      MQDungeonCount.SetSelectedIndex(0);
    } else {
      MQDungeonCount.Unhide();
    }

    //Set toggle for all tricks
    if ((kDown & KEY_DLEFT || kDown & KEY_DRIGHT) && currentSetting->GetName() == "All Tricks")  {
      for (u16 i = 0; i < Settings::detailedLogicOptions.size(); i++) {
        detailedLogicOptions[i]->SetSelectedIndex(currentSetting->GetSelectedOptionIndex());
      }
    }

    ResolveExcludedLocationConflicts();
  }

  //eventual settings
  bool ShuffleDungeonEntrances          = false;
  bool ShuffleOverworldEntrances        = false;
  bool ShuffleInteriorEntrances         = false;
  bool ShuffleSpecialIndoorEntrances    = false;
  bool Shopsanity                       = false;

  //MQ vs Vanilla Dungeon Modes
  bool DekuTreeDungeonMode              = false;
  bool DodongosCavernDungeonMode        = false;
  bool JabuJabusBellyDungeonMode        = false;
  bool ForestTempleDungeonMode          = false;
  bool FireTempleDungeonMode            = false;
  bool WaterTempleDungeonMode           = false;
  bool SpiritTempleDungeonMode          = false;
  bool ShadowTempleDungeonMode          = false;
  bool BottomOfTheWellDungeonMode       = false;
  bool IceCavernDungeonMode             = false;
  bool GerudoTrainingGroundsDungeonMode = false;
  bool GanonsCastleDungeonMode          = false;

  //Skipped Trials (initially set to true, then false ones filtered out)
  bool ForestTrialSkip                  = true;
  bool FireTrialSkip                    = true;
  bool WaterTrialSkip                   = true;
  bool SpiritTrialSkip                  = true;
  bool ShadowTrialSkip                  = true;
  bool LightTrialSkip                   = true;

  //Function to set flags depending on settings
  void UpdateSettings() {

    //shuffle the dungeon mode variables then change the amount set in MQDungeonCount
    std::array<bool*, 12> dungeonModes = {&DekuTreeDungeonMode, &DodongosCavernDungeonMode, &JabuJabusBellyDungeonMode, &ForestTempleDungeonMode,
                                          &FireTempleDungeonMode, &WaterTempleDungeonMode, &SpiritTempleDungeonMode, &ShadowTempleDungeonMode,
                                          &BottomOfTheWellDungeonMode, &IceCavernDungeonMode, &GerudoTrainingGroundsDungeonMode, &GanonsCastleDungeonMode};
    Shuffle(dungeonModes);

    if (RandomMQDungeons) {
      MQDungeonCount.SetSelectedIndex(Random(0, MQDungeonCount.GetOptionCount()));
    }
    for (u8 i = 0; i < MQDungeonCount.Value<u8>(); i++) {
      *dungeonModes[i] = DUNGEONMODE_MQ;
    }

    //shuffle the trials then require the amount set in GanonsTrialsCount
    std::array<bool*, 6> trialsSkipped = {&ForestTrialSkip, &FireTrialSkip, &WaterTrialSkip, &SpiritTrialSkip, &ShadowTrialSkip, &LightTrialSkip};
    Shuffle(trialsSkipped);

    if (RandomGanonsTrials) {
      GanonsTrialsCount.SetSelectedIndex(Random(0, GanonsTrialsCount.GetOptionCount()));
    }
    for (u8 i = 0; i < GanonsTrialsCount.Value<u8>(); i++) {
      *trialsSkipped[i] = false; //the selected trial is not skipped
    }

    HasNightStart = StartingTime.Is(STARTINGTIME_NIGHT);

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

} // namespace Settings
