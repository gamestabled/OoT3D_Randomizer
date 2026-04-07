#include "stalchild.h"
#include "settings.h"
#include "enemizer.h"
#include "enemy_souls.h"

void EnSkb_Update(Actor* thisx, GlobalContext* globalCtx);

s32 Stalchild_CanDespawn(Actor* stalchild) {
    return !Enemizer_IsEnemyRandomized(ENEMY_STALCHILD) ||
           (stalchild->parent != NULL && (gGlobalContext->sceneNum == SCENE_HYRULE_FIELD ||
                                          Math_Vec3f_DistXZ(&stalchild->home.pos, &PLAYER->actor.world.pos) > 800.0f));
}

void EnSkb_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    if (!EnemySouls_CheckSoulForActor(thisx)) {
        // prevent drowning
        thisx->depthInWater = 0;
    }

    EnSkb_Update(thisx, globalCtx);
}
