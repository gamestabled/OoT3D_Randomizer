#include "patch.hpp"
#include <fstream>
#include <string>

std::set<ItemOverride, Playthrough::ItemOverride_Compare> Overrides;

//For specification on the IPS file format, visit: https://zerosoft.zophar.net/ips.php

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
	u32 ovrTableSize = sizeof(ItemOverride) * Overrides.size();
	buf[0] = (ovrTableSize >> 8) & 0xFF;
	buf[1] = (ovrTableSize) & 0xFF;
	if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 2, FS_WRITE_FLUSH))) return false;
	totalRW += 2;

	//Write override table to code
	for (auto override : Overrides) {
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

  /*-------------------------
  |           EOF           |
  --------------------------*/

	//Write EOF to code
	if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, "EOF", 3, FS_WRITE_FLUSH | FS_WRITE_UPDATE_TIME))) return false;

	return true;
}
