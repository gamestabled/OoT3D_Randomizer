#ifndef _BIRI_H_
#define _BIRI_H_

#include "z3D/z3D.h"

/*-------------------------------
|             EnBili            |
-------------------------------*/

typedef struct EnBili {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ SkelAnime anime;
    /* 0x228 */ char jointTable[0x138];
    /* 0x360 */ char morphTable[0x138];
    /* 0x498 */ FaceAnimation faceAnim;
    /* 0x664 */ char unk_664[0x064];
} EnBili;
_Static_assert(sizeof(EnBili) == 0x6C8, "EnBili size");

void EnBili_ReinitModels(EnBili* this);

/*-------------------------------
|             EnVali            |
-------------------------------*/

typedef struct EnVali {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ SkelAnime anime;
    /* 0x228 */ char jointTable[0x23C];
    /* 0x464 */ char morphTable[0x23C];
    /* 0x6A0 */ char unk_6A0[0x168];
    /* 0x808 */ SkeletonAnimationModel* tentaclesModel;
    /* 0x80C */ SkeletonAnimationModel* innerBellModel;
    /* 0x810 */ SkeletonAnimationModel* outerBellModel;
    /* 0x814 */ SkeletonAnimationModel* purpleSphereModel_1;
    /* 0x818 */ SkeletonAnimationModel* purpleSphereModel_2;
    /* 0x81C */ SkeletonAnimationModel* purpleSphereModel_3;
    /* 0x820 */ MaterialAnimation matAnim;
    /* 0x8B0 */ char unk_8B8[0x010];
} EnVali;
_Static_assert(sizeof(EnVali) == 0x8C8, "EnVali size");

void EnVali_ReinitModels(EnVali* this);

#endif //_BIRI_H_
