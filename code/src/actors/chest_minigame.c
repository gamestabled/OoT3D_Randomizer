#include "z3D/z3D.h"
#include "settings.h"
#include "chest_minigame.h"

#define EnTakaraMan_Init ((ActorFunc)GAME_ADDR(0x26DEB8))

#define EnChanger_Init ((ActorFunc)GAME_ADDR(0x20EC50))

#define sLoserGetItemIds ((s32*)GAME_ADDR(0x521774))

void EnTakaraMan_rInit(Actor* thisx, GlobalContext* globalCtx) {
    if (gSettingsContext.shuffleChestMinigame) {
        Actor_Kill(thisx);
    } else {
        EnTakaraMan_Init(thisx, globalCtx);
    }
}

void EnChanger_rInit(Actor* thisx, GlobalContext* globalCtx) {
    if (gSettingsContext.shuffleChestMinigame) { // Set loser chests to be Ice Traps
        sLoserGetItemIds[0] = 0;
        sLoserGetItemIds[1] = 0x7C;
        sLoserGetItemIds[2] = 0x7C;
        sLoserGetItemIds[3] = 0x7C;
        sLoserGetItemIds[4] = 0x7C;
        sLoserGetItemIds[5] = 0x7C;
    }
    EnChanger_Init(thisx, globalCtx);

    // Prevent the actor from setting chest flags, but not for the
    // final room because it sets the reward itemGetInf flag
    if (gSettingsContext.shuffleChestMinigame && thisx->room != 6) {
        Actor_Kill(thisx);
    }
}
