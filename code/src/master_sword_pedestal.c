#include "z3D/z3D.h"
#include "settings.h"

void TimeTravelAdvanceCutsceneTimer () {
    if (gGlobalContext->csCtx.frames < 310) {
        if (gSaveContext.linkAge == 1) {
            gGlobalContext->csCtx.frames = 340; // Child Link
        } else {
            gGlobalContext->csCtx.frames = 310; // Adult Link
        }
    }
}
