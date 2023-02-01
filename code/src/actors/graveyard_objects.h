#ifndef _GRAVEYARD_OBJECTS_H_
#define _GRAVEYARD_OBJECTS_H_

#include "z3D/z3D.h"

typedef struct {
    Actor base;
    char dyna[24];
    void* action_fn;
    s16 timer;
} BgSpot02Objects;

void BgSpot02Objects_rUpdate(Actor* thisx, GlobalContext* globalCtx);
void BgSpot02Objects_ExplodeGrave(BgSpot02Objects* thisx);

#endif //_GRAVEYARD_OBJECTS_H_
