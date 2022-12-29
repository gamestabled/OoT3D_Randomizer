#ifndef _DEKU_SCRUBS_H_
#define _DEKU_SCRUBS_H_

#include "z3D/z3D.h"

typedef struct {
    /* 0x000 */ Actor base;
    /* 0x1A4 */ ActorFunc actionFunc;
    /* 0x1A8 */ char unk_1A8[0x40];
    /* 0x1A8 */ s16 timer1;
    /* 0x1A8 */ s16 timer2;
    /* 0x1A8 */ s16 timer4;
    /* 0x1A8 */ s16 timer5;
    /* 0x1A8 */ s16 blinkTimer;
    /* 0x1A8 */ s16 unkCounter;
    /* 0x1A8 */ s16 timer3;
} EnDntNomal;

void EnDntNomal_rUpdate(Actor* thisx, GlobalContext* globalCtx);

#endif
