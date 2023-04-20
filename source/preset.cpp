#include "preset.hpp"

#include <3ds.h>
#include <unistd.h>

#include <array>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <vector>

#include "category.hpp"
#include "settings.hpp"
#include "descriptions.hpp"
#include "tinyxml2.h"
#include "utils.hpp"

namespace fs = std::filesystem;

static const std::string CACHED_SETTINGS_FILENAME  = "CACHED_SETTINGS";
static const std::string CACHED_COSMETICS_FILENAME = "CACHED_COSMETICS";

static std::string_view GetBasePath(OptionCategory category) {
    static constexpr std::array<std::string_view, 2> paths{
        "/OoT3DR/Presets/Settings/",
        "/OoT3DR/Presets/Cosmetics/",
    };

    switch (category) {
        case OptionCategory::Setting:
        case OptionCategory::Cosmetic:
            return paths[static_cast<size_t>(category)];
        case OptionCategory::Toggle:
            break;
    }
    return "";
}

// Creates preset directories if they don't exist
void CreatePresetDirectories(FS_Archive sdmcArchive) {
    std::vector<std::string> dirs = {
        "/OoT3DR/",
        "/OoT3DR/Presets/",
        "/OoT3DR/Presets/Settings/",
        "/OoT3DR/Presets/Cosmetics/",
    };

    const auto printInfo = [&](int progress) {
        consoleClear();
        printf("\x1b[10;10HCreating Preset Directories");
        printf("\x1b[11;10HProgress: %d/%d", progress, dirs.size());
    };

    printInfo(0);
    for (size_t i = 0; i < dirs.size(); i++) {
        FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, dirs[i].c_str()), FS_ATTRIBUTE_DIRECTORY);
        printInfo(i + 1);
    }

    // Migrate presets to new directories

    std::vector<std::pair<std::string, std::string>> dirPairs = {
        { "/3ds/presets/oot3dr/settings/", "/OoT3DR/Presets/Settings/" },
        { "/3ds/presets/oot3dr/cosmetics/", "/OoT3DR/Presets/Cosmetics/" },
    };

    for (auto dirPair : dirPairs) {
        if (R_FAILED(FSUSER_OpenDirectory(nullptr, sdmcArchive, fsMakePath(PATH_ASCII, dirPair.first.c_str())))) {
            continue;
        }
        for (const auto& entry : fs::directory_iterator(dirPair.first)) {
            if (entry.is_regular_file() && entry.path().extension().string() == ".xml") {
                auto filename = entry.path().filename().string();
                consoleClear();
                printf("\x1b[10;10HMigrating Presets");
                printf("\x1b[11;10HMoving %s", filename.c_str());
                FSUSER_RenameFile(sdmcArchive, fsMakePath(PATH_ASCII, std::string(dirPair.first + filename).c_str()),
                                  sdmcArchive, fsMakePath(PATH_ASCII, std::string(dirPair.second + filename).c_str()));
            }
        }
    }
}

// Gets the preset filenames
std::vector<std::string> GetSettingsPresets() {
    std::vector<std::string> presetEntries = {};
    for (const auto& entry : fs::directory_iterator(GetBasePath(OptionCategory::Setting))) {
        if (entry.is_regular_file() && entry.path().stem().string() != CACHED_SETTINGS_FILENAME) {
            presetEntries.push_back(entry.path().stem().string());
        }
    }
    return presetEntries;
}

static std::string PresetPath(std::string_view presetName, OptionCategory category) {
    return std::string(GetBasePath(category)).append(presetName).append(".xml");
}

// Presets are now saved as XML files using the tinyxml2 library.
// Documentation: https://leethomason.github.io/tinyxml2/index.html
bool SavePreset(std::string_view presetName, OptionCategory category) {
    using namespace tinyxml2;

    XMLDocument preset = XMLDocument(false);

    // Create and insert the XML declaration
    preset.InsertEndChild(preset.NewDeclaration());

    // Create the root node
    XMLElement* rootNode = preset.NewElement("settings");
    preset.InsertEndChild(rootNode);

    for (Menu* menu : Settings::GetAllOptionMenus()) {
        if (menu->mode != OPTION_MENU) {
            continue;
        }
        for (const Option* setting : *menu->settingsList) {
            if (!setting->IsCategory(category)) {
                continue;
            }

            XMLElement* newSetting = rootNode->InsertNewChildElement("setting");
            newSetting->SetAttribute("name", SanitizedString(setting->GetName()).c_str());
            newSetting->SetText(SanitizedString(setting->GetSelectedOptionText()).c_str());
        }
    }

    XMLError e = preset.SaveFile(PresetPath(presetName, category).c_str());
    return e == XML_SUCCESS;
}

