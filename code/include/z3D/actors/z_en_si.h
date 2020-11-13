#ifndef _EN_SI_H_
#define _EN_SI_H_

#include "z3D/z3D.h"

struct EnSi;

typedef void (*EnSiActionFunc)(struct EnSi*, GlobalContext*);

typedef struct EnSi {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ EnSiActionFunc actionFunc;
    /* 0x1A8 */ char unk[0x64];
    /* 0x20C */ float* unk_20C;
} EnSi; // size 0x210

#endif //_EN_SI_H_
