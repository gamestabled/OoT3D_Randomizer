#include "z3D/z3D.h"
#include "settings.h"

s32 EnGm_CheckRewardFlag(void) {
    if (gSettingsContext.shuffleMerchants == SHUFFLEMERCHANTS_OFF) {
        return 2;
    }
    return (gSaveContext.eventChkInf[3] & 0x20) != 0;
}

void EnGm_SetRewardFlag(void) {
    if (gSettingsContext.shuffleMerchants != SHUFFLEMERCHANTS_OFF) {
        gSaveContext.eventChkInf[3] |= 0x20;
    }
}
