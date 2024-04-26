#include "dampe.h"

#define EnTk_Update ((ActorFunc)GAME_ADDR(0x1BC088))

void EnTk_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    // Custom collectible flag for the heart piece
    if (gGlobalContext->actorCtx.flags.collect & 0x100) {
        // Sets the flag for having received the reward from Dampe
        gSaveContext.itemGetInf[1] |= 0x1000;
    }
    EnTk_Update(thisx, globalCtx);
}

// Upgrades the current reward to 4, the highest
void EnTk_SetRewardFlag(EnTk* dampe) {
    dampe->currentReward = 4;
}

// Checks the clear flag for the first race (chest spawned, not opened)
// Replaces a check for hookshot in the inventory
void EnPoRelay_CheckChestFlag(EnPoRelay* dampe) {
    dampe->unk_B1C = ((gSaveContext.sceneFlags[0x48].clear & 0x00000010) != 0);
}
