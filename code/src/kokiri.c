#include "z3D/z3D.h"
#include "settings.h"

u32 EnKo_CheckOpenForest(void) {
    if ((gSettingsContext.openForest == OPENFOREST_OPEN) || (gSaveContext.eventChkInf[0] & 0x80)) {
        return 1;
    } else {
        return 0;
    }
}

u32 EnKo_CheckForestTempleBeat(void) {
    if (EventCheck(0x48) == 0) {
        return 0;
    } else {
        return 1;
    }
}
