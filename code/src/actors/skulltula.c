#include "skulltula.h"
#include "multiplayer.h"
#include "settings.h"

#define EnSw_Update_addr 0x1BB110
#define EnSw_Update ((ActorFunc)EnSw_Update_addr)

#define EnSw_GoldSkulltulaDeath (void*)0x3B91BC

void EnSw_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnSw* this = (EnSw*)thisx;
    // Remove when token picked up by other player to prevent duplicates
    if (thisx->params & 0xE000) {
        u8 idx = (thisx->params >> 8) & 0x1F;
        if (gSaveContext.gsFlags[idx] & (thisx->params & 0xFF)) {
            Actor_Kill(thisx);
            return;
        }
    }

    void* prev_action_fn = this->action_fn;

    // Fix rotation for the GS in the top room in Fire Temple MQ, which for some reason spawns upside down
    // if the MQ flag is not set and you enter the room from the door.
    if (globalCtx->sceneNum == 4 && gSettingsContext.fireTempleDungeonMode == DUNGEONMODE_MQ && thisx->room == 8) {
        thisx->world.rot.z = 0;
    }

    EnSw_Update(thisx, globalCtx);

    if (prev_action_fn != this->action_fn && this->action_fn == EnSw_GoldSkulltulaDeath) {
        Multiplayer_Send_ActorUpdate((Actor*)thisx, NULL, 0);
    }
}

typedef void (*FUN_00375B70_proc)(GlobalContext* globalCtx, Actor* actor);
#define FUN_00375B70_addr 0x375B70
#define FUN_00375B70 ((FUN_00375B70_proc)FUN_00375B70_addr)

void EnSw_Kill(EnSw* this, GlobalContext* globalCtx) {
    if (this->action_fn == EnSw_GoldSkulltulaDeath || (this->base.params & 0x4000 && !gSaveContext.nightFlag)) {
        return;
    }
    // TODO: Fix spin speed
    this->unk_word2 = 24;
    FUN_00375B70(globalCtx, &this->base); // Not needed?
    this->base.colChkInfo.health = 0;
    // this->anime.play_speed = 8.0; // Doesn't seem to matter
    this->unk_float1       = 16.0;
    this->deathTimer_maybe = 15;
    this->unk_word1        = 1;
    this->action_fn        = EnSw_GoldSkulltulaDeath;
}
