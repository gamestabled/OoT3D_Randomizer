#ifndef _OCTOROK_H_
#define _OCTOROK_H_

#include "z3D/z3D.h"

typedef struct EnOkuta {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ SkelAnime anime;
    /* 0x228 */ char unk_228[0x680];
    /* 0x8A8 */ SkeletonAnimationModel* rockModel;
    /* 0x8AC */ char unk_8AC[0x078];
} EnOkuta;
_Static_assert(sizeof(EnOkuta) == 0x924, "EnOkuta size");

void EnOkuta_ReinitModels(EnOkuta* this);

#endif //_OCTOROK_H_
