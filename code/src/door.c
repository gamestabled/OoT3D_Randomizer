#include "z3D/z3D.h"
#include "models.h"
#include "settings.h"

#define DoorShutter_Init_addr 0x2453E0
#define DoorShutter_Init ((ActorFunc)DoorShutter_Init_addr)

void DoorShutter_rInit(Actor* thisx, GlobalContext* globalCtx) {
    // In Treasure Chest Shop when its chests are shuffled,
    // make doors use permanent flags instead of temp ones
    if(globalCtx->sceneNum == 16 && gSettingsContext.shuffleChestMinigame) {
        thisx->params &= ~0x0020;
    }
    DoorShutter_Init(thisx, globalCtx);
}

// Certain doors can cause a crash depending on a freestanding
// model in the room that is being transitioned out of. We can
// avoid the crash by deleting all the models as soon as Link
// opens a door. However, some scenes have doors near freestanding
// items which don't cause a room transition, so we have to avoid
// those
void Door_CheckToDeleteCustomModels(Actor* door) {
    if ((gGlobalContext->sceneNum != 0x000C) && // Thieves' Hideout
        (gGlobalContext->sceneNum != 0x0001)) { // Dodongo's Cavern
        Model_DestroyAll();
    }
}
