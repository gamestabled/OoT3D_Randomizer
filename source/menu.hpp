#pragma once

#include <3ds.h>
#include <string>

#define MAIN_MENU 0
#define OPTION_SUB_MENU 1
#define SUB_MENU 2
#define OPTION_SUB_SUB_MENU 3
#define SUB_SUB_MENU 4
#define GENERATE_MODE 5
#define LOAD_PRESET 6
#define SAVE_PRESET 7
#define DELETE_PRESET 8
#define POST_GENERATE 9
#define MAX_MAINMENU_SETTINGS_ON_SCREEN 20
#define MAX_SUBMENU_SETTINGS_ON_SCREEN 13
#define TOP_WIDTH 50
#define BOTTOM_WIDTH 40
#define SCREEN_HEIGHT 30

#define RESET   "\x1b[0m"
#define DIM     "\x1b[2m"

#define BLACK   "\x1b[30m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MEGANTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1b[37m"

void ModeChangeInit();
void UpdateMainMenu(u32 kDown);
void UpdateOptionSubMenu(u32 kDown);
void UpdateSubMenu(u32 kDown);
void UpdatePresetsMenu(u32 kdown);
void UpdateGenerateMenu(u32 kDown);
void PrintMainMenu();
void PrintOptionSubMenu();
void PrintSubMenu();
void PrintPresetsMenu();
void PrintGenerateMenu();
void ClearDescription();
void PrintOptionDescription();
void GenerateRandomizer();
std::string GetInput(const char* hintText);

extern void MenuInit();
extern void MenuUpdate(u32 kDown);