// Read the preset XML file
bool LoadPreset(std::string_view presetName, OptionCategory category) {
    using namespace tinyxml2;

    XMLDocument preset;
    XMLError e = preset.LoadFile(PresetPath(presetName, category).c_str());
    if (e != XML_SUCCESS) {
        return false;
    }

    XMLElement* rootNode = preset.RootElement();
    if (strcmp(rootNode->Name(), "settings") != 0) {
        // We do not have our <settings> root node, so it may be the old structure. We don't support that one anymore.
        return false;
    }

    XMLElement* curNode = rootNode->FirstChildElement();

    for (Menu* menu : Settings::GetAllOptionMenus()) {
        if (menu->mode != OPTION_MENU) {
            continue;
        }

        for (Option* setting : *menu->settingsList) {
            if (!setting->IsCategory(category)) {
                continue;
            }

            // Since presets are saved linearly, we can simply loop through the nodes as
            // we loop through the settings to find most of the matching elements.
            const std::string& settingToFind = SanitizedString(setting->GetName());
            if (settingToFind == SanitizedString(curNode->Attribute("name"))) {
                setting->SetSelectedIndexByString(curNode->GetText());
                curNode = curNode->NextSiblingElement();
            } else {
                // If the current setting and element don't match, then search
                // linearly from the beginning. This will get us back on track if the
                // next setting and element line up with each other.
                curNode = rootNode->FirstChildElement();
                while (curNode != nullptr) {
                    if (settingToFind == SanitizedString(curNode->Attribute("name"))) {
                        setting->SetSelectedIndexByString(curNode->GetText());
                        curNode = curNode->NextSiblingElement();
                        break;
                    }
                    curNode = curNode->NextSiblingElement();
                }
            }

            // Reset to the beginning if we reached the end.
            if (curNode == nullptr) {
                curNode = rootNode->FirstChildElement();
            }
        }
    }
    return true;
}

