#ifndef _DEAD_HAND_H_
#define _DEAD_HAND_H_

#include "z3D/z3D.h"

/*-------------------------------
|              EnDh             |
-------------------------------*/

typedef struct EnDh {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ SkelAnime anime;
    /* 0x228 */ char unk_228[0x708];
    /* 0x930 */ SkeletonAnimationModel* dirtWaveModel;
    /* 0x934 */ MaterialAnimation* dirtWaveMatAnim;
} EnDh;
_Static_assert(sizeof(EnDh) == 0x938, "EnDh size");

void EnDh_ReinitModels(EnDh* this);

/*-------------------------------
|             EnDha             |
-------------------------------*/

void EnDha_rUpdate(Actor* thisx, GlobalContext* globalCtx);

#endif //_DEAD_HAND_H_
