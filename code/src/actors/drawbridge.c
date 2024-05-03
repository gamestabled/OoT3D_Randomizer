#include "z3D/z3D.h"
#include "drawbridge.h"

#define BgSpot00Hanebasi_Update ((ActorFunc)GAME_ADDR(0x38B390))

void BgSpot00Hanebasi_rUpdate(Actor* thisx, GlobalContext* globalCtx) {

    // if about to start Zelda Escape cutscene, don't
    if (gSaveContext.nextCutsceneIndex == 0xFFF1 && globalCtx->nextEntranceIndex == 0x00CD) {
        gSaveContext.nextCutsceneIndex = 0;
    }
    BgSpot00Hanebasi_Update(thisx, globalCtx);
}
