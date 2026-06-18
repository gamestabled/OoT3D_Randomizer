#include "z3D/z3D.h"
#include "windmill_man.h"

#define CsTimer (gGlobalContext->csCtx.frames)

void EnFu_Update(Actor* thisx, GlobalContext* globalCtx);

void EnFu_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnFu_Update(thisx, globalCtx);

    if (CsTimer > 80 && CsTimer < 480) {
        CsTimer                     = 480;
        gGlobalContext->csCtx.state = 3;
        gSaveContext.eventChkInf[6] |= 0x0080;
    }
}
