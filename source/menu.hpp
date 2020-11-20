#pragma once
#include <3ds.h>

#define MAIN_MENU 0
#define SUB_MENU 1
#define MAX_SETTINGS_ON_SCREEN 13
#define BOTTOM_COLUMNS 40
#define BOTTOM_ROWS 30

void UpdateMainMenu(u32 kDown);
void UpdateSubMenu(u32 kDown);
void PrintMainMenu();
void PrintSubMenu();
void GenerateRandomizer();
void GetInputSeed();

extern void MenuInit();
extern void MenuUpdate(u32 kDown);
