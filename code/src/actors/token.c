#include "z3D/z3D.h"
#include "z3D/actors/z_en_si.h"
#include "models.h"

#define EnSi_Init ((ActorFunc)GAME_ADDR(0x168A90))

#define EnSi_Destroy ((ActorFunc)GAME_ADDR(0x168C3C))

#define EnSi_Update ((ActorFunc)GAME_ADDR(0x1BA0C8))

#define EnSi_Draw ((ActorFunc)GAME_ADDR(0x1BA050))

#define THIS ((EnSi*)thisx)

#define EnSi_DestroyAfterText (void*)GAME_ADDR(0x3D0544)

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

void EnSi_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnSi* token = THIS;

    // Remove when token picked up by other player to prevent duplicates
    u8 idx = (token->actor.params >> 8) & 0x1F;
    if (token->actionFunc != EnSi_DestroyAfterText && gSaveContext.gsFlags[idx] & (token->actor.params & 0xFF)) {
        Actor_Kill((Actor*)token);
        return;
    }

    EnSi_Update(&token->actor, globalCtx);
}

typedef u32 (*EnSi_Draw_GetData_proc)(void);

void EnSi_rDraw(Actor* thisx, GlobalContext* globalCtx) {
    EnSi* token = THIS;

    if (token->actionFunc != (EnSiActionFunc)GAME_ADDR(0x3D0544)) {
        token->unk_20C[3] = ((EnSi_Draw_GetData_proc)GAME_ADDR(0x3695F8))() ? 0.0f : 2.0f;
        if (!Model_DrawByActor(&token->actor)) {
            EnSi_Draw(&token->actor, globalCtx);
        }
    }
}
