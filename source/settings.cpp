#include "settings.hpp"

#include <unistd.h>

#include "cosmetics.hpp"
#include "dungeon.hpp"
#include "fill.hpp"
#include "item_location.hpp"
#include "music.hpp"
#include "random.hpp"
#include "randomizer.hpp"
#include "setting_descriptions.hpp"
#include "trial.hpp"
#include "keys.hpp"

using namespace Cosmetics;
using namespace Dungeon;
using namespace Trial;
using namespace Music;

namespace Settings {
  std::string seed;
  std::string version = RANDOMIZER_VERSION "-" COMMIT_NUMBER;
  std::array<u8, 5> hashIconIndexes;

  //                                        Setting name,              Options,                                                                     Setting Descriptions (assigned in setting_descriptions.cpp)
  //Open Settings                                                                                                                                   Any option index past the last description will use the last description
  Option RandomizeOpen       = Option::Bool("Randomize Settings",     {"No","Yes"},                                                                 {openRandomize}, OptionCategory::Toggle);
  Option OpenForest          = Option::U8  ("Forest",                 {"Closed", "Open", "Closed Deku"},                                            {forestClosed, forestOpen, forestClosedDeku});
  Option OpenKakariko        = Option::U8  ("Kakariko Gate",          {"Closed", "Open"},                                                           {kakGateClosed, kakGateOpen});
  Option OpenDoorOfTime      = Option::U8  ("Door of Time",           {"Open", "Closed", "Intended"},                                               {doorOfTimeOpen, doorOfTimeClosed, doorOfTimeIntended});
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
    &RandomizeOpen,
    &OpenForest,
    &OpenKakariko,
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
  Option RandomizeWorld            = Option::Bool("Randomize Settings",     {"No","Yes"},                                                      {worldRandomize}, OptionCategory::Toggle);
  Option StartingAge               = Option::U8  ("Starting Age",           {"Adult", "Child", "Random"},                                      {ageDesc});
  u8 ResolvedStartingAge;
  Option ShuffleEntrances          = Option::Bool("Shuffle Entrances",      {"Off", "On"},                                                     {shuffleEntrancesDesc});
  Option ShuffleDungeonEntrances   = Option::Bool("  Dungeon Entrances",    {"Off", "On"},                                                     {dungeonEntrancesDesc});
  Option ShuffleOverworldEntrances = Option::Bool("  Overworld Entrances",  {"Off", "On"},                                                     {overworldEntrancesDesc});
  Option BombchusInLogic           = Option::Bool("Bombchus in Logic",      {"Off", "On"},                                                     {bombchuLogicDesc});
  Option AmmoDrops                 = Option::U8  ("Ammo Drops",             {"On", "On + Bombchu", "Off"},                                     {defaultAmmoDropsDesc, bombchuDropsDesc, noAmmoDropsDesc});
  Option HeartDropRefill           = Option::U8  ("Heart Drops and Refills",{"On", "No Drop", "No Refill", "Off"},                             {defaultHeartDropsDesc, noHeartDropsDesc, noHeartRefillDesc, scarceHeartsDesc});
  Option MQDungeonCount            = Option::U8  ("MQ Dungeon Count",       {"0","1","2","3","4","5","6","7","8","9","10","11","12", "Random"},{mqDungeonCountDesc});
  u8 MQSet;
  Option SetDungeonTypes           = Option::Bool("Set Dungeon Types",      {"Off", "On"},                                                     {setDungeonTypesDesc});
  Option MQDeku                    = Option::U8  ("  Deku Tree",            {"Vanilla", "Master Quest", "Random"},                             {setDungeonTypesDesc});
  Option MQDodongo                 = Option::U8  ("  Dodongo's Cavern",     {"Vanilla", "Master Quest", "Random"},                             {setDungeonTypesDesc});
  Option MQJabu                    = Option::U8  ("  Jabu-Jabu's Belly",    {"Vanilla", "Master Quest", "Random"},                             {setDungeonTypesDesc});
  Option MQForest                  = Option::U8  ("  Forest Temple",        {"Vanilla", "Master Quest", "Random"},                             {setDungeonTypesDesc});
  Option MQFire                    = Option::U8  ("  Fire Temple",          {"Vanilla", "Master Quest", "Random"},                             {setDungeonTypesDesc});
  Option MQWater                   = Option::U8  ("  Water Temple",         {"Vanilla", "Master Quest", "Random"},                             {setDungeonTypesDesc});
  Option MQSpirit                  = Option::U8  ("  Spirit Temple",        {"Vanilla", "Master Quest", "Random"},                             {setDungeonTypesDesc});
  Option MQShadow                  = Option::U8  ("  Shadow Temple",        {"Vanilla", "Master Quest", "Random"},                             {setDungeonTypesDesc});
  Option MQBotW                    = Option::U8  ("  Bottom of the Well",   {"Vanilla", "Master Quest", "Random"},                             {setDungeonTypesDesc});
  Option MQIceCavern               = Option::U8  ("  Ice Cavern",           {"Vanilla", "Master Quest", "Random"},                             {setDungeonTypesDesc});
  Option MQGTG                     = Option::U8  ("  Training Grounds",     {"Vanilla", "Master Quest", "Random"},                             {setDungeonTypesDesc});
  Option MQCastle                  = Option::U8  ("  Ganon's Castle",       {"Vanilla", "Master Quest", "Random"},                             {setDungeonTypesDesc});
  std::vector<Option *> worldOptions = {
    &RandomizeWorld,
    &StartingAge,
    &ShuffleEntrances,
    &ShuffleDungeonEntrances,
    &ShuffleOverworldEntrances,
    &BombchusInLogic,
    &AmmoDrops,
    &HeartDropRefill,
    &MQDungeonCount,
    &SetDungeonTypes,
    &MQDeku,
    &MQDodongo,
    &MQJabu,
    &MQForest,
    &MQFire,
    &MQWater,
    &MQSpirit,
    &MQShadow,
    &MQBotW,
    &MQIceCavern,
    &MQGTG,
    &MQCastle,
  };
  std::vector<Option *> dungeonOptions = {
    &MQDeku,
    &MQDodongo,
    &MQJabu,
    &MQForest,
    &MQFire,
    &MQWater,
    &MQSpirit,
    &MQShadow,
    &MQBotW,
    &MQIceCavern,
    &MQGTG,
    &MQCastle,
  };

  //Shuffle Settings
  Option RandomizeShuffle    = Option::Bool("Randomize Settings",     {"No","Yes"},                                                      {shuffleRandomize}, OptionCategory::Toggle);
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
  Option ShuffleMerchants    = Option::U8  ("Shuffle Merchants",      {"Off", "On (No Hints)", "On (With Hints)"},                       {merchantsDesc, merchantsHintsDesc});
  std::vector<Option *> shuffleOptions = {
    &RandomizeShuffle,
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
    &ShuffleMerchants,
  };

