#include "z3D/z3D.h"
#include "settings.h"
#include "savefile.h"

u8 Permadeath_GetOption(void) {
    // For safety, verify that the seed and save file was created with permadeath enabled
    // If Gloom is enabled and set to Death mode, only apply Permadeath when all hearts are gone.
    return gSettingsContext.permadeath && gExtSaveData.permadeath &&
           (gSettingsContext.gloomMode != GLOOMMODE_DEATH || gSaveContext.healthCapacity == 0);
}

typedef void (*SaveFile_Delete_proc)(u8 fileNum);
#define SaveFile_Delete ((SaveFile_Delete_proc)GAME_ADDR(0x446FC4))

void Permadeath_DeleteSave(void) {
    if (!Permadeath_GetOption()) {
        return;
    }
    SaveFile_Delete(gSaveContext.fileNum);
}
