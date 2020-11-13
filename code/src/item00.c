#include "z3D/z3D.h"
#include "z3D/actors/z_en_item00.h"
#include "models.h"

#define EnItem00_Init_addr 0x1F69B4
#define EnItem00_Init ((ActorFunc)EnItem00_Init_addr)

#define EnItem00_Destroy_addr 0x1F706C
#define EnItem00_Destroy ((ActorFunc)EnItem00_Destroy_addr)

#define EnItem00_Draw_addr 0x22B6C0
#define EnItem00_Draw ((ActorFunc)EnItem00_Draw_addr)

#define THIS ((EnItem00*)thisx)

void EnItem00_rInit(Actor* thisx, GlobalContext* globalCtx) {
    EnItem00* item = THIS;

    EnItem00_Init(&item->actor, globalCtx);
    Model_SpawnByActor(&item->actor, globalCtx, 0);
}

void EnItem00_rDestroy(Actor* thisx, GlobalContext* globalCtx) {
    EnItem00* item = THIS;

    Model_DestroyByActor(&item->actor);
    EnItem00_Destroy(&item->actor, globalCtx);
}

void EnItem00_rDraw(Actor* thisx, GlobalContext* globalCtX) {
    EnItem00* item = THIS;
    
    if ((item->unk_1B0 & item->unk_1AE) == 0) {
        if (!Model_DrawByActor(&item->actor)) {
            EnItem00_Draw(&item->actor, globalCtX);
        }
    }
}
