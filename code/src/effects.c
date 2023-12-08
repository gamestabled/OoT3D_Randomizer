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

#define EffectBlure_Update ((void (*)(EffectBlure*))0x227000)

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

#define SWORD_CYCLE_FRAMES_INNER 18
#define SWORD_CYCLE_FRAMES_OUTER 15
void updateSwordTrailColors(EffectBlure* effect) {
    if (gSettingsContext.rainbowSwordTrailInnerColor) {
        Colors_ChangeRainbowColorRGBA8(&effect->p2StartColor, SWORD_CYCLE_FRAMES_INNER, 0);
        Colors_ChangeRainbowColorRGBA8(&effect->p2EndColor, SWORD_CYCLE_FRAMES_INNER, 0);
    }
    if (gSettingsContext.rainbowSwordTrailOuterColor) {
        Colors_ChangeRainbowColorRGBA8(&effect->p1StartColor, SWORD_CYCLE_FRAMES_OUTER, 0);
        Colors_ChangeRainbowColorRGBA8(&effect->p1EndColor, SWORD_CYCLE_FRAMES_OUTER, 0);
    }
}

// This function is used to extend the duration of trails by drawing them less frequently.
s32 handleLongTrails(u8 durationSetting, EffectBlure* effect, Vec3f* p1, Vec3f* p2) {
    if (durationSetting <= TRAILDURATION_VANILLA || effect->elements[0].timer % (effect->elemDuration / 16) == 0) {
        return 1;
    } else {
        // If not drawing a new trail element, "pull" the most recent one to the new position
        for (s32 i = 15; i > 0; i--) {
            if (effect->elements[i].state == 1) {
                effect->elements[i].p1.x = p1->x;
                effect->elements[i].p1.y = p1->y;
                effect->elements[i].p1.z = p1->z;
                effect->elements[i].p2.x = p2->x;
                effect->elements[i].p2.y = p2->y;
                effect->elements[i].p2.z = p2->z;
                return 0;
            }
        }
        // For the first trail element, create a copy so that one stays in place and the other can be "pulled"
        effect->elements[1] = effect->elements[0];
        effect->numElements++;
    }
    return 0;
}

#define BOOM_CYCLE_FRAMES_INNER 9
#define BOOM_CYCLE_FRAMES_OUTER 7
u32 updateBoomerangTrailEffect(EffectBlure* effect, Vec3f* p1, Vec3f* p2) {
    u8 isRainbow = gSettingsContext.boomerangTrailColorMode == TRAILCOLOR_RAINBOW ||
                   gSettingsContext.boomerangTrailColorMode == TRAILCOLOR_RAINBOW_SIMPLEMODE;
    u8 isSimpleMode = gSettingsContext.boomerangTrailColorMode == TRAILCOLOR_FORCEDSIMPLEMODE ||
                      gSettingsContext.boomerangTrailColorMode == TRAILCOLOR_RAINBOW_SIMPLEMODE;

    if (gSettingsContext.customTrailEffects == OFF)
        return 1;

    if (effect->elemDuration == 8) { // using duration as a "flag" to set the colors only once (8 is vanilla)
        switch (gSettingsContext.boomerangTrailDuration) {
            case TRAILDURATION_DISABLED:
                effect->elemDuration = 0;
                break;
            case TRAILDURATION_VERYSHORT:
                effect->elemDuration = 4;
                break;
            case TRAILDURATION_VANILLA:
                effect->elemDuration = 9;
                break;
            case TRAILDURATION_LONG:
                effect->elemDuration = 16;
                break;
            case TRAILDURATION_VERYLONG:
                effect->elemDuration = 32;
                break;
            case TRAILDURATION_LIGHTSABER:
                effect->elemDuration = 64;
                break;
        }

        effect->p1StartColor.r = gSettingsContext.boomerangTrailColor.r;
        effect->p1StartColor.g = gSettingsContext.boomerangTrailColor.g;
        effect->p1StartColor.b = gSettingsContext.boomerangTrailColor.b;
        effect->p1StartColor.a = isSimpleMode ? 0xFA : 0xFF;

        effect->p2StartColor.r = gSettingsContext.boomerangTrailColor.r;
        effect->p2StartColor.g = gSettingsContext.boomerangTrailColor.g;
        effect->p2StartColor.b = gSettingsContext.boomerangTrailColor.b;
        effect->p2StartColor.a = isSimpleMode ? 0x82 : 0xFF;

        effect->p1EndColor.r = gSettingsContext.boomerangTrailColor.r;
        effect->p1EndColor.g = gSettingsContext.boomerangTrailColor.g;
        effect->p1EndColor.b = gSettingsContext.boomerangTrailColor.b;
        effect->p1EndColor.a = isSimpleMode ? 0x10 : 0xFF;

        effect->p2EndColor.r = gSettingsContext.boomerangTrailColor.r;
        effect->p2EndColor.g = gSettingsContext.boomerangTrailColor.g;
        effect->p2EndColor.b = gSettingsContext.boomerangTrailColor.b;
        effect->p2EndColor.a = isSimpleMode ? 0x10 : 0xFF;
    }

    if (isRainbow) {
        Colors_ChangeRainbowColorRGBA8(&effect->p2StartColor, BOOM_CYCLE_FRAMES_INNER, 0);
        Colors_ChangeRainbowColorRGBA8(&effect->p2EndColor, BOOM_CYCLE_FRAMES_INNER, 2);
        Colors_ChangeRainbowColorRGBA8(&effect->p1StartColor, BOOM_CYCLE_FRAMES_OUTER, 0);
        Colors_ChangeRainbowColorRGBA8(&effect->p1EndColor, BOOM_CYCLE_FRAMES_OUTER, 2);
    }

    return handleLongTrails(gSettingsContext.boomerangTrailDuration, effect, p1, p2);
}

#define BOMBCHU_CYCLE_FRAMES_INNER 12
#define BOMBCHU_CYCLE_FRAMES_OUTER 9
u32 updateChuTrailColors(EffectBlure* effect, Vec3f* p1, Vec3f* p2) {

    if (gSettingsContext.rainbowChuTrailInnerColor) {
        Colors_ChangeRainbowColorRGBA8(&effect->p2StartColor, BOMBCHU_CYCLE_FRAMES_INNER, 0);
        Colors_ChangeRainbowColorRGBA8(&effect->p2EndColor, BOMBCHU_CYCLE_FRAMES_INNER, 2);
    }
    if (gSettingsContext.rainbowChuTrailOuterColor) {
        Colors_ChangeRainbowColorRGBA8(&effect->p1StartColor, BOMBCHU_CYCLE_FRAMES_OUTER, 0);
        Colors_ChangeRainbowColorRGBA8(&effect->p1EndColor, BOMBCHU_CYCLE_FRAMES_OUTER, 2);
    }

    switch (gSettingsContext.bombchuTrailDuration) {
        case TRAILDURATION_DISABLED:
            effect->elemDuration = 0;
            break;
        case TRAILDURATION_VERYSHORT:
            effect->elemDuration = 8;
            break;
        case TRAILDURATION_VANILLA:
            effect->elemDuration = 16;
            break;
        case TRAILDURATION_LONG:
            effect->elemDuration = 32;
            break;
        case TRAILDURATION_VERYLONG:
            effect->elemDuration = 64;
            break;
        case TRAILDURATION_LIGHTSABER:
            effect->elemDuration = 128;
            break;
    }

    return handleLongTrails(gSettingsContext.bombchuTrailDuration, effect, p1, p2);
}
