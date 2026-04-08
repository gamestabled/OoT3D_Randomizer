#pragma once
#include <set>
#include <3ds.h>
#include "playthrough.hpp"
#include "settings.hpp"
#include "../code/src/settings.h"
#include "../code/src/item_override.h"
#include "../code/src/spoiler_data.h"

#define V_TO_P(addr) (addr - 0x100000)
#define P_TO_V(offset) (offset + 0x100000)
#define PATCH_CONSOLE 0
#define PATCH_CITRA 1
#define PATCH_SIZE_MAX 65535

typedef struct PatchSymbols {
    u32 rItemOverrides;
    u32 gSettingsContext;
    u32 gSpoilerData;
    u32 gSpoilerDataLocs;
    u32 rScrubRandomItemPrices;
    u32 rDungeonRewardOverrides;
    u32 rCustomMessages;
    u32 numCustomMessageEntries;
    u32 ptrCustomMessageEntries;
    u32 rShopsanityPrices;
    u32 rEntranceOverrides;
    u32 rBGMOverrides;
    u32 rSfxData;
    u32 rDungeonInfoData;
    u32 rGsLocOverrides;
    u32 rEnemyOverrides;
} PatchSymbols;

extern const PatchSymbols gPatchSymbols;

bool WriteAllPatches();
