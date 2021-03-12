#include <unistd.h>

#include "settings.hpp"
#include "setting_descriptions.hpp"
#include "item_location.hpp"
#include "random.hpp"

namespace Settings {
  std::string seed;

  //                                        Setting name,              Options,                                                Setting Descriptions (assigned in setting_descriptions.cpp)
  //Open Settings
  Option Logic               = Option::U8  ("Logic",                  {"Glitchless", "No Logic"},                              {logicGlitchless, logicNoLogic});
  Option OpenForest          = Option::U8  ("Forest",                 {"Closed", "Open"},                                      {forestClosed, forestOpen});
  Option OpenKakariko        = Option::U8  ("Kakariko Gate",          {"Closed", "Open"},                                      {kakGateClosed, kakGateOpen});
  Option OpenDoorOfTime      = Option::Bool("Door of Time",           {"Closed", "Open"},                                      {doorOfTimeDesc, doorOfTimeDesc});
  Option ZorasFountain       = Option::U8  ("Zora's Fountain",        {"Normal", "Open"},                                      {fountainNormal, fountainOpen});
  Option GerudoFortress      = Option::U8  ("Gerudo Fortress",        {"Normal", "Fast", "Open"},                              {gerudoNormal, gerudoFast, gerudoOpen});
  Option Bridge              = Option::U8  ("Rainbow Bridge",         {"Open", "Vanilla", "Stones", "Medallions", "Dungeons", "Tokens"},
                                                                      {bridgeOpen, bridgeVanilla, bridgeStones, bridgeMedallions, bridgeDungeons, bridgeTokens});
  Option TokenCount          = Option::U8  ("Token Count",            {/*Options 0-100 defined in SetDefaultOptions()*/},      std::vector<std::string_view>{101, tokenCountDesc});
  std::vector<Option *> openOptions = {
    &Logic,
    &OpenForest,
    //&OpenKakariko,
    &OpenDoorOfTime,
    &ZorasFountain,
    &GerudoFortress,
    &Bridge,
    &TokenCount,
  };

  //World Settings
  Option StartingAge         = Option::U8  ("Starting Age",           {"Adult", "Child"},                                      {ageDesc, ageDesc});
  Option BombchusInLogic     = Option::Bool("Bombchus in Logic",      {"Off", "On"},                                           {bombchuLogicDesc, bombchuLogicDesc});
  Option BombchuDrops        = Option::Bool("Bombchu Drops",          {"Off", "On"},                                           {bombchuDropDesc, bombchuDropDesc});
  Option RandomMQDungeons    = Option::Bool("Random MQ Dungeons",     {"Off", "On"},                                           {randomMQDungeonsDesc, randomMQDungeonsDesc});
  Option MirrorWorld         = Option::Bool("Mirror World",           {"Off", "On"},                                           {mirrorWorldDesc, mirrorWorldDesc});
  std::vector<Option *> worldOptions = {
    &StartingAge,
    &BombchusInLogic,
    &BombchuDrops,
    //&RandomMQDungeons, TODO: Finish MQ logic before enabling this
    &MirrorWorld,
  };

