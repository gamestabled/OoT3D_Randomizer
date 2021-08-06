#include "z3D/z3D.h"
#include "models.h"

// Certain doors can cause a crash depending on a freestanding
// model in the room that is being transitioned out of. We can
// avoid the crash by delete all the models as soon as link
// opens a door. However, some scenes have doors near freestanding
// items which don't cause a room transition, so we have to avoid
// those
void Door_CheckToDeleteCustomModels(Actor* door) {
    if ((gGlobalContext->sceneNum != 0x000C) && // Thieve's Hideout
            (gGlobalContext->sceneNum != 0x0001)) { // Dodongo's Cavern
        Model_DestroyAll();
    }
}
