#include "z3D/z3D.h"
#include "settings.h"

#include "grog.h"

#define EnHs_ActionAfterTradeCojiro ((EnHs_ActionFunc)GAME_ADDR(0x3B02C0))

void EnHs_CheckForShouldDespawn(EnHs* self) {
    if ((gSettingsContext.shuffleAdultTradeQuest == SHUFFLEADULTTRADEQUEST_ON) &&
        (gSaveContext.itemGetInf[2] & 0x2000)) {
        Actor_Kill(&self->actor);
    } else if ((gSettingsContext.shuffleAdultTradeQuest == SHUFFLEADULTTRADEQUEST_OFF) &&
               (gSaveContext.itemGetInf[3] & 0x1)) {
        Actor_Kill(&self->actor);
    }
}

void EnHs_SetTradedCojiroFlag(EnHs* self, GlobalContext* globalCtx) {
    gSaveContext.itemGetInf[2] |= 0x2000;
    self->actionFunc = EnHs_ActionAfterTradeCojiro;
    self->unk_704 |= 1;
}
