#include "z3D/z3D.h"
#include "settings.h"

u32 EnKz_CheckMovedFlag(void) {
    if ((gSaveContext.eventChkInf[3] & 0x8) || ((gSaveContext.linkAge == AGE_ADULT) && (/* setting for KZ to be open as adult */ 0))) {
        return 1;
    } else {
        return 0;
    }
}
