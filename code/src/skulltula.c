#include "skulltula.h"
#include "multiplayer.h"
#include "settings.h"

#define EnSw_Update_addr 0x1BB110
#define EnSw_Update ((ActorFunc)EnSw_Update_addr)

#define EnSw_GoldSkulltulaDeath (void*)0x3B91BC

void EnSw_rUpdate(EnSw* thisx, GlobalContext* globalCtx) {
    // Remove when token picked up by other player to prevent duplicates
    if (thisx->base.params & 0xE000) {
        u8 idx = (thisx->base.params >> 8) & 0x1F;
        if (gSaveContext.gsFlags[idx] & (thisx->base.params & 0xFF)) {
            Actor_Kill((Actor*)thisx);
            return;
        }
    }

    void* prev_action_fn = thisx->action_fn;

    EnSw_Update((Actor*)thisx, globalCtx);

    if (prev_action_fn != thisx->action_fn && thisx->action_fn == EnSw_GoldSkulltulaDeath) {
        Multiplayer_Send_ActorUpdate((Actor*)thisx, NULL, 0);
    }
}

typedef void(*FUN_00375B70_proc)(GlobalContext* globalCtx, Actor* actor);
#define FUN_00375B70_addr 0x375B70
#define FUN_00375B70 ((FUN_00375B70_proc)FUN_00375B70_addr)

void EnSw_Kill(EnSw* thisx, GlobalContext* globalCtx) {
    if (thisx->action_fn == EnSw_GoldSkulltulaDeath || (thisx->base.params & 0x4000 && !gSaveContext.nightFlag)) {
        return;
    }
    // TODO: Fix spin speed
    thisx->unk_word2 = 24;
    FUN_00375B70(globalCtx, &thisx->base); // Not needed?
    thisx->base.colChkInfo.health = 0;
    //thisx->anime.play_speed = 8.0; // Doesn't seem to matter
    thisx->unk_float1 = 16.0;
    thisx->deathTimer_maybe = 15;
    thisx->unk_word1 = 1;
    thisx->action_fn = EnSw_GoldSkulltulaDeath;
}

s32 EnSw_IsMasterQuestSkulltula(void) {
    // Certain Gold Skulltulas check the MQ flag to determine if they should have a collider or not.
    // Grezzo did this to make MQ skulltulas intangible if they're hidden inside blocks.
    // For the randomizer they have to check the individual dungeon mode.
    s16 scene = gGlobalContext->sceneNum;
    if (scene <= 9)
        return gSettingsContext.dungeonModes[scene];
    else if (scene == 11) // GtG
        return gSettingsContext.dungeonModes[11];
    else if (scene == 13) // Inside Ganon's Castle
        return gSettingsContext.dungeonModes[10];

    return 0;
}
