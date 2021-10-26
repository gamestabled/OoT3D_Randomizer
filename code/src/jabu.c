#include "z3D/z3D.h"

void Jabu_SkipOpeningCutscene(void) {
    gGlobalContext->nextEntranceIndex = 0x0028;
    gGlobalContext->sceneLoadFlag = 0x14;
    gGlobalContext->fadeOutTransition = 2;
}
