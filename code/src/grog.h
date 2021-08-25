#ifndef _GROG_H_
#define _GROG_H_

#include "z3D/z3D.h"

struct EnHs;

typedef void (*EnHs_ActionFunc)(struct EnHs* self, GlobalContext* globalCtx);

typedef struct EnHs {
    /* 0x0000 */ Actor actor;
    /* 0x01A4 */ char unk_1A4[0x560];
    /* 0x0704 */ u16 unk_704;
    /* 0x0706 */ char unk_706[0x2];
    /* 0x0708 */ EnHs_ActionFunc actionFunc;
    /* 0x070C */ char unk_70C[0x8];
} EnHs; // size = 0x714

#endif