  //Shuffle Settings
  Option ShuffleSongs        = Option::U8  ("Shuffle Songs",          {"Song Locations", "Anywhere"},                          {songsSongLocations, songsAllLocations}); //TODO: Dungeon Rewards
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
  Option GanonsBossKey       = Option::U8  ("Ganon's Boss Key",       {"Start With", "Vanilla", "Own Dungeon", "Anywhere", "LACS: Vanilla", "LACS: Medallions", "LACS: Stones", "LACS: Dungeons"},
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
  Option SkipChildStealth    = Option::Bool("Skip Child Sealth",      {"Don't Skip", "Skip"},                                  {childStealthDesc, childStealthDesc});
  Option FourPoesCutscene    = Option::Bool("Four Poes Cutscene",     {"Don't Skip", "Skip"},                                  {fourPoesDesc, fourPoesDesc});
  Option TempleOfTimeIntro   = Option::Bool("Temple of Time Intro",   {"Don't Skip", "Skip"},                                  {templeOfTimeIntroDesc, templeOfTimeIntroDesc});
  Option BigPoeTargetCount   = Option::U8  ("Big Poe Target Count",   {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"},     std::vector<std::string_view>{10, bigPoeTargetCountDesc});
  std::vector<Option *> timesaverOptions = {
    &SkipChildStealth,
    &FourPoesCutscene,
    &TempleOfTimeIntro,
    &BigPoeTargetCount,
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

  //Detailed Logic Tricks                                 ---------------------
  Option ToggleAllDetailedLogic           = Option::Bool("All Tricks",                                     {"Disable", "Enable"}, std::vector<std::string_view>{2, ToggleAllDetailedLogicDesc});
  Option LogicGrottosWithoutAgony         = Option::Bool("Grottos Without Agony",                          {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicGrottosWithoutAgonyDesc});
  Option LogicVisibleCollision            = Option::Bool("Pass Through Visible\n One-Way Collisions",      {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicVisibleCollisionDesc});
  Option LogicFewerTunicRequirements      = Option::Bool("Fewer Tunic\n Requirements",                     {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicFewerTunicRequirementsDesc});
  Option LogicLostWoodsGSBean             = Option::Bool("Lost Woods Adult GS\n without Bean",             {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicLostWoodsGSBeanDesc});
  Option LogicLabDiving                   = Option::Bool("Lake Hylia Lab Dive\n without Gold Scale",       {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicLabDivingDesc});
  Option LogicLabWallGS                   = Option::Bool("Lake Hylia Lab Wall\n GS with Jump Slash",       {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicLabWallGSDesc});
  Option LogicGraveyardPoH                = Option::Bool("Graveyard Freestanding\n PoH with Boomerang",    {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicGraveyardPoHDesc});
  Option LogicChildDampeRacePoH           = Option::Bool("Second Dampe Race as\n Child",                   {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicChildDampeRacePoHDesc});
  Option LogicGerudoKitchen               = Option::Bool("Gerudo Fortress\n Kitchen with No Items",        {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicGerudoKitchenDesc});
  Option LogicLensWasteland               = Option::Bool("Lensless Wasteland",                             {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicLensWastelandDesc});
  Option LogicReverseWasteland            = Option::Bool("Reverse Wasteland",                              {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicReverseWastelandDesc});
  Option LogicColossusGS                  = Option::Bool("Colossus Hill GS\n with Hookshot",               {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicColossusGSDesc});
  Option LogicOutsideGanonsGS             = Option::Bool("OGC GS with No Items",                           {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicOutsideGanonsGSDesc});
  Option LogicManOnRoof                   = Option::Bool("Man on Roof without\n Hookshot",                 {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicManOnRoofDesc});
  Option LogicDMTBombable                 = Option::Bool("Death Mountain Trail\n Chest with Strength",     {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicDMTBombableDesc});
  Option LogicDMTSoilGS                   = Option::Bool("DMT Soil GS without\n Destroying Boulder",       {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicDMTSoilGSDesc});
  Option LogicLinkGoronDins               = Option::Bool("Stop Link the Goron\n with Din's Fire",          {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicLinkGoronDinsDesc});
  Option LogicGoronCityLeftMost           = Option::Bool("Goron City Maze Left\n Chest with Hover Boots",  {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicGoronCityLeftMostDesc});
  Option LogicGoronCityPot                = Option::Bool("Goron City Spinning\n Pot PoH with Bombchu",     {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicGoronCityPotDesc}); //Needs Testing
  Option LogicGoronCityPotWithStrength    = Option::Bool("Goron City Spinning\n Pot PoH with Strength",    {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicGoronCityPotWithStrengthDesc});
  Option LogicChildRollingWithStrength    = Option::Bool("Rolling Goron as\n Child with Strength",         {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicChildRollingWithStrengthDesc});
  Option LogicCraterUpperToLower          = Option::Bool("Crater Upper to Lower\n with Hammer",            {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicCraterUpperToLowerDesc}); //Needs Testing
  Option LogicCraterBeanPoHWithHovers     = Option::Bool("Crater's Bean PoH\n with Hover Boots",           {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicCraterBeanPoHWithHoversDesc});
  Option LogicBiggoronBolero              = Option::Bool("Deliver Eye Drops\n with Bolero of Fire",        {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicBiggoronBoleroDesc});
  Option LogicZoraRiverLower              = Option::Bool("Zora's River Lower\n PoH with Nothing",          {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicZoraRiverLowerDesc});
  Option LogicZoraRiverUpper              = Option::Bool("Zora's River Upper\n PoH with Nothing",          {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicZoraRiverUpperDesc});
  Option LogicDekuB1WebsWithBow           = Option::Bool("Deku Tree Basement\n Web with Bow",              {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicDekuB1WebsWithBowDesc});
  Option LogicDekuB1Skip                  = Option::Bool("Deku Tree Basement\n without Slingshot",         {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicDekuB1SkipDesc});
  Option LogicDekuBasementGS              = Option::Bool("Deku Tree Basement\n Vines GS w/ Jump Slash",    {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicDekuBasementGSDesc});
  Option LogicDCStaircase                 = Option::Bool("Dodongo's Cavern\n Staircase with Bow",          {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicDCStaircaseDesc});
  Option LogicDCJump                      = Option::Bool("DC Spike Trap room\n Jump w/o Hover Boots",      {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicDCJumpDesc});
  Option LogicDCSlingshotSkip             = Option::Bool("DC Child Slingshot\n Skips",                     {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicDCSlingshotSkipDesc});
  Option LogicDCScarecrowGS               = Option::Bool("DC Scarecrow GS with\n Armos Statue",            {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicDCScarecrowGSDesc});
  Option LogicJabuBossGSAdult             = Option::Bool("Jabu Near Boss GS as\n Adult w/o Boomerang",     {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicJabuBossGSAdultDesc}); //Needs Testing
  Option LogicJabuScrubJumpDive           = Option::Bool("Jabu Scrub as Adult\n w/ Jump Dive",             {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicJabuScrubJumpDiveDesc}); //Needs Testing
  Option LogicForestOutsideBackdoor       = Option::Bool("FoT Outisde Backdoor\n w/ Jump Slash",           {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicForestOutsideBackdoorDesc}); //Needs Testing
  Option LogicForestDoorFrame             = Option::Bool("FoT East Courtyard\n Door Frame w/ Hover Boots", {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicForestDoorFrameDesc}); //Needs Testing
  Option LogicForestOutdoorEastGS         = Option::Bool("FoT East Courtyard GS\n with Boomerang",         {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicForestOutdoorEastGSDesc});
  Option LogicFireBossDoorJump            = Option::Bool("FiT Boss Door without\n Hover Boots or Pillar",  {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicFireBossDoorJumpDesc});
  Option LogicFireStrength                = Option::Bool("FiT Climb without\n Strength",                   {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicFireStrengthDesc});
  Option LogicFireScarecrow               = Option::Bool("FiT East Tower w/o\n Scarecrow\'s Song",         {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicFireScarecrowDesc});
  Option LogicFireFlameMaze               = Option::Bool("FiT Flame Wall Maze\n Skip",                     {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicFireFlameMazeDesc});
  Option LogicFireSongOfTime              = Option::Bool("FiT Song of Time Room\n GS w/o Song of Time",    {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicFireSongOfTimeDesc});
  Option LogicWaterTempleTorchLongshot    = Option::Bool("WaT Torch Longshot",                             {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicWaterTempleTorchLongshotDesc});
  Option LogicWaterCentralBow             = Option::Bool("WaT Bow Target w/o\n Longshot or Hover Boots",   {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicWaterCentralBowDesc});
  Option LogicWaterCentralGSFW            = Option::Bool("WaT Central Pillar GS\n with Farore's Wind",     {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicWaterCentralGSFWDesc});
  Option LogicWaterCrackedWallNothing     = Option::Bool("WaT Cracked Wall with\n No Additional Items",    {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicWaterCrackedWallNothingDesc});
  Option LogicWaterCrackedWallHovers      = Option::Bool("WaT Cracked Wall with\n Hover Boots",            {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicWaterCrackedWallHoversDesc});
  Option LogicWaterBossKeyRegion          = Option::Bool("WaT Boss Key Region\n with Hover Boots",         {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicWaterBossKeyRegionDesc});
  Option LogicWaterBKJumpDive             = Option::Bool("WaT Boss Key Jump\n Dive",                       {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicWaterBKJumpDiveDesc});
  Option LogicWaterNorthBasementLedgeJump = Option::Bool("WaT North Basement\n Ledge with Precise Jump",   {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicWaterNorthBasementLedgeJumpDesc});
  Option LogicWaterDragonAdult            = Option::Bool("WaT Dragon Statue\n Jump Dive",                  {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicWaterDragonAdultDesc});
  Option LogicWaterDragonJumpDive         = Option::Bool("WaT Dragon Statue\n Switch Above as Adult",      {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicWaterDragonJumpDiveDesc});
  Option LogicWaterRiverGS                = Option::Bool("WaT River GS without\n Iron Boots",              {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicWaterRiverGSDesc});
  Option LogicWaterFallingPlatformGS      = Option::Bool("WaT Falling Platform\n Room GS with Hookshot",   {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicWaterFallingPlatformGSDesc});
  Option LogicSpiritLowerAdultSwitch      = Option::Bool("SpT Lower Adult\n Switch with Bombs",            {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicSpiritLowerAdultSwitchDesc});
  Option LogicSpiritChildBombchu          = Option::Bool("SpT Child Side Bridge\n with Bombchu",           {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicSpiritChildBombchuDesc});
  Option LogicSpiritWall                  = Option::Bool("SpT Shifting Wall w/\n No Additional Items",     {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicSpiritWallDesc});
  Option LogicSpiritLobbyGS               = Option::Bool("SpT Main Room GS with\n Boomerang",              {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicSpiritLobbyGSDesc});
  Option LogicSpiritMapChest              = Option::Bool("SpT Map Chest with\n Bow",                       {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicSpiritMapChestDesc});
  Option LogicSpiritSunChest              = Option::Bool("SpT Sun Block Room\n Chest with Bow",            {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicSpiritSunChestDesc}); //Needs Testing
  Option LogicShadowFireArrowEntry        = Option::Bool("ShT Entry with Fire\n Arrows",                   {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicShadowFireArrowEntryDesc}); //Needs Testing
  Option LogicShadowUmbrella              = Option::Bool("ShT Stone Umbrella\n Skip",                      {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicShadowUmbrellaDesc});
  Option LogicShadowFreestandingKey       = Option::Bool("ShT Freestanding Key\n with Bombchu",            {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicShadowFreestandingKeyDesc});
  Option LogicShadowStatue                = Option::Bool("ShT River Statue with\n Bombchu",                {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicShadowStatueDesc});
  Option LogicChildDeadhand               = Option::Bool("Child Deadhand w/o\n Kokiri Sword",              {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicChildDeadhandDesc});
  Option LogicGtgWithoutHookshot          = Option::Bool("GTG Left Side Silver\n Rupees w/o Hookshot",     {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicGtgWithoutHookshotDesc});
  Option LogicGtgFakeWall                 = Option::Bool("GTG Fake Wall Ledge\n with Hover Boots",         {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicGtgFakeWallDesc});
  Option LogicLensSpirit                  = Option::Bool("SpT without Lens of\n Truth",                    {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicLensSpiritDesc});
  Option LogicLensShadow                  = Option::Bool("ShT before Invisible\n Moving Platform w/o Lens",{"Disable", "Enable"}, std::vector<std::string_view>{2, LogicLensShadowDesc});
  Option LogicLensShadowBack              = Option::Bool("ShT beyond Invisible\n Moving Platform w/o Lens",{"Disable", "Enable"}, std::vector<std::string_view>{2, LogicLensShadowBackDesc});
  Option LogicLensBotw                    = Option::Bool("BotW without Lens of\n Truth",                   {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicLensBotwDesc});
  Option LogicLensGtg                     = Option::Bool("GTG without Lens of\n Truth",                    {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicLensGtgDesc});
  Option LogicLensCastle                  = Option::Bool("Ganon's Castle w/o\n Lens of Truth",             {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicLensCastleDesc});
  Option LogicSpiritTrialHookshot         = Option::Bool("Spirit Trial without\n Hookshot",                {"Disable", "Enable"}, std::vector<std::string_view>{2, LogicSpiritTrialHookshotDesc});
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
    ctx.logic              = Logic.Value<u8>();
    ctx.openForest         = OpenForest.Value<u8>();
    ctx.openKakariko       = OpenKakariko.Value<u8>();
    ctx.openDoorOfTime     = (OpenDoorOfTime) ? 1 : 0;
    ctx.zorasFountain      = ZorasFountain.Value<u8>();
    ctx.gerudoFortress     = GerudoFortress.Value<u8>();
    ctx.rainbowBridge      = Bridge.Value<u8>();
    ctx.tokenCount         = TokenCount.Value<u8>();

    ctx.startingAge        = StartingAge.Value<u8>();
    ctx.bombchusInLogic    = (BombchusInLogic) ? 1 : 0;
    ctx.bombchuDrops       = (BombchuDrops) ? 1 : 0;
    ctx.randomMQDungeons   = (RandomMQDungeons) ? 1 : 0;
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
    ctx.fourPoesCutscene   = (FourPoesCutscene) ? 1 : 0;
    ctx.templeOfTimeIntro  = (TempleOfTimeIntro) ? 1 : 0;
    ctx.bigPoeTargetCount  = BigPoeTargetCount.Value<u8>() + 1;

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
    TokenCount.SetSelectedIndex(ctx.tokenCount);

    StartingAge.SetSelectedIndex(ctx.startingAge);
    BombchusInLogic.SetSelectedIndex(ctx.bombchusInLogic);
    BombchuDrops.SetSelectedIndex(ctx.bombchuDrops);
    RandomMQDungeons.SetSelectedIndex(ctx.randomMQDungeons);
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
    FourPoesCutscene.SetSelectedIndex(ctx.fourPoesCutscene);
    TempleOfTimeIntro.SetSelectedIndex(ctx.templeOfTimeIntro);
    BigPoeTargetCount.SetSelectedIndex(ctx.bigPoeTargetCount - 1);

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
    TokenCount.Hide();

    std::vector<std::string> tokenOptions = {};
    for (int i = 0; i <= 100; i++) {
      tokenOptions.push_back(std::to_string(i));
    }
    TokenCount.SetOptions(tokenOptions);
    TokenCount.SetSelectedIndex(1);

    StartingAge.SetSelectedIndex(AGE_CHILD);

    MapsAndCompasses.SetSelectedIndex(MAPSANDCOMPASSES_VANILLA);
    Keysanity.SetSelectedIndex(KEYSANITY_VANILLA);
    BossKeysanity.SetSelectedIndex(BOSSKEYSANITY_VANILLA);
    GanonsBossKey.SetSelectedIndex(GANONSBOSSKEY_VANILLA);

    AddExcludedOptions();

    DamageMultiplier.SetSelectedIndex(DAMAGEMULTIPLIER_DEFAULT);
    GenerateSpoilerLog.SetSelectedIndex(1); //true

    ItemPoolValue.SetSelectedIndex(ITEMPOOL_BALANCED);
    IceTrapValue.SetSelectedIndex(ICETRAPS_NORMAL);
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

    if (Bridge.Is(RAINBOWBRIDGE_TOKENS)) {
      TokenCount.Unhide();
    } else {
      TokenCount.Hide();
      TokenCount.SetSelectedIndex(1);
    }

    //Bombchus in Logic forces Bombchu Drops
    if (BombchusInLogic) {
      BombchuDrops.SetSelectedIndex(ON);
      BombchuDrops.Lock();
    } else {
      BombchuDrops.Unlock();
    }

    //Set toggle for all tricks
    if ((kDown & KEY_DLEFT || kDown & KEY_DRIGHT) && currentSetting->GetName() == "All Tricks")  {
      for (u16 i = 0; i < Settings::detailedLogicOptions.size(); i++) {
        detailedLogicOptions[i]->SetSelectedIndex(currentSetting->GetSelectedOptionIndex());
      }
    }
  }

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
  bool IceCavernDungeonMode             = false;
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
      IceCavernDungeonMode             = Random() % 2;
      GerudoTrainingGroundsDungeonMode = Random() % 2;
      GanonsCastleDungeonMode          = Random() % 2;
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
