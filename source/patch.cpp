#include "patch.hpp"
#include <fstream>
#include <string>

//For specification on the IPS file format, visit: https://zerosoft.zophar.net/ips.php

bool WritePatch() {

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

  /*-------------------------
  |      rItemOverrides     |
  --------------------------*/

	//Write override table address to code
	u32 patchOffset = V_TO_P(RITEMOVERRIDES_ADDR);
	buf[0] = (patchOffset >> 16) & 0xFF;
	buf[1] = (patchOffset >> 8) & 0xFF;
	buf[2] = (patchOffset) & 0xFF;
	if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 3, FS_WRITE_FLUSH))) return false;
	totalRW += 3;

	//Write override table size to code
	u32 ovrTableSize = sizeof(ItemOverride) * overrides.size();
	buf[0] = (ovrTableSize >> 8) & 0xFF;
	buf[1] = (ovrTableSize) & 0xFF;
	if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 2, FS_WRITE_FLUSH))) return false;
	totalRW += 2;

	//Write override table to code
	for (auto override : overrides) {
		if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, &override, sizeof(override), FS_WRITE_FLUSH))) return false;
		totalRW += sizeof(override);
	}

  /*-------------------------
  |     gSettingsContext    |
  --------------------------*/

	//get the settings context
	SettingsContext ctx = Settings::FillContext();

	//write settings context address to code
	patchOffset = V_TO_P(GSETTINGSCONTEXT_ADDR);
	buf[0] = (patchOffset >> 16) & 0xFF;
	buf[1] = (patchOffset >> 8) & 0xFF;
	buf[2] = (patchOffset) & 0xFF;
	if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 3, FS_WRITE_FLUSH))) return false;
	totalRW += 3;

	//Write settings context size to code
	u32 ctxSize = sizeof(SettingsContext);
	buf[0] = (ctxSize >> 8) & 0xFF;
	buf[1] = (ctxSize) & 0xFF;
	if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 2, FS_WRITE_FLUSH))) return false;
	totalRW += 2;

	//write settings context to code
	if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, &ctx, sizeof(ctx), FS_WRITE_FLUSH))) return false;
  totalRW += sizeof(SettingsContext);

	/*-------------------------------
	|     rScrubRandomItemPrices    |
	|     rScrubTextIdTable         |
	--------------------------------*/
	u16 rScrubTextIdTable[11] = { 0x9014, 0x900F, 0x900A, 0x9028, 0x9032, 0x9028, 0x9046, 0x9028, 0x9028, 0x9028, 0x9028 };

	//only fill prices in if random prices
	if (ctx.scrubsanity == SCRUBSANITY_RANDOM_PRICES) {

		//create array of random prices
		s16 rScrubRandomItemPrices[11] = {0};
		for (u8 i = 0; i < 11; i++) {
			s16 price = Playthrough::GetRandomPrice();
			rScrubRandomItemPrices[i] = price;
			rScrubTextIdTable[i] = 0x9000 + (u16)price;
		}

		//write scrub random prices address to code
		patchOffset = V_TO_P(RSCRUBRANDOMITEMPRICES_ADDR);
		buf[0] = (patchOffset >> 16) & 0xFF;
		buf[1] = (patchOffset >> 8) & 0xFF;
		buf[2] = (patchOffset) & 0xFF;
		if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 3, FS_WRITE_FLUSH))) return false;
		totalRW += 3;

		//Write scrub random prices size to code
		u32 scrubRandomPricesSize = sizeof(rScrubRandomItemPrices);
		buf[0] = (scrubRandomPricesSize >> 8) & 0xFF;
		buf[1] = (scrubRandomPricesSize) & 0xFF;
		if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 2, FS_WRITE_FLUSH))) return false;
		totalRW += 2;

		//write scrub random prices to code
		if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, &rScrubRandomItemPrices, sizeof(rScrubRandomItemPrices), FS_WRITE_FLUSH))) return false;
	  	totalRW += sizeof(rScrubRandomItemPrices);
	} else if (ctx.scrubsanity == SCRUBSANITY_AFFORDABLE) {
		for (u8 i = 0; i < 11; i++) {
			rScrubTextIdTable[i] = 0x900A;
		}
	}

	if (ctx.scrubsanity != SCRUBSANITY_OFF) {
		//write scrub text table address to code
		patchOffset = V_TO_P(0x52236C); //this is the address of the base game's scrub textId table
		buf[0] = (patchOffset >> 16) & 0xFF;
		buf[1] = (patchOffset >> 8) & 0xFF;
		buf[2] = (patchOffset) & 0xFF;
		if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 3, FS_WRITE_FLUSH))) return false;
		totalRW += 3;

		//Write scrub text table size to code
		u32 scrubTextIdTableSize = sizeof(rScrubTextIdTable);
		buf[0] = (scrubTextIdTableSize >> 8) & 0xFF;
		buf[1] = (scrubTextIdTableSize) & 0xFF;
		if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 2, FS_WRITE_FLUSH))) return false;
		totalRW += 2;

		//write scrub text table to code
		if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, &rScrubTextIdTable, sizeof(rScrubTextIdTable), FS_WRITE_FLUSH))) return false;
	  	totalRW += sizeof(rScrubTextIdTable);
	}

	/*--------------------------------
	|     rDungeonRewardOverrides    |
	---------------------------------*/

	//write rDungeonRewardOverrides address to code
	patchOffset = V_TO_P(RDUNGEONREWARDOVERRIDES_ADDR);
	buf[0] = (patchOffset >> 16) & 0xFF;
	buf[1] = (patchOffset >> 8) & 0xFF;
	buf[2] = (patchOffset) & 0xFF;
	if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 3, FS_WRITE_FLUSH))) return false;
	totalRW += 3;

	//Write rDungeonRewardOverrides size to code
	u32 rDungeonRewardOverridesSize = sizeof(Settings::rDungeonRewardOverrides);
	buf[0] = (rDungeonRewardOverridesSize >> 8) & 0xFF;
	buf[1] = (rDungeonRewardOverridesSize) & 0xFF;
	if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 2, FS_WRITE_FLUSH))) return false;
	totalRW += 2;

	//write rDungeonRewardOverrides to code
	if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, &Settings::rDungeonRewardOverrides, sizeof(Settings::rDungeonRewardOverrides), FS_WRITE_FLUSH))) return false;
  totalRW += sizeof(Settings::rDungeonRewardOverrides);

  /*-------------------------
  |           EOF           |
  --------------------------*/

	//Write EOF to code
	if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, "EOF", 3, FS_WRITE_FLUSH | FS_WRITE_UPDATE_TIME))) return false;

	return true;
}
