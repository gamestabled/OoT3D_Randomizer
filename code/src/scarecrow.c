#include "z3D/z3D.h"
#include "settings.h"

s32 Scarecrow_CheckToBeActivated(void) {
    // if (gSettingsContext.scarecrow == SCARECROW_FREE) {
    //     return (PLAYER->stateFlags2 & 0x08000000) != 0;
    // } else {
    //     return gGlobalContext->unk_2B7E == 11;
    // }
    return (PLAYER->stateFlags2 & 0x08000000) != 0;
}
