#include "z3D/z3D.h"
#include "z3D/actors/z_item_etcetera.h"
#include "models.h"

#define ItemEtcetera_Init_addr 0x273F28
#define ItemEtcetera_Init ((ActorFunc)ItemEtcetera_Init_addr)

#define ItemEtcetera_Destroy_addr 0x2740BC
#define ItemEtcetera_Destroy ((ActorFunc)ItemEtcetera_Destroy_addr)

#define ItemEtcetera_Draw_addr 0x11707C
#define ItemEtcetera_Draw ((ActorFunc)ItemEtcetera_Draw_addr)

#define THIS ((ItemEtcetera*)thisx)

void ItemEtcetera_rInit(Actor* thisx, GlobalContext* globalCtx) {
    ItemEtcetera* item = THIS;

    ItemEtcetera_Init(&item->actor, globalCtx);
    Model_SpawnByActor(&item->actor, globalCtx, item->getItemId);
}

void ItemEtcetera_rDestroy(Actor* thisx, GlobalContext* globalCtx) {
    ItemEtcetera* item = THIS;

    Model_DestroyByActor(&item->actor);
    ItemEtcetera_Destroy(&item->actor, globalCtx);
}
