#include "dampe.h"

/*-------------------------------
|              EnTk             |
-------------------------------*/

void EnTk_Update(Actor* thisx, GlobalContext* globalCtx);

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

/*-------------------------------
|           EnPoRelay           |
-------------------------------*/

void EnPoRelay_Destroy(Actor* thisx, GlobalContext* globalCtx);

void EnPoRelay_rDestroy(Actor* thisx, GlobalContext* globalCtx) {
    EnPoRelay_Destroy(thisx, globalCtx);

    // Despawn previous doors when finishing the race with Dampé.
    Actor* bgActor = globalCtx->actorCtx.actorList[ACTORTYPE_BG].first;
    while (bgActor != NULL) {
        if (bgActor->id == ACTOR_WINDMILL_OBJECTS && bgActor->world.pos.z < -1800.0) {
            Actor_Kill(bgActor);
        }
        bgActor = bgActor->next;
    }
    // Set temp flags to enable loading triggers.
    Flags_SetSwitch(globalCtx, 0x35);
    Flags_SetSwitch(globalCtx, 0x36);
    Flags_SetSwitch(globalCtx, 0x37);
}

// Checks the clear flag for the first race (chest spawned, not opened)
// Replaces a check for hookshot in the inventory
void EnPoRelay_CheckChestFlag(EnPoRelay* dampe) {
    dampe->isSecondRace = ((gSaveContext.sceneFlags[0x48].clear & 0x00000010) != 0);
}
