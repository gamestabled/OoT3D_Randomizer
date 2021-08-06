#include "z3D/z3D.h"
#include "graveyard_objects.h"

#define CsTimer (gGlobalContext->csCtx.frames)

#define BgSpot02Objects_Update_addr 0x3831AC
#define BgSpot02Objects_Update ((ActorFunc)BgSpot02Objects_Update_addr)

void BgSpot02Objects_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    BgSpot02Objects_Update(thisx, globalCtx);
    // Royal Family's Tomb.        Tomb opened (or opening).                Just for safety in case of WW.
    if (thisx->params == 0x0002 && (gSaveContext.eventChkInf[1] & 0x2000) && gSaveContext.sceneSetupIndex < 4) {
        if (CsTimer > 0 && CsTimer < 740) {
            CsTimer = 740;
        } else if (CsTimer > 740 && CsTimer < 869) {
            CsTimer = 869;
        }
    }
}
