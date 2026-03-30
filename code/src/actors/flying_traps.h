#ifndef _FLYING_TRAPS_H_
#define _FLYING_TRAPS_H_

#include "z3D/z3D.h"

struct EnYukabyun;
struct EnTuboTrap;

typedef void (*EnYukabyunActionFunc)(struct EnYukabyun* this, GlobalContext* globalCtx);
typedef void (*EnTuboTrapActionFunc)(struct EnTuboTrap* this, GlobalContext* globalCtx);

typedef struct EnYukabyun {
    /* 0x0000 */ Actor base;
    /* 0x01A4 */ EnYukabyunActionFunc actionFunc;
    /* 0x01A8 */ s16 waitCounter;
    /* 0x01AA */ char unk_1AA[0x2];
    /* 0x01AC */ ColliderCylinder* collider;
    /* 0x0204 */ SkeletonAnimationModel* saModel;
} EnYukabyun;

typedef struct EnTuboTrap {
    /* 0x0000 */ Actor base;
    /* 0x01A4 */ EnTuboTrapActionFunc actionFunc;
    /* 0x01A8 */ f32 targetY;
    /* 0x01AC */ Vec3f originPos;
    /* 0x01B8 */ ColliderCylinder* collider;
    /* 0x0210 */ SkeletonAnimationModel* saModel;
} EnTuboTrap;

void EnYukabyun_rUpdate(Actor* thisx, GlobalContext* globalCtx);
u8 FlyingTraps_IsHiddenTrap(Actor* actor);

#endif //_FLYING_TRAPS_H_
