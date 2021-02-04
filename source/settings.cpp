#include "settings.hpp"
#include "setting_descriptions.hpp"
#include "random.hpp"

namespace Settings {
  std::string seed;

  //                                        Setting name,              Options,                                                Option Descriptions (assigned in setting_descriptions.cpp), default setting index
  //Open Settings
  Option Logic               = Option::U8  ("Logic",                  {"Glitchless", "No Logic"},                              {logicGlitchless, logicNoLogic});
  Option OpenForest          = Option::U8  ("Forest",                 {"Open", "Closed"},                                      {forestOpen, forestClosed});
  Option OpenKakariko        = Option::U8  ("Kakariko Gate",          {"Open", "Closed"},                                      {kakGateOpen, kakGateClosed}, 1);
  Option OpenDoorOfTime      = Option::Bool("Door of Time",           {"Closed", "Open"},                                      {doorOfTimeDesc, doorOfTimeDesc}, true);
  Option ZorasFountain       = Option::U8  ("Zora's Fountain",        {"Normal", "Open"},                                      {fountainNormal, fountainOpen});
  Option GerudoFortress      = Option::U8  ("Gerudo Fortress",        {"Normal", "Fast", "Open"},                              {gerudoNormal, gerudoFast, gerudoOpen});
  Option Bridge              = Option::U8  ("Rainbow Bridge",         {"Open", "Vanilla", "Stones", "Medallions", "Dungeons"}, {bridgeOpen, bridgeVanilla, bridgeStones, bridgeMedallions, bridgeDungeons}, 1);
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
  Option StartingAge         = Option::U8  ("Starting Age",           {"Adult", "Child"},                                      {ageDesc, ageDesc}, 1);
  Option BombchusInLogic     = Option::Bool("Bombchus in Logic",      {"Off", "On"},                                           {bombchuLogicDesc, bombchuLogicDesc});
  Option RandomMQDungeons    = Option::Bool("Random MQ Dungeons",     {"Off", "On"},                                           {randomMQDungeonsDesc, randomMQDungeonsDesc});
  std::vector<Option *> worldOptions = {
    &StartingAge,
    &BombchusInLogic,
    //&RandomMQDungeons, TODO: Finish MQ logic before enabling this
  };

