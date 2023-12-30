#include "z3D/z3D.h"
#include "colors.h"
#include "common.h"

// This function is taken from OoTR:
// https://github.com/OoTRandomizer/OoT-Randomizer/blob/1827fbb8089d3fe3e816a297a5f3ce2c99a6e0c5/ASM/c/rainbow.c
Color_RGBA8 Colors_GetRainbowColor(u32 curFrame, u32 stepFrames) {
    static Color_RGBA8 cycleColors[] = {
        { 0xE0, 0x10, 0x10, 0x00 }, // red
        { 0xE0, 0xE0, 0x10, 0x00 }, // yellow
        { 0x10, 0xE0, 0x10, 0x00 }, // green
        { 0x10, 0xE0, 0xE0, 0x00 }, // cyan
        { 0x10, 0x10, 0xE0, 0x00 }, // blue
        { 0xE0, 0x10, 0xE0, 0x00 }, // purple
        { 0xE0, 0x10, 0x10, 0x00 }, // red
    };

    int index;
    float tweenA, tweenB;

    index = (curFrame / stepFrames) % 6;

    tweenB = ((f32)(curFrame % stepFrames) / stepFrames);
    tweenA = 1 - tweenB;

    Color_RGBA8 cA = cycleColors[index];
    Color_RGBA8 cB = cycleColors[index + 1];

    Color_RGBA8 ret;
    ret.r = (u8)((cA.r * tweenA) + (cB.r * tweenB));
    ret.g = (u8)((cA.g * tweenA) + (cB.g * tweenB));
    ret.b = (u8)((cA.b * tweenA) + (cB.b * tweenB));
    ret.a = 0xFF;
    return ret;
}

void Colors_ChangeRainbowColorRGBA8(Color_RGBA8* color, u32 stepFrames, u8 stepOffset) {
    Color_RGBA8 newColor = Colors_GetRainbowColor(rGameplayFrames + stepOffset * stepFrames, stepFrames);
    color->r             = newColor.r;
    color->g             = newColor.g;
    color->b             = newColor.b;
}
