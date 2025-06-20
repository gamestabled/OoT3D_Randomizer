#ifndef _IRON_KNUCKLE_H_
#define _IRON_KNUCKLE_H_

#include "z3D/z3D.h"

typedef struct EnIk {
    /* 0x0000 */ Actor actor;
    /* 0x01A4 */ SkelAnime skelAnime;
    /* 0x0228 */ char unk_228[0xDD4];
} EnIk;
_Static_assert(sizeof(EnIk) == 0xFFC, "EnIk size");

void EnIk_rInit(Actor* thisx, GlobalContext* globalCtx);

#endif //_IRON_KNUCKLE_H_
