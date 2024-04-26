#include "z3D/z3D.h"
#include "settings.h"
#include "demo_kankyo.h"
#include "entrance.h"
#include "grotto.h"

#define DemoKankyo_Update ((ActorFunc)GAME_ADDR(0x262EA4))

#define CsTimer (globalCtx->csCtx.frames)

void DemoKankyo_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    DemoKankyo_Update(thisx, globalCtx);

    // Warp Song particles
    if (thisx->params == 0x000F) {
        globalCtx->sceneLoadFlag     = 0x14;
        globalCtx->fadeOutTransition = 5;
        switch (globalCtx->lastPlayedSong) {
            case 0:
                globalCtx->nextEntranceIndex = Entrance_OverrideNextIndex(0x0600); // Minuet
                break;
            case 1:
                globalCtx->nextEntranceIndex = Entrance_OverrideNextIndex(0x04F6); // Bolero
                break;
            case 2:
                globalCtx->nextEntranceIndex = Entrance_OverrideNextIndex(0x0604); // Serenade
                break;
            case 3:
                globalCtx->nextEntranceIndex = Entrance_OverrideNextIndex(0x01F1); // Requiem
                break;
            case 4:
                globalCtx->nextEntranceIndex = Entrance_OverrideNextIndex(0x0568); // Nocturne
                break;
            case 5:
                globalCtx->nextEntranceIndex = Entrance_OverrideNextIndex(0x05F4); // Prelude
                break;
            default:
                globalCtx->sceneLoadFlag = 0; // if something goes wrong, the animation plays normally
        }

        // If one of the warp songs happens to lead to a grotto return, then we
        // have to force the grotto return afterwards
        Grotto_ForceGrottoReturnOnSpecialEntrance();

        if (gSaveContext.gameMode != 0) {
            // During DHWW the cutscene must play at the destination
            gSaveContext.respawnFlag = -3;
        } else if (gSaveContext.respawnFlag == -3) {
            // Unset Zoneout Type -3 to avoid cutscene at destination (technically it's not needed)
            gSaveContext.respawnFlag = 0;
        }
    }

    // Door of Time, a non-numbered cutscene is playing (it can only be the Door opening cs)
    if (thisx->params == 0x000D && gSaveContext.cutsceneIndex == 0xFFFD) {
        // skip the Spiritual Stones part of the cutscene
        if (CsTimer < 800) {
            CsTimer = 800;
        }
        // Make cutscene end when the door is fully open
        else if (CsTimer > 1090 && CsTimer < 1180) {
            CsTimer = 1180;
        }
    }
}

u32 DoorOfTime_RequirementCheck() {
    return gGlobalContext->sceneNum != 0x43 || gSettingsContext.openDoorOfTime == OPENDOOROFTIME_CLOSED ||
           (((gSaveContext.questItems >> 18) & 0x7) == 0x7 && gSaveContext.items[SLOT_OCARINA] == ITEM_OCARINA_TIME);
}
