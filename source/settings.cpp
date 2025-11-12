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
#include "descriptions.hpp"
#include "trial.hpp"
#include "keys.hpp"
#include "gold_skulltulas.hpp"
#include "enemizer.hpp"

#define CREATE_SOULMENUNAMES
#include "../code/src/enemy_souls.h"

using namespace Cosmetics;
using namespace Dungeon;
using namespace Trial;
using namespace Music;
using namespace SFX;

namespace Settings {
std::string seed;
std::string version = RANDOMIZER_VERSION "-" COMMIT_NUMBER;
std::array<u8, 5> hashIconIndexes;

std::vector<std::string> NumOpts(int min, int max, int step = 1, std::string textBefore = {},
                                 std::string textAfter = {}) {
    std::vector<std::string> options;
    options.reserve((max - min) / step + 1);
    for (int i = min; i <= max; i += step) {
        options.push_back(textBefore + std::to_string(i) + textAfter);
    }
    return options;
}

std::vector<std::string> MultiVecOpts(std::vector<std::vector<std::string>> optionsVector) {
    u32 totalSize = 0;
    for (auto vector : optionsVector) {
        totalSize += vector.size();
    }
    std::vector<std::string> options;
    options.reserve(totalSize);
    for (auto vector : optionsVector) {
        for (auto op : vector) {
            options.push_back(op);
        }
    }
    return options;
}

template <typename T, size_t N, typename Func>
static std::vector<Option*> mapArrayToOptions(const T (&array)[N], Func mapper) {
    static std::vector<Option> optionObjects;
    optionObjects.reserve(N);
    std::vector<Option*> optionPointers = {};
    for (T elem : array) {
        Option opt = mapper(elem);
        optionObjects.push_back(std::move(opt));
        optionPointers.push_back(&optionObjects.back());
    }
    return optionPointers;
}

// clang-format off
//                                        Setting name,              Options,                                                                     Setting Descriptions (assigned in setting_descriptions.cpp)                                                 Category (default: Setting),Default index (default: 0), Default hidden (default: false)
// Open Settings                                                                                                                                   Any option index past the last description will use the last description
Option RandomizeOpen       = Option::Bool("Randomize Settings",     {"No","Yes"},                                                                 {openRandomize},                                                                                            OptionCategory::Toggle);
Option OpenForest          = Option::U8  ("Forest",                 {"Closed", "Open", "Closed Deku"},                                            {forestClosed, forestOpen, forestClosedDeku},                                                               OptionCategory::Setting,    OPENFOREST_OPEN);
Option OpenKakariko        = Option::U8  ("Kakariko Gate",          {"Closed", "Open"},                                                           {kakGateClosed, kakGateOpen});
Option OpenDoorOfTime      = Option::U8  ("Door of Time",           {"Open", "Closed", "Intended"},                                               {doorOfTimeOpen, doorOfTimeClosed, doorOfTimeIntended});
Option ZorasFountain       = Option::U8  ("Zora's Fountain",        {"Normal", "Adult", "Open"},                                                  {fountainNormal, fountainAdult, fountainOpen});
Option OpenJabu            = Option::U8  ("Jabu-Jabu",              {"Closed", "Open"},                                                           {jabuJabuCloseDesc, jabuJabuOpenDesc});
Option GerudoFortress      = Option::U8  ("Gerudo Fortress",        {"Normal", "Fast", "Open"},                                                   {gerudoNormal, gerudoFast, gerudoOpen});
Option Bridge              = Option::U8  ("Rainbow Bridge",         {"Open", "Vanilla", "Stones", "Medallions", "Rewards", "Dungeons", "Tokens", "Hearts"},
                                                                     {bridgeOpen, bridgeVanilla, bridgeStones, bridgeMedallions, bridgeRewards, bridgeDungeons, bridgeTokens, bridgeHearts},                                                                  OptionCategory::Setting,    RAINBOWBRIDGE_MEDALLIONS);
Option BridgeStoneCount    = Option::U8  (2, "Stone Count",         {NumOpts(0, 3)},                                                              {bridgeStoneCountDesc},                                                                                     OptionCategory::Setting,    1,                          true);
Option BridgeMedallionCount= Option::U8  (2, "Medallion Count",     {NumOpts(0, 6)},                                                              {bridgeMedallionCountDesc},                                                                                 OptionCategory::Setting,    6);
Option BridgeRewardCount   = Option::U8  (2, "Reward Count",        {NumOpts(0, 9)},                                                              {bridgeRewardCountDesc},                                                                                    OptionCategory::Setting,    1,                          true);
Option BridgeDungeonCount  = Option::U8  (2, "Dungeon Count",       {NumOpts(0, 8)},                                                              {bridgeDungeonCountDesc},                                                                                   OptionCategory::Setting,    1,                          true);
Option BridgeTokenCount    = Option::U8  (2, "Token Count",         {NumOpts(0, 100)},                                                            {bridgeTokenCountDesc},                                                                                     OptionCategory::Setting,    1,                          true);
Option BridgeHeartCount    = Option::U8  (2, "Heart Count",         {NumOpts(0, 20)},                                                             {bridgeHeartCountDesc},                                                                                     OptionCategory::Setting,    1,                          true);
Option RandomGanonsTrials  = Option::Bool("Random Ganon's Trials",  {"Off", "On"},                                                                {randomGanonsTrialsDesc},                                                                                   OptionCategory::Setting,    ON);
Option GanonsTrialsCount   = Option::U8  (2, "Trial Count",         {NumOpts(0, 6)},                                                              {ganonsTrialCountDesc},                                                                                     OptionCategory::Setting,    1,                          true);
std::vector<Option *> openOptions = {
    &RandomizeOpen,
    &OpenForest,
    &OpenKakariko,
    &OpenDoorOfTime,
    &ZorasFountain,
    &OpenJabu,
    &GerudoFortress,
    &Bridge,
    &BridgeStoneCount,
    &BridgeMedallionCount,
    &BridgeRewardCount,
    &BridgeDungeonCount,
    &BridgeTokenCount,
    &BridgeHeartCount,
    &RandomGanonsTrials,
    &GanonsTrialsCount,
};

// World Settings
Option RandomizeWorld            = Option::Bool("Randomize Settings",     {"No","Yes"},                                                      {worldRandomize},                                                                                                OptionCategory::Toggle);
Option StartingAge               = Option::U8  ("Starting Age",           {"Adult", "Child", "Random"},                                      {ageDesc},                                                                                                       OptionCategory::Setting,    AGE_CHILD);
u8 ResolvedStartingAge;
Option ShuffleEntrances          = Option::Bool("Shuffle Entrances",       {"Off", "On"},                                                    {shuffleEntrancesDesc});
Option ShuffleDungeonEntrances   = Option::U8  (2, "Dungeon Entrances",    {"Off", "On", "On + Ganon"},                                      {dungeonEntrancesDesc});
Option ShuffleBossEntrances      = Option::U8  (2, "Boss Entrances",       {"Off", "Age Restricted", "Full"},                                {bossEntrancesDesc});
Option ShuffleOverworldEntrances = Option::Bool(2, "Overworld Entrances",  {"Off", "On"},                                                    {overworldEntrancesDesc});
Option ShuffleInteriorEntrances  = Option::U8  (2, "Interior Entrances",   {"Off", "Simple", "All"},                                         {interiorEntrancesOff, interiorEntrancesSimple, interiorEntrancesAll});
Option ShuffleGrottoEntrances    = Option::Bool(2, "Grottos Entrances",    {"Off", "On"},                                                    {grottoEntrancesDesc});
Option ShuffleOwlDrops           = Option::Bool(2, "Owl Drops",            {"Off", "On"},                                                    {owlDropsDesc});
Option ShuffleWarpSongs          = Option::Bool(2, "Warp Songs",           {"Off", "On"},                                                    {warpSongsDesc});
Option ShuffleOverworldSpawns    = Option::Bool(2, "Overworld Spawns",     {"Off", "On"},                                                    {overworldSpawnsDesc});
Option MixedEntrancePools        = Option::Bool(2, "Mixed Entrance Pools", {"Off", "On"},                                                    {mixedPoolsDesc});
Option MixDungeons               = Option::Bool(4, "Mix Dungeons",         {"Off", "On"},                                                    {mixDungeonsDesc});
Option MixOverworld              = Option::Bool(4, "Mix Overworld",        {"Off", "On"},                                                    {mixOverworldDesc});
Option MixInteriors              = Option::Bool(4, "Mix Interiors",        {"Off", "On"},                                                    {mixInteriorsDesc});
Option MixGrottos                = Option::Bool(4, "Mix Grottos",          {"Off", "On"},                                                    {mixGrottosDesc});
Option DecoupleEntrances         = Option::Bool(2, "Decouple Entrances",   {"Off", "On"},                                                    {decoupledEntrancesDesc});
Option BombchusInLogic           = Option::Bool("Bombchus in Logic",       {"Off", "On"},                                                    {bombchuLogicDesc});
Option AmmoDrops                 = Option::U8  ("Ammo Drops",              {"On", "On + Bombchu", "Off"},                                    {defaultAmmoDropsDesc, bombchuDropsDesc, noAmmoDropsDesc},                                                       OptionCategory::Setting,    AMMODROPS_BOMBCHU);
Option HeartDropRefill           = Option::U8  ("Heart Drops and Refills", {"On", "No Drop", "No Refill", "Off"},                            {defaultHeartDropsDesc, noHeartDropsDesc, noHeartRefillDesc, scarceHeartsDesc},                                  OptionCategory::Setting,    HEARTDROPREFILL_VANILLA);
Option MQDungeonCount            = Option::U8  ("MQ Dungeon Count",        {MultiVecOpts({NumOpts(0, 12), {"Random"}})},                     {mqDungeonCountDesc});
u8 MQSet;
bool DungeonModesKnown[12];
Option SetDungeonTypes           = Option::Bool("Set Dungeon Types",      {"Off", "On"},                                                     {setDungeonTypesDesc});
Option MQDeku                    = Option::U8  (2, "Deku Tree",           {"Vanilla", "Master Quest", "Random"},                             {setDungeonTypesDesc});
Option MQDodongo                 = Option::U8  (2, "Dodongo's Cavern",    {"Vanilla", "Master Quest", "Random"},                             {setDungeonTypesDesc});
Option MQJabu                    = Option::U8  (2, "Jabu-Jabu's Belly",   {"Vanilla", "Master Quest", "Random"},                             {setDungeonTypesDesc});
Option MQForest                  = Option::U8  (2, "Forest Temple",       {"Vanilla", "Master Quest", "Random"},                             {setDungeonTypesDesc});
Option MQFire                    = Option::U8  (2, "Fire Temple",         {"Vanilla", "Master Quest", "Random"},                             {setDungeonTypesDesc});
Option MQWater                   = Option::U8  (2, "Water Temple",        {"Vanilla", "Master Quest", "Random"},                             {setDungeonTypesDesc});
Option MQSpirit                  = Option::U8  (2, "Spirit Temple",       {"Vanilla", "Master Quest", "Random"},                             {setDungeonTypesDesc});
Option MQShadow                  = Option::U8  (2, "Shadow Temple",       {"Vanilla", "Master Quest", "Random"},                             {setDungeonTypesDesc});
Option MQBotW                    = Option::U8  (2, "Bottom of the Well",  {"Vanilla", "Master Quest", "Random"},                             {setDungeonTypesDesc});
Option MQIceCavern               = Option::U8  (2, "Ice Cavern",          {"Vanilla", "Master Quest", "Random"},                             {setDungeonTypesDesc});
Option MQGTG                     = Option::U8  (2, "Training Grounds",    {"Vanilla", "Master Quest", "Random"},                             {setDungeonTypesDesc});
Option MQCastle                  = Option::U8  (2, "Ganon's Castle",      {"Vanilla", "Master Quest", "Random"},                             {setDungeonTypesDesc});
Option TriforceHunt              = Option::Bool("Triforce Hunt",          {"Off", "On"},                                                     {triforceHuntDesc});
Option TriforcePiecesTotal       = Option::U8  (2, "Total pieces",        {NumOpts(1, 200)},                                                 {triforcePiecesTotalDesc},                                                                                       OptionCategory::Setting,    29);
Option TriforcePiecesRequired    = Option::U8  (2, "Required pieces",     {NumOpts(1, 100)},                                                 {triforcePiecesRequiredDesc},                                                                                    OptionCategory::Setting,    19);
Option Enemizer                  = Option::Bool("Enemy Randomizer",       {"Off", "On"},                                                     {enemizerDesc});
Option EnemizerListToggle        = Option::Bool(2, "Enemy List",          {" >", ""},                                                        {enemizerListDesc},                                                                                              OptionCategory::Toggle);
// These are initialized in InitSettings because they depend on Enemizer::enemyTypes, which is not statically initialized
std::vector<Option*> enemizerListOptions;
static Menu enemizerListMenu;
std::vector<Option *> worldOptions = {
    &RandomizeWorld,
    &StartingAge,
    &ShuffleEntrances,
    &ShuffleDungeonEntrances,
    &ShuffleBossEntrances,
    &ShuffleOverworldEntrances,
    &ShuffleInteriorEntrances,
    &ShuffleGrottoEntrances,
    &ShuffleOwlDrops,
    &ShuffleWarpSongs,
    &ShuffleOverworldSpawns,
    &MixedEntrancePools,
    &MixDungeons,
    &MixOverworld,
    &MixInteriors,
    &MixGrottos,
    &DecoupleEntrances,
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
    &TriforceHunt,
    &TriforcePiecesTotal,
    &TriforcePiecesRequired,
    &Enemizer,
    &EnemizerListToggle,
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

// Shuffle Settings
Option RandomizeShuffle       = Option::Bool("Randomize Settings",     {"No","Yes"},                                                      {shuffleRandomize},                                                                                                    OptionCategory::Toggle);
Option ShuffleRewards         = Option::U8  ("Shuffle Dungeon Rewards",{"End of Dungeons", "Any Dungeon", "Overworld", "Anywhere"},       {shuffleRewardsEndOfDungeon, shuffleRewardsAnyDungeon, shuffleRewardsOverworld, shuffleRewardsAnywhere});
Option LinksPocketItem        = Option::U8  ("Link's Pocket",          {"Dungeon Reward", "Advancement", "Anything", "Nothing"},          {linksPocketDungeonReward, linksPocketAdvancement, linksPocketAnything, linksPocketNothing});
Option ShuffleSongs           = Option::U8  ("Shuffle Songs",          {"Song Locations", "Dungeon Rewards", "Anywhere"},                 {songsSongLocations, songsDungeonRewards, songsAllLocations});
Option Shopsanity             = Option::U8  ("Shopsanity",             {MultiVecOpts({{"Off"}, NumOpts(0, 4), {"Random"}})},              {shopsOff, shopsZero, shopsOne, shopsTwo, shopsThree, shopsFour, shopsRandom});
Option ShopsanityPrices       = Option::U8  (2, "Shopsanity Prices",   {"Random", "Affordable", "Child wallet", "Adult wallet",
                                                                        "Giant's wallet", "Tycoon wallet"},                               {shopPriceRandom, shopPriceAffordable, shopPriceChild, shopPriceAdult, shopPriceGiant, shopPriceTycoon});
Option Tokensanity            = Option::U8  ("Tokensanity",            {"Off", "Dungeons", "Overworld", "All Tokens"},                    {tokensOff, tokensDungeon, tokensOverworld, tokensAllTokens});
Option Scrubsanity            = Option::U8  ("Scrub Shuffle",          {"Off", "Affordable", "Expensive", "Random Prices"},               {scrubsOff, scrubsAffordable, scrubsExpensive, scrubsRandomPrices});
Option ShuffleCows            = Option::Bool("Shuffle Cows",           {"Off", "On"},                                                     {shuffleCowsDesc});
Option ShuffleKokiriSword     = Option::Bool("Shuffle Kokiri Sword",   {"Off", "On"},                                                     {kokiriSwordDesc});
Option ShuffleMasterSword     = Option::Bool("Shuffle Master Sword",   {"Off", "On"},                                                     {masterSwordDesc});
Option ShuffleOcarinas        = Option::Bool("Shuffle Ocarinas",       {"Off", "On"},                                                     {ocarinasDesc});
Option ShuffleWeirdEgg        = Option::Bool("Shuffle Weird Egg",      {"Off", "On"},                                                     {weirdEggDesc});
Option ShuffleZeldasLetter    = Option::Bool("Shuffle Zelda's Letter", {"Off", "On"},                                                     {zeldasLetterDesc});
Option ShuffleGerudoToken     = Option::Bool("Shuffle Gerudo Token",   {"Off", "On"},                                                     {gerudoTokenDesc});
Option ShuffleMagicBeans      = Option::Bool("Shuffle Magic Beans",    {"Off", "On"},                                                     {magicBeansDesc});
Option ShuffleMerchants       = Option::U8  ("Shuffle Merchants",      {"Off", "On (No Hints)", "On (With Hints)"},                       {merchantsDesc, merchantsHintsDesc});
Option ShuffleAdultTradeQuest = Option::Bool("Shuffle Adult Trade",    {"Off", "On"},                                                     {adultTradeDesc});
Option ShuffleChestMinigame   = Option::U8  ("Shuffle Chest Minigame", {"Off", "On (Separate)", "On (Pack)"},                             {chestMinigameDesc});
Option ShuffleFrogSongRupees  = Option::Bool("Shuffle Frog Rupees",    {"Off", "On"},                                                     {frogSongRupeesDesc});
Option ShuffleEnemySouls      = Option::U8  ("Shuffle Enemy Souls",    {"Off", "All enemies", "Bosses only"},                             {enemySoulDesc});
Option ShuffleOcarinaButtons  = Option::Bool("Shuffle Ocarina Buttons",{"Off", "On"},                                                     {ocarinaButtonsDesc});
Option ShuffleRupees          = Option::Bool("Rupeesanity",            {"Off","On"},                                                 {shuffleRupeesDesc});
std::vector<Option *> shuffleOptions = {
    &RandomizeShuffle,
    &ShuffleRewards,
    &LinksPocketItem,
    &ShuffleSongs,
    &Shopsanity,
    &ShopsanityPrices,
    &Tokensanity,
    &Scrubsanity,
    &ShuffleCows,
    &ShuffleKokiriSword,
    &ShuffleMasterSword,
    &ShuffleOcarinas,
    &ShuffleWeirdEgg,
    &ShuffleZeldasLetter,
    &ShuffleGerudoToken,
    &ShuffleMagicBeans,
    &ShuffleMerchants,
    &ShuffleAdultTradeQuest,
    &ShuffleChestMinigame,
    &ShuffleFrogSongRupees,
    &ShuffleEnemySouls,
    &ShuffleOcarinaButtons,
    &ShuffleRupees,
};

// Shuffle Dungeon Items
Option RandomizeDungeon    = Option::Bool("Randomize Settings",        {"No","Yes"},                                                           {dungeonRandomize},                                                                                               OptionCategory::Toggle);
Option MapsAndCompasses    = Option::U8  ("Maps/Compasses",            {"Start With", "Vanilla", "Own Dungeon", "Any Dungeon", "Overworld", "Anywhere"},
                                                                        {mapCompassStartWith, mapCompassVanilla, mapCompassOwnDungeon, mapCompassAnyDungeon, mapCompassOverworld, mapCompassAnywhere},                                                           OptionCategory::Setting,    MAPSANDCOMPASSES_OWN_DUNGEON);
Option Keysanity           = Option::U8  ("Small Keys",                {"Start With", "Vanilla", "Own Dungeon", "Any Dungeon", "Overworld", "Anywhere"},
                                                                        {smallKeyStartWith, smallKeyVanilla, smallKeyOwnDungeon, smallKeyAnyDungeon, smallKeyOverworld, smallKeyAnywhere},                                                                       OptionCategory::Setting,    KEYSANITY_OWN_DUNGEON);
Option GerudoKeys          = Option::U8  ("Gerudo Fortress Keys",      {"Vanilla", "Any Dungeon", "Overworld", "Anywhere"},
                                                                        {gerudoKeysVanilla, gerudoKeysAnyDungeon, gerudoKeysOverworld, gerudoKeysAnywhere});
Option BossKeysanity       = Option::U8  ("Boss Keys",                 {"Start With", "Vanilla", "Own Dungeon", "Any Dungeon", "Overworld", "Anywhere"},
                                                                        {bossKeyStartWith, bossKeyVanilla, bossKeyOwnDungeon, bossKeyAnyDungeon, bossKeyOverworld, bossKeyAnywhere},                                                                             OptionCategory::Setting,    BOSSKEYSANITY_OWN_DUNGEON);
Option GanonsBossKey       = Option::U8  ("Ganon's Boss Key",          {"Start With", "Vanilla", "Own Dungeon", "Any Dungeon", "Overworld", "Anywhere", "Triforce",
                                                                        "LACS-Vanilla", "LACS-Medallions", "LACS-Stones", "LACS-Rewards", "LACS-Dungeons", "LACS-Tokens", "LACS-Hearts"},
                                                                        {ganonKeyStartWith, ganonKeyVanilla, ganonKeyOwnDungeon, ganonKeyAnyDungeon, ganonKeyOverworld, ganonKeyAnywhere, "", ganonKeyLACS},                                                         OptionCategory::Setting,    GANONSBOSSKEY_OWN_DUNGEON);
u8 LACSCondition           = 0;
Option LACSMedallionCount  = Option::U8  (2, "Medallion Count",        {NumOpts(0, 6)},                                                        {lacsMedallionCountDesc},                                                                                         OptionCategory::Setting,    1,                          true);
Option LACSStoneCount      = Option::U8  (2, "Stone Count",            {NumOpts(0, 3)},                                                        {lacsStoneCountDesc},                                                                                             OptionCategory::Setting,    1,                          true);
Option LACSRewardCount     = Option::U8  (2, "Reward Count",           {NumOpts(0, 9)},                                                        {lacsRewardCountDesc},                                                                                            OptionCategory::Setting,    1,                          true);
Option LACSDungeonCount    = Option::U8  (2, "Dungeon Count",          {NumOpts(0, 8)},                                                        {lacsDungeonCountDesc},                                                                                           OptionCategory::Setting,    1,                          true);
Option LACSTokenCount      = Option::U8  (2, "Token Count",            {NumOpts(0, 100)},                                                      {lacsTokenCountDesc},                                                                                             OptionCategory::Setting,    1,                          true);
Option LACSHeartCount      = Option::U8  (2, "Heart Count",            {NumOpts(0, 20)},                                                       {lacsHeartCountDesc},                                                                                             OptionCategory::Setting,    1,                          true);
Option KeyRings            = Option::U8  ("Key Rings",                 {"All Off", "All On", "Choose", "Random"},                              {keyRingDesc});
Option RingFortress        = Option::Bool(2, "Gerudo Fortress",        {"Off", "On"},                                                          {keyRingDesc},                                                                                                    OptionCategory::Setting);
Option RingForest          = Option::Bool(2, "Forest Temple",          {"Off", "On"},                                                          {keyRingDesc},                                                                                                    OptionCategory::Setting);
Option RingFire            = Option::Bool(2, "Fire Temple",            {"Off", "On"},                                                          {keyRingDesc},                                                                                                    OptionCategory::Setting);
Option RingWater           = Option::Bool(2, "Water Temple",           {"Off", "On"},                                                          {keyRingDesc},                                                                                                    OptionCategory::Setting);
Option RingSpirit          = Option::Bool(2, "Spirit Temple",          {"Off", "On"},                                                          {keyRingDesc},                                                                                                    OptionCategory::Setting);
Option RingShadow          = Option::Bool(2, "Shadow Temple",          {"Off", "On"},                                                          {keyRingDesc},                                                                                                    OptionCategory::Setting);
Option RingWell            = Option::Bool(2, "Bottom of the Well",     {"Off", "On"},                                                          {keyRingDesc},                                                                                                    OptionCategory::Setting);
Option RingGtg             = Option::Bool(2, "GTG",                    {"Off", "On"},                                                          {keyRingDesc},                                                                                                    OptionCategory::Setting);
Option RingCastle          = Option::Bool(2, "Ganon's Castle",         {"Off", "On"},                                                          {keyRingDesc},                                                                                                    OptionCategory::Setting);

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
    &LACSHeartCount,
    &KeyRings,
    &RingFortress,
    &RingForest,
    &RingFire,
    &RingWater,
    &RingSpirit,
    &RingShadow,
    &RingWell,
    &RingGtg,
    &RingCastle,
};
std::vector<Option *> keyRingOptions = {
    &RingFortress,
    &RingForest,
    &RingFire,
    &RingWater,
    &RingSpirit,
    &RingShadow,
    &RingWell,
    &RingGtg,
    &RingCastle,
};

// Timesaver Settings
Option SkipChildStealth    = Option::Bool("Skip Child Stealth",     {"Don't Skip", "Skip"},                                                 {childStealthDesc},                                                                                               OptionCategory::Setting,    SKIP);
Option SkipTowerEscape     = Option::Bool("Skip Tower Escape",      {"Don't Skip", "Skip"},                                                 {skipTowerEscapeDesc},                                                                                            OptionCategory::Setting,    SKIP);
Option SkipEponaRace       = Option::Bool("Skip Epona Race",        {"Don't Skip", "Skip"},                                                 {skipEponaRaceDesc});
Option SkipMinigamePhases  = Option::Bool("Minigames repetitions",  {"Don't Skip", "Skip"},                                                 {skipMinigamePhasesDesc});
Option FreeScarecrow       = Option::Bool("Free Scarecrow",         {"Off", "On"},                                                          {freeScarecrowDesc});
Option FourPoesCutscene    = Option::Bool("Four Poes Cutscene",     {"Don't Skip", "Skip"},                                                 {fourPoesDesc},                                                                                                   OptionCategory::Setting,    SKIP);
Option LakeHyliaOwl        = Option::Bool("Lake Hylia Owl",         {"Don't Skip", "Skip"},                                                 {lakeHyliaOwlDesc},                                                                                               OptionCategory::Setting,    SKIP);
Option BigPoeTargetCount   = Option::U8  ("Big Poe Target Count",   {NumOpts(1, 10)},                                                       {bigPoeTargetCountDesc});
Option NumRequiredCuccos   = Option::U8  ("Cuccos to return",       {NumOpts(0, 7)},                                                        {numRequiredCuccosDesc});
Option KingZoraSpeed       = Option::U8  ("King Zora Speed",        {"Fast", "Vanilla", "Random", "Custom"},                                {kingZoraSpeedFast, kingZoraSpeedVanilla, kingZoraSpeedRandom, kingZoraSpeedCustom});
Option ExactZoraSpeed      = Option::U8  (2, "Exact Shuffle Count", {NumOpts(1, 128)},                                                      {""});
Option CompleteMaskQuest   = Option::Bool("Complete Mask Quest",    {"Off", "On"},                                                          {completeMaskDesc});
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
    &ExactZoraSpeed,
    &CompleteMaskQuest,
};

