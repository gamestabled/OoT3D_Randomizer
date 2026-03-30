#include "z3D/z3D.h"
#include "settings.h"

void EnExRuppy_Update(Actor* thisx, GlobalContext* globalCtx);

void EnExRuppy_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    if (thisx->params == 0x2 && thisx->xzDistToPlayer < 30.0f) {
        PLAYER->actor.colChkInfo.damage = (gSettingsContext.mirrorWorld) ? 16 : 8;

        if (PLAYER->invincibilityTimer > 0) {
            PLAYER->invincibilityTimer = 0;
        }
    }
    EnExRuppy_Update(thisx, globalCtx);
}
