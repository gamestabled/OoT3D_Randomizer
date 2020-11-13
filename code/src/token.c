#include "z3D/z3D.h"
#include "z3D/actors/z_en_si.h"
#include "models.h"

#define EnSi_Init_addr 0x168A90
#define EnSi_Init ((ActorFunc)EnSi_Init_addr)

#define EnSi_Destroy_addr 0x168C3C
#define EnSi_Destroy ((ActorFunc)EnSi_Destroy_addr)

#define EnSi_Draw_addr 0x1BA050
#define EnSi_Draw ((ActorFunc)EnSi_Draw_addr)

#define THIS ((EnSi*)thisx)

void EnSi_rInit(Actor* thisx, GlobalContext* globalCtx) {
    EnSi* token = THIS;

    EnSi_Init(&token->actor, globalCtx);
    Model_SpawnByActor(&token->actor, globalCtx, 0);
}

void EnSi_rDestroy(Actor* thisx, GlobalContext* globalCtx) {
    EnSi* token = THIS;

    Model_DestroyByActor(&token->actor);
    EnSi_Destroy(&token->actor, globalCtx);
}

typedef u32 (*EnSi_Draw_GetData_proc)(void);

void EnSi_rDraw(Actor* thisx, GlobalContext* globalCtx) {
    EnSi* token = THIS;

    if (token->actionFunc != (EnSiActionFunc)0x3D0544) {
        token->unk_20C[3] = ((EnSi_Draw_GetData_proc)0x3695F8)() ? 0.0f : 2.0f;
        if (!Model_DrawByActor(&token->actor)) {
            EnSi_Draw(&token->actor, globalCtx);
        }
    }
}