// Misc Settings
Option Racing              = Option::Bool("Racing",                 {"Off", "On"},                                                          {racingDesc});
Option GossipStoneHints    = Option::U8  ("Gossip Stone Hints",     {"No Hints", "Need Nothing", "Mask of Truth", "Shard of Agony"},        {gossipStonesHintsDesc},                                                                                          OptionCategory::Setting,    HINTS_NEED_NOTHING);
Option HintDistribution    = Option::U8  (2, "Hint Distribution",   {"Useless", "Balanced", "Strong", "Very Strong", "Playthrough"},        {uselessHintsDesc, balancedHintsDesc, strongHintsDesc, veryStrongHintsDesc, playthroughHintsDesc},                OptionCategory::Setting,    HINTDISTRIBUTION_BALANCED);
Option BonusGossipHints    = Option::Bool(4, "Bonus Hints",         {"Off", "On"},                                                          {bonusGossipHintsDesc});
Option MiscHints           = Option::U8  ("Miscellaneous Hints",    {"All Disabled",  "All Enabled", "Choose"},                             {miscHintsDesc},                                                                                                  OptionCategory::Setting,    TOGGLE_ALL_ENABLED);
Option ToTAltarHints       = Option::Bool(2, "Temple of Time Altar",{"Off", "On"},                                                          {totAltarHintsDesc});
Option GanonHints          = Option::Bool(2, "Ganondorf",           {"Off", "On"},                                                          {ganonHintsDesc});
Option DampeHint           = Option::Bool(2, "Dampe's Diary",       {"Off", "On"},                                                          {dampeHintDesc});
Option SkulltulaHints      = Option::Bool(2, "House of Skulltula",  {"Off", "On"},                                                          {skulltulaHintDesc});
Option FishingHints        = Option::Bool(2, "Fishing Prizes",      {"Off", "On"},                                                          {fishingHintsDesc});
Option ClearerHints        = Option::U8  ("Hint Clarity",           {"Obscure", "Ambiguous", "Clear"},                                      {obscureHintsDesc, ambiguousHintsDesc, clearHintsDesc});
Option CompassesShowReward = Option::U8  ("Compasses Show Rewards", {"No", "Yes"},                                                          {compassesShowRewardsDesc});
Option CompassesShowWotH   = Option::U8  ("Compasses Show WotH",    {"No", "Yes"},                                                          {compassesShowWotHDesc},                                                                                          OptionCategory::Setting,    ON);
Option MapsShowDungeonMode = Option::U8  ("Maps Show Dungeon Modes",{"No", "Yes"},                                                          {mapsShowDungeonModesDesc},                                                                                       OptionCategory::Setting,    ON);
Option StartingTime        = Option::U8  ("Starting Time",          {"Day", "Night"},                                                       {startingTimeDesc});
Option ChestAnimations     = Option::Bool("Chest Animations",       {"Always Fast", "Match Contents"},                                      {chestAnimDesc});
Option ChestAppearance     = Option::U8  ("Chest Appearance Mod",   {"Vanilla", "Texture", "Size + Texture", "Classic CSMC"},             {chestVanillaDesc, chestTextureDesc, chestSizeTextureDesc, chestClassicDesc});
Option ChestAgony          = Option::Bool(2, "Need Shard of Agony", {"No", "Yes"},                                                          {chestAgonyDesc});
Option GenerateSpoilerLog  = Option::Bool("Generate Spoiler Log",   {"No", "Yes"},                                                          {""},                                                                                                             OptionCategory::Setting,    ON);
Option IngameSpoilers      = Option::Bool("Ingame Spoilers",        {"Hide", "Show"},                                                       {ingameSpoilersHideDesc, ingameSpoilersShowDesc });
bool HasNightStart         = false;
std::vector<Option *> miscOptions = {
    &Racing,
    &GossipStoneHints,
    &HintDistribution,
    &BonusGossipHints,
    &MiscHints,
    &ToTAltarHints,
    &GanonHints,
    &DampeHint,
    &SkulltulaHints,
    &FishingHints,
    &ClearerHints,
    &CompassesShowReward,
    &CompassesShowWotH,
    &MapsShowDungeonMode,
    &StartingTime,
    &ChestAnimations,
    &ChestAppearance,
    &ChestAgony,
    &GenerateSpoilerLog,
    &IngameSpoilers,
};

// Item Usability Settings
Option FaroresWindAnywhere = Option::Bool("Farore's Wind Anywhere",  {"Disabled", "Enabled"},                                               {faroresWindAnywhereDesc});
Option AgeItemsToggle      = Option::U8  ("Lift Age Restrictions",   {"All Disabled",  "All Enabled", "Choose"},                            {ageRestrictionsDesc});
Option AgeItemsInLogic     = Option::Bool(1, "Consider in Logic",    {"No", "Yes"},                                                         {ageItemsInLogicDesc});
Option StickAsAdult        = Option::Bool(2, "Adult Deku Stick",     {"Disabled", "Enabled"},                                               {adultStickDesc});
Option BoomerangAsAdult    = Option::Bool(2, "Adult Boomerang",      {"Disabled", "Enabled"},                                               {adultBoomerangDesc});
Option HammerAsChild       = Option::Bool(2, "Child Hammer",         {"Disabled", "Enabled"},                                               {childHammerDesc});
Option SlingshotAsAdult    = Option::Bool(2, "Adult Slingshot",      {"Disabled", "Enabled"},                                               {adultSlingshotDesc});
Option BowAsChild          = Option::Bool(2, "Child Bow",            {"Disabled", "Enabled"},                                               {childBowDesc});
Option HookshotAsChild     = Option::Bool(2, "Child Hookshot",       {"Disabled", "Enabled"},                                               {childHookshotDesc});
Option IronBootsAsChild    = Option::Bool(2, "Child Iron Boots",     {"Disabled", "Enabled"},                                               {childIronBootsDesc});
Option HoverBootsAsChild   = Option::Bool(2, "Child Hover Boots",    {"Disabled", "Enabled"},                                               {childHoverBootsDesc});
Option MasksAsAdult        = Option::Bool(2, "Adult Masks",          {"Disabled", "Enabled"},                                               {adultMasksDesc});
Option KokiriSwordAsAdult  = Option::Bool(2, "Adult Kokiri Sword",   {"Disabled", "Enabled"},                                               {adultKokiriSwordDesc});
Option MasterSwordAsChild  = Option::Bool(2, "Child Master Sword",   {"Disabled", "Enabled"},                                               {childMasterSwordDesc});
Option BiggoronSwordAsChild= Option::Bool(2, "Child Biggoron Sword", {"Disabled", "Enabled"},                                               {childBiggoronSwordDesc});
Option DekuShieldAsAdult   = Option::Bool(2, "Adult Deku Shield",    {"Disabled", "Enabled"},                                               {adultDekuShieldDesc});
Option MirrorShieldAsChild = Option::Bool(2, "Child Mirror Shield",  {"Disabled", "Enabled"},                                               {childMirrorShieldDesc});
Option GoronTunicAsChild   = Option::Bool(2, "Child Goron Tunic",    {"Disabled", "Enabled"},                                               {childGoronTunicDesc});
Option ZoraTunicAsChild    = Option::Bool(2, "Child Zora Tunic",     {"Disabled", "Enabled"},                                               {childZoraTunicDesc});
Option RestoreISG          = Option::Bool("Restore ISG",             {"Disabled", "Enabled"},                                               {restoreISGdesc},                                                                                                 OptionCategory::Setting,    ON);
Option GkDurability        = Option::U8  ("GK Durability",           {"Vanilla", "Random Risk", "Random Safe"},                             {gkDurabilityVanilla, gkDurabilityRandomRisk, gkDurabilityRandomSafe});
Option RetroAmmo           = Option::Bool("Rupees as Ammo",          {"Disabled", "Enabled"},                                               {retroAmmoDesc});
std::vector<Option *> itemUsabilityOptions = {
    &FaroresWindAnywhere,
    &AgeItemsToggle,
    &AgeItemsInLogic,
    &StickAsAdult,
    &BoomerangAsAdult,
    &HammerAsChild,
    &SlingshotAsAdult,
    &BowAsChild,
    &HookshotAsChild,
    &IronBootsAsChild,
    &HoverBootsAsChild,
    &MasksAsAdult,
    &KokiriSwordAsAdult,
    &MasterSwordAsChild,
    &BiggoronSwordAsChild,
    &DekuShieldAsAdult,
    &MirrorShieldAsChild,
    &GoronTunicAsChild,
    &ZoraTunicAsChild,
    &RestoreISG,
    &GkDurability,
    &RetroAmmo,
};

// Item Pool Settings
Option ItemPoolValue         = Option::U8  ("Item Pool",             {"Minimal", "Scarce", "Balanced", "Plentiful"},                        {itemPoolMinimal, itemPoolScarce, itemPoolBalanced, itemPoolPlentiful},                                           OptionCategory::Setting,    ITEMPOOL_BALANCED);
Option IceTrapValue          = Option::U8  ("Ice Traps",             {"Off", "Normal", "Extra", "Mayhem", "Onslaught"},                     {iceTrapsOff, iceTrapsNormal, iceTrapsExtra, iceTrapsMayhem, iceTrapsOnslaught},                                  OptionCategory::Setting,    ICETRAPS_NORMAL);
Option RemoveDoubleDefense   = Option::Bool("Remove Double Defense", {"No", "Yes"},                                                         {removeDDDesc});
Option ProgressiveGoronSword = Option::Bool("Prog Goron Sword",      {"Disabled", "Enabled"},                                               {progGoronSword});
std::vector<Option *> itemPoolOptions = {
    &ItemPoolValue,
    &IceTrapValue,
    &RemoveDoubleDefense,
    &ProgressiveGoronSword,
};

Option FastBunnyHood       = Option::Bool("Fast Bunny Hood",        {"Off", "On"},                                                          {fastBunnyHoodDesc});
Option KeepFWWarpPoint     = Option::Bool("Keep FW Warp Point",     {"Off", "On"},                                                          {keepFWWarpPointDesc});
Option DamageMultiplier    = Option::U8  ("Damage Multiplier",      {"x1/2", "x1", "x2", "x4", "x8", "x16", "OHKO"},                        {damageMultiDesc},                                                                                                OptionCategory::Setting,    DAMAGEMULTIPLIER_DEFAULT);
Option Permadeath          = Option::Bool("Permadeath",             {"Off", "On"},                                                          {permadeathDesc});
Option GloomMode           = Option::U8  ("Gloom Mode",             {"Off", "Death", "Damage", "Collision", "Empty"},                       {gloomModeOffDesc, gloomModeDeathDesc, gloomModeDamageDesc, gloomModeCollisionDesc, gloomModeEmptyDesc});
Option RandomTrapDmg       = Option::U8  ("Random Trap Damage",     {"Off", "Basic", "Advanced"},                                           {randomTrapDmgDesc, basicTrapDmgDesc, advancedTrapDmgDesc},                                                       OptionCategory::Setting,    RANDOMTRAPS_BASIC);
Option FireTrap            = Option::Bool(2, "Fire Trap",           {"Off", "On"},                                                          {fireTrapDesc},                                                                                                   OptionCategory::Setting,    ON);
Option AntiFairyTrap       = Option::Bool(2, "Anti-Fairy Trap",     {"Off", "On"},                                                          {antiFairyTrapDesc},                                                                                              OptionCategory::Setting,    ON);
Option CurseTraps          = Option::Bool(2, "Curse Traps",         {"Off", "On"},                                                          {curseTrapsDesc},                                                                                                 OptionCategory::Setting);
Option ScreenTraps         = Option::Bool(4, "Screen Traps",        {"Off", "On"},                                                          {screenTrapsDesc},                                                                                                OptionCategory::Setting);
Option ExtraArrowEffects   = Option::Bool("Extra Arrow Effects",    {"Off", "On"},                                                          {extraArrowEffectsDesc});
Option HyperActors         = Option::U8  ("Hyper Actors",           {"All Off", "All On", "Choose"},                                        {hyperActorsDesc});
Option HyperBosses         = Option::Bool(2, "Hyper Bosses",        {"Off", "On"},                                                          {hyperBossesDesc});
Option HyperMiddleBosses   = Option::Bool(2, "Hyper Middle Bosses", {"Off", "On"},                                                          {hyperMiddleBossesDesc});
Option HyperEnemies        = Option::Bool(2, "Hyper Enemies",       {"Off", "On"},                                                          {hyperEnemiesDesc});
Option FreeCamera          = Option::Bool("Free Camera",            {"Off", "On"},                                                          {freeCamDesc},                                                                                                    OptionCategory::Setting,    ON);
Option RandomGsLocations   = Option::Bool("Random GS Locations",    {"Off", "On"},                                                          {randomGsLocationsDesc});
Option GsLocGuaranteeNew   = Option::Bool(2, "Guarantee New",       {"Off", "On"},                                                          {gsLocGuaranteeNewDesc});
std::vector<Option*> gameplayOptions = {
    &FastBunnyHood,
    &KeepFWWarpPoint,
    &DamageMultiplier,
    &Permadeath,
    &GloomMode,
    &RandomTrapDmg,
    &FireTrap,
    &AntiFairyTrap,
    &CurseTraps,
    &ScreenTraps,
    &ExtraArrowEffects,
    &HyperActors,
    &HyperBosses,
    &HyperMiddleBosses,
    &HyperEnemies,
    &FreeCamera,
    &RandomGsLocations,
    &GsLocGuaranteeNew,
};

// Excluded Locations (Individual definitions made in ItemLocation class)
std::vector<std::vector<Option *>> excludeLocationsOptionsVector(SPOILER_COLLECTION_GROUP_COUNT);
Menu excludeKokiriForest          = Menu::SubMenu("Kokiri Forest",           &excludeLocationsOptionsVector[GROUP_KOKIRI_FOREST],              "", false);
Menu excludeLostWoods             = Menu::SubMenu("Lost Woods",              &excludeLocationsOptionsVector[GROUP_LOST_WOODS],                 "", false);
Menu excludeSacredForestMeadow    = Menu::SubMenu("Sacred Forest Meadow",    &excludeLocationsOptionsVector[GROUP_SACRED_FOREST_MEADOW],       "", false);
Menu excludeDekuTree              = Menu::SubMenu("Deku Tree",               &excludeLocationsOptionsVector[GROUP_DUNGEON_DEKU_TREE],          "", false);
Menu excludeForestTemple          = Menu::SubMenu("Forest Temple",           &excludeLocationsOptionsVector[GROUP_DUNGEON_FOREST_TEMPLE],      "", false);
Menu excludeKakariko              = Menu::SubMenu("Kakariko Village",        &excludeLocationsOptionsVector[GROUP_KAKARIKO],                   "", false);
Menu excludeGraveyard             = Menu::SubMenu("Graveyard",               &excludeLocationsOptionsVector[GROUP_GRAVEYARD],                  "", false);
Menu excludeBottomWell            = Menu::SubMenu("Bottom of the Well",      &excludeLocationsOptionsVector[GROUP_DUNGEON_BOTTOM_OF_THE_WELL], "", false);
Menu excludeShadowTemple          = Menu::SubMenu("Shadow Temple",           &excludeLocationsOptionsVector[GROUP_DUNGEON_SHADOW_TEMPLE],      "", false);
Menu excludeDeathMountainTrail    = Menu::SubMenu("Death Mountain Trail",    &excludeLocationsOptionsVector[GROUP_DEATH_MOUNTAIN_TRAIL],       "", false);
Menu excludeDeathMountainCrater   = Menu::SubMenu("Death Mountain Crater",   &excludeLocationsOptionsVector[GROUP_DEATH_MOUNTAIN_CRATER],      "", false);
Menu excludeGoronCity             = Menu::SubMenu("Goron City",              &excludeLocationsOptionsVector[GROUP_GORON_CITY],                 "", false);
Menu excludeDodongosCavern        = Menu::SubMenu("Dodongo's Cavern",        &excludeLocationsOptionsVector[GROUP_DUNGEON_DODONGOS_CAVERN],    "", false);
Menu excludeFireTemple            = Menu::SubMenu("Fire Temple",             &excludeLocationsOptionsVector[GROUP_DUNGEON_FIRE_TEMPLE],        "", false);
Menu excludeZorasRiver            = Menu::SubMenu("Zora's River",            &excludeLocationsOptionsVector[GROUP_ZORAS_RIVER],                "", false);
Menu excludeZorasDomain           = Menu::SubMenu("Zora's Domain",           &excludeLocationsOptionsVector[GROUP_ZORAS_DOMAIN],               "", false);
Menu excludeZorasFountain         = Menu::SubMenu("Zora's Fountain",         &excludeLocationsOptionsVector[GROUP_ZORAS_FOUNTAIN],             "", false);
Menu excludeJabuJabu              = Menu::SubMenu("Jabu Jabu's Belly",       &excludeLocationsOptionsVector[GROUP_DUNGEON_JABUJABUS_BELLY],    "", false);
Menu excludeIceCavern             = Menu::SubMenu("Ice Cavern",              &excludeLocationsOptionsVector[GROUP_DUNGEON_ICE_CAVERN],         "", false);
Menu excludeHyruleField           = Menu::SubMenu("Hyrule Field",            &excludeLocationsOptionsVector[GROUP_HYRULE_FIELD],               "", false);
Menu excludeLonLonRanch           = Menu::SubMenu("Lon Lon Ranch",           &excludeLocationsOptionsVector[GROUP_LON_LON_RANCH],              "", false);
Menu excludeLakeHylia             = Menu::SubMenu("Lake Hylia",              &excludeLocationsOptionsVector[GROUP_LAKE_HYLIA],                 "", false);
Menu excludeWaterTemple           = Menu::SubMenu("Water Temple",            &excludeLocationsOptionsVector[GROUP_DUNGEON_WATER_TEMPLE],       "", false);
Menu excludeGerudoValley          = Menu::SubMenu("Gerudo Valley",           &excludeLocationsOptionsVector[GROUP_GERUDO_VALLEY],              "", false);
Menu excludeHauntedWasteland      = Menu::SubMenu("Haunted Wasteland",       &excludeLocationsOptionsVector[GROUP_HAUNTED_WASTELAND],          "", false);
Menu excludeGerudoTrainingGrounds = Menu::SubMenu("Gerudo Training Grounds", &excludeLocationsOptionsVector[GROUP_GERUDO_TRAINING_GROUND],     "", false);
Menu excludeSpiritTemple          = Menu::SubMenu("Spirit Temple",           &excludeLocationsOptionsVector[GROUP_DUNGEON_SPIRIT_TEMPLE],      "", false);
Menu excludeMarket                = Menu::SubMenu("Market",                  &excludeLocationsOptionsVector[GROUP_MARKET],                     "", false);
Menu excludeHyruleCastle          = Menu::SubMenu("Hyrule Castle",           &excludeLocationsOptionsVector[GROUP_HYRULE_CASTLE],              "", false);
Menu excludeGanonsCastle          = Menu::SubMenu("Ganon's Castle",          &excludeLocationsOptionsVector[GROUP_DUNGEON_GANONS_CASTLE],      "", false);
std::vector<Menu *> excludeLocationsMenus = {
    &excludeKokiriForest,
    &excludeLostWoods,
    &excludeSacredForestMeadow,
    &excludeDekuTree,
    &excludeForestTemple,
    &excludeKakariko,
    &excludeGraveyard,
    &excludeBottomWell,
    &excludeShadowTemple,
    &excludeDeathMountainTrail,
    &excludeDeathMountainCrater,
    &excludeGoronCity,
    &excludeDodongosCavern,
    &excludeFireTemple,
    &excludeZorasRiver,
    &excludeZorasDomain,
    &excludeZorasFountain,
    &excludeJabuJabu,
    &excludeIceCavern,
    &excludeHyruleField,
    &excludeLonLonRanch,
    &excludeLakeHylia,
    &excludeWaterTemple,
    &excludeGerudoValley,
    &excludeHauntedWasteland,
    &excludeGerudoTrainingGrounds,
    &excludeSpiritTemple,
    &excludeMarket,
    &excludeHyruleCastle,
    &excludeGanonsCastle,
};

// Starting Inventory submenus and menus
std::vector<std::string> bottleOptions = {"Off", "Empty Bottle", "Red Potion", "Green Potion", "Blue Potion", "Fairy", "Fish", "Milk", "Blue Fire", "Bugs", "Big Poe", "Half Milk", "Poe"};
Option StartingStickCapacity    = Option::U8  ("Deku Stick Capacity",  {NumOpts(10, 30, 10, {}, " Deku Sticks")},                                       {""});
Option StartingNutCapacity      = Option::U8  ("Deku Nut Capacity",    {NumOpts(20, 40, 10, {}, " Deku Nuts")},                                         {""});
Option StartingSlingshot        = Option::U8  ("Slingshot",            {"Off",             "Slingshot (30)",   "Slingshot (40)",    "Slingshot (50)"},  {""});
Option StartingOcarina          = Option::U8  ("Ocarina",              {"Off",             "Fairy Ocarina",    "Ocarina of Time"},                      {""});
Option StartingBombBag          = Option::U8  ("Bombs",                {"Off",             "Bomb Bag (20)",    "Bomb Bag (30)",     "Bomb Bag (40)"},   {""});
Option StartingBombchus         = Option::U8  ("Bombchus",             {"Off",             "20 Bombchus",      "50 Bombchus"},                          {""});
Option StartingBoomerang        = Option::U8  ("Boomerang",            {"Off",             "On"},                                                       {""});
Option StartingHookshot         = Option::U8  ("Hookshot",             {"Off",             "Hookshot",         "Longshot"},                             {""});
Option StartingBow              = Option::U8  ("Bow",                  {"Off",             "Bow (30)",         "Bow (40)",          "Bow (50)"},        {""});
Option StartingFireArrows       = Option::U8  ("Fire Arrow",           {"Off",             "On"},                                                       {""});
Option StartingIceArrows        = Option::U8  ("Ice Arrow",            {"Off",             "On"},                                                       {""});
Option StartingLightArrows      = Option::U8  ("Light Arrow",          {"Off",             "On"},                                                       {""});
Option StartingMegatonHammer    = Option::U8  ("Megaton Hammer",       {"Off",             "On"},                                                       {""});
Option StartingIronBoots        = Option::U8  ("Iron Boots",           {"Off",             "On"},                                                       {""});
Option StartingHoverBoots       = Option::U8  ("Hover Boots",          {"Off",             "On"},                                                       {""});
Option StartingLensOfTruth      = Option::U8  ("Lens of Truth",        {"Off",             "On"},                                                       {""});
Option StartingDinsFire         = Option::U8  ("Din's Fire",           {"Off",             "On"},                                                       {""});
Option StartingFaroresWind      = Option::U8  ("Farore's Wind",        {"Off",             "On"},                                                       {""});
Option StartingNayrusLove       = Option::U8  ("Nayru's Love",         {"Off",             "On"},                                                       {""});
Option StartingMagicBean        = Option::U8  ("Magic Beans",          {"Off",             "On"},                                                       {""});
Option StartingBottle1          = Option::U8  ("Bottle 1",             bottleOptions,                                                                   {""});
Option StartingBottle2          = Option::U8  ("Bottle 2",             bottleOptions,                                                                   {""});
Option StartingBottle3          = Option::U8  ("Bottle 3",             bottleOptions,                                                                   {""});
Option StartingBottle4          = Option::U8  ("Bottle 4",             bottleOptions,                                                                   {""});
Option StartingRutoBottle       = Option::U8  ("Ruto's Letter",        {"Off",             "On"},                                                       {""});
Option StartingChildTrade       = Option::U8  ("Bunny Hood",           {"Off",             "On"},                                                       {startingBunnyHoodDesc});
std::vector<Option *> startingItemsOptions = {
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
    &StartingChildTrade,
};

