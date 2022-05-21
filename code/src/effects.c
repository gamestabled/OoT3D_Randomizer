#include "z3D/z3D.h"
#include "settings.h"
#include "colors.h"

typedef struct {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 timer;
    /* 0x08 */ Vec3f p1;
    /* 0x14 */ Vec3f p2;
    /* 0x20 */ u32 flags;
} EffectBlureElement; // size = 0x24

typedef struct {
    /* 0x000 */ EffectBlureElement elements[16];
    /* 0x240 */ char unk_240[0x08];
    /* 0x248 */ u16 flags;
    /* 0x24A */ char unk_24A[0x04];
    /* 0x24E */ Color_RGBA8 p1StartColor;
    /* 0x252 */ Color_RGBA8 p2StartColor;
    /* 0x256 */ Color_RGBA8 p1EndColor;
    /* 0x25A */ Color_RGBA8 p2EndColor;
    /* 0x25E */ u8 numElements;
    /* 0x25F */ u8 elemDuration;
    /* 0x260 */ u8 unkFlag;
    /* 0x261 */ u8 drawMode;
    /* 0x262 */ char unk_262[0x0A];
    /* 0x26C */ u32 unk_pointer_26C;
    /* 0x270 */ u32 unk_pointer_270;
    /* 0x274 */ char unk_274[0x0E];
    /* 0x282 */ u8 unkDrawMode1;
    /* 0x283 */ u8 unkDrawMode2;
} EffectBlure; // size = ??

#define EffectBlure_Update ((void(*)(EffectBlure*))0x227000)

// This function is called when a new effect element tries to spawn but there's no space left.
// The vanilla game simply fails to spawn the new element, but with the randomizer extended duration setting,
// it is best to clear the oldest element to make space instead.
s32 forceTrailEffectUpdate(EffectBlure* effect) {
    if (effect->numElements >= 16) {
        effect->elements[0].state = 0;
        EffectBlure_Update(effect);
    }

    return effect->numElements;
}

void changeRainbowColorRGBA8(Color_RGBA8* color) {
    #define COLOR_SPEED 17 //255 = 3*17*5
    if (color->r == 0xFF && color->g != 0xFF && color->b == 0)
        color->g += COLOR_SPEED;
    else if (color->r != 0 && color->g == 0xFF && color->b == 0)
        color->r -= COLOR_SPEED;
    else if (color->r == 0 && color->g == 0xFF && color->b != 0xFF)
        color->b += COLOR_SPEED;
    else if (color->r == 0 && color->g != 0 && color->b == 0xFF)
        color->g -= COLOR_SPEED;
    else if (color->r != 0xFF && color->g == 0 && color->b == 0xFF)
        color->r += COLOR_SPEED;
    else if (color->r == 0xFF && color->g == 0 && color->b != 0)
        color->b -= COLOR_SPEED;
    else {
        color->r = 0xFF;
        color->g = 0;
        color->b = 0;
    }
}

void updateSwordTrailColors(EffectBlure* effect) {
    if (gSettingsContext.rainbowSwordTrailInnerColor) {
        changeRainbowColorRGBA8(&effect->p2StartColor);
        changeRainbowColorRGBA8(&effect->p2EndColor);
    }
    if (gSettingsContext.rainbowSwordTrailOuterColor) {
        changeRainbowColorRGBA8(&effect->p1StartColor);
        changeRainbowColorRGBA8(&effect->p1EndColor);
    }
}

void updateBoomerangTrailColors(EffectBlure* effect) {

    if (gSettingsContext.customTrailEffects == OFF)
        return;

    if (effect->elemDuration == 8) { // using duration as a "flag" to set the colors only once (8 is vanilla)
        effect->elemDuration = 0x10;

        effect->p1StartColor.r = gSettingsContext.boomerangTrailColor.r;
        effect->p1StartColor.g = gSettingsContext.boomerangTrailColor.g;
        effect->p1StartColor.b = gSettingsContext.boomerangTrailColor.b;
        effect->p1StartColor.a = (gSettingsContext.boomerangTrailColorMode == TRAILCOLOR_FORCEDSIMPLEMODE) ? 0xFA : 0xFF;

        effect->p2StartColor.r = gSettingsContext.boomerangTrailColor.r;
        effect->p2StartColor.g = gSettingsContext.boomerangTrailColor.g;
        effect->p2StartColor.b = gSettingsContext.boomerangTrailColor.b;
        effect->p2StartColor.a = (gSettingsContext.boomerangTrailColorMode == TRAILCOLOR_FORCEDSIMPLEMODE) ? 0x82 : 0xFF;

        effect->p1EndColor.r   = gSettingsContext.boomerangTrailColor.r;
        effect->p1EndColor.g   = gSettingsContext.boomerangTrailColor.g;
        effect->p1EndColor.b   = gSettingsContext.boomerangTrailColor.b;
        effect->p1EndColor.a   = (gSettingsContext.boomerangTrailColorMode == TRAILCOLOR_FORCEDSIMPLEMODE) ? 0x10 : 0xFF;

        effect->p2EndColor.r   = gSettingsContext.boomerangTrailColor.r;
        effect->p2EndColor.g   = gSettingsContext.boomerangTrailColor.g;
        effect->p2EndColor.b   = gSettingsContext.boomerangTrailColor.b;
        effect->p2EndColor.a   = (gSettingsContext.boomerangTrailColorMode == TRAILCOLOR_FORCEDSIMPLEMODE) ? 0x10 : 0xFF;
    }

    if (gSettingsContext.boomerangTrailColorMode == TRAILCOLOR_RAINBOW) {
        changeRainbowColorRGBA8(&effect->p2StartColor);
        changeRainbowColorRGBA8(&effect->p2EndColor);
        changeRainbowColorRGBA8(&effect->p1StartColor);
        changeRainbowColorRGBA8(&effect->p1EndColor);
    }
}

void updateChuTrailColors(EffectBlure* effect) {

    if (gSettingsContext.rainbowChuTrailInnerColor) {
        changeRainbowColorRGBA8(&effect->p2StartColor);
        changeRainbowColorRGBA8(&effect->p2EndColor);
    }
    if (gSettingsContext.rainbowChuTrailOuterColor) {
        changeRainbowColorRGBA8(&effect->p1StartColor);
        changeRainbowColorRGBA8(&effect->p1EndColor);
    }
}
