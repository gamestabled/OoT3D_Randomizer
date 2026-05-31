#ifndef _TORCH_SLUG_H_
#define _TORCH_SLUG_H_

#include "z3D/z3D.h"

typedef struct EnBw {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ SkelAnime anime;
    /* 0x228 */ char unk_228[0x208];
    /* 0x430 */ MaterialAnimation* matAnim;
    /* 0x434 */ char unk_434[0x138];
} EnBw;
_Static_assert(sizeof(EnBw) == 0x56C, "EnBw size");

void EnBw_ReinitModels(EnBw* this);

#endif //_TORCH_SLUG_H_
