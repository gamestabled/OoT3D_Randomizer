#include "z3D/z3D.h"
#include "settings.h"
#include "red_ice.h"

#define ACTOR_BG_ICE_SHELTER 0xEF // Red Ice
#define ACTOR_EN_ARROW 0x16
#define ARROW_ICE 4

#define BgIceShelter_Melt ((BgIceShelterActionFunc)GAME_ADDR(0x3F5F00))
#define NA_SE_EV_ICE_MELT 0x10001F9

void RedIce_CheckIceArrow(Collider* at, Collider* ac) {
    if (gSettingsContext.extraArrowEffects && at->actor != 0 && at->actor->id == ACTOR_EN_ARROW &&
        at->actor->params == ARROW_ICE && ac->actor != 0 && ac->actor->id == ACTOR_BG_ICE_SHELTER) {

        BgIceShelter* ice = (BgIceShelter*)ac->actor;
        s16 type          = (ice->dyna.actor.params >> 8) & 7;

        if (type == RED_ICE_KING_ZORA) {
            if (ice->dyna.actor.parent != 0) {
                ice->dyna.actor.parent->freezeTimer = 50;
            }
        }

        ice->actionFunc = BgIceShelter_Melt;
        ice->alpha      = 0xFF;
        Audio_PlayActorSfx2(&ice->dyna.actor, NA_SE_EV_ICE_MELT);
    }
}
