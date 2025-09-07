#include "patch.hpp"

#include "cosmetics.hpp"
#include "custom_messages.hpp"
#include "music.hpp"
#include "sound_effects.hpp"
#include "shops.hpp"
#include "spoiler_log.hpp"
#include "entrance.hpp"
#include "hints.hpp"
#include "gold_skulltulas.hpp"
#include "utils.hpp"
#include "enemizer.hpp"

#include <array>
#include <cstring>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "../code/src/custom_models.h"
#include "../code/src/enemizer.h"

const PatchSymbols UsaSymbols = { GSETTINGSCONTEXT_USA_ADDR,
                                  GSPOILERDATA_USA_ADDR,
                                  GSPOILERDATALOCS_USA_ADDR,
                                  NUMCUSTOMMESSAGEENTRIES_USA_ADDR,
                                  PTRCUSTOMMESSAGEENTRIES_USA_ADDR,
                                  RBGMOVERRIDES_USA_ADDR,
                                  RCUSTOMMESSAGES_USA_ADDR,
                                  RDUNGEONINFODATA_USA_ADDR,
                                  RDUNGEONREWARDOVERRIDES_USA_ADDR,
                                  RENEMYOVERRIDES_USA_ADDR,
                                  RENTRANCEOVERRIDES_USA_ADDR,
                                  RGSLOCOVERRIDES_USA_ADDR,
                                  RITEMOVERRIDES_USA_ADDR,
                                  RSCRUBRANDOMITEMPRICES_USA_ADDR,
                                  RSFXDATA_USA_ADDR,
                                  RSHOPSANITYPRICES_USA_ADDR };

const PatchSymbols EurSymbols = { GSETTINGSCONTEXT_EUR_ADDR,
                                  GSPOILERDATA_EUR_ADDR,
                                  GSPOILERDATALOCS_EUR_ADDR,
                                  NUMCUSTOMMESSAGEENTRIES_EUR_ADDR,
                                  PTRCUSTOMMESSAGEENTRIES_EUR_ADDR,
                                  RBGMOVERRIDES_EUR_ADDR,
                                  RCUSTOMMESSAGES_EUR_ADDR,
                                  RDUNGEONINFODATA_EUR_ADDR,
                                  RDUNGEONREWARDOVERRIDES_EUR_ADDR,
                                  RENEMYOVERRIDES_EUR_ADDR,
                                  RENTRANCEOVERRIDES_EUR_ADDR,
                                  RGSLOCOVERRIDES_EUR_ADDR,
                                  RITEMOVERRIDES_EUR_ADDR,
                                  RSCRUBRANDOMITEMPRICES_EUR_ADDR,
                                  RSFXDATA_EUR_ADDR,
                                  RSHOPSANITYPRICES_EUR_ADDR };

// For specification on the IPS file format, visit: https://zerosoft.zophar.net/ips.php

using FILEPtr = std::unique_ptr<FILE, decltype(&std::fclose)>;

