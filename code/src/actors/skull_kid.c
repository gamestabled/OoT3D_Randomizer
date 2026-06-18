#include "skull_kid.h"
#include "settings.h"
#include "enemy_souls.h"
#include "enemizer.h"
#include "actor.h"

void EnSkj_Update(Actor* thisx, GlobalContext* globalCtx);

void EnSkj_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnSkj* this = (EnSkj*)thisx;

    EnSkj_Update(thisx, globalCtx);

    if (EnemySouls_IsInvulnerable(thisx) && thisx->type == ACTORTYPE_ENEMY) {
        // When a soulless enemy skull kid backflips, don't let it fade away and despawn.
        this->backflipFlag = 0;
    }
}

u8 SkullKid_IsRandomized(void) {
    return Enemizer_IsEnemyRandomized(ENEMY_SKULL_KID);
}

void EnSkj_ReinitModels(EnSkj* this) {
    Actor_DestroySkelModels(&this->actor, &this->needleModel, NULL);
    Actor_CreateSkelModels(&this->actor, gGlobalContext, &this->needleModel, 1, NULL);

    Actor_ReinitSkelAnime(&this->actor, &this->anime, 0);
}
