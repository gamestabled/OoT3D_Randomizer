#include "z3D/z3D.h"
#include "settings.h"
#include "savefile.h"

u8 Permadeath_GetOption(void) {
    // For safety, verify that the seed and save file was created with permadeath enabled
    return gSettingsContext.permadeath && gExtSaveData.permadeath;
}

typedef void (*SaveFile_Delete_proc)(u8 fileNum);
#ifdef Version_EUR
    #define SaveFile_Delete_addr 0x446FE4
#else
    #define SaveFile_Delete_addr 0x446FC4
#endif
#define SaveFile_Delete ((SaveFile_Delete_proc)SaveFile_Delete_addr)

void Permadeath_DeleteSave(void) {
    if (!Permadeath_GetOption()) {
        return;
    }
    SaveFile_Delete(gSaveContext.fileNum);
}
