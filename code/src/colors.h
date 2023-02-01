#ifndef _COLORS_H_
#define _COLORS_H_

typedef struct {
    u8 r, g, b, a;
} Color_RGBA8;

typedef struct {
    f32 r, g, b, a;
} Color_RGBAf;

void Colors_ChangeRainbowColorRGBAf(Color_RGBAf* color, float speed, float max);

#endif //_COLORS_H_
