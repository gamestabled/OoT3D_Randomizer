#include "z3D/z3D.h"
#include "settings.h"
#include "chest_minigame.h"

void EnTakaraMan_Init(Actor* thisx, GlobalContext* globalCtx);
void EnChanger_Init(Actor* thisx, GlobalContext* globalCtx);

extern s32 EnChanger_LoserGetItemIds[];

void EnTakaraMan_rInit(Actor* thisx, GlobalContext* globalCtx) {
    if (gSettingsContext.shuffleChestMinigame) {
        Actor_Kill(thisx);
    } else {
        EnTakaraMan_Init(thisx, globalCtx);
    }
}

void EnChanger_rInit(Actor* thisx, GlobalContext* globalCtx) {
    if (gSettingsContext.shuffleChestMinigame) { // Set loser chests to be Ice Traps
        EnChanger_LoserGetItemIds[0] = 0;
        EnChanger_LoserGetItemIds[1] = 0x7C;
        EnChanger_LoserGetItemIds[2] = 0x7C;
        EnChanger_LoserGetItemIds[3] = 0x7C;
        EnChanger_LoserGetItemIds[4] = 0x7C;
        EnChanger_LoserGetItemIds[5] = 0x7C;
    }
    EnChanger_Init(thisx, globalCtx);

    // Prevent the actor from setting chest flags, but not for the
    // final room because it sets the reward itemGetInf flag
    if (gSettingsContext.shuffleChestMinigame && thisx->room != 6) {
        Actor_Kill(thisx);
    }
}
