#include "z3D/z3D.h"
#include "settings.h"

#define EnExRuppy_Update_addr 0x2689B8
#define EnExRuppy_Update ((ActorFunc)EnExRuppy_Update_addr)

void EnExRuppy_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    if (thisx->params == 0x2 && thisx->xzDistToPlayer < 30.0f) {
        PLAYER->actor.colChkInfo.damage = (gSettingsContext.mirrorWorld) ? 16 : 8;
    }
    EnExRuppy_Update(thisx, globalCtx);
}
