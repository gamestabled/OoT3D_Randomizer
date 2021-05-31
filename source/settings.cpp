#include "settings.hpp"

#include <unistd.h>

#include "cosmetics.hpp"
#include "dungeon.hpp"
#include "fill.hpp"
#include "item_location.hpp"
#include "random.hpp"
#include "randomizer.hpp"
#include "setting_descriptions.hpp"
#include "trial.hpp"
#include "keys.hpp"

using namespace Cosmetics;
using namespace Dungeon;
using namespace Trial;

namespace Settings {
  std::string seed;
  std::string version = RANDOMIZER_VERSION "-COMMITNUM";
  std::array<u8, 5> hashIconIndexes;

  //                                        Setting name,              Options,                                                                     Setting Descriptions (assigned in setting_descriptions.cpp)
  //Open Settings                                                                                                                                   Any option index past the last description will use the last description
  Option Logic               = Option::U8  ("Logic",                  {"Glitchless", "No Logic"},                                                   {logicGlitchless, logicNoLogic});
  Option OpenForest          = Option::U8  ("Forest",                 {"Closed", "Open"},                                                           {forestClosed, forestOpen});
  Option OpenKakariko        = Option::U8  ("Kakariko Gate",          {"Closed", "Open"},                                                           {kakGateClosed, kakGateOpen});
  Option OpenDoorOfTime      = Option::Bool("Door of Time",           {"Closed", "Open"},                                                           {doorOfTimeDesc});
  Option ZorasFountain       = Option::U8  ("Zora's Fountain",        {"Normal", "Adult", "Open"},                                                  {fountainNormal, fountainAdult, fountainOpen});
  Option GerudoFortress      = Option::U8  ("Gerudo Fortress",        {"Normal", "Fast", "Open"},                                                   {gerudoNormal, gerudoFast, gerudoOpen});
  Option Bridge              = Option::U8  ("Rainbow Bridge",         {"Open", "Vanilla", "Stones", "Medallions", "Rewards", "Dungeons", "Tokens"}, {bridgeOpen, bridgeVanilla, bridgeStones, bridgeMedallions, bridgeRewards, bridgeDungeons, bridgeTokens});
  Option BridgeStoneCount    = Option::U8  ("  Stone Count",          {"0", "1", "2", "3"},                                                         {bridgeStoneCountDesc});
  Option BridgeMedallionCount= Option::U8  ("  Medallion Count",      {"0", "1", "2", "3", "4", "5", "6"},                                          {bridgeMedallionCountDesc});
  Option BridgeRewardCount   = Option::U8  ("  Reward Count",         {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"},                           {bridgeRewardCountDesc});
  Option BridgeDungeonCount  = Option::U8  ("  Dungeon Count",        {"0", "1", "2", "3", "4", "5", "6", "7", "8"},                                {bridgeDungeonCountDesc});
  Option BridgeTokenCount    = Option::U8  ("  Token Count",          {/*Options 0-100 defined in SetDefaultSettings()*/},                          {bridgeTokenCountDesc});
  Option RandomGanonsTrials  = Option::Bool("Random Ganon's Trials",  {"Off", "On"},                                                                {randomGanonsTrialsDesc});
  Option GanonsTrialsCount   = Option::U8  ("  Trial Count",          {"0", "1", "2", "3", "4", "5", "6"},                                          {ganonsTrialCountDesc});
  std::vector<Option *> openOptions = {
    &Logic,
    &OpenForest,
    //&OpenKakariko,
    &OpenDoorOfTime,
    &ZorasFountain,
    &GerudoFortress,
    &Bridge,
    &BridgeStoneCount,
    &BridgeMedallionCount,
    &BridgeRewardCount,
    &BridgeDungeonCount,
    &BridgeTokenCount,
    &RandomGanonsTrials,
    &GanonsTrialsCount,
  };

  //World Settings
  Option StartingAge         = Option::U8  ("Starting Age",           {"Adult", "Child", "Random"},                                      {ageDesc});
  u8 ResolvedStartingAge;
  Option BombchusInLogic     = Option::Bool("Bombchus in Logic",      {"Off", "On"},                                                     {bombchuLogicDesc});
  Option BombchuDrops        = Option::Bool("Bombchu Drops",          {"Off", "On"},                                                     {bombchuDropDesc});
  Option RandomMQDungeons    = Option::Bool("Random MQ Dungeons",     {"Off", "On"},                                                     {randomMQDungeonsDesc});
  Option MQDungeonCount      = Option::U8  ("  MQ Dungeon Count",     {"0","1","2","3","4","5","6","7","8","9","10","11","12"},          {mqDungeonCountDesc});
  std::vector<Option *> worldOptions = {
    &StartingAge,
    &BombchusInLogic,
    &BombchuDrops,
    &RandomMQDungeons,
    &MQDungeonCount,
  };

  //Shuffle Settings
  Option ShuffleRewards      = Option::U8  ("Shuffle Dungeon Rewards",{"End of Dungeons", "Any Dungeon", "Overworld", "Anywhere"},       {shuffleRewardsEndOfDungeon, shuffleRewardsAnyDungeon, shuffleRewardsOverworld, shuffleRewardsAnywhere});
  Option LinksPocketItem     = Option::U8  ("Link's Pocket",          {"Dungeon Reward", "Advancement", "Anything", "Nothing"},          {linksPocketDungeonReward, linksPocketAdvancement, linksPocketAnything, linksPocketNothing});
  Option ShuffleSongs        = Option::U8  ("Shuffle Songs",          {"Song Locations", "Dungeon Rewards", "Anywhere"},                 {songsSongLocations, songsDungeonRewards, songsAllLocations});
  Option Shopsanity          = Option::U8  ("Shopsanity",             {"Off", "0", "1", "2", "3", "4", "Random"},                        {shopsOff, shopsZero, shopsOne, shopsTwo, shopsThree, shopsFour, shopsRandom});
  Option Tokensanity         = Option::U8  ("Tokensanity",            {"Off", "Dungeons", "Overworld", "All Tokens"},                    {tokensOff, tokensDungeon, tokensOverworld, tokensAllTokens});
  Option Scrubsanity         = Option::U8  ("Scrub Shuffle",          {"Off", "Affordable", "Expensive", "Random Prices"},               {scrubsOff, scrubsAffordable, scrubsExpensive, scrubsRandomPrices});
  Option ShuffleCows         = Option::Bool("Shuffle Cows",           {"Off", "On"},                                                     {shuffleCowsDesc});
  Option ShuffleKokiriSword  = Option::Bool("Shuffle Kokiri Sword",   {"Off", "On"},                                                     {kokiriSwordDesc});
  Option ShuffleOcarinas     = Option::Bool("Shuffle Ocarinas",       {"Off", "On"},                                                     {ocarinasDesc});
  Option ShuffleWeirdEgg     = Option::Bool("Shuffle Weird Egg",      {"Off", "On"},                                                     {weirdEggDesc});
  Option ShuffleGerudoToken  = Option::Bool("Shuffle Gerudo Token",   {"Off", "On"},                                                     {gerudoTokenDesc});
  Option ShuffleMagicBeans   = Option::Bool("Shuffle Magic Beans",    {"Off", "On"},                                                     {magicBeansDesc});
  //TODO: Medigoron and Carpet Salesman
  std::vector<Option *> shuffleOptions = {
    &ShuffleRewards,
    &LinksPocketItem,
    &ShuffleSongs,
    &Shopsanity,
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
  Option MapsAndCompasses    = Option::U8  ("Maps/Compasses",         {"Start With", "Vanilla", "Own Dungeon", "Any Dungeon", "Overworld", "Anywhere"},
                                                                      {mapCompassStartWith, mapCompassVanilla, mapCompassOwnDungeon, mapCompassAnyDungeon, mapCompassOverworld, mapCompassAnywhere});
  Option Keysanity           = Option::U8  ("Small Keys",             {"Start With", "Vanilla", "Own Dungeon", "Any Dungeon", "Overworld", "Anywhere"},
                                                                      {smallKeyStartWith, smallKeyVanilla, smallKeyOwnDungeon, smallKeyAnyDungeon, smallKeyOverworld, smallKeyAnywhere});
  Option GerudoKeys          = Option::U8  ("Gerudo Fortress Keys",   {"Vanilla", "Any Dungeon", "Overworld", "Anywhere"},
                                                                      {gerudoKeysVanilla, gerudoKeysAnyDungeon, gerudoKeysOverworld, gerudoKeysAnywhere});
  Option BossKeysanity       = Option::U8  ("Boss Keys",              {"Start With", "Vanilla", "Own Dungeon", "Any Dungeon", "Overworld", "Anywhere"},
                                                                      {bossKeyStartWith, bossKeyVanilla, bossKeyOwnDungeon, bossKeyAnyDungeon, bossKeyOverworld, bossKeyAnywhere});
  Option GanonsBossKey       = Option::U8  ("Ganon's Boss Key",       {"Start With", "Vanilla", "Own Dungeon", "Any Dungeon", "Overworld", "Anywhere", "LACS-Vanilla", "LACS-Medallions", "LACS-Stones", "LACS-Rewards", "LACS-Dungeons", "LACS-Tokens"},
                                                                      {ganonKeyStartWith, ganonKeyVanilla, ganonKeyOwnDungeon, ganonKeyAnyDungeon, ganonKeyOverworld, ganonKeyAnywhere, ganonKeyLACS});
  u8 LACSCondition           = 0;
  Option LACSMedallionCount  = Option::U8  ("  Medallion Count",      {"0", "1", "2", "3", "4", "5", "6"},                                    {lacsMedallionCountDesc});
  Option LACSStoneCount      = Option::U8  ("  Stone Count",          {"0", "1", "2", "3"},                                                   {lacsStoneCountDesc});
  Option LACSRewardCount     = Option::U8  ("  Reward Count",         {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"},                     {lacsRewardCountDesc});
  Option LACSDungeonCount    = Option::U8  ("  Dungeon Count",        {"0", "1", "2", "3", "4", "5", "6", "7", "8"},                          {lacsDungeonCountDesc});
  Option LACSTokenCount      = Option::U8  ("  Token Count",          {/*Options 0-100 defined in SetDefaultSettings()*/},                    {lacsTokenCountDesc});
  std::vector<Option *> shuffleDungeonItemOptions = {
    &MapsAndCompasses,
    &Keysanity,
    &GerudoKeys,
    &BossKeysanity,
    &GanonsBossKey,
    &LACSMedallionCount,
    &LACSStoneCount,
    &LACSRewardCount,
    &LACSDungeonCount,
    &LACSTokenCount,
  };

  //Timesaver Settings
  Option SkipChildStealth    = Option::Bool("Skip Child Stealth",     {"Don't Skip", "Skip"},                                                 {childStealthDesc});
  Option SkipTowerEscape     = Option::Bool("Skip Tower Escape",      {"Don't Skip", "Skip"},                                                 {skipTowerEscapeDesc});
  Option SkipEponaRace       = Option::Bool("Skip Epona Race",        {"Don't Skip", "Skip"},                                                 {skipEponaRaceDesc});
  Option SkipMinigamePhases  = Option::Bool("Minigames repetitions",  {"Don't Skip", "Skip"},                                                 {skipMinigamePhasesDesc});
  Option FreeScarecrow       = Option::Bool("Free Scarecrow",         {"Off", "On"},                                                          {freeScarecrowDesc});
  Option FourPoesCutscene    = Option::Bool("Four Poes Cutscene",     {"Don't Skip", "Skip"},                                                 {fourPoesDesc});
  Option TempleOfTimeIntro   = Option::Bool("Temple of Time Intro",   {"Don't Skip", "Skip"},                                                 {templeOfTimeIntroDesc});
  Option BigPoeTargetCount   = Option::U8  ("Big Poe Target Count",   {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"},                    {bigPoeTargetCountDesc});
  Option NumRequiredCuccos   = Option::U8  ("Cuccos to return",       {"0", "1", "2", "3", "4", "5", "6", "7"},                               {numRequiredCuccosDesc});
  std::vector<Option *> timesaverOptions = {
    &SkipChildStealth,
    &SkipTowerEscape,
    &SkipEponaRace,
    &SkipMinigamePhases,
    &FreeScarecrow,
    &FourPoesCutscene,
    &TempleOfTimeIntro,
    &BigPoeTargetCount,
    &NumRequiredCuccos,
  };

  //Misc Settings
  Option GossipStoneHints    = Option::U8  ("Gossip Stone Hints",     {"No Hints", "Need Nothing", "Mask of Truth", "Shard of Agony"},        {gossipStonesHintsDesc});
  Option ClearerHints        = Option::Bool("  Clearer Hints",        {"Off", "On"},                                                          {clearerHintsDesc});
  Option HintDistribution    = Option::U8  ("  Hint Distribution",    {"Useless", "Balanced", "Strong", "Very Strong"},                       {uselessHintsDesc, balancedHintsDesc, strongHintsDesc, veryStrongHintsDesc});
  Option DamageMultiplier    = Option::U8  ("Damage Multiplier",      {"Half", "Default", "Double", "Quadruple", "OHKO"},                     {damageMultiDesc});
  Option StartingTime        = Option::U8  ("Starting Time",          {"Day", "Night"},                                                       {startingTimeDesc});
  Option NightGSExpectSuns   = Option::Bool("Night GSs Expect Sun's", {"Off", "On"},                                                          {nightGSDesc});
  Option ChestAnimations     = Option::Bool("Chest Animations",       {"Always Fast", "Match Contents"},                                      {chestAnimDesc});
  Option ChestSize           = Option::Bool("Chest Size and Color",   {"Vanilla", "Match Contents"},                                          {chestSizeDesc});
  Option GenerateSpoilerLog  = Option::Bool("Generate Spoiler Log",   {"No", "Yes"},                                                          {"", ""});
  Option MenuOpeningButton   = Option::U8  ("Open Info Menu with",    {"Select","Start","D-Pad Up","D-Pad Down","D-Pad Right","D-Pad Left",}, {menuButtonDesc});
  bool HasNightStart         = false;
  std::vector<Option *> miscOptions = {
    &GossipStoneHints,
    &ClearerHints,
    &HintDistribution,
    &DamageMultiplier,
    &StartingTime,
    &NightGSExpectSuns,
    &ChestAnimations,
    &ChestSize,
    &GenerateSpoilerLog,
    &MenuOpeningButton,
  };

  //Item Usability Settings
  Option StickAsAdult        = Option::Bool("Adult Deku Stick",       {"Disabled", "Enabled"},                                                {adultStickDesc});
  Option BoomerangAsAdult    = Option::Bool("Adult Boomerang",        {"Disabled", "Enabled"},                                                {adultBoomerangDesc});
  Option HammerAsChild       = Option::Bool("Child Hammer",           {"Disabled", "Enabled"},                                                {childHammerDesc});
  std::vector<Option *> itemUsabilityOptions = {
    &StickAsAdult,
    &BoomerangAsAdult,
    &HammerAsChild,
  };

  //Item Pool Settings
  Option ItemPoolValue       = Option::U8  ("Item Pool",              {"Plentiful", "Balanced", "Scarce", "Minimal"},                         {itemPoolPlentiful, itemPoolBalanced, itemPoolScarce, itemPoolMinimal});
  Option IceTrapValue        = Option::U8  ("Ice Traps",              {"Off", "Normal", "Extra", "Mayhem", "Onslaught"},                      {iceTrapsOff, iceTrapsNormal, iceTrapsExtra, iceTrapsMayhem, iceTrapsOnslaught});
  std::vector<Option *> itemPoolOptions = {
    &ItemPoolValue,
    &IceTrapValue,
  };

  //Excluded Locations (Individual definitions made in ItemLocation class)
  std::vector<Option *> excludeLocationsOptions = {};

  std::vector<std::string> bottleOptions = {"None", "Empty Bottle", "Red Potion", "Green Potion", "Blue Potion", "Fairy", "Fish", "Milk", "Blue Fire", "Bugs", "Big Poe", "Half Milk", "Poe"};
  Option StartingItemsToggle      = Option::Bool("All Items Toggle",       {"None", "All"},                                                        {"Toggle all items at once."}, OptionCategory::Toggle);
  Option StartingConsumables      = Option::Bool("Start with Consumables", {"No", "Yes"},                                                          {startWithConsumablesDesc});
  Option StartingMaxRupees        = Option::Bool("Start with Max Rupees",  {"No", "Yes"},                                                          {startWithMaxRupeesDesc});
  Option StartingStickCapacity    = Option::U8  ("Deku Stick Capacity",    {"10 (default)", "20 Deku Sticks", "30 Deku Sticks"},                   {""});
  Option StartingNutCapacity      = Option::U8  ("Deku Nut Capacity",      {"20 (default)", "30 Deku Nuts", "40 Deku Nuts"},                       {""});
  Option StartingBombBag          = Option::U8  ("Bomb Bag",               {"None", "Bomb Bag 20", "Bomb Bag 30", "Bomb Bag 40"},                  {""});
  Option StartingBombchus         = Option::U8  ("Bombchus",               {"None", "Bombchus"},                                                   {""});
  Option StartingBow              = Option::U8  ("Bow",                    {"None", "Bow + Quiver 30", "Bow + Quiver 40", "Bow + Quiver 50"},      {""});
  Option StartingFireArrows       = Option::U8  ("Fire Arrows",            {"None", "Fire Arrows"},                                                {""});
  Option StartingIceArrows        = Option::U8  ("Ice Arrows",             {"None", "Ice Arrows"},                                                 {""});
  Option StartingLightArrows      = Option::U8  ("Light Arrows",           {"None", "Light Arrows"},                                               {""});
  Option StartingDinsFire         = Option::U8  ("Din's Fire",             {"None", "Din's Fire"},                                                 {""});
  Option StartingFaroresWind      = Option::U8  ("Farore's Wind",          {"None", "Farore's Wind"},                                              {""});
  Option StartingNayrusLove       = Option::U8  ("Nayru's Love",           {"None", "Nayru's Love"},                                               {""});
  Option StartingSlingshot        = Option::U8  ("Slingshot",              {"None", "Slingshot 30", "Slingshot 40", "Slingshot 50"},               {""});
  Option StartingBoomerang        = Option::U8  ("Boomerang",              {"None", "Boomerang"},                                                  {""});
  Option StartingLensOfTruth      = Option::U8  ("Lens of Truth",          {"None", "Lens of Truth"},                                              {""});
  Option StartingMagicBean        = Option::U8  ("Magic Beans",            {"None", "Magic Beans"},                                                {""});
  Option StartingMegatonHammer    = Option::U8  ("Megaton Hammer",         {"None", "Megaton Hammer"},                                             {""});
  Option StartingHookshot         = Option::U8  ("Hookshot",               {"None", "Hookshot", "Longshot"},                                       {""});
  Option StartingIronBoots        = Option::U8  ("Iron Boots",             {"None", "Iron Boots"},                                                 {""});
  Option StartingHoverBoots       = Option::U8  ("Hover Boots",            {"None", "Hover Boots"},                                                {""});
  Option StartingBottle1          = Option::U8  ("Bottle Slot 1",          bottleOptions,                                                          {""});
  Option StartingBottle2          = Option::U8  ("Bottle Slot 2",          bottleOptions,                                                          {""});
  Option StartingBottle3          = Option::U8  ("Bottle Slot 3",          bottleOptions,                                                          {""});
  Option StartingRutoBottle       = Option::U8  ("Ruto's Letter",          {"None", "Ruto's Letter"},                                              {""});
  Option StartingOcarina          = Option::U8  ("Ocarina",                {"None", "Fairy Ocarina", "Ocarina of Time"},                           {""});
  Option StartingZeldasLullaby    = Option::U8  ("Zelda's Lullaby",        {"None", "Zelda's Lullaby"},                                            {""});
  Option StartingEponasSong       = Option::U8  ("Epona's Song",           {"None", "Epona's Song"},                                               {""});
  Option StartingSariasSong       = Option::U8  ("Saria's Song",           {"None", "Saria's Song"},                                               {""});
  Option StartingSunsSong         = Option::U8  ("Sun's Song",             {"None", "Sun's Song"},                                                 {""});
  Option StartingSongOfTime       = Option::U8  ("Song of Time",           {"None", "Song of Time"},                                               {""});
  Option StartingSongOfStorms     = Option::U8  ("Song of Storms",         {"None", "Song of Storms"},                                             {""});
  Option StartingMinuetOfForest   = Option::U8  ("Minuet of Forest",       {"None", "Minuet"},                                                     {""});
  Option StartingBoleroOfFire     = Option::U8  ("Bolero of Fire",         {"None", "Bolero"},                                                     {""});
  Option StartingSerenadeOfWater  = Option::U8  ("Serenade of Water",      {"None", "Serenade"},                                                   {""});
  Option StartingRequiemOfSpirit  = Option::U8  ("Requiem of Spirit",      {"None", "Requiem"},                                                    {""});
  Option StartingNocturneOfShadow = Option::U8  ("Nocturne of Shadow",     {"None", "Nocturne"},                                                   {""});
  Option StartingPreludeOfLight   = Option::U8  ("Prelude of Light",       {"None", "Prelude"},                                                    {""});
  Option StartingKokiriSword      = Option::U8  ("Kokiri Sword",           {"None", "Kokiri Sword"},                                               {""});
  Option StartingBiggoronSword    = Option::U8  ("Biggoron Sword",         {"None", "Biggoron Sword"},                                             {""});
  Option StartingDekuShield       = Option::U8  ("Deku Shield",            {"None", "Deku Shield"},                                                {""});
  Option StartingHylianShield     = Option::U8  ("Hylian Shield",          {"None", "Hylian Shield"},                                              {""});
  Option StartingMirrorShield     = Option::U8  ("Mirror Shield",          {"None", "Mirror Shield"},                                              {""});
  Option StartingGoronTunic       = Option::U8  ("Goron Tunic",            {"None", "Goron Tunic"},                                                {""});
  Option StartingZoraTunic        = Option::U8  ("Zora Tunic",             {"None", "Zora Tunic"},                                                 {""});
  Option StartingMagicMeter       = Option::U8  ("Magic Meter",            {"None", "Single Magic", "Double Magic"},                               {""});
  Option StartingStrength         = Option::U8  ("Strength",               {"None", "Goron Bracelet", "Silver Gauntlets", "Gold Gauntlets"},       {""});
  Option StartingScale            = Option::U8  ("Scale",                  {"None", "Silver Scale", "Gold Scale"},                                 {""});
  Option StartingWallet           = Option::U8  ("Wallet",                 {"None", "Adult's Wallet", "Giant's Wallet", "Tycoon's Wallet"},        {""});
  Option StartingShardOfAgony     = Option::U8  ("Shard of Agony",         {"None", "Shard of Agony"},                                             {""});
  Option StartingDoubleDefense    = Option::U8  ("Double Defense",         {"None", "Double Defense"},                                             {""});
  std::vector<Option *> startingInventoryOptions = {
    &StartingItemsToggle,
    &StartingConsumables,
    &StartingMaxRupees,
    &StartingStickCapacity,
    &StartingNutCapacity,
    &StartingBombBag,
    &StartingBombchus,
    &StartingBow,
    &StartingFireArrows,
    &StartingIceArrows,
    &StartingLightArrows,
    &StartingDinsFire,
    &StartingFaroresWind,
    &StartingNayrusLove,
    &StartingSlingshot,
    &StartingBoomerang,
    &StartingLensOfTruth,
    &StartingMagicBean,
    &StartingMegatonHammer,
    &StartingHookshot,
    &StartingIronBoots,
    &StartingHoverBoots,
    &StartingBottle1,
    &StartingBottle2,
    &StartingBottle3,
    &StartingRutoBottle,
    &StartingOcarina,
    &StartingZeldasLullaby,
    &StartingEponasSong,
    &StartingSariasSong,
    &StartingSunsSong,
    &StartingSongOfTime,
    &StartingSongOfStorms,
    &StartingMinuetOfForest,
    &StartingBoleroOfFire,
    &StartingSerenadeOfWater,
    &StartingRequiemOfSpirit,
    &StartingNocturneOfShadow,
    &StartingPreludeOfLight,
    &StartingKokiriSword,
    &StartingBiggoronSword,
    &StartingDekuShield,
    &StartingHylianShield,
    &StartingMirrorShield,
    &StartingGoronTunic,
    &StartingZoraTunic,
    &StartingMagicMeter,
    &StartingStrength,
    &StartingScale,
    &StartingWallet,
    &StartingShardOfAgony,
    &StartingDoubleDefense,
  };

  //Function to make defining logic tricks easier to read
  Option LogicTrick(std::string setting, std::string_view description) {
    return Option::Bool(setting, {"Disabled", "Enabled"}, {description});
  }

  //Detailed Logic Tricks                               ---------------------
  Option ToggleAllDetailedLogic           = Option::Bool("All Tricks", {"Disabled", "Enabled"},              {"Toggle all tricks at once."}, OptionCategory::Toggle);
  Option LogicGrottosWithoutAgony         = LogicTrick("Grottos Without Agony",                              LogicGrottosWithoutAgonyDesc);
  Option LogicVisibleCollision            = LogicTrick("Pass Through Visible\n One-Way Collisions",          LogicVisibleCollisionDesc);
  Option LogicFewerTunicRequirements      = LogicTrick("Fewer Tunic\n Requirements",                         LogicFewerTunicRequirementsDesc);
  Option LogicLostWoodsGSBean             = LogicTrick("Lost Woods Adult GS\n without Bean",                 LogicLostWoodsGSBeanDesc);
  Option LogicLabDiving                   = LogicTrick("Lake Hylia Lab Dive\n without Gold Scale",           LogicLabDivingDesc);
  Option LogicLabWallGS                   = LogicTrick("Lake Hylia Lab Wall\n GS with Jump Slash",           LogicLabWallGSDesc);
  Option LogicGraveyardPoH                = LogicTrick("Graveyard Freestanding\n PoH with Boomerang",        LogicGraveyardPoHDesc);
  Option LogicChildDampeRacePoH           = LogicTrick("Second Dampe Race as\n Child",                       LogicChildDampeRacePoHDesc);
  Option LogicGerudoKitchen               = LogicTrick("Gerudo Fortress\n Kitchen with No Items",            LogicGerudoKitchenDesc);
  Option LogicLensWasteland               = LogicTrick("Lensless Wasteland",                                 LogicLensWastelandDesc);
  Option LogicReverseWasteland            = LogicTrick("Reverse Wasteland",                                  LogicReverseWastelandDesc);
  Option LogicColossusGS                  = LogicTrick("Colossus Hill GS\n with Hookshot",                   LogicColossusGSDesc);
  Option LogicOutsideGanonsGS             = LogicTrick("OGC GS with No Items",                               LogicOutsideGanonsGSDesc);
  Option LogicManOnRoof                   = LogicTrick("Man on Roof without\n Hookshot",                     LogicManOnRoofDesc);
  Option LogicDMTBombable                 = LogicTrick("Death Mountain Trail\n Chest with Strength",         LogicDMTBombableDesc);
  Option LogicDMTSoilGS                   = LogicTrick("DMT Soil GS without\n Destroying Boulder",           LogicDMTSoilGSDesc);
  Option LogicLinkGoronDins               = LogicTrick("Stop Link the Goron\n with Din's Fire",              LogicLinkGoronDinsDesc);
  Option LogicGoronCityLeftMost           = LogicTrick("Goron City Maze Left\n Chest with Hover Boots",      LogicGoronCityLeftMostDesc);
  Option LogicGoronCityPot                = LogicTrick("Goron City Spinning\n Pot PoH with Bombchu",         LogicGoronCityPotDesc); //Needs Testing
  Option LogicGoronCityPotWithStrength    = LogicTrick("Goron City Spinning\n Pot PoH with Strength",        LogicGoronCityPotWithStrengthDesc);
  Option LogicChildRollingWithStrength    = LogicTrick("Rolling Goron as\n Child with Strength",             LogicChildRollingWithStrengthDesc);
  Option LogicCraterUpperToLower          = LogicTrick("Crater Upper to Lower\n with Hammer",                LogicCraterUpperToLowerDesc); //Needs Testing
  Option LogicCraterBeanPoHWithHovers     = LogicTrick("Crater's Bean PoH\n with Hover Boots",               LogicCraterBeanPoHWithHoversDesc);
  Option LogicBiggoronBolero              = LogicTrick("Deliver Eye Drops\n with Bolero of Fire",            LogicBiggoronBoleroDesc);
  Option LogicZoraRiverLower              = LogicTrick("Zora's River Lower\n PoH with Nothing",              LogicZoraRiverLowerDesc);
  Option LogicZoraRiverUpper              = LogicTrick("Zora's River Upper\n PoH with Nothing",              LogicZoraRiverUpperDesc);
  Option LogicDekuB1WebsWithBow           = LogicTrick("Deku Tree Basement\n Web with Bow",                  LogicDekuB1WebsWithBowDesc);
  Option LogicDekuB1Skip                  = LogicTrick("Deku Tree Basement\n without Slingshot",             LogicDekuB1SkipDesc);
  Option LogicDekuBasementGS              = LogicTrick("Deku Tree Basement\n Vines GS w/ Jump Slash",        LogicDekuBasementGSDesc);
  Option LogicDCStaircase                 = LogicTrick("Dodongo's Cavern\n Staircase with Bow",              LogicDCStaircaseDesc);
  Option LogicDCJump                      = LogicTrick("DC Spike Trap room\n Jump w/o Hover Boots",          LogicDCJumpDesc);
  Option LogicDCSlingshotSkip             = LogicTrick("DC Child Slingshot\n Skips",                         LogicDCSlingshotSkipDesc);
  Option LogicDCScarecrowGS               = LogicTrick("DC Scarecrow GS with\n Armos Statue",                LogicDCScarecrowGSDesc);
  Option LogicJabuBossGSAdult             = LogicTrick("Jabu Near Boss GS as\n Adult w/o Boomerang",         LogicJabuBossGSAdultDesc); //Needs Testing
  Option LogicJabuScrubJumpDive           = LogicTrick("Jabu Scrub as Adult\n w/ Jump Dive",                 LogicJabuScrubJumpDiveDesc); //Needs Testing
  Option LogicForestOutsideBackdoor       = LogicTrick("FoT Outisde Backdoor\n w/ Jump Slash",               LogicForestOutsideBackdoorDesc); //Needs Testing
  Option LogicForestDoorFrame             = LogicTrick("FoT East Courtyard\n Door Frame w/ Hover Boots",     LogicForestDoorFrameDesc); //Needs Testing
  Option LogicForestOutdoorEastGS         = LogicTrick("FoT East Courtyard GS\n with Boomerang",             LogicForestOutdoorEastGSDesc);
  Option LogicFireBossDoorJump            = LogicTrick("FiT Boss Door without\n Hover Boots or Pillar",      LogicFireBossDoorJumpDesc);
  Option LogicFireStrength                = LogicTrick("FiT Climb without\n Strength",                       LogicFireStrengthDesc);
  Option LogicFireScarecrow               = LogicTrick("FiT East Tower w/o\n Scarecrow\'s Song",             LogicFireScarecrowDesc);
  Option LogicFireFlameMaze               = LogicTrick("FiT Flame Wall Maze\n Skip",                         LogicFireFlameMazeDesc);
  Option LogicFireSongOfTime              = LogicTrick("FiT Song of Time Room\n GS w/o Song of Time",        LogicFireSongOfTimeDesc);
  Option LogicWaterTempleTorchLongshot    = LogicTrick("WaT Torch Longshot",                                 LogicWaterTempleTorchLongshotDesc);
  Option LogicWaterTempleUpperBoost       = LogicTrick("WaT Upper Ledge Jump\n with Bombs",                  LogicWaterTempleUpperBoostDesc);
  Option LogicWaterCentralBow             = LogicTrick("WaT Bow Target w/o\n Longshot or Hover Boots",       LogicWaterCentralBowDesc);
  Option LogicWaterCentralGSFW            = LogicTrick("WaT Central Pillar GS\n with Farore's Wind",         LogicWaterCentralGSFWDesc);
  Option LogicWaterCrackedWallNothing     = LogicTrick("WaT Cracked Wall with\n No Additional Items",        LogicWaterCrackedWallNothingDesc);
  Option LogicWaterCrackedWallHovers      = LogicTrick("WaT Cracked Wall with\n Hover Boots",                LogicWaterCrackedWallHoversDesc);
  Option LogicWaterBossKeyRegion          = LogicTrick("WaT Boss Key Region\n with Hover Boots",             LogicWaterBossKeyRegionDesc);
  Option LogicWaterBKJumpDive             = LogicTrick("WaT Boss Key Jump\n Dive",                           LogicWaterBKJumpDiveDesc);
  Option LogicWaterNorthBasementLedgeJump = LogicTrick("WaT North Basement\n Ledge with Precise Jump",       LogicWaterNorthBasementLedgeJumpDesc);
  Option LogicWaterDragonAdult            = LogicTrick("WaT Dragon Statue\n Jump Dive",                      LogicWaterDragonAdultDesc);
  Option LogicWaterDragonJumpDive         = LogicTrick("WaT Dragon Statue\n Switch Above as Adult",          LogicWaterDragonJumpDiveDesc);
  Option LogicWaterRiverGS                = LogicTrick("WaT River GS without\n Iron Boots",                  LogicWaterRiverGSDesc);
  Option LogicWaterFallingPlatformGS      = LogicTrick("WaT Falling Platform\n Room GS with Hookshot",       LogicWaterFallingPlatformGSDesc);
  Option LogicSpiritLowerAdultSwitch      = LogicTrick("SpT Lower Adult\n Switch with Bombs",                LogicSpiritLowerAdultSwitchDesc);
  Option LogicSpiritChildBombchu          = LogicTrick("SpT Child Side Bridge\n with Bombchu",               LogicSpiritChildBombchuDesc);
  Option LogicSpiritWall                  = LogicTrick("SpT Shifting Wall w/\n No Additional Items",         LogicSpiritWallDesc);
  Option LogicSpiritLobbyGS               = LogicTrick("SpT Main Room GS with\n Boomerang",                  LogicSpiritLobbyGSDesc);
  Option LogicSpiritMapChest              = LogicTrick("SpT Map Chest with\n Bow",                           LogicSpiritMapChestDesc);
  Option LogicSpiritSunChest              = LogicTrick("SpT Sun Block Room\n Chest with Bow",                LogicSpiritSunChestDesc); //Needs Testing
  Option LogicShadowFireArrowEntry        = LogicTrick("ShT Entry with Fire\n Arrows",                       LogicShadowFireArrowEntryDesc); //Needs Testing
  Option LogicShadowUmbrella              = LogicTrick("ShT Stone Umbrella\n Skip",                          LogicShadowUmbrellaDesc);
  Option LogicShadowFreestandingKey       = LogicTrick("ShT Freestanding Key\n with Bombchu",                LogicShadowFreestandingKeyDesc);
  Option LogicShadowStatue                = LogicTrick("ShT River Statue with\n Bombchu",                    LogicShadowStatueDesc);
  Option LogicChildDeadhand               = LogicTrick("Child Deadhand w/o\n Kokiri Sword",                  LogicChildDeadhandDesc);
  Option LogicGtgWithoutHookshot          = LogicTrick("GTG Left Side Silver\n Rupees w/o Hookshot",         LogicGtgWithoutHookshotDesc);
  Option LogicGtgFakeWall                 = LogicTrick("GTG Fake Wall Ledge\n with Hover Boots",             LogicGtgFakeWallDesc);
  Option LogicLensSpirit                  = LogicTrick("SpT without Lens of\n Truth",                        LogicLensSpiritDesc);
  Option LogicLensShadow                  = LogicTrick("ShT before Invisible\n Moving Platform w/o Lens",    LogicLensShadowDesc);
  Option LogicLensShadowBack              = LogicTrick("ShT beyond Invisible\n Moving Platform w/o Lens",    LogicLensShadowBackDesc);
  Option LogicLensBotw                    = LogicTrick("BotW without Lens of\n Truth",                       LogicLensBotwDesc);
  Option LogicLensGtg                     = LogicTrick("GTG without Lens of\n Truth",                        LogicLensGtgDesc);
  Option LogicLensCastle                  = LogicTrick("Ganon's Castle w/o\n Lens of Truth",                 LogicLensCastleDesc);
  Option LogicLensJabuMQ                  = LogicTrick("JJB MQ without Lens of\n Truth",                     LogicLensJabuMQDesc);
  Option LogicLensSpiritMQ                = LogicTrick("SpT MQ without Lens of\n Truth",                     LogicLensSpiritMQDesc);
  Option LogicLensShadowMQ                = LogicTrick("ShT MQ before Invisible\n Moving Platform w/o Lens", LogicLensShadowMQDesc);
  Option LogicLensShadowMQBack            = LogicTrick("ShT MQ beyond Invisible\n Moving Platform w/o Lens", LogicLensShadowMQBackDesc);
  Option LogicLensBotwMQ                  = LogicTrick("BotW MQ without Lens of\n Truth",                    LogicLensBotwMQDesc);
  Option LogicLensGtgMQ                   = LogicTrick("GTG MQ without Lens of\n Truth",                     LogicLensGtgMQDesc);
  Option LogicLensCastleMQ                = LogicTrick("Ganon's Castle MQ w/o\n Lens of Truth",              LogicLensCastleMQDesc);
  Option LogicSpiritTrialHookshot         = LogicTrick("Spirit Trial without\n Hookshot",                    LogicSpiritTrialHookshotDesc);
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
    &LogicLensJabuMQ,
    &LogicLensSpiritMQ,
    &LogicLensShadowMQ,
    &LogicLensShadowMQBack,
    &LogicLensBotwMQ,
    &LogicLensGtgMQ,
    &LogicLensCastleMQ,
    &LogicSpiritTrialHookshot,
  };

  static std::vector<std::string> gauntletOptions = {
    std::string(RANDOM_CHOICE_STR),
    std::string(RANDOM_COLOR_STR),
    std::string(CUSTOM_COLOR_STR),
    "Silver",
    "Gold",
    "Black",
    "Green",
    "Blue",
    "Bronze",
    "Red",
    "Sky Blue",
    "Pink",
    "Magenta",
    "Orange",
    "Lime",
    "Purple",
  };
  static std::vector<std::string> tunicOptions = {
    std::string(RANDOM_CHOICE_STR),
    std::string(RANDOM_COLOR_STR),
    std::string(CUSTOM_COLOR_STR),
    "Kokiri Green",
    "Goron Red",
    "Zora Blue",
    "Black",
    "White",
    "Azure Blue",
    "Vivid Cyan",
    "Light Red",
    "Fuchsia",
    "Purple",
    "Majora Purple",
    "Twitch Purple",
    "Purple Heart",
    "Persian Rose",
    "Dirty Yellow",
    "Blush Pink",
    "Hot Pink",
    "Rose Pink",
    "Orange",
    "Gray",
    "Gold",
    "Silver",
    "Beige",
    "Teal",
    "Blood Red",
    "Blood Orange",
    "Royal Blue",
    "Sonic Blue",
    "NES Green",
    "Dark Green",
    "Lumen",
  };
  static std::vector<std::string_view> cosmeticDescriptions = {
    RANDOM_CHOICE_DESC,
    RANDOM_COLOR_DESC,
    CUSTOM_COLOR_DESC,
    "This will only affect the color on Link's model.",
  };

  Option KokiriTunicColor           = Option::U8("Kokiri Tunic Color",     tunicOptions,    cosmeticDescriptions, OptionCategory::Cosmetic);
  Option GoronTunicColor            = Option::U8("Goron Tunic Color",      tunicOptions,    cosmeticDescriptions, OptionCategory::Cosmetic);
  Option ZoraTunicColor             = Option::U8("Zora Tunic Color",       tunicOptions,    cosmeticDescriptions, OptionCategory::Cosmetic);
  Option SilverGauntletsColor       = Option::U8("Silver Gauntlets Color", gauntletOptions, cosmeticDescriptions, OptionCategory::Cosmetic);
  Option GoldGauntletsColor         = Option::U8("Gold Gauntlets Color",   gauntletOptions, cosmeticDescriptions, OptionCategory::Cosmetic);
  std::string finalKokiriTunicColor     = KokiriTunicColor.GetSelectedOptionText();
  std::string finalGoronTunicColor      = GoronTunicColor.GetSelectedOptionText();
  std::string finalZoraTunicColor       = ZoraTunicColor.GetSelectedOptionText();
  std::string finalSilverGauntletsColor = SilverGauntletsColor.GetSelectedOptionText();
  std::string finalGoldGauntletsColor   = GoldGauntletsColor.GetSelectedOptionText();

  Option MirrorWorld = Option::Bool("Mirror World",         {"Off", "On"},   {mirrorWorldDesc}, OptionCategory::Cosmetic);

  std::vector<Option *> cosmeticOptions = {
    &KokiriTunicColor,
    &GoronTunicColor,
    &ZoraTunicColor,
    &SilverGauntletsColor,
    &GoldGauntletsColor,
    &MirrorWorld,
  };

  MenuItem loadSettingsPreset       = MenuItem::Action ("Load Settings Preset",       LOAD_PRESET);
  MenuItem saveSettingsPreset       = MenuItem::Action ("Save Settings Preset",       SAVE_PRESET);
  MenuItem deleteSettingsPreset     = MenuItem::Action ("Delete Settings Preset",     DELETE_PRESET);
  std::vector<MenuItem *> settingsPresetItems = {
    &loadSettingsPreset,
    &saveSettingsPreset,
    &deleteSettingsPreset,
  };

  MenuItem open                     = MenuItem::SubMenu("Open Settings",              &openOptions);
  MenuItem world                    = MenuItem::SubMenu("World Settings",             &worldOptions);
  MenuItem shuffle                  = MenuItem::SubMenu("Shuffle Settings",           &shuffleOptions);
  MenuItem shuffleDungeonItems      = MenuItem::SubMenu("Shuffle Dungeon Items",      &shuffleDungeonItemOptions);
  MenuItem excludeLocations         = MenuItem::SubMenu("Exclude Locations",          &excludeLocationsOptions);
  MenuItem detailedLogic            = MenuItem::SubMenu("Detailed Logic Settings",    &detailedLogicOptions);
  MenuItem startingInventory        = MenuItem::SubMenu("Starting Inventory",         &startingInventoryOptions);
  MenuItem timesaverSettings        = MenuItem::SubMenu("Timesaver Settings",         &timesaverOptions);
  MenuItem miscSettings             = MenuItem::SubMenu("Misc Settings",              &miscOptions);
  MenuItem itemPoolSettings         = MenuItem::SubMenu("Item Pool Settings",         &itemPoolOptions);
  MenuItem itemUsabilitySettings    = MenuItem::SubMenu("Item Usability Settings",    &itemUsabilityOptions);
  MenuItem settingsPresets          = MenuItem::SubMenu("Settings Presets",           &settingsPresetItems);
  MenuItem cosmetics                = MenuItem::SubMenu("Cosmetic Settings",          &cosmeticOptions);
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
    &startingInventory,
    &miscSettings,
    &itemPoolSettings,
    &itemUsabilitySettings,
    &cosmetics,
    &settingsPresets,
    &generateRandomizer,
  };

  //declared here, set in fill.cpp
  u32 LinksPocketRewardBitMask = 0;
  std::array<u32, 9> rDungeonRewardOverrides{};

  //declared here, set in menu.cpp
  u8 PlayOption;

  //Fills and returns a SettingsContext struct.
  //This struct is written to the code.ips patch and allows the game
  //to read what settings the player selected to make in game decisions.
  SettingsContext FillContext() {
    SettingsContext ctx = {};
    ctx.hashIndexes[0] = hashIconIndexes[0];
    ctx.hashIndexes[1] = hashIconIndexes[1];
    ctx.hashIndexes[2] = hashIconIndexes[2];
    ctx.hashIndexes[3] = hashIconIndexes[3];
    ctx.hashIndexes[4] = hashIconIndexes[4];

    ctx.logic                = Logic.Value<u8>();
    ctx.openForest           = OpenForest.Value<u8>();
    ctx.openKakariko         = OpenKakariko.Value<u8>();
    ctx.openDoorOfTime       = (OpenDoorOfTime) ? 1 : 0;
    ctx.zorasFountain        = ZorasFountain.Value<u8>();
    ctx.gerudoFortress       = GerudoFortress.Value<u8>();
    ctx.rainbowBridge        = Bridge.Value<u8>();
    ctx.bridgeStoneCount     = BridgeStoneCount.Value<u8>();
    ctx.bridgeMedallionCount = BridgeMedallionCount.Value<u8>();
    ctx.bridgeRewardCount    = BridgeRewardCount.Value<u8>();
    ctx.bridgeDungeonCount   = BridgeDungeonCount.Value<u8>();
    ctx.bridgeTokenCount     = BridgeTokenCount.Value<u8>();
    ctx.randomGanonsTrials   = (RandomGanonsTrials) ? 1 : 0;
    ctx.ganonsTrialsCount    = GanonsTrialsCount.Value<u8>();

    ctx.startingAge          = StartingAge.Value<u8>();
    ctx.resolvedStartingAge  = ResolvedStartingAge;

    ctx.bombchusInLogic      = (BombchusInLogic) ? 1 : 0;
    ctx.bombchuDrops         = (BombchuDrops) ? 1 : 0;
    ctx.randomMQDungeons     = (RandomMQDungeons) ? 1 : 0;
    ctx.mqDungeonCount       = MQDungeonCount.Value<u8>();
    ctx.mirrorWorld          = (MirrorWorld) ? 1 : 0;

    ctx.shuffleRewards       = ShuffleRewards.Value<u8>();
    ctx.linksPocketItem      = LinksPocketItem.Value<u8>();
    ctx.shuffleSongs         = ShuffleSongs.Value<u8>();
    ctx.tokensanity          = Tokensanity.Value<u8>();
    ctx.scrubsanity          = Scrubsanity.Value<u8>();
    ctx.shuffleCows          = (ShuffleCows) ? 1 : 0;
    ctx.shuffleKokiriSword   = (ShuffleKokiriSword) ? 1 : 0;
    ctx.shuffleOcarinas      = (ShuffleOcarinas) ? 1 : 0;
    ctx.shuffleWeirdEgg      = (ShuffleWeirdEgg) ? 1 : 0;
    ctx.shuffleGerudoToken   = (ShuffleGerudoToken) ? 1 : 0;
    ctx.shuffleMagicBeans    = (ShuffleMagicBeans) ? 1 : 0;

    ctx.mapsAndCompasses     = MapsAndCompasses.Value<u8>();
    ctx.keysanity            = Keysanity.Value<u8>();
    ctx.gerudoKeys           = GerudoKeys.Value<u8>();
    ctx.bossKeysanity        = BossKeysanity.Value<u8>();
    ctx.ganonsBossKey        = GanonsBossKey.Value<u8>();
    ctx.lacsCondition        = LACSCondition;
    ctx.lacsMedallionCount   = LACSMedallionCount.Value<u8>();
    ctx.lacsStoneCount       = LACSStoneCount.Value<u8>();
    ctx.lacsRewardCount      = LACSRewardCount.Value<u8>();
    ctx.lacsDungeonCount     = LACSDungeonCount.Value<u8>();
    ctx.lacsTokenCount       = LACSTokenCount.Value<u8>();

    ctx.skipChildStealth     = (SkipChildStealth) ? 1 : 0;
    ctx.skipTowerEscape      = (SkipTowerEscape) ? 1 : 0;
    ctx.skipEponaRace        = (SkipEponaRace) ? 1 : 0;
    ctx.skipMinigamePhases   = (SkipMinigamePhases) ? 1 : 0;
    ctx.freeScarecrow        = (FreeScarecrow) ? 1 : 0;
    ctx.fourPoesCutscene     = (FourPoesCutscene) ? 1 : 0;
    ctx.templeOfTimeIntro    = (TempleOfTimeIntro) ? 1 : 0;
    ctx.bigPoeTargetCount    = BigPoeTargetCount.Value<u8>() + 1;
    ctx.numRequiredCuccos    = NumRequiredCuccos.Value<u8>();

    ctx.gossipStoneHints     = GossipStoneHints.Value<u8>();
    ctx.damageMultiplier     = DamageMultiplier.Value<u8>();
    ctx.startingTime         = StartingTime.Value<u8>();
    ctx.chestAnimations      = (ChestAnimations) ? 1 : 0;
    ctx.chestSize            = (ChestSize) ? 1 : 0;
    ctx.generateSpoilerLog   = (GenerateSpoilerLog) ? 1 : 0;
    ctx.menuOpeningButton    = MenuOpeningButton.Value<u8>();

    ctx.stickAsAdult         = (StickAsAdult) ? 1 : 0;
    ctx.boomerangAsAdult     = (BoomerangAsAdult) ? 1 : 0;
    ctx.hammerAsChild        = (HammerAsChild) ? 1 : 0;

    ctx.itemPoolValue        = ItemPoolValue.Value<u8>();
    ctx.iceTrapValue         = IceTrapValue.Value<u8>();

    ctx.linksPocketRewardBitMask = LinksPocketRewardBitMask;

    ctx.dekuTreeDungeonMode              = DekuTree.IsMQ()              ? 1 : 0;
    ctx.dodongosCavernDungeonMode        = DodongosCavern.IsMQ()        ? 1 : 0;
    ctx.jabuJabusBellyDungeonMode        = JabuJabusBelly.IsMQ()        ? 1 : 0;
    ctx.forestTempleDungeonMode          = ForestTemple.IsMQ()          ? 1 : 0;
    ctx.fireTempleDungeonMode            = FireTemple.IsMQ()            ? 1 : 0;
    ctx.waterTempleDungeonMode           = WaterTemple.IsMQ()           ? 1 : 0;
    ctx.spiritTempleDungeonMode          = SpiritTemple.IsMQ()          ? 1 : 0;
    ctx.shadowTempleDungeonMode          = ShadowTemple.IsMQ()          ? 1 : 0;
    ctx.bottomOfTheWellDungeonMode       = BottomOfTheWell.IsMQ()       ? 1 : 0;
    ctx.iceCavernDungeonMode             = IceCavern.IsMQ()             ? 1 : 0;
    ctx.gerudoTrainingGroundsDungeonMode = GerudoTrainingGrounds.IsMQ() ? 1 : 0;
    ctx.ganonsCastleDungeonMode          = GanonsCastle.IsMQ()          ? 1 : 0;

    ctx.forestTrialSkip = (ForestTrial.IsSkipped()) ? 1 : 0;
    ctx.fireTrialSkip   = (FireTrial.IsSkipped())   ? 1 : 0;
    ctx.waterTrialSkip  = (WaterTrial.IsSkipped())  ? 1 : 0;
    ctx.spiritTrialSkip = (SpiritTrial.IsSkipped()) ? 1 : 0;
    ctx.shadowTrialSkip = (ShadowTrial.IsSkipped()) ? 1 : 0;
    ctx.lightTrialSkip  = (LightTrial.IsSkipped())  ? 1 : 0;

    //Starting Inventory
    ctx.startingConsumables   = (StartingConsumables) ? 1 : 0;
    ctx.startingMaxRupees     = (StartingMaxRupees) ? 1 : 0;
    ctx.startingStickCapacity = StartingStickCapacity.Value<u8>();
    ctx.startingNutCapacity   = StartingNutCapacity.Value<u8>();
    ctx.startingBombBag       = StartingBombBag.Value<u8>();
    ctx.startingBombchus      = StartingBombchus.Value<u8>();
    ctx.startingBow           = StartingBow.Value<u8>();
    ctx.startingFireArrows    = StartingFireArrows.Value<u8>();
    ctx.startingIceArrows     = StartingIceArrows.Value<u8>();
    ctx.startingLightArrows   = StartingLightArrows.Value<u8>();
    ctx.startingDinsFire      = StartingDinsFire.Value<u8>();
    ctx.startingFaroresWind   = StartingFaroresWind.Value<u8>();
    ctx.startingNayrusLove    = StartingNayrusLove.Value<u8>();
    ctx.startingSlingshot     = StartingSlingshot.Value<u8>();
    ctx.startingBoomerang     = StartingBoomerang.Value<u8>();
    ctx.startingLensOfTruth   = StartingLensOfTruth.Value<u8>();
    ctx.startingMagicBean     = StartingMagicBean.Value<u8>();
    ctx.startingMegatonHammer = StartingMegatonHammer.Value<u8>();
    ctx.startingHookshot      = StartingHookshot.Value<u8>();
    ctx.startingIronBoots     = StartingIronBoots.Value<u8>();
    ctx.startingHoverBoots    = StartingHoverBoots.Value<u8>();
    ctx.startingBottle1       = StartingBottle1.Value<u8>();
    ctx.startingBottle2       = StartingBottle2.Value<u8>();
    ctx.startingBottle3       = StartingBottle3.Value<u8>();
    ctx.startingRutoBottle    = StartingRutoBottle.Value<u8>();
    ctx.startingOcarina       = StartingOcarina.Value<u8>();
    ctx.startingKokiriSword   = StartingKokiriSword.Value<u8>();
    ctx.startingBiggoronSword = StartingBiggoronSword.Value<u8>();
    ctx.startingMagicMeter    = StartingMagicMeter.Value<u8>();
    ctx.startingDoubleDefense = StartingDoubleDefense.Value<u8>();

    //Starting Quest Items
    ctx.startingQuestItems |= StartingMinuetOfForest.Value<u8>()   << 6;
    ctx.startingQuestItems |= StartingBoleroOfFire.Value<u8>()     << 7;
    ctx.startingQuestItems |= StartingSerenadeOfWater.Value<u8>()  << 8;
    ctx.startingQuestItems |= StartingRequiemOfSpirit.Value<u8>()  << 9;
    ctx.startingQuestItems |= StartingNocturneOfShadow.Value<u8>() << 10;
    ctx.startingQuestItems |= StartingPreludeOfLight.Value<u8>()   << 11;
    ctx.startingQuestItems |= StartingZeldasLullaby.Value<u8>()    << 12;
    ctx.startingQuestItems |= StartingEponasSong.Value<u8>()       << 13;
    ctx.startingQuestItems |= StartingSariasSong.Value<u8>()       << 14;
    ctx.startingQuestItems |= StartingSunsSong.Value<u8>()         << 15;
    ctx.startingQuestItems |= StartingSongOfTime.Value<u8>()       << 16;
    ctx.startingQuestItems |= StartingSongOfStorms.Value<u8>()     << 17;
    ctx.startingQuestItems |= StartingShardOfAgony.Value<u8>()     << 21;

    //Give the Gerudo Token if Gerudo Fortress is Open and Shuffle Gerudo Card is off
    if (GerudoFortress.Is(GERUDOFORTRESS_OPEN) && !ShuffleGerudoToken) {
        ctx.startingQuestItems |= 0x00400000;
    }

    //Starting Equipment
    ctx.startingEquipment |= StartingKokiriSword.Value<u8>();
    ctx.startingEquipment |= StartingBiggoronSword.Value<u8>() << 2;
    ctx.startingEquipment |= StartingDekuShield.Value<u8>()    << 4;
    ctx.startingEquipment |= StartingHylianShield.Value<u8>()  << 5;
    ctx.startingEquipment |= StartingMirrorShield.Value<u8>()  << 6;
    ctx.startingEquipment |= StartingGoronTunic.Value<u8>()    << 9;
    ctx.startingEquipment |= StartingZoraTunic.Value<u8>()     << 10;

    //Starting Upgrades
    ctx.startingUpgrades |= StartingStrength.Value<u8>() << 6;
    ctx.startingUpgrades |= StartingScale.Value<u8>() << 9;
    ctx.startingUpgrades |= StartingWallet.Value<u8>() << 12;

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

  //set default cosmetics where the default is not the first option
  void SetDefaultCosmetics() {
    SilverGauntletsColor.SetSelectedIndex(3); //Silver
    GoldGauntletsColor.SetSelectedIndex(4);   //Gold
    KokiriTunicColor.SetSelectedIndex(3);     //Kokiri Green
    GoronTunicColor.SetSelectedIndex(4);      //Goron Red
    ZoraTunicColor.SetSelectedIndex(5);       //Zora Blue
  }

  //Set default settings for all settings where the default is not the first option
  void SetDefaultSettings() {
    OpenForest.SetSelectedIndex(OPENFOREST_OPEN);
    OpenDoorOfTime.SetSelectedIndex(1); //1 is Open, 0 is Closed
    Bridge.SetSelectedIndex(RAINBOWBRIDGE_VANILLA);
    BridgeTokenCount.Hide();
    RandomGanonsTrials.SetSelectedIndex(ON);
    GanonsTrialsCount.Hide();

    {
      std::vector<std::string> tokenOptions;
      tokenOptions.reserve(101);
      for (int i = 0; i <= 100; i++) {
        tokenOptions.push_back(std::to_string(i));
      }
      BridgeTokenCount.SetOptions(tokenOptions);
      BridgeTokenCount.SetSelectedIndex(1);
      LACSTokenCount.SetOptions(tokenOptions);
      LACSTokenCount.SetSelectedIndex(1);
    }

    StartingAge.SetSelectedIndex(AGE_CHILD);

    MapsAndCompasses.SetSelectedIndex(MAPSANDCOMPASSES_VANILLA);
    Keysanity.SetSelectedIndex(KEYSANITY_VANILLA);
    BossKeysanity.SetSelectedIndex(BOSSKEYSANITY_VANILLA);
    GanonsBossKey.SetSelectedIndex(GANONSBOSSKEY_VANILLA);

    AddExcludedOptions();
    Location(HC_ZELDAS_LETTER)->GetExcludedOption()->Hide(); //don't let users exclude these locations
    Location(MARKET_BOMBCHU_BOWLING_BOMBCHUS)->GetExcludedOption()->Hide();
    Location(GANON)->GetExcludedOption()->Hide();

    GossipStoneHints.SetSelectedIndex(HINTS_NEED_NOTHING);
    HintDistribution.SetSelectedIndex(1); //balanced

    DamageMultiplier.SetSelectedIndex(DAMAGEMULTIPLIER_DEFAULT);
    GenerateSpoilerLog.SetSelectedIndex(1); //true

    ItemPoolValue.SetSelectedIndex(ITEMPOOL_BALANCED);
    IceTrapValue.SetSelectedIndex(ICETRAPS_NORMAL);

    SetDefaultCosmetics();
  }

  //Include and Lock the desired locations
  void IncludeAndHide(std::vector<LocationKey> locations) {
    for (LocationKey loc : locations) {
      Location(loc)->GetExcludedOption()->SetSelectedIndex(INCLUDE);
      Location(loc)->GetExcludedOption()->Hide();
    }
  }

  //Unlock the desired locations
  void Unhide(std::vector<LocationKey> locations) {
    for (LocationKey loc : locations) {
      Location(loc)->GetExcludedOption()->Unhide();
    }
  }

  //This function will hide certain locations from the Excluded Locations
  //menu if the player's current settings would require non-junk to be placed
  //at those locations. Excluded locations will have junk placed at them.
  void ResolveExcludedLocationConflicts() {

    //Force include shops if shopsanity is off
    std::vector<LocationKey> shopLocations = GetLocations(everyPossibleLocation, Category::cShop);
    if (Shopsanity.IsNot(SHOPSANITY_OFF)) {
      Unhide(shopLocations);
    } else {
      IncludeAndHide(shopLocations);
    }
    //For now, just always hide shop locations, as not sure how to handle hiding them-
    //1-4 should always be hidden, while the others should be settings dependent, but random shopsanity makes that more complicated...
    // IncludeAndHide(shopLocations);

    //Force include song locations
    std::vector<LocationKey> songLocations = GetLocations(everyPossibleLocation, Category::cSong);
    std::vector<LocationKey> songDungeonRewards = GetLocations(everyPossibleLocation, Category::cSongDungeonReward);

    //Unhide all song locations, then lock necessary ones
    Unhide(songLocations);
    Unhide(songDungeonRewards);

    if (ShuffleSongs.Is(SONGSHUFFLE_SONG_LOCATIONS)) {
      IncludeAndHide(songLocations);
    } else if (ShuffleSongs.Is(SONGSHUFFLE_DUNGEON_REWARDS)) {
      IncludeAndHide(songDungeonRewards);
    }

    //Force Include Vanilla Skulltula locations
    std::vector<LocationKey> skulltulaLocations = GetLocations(everyPossibleLocation, Category::cSkulltula);
    Unhide(skulltulaLocations);
    if (Tokensanity.IsNot(TOKENSANITY_ALL_TOKENS)) {
      if (Tokensanity.Is(TOKENSANITY_OVERWORLD)) {
        //filter overworld skulls so we're just left with dungeons
        FilterAndEraseFromPool(skulltulaLocations, [](LocationKey loc){return Location(loc)->GetScene() >= 0x0A;});
      } else if (Tokensanity.Is(TOKENSANITY_DUNGEONS)) {
        //filter dungeon skulls so we're just left with overworld
        FilterAndEraseFromPool(skulltulaLocations, [](LocationKey loc){return Location(loc)->GetScene() < 0x0A;});
      }
      IncludeAndHide(skulltulaLocations);
    }

    //Force Include scrubs if Scrubsanity is Off
    std::vector<LocationKey> scrubLocations = GetLocations(everyPossibleLocation, Category::cDekuScrub);
    if (Scrubsanity.Is(OFF)) {
      IncludeAndHide(scrubLocations);
    } else {
      Unhide(scrubLocations);
    }

    //Force include Cows if Shuffle Cows is Off
    std::vector<LocationKey> cowLocations = GetLocations(everyPossibleLocation, Category::cCow);
    if (ShuffleCows) {
      Unhide(cowLocations);
    } else {
      IncludeAndHide(cowLocations);
    }

    //Force include the Kokiri Sword Chest if Shuffle Kokiri Sword is Off
    if (ShuffleKokiriSword) {
      Unhide({KF_KOKIRI_SWORD_CHEST});
    } else {
      IncludeAndHide({KF_KOKIRI_SWORD_CHEST});
    }

    //Force include the ocarina locations if Shuffle Ocarinas is Off
    std::vector<LocationKey> ocarinaLocations = {LW_GIFT_FROM_SARIA, HF_OCARINA_OF_TIME_ITEM};
    if (ShuffleOcarinas) {
      Unhide(ocarinaLocations);
    } else {
      IncludeAndHide(ocarinaLocations);
    }

    //Force include Malon if Shuffle Weird Egg is Off
    if (ShuffleWeirdEgg) {
      Unhide({HC_MALON_EGG});
    } else {
      IncludeAndHide({HC_MALON_EGG});
    }

    //Force include Gerudo Token Location if it's not shuffled
    if (ShuffleGerudoToken) {
      Unhide({GF_GERUDO_TOKEN});
    } else {
      IncludeAndHide({GF_GERUDO_TOKEN});
    }

    //Force include Magic Bean salesman if Shuffle Magic Beans is off
    if (ShuffleMagicBeans) {
      Unhide({ZR_MAGIC_BEAN_SALESMAN});
    } else {
      IncludeAndHide({ZR_MAGIC_BEAN_SALESMAN});
    }

    //Force include Map and Compass Chests when Vanilla
    std::vector<LocationKey> mapChests = GetLocations(everyPossibleLocation, Category::cVanillaMap);
    std::vector<LocationKey> compassChests = GetLocations(everyPossibleLocation, Category::cVanillaCompass);
    if (MapsAndCompasses.Is(MAPSANDCOMPASSES_VANILLA)) {
      IncludeAndHide(mapChests);
      IncludeAndHide(compassChests);
    } else {
      Unhide(mapChests);
      Unhide(compassChests);
    }

    //Force include Vanilla Small Key Locations (except gerudo Fortress) on Vanilla Keys
    std::vector<LocationKey> smallKeyChests = GetLocations(everyPossibleLocation, Category::cVanillaSmallKey);
    if (Keysanity.Is(KEYSANITY_VANILLA)) {
      IncludeAndHide(smallKeyChests);
    } else {
      Unhide(smallKeyChests);
    }

    //Force include Gerudo Fortress carpenter fights if GF Small Keys are Vanilla
    std::vector<LocationKey> vanillaGFKeyLocations = GetLocations(everyPossibleLocation, Category::cVanillaGFSmallKey);
    if (GerudoKeys.Is(GERUDOKEYS_VANILLA)) {
      IncludeAndHide(vanillaGFKeyLocations);
    } else {
      Unhide(vanillaGFKeyLocations);
    }

    //Force include Boss Key Chests if Boss Keys are Vanilla
    std::vector<LocationKey> bossKeyChests = GetLocations(everyPossibleLocation, Category::cVanillaBossKey);
    if (BossKeysanity.Is(BOSSKEYSANITY_VANILLA)) {
      IncludeAndHide(bossKeyChests);
    } else {
      Unhide(bossKeyChests);
    }

    //Force include Ganons Boss Key Chest if ganons boss key has to be there
    if (GanonsBossKey.Is(GANONSBOSSKEY_VANILLA)) {
      IncludeAndHide({GANONS_TOWER_BOSS_KEY_CHEST});
    } else {
      Unhide({GANONS_TOWER_BOSS_KEY_CHEST});
    }

    //Force include Light Arrow item if ganons boss key has to be there
    if (GanonsBossKey.Value<u8>() >= GANONSBOSSKEY_LACS_VANILLA) {
      IncludeAndHide({TOT_LIGHT_ARROWS_CUTSCENE});
    } else {
      Unhide({TOT_LIGHT_ARROWS_CUTSCENE});
    }
  }

  //Hide certain settings if they aren't relevant or Lock settings if they
  //can't be changed due to another setting that was chosen. (i.e. Closed Forest
  //will force Starting Age to Child).
  void ForceChange(u32 kDown, Option* currentSetting) {

    //Adult is not compatible with Closed Forest
    if (OpenForest.Is(OPENFOREST_CLOSED)) {
      StartingAge.SetSelectedIndex(AGE_CHILD);
      StartingAge.Lock();
    } else {
      StartingAge.Unlock();
    }

    //Only show stone count option if Stones is selected
    if (Bridge.Is(RAINBOWBRIDGE_STONES)) {
      BridgeStoneCount.Unhide();
    } else {
      BridgeStoneCount.SetSelectedIndex(3);
      BridgeStoneCount.Hide();
    }

    //Only show medallion count option if Medallions is selected
    if (Bridge.Is(RAINBOWBRIDGE_MEDALLIONS)) {
      BridgeMedallionCount.Unhide();
    } else {
      BridgeMedallionCount.Hide();
      BridgeMedallionCount.SetSelectedIndex(6);
    }

    //Only show reward count option if Rewards is selected
    if (Bridge.Is(RAINBOWBRIDGE_REWARDS)) {
      BridgeRewardCount.Unhide();
    } else {
      BridgeRewardCount.SetSelectedIndex(9);
      BridgeRewardCount.Hide();
    }

    //Only show reward count option if Rewards is selected
    if (Bridge.Is(RAINBOWBRIDGE_DUNGEONS)) {
      BridgeDungeonCount.Unhide();
    } else {
      BridgeDungeonCount.SetSelectedIndex(8);
      BridgeDungeonCount.Hide();
    }

    //Only show token count option if Tokens is selected
    if (Bridge.Is(RAINBOWBRIDGE_TOKENS)) {
      BridgeTokenCount.Unhide();
    } else {
      BridgeTokenCount.SetSelectedIndex(1);
      BridgeTokenCount.Hide();
    }

    //Only show Trial Count option if Random Trial Count is off
    if (RandomGanonsTrials) {
      GanonsTrialsCount.SetSelectedIndex(6);
      GanonsTrialsCount.Hide();
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
      MQDungeonCount.SetSelectedIndex(0);
      MQDungeonCount.Hide();
    } else {
      MQDungeonCount.Unhide();
    }

    //Force Link's Pocket Item to be a dungeon reward if Shuffle Rewards is end of dungeons
    if (ShuffleRewards.Is(REWARDSHUFFLE_END_OF_DUNGEON)) {
      LinksPocketItem.Lock();
      LinksPocketItem.SetSelectedIndex(LINKSPOCKETITEM_DUNGEON_REWARD);
    } else {
      LinksPocketItem.Unlock();
    }

    //Only show Medallion Count if setting Ganons Boss Key to LACS Medallions
    if (GanonsBossKey.Is(GANONSBOSSKEY_LACS_MEDALLIONS)) {
      LACSMedallionCount.Unhide();
    } else {
      LACSMedallionCount.SetSelectedIndex(6);
      LACSMedallionCount.Hide();
    }

    //Only show Stone Count if setting Ganons Boss Key to LACS Stones
    if (GanonsBossKey.Is(GANONSBOSSKEY_LACS_STONES)) {
      LACSStoneCount.Unhide();
    } else {
      LACSStoneCount.SetSelectedIndex(3);
      LACSStoneCount.Hide();
    }

    //Only show Reward Count if setting Ganons Boss Key to LACS Rewards
    if (GanonsBossKey.Is(GANONSBOSSKEY_LACS_REWARDS)) {
      LACSRewardCount.Unhide();
    } else {
      LACSRewardCount.SetSelectedIndex(9);
      LACSRewardCount.Hide();
    }

    //Only show Dungeon Count if setting Ganons Boss Key to LACS Dungeons
    if (GanonsBossKey.Is(GANONSBOSSKEY_LACS_DUNGEONS)) {
      LACSDungeonCount.Unhide();
    } else {
      LACSDungeonCount.SetSelectedIndex(8);
      LACSDungeonCount.Hide();
    }

    //Only show Token Count if setting Ganons Boss Key to LACS Tokens
    if (GanonsBossKey.Is(GANONSBOSSKEY_LACS_TOKENS)) {
      LACSTokenCount.Unhide();
    } else {
      LACSTokenCount.SetSelectedIndex(100);
      LACSTokenCount.Hide();
    }

    //Only show hint options if hints are enabled
    if (GossipStoneHints.Is(HINTS_NO_HINTS)) {
      ClearerHints.Hide();
      HintDistribution.Hide();
    } else {
      ClearerHints.Unhide();
      HintDistribution.Unhide();
    }

    //Set toggle for all tricks
    if ((kDown & KEY_DLEFT || kDown & KEY_DRIGHT) && currentSetting->GetName() == "All Tricks")  {
      for (u16 i = 0; i < Settings::detailedLogicOptions.size(); i++) {
        detailedLogicOptions[i]->SetSelectedIndex(currentSetting->GetSelectedOptionIndex());
      }
    }

    //Set toggle for all items
    if ((kDown & KEY_DLEFT || kDown & KEY_DRIGHT) && currentSetting->GetName() == "All Items Toggle")  {
      for (u16 i = 0; i < Settings::startingInventoryOptions.size(); i++) {
        startingInventoryOptions[i]->SetSelectedIndex(currentSetting->GetSelectedOptionIndex());
      }
    }

    ResolveExcludedLocationConflicts();
  }

  //eventual settings
  bool ShuffleDungeonEntrances          = false;
  bool ShuffleOverworldEntrances        = false;
  bool ShuffleInteriorEntrances         = false;
  bool ShuffleSpecialIndoorEntrances    = false;

  //Function to update cosmetics options depending on choices
  void UpdateCosmetics() {
    if (KokiriTunicColor.Is(CUSTOM_COLOR)) {
      finalKokiriTunicColor = GetCustomColor(KokiriTunicColor.GetSelectedOptionText());
    } else if (KokiriTunicColor.Is(RANDOM_CHOICE)) {
      finalKokiriTunicColor = tunicColors[rand() % tunicColors.size()]; //use default rand to not interfere with seed
    } else if (KokiriTunicColor.Is(RANDOM_COLOR)) {
      finalKokiriTunicColor = RandomColor();
    } else {
      finalKokiriTunicColor = tunicColors[KokiriTunicColor.GetSelectedOptionIndex() - NON_COLOR_COUNT];
    }

    if (GoronTunicColor.Is(CUSTOM_COLOR)) {
      finalGoronTunicColor = GetCustomColor(GoronTunicColor.GetSelectedOptionText());
    } else if (GoronTunicColor.Is(RANDOM_CHOICE)) {
      finalGoronTunicColor = tunicColors[rand() % tunicColors.size()]; //use default rand to not interfere with seed
    } else if (GoronTunicColor.Is(RANDOM_COLOR)) {
      finalGoronTunicColor = RandomColor();
    } else {
      finalGoronTunicColor = tunicColors[GoronTunicColor.GetSelectedOptionIndex() - NON_COLOR_COUNT];
    }

    if (ZoraTunicColor.Is(CUSTOM_COLOR)) {
      finalZoraTunicColor = GetCustomColor(ZoraTunicColor.GetSelectedOptionText());
    } else if (ZoraTunicColor.Is(RANDOM_CHOICE)) {
      finalZoraTunicColor = tunicColors[rand() % tunicColors.size()]; //use default rand to not interfere with seed
    } else if (ZoraTunicColor.Is(RANDOM_COLOR)) {
      finalZoraTunicColor = RandomColor();
    } else {
      finalZoraTunicColor = tunicColors[ZoraTunicColor.GetSelectedOptionIndex() - NON_COLOR_COUNT];
    }

    if (SilverGauntletsColor.Is(CUSTOM_COLOR)) {
      finalSilverGauntletsColor = GetCustomColor(SilverGauntletsColor.GetSelectedOptionText());
    } else if (SilverGauntletsColor.Is(RANDOM_CHOICE)) {
      finalSilverGauntletsColor = gauntletColors[rand() % gauntletColors.size()]; //use default rand to not interfere with seed
    } else if (SilverGauntletsColor.Is(RANDOM_COLOR)) {
      finalSilverGauntletsColor = RandomColor();
    } else {
      finalSilverGauntletsColor = gauntletColors[SilverGauntletsColor.GetSelectedOptionIndex() - NON_COLOR_COUNT];
    }

    if (GoldGauntletsColor.Is(CUSTOM_COLOR)) {
      finalGoldGauntletsColor = GetCustomColor(GoldGauntletsColor.GetSelectedOptionText());
    } else if (GoldGauntletsColor.Is(RANDOM_CHOICE)) {
      finalGoldGauntletsColor = gauntletColors[rand() % gauntletColors.size()]; //use default rand to not interfere with seed
    } else if (GoldGauntletsColor.Is(RANDOM_COLOR)) {
      finalGoldGauntletsColor = RandomColor();
    } else {
      finalGoldGauntletsColor = gauntletColors[GoldGauntletsColor.GetSelectedOptionIndex() - NON_COLOR_COUNT];
    }
  }

  //Function to set flags depending on settings
  void UpdateSettings() {

    //shuffle the dungeons and then set MQ for as many as necessary
    auto dungeons = dungeonList;
    Shuffle(dungeons);

    //Clear MQ dungeons
    for (u8 i = 0; i < dungeons.size(); i++) {
      dungeons[i]->ClearMQ();
    }

    //Set appropriate amount of MQ dungeons
    if (RandomMQDungeons) {
      MQDungeonCount.SetSelectedIndex(Random(0, MQDungeonCount.GetOptionCount()));
    }
    for (u8 i = 0; i < MQDungeonCount.Value<u8>(); i++) {
      dungeons[i]->SetMQ();
    }

    //shuffle the trials then require the amount set in GanonsTrialsCount
    auto trials = trialList;
    Shuffle(trials);

    //clear required trials
    for (auto& trial : trials) {
      trial->SetAsSkipped();
    }

    //Set appropriate amount of required trials
    if (RandomGanonsTrials) {
      GanonsTrialsCount.SetSelectedIndex(Random(0, GanonsTrialsCount.GetOptionCount()));
    }
    for (u8 i = 0; i < GanonsTrialsCount.Value<u8>(); i++) {
      trials[i]->SetAsRequired();
    }

    if (StartingAge.Is(AGE_RANDOM)) {
      int choice = Random(0, 2); //50% chance of each
      if (choice == 0) {
        ResolvedStartingAge = AGE_CHILD;
      }
      else {
        ResolvedStartingAge = AGE_ADULT;
      }
    }
    else {
      ResolvedStartingAge = StartingAge.Value<u8>();
    }

    HasNightStart = StartingTime.Is(STARTINGTIME_NIGHT);

    if (GanonsBossKey.Is(GANONSBOSSKEY_LACS_MEDALLIONS)) {
      LACSCondition = LACSCONDITION_MEDALLIONS;
    } else if (GanonsBossKey.Is(GANONSBOSSKEY_LACS_STONES)) {
      LACSCondition = LACSCONDITION_STONES;
    } else if (GanonsBossKey.Is(GANONSBOSSKEY_LACS_REWARDS)) {
      LACSCondition = LACSCONDITION_REWARDS;
    } else if (GanonsBossKey.Is(GANONSBOSSKEY_LACS_DUNGEONS)) {
      LACSCondition = LACSCONDITION_DUNGEONS;
    } else if (GanonsBossKey.Is(GANONSBOSSKEY_LACS_TOKENS)) {
      LACSCondition = LACSCONDITION_TOKENS;
    } else {
      LACSCondition = LACSCONDITION_VANILLA;
    }

    UpdateCosmetics();
  }

} // namespace Settings
