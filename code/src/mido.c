#include "z3D/z3D.h"
#include "3ds/types.h"
#include "settings.h"


u32 EnMd_ShouldSpawn(void) {
    bool DekuTreeDead = (gSaveContext.eventChkInf[0] & 0x80); //"Obtained Kokiri Emerald & Deku Tree Dead"
    bool ObtainedLetter = (gSaveContext.eventChkInf[4] & 0x1); //"Obtained Zelda's Letter"
    bool ShowedSword = (gSaveContext.eventChkInf[0] & 0x10); //"Showed Mido Sword & Shield"
    bool SpokeAfterDeath = (gSaveContext.eventChkInf[1] & 0x1000); //"Spoke to Mido After Deku Tree's Death"
    bool DontSpawnForest = ShowedSword && (DekuTreeDead || ObtainedLetter);
    if (gGlobalContext->sceneNum == 0x55) { //Kokiri Forest, spawn if conditions to disappear not met
        if (!DontSpawnForest) {
            return 1;
        }
    }

    if (gGlobalContext->sceneNum == 0x28) { //Mido's house, spawn if conditiosn to disappear are met and child
        if (DontSpawnForest && gSaveContext.linkAge == AGE_CHILD) {
            return 1;
        }
    }

    if (gGlobalContext->sceneNum == 0x5B) { //Lost woods, always spawn
        return 1;
    }

    return 0;
}
