#include "ocarina_notes.h"
#include "savefile.h"
#include "settings.h"

s32 OcarinaNotes_IsButtonOwned(OcarinaNoteButton button) {
    return (gSettingsContext.shuffleOcarinaButtons == OFF) ||
           (gExtSaveData.extInf[EXTINF_OCARINA_BUTTONS] & (1 << button));
}

void OcarinaNotes_RegisterButtonOwned(OcarinaNoteButton button) {
    gExtSaveData.extInf[EXTINF_OCARINA_BUTTONS] |= (1 << button);
}

void OcarinaNotes_MoveButtons(void* spriteStruct, Vec2f* posOffset, u32 unk, u32 spriteIndex) {
    if (spriteStruct != OcarinaUIStruct) {
        return;
    }

    u8 shouldDraw = TRUE;

    switch (spriteIndex) {
        case OCS_L_BG_L:
        case OCS_L_BG_M:
        case OCS_L_BG_R:
        case OCS_L_BUTTON:
        case OCS_L_LETTER:
        case OCS_L_SHADOW_L:
        case OCS_L_SHADOW_M:
        case OCS_L_SHADOW_R:
            shouldDraw = OcarinaNotes_IsButtonOwned(OCARINA_BUTTON_L);
            break;
        case OCS_R_BG_L:
        case OCS_R_BG_M:
        case OCS_R_BG_R:
        case OCS_R_BUTTON:
        case OCS_R_LETTER:
        case OCS_R_SHADOW_L:
        case OCS_R_SHADOW_M:
        case OCS_R_SHADOW_R:
            shouldDraw = OcarinaNotes_IsButtonOwned(OCARINA_BUTTON_R);
            break;
        case OCS_X_BG_L:
        case OCS_X_BG_R:
        case OCS_X_BUTTON:
        case OCS_X_LETTER:
        case OCS_X_SHADOW_L:
        case OCS_X_SHADOW_R:
            shouldDraw = OcarinaNotes_IsButtonOwned(OCARINA_BUTTON_X);
            break;
        case OCS_Y_BG_L:
        case OCS_Y_BG_R:
        case OCS_Y_BUTTON:
        case OCS_Y_LETTER:
        case OCS_Y_SHADOW_L:
        case OCS_Y_SHADOW_R:
            shouldDraw = OcarinaNotes_IsButtonOwned(OCARINA_BUTTON_Y);
            break;
        case OCS_A_BG_L:
        case OCS_A_BG_R:
        case OCS_A_BUTTON:
        case OCS_A_LETTER:
        case OCS_A_SHADOW_L:
        case OCS_A_SHADOW_R:
            shouldDraw = OcarinaNotes_IsButtonOwned(OCARINA_BUTTON_A);
            break;
    }

    if (shouldDraw == FALSE) {
        // yeet sprite off-screen
        posOffset->x += 500.0f;
        posOffset->y += 500.0f;
    }
}

u32 OcarinaNotes_HandleInputs(u32 ocarinaInputs) {
    static const u32 btnShifts[5] = { 7, 9, 10, 11, 8 }; // not the same offsets as the btn_t struct
    u32 ownedBtnsMask             = 0;
    for (OcarinaNoteButton btn = 0; btn < 5; btn++) {
        ownedBtnsMask |= (OcarinaNotes_IsButtonOwned(btn) << btnShifts[btn]);
    }
    ocarinaInputs &= ownedBtnsMask;
    return ocarinaInputs;
}
