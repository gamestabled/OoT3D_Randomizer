#ifndef _ACTOR_H_
#define _ACTOR_H_

#include "z3D/z3D.h"

void Actor_Init();
void ActorSetup_Extra();
s32 Actor_CollisionATvsAC(Collider* at, Collider* ac);

#endif //_ACTOR_H_
