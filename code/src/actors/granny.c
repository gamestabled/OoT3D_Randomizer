#include "z3D/z3D.h"
#include "settings.h"

#define GRANNY_FLAG (gSaveContext.eventChkInf[3] & 0x04)

s32 EnDs_GetTextID(void) {
    if ((gSettingsContext.shuffleMerchants != SHUFFLEMERCHANTS_OFF) && !GRANNY_FLAG) {
        return 0x9121; // custom text
    }
    return 0x500C; // vanilla text
}

s32 EnDs_ShouldIgnoreBottle(void) {
    return (gSettingsContext.shuffleMerchants != SHUFFLEMERCHANTS_OFF) && !GRANNY_FLAG;
}

s32 EnDs_ItemOverride(void) {
    if (gSettingsContext.shuffleMerchants == SHUFFLEMERCHANTS_OFF || GRANNY_FLAG) {
        return GI_POTION_BLUE;
    } else {
        return GI_POTION_RED; // will be overridden
    }
}

void EnDs_SetRewardFlag(void) {
    gSaveContext.eventChkInf[3] |= 0x04;
}
