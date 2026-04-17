#include "z3D/z3D.h"
#include "settings.h"
#include "red_ice.h"

#define ARROW_ICE 4

void BgIceShelter_Melt(BgIceShelter* this, GlobalContext* globalCtx);

void RedIce_CheckIceArrow(Collider* at, Collider* ac) {
    if (gSettingsContext.extraArrowEffects && at->actor != NULL && at->actor->id == ACTOR_ARROW &&
        at->actor->params == ARROW_ICE && ac->actor != NULL && ac->actor->id == ACTOR_RED_ICE) {

        BgIceShelter* ice = (BgIceShelter*)ac->actor;
        s16 type          = (ice->dyna.actor.params >> 8) & 7;

        if (type == RED_ICE_KING_ZORA) {
            if (ice->dyna.actor.parent != NULL) {
                ice->dyna.actor.parent->freezeTimer = 50;
            }
        }

        ice->actionFunc = BgIceShelter_Melt;
        ice->alpha      = 0xFF;
        Actor_PlaySfx(&ice->dyna.actor, NA_SE_EV_ICE_MELT);
    }
}
