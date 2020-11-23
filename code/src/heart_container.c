#include "z3D/z3D.h"
#include "z3D/actors/z_item_b_heart.h"
#include "models.h"

#define ItemBHeart_Init_addr 0x25375C
#define ItemBHeart_Init ((ActorFunc)ItemBHeart_Init_addr)

#define ItemBHeart_Destroy_addr 0x2537D4
#define ItemBHeart_Destroy ((ActorFunc)ItemBHeart_Destroy_addr)

#define ItemBHeart_Draw_addr 0x285BEC
#define ItemBHeart_Draw ((ActorFunc)ItemBHeart_Draw_addr)

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

void ItemBHeart_rDraw(Actor* thisx, GlobalContext* globalCtX) {
    ItemBHeart* container = THIS;
    
    if (!Model_DrawByActor(&container->actor)) {
        ItemBHeart_Draw(&container->actor, globalCtX);
    }
}
