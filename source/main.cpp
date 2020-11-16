#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include <set>
#include <cstring>
#include <vector>

#include "playthrough.hpp"
#include "settings.hpp"
#include "../code/src/item_override.h"


#define ITEMOVERRIDETABLE_ADDR 0x005d1e40 //TODO, make this automatically generate
#define V_TO_P(addr) (addr - 0x100000)
#define MAX_SETTINGS_ON_SCREEN 14

std::set<ItemOverride, Playthrough::ItemOverride_Compare> Overrides;
u8 selectedSetting;
u8 selectedMenu;
int settingBound;
int menuBound;
Menu currentMenu;
Option* currentSetting;

bool WriteOverridesToPatch() {
	Result res = 0;
	FS_Archive sdmcArchive = 0;
	Handle basecode;
	Handle code;
	u32 bytesRead = 0;
	u32 bytesWritten = 0;
	u32 totalRW = 0;
	char buf[512];

	//Open SD archive
	if (!R_SUCCEEDED(res = FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) return false;
	//Open basecode
	if (!R_SUCCEEDED(res = FSUSER_OpenFile(&basecode, sdmcArchive, fsMakePath(PATH_ASCII, "/luma/titles/0004000000033500/basecode.ips"), FS_OPEN_READ, FS_ATTRIBUTE_READ_ONLY))) return false;
	//Open code
	if (!R_SUCCEEDED(res = FSUSER_OpenFile(&code, sdmcArchive, fsMakePath(PATH_ASCII, "/luma/titles/0004000000033500/code.ips"), FS_OPEN_WRITE | FS_OPEN_CREATE, 0))) return false;

	//Copy basecode to code
	do {
		//Read from basecode
		if (!R_SUCCEEDED(res = FSFILE_Read(basecode, &bytesRead, totalRW, buf, sizeof(buf)))) return false;
		//Write to code
		if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, bytesRead, FS_WRITE_FLUSH))) return false;
		totalRW += bytesRead;
	} while (bytesRead > 0);

	totalRW -= 3;
	//Write override table address to code
	u32 patchOffset = V_TO_P(ITEMOVERRIDETABLE_ADDR);
	buf[0] = (patchOffset >> 16) & 0xFF;
	buf[1] = (patchOffset >> 8) & 0xFF;
	buf[2] = (patchOffset) & 0xFF;
	if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 3, FS_WRITE_FLUSH))) return false;
	totalRW += 3;

	//Write override table size to code
	u32 ovrTableSize = sizeof(ItemOverride) * Overrides.size();
	printf("size: %lx\n", ovrTableSize);
	buf[0] = (ovrTableSize >> 8) & 0xFF;
	buf[1] = (ovrTableSize) & 0xFF;
	if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 2, FS_WRITE_FLUSH))) return false;
	totalRW += 2;

	//Write override table to code
	for (auto override : Overrides) {
		if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, &override, sizeof(override), FS_WRITE_FLUSH))) return false;
		totalRW += sizeof(override);
	}
	//Write EOF to code
	if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, "EOF", 3, FS_WRITE_FLUSH | FS_WRITE_UPDATE_TIME))) return false;

	return true;
}

void UpdateMenuView() {
	if (selectedSetting >= settingBound + MAX_SETTINGS_ON_SCREEN) {
		settingBound++;
	}

	if (selectedSetting < settingBound)  {
		settingBound = selectedSetting;
	}
}

void PrintOptions() {
	UpdateMenuView();
	for (u8 i = 0; i < MAX_SETTINGS_ON_SCREEN; i++) {

		if (i + settingBound >= Settings::Options.size()) break;

		Option* setting = Settings::Options[i + settingBound];

		if (selectedSetting == i + settingBound) {
			printf("\x1b[%d;%dH\x1b[32m>", 2 + (i * 2),  1);
			printf("\x1b[%d;%dH%s:",       2 + (i * 2),  2, setting->name.c_str());
			printf("\x1b[%d;%dH%s\x1b[0m", 2 + (i * 2), 21, setting->options[setting->selectedOption].c_str());
		} else {
			printf("\x1b[%d;%dH%s:",       2 + (i * 2),  2, setting->name.c_str());
			printf("\x1b[%d;%dH%s",        2 + (i * 2), 21, setting->options[setting->selectedOption].c_str());
		}

		*setting->var = setting->options[setting->selectedOption];
	}
}

void UpdateOptions(u32 kDown) {
	if (kDown & KEY_DUP) {
		if (selectedSetting != 0)
			selectedSetting--;
	}
	if (kDown & KEY_DDOWN) {
		if (selectedSetting != Settings::Options.size() - 1)
			selectedSetting++;
	}

	currentSetting = Settings::Options[selectedSetting];

	if (kDown & KEY_DRIGHT) {
		if (currentSetting->selectedOption != currentSetting->options.size() - 1)
			currentSetting->selectedOption++;
	}
	if (kDown & KEY_DLEFT) {
		if (currentSetting->selectedOption != 0)
			currentSetting->selectedOption--;
	}
}

int main() {
	gfxInitDefault();

	PrintConsole topScreen, bottomScreen;

	consoleInit(GFX_TOP,    &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);

	consoleSelect(&topScreen);

	printf("OoT3D Randomizer testing!\n");
	printf("Press Start to exit!\n");
	printf("Use D-pad to select settings!\n");
	printf("Press A to create the patch!\n");

	unsigned int seed = 0;
	menuBound = 0;
	settingBound = 0;
	selectedSetting = 0;
	currentSetting = Settings::Options[selectedSetting];


	while (aptMainLoop()) {
		hidScanInput();

		u32 kDown = hidKeysDown();

		if (kDown & KEY_START)
			break;

		if (kDown & KEY_DUP || kDown & KEY_DDOWN || kDown & KEY_DLEFT || kDown & KEY_DRIGHT) {
			consoleSelect(&bottomScreen);
			consoleClear();
		}

		UpdateOptions(kDown);
		consoleSelect(&bottomScreen);
		PrintOptions();
		consoleSelect(&topScreen);

		if (kDown & KEY_A) { // If the A button got pressed, do the thing
			Overrides.clear();
			//printf("about to fill with seed %d\n", seed);
			int ret = Playthrough::Fill(0, seed, Overrides);
			if (ret < 0) {
				printf("Error %d with fill. Press Start to exit.\n", ret);
				continue;
			}
			printf("made it past fill! nice!\n");
			printf("about to write overrides to patch\n");
			if (WriteOverridesToPatch()) {
				printf("Created the patch. Have fun!\n");
			} else {
				printf("Error creating patch. Press Start to exit.\n");
			}
		}

		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		//Wait for VBlank
		gspWaitForVBlank();
	}

	gfxExit();
	return 0;
}
