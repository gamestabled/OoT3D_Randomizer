#ifndef _TAILPASARAN_H_
#define _TAILPASARAN_H_

#include "z3D/z3D.h"

struct EnTp;

typedef void (*EnTpActionFunc)(struct EnTp* this, GlobalContext* globalCtx);

typedef enum EnTpType {
    /* -1 */ TAILPASARAN_HEAD = -1,
    /*  0 */ TAILPASARAN_TAIL,
    /* 10 */ TAILPASARAN_FRAGMENT = 10,
    /* 11 */ TAILPASARAN_TAIL_DYING,
    /* 12 */ TAILPASARAN_HEAD_DYING,
} EnTpType;

typedef struct EnTp {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ s32 actionIndex;
    /* 0x1A8 */ s32 unk_1A8;
    /* 0x1AC */ EnTpActionFunc actionFunc;
    /* 0x1B0 */ SkelAnime skelAnime;
    /* 0x234 */ char unk_234[0x300];
    /* 0x534 */ SkeletonAnimationModel* model;
    /* 0x538 */ char unk_538[0x004];
    /* 0x53C */ MaterialAnimation matAnim;
} EnTp;
_Static_assert(sizeof(EnTp) == 0x5D4, "EnTp size");

void EnTp_ReinitModels(EnTp* this);

#endif //_TAILPASARAN_H_
