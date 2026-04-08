#include "z3D/z3D.h"
#include "settings.h"
#include "savefile.h"

u8 Permadeath_GetOption(void) {
    // For safety, verify that the seed and save file was created with permadeath enabled
    // If Gloom is enabled and set to Death mode, only apply Permadeath when all hearts are gone.
    return gSettingsContext.permadeath && gExtSaveData.permadeath &&
           (gSettingsContext.gloomMode != GLOOMMODE_DEATH || gSaveContext.healthCapacity == 0);
}

void SaveFile_Delete(u8 fileNum);

void Permadeath_DeleteSave(void) {
    if (!Permadeath_GetOption()) {
        return;
    }
    SaveFile_Delete(gSaveContext.fileNum);
}
