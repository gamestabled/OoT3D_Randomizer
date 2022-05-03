#ifndef _EN_ITEM00_H_
#define _EN_ITEM00_H_

#include "z3D/z3D.h"

typedef struct EnItem00 {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ void* action_fn;
    /* 0x1A8 */ u16 collectibleFlag;
    /* 0x1AA */ char unk_1AA[0x4];
    /* 0x1AE */ u16 unk_1AE;
    /* 0x1B0 */ u16 unk_1B0;
    /* 0x1B2 */ char unk_1B2[0x66];
} EnItem00; // size 0x218

#endif //_EN_ITEM00_H_
