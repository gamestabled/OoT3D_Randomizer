#include "door.h"
#include "models.h"
#include "settings.h"
#include "multiplayer.h"

// Certain doors can cause a crash depending on a freestanding
// model in the room that is being transitioned out of. We can
// avoid the crash by deleting all the models as soon as Link
// opens a door. However, some scenes have doors near freestanding
// items which don't cause a room transition, so we have to avoid
// those
void Door_CheckToDeleteCustomModels(Actor* door) {
    if ((gGlobalContext->sceneNum != 0x000C) && // Thieves' Hideout
        (gGlobalContext->sceneNum != 0x0001)) { // Dodongo's Cavern
        Model_DestroyAll();
    }
}

/*------------------------------
|           EN_DOOR            |
------------------------------*/

void EnDoor_Update(Actor* thisx, GlobalContext* globalCtx);

void EnDoor_Idle(EnDoor* this, GlobalContext* globalCtx);
void EnDoor_Open(EnDoor* this, GlobalContext* globalCtx);
void EnDoor_Unlocking(EnDoor* this, GlobalContext* globalCtx);

void EnDoor_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnDoor* this = (EnDoor*)thisx;

    EnDoorActionFunc prev_action_fn = this->action_fn;

    EnDoor_Update(thisx, globalCtx);

    if (this->lock_timer != 0 && prev_action_fn == EnDoor_Idle && this->action_fn == EnDoor_Open) {
        Multiplayer_Send_UnlockedDoor(this->base.params & 0x3F);
        Multiplayer_Send_ActorUpdate(thisx, NULL, 0);
    }
}

void EnDoor_Unlock(EnDoor* this) {
    if (this->action_fn != EnDoor_Idle) {
        return;
    }
    this->action_fn = &EnDoor_Unlocking;
    PlaySFX(0x10001D3, &this->base.world.pos, 4, &gSfxDefaultFreqAndVolScale, &gSfxDefaultFreqAndVolScale,
            &gSfxDefaultReverb); // NA_SE_EV_CHAIN_KEY_UNLOCK
}

void EnDoor_Unlocking(EnDoor* this, GlobalContext* globalCtx) {
    if (this->lock_timer > 0) {
        this->lock_timer--;
        return;
    }
    this->action_fn = EnDoor_Idle;
}

/*------------------------------
|         DOOR_SHUTTER         |
------------------------------*/

void DoorShutter_Init(Actor* thisx, GlobalContext* globalCtx);

void DoorShutter_rInit(Actor* thisx, GlobalContext* globalCtx) {
    // In Treasure Chest Shop when its chests are shuffled,
    // make doors use permanent flags instead of temp ones
    if (gSettingsContext.shuffleChestMinigame && globalCtx->sceneNum == SCENE_TREASURE_BOX_SHOP) {
        thisx->params &= ~0x0020;
    }
    // Door after Nabooru Knuckle: open on room clear instead of switch flag if the enemy is randomized
    else if (gEnemizerLocationFlags.nabooruKnuckle && globalCtx->sceneNum == SCENE_SPIRIT_TEMPLE_BOSS &&
             thisx->params == 0x0485) {
        thisx->params = 0x0440;
    }

    DoorShutter_Init(thisx, globalCtx);
}

void DoorShutter_Update(Actor* thisx, GlobalContext* globalCtx);

void DoorShutter_SlidingDoor_Idle(DoorShutter* this, GlobalContext* globalCtx);
void DoorShutter_SlidingDoor_Open(DoorShutter* this, GlobalContext* globalCtx);
void DoorShutter_Unlocking(DoorShutter* this, GlobalContext* globalCtx);

void DoorShutter_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    DoorShutter* this = (DoorShutter*)thisx;

    DoorShutterActionFunc prev_action_fn = this->action_fn;

    DoorShutter_Update(thisx, globalCtx);

    // Don't sync chest minigame doors when the setting is off
    if (globalCtx->sceneNum == 16 && gSettingsContext.shuffleChestMinigame == SHUFFLECHESTMINIGAME_OFF) {
        return;
    }

    if (this->lock_timer != 0 && prev_action_fn == DoorShutter_SlidingDoor_Idle &&
        this->action_fn == DoorShutter_SlidingDoor_Open) {
        if (this->door_type_maybe != 5) {
            Multiplayer_Send_UnlockedDoor(thisx->params & 0x3F);
        }
        Multiplayer_Send_ActorUpdate(thisx, NULL, 0);
    }
}

void DoorShutter_Unlock(DoorShutter* this) {
    if (this->action_fn != DoorShutter_SlidingDoor_Idle) {
        return;
    }
    this->action_fn = &DoorShutter_Unlocking;
    //                         NA_SE_EV_CHAIN_KEY_UNLOCK : NA_SE_EV_CHAIN_KEY_UNLOCK_B
    u32 sfx_id = this->door_type_maybe != 5 ? 0x10001D3 : 0x1000200;
    PlaySFX(sfx_id, &this->base.world.pos, 4, &gSfxDefaultFreqAndVolScale, &gSfxDefaultFreqAndVolScale,
            &gSfxDefaultReverb);
}

void DoorShutter_Unlocking(DoorShutter* this, GlobalContext* globalCtx) {
    if (this->lock_timer > 0) {
        this->lock_timer--;
        return;
    }
    this->action_fn = DoorShutter_SlidingDoor_Idle;
}

/*------------------------------
|         DOOR_GERUDO          |
------------------------------*/

void DoorGerudo_Update(Actor* thisx, GlobalContext* globalCtx);

void DoorGerudo_Idle(DoorGerudo* this, GlobalContext* globalCtx);
void DoorGerudo_Unlocking(DoorGerudo* this, GlobalContext* globalCtx);

void DoorGerudo_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    DoorGerudo* this = (DoorGerudo*)thisx;

    DoorGerudoActionFunc prev_action_fn = this->action_fn;

    DoorGerudo_Update(thisx, globalCtx);

    if (this->lock_timer != 0 && prev_action_fn == DoorGerudo_Idle && this->action_fn == DoorGerudo_Unlocking) {
        Multiplayer_Send_UnlockedDoor(thisx->params & 0x3F);
        Multiplayer_Send_ActorUpdate(thisx, NULL, 0);
    }
}

void DoorGerudo_Unlock(DoorGerudo* this) {
    if (this->action_fn != DoorGerudo_Idle || this->lock_timer == 0) {
        return;
    }
    this->action_fn = DoorGerudo_Unlocking;
    PlaySFX(0x10001D3, &this->base.world.pos, 4, &gSfxDefaultFreqAndVolScale, &gSfxDefaultFreqAndVolScale,
            &gSfxDefaultReverb); // NA_SE_EV_CHAIN_KEY_UNLOCK
}
