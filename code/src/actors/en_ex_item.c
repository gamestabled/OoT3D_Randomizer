#include "z3D/z3D.h"
#include "z3D/actors/z_en_ex_item.h"
#include "models.h"

#define EnExItem_Init ((ActorFunc)GAME_ADDR(0x20FC50))

#define EnExItem_Destroy ((ActorFunc)GAME_ADDR(0x20FDE0))

#define THIS ((EnExItem*)thisx)

void EnExItem_rInit(Actor* thisx, GlobalContext* globalCtx) {
    EnExItem* item = THIS;

    EnExItem_Init(&item->actor, globalCtx);

    switch (item->actor.params & 0xFF) {
        case 0x0:
        case 0x5:
        case 0x14:
        case 0x19:
            Model_SpawnByActor(&item->actor, globalCtx, 0x33);
            break;
        case 0x1:
        case 0x6:
            Model_SpawnByActor(&item->actor, globalCtx, 0x3E);
            break;
        case 0x13:
            Model_SpawnByActor(&item->actor, globalCtx, 0x60);
            break;
    }
}

void EnExItem_rDestroy(Actor* thisx, GlobalContext* globalCtx) {
    EnExItem* item = THIS;

    Model_DestroyByActor(&item->actor);
    EnExItem_Destroy(&item->actor, globalCtx);
}
