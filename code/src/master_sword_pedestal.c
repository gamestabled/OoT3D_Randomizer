#include "z3D/z3D.h"
#include "settings.h"
#include "savefile.h"

u8 ShouldSkipMasterSwordCutscene() {
    return gExtSaveData.hasTraveledTimeOnce || gSettingsContext.openDoorOfTime == OPENDOOROFTIME_OPEN;
}

void TimeTravelAdvanceCutsceneTimer() {
    if (gGlobalContext->csCtx.frames < 310 && ShouldSkipMasterSwordCutscene()) {
        if (gSaveContext.linkAge == 1) {
            gGlobalContext->csCtx.frames = 340; // Child Link
        } else {
            gGlobalContext->csCtx.frames = 310; // Adult Link
        }
    }
}

void SetTimeTraveled() {
    gExtSaveData.hasTraveledTimeOnce = 1;
}
