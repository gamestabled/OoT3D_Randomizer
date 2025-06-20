#ifndef _STINGER_H
#define _STINGER_H

#include "z3D/z3D.h"

struct EnEiyer;

typedef void (*EnEiyerActionFunc)(struct EnEiyer*, GlobalContext*);

typedef struct EnEiyer {
    /* 0x0000 */ Actor actor;
    /* 0x01A4 */ char unk_1A4[0x638];
    /* 0x07DC */ EnEiyerActionFunc actionFunc;
    /* 0x07E0 */ char unk_7E0[0x68];
} EnEiyer;
_Static_assert(sizeof(EnEiyer) == 0x848, "EnEiyer size");

void EnEiyer_rUpdate(Actor* thisx, GlobalContext* globalCtx);

#endif //_STINGER_H
