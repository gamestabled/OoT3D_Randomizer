#ifndef _GRAVEYARD_OBJECTS_H_
#define _GRAVEYARD_OBJECTS_H_

#include "z3D/z3D.h"

struct BgSpot02Objects;

typedef void (*BgSpot02ObjectsActionFunc)(struct BgSpot02Objects* this, GlobalContext* globalCtx);

typedef struct BgSpot02Objects {
    Actor base;
    char dyna[24];
    BgSpot02ObjectsActionFunc action_fn;
    s16 timer;
} BgSpot02Objects;

void BgSpot02Objects_rUpdate(Actor* thisx, GlobalContext* globalCtx);
void BgSpot02Objects_ExplodeGrave(BgSpot02Objects* this);

#endif //_GRAVEYARD_OBJECTS_H_
