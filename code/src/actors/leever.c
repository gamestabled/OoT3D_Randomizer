#include "leever.h"
#include "settings.h"

#define EnReeba_SetupSurface ((EnReebaActionFunc)GAME_ADDR(0x181394))
#define EnReeba_Die ((EnReebaActionFunc)GAME_ADDR(0x3D4CB0))

s32 Leever_ShouldSurviveOutsideSand(Actor* actor) {
    return Enemizer_IsEnemyRandomized(ENEMY_LEEVER) &&
           (actor->parent == NULL ||
            (gGlobalContext->sceneNum != SCENE_DESERT_COLOSSUS && gGlobalContext->sceneNum != SCENE_HAUNTED_WASTELAND));
}

void Leever_AfterSink(EnReeba* leever) {
    if (leever->actor.colChkInfo.health == 0) {
        // Base game bug: if the Leever is killed on the same frame it hits Link, its action function will be set to
        // `EnReeba_Die` and then `EnReeba_Sink` during the same update cycle; when this happens it doesn't drop items
        // and, if it's a randomized enemy, it becomes an invulnerable zombie with 0 health and no colliders. Fix this
        // by resetting the action function to `EnReeba_Die`.
        leever->actionFunc = EnReeba_Die;
    } else if (Enemizer_IsEnemyRandomized(ENEMY_LEEVER) && leever->actor.parent == NULL) {
        leever->actor.world.pos = leever->actor.home.pos;
        leever->actionFunc      = EnReeba_SetupSurface;
    } else {
        Actor_Kill(&leever->actor);
    }
}

void Leever_AfterDie(Actor* actor) {
    if (Enemizer_IsEnemyRandomized(ENEMY_LEEVER) && actor->parent == NULL && actor->colChkInfo.health == 0) {
        Actor_Kill(actor);
    }
}
