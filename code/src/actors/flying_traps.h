#ifndef _FLYING_TRAPS_H_
#define _FLYING_TRAPS_H_

#include "z3D/z3D.h"

/*-------------------------------
|           EnTuboTrap          |
-------------------------------*/

#define POT_CMB_INDEX 13

struct EnTuboTrap;

typedef void (*EnTuboTrapActionFunc)(struct EnTuboTrap* this, GlobalContext* globalCtx);

typedef struct EnTuboTrapExtension {
    u8 usingModifiedModel;
} EnTuboTrapExtension;

typedef struct EnTuboTrap {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ EnTuboTrapActionFunc actionFunc;
    /* 0x1A8 */ f32 targetY;
    /* 0x1AC */ Vec3f originPos;
    /* 0x1B8 */ ColliderCylinder* collider;
    /* 0x1BC */ char unk_1BC[0x054];
    /* 0x210 */ SkeletonAnimationModel* saModel;
    EnTuboTrapExtension rExt;
} EnTuboTrap;
_Static_assert(offsetof(EnTuboTrap, rExt) == 0x214, "EnTuboTrap size");

void EnTuboTrap_rDraw(Actor* thisx, GlobalContext* globalCtx);

/*-------------------------------
|           EnYukabyun          |
-------------------------------*/

#define FLYING_TILE_CMB_INDEX 1

struct EnYukabyun;

typedef void (*EnYukabyunActionFunc)(struct EnYukabyun* this, GlobalContext* globalCtx);

typedef struct EnYukabyunExtension {
    u8 usingModifiedModel;
} EnYukabyunExtension;

typedef struct EnYukabyun {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ EnYukabyunActionFunc actionFunc;
    /* 0x1A8 */ s16 waitCounter;
    /* 0x1AC */ ColliderCylinder collider;
    /* 0x204 */ SkeletonAnimationModel* saModel;
    EnYukabyunExtension rExt;
} EnYukabyun;
_Static_assert(offsetof(EnYukabyun, rExt) == 0x208, "EnYukabyun size");

void EnYukabyun_rUpdate(Actor* thisx, GlobalContext* globalCtx);
void EnYukabyun_rDraw(Actor* thisx, GlobalContext* globalCtx);

/*-------------------------------
|            Generic            |
-------------------------------*/

u8 FlyingTraps_IsHiddenTrap(Actor* actor);

#endif //_FLYING_TRAPS_H_
