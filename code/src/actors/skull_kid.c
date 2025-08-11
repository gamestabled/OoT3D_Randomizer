#include "skull_kid.h"
#include "settings.h"
#include "enemy_souls.h"
#include "enemizer.h"

#define EnSkj_Update ((ActorFunc)GAME_ADDR(0x1DE890))

void EnSkj_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnSkj* this = (EnSkj*)thisx;

    EnSkj_Update(thisx, globalCtx);

    if (!EnemySouls_CheckSoulForActor(thisx) && thisx->type == ACTORTYPE_ENEMY) {
        // When a soulless enemy skull kid backflips, don't let it fade away and despawn.
        this->backflipFlag = 0;
    }
}

u8 SkullKid_IsRandomized(void) {
    return Enemizer_IsEnemyRandomized(ENEMY_SKULL_KID);
}
