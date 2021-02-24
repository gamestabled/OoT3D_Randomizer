#include "patch.hpp"

#include <array>
#include <fstream>
#include <string>
#include <cstring>

// For specification on the IPS file format, visit: https://zerosoft.zophar.net/ips.php

bool WritePatch() {
  Result res = 0;
  FS_Archive sdmcArchive = 0;
  Handle code;
  Handle finalExheader;
  u32 bytesWritten = 0;
  u32 totalRW = 0;
  char buf[512];

  // Open SD archive
  if (!R_SUCCEEDED(res = FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) {
    return false;
  }

  //Create necessary folders where patch files need to go (if they don't exist);
  //Create the luma directory if it doesn't exist (on citra)
  FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, "/luma"), FS_ATTRIBUTE_DIRECTORY);
  //Create the titles directory if it doesn't exist
  FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, "/luma/titles"), FS_ATTRIBUTE_DIRECTORY);
  //Create the 0004000000033500 directory if it doesn't exist (oot3d game id)
  FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, "/luma/titles/0004000000033500"), FS_ATTRIBUTE_DIRECTORY);

  /*romfs is used to get files from the romfs folder. This allows us to copy
  from basecode and write the exheader without the user needing to worry about
  placing them manually on their SD card.*/
  Result rc = romfsInit();
  if (rc) {
    printf("\nromfsInit: %08lX\n", rc);
  }

  /*-------------------------
  |       basecode.ips      |
  --------------------------*/

  // Delete code.ips if it exists
  FSUSER_DeleteFile(sdmcArchive, fsMakePath(PATH_ASCII, "/luma/titles/0004000000033500/code.ips"));

  // Open code.ips
  if (!R_SUCCEEDED(res = FSUSER_OpenFile(&code, sdmcArchive, fsMakePath(PATH_ASCII, "/luma/titles/0004000000033500/code.ips"), FS_OPEN_WRITE | FS_OPEN_CREATE, 0))) {
    return false;
  }

  // Copy basecode to code
  FILE* basecode = fopen("romfs:/basecode.ips", "r");
  if (basecode) {
    char* buffer;
    long lSize;

    // obtain basecode.ips file size
    fseek(basecode , 0 , SEEK_END);
    lSize = ftell(basecode);
    rewind(basecode);

    // allocate memory to contain basecode.ips
    buffer = (char*) malloc(sizeof(char) * lSize);

    // copy basecode.ips into the buffer
    fread(buffer,1,lSize,basecode);

    // Write the buffer to code.ips
    if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buffer, lSize, FS_WRITE_FLUSH))) {
      return false;
    }

    totalRW += bytesWritten - 3; // -3 to overwrite EOF
    fclose(basecode);
    free(buffer);
  }

  /*-------------------------
  |      rItemOverrides     |
  --------------------------*/

  // Write override table address to code
  u32 patchOffset = V_TO_P(RITEMOVERRIDES_ADDR);
  buf[0] = (patchOffset >> 16) & 0xFF;
  buf[1] = (patchOffset >> 8) & 0xFF;
  buf[2] = (patchOffset) & 0xFF;
  if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 3, FS_WRITE_FLUSH))) {
    return false;
  }
  totalRW += 3;

  // Write override table size to code
  const u32 ovrTableSize = sizeof(ItemOverride) * overrides.size();
  buf[0] = (ovrTableSize >> 8) & 0xFF;
  buf[1] = (ovrTableSize) & 0xFF;
  if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 2, FS_WRITE_FLUSH))) {
    return false;
  }
  totalRW += 2;

  // Write override table to code
  for (const auto& override : overrides) {
    if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, &override, sizeof(override), FS_WRITE_FLUSH))) {
      return false;
    }
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
  if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 3, FS_WRITE_FLUSH))) {
    return false;
  }
  totalRW += 3;

  //Write settings context size to code
  const u32 ctxSize = sizeof(SettingsContext);
  buf[0] = (ctxSize >> 8) & 0xFF;
  buf[1] = (ctxSize) & 0xFF;
  if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 2, FS_WRITE_FLUSH))) {
    return false;
  }
  totalRW += 2;

  //write settings context to code
  if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, &ctx, sizeof(ctx), FS_WRITE_FLUSH))) {
    return false;
  }
  totalRW += sizeof(SettingsContext);

  /*-------------------------------
  |     rScrubRandomItemPrices    |
  |     rScrubTextIdTable         |
  --------------------------------*/
  std::array<u16, 11> rScrubTextIdTable{
    0x9014, 0x900F, 0x900A, 0x9028, 0x9032, 0x9028,
    0x9046, 0x9028, 0x9028, 0x9028, 0x9028
  };

  // Only fill prices in if random prices
  if (ctx.scrubsanity == SCRUBSANITY_RANDOM_PRICES) {
    // Create array of random prices
    std::array<s16, 11> rScrubRandomItemPrices{};
    for (size_t i = 0; i < rScrubRandomItemPrices.size(); i++) {
      const s16 price = Playthrough::GetRandomPrice();
      rScrubRandomItemPrices[i] = price;
      rScrubTextIdTable[i] = static_cast<u16>(0x9000 + static_cast<u16>(price));
    }

    // Write scrub random prices address to code
    patchOffset = V_TO_P(RSCRUBRANDOMITEMPRICES_ADDR);
    buf[0] = (patchOffset >> 16) & 0xFF;
    buf[1] = (patchOffset >> 8) & 0xFF;
    buf[2] = (patchOffset) & 0xFF;
    if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 3, FS_WRITE_FLUSH))) {
      return false;
    }
    totalRW += 3;

    // Write scrub random prices size to code
    const u32 scrubRandomPricesSize = sizeof(rScrubRandomItemPrices);
    buf[0] = (scrubRandomPricesSize >> 8) & 0xFF;
    buf[1] = (scrubRandomPricesSize) & 0xFF;
    if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 2, FS_WRITE_FLUSH))) {
      return false;
    }
    totalRW += 2;

    // Write scrub random prices to code
    if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, &rScrubRandomItemPrices, sizeof(rScrubRandomItemPrices), FS_WRITE_FLUSH))) {
      return false;
    }
    totalRW += sizeof(rScrubRandomItemPrices);
  } else if (ctx.scrubsanity == SCRUBSANITY_AFFORDABLE) {
    rScrubTextIdTable.fill(0x900A);
  }

  if (ctx.scrubsanity != SCRUBSANITY_OFF) {
    // Write scrub text table address to code
    patchOffset = V_TO_P(0x52236C); //this is the address of the base game's scrub textId table
    buf[0] = (patchOffset >> 16) & 0xFF;
    buf[1] = (patchOffset >> 8) & 0xFF;
    buf[2] = (patchOffset) & 0xFF;
    if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 3, FS_WRITE_FLUSH))) {
      return false;
    }
    totalRW += 3;

    // Write scrub text table size to code
    const u32 scrubTextIdTableSize = sizeof(rScrubTextIdTable);
    buf[0] = (scrubTextIdTableSize >> 8) & 0xFF;
    buf[1] = (scrubTextIdTableSize) & 0xFF;
    if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 2, FS_WRITE_FLUSH))) {
      return false;
    }
    totalRW += 2;

    // Write scrub text table to code
    if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, &rScrubTextIdTable, sizeof(rScrubTextIdTable), FS_WRITE_FLUSH))) {
      return false;
    }
    totalRW += sizeof(rScrubTextIdTable);
  }

  /*--------------------------------
  |     rDungeonRewardOverrides    |
  ---------------------------------*/

  // Write rDungeonRewardOverrides address to code
  patchOffset = V_TO_P(RDUNGEONREWARDOVERRIDES_ADDR);
  buf[0] = (patchOffset >> 16) & 0xFF;
  buf[1] = (patchOffset >> 8) & 0xFF;
  buf[2] = (patchOffset) & 0xFF;
  if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 3, FS_WRITE_FLUSH))) {
    return false;
  }
  totalRW += 3;

  // Write rDungeonRewardOverrides size to code
  const u32 rDungeonRewardOverridesSize = sizeof(Settings::rDungeonRewardOverrides);
  buf[0] = (rDungeonRewardOverridesSize >> 8) & 0xFF;
  buf[1] = (rDungeonRewardOverridesSize) & 0xFF;
  if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 2, FS_WRITE_FLUSH))) {
    return false;
  }
  totalRW += 2;

  // Write rDungeonRewardOverrides to code
  if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, Settings::rDungeonRewardOverrides.data(), sizeof(Settings::rDungeonRewardOverrides), FS_WRITE_FLUSH))) {
    return false;
  }
  totalRW += sizeof(Settings::rDungeonRewardOverrides);

  /*-------------------------
  |           EOF           |
  --------------------------*/

  // Write EOF to code
  if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, "EOF", 3, FS_WRITE_FLUSH | FS_WRITE_UPDATE_TIME))) {
    return false;
  }

  /*-------------------------
  |       exheader.bin      |
  --------------------------*/
  // Delete exheader.bin if it exists
  FSUSER_DeleteFile(sdmcArchive, fsMakePath(PATH_ASCII, "/luma/titles/0004000000033500/exheader.bin"));

  // Open final exheader.bin destination
  if (!R_SUCCEEDED(res = FSUSER_OpenFile(&finalExheader, sdmcArchive, fsMakePath(PATH_ASCII, "/luma/titles/0004000000033500/exheader.bin"), FS_OPEN_WRITE | FS_OPEN_CREATE, 0))) {
    return false;
  }

  // Get exheader for proper playOption
  const char * filePath;
  if (Settings::PlayOption == PATCH_CONSOLE) {
    filePath = "romfs:/exheader.bin";
  } else {
    filePath = "romfs:/exheader_citra.bin";
  }

  // Copy exheader.bin from romfs to final destination
  FILE* exheader = fopen(filePath, "r");
  if (exheader) {
    char* buffer;
    long lSize;

    // obtain exheader file size
    fseek(exheader , 0 , SEEK_END);
    lSize = ftell(exheader);
    rewind(exheader);

    // allocate memory to contain exheader
    buffer = (char*) malloc(sizeof(char) * lSize);

    // copy exheader into the buffer
    fread(buffer,1,lSize,exheader);

    // Write the buffer to final exheader.bin destination
    if (!R_SUCCEEDED(res = FSFILE_Write(finalExheader, &bytesWritten, 0, buffer, lSize, FS_WRITE_FLUSH))) {
      return false;
    }

    fclose(exheader);
    free(buffer);
  }

  FSFILE_Close(code);
  FSFILE_Close(finalExheader);
  FSUSER_CloseArchive(sdmcArchive);

  return true;
}
