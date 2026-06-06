#ifndef _FREEZARD_H_
#define _FREEZARD_H_

#include "z3D/z3D.h"

typedef struct EnFz {
    /* 0x0000 */ Actor actor;
    /* 0x01A4 */ char unk_1A4[0x104C];
    /* 0x11F0 */ SkeletonAnimationModel* mainModel;
    /* 0x11F4 */ SkeletonAnimationModel* models[61];
    /* 0x12E8 */ s32 cmbIndices[61];
} EnFz;
_Static_assert(sizeof(EnFz) == 0x13DC, "EnFz size");

void EnFz_ReinitModels(EnFz* this);

#endif //_FREEZARD_H_