Option StartingZeldasLullaby    = Option::U8  ("Zelda's Lullaby",      {"Off",             "On"},                                                       {""});
Option StartingEponasSong       = Option::U8  ("Epona's Song",         {"Off",             "On"},                                                       {""});
Option StartingSariasSong       = Option::U8  ("Saria's Song",         {"Off",             "On"},                                                       {""});
Option StartingSunsSong         = Option::U8  ("Sun's Song",           {"Off",             "On"},                                                       {""});
Option StartingSongOfTime       = Option::U8  ("Song of Time",         {"Off",             "On"},                                                       {""});
Option StartingSongOfStorms     = Option::U8  ("Song of Storms",       {"Off",             "On"},                                                       {""});
Option StartingMinuetOfForest   = Option::U8  ("Minuet of Forest",     {"Off",             "On"},                                                       {""});
Option StartingBoleroOfFire     = Option::U8  ("Bolero of Fire",       {"Off",             "On"},                                                       {""});
Option StartingSerenadeOfWater  = Option::U8  ("Serenade of Water",    {"Off",             "On"},                                                       {""});
Option StartingRequiemOfSpirit  = Option::U8  ("Requiem of Spirit",    {"Off",             "On"},                                                       {""});
Option StartingNocturneOfShadow = Option::U8  ("Nocturne of Shadow",   {"Off",             "On"},                                                       {""});
Option StartingPreludeOfLight   = Option::U8  ("Prelude of Light",     {"Off",             "On"},                                                       {""});
std::vector<Option *> startingSongsOptions = {
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
};

Option StartingKokiriSword      = Option::U8  ("Kokiri Sword",         {"Off",             "On"},                                                       {""});
Option StartingMasterSword      = Option::U8  ("Master Sword",         {"Off",             "On"},                                                       {""});
Option StartingBiggoronSword    = Option::U8  ("Biggoron Sword",       {"Off",             "Giant's Knife",    "Biggoron Sword"},                       {""});
Option StartingDekuShield       = Option::U8  ("Deku Shield",          {"Off",             "On"},                                                       {""});
Option StartingHylianShield     = Option::U8  ("Hylian Shield",        {"Off",             "On"},                                                       {""});
Option StartingMirrorShield     = Option::U8  ("Mirror Shield",        {"Off",             "On"},                                                       {""});
Option StartingGoronTunic       = Option::U8  ("Goron Tunic",          {"Off",             "On"},                                                       {""});
Option StartingZoraTunic        = Option::U8  ("Zora Tunic",           {"Off",             "On"},                                                       {""});
Option StartingStrength         = Option::U8  ("Strength Upgrade",     {"Off",             "Goron Bracelet",   "Silver Gauntlet",  "Golden Gauntlet"},  {""});
Option StartingScale            = Option::U8  ("Scale Upgrade",        {"Off",             "Silver Scale",     "Golden Scale"},                         {""});
Option StartingWallet           = Option::U8  ("Wallet Upgrade",       {"Off",             "Adult's Wallet",   "Giant's Wallet",   "Tycoon's Wallet"},  {""});
Option StartingShardOfAgony     = Option::U8  ("Shard of Agony",       {"Off",             "On"},                                                       {""});
Option StartingHearts           = Option::U8  ("Hearts",               {NumOpts(0, 20)},                                                                {startingHealthDesc,""}, OptionCategory::Setting, 3); // Default 3 hearts
Option StartingMagicMeter       = Option::U8  ("Magic Meter",          {"Off",             "Single Magic",     "Double Magic"},                         {""});
Option StartingDoubleDefense    = Option::U8  ("Double Defense",       {"Off",             "On"},                                                       {""});
std::vector<Option *> startingEquipmentOptions = {
    &StartingKokiriSword,
    &StartingMasterSword,
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
    &StartingHearts,
    &StartingMagicMeter,
    &StartingDoubleDefense,
};

Option StartingKokiriEmerald    = Option::U8  ("Kokiri's Emerald",     {"Off",             "On"},                                                       {""});
Option StartingGoronRuby        = Option::U8  ("Goron's Ruby",         {"Off",             "On"},                                                       {""});
Option StartingZoraSapphire     = Option::U8  ("Zora's Sapphire",      {"Off",             "On"},                                                       {""});
Option StartingLightMedallion   = Option::U8  ("Light Medallion",      {"Off",             "On"},                                                       {""});
Option StartingForestMedallion  = Option::U8  ("Forest Medallion",     {"Off",             "On"},                                                       {""});
Option StartingFireMedallion    = Option::U8  ("Fire Medallion",       {"Off",             "On"},                                                       {""});
Option StartingWaterMedallion   = Option::U8  ("Water Medallion",      {"Off",             "On"},                                                       {""});
Option StartingSpiritMedallion  = Option::U8  ("Spirit Medallion",     {"Off",             "On"},                                                       {""});
Option StartingShadowMedallion  = Option::U8  ("Shadow Medallion",     {"Off",             "On"},                                                       {""});
std::vector<Option *> startingStonesMedallionsOptions = {
    &StartingKokiriEmerald,
    &StartingGoronRuby,
    &StartingZoraSapphire,
    &StartingLightMedallion,
    &StartingForestMedallion,
    &StartingFireMedallion,
    &StartingWaterMedallion,
    &StartingSpiritMedallion,
    &StartingShadowMedallion,
};

// Initialize startingEnemySoulsOptions with one Option for each element in SoulMenuNames
std::vector<Option *> startingEnemySoulsOptions = mapArrayToOptions(SoulMenuNames, [](SoulMenuInfo info){
    return Option::U8 (info.name, {"Off", "On"}, {""});
});

Option StartingOcarinaButtonL = Option::U8  ("Ocarina Button L", {"Off", "On"}, {""});
Option StartingOcarinaButtonR = Option::U8  ("Ocarina Button R", {"Off", "On"}, {""});
Option StartingOcarinaButtonX = Option::U8  ("Ocarina Button X", {"Off", "On"}, {""});
Option StartingOcarinaButtonY = Option::U8  ("Ocarina Button Y", {"Off", "On"}, {""});
Option StartingOcarinaButtonA = Option::U8  ("Ocarina Button A", {"Off", "On"}, {""});
std::vector<Option *> startingOcarinaButtonsOptions = {
    &StartingOcarinaButtonL,
    &StartingOcarinaButtonR,
    &StartingOcarinaButtonX,
    &StartingOcarinaButtonY,
    &StartingOcarinaButtonA,
};

Option StartingConsumables      = Option::Bool("Start with Consumables", {"No",               "Yes"},                                                     {startWithConsumablesDesc});
Option StartingMaxRupees        = Option::Bool("Start with Max Rupees",  {"No",               "Yes"},                                                     {startWithMaxRupeesDesc});
Option StartingSkulltulaToken   = Option::U8  ("Gold Skulltula Tokens",  {NumOpts(0, 100)},                                                               {""});
std::vector<Option *> startingOthersOptions = {
    &StartingConsumables,
    &StartingMaxRupees,
    &StartingSkulltulaToken,
};

Menu startingItems            = Menu::SubMenu("Items",                &startingItemsOptions,            "", false);
Menu startingSongs            = Menu::SubMenu("Ocarina Songs",        &startingSongsOptions,            "", false);
Menu startingEquipment        = Menu::SubMenu("Equipment & Upgrades", &startingEquipmentOptions,        "", false);
Menu startingStonesMedallions = Menu::SubMenu("Stones & Medallions",  &startingStonesMedallionsOptions, "", false);
Menu startingEnemySouls       = Menu::SubMenu("Enemy Souls",          &startingEnemySoulsOptions,       "", false);
Menu startingOcarinaButtons   = Menu::SubMenu("Ocarina Buttons",      &startingOcarinaButtonsOptions,   "", false);
Menu startingOthers           = Menu::SubMenu("Other",                &startingOthersOptions,           "", false);
std::vector<Menu *> startingInventoryOptions = {
    &startingItems,
    &startingSongs,
    &startingEquipment,
    &startingStonesMedallions,
    &startingEnemySouls,
    &startingOcarinaButtons,
    &startingOthers,
};
Option Logic              = Option::U8  ("Logic",                   {"Glitchless", "Glitched", "No Logic", "Vanilla"}, {logicGlitchless, logicGlitched, logicNoLogic, logicVanilla});
Option LocationsReachable = Option::Bool("All Locations Reachable", {"Off", "On"},                                     {locationsReachableDesc},                                                                                                              OptionCategory::Setting,    ON);
Option NightGSExpectSuns  = Option::Bool("Night GSs Expect Sun's",  {"Off", "On"},                                     {nightGSDesc});
std::vector<Option *> logicOptions = {
    &Logic,
    &LocationsReachable,
    &NightGSExpectSuns,
};

// Function to make defining logic tricks easier to read
Option LogicTrick(std::string setting, std::string_view description) {
    return Option::Bool(1, setting, {"Disabled", "Enabled"}, {description});
}

// Detailed Logic Tricks                               ---------------------
Option ToggleAllTricks                  = Option::U8("All Tricks", {"None", "Novice", "Intermediate", "Expert"},  {ToggleLogicNoneDesc, ToggleLogicNoviceDesc, ToggleLogicIntermediateDesc, ToggleLogicExpertDesc},                                           OptionCategory::Toggle);
Option LogicGrottosWithoutAgony         = LogicTrick("Grotto Access\n  w/o Shard of Agony",       LogicGrottosWithoutAgonyDesc);
Option LogicVisibleCollision            = LogicTrick("Go Through Visible\n  One-Way Collisions",  LogicVisibleCollisionDesc);
Option LogicFewerTunicRequirements      = LogicTrick("Fewer Tunic\n  Requirements",               LogicFewerTunicRequirementsDesc);
Option LogicLostWoodsGSBean             = LogicTrick("LW Adult Tree GS\n  w/o Magic Beans",       LogicLostWoodsGSBeanDesc);
Option LogicLabDiving                   = LogicTrick("LH Lab Dive\n  w/o Gold Scale",             LogicLabDivingDesc);
Option LogicLabWallGS                   = LogicTrick("LH Lab Wall GS\n  w/ Jump Slash",           LogicLabWallGSDesc);
Option LogicGraveyardPoH                = LogicTrick("GY Crate PoH\n  w/ Boomerang",              LogicGraveyardPoHDesc);
Option LogicChildDampeRacePoH           = LogicTrick("GY Second Dampe\n  Race as Child",          LogicChildDampeRacePoHDesc);
Option LogicGVHammerChest               = LogicTrick("GV Hammer Chest\n  w/o Hammer",             LogicGVHammerChestDesc);
Option LogicGerudoKitchen               = LogicTrick("GF Through Kitchen\n  w/ Nothing",          LogicGerudoKitchenDesc);
Option LogicGerudoChildClimb            = LogicTrick("GF Top Floor\n  as child",                  LogicGerudoChildClimbDesc);
Option LogicLensWasteland               = LogicTrick("Haunted Wasteland\n  w/o Lens of Truth",    LogicLensWastelandDesc);
Option LogicReverseWasteland            = LogicTrick("Haunted Wasteland\n  in Reverse",           LogicReverseWastelandDesc);
Option LogicColossusGS                  = LogicTrick("Colossus Hill GS\n  w/ Hookshot",           LogicColossusGSDesc);
Option LogicOutsideGanonsGS             = LogicTrick("Outside GaC GS\n  w/ Jump Slash",           LogicOutsideGanonsGSDesc);
Option LogicManOnRoof                   = LogicTrick("Kak Roof Guy\n  w/o Hookshot",              LogicManOnRoofDesc);
Option LogicWindmillPoHHookshot         = LogicTrick("Windmill PoH\n  w/ Hookshot",               LogicWindmillPoHHookshotDesc);
Option LogicDMTBombable                 = LogicTrick("DMT Wall Chest\n  w/ Strength",             LogicDMTBombableDesc);
Option LogicDMTSoilGS                   = LogicTrick("DMT Soil GS\n  w/o Opening DC",             LogicDMTSoilGSDesc);
Option LogicDMTSummitHover              = LogicTrick("DMT Summit\n  w/ Hover Boots",              LogicDMTSummitHoverDesc);
Option LogicLinkGoronDins               = LogicTrick("GoC Adult Goron\n  w/ Din's Fire",          LogicLinkGoronDinsDesc);
Option LogicGoronCityLeftMost           = LogicTrick("GoC Maze Left Chest\n  w/ Hover Boots",     LogicGoronCityLeftMostDesc);
Option LogicGoronCityPot                = LogicTrick("GoC Goron Vase PoH\n  w/ Bombchu",          LogicGoronCityPotDesc); //Needs Testing
Option LogicGoronCityPotWithStrength    = LogicTrick("GoC Goron Vase PoH\n  w/ Strength",         LogicGoronCityPotWithStrengthDesc);
Option LogicChildRollingWithStrength    = LogicTrick("GoC Child Goron\n  w/ Strength",            LogicChildRollingWithStrengthDesc);
Option LogicCraterUpperToLower          = LogicTrick("DMC Upper to Lower\n  w/ Hammer",           LogicCraterUpperToLowerDesc); //Needs Testing
Option LogicCraterBeanPoHWithHovers     = LogicTrick("DMC Bean PoH\n  w/ Hover Boots",            LogicCraterBeanPoHWithHoversDesc);
Option LogicBiggoronBolero              = LogicTrick("DMC Deliver Eyedrops\n  w/ Bolero of Fire", LogicBiggoronBoleroDesc);
Option LogicZoraRiverLower              = LogicTrick("ZR Lower PoH\n  w/ Nothing",                LogicZoraRiverLowerDesc);
Option LogicZoraRiverUpper              = LogicTrick("ZR Upper PoH\n  w/ Nothing",                LogicZoraRiverUpperDesc);
Option LogicZFGreatFairy                = LogicTrick("ZF Great Fairy\n  w/o Explosives",          LogicZFGreatFairyDesc);
Option LogicDekuB1WebsWithBow           = LogicTrick("DT B1 Web\n  w/ Bow",                       LogicDekuB1WebsWithBowDesc);
Option LogicDekuB1Skip                  = LogicTrick("DT B1 Navigation\n  w/o Slingshot",         LogicDekuB1SkipDesc);
Option LogicDekuBasementGS              = LogicTrick("DT B1 Vines GS\n  w/ Jump Slash",           LogicDekuBasementGSDesc);
Option LogicDCStaircase                 = LogicTrick("DC Staircase\n  w/ Bow",                    LogicDCStaircaseDesc);
Option LogicDCJump                      = LogicTrick("DC Spike Trap Room\n  w/o Hover Boots",     LogicDCJumpDesc);
Option LogicDCSlingshotSkip             = LogicTrick("DC Eye Switches\n  w/o Slingshot",          LogicDCSlingshotSkipDesc);
Option LogicDCScarecrowGS               = LogicTrick("DC Scarecrow GS\n  w/ Armos Statue",        LogicDCScarecrowGSDesc);
Option LogicJabuBossGSAdult             = LogicTrick("JJB Near Boss GS\n  as Adult",              LogicJabuBossGSAdultDesc); //Needs Testing
Option LogicJabuScrubJumpDive           = LogicTrick("JJB Deku Scrub\n  as Adult",                LogicJabuScrubJumpDiveDesc); //Needs Testing
Option LogicForestOutsideBackdoor       = LogicTrick("FoT West Backdoor\n  w/ Jump Slash",        LogicForestOutsideBackdoorDesc); //Needs Testing
Option LogicForestDoorFrame             = LogicTrick("FoT East Scarecrow\n  w/ Hover Boots",      LogicForestDoorFrameDesc); //Needs Testing
Option LogicForestOutdoorEastGS         = LogicTrick("FoT East Yard GS\n  w/ Boomerang",          LogicForestOutdoorEastGSDesc);
Option LogicFireBossDoorJump            = LogicTrick("FiT Boss Door\n  w/o Hover Boots",          LogicFireBossDoorJumpDesc);
Option LogicFireStrength                = LogicTrick("FiT Climb Block\n  w/o Strength",           LogicFireStrengthDesc);
Option LogicFireScarecrow               = LogicTrick("FiT East Tower\n  w/o Scarecrow",           LogicFireScarecrowDesc);
Option LogicFireFlameMaze               = LogicTrick("FiT Firewall Maze\n  w/ Nothing",           LogicFireFlameMazeDesc);
Option LogicFireSongOfTime              = LogicTrick("FiT SoT Room GS\n  w/o SoT",                LogicFireSongOfTimeDesc);
Option LogicWaterTempleTorchLongshot    = LogicTrick("WaT Torch Longshot\n  Shortcut",            LogicWaterTempleTorchLongshotDesc);
Option LogicWaterTempleUpperBoost       = LogicTrick("WaT Boss Ledge\n  w/ Bombs",                LogicWaterTempleUpperBoostDesc);
Option LogicWaterCentralBow             = LogicTrick("WaT Bow Target\n  w/o Longshot/Hover",      LogicWaterCentralBowDesc);
Option LogicWaterCentralGSFW            = LogicTrick("WaT Center Room GS\n  w/ Farore's Wind",    LogicWaterCentralGSFWDesc);
Option LogicWaterCrackedWallNothing     = LogicTrick("WaT Cracked Wall\n  w/ Nothing",            LogicWaterCrackedWallNothingDesc);
Option LogicWaterCrackedWallHovers      = LogicTrick("WaT Cracked Wall\n  w/ Hover Boots",        LogicWaterCrackedWallHoversDesc);
Option LogicWaterBossKeyRegion          = LogicTrick("WaT B1 North Area\n  w/ Hover Boots",       LogicWaterBossKeyRegionDesc);
Option LogicWaterBKJumpDive             = LogicTrick("WaT Boss Key Room\n  w/o Iron Boots",       LogicWaterBKJumpDiveDesc);
Option LogicWaterNorthBasementLedgeJump = LogicTrick("WaT Boss Key Rooms\n  w/ Precise Jump",     LogicWaterNorthBasementLedgeJumpDesc);
Option LogicWaterDragonAdult            = LogicTrick("WaT Whirlpool\n  w/o Iron Boots",           LogicWaterDragonAdultDesc);
Option LogicWaterDragonJumpDive         = LogicTrick("WaT Whirlpool Up\n  w/o Iron Boots",        LogicWaterDragonJumpDiveDesc);
Option LogicWaterRiverGS                = LogicTrick("WaT River GS\n  w/o Iron Boots",            LogicWaterRiverGSDesc);
Option LogicWaterFallingPlatformGS      = LogicTrick("WaT Waterfall GS\n  w/ Hookshot",           LogicWaterFallingPlatformGSDesc);
Option LogicSpiritLowerAdultSwitch      = LogicTrick("SpT Ceiling Switch\n  w/ Bombs",            LogicSpiritLowerAdultSwitchDesc);
Option LogicSpiritChildBombchu          = LogicTrick("SpT Child Bridge\n  w/ Bombchu",            LogicSpiritChildBombchuDesc);
Option LogicSpiritWall                  = LogicTrick("SpT Shifting Wall\n  w/ Nothing",           LogicSpiritWallDesc);
Option LogicSpiritLobbyGS               = LogicTrick("SpT Main Room GS\n  w/ Boomerang",          LogicSpiritLobbyGSDesc);
Option LogicSpiritMapChest              = LogicTrick("SpT Map Chest\n  w/ Bow",                   LogicSpiritMapChestDesc);
Option LogicSpiritSunChest              = LogicTrick("SpT Sun Block Room\n  w/ Bow",              LogicSpiritSunChestDesc);
Option LogicShadowFireArrowEntry        = LogicTrick("ShT Entry\n  w/ Fire Arrows",               LogicShadowFireArrowEntryDesc); //Needs Testing
Option LogicShadowUmbrella              = LogicTrick("ShT Stone Umbrella\n  w/ Hover Boots",      LogicShadowUmbrellaDesc);
Option LogicShadowFreestandingKey       = LogicTrick("ShT Skull Vase Key\n  w/ Bombchu",          LogicShadowFreestandingKeyDesc);
Option LogicShadowStatue                = LogicTrick("ShT River Statue\n  w/ Bombchu",            LogicShadowStatueDesc);
Option LogicShadowBongo                 = LogicTrick("ShT Bongo\n  w/o Projectiles",              LogicShadowBongoDesc);
Option LogicChildDeadhand               = LogicTrick("BotW Deadhand\n  w/o Sword",                LogicChildDeadhandDesc);
Option LogicGtgWithoutHookshot          = LogicTrick("GTG West Silver Rupee\n  w/o Hookshot",     LogicGtgWithoutHookshotDesc);
Option LogicGtgFakeWall                 = LogicTrick("GTG Invisible Wall\n  w/ Hover Boots",      LogicGtgFakeWallDesc);
Option LogicLensSpirit                  = LogicTrick("SpT Navigate\n  w/o Lens of Truth",         LogicLensSpiritDesc);
Option LogicLensShadow                  = LogicTrick("ShT Early Rooms\n  w/o Lens of Truth",      LogicLensShadowDesc);
Option LogicLensShadowBack              = LogicTrick("ShT Later Rooms\n  w/o Lens of Truth",      LogicLensShadowBackDesc);
Option LogicLensBotw                    = LogicTrick("BotW Navigate\n  w/o Lens of Truth",        LogicLensBotwDesc);
Option LogicLensGtg                     = LogicTrick("GTG Navigate\n  w/o Lens of Truth",         LogicLensGtgDesc);
Option LogicLensCastle                  = LogicTrick("GaC Navigate\n  w/o Lens of Truth",         LogicLensCastleDesc);
Option LogicLensJabuMQ                  = LogicTrick("JJB MQ Navigate\n  w/o Lens of Truth",      LogicLensJabuMQDesc);
Option LogicLensSpiritMQ                = LogicTrick("SpT MQ Navigate\n  w/o Lens of Truth",      LogicLensSpiritMQDesc);
Option LogicLensShadowMQ                = LogicTrick("ShT MQ Early Rooms\n  w/o Lens of Truth",   LogicLensShadowMQDesc);
Option LogicLensShadowMQBack            = LogicTrick("ShT MQ Later Rooms\n  w/o Lens of Truth",   LogicLensShadowMQBackDesc);
Option LogicLensBotwMQ                  = LogicTrick("BotW MQ Nagivate\n  w/o Lens of Truth",     LogicLensBotwMQDesc);
Option LogicLensGtgMQ                   = LogicTrick("GTG MQ Navigate\n  w/o Lens of Truth",      LogicLensGtgMQDesc);
Option LogicLensCastleMQ                = LogicTrick("GaC MQ Navigate\n  w/o Lens of Truth",      LogicLensCastleMQDesc);
Option LogicSpiritTrialHookshot         = LogicTrick("Spirit Trial\n  w/o Hookshot",              LogicSpiritTrialHookshotDesc);
Option LogicFlamingChests               = LogicTrick("Open chests through\n  flame circles",      LogicFlamingChestsDesc);
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
    &LogicGVHammerChest,
    &LogicGerudoKitchen,
    &LogicGerudoChildClimb,
    &LogicLensWasteland,
    &LogicReverseWasteland,
    &LogicColossusGS,
    &LogicOutsideGanonsGS,
    &LogicManOnRoof,
    &LogicWindmillPoHHookshot,
    &LogicDMTBombable,
    &LogicDMTSoilGS,
    &LogicDMTSummitHover,
    &LogicLinkGoronDins,
    &LogicGoronCityLeftMost,
    &LogicGoronCityPot,
    &LogicGoronCityPotWithStrength,
    &LogicChildRollingWithStrength,
    // &LogicCraterUpperToLower, Needs Testing           Possible to break in 1 swing if you hit the right place? Right angle? Seems very inconsistent.
    &LogicCraterBeanPoHWithHovers,
    &LogicBiggoronBolero,
    &LogicZoraRiverLower,
    &LogicZoraRiverUpper,
    &LogicZFGreatFairy,
    &LogicDekuB1WebsWithBow,
    &LogicDekuB1Skip,
    &LogicDekuBasementGS,
    &LogicDCStaircase,
    &LogicDCJump,
    &LogicDCSlingshotSkip,
    &LogicDCScarecrowGS,
    // &LogicJabuBossGSAdult, Needs Testing              Don't know if possible as described, easier method exists as you can just backwalk with the box
    &LogicJabuScrubJumpDive,
    // &LogicForestOutsideBackdoor, Needs Testing        Possible with bombchu damage boost, jumpslash is definitely harder than "intermediate" if at all possible
    &LogicForestDoorFrame,
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
    &LogicSpiritSunChest,
    // &LogicShadowFireArrowEntry, Needs Testing
    &LogicShadowUmbrella,
    &LogicShadowFreestandingKey,
    &LogicShadowStatue,
    &LogicShadowBongo,
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
    &LogicFlamingChests,
};
// clang-format on
// Function to avoid accidentally naming the options wrong, as logic.cpp requires these exact names
std::vector<std::string> GlitchDifficultyOptions(u8 enabledDifficulties) {
    static constexpr std::array glitchDifficulties{ "Novice", "Intermediate", "Advanced", "Expert", "Hero" };

    std::vector<std::string> selectableDifficulties;
    selectableDifficulties.push_back("Disabled");
    for (size_t i = 0; i < glitchDifficulties.size(); i++) {
        if ((enabledDifficulties >> i) & 1) {
            selectableDifficulties.push_back(glitchDifficulties[i]);
        }
    }

    return selectableDifficulties;
}
// clang-format off
Option ToggleAllGlitches        = Option::U8("All Glitches",          GlitchDifficultyOptions(0b11111), { ToggleAllGlitchesDesc }, OptionCategory::Toggle);
Option GlitchRestrictedItems    = Option::U8("Restricted Items",      GlitchDifficultyOptions(0b00001), { GlitchRestrictedItemsDescDisabled    , GlitchRestrictedItemsDescNovice                                                                                                                                                              });
Option GlitchSuperStab          = Option::U8("Super Stab",            GlitchDifficultyOptions(0b00001), { GlitchSuperStabDescDisabled          , GlitchSuperStabDescNovice                                                                                                                                                                    });
Option GlitchISG                = Option::U8("Infinite Sword Glitch", GlitchDifficultyOptions(0b00111), { GlitchISGDescDisabled                , GlitchISGDescNovice                , GlitchISGDescIntermediate                , GlitchISGDescAdvanced                                                                                        });
Option GlitchHover              = Option::U8("Bomb Hover",            GlitchDifficultyOptions(0b00111), { GlitchHoverDescDisabled              , GlitchHoverDescNovice              , GlitchHoverDescIntermediate              , GlitchHoverDescAdvanced                                                                                      });
Option GlitchBombOI             = Option::U8("Ocarina Items (Bomb)",  GlitchDifficultyOptions(0b01111), { GlitchBombOIDescDisabled             , GlitchBombOIDescNovice             , GlitchBombOIDescIntermediate             , GlitchBombOIDescAdvanced             , GlitchBombOIDescExpert                                                });
Option GlitchHoverBoost         = Option::U8("HoverBoost",            GlitchDifficultyOptions(0b00111), { GlitchHoverBoostDescDisabled         , GlitchHoverBoostDescNovice         , GlitchHoverBoostDescIntermediate         , GlitchHoverBoostDescAdvanced                                                                                 });
Option GlitchSuperSlide         = Option::U8("Extended Super Slide",  GlitchDifficultyOptions(0b01111), { GlitchSuperSlideDescDisabled         , GlitchSuperSlideDescNovice         , GlitchSuperSlideDescIntermediate         , GlitchSuperSlideDescAdvanced         , GlitchSuperSlideDescExpert                                            });
Option GlitchMegaflip           = Option::U8("Megaflip",              GlitchDifficultyOptions(0b11111), { GlitchMegaflipDescDisabled           , GlitchMegaflipDescNovice           , GlitchMegaflipDescIntermediate           , GlitchMegaflipDescAdvanced           , GlitchMegaflipDescExpert           , GlitchMegaflipDescHero           });
Option GlitchASlide             = Option::U8("A-Slide",               GlitchDifficultyOptions(0b01111), { GlitchASlideDescDisabled             , GlitchASlideDescNovice             , GlitchASlideDescIntermediate             , GlitchASlideDescAdvanced             , GlitchASlideDescExpert                                                });
Option GlitchHammerSlide        = Option::U8("Hammer Slide",          GlitchDifficultyOptions(0b00011), { GlitchHammerSlideDescDisabled        , GlitchHammerSlideDescNovice        , GlitchHammerSlideDescIntermediate                                                                                                                       });
Option GlitchLedgeCancel        = Option::U8("Ledge Cancel",          GlitchDifficultyOptions(0b00111), { GlitchLedgeCancelDescDisabled        , GlitchLedgeCancelDescNovice        , GlitchLedgeCancelDescIntermediate        , GlitchLedgeCancelDescAdvanced                                                                                });
Option GlitchActionSwap         = Option::U8("Action Swap",           GlitchDifficultyOptions(0b00101), { GlitchActionSwapDescDisabled         , GlitchActionSwapDescNovice                                                    , GlitchActionSwapDescAdvanced                                                                                 });
Option GlitchQPA                = Option::U8("Quick Put Away",        GlitchDifficultyOptions(0b01111), { GlitchQPADescDisabled                , GlitchQPADescNovice                , GlitchQPADescIntermediate                , GlitchQPADescAdvanced                , GlitchQPADescExpert                                                   });
Option GlitchHookshotClip       = Option::U8("Hookshot Clip",         GlitchDifficultyOptions(0b00011), { GlitchHookshotClipDescDisabled       , GlitchHookshotClipDescNovice       , GlitchHookshotClipDescIntermediate                                                                                                                      });
Option GlitchHookshotJump_Bonk  = Option::U8("Hookshot Jump (Bonk)",  GlitchDifficultyOptions(0b00111), { GlitchHookshotJump_BonkDescDisabled  , GlitchHookshotJump_BonkDescNovice  , GlitchHookshotJump_BonkDescIntermediate  , GlitchHookshotJump_BonkDescAdvanced                                                                          });
Option GlitchHookshotJump_Boots = Option::U8("Hookshot Jump (Boots)", GlitchDifficultyOptions(0b00111), { GlitchHookshotJump_BootsDescDisabled , GlitchHookshotJump_BootsDescNovice , GlitchHookshotJump_BootsDescIntermediate , GlitchHookshotJump_BootsDescAdvanced                                                                         });
Option GlitchCutsceneDive       = Option::U8("Cutscene Dives",        GlitchDifficultyOptions(0b00111), { GlitchCutsceneDiveDescDisabled       , GlitchCutsceneDiveDescNovice       , GlitchCutsceneDiveDescIntermediate       , GlitchCutsceneDiveDescAdvanced                                                                               });
Option GlitchNaviDive_Stick     = Option::U8("Navi Dive (Stick)",     GlitchDifficultyOptions(0b00111), { GlitchNaviDive_StickDescDisabled     , GlitchNaviDive_StickDescNovice     , GlitchNaviDive_StickDescIntermediate     , GlitchNaviDive_StickDescAdvanced                                                                             });
Option GlitchTripleSlashClip    = Option::U8("Triple Slash Clip",     GlitchDifficultyOptions(0b01111), { GlitchTripleSlashClipDescDisabled    , GlitchTripleSlashClipDescNovice    , GlitchTripleSlashClipDescIntermediate    , GlitchTripleSlashClipDescAdvanced    , GlitchTripleSlashClipDescExpert                                       });
Option GlitchLedgeClip          = Option::U8("Ledge Clip",            GlitchDifficultyOptions(0b00111), { GlitchLedgeClipDescDisabled          , GlitchLedgeClipDescNovice          , GlitchLedgeClipDescIntermediate          , GlitchLedgeClipDescAdvanced                                                                                  });
Option GlitchSeamWalk           = Option::U8("Seam Walk",             GlitchDifficultyOptions(0b11111), { GlitchSeamWalkDescDisabled           , GlitchSeamWalkDescNovice           , GlitchSeamWalkDescIntermediate           , GlitchSeamWalkDescAdvanced           , GlitchSeamWalkDescExpert           , GlitchSeamWalkDescHero           });
std::vector<Option*> glitchCategories = {
    &ToggleAllGlitches,
    &GlitchRestrictedItems,
    &GlitchSuperStab,
    &GlitchISG,
    &GlitchHover,
    &GlitchBombOI,
    &GlitchHoverBoost,
    &GlitchSuperSlide,
    &GlitchMegaflip,
    &GlitchASlide,
    &GlitchHammerSlide,
    &GlitchLedgeCancel,
    &GlitchActionSwap,
    &GlitchQPA,
    &GlitchHookshotClip,
    &GlitchHookshotJump_Bonk,
    &GlitchHookshotJump_Boots,
    &GlitchCutsceneDive,
    &GlitchNaviDive_Stick,
    &GlitchTripleSlashClip,
    &GlitchLedgeClip,
    &GlitchSeamWalk,
};

