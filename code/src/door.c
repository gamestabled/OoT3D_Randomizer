#include "z3D/z3D.h"
#include "models.h"

// Certain doors can cause a crash depending on a freestanding
// model in the room that is being transitioned out of. We can
// avoid the crash by delete all the models as soon as these
// doors are opened
void Door_CheckToDeleteCustomModels(Actor* door) {
    s32 transitionActorId = (u16)door->params >> 0xA;

    if ((gGlobalContext->sceneNum == 0x000B) || //GTG (it's safe to do all doors in here, though we just need to cover the lava room)
        ((gGlobalContext->sceneNum == 0x0007) && (transitionActorId == 0xA)) || //Shadow Temple one huge pot room -> invisible spikes room
        ((gGlobalContext->sceneNum == 0x0008) && (transitionActorId == 0x5))) { //BOTW coffin room -> main room
        Model_DestroyAll();
    }
}
