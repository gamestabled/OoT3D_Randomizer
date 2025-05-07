#ifndef _GUAY_H_
#define _GUAY_H_

#include "z3D/z3D.h"

struct EnCrow;

typedef void (*EnCrowActionFunc)(struct EnCrow*, GlobalContext*);

typedef struct EnCrow {
    /* 0x0000 */ Actor actor;
    /* 0x01A4 */ char unk_1A4[0x3F4];
    /* 0x0598 */ EnCrowActionFunc actionFunc;
    /* 0x059C */ char unk_59C[0x08];
    /* 0x05A4 */ ColliderJntSph collider;
    /* 0x05C4 */ char unk_5C4[0x54];
} EnCrow;
_Static_assert(sizeof(EnCrow) == 0x618, "EnCrow size");

void EnCrow_rUpdate(Actor* thisx, GlobalContext* globalCtx);

#endif //_GUAY_H_