Option GlitchWWTEscape         = Option::Bool("WWT Kokiri\n  Forest Escape", {"Off", "On"}, {GlitchWWTEscapeDesc});
Option GlitchGVTentAsChild     = Option::Bool("Enter GV Tent\n  as Child",   {"Off", "On"}, {GlitchGVTentAsChildDesc});
Option GlitchGFGuardSneak      = Option::Bool("Sneak Past\n  the GF Guard",  {"Off", "On"}, {GlitchGFGuardSneakDesc});
Option GlitchItemlessWasteland = Option::Bool("Cross the HW\n  w/o Items",   {"Off", "On"}, {GlitchItemlessWastelandDesc});
Option GlitchOccamsStatue      = Option::Bool("Occam's Statue",              {"Off", "On"}, {GlitchOccamsStatueDesc});
Option GlitchZDOoBJumpSlash    = Option::Bool("ZD OoB w/\n  Jump Slash",     {"Off", "On"}, {GlitchZDOoBJumpSlashDesc});
Option GlitchJabuStickRecoil   = Option::Bool("Enter Jabu\n  w/o Bottle",    {"Off", "On"}, {GlitchJabuStickRecoilDesc});
Option GlitchJabuAdult         = Option::Bool("Enter Jabu\n  as Adult",      {"Off", "On"}, {GlitchJabuAdultDesc});
Option GlitchBlueFireWall      = Option::Bool("Break Walls\n  w/ Blue Fire", {"Off", "On"}, {GlitchBlueFireWallDesc});
Option GlitchClassicHalfie     = Option::Bool("Classic Halfie",              {"Off", "On"}, {GlitchClassicHalfieDesc});
Option GlitchModernHalfie      = Option::Bool("Modern Halfie",               {"Off", "On"}, {GlitchModernHalfieDesc});
Option GlitchJabuSwitch        = Option::Bool("Jabu Switch\n  w/ CS item",   {"Off", "On"}, {GlitchJabuSwitchDesc});
Option GlitchForestBKSkip      = Option::Bool("Forest Temple\n  BK Skip",    {"Off", "On"}, {GlitchForestBKSkipDesc});
Option GlitchFireGrunzClip     = Option::Bool("Fire Temple\n  Grunz Clip",   {"Off", "On"}, {GlitchFireGrunzClipDesc});
// These are all expected to be booleans by the GlitchEnabled function
std::vector<Option*> miscGlitches = {
    &GlitchWWTEscape,
    &GlitchGVTentAsChild,
    &GlitchGFGuardSneak,
    &GlitchItemlessWasteland,
    &GlitchOccamsStatue,
    &GlitchZDOoBJumpSlash,
    &GlitchJabuStickRecoil,
    &GlitchJabuAdult,
    &GlitchBlueFireWall,
    &GlitchClassicHalfie,
    &GlitchModernHalfie,
    &GlitchJabuSwitch,
    &GlitchForestBKSkip,
    &GlitchFireGrunzClip,
};

Menu glitchCategorySettings = Menu::SubMenu("General Categories",     &glitchCategories, "", false);
Menu miscGlitchSettings     = Menu::SubMenu("Miscellaneous Glitches", &miscGlitches,     "", false);
std::vector<Menu*> glitchOptions = {
    &glitchCategorySettings,
    &miscGlitchSettings,
};

Option MP_Enabled        = Option::U8  ("Multiplayer",     {"Off", "On (Local)"}, {mp_EnabledDesc});
Option MP_SharedProgress = Option::Bool("Shared Progress", {"Off", "On"},         {mp_SharedProgressDesc});
Option MP_SyncId         = Option::U8  (2, "Sync ID",      {NumOpts(1, 8)},       {mp_SyncIdDesc}, OptionCategory::Cosmetic);
Option MP_SharedHealth   = Option::Bool("Shared Health",   {"Off", "On"},         {mp_SharedHealthDesc});
Option MP_SharedRupees   = Option::Bool("Shared Rupees",   {"Off", "On"},         {mp_SharedRupeesDesc});
Option MP_SharedAmmo     = Option::Bool("Shared Ammo",     {"Off", "On"},         {mp_SharedAmmoDesc});
std::vector<Option*> multiplayerOptions = {
    &MP_Enabled,
    &MP_SharedProgress,
    &MP_SyncId,
    &MP_SharedHealth,
    &MP_SharedRupees,
    &MP_SharedAmmo,
};

Option QuickText           = Option::U8  ("Quick Text",             {"0: Vanilla", "1: Skippable", "2: Instant", "3: Turbo"},               {quickTextDesc0, quickTextDesc1, quickTextDesc2, quickTextDesc3},                                                 OptionCategory::Cosmetic,   QUICKTEXT_INSTANT);
Option MenuOpeningButton   = Option::U8  ("Open Info Menu with",    {"Select","Start","D-Pad Up","D-Pad Down","D-Pad Right","D-Pad Left",}, {menuButtonDesc},                                                                                                 OptionCategory::Cosmetic);
Option ArrowSwitchButton   = Option::U8  ("Switch Arrows with",     {"D-Pad Right","D-Pad Left","D-Pad Up","D-Pad Down","Touch Screen",},   {arrowSwitchDesc},                                                                                                OptionCategory::Cosmetic);
std::vector<Option*> preferenceOptions = {
    &QuickText,
    &MenuOpeningButton,
    &ArrowSwitchButton,
};

Option ZTargeting         = Option::U8("L-Targeting",          {"Switch", "Hold"},                                          {""},                     OptionCategory::Cosmetic, 1);
Option CameraControl      = Option::U8("Camera Control",       {"Normal", "Invert Y-axis"},                                 {""},                     OptionCategory::Cosmetic);
Option MotionControl      = Option::U8("Motion Control",       {"On", "Off"},                                               {""},                     OptionCategory::Cosmetic);
Option TogglePlayMusic    = Option::U8("Play Music",           {"Off", "On"},                                               {""},                     OptionCategory::Cosmetic, 1);
Option TogglePlaySFX      = Option::U8("Play Sound Effects",   {"Off", "On"},                                               {""},                     OptionCategory::Cosmetic, 1);
Option NaviNotifications  = Option::U8("Navi Notifications",   {"Silenced", "Normal", "Constant"},                          {naviNotificationsDesc},  OptionCategory::Cosmetic, NAVINOTIFS_NORMAL);
Option IgnoreMaskReaction = Option::U8("Ignore Mask Reaction", {"Off", "On"},                                               {ignoreMaskReactionDesc}, OptionCategory::Cosmetic);
Option SkipSongReplays    = Option::U8("Skip Song Replays",    {"Don't Skip", "Skip (No SFX)", "Skip (Keep SFX)"},          {skipSongReplaysDesc},    OptionCategory::Cosmetic);
Option FreeCamControl     = Option::U8("Free Camera Control",  {"Normal", "Invert Y-Axis", "Invert X-Axis", "Invert Both"}, {""},                     OptionCategory::Cosmetic);
std::vector<Option*> ingameDefaultOptions = {
    &ZTargeting,
    &CameraControl,
    &MotionControl,
    &TogglePlayMusic,
    &TogglePlaySFX,
    &NaviNotifications,
    &IgnoreMaskReaction,
    &SkipSongReplays,
    &FreeCamControl,
};

// Function to make options vectors for Navi and Tunic colors without the "Same as ..." option
std::vector<std::string> VectorCopyExceptLastElement(std::vector<std::string> vect) {
      std::vector<std::string> copy(vect.begin(), std::prev(vect.end()));
      return copy;
}

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

static std::vector<std::string> childTunicOptions = {
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
    "Gold",
    "Rainbow",
    "Same as Kokiri",
};
#define RAINBOW_TUNIC (childTunicOptions.size() - 2)
#define SAME_AS_KOKIRI (childTunicOptions.size() - 1)
static std::vector<std::string> tunicOptions = VectorCopyExceptLastElement(childTunicOptions);

static std::vector<std::string> naviOuterOptionNames = {
    std::string(RANDOM_CHOICE_STR),
    std::string(RANDOM_COLOR_STR),
    std::string(CUSTOM_COLOR_STR),
    "White",
    "Green",
    "Light Blue",
    "Yellow",
    "Red",
    "Magenta",
    "Gold",
    "Black",
    "Tatl",
    "Tael",
    "Fi",
    "Ciela",
    "Epona",
    "Ezlo",
    "King Red Lions",
    "Linebeck",
    "Loftwing",
    "Midna",
    "Phantom Zelda",
    "Rainbow",
    "Same as Inner",
};
#define RAINBOW_NAVI (naviOuterOptionNames.size() - 2)
#define SAME_AS_INNER_NAVI (naviOuterOptionNames.size() - 1)
static std::vector<std::string> naviInnerOptionNames = VectorCopyExceptLastElement(naviOuterOptionNames);

static std::vector<std::string> weaponTrailOuterOptionNames = {
    std::string(RANDOM_CHOICE_STR),
    std::string(RANDOM_COLOR_STR),
    std::string(CUSTOM_COLOR_STR),
    "White",
    "Black",
    "Red",
    "Green",
    "Blue",
    "Yellow",
    "Cyan",
    "Magenta",
    "Orange",
    "Gold",
    "Purple",
    "Pink",
    "Rainbow",
    "Same as Inner",
};
#define RAINBOW_TRAIL (weaponTrailOuterOptionNames.size() - 2)
#define SAME_AS_INNER_TRAIL (weaponTrailOuterOptionNames.size() - 1)
static std::vector<std::string> weaponTrailInnerOptionNames = VectorCopyExceptLastElement(weaponTrailOuterOptionNames);

static std::vector<std::string> trailDurationOptionNames = {
    "Disabled",
    "Very short",
    "Vanilla",
    "Long",
    "Very Long",
    "Lightsaber",
};

static std::vector<std::string> chuTrailDurationOptionNames = {
    "Disabled",
    "Short",
    "Vanilla",
    "Long",
    "Very Long",
    "Hero's Path",
};

static std::vector<std::string_view> cosmeticDescriptions = {
    RANDOM_CHOICE_DESC,
    RANDOM_COLOR_DESC,
    CUSTOM_COLOR_DESC,
    "This will only affect the color on Link's model.",
};

Option CustomTunicColors          = Option::Bool("Custom Tunic Colors",      {"Off", "On"},                 {""},                                                                                                                                                             OptionCategory::Cosmetic);
Option ChildTunicColor            = Option::U8  (2, "Child Tunic Color",     childTunicOptions,             cosmeticDescriptions,                                                                                                                                             OptionCategory::Cosmetic,        SAME_AS_KOKIRI);
Option KokiriTunicColor           = Option::U8  (2, "Kokiri Tunic Color",    tunicOptions,                  cosmeticDescriptions,                                                                                                                                             OptionCategory::Cosmetic,                     3); // Kokiri Green
Option GoronTunicColor            = Option::U8  (2, "Goron Tunic Color",     tunicOptions,                  cosmeticDescriptions,                                                                                                                                             OptionCategory::Cosmetic,                     4); // Goron Red
Option ZoraTunicColor             = Option::U8  (2, "Zora Tunic Color",      tunicOptions,                  cosmeticDescriptions,                                                                                                                                             OptionCategory::Cosmetic,                     5); // Zora Blue
Option SilverGauntletsColor       = Option::U8  ("Silver Gauntlets Color",   gauntletOptions,               cosmeticDescriptions,                                                                                                                                             OptionCategory::Cosmetic,                     3); // Silver
Option GoldGauntletsColor         = Option::U8  ("Gold Gauntlets Color",     gauntletOptions,               cosmeticDescriptions,                                                                                                                                             OptionCategory::Cosmetic,                     4); // Gold
Option CustomNaviColors           = Option::Bool("Custom Navi Colors",       {"Off", "On"},                 {""},                                                                                                                                                             OptionCategory::Cosmetic);
Option IdleNaviInnerColor         = Option::U8  (2, "Idle (Inner)",          naviInnerOptionNames,          {RANDOM_CHOICE_DESC, RANDOM_COLOR_DESC, CUSTOM_COLOR_DESC, naviColorsDesc},                                                                                       OptionCategory::Cosmetic,                     3); // White
Option NPCNaviInnerColor          = Option::U8  (2, "On NPC (Inner)",        naviInnerOptionNames,          {RANDOM_CHOICE_DESC, RANDOM_COLOR_DESC, CUSTOM_COLOR_DESC, naviColorsDesc},                                                                                       OptionCategory::Cosmetic,                     5); // Light Blue
Option EnemyNaviInnerColor        = Option::U8  (2, "On Enemy (Inner)",      naviInnerOptionNames,          {RANDOM_CHOICE_DESC, RANDOM_COLOR_DESC, CUSTOM_COLOR_DESC, naviColorsDesc},                                                                                       OptionCategory::Cosmetic,                     6); // Yellow
Option PropNaviInnerColor         = Option::U8  (2, "On Prop (Inner)",       naviInnerOptionNames,          {RANDOM_CHOICE_DESC, RANDOM_COLOR_DESC, CUSTOM_COLOR_DESC, naviColorsDesc},                                                                                       OptionCategory::Cosmetic,                     4); // Green
Option IdleNaviOuterColor         = Option::U8  (2, "Idle (Outer)",          naviOuterOptionNames,          {RANDOM_CHOICE_DESC, RANDOM_COLOR_DESC, CUSTOM_COLOR_DESC, naviColorsDesc},                                                                                       OptionCategory::Cosmetic,    SAME_AS_INNER_NAVI);
Option NPCNaviOuterColor          = Option::U8  (2, "On NPC (Outer)",        naviOuterOptionNames,          {RANDOM_CHOICE_DESC, RANDOM_COLOR_DESC, CUSTOM_COLOR_DESC, naviColorsDesc},                                                                                       OptionCategory::Cosmetic,    SAME_AS_INNER_NAVI);
Option EnemyNaviOuterColor        = Option::U8  (2, "On Enemy (Outer)",      naviOuterOptionNames,          {RANDOM_CHOICE_DESC, RANDOM_COLOR_DESC, CUSTOM_COLOR_DESC, naviColorsDesc},                                                                                       OptionCategory::Cosmetic,    SAME_AS_INNER_NAVI);
Option PropNaviOuterColor         = Option::U8  (2, "On Prop (Outer)",       naviOuterOptionNames,          {RANDOM_CHOICE_DESC, RANDOM_COLOR_DESC, CUSTOM_COLOR_DESC, naviColorsDesc},                                                                                       OptionCategory::Cosmetic,    SAME_AS_INNER_NAVI);
Option CustomTrailEffects         = Option::Bool("Custom Trail Effects",     {"Off", "On"},                 {""},                                                                                                                                                             OptionCategory::Cosmetic);
Option ChosenSimpleMode           = Option::Bool(2, "Draw simple texture",   {"When necessary","Always"},   {necessarySimpleModeDesc,alwaysSimpleModeDesc},                                                                                                                   OptionCategory::Cosmetic);
Option SwordTrailInnerColor       = Option::U8  (2, "Sword (Inner Color)",   weaponTrailInnerOptionNames,   {RANDOM_CHOICE_DESC, RANDOM_COLOR_DESC, CUSTOM_COLOR_DESC, "Select the color that appears from the base\nof the sword."},                                         OptionCategory::Cosmetic,                      3); // White
Option SwordTrailOuterColor       = Option::U8  (2, "Sword (Outer Color)",   weaponTrailOuterOptionNames,   {RANDOM_CHOICE_DESC, RANDOM_COLOR_DESC, CUSTOM_COLOR_DESC, "Select the color that appears from the tip\nof the sword."},                                          OptionCategory::Cosmetic,    SAME_AS_INNER_TRAIL);
Option SwordTrailDuration         = Option::U8  (2, "Sword (Duration)",      trailDurationOptionNames,      {"Select the duration for sword trails.\n\nIf too many trails are on screen, the duration\nmay be capped at Long for some of them."},                             OptionCategory::Cosmetic,                      2); // Vanilla
Option BoomerangTrailColor        = Option::U8  (2, "Boomerang (Color)",     weaponTrailInnerOptionNames,   {RANDOM_CHOICE_DESC, RANDOM_COLOR_DESC, CUSTOM_COLOR_DESC, "Select the color for boomerang trails."},                                                             OptionCategory::Cosmetic,                      8); // Yellow
Option BoomerangTrailDuration     = Option::U8  (2, "Boomerang (Duration)",  trailDurationOptionNames,      {"Select the duration for boomerang trails."},                                                                                                                    OptionCategory::Cosmetic,                      2); // Vanilla
Option BombchuTrailInnerColor     = Option::U8  (2, "Bombchu (Inner Color)", weaponTrailInnerOptionNames,   {RANDOM_CHOICE_DESC, RANDOM_COLOR_DESC, CUSTOM_COLOR_DESC, "Select the color for the center of the\nbombchu trail."},                                             OptionCategory::Cosmetic,                      5); // Red
Option BombchuTrailOuterColor     = Option::U8  (2, "Bombchu (Outer Color)", weaponTrailOuterOptionNames,   {RANDOM_CHOICE_DESC, RANDOM_COLOR_DESC, CUSTOM_COLOR_DESC, "Select the color for the sides of the\nbombchu trail."},                                              OptionCategory::Cosmetic,    SAME_AS_INNER_TRAIL);
Option BombchuTrailDuration       = Option::U8  (2, "Bombchu (Duration)",    chuTrailDurationOptionNames,   {"Select the duration for bombchu trails."},                                                                                                                      OptionCategory::Cosmetic,                      2); // Vanilla
std::string finalChildTunicColor      = ChildTunicColor.GetSelectedOptionText();
std::string finalKokiriTunicColor     = KokiriTunicColor.GetSelectedOptionText();
std::string finalGoronTunicColor      = GoronTunicColor.GetSelectedOptionText();
std::string finalZoraTunicColor       = ZoraTunicColor.GetSelectedOptionText();
std::string finalSilverGauntletsColor = SilverGauntletsColor.GetSelectedOptionText();
std::string finalGoldGauntletsColor   = GoldGauntletsColor.GetSelectedOptionText();
std::string finalIdleNaviInnerColor   = IdleNaviInnerColor.GetSelectedOptionText();
std::string finalNPCNaviInnerColor    = NPCNaviInnerColor.GetSelectedOptionText();
std::string finalEnemyNaviInnerColor  = EnemyNaviInnerColor.GetSelectedOptionText();
std::string finalPropNaviInnerColor   = PropNaviInnerColor.GetSelectedOptionText();
std::string finalIdleNaviOuterColor   = IdleNaviOuterColor.GetSelectedOptionText();
std::string finalNPCNaviOuterColor    = NPCNaviOuterColor.GetSelectedOptionText();
std::string finalEnemyNaviOuterColor  = EnemyNaviOuterColor.GetSelectedOptionText();
std::string finalPropNaviOuterColor   = PropNaviOuterColor.GetSelectedOptionText();
std::string finalSwordTrailOuterColor = SwordTrailOuterColor.GetSelectedOptionText();
std::string finalSwordTrailInnerColor = SwordTrailInnerColor.GetSelectedOptionText();
Color_RGBA8 finalBoomerangColor = {0};
u8 boomerangTrailColorMode = 0;
std::string finalChuTrailInnerColor   = BombchuTrailInnerColor.GetSelectedOptionText();
std::string finalChuTrailOuterColor   = BombchuTrailOuterColor.GetSelectedOptionText();

