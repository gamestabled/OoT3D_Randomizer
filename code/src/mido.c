#include "z3D/z3D.h"
#include "3ds/types.h"
#include "settings.h"


//Fixes it so that Mido only spawns in Kokiri forest while he's useful (i.e. until you show him sword and shield)
//Done to fix vanilla weirdness where Mido despawns in forest after obtaining Zelda's letter
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

//Fixes an issue where Mido prioritizes Mido telling you about the Deku tree's death over showing him sword and shield
u16 EnMd_GetTextKokiriForest() {

    if (gSaveContext.eventChkInf[0] & 0x10) {
        return 0x1034;
    }
       //Has kokiri sword                         Has deku shield
    if ((gSaveContext.equips.equipment & 0x1) && (gSaveContext.equips.equipment & 0x10)) { //Text to tell you you're cool for having a sword
        return 0x1033;
    }

    if (gSaveContext.infTable[0] & 0x1000) {
        return 0x1030;
    }

    return 0x102F;
}
