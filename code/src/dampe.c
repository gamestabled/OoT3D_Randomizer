#include "z3D/z3D.h"

typedef struct {
    /* 0x000 */ char unk_00[0xBA8];
    /* 0xBA8 */ u32  currentReward;
} EnTk;

typedef struct {
    /* 0x000 */ char unk_00[0xB1C];
    /* 0xB1C */ u8   unk_B1C;
} EnPoRelay;


// Sets the flag for having received the reward from Dampe
// Upgrades the current reward to 4, the highest
void EnTk_SetRewardFlag(EnTk* dampe) {
    gSaveContext.itemGetInf[1] |= 0x1000;
    dampe->currentReward = 4;
}

// Runs in the destroy function for Dampe
// Checks if the reward was collected, and if not
// unsets the flag for having received the reward
void EnTk_CheckCollectFlag(void) {
    // Custom collectible flag for the heart piece
    if (!(gGlobalContext->actorCtx.flags.collect & 0x100)) {
        gSaveContext.itemGetInf[1] &= ~0x1000;
    }
}

// Checks the clear flag for the first race (chest spawned, not opened)
// Replaces a check for hookshot in the inventory
void EnPoRelay_CheckChestFlag(EnPoRelay* dampe) {
    dampe->unk_B1C = ((gSaveContext.sceneFlags[0x48].clear & 0x00000010) != 0);
}
