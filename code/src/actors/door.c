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

// EnDoor

#define EnDoor_Update ((ActorFunc)GAME_ADDR(0x1F53C8))

#define EnDoor_Idle (void*)GAME_ADDR(0x3F1B28)
#define EnDoor_Open (void*)GAME_ADDR(0x3EC04C)
void EnDoor_Unlocking(EnDoor* thisx, GlobalContext* globalCtx);

void EnDoor_rUpdate(EnDoor* thisx, GlobalContext* globalCtx) {
    void* prev_action_fn = thisx->action_fn;

    EnDoor_Update((Actor*)thisx, globalCtx);

    if (thisx->lock_timer != 0 && prev_action_fn == EnDoor_Idle && thisx->action_fn == EnDoor_Open) {
        Multiplayer_Send_UnlockedDoor(thisx->base.params & 0x3F);
        Multiplayer_Send_ActorUpdate((Actor*)thisx, NULL, 0);
    }
}

void EnDoor_Unlock(EnDoor* thisx) {
    if (thisx->action_fn != EnDoor_Idle) {
        return;
    }
    thisx->action_fn = &EnDoor_Unlocking;
    PlaySFX(0x10001D3, &thisx->base.world.pos, 4, (f32*)GAME_ADDR(0x54AC20), (f32*)GAME_ADDR(0x54AC20),
            (s8*)GAME_ADDR(0x54AC24)); // NA_SE_EV_CHAIN_KEY_UNLOCK
}

void EnDoor_Unlocking(EnDoor* thisx, GlobalContext* globalCtx) {
    if (thisx->lock_timer > 0) {
        thisx->lock_timer--;
        return;
    }
    thisx->action_fn = EnDoor_Idle;
}

// DoorShutter

#define DoorShutter_Init ((ActorFunc)GAME_ADDR(0x2453E0))

void DoorShutter_rInit(Actor* thisx, GlobalContext* globalCtx) {
    // In Treasure Chest Shop when its chests are shuffled,
    // make doors use permanent flags instead of temp ones
    if (globalCtx->sceneNum == 16 && gSettingsContext.shuffleChestMinigame) {
        thisx->params &= ~0x0020;
    }
    DoorShutter_Init(thisx, globalCtx);
}

#define DoorShutter_Update_addr
#define DoorShutter_Update ((ActorFunc)GAME_ADDR(0x27E6E0))

#define DoorShutter_SlidingDoor_Idle (void*)GAME_ADDR(0x3F4A3C)
#define DoorShutter_SlidingDoor_Open (void*)GAME_ADDR(0x3EEE7C)
void DoorShutter_Unlocking(DoorShutter* thisx, GlobalContext* globalCtx);

void DoorShutter_rUpdate(DoorShutter* thisx, GlobalContext* globalCtx) {
    void* prev_action_fn = thisx->action_fn;

    DoorShutter_Update((Actor*)thisx, globalCtx);

    // Don't sync chest minigame doors when the setting is off
    if (globalCtx->sceneNum == 16 && gSettingsContext.shuffleChestMinigame == SHUFFLECHESTMINIGAME_OFF) {
        return;
    }

    if (thisx->lock_timer != 0 && prev_action_fn == DoorShutter_SlidingDoor_Idle &&
        thisx->action_fn == DoorShutter_SlidingDoor_Open) {
        if (thisx->door_type_maybe != 5) {
            Multiplayer_Send_UnlockedDoor(thisx->base.params & 0x3F);
        }
        Multiplayer_Send_ActorUpdate((Actor*)thisx, NULL, 0);
    }
}

void DoorShutter_Unlock(DoorShutter* thisx) {
    if (thisx->action_fn != DoorShutter_SlidingDoor_Idle) {
        return;
    }
    thisx->action_fn = &DoorShutter_Unlocking;
    //                         NA_SE_EV_CHAIN_KEY_UNLOCK : NA_SE_EV_CHAIN_KEY_UNLOCK_B
    u32 sfx_id = thisx->door_type_maybe != 5 ? 0x10001D3 : 0x1000200;
    PlaySFX(sfx_id, &thisx->base.world.pos, 4, (f32*)GAME_ADDR(0x54AC20), (f32*)GAME_ADDR(0x54AC20),
            (s8*)GAME_ADDR(0x54AC24));
}

void DoorShutter_Unlocking(DoorShutter* thisx, GlobalContext* globalCtx) {
    if (thisx->lock_timer > 0) {
        thisx->lock_timer--;
        return;
    }
    thisx->action_fn = DoorShutter_SlidingDoor_Idle;
}

// DoorGerudo

#define DoorGerudo_Update ((ActorFunc)GAME_ADDR(0x263118))

#define DoorGerudo_Idle (void*)GAME_ADDR(0x3F3FA0)
#define DoorGerudo_Unlocking (void*)GAME_ADDR(0x3EEE38)

void DoorGerudo_rUpdate(DoorGerudo* thisx, GlobalContext* globalCtx) {
    void* prev_action_fn = thisx->action_fn;

    DoorGerudo_Update((Actor*)thisx, globalCtx);

    if (thisx->lock_timer != 0 && prev_action_fn == DoorGerudo_Idle && thisx->action_fn == DoorGerudo_Unlocking) {
        Multiplayer_Send_UnlockedDoor(thisx->base.params & 0x3F);
        Multiplayer_Send_ActorUpdate((Actor*)thisx, NULL, 0);
    }
}

void DoorGerudo_Unlock(DoorGerudo* thisx) {
    if (thisx->action_fn != DoorGerudo_Idle || thisx->lock_timer == 0) {
        return;
    }
    thisx->action_fn = DoorGerudo_Unlocking;
    PlaySFX(0x10001D3, &thisx->base.world.pos, 4, (f32*)GAME_ADDR(0x54AC20), (f32*)GAME_ADDR(0x54AC20),
            (s8*)GAME_ADDR(0x54AC24)); // NA_SE_EV_CHAIN_KEY_UNLOCK
}