Option ColoredKeys         = Option::Bool("Colored Small Keys",     {"Off", "On"},                                {coloredKeysDesc},                                                                                                                                  OptionCategory::Cosmetic);
Option ColoredBossKeys     = Option::Bool("Colored Boss Keys",      {"Off", "On"},                                {coloredBossKeysDesc},                                                                                                                              OptionCategory::Cosmetic);
Option MirrorWorld         = Option::U8  ("Mirror World",           {"Off", "On", "Scene", "Entrance", "Random"}, {mirrorWorldOffDesc, mirrorWorldOnDesc, mirrorWorldSceneDesc, mirrorWorldEntranceDesc, mirrorWorldRandomDesc},                                      OptionCategory::Cosmetic);
Option BetaSoldOut         = Option::Bool("Beta Sold-Out Model",    {"Off", "On"},                                {betaSoldOutDesc},                                                                                                                                  OptionCategory::Cosmetic);
Option SoullessEnemiesLook = Option::U8  ("Soulless Enemies Look",  {"Purple Flame", "Flashing"},                 {soullessPurpleFlameDesc, soullessFlashingDesc},                                                                                                    OptionCategory::Cosmetic);

std::vector<Option *> cosmeticOptions = {
    &CustomTunicColors,
    &ChildTunicColor,
    &KokiriTunicColor,
    &GoronTunicColor,
    &ZoraTunicColor,
    &SilverGauntletsColor,
    &GoldGauntletsColor,
    &CustomNaviColors,
    &IdleNaviInnerColor,
    &NPCNaviInnerColor,
    &EnemyNaviInnerColor,
    &PropNaviInnerColor,
    &IdleNaviOuterColor,
    &NPCNaviOuterColor,
    &EnemyNaviOuterColor,
    &PropNaviOuterColor,
    &CustomTrailEffects,
    &ChosenSimpleMode,
    &SwordTrailInnerColor,
    &SwordTrailOuterColor,
    &SwordTrailDuration,
    &BoomerangTrailColor,
    &BoomerangTrailDuration,
    &BombchuTrailInnerColor,
    &BombchuTrailOuterColor,
    &BombchuTrailDuration,
    &ColoredKeys,
    &ColoredBossKeys,
    &MirrorWorld,
    &BetaSoldOut,
    &SoullessEnemiesLook,
};

static std::vector<std::string> musicOptions = {"Off", "On (Mixed)", "On (Grouped)", "On (Own)"};

Option ShuffleMusic    = Option::Bool("Shuffle Music",                   {"Off", "On"},                             {musicRandoDesc},                                                                                                                          OptionCategory::Cosmetic);
Option ShuffleBGM      = Option::U8  (2, "Shuffle BGM",                  {musicOptions},                            {shuffleBGMDesc},                                                                                                                          OptionCategory::Cosmetic,               SHUFFLEMUSIC_MIXED);
Option ShuffleMelodies = Option::U8  (2, "Shuffle Melodies",             {musicOptions},                            {shuffleMelodiesDesc},                                                                                                                     OptionCategory::Cosmetic,               SHUFFLEMUSIC_GROUPED);
Option CustomMusic     = Option::Bool(2, "Custom Music",                 {"Off", "On"},                             {customMusicDesc},                                                                                                                         OptionCategory::Cosmetic);
Option CustomMusicOnly = Option::Bool(4, "Custom Music Only",            {"Off", "On"},                             {customMusicOnlyDesc},                                                                                                                     OptionCategory::Cosmetic);

Option ShuffleSFX              = Option::U8  ("Shuffle SFX",             {"Off", "All", "Scene Specific", "Chaos"}, {shuffleSFXOff, shuffleSFXAll, shuffleSFXSceneSpecific, shuffleSFXChaos},                                                                  OptionCategory::Cosmetic);
Option ShuffleSFXFootsteps     = Option::Bool(2, "Include Footsteps",    {"No", "Yes"},                             {""},                                                                                                                                      OptionCategory::Cosmetic,               ON);
Option ShuffleSFXLinkVoice     = Option::Bool(2, "Include Link's Voice", {"No", "Yes"},                             {""},                                                                                                                                      OptionCategory::Cosmetic,               ON);
Option ShuffleSFXCategorically = Option::Bool(2, "Categorical Shuffle",  {"Off", "On"},                             {shuffleSFXCategorically},                                                                                                                 OptionCategory::Cosmetic,               ON);

std::vector<Option*> audioOptions = {
    &ShuffleMusic,
    &ShuffleBGM,
    &ShuffleMelodies,
    &CustomMusic,
    &CustomMusicOnly,
    &ShuffleSFX,
    &ShuffleSFXFootsteps,
    &ShuffleSFXLinkVoice,
    &ShuffleSFXCategorically,
};

Menu preferences              = Menu::SubMenu("Misc Preferences",           &preferenceOptions);
Menu ingameDefaults           = Menu::SubMenu("Ingame Defaults",            &ingameDefaultOptions, menuIngameDefaultsDesc);
Menu cosmetics                = Menu::SubMenu("Cosmetic Settings",          &cosmeticOptions);
Menu audio                    = Menu::SubMenu("Audio Settings",             &audioOptions);
std::vector<Menu*> personalizationOptions = {
    &preferences,
    &ingameDefaults,
    &cosmetics,
    &audio,
};

Menu loadPremadePreset      = Menu::Action("Load Premade Preset",        LOAD_PREMADE_PRESET);
Menu loadCustomPreset       = Menu::Action("Load Custom Preset",         LOAD_CUSTOM_PRESET);
Menu saveCustomPreset       = Menu::Action("Save Custom Preset",         SAVE_CUSTOM_PRESET);
Menu deleteCustomPreset     = Menu::Action("Delete Custom Preset",       DELETE_CUSTOM_PRESET);
Menu resetToDefaultSettings = Menu::Action("Reset to Default Settings",  RESET_TO_DEFAULTS, menuResetToDefaultsDesc);

std::vector<Menu *> settingsPresetItems = {
    &loadPremadePreset,
    &loadCustomPreset,
    &saveCustomPreset,
    &deleteCustomPreset,
    &resetToDefaultSettings,
};

// Detailed Logic Options Submenu
Menu logicSettings    = Menu::SubMenu("Logic Options",     &logicOptions);
Menu excludeLocations = Menu::SubMenu("Exclude Locations", &excludeLocationsMenus, "",                    false);
Menu tricks           = Menu::SubMenu("Logical Tricks",    &trickOptions,          "",                    false);
Menu glitchSettings   = Menu::SubMenu("Glitch Options",    &glitchOptions,         menuGlitchOptionsDesc, false);
std::vector<Menu *> detailedLogicOptions = {
    &logicSettings,
    &excludeLocations,
    &tricks,
    &glitchSettings,
};

Menu open                     = Menu::SubMenu("Open Settings",              &openOptions, menuOpenSettingsDesc);
Menu world                    = Menu::SubMenu("World Settings",             &worldOptions);
Menu shuffle                  = Menu::SubMenu("Shuffle Settings",           &shuffleOptions);
Menu shuffleDungeonItems      = Menu::SubMenu("Shuffle Dungeon Items",      &shuffleDungeonItemOptions);
Menu detailedLogic            = Menu::SubMenu("Detailed Logic Settings",    &detailedLogicOptions);
Menu startingInventory        = Menu::SubMenu("Starting Inventory",         &startingInventoryOptions, "", false);
Menu timesaverSettings        = Menu::SubMenu("Timesaver Settings",         &timesaverOptions);
Menu miscSettings             = Menu::SubMenu("Misc Settings",              &miscOptions);
Menu itemPoolSettings         = Menu::SubMenu("Item Pool Settings",         &itemPoolOptions);
Menu itemUsabilitySettings    = Menu::SubMenu("Item Usability Settings",    &itemUsabilityOptions);
Menu gameplaySettings         = Menu::SubMenu("Gameplay Settings",          &gameplayOptions);
Menu multiplayerSettings      = Menu::SubMenu("Multiplayer Settings",       &multiplayerOptions);
Menu personalization          = Menu::SubMenu("Personalization Settings",   &personalizationOptions, menuPersonalizationDesc);
Menu settingsPresets          = Menu::SubMenu("Settings Presets",           &settingsPresetItems);
Menu generateRandomizer       = Menu::Action ("Generate Randomizer",        GENERATE_MODE);

// adding a menu with no options crashes, might fix later
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
    &gameplaySettings,
    &multiplayerSettings,
    &personalization,
    &settingsPresets,
    &generateRandomizer,
};
// clang-format on

// declared here, set in fill.cpp
u32 LinksPocketRewardBitMask = 0;
std::array<u32, 9> rDungeonRewardOverrides{};

// declared here, set in menu.cpp
u8 PlayOption;
u8 Region;

// Fills and returns a SettingsContext struct.
// This struct is written to the code.ips patch and allows the game
// to read what settings the player selected to make in game decisions.
SettingsContext FillContext() {
    SettingsContext ctx = {};
    ctx.hashIndexes[0]  = hashIconIndexes[0];
    ctx.hashIndexes[1]  = hashIconIndexes[1];
    ctx.hashIndexes[2]  = hashIconIndexes[2];
    ctx.hashIndexes[3]  = hashIconIndexes[3];
    ctx.hashIndexes[4]  = hashIconIndexes[4];
    ctx.region          = Region;

    ctx.logic                = Logic.Value<u8>();
    ctx.openForest           = OpenForest.Value<u8>();
    ctx.openKakariko         = OpenKakariko.Value<u8>();
    ctx.openDoorOfTime       = OpenDoorOfTime.Value<u8>();
    ctx.zorasFountain        = ZorasFountain.Value<u8>();
    ctx.openJabu             = OpenJabu.Value<u8>();
    ctx.gerudoFortress       = GerudoFortress.Value<u8>();
    ctx.rainbowBridge        = Bridge.Value<u8>();
    ctx.bridgeStoneCount     = BridgeStoneCount.Value<u8>();
    ctx.bridgeMedallionCount = BridgeMedallionCount.Value<u8>();
    ctx.bridgeRewardCount    = BridgeRewardCount.Value<u8>();
    ctx.bridgeDungeonCount   = BridgeDungeonCount.Value<u8>();
    ctx.bridgeTokenCount     = BridgeTokenCount.Value<u8>();
    ctx.bridgeHeartCount     = BridgeHeartCount.Value<u8>();
    ctx.randomGanonsTrials   = (RandomGanonsTrials) ? 1 : 0;
    ctx.ganonsTrialsCount    = GanonsTrialsCount.Value<u8>();

    ctx.startingAge               = StartingAge.Value<u8>();
    ctx.resolvedStartingAge       = ResolvedStartingAge;
    ctx.shuffleDungeonEntrances   = ShuffleDungeonEntrances.Value<u8>();
    ctx.shuffleBossEntrances      = ShuffleBossEntrances.Value<u8>();
    ctx.shuffleOverworldEntrances = (ShuffleOverworldEntrances) ? 1 : 0;
    ctx.shuffleInteriorEntrances  = ShuffleInteriorEntrances.Value<u8>();
    ctx.shuffleGrottoEntrances    = (ShuffleGrottoEntrances) ? 1 : 0;
    ctx.shuffleOwlDrops           = (ShuffleOwlDrops) ? 1 : 0;
    ctx.shuffleWarpSongs          = (ShuffleWarpSongs) ? 1 : 0;
    ctx.shuffleOverworldSpawns    = (ShuffleOverworldSpawns) ? 1 : 0;
    ctx.mixedEntrancePools        = (MixedEntrancePools) ? 1 : 0;
    ctx.mixDungeons               = (MixDungeons) ? 1 : 0;
    ctx.mixOverworld              = (MixOverworld) ? 1 : 0;
    ctx.mixInteriors              = (MixInteriors) ? 1 : 0;
    ctx.mixGrottos                = (MixGrottos) ? 1 : 0;
    ctx.decoupleEntrances         = (DecoupleEntrances) ? 1 : 0;
    ctx.bombchusInLogic           = (BombchusInLogic) ? 1 : 0;
    ctx.ammoDrops                 = AmmoDrops.Value<u8>();
    ctx.heartDropRefill           = HeartDropRefill.Value<u8>();
    ctx.randomMQDungeons          = (MQDungeonCount.Value<u8>() == 13) ? 1 : 0;
    ctx.mqDungeonCount            = MQSet;

    ctx.triforceHunt           = (TriforceHunt) ? 1 : 0;
    ctx.triforcePiecesTotal    = TriforcePiecesTotal.Value<u8>() + 1;
    ctx.triforcePiecesRequired = TriforcePiecesRequired.Value<u8>() + 1;

    ctx.enemizer = (Enemizer) ? 1 : 0;
    for (u8 i = 0; i < ENEMY_MAX; i++) {
        ctx.enemizerList[i] = enemizerListOptions[i]->Value<u8>();
    }

    ctx.shuffleRewards         = ShuffleRewards.Value<u8>();
    ctx.linksPocketItem        = LinksPocketItem.Value<u8>();
    ctx.shuffleSongs           = ShuffleSongs.Value<u8>();
    ctx.tokensanity            = Tokensanity.Value<u8>();
    ctx.scrubsanity            = Scrubsanity.Value<u8>();
    ctx.shuffleCows            = (ShuffleCows) ? 1 : 0;
    ctx.shuffleKokiriSword     = (ShuffleKokiriSword) ? 1 : 0;
    ctx.shuffleMasterSword     = (ShuffleMasterSword) ? 1 : 0;
    ctx.shuffleOcarinas        = (ShuffleOcarinas) ? 1 : 0;
    ctx.shuffleWeirdEgg        = (ShuffleWeirdEgg) ? 1 : 0;
    ctx.shuffleGerudoToken     = (ShuffleGerudoToken) ? 1 : 0;
    ctx.shuffleMagicBeans      = (ShuffleMagicBeans) ? 1 : 0;
    ctx.shuffleMerchants       = ShuffleMerchants.Value<u8>();
    ctx.shuffleFrogSongRupees  = (ShuffleFrogSongRupees) ? 1 : 0;
    ctx.shuffleAdultTradeQuest = (ShuffleAdultTradeQuest) ? 1 : 0;
    ctx.shuffleChestMinigame   = ShuffleChestMinigame.Value<u8>();
    ctx.shuffleEnemySouls      = ShuffleEnemySouls.Value<u8>();
    ctx.shuffleOcarinaButtons  = (ShuffleOcarinaButtons) ? 1 : 0;

    ctx.mapsAndCompasses   = MapsAndCompasses.Value<u8>();
    ctx.keysanity          = Keysanity.Value<u8>();
    ctx.gerudoKeys         = GerudoKeys.Value<u8>();
    ctx.bossKeysanity      = BossKeysanity.Value<u8>();
    ctx.ganonsBossKey      = GanonsBossKey.Value<u8>();
    ctx.lacsCondition      = LACSCondition;
    ctx.lacsMedallionCount = LACSMedallionCount.Value<u8>();
    ctx.lacsStoneCount     = LACSStoneCount.Value<u8>();
    ctx.lacsRewardCount    = LACSRewardCount.Value<u8>();
    ctx.lacsDungeonCount   = LACSDungeonCount.Value<u8>();
    ctx.lacsTokenCount     = LACSTokenCount.Value<u8>();
    ctx.lacsHeartCount     = LACSHeartCount.Value<u8>();

    ctx.ringFortress = (RingFortress) ? 1 : 0;
    ctx.ringForest   = (RingForest) ? 1 : 0;
    ctx.ringFire     = (RingFire) ? 1 : 0;
    ctx.ringWater    = (RingWater) ? 1 : 0;
    ctx.ringSpirit   = (RingSpirit) ? 1 : 0;
    ctx.ringShadow   = (RingShadow) ? 1 : 0;
    ctx.ringWell     = (RingWell) ? 1 : 0;
    ctx.ringGtg      = (RingGtg) ? 1 : 0;
    ctx.ringCastle   = (RingCastle) ? 1 : 0;

    ctx.skipChildStealth   = (SkipChildStealth) ? 1 : 0;
    ctx.skipTowerEscape    = (SkipTowerEscape) ? 1 : 0;
    ctx.skipEponaRace      = (SkipEponaRace) ? 1 : 0;
    ctx.skipMinigamePhases = (SkipMinigamePhases) ? 1 : 0;
    ctx.freeScarecrow      = (FreeScarecrow) ? 1 : 0;
    ctx.fourPoesCutscene   = (FourPoesCutscene) ? 1 : 0;
    ctx.lakeHyliaOwl       = (LakeHyliaOwl) ? 1 : 0;
    ctx.bigPoeTargetCount  = BigPoeTargetCount.Value<u8>() + 1;
    ctx.numRequiredCuccos  = NumRequiredCuccos.Value<u8>();
    ctx.kingZoraSpeed      = KingZoraSpeed.Value<u8>();
    ctx.exactZoraSpeed     = ExactZoraSpeed.Value<u8>();
    ctx.completeMaskQuest  = CompleteMaskQuest ? 1 : 0;
    ctx.quickText          = QuickText.Value<u8>();
    ctx.skipSongReplays    = SkipSongReplays.Value<u8>();
    ctx.keepFWWarpPoint    = KeepFWWarpPoint ? 1 : 0;
    ctx.fastBunnyHood      = FastBunnyHood ? 1 : 0;

    ctx.gossipStoneHints    = GossipStoneHints.Value<u8>();
    ctx.totAltarHints       = ToTAltarHints ? 1 : 0;
    ctx.ganonHints          = GanonHints ? 1 : 0;
    ctx.sheikHints          = (GanonHints && GanonsTrialsCount.Value<u8>() > 0 &&
                      (!StartingLightArrows || (ShuffleMasterSword && !StartingMasterSword)));
    ctx.dampeHint           = DampeHint ? 1 : 0;
    ctx.skulltulaHints      = SkulltulaHints ? 1 : 0;
    ctx.fishingHints        = FishingHints ? 1 : 0;
    ctx.compassesShowReward = CompassesShowReward.Value<u8>();
    ctx.compassesShowWotH   = CompassesShowWotH.Value<u8>();
    ctx.mapsShowDungeonMode = MapsShowDungeonMode.Value<u8>();
    ctx.damageMultiplier    = DamageMultiplier.Value<u8>();
    ctx.permadeath          = (Permadeath) ? 1 : 0;
    ctx.gloomMode           = GloomMode.Value<u8>();
    ctx.startingTime        = StartingTime.Value<u8>();
    ctx.chestAnimations     = (ChestAnimations) ? 1 : 0;
    ctx.chestAppearance     = ChestAppearance.Value<u8>();
    ctx.chestAgony          = (ChestAgony) ? 1 : 0;
    ctx.generateSpoilerLog  = (GenerateSpoilerLog) ? 1 : 0;
    ctx.ingameSpoilers      = (IngameSpoilers) ? 1 : 0;
    ctx.menuOpeningButton   = MenuOpeningButton.Value<u8>();
    ctx.arrowSwitchButton   = ArrowSwitchButton.Value<u8>();
    ctx.randomTrapDmg       = RandomTrapDmg.Value<u8>();
    ctx.fireTrap            = (FireTrap) ? 1 : 0;
    ctx.antiFairyTrap       = (AntiFairyTrap) ? 1 : 0;
    ctx.curseTraps          = (CurseTraps) ? 1 : 0;
    ctx.screenTraps         = (ScreenTraps) ? 1 : 0;
    ctx.extraArrowEffects   = (ExtraArrowEffects) ? 1 : 0;
    ctx.hyperBosses         = (HyperBosses) ? 1 : 0;
    ctx.hyperMiddleBosses   = (HyperMiddleBosses) ? 1 : 0;
    ctx.hyperEnemies        = (HyperEnemies) ? 1 : 0;
    ctx.freeCamera          = (FreeCamera) ? 1 : 0;
    ctx.randomGsLocations   = (RandomGsLocations) ? 1 : 0;

    ctx.faroresWindAnywhere  = (FaroresWindAnywhere) ? 1 : 0;
    ctx.stickAsAdult         = (StickAsAdult) ? 1 : 0;
    ctx.boomerangAsAdult     = (BoomerangAsAdult) ? 1 : 0;
    ctx.hammerAsChild        = (HammerAsChild) ? 1 : 0;
    ctx.slingshotAsAdult     = (SlingshotAsAdult) ? 1 : 0;
    ctx.bowAsChild           = (BowAsChild) ? 1 : 0;
    ctx.hookshotAsChild      = (HookshotAsChild) ? 1 : 0;
    ctx.ironbootsAsChild     = (IronBootsAsChild) ? 1 : 0;
    ctx.hoverbootsAsChild    = (HoverBootsAsChild) ? 1 : 0;
    ctx.masksAsAdult         = (MasksAsAdult) ? 1 : 0;
    ctx.kokiriSwordAsAdult   = (KokiriSwordAsAdult) ? 1 : 0;
    ctx.masterSwordAsChild   = (MasterSwordAsChild) ? 1 : 0;
    ctx.biggoronSwordAsChild = (BiggoronSwordAsChild) ? 1 : 0;
    ctx.dekuShieldAsAdult    = (DekuShieldAsAdult) ? 1 : 0;
    ctx.mirrorShieldAsChild  = (MirrorShieldAsChild) ? 1 : 0;
    ctx.goronTunicAsChild    = (GoronTunicAsChild) ? 1 : 0;
    ctx.zoraTunicAsChild     = (ZoraTunicAsChild) ? 1 : 0;
    ctx.restoreISG           = (RestoreISG) ? 1 : 0;
    ctx.gkDurability         = GkDurability.Value<u8>();
    ctx.retroAmmo            = (RetroAmmo) ? 1 : 0;

    ctx.itemPoolValue         = ItemPoolValue.Value<u8>();
    ctx.iceTrapValue          = IceTrapValue.Value<u8>();
    ctx.progressiveGoronSword = (ProgressiveGoronSword) ? 1 : 0;

    ctx.mp_Enabled        = MP_Enabled.Value<u8>();
    ctx.mp_SharedProgress = (MP_SharedProgress) ? 1 : 0;
    ctx.mp_SyncId         = MP_SyncId.Value<u8>() + 1;
    ctx.mp_SharedAmmo     = (MP_SharedAmmo) ? 1 : 0;
    ctx.mp_SharedHealth   = (MP_SharedHealth) ? 1 : 0;
    ctx.mp_SharedRupees   = (MP_SharedRupees) ? 1 : 0;

    ctx.zTargeting         = ZTargeting.Value<u8>();
    ctx.cameraControl      = CameraControl.Value<u8>();
    ctx.motionControl      = MotionControl.Value<u8>();
    ctx.playMusic          = TogglePlayMusic.Value<u8>();
    ctx.playSFX            = TogglePlaySFX.Value<u8>();
    ctx.naviNotifications  = NaviNotifications.Value<u8>();
    ctx.ignoreMaskReaction = IgnoreMaskReaction.Value<u8>();
    ctx.freeCamControl     = FreeCamControl.Value<u8>();

    ctx.customTunicColors           = (CustomTunicColors) ? 1 : 0;
    ctx.rainbowChildTunic           = (ChildTunicColor.Value<u8>() == RAINBOW_TUNIC) ? 1 : 0;
    ctx.rainbowKokiriTunic          = (KokiriTunicColor.Value<u8>() == RAINBOW_TUNIC) ? 1 : 0;
    ctx.rainbowGoronTunic           = (GoronTunicColor.Value<u8>() == RAINBOW_TUNIC) ? 1 : 0;
    ctx.rainbowZoraTunic            = (ZoraTunicColor.Value<u8>() == RAINBOW_TUNIC) ? 1 : 0;
    ctx.customNaviColors            = (CustomNaviColors) ? 1 : 0;
    ctx.rainbowIdleNaviInnerColor   = (IdleNaviInnerColor.Value<u8>() == RAINBOW_NAVI) ? 1 : 0;
    ctx.rainbowNPCNaviInnerColor    = (NPCNaviInnerColor.Value<u8>() == RAINBOW_NAVI) ? 1 : 0;
    ctx.rainbowEnemyNaviInnerColor  = (EnemyNaviInnerColor.Value<u8>() == RAINBOW_NAVI) ? 1 : 0;
    ctx.rainbowPropNaviInnerColor   = (PropNaviInnerColor.Value<u8>() == RAINBOW_NAVI) ? 1 : 0;
    ctx.rainbowIdleNaviOuterColor   = (IdleNaviOuterColor.Value<u8>() == RAINBOW_NAVI) ? 1 : 0;
    ctx.rainbowNPCNaviOuterColor    = (NPCNaviOuterColor.Value<u8>() == RAINBOW_NAVI) ? 1 : 0;
    ctx.rainbowEnemyNaviOuterColor  = (EnemyNaviOuterColor.Value<u8>() == RAINBOW_NAVI) ? 1 : 0;
    ctx.rainbowPropNaviOuterColor   = (PropNaviOuterColor.Value<u8>() == RAINBOW_NAVI) ? 1 : 0;
    ctx.customTrailEffects          = (CustomTrailEffects) ? 1 : 0;
    ctx.rainbowSwordTrailInnerColor = (SwordTrailInnerColor.Value<u8>() == RAINBOW_TRAIL) ? 1 : 0;
    ctx.rainbowSwordTrailOuterColor = (SwordTrailOuterColor.Value<u8>() == RAINBOW_TRAIL) ? 1 : 0;
    ctx.boomerangTrailColor.r       = finalBoomerangColor.r;
    ctx.boomerangTrailColor.g       = finalBoomerangColor.g;
    ctx.boomerangTrailColor.b       = finalBoomerangColor.b;
    ctx.boomerangTrailColor.a       = finalBoomerangColor.a;
    ctx.boomerangTrailColorMode     = boomerangTrailColorMode;
    ctx.boomerangTrailDuration      = BoomerangTrailDuration.Value<u8>();
    ctx.rainbowChuTrailInnerColor   = (BombchuTrailInnerColor.Value<u8>() == RAINBOW_TRAIL) ? 1 : 0;
    ctx.rainbowChuTrailOuterColor   = (BombchuTrailOuterColor.Value<u8>() == RAINBOW_TRAIL) ? 1 : 0;
    ctx.bombchuTrailDuration        = BombchuTrailDuration.Value<u8>();
    ctx.mirrorWorld                 = MirrorWorld.Value<u8>();
    ctx.coloredKeys                 = (ColoredKeys) ? 1 : 0;
    ctx.coloredBossKeys             = (ColoredBossKeys) ? 1 : 0;
    ctx.soullessEnemiesLook         = SoullessEnemiesLook.Value<u8>();
    ctx.shuffleSFX                  = ShuffleSFX.Value<u8>();
    ctx.shuffleSFXFootsteps         = (ShuffleSFXFootsteps) ? 1 : 0;
    ctx.shuffleSFXLinkVoice         = (ShuffleSFXLinkVoice) ? 1 : 0;
    ctx.shuffleSFXCategorically     = (ShuffleSFXCategorically) ? 1 : 0;

    ctx.linksPocketRewardBitMask = LinksPocketRewardBitMask;

    ctx.dekuTreeDungeonMode              = DekuTree.IsMQ() ? 1 : 0;
    ctx.dodongosCavernDungeonMode        = DodongosCavern.IsMQ() ? 1 : 0;
    ctx.jabuJabusBellyDungeonMode        = JabuJabusBelly.IsMQ() ? 1 : 0;
    ctx.forestTempleDungeonMode          = ForestTemple.IsMQ() ? 1 : 0;
    ctx.fireTempleDungeonMode            = FireTemple.IsMQ() ? 1 : 0;
    ctx.waterTempleDungeonMode           = WaterTemple.IsMQ() ? 1 : 0;
    ctx.spiritTempleDungeonMode          = SpiritTemple.IsMQ() ? 1 : 0;
    ctx.shadowTempleDungeonMode          = ShadowTemple.IsMQ() ? 1 : 0;
    ctx.bottomOfTheWellDungeonMode       = BottomOfTheWell.IsMQ() ? 1 : 0;
    ctx.iceCavernDungeonMode             = IceCavern.IsMQ() ? 1 : 0;
    ctx.ganonsCastleDungeonMode          = GanonsCastle.IsMQ() ? 1 : 0;
    ctx.gerudoTrainingGroundsDungeonMode = GerudoTrainingGrounds.IsMQ() ? 1 : 0;

    for (u8 i = 0; i < sizeof(ctx.dungeonModesKnown); ++i) {
        ctx.dungeonModesKnown[i] = DungeonModesKnown[i];
    }

    ctx.forestTrialSkip = (ForestTrial.IsSkipped()) ? 1 : 0;
    ctx.fireTrialSkip   = (FireTrial.IsSkipped()) ? 1 : 0;
    ctx.waterTrialSkip  = (WaterTrial.IsSkipped()) ? 1 : 0;
    ctx.spiritTrialSkip = (SpiritTrial.IsSkipped()) ? 1 : 0;
    ctx.shadowTrialSkip = (ShadowTrial.IsSkipped()) ? 1 : 0;
    ctx.lightTrialSkip  = (LightTrial.IsSkipped()) ? 1 : 0;

    // Starting Inventory
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
    ctx.startingChildTrade    = StartingChildTrade.Value<u8>();
    ctx.startingOcarina       = StartingOcarina.Value<u8>();
    ctx.startingKokiriSword   = StartingKokiriSword.Value<u8>();
    ctx.startingBiggoronSword = StartingBiggoronSword.Value<u8>();
    ctx.startingHearts        = StartingHearts.Value<u8>();
    ctx.startingMagicMeter    = StartingMagicMeter.Value<u8>();
    ctx.startingDoubleDefense = StartingDoubleDefense.Value<u8>();

    // Starting Quest Items
    ctx.startingQuestItems |= StartingMinuetOfForest.Value<u8>() << 6;
    ctx.startingQuestItems |= StartingBoleroOfFire.Value<u8>() << 7;
    ctx.startingQuestItems |= StartingSerenadeOfWater.Value<u8>() << 8;
    ctx.startingQuestItems |= StartingRequiemOfSpirit.Value<u8>() << 9;
    ctx.startingQuestItems |= StartingNocturneOfShadow.Value<u8>() << 10;
    ctx.startingQuestItems |= StartingPreludeOfLight.Value<u8>() << 11;
    ctx.startingQuestItems |= StartingZeldasLullaby.Value<u8>() << 12;
    ctx.startingQuestItems |= StartingEponasSong.Value<u8>() << 13;
    ctx.startingQuestItems |= StartingSariasSong.Value<u8>() << 14;
    ctx.startingQuestItems |= StartingSunsSong.Value<u8>() << 15;
    ctx.startingQuestItems |= StartingSongOfTime.Value<u8>() << 16;
    ctx.startingQuestItems |= StartingSongOfStorms.Value<u8>() << 17;
    ctx.startingQuestItems |= StartingShardOfAgony.Value<u8>() << 21;
    ctx.startingDungeonReward |= StartingKokiriEmerald.Value<u8>() << 18;
    ctx.startingDungeonReward |= StartingGoronRuby.Value<u8>() << 19;
    ctx.startingDungeonReward |= StartingZoraSapphire.Value<u8>() << 20;
    ctx.startingDungeonReward |= StartingLightMedallion.Value<u8>() << 5;
    ctx.startingDungeonReward |= StartingForestMedallion.Value<u8>() << 0;
    ctx.startingDungeonReward |= StartingFireMedallion.Value<u8>() << 1;
    ctx.startingDungeonReward |= StartingWaterMedallion.Value<u8>() << 2;
    ctx.startingDungeonReward |= StartingSpiritMedallion.Value<u8>() << 3;
    ctx.startingDungeonReward |= StartingShadowMedallion.Value<u8>() << 4;

    // Starting enemy souls
    for (u32 i = 0; i < SOUL_MAX; i++) {
        u32 soulBitIdx = SoulMenuNames[i].soulId;
        Option* opt    = startingEnemySoulsOptions.at(i);
        ctx.startingEnemySouls[soulBitIdx >> 3] |= opt->Value<u8>() << (soulBitIdx & 0b111);
    }

    ctx.startingOcarinaButtons |= StartingOcarinaButtonL.Value<u8>() << 0;
    ctx.startingOcarinaButtons |= StartingOcarinaButtonR.Value<u8>() << 1;
    ctx.startingOcarinaButtons |= StartingOcarinaButtonX.Value<u8>() << 2;
    ctx.startingOcarinaButtons |= StartingOcarinaButtonY.Value<u8>() << 3;
    ctx.startingOcarinaButtons |= StartingOcarinaButtonA.Value<u8>() << 4;

    ctx.startingTokens = StartingSkulltulaToken.Value<u8>();

    // Give the Gerudo Token if Gerudo Fortress is Open and Shuffle Gerudo Card is off
    if (GerudoFortress.Is(GERUDOFORTRESS_OPEN) && !ShuffleGerudoToken) {
        ctx.startingQuestItems |= 0x00400000;
    }

    // Starting Equipment
    ctx.startingEquipment |= StartingKokiriSword.Value<u8>();
    ctx.startingEquipment |= StartingMasterSword.Value<u8>() << 1;
    ctx.startingEquipment |= (StartingBiggoronSword.Value<u8>() ? 1 : 0) << 2;
    ctx.startingEquipment |= StartingDekuShield.Value<u8>() << 4;
    ctx.startingEquipment |= StartingHylianShield.Value<u8>() << 5;
    ctx.startingEquipment |= StartingMirrorShield.Value<u8>() << 6;
    ctx.startingEquipment |= StartingGoronTunic.Value<u8>() << 9;
    ctx.startingEquipment |= StartingZoraTunic.Value<u8>() << 10;
    ctx.startingEquipment |= StartingIronBoots.Value<u8>() << 13;
    ctx.startingEquipment |= StartingHoverBoots.Value<u8>() << 14;

    // Starting Upgrades
    ctx.startingUpgrades |= StartingStrength.Value<u8>() << 6;
    ctx.startingUpgrades |= StartingScale.Value<u8>() << 9;
    ctx.startingUpgrades |= StartingWallet.Value<u8>() << 12;

    return ctx;
}

