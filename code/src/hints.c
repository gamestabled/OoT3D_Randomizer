#include "z3D/z3D.h"
#include "settings.h"

#define MASK_OF_TRUTH_ID 8

#define Player_GetMaskFunc_addr 0x36EF98
u8 (*Player_GetMask)(GlobalContext*) = (void *)Player_GetMaskFunc_addr;

u8 Hints_CanReadHints(void) {
    return (gSettingsContext.gossipStoneHints == HINTS_NEED_NOTHING)  ||
           (gSettingsContext.gossipStoneHints == HINTS_MASK_OF_TRUTH  && Player_GetMask(gGlobalContext) == MASK_OF_TRUTH_ID) ||
           (gSettingsContext.gossipStoneHints == HINTS_SHARD_OF_AGONY && (gSaveContext.questItems >> 21) & 0x1);
}
