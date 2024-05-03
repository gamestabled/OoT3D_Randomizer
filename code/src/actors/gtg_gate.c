#include "gtg_gate.h"
#include "settings.h"

#define BgSpot12Saku_Update ((ActorFunc)GAME_ADDR(0x29E030))

#define BgSpot12Saku_Init ((ActorFunc)GAME_ADDR(0x27AD6C))

void BgSpot12Saku_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    // If ER is on, when the guard opens the GtG gate its permanent flag will be set.
    if (gSettingsContext.shuffleDungeonEntrances && globalCtx->actorCtx.flags.tempSwch & 0x04000000) {
        globalCtx->actorCtx.flags.swch |= 0x00000004;
    }
    BgSpot12Saku_Update(thisx, globalCtx);
}

void BgSpot12Saku_rInit(Actor* thisx, GlobalContext* globalCtx) {
    // If ER is on, force the gate to always use its permanent flag
    // (which it only uses in Child Gerudo Fortress in the vanilla game)
    if (gSettingsContext.shuffleDungeonEntrances) {
        thisx->params = 0x0002;
    }
    BgSpot12Saku_Init(thisx, globalCtx);
}
