#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include <set>
#include <cstring>

#include "playthrough.hpp"
#include "../code/src/item_override.h"


#define ITEMOVERRIDETABLE_ADDR 0x005d1e40 //TODO, make this automatically generate
#define V_TO_P(addr) (addr - 0x100000)

std::set<ItemOverride, Playthrough::ItemOverride_Compare> Overrides;

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

int main() {
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);

	printf("OoT3D Randomizer testing!\n");
	printf("Press Start to exit!\n");
	printf("Use D-pad to change the random seed!\n");
	printf("Press A create the patch!\n");

	unsigned int seed = 0;
	printf("Seed: %d\n", seed);

	while (aptMainLoop()) {
		gspWaitForVBlank();
		gfxSwapBuffers();
		hidScanInput();

		u32 kDown = hidKeysDown();

		if (kDown & KEY_START)
			break;

		if (kDown & KEY_DUP)
			seed += 1;
		if (kDown & KEY_DDOWN)
			seed -= 1;
		if (kDown & KEY_DRIGHT)
			seed += 10;
		if (kDown & KEY_DLEFT)
			seed -= 10;

		if (kDown & KEY_A) { // If the A button got pressed, do the thing
			Overrides.clear();
			printf("about to fill with seed %d\n", seed);
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
	}

	gfxExit();
	return 0;
}
