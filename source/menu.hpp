#pragma once
#include <3ds.h>
#include <string>

#define MAIN_MENU 0
#define SUB_MENU 1
#define GENERATE_MODE 2
#define LOAD_PRESET 3
#define SAVE_PRESET 4
#define MAX_SETTINGS_ON_SCREEN 13
#define TOP_WIDTH 50
#define BOTTOM_WIDTH 40
#define SCREEN_HEIGHT 30

void ModeChangeInit();
void UpdateMainMenu(u32 kDown);
void UpdateSubMenu(u32 kDown);
void UpdatePresetsMenu(u32 kdown);
void PrintMainMenu();
void PrintSubMenu();
void PrintPresetsMenu();
void ClearDescription();
void PrintOptionDescrption();
bool CreatePresetDirectories();
void GetPresets();
bool LoadPreset(std::string presetName);
bool SaveSettingsPreset();
void GenerateRandomizer();
std::string GetInput(const char* hintText);

extern void MenuInit();
extern void MenuUpdate(u32 kDown);
