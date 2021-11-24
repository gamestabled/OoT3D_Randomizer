#include "settings.hpp"

#include <unistd.h>

#include "cosmetics.hpp"
#include "dungeon.hpp"
#include "fill.hpp"
#include "item_location.hpp"
#include "music.hpp"
#include "sound_effects.hpp"
#include "random.hpp"
#include "randomizer.hpp"
#include "setting_descriptions.hpp"
#include "trial.hpp"
#include "keys.hpp"

using namespace Cosmetics;
using namespace Dungeon;
using namespace Trial;
using namespace Music;
using namespace SFX;

namespace Settings {
  std::string seed;
  std::string version = RANDOMIZER_VERSION "-" COMMIT_NUMBER;
  std::array<u8, 5> hashIconIndexes;

  //                                        Setting name,              Options,                                                                     Setting Descriptions (assigned in setting_descriptions.cpp)                                                 Category (default: Setting),Default index (default: 0), Default hidden (default: false)
  //Open Settings                                                                                                                                   Any option index past the last description will use the last description
  Option RandomizeOpen       = Option::Bool("Randomize Settings",     {"No","Yes"},                                                                 {openRandomize},                                                                                            OptionCategory::Toggle);
  Option OpenForest          = Option::U8  ("Forest",                 {"Closed", "Open", "Closed Deku"},                                            {forestClosed, forestOpen, forestClosedDeku},                                                               OptionCategory::Setting,    OPENFOREST_OPEN);
  Option OpenKakariko        = Option::U8  ("Kakariko Gate",          {"Closed", "Open"},                                                           {kakGateClosed, kakGateOpen});
  Option OpenDoorOfTime      = Option::U8  ("Door of Time",           {"Open", "Closed", "Intended"},                                               {doorOfTimeOpen, doorOfTimeClosed, doorOfTimeIntended});
  Option ZorasFountain       = Option::U8  ("Zora's Fountain",        {"Normal", "Adult", "Open"},                                                  {fountainNormal, fountainAdult, fountainOpen});
  Option GerudoFortress      = Option::U8  ("Gerudo Fortress",        {"Normal", "Fast", "Open"},                                                   {gerudoNormal, gerudoFast, gerudoOpen});
  Option Bridge              = Option::U8  ("Rainbow Bridge",         {"Open", "Vanilla", "Stones", "Medallions", "Rewards", "Dungeons", "Tokens"}, {bridgeOpen, bridgeVanilla, bridgeStones, bridgeMedallions, bridgeRewards, bridgeDungeons, bridgeTokens},   OptionCategory::Setting,    RAINBOWBRIDGE_VANILLA);
  Option BridgeStoneCount    = Option::U8  ("  Stone Count",          {"0", "1", "2", "3"},                                                         {bridgeStoneCountDesc},                                                                                     OptionCategory::Setting,    1,                          true);
  Option BridgeMedallionCount= Option::U8  ("  Medallion Count",      {"0", "1", "2", "3", "4", "5", "6"},                                          {bridgeMedallionCountDesc},                                                                                 OptionCategory::Setting,    1,                          true);
  Option BridgeRewardCount   = Option::U8  ("  Reward Count",         {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"},                           {bridgeRewardCountDesc},                                                                                    OptionCategory::Setting,    1,                          true);
  Option BridgeDungeonCount  = Option::U8  ("  Dungeon Count",        {"0", "1", "2", "3", "4", "5", "6", "7", "8"},                                {bridgeDungeonCountDesc},                                                                                   OptionCategory::Setting,    1,                          true);
  Option BridgeTokenCount    = Option::U8  ("  Token Count",          {/*Options 0-100 defined in InitSettings()*/},                                {bridgeTokenCountDesc},                                                                                     OptionCategory::Setting,    1,                          true);
  Option RandomGanonsTrials  = Option::Bool("Random Ganon's Trials",  {"Off", "On"},                                                                {randomGanonsTrialsDesc},                                                                                   OptionCategory::Setting,    ON);
  Option GanonsTrialsCount   = Option::U8  ("  Trial Count",          {"0", "1", "2", "3", "4", "5", "6"},                                          {ganonsTrialCountDesc},                                                                                     OptionCategory::Setting,    1,                          true);
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
  Option RandomizeWorld            = Option::Bool("Randomize Settings",     {"No","Yes"},                                                      {worldRandomize},                                                                                                OptionCategory::Toggle);
  Option StartingAge               = Option::U8  ("Starting Age",           {"Adult", "Child", "Random"},                                      {ageDesc},                                                                                                       OptionCategory::Setting,    AGE_CHILD);
  u8 ResolvedStartingAge;
  Option ShuffleEntrances          = Option::Bool("Shuffle Entrances",      {"Off", "On"},                                                     {shuffleEntrancesDesc});
  Option ShuffleDungeonEntrances   = Option::Bool("  Dungeon Entrances",    {"Off", "On"},                                                     {dungeonEntrancesDesc});
  Option ShuffleOverworldEntrances = Option::Bool("  Overworld Entrances",  {"Off", "On"},                                                     {overworldEntrancesDesc});
  Option ShuffleInteriorEntrances  = Option::U8  ("  Interior Entrances",   {"Off", "Simple", "All"},                                          {interiorEntrancesOff, interiorEntrancesSimple, interiorEntrancesAll});
  Option ShuffleGrottoEntrances    = Option::Bool("  Grottos Entrances",    {"Off", "On"},                                                     {grottoEntrancesDesc});
  Option BombchusInLogic           = Option::Bool("Bombchus in Logic",      {"Off", "On"},                                                     {bombchuLogicDesc});
  Option AmmoDrops                 = Option::U8  ("Ammo Drops",             {"On", "On + Bombchu", "Off"},                                     {defaultAmmoDropsDesc, bombchuDropsDesc, noAmmoDropsDesc},                                                       OptionCategory::Setting,    AMMODROPS_BOMBCHU);
  Option HeartDropRefill           = Option::U8  ("Heart Drops and Refills",{"On", "No Drop", "No Refill", "Off"},                             {defaultHeartDropsDesc, noHeartDropsDesc, noHeartRefillDesc, scarceHeartsDesc},                                  OptionCategory::Setting,    HEARTDROPREFILL_VANILLA);
  Option MQDungeonCount            = Option::U8  ("MQ Dungeon Count",       {"0","1","2","3","4","5","6","7","8","9","10","11","12", "Random"},{mqDungeonCountDesc});
  u8 MQSet;
  bool DungeonModesKnown;
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
    &ShuffleInteriorEntrances,
    &ShuffleGrottoEntrances,
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
  Option RandomizeShuffle       = Option::Bool("Randomize Settings",     {"No","Yes"},                                                      {shuffleRandomize},                                                                                                    OptionCategory::Toggle);
  Option ShuffleRewards         = Option::U8  ("Shuffle Dungeon Rewards",{"End of Dungeons", "Any Dungeon", "Overworld", "Anywhere"},       {shuffleRewardsEndOfDungeon, shuffleRewardsAnyDungeon, shuffleRewardsOverworld, shuffleRewardsAnywhere});
  Option LinksPocketItem        = Option::U8  ("Link's Pocket",          {"Dungeon Reward", "Advancement", "Anything", "Nothing"},          {linksPocketDungeonReward, linksPocketAdvancement, linksPocketAnything, linksPocketNothing});
  Option ShuffleSongs           = Option::U8  ("Shuffle Songs",          {"Song Locations", "Dungeon Rewards", "Anywhere"},                 {songsSongLocations, songsDungeonRewards, songsAllLocations});
  Option Shopsanity             = Option::U8  ("Shopsanity",             {"Off", "0", "1", "2", "3", "4", "Random"},                        {shopsOff, shopsZero, shopsOne, shopsTwo, shopsThree, shopsFour, shopsRandom});
  Option Tokensanity            = Option::U8  ("Tokensanity",            {"Off", "Dungeons", "Overworld", "All Tokens"},                    {tokensOff, tokensDungeon, tokensOverworld, tokensAllTokens});
  Option Scrubsanity            = Option::U8  ("Scrub Shuffle",          {"Off", "Affordable", "Expensive", "Random Prices"},               {scrubsOff, scrubsAffordable, scrubsExpensive, scrubsRandomPrices});
  Option ShuffleCows            = Option::Bool("Shuffle Cows",           {"Off", "On"},                                                     {shuffleCowsDesc});
  Option ShuffleKokiriSword     = Option::Bool("Shuffle Kokiri Sword",   {"Off", "On"},                                                     {kokiriSwordDesc});
  Option ShuffleOcarinas        = Option::Bool("Shuffle Ocarinas",       {"Off", "On"},                                                     {ocarinasDesc});
  Option ShuffleWeirdEgg        = Option::Bool("Shuffle Weird Egg",      {"Off", "On"},                                                     {weirdEggDesc});
  Option ShuffleGerudoToken     = Option::Bool("Shuffle Gerudo Token",   {"Off", "On"},                                                     {gerudoTokenDesc});
  Option ShuffleMagicBeans      = Option::Bool("Shuffle Magic Beans",    {"Off", "On"},                                                     {magicBeansDesc});
  Option ShuffleMerchants       = Option::U8  ("Shuffle Merchants",      {"Off", "On (No Hints)", "On (With Hints)"},                       {merchantsDesc, merchantsHintsDesc});
  Option ShuffleAdultTradeQuest = Option::Bool("Shuffle Adult Trade",    {"Off", "On"},                                                     {adultTradeDesc});
  Option ShuffleChestMinigame   = Option::U8  ("Shuffle Chest Minigame", {"Off", "On (Separate)", "On (Pack)"},                             {chestMinigameDesc});
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
    &ShuffleAdultTradeQuest,
    &ShuffleChestMinigame,
  };

  //Shuffle Dungeon Items
  Option RandomizeDungeon    = Option::Bool("Randomize Settings",     {"No","Yes"},                                                      {dungeonRandomize},                                                                                                    OptionCategory::Toggle);
  Option MapsAndCompasses    = Option::U8  ("Maps/Compasses",         {"Start With", "Vanilla", "Own Dungeon", "Any Dungeon", "Overworld", "Anywhere"},
                                                                      {mapCompassStartWith, mapCompassVanilla, mapCompassOwnDungeon, mapCompassAnyDungeon, mapCompassOverworld, mapCompassAnywhere},                                                            OptionCategory::Setting,    MAPSANDCOMPASSES_OWN_DUNGEON);
  Option Keysanity           = Option::U8  ("Small Keys",             {"Start With", "Vanilla", "Own Dungeon", "Any Dungeon", "Overworld", "Anywhere"},
                                                                      {smallKeyStartWith, smallKeyVanilla, smallKeyOwnDungeon, smallKeyAnyDungeon, smallKeyOverworld, smallKeyAnywhere},                                                                        OptionCategory::Setting,    KEYSANITY_OWN_DUNGEON);
  Option GerudoKeys          = Option::U8  ("Gerudo Fortress Keys",   {"Vanilla", "Any Dungeon", "Overworld", "Anywhere"},
                                                                      {gerudoKeysVanilla, gerudoKeysAnyDungeon, gerudoKeysOverworld, gerudoKeysAnywhere});
  Option BossKeysanity       = Option::U8  ("Boss Keys",              {"Start With", "Vanilla", "Own Dungeon", "Any Dungeon", "Overworld", "Anywhere"},
                                                                      {bossKeyStartWith, bossKeyVanilla, bossKeyOwnDungeon, bossKeyAnyDungeon, bossKeyOverworld, bossKeyAnywhere},                                                                              OptionCategory::Setting,    BOSSKEYSANITY_OWN_DUNGEON);
  Option GanonsBossKey       = Option::U8  ("Ganon's Boss Key",       {"Start With", "Vanilla", "Own Dungeon", "Any Dungeon", "Overworld", "Anywhere", "LACS-Vanilla", "LACS-Medallions", "LACS-Stones", "LACS-Rewards", "LACS-Dungeons", "LACS-Tokens"},
                                                                      {ganonKeyStartWith, ganonKeyVanilla, ganonKeyOwnDungeon, ganonKeyAnyDungeon, ganonKeyOverworld, ganonKeyAnywhere, ganonKeyLACS},                                                          OptionCategory::Setting,    GANONSBOSSKEY_OWN_DUNGEON);
  u8 LACSCondition           = 0;
  Option LACSMedallionCount  = Option::U8  ("  Medallion Count",      {"0", "1", "2", "3", "4", "5", "6"},                                    {lacsMedallionCountDesc},                                                                                         OptionCategory::Setting,    1,                          true);
  Option LACSStoneCount      = Option::U8  ("  Stone Count",          {"0", "1", "2", "3"},                                                   {lacsStoneCountDesc},                                                                                             OptionCategory::Setting,    1,                          true);
  Option LACSRewardCount     = Option::U8  ("  Reward Count",         {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"},                     {lacsRewardCountDesc},                                                                                            OptionCategory::Setting,    1,                          true);
  Option LACSDungeonCount    = Option::U8  ("  Dungeon Count",        {"0", "1", "2", "3", "4", "5", "6", "7", "8"},                          {lacsDungeonCountDesc},                                                                                           OptionCategory::Setting,    1,                          true);
  Option LACSTokenCount      = Option::U8  ("  Token Count",          {/*Options 0-100 defined in InitSettings()*/},                          {lacsTokenCountDesc},                                                                                             OptionCategory::Setting,    1,                          true);

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
  Option SkipChildStealth    = Option::Bool("Skip Child Stealth",     {"Don't Skip", "Skip"},                                                 {childStealthDesc},                                                                                               OptionCategory::Setting,    SKIP);
  Option SkipTowerEscape     = Option::Bool("Skip Tower Escape",      {"Don't Skip", "Skip"},                                                 {skipTowerEscapeDesc},                                                                                            OptionCategory::Setting,    SKIP);
  Option SkipEponaRace       = Option::Bool("Skip Epona Race",        {"Don't Skip", "Skip"},                                                 {skipEponaRaceDesc});
  Option SkipMinigamePhases  = Option::Bool("Minigames repetitions",  {"Don't Skip", "Skip"},                                                 {skipMinigamePhasesDesc});
  Option FreeScarecrow       = Option::Bool("Free Scarecrow",         {"Off", "On"},                                                          {freeScarecrowDesc});
  Option FourPoesCutscene    = Option::Bool("Four Poes Cutscene",     {"Don't Skip", "Skip"},                                                 {fourPoesDesc},                                                                                                   OptionCategory::Setting,    SKIP);
  Option LakeHyliaOwl        = Option::Bool("Lake Hylia Owl",         {"Don't Skip", "Skip"},                                                 {lakeHyliaOwlDesc},                                                                                               OptionCategory::Setting,    SKIP);
  Option BigPoeTargetCount   = Option::U8  ("Big Poe Target Count",   {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"},                    {bigPoeTargetCountDesc});
  Option NumRequiredCuccos   = Option::U8  ("Cuccos to return",       {"0", "1", "2", "3", "4", "5", "6", "7"},                               {numRequiredCuccosDesc});
  Option KingZoraSpeed       = Option::U8  ("King Zora Speed",        {"Fast", "Vanilla", "Random"},                                          {kingZoraSpeedFast, kingZoraSpeedVanilla, kingZoraSpeedRandom});
  Option CompleteMaskQuest   = Option::Bool("Complete Mask Quest",    {"Off", "On"},                                                          {completeMaskDesc});
  Option QuickText           = Option::U8  ("Quick Text",             {"0: Vanilla", "1: Skippable", "2: Instant", "3: Turbo"},               {quickTextDesc0, quickTextDesc1, quickTextDesc2, quickTextDesc3},                                                 OptionCategory::Setting,    QUICKTEXT_INSTANT);
  Option SkipSongReplays     = Option::U8  ("  Skip Song Replays",    {"Don't Skip", "Skip (No SFX)", "Skip (Keep SFX)"},                     {skipSongReplaysDesc});
  Option KeepFWWarpPoint     = Option::Bool("Keep FW Warp Point",     {"Off", "On"},                                                          {keepFWWarpPointDesc});
  std::vector<Option *> timesaverOptions = {
    &SkipChildStealth,
    &SkipTowerEscape,
    &SkipEponaRace,
    &SkipMinigamePhases,
    &FreeScarecrow,
    &FourPoesCutscene,
    &LakeHyliaOwl,
    &BigPoeTargetCount,
    &NumRequiredCuccos,
    &KingZoraSpeed,
    &CompleteMaskQuest,
    &QuickText,
    &SkipSongReplays,
    &KeepFWWarpPoint,
  };

  //Misc Settings
  Option GossipStoneHints    = Option::U8  ("Gossip Stone Hints",     {"No Hints", "Need Nothing", "Mask of Truth", "Shard of Agony"},        {gossipStonesHintsDesc},                                                                                          OptionCategory::Setting,    HINTS_NEED_NOTHING);
  Option ClearerHints        = Option::U8  ("  Hint Clarity",         {"Obscure", "Ambiguous", "Clear"},                                      {obscureHintsDesc, ambiguousHintsDesc, clearHintsDesc});
  Option HintDistribution    = Option::U8  ("  Hint Distribution",    {"Useless", "Balanced", "Strong", "Very Strong"},                       {uselessHintsDesc, balancedHintsDesc, strongHintsDesc, veryStrongHintsDesc},                                      OptionCategory::Setting,    1); // Balanced
  Option CompassesShowReward = Option::U8  ("Compasses Show Rewards", {"No", "Yes"},                                                          {compassesShowRewardsDesc},                                                                                       OptionCategory::Setting,    1);
  Option CompassesShowWotH   = Option::U8  ("Compasses Show WotH",    {"No", "Yes"},                                                          {compassesShowWotHDesc},                                                                                          OptionCategory::Setting,    1);
  Option MapsShowDungeonMode = Option::U8  ("Maps Show Dungeon Modes",{"No", "Yes"},                                                          {mapsShowDungeonModesDesc},                                                                                       OptionCategory::Setting,    1);
  Option DamageMultiplier    = Option::U8  ("Damage Multiplier",      {"x1/2", "x1", "x2", "x4", "x8", "x16", "OHKO"},                        {damageMultiDesc},                                                                                                OptionCategory::Setting,    DAMAGEMULTIPLIER_DEFAULT);
  Option StartingTime        = Option::U8  ("Starting Time",          {"Day", "Night"},                                                       {startingTimeDesc});
  Option ChestAnimations     = Option::Bool("Chest Animations",       {"Always Fast", "Match Contents"},                                      {chestAnimDesc});
  Option ChestSize           = Option::Bool("Chest Size and Color",   {"Vanilla", "Match Contents"},                                          {chestSizeDesc});
  Option GenerateSpoilerLog  = Option::Bool("Generate Spoiler Log",   {"No", "Yes"},                                                          {"", ""},                                                                                                         OptionCategory::Setting,    1); // On
  Option IngameSpoilers      = Option::Bool("Ingame Spoilers",        {"Hide", "Show"},                                                       {ingameSpoilersHideDesc, ingameSpoilersShowDesc });
  Option MenuOpeningButton   = Option::U8  ("Open Info Menu with",    {"Select","Start","D-Pad Up","D-Pad Down","D-Pad Right","D-Pad Left",}, {menuButtonDesc});
  Option RandomTrapDmg       = Option::U8  ("Random Trap Damage",     {"Off", "Basic", "Advanced"},                                           {randomTrapDmgDesc, basicTrapDmgDesc, advancedTrapDmgDesc},                                                       OptionCategory::Setting,    1); // Basic
  bool HasNightStart         = false;
  std::vector<Option *> miscOptions = {
    &GossipStoneHints,
    &ClearerHints,
    &HintDistribution,
    &CompassesShowReward,
    &CompassesShowWotH,
    &MapsShowDungeonMode,
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
  Option ItemPoolValue         = Option::U8  ("Item Pool",             {"Plentiful", "Balanced", "Scarce", "Minimal"},                        {itemPoolPlentiful, itemPoolBalanced, itemPoolScarce, itemPoolMinimal},                                           OptionCategory::Setting,    ITEMPOOL_BALANCED);
  Option IceTrapValue          = Option::U8  ("Ice Traps",             {"Off", "Normal", "Extra", "Mayhem", "Onslaught"},                     {iceTrapsOff, iceTrapsNormal, iceTrapsExtra, iceTrapsMayhem, iceTrapsOnslaught},                                  OptionCategory::Setting,    ICETRAPS_NORMAL);
  Option RemoveDoubleDefense   = Option::Bool("Remove Double Defense", {"No", "Yes"},                                                         {removeDDDesc});
  Option ProgressiveGoronSword = Option::Bool("Prog Goron Sword",      {"Disabled", "Enabled"},                                               {progGoronSword});
  std::vector<Option *> itemPoolOptions = {
    &ItemPoolValue,
    &IceTrapValue,
    &RemoveDoubleDefense,
    &ProgressiveGoronSword,
  };

  //Excluded Locations (Individual definitions made in ItemLocation class)
  std::vector<std::vector<Option *>> excludeLocationsOptionsVector(SPOILER_COLLECTION_GROUP_COUNT);
  Menu excludeKokiriForest          = Menu::SubMenu("Kokiri Forest",           &excludeLocationsOptionsVector[GROUP_KOKIRI_FOREST], false);
  Menu excludeLostWoods             = Menu::SubMenu("Lost Woods",              &excludeLocationsOptionsVector[GROUP_LOST_WOODS], false);
  Menu excludeDekuTree              = Menu::SubMenu("Deku Tree",               &excludeLocationsOptionsVector[GROUP_DUNGEON_DEKU_TREE], false);
  Menu excludeForestTemple          = Menu::SubMenu("Forest Temple",           &excludeLocationsOptionsVector[GROUP_DUNGEON_FOREST_TEMPLE], false);
  Menu excludeKakariko              = Menu::SubMenu("Kakariko Village",        &excludeLocationsOptionsVector[GROUP_KAKARIKO], false);
  Menu excludeBottomWell            = Menu::SubMenu("Bottom of the Well",      &excludeLocationsOptionsVector[GROUP_DUNGEON_BOTTOM_OF_THE_WELL], false);
  Menu excludeShadowTemple          = Menu::SubMenu("Shadow Temple",           &excludeLocationsOptionsVector[GROUP_DUNGEON_SHADOW_TEMPLE], false);
  Menu excludeDeathMountain         = Menu::SubMenu("Death Mountain",          &excludeLocationsOptionsVector[GROUP_DEATH_MOUNTAIN], false);
  Menu excludeGoronCity             = Menu::SubMenu("Goron City",              &excludeLocationsOptionsVector[GROUP_GORON_CITY], false);
  Menu excludeDodongosCavern        = Menu::SubMenu("Dodongo's Cavern",        &excludeLocationsOptionsVector[GROUP_DUNGEON_DODONGOS_CAVERN], false);
  Menu excludeFireTemple            = Menu::SubMenu("Fire Temple",             &excludeLocationsOptionsVector[GROUP_DUNGEON_FIRE_TEMPLE], false);
  Menu excludeZorasRiver            = Menu::SubMenu("Zora's River",            &excludeLocationsOptionsVector[GROUP_ZORAS_RIVER], false);
  Menu excludeZorasDomain           = Menu::SubMenu("Zora's Domain",           &excludeLocationsOptionsVector[GROUP_ZORAS_DOMAIN], false);
  Menu excludeJabuJabu              = Menu::SubMenu("Jabu Jabu's Belly",       &excludeLocationsOptionsVector[GROUP_DUNGEON_JABUJABUS_BELLY], false);
  Menu excludeIceCavern             = Menu::SubMenu("Ice Cavern",              &excludeLocationsOptionsVector[GROUP_DUNGEON_ICE_CAVERN], false);
  Menu excludeHyruleField           = Menu::SubMenu("Hyrule Field",            &excludeLocationsOptionsVector[GROUP_HYRULE_FIELD], false);
  Menu excludeLonLonRanch           = Menu::SubMenu("Lon Lon Ranch",           &excludeLocationsOptionsVector[GROUP_LON_LON_RANCH], false);
  Menu excludeLakeHylia             = Menu::SubMenu("Lake Hylia",              &excludeLocationsOptionsVector[GROUP_LAKE_HYLIA], false);
  Menu excludeWaterTemple           = Menu::SubMenu("Water Temple",            &excludeLocationsOptionsVector[GROUP_DUNGEON_WATER_TEMPLE], false);
  Menu excludeGerudoValley          = Menu::SubMenu("Gerudo Valley",           &excludeLocationsOptionsVector[GROUP_GERUDO_VALLEY], false);
  Menu excludeGerudoTrainingGrounds = Menu::SubMenu("Gerudo Training Grounds", &excludeLocationsOptionsVector[GROUP_GERUDO_TRAINING_GROUND], false);
  Menu excludeSpiritTemple          = Menu::SubMenu("Spirit Temple",           &excludeLocationsOptionsVector[GROUP_DUNGEON_SPIRIT_TEMPLE], false);
  Menu excludeHyruleCastle          = Menu::SubMenu("Hyrule Castle",           &excludeLocationsOptionsVector[GROUP_HYRULE_CASTLE], false);
  Menu excludeGanonsCastle          = Menu::SubMenu("Ganon's Castle",          &excludeLocationsOptionsVector[GROUP_DUNGEON_GANONS_CASTLE], false);
  std::vector<Menu *> excludeLocationsMenus = {
    &excludeKokiriForest,
    &excludeLostWoods,
    &excludeDekuTree,
    &excludeForestTemple,
    &excludeKakariko,
    &excludeBottomWell,
    &excludeShadowTemple,
    &excludeDeathMountain,
    &excludeGoronCity,
    &excludeDodongosCavern,
    &excludeFireTemple,
    &excludeZorasRiver,
    &excludeZorasDomain,
    &excludeJabuJabu,
    &excludeIceCavern,
    &excludeHyruleField,
    &excludeLonLonRanch,
    &excludeLakeHylia,
    &excludeWaterTemple,
    &excludeGerudoValley,
    &excludeGerudoTrainingGrounds,
    &excludeSpiritTemple,
    &excludeHyruleCastle,
    &excludeGanonsCastle,
  };

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
  Option StartingBottle4          = Option::U8  ("  Bottle Slot 4",        bottleOptions,                                                                   {""});
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
  Option StartingSkulltulaToken   = Option::U8  ("Gold Skulltula Tokens",  {/*Options 0-100 defined in InitSettings()*/},                                   {""},                                                                                               OptionCategory::Setting,    0,                          false);
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
    &StartingBottle4,
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
  Option LocationsReachable = Option::Bool("All Locations Reachable", {"Off", "On"},                                     {locationsReachableDesc},                                                                                                              OptionCategory::Setting,    1); //All Locations Reachable On
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
  Option ToggleAllTricks                  = Option::U8("All Tricks", {"None", "Novice", "Intermediate", "Expert"},  {ToggleLogicNoneDesc, ToggleLogicNoviceDesc, ToggleLogicIntermediateDesc, ToggleLogicExpertDesc},                                           OptionCategory::Toggle);
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

  //Function to avoid accidentally naming the options wrong, as logic.cpp requires these exact names
  std::vector<std::string> GlitchDifficultyOptions(u8 enabledDifficulties) {
    static constexpr std::array glitchDifficulties{"Novice", "Intermediate", "Advanced", "Expert", "Hero"};

    std::vector<std::string> selectableDifficulties;
    selectableDifficulties.push_back("Disabled");
    for (size_t i = 0; i < glitchDifficulties.size(); i++) {
      if ((enabledDifficulties >> i) & 1) {
        selectableDifficulties.push_back(glitchDifficulties[i]);
      }
    }

    return selectableDifficulties;
  }

  Option GlitchISG                = Option::U8("Infinite Sword Glitch", GlitchDifficultyOptions(0b00001), {GlitchISGDescDisabled, GlitchISGDescNovice});
  Option GlitchHover              = Option::U8("Bomb Hover",            GlitchDifficultyOptions(0b00111), {GlitchHoverDescDisabled, GlitchHoverDescNovice, GlitchHoverDescIntermediate, GlitchHoverDescAdvanced});
  Option GlitchMegaflip           = Option::U8("Megaflip",              GlitchDifficultyOptions(0b00011), {GlitchMegaflipDescDisabled, GlitchMegaflipDescNovice, GlitchMegaflipDescIntermediate});
  Option GlitchHookshotClip       = Option::U8("Hookshot Clip",         GlitchDifficultyOptions(0b00001), {GlitchHookshotClipDescDisabled, GlitchHookshotClipDescNovice});
  Option GlitchHookshotJump_Bonk  = Option::U8("Hookshot Jump (Bonk)",  GlitchDifficultyOptions(0b00010), {GlitchHookshotJump_BonkDescDisabled, GlitchHookshotJump_BonkDescIntermediate});
  Option GlitchHookshotJump_Boots = Option::U8("Hookshot Jump (Boots)", GlitchDifficultyOptions(0b00011), {GlitchHookshotJump_BootsDescDisabled, GlitchHookshotJump_BootsDescNovice, GlitchHookshotJump_BootsDescIntermediate});
  Option GlitchLedgeClip          = Option::U8("Ledge Clip",            GlitchDifficultyOptions(0b00011), {GlitchLedgeClipDescDisabled, GlitchLedgeClipDescNovice, GlitchLedgeClipDescIntermediate});
  Option GlitchTripleSlashClip    = Option::U8("Triple Slash Clip",     GlitchDifficultyOptions(0b00001), {GlitchTripleSlashClipDescDisabled, GlitchTripleSlashClipDescNovice});
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
    "Orange",
    "Yellow",
    "Cyan",
    "Indigo",
    "Purple",
    "Pink",
    "Dark Gray",
    "Salmon",
    "Wine Red",
    "Beige",
    "Brown",
    "Sand",
    "Tea Green",
    "Dark Green",
    "Powder Blue",
    "Teal",
    "Sky Blue",
    "Faded Blue",
    "Lavender",
    "Magenta",
    "Mauve",
    "Silver",
    "Gold"
  };
  static std::vector<std::string_view> cosmeticDescriptions = {
    RANDOM_CHOICE_DESC,
    RANDOM_COLOR_DESC,
    CUSTOM_COLOR_DESC,
    "This will only affect the color on Link's model.",
  };

  Option CustomTunicColors          = Option::Bool("Custom Tunic Colors",    {"Off", "On"},   {""},                                                                                                                                                             OptionCategory::Cosmetic);
  Option ChildTunicColor            = Option::U8  ("  Child Tunic Color",    tunicOptions,    cosmeticDescriptions,                                                                                                                                             OptionCategory::Cosmetic,               3); // Kokiri Green
  Option KokiriTunicColor           = Option::U8  ("  Kokiri Tunic Color",   tunicOptions,    cosmeticDescriptions,                                                                                                                                             OptionCategory::Cosmetic,               3); // Kokiri Green
  Option GoronTunicColor            = Option::U8  ("  Goron Tunic Color",    tunicOptions,    cosmeticDescriptions,                                                                                                                                             OptionCategory::Cosmetic,               4); // Goron Red
  Option ZoraTunicColor             = Option::U8  ("  Zora Tunic Color",     tunicOptions,    cosmeticDescriptions,                                                                                                                                             OptionCategory::Cosmetic,               5); // Zora Blue
  Option SilverGauntletsColor       = Option::U8  ("Silver Gauntlets Color", gauntletOptions, cosmeticDescriptions,                                                                                                                                             OptionCategory::Cosmetic,               3); // Silver
  Option GoldGauntletsColor         = Option::U8  ("Gold Gauntlets Color",   gauntletOptions, cosmeticDescriptions,                                                                                                                                             OptionCategory::Cosmetic,               4); // Gold
  std::string finalChildTunicColor      = ChildTunicColor.GetSelectedOptionText();
  std::string finalKokiriTunicColor     = KokiriTunicColor.GetSelectedOptionText();
  std::string finalGoronTunicColor      = GoronTunicColor.GetSelectedOptionText();
  std::string finalZoraTunicColor       = ZoraTunicColor.GetSelectedOptionText();
  std::string finalSilverGauntletsColor = SilverGauntletsColor.GetSelectedOptionText();
  std::string finalGoldGauntletsColor   = GoldGauntletsColor.GetSelectedOptionText();

  Option ColoredKeys =     Option::Bool("Colored Small Keys", {"Off", "On"}, {coloredKeysDesc},                                                                                                                                                                 OptionCategory::Cosmetic);
  Option ColoredBossKeys = Option::Bool("Colored Boss Keys",  {"Off", "On"}, {coloredBossKeysDesc},                                                                                                                                                             OptionCategory::Cosmetic);
  Option MirrorWorld =     Option::Bool("Mirror World",       {"Off", "On"}, {mirrorWorldDesc},                                                                                                                                                                 OptionCategory::Cosmetic);

  static std::vector<std::string> fanfareOptions = {"Off", "Only Fanfares", "Fanfares +\n                         Ocarina Music"};
  static std::vector<std::string_view> fanfareDescriptions = {fanfaresOffDesc, onlyFanfaresDesc, fanfaresOcarinaDesc};

  Option ShuffleMusic =    Option::Bool("Shuffle Music",           {"Off", "On"},                         {musicRandoDesc},                                                                                                                                     OptionCategory::Cosmetic);
  Option ShuffleBGM =      Option::U8  ("  Shuffle BGM",           {"Off", "On (Grouped)", "On (Mixed)"}, {shuffleBGMDesc},                                                                                                                                     OptionCategory::Cosmetic,               2); // On (Mixed)
  Option ShuffleFanfares = Option::U8  ("  Shuffle Fanfares",      {fanfareOptions},                      {fanfareDescriptions},                                                                                                                                OptionCategory::Cosmetic,               1); // Fanfares only
  Option ShuffleOcaMusic = Option::Bool("  Shuffle Ocarina Music", {"Off", "On"},                         {shuffleOcaMusicDesc},                                                                                                                                OptionCategory::Cosmetic,               1); // On

  Option ShuffleSFX              = Option::U8  ("Shuffle SFX",           {"Off", "All", "Scene Specific", "Chaos"}, {shuffleSFXOff, shuffleSFXAll, shuffleSFXSceneSpecific, shuffleSFXChaos},                                                                   OptionCategory::Cosmetic);
  Option ShuffleSFXCategorically = Option::Bool("  Categorical Shuffle", {"Off", "On"},                             {shuffleSFXCategorically},                                                                                                                  OptionCategory::Cosmetic,               1); // On

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
    &ShuffleSFX,
    &ShuffleSFXCategorically,
  };

  Menu loadSettingsPreset       = Menu::Action("Load Settings Preset",       LOAD_PRESET);
  Menu saveSettingsPreset       = Menu::Action("Save Settings Preset",       SAVE_PRESET);
  Menu deleteSettingsPreset     = Menu::Action("Delete Settings Preset",     DELETE_PRESET);
  Menu resetToDefaultSettings   = Menu::Action("Reset to Default Settings",  RESET_TO_DEFAULTS);

  std::vector<Menu *> settingsPresetItems = {
    &loadSettingsPreset,
    &saveSettingsPreset,
    &deleteSettingsPreset,
    &resetToDefaultSettings,
  };

  //Detailed Logic Options Submenu
  Menu logicSettings    = Menu::SubMenu("Logic Options",     &logicOptions);
  Menu excludeLocations = Menu::SubMenu("Exclude Locations", &excludeLocationsMenus, false);
  Menu tricks           = Menu::SubMenu("Logical Tricks",    &trickOptions, false);
  Menu glitchSettings   = Menu::SubMenu("Glitch Options",    &glitchOptions, false);
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
  Menu startingInventory        = Menu::SubMenu("Starting Inventory",         &startingInventoryOptions, false);
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
    ctx.playOption = PlayOption;

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
    ctx.shuffleOverworldEntrances = (ShuffleOverworldEntrances) ? 1 : 0;
    ctx.shuffleInteriorEntrances = ShuffleInteriorEntrances.Value<u8>();
    ctx.shuffleGrottoEntrances  = (ShuffleGrottoEntrances) ? 1 : 0;
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
    ctx.shuffleAdultTradeQuest = (ShuffleAdultTradeQuest) ? 1 : 0;
    ctx.shuffleChestMinigame = ShuffleChestMinigame.Value<u8>();

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
    ctx.lakeHyliaOwl         = (LakeHyliaOwl) ? 1 : 0;
    ctx.bigPoeTargetCount    = BigPoeTargetCount.Value<u8>() + 1;
    ctx.numRequiredCuccos    = NumRequiredCuccos.Value<u8>();
    ctx.kingZoraSpeed        = KingZoraSpeed.Value<u8>();
    ctx.completeMaskQuest    = CompleteMaskQuest ? 1 : 0;
    ctx.quickText            = QuickText.Value<u8>();
    ctx.skipSongReplays      = SkipSongReplays.Value<u8>();
    ctx.keepFWWarpPoint      = KeepFWWarpPoint ? 1 : 0;

    ctx.gossipStoneHints     = GossipStoneHints.Value<u8>();
    ctx.compassesShowReward  = CompassesShowReward.Value<u8>();
    ctx.compassesShowWotH    = CompassesShowWotH.Value<u8>();
    ctx.mapsShowDungeonMode  = MapsShowDungeonMode.Value<u8>();
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
    ctx.shuffleSFX           = ShuffleSFX.Value<u8>();
    ctx.shuffleSFXCategorically = (ShuffleSFXCategorically) ? 1 : 0;

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
    ctx.ganonsCastleDungeonMode          = GanonsCastle.IsMQ()          ? 1 : 0;
    ctx.gerudoTrainingGroundsDungeonMode = GerudoTrainingGrounds.IsMQ() ? 1 : 0;

    ctx.dungeonModesKnown = DungeonModesKnown;

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
    ctx.startingBottle4       = StartingBottle4.Value<u8>();
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
    ctx.startingEquipment |= StartingIronBoots.Value<u8>()     << 13;
    ctx.startingEquipment |= StartingHoverBoots.Value<u8>()    << 14;

    //Starting Upgrades
    ctx.startingUpgrades |= StartingStrength.Value<u8>() << 6;
    ctx.startingUpgrades |= StartingScale.Value<u8>() << 9;
    ctx.startingUpgrades |= StartingWallet.Value<u8>() << 12;

    return ctx;
  }

  //Set default cosmetics where the default is not the first option
  static void SetDefaultCosmetics() {
    for (auto op : cosmeticOptions) {
      op->SetToDefault();
    }
  }

  //One-time initialization
  void InitSettings() {
    //Set up token options
    //TODO: Create new 'number range' option type so this isn't necessary
    std::vector<std::string> tokenOptions;
    tokenOptions.reserve(101);
    for (int i = 0; i <= 100; i++) {
      tokenOptions.push_back(std::to_string(i));
    }
    BridgeTokenCount.SetOptions(tokenOptions);
    StartingSkulltulaToken.SetOptions(tokenOptions);
    LACSTokenCount.SetOptions(tokenOptions);

    //Create Location Exclude settings
    AddExcludedOptions();

    SetDefaultSettings();
  }

  //Set default settings for all settings
  void SetDefaultSettings() {
    for (auto op : openOptions) {
      op->SetToDefault();
    }
    for (auto op : worldOptions) {
      op->SetToDefault();
    }
    for (auto op : shuffleOptions) {
      op->SetToDefault();
    }
    for (auto op : shuffleDungeonItemOptions) {
      op->SetToDefault();
    }
    for (auto op : timesaverOptions) {
      op->SetToDefault();
    }
    for (auto op : miscOptions) {
      op->SetToDefault();
    }
    for (auto op : itemUsabilityOptions) {
      op->SetToDefault();
    }
    for (auto op : itemPoolOptions) {
      op->SetToDefault();
    }
    for (auto menu : excludeLocationsMenus) {
      for (auto op : *menu->settingsList) {
        op->SetToDefault();
      }
    }
    for (auto op : startingInventoryOptions) {
      op->SetToDefault();
    }
    for (auto op : logicOptions) {
      op->SetToDefault();
    }
    for (auto op : trickOptions) {
      op->SetToDefault();
    }
    for (auto op : glitchOptions) {
      op->SetToDefault();
    }

    for (auto loc : allLocations) {
      Location(loc)->GetExcludedOption()->SetToDefault();
    }
    //Don't let users exclude these locations
    //TODO: Make sure the defaults are set appropriately for these?
    Location(HC_ZELDAS_LETTER)->GetExcludedOption()->Hide();
    Location(MARKET_BOMBCHU_BOWLING_BOMBCHUS)->GetExcludedOption()->Hide();
    Location(GANON)->GetExcludedOption()->Hide();

    SetDefaultCosmetics();

    ResolveExcludedLocationConflicts();
    for (Menu* menu : Settings::GetAllOptionMenus()) {
      menu->ResetMenuIndex();
    }
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
          startingInventoryOptions[i]->Hide();
          startingInventoryOptions[i]->SetSelectedIndex(0);
          break;
        case 1:
          startingInventoryOptions[i]->Hide();
          startingInventoryOptions[i]->SetSelectedIndex((startingInventoryOptions[i]->GetOptionCount())-1);
          break;
        case 2:
          startingInventoryOptions[i]->Unhide();
          break;
      }
    }
  }

  //This function will hide certain locations from the Excluded Locations
  //menu if the player's current settings would require non-junk to be placed
  //at those locations. Excluded locations will have junk placed at them.
  void ResolveExcludedLocationConflicts() {

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

    //Force include adult trade quest if Shuffle Adult Trade Quest is off
    std::vector<LocationKey> adultTradeLocations = {KAK_TRADE_POCKET_CUCCO, LW_TRADE_COJIRO, KAK_TRADE_ODD_MUSHROOM, LW_TRADE_ODD_POULTICE, GV_TRADE_SAW, DMT_TRADE_BROKEN_SWORD, ZD_TRADE_PRESCRIPTION, LH_TRADE_FROG, DMT_TRADE_EYEDROPS};
    if (ShuffleAdultTradeQuest) {
      Unhide(adultTradeLocations);
    } else {
      IncludeAndHide(adultTradeLocations);
    }

    //Force include Chest Game keys if Shuffle Chest Minigame is off
    std::vector<LocationKey> ChestMinigameLocations = {MARKET_TREASURE_CHEST_GAME_ITEM_1, MARKET_TREASURE_CHEST_GAME_ITEM_2, MARKET_TREASURE_CHEST_GAME_ITEM_3, MARKET_TREASURE_CHEST_GAME_ITEM_4, MARKET_TREASURE_CHEST_GAME_ITEM_5};
    if (ShuffleChestMinigame) {
      Unhide(ChestMinigameLocations);
    } else {
      IncludeAndHide(ChestMinigameLocations);
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
    CollapseCategory(StartingSongsToggle, 29, 41);
    CollapseCategory(StartingUpgradesToggle, 42, 56);
    CollapseCategory(StartingQuestToggle, 57, 66);
    for(int i = 23; i < 28 ;++i){
      switch(StartingInventoryToggle.Value<u8>()) {
        case 0:
          startingInventoryOptions[i]->Hide();
          startingInventoryOptions[i]->SetSelectedIndex(0);
          break;
        case 1:
          startingInventoryOptions[i]->Hide();
          startingInventoryOptions[i]->SetSelectedIndex(1);
          break;
        case 2:
          startingInventoryOptions[i]->Unhide();
          break;
      }
      // If Zora's Fountain is open, hide and un-select Ruto's Letter
      if (ZorasFountain.Is(ZORASFOUNTAIN_OPEN) && i == 27) {
        startingInventoryOptions[i]->Hide();
        startingInventoryOptions[i]->SetSelectedIndex(0);
      }
      // If not open, hide and un-select bottle 4
      else if (ZorasFountain.IsNot(ZORASFOUNTAIN_OPEN) && i == 26) {
        startingInventoryOptions[i]->Hide();
        startingInventoryOptions[i]->SetSelectedIndex(0);
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
        ShuffleInteriorEntrances.Unhide();
        ShuffleGrottoEntrances.Unhide();
      } else {
        ShuffleDungeonEntrances.SetSelectedIndex(OFF);
        ShuffleDungeonEntrances.Hide();
        ShuffleOverworldEntrances.SetSelectedIndex(OFF);
        ShuffleOverworldEntrances.Hide();
        ShuffleInteriorEntrances.SetSelectedIndex(SHUFFLEINTERIORS_OFF);
        ShuffleInteriorEntrances.Hide();
        ShuffleGrottoEntrances.SetSelectedIndex(OFF);
        ShuffleGrottoEntrances.Hide();
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
          //LogicDMTSoilGS.SetSelectedIndex(1);
          LogicLinkGoronDins.SetSelectedIndex(1);
          LogicGoronCityPotWithStrength.SetSelectedIndex(1);
          //LogicCraterUpperToLower.SetSelectedIndex(1);
          LogicBiggoronBolero.SetSelectedIndex(1);
          LogicDekuB1Skip.SetSelectedIndex(1);
          LogicDekuBasementGS.SetSelectedIndex(1);
          LogicDCStaircase.SetSelectedIndex(1);
          LogicDCScarecrowGS.SetSelectedIndex(1);
          //LogicJabuBossGSAdult.SetSelectedIndex(1);
          //LogicJabuScrubJumpDive.SetSelectedIndex(1);
          //LogicForestOutsideBackdoor.SetSelectedIndex(1);
          //LogicForestDoorFrame.SetSelectedIndex(1);
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
          //LogicGoronCityPot.SetSelectedIndex(1);
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
          //LogicSpiritSunChest.SetSelectedIndex(1);
          //LogicShadowFireArrowEntry.SetSelectedIndex(1);
          LogicShadowUmbrella.SetSelectedIndex(1);
          LogicGtgWithoutHookshot.SetSelectedIndex(1);
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

    // Audio
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

    if (ShuffleSFX) {
      ShuffleSFXCategorically.Unhide();
    } else {
      ShuffleSFXCategorically.Hide();
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

  //Options that should be saved, set to default, then restored after finishing when vanilla logic is enabled
  std::vector<Option *> vanillaLogicDefaults = {
    &LinksPocketItem,
    &ShuffleRewards,
    &ShuffleSongs,
    &Shopsanity,
    &Scrubsanity,
    &ShuffleCows,
    &ShuffleMagicBeans,
    &ShuffleMerchants,
    &ShuffleAdultTradeQuest,
    &GossipStoneHints,
  };

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

      // If we won't be randomly choosing any MQ dungeons, dungeon modes are assumed known
      DungeonModesKnown = randMQOption.size() == 0;

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

      // If we won't be randomly choosing any MQ dungeons, dungeon modes are assumed known
      DungeonModesKnown = MQSet == 0;

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
      for (Option* setting : vanillaLogicDefaults) {
        setting->SetDelayedOption();
        setting->SetSelectedIndex(0);
      }
      Keysanity.SetDelayedOption();
      Keysanity.SetSelectedIndex(3); //Set small keys to any dungeon so FiT basement door will be locked
    }

    InitMusicRandomizer();
    if (ShuffleMusic) {
      if (ShuffleBGM.Is(1)) {
        Music::ShuffleSequences(Music::SeqType::SEQ_BGM_WORLD);
        Music::ShuffleSequences(Music::SeqType::SEQ_BGM_EVENT);
        Music::ShuffleSequences(Music::SeqType::SEQ_BGM_BATTLE);
      } else if (ShuffleBGM.Is(2)) {
        Music::ShuffleSequences(Music::SeqType::SEQ_BGM_WORLD | Music::SeqType::SEQ_BGM_EVENT | Music::SeqType::SEQ_BGM_BATTLE);
      }

      if (ShuffleFanfares.Is(2)) {
        Music::ShuffleSequences(Music::SeqType::SEQ_FANFARE | Music::SeqType::SEQ_OCARINA);
      } else {
        if (ShuffleFanfares.Is(1)) {
          Music::ShuffleSequences(Music::SeqType::SEQ_FANFARE);
        }

        if (ShuffleOcaMusic) {
          Music::ShuffleSequences(Music::SeqType::SEQ_OCARINA);
        }
      }
    }

    InitSFXRandomizer();
    if (ShuffleSFX.IsNot(SHUFFLESFX_OFF)) {
      SFX::ShuffleSequences(ShuffleSFXCategorically.Value<bool>());
    }
  }

  //If this is an option menu, return the options
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
  const std::vector<Menu*> GetAllOptionMenus() {
    std::vector<Menu*> allMenus;
    for (Menu* menu : Settings::mainMenu) {
      std::vector<Menu*> foundMenus = GetMenusRecursive(menu);
      allMenus.insert(allMenus.end(), foundMenus.begin(), foundMenus.end());
    }
    return allMenus;
  }

} // namespace Settings
