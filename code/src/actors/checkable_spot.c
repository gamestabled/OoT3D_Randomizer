#include "z3D/z3D.h"
#include "checkable_spot.h"
#include "savefile.h"
#include "settings.h"

#define EnWonderTalk_Update_addr 0x3731F4
#define EnWonderTalk_Update ((ActorFunc)EnWonderTalk_Update_addr)

#define EnWonderTalk2_Update_addr 0x3794EC
#define EnWonderTalk2_Update ((ActorFunc)EnWonderTalk2_Update_addr)

void EnWonderTalk_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnWonderTalk* this = (EnWonderTalk*)thisx;
    if (this->actionFunc == (ActorFunc)0x2065E0 && thisx->params == 0x0FFF) { // reading ToT altar
        gExtSaveData.extInf[EXTINF_TOTALTAR_FLAGS] |= (1 << gSaveContext.linkAge);
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
