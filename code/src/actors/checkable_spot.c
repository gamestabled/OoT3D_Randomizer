#include "z3D/z3D.h"
#include "checkable_spot.h"
#include "savefile.h"
#include "settings.h"

void EnWonderTalk_Update(Actor* thisx, GlobalContext* globalCtx);
void EnWonderTalk2_Update(Actor* thisx, GlobalContext* globalCtx);

void EnWonderTalk_Action_2065E0(EnWonderTalk* this, GlobalContext* globalCtx);

void EnWonderTalk_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnWonderTalk* this = (EnWonderTalk*)thisx;
    if (this->actionFunc == EnWonderTalk_Action_2065E0 && thisx->params == 0x0FFF) { // reading ToT altar
        gExtSaveData.extInf.totAltarFlags |= (1 << gSaveContext.linkAge);
    }
    EnWonderTalk_Update(thisx, globalCtx);
}

void EnWonderTalk2_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    // Automatic text boxes (GtG, Shadow Temple) despawn immediately so they don't appear
    if ((thisx->params & 0xC000) == 0x4000) {
        Actor_Kill(thisx);
    } else {
        EnWonderTalk2_Update(thisx, globalCtx);
    }
}
