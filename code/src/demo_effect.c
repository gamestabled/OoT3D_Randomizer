#include "z3D/z3D.h"
#include "z3D/actors/z_demo_effect.h"
#include "models.h"

#define DemoEffect_Init_addr 0x22345C
#define DemoEffect_Init ((ActorFunc)DemoEffect_Init_addr)

#define DemoEffect_Destroy_addr 0x2245B8
#define DemoEffect_Destroy ((ActorFunc)DemoEffect_Destroy_addr)

#define THIS ((DemoEffect*)thisx)

void DemoEffect_rInit(Actor* thisx, GlobalContext* globalCtx) {
    DemoEffect* reward = THIS;

    DemoEffect_Init(&reward->actor, globalCtx);
    Model_SpawnByActor(&reward->actor, globalCtx, 0);
}

void DemoEffect_rDestroy(Actor* thisx, GlobalContext* globalCtx) {
    DemoEffect* reward = THIS;

    Model_DestroyByActor(&reward->actor);
    DemoEffect_Destroy(&reward->actor, globalCtx);
}
