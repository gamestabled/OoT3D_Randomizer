#include "guay.h"
#include "settings.h"

#define EnCrow_Update ((ActorFunc)GAME_ADDR(0x1F4D40))

#define EnCrow_Respawn ((EnCrowActionFunc)GAME_ADDR(0x158648))

#define sDefaultColliderRadius 20

void EnCrow_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnCrow* this = (EnCrow*)thisx;

    EnCrow_Update(thisx, globalCtx);

    if (gSettingsContext.enemizer == ON) {
        if (thisx->params == 0x001) { // Mega Guay, change size
            this->collider.elements[0].dim.worldSphere.radius = sDefaultColliderRadius * 3.0;
            Math_SmoothStepToF(&this->actor.scale.x, 0.03f, 3, 0.003f, 0.0);
            this->actor.scale.z = this->actor.scale.y = this->actor.scale.x;
        }
        if (this->actionFunc == EnCrow_Respawn) {
            // Kill the actor when the guay is defeated so that dungeon rooms can be cleared.
            Actor_Kill(thisx);
        }
    }
}
