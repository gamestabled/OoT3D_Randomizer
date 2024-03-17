#include <3ds.h>
#include <dirent.h>

#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>

#include "cosmetics.hpp"
#include "menu.hpp"
#include "patch.hpp"
#include "preset.hpp"
#include "randomizer.hpp"
#include "settings.hpp"
#include "spoiler_log.hpp"
#include "location_access.hpp"
#include "debug.hpp"
#include "music.hpp"

namespace {
bool seedChanged;
bool chosePlayOption;
u16 pastSeedLength;
PrintConsole topScreen, bottomScreen;
std::vector<std::string> presetEntries;
std::vector<Menu*> menuList;
Option* currentSetting;
Menu* currentMenu;
} // namespace

void PrintTopScreen() {
    consoleSelect(&topScreen);
    consoleClear();
    printf("\x1b[2;11H%sOcarina of Time 3D Randomizer%s", CYAN, RESET);
    printf("\x1b[3;18H%s%s-%s%s", CYAN, RANDOMIZER_VERSION, COMMIT_NUMBER, RESET);
    printf("\x1b[4;10HA/B/D-pad: Navigate Menu\n");
    printf("            Select: Exit to Homebrew Menu\n");
    printf("                 Y: New Random Seed\n");
    printf("                 X: Input Custom Seed\n");
    printf("\x1b[11;7HCurrent Seed: %s", Settings::seed.c_str());
}

