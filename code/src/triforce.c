#include "triforce.h"
#include "item_override.h"
#include "common.h"
#include "savefile.h"

#define TEXT_STATE_DONE 6

u8 TriforceWarpStatus = TRIFORCEWARP_OFF;

void Triforce_HandleCreditsWarp(void) {
    static s32 sPreviousTextState = 0; // used to add a one-frame delay

    if ((TriforceWarpStatus == TRIFORCEWARP_WHEN_TEXT_COMPLETE && sPreviousTextState == TEXT_STATE_DONE) ||
        (TriforceWarpStatus == TRIFORCEWARP_WHEN_PLAYER_READY && IsInGame() && !gIsBottomScreenDimmed &&
         PauseContext_GetState() == 0 && gGlobalContext->sceneLoadFlag == 0 && !isItemOverrideActive &&
         gGlobalContext->csCtx.state == 0 && !ItemOverride_IsAPendingOverride())) {
        // Set final time for Zelda's text
        gFinalPlaytimeSeconds = gExtSaveData.playtimeSeconds;
        // Save progress
        SaveGame(gGlobalContext, FALSE);
        // Warp to Ganon sealing cutscene
        gGlobalContext->nextEntranceIndex = 0x00A0;
        gSaveContext.nextCutsceneIndex    = 0xFFF8;
        gEntranceTable[0x00A0].field |= 0x8000; // continue playing background music (namely get item fanfare)
        gGlobalContext->fadeOutTransition = 0x2F;
        gGlobalContext->sceneLoadFlag     = 0x14;
        PLAYER->stateFlags1 |= 1; // Loading area
        TriforceWarpStatus = TRIFORCEWARP_OFF;
    }
    sPreviousTextState = Message_GetState();
}

// Used in hook_TurboTextSignalNPC to make NPCs set their collection flag before the credits warp save.
s32 Triforce_IsWaitingForText(void) {
    return TriforceWarpStatus == TRIFORCEWARP_WHEN_TEXT_COMPLETE;
}
