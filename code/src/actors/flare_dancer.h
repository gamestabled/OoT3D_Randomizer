#ifndef _FLARE_DANCER_H_
#define _FLARE_DANCER_H_

#include "z3D/z3D.h"

struct EnFd;
struct EnFdFire;

typedef void (*EnFdActionFunc)(struct EnFd*, GlobalContext*);
typedef void (*EnFdFireActionFunc)(struct EnFdFire*, GlobalContext*);

typedef struct EnFd {
    /* 0x0000 */ Actor actor;
    /* 0x01A4 */ SkelAnime skelAnime;
    /* 0x0228 */ char unk_228[0x4];
    /* 0x022C */ EnFdActionFunc actionFunc;
    /* 0x0230 */ char unk_230[0x26BC];
} EnFd;
_Static_assert(sizeof(EnFd) == 0x28EC, "EnFd size");

typedef struct EnFdFire {
    /* 0x0000 */ Actor actor;
    /* 0x01A4 */ EnFdFireActionFunc actionFunc;
    /* 0x01A8 */ ColliderCylinder collider;
    /* 0x0200 */ f32 spawnRadius;
    /* 0x0204 */ f32 scale;
    /* 0x0208 */ char unk_208[0x2];
    /* 0x020A */ s16 deathTimer;
    /* 0x020C */ s16 tile2Y;
    /* 0x020E */ char unk_20E[0xE];
} EnFdFire;
_Static_assert(sizeof(EnFdFire) == 0x21C, "EnFdFire size");

void EnFd_rUpdate(Actor* thisx, GlobalContext* globalCtx);

#endif //_FLARE_DANCER_H_
