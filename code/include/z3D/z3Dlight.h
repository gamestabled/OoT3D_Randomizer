#ifndef _Z3DLIGHT_H_
#define _Z3DLIGHT_H_

#include "s_types.h"
#include "s_colors.h"

typedef struct LightPoint {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ Color_RGB8 color;
    /* 0x0F */ u8 drawGlow;
    /* 0x10 */ s16 radius;
    /* 0x12 */ u8 unk_12;
} LightPoint;
_Static_assert(sizeof(LightPoint) == 0x14, "LightPoint size");

typedef union LightParams {
    LightPoint point;
    // LightDirectional dir;
} LightParams;

typedef struct LightInfo {
    /* 0x0 */ u8 type;
    /* 0x4 */ LightParams params;
} LightInfo;
_Static_assert(sizeof(LightInfo) == 0x18, "LightInfo size");

#endif // _Z3DLIGHT_H_
