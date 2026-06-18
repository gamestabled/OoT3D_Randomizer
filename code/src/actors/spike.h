#ifndef _SPIKE_H_
#define _SPIKE_H_

#include "z3D/z3D.h"

typedef struct EnNy {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ char unk_1A4[0x1DC];
    /* 0x380 */ SkeletonAnimationModel* stoneCoreModel;
    /* 0x384 */ SkeletonAnimationModel* smoothCoreModel;
    /* 0x388 */ SkeletonAnimationModel* spikesModel;
    /* 0x38C */ SkeletonAnimationModel* debrisModels[8];
    /* 0x3AC */ SkeletonAnimationModel* smokeModels[4];
} EnNy;
_Static_assert(sizeof(EnNy) == 0x3BC, "EnNy size");

void EnNy_ReinitModels(EnNy* this);

#endif //_SPIKE_H_
