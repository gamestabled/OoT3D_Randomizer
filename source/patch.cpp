#include "patch.hpp"

#include "cosmetics.hpp"
#include "custom_messages.hpp"
#include "shops.hpp"

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

bool WritePatch() {
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
    printf("\nbasecode size: %lx\n", totalRW);
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
  printf("\nAfter Overrides: %lx\n", totalRW);
  sleep(1);
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
  printf("\nAfter SettingsContext: %lx\n", totalRW);
  sleep(1);
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
      const s16 price = GetRandomScrubPrice();
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
  printf("\nAfter Scrubs1: %lx\n", totalRW);
  sleep(1);
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
  printf("\nAfter Scrubs 2: %lx\n", totalRW);
  sleep(1);
  /*-------------------------------
  |     rShopsanityPrices         |
  --------------------------------*/

  if (Settings::Shopsanity.IsNot(SHOPSANITY_OFF) && Settings::Shopsanity.IsNot(SHOPSANITY_ZERO)) {
    //Get prices from shop item vector
    std::array<s32, 32> rShopsanityPrices{};
    int i = 4;
    while (i < 64) {
      rShopsanityPrices[TransformShopIndex(i)] = ItemTable(ShopItems[i]).GetPrice();
      if (i % 8 == 7) { //Last index for this shop, skip ahead to relevant index of next shop
        i += 5;
      }
      else { //Go to next item within shop
        i++;
      }
    }

    // Write shopsanity item prices address to code
    patchOffset = V_TO_P(RSHOPSANITYPRICES_ADDR);
    buf[0] = (patchOffset >> 16) & 0xFF;
    buf[1] = (patchOffset >> 8) & 0xFF;
    buf[2] = (patchOffset) & 0xFF;
    if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 3, FS_WRITE_FLUSH))) {
      return false;
    }
    totalRW += 3;

    // Write shopsanity item prices size to code
    const u32 shopsanityPricesSize = sizeof(rShopsanityPrices);
    buf[0] = (shopsanityPricesSize >> 8) & 0xFF;
    buf[1] = (shopsanityPricesSize) & 0xFF;
    if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 2, FS_WRITE_FLUSH))) {
      return false;
    }
    totalRW += 2;

    // Write shopsanity item prices to code
    if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, &rShopsanityPrices, sizeof(rShopsanityPrices), FS_WRITE_FLUSH))) {
      return false;
    }
    totalRW += sizeof(rShopsanityPrices);
  }
  printf("\nAfter Shopsanity: %lx\n", totalRW);
  sleep(1);
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
  printf("\nAfter DungeonRewards: %lx\n", totalRW);
  sleep(1);
  /*--------------------------------
  |     rCustomMessageEntries      |
  ---------------------------------*/

  std::pair<const char*, u32> messageDataInfo = CustomMessages::RawMessageData();
  std::pair<const char*, u32> messageEntriesInfo = CustomMessages::RawMessageEntryData();

  // Write message data address to code
  u32 messageDataOffset = V_TO_P(RCUSTOMMESSAGES_ADDR);
  buf[0] = (messageDataOffset >> 16) & 0xFF;
  buf[1] = (messageDataOffset >> 8) & 0xFF;
  buf[2] = (messageDataOffset) & 0xFF;
  if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 3, FS_WRITE_FLUSH))) {
    return false;
  }
  totalRW += 3;

  // Write message data size to code
  const u32 messageDataSize = messageDataInfo.second;
  buf[0] = (messageDataSize >> 8) & 0xFF;
  buf[1] = (messageDataSize) & 0xFF;
  if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 2, FS_WRITE_FLUSH))) {
    return false;
  }
  totalRW += 2;

  // Write message data to code
  if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, messageDataInfo.first, messageDataSize, FS_WRITE_FLUSH))) {
    return false;
  }
  totalRW += messageDataSize;

  // Write message entries address to code
  u32 messageEntriesOffset = (messageDataOffset + messageDataSize + 3) & ~3; //round up and align with u32
  buf[0] = (messageEntriesOffset >> 16) & 0xFF;
  buf[1] = (messageEntriesOffset >> 8) & 0xFF;
  buf[2] = (messageEntriesOffset) & 0xFF;
  if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 3, FS_WRITE_FLUSH))) {
    return false;
  }
  totalRW += 3;

  // Write message entries size to code
  const u32 messageEntriesSize = messageEntriesInfo.second;
  buf[0] = (messageEntriesSize >> 8) & 0xFF;
  buf[1] = (messageEntriesSize) & 0xFF;
  if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 2, FS_WRITE_FLUSH))) {
    return false;
  }
  totalRW += 2;

  // Write message entries to code
  if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, messageEntriesInfo.first, messageEntriesSize, FS_WRITE_FLUSH))) {
    return false;
  }
  totalRW += messageEntriesSize;

  // Write ptrCustomMessageEntries address to code
  patchOffset = V_TO_P(PTRCUSTOMMESSAGEENTRIES_ADDR);
  buf[0] = (patchOffset >> 16) & 0xFF;
  buf[1] = (patchOffset >> 8) & 0xFF;
  buf[2] = (patchOffset) & 0xFF;
  if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 3, FS_WRITE_FLUSH))) {
    return false;
  }
  totalRW += 3;

  // Write ptrCustomMessageEntries size to code
  const u32 ptrCustomMessageEntriesSize = 4;
  buf[0] = (ptrCustomMessageEntriesSize >> 8) & 0xFF;
  buf[1] = (ptrCustomMessageEntriesSize) & 0xFF;
  if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 2, FS_WRITE_FLUSH))) {
    return false;
  }
  totalRW += 2;

  // Write ptrCustomMessageEntries to code
  const u32 ptrCustomMessageEntriesData = P_TO_V(messageEntriesOffset);
  if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, &ptrCustomMessageEntriesData, 4, FS_WRITE_FLUSH))) {
    return false;
  }
  totalRW += 4;

  // Write numCustomMessageEntries address to code
  patchOffset = V_TO_P(NUMCUSTOMMESSAGEENTRIES_ADDR);
  buf[0] = (patchOffset >> 16) & 0xFF;
  buf[1] = (patchOffset >> 8) & 0xFF;
  buf[2] = (patchOffset) & 0xFF;
  if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 3, FS_WRITE_FLUSH))) {
    return false;
  }
  totalRW += 3;

  // Write numCustomMessageEntries size to code
  const u32 numCustomMessageEntriesSize = 4;
  buf[0] = (numCustomMessageEntriesSize >> 8) & 0xFF;
  buf[1] = (numCustomMessageEntriesSize) & 0xFF;
  if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 2, FS_WRITE_FLUSH))) {
    return false;
  }
  totalRW += 2;

  // Write numCustomMessageEntries to code
  const u32 numCustomMessageEntriesData = CustomMessages::NumMessages();
  if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, &numCustomMessageEntriesData, 4, FS_WRITE_FLUSH))) {
    return false;
  }
  totalRW += 4;
  printf("\nAfter CustomMessageEntries: %lx\n", totalRW);
  sleep(1);
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
  buf[0] = (patchOffset >> 16) & 0xFF;
  buf[1] = (patchOffset >> 8) & 0xFF;
  buf[2] = (patchOffset) & 0xFF;
  if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 3, FS_WRITE_FLUSH))) {
    return false;
  }
  totalRW += 3;

  // Write gauntletColors size to code
  const u32 rGauntletColorsSize = sizeof(rGauntletColors);
  buf[0] = (rGauntletColorsSize >> 8) & 0xFF;
  buf[1] = (rGauntletColorsSize) & 0xFF;
  if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, buf, 2, FS_WRITE_FLUSH))) {
    return false;
  }
  totalRW += 2;

  // Write gauntletColors to code
  if (!R_SUCCEEDED(res = FSFILE_Write(code, &bytesWritten, totalRW, rGauntletColors.data(), sizeof(rGauntletColors), FS_WRITE_FLUSH))) {
    return false;
  }
  totalRW += sizeof(rGauntletColors);
  printf("\nAfter Gauntlet Colors: %lx\n", totalRW);
  sleep(1);
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

  // Cosmetics::Color_RGB kokiriTunicColor = Cosmetics::HexStrToColorRGB(Settings::finalKokiriTunicColor);
  // Cosmetics::Color_RGB goronTunicColor  = Cosmetics::HexStrToColorRGB(Settings::finalGoronTunicColor);
  // Cosmetics::Color_RGB zoraTunicColor   = Cosmetics::HexStrToColorRGB(Settings::finalZoraTunicColor);

  CopyFile(sdmcArchive, "/luma/titles/0004000000033500/romfs/actor/zelda_gi_melody.zar", "romfs:/zelda_gi_melody.zar");

  FSUSER_CloseArchive(sdmcArchive);

  return true;
}
