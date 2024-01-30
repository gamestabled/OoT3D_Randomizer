#ifndef _COLORS_H_
#define _COLORS_H_

typedef struct {
    u8 r, g, b, a;
} Color_RGBA8;

typedef struct {
    f32 r, g, b, a;
} Color_RGBAf;

Color_RGBA8 Colors_GetRainbowColor(u32 curFrame, u32 stepFrames);

// Function to change rainbow color without affecting alpha component.
void Colors_ChangeRainbowColorRGBA8(Color_RGBA8* color, u32 stepFrames, u8 stepOffset);

#endif //_COLORS_H_