bool WritePatch(u32 patchOffset, s32 patchSize, char* patchDataPtr, Handle& code, u32& bytesWritten, u32& totalRW,
                char* buf) {

    // patch sizes greater than PATCH_SIZE_MAX have to be split up due to IPS patching specifications
    while (patchSize > 0) {
        // Write patch offset address to code
        buf[0] = (patchOffset >> 16) & 0xFF;
        buf[1] = (patchOffset >> 8) & 0xFF;
        buf[2] = (patchOffset)&0xFF;
        if (!R_SUCCEEDED(FSFILE_Write(code, &bytesWritten, totalRW, buf, 3, FS_WRITE_FLUSH))) {
            return false;
        }
        totalRW += 3;

        // Write patch size to code
        u32 newPatchSize = (patchSize > PATCH_SIZE_MAX) ? PATCH_SIZE_MAX : patchSize;
        buf[0]           = (newPatchSize >> 8) & 0xFF;
        buf[1]           = (newPatchSize)&0xFF;
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
    CitraPrint("patch.cpp: totalRW=" + std::to_string(totalRW));
#endif
    return true;
}

void WriteFloatToBuffer(std::vector<char>& buffer, float f, size_t offset) {
    memcpy(buffer.data() + offset, &f, sizeof(float));
}

bool WriteAllPatches() {
    Result res             = 0;
    FS_Archive sdmcArchive = 0;
    Handle code;
    u32 bytesWritten = 0;
    u32 totalRW      = 0;
    char buf[512];
    std::string titleId = Settings::TitleId();
    PatchSymbols patchSymbols;
    if (Settings::Region == REGION_EUR) {
        patchSymbols = EurSymbols;
    } else { // REGION_NA
        patchSymbols = UsaSymbols;
    }

    // Open SD archive
    if (!R_SUCCEEDED(res = FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) {
        return false;
    }

    // Create necessary folders where patch files need to go (if they don't exist);
    // Create the luma directory if it doesn't exist (on citra)
    FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, "/luma"), FS_ATTRIBUTE_DIRECTORY);
    // Create the titles directory if it doesn't exist
    FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, "/luma/titles"), FS_ATTRIBUTE_DIRECTORY);
    // Create the 0004000000033500 (33600 for EUR) directory if it doesn't exist (oot3d game id)
    FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, ("/luma/titles/" + titleId).c_str()),
                           FS_ATTRIBUTE_DIRECTORY);
    // Create the romfs directory if it doesn't exist (for LayeredFS)
    FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, ("/luma/titles/" + titleId + "/romfs").c_str()),
                           FS_ATTRIBUTE_DIRECTORY);
    // Create the actor directory if it doesn't exist
    FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, ("/luma/titles/" + titleId + "/romfs/actor").c_str()),
                           FS_ATTRIBUTE_DIRECTORY);

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
    FSUSER_DeleteFile(sdmcArchive, fsMakePath(PATH_ASCII, ("/luma/titles/" + titleId + "/code.ips").c_str()));

    // Open code.ips
    if (!R_SUCCEEDED(res = FSUSER_OpenFile(&code, sdmcArchive,
                                           fsMakePath(PATH_ASCII, ("/luma/titles/" + titleId + "/code.ips").c_str()),
                                           FS_OPEN_WRITE | FS_OPEN_CREATE, 0))) {
        return false;
    }

    // Copy basecode to code
    const char* basecodeFile = Settings::Region == REGION_NA ? "romfs:/basecode_USA.ips" : "romfs:/basecode_EUR.ips";
    if (auto basecode = FILEPtr{ std::fopen(basecodeFile, "r"), std::fclose }) {
        // obtain basecode.ips file size
        fseek(basecode.get(), 0, SEEK_END);
        const auto lSize = static_cast<size_t>(ftell(basecode.get()));
        rewind(basecode.get());

        // copy basecode.ips into the buffer
        std::vector<char> buffer(lSize);
        fread(buffer.data(), 1, buffer.size(), basecode.get());

        // Write the buffer to code.ips
        if (!R_SUCCEEDED(
                res = FSFILE_Write(code, &bytesWritten, totalRW, buffer.data(), buffer.size(), FS_WRITE_FLUSH))) {
            return false;
        }

        totalRW += bytesWritten - 3; // -3 to overwrite EOF
#ifdef ENABLE_DEBUG
        CitraPrint("patch.cpp: totalRW=" + std::to_string(totalRW));
#endif
    }

    /*-------------------------
    |      rItemOverrides     |
    --------------------------*/

    u32 patchOffset                             = V_TO_P(patchSymbols.RITEMOVERRIDES_ADDR);
    s32 patchSize                               = sizeof(ItemOverride) * overrides.size();
    ItemOverride ovrPatchData[overrides.size()] = {};
    // generate override data
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

    patchOffset                                              = V_TO_P(patchSymbols.RENTRANCEOVERRIDES_ADDR);
    patchSize                                                = sizeof(EntranceOverride) * entranceOverrides.size();
    EntranceOverride eOvrPatchData[entranceOverrides.size()] = {};
    // generate entrance override patch data
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

    patchOffset = V_TO_P(patchSymbols.GSETTINGSCONTEXT_ADDR);
    patchSize   = sizeof(SettingsContext);
    // get the settings context
    SettingsContext ctx = Settings::FillContext();
    if (!WritePatch(patchOffset, patchSize, (char*)(&ctx), code, bytesWritten, totalRW, buf)) {
        return false;
    }

    /*-------------------------
    |       gSpoilerData      |
    --------------------------*/

    patchOffset = V_TO_P(patchSymbols.GSPOILERDATA_ADDR);
    patchSize   = sizeof(SpoilerData);
    if (!WritePatch(patchOffset, patchSize, (char*)(GetSpoilerData()), code, bytesWritten, totalRW, buf)) {
        return false;
    }
    patchSize = sizeof(SpoilerDataLocs);
    for (size_t idx = 0; idx < SPOILER_LOCDATS; idx++) {
        patchOffset = V_TO_P(patchSymbols.GSPOILERDATALOCS_ADDR) + (patchSize * idx);
        if (!WritePatch(patchOffset, patchSize, (char*)(GetSpoilerDataLocs(idx)), code, bytesWritten, totalRW, buf)) {
            return false;
        }
    }

    /*-------------------------------
    |     rScrubRandomItemPrices    |
    |     rScrubTextIdTable         |
    --------------------------------*/
    std::array<u16, 11> rScrubTextIdTable{ 0x9014, 0x900F, 0x900A, 0x9028, 0x9032, 0x9028,
                                           0x9046, 0x9028, 0x9028, 0x9028, 0x9028 };

    // Only fill prices in if random prices
    if (ctx.scrubsanity == SCRUBSANITY_RANDOM_PRICES) {
        // Create array of random prices
        std::array<s16, 11> rScrubRandomItemPrices{};
        for (i = 0; i < rScrubRandomItemPrices.size(); i++) {
            const s16 price           = GetRandomScrubPrice();
            rScrubRandomItemPrices[i] = price;
            rScrubTextIdTable[i]      = static_cast<u16>(0x9000 + static_cast<u16>(price));
        }

        // Write the patch for random scrub prices
        patchOffset = V_TO_P(patchSymbols.RSCRUBRANDOMITEMPRICES_ADDR);
        patchSize   = sizeof(rScrubRandomItemPrices);
        if (!WritePatch(patchOffset, patchSize, (char*)(&rScrubRandomItemPrices), code, bytesWritten, totalRW, buf)) {
            return false;
        }

    } else if (ctx.scrubsanity == SCRUBSANITY_AFFORDABLE) {
        // If affordable is set, write all text IDs as the 10 rupee price ID
        rScrubTextIdTable.fill(0x900A);
    }
    if (ctx.scrubsanity != SCRUBSANITY_OFF) {
        // Write the patch for the scrub text ID table
        patchOffset = V_TO_P(0x52236C); // this is the address of the base game's scrub textId table
        patchSize   = sizeof(rScrubTextIdTable);
        if (!WritePatch(patchOffset, patchSize, (char*)(&rScrubTextIdTable), code, bytesWritten, totalRW, buf)) {
            return false;
        }
    }

    /*-------------------------------
    |     rShopsanityPrices         |
    --------------------------------*/

    if (Settings::Shopsanity.IsNot(SHOPSANITY_OFF) && Settings::Shopsanity.IsNot(SHOPSANITY_ZERO)) {
        // Get prices from shop item vector
        std::array<s32, 32> rShopsanityPrices{};
        for (i = 0; i < 32; i++) {
            rShopsanityPrices[i] = NonShopItems[i].Price;
        }

        // Write shopsanity item prices to the patch
        patchOffset = V_TO_P(patchSymbols.RSHOPSANITYPRICES_ADDR);
        patchSize   = sizeof(rShopsanityPrices);
        if (!WritePatch(patchOffset, patchSize, (char*)(&rShopsanityPrices), code, bytesWritten, totalRW, buf)) {
            return false;
        }
    }

    /*--------------------------------
    |     rDungeonRewardOverrides    |
    ---------------------------------*/
    // Write rDungeonRewardOverrides to the patch
    if (Settings::ShuffleRewards.Is(REWARDSHUFFLE_END_OF_DUNGEON)) {
        patchOffset = V_TO_P(patchSymbols.RDUNGEONREWARDOVERRIDES_ADDR);
        patchSize   = sizeof(Settings::rDungeonRewardOverrides);
        if (!WritePatch(patchOffset, patchSize, (char*)(&Settings::rDungeonRewardOverrides), code, bytesWritten,
                        totalRW, buf)) {
            return false;
        }
    }

    /*--------------------------------
    |     rCustomMessageEntries      |
    ---------------------------------*/

    std::pair<const char*, u32> messageDataInfo    = CustomMessages::RawMessageData();
    std::pair<const char*, u32> messageEntriesInfo = CustomMessages::RawMessageEntryData();

    // Write message data to patch
    u32 messageDataOffset = V_TO_P(patchSymbols.RCUSTOMMESSAGES_ADDR);
    s32 messageDataSize   = messageDataInfo.second;
    if (!WritePatch(messageDataOffset, messageDataSize, (char*)messageDataInfo.first, code, bytesWritten, totalRW,
                    buf)) {
        return false;
    }

    // Write message entries to patch
    u32 messageEntriesOffset = (messageDataOffset + messageDataSize + 3) & ~3; // round up and align with u32
    s32 messageEntriesSize   = messageEntriesInfo.second;
    if (!WritePatch(messageEntriesOffset, messageEntriesSize, (char*)messageEntriesInfo.first, code, bytesWritten,
                    totalRW, buf)) {
        return false;
    }

    // Write ptrCustomMessageEntries to patch
    patchOffset                     = V_TO_P(patchSymbols.PTRCUSTOMMESSAGEENTRIES_ADDR);
    patchSize                       = 4;
    u32 ptrCustomMessageEntriesData = P_TO_V(messageEntriesOffset);
    if (!WritePatch(patchOffset, patchSize, (char*)(&ptrCustomMessageEntriesData), code, bytesWritten, totalRW, buf)) {
        return false;
    }

    // Write numCustomMessageEntries to code
    patchOffset                     = V_TO_P(patchSymbols.NUMCUSTOMMESSAGEENTRIES_ADDR);
    patchSize                       = 4;
    u32 numCustomMessageEntriesData = CustomMessages::NumMessages();
    if (!WritePatch(patchOffset, patchSize, (char*)(&numCustomMessageEntriesData), code, bytesWritten, totalRW, buf)) {
        return false;
    }

    /*--------------------------------
    |       Extra Arrow Effects      |
    ---------------------------------*/

    const u32 BREAKWALL_BUMPERFLAGS_ADDR = 0x00510C80;
    const u32 ARROW_ATFLAGS_ADDR         = 0x00520749;
    const u32 SUNSWITCH_BUMPERFLAGS_ADDR = 0x00535390;

    u32 patchOffset_Breakwall = V_TO_P(BREAKWALL_BUMPERFLAGS_ADDR);
    u32 patchOffset_Arrow     = V_TO_P(ARROW_ATFLAGS_ADDR);
    u32 patchOffset_SunSwitch = V_TO_P(SUNSWITCH_BUMPERFLAGS_ADDR);

    u8 arrowAtFlags          = 0x29;       // adding AT_TYPE_OTHER (0x20)
    u32 breakwallBumperFlags = 0x00001048; // adding Ice Arrow damage (0x00001000)
    u32 sunSwitchBumperFlags = 0x00202000; // adding Light Arrow damage (0x00002000)

    if (ctx.extraArrowEffects && (!WritePatch(patchOffset_Breakwall, sizeof(breakwallBumperFlags),
                                              (char*)(&breakwallBumperFlags), code, bytesWritten, totalRW, buf) ||
                                  !WritePatch(patchOffset_Arrow, sizeof(arrowAtFlags), (char*)(&arrowAtFlags), code,
                                              bytesWritten, totalRW, buf) ||
                                  !WritePatch(patchOffset_SunSwitch, sizeof(sunSwitchBumperFlags),
                                              (char*)(&sunSwitchBumperFlags), code, bytesWritten, totalRW, buf))) {
        return false;
    }

    /*--------------------------------
    |         rBGMOverrides          |
    ---------------------------------*/

    // Only write patch if index variant of music shuffle is used
    if (!Music::archiveFound) {
        patchOffset = V_TO_P(patchSymbols.RBGMOVERRIDES_ADDR);
        patchSize   = sizeof(Music::seqOverridesMusic);
        if (!WritePatch(patchOffset, patchSize, (char*)Music::seqOverridesMusic.data(), code, bytesWritten, totalRW,
                        buf)) {
            return false;
        }
    }

    /*---------------------------------
    |            rSfxData             |
    ---------------------------------*/

    patchOffset = V_TO_P(patchSymbols.RSFXDATA_ADDR);
    patchSize   = sizeof(SFXData);
    if (!WritePatch(patchOffset, patchSize, (char*)(&SFX::GetSFXData()), code, bytesWritten, totalRW, buf)) {
        return false;
    }

    /*---------------------------------
    |        rDungeonInfoData         |
    ---------------------------------*/

    patchOffset = V_TO_P(patchSymbols.RDUNGEONINFODATA_ADDR);
    patchSize   = sizeof(dungeonInfoData);
    if (!WritePatch(patchOffset, patchSize, (char*)(&dungeonInfoData), code, bytesWritten, totalRW, buf)) {
        return false;
    }

    /*--------------------------------
    |         Gauntlet Colors        |
    ---------------------------------*/

    const u32 GAUNTLETCOLORSARRAY_ADDR = 0x0053CA1C;
    const std::array rGauntletColors{
        Cosmetics::HexStrToColorRGBAf(Settings::finalSilverGauntletsColor),
        Cosmetics::HexStrToColorRGBAf(Settings::finalGoldGauntletsColor),
    };

    // Write Gauntlet Colors address to code
    patchOffset = V_TO_P(GAUNTLETCOLORSARRAY_ADDR);
    patchSize   = sizeof(rGauntletColors);
    if (!WritePatch(patchOffset, patchSize, (char*)rGauntletColors.data(), code, bytesWritten, totalRW, buf)) {
        return false;
    }

    /*--------------------------------
    |           Navi Colors          |
    ---------------------------------*/

    const u32 NAVICOLORSARRAY_ADDR = 0x0050C998;
    const std::array rNaviColors{
        Cosmetics::HexStrToColorRGBA8(Settings::finalPropNaviInnerColor),
        Cosmetics::HexStrToColorRGBA8(Settings::finalPropNaviOuterColor),

        Cosmetics::HexStrToColorRGBA8(Settings::finalPropNaviInnerColor),
        Cosmetics::HexStrToColorRGBA8(Settings::finalPropNaviOuterColor),

        Cosmetics::HexStrToColorRGBA8(Settings::finalIdleNaviInnerColor),
        Cosmetics::HexStrToColorRGBA8(Settings::finalIdleNaviOuterColor),

        Cosmetics::HexStrToColorRGBA8(Settings::finalPropNaviInnerColor),
        Cosmetics::HexStrToColorRGBA8(Settings::finalPropNaviOuterColor),

        Cosmetics::HexStrToColorRGBA8(Settings::finalNPCNaviInnerColor),
        Cosmetics::HexStrToColorRGBA8(Settings::finalNPCNaviOuterColor),

        Cosmetics::HexStrToColorRGBA8(Settings::finalEnemyNaviInnerColor),
        Cosmetics::HexStrToColorRGBA8(Settings::finalEnemyNaviOuterColor),

        Cosmetics::HexStrToColorRGBA8(Settings::finalPropNaviInnerColor),
        Cosmetics::HexStrToColorRGBA8(Settings::finalPropNaviOuterColor),

        Cosmetics::HexStrToColorRGBA8(Settings::finalPropNaviInnerColor),
        Cosmetics::HexStrToColorRGBA8(Settings::finalPropNaviOuterColor),

        Cosmetics::HexStrToColorRGBA8(Settings::finalPropNaviInnerColor),
        Cosmetics::HexStrToColorRGBA8(Settings::finalPropNaviOuterColor),

        Cosmetics::HexStrToColorRGBA8(Settings::finalEnemyNaviInnerColor),
        Cosmetics::HexStrToColorRGBA8(Settings::finalEnemyNaviOuterColor),

        Cosmetics::HexStrToColorRGBA8(Settings::finalPropNaviInnerColor),
        Cosmetics::HexStrToColorRGBA8(Settings::finalPropNaviOuterColor),

        Cosmetics::HexStrToColorRGBA8(Settings::finalPropNaviInnerColor),
        Cosmetics::HexStrToColorRGBA8(Settings::finalPropNaviOuterColor),

        Cosmetics::HexStrToColorRGBA8(Settings::finalPropNaviInnerColor),
        Cosmetics::HexStrToColorRGBA8(Settings::finalPropNaviOuterColor),
    };

    // Write Navi Colors address to code
    patchOffset = V_TO_P(NAVICOLORSARRAY_ADDR);
    patchSize   = sizeof(rNaviColors);
    if (ctx.customNaviColors &&
        !WritePatch(patchOffset, patchSize, (char*)rNaviColors.data(), code, bytesWritten, totalRW, buf)) {
        return false;
    }

    /*--------------------------------
    |           Sword Trails         |
    ---------------------------------*/

    const u32 SWORDTRAILCOLORSARRAY_ADDR = 0x0053C136;
    Color_RGBA8 p1StartColor             = Cosmetics::HexStrToColorRGBA8(Settings::finalSwordTrailOuterColor);
    Color_RGBA8 p2StartColor             = Cosmetics::HexStrToColorRGBA8(Settings::finalSwordTrailInnerColor);
    Color_RGBA8 p1EndColor               = Cosmetics::HexStrToColorRGBA8(Settings::finalSwordTrailOuterColor);
    Color_RGBA8 p2EndColor               = Cosmetics::HexStrToColorRGBA8(Settings::finalSwordTrailInnerColor);
    bool shouldDrawSimple                = Settings::ChosenSimpleMode ||
                            (p1StartColor.r != 0xFF && p1StartColor.g != 0xFF && p1StartColor.b != 0xFF) ||
                            (p2StartColor.r != 0xFF && p2StartColor.g != 0xFF && p2StartColor.b != 0xFF);
    // Restore original alpha for End colors
    p1EndColor.a = 0;
    p2EndColor.a = 0;
    if (shouldDrawSimple) {
        p1StartColor.a = 0xC0;
        p2StartColor.a = 0xC0;
    }

    const std::array rSwordTrailColors{ p1StartColor, p2StartColor, p1EndColor, p2EndColor };

    // Write Sword Trail Colors address to code
    patchOffset = V_TO_P(SWORDTRAILCOLORSARRAY_ADDR);
    patchSize   = sizeof(rSwordTrailColors);
    if (ctx.customTrailEffects &&
        !WritePatch(patchOffset, patchSize, (char*)rSwordTrailColors.data(), code, bytesWritten, totalRW, buf)) {
        return false;
    }

    const u32 SWORDTRAILDURATION_ADDR = 0x0053C146;
    char rSwordTrailDuration          = 6;
    switch (Settings::SwordTrailDuration.Value<u8>()) {
        case TRAILDURATION_DISABLED:
            rSwordTrailDuration = 0;
            break;
        case TRAILDURATION_VERYSHORT:
            rSwordTrailDuration = 3;
            break;
        case TRAILDURATION_VANILLA:
            rSwordTrailDuration = 6;
            break;
        case TRAILDURATION_LONG:
            rSwordTrailDuration = 16;
            break;
        case TRAILDURATION_VERYLONG:
            rSwordTrailDuration = 24;
            break;
        case TRAILDURATION_LIGHTSABER:
            rSwordTrailDuration = 32;
            break;
    }

    // Write Sword Trail Duration to code
    patchOffset = V_TO_P(SWORDTRAILDURATION_ADDR);
    patchSize   = sizeof(rSwordTrailDuration);
    if (!WritePatch(patchOffset, patchSize, &rSwordTrailDuration, code, bytesWritten, totalRW, buf)) {
        return false;
    }

    const u32 SWORDTRAILUNKMODE_ADDR = 0x0053C158;
    char rSwordTrailUnkMode          = 0; // Mode 0 is needed to draw black.

    // Write Sword Trail UnkMode to code
    patchOffset = V_TO_P(SWORDTRAILUNKMODE_ADDR);
    patchSize   = sizeof(rSwordTrailUnkMode);
    if (ctx.customTrailEffects && shouldDrawSimple &&
        !WritePatch(patchOffset, patchSize, &rSwordTrailUnkMode, code, bytesWritten, totalRW, buf)) {
        return false;
    }

    /*--------------------------------
    |         Bombchu Trails         |
    ---------------------------------*/

    const u32 BOMBCHUTRAILCOLORSARRAY_ADDR = 0x00521248;
    p1StartColor                           = Cosmetics::HexStrToColorRGBA8(Settings::finalChuTrailOuterColor);
    p2StartColor                           = Cosmetics::HexStrToColorRGBA8(Settings::finalChuTrailInnerColor);
    p1EndColor                             = Cosmetics::HexStrToColorRGBA8(Settings::finalChuTrailOuterColor);
    p2EndColor                             = Cosmetics::HexStrToColorRGBA8(Settings::finalChuTrailInnerColor);
    // Restore original alpha
    p1StartColor.a = 0xFA;
    p2StartColor.a = 0x82;
    p1EndColor.a   = 0x34;
    p2EndColor.a   = 0x62;

    const std::array rBombchuTrailColors{ p1StartColor, p2StartColor, p1EndColor, p2EndColor };

    // Write Bombchu Trail Colors address to code
    patchOffset = V_TO_P(BOMBCHUTRAILCOLORSARRAY_ADDR);
    patchSize   = sizeof(rBombchuTrailColors);
    if (ctx.customTrailEffects &&
        !WritePatch(patchOffset, patchSize, (char*)rBombchuTrailColors.data(), code, bytesWritten, totalRW, buf)) {
        return false;
    }

    const u32 BOMBCHUTRAILUNKMODE_ADDR =
        0x0020EAB4; // This is part of an ASM instruction, "mov r0,#0xE". Mode 0 is needed to draw black and blue.
    char rBombchuTrailUnkMode = 0;

    // Write Bombchu Trail UnkMode address to code
    patchOffset = V_TO_P(BOMBCHUTRAILUNKMODE_ADDR);
    patchSize   = sizeof(rBombchuTrailUnkMode);
    if (ctx.customTrailEffects &&
        !WritePatch(patchOffset, patchSize, &rBombchuTrailUnkMode, code, bytesWritten, totalRW, buf)) {
        return false;
    }

    /*--------------------------------
    |        Boomerang Trails        |
    ---------------------------------*/

    /*
    Colors are not set here, because they're not saved as data in the game, they're set with ASM instructions instead.
    So it's easier to use a patch in oot.ld to change them.
    */

    // variable from Sword Trails
    shouldDrawSimple = Settings::ChosenSimpleMode || ctx.boomerangTrailColorMode == TRAILCOLOR_FORCEDSIMPLEMODE ||
                       ctx.boomerangTrailColorMode == TRAILCOLOR_RAINBOW_SIMPLEMODE;

    const u32 BOOMERANGTRAILUNKMODE_ADDR = 0x001ADB18; // This is part of an ASM instruction, "mov r0,#0xC"
    char rBoomerangTrailUnkMode          = 0;
    // As for Bombchus, setting this to 0 is needed to draw dark colors, but this time this will actually change how the
    // trail looks like. So it should only be done if the chosen color doesn't have any component at max level.

    // Write Boomerang Trail UnkMode address to code
    patchOffset = V_TO_P(BOOMERANGTRAILUNKMODE_ADDR);
    patchSize   = sizeof(rBoomerangTrailUnkMode);
    if (ctx.customTrailEffects && shouldDrawSimple &&
        !WritePatch(patchOffset, patchSize, &rBoomerangTrailUnkMode, code, bytesWritten, totalRW, buf)) {
        return false;
    }

    /*---------------------------------
    |     Gold Skulltula Locations    |
    ---------------------------------*/

    patchOffset = V_TO_P(patchSymbols.RGSLOCOVERRIDES_ADDR);
    patchSize   = sizeof(GsLocOverride) * Gs_GetOverrideData()->size();

    if (!WritePatch(patchOffset, patchSize, (char*)Gs_GetOverrideData()->data(), code, bytesWritten, totalRW, buf)) {
        return false;
    }

    /*---------------------------------
    |   Sold Out Cosmetic Shop Model  |
    ---------------------------------*/

    const u32 SHOPITEMENTRY_SOLDOUT_CMBINDEX_ADDR = 0x525672;
    char soldOutCMBIndex                          = 0;

    patchOffset = V_TO_P(SHOPITEMENTRY_SOLDOUT_CMBINDEX_ADDR);
    patchSize   = 1;

    if (Settings::BetaSoldOut &&
        !WritePatch(patchOffset, patchSize, &soldOutCMBIndex, code, bytesWritten, totalRW, buf)) {
        return false;
    }

    /*---------------------------------
    |         Enemy Overrides         |
    ---------------------------------*/

    if (Settings::Enemizer) {
        std::vector<EnemyOverride> enemyOverrides;
        Enemizer::FillPatchOverrides(enemyOverrides);

        patchOffset = V_TO_P(patchSymbols.RENEMYOVERRIDES_ADDR);
        patchSize   = sizeof(EnemyOverride) * enemyOverrides.size();

        if (!WritePatch(patchOffset, patchSize, (char*)enemyOverrides.data(), code, bytesWritten, totalRW, buf)) {
            return false;
        }
    }

    /*-------------------------
    |           EOF           |
    --------------------------*/

    // Write EOF to code
    if (!R_SUCCEEDED(res =
                         FSFILE_Write(code, &bytesWritten, totalRW, "EOF", 3, FS_WRITE_FLUSH | FS_WRITE_UPDATE_TIME))) {
        return false;
    }

    FSFILE_Close(code);

    /*-------------------------
    |       exheader.bin      |
    --------------------------*/
    // Get exheader for proper playOption
    const char* filePath;
    if (Settings::PlayOption == PATCH_CONSOLE) {
        filePath = "romfs:/exheader.bin";
    } else {
        filePath = "romfs:/exheader_citra.bin";
    }

    CopyFile(sdmcArchive, ("/luma/titles/" + titleId + "/exheader.bin").c_str(), filePath);

    /*-------------------------
    |       custom assets      |
    --------------------------*/

    Color_RGBAf childTunicColor  = Cosmetics::HexStrToColorRGBAf(Settings::finalChildTunicColor);
    Color_RGBAf kokiriTunicColor = Cosmetics::HexStrToColorRGBAf(Settings::finalKokiriTunicColor);
    Color_RGBAf goronTunicColor  = Cosmetics::HexStrToColorRGBAf(Settings::finalGoronTunicColor);
    Color_RGBAf zoraTunicColor   = Cosmetics::HexStrToColorRGBAf(Settings::finalZoraTunicColor);

    // Delete assets if it exists
    Handle assetsOut;
    std::string assetsOutPath = "/luma/titles/" + titleId + "/romfs/actor/zelda_gi_melody.zar";
    const char* assetsInPath  = "romfs:/zelda_gi_melody.zar";
    FSUSER_DeleteFile(sdmcArchive, fsMakePath(PATH_ASCII, assetsOutPath.c_str()));

    // Open assets destination
    if (!R_SUCCEEDED(res = FSUSER_OpenFile(&assetsOut, sdmcArchive, fsMakePath(PATH_ASCII, assetsOutPath.c_str()),
                                           FS_OPEN_WRITE | FS_OPEN_CREATE, 0))) {
        return false;
    }

    if (auto file = FILEPtr{ std::fopen(assetsInPath, "r"), std::fclose }) {
        // obtain assets size
        fseek(file.get(), 0, SEEK_END);
        const auto lSize = static_cast<size_t>(ftell(file.get()));
        rewind(file.get());

        // copy assets into the buffer
        std::vector<char> buffer(lSize);
        fread(buffer.data(), 1, buffer.size(), file.get());

        // obtain offsets for tunic textures
        size_t dataSectionOffsetInZAR = *(size_t*)(buffer.data() + 0x14);
        size_t adultTunicOffsetInZAR  = *(size_t*)(buffer.data() + dataSectionOffsetInZAR + TEXANIM_LINK_BODY * 4);
        size_t childTunicOffsetInZAR = *(size_t*)(buffer.data() + dataSectionOffsetInZAR + TEXANIM_CHILD_LINK_BODY * 4);

        // edit assets as needed
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
        if (!R_SUCCEEDED(res =
                             FSFILE_Write(assetsOut, &bytesWritten, 0, buffer.data(), buffer.size(), FS_WRITE_FLUSH))) {
            return false;
        }
    }
    FSFILE_Close(assetsOut);

    FSUSER_CloseArchive(sdmcArchive);

    romfsExit();

    return true;
}
