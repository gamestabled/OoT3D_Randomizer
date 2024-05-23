#ifndef _FISHING_H_
#define _FISHING_H_

#include "z3D/z3D.h"

#define Fishing_Init ((ActorFunc)GAME_ADDR(0x1C0AD8))
#define Fishing_UpdateFish ((ActorFunc)GAME_ADDR(0x1F9ACC))
#define Fishing_DrawFish ((ActorFunc)GAME_ADDR(0x1F98B4))

#define EN_FISH_AQUARIUM 200 // param for record fish in tank.

void Fishing_rInit(Actor* thisx, GlobalContext* globalCtx);
void Fishing_rUpdateFish(Actor* thisx, GlobalContext* globalCtx);
void Fishing_rDrawFish(Actor* thisx, GlobalContext* globalCtx);

#endif //_FISHING_H_
