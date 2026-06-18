#include "z3D/z3D.h"
#include "z3D/actors/z_item_ocarina.h"
#include "models.h"

void ItemOcarina_Init(Actor* thisx, GlobalContext* globalCtx);
void ItemOcarina_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ItemOcarina_Draw(Actor* thisx, GlobalContext* globalCtx);

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
