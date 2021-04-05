#include "z3D/z3D.h"
#include "models.h"

// Certain doors can cause a crash depending on a freestanding
// model in the room that is being transitioned out of. We can
// avoid the crash by delete all the models as soon as these
// doors are opened
void Door_CheckToDeleteCustomModels(Actor* door) {
    s32 transitionActorId = (u16)door->params >> 0xA;

    if (((gGlobalContext->sceneNum == 0x000B) && (transitionActorId == 0xB)) ||
        ((gGlobalContext->sceneNum == 0x0007) && (transitionActorId == 0xA))) {
        Model_DestroyAll();
    }
}
