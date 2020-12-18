#include "z3D/z3D.h"
#include "z3D/actors/z_item_ocarina.h"
#include "models.h"

#define ItemOcarina_Init_addr 0x253818
#define ItemOcarina_Init ((ActorFunc)ItemOcarina_Init_addr)

#define ItemOcarina_Destroy_addr 0x253A1C
#define ItemOcarina_Destroy ((ActorFunc)ItemOcarina_Destroy_addr)

#define ItemOcarina_Draw_addr 0x285D48
#define ItemOcarina_Draw ((ActorFunc)ItemOcarina_Draw_addr)

#define THIS ((ItemOcarina*)thisx)

void ItemOcarina_rInit(Actor* thisx, GlobalContext* globalCtx) {
    ItemOcarina* ocarina = THIS;

    ItemOcarina_Init(&ocarina->actor, globalCtx);
    Model_SpawnByActor(&ocarina->actor, globalCtx, GI_OCARINA_OOT);
}

void ItemOcarina_rDestroy(Actor* thisx, GlobalContext* globalCtx) {
    ItemOcarina* ocarina = THIS;

    Model_DestroyByActor(&ocarina->actor);
    ItemOcarina_Destroy(&ocarina->actor, globalCtx);
}

void ItemOcarina_rDraw(Actor* thisx, GlobalContext* globalCtX) {
    ItemOcarina* ocarina = THIS;
    
    if (!Model_DrawByActor(&ocarina->actor)) {
        ItemOcarina_Draw(&ocarina->actor, globalCtX);
    }
}
