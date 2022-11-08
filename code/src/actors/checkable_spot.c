#include "z3D/z3D.h"
#include "checkable_spot.h"

#define EnWonderTalk2_Update_addr 0x3794EC
#define EnWonderTalk2_Update ((ActorFunc)EnWonderTalk2_Update_addr)

//#define EnWonderTalk2_Destroy_addr 0x298D84
//#define EnWonderTalk2_Destroy ((ActorFunc)EnWonderTalk2_Destroy_addr)

void EnWonderTalk2_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    if ((thisx->params & 0xC000) ==
        0x4000) { // automatic text boxes (GtG, Shadow Temple) despawn immediately so they don't appear
        Actor_Kill(thisx);
    } else {
        EnWonderTalk2_Update(thisx, globalCtx);
    }
}
