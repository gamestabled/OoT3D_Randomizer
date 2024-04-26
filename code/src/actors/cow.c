#include "z3D/z3D.h"
#include "settings.h"
#include "entrance.h"
#include "cow.h"

#define EnCow_Init ((ActorFunc)GAME_ADDR(0x189FD4))

#define EnCow_Destroy ((ActorFunc)GAME_ADDR(0x18A3E4))

static s32 sNumCows = 0;

void EnCow_rInit(Actor* thisx, GlobalContext* globalCtx) {
    static PosRot LLR_TowerRightCow_PosRot = { { -283.13f, 0.0f, 110.46f }, { 0x0000, 0x5044, 0x0000 } };

    if (Entrance_SceneAndSpawnAre(0x3E, 0x0D)) { // DMT grotto, index 05FC in the entrance table
        thisx->home.rot.x = 1;
    } else if (Entrance_SceneAndSpawnAre(0x3E, 0x05)) { // HF grotto, index 05A8 in the entrance table
        thisx->home.rot.x = 2;
    } else if (gGlobalContext->sceneNum == 0x0002) { // Jabu-Jabu (MQ)
        thisx->home.rot.x = 1;
    } else {
        thisx->home.rot.x = (sNumCows == 0) ? 1 : 2; // All others
    }
    sNumCows++;

    // Move the right cow in LLR tower
    if ((gGlobalContext->sceneNum == 0x004C) && (thisx->home.rot.x == 1)) {
        thisx->world = LLR_TowerRightCow_PosRot;
    }

    EnCow_Init(thisx, globalCtx);
}

void EnCow_rDestroy(Actor* thisx, GlobalContext* globalCtx) {
    sNumCows = 0;
    EnCow_Destroy(thisx, globalCtx);
}

u32 EnCow_BottleCheck(Actor* cow) {
    s16 cowId = cow->home.rot.x;

    // If cow doesn't give an item, or the collect flag is set, check for bottle
    // Otherwise, we give the item, return true
    if (!gSettingsContext.shuffleCows || (cowId == 0) || (gGlobalContext->actorCtx.flags.collect & (cowId << 0x18))) {
        return Inventory_HasEmptyBottle();
    } else {
        return 1;
    }
}

s32 EnCow_ItemOverride(Actor* cow) {
    s16 cowId = cow->home.rot.x;

    // If cow doesn't give an item, or the collect flag is set, give milk refill
    if (!gSettingsContext.shuffleCows || (cowId == 0) || (gGlobalContext->actorCtx.flags.collect & (cowId << 0x18))) {
        return GI_MILK;
    } else {
        gGlobalContext->actorCtx.flags.collect |= (cowId << 0x18);
        return GI_MILK_BOTTLE + cowId;
    }
}
