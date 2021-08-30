#include "patch.hpp"

#include "cosmetics.hpp"
#include "custom_messages.hpp"
#include "music.hpp"
#include "shops.hpp"
#include "spoiler_log.hpp"
#include "entrance.hpp"

#include <array>
#include <cstring>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

// For specification on the IPS file format, visit: https://zerosoft.zophar.net/ips.php

using FILEPtr = std::unique_ptr<FILE, decltype(&std::fclose)>;

bool CopyFile(FS_Archive sdmcArchive, const char* dst, const char* src) {
  Result res = 0;
  Handle outFile;
  u32 bytesWritten = 0;
  // Delete dst if it exists
  FSUSER_DeleteFile(sdmcArchive, fsMakePath(PATH_ASCII, dst));

  // Open dst destination
  if (!R_SUCCEEDED(res = FSUSER_OpenFile(&outFile, sdmcArchive, fsMakePath(PATH_ASCII, dst), FS_OPEN_WRITE | FS_OPEN_CREATE, 0))) {
    return false;
  }

  if (auto file = FILEPtr{std::fopen(src, "r"), std::fclose}) {
    // obtain file size
    fseek(file.get(), 0, SEEK_END);
    const auto lSize = static_cast<size_t>(ftell(file.get()));
    rewind(file.get());

    // copy file into the buffer
    std::vector<char> buffer(lSize);
    fread(buffer.data(), 1, buffer.size(), file.get());

    // Write the buffer to final destination
    if (!R_SUCCEEDED(res = FSFILE_Write(outFile, &bytesWritten, 0, buffer.data(), buffer.size(), FS_WRITE_FLUSH))) {
      return false;
    }
  }

  FSFILE_Close(outFile);
  return true;
}

bool WritePatch(u32 patchOffset, s32 patchSize, char* patchDataPtr, Handle& code, u32& bytesWritten, u32& totalRW, char* buf) {

  //patch sizes greater than PATCH_SIZE_MAX have to be split up due to IPS patching specifications
  while (patchSize > 0) {
    // Write patch offset address to code
    buf[0] = (patchOffset >> 16) & 0xFF;
    buf[1] = (patchOffset >> 8) & 0xFF;
    buf[2] = (patchOffset) & 0xFF;
    if (!R_SUCCEEDED(FSFILE_Write(code, &bytesWritten, totalRW, buf, 3, FS_WRITE_FLUSH))) {
      return false;
    }
    totalRW += 3;

    // Write patch size to code
    u32 newPatchSize = (patchSize > PATCH_SIZE_MAX) ? PATCH_SIZE_MAX : patchSize;
    buf[0] = (newPatchSize >> 8) & 0xFF;
    buf[1] = (newPatchSize) & 0xFF;
    if (!R_SUCCEEDED(FSFILE_Write(code, &bytesWritten, totalRW, buf, 2, FS_WRITE_FLUSH))) {
      return false;
    }
    totalRW += 2;

    // Write patch data to code
    if (!R_SUCCEEDED(FSFILE_Write(code, &bytesWritten, totalRW, patchDataPtr, newPatchSize, FS_WRITE_FLUSH))) {
      return false;
    }
    totalRW += newPatchSize;

    patchDataPtr += PATCH_SIZE_MAX;
    patchOffset += PATCH_SIZE_MAX;
    patchSize -= PATCH_SIZE_MAX;
  }
  #ifdef ENABLE_DEBUG
    CitraPrint(std::to_string(totalRW));
  #endif
  return true;
}

void WriteFloatToBuffer(std::vector<char>& buffer, float f, size_t offset) {
  memcpy(buffer.data() + offset, &f, sizeof(float));
}

