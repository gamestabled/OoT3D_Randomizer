#include "z3D/z3D.h"
#include "anubis.h"
#include "enemy_souls.h"

#define EnAnubice_Update ((ActorFunc)0x246E58)

void EnAnubice_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnAnubice* this = (EnAnubice*)thisx;

    if (!EnemySouls_CheckSoulForActor(thisx)) {
        for (s32 i = 0; i < 5; i++) {
            this->flameCircles[i] = 0;
        }
    }
    EnAnubice_Update(thisx, globalCtx);
}
