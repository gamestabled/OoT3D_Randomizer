#ifndef _DEKU_SCRUBS_H_
#define _DEKU_SCRUBS_H_

#include "z3D/z3D.h"

typedef struct {
    /* 0x000 */ Actor base;
    /* 0x1A4 */ ActorFunc actionFunc;
    /* 0x1A8 */ char unk_1A8[0x40];
    /* 0x1E8 */ s16 timer1;
    /* 0x1EA */ s16 timer2;
    /* 0x1EC */ s16 timer4;
    /* 0x1EE */ s16 timer5;
    /* 0x1F0 */ s16 blinkTimer;
    /* 0x1F2 */ s16 unkCounter;
    /* 0x1F4 */ s16 timer3;
    /* 0x1F6 */ char unk_1F6[0x702];
} EnDntNomal;
_Static_assert(sizeof(EnDntNomal) == 0x8F8, "EnDntNomal size");

typedef struct EnHintnuts {
    /* 0x0000 */ Actor actor;
    /* 0x01A4 */ char unk_1A4[0x08];
    /* 0x01AC */ u16 textIdCopy;
    /* 0x01B0 */ char unk_1B0[0x488];
} EnHintnuts;
_Static_assert(sizeof(EnHintnuts) == 0x638, "EnHintnuts size");

void EnDntNomal_rUpdate(Actor* thisx, GlobalContext* globalCtx);

void EnHintnuts_rInit(Actor* thisx, GlobalContext* globalCtx);

#endif
