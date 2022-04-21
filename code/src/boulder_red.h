#ifndef _BOULDER_RED_H_
#define _BOULDER_RED_H_

#include "z3D/z3D.h"

typedef struct {
    Actor base;
    char collider[88];
    f32 shake_position_size;
    f32 shake_rotation_size;
    s16 shake_frames;
    s16 shake_position_phase;
    s16 shake_rotation_phase;
    s16 hit_count;
    SkeletonAnimationModel* animation_model;
} ObjHamishi;

void ObjHamishi_rUpdate(ObjHamishi* thisx, GlobalContext* globalCtx);
void ObjHamishi_Hit(ObjHamishi* thisx);

#endif //_BOULDER_RED_H_