  //Shuffle Settings
  Option ShuffleSongs        = Option::U8  ("Shuffle Songs",          {"Song Locations", "Anywhere"},                          {songsSongLocations, songsAllLocations}); //TODO: Dungeon Rewards
  Option Tokensanity         = Option::U8  ("Tokensanity",            {"Vanilla", "Anywhere"},                                 {tokensVanilla, tokensAllLocations});
  Option Scrubsanity         = Option::U8  ("Scrub Shuffle",          {"Off", "Affordable", "Expensive", "Random Prices"},     {scrubsOff, scrubsAffordable, scrubsExpensive, scrubsRandomPrices});
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
    &ShuffleKokiriSword,
    &ShuffleOcarinas,
    &ShuffleWeirdEgg,
    &ShuffleGerudoToken,
    &ShuffleMagicBeans,
    //TODO: Medigoron and Carpet Salesman
  };

  //Shuffle Dungeon Items
  Option Keysanity           = Option::U8  ("Small Keys",             {"Vanilla", "Own Dungeon", "Anywhere"},                  {smallKeyVanilla, smallKeyOwnDungeon, smallKeyAnywhere});
  Option BossKeysanity       = Option::U8  ("Boss Keys",              {"Vanilla", "Own Dungeon", "Anywhere"},                  {bossKeyVanilla, bossKeyOwnDungeon, bossKeyAnywhere});
  Option GanonsBossKey       = Option::U8  ("Ganon's Boss Key",       {"Vanilla", "Own Dungeon", "Anywhere", "LACS: Vanilla", "LACS: Medallions", "LACS: Stones", "LACS: Dungeons"},
                                                                      {ganonKeyVanilla, ganonKeyOwnDungeon, ganonKeyAnywhere, ganonKeyLACS, ganonKeyLACS, ganonKeyLACS, ganonKeyLACS});
  Option MapsAndCompasses    = Option::U8  ("Maps/Compasses",         {"Start With", "Vanilla", "Own Dungeon", "Anywhere"},    {mapCompassStartWith, mapCompassVanilla, mapCompassOwnDungeon, mapCompassAnywhere}, 1);
  u8 LACSCondition           = 0;
  std::vector<Option *> shuffleDungeonItemOptions = {
    &Keysanity,
    &BossKeysanity,
    &GanonsBossKey,
    &MapsAndCompasses,
  };

  //Timesaver Settings
  Option SkipChildStealth    = Option::U8  ("Skip Child Sealth",      {"Don't Skip", "Skip"},                                  {childStealthDesc, childStealthDesc});
  Option FourPoesCutscene    = Option::Bool("Four Poes Cutscene",     {"Skip", "Don't Skip"},                                  {fourPoesDesc, fourPoesDesc});
  Option BigPoeTargetCount   = Option::U8  ("Big Poe Target Count",   {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"},     {"", "", "", "", "", "", "", "", "", ""});
  std::vector<Option *> timesaverOptions = {
    &SkipChildStealth,
    &FourPoesCutscene,
    &BigPoeTargetCount,
  };

  //Misc Settings
  Option DamageMultiplier    = Option::U8  ("Damage Multiplier",      {"Half", "Default", "Double", "Quadruple", "OHKO"},      {damageMultiDesc, damageMultiDesc, damageMultiDesc, damageMultiDesc, damageMultiDesc}, 1);
  Option StartingTime        = Option::U8  ("Starting Time",          {"Day", "Night"},                                        {startingTimeDesc, startingTimeDesc});
  bool HasNightStart         = false;
  std::vector<Option *> miscOptions = {
    &DamageMultiplier,
    &StartingTime,
  };

  //Advanced Glitch Settings
  Option BoomerangAsAdult    = Option::U8  ("Enable Adult Boomerang", {"No", "Yes"},                                           {adultBoomerangDesc, adultBoomerangDesc});
  Option HammerAsChild       = Option::U8  ("Enable Child Hammer",    {"No", "Yes"},                                           {childHammerDesc, childHammerDesc});
  std::vector<Option *> advancedGlitchedOptions = {
    &BoomerangAsAdult,
    &HammerAsChild,
  };

  //Item Pool Settings
  Option ItemPoolValue       = Option::U8  ("Item Pool",              {"Plentiful", "Balanced", "Scarce", "Minimal"},          {itemPoolPlentiful, itemPoolBalanced, itemPoolScarce, itemPoolMinimal}, 1);
  //TODO: Ice Traps

  //Excluded Locations (definitions made in ItemLocation class)
  std::vector<Option *> excludeLocationsOptions = {};

  //Enable Tricks                                         ---------------------
  Option LogicGrottosWithoutAgony         = Option::Bool("Grottos Without Agony",                          {"Disable", "Enable"}, {"", ""});
  Option LogicVisibleCollision            = Option::Bool("Pass Through Visible\n One-Way Collisions",      {"Disable", "Enable"}, {"", ""});
  Option LogicFewerTunicRequirements      = Option::Bool("Fewer Tunic\n Requirements",                     {"Disable", "Enable"}, {"", ""});
  Option LogicLostWoodsBridge             = Option::Bool("Jump onto the Lost\n Woods Bridge as Adult",     {"Disable", "Enable"}, {"", ""});
  Option LogicLostWoodsGSBean             = Option::Bool("Lost Woods Adult GS\n without Bean",             {"Disable", "Enable"}, {"", ""});
  Option LogicLabDiving                   = Option::Bool("Lake Hylia Lab Dive\n without Gold Scale",       {"Disable", "Enable"}, {"", ""});
  Option LogicLabWallGS                   = Option::Bool("Lake Hylia Lab Wall\n GS with Jump Slash",       {"Disable", "Enable"}, {"", ""});
  Option LogicGraveyardPoH                = Option::Bool("Graveyard Freestanding\n PoH with Boomerang",    {"Disable", "Enable"}, {"", ""});
  Option LogicChildDampeRacePoH           = Option::Bool("Second Dampe Race as\n Child",                   {"Disable", "Enable"}, {"", ""});
  Option LogicGerudoKitchen               = Option::Bool("Gerudo Fortress\n Kitchen with No Items",        {"Disable", "Enable"}, {"", ""});
  Option LogicLensWasteland               = Option::Bool("Lensless Wasteland",                             {"Disable", "Enable"}, {"", ""});
  Option LogicReverseWasteland            = Option::Bool("Reverse Wasteland",                              {"Disable", "Enable"}, {"", ""});
  Option LogicColossusGS                  = Option::Bool("Colossus Hill GS\n with Hookshot",               {"Disable", "Enable"}, {"", ""});
  Option LogicManOnRoof                   = Option::Bool("Man on Roof without\n Hookshot",                 {"Disable", "Enable"}, {"", ""});
  Option LogicKakarikoTowerGS             = Option::Bool("Kakariko Tower GS\n with Jump Slash",            {"Disable", "Enable"}, {"", ""}); //Needs Testing
  Option LogicDMTBombable                 = Option::Bool("Death Mountain Trail\n Chest with Strength",     {"Disable", "Enable"}, {"", ""});
  Option LogicDMTSoilGS                   = Option::Bool("DMT Soil GS without\n Destroying Boulder",       {"Disable", "Enable"}, {"", ""});
  Option LogicLinkGoronDins               = Option::Bool("Stop Link the Goron\n with Din's Fire",          {"Disable", "Enable"}, {"", ""});
  Option LogicGoronCityLeftMost           = Option::Bool("Goron City Maze Left\n Chest with Hover Boots",  {"Disable", "Enable"}, {"", ""});
  Option LogicGoronCityPot                = Option::Bool("Goron City Spinning\n Pot PoH with Bombchu",     {"Disable", "Enable"}, {"", ""}); //Needs Testing
  Option LogicGoronCityPotWithStrength    = Option::Bool("Goron City Spinning\n Pot PoH with Strength",    {"Disable", "Enable"}, {"", ""});
  Option LogicChildRollingWithStrength    = Option::Bool("Rolling Goron as\n Child with Strength",         {"Disable", "Enable"}, {"", ""});
  Option LogicCraterUpperToLower          = Option::Bool("Crater Upper to Lower\n with Hammer",            {"Disable", "Enable"}, {"", ""}); //Needs Testing
  Option LogicCraterBeanPoHWithHovers     = Option::Bool("Crater's Bean PoH\n with Hover Boots",           {"Disable", "Enable"}, {"", ""});
  Option LogicBiggoronBolero              = Option::Bool("Deliver Eye Drops\n with Bolero of Fire",        {"Disable", "Enable"}, {"", ""});
  Option LogicZoraRiverLower              = Option::Bool("Zora's River Lower\n PoH with Nothing",          {"Disable", "Enable"}, {"", ""});
  Option LogicZoraRiverUpper              = Option::Bool("Zora's River Upper\n PoH with Nothing",          {"Disable", "Enable"}, {"", ""});
  Option LogicDekuB1WebsWithBow           = Option::Bool("Deku Tree Basement\n Web with Bow",              {"Disable", "Enable"}, {"", ""});
  Option LogicDekuB1Skip                  = Option::Bool("Deku Tree Basement\n without Slingshot",         {"Disable", "Enable"}, {"", ""});
  Option LogicDekuBasementGS              = Option::Bool("Deku Tree Basement\n Vines GS w/ Jump Slash",    {"Disable", "Enable"}, {"", ""});
  Option LogicDCStaircase                 = Option::Bool("Dodongo's Cavern\n Staircase with Bow",          {"Disable", "Enable"}, {"", ""});
  Option LogicDCJump                      = Option::Bool("DC Spike Trap room\n Jump w/o Hover Boots",      {"Disable", "Enable"}, {"", ""});
  Option LogicDCSlingshotSkip             = Option::Bool("DC Child Slingshot\n Skips",                     {"Disable", "Enable"}, {"", ""});
  Option LogicDCScarecrowGS               = Option::Bool("DC Scarecrow GS with\n Armos Statue",            {"Disable", "Enable"}, {"", ""});
  Option LogicJabuBossGSAdult             = Option::Bool("Jabu Near Boss GS as\n Adult w/o Boomerang",     {"Disable", "Enable"}, {"", ""}); //Needs Testing
  Option LogicJabuScrubJumpDive           = Option::Bool("Jabu Scrub as Adult\n w/ Jump Dive",             {"Disable", "Enable"}, {"", ""}); //Needs Testing
  Option LogicForestOutsideBackdoor       = Option::Bool("FoT Outisde Backdoor\n w/ Jump Slash",           {"Disable", "Enable"}, {"", ""}); //Needs Testing
  Option LogicForestDoorFrame             = Option::Bool("FoT East Courtyard\n Door Frame w/ Hover Boots", {"Disable", "Enable"}, {"", ""}); //Needs Testing
  Option LogicForestOutdoorEastGS         = Option::Bool("FoT East Courtyard GS\n with Boomerang",         {"Disable", "Enable"}, {"", ""});
  Option LogicFireBossDoorJump            = Option::Bool("FiT Boss Door without\n Hover Boots or Pillar",  {"Disable", "Enable"}, {"", ""});
  Option LogicFireStrength                = Option::Bool("FiT Climb without\n Strength",                   {"Disable", "Enable"}, {"", ""});
  Option LogicFireScarecrow               = Option::Bool("FiT East Tower w/o\n Scarecrow\'s Song",         {"Disable", "Enable"}, {"", ""});
  Option LogicFireFlameMaze               = Option::Bool("FiT Flame Wall Maze\n Skip",                     {"Disable", "Enable"}, {"", ""});
  Option LogicFireSongOfTime              = Option::Bool("FiT Song of Time Room\n GS w/o Song of Time",    {"Disable", "Enable"}, {"", ""});
  Option LogicWaterHookshotEntry          = Option::Bool("WaT Entry w/o Iron\n Boots using Hookshot",      {"Disable", "Enable"}, {"", ""}); //Needs Testing
  Option LogicWaterTempleTorchLongshot    = Option::Bool("WaT Torch Longshot",                             {"Disable", "Enable"}, {"", ""});
  Option LogicWaterCentralBow             = Option::Bool("WaT Bow Target w/o\n Longshot or Hover Boots",   {"Disable", "Enable"}, {"", ""});
  Option LogicWaterCrackedWallNothing     = Option::Bool("WaT Cracked Wall with\n No Additional Items",    {"Disable", "Enable"}, {"", ""});
  Option LogicWaterCrackedWallHovers      = Option::Bool("WaT Cracked Wall with\n Hover Boots",            {"Disable", "Enable"}, {"", ""});
  Option LogicWaterBossKeyRegion          = Option::Bool("WaT Boss Key Region\n with Hover Boots",         {"Disable", "Enable"}, {"", ""});
  Option LogicWaterBKJumpDive             = Option::Bool("WaT Boss Key Jump\n Dive",                       {"Disable", "Enable"}, {"", ""});
  Option LogicWaterNorthBasementLedgeJump = Option::Bool("WaT North Basement\n Ledge with Precise Jump",   {"Disable", "Enable"}, {"", ""});
  Option LogicWaterDragonBombchu          = Option::Bool("", {"Disable", "Enable"}, {"", ""}); //Needs to be updated
  Option LogicWaterDragonJumpDive         = Option::Bool("Wat Dragon Statue\n Jump Dive",                  {"Disable", "Enable"}, {"", ""});
  Option LogicWaterRiverGS                = Option::Bool("WaT River GS without\n Iron Boots",              {"Disable", "Enable"}, {"", ""});
  Option LogicWaterFallingPlatformGS      = Option::Bool("WaT Falling Platform\n Room GS with Hookshot",   {"Disable", "Enable"}, {"", ""});
  Option LogicSpiritLowerAdultSwitch      = Option::Bool("SpT Lower Adult\n Switch with Bombs",            {"Disable", "Enable"}, {"", ""});
  Option LogicSpiritChildBombchu          = Option::Bool("SpT Child Side Bridge\n with Bombchu",           {"Disable", "Enable"}, {"", ""});
  Option LogicSpiritWall                  = Option::Bool("SpT Shifting Wall w/\n No Additional Items",     {"Disable", "Enable"}, {"", ""});
  Option LogicSpiritLobbyGS               = Option::Bool("SpT Main Room GS with\n Boomerang",              {"Disable", "Enable"}, {"", ""});
  Option LogicSpiritMapChest              = Option::Bool("SpT Map Chest with\n Bow",                       {"Disable", "Enable"}, {"", ""}); //Needs Testing
  Option LogicSpiritSunChest              = Option::Bool("SpT Sun Block Room\n Chest with Bow",            {"Disable", "Enable"}, {"", ""}); //Needs Testing
  Option LogicShadowFireArrowEntry        = Option::Bool("ShT Entry with Fire\n Arrows",                   {"Disable", "Enable"}, {"", ""}); //Needs Testing
  Option LogicShadowUmbrella              = Option::Bool("ShT Stone Umbrella\n Skip",                      {"Disable", "Enable"}, {"", ""});
  Option LogicShadowFreestandingKey       = Option::Bool("ShT Freestanding Key\n with Bombchu",            {"Disable", "Enable"}, {"", ""});
  Option LogicShadowStatue                = Option::Bool("ShT River Statue with\n Bombchu",                {"Disable", "Enable"}, {"", ""});
  Option LogicBotwCageGS                  = Option::Bool("BotW Map Chest with\n Strength & Sticks",        {"Disable", "Enable"}, {"", ""}); //Needs Testing
  Option LogicChildDeadhand               = Option::Bool("Child Deadhand w/o\n Kokiri Sword",              {"Disable", "Enable"}, {"", ""});
  Option LogicGtgWithoutHookshot          = Option::Bool("GTG Left Side Silver\n Rupees w/o Hookshot",     {"Disable", "Enable"}, {"", ""});
  Option LogicGtgFakeWall                 = Option::Bool("GTG Fake Wall Ledge\n with Hover Boots",         {"Disable", "Enable"}, {"", ""});
  Option LogicLensSpirit                  = Option::Bool("SpT without Lens of\n Truth",                    {"Disable", "Enable"}, {"", ""});
  Option LogicLensShadow                  = Option::Bool("ShT before Invisible\n Moving Platform w/o Lens",{"Disable", "Enable"}, {"", ""});
  Option LogicLensShadowBack              = Option::Bool("ShT beyond Invisible\n Moving Platform w/o Lens",{"Disable", "Enable"}, {"", ""});
  Option LogicLensBotw                    = Option::Bool("BotW without Lens of\n Truth",                   {"Disable", "Enable"}, {"", ""});
  Option LogicLensGtg                     = Option::Bool("GTG without Lens of\n Truth",                    {"Disable", "Enable"}, {"", ""});
  Option LogicLensCastle                  = Option::Bool("Ganon's Castle w/o\n Lens of Truth",             {"Disable", "Enable"}, {"", ""});
  Option LogicSpiritTrialHookshot         = Option::Bool("Spirit Trial without\n Hookshot",                {"Disable", "Enable"}, {"", ""});
  std::vector<Option *> detailedLogicOptions = {
    &LogicGrottosWithoutAgony,
    &LogicVisibleCollision,
    &LogicFewerTunicRequirements,
    &LogicLostWoodsBridge,
    &LogicLostWoodsGSBean,
    &LogicLabDiving,
    &LogicLabWallGS,
    &LogicGraveyardPoH,
    &LogicChildDampeRacePoH,
    &LogicGerudoKitchen,
    &LogicLensWasteland,
    &LogicReverseWasteland,
    &LogicColossusGS,
    &LogicManOnRoof,
    &LogicKakarikoTowerGS,
    &LogicDMTBombable,
    &LogicDMTSoilGS,
    &LogicLinkGoronDins,
    &LogicGoronCityLeftMost,
    &LogicGoronCityPot,
    &LogicGoronCityPotWithStrength,
    &LogicChildRollingWithStrength,
    &LogicCraterUpperToLower,
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
    &LogicJabuBossGSAdult,
    &LogicJabuScrubJumpDive,
    &LogicForestOutsideBackdoor,
    &LogicForestDoorFrame,
    &LogicForestOutdoorEastGS,
    &LogicFireBossDoorJump,
    &LogicFireStrength,
    &LogicFireScarecrow,
    &LogicFireFlameMaze,
    &LogicFireSongOfTime,
    &LogicWaterHookshotEntry,
    &LogicWaterTempleTorchLongshot,
    &LogicWaterCentralBow,
    &LogicWaterCrackedWallNothing,
    &LogicWaterCrackedWallHovers,
    &LogicWaterBossKeyRegion,
    &LogicWaterBKJumpDive,
    &LogicWaterNorthBasementLedgeJump,
    //&LogicWaterDragonBombchu,
    &LogicWaterDragonJumpDive,
    &LogicWaterRiverGS,
    &LogicWaterFallingPlatformGS,
    &LogicSpiritLowerAdultSwitch,
    &LogicSpiritChildBombchu,
    &LogicSpiritWall,
    &LogicSpiritLobbyGS,
    &LogicSpiritMapChest,
    &LogicSpiritSunChest,
    &LogicShadowFireArrowEntry,
    &LogicShadowUmbrella,
    &LogicShadowFreestandingKey,
    &LogicShadowStatue,
    &LogicBotwCageGS,
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
  MenuItem advancedGlitchedSettings = MenuItem::SubMenu("Advanced Glitched Settings", &advancedGlitchedOptions);
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
    &advancedGlitchedSettings,
    &loadSettingsPreset,
    &saveSettingsPreset,
    &generateRandomizer,
  };

  //declared here, set in fill.cpp
  u32 LinksPocketRewardBitMask = 0;

  std::array<u32, 9> rDungeonRewardOverrides{};

  //Fills a SettingsContext struct which is sent to the patch
  SettingsContext FillContext() {
    SettingsContext ctx = {};
    ctx.logic              = Logic.Value<u8>();
    ctx.openForest         = OpenForest.Value<u8>();
    ctx.openKakariko       = OpenKakariko.Value<u8>();
    ctx.openDoorOfTime     = OpenDoorOfTime.Value<bool>();
    ctx.zorasFountain      = ZorasFountain.Value<u8>();
    ctx.gerudoFortress     = GerudoFortress.Value<u8>();
    ctx.rainbowBridge      = Bridge.Value<u8>();

    ctx.startingAge        = StartingAge.Value<u8>();
    ctx.bombchusInLogic    = BombchusInLogic.Value<bool>();
    ctx.randomMQDungeons   = RandomMQDungeons.Value<bool>();

    ctx.shuffleSongs       = ShuffleSongs.Value<u8>();
    ctx.tokensanity        = Tokensanity.Value<u8>();
    ctx.scrubsanity        = Scrubsanity.Value<u8>();
    ctx.shuffleKokiriSword = ShuffleKokiriSword.Value<bool>();
    ctx.shuffleOcarinas    = ShuffleOcarinas.Value<bool>();
    ctx.shuffleWeirdEgg    = ShuffleWeirdEgg.Value<bool>();
    ctx.shuffleGerudoToken = ShuffleGerudoToken.Value<bool>();
    ctx.shuffleMagicBeans  = ShuffleMagicBeans.Value<bool>();

    ctx.keysanity          = Keysanity.Value<u8>();
    ctx.bossKeysanity      = BossKeysanity.Value<u8>();
    ctx.ganonsBossKey      = GanonsBossKey.Value<u8>();
    ctx.mapsAndCompasses   = MapsAndCompasses.Value<u8>();
    ctx.lacsCondition      = LACSCondition;

    ctx.skipChildStealth   = SkipChildStealth.Value<u8>();
    ctx.fourPoesCutscene   = FourPoesCutscene.Value<bool>();
    ctx.bigPoeTargetCount  = BigPoeTargetCount.Value<u8>() + 1;

    ctx.damageMultiplier   = DamageMultiplier.Value<u8>();
    ctx.startingTime       = StartingTime.Value<u8>();

    ctx.boomerangAsAdult   = BoomerangAsAdult.Value<u8>();
    ctx.hammerAsChild      = HammerAsChild.Value<u8>();

    ctx.itemPoolValue      = ItemPoolValue.Value<u8>();

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

    for (u16 i = 0; i < detailedLogicOptions.size(); i++) {
      ctx.detailedLogic[i] = detailedLogicOptions[i]->GetSelectedOptionIndex();
    }

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

    StartingAge.SetSelectedIndex(ctx.startingAge);
    BombchusInLogic.SetSelectedIndex(ctx.bombchusInLogic);
    RandomMQDungeons.SetSelectedIndex(ctx.randomMQDungeons);

    ShuffleSongs.SetSelectedIndex(ctx.shuffleSongs);
    Tokensanity.SetSelectedIndex(ctx.tokensanity);
    Scrubsanity.SetSelectedIndex(ctx.scrubsanity);
    ShuffleKokiriSword.SetSelectedIndex(ctx.shuffleKokiriSword);
    ShuffleOcarinas.SetSelectedIndex(ctx.shuffleOcarinas);
    ShuffleWeirdEgg.SetSelectedIndex(ctx.shuffleWeirdEgg);
    ShuffleGerudoToken.SetSelectedIndex(ctx.shuffleGerudoToken);
    ShuffleMagicBeans.SetSelectedIndex(ctx.shuffleMagicBeans);

    Keysanity.SetSelectedIndex(ctx.keysanity);
    BossKeysanity.SetSelectedIndex(ctx.bossKeysanity);
    GanonsBossKey.SetSelectedIndex(ctx.ganonsBossKey);
    MapsAndCompasses.SetSelectedIndex(ctx.mapsAndCompasses);

    SkipChildStealth.SetSelectedIndex(ctx.skipChildStealth);
    FourPoesCutscene.SetSelectedIndex(ctx.fourPoesCutscene);
    BigPoeTargetCount.SetSelectedIndex(ctx.bigPoeTargetCount - 1);

    DamageMultiplier.SetSelectedIndex(ctx.damageMultiplier);
    StartingTime.SetSelectedIndex(ctx.startingTime);

    BoomerangAsAdult.SetSelectedIndex(ctx.boomerangAsAdult);
    HammerAsChild.SetSelectedIndex(ctx.hammerAsChild);

    ItemPoolValue.SetSelectedIndex(ctx.itemPoolValue);

    for (u16 i = 0; i < detailedLogicOptions.size(); i++) {
      detailedLogicOptions[i]->SetSelectedIndex(ctx.detailedLogic[i]);
    }

    for (u16 i = 0; i < excludeLocationsOptions.size(); i++) {
      excludeLocationsOptions[i]->SetSelectedIndex(ctx.excludeLocations[i]);
    }
  }

  bool BombchuDrop                      = false;
  bool SkippedTrials                    = false;
  bool ShuffleDungeonEntrances          = false;
  bool ShuffleOverworldEntrances        = false;
  bool ShuffleInteriorEntrances         = false;
  bool ShuffleSpecialIndoorEntrances    = false;
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

  //Function to set flags depending on settings
  void UpdateSettings() {

    //1 is MQ, 0 is Vanilla
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
