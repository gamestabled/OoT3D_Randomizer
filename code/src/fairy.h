#ifndef _FAIRY_H_
#define _FAIRY_H_

#include "z3D/z3D.h"

typedef struct EnElf {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ SkelAnime skelAnime;
    /* 0x228 */ char unk_228[0x700];
    /* 0x928 */ Color_RGBAf innerColor;
    /* 0x938 */ Color_RGBAf outerColor;
    /* 0x948 */ LightInfo lightInfoGlow;
    /* 0x960 */ void* lightNodeGlow;
    /* 0x964 */ LightInfo lightInfoNoGlow;
    /* 0x97C */ void* lightNodeNoGlow;
    /* 0x980 */ Vec3f unk_28C;
    /* 0x98C */ void* elfMsg;
    /* 0x990 */ char unk_990[0x40];
} EnElf;
_Static_assert(sizeof(EnElf) == 0x9D0, "EnElf size");

void EnElf_UpdateNavi(Actor* thisx, GlobalContext* globalCtx);
void EnElf_Draw(Actor* thisx, GlobalContext* globalCtx);

void Fairy_UpdateRainbowNaviColors(EnElf* navi);
void Fairy_ResetRainbowCMABs(void);

#endif //_FAIRY_H_
