#include "z3D/z3D.h"
#include "3ds/types.h"
#include "settings.h"


u32 EnMd_ShouldSpawn(void) {
    bool ShowedSword = (gSaveContext.eventChkInf[0] & 0x10); //"Showed Mido Sword & Shield"
    if (gGlobalContext->sceneNum == 0x55) { //Kokiri Forest, spawn if hasn't been showed sword and shield yet
        if (!ShowedSword) {
            return 1;
        }
    }

    if (gGlobalContext->sceneNum == 0x28) { //Mido's house, spawn if not spawning in forest
        if (ShowedSword && gSaveContext.linkAge == AGE_CHILD) {
            return 1;
        }
    }

    if (gGlobalContext->sceneNum == 0x5B) { //Lost woods, always spawn
        return 1;
    }

    return 0;
}
