#include "z3D/z3D.h"
#include "settings.h"

s32 EnGm_CheckRewardFlag(void) {
    // 0: blt, skip equipment check
    // 1: beq, goto text id 304D, no item offer
    // 2: continue like normal
    if (gSettingsContext.shuffleMerchants != SHUFFLEMERCHANTS_OFF && (gSaveContext.eventChkInf[3] & 0x20) == 0) {
        return 0;
    } else if (gSettingsContext.progressiveGoronSword && ((gSaveContext.equipment >> 2) & 0x1) == 0) {
        return 1;
    }
    return 2;
}

void EnGm_SetRewardFlag(void) {
    gSaveContext.eventChkInf[3] |= 0x20;
}

s32 EnGm_UseCustomText(void) {
    return (gSettingsContext.shuffleMerchants != SHUFFLEMERCHANTS_OFF && (gSaveContext.eventChkInf[3] & 0x20) == 0);
}

s32 EnGm_ItemOverride(void) {
    if (gSettingsContext.shuffleMerchants == SHUFFLEMERCHANTS_OFF || gSaveContext.eventChkInf[3] & 0x20) {
        return GI_SWORD_KNIFE;
    } else {
        return GI_MASK_GORON;
    }
}
