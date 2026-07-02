#ifndef _TENTACLE_H_
#define _TENTACLE_H_

#include "z3D/z3D.h"

/*-------------------------------
|         Enemy Tentacle        |
-------------------------------*/

typedef struct EnBa {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ SkelAnime anime;
    /* 0x228 */ char unk_228[0x5B0];
    /* 0x7D8 */ MaterialAnimation* matAnim;
    /* 0x7DC */ FaceAnimation faceAnim;
    /* 0x9A8 */ char unk_7E0[0x294];
    /* 0xC3C */ SkeletonAnimationModel* deadBlobModel;
    /* 0xC40 */ char unk_C40[0x00C];
} EnBa;
_Static_assert(sizeof(EnBa) == 0xC4C, "EnBa size");

void EnBa_ReinitModels(EnBa* this);

/*-------------------------------
|     Path Blocking Tentacle    |
-------------------------------*/

typedef struct EnBx {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ SkelAnime anime;
    /* 0x228 */ char unk_228[0x1A0];
    /* 0x3C8 */ MaterialAnimation matAnim;
    /* 0x460 */ FaceAnimation faceAnim;
    /* 0x62C */ char unk_62C[0x158];
} EnBx;
_Static_assert(sizeof(EnBx) == 0x784, "EnBx size");

void EnBx_ReinitModels(EnBx* this);

#endif //_TENTACLE_H_
