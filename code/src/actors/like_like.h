#ifndef _LIKE_LIKE_H_
#define _LIKE_LIKE_H_

#include "z3D/z3D.h"

typedef struct EnRr {
    /* 0x0000 */ Actor actor;
    /* 0x01A4 */ char unk_01A4[0x2294];
    /* 0x2438 */ SkelAnime skelAnime;
    /* 0x24BC */ char unk_24BC[0x02F8];
    /* 0x27B4 */ MaterialAnimation matAnim;
    /* 0x284C */ char unk_284C[0x0004];
} EnRr;
_Static_assert(sizeof(EnRr) == 0x2850, "EnRr size");

void EnRr_ReinitModels(EnRr* this);

#endif //_LIKE_LIKE_H_
