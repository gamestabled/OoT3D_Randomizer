#ifndef _ARMOS_H_
#define _ARMOS_H_

#include "z3D/z3D.h"

#define ARMOS_CMB_INDEX 0

typedef struct EnAmExtension {
    u8 usingModifiedModel;
} EnAmExtension;

typedef struct EnAm {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x1BC */ SkelAnime anime;
    /* 0x240 */ char unk_240[0x224];
    /* 0x464 */ u8 textureBlend; // 0 = statue textures; 255 = enemy textures
    /* 0x465 */ char unk_465[0x147];
    EnAmExtension rExt;
} EnAm;
_Static_assert(offsetof(EnAm, rExt) == 0x5AC, "EnAm size");

void EnAm_rDraw(Actor* thisx, GlobalContext* globalCtx);

#endif //_ARMOS_H_