// Delete the selected preset
bool DeletePreset(std::string_view presetName, OptionCategory category) {
    Result res;
    FS_Archive sdmcArchive = 0;

    const std::string filepath = PresetPath(presetName, category);

    // Open SD archive
    if (!R_SUCCEEDED(res = FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) {
        printf("\x1b[22;5HFailed to load SD Archive.");
        return false;
    }

    FSUSER_DeleteFile(sdmcArchive, fsMakePath(PATH_ASCII, filepath.c_str()));
    return true;
}

// Saves the new preset to a file
bool SaveSpecifiedPreset(std::string_view presetName, OptionCategory category) {
    // don't save if the user cancelled
    if (presetName.empty()) {
        return false;
    }
    return SavePreset(presetName, category);
}

void SaveCachedSettings() {
    SavePreset(CACHED_SETTINGS_FILENAME, OptionCategory::Setting);
}

void LoadCachedSettings() {
    // If cache file exists, load it
    for (const auto& entry : fs::directory_iterator(GetBasePath(OptionCategory::Setting))) {
        if (entry.path().stem().string() == CACHED_SETTINGS_FILENAME) {
            // File exists, open
            LoadPreset(CACHED_SETTINGS_FILENAME, OptionCategory::Setting);
        }
    }
}

bool SaveCachedCosmetics() {
    return SavePreset(CACHED_COSMETICS_FILENAME, OptionCategory::Cosmetic);
}

void LoadCachedCosmetics() {
    // If cache file exists, load it
    for (const auto& entry : fs::directory_iterator(GetBasePath(OptionCategory::Cosmetic))) {
        if (entry.path().stem().string() == CACHED_COSMETICS_FILENAME) {
            // File exists, open
            LoadPreset(CACHED_COSMETICS_FILENAME, OptionCategory::Cosmetic);
        }
    }
}

PremadePreset presetNintended = { "Nintended",
                                  presetNintendedDesc,
                                  {
                                      // Open Settings
                                      { &Settings::OpenForest, OPENFOREST_CLOSED },
                                      { &Settings::OpenKakariko, OPENKAKARIKO_CLOSED },
                                      { &Settings::OpenDoorOfTime, OPENDOOROFTIME_INTENDED },
                                      { &Settings::ZorasFountain, ZORASFOUNTAIN_NORMAL },
                                      { &Settings::OpenJabu, JABUJABU_CLOSED },
                                      { &Settings::GerudoFortress, GERUDOFORTRESS_NORMAL },
                                      { &Settings::Bridge, RAINBOWBRIDGE_MEDALLIONS },
                                      { &Settings::BridgeMedallionCount, 6 },
                                      { &Settings::RandomGanonsTrials, OFF },
                                      { &Settings::GanonsTrialsCount, 6 },
                                  } };

PremadePreset presetAllsanity = { "Allsanity",
                                  presetAllsanityDesc,
                                  {
                                      // World Settings
                                      { &Settings::ShuffleEntrances, ON },
                                      { &Settings::ShuffleDungeonEntrances, SHUFFLEDUNGEONS_GANON },
                                      { &Settings::ShuffleBossEntrances, SHUFFLEBOSSES_FULL },
                                      { &Settings::ShuffleOverworldEntrances, ON },
                                      { &Settings::ShuffleInteriorEntrances, SHUFFLEINTERIORS_ALL },
                                      { &Settings::ShuffleGrottoEntrances, ON },
                                      { &Settings::ShuffleOwlDrops, ON },
                                      { &Settings::ShuffleWarpSongs, ON },
                                      { &Settings::ShuffleOverworldSpawns, ON },
                                      { &Settings::MixedEntrancePools, ON },
                                      { &Settings::MixDungeons, ON },
                                      { &Settings::MixOverworld, ON },
                                      { &Settings::MixInteriors, ON },
                                      { &Settings::MixGrottos, ON },
                                      { &Settings::DecoupleEntrances, ON },
                                      // Shuffle Settings
                                      { &Settings::ShuffleRewards, REWARDSHUFFLE_ANYWHERE },
                                      { &Settings::LinksPocketItem, LINKSPOCKETITEM_ANYTHING },
                                      { &Settings::ShuffleSongs, SONGSHUFFLE_ANYWHERE },
                                      { &Settings::Shopsanity, SHOPSANITY_FOUR },
                                      { &Settings::Tokensanity, TOKENSANITY_ALL_TOKENS },
                                      { &Settings::Scrubsanity, SCRUBSANITY_AFFORDABLE },
                                      { &Settings::ShuffleCows, ON },
                                      { &Settings::ShuffleKokiriSword, ON },
                                      { &Settings::ShuffleMasterSword, ON },
                                      { &Settings::ShuffleOcarinas, ON },
                                      { &Settings::ShuffleWeirdEgg, ON },
                                      { &Settings::ShuffleGerudoToken, ON },
                                      { &Settings::ShuffleMagicBeans, ON },
                                      { &Settings::ShuffleMerchants, SHUFFLEMERCHANTS_HINTS },
                                      { &Settings::ShuffleAdultTradeQuest, ON },
                                      { &Settings::ShuffleChestMinigame, SHUFFLECHESTMINIGAME_SINGLE_KEYS },
                                      { &Settings::ShuffleFrogSongRupees, ON },
                                      // Shuffle Dungeon Items
                                      { &Settings::MapsAndCompasses, MAPSANDCOMPASSES_ANYWHERE },
                                      { &Settings::Keysanity, KEYSANITY_ANYWHERE },
                                      { &Settings::GerudoKeys, GERUDOKEYS_ANYWHERE },
                                      { &Settings::BossKeysanity, BOSSKEYSANITY_ANYWHERE },
                                      { &Settings::GanonsBossKey, GANONSBOSSKEY_ANYWHERE },
                                  } };

PremadePreset presetRacing = { "Racing",
                               presetRacingDesc,
                               {
                                   // Open Settings
                                   { &Settings::OpenForest, OPENFOREST_OPEN },
                                   { &Settings::OpenKakariko, OPENKAKARIKO_OPEN },
                                   { &Settings::OpenDoorOfTime, OPENDOOROFTIME_OPEN },
                                   { &Settings::ZorasFountain, ZORASFOUNTAIN_NORMAL },
                                   { &Settings::GerudoFortress, GERUDOFORTRESS_FAST },
                                   { &Settings::Bridge, RAINBOWBRIDGE_MEDALLIONS },
                                   { &Settings::BridgeMedallionCount, 6 },
                                   { &Settings::RandomGanonsTrials, OFF },
                                   { &Settings::GanonsTrialsCount, 0 },
                                   // World Settings
                                   { &Settings::StartingAge, AGE_ADULT },
                                   { &Settings::ShuffleEntrances, ON },
                                   { &Settings::ShuffleDungeonEntrances, SHUFFLEDUNGEONS_ON },
                                   { &Settings::BombchusInLogic, OFF },
                                   { &Settings::AmmoDrops, AMMODROPS_VANILLA },
                                   // Shuffle Settings
                                   { &Settings::ShuffleRewards, REWARDSHUFFLE_ANYWHERE },
                                   { &Settings::Tokensanity, TOKENSANITY_DUNGEONS },
                                   { &Settings::ShuffleKokiriSword, ON },
                                   { &Settings::MapsAndCompasses, MAPSANDCOMPASSES_START_WITH },
                                   { &Settings::GanonsBossKey, GANONSBOSSKEY_LACS_DUNGEONS },
                                   { &Settings::LACSDungeonCount, 5 },
                                   // Timesaver Settings
                                   { &Settings::SkipChildStealth, SKIP },
                                   { &Settings::SkipTowerEscape, SKIP },
                                   { &Settings::SkipEponaRace, SKIP },
                                   { &Settings::SkipMinigamePhases, SKIP },
                                   { &Settings::FreeScarecrow, ON },
                                   { &Settings::FourPoesCutscene, SKIP },
                                   { &Settings::LakeHyliaOwl, SKIP },
                                   { &Settings::BigPoeTargetCount, 0 }, // Index 0 is 1 poe
                                   { &Settings::NumRequiredCuccos, 3 },
                                   { &Settings::KingZoraSpeed, KINGZORASPEED_FAST },
                                   { &Settings::CompleteMaskQuest, ON },
                                   { &Settings::FastBunnyHood, ON },
                                   // Logical Tricks
                                   { &Settings::LogicGrottosWithoutAgony, ON },
                                   { &Settings::LogicVisibleCollision, ON },
                                   { &Settings::LogicFewerTunicRequirements, ON },
                                   { &Settings::LogicLostWoodsGSBean, ON },
                                   { &Settings::LogicLabDiving, ON },
                                   { &Settings::LogicManOnRoof, ON },
                                   { &Settings::LogicWindmillPoHHookshot, ON },
                                   { &Settings::LogicCraterBeanPoHWithHovers, ON },
                                   { &Settings::LogicDCJump, ON },
                                   { &Settings::LogicChildDeadhand, ON },
                                   { &Settings::LogicLensSpirit, ON },
                                   { &Settings::LogicLensShadow, ON },
                                   { &Settings::LogicLensShadowBack, ON },
                                   { &Settings::LogicLensBotw, ON },
                                   { &Settings::LogicLensGtg, ON },
                                   { &Settings::LogicLensCastle, ON },
                                   { &Settings::LogicLensJabuMQ, ON },
                                   { &Settings::LogicLensSpiritMQ, ON },
                                   { &Settings::LogicLensShadowMQ, ON },
                                   { &Settings::LogicLensShadowMQBack, ON },
                                   { &Settings::LogicLensBotwMQ, ON },
                                   { &Settings::LogicLensGtgMQ, ON },
                                   { &Settings::LogicFlamingChests, ON },
                                   // Starting Inventory
                                   { &Settings::StartingOcarina, 1 }, // Fairy Ocarina
                                   { &Settings::StartingKokiriSword, ON },
                                   { &Settings::StartingDekuShield, ON },
                                   { &Settings::StartingHylianShield, ON },
                                   { &Settings::StartingConsumables, ON },
                                   // Misc Settings
                                   { &Settings::Racing, ON },
                                   { &Settings::GossipStoneHints, HINTS_NEED_NOTHING },
                                   { &Settings::ClearerHints, HINTMODE_CLEAR },
                                   { &Settings::HintDistribution, HINTDISTRIBUTION_STRONG },
                                   { &Settings::CompassesShowReward, OFF },
                                   { &Settings::CompassesShowWotH, OFF },
                                   { &Settings::MapsShowDungeonMode, ON },
                                   { &Settings::StartingTime, STARTINGTIME_NIGHT },
                                   { &Settings::ChestAnimations, CHESTANIMATIONS_ALWAYSFAST },
                                   { &Settings::ChestAppearance, CHESTAPPEARANCE_TEXTURE },
                                   { &Settings::GenerateSpoilerLog, OFF },
                                   { &Settings::RandomTrapDmg, RANDOMTRAPS_OFF },
                                   // Item Pool Settings
                                   { &Settings::IceTrapValue, ICETRAPS_OFF },
                               },
                               {
                                   // Excluded Locations
                                   KAK_40_GOLD_SKULLTULA_REWARD,
                                   KAK_50_GOLD_SKULLTULA_REWARD,
                               } };

PremadePreset presetVanilla = { "Vanilla Plus",
                                presetVanillaDesc,
                                {
                                    // Open Settings
                                    { &Settings::OpenForest, OPENFOREST_CLOSED },
                                    { &Settings::OpenKakariko, OPENKAKARIKO_CLOSED },
                                    { &Settings::OpenDoorOfTime, OPENDOOROFTIME_INTENDED },
                                    { &Settings::ZorasFountain, ZORASFOUNTAIN_NORMAL },
                                    { &Settings::OpenJabu, JABUJABU_CLOSED },
                                    { &Settings::GerudoFortress, GERUDOFORTRESS_NORMAL },
                                    { &Settings::Bridge, RAINBOWBRIDGE_MEDALLIONS },
                                    { &Settings::BridgeMedallionCount, 6 },
                                    { &Settings::RandomGanonsTrials, OFF },
                                    { &Settings::GanonsTrialsCount, 6 },
                                    // Timesaver Settings
                                    { &Settings::SkipChildStealth, DONT_SKIP },
                                    { &Settings::SkipTowerEscape, DONT_SKIP },
                                    { &Settings::SkipEponaRace, DONT_SKIP },
                                    { &Settings::SkipMinigamePhases, SKIP },
                                    { &Settings::FreeScarecrow, OFF },
                                    { &Settings::FourPoesCutscene, SKIP },
                                    { &Settings::LakeHyliaOwl, SKIP },
                                    { &Settings::BigPoeTargetCount, 0 }, // Index 0 is 1 poe
                                    { &Settings::NumRequiredCuccos, 1 },
                                    { &Settings::KingZoraSpeed, KINGZORASPEED_FAST },
                                    { &Settings::CompleteMaskQuest, OFF },
                                    { &Settings::KeepFWWarpPoint, ON },
                                    { &Settings::FastBunnyHood, ON },
                                    // Logic Options
                                    { &Settings::Logic, LOGIC_VANILLA },
                                    // Item Usability Settings
                                    { &Settings::FaroresWindAnywhere, ON },
                                } };

PremadePreset presetFullChaos = { "Full Chaos",
                                  presetFullChaosDesc,
                                  {
                                      // Open Settings
                                      { &Settings::OpenForest, OPENFOREST_CLOSED },
                                      { &Settings::OpenKakariko, OPENKAKARIKO_CLOSED },
                                      { &Settings::OpenDoorOfTime, OPENDOOROFTIME_INTENDED },
                                      { &Settings::ZorasFountain, ZORASFOUNTAIN_NORMAL },
                                      { &Settings::OpenJabu, JABUJABU_CLOSED },
                                      { &Settings::GerudoFortress, GERUDOFORTRESS_NORMAL },
                                      { &Settings::Bridge, RAINBOWBRIDGE_TOKENS },
                                      { &Settings::BridgeTokenCount, 100 },
                                      { &Settings::RandomGanonsTrials, OFF },
                                      { &Settings::GanonsTrialsCount, 6 },
                                      // World Settings
                                      { &Settings::StartingAge, AGE_CHILD },
                                      { &Settings::ShuffleEntrances, ON },
                                      { &Settings::ShuffleDungeonEntrances,
                                        SHUFFLEDUNGEONS_ON }, // Including Ganon's Castle could make it too easy
                                      { &Settings::ShuffleOverworldEntrances, ON },
                                      { &Settings::ShuffleInteriorEntrances, SHUFFLEINTERIORS_ALL },
                                      { &Settings::ShuffleGrottoEntrances, ON },
                                      { &Settings::ShuffleOwlDrops, ON },
                                      { &Settings::ShuffleWarpSongs, ON },
                                      { &Settings::ShuffleOverworldSpawns, ON },
                                      { &Settings::MixedEntrancePools, ON },
                                      { &Settings::MixDungeons, ON },
                                      { &Settings::MixOverworld, ON },
                                      { &Settings::MixInteriors, ON },
                                      { &Settings::MixGrottos, ON },
                                      { &Settings::DecoupleEntrances, ON },
                                      { &Settings::AmmoDrops, AMMODROPS_NONE },
                                      { &Settings::HeartDropRefill, HEARTDROPREFILL_NODROPREFILL },
                                      { &Settings::MQDungeonCount, 13 }, // Random

                                      // Shuffle Settings
                                      { &Settings::ShuffleRewards, REWARDSHUFFLE_ANYWHERE },
                                      { &Settings::LinksPocketItem, LINKSPOCKETITEM_ANYTHING },
                                      { &Settings::ShuffleSongs, SONGSHUFFLE_ANYWHERE },
                                      { &Settings::Shopsanity, SHOPSANITY_FOUR },
                                      { &Settings::Tokensanity, TOKENSANITY_ALL_TOKENS },
                                      { &Settings::Scrubsanity, SCRUBSANITY_RANDOM_PRICES },
                                      { &Settings::ShuffleCows, ON },
                                      { &Settings::ShuffleKokiriSword, ON },
                                      { &Settings::ShuffleMasterSword, ON },
                                      { &Settings::ShuffleOcarinas, ON },
                                      { &Settings::ShuffleWeirdEgg, ON },
                                      { &Settings::ShuffleGerudoToken, ON },
                                      { &Settings::ShuffleMagicBeans, ON },
                                      { &Settings::ShuffleMerchants, SHUFFLEMERCHANTS_NO_HINTS },
                                      { &Settings::ShuffleAdultTradeQuest, ON },
                                      { &Settings::ShuffleChestMinigame, SHUFFLECHESTMINIGAME_SINGLE_KEYS },
                                      { &Settings::ShuffleFrogSongRupees, ON },
                                      // Shuffle Dungeon Items
                                      { &Settings::MapsAndCompasses, MAPSANDCOMPASSES_ANYWHERE },
                                      { &Settings::Keysanity, KEYSANITY_ANYWHERE },
                                      { &Settings::GerudoKeys, GERUDOKEYS_ANYWHERE },
                                      { &Settings::BossKeysanity, BOSSKEYSANITY_ANYWHERE },
                                      { &Settings::GanonsBossKey, GANONSBOSSKEY_ANYWHERE },
                                      // Timesaver Settings
                                      { &Settings::SkipChildStealth, DONT_SKIP },
                                      { &Settings::SkipTowerEscape, DONT_SKIP },
                                      { &Settings::SkipEponaRace, DONT_SKIP },
                                      { &Settings::SkipMinigamePhases, DONT_SKIP },
                                      { &Settings::FreeScarecrow, OFF },
                                      { &Settings::BigPoeTargetCount, 9 }, // Index 9 is 10 poes
                                      { &Settings::NumRequiredCuccos, 7 },
                                      { &Settings::KingZoraSpeed, KINGZORASPEED_CUSTOM },
                                      { &Settings::ExactZoraSpeed, 127 }, // Index 127 is 128 mweeps

                                      // Logic Options
                                      { &Settings::Logic, LOGIC_NONE },
                                      // Starting Inventory
                                      { &Settings::StartingHearts, 0 },
                                      // Misc Settings
                                      { &Settings::GossipStoneHints, HINTS_NEED_NOTHING },
                                      { &Settings::ClearerHints, HINTMODE_CLEAR },
                                      { &Settings::HintDistribution, HINTDISTRIBUTION_USELESS },
                                      { &Settings::CompassesShowReward, OFF },
                                      { &Settings::CompassesShowWotH, OFF },
                                      { &Settings::MapsShowDungeonMode, OFF },
                                      { &Settings::DamageMultiplier, DAMAGEMULTIPLIER_OHKO },
                                      { &Settings::Permadeath, ON },
                                      { &Settings::RandomTrapDmg, RANDOMTRAPS_ADVANCED },
                                      { &Settings::FireTrap, ON },
                                      { &Settings::AntiFairyTrap, ON },
                                      { &Settings::CurseTraps, ON },
                                      { &Settings::HyperActors, HYPERACTORS_ON },
                                      // Item Pool Settings
                                      { &Settings::IceTrapValue, ICETRAPS_ONSLAUGHT },
                                      { &Settings::RemoveDoubleDefense, OFF },
                                      { &Settings::ProgressiveGoronSword, ON },
                                      // Item Usability Settings
                                      { &Settings::RestoreISG, OFF },
                                      { &Settings::GkDurability, GKDURABILITY_RANDOMRISK },
                                  } };

std::vector<PremadePreset*> premadePresets = {
    &presetNintended, &presetAllsanity, &presetRacing, &presetVanilla, &presetFullChaos,
};
