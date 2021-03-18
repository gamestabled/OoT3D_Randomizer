#include "z3D/z3D.h"
#include "settings.h"

u32 EnKz_CheckMovedFlag(void) {
    if ((gSaveContext.eventChkInf[3] & 0x8) || ((gSaveContext.linkAge == AGE_ADULT) && (gSettingsContext.zorasFountain == ZORASFOUNTAIN_ADULT))) {
        return 1;
    } else {
        return 0;
    }
}
