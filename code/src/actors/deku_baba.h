#ifndef _DEKU_BABA_H_
#define _DEKU_BABA_H_

#include "z3D/z3D.h"

/*-------------------------------
|           EnDekubaba          |
-------------------------------*/

typedef struct EnDekubaba {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ char unk_1A4[0x030];
    /* 0x1D4 */ SkelAnime anime;
    /* 0x258 */ char unk_258[0x3A0];
    /* 0x5F8 */ SkeletonAnimationModel* stalkModel_1;
    /* 0x5FC */ SkeletonAnimationModel* stalkModel_2;
    /* 0x600 */ SkeletonAnimationModel* stalkModel_3;
    /* 0x604 */ SkeletonAnimationModel* leavesModel;
    /* 0x608 */ SkeletonAnimationModel* stickModel;
} EnDekubaba;
_Static_assert(sizeof(EnDekubaba) == 0x60C, "EnDekubaba size");

void EnDekubaba_ReinitModels(EnDekubaba* this);

/*-------------------------------
|           EnKarebaba          |
-------------------------------*/

typedef struct EnKarebaba {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ SkelAnime anime;
    /* 0x228 */ char unk_228[0x1F0];
    /* 0x418 */ SkeletonAnimationModel* stalkModel_1;
    /* 0x41C */ SkeletonAnimationModel* stalkModel_2;
    /* 0x420 */ SkeletonAnimationModel* stalkModel_3;
    /* 0x424 */ SkeletonAnimationModel* stickModel;
    /* 0x428 */ SkeletonAnimationModel* leavesModel;
    /* 0x42C */ char unk_42C[0x004];
} EnKarebaba;
_Static_assert(sizeof(EnKarebaba) == 0x430, "EnKarebaba size");

void EnKarebaba_ReinitModels(EnKarebaba* this);

#endif //_DEKU_BABA_H_
