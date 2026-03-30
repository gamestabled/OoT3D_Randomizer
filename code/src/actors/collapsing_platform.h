#ifndef _COLLAPSING_PLATFORM_H_
#define _COLLAPSING_PLATFORM_H_

#include "z3D/z3D.h"

struct ObjLift;

typedef void (*ObjLiftActionFunc)(struct ObjLift* this, GlobalContext* globalCtx);

typedef struct ObjLift {
    Actor base;
    char dyna[24];
    ObjLiftActionFunc action_fn;
    SkeletonAnimationModel* animation_model;
    char unk_1C4[6];
    u16 timer;
} ObjLift;

void ObjLift_rUpdate(Actor* thisx, GlobalContext* globalCtx);
void ObjLift_SetActionFn(ObjLift* this, ObjLiftActionFunc new_action_fn);

#endif //_COLLAPSING_PLATFORM_H_
