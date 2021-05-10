#include "z3D/z3D.h"
#include "settings.h"

s32 Scarecrow_CheckToBeActivated(void) {
    if (gSettingsContext.freeScarecrow == ON) {
        return (PLAYER->stateFlags2 & 0x08000000) != 0; //Check if Link is holding ocarina
    } else {
        return gGlobalContext->unk_2B7E == 11; //Check if scarecrow's song was just played
    }
}
