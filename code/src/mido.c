#include "z3D/z3D.h"
#include "3ds/types.h"
#include "settings.h"


//Done to fix vanilla weirdness where Mido despawns in forest after obtaining Zelda's letter
u32 EnMd_ShouldSpawn(void) {
    bool DekuTreeDead = (gSaveContext.eventChkInf[0] & 0x80); //"Obtained Kokiri Emerald & Deku Tree Dead"
    bool ObtainedLetter = (gSaveContext.eventChkInf[4] & 0x1); //"Obtained Zelda's Letter"
    bool ShowedSword = (gSaveContext.eventChkInf[0] & 0x10); //"Showed Mido Sword & Shield"
    //We want to make sure Mido stays outside until after showing him the sword
    //To work like how vanilla does, he's also allowed to stay outside until you either get the letter or Deku Tree is dead
    bool SpawnInForest = !(ShowedSword && (ObtainedLetter || DekuTreeDead));
    if (gGlobalContext->sceneNum == 0x55) { //Kokiri Forest, spawn if hasn't been showed sword and shield yet
        if (SpawnInForest) {
            return 1;
        }
    }

    if (gGlobalContext->sceneNum == 0x28) { //Mido's house, spawn if not spawning in forest
        if (!SpawnInForest && gSaveContext.linkAge == AGE_CHILD) {
            return 1;
        }
    }

    if (gGlobalContext->sceneNum == 0x5B) { //Lost woods, spawn always
        return 1;
    }

    return 0;
}

//Fixes an issue where Mido prioritizes telling you about the Deku tree's death over showing him sword and shield
u16 EnMd_GetTextKokiriForest() {

    if (gSaveContext.eventChkInf[0] & 0x10) {
        return 0x1034;
    }
    //   Has kokiri sword                         Has deku shield
    if ((gSaveContext.equips.equipment & 0x1) && (gSaveContext.equips.equipment & 0x10)) {
        return 0x1033; //Text to tell you you're cool for having a sword
    }

    if (gSaveContext.infTable[0] & 0x1000) {
        return 0x1030;
    }

    return 0x102F;
}
