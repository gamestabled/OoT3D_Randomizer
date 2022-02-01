#ifndef _COLLAPSING_PLATFORM_H_
#define _COLLAPSING_PLATFORM_H_

#include "z3D/z3D.h"

typedef struct {
    Actor base;
    char dyna[24];
    void* action_fn;
    SkeletonAnimationModel* animation_model;
    char unk_1C4[6];
    u16 timer;
} ObjLift;

void ObjLift_rUpdate(ObjLift* thisx, GlobalContext* globalCtx);
void ObjLift_SetActionFn(ObjLift* thisx, void* new_action_fn);

#endif //_COLLAPSING_PLATFORM_H_
