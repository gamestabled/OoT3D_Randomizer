#include "z3D/z3D.h"
#include "windmill_man.h"

#define CsTimer (gGlobalContext->csCtx.frames)

#define EnFu_Update ((ActorFunc)GAME_ADDR(0x1B1328))

void EnFu_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnFu_Update(thisx, globalCtx);

    if (CsTimer > 80 && CsTimer < 480) {
        CsTimer                     = 480;
        gGlobalContext->csCtx.state = 3;
        gSaveContext.eventChkInf[6] |= 0x0080;
    }
}
