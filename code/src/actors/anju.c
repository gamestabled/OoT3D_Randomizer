#include "z3D/z3D.h"
#include "settings.h"

#include "anju.h"

u32 EnNiwLady_CheckCuccoAmount(u32 cuccosInPen) {
    return cuccosInPen - gSettingsContext.numRequiredCuccos + 7;
}

void EnNiwLady_rGiveCojiro(EnNiwLady* self, GlobalContext* globalCtx) {
    if (Actor_HasParent(&self->actor, globalCtx)) {
        gSaveContext.itemGetInf[2] |= 0x4000;
        self->actionFunc = (EnNiwLady_ActionFunc)GAME_ADDR(0x2389EC);
    } else {
        GiveItem(&self->actor, globalCtx, GI_COJIRO, 200.0f, 100.0f);
    }
}
