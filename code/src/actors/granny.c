#include "z3D/z3D.h"
#include "settings.h"

s32 EnDs_GetTextID(void) {
    if ((gSettingsContext.shuffleMerchants == SHUFFLEMERCHANTS_HINTS) && !Flags_GetSwitch(gGlobalContext, 0x32)) {
        return 0x9121; // custom text
    }
    return 0x500C; // vanilla text
}

s32 EnDs_ShouldIgnoreBottle(void) {
    return (gSettingsContext.shuffleMerchants != SHUFFLEMERCHANTS_OFF) && !Flags_GetSwitch(gGlobalContext, 0x32);
}

s32 EnDs_ItemOverride(void) {
    if (gSettingsContext.shuffleMerchants == SHUFFLEMERCHANTS_OFF || Flags_GetSwitch(gGlobalContext, 0x32)) {
        return GI_POTION_BLUE;
    } else {
        return GI_POTION_RED; // will be overridden
    }
}

void EnDs_SetRewardFlag(void) {
    Flags_SetSwitch(gGlobalContext, 0x32);
}
