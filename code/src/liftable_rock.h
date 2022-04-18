#ifndef _LIFTABLE_ROCK_H_
#define _LIFTABLE_ROCK_H_

#define SMALL_ROCK 0
#define LARGE_ROCK 1

#include "../include/z3D/z3D.h"

typedef struct {
    Actor base;
    void* action_fn;
    char collider[88];
    SkeletonAnimationModel* animation_model;
} EnIshi;

void EnIshi_rInit(Actor* thisx, GlobalContext* globalCtx);
void EnIshi_rUpdate(EnIshi* thisx, GlobalContext* globalCtx);

#endif //_LIFTABLE_ROCK_H_