// One-time initialization
void InitSettings() {
    enemizerListOptions = mapArrayToOptions(Enemizer::enemyTypes, [](Enemizer::EnemyType enemy) {
        bool hidden = enemy.actorId == 0 || enemy.validLocTypes.empty();
        return Option::U8(enemy.name, { "Randomized", "Vanilla", "Removed" },
                          {
                              enemyRandomizedDesc,
                              enemyVanillaDesc,
                              enemyRemovedDesc,
                          },
                          OptionCategory::Setting, 0, hidden);
    });
    enemizerListMenu    = Menu::SubMenu("Enemy List", &enemizerListOptions, "", false);

    // Create Location Exclude settings
    AddExcludedOptions();

    SetDefaultSettings();
}

// Set default settings for all settings
void SetDefaultSettings() {
    std::function<void(std::vector<Menu*>*)> setAllOptionsToDefault = [&](std::vector<Menu*>* menuPtr) {
        for (auto menu : *menuPtr) {
            if (menu->mode == SUB_MENU) {
                setAllOptionsToDefault(menu->itemsList);
            } else if (menu->mode == OPTION_MENU) {
                for (auto option : *menu->settingsList) {
                    if (option->IsCategory(OptionCategory::Cosmetic)) {
                        continue;
                    }
                    option->SetToDefault();
                }
            }
        }
    };

    setAllOptionsToDefault(&mainMenu);

    // Don't let users exclude these locations
    // TODO: Make sure the defaults are set appropriately for these?
    Location(MARKET_BOMBCHU_BOWLING_BOMBCHUS)->GetExcludedOption()->Hide();
    Location(GANON)->GetExcludedOption()->Hide();

    ResolveExcludedLocationConflicts();
    for (Menu* menu : Settings::GetAllOptionMenus()) {
        menu->ResetMenuIndex();
    }
}

// Include and Lock the desired locations
static void IncludeAndHide(std::vector<LocationKey> locations) {
    for (LocationKey loc : locations) {
        Location(loc)->GetExcludedOption()->SetSelectedIndex(INCLUDE);
        Location(loc)->GetExcludedOption()->Hide();
    }
}

// Unlock the desired locations
static void Unhide(std::vector<LocationKey> locations) {
    for (LocationKey loc : locations) {
        Location(loc)->GetExcludedOption()->Unhide();
    }
}

// Used for toggle options, enables/disables all the options between the 2 given
void ToggleSet(std::vector<Option*> optionsList, Option* toggleOption, Option* firstOptionInSet,
               Option* lastOptionInSet) {
    u32 i;
    for (i = 0; i < optionsList.size(); i++) {
        if (optionsList[i] == firstOptionInSet)
            break;
    }
    for (; i < optionsList.size(); i++) {
        switch (toggleOption->Value<u8>()) {
            case 0:
                optionsList[i]->Hide();
                optionsList[i]->SetSelectedIndex(0);
                break;
            case 1:
                optionsList[i]->Hide();
                optionsList[i]->SetSelectedIndex(1);
                break;
            case 2:
                optionsList[i]->Unhide();
                break;
        }
        if (optionsList[i] == lastOptionInSet)
            return;
    }
}

// This function will hide certain locations from the Excluded Locations
// menu if the player's current settings would require non-junk to be placed
// at those locations. Excluded locations will have junk placed at them.
void ResolveExcludedLocationConflicts() {

    std::vector<LocationKey> shopLocations = GetLocations(everyPossibleLocation, Category::cShop);
    // For now, just always hide shop locations, as not sure how to handle hiding them-
    // 1-4 should always be hidden, while the others should be settings dependent, but random shopsanity makes that more
    // complicated... Excluded shop locations are also wonky
    IncludeAndHide(shopLocations);

    // Force include song locations
    std::vector<LocationKey> songLocations      = GetLocations(everyPossibleLocation, Category::cSong);
    std::vector<LocationKey> songDungeonRewards = GetLocations(everyPossibleLocation, Category::cSongDungeonReward);

    // Unhide all song locations, then lock necessary ones
    Unhide(songLocations);
    Unhide(songDungeonRewards);

    if (ShuffleSongs.Is(SONGSHUFFLE_SONG_LOCATIONS)) {
        IncludeAndHide(songLocations);
    } else if (ShuffleSongs.Is(SONGSHUFFLE_DUNGEON_REWARDS)) {
        IncludeAndHide(songDungeonRewards);
    }

    // Force Include Dungeon Rewards if set to End of Dungeons
    std::vector<LocationKey> rewardsLocations = GetLocations(everyPossibleLocation, Category::cDungeonReward);
    if (ShuffleRewards.IsNot(REWARDSHUFFLE_END_OF_DUNGEON)) {
        Unhide(rewardsLocations);
    } else {
        IncludeAndHide(rewardsLocations);
    }

    // Only show Shopsanity prices setting if Shopsanity is enabled
    if (!Shopsanity.Is(SHOPSANITY_OFF) && !Shopsanity.Is(SHOPSANITY_ZERO)) {
        ShopsanityPrices.Unhide();
    } else {
        ShopsanityPrices.Hide();
    }

    // Force Include Vanilla Skulltula locations
    std::vector<LocationKey> skulltulaLocations = GetLocations(everyPossibleLocation, Category::cSkulltula);
    Unhide(skulltulaLocations);
    if (Tokensanity.IsNot(TOKENSANITY_ALL_TOKENS)) {
        if (Tokensanity.Is(TOKENSANITY_OVERWORLD)) {
            // filter overworld skulls so we're just left with dungeons
            FilterAndEraseFromPool(skulltulaLocations,
                                   [](const LocationKey loc) { return Location(loc)->GetScene() >= 0x0A; });
        } else if (Tokensanity.Is(TOKENSANITY_DUNGEONS)) {
            // filter dungeon skulls so we're just left with overworld
            FilterAndEraseFromPool(skulltulaLocations,
                                   [](const LocationKey loc) { return Location(loc)->GetScene() < 0x0A; });
        }
        IncludeAndHide(skulltulaLocations);
    }

    // Force Include scrubs if Scrubsanity is Off
    std::vector<LocationKey> scrubLocations =
        GetLocations(everyPossibleLocation, Category::cDekuScrub, Category::cDekuScrubUpgrades);
    if (Scrubsanity.Is(OFF)) {
        IncludeAndHide(scrubLocations);
    } else {
        Unhide(scrubLocations);
    }

    // Force include Cows if Shuffle Cows is Off
    std::vector<LocationKey> cowLocations = GetLocations(everyPossibleLocation, Category::cCow);
    if (ShuffleCows) {
        Unhide(cowLocations);
    } else {
        IncludeAndHide(cowLocations);
    }

    // Force include the Kokiri Sword Chest if Shuffle Kokiri Sword is Off
    if (ShuffleKokiriSword) {
        Unhide({ KF_KOKIRI_SWORD_CHEST });
    } else {
        IncludeAndHide({ KF_KOKIRI_SWORD_CHEST });
    }

    // Force include the ocarina locations if Shuffle Ocarinas is Off
    std::vector<LocationKey> ocarinaLocations = { LW_GIFT_FROM_SARIA, HF_OCARINA_OF_TIME_ITEM };
    if (ShuffleOcarinas) {
        Unhide(ocarinaLocations);
    } else {
        IncludeAndHide(ocarinaLocations);
    }

    // Force include Malon if Shuffle Weird Egg is Off
    if (ShuffleWeirdEgg) {
        Unhide({ HC_MALON_EGG });
    } else {
        IncludeAndHide({ HC_MALON_EGG });
    }

    // Force include Zelda if Shuffle Zelda's Letter is Off
    if (ShuffleZeldasLetter) {
        Unhide({ HC_ZELDAS_LETTER });
    } else {
        IncludeAndHide({ HC_ZELDAS_LETTER });
    }

    // Force include Gerudo Token Location if it's not shuffled
    if (!ShuffleGerudoToken || GerudoFortress.Is(GERUDOFORTRESS_OPEN)) {
        IncludeAndHide({ GF_GERUDO_TOKEN });
    } else {
        Unhide({ GF_GERUDO_TOKEN });
    }

    // Force include Magic Bean salesman if Shuffle Magic Beans is off
    if (ShuffleMagicBeans) {
        Unhide({ ZR_MAGIC_BEAN_SALESMAN });
    } else {
        IncludeAndHide({ ZR_MAGIC_BEAN_SALESMAN });
    }

    // Force include Medigoron, Granny and Carpet salesman if Shuffle Merchants is off
    if (ShuffleMerchants.IsNot(SHUFFLEMERCHANTS_OFF)) {
        Unhide({ GC_MEDIGORON });
        Unhide({ KAK_GRANNYS_SHOP });
        Unhide({ WASTELAND_BOMBCHU_SALESMAN });
    } else {
        IncludeAndHide({ GC_MEDIGORON });
        IncludeAndHide({ KAK_GRANNYS_SHOP });
        IncludeAndHide({ WASTELAND_BOMBCHU_SALESMAN });
    }

    // Force include frog song rupees if they're not shuffled
    if (ShuffleFrogSongRupees) {
        Unhide({ ZR_FROGS_ZELDAS_LULLABY });
        Unhide({ ZR_FROGS_EPONAS_SONG });
        Unhide({ ZR_FROGS_SARIAS_SONG });
        Unhide({ ZR_FROGS_SUNS_SONG });
        Unhide({ ZR_FROGS_SONG_OF_TIME });
    } else {
        IncludeAndHide({ ZR_FROGS_ZELDAS_LULLABY });
        IncludeAndHide({ ZR_FROGS_EPONAS_SONG });
        IncludeAndHide({ ZR_FROGS_SARIAS_SONG });
        IncludeAndHide({ ZR_FROGS_SUNS_SONG });
        IncludeAndHide({ ZR_FROGS_SONG_OF_TIME });
    }

    // Force include adult trade quest if Shuffle Adult Trade Quest is off
    std::vector<LocationKey> adultTradeLocations = { KAK_TRADE_POCKET_CUCCO, LW_TRADE_COJIRO, KAK_TRADE_ODD_MUSHROOM,
                                                     LW_TRADE_ODD_POULTICE,  GV_TRADE_SAW,    DMT_TRADE_BROKEN_SWORD,
                                                     ZD_TRADE_PRESCRIPTION,  LH_TRADE_FROG,   DMT_TRADE_EYEDROPS };
    if (ShuffleAdultTradeQuest) {
        Unhide(adultTradeLocations);
    } else {
        IncludeAndHide(adultTradeLocations);
    }

    // Force include Chest Game keys if Shuffle Chest Minigame is off
    std::vector<LocationKey> ChestMinigameLocations = {
        MARKET_TREASURE_CHEST_GAME_ITEM_1, MARKET_TREASURE_CHEST_GAME_ITEM_2, MARKET_TREASURE_CHEST_GAME_ITEM_3,
        MARKET_TREASURE_CHEST_GAME_ITEM_4, MARKET_TREASURE_CHEST_GAME_ITEM_5
    };
    if (ShuffleChestMinigame) {
        Unhide(ChestMinigameLocations);
    } else {
        IncludeAndHide(ChestMinigameLocations);
    }

    // Force include Map and Compass Chests when Vanilla
    std::vector<LocationKey> mapChests     = GetLocations(everyPossibleLocation, Category::cVanillaMap);
    std::vector<LocationKey> compassChests = GetLocations(everyPossibleLocation, Category::cVanillaCompass);
    if (MapsAndCompasses.Is(MAPSANDCOMPASSES_VANILLA)) {
        IncludeAndHide(mapChests);
        IncludeAndHide(compassChests);
    } else {
        Unhide(mapChests);
        Unhide(compassChests);
    }

    // Force include Vanilla Small Key Locations (except gerudo Fortress) on Vanilla Keys
    std::vector<LocationKey> smallKeyChests = GetLocations(everyPossibleLocation, Category::cVanillaSmallKey);
    if (Keysanity.Is(KEYSANITY_VANILLA)) {
        IncludeAndHide(smallKeyChests);
    } else {
        Unhide(smallKeyChests);
    }

    // Force include Gerudo Fortress carpenter fights if GF Small Keys are Vanilla
    std::vector<LocationKey> vanillaGFKeyLocations = GetLocations(everyPossibleLocation, Category::cVanillaGFSmallKey);
    if (GerudoKeys.Is(GERUDOKEYS_VANILLA)) {
        IncludeAndHide(vanillaGFKeyLocations);
    } else {
        Unhide(vanillaGFKeyLocations);
    }

    // Force include Boss Key Chests if Boss Keys are Vanilla
    std::vector<LocationKey> bossKeyChests = GetLocations(everyPossibleLocation, Category::cVanillaBossKey);
    if (BossKeysanity.Is(BOSSKEYSANITY_VANILLA)) {
        IncludeAndHide(bossKeyChests);
    } else {
        Unhide(bossKeyChests);
    }

    // Force include Ganons Boss Key Chest if ganons boss key has to be there
    if (GanonsBossKey.Is(GANONSBOSSKEY_VANILLA)) {
        IncludeAndHide({ GANONS_TOWER_BOSS_KEY_CHEST });
    } else {
        Unhide({ GANONS_TOWER_BOSS_KEY_CHEST });
    }

    // Force include Light Arrow item if ganons boss key has to be there
    if (GanonsBossKey.Value<u8>() >= GANONSBOSSKEY_LACS_VANILLA) {
        IncludeAndHide({ TOT_LIGHT_ARROWS_CUTSCENE });
    } else {
        Unhide({ TOT_LIGHT_ARROWS_CUTSCENE });
    }
}

u8 DungeonsOfType(u8 type) {
    u8 count = 0;

    for (Option* option : dungeonOptions) {
        count += (option->Value<u8>() == type) ? 1 : 0;
    }

    return count;
}

