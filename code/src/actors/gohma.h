#ifndef _GOHMA_H_
#define _GOHMA_H_

#include "z3D/z3D.h"

struct EnGoma;
typedef void (*EnGomaActionFunc)(struct EnGoma*, GlobalContext*);

#define EnGoma_SetupHatch ((EnGomaActionFunc)GAME_ADDR(0x1741C8))

typedef struct EnGoma {
    /* 0x0000 */ Actor base;
    /* 0x01A4 */ char unk_1A4[0x564];
    /* 0x0708 */ EnGomaActionFunc actionFunc;
    /* 0x070C */ char unk_70C[0x110];
} EnGoma;
_Static_assert(sizeof(EnGoma) == 0x81C, "EnGoma size");

#endif //_GOHMA_H_