void MenuInit() {
    Settings::InitSettings();

    seedChanged     = false;
    chosePlayOption = false;
    pastSeedLength  = Settings::seed.length();

    Menu* main = new Menu("Main", MenuType::MainMenu, &Settings::mainMenu, MAIN_MENU);
    menuList.push_back(main);
    currentMenu = main;

    srand(time(NULL));
    consoleInit(GFX_TOP, &topScreen);
    consoleInit(GFX_BOTTOM, &bottomScreen);

    consoleSelect(&topScreen);

    // Create directories
    FS_Archive sdmcArchive;
    if (R_SUCCEEDED(FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) {
        CreateLogDirectories(sdmcArchive);
        CreatePresetDirectories(sdmcArchive);
        Music::CreateMusicDirectories(sdmcArchive);

        FSUSER_CloseArchive(sdmcArchive);
    } else {
        consoleClear();
        printf("\x1b[10;10HFailed to create directories.");
        printf("\x1b[11;10H- Spoiler logs won't be written.");
        printf("\x1b[12;10H- Loading presets might crash.");
        printf("\x1b[13;10H- Custom music will fail.");
        printf("\x1b[15;10HPress B to continue.");

        while (aptMainLoop()) {
            hidScanInput();
            if (hidKeysHeld() & KEY_B) {
                break;
            }
        }
    }

    // If cached presets exist, load them
    LoadCachedSettings();
    LoadCachedCosmetics();
    // If Randomize all settings in a category is selected
    // Re-randomize them
    Settings::RandomizeAllSettings();

    PrintTopScreen();

    consoleSelect(&bottomScreen);
    PrintMainMenu();
}

void MoveCursor(u32 kDown, bool updatedByHeld) {
    // Option sub menus need special checking for locked options
    if (currentMenu->mode == OPTION_MENU) {
        // Cancel if holding and reached first/last selectable option
        if (updatedByHeld) {
            bool noSelectableOption = true;
            if (kDown & KEY_UP) {
                for (int i = currentMenu->menuIdx - 1; i >= 0; i--) {
                    if (!currentMenu->settingsList->at(i)->IsHidden() &&
                        !currentMenu->settingsList->at(i)->IsLocked()) {
                        noSelectableOption = false;
                        break;
                    }
                }
            }
            if (kDown & KEY_DOWN) {
                for (size_t i = currentMenu->menuIdx + 1; i < currentMenu->settingsList->size(); i++) {
                    if (!currentMenu->settingsList->at(i)->IsHidden() &&
                        !currentMenu->settingsList->at(i)->IsLocked()) {
                        noSelectableOption = false;
                        break;
                    }
                }
            }
            if (noSelectableOption) {
                return;
            }
        }
        // Loop through settings until an unlocked one is reached
        do {
            if ((kDown & KEY_UP) != 0) {
                currentMenu->menuIdx--;
            }
            if ((kDown & KEY_DOWN) != 0) {
                currentMenu->menuIdx++;
            }

            // Bounds checking
            if (currentMenu->menuIdx == currentMenu->settingsList->size()) {
                currentMenu->menuIdx = 0;
            } else if (currentMenu->menuIdx == 0xFFFF) {
                currentMenu->menuIdx = static_cast<u16>(currentMenu->settingsList->size() - 1);
            }

            currentSetting = currentMenu->settingsList->at(currentMenu->menuIdx);
        } while (currentSetting->IsLocked() || currentSetting->IsHidden());
    }
    // All other menus except reset-to-defaults confirmation
    else if (currentMenu->mode != RESET_TO_DEFAULTS) {
        u16 max = -1;
        if (currentMenu->mode == LOAD_PREMADE_PRESET) {
            max = premadePresets.size();
        } else if (currentMenu->mode == LOAD_CUSTOM_PRESET ||
                   currentMenu->mode == DELETE_CUSTOM_PRESET) { // Number of presets if applicable
            max = presetEntries.size();
        } else if (currentMenu->mode == GENERATE_MODE) { // Generate menu: 2 options
            max = 2;
        } else if (currentMenu->itemsList != nullptr) {
            max = currentMenu->itemsList->size(); // Default max: Number of items in menu
        }

        // Cancel if holding and reached first/last menu
        if (updatedByHeld) {
            if ((kDown & KEY_UP && currentMenu->menuIdx == 0) ||
                (kDown & KEY_DOWN && currentMenu->menuIdx == max - 1)) {
                return;
            }
        }

        if (kDown & KEY_UP) {
            currentMenu->menuIdx--;
        }
        if (kDown & KEY_DOWN) {
            currentMenu->menuIdx++;
        }

        // Bounds checking
        if (currentMenu->menuIdx == max) {
            currentMenu->menuIdx = 0;
        } else if (currentMenu->menuIdx == 0xFFFF) {
            currentMenu->menuIdx = max - 1;
        }

        // Scroll Check
        u16 max_entries_on_screen = MAX_SUBMENUS_ON_SCREEN;
        if (currentMenu->mode == LOAD_CUSTOM_PRESET || currentMenu->mode == DELETE_CUSTOM_PRESET) {
            max_entries_on_screen = MAX_SUBMENU_SETTINGS_ON_SCREEN;
        }
        if (currentMenu->menuIdx >
            currentMenu->settingBound + (max_entries_on_screen - (currentMenu->menuIdx == max - 1 ? 1 : 2))) {
            currentMenu->settingBound =
                currentMenu->menuIdx - (max_entries_on_screen - (currentMenu->menuIdx == max - 1 ? 1 : 2));
        } else if (currentMenu->menuIdx < currentMenu->settingBound + 1) {
            currentMenu->settingBound = std::max(currentMenu->menuIdx - 1, 0);
        }

        // Shared cursor for preset menus
        if (currentMenu->mode == LOAD_CUSTOM_PRESET) {
            Settings::deleteCustomPreset.settingBound = currentMenu->settingBound;
            Settings::deleteCustomPreset.menuIdx      = currentMenu->menuIdx;
        } else if (currentMenu->mode == DELETE_CUSTOM_PRESET) {
            Settings::loadCustomPreset.settingBound = currentMenu->settingBound;
            Settings::loadCustomPreset.menuIdx      = currentMenu->menuIdx;
        }
    }
}

void MenuUpdate(u32 kDown, bool updatedByHeld, u32 kHeld) {
    consoleSelect(&bottomScreen);
    if (currentMenu->mode != POST_GENERATE || (kDown & KEY_B)) {
        // Don't clear console if ValidateSettings printed error
        consoleClear();
    }

    // Check for menu change
    // If user pressed A on a non-option, non-action menu, they're navigating to a new menu
    if (kDown & KEY_A && currentMenu->mode != OPTION_MENU && currentMenu->type != MenuType::Action) {
        if (currentMenu->itemsList->size() > currentMenu->menuIdx) {
            Menu* newMenu;
            newMenu = currentMenu->itemsList->at(currentMenu->menuIdx);
            menuList.push_back(newMenu);
            currentMenu = menuList.back();
            ModeChangeInit();
            kDown = 0;
        }
        // If they pressed B on any menu other than main, go backwards to the previous menu
    } else if (kDown & KEY_B && currentMenu->mode != MAIN_MENU && !chosePlayOption) {
        // Want to reset generate menu when leaving
        if (currentMenu->mode == POST_GENERATE) {
            currentMenu->mode = GENERATE_MODE;
        }
        consoleSelect(&topScreen);
        PrintTopScreen();
        menuList.pop_back();
        currentMenu = menuList.back();
        ModeChangeInit();
        kDown = 0;
    }

    if (currentMenu->mode != POST_GENERATE) {

        // New Random Seed
        if (kDown & KEY_Y) {
            pastSeedLength = Settings::seed.length();
            Settings::seed = std::to_string(rand());
            seedChanged    = true;
        }

        // Input Custom Seed
        if (kDown & KEY_X) {
            pastSeedLength = Settings::seed.length();
            Settings::seed = GetInput("Enter Seed");
            seedChanged    = true;
        }

        // Reprint seed if it changed
        if (seedChanged) {
            std::string spaces = "";
            spaces.append(pastSeedLength, ' ');
            consoleSelect(&topScreen);
            printf("\x1b[11;21H%s", spaces.c_str());
            printf("\x1b[11;21H%s", Settings::seed.c_str());
            seedChanged = false;
        }
    }

    // Print current menu (if applicable)
    consoleSelect(&bottomScreen);
    MoveCursor(kDown, updatedByHeld); // Move cursor, if applicable
    if (currentMenu->mode == MAIN_MENU) {
        PrintMainMenu();
    } else if (currentMenu->mode == OPTION_MENU) {
        UpdateOptionSubMenu(kDown, kHeld);
        PrintOptionSubMenu();
    } else if (currentMenu->mode == LOAD_PREMADE_PRESET) {
        UpdatePremadePresetsMenu(kDown);
        PrintPremadePresetsMenu(kDown);
    } else if (currentMenu->mode == LOAD_CUSTOM_PRESET) {
        UpdateCustomPresetsMenu(kDown);
        PrintCustomPresetsMenu();
    } else if (currentMenu->mode == DELETE_CUSTOM_PRESET) {
        UpdateCustomPresetsMenu(kDown);
        PrintCustomPresetsMenu();
    } else if (currentMenu->mode == RESET_TO_DEFAULTS) {
        UpdateResetToDefaultsMenu(kDown);
        PrintResetToDefaultsMenu();
    } else if (currentMenu->mode == GENERATE_MODE) {
        UpdateGenerateMenu(kDown);
        if (currentMenu->mode != POST_GENERATE) {
            PrintGenerateMenu();
        }
    } else if (currentMenu->mode == SUB_MENU) {
        PrintSubMenu();
    }
}

void ModeChangeInit() {
    if (currentMenu->mode == OPTION_MENU) {
        // loop through until we reach an unlocked setting
        while (currentMenu->settingsList->at(currentMenu->menuIdx)->IsLocked() ||
               currentMenu->settingsList->at(currentMenu->menuIdx)->IsHidden()) {
            currentMenu->menuIdx++;
            if (currentMenu->menuIdx >= currentMenu->settingsList->size()) {
                currentMenu->menuIdx = 0;
            }
        }
        currentSetting = currentMenu->settingsList->at(currentMenu->menuIdx);

    } else if (currentMenu->mode == SAVE_CUSTOM_PRESET) {
        ClearDescription();
        if (SaveSpecifiedPreset(GetInput("Preset Name").substr(0, 19), OptionCategory::Setting)) {
            printf("\x1b[24;5HPreset Saved!");
            printf("\x1b[26;5HPress B to return to the preset menu.");
        } else {
            printf("\x1b[24;5HFailed to save preset.");
            printf("\x1b[26;5HPress B to return to the preset menu.");
        }

    } else if (currentMenu->mode == LOAD_CUSTOM_PRESET || currentMenu->mode == DELETE_CUSTOM_PRESET) {
        presetEntries = GetSettingsPresets();

    } else if (currentMenu->mode == GENERATE_MODE) {
    }
}

void UpdateCustomCosmeticColors(u32 kDown) {
    if (kDown & KEY_A) {
        if (currentSetting->GetSelectedOptionText().compare(0, 8, Cosmetics::CUSTOM_COLOR_PREFIX) == 0) {
            std::string newColor = GetInput("Enter a 6 digit hex color").substr(0, 6);
            if (Cosmetics::ValidHexString(newColor)) {
                currentSetting->SetSelectedOptionText(Cosmetics::CustomColorOptionText(newColor));
            }
        }
    }
}

void UpdateOptionSubMenu(u32 kDown, u32 kHeld) {
    bool fastScrolling = kHeld & KEY_A;
    currentSetting->ScrollOptionIndex(kDown, fastScrolling);
    currentSetting->SetVariable();
    Settings::ForceChange(kDown, currentSetting);
    UpdateCustomCosmeticColors(kDown);
}

void UpdatePremadePresetsMenu(u32 kDown) {
    consoleSelect(&topScreen);
    if (kDown & KEY_A) {
        Settings::SetDefaultSettings();
        for (auto optionOverride : premadePresets[currentMenu->menuIdx]->optionOverrides) {
            optionOverride.first->SetSelectedIndex(optionOverride.second);
        }
        for (auto loc : premadePresets[currentMenu->menuIdx]->excludedLocations) {
            Location(loc)->GetExcludedOption()->SetSelectedIndex(EXCLUDE);
        }
        Settings::ResolveExcludedLocationConflicts();
        for (Menu* menu : Settings::GetAllOptionMenus()) {
            menu->ResetMenuIndex();
        }
        ClearDescription();
        printf("\x1b[24;5HPreset Loaded!");
    }
}

void UpdateCustomPresetsMenu(u32 kDown) {
    consoleSelect(&topScreen);
    // clear any potential message
    ClearDescription();
    if (kDown & KEY_A && currentMenu->mode == LOAD_CUSTOM_PRESET && !presetEntries.empty()) {
        Settings::SetDefaultSettings();
        if (LoadPreset(presetEntries[currentMenu->menuIdx], OptionCategory::Setting)) {
            Settings::ResolveExcludedLocationConflicts();
            for (Menu* menu : Settings::GetAllOptionMenus()) {
                menu->ResetMenuIndex();
            }
            printf("\x1b[24;5HPreset Loaded!");
        } else {
            printf("\x1b[24;5HFailed to load preset.");
        }
    } else if (kDown & KEY_A && currentMenu->mode == DELETE_CUSTOM_PRESET && !presetEntries.empty()) {
        if (DeletePreset(presetEntries[currentMenu->menuIdx], OptionCategory::Setting)) {
            presetEntries.erase(presetEntries.begin() + currentMenu->menuIdx);
            if (currentMenu->menuIdx == presetEntries.size()) { // Catch when last preset is deleted
                currentMenu->menuIdx--;
            }
            printf("\x1b[24;5HPreset Deleted.");
        } else {
            printf("\x1b[24;5HFailed to delete preset.");
        }
    }
}

void UpdateResetToDefaultsMenu(u32 kDown) {
    consoleSelect(&topScreen);
    // clear any potential message
    ClearDescription();
    if (kDown & KEY_A) {
        Settings::SetDefaultSettings();
        printf("\x1b[24;7HSettings have been reset to defaults.");
    }
}

void UpdateGenerateMenu(u32 kDown) {
    if (!chosePlayOption) {
        if ((kDown & KEY_A) != 0) {
            Settings::PlayOption = currentMenu->menuIdx;
            consoleSelect(&bottomScreen);
            consoleClear();
            chosePlayOption = true;
        }
    } else {
        if ((kDown & KEY_B) != 0) {
            consoleSelect(&bottomScreen);
            consoleClear();
            chosePlayOption = false;
        } else if ((kDown & KEY_A) != 0) {
            Settings::Region = currentMenu->menuIdx;
            consoleSelect(&bottomScreen);
            consoleClear();
            GenerateRandomizer();
            // This is just a dummy mode to stop the prompt from appearing again
            currentMenu->mode = POST_GENERATE;
            chosePlayOption   = false;
        }
    }
}

void PrintMainMenu() {
    printf("\x1b[0;%dHMain Settings", 1 + (BOTTOM_WIDTH - 13) / 2);

    for (u8 i = 0; i < MAX_SUBMENUS_ON_SCREEN; i++) {
        if (i >= Settings::mainMenu.size())
            break;

        Menu* menu = Settings::mainMenu[i];

        u8 row = 3 + i;
        // make the current menu green
        if (currentMenu->menuIdx == i) {
            printf("\x1b[%d;%dH%s>", row, 2, GREEN);
            printf("\x1b[%d;%dH%s%s", row, 3, menu->name.c_str(), RESET);
        } else {
            printf("\x1b[%d;%dH%s", row, 3, menu->name.c_str());
        }
    }

    PrintDescription(currentMenu->itemsList->at(currentMenu->menuIdx)->description);
}

void PrintOptionSubMenu() {
    // bounds checking incase settings go off screen
    // this is complicated to account for hidden settings and there's probably a better way to do it
    u16 hiddenSettings  = 0;
    u16 visibleSettings = 0;
    for (u16 i = currentMenu->settingBound; visibleSettings < MAX_SUBMENU_SETTINGS_ON_SCREEN; i++) {
        if (i >= currentMenu->settingsList->size()) {
            break;
        }
        if (currentMenu->settingsList->at(i)->IsHidden()) {
            hiddenSettings++;
        } else {
            visibleSettings++;
        }
    }
    bool isLastVisibleSetting = true;
    for (size_t i = currentMenu->menuIdx + 1; i < currentMenu->settingsList->size(); i++) {
        if (!currentMenu->settingsList->at(i)->IsHidden()) {
            isLastVisibleSetting = false;
            break;
        }
    }
    if (currentMenu->menuIdx >=
        currentMenu->settingBound - (isLastVisibleSetting ? 0 : 1) + MAX_SUBMENU_SETTINGS_ON_SCREEN + hiddenSettings) {
        currentMenu->settingBound = currentMenu->menuIdx;
        u8 offset                 = 0;
        // skip over hidden settings
        while (offset < MAX_SUBMENU_SETTINGS_ON_SCREEN - (isLastVisibleSetting ? 1 : 2)) {
            currentMenu->settingBound--;
            if (currentMenu->settingBound == 0) {
                break;
            }
            offset += currentMenu->settingsList->at(currentMenu->settingBound)->IsHidden() ? 0 : 1;
        }
    } else if (currentMenu->menuIdx < currentMenu->settingBound + 1) {
        currentMenu->settingBound = std::max(currentMenu->menuIdx - 1, 0);
    }

    // print menu name
    printf("\x1b[0;%dH%s", 1 + (BOTTOM_WIDTH - currentMenu->name.length()) / 2, currentMenu->name.c_str());

    // keep count of hidden settings to not make blank spaces appear in the list
    hiddenSettings = 0;

    for (u8 i = 0; i - hiddenSettings < MAX_SUBMENU_SETTINGS_ON_SCREEN; i++) {
        // break if there are no more settings to print
        if (i + currentMenu->settingBound >= currentMenu->settingsList->size())
            break;

        Option* setting = currentMenu->settingsList->at(i + currentMenu->settingBound);

        u8 row = 3 + ((i - hiddenSettings) * 2);

        const auto PrintSettingAndOption = [&](std::string color) {
            size_t newlinePos;
            bool hasNewline;

            printf(color.data());

            // Selection Arrow
            if (color == GREEN) {
                printf("\x1b[%d;%dH>", row, 1);
            }

            // Setting
            newlinePos = setting->GetName().find('\n');
            hasNewline = newlinePos != std::string::npos;
            printf("\x1b[%d;%dH%.*s%s", row, 2 + setting->GetIndent(), newlinePos, setting->GetName().data(),
                   hasNewline ? "" : ":");
            if (hasNewline) {
                printf("\x1b[%d;%dH%s:", row + 1, 2 + setting->GetIndent(), setting->GetName().data() + newlinePos + 1);
            }

            // Option
            newlinePos = setting->GetSelectedOptionText().find('\n');
            hasNewline = newlinePos != std::string::npos;
            printf("\x1b[%d;%dH%.*s", row, 26, newlinePos, setting->GetSelectedOptionText().data());
            if (hasNewline) {
                printf("\x1b[%d;%dH%s", row + 1, 26, setting->GetSelectedOptionText().data() + newlinePos + 1);
            }

            printf(RESET);
        };

        // make the current setting green
        if (currentMenu->menuIdx == i + currentMenu->settingBound) {
            PrintSettingAndOption(GREEN);
        }
        // dim to make a locked setting grey
        else if (setting->IsLocked()) {
            PrintSettingAndOption(DIM);
        }
        // don't display hidden settings
        else if (setting->IsHidden()) {
            hiddenSettings++;
            continue;
        } else {
            PrintSettingAndOption(WHITE);
        }
    }

    PrintDescription(currentSetting->GetSelectedOptionDescription());
}

void PrintSubMenu() {
    printf("\x1b[0;%dH%s", 1 + (BOTTOM_WIDTH - currentMenu->name.length()) / 2, currentMenu->name.c_str());

    for (u8 i = 0; i < MAX_SUBMENUS_ON_SCREEN; i++) {
        if (i >= currentMenu->itemsList->size())
            break;

        u8 row = 3 + i;
        // make the current menu green
        if (currentMenu->menuIdx == currentMenu->settingBound + i) {
            printf("\x1b[%d;%dH%s>", row, 2, GREEN);
            printf("\x1b[%d;%dH%s%s", row, 3, currentMenu->itemsList->at(currentMenu->settingBound + i)->name.c_str(),
                   RESET);
        } else {
            printf("\x1b[%d;%dH%s", row, 3, currentMenu->itemsList->at(currentMenu->settingBound + i)->name.c_str());
        }
    }

    PrintDescription(currentMenu->itemsList->at(currentMenu->menuIdx)->description);
}

void PrintPremadePresetsMenu(u32 kDown) {
    consoleSelect(&bottomScreen);
    printf("\x1b[0;%dHSelect a Preset to Load", 1 + (BOTTOM_WIDTH - 23) / 2);

    for (u8 i = 0; i < MAX_SUBMENU_SETTINGS_ON_SCREEN; i++) {
        if (i + currentMenu->settingBound >= premadePresets.size())
            break;

        std::string preset = premadePresets[currentMenu->settingBound + i]->name.data();

        u8 row = 3 + (i * 2);
        // make the current preset green
        if (currentMenu->menuIdx == currentMenu->settingBound + i) {
            printf("\x1b[%d;%dH%s>", row, 14, GREEN);
            printf("\x1b[%d;%dH%s%s", row, 15, preset.c_str(), RESET);
        } else {
            printf("\x1b[%d;%dH%s", row, 15, preset.c_str());
        }
    }

    if (!(kDown & KEY_A)) {
        PrintDescription(premadePresets[currentMenu->menuIdx]->description);
    }
}

void PrintCustomPresetsMenu() {
    consoleSelect(&bottomScreen);
    if (presetEntries.empty()) {
        printf("\x1b[10;4HNo Presets Detected!");
        printf("\x1b[12;4HPress B to return to the preset menu.");
        return;
    }

    if (currentMenu->mode == LOAD_CUSTOM_PRESET) {
        printf("\x1b[0;%dHSelect a Preset to Load", 1 + (BOTTOM_WIDTH - 23) / 2);
    } else if (currentMenu->mode == DELETE_CUSTOM_PRESET) {
        printf("\x1b[0;%dHSelect a Preset to Delete", 1 + (BOTTOM_WIDTH - 25) / 2);
    }

    for (u8 i = 0; i < MAX_SUBMENU_SETTINGS_ON_SCREEN; i++) {
        if (i + currentMenu->settingBound >= presetEntries.size())
            break;

        std::string preset = presetEntries[currentMenu->settingBound + i];

        u8 row = 3 + (i * 2);
        // make the current preset green
        if (currentMenu->menuIdx == currentMenu->settingBound + i) {
            printf("\x1b[%d;%dH%s>", row, 14, GREEN);
            printf("\x1b[%d;%dH%s%s", row, 15, preset.c_str(), RESET);
        } else {
            printf("\x1b[%d;%dH%s", row, 15, preset.c_str());
        }
    }
}

void PrintResetToDefaultsMenu() {
    consoleSelect(&bottomScreen);
    printf("\x1b[10;2HPress A to reset to default settings.");
    printf("\x1b[12;2HPress B to return to the preset menu.");
}

void PrintGenerateMenu() {

    consoleSelect(&bottomScreen);

    if (!chosePlayOption) {
        printf("\x1b[3;%dHHow will you play?", 1 + (BOTTOM_WIDTH - 18) / 2);
        std::vector<std::string> playOptions = { "3ds Console", "Citra Emulator" };

        for (u8 i = 0; i < playOptions.size(); i++) {

            std::string option = playOptions[i];
            u8 row             = 6 + (i * 2);
            // make the current selection green
            if (currentMenu->menuIdx == i) {
                printf("\x1b[%d;%dH%s>", row, 14, GREEN);
                printf("\x1b[%d;%dH%s%s", row, 15, option.c_str(), RESET);
            } else {
                printf("\x1b[%d;%dH%s", row, 15, option.c_str());
            }
        }
    } else {
        printf("\x1b[3;%dHSelect your game region", 1 + (BOTTOM_WIDTH - 18) / 2);
        std::vector<std::string> regionOptions = { "North America (33500)", "Europe (33600)" };

        for (u8 i = 0; i < regionOptions.size(); i++) {

            std::string option = regionOptions[i];
            u8 row             = 6 + (i * 2);
            // make the current selection green
            if (currentMenu->menuIdx == i) {
                printf("\x1b[%d;%dH%s>", row, 14, GREEN);
                printf("\x1b[%d;%dH%s%s", row, 15, option.c_str(), RESET);
            } else {
                printf("\x1b[%d;%dH%s", row, 15, option.c_str());
            }
        }
    }
}

void ClearDescription() {
    consoleSelect(&topScreen);

    // clear the previous description
    std::string spaces = "";
    spaces.append(11 * TOP_WIDTH, ' ');
    printf("\x1b[20;0H%s", spaces.c_str());
}

void PrintDescription(std::string_view description) {
    ClearDescription();
    printf("\x1b[20;0H%s", description.data());
}

static void RestoreOverrides() {
    if (Settings::Racing) {
        for (auto overridePair : Settings::racingOverrides) {
            overridePair.first->RestoreDelayedOption();
        }
    }

    if (Settings::Logic.Is(LOGIC_VANILLA)) {
        for (auto overridePair : Settings::vanillaLogicOverrides) {
            overridePair.first->RestoreDelayedOption();
        }
    }

    // Reload Cosmetic settings because Random Choice options might have been changed during generation
    LoadCachedCosmetics();
}

void GenerateRandomizer() {

    if (!Settings::ValidateSettings()) {
        return;
    }

    consoleSelect(&topScreen);
    consoleClear();
    printf("\x1b[6;10HCaching Settings...");

    // After choosing to generate, cache chosen settings for later
    SaveCachedSettings();
    SaveCachedCosmetics();
    printf("Done");

    // if a blank seed was entered, make a random one
    if (Settings::seed.empty()) {
        Settings::seed = std::to_string(rand());
    } else if (Settings::seed.rfind("seed_testing_count", 0) == 0) {
        const int count = std::stoi(Settings::seed.substr(18), nullptr);
        Playthrough::Playthrough_Repeat(count);
        return;
    }

    int ret = Playthrough::Playthrough_Init(std::hash<std::string>{}(Settings::seed));
    if (ret < 0) {
        if (ret == -1) { // Failed to generate after 5 tries
            printf("\n\nFailed to generate after 5 tries.\nPress B to go back to the menu.\nA different seed might be "
                   "successful.");
            PlacementLog_Msg("\nRANDOMIZATION FAILED COMPLETELY. PLZ FIX\n");
            PlacementLog_Write();
            RestoreOverrides();
            return;
        } else {
            printf("\n\nError %d with fill.\nPress Select to exit or B to go back to the menu.\n", ret);
            RestoreOverrides();
            return;
        }
    }

    if (Settings::ShuffleMusic) {
        printf("\x1b[12;10HShuffling Music...");
        auto musicRes = Music::ShuffleMusic_Archive();
        if (musicRes == Music::SARSHUFFLE_SUCCESS) {
            printf("Done");
        } else {
            if (musicRes == Music::SARSHUFFLE_BCSAR_NOT_FOUND && !Settings::CustomMusic) {
                // Inform that the original music shuffle system is used
                printf("Legacy");
            } else {
                printf("Error %d", musicRes);
            }
        }
    }

    printf("\x1b[13;10HWriting Patch...");
    if (WriteAllPatches()) {
        printf("Done");
        if (Settings::PlayOption == PATCH_CONSOLE) {
            printf("\x1b[15;10HQuit out using the home menu. Then\n");
            printf("\x1b[16;10Henable game patching and launch OoT3D!\n");
        } else if (Settings::PlayOption == PATCH_CITRA) {
            printf("\x1b[15;10HCopy code.ips, exheader.bin and romfs to\n");
            printf("\x1b[16;10Hthe OoT3D mods folder, then launch OoT3D!\n");
        }

        const auto& randomizerHash = GetRandomizerHash();
        printf("\x1b[18;10HHash:");
        for (size_t i = 0; i < randomizerHash.size(); i++) {
            printf("\x1b[%zu;11H- %s", i + 19, randomizerHash[i].c_str());
        }
    } else {
        printf("Failed\nPress Select to exit.\n");
    }

    RestoreOverrides();
}

// opens up the 3ds software keyboard for getting user input
std::string GetInput(const char* hintText) {
    SwkbdState swkbd;
    char text[60];
    SwkbdButton button = SWKBD_BUTTON_NONE;

    swkbdInit(&swkbd, SWKBD_TYPE_WESTERN, 2, -1);
    swkbdSetValidation(&swkbd, SWKBD_NOTEMPTY_NOTBLANK,
                       SWKBD_FILTER_AT | SWKBD_FILTER_PERCENT | SWKBD_FILTER_BACKSLASH | SWKBD_FILTER_PROFANITY, 2);
    swkbdSetFeatures(&swkbd, SWKBD_MULTILINE);
    swkbdSetHintText(&swkbd, hintText);
    swkbdSetButton(&swkbd, SWKBD_BUTTON_LEFT, "Cancel", false);

    button = swkbdInputText(&swkbd, text, sizeof(text));

    if (button == SWKBD_BUTTON_LEFT) {
        return "";
    }

    return std::string(text);
}
