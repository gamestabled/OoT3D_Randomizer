#ifndef _ACTOR_H_
#define _ACTOR_H_

#include "z3D/z3D.h"

// Actor whose init or update function is currently running
extern Actor* gRunningActor;

void Actor_Init();
void ActorSetup_Extra();
s32 Actor_CollisionATvsAC(Collider* at, Collider* ac);
s32 Actor_IsBoss(Actor* actor);
void Actor_ReinitSkelAnime(Actor* actor, SkelAnime* anime, s32 cmbIndex);

#endif //_ACTOR_H_
