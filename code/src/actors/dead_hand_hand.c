#include "dead_hand_hand.h"
#include "settings.h"

void EnDha_Update(Actor* thisx, GlobalContext* globalCtx);

void EnDha_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnDha_Update(thisx, globalCtx);

    if (Enemizer_IsEnemyRandomized(ENEMY_DEAD_HAND_HAND) && thisx->parent == NULL &&
        thisx->shape.yOffset <= -12000.0f) {
        // Kill the actor when the hand is defeated so that dungeon rooms can be cleared.
        Actor_Kill(thisx);
    }
}
