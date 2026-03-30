#include "z3D/z3D.h"
#include "collapsing_castle.h"

void DemoGt_Update(Actor* thisx, GlobalContext* globalCtx);

void DemoGt_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    DemoGt_Update(thisx, globalCtx);
    // set cutscene timer to near the end of the cutscene
    if (globalCtx->csCtx.frames > 10 && globalCtx->csCtx.frames < 100) {
        globalCtx->csCtx.frames = 1670;
    }
}
