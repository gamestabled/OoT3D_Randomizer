#ifndef _ANJU_H_
#define _ANJU_H_

#include "z3D/z3D.h"

struct EnNiwLady;

typedef void (*EnNiwLady_ActionFunc)(struct EnNiwLady* self, GlobalContext* globalCtx);

typedef struct EnNiwLady {
    /* 0x0000 */ Actor actor;
    /* 0x01A4 */ char unk_1A4[0x69C];
    /* 0x0840 */ EnNiwLady_ActionFunc actionFunc;
    /* 0x0844 */ char unk_844[0x030];
    /* 0x0874 */ s32 getItemId;
    /* 0x0878 */ char unk_878[0x250];
} EnNiwLady; // size = 0xAC8

#endif
