#ifndef _KEESE_H_
#define _KEESE_H_

#include "z3D/z3D.h"

typedef struct EnFirefly {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ Vec3f bodyPartsPos[3];
    /* 0x1C8 */ SkelAnime skelAnime;
    /* 0x24C */ char unk_24C[0x568];
} EnFirefly;
_Static_assert(sizeof(EnFirefly) == 0x7B4, "EnFirefly size");

void EnFirefly_ReinitModels(EnFirefly* this);

#endif //_KEESE_H_
