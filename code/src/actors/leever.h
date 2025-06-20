#ifndef _LEEVER_H_
#define _LEEVER_H_

#include "z3D/z3D.h"

struct EnReeba;

typedef void (*EnReebaActionFunc)(struct EnReeba*, GlobalContext*);

typedef struct EnReeba {
    /* 0x0000 */ Actor actor;
    /* 0x01A4 */ char unk_1A4[0x2FC];
    /* 0x04A0 */ EnReebaActionFunc actionFunc;
    /* 0x04A4 */ char unk_4A4[0x14];
    /* 0x04B8 */ f32 yOffsetTarget;
    /* 0x04BC */ f32 yOffsetStep;
    /* 0x04C0 */ f32 scale;
    /* 0x04C4 */ char unk_4C4[0x58];
} EnReeba;
_Static_assert(sizeof(EnReeba) == 0x51C, "EnReeba size");

#endif //_LEEVER_H_
