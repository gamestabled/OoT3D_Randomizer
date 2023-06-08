#pragma once
#include <set>
#include <3ds.h>
#include "playthrough.hpp"
#include "settings.hpp"
#include "patch_symbols_USA.hpp"
#include "patch_symbols_EUR.hpp"
#include "../code/src/settings.h"
#include "../code/src/item_override.h"
#include "../code/src/spoiler_data.h"

#define V_TO_P(addr) (addr - 0x100000)
#define P_TO_V(offset) (offset + 0x100000)
#define PATCH_CONSOLE 0
#define PATCH_CITRA 1
#define PATCH_SIZE_MAX 65535

typedef struct {
    u32 GSETTINGSCONTEXT_ADDR;
    u32 GSPOILERDATA_ADDR;
    u32 GSPOILERDATALOCS_ADDR;
    u32 NUMCUSTOMMESSAGEENTRIES_ADDR;
    u32 PTRCUSTOMMESSAGEENTRIES_ADDR;
    u32 RBGMOVERRIDES_ADDR;
    u32 RCUSTOMMESSAGES_ADDR;
    u32 RDUNGEONINFODATA_ADDR;
    u32 RDUNGEONREWARDOVERRIDES_ADDR;
    u32 RENTRANCEOVERRIDES_ADDR;
    u32 RGSLOCOVERRIDES_ADDR;
    u32 RITEMOVERRIDES_ADDR;
    u32 RSCRUBRANDOMITEMPRICES_ADDR;
    u32 RSFXDATA_ADDR;
    u32 RSHOPSANITYPRICES_ADDR;
} PatchSymbols;

extern const PatchSymbols EurSymbols;
extern const PatchSymbols UsaSymbols;

bool WriteAllPatches();