// Hide certain settings if they aren't relevant or Lock settings if they
// can't be changed due to another setting that was chosen. (i.e. Closed Forest
// will force Starting Age to Child).
void ForceChange(u32 kDown, Option* currentSetting) {

    // If Zora's Fountain is open, hide and un-select Ruto's Letter. If not open, hide and un-select bottle 4 instead
    if (ZorasFountain.Is(ZORASFOUNTAIN_OPEN)) {
        startingItemsOptions[23]->Unhide();
        startingItemsOptions[24]->Hide();
        startingItemsOptions[24]->SetSelectedIndex(0);
    } else {
        startingItemsOptions[24]->Unhide();
        startingItemsOptions[23]->Hide();
        startingItemsOptions[23]->SetSelectedIndex(0);
    }

    // Only hide the options for now, select them later in UpdateSettings()
    RandomizeAllSettings();

    // Only go through options if all settings are not randomized
    if (!RandomizeOpen) {
        // Adult is not compatible with Closed Forest
        // Adult is also not compatible with Intended DoT + Unshuffled Ocarinas unless the player starts with an ocarina
        if (OpenForest.Is(OPENFOREST_CLOSED) ||
            (OpenDoorOfTime.Is(OPENDOOROFTIME_INTENDED) && !ShuffleOcarinas && StartingOcarina.Is(OFF))) {
            StartingAge.SetSelectedIndex(AGE_CHILD);
            StartingAge.Lock();
        } else {
            StartingAge.Unlock();
        }

        // Only show stone count option if Stones is selected
        if (Bridge.Is(RAINBOWBRIDGE_STONES)) {
            BridgeStoneCount.Unhide();
        } else {
            BridgeStoneCount.SetSelectedIndex(3);
            BridgeStoneCount.Hide();
        }

        // Only show medallion count option if Medallions is selected
        if (Bridge.Is(RAINBOWBRIDGE_MEDALLIONS)) {
            BridgeMedallionCount.Unhide();
        } else {
            BridgeMedallionCount.Hide();
            BridgeMedallionCount.SetSelectedIndex(6);
        }

        // Only show reward count option if Rewards is selected
        if (Bridge.Is(RAINBOWBRIDGE_REWARDS)) {
            BridgeRewardCount.Unhide();
        } else {
            BridgeRewardCount.SetSelectedIndex(9);
            BridgeRewardCount.Hide();
        }

        // Only show reward count option if Rewards is selected
        if (Bridge.Is(RAINBOWBRIDGE_DUNGEONS)) {
            BridgeDungeonCount.Unhide();
        } else {
            BridgeDungeonCount.SetSelectedIndex(8);
            BridgeDungeonCount.Hide();
        }

        // Only show token count option if Tokens is selected
        if (Bridge.Is(RAINBOWBRIDGE_TOKENS)) {
            BridgeTokenCount.Unhide();
        } else {
            BridgeTokenCount.SetSelectedIndex(100);
            BridgeTokenCount.Hide();
        }

        // Only show heart count option if Hearts is selected
        if (Bridge.Is(RAINBOWBRIDGE_HEARTS)) {
            BridgeHeartCount.Unhide();
        } else {
            BridgeHeartCount.SetSelectedIndex(20);
            BridgeHeartCount.Hide();
        }

        // Only show Trial Count option if Random Trial Count is off
        if (RandomGanonsTrials) {
            GanonsTrialsCount.SetSelectedIndex(6);
            GanonsTrialsCount.Hide();
        } else {
            GanonsTrialsCount.Unhide();
        }
    }

    // Only show Manual Zora Speed if it's set to Custom
    if (KingZoraSpeed.Is(KINGZORASPEED_CUSTOM)) {
        ExactZoraSpeed.Unhide();
    } else {
        ExactZoraSpeed.Hide();
    }

    // Only go through options if all settings are not randomized
    if (!RandomizeWorld) {
        // Show Shuffle options when Shuffle Entrances is On
        if (ShuffleEntrances) {
            ShuffleDungeonEntrances.Unhide();
            ShuffleBossEntrances.Unhide();
            ShuffleOverworldEntrances.Unhide();
            ShuffleInteriorEntrances.Unhide();
            ShuffleGrottoEntrances.Unhide();
            ShuffleOwlDrops.Unhide();
            ShuffleWarpSongs.Unhide();
            ShuffleOverworldSpawns.Unhide();
            MixedEntrancePools.Unhide();
            DecoupleEntrances.Unhide();
        } else {
            ShuffleDungeonEntrances.SetSelectedIndex(SHUFFLEDUNGEONS_OFF);
            ShuffleDungeonEntrances.Hide();
            ShuffleBossEntrances.SetSelectedIndex(SHUFFLEBOSSES_OFF);
            ShuffleBossEntrances.Hide();
            ShuffleOverworldEntrances.SetSelectedIndex(OFF);
            ShuffleOverworldEntrances.Hide();
            ShuffleInteriorEntrances.SetSelectedIndex(SHUFFLEINTERIORS_OFF);
            ShuffleInteriorEntrances.Hide();
            ShuffleGrottoEntrances.SetSelectedIndex(OFF);
            ShuffleGrottoEntrances.Hide();
            ShuffleOwlDrops.SetSelectedIndex(OFF);
            ShuffleOwlDrops.Hide();
            ShuffleWarpSongs.SetSelectedIndex(OFF);
            ShuffleWarpSongs.Hide();
            ShuffleOverworldSpawns.SetSelectedIndex(OFF);
            ShuffleOverworldSpawns.Hide();
            MixedEntrancePools.SetSelectedIndex(OFF);
            MixedEntrancePools.Hide();
            DecoupleEntrances.SetSelectedIndex(OFF);
            DecoupleEntrances.Hide();
        }

        // Only show the options for mixing each pool if they're already being shuffled
        if (MixedEntrancePools) {
            if (ShuffleDungeonEntrances) {
                MixDungeons.Unhide();
            } else {
                MixDungeons.Hide();
                MixDungeons.SetSelectedIndex(OFF);
            }

            if (ShuffleOverworldEntrances) {
                MixOverworld.Unhide();
            } else {
                MixOverworld.Hide();
                MixOverworld.SetSelectedIndex(OFF);
            }

            if (ShuffleInteriorEntrances.IsNot(OFF)) {
                MixInteriors.Unhide();
            } else {
                MixInteriors.Hide();
                MixInteriors.SetSelectedIndex(OFF);
            }

            if (ShuffleGrottoEntrances) {
                MixGrottos.Unhide();
            } else {
                MixGrottos.Hide();
                MixGrottos.SetSelectedIndex(OFF);
            }
        } else {
            MixDungeons.Hide();
            MixDungeons.SetSelectedIndex(OFF);
            MixOverworld.Hide();
            MixOverworld.SetSelectedIndex(OFF);
            MixInteriors.Hide();
            MixInteriors.SetSelectedIndex(OFF);
            MixGrottos.Hide();
            MixGrottos.SetSelectedIndex(OFF);
        }

        if (TriforceHunt) {
            TriforcePiecesTotal.Unhide();
            TriforcePiecesRequired.Unhide();
        } else {
            TriforcePiecesTotal.Hide();
            TriforcePiecesRequired.Hide();
        }

        if (Enemizer) {
            EnemizerListToggle.Unhide();
        } else {
            EnemizerListToggle.Hide();
        }
    }

    if (EnemizerListToggle) {
        // Open Enemy List and reset the toggle option.
        GoToMenu(&enemizerListMenu);
        EnemizerListToggle.SetToDefault();
    }

    // If Triforce Hunt is enabled, lock Ganon BK setting to the "Triforce" option.
    // Otherwise, make that option unselectable by switching to the next one over.
    if (TriforceHunt) {
        GanonsBossKey.SetSelectedIndex(GANONSBOSSKEY_TRIFORCE);
        GanonsBossKey.Lock();
    } else {
        GanonsBossKey.Unlock();
        if (GanonsBossKey.Is(GANONSBOSSKEY_TRIFORCE)) {
            if (currentSetting == &GanonsBossKey) {
                GanonsBossKey.ScrollOptionIndex(kDown);
            } else {
                GanonsBossKey.SetSelectedIndex(GANONSBOSSKEY_START_WITH);
            }
            GanonsBossKey.SetVariable();
        }
    }

    // Make sure the required pieces are less than the total pieces
    if (TriforcePiecesRequired.Value<u8>() > TriforcePiecesTotal.Value<u8>()) {
        if (currentSetting == &TriforcePiecesTotal) {
            TriforcePiecesRequired.SetSelectedIndex(currentSetting->GetSelectedOptionIndex());
        } else if (currentSetting == &TriforcePiecesRequired) {
            TriforcePiecesTotal.SetSelectedIndex(currentSetting->GetSelectedOptionIndex());
        } else { // randomized settings
            // invert amounts
            u8 temp = TriforcePiecesRequired.GetSelectedOptionIndex();
            TriforcePiecesRequired.SetSelectedIndex(TriforcePiecesTotal.GetSelectedOptionIndex());
            TriforcePiecesTotal.SetSelectedIndex(temp);
        }
    }

    if (SetDungeonTypes) {
        for (Option* option : dungeonOptions) {
            option->Unhide();
        }

        // Restrict MQDungeonCount options so they can't be less than the number of dungeons set to MQ and can't be more
        // than the number of dungeons set to MQ plus the number of dungeons set to random
        u8 MQ = DungeonsOfType(1), R = DungeonsOfType(2);
        if (MQDungeonCount.Value<u8>() < MQ) {
            MQDungeonCount.SetSelectedIndex((currentSetting == &MQDungeonCount && (kDown & KEY_LEFT)) ? 13 : MQ);
        } else if (MQDungeonCount.Value<u8>() != 13 && MQDungeonCount.Value<u8>() > MQ + R) {
            MQDungeonCount.SetSelectedIndex((currentSetting == &MQDungeonCount && (kDown & KEY_RIGHT)) ? 13 : MQ + R);
        }
    } else {
        for (Option* option : dungeonOptions) {
            option->SetSelectedIndex(2);
            option->Hide();
        }
    }

    // Force Link's Pocket Item to be a dungeon reward if Shuffle Rewards is end of dungeons
    if (ShuffleRewards.Is(REWARDSHUFFLE_END_OF_DUNGEON)) {
        LinksPocketItem.Lock();
        LinksPocketItem.SetSelectedIndex(LINKSPOCKETITEM_DUNGEON_REWARD);
        if (RandomizeShuffle) {
            // Even if it is supposed to be locked, still hide it to keep the surprise
            LinksPocketItem.Unlock();
            LinksPocketItem.Hide();
        }
    } else {
        LinksPocketItem.Unlock();
    }

    if (ShuffleEnemySouls || RandomizeShuffle) {
        startingEnemySouls.Unlock();
        SoullessEnemiesLook.Unlock();
    } else {
        startingEnemySouls.Lock();
        startingInventory.ResetMenuIndex();
        SoullessEnemiesLook.Lock();
    }

    if (ShuffleOcarinaButtons || RandomizeShuffle) {
        startingOcarinaButtons.Unlock();
    } else {
        startingOcarinaButtons.Lock();
        startingInventory.ResetMenuIndex();
    }

    if (!RandomizeDungeon) {
        // Only show Medallion Count if setting Ganons Boss Key to LACS Medallions
        if (GanonsBossKey.Is(GANONSBOSSKEY_LACS_MEDALLIONS)) {
            LACSMedallionCount.Unhide();
        } else {
            LACSMedallionCount.SetSelectedIndex(6);
            LACSMedallionCount.Hide();
        }

        // Only show Stone Count if setting Ganons Boss Key to LACS Stones
        if (GanonsBossKey.Is(GANONSBOSSKEY_LACS_STONES)) {
            LACSStoneCount.Unhide();
        } else {
            LACSStoneCount.SetSelectedIndex(3);
            LACSStoneCount.Hide();
        }

        // Only show Reward Count if setting Ganons Boss Key to LACS Rewards
        if (GanonsBossKey.Is(GANONSBOSSKEY_LACS_REWARDS)) {
            LACSRewardCount.Unhide();
        } else {
            LACSRewardCount.SetSelectedIndex(9);
            LACSRewardCount.Hide();
        }

        // Only show Dungeon Count if setting Ganons Boss Key to LACS Dungeons
        if (GanonsBossKey.Is(GANONSBOSSKEY_LACS_DUNGEONS)) {
            LACSDungeonCount.Unhide();
        } else {
            LACSDungeonCount.SetSelectedIndex(8);
            LACSDungeonCount.Hide();
        }

        // Only show Token Count if setting Ganons Boss Key to LACS Tokens
        if (GanonsBossKey.Is(GANONSBOSSKEY_LACS_TOKENS)) {
            LACSTokenCount.Unhide();
        } else {
            LACSTokenCount.SetSelectedIndex(100);
            LACSTokenCount.Hide();
        }

        // Only show Heart Count if setting Ganons Boss Key to LACS Hearts
        if (GanonsBossKey.Is(GANONSBOSSKEY_LACS_HEARTS)) {
            LACSHeartCount.Unhide();
        } else {
            LACSHeartCount.SetSelectedIndex(20);
            LACSHeartCount.Hide();
        }

        if (KeyRings.Is(KEYRINGS_CHOOSE)) {
            for (Option* option : keyRingOptions) {
                option->Unhide();
            }
        } else {
            for (Option* option : keyRingOptions) {
                option->Hide();
                if (KeyRings.Is(KEYRINGS_OFF)) {
                    option->SetSelectedIndex(OFF);
                } else if (KeyRings.Is(KEYRINGS_ON)) {
                    option->SetSelectedIndex(ON);
                }
            }
        }
    }

    // Since No Logic doesn't create a playthrough, select the next best hint distribution
    if (Logic.Is(LOGIC_NONE) && HintDistribution.Is(HINTDISTRIBUTION_PLAYTHROUGH)) {
        if (currentSetting == &HintDistribution && kDown & KEY_RIGHT) {
            HintDistribution.SetSelectedIndex(HINTDISTRIBUTION_USELESS);
        } else {
            HintDistribution.SetSelectedIndex(HINTDISTRIBUTION_VERYSTRONG);
        }
    }

    // Only show hint options if hints are enabled
    if (GossipStoneHints.Is(HINTS_NO_HINTS)) {
        HintDistribution.Hide();
        BonusGossipHints.Hide();
    } else {
        HintDistribution.Unhide();
        if (HintDistribution.Is(HINTDISTRIBUTION_PLAYTHROUGH)) {
            BonusGossipHints.Unhide();
        } else {
            BonusGossipHints.Hide();
        }
    }

    // Manage toggle for misc hints options
    ToggleSet(miscOptions, &MiscHints, &ToTAltarHints, &FishingHints);

    if (ChestAppearance.IsNot(CHESTAPPEARANCE_VANILLA)) {
        ChestAgony.Unhide();
    } else {
        ChestAgony.Hide();
        ChestAgony.SetSelectedIndex(0);
    }

    // Only show advanced trap options if random trap damage is set to "Advanced"
    if (RandomTrapDmg.Is(RANDOMTRAPS_ADVANCED)) {
        FireTrap.Unhide();
        AntiFairyTrap.Unhide();
        CurseTraps.Unhide();
    } else {
        FireTrap.Hide();
        AntiFairyTrap.Hide();
        CurseTraps.Hide();
        CurseTraps.SetSelectedIndex(0);
    }

    if (CurseTraps) {
        ScreenTraps.Unhide();
    } else {
        ScreenTraps.Hide();
        ScreenTraps.SetSelectedIndex(0);
    }

    ToggleSet(gameplayOptions, &HyperActors, &HyperBosses, &HyperEnemies);

    if (FreeCamera) {
        FreeCamControl.Unhide();
    } else {
        FreeCamControl.Hide();
        FreeCamControl.SetSelectedIndex(0);
    }

    if (RandomGsLocations) {
        GsLocGuaranteeNew.Unhide();
    } else {
        GsLocGuaranteeNew.Hide();
    }

    // Manage toggle for item usability options
    ToggleSet(itemUsabilityOptions, &AgeItemsToggle, &StickAsAdult, &ZoraTunicAsChild);
    if (AgeItemsToggle.Value<u8>() > 0) {
        AgeItemsInLogic.Unhide();
    } else {
        AgeItemsInLogic.Hide();
        AgeItemsInLogic.SetSelectedIndex(0);
    }

    if (RemoveDoubleDefense) {
        StartingDoubleDefense.SetSelectedIndex(0);
        StartingDoubleDefense.Lock();
    } else {
        StartingDoubleDefense.Unlock();
    }

    if (RestoreISG) {
        GlitchISG.Unlock();
        GlitchHover.Unlock();
    } else {
        GlitchISG.SetSelectedIndex(0);
        GlitchISG.Lock();
        GlitchHover.SetSelectedIndex(0);
        GlitchHover.Lock();
    }

    if (currentSetting != nullptr) {
        if ((kDown & KEY_LEFT || kDown & KEY_RIGHT) && currentSetting == &ToggleAllTricks) {
            for (u16 i = 1; i < Settings::trickOptions.size(); i++) {
                trickOptions[i]->SetSelectedIndex(0);
            }
            if (currentSetting->GetSelectedOptionIndex() >= 1) { // novice options
                LogicGrottosWithoutAgony.SetSelectedIndex(1);
                LogicVisibleCollision.SetSelectedIndex(1);
                LogicFewerTunicRequirements.SetSelectedIndex(1);
                LogicLostWoodsGSBean.SetSelectedIndex(1);
                LogicLabDiving.SetSelectedIndex(1);
                LogicGraveyardPoH.SetSelectedIndex(1);
                LogicGVHammerChest.SetSelectedIndex(1);
                LogicManOnRoof.SetSelectedIndex(1);
                LogicWindmillPoHHookshot.SetSelectedIndex(1);
                LogicGoronCityLeftMost.SetSelectedIndex(1);
                LogicZoraRiverLower.SetSelectedIndex(1);
                LogicZoraRiverUpper.SetSelectedIndex(1);
                LogicZFGreatFairy.SetSelectedIndex(1);
                LogicDekuB1WebsWithBow.SetSelectedIndex(1);
                LogicDCJump.SetSelectedIndex(1);
                LogicJabuScrubJumpDive.SetSelectedIndex(1);
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
                LogicFlamingChests.SetSelectedIndex(1);
            }
            if (currentSetting->GetSelectedOptionIndex() >= 2) { // intermediate options
                LogicLabWallGS.SetSelectedIndex(1);
                LogicChildDampeRacePoH.SetSelectedIndex(1);
                LogicGerudoKitchen.SetSelectedIndex(1);
                LogicGerudoChildClimb.SetSelectedIndex(1);
                LogicOutsideGanonsGS.SetSelectedIndex(1);
                LogicDMTSoilGS.SetSelectedIndex(1);
                LogicDMTSummitHover.SetSelectedIndex(1);
                LogicLinkGoronDins.SetSelectedIndex(1);
                LogicGoronCityPotWithStrength.SetSelectedIndex(1);
                // LogicCraterUpperToLower.SetSelectedIndex(1);
                LogicBiggoronBolero.SetSelectedIndex(1);
                LogicDekuB1Skip.SetSelectedIndex(1);
                LogicDekuBasementGS.SetSelectedIndex(1);
                LogicDCStaircase.SetSelectedIndex(1);
                LogicDCScarecrowGS.SetSelectedIndex(1);
                // LogicJabuBossGSAdult.SetSelectedIndex(1);
                // LogicForestOutsideBackdoor.SetSelectedIndex(1);
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
            if (currentSetting->GetSelectedOptionIndex() == 3) { // expert options
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
                // LogicShadowFireArrowEntry.SetSelectedIndex(1);
                LogicShadowUmbrella.SetSelectedIndex(1);
                LogicShadowBongo.SetSelectedIndex(1);
                LogicGtgWithoutHookshot.SetSelectedIndex(1);
            }
        }
    }

    if ((kDown & KEY_LEFT || kDown & KEY_RIGHT) && currentSetting == &ToggleAllGlitches) {
        auto setDifficulty = ToggleAllGlitches.GetSelectedOptionIndex();
        for (auto option : glitchCategories) {
            if (option == &ToggleAllGlitches || (!RestoreISG && (option == &GlitchISG || option == &GlitchHover))) {
                continue;
            }
            // See if the glitch option has the set difficulty available.
            // If not, check one difficulty lower. Repeat until found.
            // (All glitches are guaranteed to have "Disabled")
            bool difficultyFound = false;
            for (size_t i = setDifficulty; i >= 0; i--) {
                for (size_t j = 0; j < option->GetOptions().size(); j++) {
                    if (option->GetOptions()[j] == GlitchDifficulties[i]) {
                        option->SetSelectedIndex(j);
                        difficultyFound = true;
                        break;
                    }
                }
                if (difficultyFound) {
                    break;
                }
            }
        }
    }

    // Multiplayer
    for (auto op : multiplayerOptions) {
        if (op == &MP_Enabled) {
            continue;
        }
        if (MP_Enabled) {
            op->Unhide();
        } else {
            op->Hide();
            op->SetSelectedIndex(0);
        }
    }
    if (MP_SharedProgress) {
        MP_SyncId.Unhide();
    } else {
        MP_SyncId.Hide();
        MP_SyncId.SetSelectedIndex(0);
    }

    // Tunic Colors
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
        ChildTunicColor.SetSelectedIndex(SAME_AS_KOKIRI);
        KokiriTunicColor.SetSelectedIndex(3); // Kokiri Green
        GoronTunicColor.SetSelectedIndex(4);  // Goron Red
        ZoraTunicColor.SetSelectedIndex(5);   // Zora Blue
    }

    if (CustomNaviColors) {
        IdleNaviInnerColor.Unhide();
        NPCNaviInnerColor.Unhide();
        EnemyNaviInnerColor.Unhide();
        PropNaviInnerColor.Unhide();
        IdleNaviOuterColor.Unhide();
        NPCNaviOuterColor.Unhide();
        EnemyNaviOuterColor.Unhide();
        PropNaviOuterColor.Unhide();
    } else {
        IdleNaviInnerColor.Hide();
        NPCNaviInnerColor.Hide();
        EnemyNaviInnerColor.Hide();
        PropNaviInnerColor.Hide();
        IdleNaviOuterColor.Hide();
        NPCNaviOuterColor.Hide();
        EnemyNaviOuterColor.Hide();
        PropNaviOuterColor.Hide();
        IdleNaviInnerColor.SetSelectedIndex(3);  // White
        NPCNaviInnerColor.SetSelectedIndex(5);   // Light Blue
        EnemyNaviInnerColor.SetSelectedIndex(6); // Yellow
        PropNaviInnerColor.SetSelectedIndex(4);  // Green
        IdleNaviOuterColor.SetSelectedIndex(SAME_AS_INNER_NAVI);
        NPCNaviOuterColor.SetSelectedIndex(SAME_AS_INNER_NAVI);
        EnemyNaviOuterColor.SetSelectedIndex(SAME_AS_INNER_NAVI);
        PropNaviOuterColor.SetSelectedIndex(SAME_AS_INNER_NAVI);
    }

    if (CustomTrailEffects) {
        ChosenSimpleMode.Unhide();
        SwordTrailInnerColor.Unhide();
        SwordTrailOuterColor.Unhide();
        SwordTrailDuration.Unhide();
        BoomerangTrailColor.Unhide();
        BoomerangTrailDuration.Unhide();
        BombchuTrailInnerColor.Unhide();
        BombchuTrailOuterColor.Unhide();
        BombchuTrailDuration.Unhide();
    } else {
        ChosenSimpleMode.Hide();
        SwordTrailInnerColor.Hide();
        SwordTrailOuterColor.Hide();
        SwordTrailDuration.Hide();
        BoomerangTrailColor.Hide();
        BoomerangTrailDuration.Hide();
        BombchuTrailInnerColor.Hide();
        BombchuTrailOuterColor.Hide();
        BombchuTrailDuration.Hide();
        ChosenSimpleMode.SetSelectedIndex(OFF);
        SwordTrailInnerColor.SetSelectedIndex(3); // White
        SwordTrailOuterColor.SetSelectedIndex(SAME_AS_INNER_TRAIL);
        SwordTrailDuration.SetSelectedIndex(2);     // Vanilla
        BoomerangTrailColor.SetSelectedIndex(8);    // Yellow
        BoomerangTrailDuration.SetSelectedIndex(2); // Vanilla
        BombchuTrailInnerColor.SetSelectedIndex(5); // Red
        BombchuTrailOuterColor.SetSelectedIndex(SAME_AS_INNER_TRAIL);
        BombchuTrailDuration.SetSelectedIndex(2); // Vanilla
    }

    // Audio
    if (ShuffleMusic) {
        ShuffleBGM.Unhide();
        ShuffleMelodies.Unhide();
        CustomMusic.Unhide();
        if (CustomMusic) {
            CustomMusicOnly.Unhide();
        } else {
            CustomMusicOnly.Hide();
            CustomMusicOnly.SetSelectedIndex(OFF);
        }
    } else {
        ShuffleBGM.Hide();
        ShuffleMelodies.Hide();
        CustomMusic.Hide();
        CustomMusicOnly.Hide();
        CustomMusicOnly.SetSelectedIndex(OFF);
    }

    if (ShuffleSFX) {
        ShuffleSFXFootsteps.Unhide();
        ShuffleSFXLinkVoice.Unhide();
        ShuffleSFXCategorically.Unhide();
    } else {
        ShuffleSFXFootsteps.Hide();
        ShuffleSFXLinkVoice.Hide();
        ShuffleSFXCategorically.Hide();
    }

    ResolveExcludedLocationConflicts();
}
// clang-format off
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

