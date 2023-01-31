#ifndef _CHECKABLE_SPOT_H_
#define _CHECKABLE_SPOT_H_

#include "z3D/z3D.h"

typedef struct EnWonderTalk {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ ActorFunc actionFunc;
    /* 0x1A8 */ char unk_1A8[0x15];
} EnWonderTalk; // size = 0x1BD

void EnWonderTalk_rUpdate(Actor* thisx, GlobalContext* globalCtx);

void EnWonderTalk2_rUpdate(Actor* thisx, GlobalContext* globalCtx);

#endif //_CHECKABLE_SPOT_H_
