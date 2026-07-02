#ifndef _WALLMASTER_H_
#define _WALLMASTER_H_

#include "z3D/z3D.h"

typedef struct EnWallmas {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ SkelAnime anime;
    /* 0x228 */ char unk_228[0x5B0];
    /* 0x7D8 */ SkeletonAnimationModel* shadowModel;
    /* 0x7DC */ char unk_7DC[0x068];
} EnWallmas;
_Static_assert(sizeof(EnWallmas) == 0x844, "EnWallmas size");

void EnWallmas_ReinitModels(EnWallmas* this);

#endif //_WALLMASTER_H_
