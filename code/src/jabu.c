#include "z3D/z3D.h"
#include "entrance.h"

void Jabu_SkipOpeningCutscene(void) {
    gGlobalContext->nextEntranceIndex = Entrance_OverrideNextIndex(0x0028);
    gGlobalContext->sceneLoadFlag = 0x14;
    gGlobalContext->fadeOutTransition = 2;
}

// Used to make the small crate appear after Ruto gets the sapphire
// By default it would appear only after beating the dungeon
s32 ObjKibako_CheckRuto(void) {
    return gSaveContext.infTable[0x14] & 0x20;
}
