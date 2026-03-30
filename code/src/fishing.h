#ifndef _FISHING_H_
#define _FISHING_H_

#include "z3D/z3D.h"

void Fishing_Init(Actor* thisx, GlobalContext* globalCtx);
void Fishing_UpdateFish(Actor* thisx, GlobalContext* globalCtx);
void Fishing_DrawFish(Actor* thisx, GlobalContext* globalCtx);

#define EN_FISH_AQUARIUM 200 // param for record fish in tank.

void Fishing_rInit(Actor* thisx, GlobalContext* globalCtx);
void Fishing_rUpdateFish(Actor* thisx, GlobalContext* globalCtx);
void Fishing_rDrawFish(Actor* thisx, GlobalContext* globalCtx);

#endif //_FISHING_H_
