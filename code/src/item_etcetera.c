#include "z3D/z3D.h"
#include "z3D/actors/z_item_etcetera.h"
#include "models.h"
#include "settings.h"

#define ItemEtcetera_Init_addr 0x273F28
#define ItemEtcetera_Init ((ActorFunc)ItemEtcetera_Init_addr)

#define ItemEtcetera_Destroy_addr 0x2740BC
#define ItemEtcetera_Destroy ((ActorFunc)ItemEtcetera_Destroy_addr)

#define ItemEtcetera_Update_addr 0x298D88
#define ItemEtcetera_Update ((ActorFunc)ItemEtcetera_Update_addr)

#define ItemEtcetera_Draw_addr 0x11707C
#define ItemEtcetera_Draw ((ActorFunc)ItemEtcetera_Draw_addr)

#define THIS ((ItemEtcetera*)thisx)

void ItemEtcetera_rInit(Actor* thisx, GlobalContext* globalCtx) {
    // In Treasure Box Shop when its chests are shuffled, don't show
    // items inside chests. Also, never show the heart piece
    if (globalCtx->sceneNum == 16 && (gSettingsContext.shuffleChestMinigame || thisx->params == 0x0A0C)) {
        Actor_Kill(thisx);
        return;
    }

    ItemEtcetera* item = THIS;

    ItemEtcetera_Init(&item->actor, globalCtx);
    Model_SpawnByActor(&item->actor, globalCtx, item->getItemId);
}

void ItemEtcetera_rDestroy(Actor* thisx, GlobalContext* globalCtx) {
    ItemEtcetera* item = THIS;

    Model_DestroyByActor(&item->actor);
    ItemEtcetera_Destroy(&item->actor, globalCtx);
}

void ItemEtcetera_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    ItemEtcetera* item = THIS;

    switch (item->actor.params & 0xFF) {
        case 1: // Ruto's Letter
            if (gSaveContext.eventChkInf[3] & 0x2) {
                Actor_Kill(&item->actor);
                return;
            }
            break;
        case 7: // Fire Arrows
            if (gGlobalContext->actorCtx.flags.chest & 0x1) {
                Actor_Kill(&item->actor);
                return;
            }
            break;
    }

    ItemEtcetera_Update(&item->actor, globalCtx);
}
