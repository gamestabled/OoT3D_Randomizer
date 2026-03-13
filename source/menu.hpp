#pragma once

#include <3ds.h>
#include <string>

#define MAIN_MENU 0
#define SUB_MENU 1
#define OPTION_MENU 2
#define GENERATE_MODE 3
#define LOAD_PREMADE_RANDOMIZATION_PRESET 4
#define LOAD_CUSTOM_RANDOMIZATION_PRESET 5
#define SAVE_CUSTOM_RANDOMIZATION_PRESET 6
#define DELETE_CUSTOM_RANDOMIZATION_PRESET 7
#define POST_GENERATE 8
#define RESET_TO_DEFAULT_RANDOMIZATION_SETTINGS 9
#define LOAD_CUSTOM_COSMETIC_PRESET 10
#define SAVE_CUSTOM_COSMETIC_PRESET 11
#define DELETE_CUSTOM_COSMETIC_PRESET 12
#define RESET_TO_DEFAULT_COSMETICS 13

#define MAX_SUBMENUS_ON_SCREEN 27
#define MAX_SUBMENU_SETTINGS_ON_SCREEN 13
#define TOP_WIDTH 50
#define BOTTOM_WIDTH 40
#define SCREEN_HEIGHT 30

#define RESET "\x1b[0m"
#define DIM "\x1b[2m"

#define BLACK "\x1b[30m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MEGANTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"

enum class PresetType {
    RANDOMIZATION,
    COSMETICS,
};

class Menu;

void ModeChangeInit();
void UpdateOptionSubMenu(u32 kDown, u32 kHeld);
void UpdatePremadePresetsMenu(u32 kDown);
void UpdateCustomPresetsMenu(u32 kDown, PresetType presetType = PresetType::RANDOMIZATION);
void UpdateResetToDefaultsMenu(u32 kdown, PresetType presetType = PresetType::RANDOMIZATION);
void UpdateGenerateMenu(u32 kDown);
void GoToMenu(Menu* newMenu);
void PrintMainMenu();
void PrintOptionSubMenu();
void PrintSubMenu();
void PrintPremadePresetsMenu(u32 kDown);
void PrintCustomPresetsMenu(PresetType presetType = PresetType::RANDOMIZATION);
void PrintResetToDefaultsMenu();
void PrintGenerateMenu();
void ClearDescription();
void PrintDescription(std::string_view description);
void GenerateRandomizer();
std::string GetInput(const char* hintText);

extern void MenuInit();
extern void MenuUpdate(u32 kDown, bool updatedByHeld, u32 kHeld);
