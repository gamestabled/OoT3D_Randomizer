#ifndef _FAIRY_H_
#define _FAIRY_H_

#include "z3D/z3D.h"
#include "colors.h"

typedef struct EnElf {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ char unk_1A4[0x784];
    /* 0x928 */ Color_RGBAf innerColor;
    /* 0x938 */ Color_RGBAf outerColor;
} EnElf;

void Fairy_UpdateRainbowNaviColors(EnElf* navi);
void Fairy_ResetRainbowCMABs(void);

#endif //_FAIRY_H_
