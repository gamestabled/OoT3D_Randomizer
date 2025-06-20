#include "dead_hand_hand.h"
#include "settings.h"

#define EnDha_Update ((ActorFunc)GAME_ADDR(0x113050))

void EnDha_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnDha_Update(thisx, globalCtx);

    if (gSettingsContext.enemizer == ON && thisx->parent == NULL && thisx->shape.yOffset <= -12000.0f) {
        // Kill the actor when the hand is defeated so that dungeon rooms can be cleared.
        Actor_Kill(thisx);
    }
}