  //Shuffle Dungeon Items
  Option RandomizeDungeon    = Option::Bool("Randomize Settings",     {"No","Yes"},                                                      {dungeonRandomize}, OptionCategory::Toggle);
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
    &RandomizeDungeon,
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
  Option KingZoraSpeed       = Option::U8  ("King Zora Speed",        {"Fast", "Vanilla", "Random"},                                          {kingZoraSpeedFast, kingZoraSpeedVanilla, kingZoraSpeedRandom});
  Option CompleteMaskQuest   = Option::Bool("Complete Mask Quest",    {"Off", "On"},                                                          {completeMaskDesc});
  Option QuickText           = Option::U8  ("Quick Text",             {"0: Vanilla", "1: Skippable", "2: Instant", "3: Turbo"},               {quickTextDesc0, quickTextDesc1, quickTextDesc2, quickTextDesc3});
  Option SkipSongReplays     = Option::U8  ("  Skip Song Replays",    {"Don't Skip", "Skip (No SFX)", "Skip (Keep SFX)"},                     {skipSongReplaysDesc});
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
    &KingZoraSpeed,
    &CompleteMaskQuest,
    &QuickText,
    &SkipSongReplays,
  };

  //Misc Settings
  Option GossipStoneHints    = Option::U8  ("Gossip Stone Hints",     {"No Hints", "Need Nothing", "Mask of Truth", "Shard of Agony"},        {gossipStonesHintsDesc});
  Option ClearerHints        = Option::Bool("  Clearer Hints",        {"Off", "On"},                                                          {clearerHintsDesc});
  Option HintDistribution    = Option::U8  ("  Hint Distribution",    {"Useless", "Balanced", "Strong", "Very Strong"},                       {uselessHintsDesc, balancedHintsDesc, strongHintsDesc, veryStrongHintsDesc});
  Option DamageMultiplier    = Option::U8  ("Damage Multiplier",      {"x1/2", "x1", "x2", "x4", "x8", "x16", "OHKO"},                        {damageMultiDesc});
  Option StartingTime        = Option::U8  ("Starting Time",          {"Day", "Night"},                                                       {startingTimeDesc});
  Option ChestAnimations     = Option::Bool("Chest Animations",       {"Always Fast", "Match Contents"},                                      {chestAnimDesc});
  Option ChestSize           = Option::Bool("Chest Size and Color",   {"Vanilla", "Match Contents"},                                          {chestSizeDesc});
  Option GenerateSpoilerLog  = Option::Bool("Generate Spoiler Log",   {"No", "Yes"},                                                          {"", ""});
  Option IngameSpoilers      = Option::Bool("Ingame Spoilers",        {"Hide", "Show"},                                                       {ingameSpoilersHideDesc, ingameSpoilersShowDesc });
  Option MenuOpeningButton   = Option::U8  ("Open Info Menu with",    {"Select","Start","D-Pad Up","D-Pad Down","D-Pad Right","D-Pad Left",}, {menuButtonDesc});
  Option RandomTrapDmg       = Option::U8  ("Random Trap Damage",     {"Off", "Basic", "Advanced"},                                           {randomTrapDmgDesc, basicTrapDmgDesc, advancedTrapDmgDesc});
  bool HasNightStart         = false;
  std::vector<Option *> miscOptions = {
    &GossipStoneHints,
    &ClearerHints,
    &HintDistribution,
    &DamageMultiplier,
    &StartingTime,
    &ChestAnimations,
    &ChestSize,
    &GenerateSpoilerLog,
    &IngameSpoilers,
    &MenuOpeningButton,
    &RandomTrapDmg,
  };

  //Item Usability Settings
  Option FaroresWindAnywhere = Option::Bool("Farore's Wind Anywhere", {"Disabled", "Enabled"},                                                {faroresWindAnywhereDesc});
  Option StickAsAdult        = Option::Bool("Adult Deku Stick",       {"Disabled", "Enabled"},                                                {adultStickDesc});
  Option BoomerangAsAdult    = Option::Bool("Adult Boomerang",        {"Disabled", "Enabled"},                                                {adultBoomerangDesc});
  Option HammerAsChild       = Option::Bool("Child Hammer",           {"Disabled", "Enabled"},                                                {childHammerDesc});
  Option GkDurability        = Option::U8  ("GK Durability",          {"Vanilla", "Random Risk", "Random Safe"},                              {gkDurabilityVanilla, gkDurabilityRandomRisk, gkDurabilityRandomSafe});
  std::vector<Option *> itemUsabilityOptions = {
    &FaroresWindAnywhere,
    &StickAsAdult,
    &BoomerangAsAdult,
    &HammerAsChild,
    &GkDurability,
  };

  //Item Pool Settings
  Option ItemPoolValue         = Option::U8  ("Item Pool",             {"Plentiful", "Balanced", "Scarce", "Minimal"},                        {itemPoolPlentiful, itemPoolBalanced, itemPoolScarce, itemPoolMinimal});
  Option IceTrapValue          = Option::U8  ("Ice Traps",             {"Off", "Normal", "Extra", "Mayhem", "Onslaught"},                     {iceTrapsOff, iceTrapsNormal, iceTrapsExtra, iceTrapsMayhem, iceTrapsOnslaught});
  Option RemoveDoubleDefense   = Option::Bool("Remove Double Defense", {"No", "Yes"},                                                         {removeDDDesc});
  Option ProgressiveGoronSword = Option::Bool("Prog Goron Sword",      {"Disabled", "Enabled"},                                               {progGoronSword});
  std::vector<Option *> itemPoolOptions = {
    &ItemPoolValue,
    &IceTrapValue,
    &RemoveDoubleDefense,
    &ProgressiveGoronSword,
  };

  //Excluded Locations (Individual definitions made in ItemLocation class)
  std::vector<Option *> excludeLocationsOptions = {};

  std::vector<std::string> bottleOptions = {"None", "Empty Bottle", "Red Potion", "Green Potion", "Blue Potion", "Fairy", "Fish", "Milk", "Blue Fire", "Bugs", "Big Poe", "Half Milk", "Poe"};
  std::vector<std::string> healthOptions = { "3 hearts",  "4 hearts",  "5 hearts",  "6 hearts",  "7 hearts",  "8 hearts",  "9 hearts", "10 hearts", "11 hearts", "12 hearts",
                                            "13 hearts", "14 hearts", "15 hearts", "16 hearts", "17 hearts", "18 hearts", "19 hearts", "20 hearts"};//,  "1 heart",   "2 hearts"}; // TODO: logic for lower health
  Option StartingConsumables      = Option::Bool("Start with Consumables", {"No",               "Yes"},                                                     {startWithConsumablesDesc});
  Option StartingMaxRupees        = Option::Bool("Start with Max Rupees",  {"No",               "Yes"},                                                     {startWithMaxRupeesDesc});
  Option StartingInventoryToggle  = Option::U8  ("Inventory",              {"All Off",          "All On",           "Choose"},                              {""});
  Option StartingStickCapacity    = Option::U8  ("  Deku Sticks",          {"10 Deku Sticks",   "20 Deku Sticks",   "30 Deku Sticks"},                      {""});
  Option StartingNutCapacity      = Option::U8  ("  Deku Nuts",            {"20 Deku Nuts",     "30 Deku Nuts",     "40 Deku Nuts"},                        {""});
  Option StartingSlingshot        = Option::U8  ("  Slingshot",            {"None",             "Slingshot 30",     "Slingshot 40",     "Slingshot 50"},    {""});
  Option StartingOcarina          = Option::U8  ("  Ocarina",              {"None",             "Fairy Ocarina",    "Ocarina of Time"},                     {""});
  Option StartingBombBag          = Option::U8  ("  Bomb Bag",             {"None",             "Bomb Bag 20",      "Bomb Bag 30",      "Bomb Bag 40"},     {""});
  Option StartingBombchus         = Option::U8  ("  Bombchus",             {"None",             "Bombchus"},                                                {""});
  Option StartingBoomerang        = Option::U8  ("  Boomerang",            {"None",             "Boomerang"},                                               {""});
  Option StartingHookshot         = Option::U8  ("  Hookshot",             {"None",             "Hookshot",         "Longshot"},                            {""});
  Option StartingBow              = Option::U8  ("  Bow",                  {"None",             "Bow + Quiver 30",  "Bow + Quiver 40",  "Bow + Quiver 50"}, {""});
  Option StartingFireArrows       = Option::U8  ("  Fire Arrow",           {"None",             "Fire Arrow"},                                              {""});
  Option StartingIceArrows        = Option::U8  ("  Ice Arrow",            {"None",             "Ice Arrow"},                                               {""});
  Option StartingLightArrows      = Option::U8  ("  Light Arrow",          {"None",             "Light Arrow"},                                             {""});
  Option StartingMegatonHammer    = Option::U8  ("  Megaton Hammer",       {"None",             "Megaton Hammer"},                                          {""});
  Option StartingIronBoots        = Option::U8  ("  Iron Boots",           {"None",             "Iron Boots"},                                              {""});
  Option StartingHoverBoots       = Option::U8  ("  Hover Boots",          {"None",             "Hover Boots"},                                             {""});
  Option StartingLensOfTruth      = Option::U8  ("  Lens of Truth",        {"None",             "Lens of Truth"},                                           {""});
  Option StartingDinsFire         = Option::U8  ("  Din's Fire",           {"None",             "Din's Fire"},                                              {""});
  Option StartingFaroresWind      = Option::U8  ("  Farore's Wind",        {"None",             "Farore's Wind"},                                           {""});
  Option StartingNayrusLove       = Option::U8  ("  Nayru's Love",         {"None",             "Nayru's Love"},                                            {""});
  Option StartingMagicBean        = Option::U8  ("  Magic Beans",          {"None",             "Magic Beans"},                                             {""});
  Option StartingBottle1          = Option::U8  ("  Bottle Slot 1",        bottleOptions,                                                                   {""});
  Option StartingBottle2          = Option::U8  ("  Bottle Slot 2",        bottleOptions,                                                                   {""});
  Option StartingBottle3          = Option::U8  ("  Bottle Slot 3",        bottleOptions,                                                                   {""});
  Option StartingRutoBottle       = Option::U8  ("  Ruto's Letter",        {"None",             "Ruto's Letter"},                                           {""});
  Option StartingSongsToggle      = Option::U8  ("Ocarina Songs",          {"All Off",          "All On",           "Choose"},                              {""});
  Option StartingZeldasLullaby    = Option::U8  ("  Zelda's Lullaby",      {"None",             "Zelda's Lull."},                                           {""});
  Option StartingEponasSong       = Option::U8  ("  Epona's Song",         {"None",             "Epona's Song"},                                            {""});
  Option StartingSariasSong       = Option::U8  ("  Saria's Song",         {"None",             "Saria's Song"},                                            {""});
  Option StartingSunsSong         = Option::U8  ("  Sun's Song",           {"None",             "Sun's Song"},                                              {""});
  Option StartingSongOfTime       = Option::U8  ("  Song of Time",         {"None",             "Song of Time"},                                            {""});
  Option StartingSongOfStorms     = Option::U8  ("  Song of Storms",       {"None",             "Song of Storms"},                                          {""});
  Option StartingMinuetOfForest   = Option::U8  ("  Minuet of Forest",     {"None",             "Minuet of F."},                                            {""});
  Option StartingBoleroOfFire     = Option::U8  ("  Bolero of Fire",       {"None",             "Bolero of Fire"},                                          {""});
  Option StartingSerenadeOfWater  = Option::U8  ("  Serenade of Water",    {"None",             "Serenade of W."},                                          {""});
  Option StartingRequiemOfSpirit  = Option::U8  ("  Requiem of Spirit",    {"None",             "Requiem of S."},                                           {""});
  Option StartingNocturneOfShadow = Option::U8  ("  Nocturne of Shadow",   {"None",             "Nocturne of S."},                                          {""});
  Option StartingPreludeOfLight   = Option::U8  ("  Prelude of Light",     {"None",             "Prelude of L."},                                           {""});
  Option StartingUpgradesToggle   = Option::U8  ("Equipment & Upgrades",   {"All Off",          "All On",           "Choose"},                              {""});
  Option StartingKokiriSword      = Option::U8  ("  Kokiri Sword",         {"None",             "Kokiri Sword"},                                            {""});
  Option StartingBiggoronSword    = Option::U8  ("  Biggoron Sword",       {"None",             "Giant's Knife",    "Biggoron Sword"},                      {""});
  Option StartingDekuShield       = Option::U8  ("  Deku Shield",          {"None",             "Deku Shield"},                                             {""});
  Option StartingHylianShield     = Option::U8  ("  Hylian Shield",        {"None",             "Hylian Shield"},                                           {""});
  Option StartingMirrorShield     = Option::U8  ("  Mirror Shield",        {"None",             "Mirror Shield"},                                           {""});
  Option StartingGoronTunic       = Option::U8  ("  Goron Tunic",          {"None",             "Goron Tunic"},                                             {""});
  Option StartingZoraTunic        = Option::U8  ("  Zora Tunic",           {"None",             "Zora Tunic"},                                              {""});
  Option StartingStrength         = Option::U8  ("  Strength Upgrade",     {"None",             "Goron Bracelet",   "Silver Gauntlet",  "Golden Gauntlet"}, {""});
  Option StartingScale            = Option::U8  ("  Scale Upgrade",        {"None",             "Silver Scale"  ,   "Golden Scale"},                        {""});
  Option StartingWallet           = Option::U8  ("  Wallet Upgrade",       {"None",             "Adult's Wallet",   "Giant's Wallet" ,  "Tycoon's Wallet"}, {""});
  Option StartingShardOfAgony     = Option::U8  ("  Shard of Agony",       {"None",             "Shard of Agony"},                                          {""});
  Option StartingHealth           = Option::U8  ("  Health",               healthOptions,                                                                   {""});
  Option StartingMagicMeter       = Option::U8  ("  Magic Meter",          {"None",             "Single Magic",     "Double Magic"},                        {""});
  Option StartingDoubleDefense    = Option::U8  ("  Double Defense",       {"None",             "Double Defence"},                                          {""});
  Option StartingQuestToggle      = Option::U8  ("Quest Items",            {"All Off",          "All On",           "Choose"},                              {""});
  Option StartingKokiriEmerald    = Option::U8  ("  Kokiri's Emerald",     {"None",             "Kokiri's Emer."},                                          {""});
  Option StartingGoronRuby        = Option::U8  ("  Goron's Ruby",         {"None",             "Goron's Ruby"},                                            {""});
  Option StartingZoraSapphire     = Option::U8  ("  Zora's Sapphire",      {"None",             "Zora's Sapph."},                                           {""});
  Option StartingLightMedallion   = Option::U8  ("  Light Medallion",      {"None",             "Light Medall."},                                           {""});
  Option StartingForestMedallion  = Option::U8  ("  Forest Medallion",     {"None",             "Forest Medall."},                                          {""});
  Option StartingFireMedallion    = Option::U8  ("  Fire Medallion",       {"None",             "Fire Medallion"},                                          {""});
  Option StartingWaterMedallion   = Option::U8  ("  Water Medallion",      {"None",             "Water Medall."},                                           {""});
  Option StartingSpiritMedallion  = Option::U8  ("  Spirit Medallion",     {"None",             "Spirit Medall."},                                          {""});
  Option StartingShadowMedallion  = Option::U8  ("  Shadow Medallion",     {"None",             "Shadow Medall."},                                          {""});
  Option StartingSkulltulaToken   = Option::U8  ("Gold Skulltula Tokens",  {/*Options 0-100 defined in SetDefaultSettings()*/},                             {""});
  std::vector<Option *> startingInventoryOptions = {
    &StartingConsumables,
    &StartingMaxRupees,
    &StartingInventoryToggle,
    &StartingStickCapacity,
    &StartingNutCapacity,
    &StartingSlingshot,
    &StartingOcarina,
    &StartingBombBag,
    &StartingBombchus,
    &StartingBoomerang,
    &StartingHookshot,
    &StartingBow,
    &StartingFireArrows,
    &StartingIceArrows,
    &StartingLightArrows,
    &StartingMegatonHammer,
    &StartingIronBoots,
    &StartingHoverBoots,
    &StartingLensOfTruth,
    &StartingDinsFire,
    &StartingFaroresWind,
    &StartingNayrusLove,
    &StartingMagicBean,
    &StartingBottle1,
    &StartingBottle2,
    &StartingBottle3,
    &StartingRutoBottle,
    &StartingSongsToggle,
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
    &StartingUpgradesToggle,
    &StartingKokiriSword,
    &StartingBiggoronSword,
    &StartingDekuShield,
    &StartingHylianShield,
    &StartingMirrorShield,
    &StartingGoronTunic,
    &StartingZoraTunic,
    &StartingStrength,
    &StartingScale,
    &StartingWallet,
    &StartingShardOfAgony,
    &StartingHealth,
    &StartingMagicMeter,
    &StartingDoubleDefense,
    &StartingQuestToggle,
    &StartingKokiriEmerald,
    &StartingGoronRuby,
    &StartingZoraSapphire,
    &StartingLightMedallion,
    &StartingForestMedallion,
    &StartingFireMedallion,
    &StartingWaterMedallion,
    &StartingSpiritMedallion,
    &StartingShadowMedallion,
    &StartingSkulltulaToken,
  };

  Option Logic              = Option::U8  ("Logic",                   {"Glitchless", "Glitched", "No Logic", "Vanilla"}, {logicGlitchless, logicGlitched, logicNoLogic, logicVanilla});
  Option LocationsReachable = Option::Bool("All Locations Reachable", {"Off", "On"},                                     {locationsReachableDesc}); 
  Option NightGSExpectSuns  = Option::Bool("Night GSs Expect Sun's",  {"Off", "On"},                                     {nightGSDesc});
  std::vector<Option *> logicOptions = {
    &Logic,
    &LocationsReachable,
    &NightGSExpectSuns,
  };

  //Function to make defining logic tricks easier to read
  Option LogicTrick(std::string setting, std::string_view description) {
    return Option::Bool(setting, {"Disabled", "Enabled"}, {description});
  }

  //Detailed Logic Tricks                               ---------------------
  Option ToggleAllTricks                  = Option::U8("All Tricks", {"None", "Novice", "Intermediate", "Expert"},  {ToggleLogicNoneDesc, ToggleLogicNoviceDesc, ToggleLogicIntermediateDesc, ToggleLogicExpertDesc}, OptionCategory::Toggle);
  Option LogicGrottosWithoutAgony         = LogicTrick(" Grotto Access\n   w/o Shard of Agony",       LogicGrottosWithoutAgonyDesc);
  Option LogicVisibleCollision            = LogicTrick(" Go Through Visible\n   One-Way Collisions",  LogicVisibleCollisionDesc);
  Option LogicFewerTunicRequirements      = LogicTrick(" Fewer Tunic\n   Requirements",               LogicFewerTunicRequirementsDesc);
  Option LogicLostWoodsGSBean             = LogicTrick(" LW Adult Tree GS\n   w/o Magic Beans",       LogicLostWoodsGSBeanDesc);
  Option LogicLabDiving                   = LogicTrick(" LH Lab Dive\n   w/o Gold Scale",             LogicLabDivingDesc);
  Option LogicLabWallGS                   = LogicTrick(" LH Lab Wall GS\n   w/ Jump Slash",           LogicLabWallGSDesc);
  Option LogicGraveyardPoH                = LogicTrick(" GY Crate PoH\n   w/ Boomerang",              LogicGraveyardPoHDesc);
  Option LogicChildDampeRacePoH           = LogicTrick(" GY Second Dampe\n   Race as Child",          LogicChildDampeRacePoHDesc);
  Option LogicGerudoKitchen               = LogicTrick(" GF Through Kitchen\n   w/ Nothing",          LogicGerudoKitchenDesc);
  Option LogicLensWasteland               = LogicTrick(" Haunted Wasteland\n   w/o Lens of Truth",    LogicLensWastelandDesc);
  Option LogicReverseWasteland            = LogicTrick(" Haunted Wasteland\n   in Reverse",           LogicReverseWastelandDesc);
  Option LogicColossusGS                  = LogicTrick(" Colossus Hill GS\n   w/ Hookshot",           LogicColossusGSDesc);
  Option LogicOutsideGanonsGS             = LogicTrick(" Outside GaC GS\n   w/ Jump Slash",           LogicOutsideGanonsGSDesc);
  Option LogicManOnRoof                   = LogicTrick(" Kak Roof Guy\n   w/o Hookshot",              LogicManOnRoofDesc);
  Option LogicDMTBombable                 = LogicTrick(" DMT Wall Chest\n   w/ Strength",             LogicDMTBombableDesc);
  Option LogicDMTSoilGS                   = LogicTrick(" DMT Soil GS\n   w/o Opening DC",             LogicDMTSoilGSDesc);
  Option LogicLinkGoronDins               = LogicTrick(" GoC Adult Goron\n   w/ Din's Fire",          LogicLinkGoronDinsDesc);
  Option LogicGoronCityLeftMost           = LogicTrick(" GoC Maze Left Chest\n   w/ Hover Boots",     LogicGoronCityLeftMostDesc);
  Option LogicGoronCityPot                = LogicTrick(" GoC Goron Vase PoH\n   w/ Bombchu",          LogicGoronCityPotDesc); //Needs Testing
  Option LogicGoronCityPotWithStrength    = LogicTrick(" GoC Goron Vase PoH\n   w/ Strength",         LogicGoronCityPotWithStrengthDesc);
  Option LogicChildRollingWithStrength    = LogicTrick(" GoC Child Goron\n   w/ Strength",            LogicChildRollingWithStrengthDesc);
  Option LogicCraterUpperToLower          = LogicTrick(" DMC Upper to Lower\n   w/ Hammer",           LogicCraterUpperToLowerDesc); //Needs Testing
  Option LogicCraterBeanPoHWithHovers     = LogicTrick(" DMC Bean PoH\n   w/ Hover Boots",            LogicCraterBeanPoHWithHoversDesc);
  Option LogicBiggoronBolero              = LogicTrick(" DMC Deliver Eyedrops\n   w/ Bolero of Fire", LogicBiggoronBoleroDesc);
  Option LogicZoraRiverLower              = LogicTrick(" ZR Lower PoH\n   w/ Nothing",                LogicZoraRiverLowerDesc);
  Option LogicZoraRiverUpper              = LogicTrick(" ZR Upper PoH\n   w/ Nothing",                LogicZoraRiverUpperDesc);
  Option LogicDekuB1WebsWithBow           = LogicTrick(" DT B1 Web\n   w/ Bow",                       LogicDekuB1WebsWithBowDesc);
  Option LogicDekuB1Skip                  = LogicTrick(" DT B1 Navigation\n   w/o Slingshot",         LogicDekuB1SkipDesc);
  Option LogicDekuBasementGS              = LogicTrick(" DT B1 Vines GS\n   w/ Jump Slash",           LogicDekuBasementGSDesc);
  Option LogicDCStaircase                 = LogicTrick(" DC Staircase\n   w/ Bow",                    LogicDCStaircaseDesc);
  Option LogicDCJump                      = LogicTrick(" DC Spike Trap Room\n   w/o Hover Boots",     LogicDCJumpDesc);
  Option LogicDCSlingshotSkip             = LogicTrick(" DC Eye Switches\n   w/o Slingshot",          LogicDCSlingshotSkipDesc);
  Option LogicDCScarecrowGS               = LogicTrick(" DC Scarecrow GS\n   w/ Armos Statue",        LogicDCScarecrowGSDesc);
  Option LogicJabuBossGSAdult             = LogicTrick(" JJB Near Boss GS\n   as Adult",              LogicJabuBossGSAdultDesc); //Needs Testing
  Option LogicJabuScrubJumpDive           = LogicTrick(" JJB Deku Scrub\n   as Adult",                LogicJabuScrubJumpDiveDesc); //Needs Testing
  Option LogicForestOutsideBackdoor       = LogicTrick(" FoT West Backdoor\n   w/ Jump Slash",        LogicForestOutsideBackdoorDesc); //Needs Testing
  Option LogicForestDoorFrame             = LogicTrick(" FoT East Scarecrow\n   w/ Hover Boots",      LogicForestDoorFrameDesc); //Needs Testing
  Option LogicForestOutdoorEastGS         = LogicTrick(" FoT East Yard GS\n   w/ Boomerang",          LogicForestOutdoorEastGSDesc);
  Option LogicFireBossDoorJump            = LogicTrick(" FiT Boss Door\n   w/o Hover Boots",          LogicFireBossDoorJumpDesc);
  Option LogicFireStrength                = LogicTrick(" FiT Climb Block\n   w/o Strength",           LogicFireStrengthDesc);
  Option LogicFireScarecrow               = LogicTrick(" FiT East Tower\n   w/o Scarecrow",           LogicFireScarecrowDesc);
  Option LogicFireFlameMaze               = LogicTrick(" FiT Firewall Maze\n   w/ Nothing",           LogicFireFlameMazeDesc);
  Option LogicFireSongOfTime              = LogicTrick(" FiT SoT Room GS\n   w/o SoT",                LogicFireSongOfTimeDesc);
  Option LogicWaterTempleTorchLongshot    = LogicTrick(" WaT Torch Longshot\n   Shortcut",            LogicWaterTempleTorchLongshotDesc);
  Option LogicWaterTempleUpperBoost       = LogicTrick(" WaT Boss Ledge\n   w/ Bombs",                LogicWaterTempleUpperBoostDesc);
  Option LogicWaterCentralBow             = LogicTrick(" WaT Bow Target\n   w/o Longshot/Hover",      LogicWaterCentralBowDesc);
  Option LogicWaterCentralGSFW            = LogicTrick(" WaT Center Room GS\n   w/ Farore's Wind",    LogicWaterCentralGSFWDesc);
  Option LogicWaterCrackedWallNothing     = LogicTrick(" WaT Cracked Wall\n   w/ Nothing",            LogicWaterCrackedWallNothingDesc);
  Option LogicWaterCrackedWallHovers      = LogicTrick(" WaT Cracked Wall\n   w/ Hover Boots",        LogicWaterCrackedWallHoversDesc);
  Option LogicWaterBossKeyRegion          = LogicTrick(" WaT B1 North Area\n   w/ Hover Boots",       LogicWaterBossKeyRegionDesc);
  Option LogicWaterBKJumpDive             = LogicTrick(" WaT Boss Key Room\n   w/o Iron Boots",       LogicWaterBKJumpDiveDesc);
  Option LogicWaterNorthBasementLedgeJump = LogicTrick(" WaT Boss Key Rooms\n   w/ Precise Jump",     LogicWaterNorthBasementLedgeJumpDesc);
  Option LogicWaterDragonAdult            = LogicTrick(" WaT Whirlpool\n   w/o Iron Boots",           LogicWaterDragonAdultDesc);
  Option LogicWaterDragonJumpDive         = LogicTrick(" WaT Whirlpool Up\n   w/o Iron Boots",        LogicWaterDragonJumpDiveDesc);
  Option LogicWaterRiverGS                = LogicTrick(" WaT River GS\n   w/o Iron Boots",            LogicWaterRiverGSDesc);
  Option LogicWaterFallingPlatformGS      = LogicTrick(" WaT Waterfall GS\n   w/ Hookshot",           LogicWaterFallingPlatformGSDesc);
  Option LogicSpiritLowerAdultSwitch      = LogicTrick(" SpT Ceiling Switch\n   w/ Bombs",            LogicSpiritLowerAdultSwitchDesc);
  Option LogicSpiritChildBombchu          = LogicTrick(" SpT Child Bridge\n   w/ Bombchu",            LogicSpiritChildBombchuDesc);
  Option LogicSpiritWall                  = LogicTrick(" SpT Shifting Wall\n   w/ Nothing",           LogicSpiritWallDesc);
  Option LogicSpiritLobbyGS               = LogicTrick(" SpT Main Room GS\n   w/ Boomerang",          LogicSpiritLobbyGSDesc);
  Option LogicSpiritMapChest              = LogicTrick(" SpT Map Chest\n   w/ Bow",                   LogicSpiritMapChestDesc);
  Option LogicSpiritSunChest              = LogicTrick(" SpT Sun Block Room\n   w/ Bow",              LogicSpiritSunChestDesc); //Needs Testing
  Option LogicShadowFireArrowEntry        = LogicTrick(" ShT Entry\n   w/ Fire Arrows",               LogicShadowFireArrowEntryDesc); //Needs Testing
  Option LogicShadowUmbrella              = LogicTrick(" ShT Stone Umbrella\n   w/ Hover Boots",      LogicShadowUmbrellaDesc);
  Option LogicShadowFreestandingKey       = LogicTrick(" ShT Skull Vase Key\n   w/ Bombchu",          LogicShadowFreestandingKeyDesc);
  Option LogicShadowStatue                = LogicTrick(" ShT River Statue\n   w/ Bombchu",            LogicShadowStatueDesc);
  Option LogicChildDeadhand               = LogicTrick(" BotW Deadhand\n   w/o Sword",                LogicChildDeadhandDesc);
  Option LogicGtgWithoutHookshot          = LogicTrick(" GTG West Silver Rupee\n   w/o Hookshot",     LogicGtgWithoutHookshotDesc);
  Option LogicGtgFakeWall                 = LogicTrick(" GTG Invisible Wall\n   w/ Hover Boots",      LogicGtgFakeWallDesc);
  Option LogicLensSpirit                  = LogicTrick(" SpT Navigate\n   w/o Lens of Truth",         LogicLensSpiritDesc);
  Option LogicLensShadow                  = LogicTrick(" ShT Early Rooms\n   w/o Lens of Truth",      LogicLensShadowDesc);
  Option LogicLensShadowBack              = LogicTrick(" ShT Later Rooms\n   w/o Lens of Truth",      LogicLensShadowBackDesc);
  Option LogicLensBotw                    = LogicTrick(" BotW Navigate\n   w/o Lens of Truth",        LogicLensBotwDesc);
  Option LogicLensGtg                     = LogicTrick(" GTG Navigate\n   w/o Lens of Truth",         LogicLensGtgDesc);
  Option LogicLensCastle                  = LogicTrick(" GaC Navigate\n   w/o Lens of Truth",         LogicLensCastleDesc);
  Option LogicLensJabuMQ                  = LogicTrick(" JJB MQ Navigate\n   w/o Lens of Truth",      LogicLensJabuMQDesc);
  Option LogicLensSpiritMQ                = LogicTrick(" SpT MQ Navigate\n   w/o Lens of Truth",      LogicLensSpiritMQDesc);
  Option LogicLensShadowMQ                = LogicTrick(" ShT MQ Early Rooms\n   w/o Lens of Truth",   LogicLensShadowMQDesc);
  Option LogicLensShadowMQBack            = LogicTrick(" ShT MQ Later Rooms\n   w/o Lens of Truth",   LogicLensShadowMQBackDesc);
  Option LogicLensBotwMQ                  = LogicTrick(" BotW MQ Nagivate\n   w/o Lens of Truth",     LogicLensBotwMQDesc);
  Option LogicLensGtgMQ                   = LogicTrick(" GTG MQ Navigate\n   w/o Lens of Truth",      LogicLensGtgMQDesc);
  Option LogicLensCastleMQ                = LogicTrick(" GaC MQ Navigate\n   w/o Lens of Truth",      LogicLensCastleMQDesc);
  Option LogicSpiritTrialHookshot         = LogicTrick(" Spirit Trial\n   w/o Hookshot",              LogicSpiritTrialHookshotDesc);
  std::vector<Option *> trickOptions = {
    &ToggleAllTricks,
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

  //Function to make defining glitch tricks easier to read
  Option GlitchTrick(std::string setting, u8 enabledDifficulties, std::vector<std::string_view> description) {
    //enabledDifficulties bits
    //0: Novice
    //1: Intermediate
    //2: Advanced
    //3: Expert
    //4: Hero

    std::vector<std::string> selectableDifficulties;
    std::vector<std::string_view> includedDescriptions;

    selectableDifficulties.push_back("Disabled");
    includedDescriptions.push_back(description[0]);
    for (size_t i = 0; i < GlitchDifficulties.size(); i++) {
      if ((enabledDifficulties >> i) & 1) {
        selectableDifficulties.push_back(GlitchDifficulties[i]);
        includedDescriptions.push_back(description[i + 1]);
      }
    }

    return Option::U8(setting, selectableDifficulties, includedDescriptions);
  }

  Option GlitchISG                = GlitchTrick("Infinite Sword Glitch", 0b00001, GlitchISGDesc);
  Option GlitchHover              = GlitchTrick("Bomb Hover",            0b00111, GlitchHoverDesc);
  Option GlitchMegaflip           = GlitchTrick("Megaflip",              0b00011, GlitchMegaflipDesc);
  Option GlitchHookshotClip       = GlitchTrick("Hookshot Clip",         0b00001, GlitchHookshotClipDesc);
  Option GlitchHookshotJump_Bonk  = GlitchTrick("Hookshot Jump (Bonk)",  0b00010, GlitchHookshotJump_BonkDesc);
  Option GlitchHookshotJump_Boots = GlitchTrick("Hookshot Jump (Boots)", 0b00011, GlitchHookshotJump_BootsDesc);
  Option GlitchLedgeClip          = GlitchTrick("Ledge Clip",            0b00011, GlitchLedgeClipDesc);
  Option GlitchTripleSlashClip    = GlitchTrick("Triple Slash Clip",     0b00001, GlitchTripleSlashClipDesc);
  std::vector<Option*> glitchOptions = {
    &GlitchISG,
    &GlitchHover,
    &GlitchMegaflip,
    &GlitchHookshotClip,
    &GlitchHookshotJump_Bonk,
    &GlitchHookshotJump_Boots,
    &GlitchLedgeClip,
    &GlitchTripleSlashClip,
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
    "Magenta",
    "Violet",
    "Persian Rose",
    "Dirty Yellow",
    "Blush Pink",
    "Hot Pink",
    "Rose Pink",
    "Orange",
    "Gray",
    "Yellow",
    "Silver",
    "Beige",
    "Teal",
    "Blood Red",
    "Blood Orange",
    "Royal Blue",
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

  Option CustomTunicColors          = Option::Bool("Custom Tunic Colors",    {"Off", "On"},   {""},                 OptionCategory::Cosmetic);
  Option ChildTunicColor            = Option::U8  ("  Child Tunic Color",    tunicOptions,    cosmeticDescriptions, OptionCategory::Cosmetic);
  Option KokiriTunicColor           = Option::U8  ("  Kokiri Tunic Color",   tunicOptions,    cosmeticDescriptions, OptionCategory::Cosmetic);
  Option GoronTunicColor            = Option::U8  ("  Goron Tunic Color",    tunicOptions,    cosmeticDescriptions, OptionCategory::Cosmetic);
  Option ZoraTunicColor             = Option::U8  ("  Zora Tunic Color",     tunicOptions,    cosmeticDescriptions, OptionCategory::Cosmetic);
  Option SilverGauntletsColor       = Option::U8  ("Silver Gauntlets Color", gauntletOptions, cosmeticDescriptions, OptionCategory::Cosmetic);
  Option GoldGauntletsColor         = Option::U8  ("Gold Gauntlets Color",   gauntletOptions, cosmeticDescriptions, OptionCategory::Cosmetic);
  std::string finalChildTunicColor      = ChildTunicColor.GetSelectedOptionText();
  std::string finalKokiriTunicColor     = KokiriTunicColor.GetSelectedOptionText();
  std::string finalGoronTunicColor      = GoronTunicColor.GetSelectedOptionText();
  std::string finalZoraTunicColor       = ZoraTunicColor.GetSelectedOptionText();
  std::string finalSilverGauntletsColor = SilverGauntletsColor.GetSelectedOptionText();
  std::string finalGoldGauntletsColor   = GoldGauntletsColor.GetSelectedOptionText();

  Option ColoredKeys =     Option::Bool("Colored Small Keys", {"Off", "On"}, {coloredKeysDesc},     OptionCategory::Cosmetic);
  Option ColoredBossKeys = Option::Bool("Colored Boss Keys",  {"Off", "On"}, {coloredBossKeysDesc}, OptionCategory::Cosmetic);
  Option MirrorWorld =     Option::Bool("Mirror World",       {"Off", "On"}, {mirrorWorldDesc},     OptionCategory::Cosmetic);

  static std::vector<std::string> fanfareOptions = {"Off", "Only Fanfares", "Fanfares +\n                         Ocarina Music"};
  static std::vector<std::string_view> fanfareDescriptions = {fanfaresOffDesc, onlyFanfaresDesc, fanfaresOcarinaDesc};

  Option ShuffleMusic =    Option::Bool("Shuffle Music",           {"Off", "On"},    {musicRandoDesc},      OptionCategory::Cosmetic);
  Option ShuffleBGM =      Option::Bool("  Shuffle BGM",           {"Off", "On"},    {shuffleBGMDesc},      OptionCategory::Cosmetic);
  Option ShuffleFanfares = Option::U8  ("  Shuffle Fanfares",      {fanfareOptions}, {fanfareDescriptions}, OptionCategory::Cosmetic);
  Option ShuffleOcaMusic = Option::Bool("  Shuffle Ocarina Music", {"Off", "On"},    {shuffleOcaMusicDesc}, OptionCategory::Cosmetic);

  std::vector<Option *> cosmeticOptions = {
    &CustomTunicColors,
    &ChildTunicColor,
    &KokiriTunicColor,
    &GoronTunicColor,
    &ZoraTunicColor,
    &SilverGauntletsColor,
    &GoldGauntletsColor,
    &ColoredKeys,
    &ColoredBossKeys,
    &MirrorWorld,
    &ShuffleMusic,
    &ShuffleBGM,
    &ShuffleFanfares,
    &ShuffleOcaMusic,
  };

  Menu loadSettingsPreset       = Menu::Action("Load Settings Preset",       LOAD_PRESET);
  Menu saveSettingsPreset       = Menu::Action("Save Settings Preset",       SAVE_PRESET);
  Menu deleteSettingsPreset     = Menu::Action("Delete Settings Preset",     DELETE_PRESET);
  std::vector<Menu *> settingsPresetItems = {
    &loadSettingsPreset,
    &saveSettingsPreset,
    &deleteSettingsPreset,
  };

  //Detailed Logic Options Submenu
  Menu logicSettings    = Menu::SubMenu("Logic Options",     &logicOptions);
  Menu excludeLocations = Menu::SubMenu("Exclude Locations", &excludeLocationsOptions);
  Menu tricks           = Menu::SubMenu("Logical Tricks",    &trickOptions);
  Menu glitchSettings   = Menu::SubMenu("Glitch Options",    &glitchOptions);
  std::vector<Menu *> detailedLogicOptions = {
    &logicSettings,
    &excludeLocations,
    &tricks,
    &glitchSettings,
  };

  Menu open                     = Menu::SubMenu("Open Settings",              &openOptions);
  Menu world                    = Menu::SubMenu("World Settings",             &worldOptions);
  Menu shuffle                  = Menu::SubMenu("Shuffle Settings",           &shuffleOptions);
  Menu shuffleDungeonItems      = Menu::SubMenu("Shuffle Dungeon Items",      &shuffleDungeonItemOptions);
  Menu detailedLogic            = Menu::SubMenu("Detailed Logic Settings",    &detailedLogicOptions);
  Menu startingInventory        = Menu::SubMenu("Starting Inventory",         &startingInventoryOptions);
  Menu timesaverSettings        = Menu::SubMenu("Timesaver Settings",         &timesaverOptions);
  Menu miscSettings             = Menu::SubMenu("Misc Settings",              &miscOptions);
  Menu itemPoolSettings         = Menu::SubMenu("Item Pool Settings",         &itemPoolOptions);
  Menu itemUsabilitySettings    = Menu::SubMenu("Item Usability Settings",    &itemUsabilityOptions);
  Menu settingsPresets          = Menu::SubMenu("Settings Presets",           &settingsPresetItems);
  Menu cosmetics                = Menu::SubMenu("Cosmetic Settings",          &cosmeticOptions);
  Menu generateRandomizer       = Menu::Action ("Generate Randomizer",        GENERATE_MODE);

  //adding a menu with no options crashes, might fix later
  std::vector<Menu *> mainMenu = {
    &open,
    &world,
    &shuffle,
    &shuffleDungeonItems,
    &timesaverSettings,
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
    ctx.openDoorOfTime       = OpenDoorOfTime.Value<u8>();
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
    ctx.shuffleDungeonEntrances = (ShuffleDungeonEntrances) ? 1 : 0;
    ctx.bombchusInLogic         = (BombchusInLogic) ? 1 : 0;
    ctx.ammoDrops            = AmmoDrops.Value<u8>();
    ctx.heartDropRefill      = HeartDropRefill.Value<u8>();
    ctx.randomMQDungeons        = (MQDungeonCount.Value<u8>() == 13) ? 1 : 0;
    ctx.mqDungeonCount          = MQSet;

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
    ctx.shuffleMerchants     = ShuffleMerchants.Value<u8>();

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
    ctx.kingZoraSpeed        = KingZoraSpeed.Value<u8>();
    ctx.completeMaskQuest    = CompleteMaskQuest ? 1 : 0;
    ctx.quickText            = QuickText.Value<u8>();
    ctx.skipSongReplays      = SkipSongReplays.Value<u8>();

    ctx.gossipStoneHints     = GossipStoneHints.Value<u8>();
    ctx.damageMultiplier     = DamageMultiplier.Value<u8>();
    ctx.startingTime         = StartingTime.Value<u8>();
    ctx.chestAnimations      = (ChestAnimations) ? 1 : 0;
    ctx.chestSize            = (ChestSize) ? 1 : 0;
    ctx.generateSpoilerLog   = (GenerateSpoilerLog) ? 1 : 0;
    ctx.ingameSpoilers       = (IngameSpoilers) ? 1 : 0;
    ctx.menuOpeningButton    = MenuOpeningButton.Value<u8>();
    ctx.randomTrapDmg        = RandomTrapDmg.Value<u8>();

    ctx.faroresWindAnywhere  = (FaroresWindAnywhere) ? 1 : 0;
    ctx.stickAsAdult         = (StickAsAdult) ? 1 : 0;
    ctx.boomerangAsAdult     = (BoomerangAsAdult) ? 1 : 0;
    ctx.hammerAsChild        = (HammerAsChild) ? 1 : 0;
    ctx.gkDurability         = GkDurability.Value<u8>();

    ctx.itemPoolValue        = ItemPoolValue.Value<u8>();
    ctx.iceTrapValue         = IceTrapValue.Value<u8>();
    ctx.progressiveGoronSword = (ProgressiveGoronSword) ? 1 : 0;

    ctx.customTunicColors    = (CustomTunicColors) ? 1 : 0;
    ctx.mirrorWorld          = (MirrorWorld) ? 1 : 0;
    ctx.coloredKeys          = (ColoredKeys) ? 1 : 0;
    ctx.coloredBossKeys      = (ColoredBossKeys) ? 1 : 0;

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
    ctx.startingHealth        = (StartingHealth.Value<u8>() + 2) % 20 + 1;
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
    ctx.startingDungeonReward |= StartingKokiriEmerald.Value<u8>()    << 18;
    ctx.startingDungeonReward |= StartingGoronRuby.Value<u8>()        << 19;
    ctx.startingDungeonReward |= StartingZoraSapphire.Value<u8>()     << 20;
    ctx.startingDungeonReward |= StartingLightMedallion.Value<u8>()   << 5;
    ctx.startingDungeonReward |= StartingForestMedallion.Value<u8>()  << 0;
    ctx.startingDungeonReward |= StartingFireMedallion.Value<u8>()    << 1;
    ctx.startingDungeonReward |= StartingWaterMedallion.Value<u8>()   << 2;
    ctx.startingDungeonReward |= StartingSpiritMedallion.Value<u8>()  << 3;
    ctx.startingDungeonReward |= StartingShadowMedallion.Value<u8>()  << 4;

    ctx.startingTokens        = StartingSkulltulaToken.Value<u8>();

    //Give the Gerudo Token if Gerudo Fortress is Open and Shuffle Gerudo Card is off
    if (GerudoFortress.Is(GERUDOFORTRESS_OPEN) && !ShuffleGerudoToken) {
        ctx.startingQuestItems |= 0x00400000;
    }

    //Starting Equipment
    ctx.startingEquipment |= StartingKokiriSword.Value<u8>();
    ctx.startingEquipment |= (StartingBiggoronSword.Value<u8>() ? 1: 0) << 2;
    ctx.startingEquipment |= StartingDekuShield.Value<u8>()    << 4;
    ctx.startingEquipment |= StartingHylianShield.Value<u8>()  << 5;
    ctx.startingEquipment |= StartingMirrorShield.Value<u8>()  << 6;
    ctx.startingEquipment |= StartingGoronTunic.Value<u8>()    << 9;
    ctx.startingEquipment |= StartingZoraTunic.Value<u8>()     << 10;

    //Starting Upgrades
    ctx.startingUpgrades |= StartingStrength.Value<u8>() << 6;
    ctx.startingUpgrades |= StartingScale.Value<u8>() << 9;
    ctx.startingUpgrades |= StartingWallet.Value<u8>() << 12;

    return ctx;
  }

  //set default cosmetics where the default is not the first option
  static void SetDefaultCosmetics() {
    SilverGauntletsColor.SetSelectedIndex(3); //Silver
    GoldGauntletsColor.SetSelectedIndex(4);   //Gold
    ChildTunicColor.SetSelectedIndex(3);      //Kokiri Green
    KokiriTunicColor.SetSelectedIndex(3);     //Kokiri Green
    GoronTunicColor.SetSelectedIndex(4);      //Goron Red
    ZoraTunicColor.SetSelectedIndex(5);       //Zora Blue

    ShuffleMusic.SetSelectedIndex(0);         // Off
    ShuffleBGM.SetSelectedIndex(1);           // On
    ShuffleFanfares.SetSelectedIndex(1);      // Fanfares only
    ShuffleOcaMusic.SetSelectedIndex(1);      // On
  }

  //Set default settings for all settings where the default is not the first option
  void SetDefaultSettings() {
    OpenForest.SetSelectedIndex(OPENFOREST_OPEN);
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
      StartingSkulltulaToken.SetOptions(tokenOptions);
      BridgeTokenCount.SetSelectedIndex(1);
      LACSTokenCount.SetOptions(tokenOptions);
      LACSTokenCount.SetSelectedIndex(1);
    }

    StartingAge.SetSelectedIndex(AGE_CHILD);
    AmmoDrops.SetSelectedIndex(AMMODROPS_VANILLA);
    HeartDropRefill.SetSelectedIndex(HEARTDROPREFILL_VANILLA);
    MapsAndCompasses.SetSelectedIndex(MAPSANDCOMPASSES_VANILLA);
    Keysanity.SetSelectedIndex(KEYSANITY_VANILLA);
    BossKeysanity.SetSelectedIndex(BOSSKEYSANITY_VANILLA);
    GanonsBossKey.SetSelectedIndex(GANONSBOSSKEY_VANILLA);

    AddExcludedOptions();
    Location(HC_ZELDAS_LETTER)->GetExcludedOption()->Hide(); //don't let users exclude these locations
    Location(MARKET_BOMBCHU_BOWLING_BOMBCHUS)->GetExcludedOption()->Hide();
    Location(GANON)->GetExcludedOption()->Hide();

    QuickText.SetSelectedIndex(QUICKTEXT_SKIPPABLE);

    GossipStoneHints.SetSelectedIndex(HINTS_NEED_NOTHING);
    HintDistribution.SetSelectedIndex(1); //balanced

    DamageMultiplier.SetSelectedIndex(DAMAGEMULTIPLIER_DEFAULT);
    GenerateSpoilerLog.SetSelectedIndex(1); //true

    ItemPoolValue.SetSelectedIndex(ITEMPOOL_BALANCED);
    IceTrapValue.SetSelectedIndex(ICETRAPS_NORMAL);

    LocationsReachable.SetSelectedIndex(1); //All Locations Reachable On

    SetDefaultCosmetics();
  }

  //Include and Lock the desired locations
  static void IncludeAndHide(std::vector<LocationKey> locations) {
    for (LocationKey loc : locations) {
      Location(loc)->GetExcludedOption()->SetSelectedIndex(INCLUDE);
      Location(loc)->GetExcludedOption()->Hide();
    }
  }

  //Unlock the desired locations
  static void Unhide(std::vector<LocationKey> locations) {
    for (LocationKey loc : locations) {
      Location(loc)->GetExcludedOption()->Unhide();
    }
  }

		
  //Used for Starting Inventory options, enables/disables the options or expands/collapses each category based on their index number
  void CollapseCategory(Option startingInventorySections, int startNum, int endNum) {
    for(int i = startNum; i < endNum ;++i){
      switch(startingInventorySections.Value<u8>()) {
        case 0: 
        startingInventoryOptions[i] -> Hide();
        startingInventoryOptions[i] -> SetSelectedIndex(0);
        break;
        case 1:
        startingInventoryOptions[i] -> Hide();
        startingInventoryOptions[i] -> SetSelectedIndex((startingInventoryOptions[i]->GetOptionCount())-1);
        break;
        case 2:
        startingInventoryOptions[i] -> Unhide();
        break;
      }
    }
  }

  //This function will hide certain locations from the Excluded Locations
  //menu if the player's current settings would require non-junk to be placed
  //at those locations. Excluded locations will have junk placed at them.
  static void ResolveExcludedLocationConflicts() {

    std::vector<LocationKey> shopLocations = GetLocations(everyPossibleLocation, Category::cShop);
    //For now, just always hide shop locations, as not sure how to handle hiding them-
    //1-4 should always be hidden, while the others should be settings dependent, but random shopsanity makes that more complicated...
    //Excluded shop locations are also wonky
    IncludeAndHide(shopLocations);

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
        FilterAndEraseFromPool(skulltulaLocations, [](const LocationKey loc){return Location(loc)->GetScene() >= 0x0A;});
      } else if (Tokensanity.Is(TOKENSANITY_DUNGEONS)) {
        //filter dungeon skulls so we're just left with overworld
        FilterAndEraseFromPool(skulltulaLocations, [](const LocationKey loc){return Location(loc)->GetScene() < 0x0A;});
      }
      IncludeAndHide(skulltulaLocations);
    }

    //Force Include scrubs if Scrubsanity is Off
    std::vector<LocationKey> scrubLocations = GetLocations(everyPossibleLocation, Category::cDekuScrub, Category::cDekuScrubUpgrades);
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

    //Force include Medigoron and Carpet salesman if Shuffle Merchants is off
    if (ShuffleMerchants.IsNot(SHUFFLEMERCHANTS_OFF)) {
      Unhide({GC_MEDIGORON});
      Unhide({WASTELAND_BOMBCHU_SALESMAN});
    } else {
      IncludeAndHide({GC_MEDIGORON});
      IncludeAndHide({WASTELAND_BOMBCHU_SALESMAN});
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

  u8 DungeonsOfType(u8 type) {
    u8 count = 0;

    for (Option *option : dungeonOptions) {
      count += (option->Value<u8>() == type) ? 1 : 0;
    }

    return count;
  }

  //Hide certain settings if they aren't relevant or Lock settings if they
  //can't be changed due to another setting that was chosen. (i.e. Closed Forest
  //will force Starting Age to Child).
  void ForceChange(u32 kDown, Option* currentSetting) {

    //Groups the item categories; bottles are handled separately because the proper item is Empty Bottle (1)
    CollapseCategory(StartingInventoryToggle, 3, 23);
    CollapseCategory(StartingSongsToggle, 28, 40);
    CollapseCategory(StartingUpgradesToggle, 41, 55);
    CollapseCategory(StartingQuestToggle, 56, 65);
    for(int i = 23; i < 27 ;++i){ 
      switch(StartingInventoryToggle.Value<u8>()) {
        case 0: 
        startingInventoryOptions[i] -> Hide();
        startingInventoryOptions[i] -> SetSelectedIndex(0);
        break;
        case 1:
        startingInventoryOptions[i] -> Hide();
        startingInventoryOptions[i] -> SetSelectedIndex(1);
        break;
        case 2:
        startingInventoryOptions[i] -> Unhide();
        break;
      }
    }
    //Only hide the options for now, select them later in UpdateSettings()
    RandomizeAllSettings();

    //Only go through options if all settings are not randomized
    if (!RandomizeOpen) {
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
    }

    //Only go through options if all settings are not randomized
    if (!RandomizeWorld) {
      //Show Shuffle options when Shuffle Entrances is On
      if (ShuffleEntrances) {
        ShuffleDungeonEntrances.Unhide();
        ShuffleOverworldEntrances.Unhide();
      } else {
        ShuffleDungeonEntrances.SetSelectedIndex(OFF);
        ShuffleDungeonEntrances.Hide();
        ShuffleOverworldEntrances.SetSelectedIndex(OFF);
        ShuffleOverworldEntrances.Hide();
      }
    }

    if (SetDungeonTypes) {
      for (Option *option : dungeonOptions) {
        option->Unhide();
      }

      // Restrict MQDungeonCount options so they can't be less than the number of dungeons set to MQ and can't be more
      // than the number of dungeons set to MQ plus the number of dungeons set to random
      u8 MQ = DungeonsOfType(1), R = DungeonsOfType(2);
      if (MQDungeonCount.Value<u8>() < MQ) {
        MQDungeonCount.SetSelectedIndex((currentSetting == &MQDungeonCount && (kDown & KEY_DLEFT )) ? 13 : MQ);
      } else if (MQDungeonCount.Value<u8>() != 13 && MQDungeonCount.Value<u8>() > MQ + R) {
        MQDungeonCount.SetSelectedIndex((currentSetting == &MQDungeonCount && (kDown & KEY_DRIGHT)) ? 13 : MQ + R);
      }
    } else {
      for (Option *option : dungeonOptions) {
        option->SetSelectedIndex(2);
        option->Hide();
      }
    }

    //Force Link's Pocket Item to be a dungeon reward if Shuffle Rewards is end of dungeons
    if (ShuffleRewards.Is(REWARDSHUFFLE_END_OF_DUNGEON)) {
      LinksPocketItem.Lock();
      LinksPocketItem.SetSelectedIndex(LINKSPOCKETITEM_DUNGEON_REWARD);
      if (RandomizeShuffle) {
        //Even if it is supposed to be locked, still hide it to keep the surprise
        LinksPocketItem.Unlock();
        LinksPocketItem.Hide();
      }
    } else {
      LinksPocketItem.Unlock();
    }

    if (!RandomizeDungeon) {
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
    }

    //Only show Skip Song Replays if Quick Text is enabled
    if (QuickText.Is(QUICKTEXT_VANILLA)) {
      SkipSongReplays.SetSelectedIndex(DONT_SKIP);
      SkipSongReplays.Hide();
    } else {
      SkipSongReplays.Unhide();
    }

    //Only show hint options if hints are enabled
    if (GossipStoneHints.Is(HINTS_NO_HINTS)) {
      ClearerHints.Hide();
      HintDistribution.Hide();
    } else {
      ClearerHints.Unhide();
      HintDistribution.Unhide();
    }

    if (RemoveDoubleDefense) {
      StartingDoubleDefense.SetSelectedIndex(0);
      StartingDoubleDefense.Lock();
    } else {
      StartingDoubleDefense.Unlock();
    }

    if (currentSetting != nullptr) {
      if ((kDown & KEY_DLEFT || kDown & KEY_DRIGHT) && currentSetting->GetName() == "All Tricks")  {
        for (u16 i = 1; i < Settings::trickOptions.size(); i++) {
          trickOptions[i]->SetSelectedIndex(0);
        }
        if(currentSetting->GetSelectedOptionIndex() >= 1){ //novice options
          LogicGrottosWithoutAgony.SetSelectedIndex(1);
          LogicVisibleCollision.SetSelectedIndex(1);
          LogicFewerTunicRequirements.SetSelectedIndex(1);
          LogicLostWoodsGSBean.SetSelectedIndex(1);
          LogicLabDiving.SetSelectedIndex(1);
          LogicGraveyardPoH.SetSelectedIndex(1);
          LogicManOnRoof.SetSelectedIndex(1);
          LogicGoronCityLeftMost.SetSelectedIndex(1);
          LogicZoraRiverLower.SetSelectedIndex(1);
          LogicZoraRiverUpper.SetSelectedIndex(1);
          LogicDekuB1WebsWithBow.SetSelectedIndex(1);
          LogicDCJump.SetSelectedIndex(1);
          LogicForestOutdoorEastGS.SetSelectedIndex(1);
          LogicFireScarecrow.SetSelectedIndex(1);
          LogicWaterTempleTorchLongshot.SetSelectedIndex(1);
          LogicWaterCentralGSFW.SetSelectedIndex(1);
          LogicWaterNorthBasementLedgeJump.SetSelectedIndex(1);
          LogicWaterRiverGS.SetSelectedIndex(1);
          LogicSpiritLowerAdultSwitch.SetSelectedIndex(1);
          LogicShadowStatue.SetSelectedIndex(1);
          LogicChildDeadhand.SetSelectedIndex(1);
          LogicGtgWithoutHookshot.SetSelectedIndex(1);
          LogicGtgFakeWall.SetSelectedIndex(1);
          LogicLensSpirit.SetSelectedIndex(1);
          LogicLensShadow.SetSelectedIndex(1);
          LogicLensGtg.SetSelectedIndex(1);
          LogicLensJabuMQ.SetSelectedIndex(1);
          LogicLensSpiritMQ.SetSelectedIndex(1);
          LogicLensShadowMQ.SetSelectedIndex(1);
          LogicLensBotwMQ.SetSelectedIndex(1);
          LogicLensGtgMQ.SetSelectedIndex(1);
        } 
        if(currentSetting->GetSelectedOptionIndex() >= 2){ //intermediate options
          LogicLabWallGS.SetSelectedIndex(1);
          LogicChildDampeRacePoH.SetSelectedIndex(1);
          LogicGerudoKitchen.SetSelectedIndex(1);
          LogicOutsideGanonsGS.SetSelectedIndex(1);
          LogicDMTSoilGS.SetSelectedIndex(1);
          LogicLinkGoronDins.SetSelectedIndex(1);
          LogicGoronCityPotWithStrength.SetSelectedIndex(1);
          LogicCraterUpperToLower.SetSelectedIndex(1);
          LogicBiggoronBolero.SetSelectedIndex(1);
          LogicDekuB1Skip.SetSelectedIndex(1);
          LogicDekuBasementGS.SetSelectedIndex(1);
          LogicDCStaircase.SetSelectedIndex(1);
          LogicDCScarecrowGS.SetSelectedIndex(1);
          LogicJabuBossGSAdult.SetSelectedIndex(1);
          LogicJabuScrubJumpDive.SetSelectedIndex(1);
          LogicForestOutsideBackdoor.SetSelectedIndex(1);
          LogicForestDoorFrame.SetSelectedIndex(1);
          LogicFireBossDoorJump.SetSelectedIndex(1);
          LogicFireSongOfTime.SetSelectedIndex(1);
          LogicWaterCentralBow.SetSelectedIndex(1);
          LogicWaterBossKeyRegion.SetSelectedIndex(1);
          LogicWaterBKJumpDive.SetSelectedIndex(1);
          LogicWaterFallingPlatformGS.SetSelectedIndex(1);
          LogicSpiritChildBombchu.SetSelectedIndex(1);
          LogicSpiritLobbyGS.SetSelectedIndex(1);
          LogicSpiritMapChest.SetSelectedIndex(1);
          LogicShadowFreestandingKey.SetSelectedIndex(1);
          LogicLensShadowBack.SetSelectedIndex(1);
          LogicLensBotw.SetSelectedIndex(1);
          LogicLensCastle.SetSelectedIndex(1);
          LogicLensShadowMQBack.SetSelectedIndex(1);
          LogicLensCastleMQ.SetSelectedIndex(1);
          LogicSpiritTrialHookshot.SetSelectedIndex(1);
        }
        if(currentSetting->GetSelectedOptionIndex() == 3){ //expert options
          LogicLensWasteland.SetSelectedIndex(1);
          LogicReverseWasteland.SetSelectedIndex(1);
          LogicColossusGS.SetSelectedIndex(1);
          LogicDMTBombable.SetSelectedIndex(1);
          LogicGoronCityPot.SetSelectedIndex(1);
          LogicChildRollingWithStrength.SetSelectedIndex(1);
          LogicCraterBeanPoHWithHovers.SetSelectedIndex(1);
          LogicDCSlingshotSkip.SetSelectedIndex(1);
          LogicFireStrength.SetSelectedIndex(1);
          LogicFireFlameMaze.SetSelectedIndex(1);
          LogicWaterTempleUpperBoost.SetSelectedIndex(1);
          LogicWaterCrackedWallNothing.SetSelectedIndex(1);
          LogicWaterCrackedWallHovers.SetSelectedIndex(1);
          LogicWaterDragonAdult.SetSelectedIndex(1);
          LogicWaterDragonJumpDive.SetSelectedIndex(1);
          LogicSpiritWall.SetSelectedIndex(1);
          LogicSpiritSunChest.SetSelectedIndex(1);
          LogicShadowFireArrowEntry.SetSelectedIndex(1);
          LogicShadowUmbrella.SetSelectedIndex(1);
        }
      }
    }

    //Tunic Colors
    if (CustomTunicColors) {
      ChildTunicColor.Unhide();
      KokiriTunicColor.Unhide();
      GoronTunicColor.Unhide();
      ZoraTunicColor.Unhide();
    } else {
      ChildTunicColor.Hide();
      KokiriTunicColor.Hide();
      GoronTunicColor.Hide();
      ZoraTunicColor.Hide();
      ChildTunicColor.SetSelectedIndex(3);  //Kokiri Green
      KokiriTunicColor.SetSelectedIndex(3); //Kokiri Green
      GoronTunicColor.SetSelectedIndex(4);  //Goron Red
      ZoraTunicColor.SetSelectedIndex(5);   //Zora Blue
    }

    // Music
    if (ShuffleMusic) {
      ShuffleBGM.Unhide();
      ShuffleFanfares.Unhide();
      if(ShuffleFanfares.Is(2)) // Fanfares + ocarina
        ShuffleOcaMusic.Hide();
      else
        ShuffleOcaMusic.Unhide();
    } else {
      ShuffleBGM.Hide();
      ShuffleFanfares.Hide();
      ShuffleOcaMusic.Hide();
    }

    ResolveExcludedLocationConflicts();
  }

  bool IsMQOption(Option *option) {
    return option == &MQDungeonCount  ||
           option == &SetDungeonTypes ||
           option == &MQDeku          ||
           option == &MQDodongo       ||
           option == &MQJabu          ||
           option == &MQForest        ||
           option == &MQFire          ||
           option == &MQWater         ||
           option == &MQSpirit        ||
           option == &MQShadow        ||
           option == &MQBotW          ||
           option == &MQIceCavern     ||
           option == &MQGTG           ||
           option == &MQCastle;
  }

  // Randomizes all settings in a category if chosen
  // Hides all relevant options
  void RandomizeAllSettings(const bool selectOptions /*= false*/) {

    // Open Settings
    if (RandomizeOpen) {
      // Skip RandomizeOpen Option
      for (size_t i = 1; i < openOptions.size(); i++) {
        //hide options
        openOptions[i]->Hide();

        //randomize options
        if (selectOptions) {
          openOptions[i]->SetSelectedIndex(Random(0,openOptions[i]->GetOptionCount()));
        }
      }
      // Randomize Ganon Trials
      RandomGanonsTrials.SetSelectedIndex(ON);
    }
    else {
      for (size_t i = 1; i < openOptions.size(); i++) {
        openOptions[i]->Unhide();
      }
    }

    // World Settings
    if (RandomizeWorld) {
      // Skip RandomizeWorld Option
      for (size_t i=1; i < worldOptions.size(); i++) {
        // skip MQ options
        if (IsMQOption(worldOptions[i])) {
          continue;
        }
        worldOptions[i]->Hide();
        //randomize options
        if (selectOptions) {
          worldOptions[i]->SetSelectedIndex(Random(0,worldOptions[i]->GetOptionCount()));
        }
      }
    }
    else {
      for (size_t i=1; i < worldOptions.size(); i++) {
        if (IsMQOption(worldOptions[i])) {
          continue;
        }
        worldOptions[i]->Unhide();
      }
    }

    // Shuffle Settings
    if (RandomizeShuffle) {
      // Still displays if previously locked
      LinksPocketItem.Unlock();
      // Skip RandomizeShuffle Option
      for (size_t i=1; i < shuffleOptions.size(); i++) {
        shuffleOptions[i]->Hide();
        //randomize options
        if (selectOptions) {
          shuffleOptions[i]->SetSelectedIndex(Random(0,shuffleOptions[i]->GetOptionCount()));
        }
      }
      // Double check that this is the case in case of randomization on init
      if (ShuffleRewards.Is(REWARDSHUFFLE_END_OF_DUNGEON)) {
        LinksPocketItem.SetSelectedIndex(LINKSPOCKETITEM_DUNGEON_REWARD);
      }
    }
    else {
      for (size_t i=1; i < shuffleOptions.size(); i++) {
        shuffleOptions[i]->Unhide();
      }
    }

    // Dungeon Shuffle Settings
    if (RandomizeDungeon) {
      // Skip RandomizeDungeon Option
      for (size_t i=1; i < shuffleDungeonItemOptions.size(); i++) {
        shuffleDungeonItemOptions[i]->Hide();
        //randomize options
        if (selectOptions) {
          shuffleDungeonItemOptions[i]->SetSelectedIndex(Random(0,shuffleDungeonItemOptions[i]->GetOptionCount()));
        }
      }
    }
    else {
      for (size_t i=1; i < shuffleDungeonItemOptions.size(); i++) {
        shuffleDungeonItemOptions[i]->Unhide();
      }
    }

    //resolve any settings that need to change
    if (selectOptions) {
      ForceChange(0, nullptr);
    }
  }

  //eventual settings
  bool ShuffleInteriorEntrances         = false;
  bool ShuffleSpecialIndoorEntrances    = false;

  template <typename colorsArray>
  static void ChooseFinalColor(const Option& cosmeticOption, std::string& colorStr, const colorsArray& colors) {
    if (cosmeticOption.Is(CUSTOM_COLOR)) {
      colorStr = GetCustomColor(cosmeticOption.GetSelectedOptionText());
    } else if (cosmeticOption.Is(RANDOM_CHOICE)) {
      colorStr = colors[rand() % colors.size()]; //use default rand to not interfere with seed
    } else if (cosmeticOption.Is(RANDOM_COLOR)) {
      colorStr = RandomColor();
    } else {
      colorStr = colors[cosmeticOption.GetSelectedOptionIndex() - NON_COLOR_COUNT];
    }
  }

  //Function to update cosmetics options depending on choices
  static void UpdateCosmetics() {

    ChooseFinalColor(ChildTunicColor, finalChildTunicColor, tunicColors);
    ChooseFinalColor(KokiriTunicColor, finalKokiriTunicColor, tunicColors);
    ChooseFinalColor(GoronTunicColor, finalGoronTunicColor, tunicColors);
    ChooseFinalColor(ZoraTunicColor, finalZoraTunicColor, tunicColors);
    ChooseFinalColor(SilverGauntletsColor, finalSilverGauntletsColor, gauntletColors);
    ChooseFinalColor(GoldGauntletsColor, finalGoldGauntletsColor, gauntletColors);
  }

  //Function to set flags depending on settings
  void UpdateSettings() {

    RandomizeAllSettings(true); //now select any random options instead of just hiding them

    //shuffle the dungeons and then set MQ for as many as necessary
    auto dungeons = dungeonList;
    if (SetDungeonTypes) {
      MQSet = MQDungeonCount.Value<u8>();
      u8 dungeonCount = 0;
      std::vector<u8> randMQOption = {};

      for (size_t i = 0; i < dungeons.size(); i++) {
        dungeons[i]->ClearMQ();

        switch (dungeonOptions[i]->Value<u8>()) {
          case 1:
            // Set MQ dungeons and track how many have been set
            dungeons[i]->SetMQ();
            dungeonCount++;
            break;
          case 2:
            // Track indexes of dungeons set to random
            randMQOption.push_back(i);
            break;
        }
      }

      // Add more MQ dungeons from the pool set to random until the MQ dungeon count is reached
      Shuffle(randMQOption);

      if (MQSet == 13) {
        MQSet = dungeonCount + Random(0, randMQOption.size() + 1);
      }

      for (u8 i = 0; dungeonCount < MQSet; i++) {
        dungeons[randMQOption[i]]->SetMQ();
        dungeonCount++;
      }
    } else {
      Shuffle(dungeons);
      MQSet = MQDungeonCount.Value<u8>();

      //Clear MQ dungeons
      for (size_t i = 0; i < dungeons.size(); i++) {
        dungeons[i]->ClearMQ();
      }

      //Set appropriate amount of MQ dungeons
      if (MQSet == 13) {
        MQSet = Random(0, 13);
      }
      for (u8 i = 0; i < MQSet; i++) {
        dungeons[i]->SetMQ();
      }
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

    //If vanilla logic, we want to set all settings which unnecessarily modify vanilla behavior to off
    if (Logic.Is(LOGIC_VANILLA)) {
      ShuffleRewards.SetSelectedIndex(0);
      LinksPocketItem.SetSelectedIndex(0);
      ShuffleSongs.SetSelectedIndex(0);
      Scrubsanity.SetSelectedIndex(0);
      ShuffleCows.SetSelectedIndex(0);
      ShuffleMagicBeans.SetSelectedIndex(0);
      ShuffleMerchants.SetSelectedIndex(0);
      Keysanity.SetSelectedIndex(3); //Set small keys to any dungeon so FiT basement door will be locked
      GossipStoneHints.SetSelectedIndex(0);
    }

    InitMusicRandomizer();
    if (ShuffleMusic) {
      if (ShuffleBGM) {
        ShuffleSequences(SeqType::SEQ_BGM);
      }
      
      if (ShuffleFanfares.Is(2)) {
        ShuffleSequences(SeqType::SEQ_FANFARE | SeqType::SEQ_OCARINA);
      } else {
        if (ShuffleFanfares.Is(1)) {
          ShuffleSequences(SeqType::SEQ_FANFARE);
        }
        
        if (ShuffleOcaMusic) {
          ShuffleSequences(SeqType::SEQ_OCARINA);
        }
      }
    }
  }

  //If this is an option menu, return th options
  //Else, recursively call each sub menu of this sub menu
  const std::vector<Menu*> GetMenusRecursive(Menu* menu) {
    std::vector<Menu*> menus;
    if (menu->mode == OPTION_SUB_MENU) {
      menus.push_back(menu);
    } else if (menu->mode == SUB_MENU) {
        for (Menu* subMenu : *menu->itemsList) {
          std::vector<Menu*> foundMenus = GetMenusRecursive(subMenu);
          menus.insert(menus.end(), foundMenus.begin(), foundMenus.end());
        }
    }
    return menus;
  }

  //Recursively look through each menu from the main menu to get all settings
  const std::vector<Menu*> GetAllMenus() {
    std::vector<Menu*> allMenus;
    for (Menu* menu : Settings::mainMenu) {
      std::vector<Menu*> foundMenus = GetMenusRecursive(menu);
      allMenus.insert(allMenus.end(), foundMenus.begin(), foundMenus.end());
    }
    return allMenus;
  }

} // namespace Settings
