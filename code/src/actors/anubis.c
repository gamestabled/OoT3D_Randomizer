#include "z3D/z3D.h"
#include "anubis.h"
#include "enemy_souls.h"

#define EnAnubice_Update ((ActorFunc)GAME_ADDR(0x246E58))

void EnAnubice_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnAnubice* this = (EnAnubice*)thisx;

    if (!EnemySouls_CheckSoulForActor(thisx)) {
        for (s32 i = 0; i < 5; i++) {
            this->flameCircles[i] = 0;
        }
    }

    // Fix Anubis falling out of bounds when trying to go back to home position
    if (this->isPlayerOutOfRange) {
        if (thisx->world.pos.y < thisx->home.pos.y) {
            thisx->gravity    = 0.0f;
            thisx->velocity.y = 0.0f;
        }
        Math_SmoothStepToF(&thisx->world.pos.y, thisx->home.pos.y, 3, 10.0, 0.0);
    }

    EnAnubice_Update(thisx, globalCtx);
}
