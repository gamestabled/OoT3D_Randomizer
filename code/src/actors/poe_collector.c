#include "z3D/z3D.h"
#include "settings.h"

u32 EnGb_CheckPoints(u32 points) {
    return (points == (gSettingsContext.bigPoeTargetCount * 100));
}

u16 EnGb_GetFirstTextbox(void) {
    return 0x9080 + gSettingsContext.bigPoeTargetCount;
}
