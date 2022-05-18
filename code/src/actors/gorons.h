#ifndef _GORONS_H_
#define _GORONS_H_

#include "z3D/z3D.h"

struct EnGo2;

typedef void (*EnGo2_ActionFunc)(struct EnGo2* self, GlobalContext* globalCtx);

#define BIGGORON_TRADED_CLAIM_CHECK (1 << 0)
#define BIGGORON_TRADED_EYEDROPS (1 << 1)
#define BIGGORON_TRADED_BROKEN_SWORD (1 << 2)

typedef struct EnGo2 {
    /* 0x0000 */ Actor actor;
    /* 0x01A4 */ char unk_1A4[0xA18];
    /* 0x0BBC */ EnGo2_ActionFunc actionFunc;
    /* 0x0BC0 */ char unk_BC0[0x338];
    /* 0x0EF8 */ s32 getItemId;
    /* 0x0EFC */ char unk_EFC[0xC];
} EnGo2; // size = 0xF08

#endif
