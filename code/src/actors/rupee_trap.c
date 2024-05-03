#include "z3D/z3D.h"
#include "settings.h"

#define EnExRuppy_Update ((ActorFunc)GAME_ADDR(0x2689B8))

void EnExRuppy_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    if (thisx->params == 0x2 && thisx->xzDistToPlayer < 30.0f) {
        PLAYER->actor.colChkInfo.damage = (gSettingsContext.mirrorWorld) ? 16 : 8;

        if (PLAYER->invincibilityTimer > 0) {
            PLAYER->invincibilityTimer = 0;
        }
    }
    EnExRuppy_Update(thisx, globalCtx);
}
