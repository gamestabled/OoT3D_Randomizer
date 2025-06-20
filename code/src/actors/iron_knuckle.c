#include "iron_knuckle.h"
#include "settings.h"

#define EnIk_Init ((ActorFunc)GAME_ADDR(0x164B0C))

void EnIk_rInit(Actor* thisx, GlobalContext* globalCtx) {
    EnIk* this = (EnIk*)thisx;
    EnIk_Init(thisx, globalCtx);

    if (gSettingsContext.enemizer == ON) {
        // Wake up immediately
        this->skelAnime.playSpeed = 1.0f;
    }
}
