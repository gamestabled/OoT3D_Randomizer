#pragma once
#include <3ds.h>

#define MAIN_MENU 0
#define SUB_MENU 1
#define GENERATE_MODE 2
#define MAX_SETTINGS_ON_SCREEN 13
#define TOP_WIDTH 50
#define BOTTOM_WIDTH 40
#define SCREEN_HEIGHT 30

void UpdateMainMenu(u32 kDown);
void UpdateSubMenu(u32 kDown);
void PrintMainMenu();
void PrintSubMenu();
void ClearDescription();
void PrintOptionDescrption();
void GenerateRandomizer();
void GetInputSeed();

extern void MenuInit();
extern void MenuUpdate(u32 kDown);
