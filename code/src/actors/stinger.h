#ifndef _STINGER_H
#define _STINGER_H

#include "z3D/z3D.h"

struct EnEiyer;

typedef void (*EnEiyerActionFunc)(struct EnEiyer*, GlobalContext*);

typedef struct EnEiyer {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ SkelAnime anime;
    /* 0x228 */ char unk_228[0x5B0];
    /* 0x7D8 */ SkeletonAnimationModel* saModel;
    /* 0x7DC */ EnEiyerActionFunc actionFunc;
    /* 0x7E0 */ char unk_7E0[0x68];
} EnEiyer;
_Static_assert(sizeof(EnEiyer) == 0x848, "EnEiyer size");

void EnEiyer_rUpdate(Actor* thisx, GlobalContext* globalCtx);
void EnEiyer_ReinitModels(EnEiyer* this);

#endif //_STINGER_H