// Options that should be overridden and then restored after generating when racing is enabled
std::vector<std::pair<Option*, u8>> racingOverrides = {
    { &QuickText, QUICKTEXT_TURBO },
    { &SkipSongReplays, SONGREPLAYS_SKIP_NO_SFX },
    { &ColoredKeys, ON },
    { &ColoredBossKeys, ON },
    { &SoullessEnemiesLook, SOULLESSLOOK_PURPLE_FLAME },
};
// clang-format on

// Options that should be overridden and then restored after generating when vanilla logic is enabled
std::vector<std::pair<Option*, u8>> vanillaLogicOverrides = {
    { &TriforceHunt, OFF },
    { &LinksPocketItem, LINKSPOCKETITEM_DUNGEON_REWARD },
    { &ShuffleRewards, REWARDSHUFFLE_END_OF_DUNGEON },
    { &ShuffleSongs, SONGSHUFFLE_SONG_LOCATIONS },
    { &Shopsanity, SHOPSANITY_OFF },
    { &Scrubsanity, SCRUBSANITY_OFF },
    { &ShuffleCows, OFF },
    { &ShuffleMagicBeans, OFF },
    { &ShuffleMerchants, SHUFFLEMERCHANTS_OFF },
    { &ShuffleAdultTradeQuest, SHUFFLEADULTTRADEQUEST_ON },
    { &ShuffleChestMinigame, SHUFFLECHESTMINIGAME_OFF },
    { &ShuffleFrogSongRupees, SHUFFLEFROGSONGRUPEES_OFF },
    { &ShuffleEnemySouls, OFF },
    { &ShuffleOcarinaButtons, OFF },
    { &Keysanity, KEYSANITY_ANY_DUNGEON }, // Set small keys to any dungeon so FiT basement door will be locked
    { &GossipStoneHints, HINTS_NO_HINTS },
};

// Randomizes all settings in a category if chosen
// Hides all relevant options
void RandomizeAllSettings(const bool selectOptions /*= false*/) {

    // Open Settings
    if (RandomizeOpen) {
        // Skip RandomizeOpen Option
        for (size_t i = 1; i < openOptions.size(); i++) {
            // hide options
            openOptions[i]->Hide();

            // randomize options
            if (selectOptions) {
                openOptions[i]->SetSelectedIndex(Random(0, openOptions[i]->GetOptionCount()));
            }
        }
        // Randomize Ganon Trials
        RandomGanonsTrials.SetSelectedIndex(ON);
    } else {
        for (size_t i = 1; i < openOptions.size(); i++) {
            openOptions[i]->Unhide();
        }
    }

    // World Settings
    if (RandomizeWorld) {
        // Skip RandomizeWorld Option
        for (size_t i = 1; i < worldOptions.size(); i++) {
            // skip MQ options
            if (IsMQOption(worldOptions[i])) {
                continue;
            }
            worldOptions[i]->Hide();
            // randomize options
            if (selectOptions) {
                worldOptions[i]->SetSelectedIndex(Random(0, worldOptions[i]->GetOptionCount()));
            }
            // Sanity Check Closed Forest
            if (OpenForest.Is(OPENFOREST_CLOSED)) {
                StartingAge.SetSelectedIndex(AGE_CHILD);
            }
        }
    } else {
        for (size_t i = 1; i < worldOptions.size(); i++) {
            if (IsMQOption(worldOptions[i])) {
                continue;
            }
            worldOptions[i]->Unhide();
        }
    }

    // Sanity Check Entrance Shuffling
    if (!ShuffleEntrances) {
        ShuffleDungeonEntrances.SetSelectedIndex(OFF);
        ShuffleBossEntrances.SetSelectedIndex(OFF);
        ShuffleOverworldEntrances.SetSelectedIndex(OFF);
        ShuffleInteriorEntrances.SetSelectedIndex(OFF);
        ShuffleGrottoEntrances.SetSelectedIndex(OFF);
        ShuffleOwlDrops.SetSelectedIndex(OFF);
        ShuffleWarpSongs.SetSelectedIndex(OFF);
        ShuffleOverworldSpawns.SetSelectedIndex(OFF);
        MixedEntrancePools.SetSelectedIndex(OFF);
        DecoupleEntrances.SetSelectedIndex(OFF);
    }

    if (!MixedEntrancePools) {
        MixDungeons.SetSelectedIndex(OFF);
        MixOverworld.SetSelectedIndex(OFF);
        MixInteriors.SetSelectedIndex(OFF);
        MixGrottos.SetSelectedIndex(OFF);
    }

    // Shuffle Settings
    if (RandomizeShuffle) {
        // Still displays if previously locked
        LinksPocketItem.Unlock();
        // Skip RandomizeShuffle Option
        for (size_t i = 1; i < shuffleOptions.size(); i++) {
            shuffleOptions[i]->Hide();
            // randomize options
            if (selectOptions) {
                shuffleOptions[i]->SetSelectedIndex(Random(0, shuffleOptions[i]->GetOptionCount()));
            }
        }
        // Double check that this is the case in case of randomization on init
        if (ShuffleRewards.Is(REWARDSHUFFLE_END_OF_DUNGEON)) {
            LinksPocketItem.SetSelectedIndex(LINKSPOCKETITEM_DUNGEON_REWARD);
        }
    } else {
        for (size_t i = 1; i < shuffleOptions.size(); i++) {
            shuffleOptions[i]->Unhide();
        }
    }

    // Dungeon Shuffle Settings
    if (RandomizeDungeon) {
        // Skip RandomizeDungeon Option
        for (size_t i = 1; i < shuffleDungeonItemOptions.size(); i++) {
            shuffleDungeonItemOptions[i]->Hide();
            // randomize options
            if (selectOptions) {
                shuffleDungeonItemOptions[i]->SetSelectedIndex(
                    Random(0, shuffleDungeonItemOptions[i]->GetOptionCount()));
            }
        }
    } else {
        for (size_t i = 1; i < shuffleDungeonItemOptions.size(); i++) {
            shuffleDungeonItemOptions[i]->Unhide();
        }
    }

    // resolve any settings that need to change
    if (selectOptions) {
        ValidateSettings();
        ForceChange(0, nullptr);
    }
}

template <typename colorsArray>
static void ChooseFinalColor(Option& cosmeticOption, std::string& colorStr, const colorsArray& colors) {
    if (cosmeticOption.Is(CUSTOM_COLOR)) {
        colorStr = GetCustomColor(cosmeticOption.GetSelectedOptionText());
    } else if (cosmeticOption.Is(RANDOM_CHOICE)) {
        size_t randomIndex = Random(0, colors.size(), true);
        cosmeticOption.SetSelectedIndex(
            randomIndex + NON_COLOR_COUNT); // set index so it can be copied for other settings (Navi outer color)
        colorStr = colors[randomIndex];
    } else if (cosmeticOption.Is(RANDOM_COLOR)) {
        colorStr = RandomColor();
    } else {
        colorStr = colors[cosmeticOption.GetSelectedOptionIndex() - NON_COLOR_COUNT];
    }
}

static void ChooseFinalNaviColor(Option& innerColorOption, Option& outerColorOption, std::string& innerColorStr,
                                 std::string& outerColorStr) {
    ChooseFinalColor(innerColorOption, innerColorStr, naviInnerColors);

    // If the outer color is "Same as Inner", only random and custom colors are copied directly via the hex code.
    // If instead a listed color is chosen (even through Random Choice), the outer color will use the same index as the
    // inner one to preserve color palettes (e.g. Midna giving black inner and gold outer).
    if (outerColorOption.Is(SAME_AS_INNER_NAVI) &&
        (innerColorOption.Is(RANDOM_COLOR) || innerColorOption.Is(CUSTOM_COLOR))) {
        outerColorStr = innerColorStr;
    } else if (outerColorOption.Is(SAME_AS_INNER_NAVI)) {
        outerColorOption.SetSelectedIndex(innerColorOption.Value<u8>());
        ChooseFinalColor(outerColorOption, outerColorStr, naviOuterColors);
    } else {
        ChooseFinalColor(outerColorOption, outerColorStr, naviOuterColors);
    }
}

// Function to update cosmetics options depending on choices
static void UpdateCosmetics() {
    // Tunics
    ChooseFinalColor(KokiriTunicColor, finalKokiriTunicColor, tunicColors);
    ChooseFinalColor(GoronTunicColor, finalGoronTunicColor, tunicColors);
    ChooseFinalColor(ZoraTunicColor, finalZoraTunicColor, tunicColors);
    if (ChildTunicColor.Is(SAME_AS_KOKIRI)) {
        finalChildTunicColor = finalKokiriTunicColor;
        ChildTunicColor.SetSelectedIndex(KokiriTunicColor.Value<u8>());
    } else {
        ChooseFinalColor(ChildTunicColor, finalChildTunicColor, tunicColors);
    }
    // Gauntlets
    ChooseFinalColor(SilverGauntletsColor, finalSilverGauntletsColor, gauntletColors);
    ChooseFinalColor(GoldGauntletsColor, finalGoldGauntletsColor, gauntletColors);
    // Navi
    ChooseFinalNaviColor(IdleNaviInnerColor, IdleNaviOuterColor, finalIdleNaviInnerColor, finalIdleNaviOuterColor);
    ChooseFinalNaviColor(NPCNaviInnerColor, NPCNaviOuterColor, finalNPCNaviInnerColor, finalNPCNaviOuterColor);
    ChooseFinalNaviColor(EnemyNaviInnerColor, EnemyNaviOuterColor, finalEnemyNaviInnerColor, finalEnemyNaviOuterColor);
    ChooseFinalNaviColor(PropNaviInnerColor, PropNaviOuterColor, finalPropNaviInnerColor, finalPropNaviOuterColor);
    // Sword Trail
    ChooseFinalColor(SwordTrailInnerColor, finalSwordTrailInnerColor, weaponTrailColors);
    if (SwordTrailOuterColor.Is(SAME_AS_INNER_TRAIL)) {
        SwordTrailOuterColor.SetSelectedIndex(SwordTrailInnerColor.Value<u8>());
        finalSwordTrailOuterColor = finalSwordTrailInnerColor;
    } else {
        ChooseFinalColor(SwordTrailOuterColor, finalSwordTrailOuterColor, weaponTrailColors);
    }
    // Boomerang Trail
    std::string tempString;
    Color_RGBA8 tempColor;
    ChooseFinalColor(BoomerangTrailColor, tempString, weaponTrailColors);
    tempColor             = Cosmetics::HexStrToColorRGBA8(tempString);
    finalBoomerangColor.r = tempColor.r;
    finalBoomerangColor.g = tempColor.g;
    finalBoomerangColor.b = tempColor.b;
    finalBoomerangColor.a = tempColor.a;
    if (Settings::BoomerangTrailColor.Value<u8>() == RAINBOW_TRAIL) {
        boomerangTrailColorMode = (ChosenSimpleMode) ? TRAILCOLOR_RAINBOW_SIMPLEMODE : TRAILCOLOR_RAINBOW;
    } else if (ChosenSimpleMode ||
               (Settings::finalBoomerangColor.r != 0xFF && Settings::finalBoomerangColor.g != 0xFF &&
                Settings::finalBoomerangColor.b != 0xFF) ||
               (Settings::BoomerangTrailColor.Value<u8>() == 3)) { // Chosen Simple Mode, dark color, or White
        boomerangTrailColorMode = TRAILCOLOR_FORCEDSIMPLEMODE;
    } else {
        boomerangTrailColorMode = TRAILCOLOR_VANILLAMODE;
    }
    // Bombchus Trail
    ChooseFinalColor(BombchuTrailInnerColor, finalChuTrailInnerColor, weaponTrailColors);
    if (BombchuTrailOuterColor.Is(SAME_AS_INNER_TRAIL)) {
        BombchuTrailOuterColor.SetSelectedIndex(BombchuTrailInnerColor.Value<u8>());
        finalChuTrailOuterColor = finalChuTrailInnerColor;
    } else {
        ChooseFinalColor(BombchuTrailOuterColor, finalChuTrailOuterColor, weaponTrailColors);
    }
}

// Function to set flags depending on settings
void UpdateSettings() {
    // Override cosmetic options that can affect how fast a seed is beaten
    if (Racing) {
        for (auto overridePair : racingOverrides) {
            overridePair.first->SetSelectedIndex(overridePair.second);
        }
    }

    // If vanilla logic, we want to set all settings which unnecessarily modify vanilla behavior to off
    if (Logic.Is(LOGIC_VANILLA)) {
        for (auto overridePair : vanillaLogicOverrides) {
            overridePair.first->SetSelectedIndex(overridePair.second);
        }
    }

    if (GloomMode.IsNot(GLOOMMODE_OFF) && Logic.IsNot(LOGIC_NONE) && !(GoronTunicAsChild && AgeItemsInLogic)) {
        for (LocationKey loc : childOnlyHotLocations) {
            Location(loc)->GetExcludedOption()->SetSelectedIndex(EXCLUDE);
        }
    }

    RandomizeAllSettings(true); // now select any random options instead of just hiding them

    // shuffle the dungeons and then set MQ for as many as necessary
    auto dungeons = dungeonList;
    if (SetDungeonTypes) {
        MQSet                        = MQDungeonCount.Value<u8>();
        u8 dungeonCount              = 0;
        std::vector<u8> randMQOption = {};

        for (size_t i = 0; i < dungeons.size(); i++) {
            dungeons[i]->ClearMQ();
            // Dungeon mode assumed known at first
            DungeonModesKnown[i] = true;

            switch (dungeonOptions[i]->Value<u8>()) {
                case 1:
                    // Set MQ dungeons and track how many have been set
                    dungeons[i]->SetMQ();
                    dungeonCount++;
                    break;
                case 2:
                    // Track indexes of dungeons set to random
                    randMQOption.push_back(i);
                    // Dungeon mode will be unknown for this dungeon
                    DungeonModesKnown[i] = false;
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

        // Clear MQ dungeons
        for (size_t i = 0; i < dungeons.size(); i++) {
            dungeons[i]->ClearMQ();
        }

        // If we won't be randomly choosing any MQ dungeons, or if we'll be setting
        // all dungeons to MQ, dungeon modes are assumed known
        bool allDungeonModesKnown = MQSet == 0 || MQSet == dungeons.size();
        for (u8 i = 0; i < sizeof(DungeonModesKnown); ++i) {
            DungeonModesKnown[i] = allDungeonModesKnown;
        }

        // Set appropriate amount of MQ dungeons
        if (MQSet == 13) {
            MQSet = Random(0, 13);
        }
        for (u8 i = 0; i < MQSet; i++) {
            dungeons[i]->SetMQ();
        }
    }

    // Set key ring for each dungeon
    for (size_t i = 0; i < dungeons.size(); i++) {
        dungeons[i]->ClearKeyRing();
    }
    if (KeyRings) {
        // Rangom Key Rings
        if (KeyRings.Is(KEYRINGS_RANDOM)) {
            auto keyRings = keyRingOptions;
            Shuffle(keyRings);
            auto amount = Random(0, keyRings.size() + 1);
            for (size_t i = 0; i < keyRings.size(); i++) {
                if (i < amount) {
                    keyRings[i]->SetSelectedIndex(ON);
                } else {
                    keyRings[i]->SetSelectedIndex(OFF);
                }
            }
        }
        if (RingWell) {
            BottomOfTheWell.SetKeyRing();
        }
        if (RingForest) {
            ForestTemple.SetKeyRing();
        }
        if (RingFire) {
            FireTemple.SetKeyRing();
        }
        if (RingWater) {
            WaterTemple.SetKeyRing();
        }
        if (RingSpirit) {
            SpiritTemple.SetKeyRing();
        }
        if (RingShadow) {
            ShadowTemple.SetKeyRing();
        }
        if (RingGtg) {
            GerudoTrainingGrounds.SetKeyRing();
        }
        if (RingCastle) {
            GanonsCastle.SetKeyRing();
        }
    }

    // shuffle the trials then require the amount set in GanonsTrialsCount
    auto trials = trialList;
    Shuffle(trials);

    // clear required trials
    for (auto& trial : trials) {
        trial->SetAsSkipped();
    }

    // Set appropriate amount of required trials
    if (RandomGanonsTrials) {
        GanonsTrialsCount.SetSelectedIndex(Random(0, GanonsTrialsCount.GetOptionCount()));
    }
    for (u8 i = 0; i < GanonsTrialsCount.Value<u8>(); i++) {
        trials[i]->SetAsRequired();
    }

    if (StartingAge.Is(AGE_RANDOM)) {
        int choice = Random(0, 2); // 50% chance of each
        if (choice == 0) {
            ResolvedStartingAge = AGE_CHILD;
        } else {
            ResolvedStartingAge = AGE_ADULT;
        }
    } else {
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
    } else if (GanonsBossKey.Is(GANONSBOSSKEY_LACS_HEARTS)) {
        LACSCondition = LACSCONDITION_HEARTS;
    } else {
        LACSCondition = LACSCONDITION_VANILLA;
    }

    UpdateCosmetics();

    InitMusicRandomizer();
    if (ShuffleMusic) {
        if (ShuffleBGM.Is(SHUFFLEMUSIC_MIXED)) {
            Music::ShuffleSequences(Music::SeqType::SEQ_BGM_WORLD | Music::SeqType::SEQ_BGM_EVENT |
                                    Music::SeqType::SEQ_BGM_BATTLE);
            Music::ShuffleSequences(Music::SeqType::SEQ_BGM_ERROR);
        } else if (ShuffleBGM.Is(SHUFFLEMUSIC_GROUPED)) {
            Music::ShuffleSequences(Music::SeqType::SEQ_BGM_WORLD);
            Music::ShuffleSequences(Music::SeqType::SEQ_BGM_EVENT);
            Music::ShuffleSequences(Music::SeqType::SEQ_BGM_BATTLE);
        }

        if (ShuffleMelodies.Is(SHUFFLEMUSIC_MIXED)) {
            Music::ShuffleSequences(Music::SeqType::SEQ_FANFARE | Music::SeqType::SEQ_OCARINA);
        } else if (ShuffleMelodies.Is(SHUFFLEMUSIC_GROUPED)) {
            Music::ShuffleSequences(Music::SeqType::SEQ_FANFARE);
            Music::ShuffleSequences(Music::SeqType::SEQ_OCARINA);
        }
    }

    InitSFXRandomizer();
    if (ShuffleSFX.IsNot(SHUFFLESFX_OFF)) {
        SFX::ShuffleSequences(ShuffleSFXCategorically.Value<bool>());
    }
}

// If this is an option menu, return the options
// Else, recursively call each sub menu of this sub menu
const std::vector<Menu*> GetMenusRecursive(Menu* menu) {
    std::vector<Menu*> menus;
    if (menu->mode == OPTION_MENU) {
        menus.push_back(menu);
    } else if (menu->mode == SUB_MENU) {
        for (Menu* subMenu : *menu->itemsList) {
            std::vector<Menu*> foundMenus = GetMenusRecursive(subMenu);
            menus.insert(menus.end(), foundMenus.begin(), foundMenus.end());
        }
    }
    return menus;
}

// Recursively look through each menu from the main menu to get all settings
const std::vector<Menu*> GetAllOptionMenus() {
    std::vector<Menu*> allMenus;
    for (Menu* menu : Settings::mainMenu) {
        std::vector<Menu*> foundMenus = GetMenusRecursive(menu);
        allMenus.insert(allMenus.end(), foundMenus.begin(), foundMenus.end());
    }
    allMenus.push_back(&enemizerListMenu); // this menu is detached from the others
    return allMenus;
}

bool IsGlitchOption(Option& option) {
    for (auto op : glitchCategories) {
        if (op == &ToggleAllGlitches) {
            continue;
        }
        if (&option == op) {
            return true;
        }
    }
    return false;
}

u8 GlitchValue(Option& glitchOption) {
    if (Logic.IsNot(LOGIC_GLITCHED) || !IsGlitchOption(glitchOption)) {
        return 0;
    }
    for (size_t difficulty = 0; difficulty < GlitchDifficulties.size(); difficulty++) {
        if (glitchOption.GetSelectedOptionText() == GlitchDifficulties[difficulty]) {
            return difficulty;
        }
    }
    return 0;
}

bool GlitchEnabled(Option& glitchOption, GlitchDifficulty glitchDifficulty) {
    if (Logic.IsNot(LOGIC_GLITCHED) || !IsGlitchOption(glitchOption)) {
        return false;
    }
    return GlitchValue(glitchOption) >= static_cast<u8>(glitchDifficulty);
}

bool GlitchEnabled(Option& glitchOption) {
    auto isMiscGlitch = [&] {
        for (auto op : miscGlitches) {
            if (&glitchOption == op) {
                return true;
            }
        }
        return false;
    };

    return Logic.Is(LOGIC_GLITCHED) && isMiscGlitch() && glitchOption;
}

// This function checks for conflicting settings similarly to ForceChange, but:
// - it only gets called when generating a seed instead of after any input on settings menus, and
// - it only changes the selected options if the setting is hidden (randomized), otherwise it prints an error message to
//   let the player choose how to solve the conflict.
bool ValidateSettings() {
    bool valid = true;
    u8 posY    = 5;

    // Check Heart requirements
    s32 maxHearts = 20;
    switch (ItemPoolValue.Value<u8>()) {
        case ITEMPOOL_MINIMAL:
            maxHearts = 3;
            break;
        case ITEMPOOL_SCARCE:
            maxHearts = 12;
            break;
    }
    bool printHeartError = false;
    if (Bridge.Is(RAINBOWBRIDGE_HEARTS) && BridgeHeartCount.Value<u8>() > maxHearts) {
        if (BridgeHeartCount.IsHidden()) {
            BridgeHeartCount.SetSelectedIndex(maxHearts);
        } else {
            printHeartError = true;
        }
    }
    if (GanonsBossKey.Is(GANONSBOSSKEY_LACS_HEARTS) && LACSHeartCount.Value<u8>() > maxHearts) {
        if (LACSHeartCount.IsHidden()) {
            LACSHeartCount.SetSelectedIndex(maxHearts);
        } else {
            printHeartError = true;
        }
    }
    if (printHeartError) {
        printf("\x1b[%d;0H"
               "----------------------------------------"
               "Not enough Hearts in pool!\n\n"
               "Please choose a different Item Pool\n"
               "setting or lower the Hearts requirement."
               "----------------------------------------",
               posY);
        valid = false;
        posY += 7;
    }

    // Check that there are no Heart requirements with Gloom Mode.
    if (GloomMode.IsNot(GLOOMMODE_OFF) &&
        (Bridge.Is(RAINBOWBRIDGE_HEARTS) || GanonsBossKey.Is(GANONSBOSSKEY_LACS_HEARTS))) {
        if (Bridge.IsHidden() && GanonsBossKey.IsHidden()) {
            Bridge.SetSelectedIndex(RAINBOWBRIDGE_VANILLA);
            GanonsBossKey.SetSelectedIndex(GANONSBOSSKEY_VANILLA);
        } else {
            printf("\x1b[%d;0H"
                   "----------------------------------------"
                   "Gloom Mode is incompatible with Heart\n"
                   "requirements for LACS or Rainbow Bridge."
                   "----------------------------------------",
                   posY);
            valid = false;
            posY += 5;
        }
    }

    // Check that there are no MQ dungeons with Enemy Souls or Enemy Randomizer.
    if ((ShuffleEnemySouls.Is(SHUFFLEENEMYSOULS_ALL) || Enemizer) && MQDungeonCount.IsNot(0) &&
        Logic.IsNot(LOGIC_NONE) && Logic.IsNot(LOGIC_VANILLA)) {
        if (ShuffleEnemySouls.IsHidden() && Enemizer.IsHidden()) {
            ShuffleEnemySouls.SetSelectedIndex(SHUFFLEENEMYSOULS_OFF);
            Enemizer.SetSelectedIndex(OFF);
        } else {
            printf("\x1b[%d;0H"
                   "----------------------------------------"
                   "Enemy Soul Shuffle and Enemy Randomizer\n"
                   "currently do not have logic for Master\n"
                   "Quest dungeons.\n"
                   "\n"
                   "Please disable one of the following:\n"
                   " - MQ Dungeons (setting Count to 0)\n"
                   " - Logic\n"
                   " - Enemy Soul Shuffle / Enemy Randomizer"
                   "----------------------------------------",
                   posY);
            valid = false;
            posY += 11;
        }
    }
    if (ShuffleRupees && MQDungeonCount.IsNot(0) && Logic.IsNot(LOGIC_NONE) && Logic.IsNot(LOGIC_VANILLA)) {
        if (ShuffleRupees.IsHidden()) {
            ShuffleRupees.SetSelectedIndex(OFF);
        } else {
            printf("\x1b[%d;0H"
                   "----------------------------------------"
                   "Rupeesanity currently does not have\n"
                   "logic for Master Quest dungeons.\n"
                   "\n"
                   "Please disable one of the following:\n"
                   " - MQ Dungeons (setting Count to 0)\n"
                   " - Logic\n"
                   " - Rupeesanity\n"
                   "----------------------------------------",
                   posY);
            valid = false;
            posY += 11;
        }
    }

    return valid;
}

std::string TitleId() {
    if (Region == REGION_EUR) {
        return "0004000000033600";
    } else { // REGION_NA
        return "0004000000033500";
    }
}

} // namespace Settings
