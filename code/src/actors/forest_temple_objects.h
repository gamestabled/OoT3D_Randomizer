#ifndef _FOREST_TEMPLE_OBJECTS_H_
#define _FOREST_TEMPLE_OBJECTS_H_

#include "z3D/z3D.h"

struct BgMoriBigst;

typedef void (*BgMoriBigstActionFunc)(struct BgMoriBigst*, GlobalContext*);

typedef struct BgMoriBigst {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x01BC */ BgMoriBigstActionFunc actionFunc;
    /* 0x01C0 */ s16 waitTimer;
    /* 0x01C2 */ s8 moriTexObjectSlot;
    /* 0x01C4 */ SkeletonAnimationModel* saModel;
} BgMoriBigst;
_Static_assert(sizeof(BgMoriBigst) == 0x1C8, "BgMoriBigst size");

#define activeStalfosCount dyna.actor.home.rot.z

void BgMoriBigst_rUpdate(Actor* thisx, GlobalContext* globalCtx);

Bool ForestStalfosFight_BeforeActorUpdate(Actor* actor);
void ForestStalfosFight_AfterActorUpdate(Actor* actor);

#endif //_FOREST_TEMPLE_OBJECTS_H_
