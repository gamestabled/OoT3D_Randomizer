#ifndef _DAMPE_H_
#define _DAMPE_H_

#include "z3D/z3D.h"

typedef struct {
    /* 0x000 */ char unk_00[0xBA8];
    /* 0xBA8 */ u32 currentReward;
} EnTk;

typedef struct {
    /* 0x000 */ char unk_00[0xB1C];
    /* 0xB1C */ u8 unk_B1C;
} EnPoRelay;

void EnTk_rUpdate(Actor* thisx, GlobalContext* globalCtx);

#endif
