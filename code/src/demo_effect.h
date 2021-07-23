#ifndef _DEMO_EFFECT_H_
#define _DEMO_EFFECT_H_

#include "z3D/z3D.h"
#include "z3D/actors/z_demo_effect.h"

void DemoEffect_rInit(Actor* thisx, GlobalContext* globalCtx);
void DemoEffect_rDestroy(Actor* thisx, GlobalContext* globalCtx);
void DemoEffect_rUpdate(Actor* thisx, GlobalContext* globalCtx);

#endif //_DEMO_EFFECT_H_
