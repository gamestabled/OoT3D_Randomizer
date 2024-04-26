#ifndef _OCARINA_NOTES_H_
#define _OCARINA_NOTES_H_

#include "z3D/z3D.h"
#include "input.h"

typedef enum OcarinaNoteButton {
    OCARINA_BUTTON_L,
    OCARINA_BUTTON_R,
    OCARINA_BUTTON_X,
    OCARINA_BUTTON_Y,
    OCARINA_BUTTON_A,
} OcarinaNoteButton;

enum OcarinaSprites {
    OCS_L_BG_L = 0x3F,
    OCS_L_BG_M,
    OCS_L_BG_R,
    OCS_L_BUTTON,
    OCS_L_LETTER,
    OCS_R_BG_L,
    OCS_R_BG_M,
    OCS_R_BG_R,
    OCS_R_BUTTON,
    OCS_R_LETTER,
    OCS_X_BG_L,
    OCS_X_BG_R,
    OCS_X_BUTTON,
    OCS_X_LETTER,
    OCS_Y_BG_L,
    OCS_Y_BG_R,
    OCS_Y_BUTTON,
    OCS_Y_LETTER,
    OCS_A_BG_L,
    OCS_A_BG_R,
    OCS_A_BUTTON,
    OCS_A_LETTER,
    OCS_BACK_SHADOW_L,
    OCS_BACK_SHADOW_M,
    OCS_BACK_SHADOW_R,
    OCS_SONGS_SHADOW_L,
    OCS_SONGS_SHADOW_M,
    OCS_SONGS_SHADOW_R,
    OCS_L_SHADOW_L,
    OCS_L_SHADOW_M,
    OCS_L_SHADOW_R,
    OCS_R_SHADOW_L,
    OCS_R_SHADOW_M,
    OCS_R_SHADOW_R,
    OCS_X_SHADOW_L,
    OCS_X_SHADOW_R,
    OCS_Y_SHADOW_L,
    OCS_Y_SHADOW_R,
    OCS_A_SHADOW_L,
    OCS_A_SHADOW_R,
    OCS_YELLOW_MARKER_1,
    OCS_YELLOW_MARKER_2,
    OCS_YELLOW_MARKER_3,
    OCS_YELLOW_MARKER_4,
    OCS_YELLOW_MARKER_5,
}; // max 0x6C

#define OcarinaUIStruct (*((void**)GAME_ADDR(0x5093EC)))

s32 OcarinaNotes_IsButtonOwned(OcarinaNoteButton button);
void OcarinaNotes_RegisterButtonOwned(OcarinaNoteButton button);

#endif //_OCARINA_NOTES_H_
