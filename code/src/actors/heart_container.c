#include "z3D/z3D.h"
#include "z3D/actors/z_item_b_heart.h"
#include "models.h"

#define ItemBHeart_Init ((ActorFunc)GAME_ADDR(0x25375C))

#define ItemBHeart_Destroy ((ActorFunc)GAME_ADDR(0x2537D4))

#define ItemBHeart_Update ((ActorFunc)GAME_ADDR(0x285C18))

#define ItemBHeart_Draw ((ActorFunc)GAME_ADDR(0x285BEC))

#define THIS ((ItemBHeart*)thisx)

void ItemBHeart_rInit(Actor* thisx, GlobalContext* globalCtx) {
    ItemBHeart* container = THIS;

    ItemBHeart_Init(&container->actor, globalCtx);
    Model_SpawnByActor(&container->actor, globalCtx, 0x4F);
}

void ItemBHeart_rDestroy(Actor* thisx, GlobalContext* globalCtx) {
    ItemBHeart* container = THIS;

    Model_DestroyByActor(&container->actor);
    ItemBHeart_Destroy(&container->actor, globalCtx);
}

void ItemBHeart_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    ItemBHeart* container = THIS;

    if (Flags_GetCollectible(globalCtx, 0x1F)) {
        Actor_Kill(&container->actor);
        return;
    }

    ItemBHeart_Update(&container->actor, globalCtx);
}

void ItemBHeart_rDraw(Actor* thisx, GlobalContext* globalCtX) {
    ItemBHeart* container = THIS;

    if (!Model_DrawByActor(&container->actor)) {
        ItemBHeart_Draw(&container->actor, globalCtX);
    }
}
