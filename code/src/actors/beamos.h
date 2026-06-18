#ifndef _BEAMOS_H_
#define _BEAMOS_H_

#include "z3D/z3D.h"

typedef struct EnVm {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ SkelAnime anime;
    /* 0x228 */ char unk_228[0x420];
    /* 0x648 */ SkeletonAnimationModel* saModel;
    /* 0x64C */ MaterialAnimation matAnim;
} EnVm;
_Static_assert(sizeof(EnVm) == 0x6E4, "EnVm size");

void EnVm_ReinitModels(EnVm* this);

#endif //_BEAMOS_H_