bool WriteAllPatches() {
  Result res = 0;
  FS_Archive sdmcArchive = 0;
  Handle code;
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
  //Create the romfs directory if it doesn't exist (for LayeredFS)
  FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, "/luma/titles/0004000000033500/romfs"), FS_ATTRIBUTE_DIRECTORY);
  //Create the actor directory if it doesn't exist
  FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, "/luma/titles/0004000000033500/romfs/actor"), FS_ATTRIBUTE_DIRECTORY);

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
  if (auto basecode = FILEPtr{std::fopen("romfs:/basecode.ips", "r"), std::fclose}) {
    // obtain basecode.ips file size
    fseek(basecode.get(), 0, SEEK_END);
    const auto lSize = static_cast<size_t>(ftell(basecode.get()));
    rewind(basecode.get());

    // copy basecode.ips into the buffer
    std::vector<char> buffer(lSize);
    fread(buffer.data(), 1, buffer.size(), basecode.get());

    // Write the buffer to code.ips
    if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buffer.data(), buffer.size(), FS_WRITE_FLUSH))) {
      return false;
    }

    totalRW += bytesWritten - 3; // -3 to overwrite EOF
    #ifdef ENABLE_DEBUG
      CitraPrint(std::to_string(totalRW));
    #endif
  }

  /*-------------------------
  |      rItemOverrides     |
  --------------------------*/

  u32 patchOffset = V_TO_P(RITEMOVERRIDES_ADDR);
  s32 patchSize = sizeof(ItemOverride) * overrides.size();
  ItemOverride ovrPatchData[overrides.size()] = {};
  //generate override data
  size_t i = 0;
  for (const auto& override : overrides) {
    ovrPatchData[i] = override;
    i++;
  }
  if (!WritePatch(patchOffset, patchSize, (char*)ovrPatchData, code, bytesWritten, totalRW, buf)) {
    return false;
  }

  /*-------------------------
  |    rEntranceOverrides   |
  --------------------------*/

  patchOffset = V_TO_P(RENTRANCEOVERRIDES_ADDR);
  patchSize = sizeof(EntranceOverride) * entranceOverrides.size();
  EntranceOverride eOvrPatchData[entranceOverrides.size()] = {};
  //generate entrance override patch data
  i = 0;
  for (const auto& entranceOverride : entranceOverrides) {
    eOvrPatchData[i] = entranceOverride;
    i++;
  }
  if (!WritePatch(patchOffset, patchSize, (char*)eOvrPatchData, code, bytesWritten, totalRW, buf)) {
    return false;
  }

  /*-------------------------
  |     gSettingsContext    |
  --------------------------*/

  patchOffset = V_TO_P(GSETTINGSCONTEXT_ADDR);
  patchSize = sizeof(SettingsContext);
  //get the settings context
  SettingsContext ctx = Settings::FillContext();
  if (!WritePatch(patchOffset, patchSize, (char*)(&ctx), code, bytesWritten, totalRW, buf)) {
    return false;
  }

  /*-------------------------
  |       gSpoilerData      |
  --------------------------*/

  patchOffset = V_TO_P(GSPOILERDATA_ADDR);
  patchSize = sizeof(SpoilerData);
  //Get the spoiler data
  SpoilerData spoilerData = GetSpoilerData();
  if (!WritePatch(patchOffset, patchSize, (char*)(&spoilerData), code, bytesWritten, totalRW, buf)) {
    return false;
  }

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
    for (i = 0; i < rScrubRandomItemPrices.size(); i++) {
      const s16 price = GetRandomScrubPrice();
      rScrubRandomItemPrices[i] = price;
      rScrubTextIdTable[i] = static_cast<u16>(0x9000 + static_cast<u16>(price));
    }

    // Write the patch for random scrub prices
    patchOffset = V_TO_P(RSCRUBRANDOMITEMPRICES_ADDR);
    patchSize = sizeof(rScrubRandomItemPrices);
    if (!WritePatch(patchOffset, patchSize, (char*)(&rScrubRandomItemPrices), code, bytesWritten, totalRW, buf)) {
      return false;
    }

  } else if (ctx.scrubsanity == SCRUBSANITY_AFFORDABLE) {
    //If affordable is set, write all text IDs as the 10 rupee price ID
    rScrubTextIdTable.fill(0x900A);
  }
  if (ctx.scrubsanity != SCRUBSANITY_OFF) {
    //Write the patch for the scrub text ID table
    patchOffset = V_TO_P(0x52236C); //this is the address of the base game's scrub textId table
    patchSize = sizeof(rScrubTextIdTable);
    if (!WritePatch(patchOffset, patchSize, (char*)(&rScrubTextIdTable), code, bytesWritten, totalRW, buf)) {
      return false;
    }
  }

  /*-------------------------------
  |     rShopsanityPrices         |
  --------------------------------*/

  if (Settings::Shopsanity.IsNot(SHOPSANITY_OFF) && Settings::Shopsanity.IsNot(SHOPSANITY_ZERO)) {
    //Get prices from shop item vector
    std::array<s32, 32> rShopsanityPrices{};
    for (i = 0; i < 32; i++) {
      rShopsanityPrices[i] = NonShopItems[i].Price;
    }

    // Write shopsanity item prices to the patch
    patchOffset = V_TO_P(RSHOPSANITYPRICES_ADDR);
    patchSize = sizeof(rShopsanityPrices);
    if (!WritePatch(patchOffset, patchSize, (char*)(&rShopsanityPrices), code, bytesWritten, totalRW, buf)) {
      return false;
    }
  }

  /*--------------------------------
  |     rDungeonRewardOverrides    |
  ---------------------------------*/
  // Write rDungeonRewardOverrides to the patch
  patchOffset = V_TO_P(RDUNGEONREWARDOVERRIDES_ADDR);
  patchSize = sizeof(Settings::rDungeonRewardOverrides);
  if (!WritePatch(patchOffset, patchSize, (char*)(&Settings::rDungeonRewardOverrides), code, bytesWritten, totalRW, buf)) {
    return false;
  }

  /*--------------------------------
  |     rCustomMessageEntries      |
  ---------------------------------*/

  std::pair<const char*, u32> messageDataInfo = CustomMessages::RawMessageData();
  std::pair<const char*, u32> messageEntriesInfo = CustomMessages::RawMessageEntryData();

  // Write message data to patch
  u32 messageDataOffset = V_TO_P(RCUSTOMMESSAGES_ADDR);
  s32 messageDataSize = messageDataInfo.second;
  if (!WritePatch(messageDataOffset, messageDataSize, (char*)messageDataInfo.first, code, bytesWritten, totalRW, buf)) {
    return false;
  }

  // Write message entries to patch
  u32 messageEntriesOffset = (messageDataOffset + messageDataSize + 3) & ~3; //round up and align with u32
  s32 messageEntriesSize = messageEntriesInfo.second;
  if (!WritePatch(messageEntriesOffset, messageEntriesSize, (char*)messageEntriesInfo.first, code, bytesWritten, totalRW, buf)) {
    return false;
  }

  // Write ptrCustomMessageEntries to patch
  patchOffset = V_TO_P(PTRCUSTOMMESSAGEENTRIES_ADDR);
  patchSize = 4;
  u32 ptrCustomMessageEntriesData = P_TO_V(messageEntriesOffset);
  if (!WritePatch(patchOffset, patchSize, (char*)(&ptrCustomMessageEntriesData), code, bytesWritten, totalRW, buf)) {
    return false;
  }

  // Write numCustomMessageEntries to code
  patchOffset = V_TO_P(NUMCUSTOMMESSAGEENTRIES_ADDR);
  patchSize = 4;
  u32 numCustomMessageEntriesData = CustomMessages::NumMessages();
  if (!WritePatch(patchOffset, patchSize, (char*)(&numCustomMessageEntriesData), code, bytesWritten, totalRW, buf)) {
    return false;
  }

  /*--------------------------------
  |         rBGMOverrides          |
  ---------------------------------*/

  patchOffset = V_TO_P(RBGMOVERRIDES_ADDR);
  patchSize = sizeof(Music::seqOverrides);
  if (!WritePatch(patchOffset, patchSize, (char*)Music::seqOverrides.data(), code, bytesWritten, totalRW, buf)) {
    return false;
  }

  /*--------------------------------
  |         Gauntlet Colors        |
  ---------------------------------*/

  const u32 GAUNTLETCOLORSARRAY_ADDR = 0x0053CA1C;
  const std::array rGauntletColors{
    Cosmetics::HexStrToColorRGB(Settings::finalSilverGauntletsColor),
    Cosmetics::HexStrToColorRGB(Settings::finalGoldGauntletsColor),
  };

  // Write Gauntlet Colors address to code
  patchOffset = V_TO_P(GAUNTLETCOLORSARRAY_ADDR);
  patchSize = sizeof(rGauntletColors);
  if (!WritePatch(patchOffset, patchSize, (char*)rGauntletColors.data(), code, bytesWritten, totalRW, buf)) {
    return false;
  }

  /*-------------------------
  |           EOF           |
  --------------------------*/

  // Write EOF to code
  if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, "EOF", 3, FS_WRITE_FLUSH | FS_WRITE_UPDATE_TIME))) {
    return false;
  }

  FSFILE_Close(code);

  /*-------------------------
  |       exheader.bin      |
  --------------------------*/
  // Get exheader for proper playOption
  const char * filePath;
  if (Settings::PlayOption == PATCH_CONSOLE) {
    filePath = "romfs:/exheader.bin";
  } else {
    filePath = "romfs:/exheader_citra.bin";
  }

  CopyFile(sdmcArchive, "/luma/titles/0004000000033500/exheader.bin", filePath);

  /*-------------------------
  |       custom assets      |
  --------------------------*/

  Cosmetics::Color_RGB childTunicColor  = Cosmetics::HexStrToColorRGB(Settings::finalChildTunicColor);
  Cosmetics::Color_RGB kokiriTunicColor = Cosmetics::HexStrToColorRGB(Settings::finalKokiriTunicColor);
  Cosmetics::Color_RGB goronTunicColor  = Cosmetics::HexStrToColorRGB(Settings::finalGoronTunicColor);
  Cosmetics::Color_RGB zoraTunicColor   = Cosmetics::HexStrToColorRGB(Settings::finalZoraTunicColor);

  // Delete assets if it exists
  Handle assetsOut;
  const char* assetsOutPath = "/luma/titles/0004000000033500/romfs/actor/zelda_gi_melody.zar";
  const char* assetsInPath = "romfs:/zelda_gi_melody.zar";
  FSUSER_DeleteFile(sdmcArchive, fsMakePath(PATH_ASCII, assetsOutPath));

  // Open assets destination
  if (!R_SUCCEEDED(res = FSUSER_OpenFile(&assetsOut, sdmcArchive, fsMakePath(PATH_ASCII, assetsOutPath), FS_OPEN_WRITE | FS_OPEN_CREATE, 0))) {
    return false;
  }

  if (auto file = FILEPtr{std::fopen(assetsInPath, "r"), std::fclose}) {
    // obtain assets size
    fseek(file.get(), 0, SEEK_END);
    const auto lSize = static_cast<size_t>(ftell(file.get()));
    rewind(file.get());

    // copy assets into the buffer
    std::vector<char> buffer(lSize);
    fread(buffer.data(), 1, buffer.size(), file.get());

    // edit assets as needed
    const size_t adultTunicOffsetInZAR = 0x1021C;
    const size_t childTunicOffsetInZAR = 0x1E7FC;

    WriteFloatToBuffer(buffer, kokiriTunicColor.r, adultTunicOffsetInZAR + 0x70);
    WriteFloatToBuffer(buffer, kokiriTunicColor.g, adultTunicOffsetInZAR + 0x98);
    WriteFloatToBuffer(buffer, kokiriTunicColor.b, adultTunicOffsetInZAR + 0xC0);

    WriteFloatToBuffer(buffer, goronTunicColor.r, adultTunicOffsetInZAR + 0x78);
    WriteFloatToBuffer(buffer, goronTunicColor.g, adultTunicOffsetInZAR + 0xA0);
    WriteFloatToBuffer(buffer, goronTunicColor.b, adultTunicOffsetInZAR + 0xC8);

    WriteFloatToBuffer(buffer, zoraTunicColor.r, adultTunicOffsetInZAR + 0x80);
    WriteFloatToBuffer(buffer, zoraTunicColor.g, adultTunicOffsetInZAR + 0xA8);
    WriteFloatToBuffer(buffer, zoraTunicColor.b, adultTunicOffsetInZAR + 0xD0);

    WriteFloatToBuffer(buffer, childTunicColor.r, childTunicOffsetInZAR + 0x70);
    WriteFloatToBuffer(buffer, childTunicColor.g, childTunicOffsetInZAR + 0x88);
    WriteFloatToBuffer(buffer, childTunicColor.b, childTunicOffsetInZAR + 0xA0);

    // Write the assets to final destination
    if (!R_SUCCEEDED(res = FSFILE_Write(assetsOut, &bytesWritten, 0, buffer.data(), buffer.size(), FS_WRITE_FLUSH))) {
      return false;
    }
  }
  FSFILE_Close(assetsOut);

  FSUSER_CloseArchive(sdmcArchive);

  return true;
}
