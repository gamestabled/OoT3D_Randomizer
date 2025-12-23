#include "z3D/z3D.h"
#include "item_override.h"
#include "settings.h"
#include "savefile.h"

u8 ShouldSkipMasterSwordCutscene() {
    return gExtSaveData.hasTimeTraveled || gSettingsContext.openDoorOfTime == OPENDOOROFTIME_OPEN;
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
    gExtSaveData.hasTimeTraveled = 1;
}

void Pedestal_PickUpMasterSword(void) {
    // Push pedestal item
    if (gSettingsContext.shuffleMasterSword && !(gExtSaveData.extInf.masterSwordFlags & 2)) {
        ItemOverride_PushDelayedOverride(0x00);
    }

    if (!SaveFile_SwordlessPatchesEnabled()) {
        // Add master sword to inventory
        gSaveContext.equipment |= 0x2;
    }

    // Mark pedestal item collected
    gExtSaveData.extInf.masterSwordFlags |= 2;
}
