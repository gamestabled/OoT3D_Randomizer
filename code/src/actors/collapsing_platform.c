#include "collapsing_platform.h"
#include "multiplayer.h"

#define ObjLift_Update ((ActorFunc)GAME_ADDR(0x2159DC))

#define ObjLift_Wait (void*)GAME_ADDR(0x3C05B0)
#define ObjLift_Shake (void*)GAME_ADDR(0x110E98)
#define ObjLift_Fall (void*)GAME_ADDR(0x3BB7BC)

void ObjLift_rUpdate(ObjLift* thisx, GlobalContext* globalCtx) {
    void* prev_action_fn = thisx->action_fn;

    ObjLift_Update((Actor*)thisx, globalCtx);

    if (prev_action_fn != thisx->action_fn && prev_action_fn == ObjLift_Wait) {
        Multiplayer_Send_ActorUpdate((Actor*)thisx, &thisx->action_fn, sizeof(void*));
    }
}

void ObjLift_SetActionFn(ObjLift* thisx, void* new_action_fn) {
    if (thisx->action_fn != ObjLift_Wait) {
        return;
    }
    if (new_action_fn == ObjLift_Shake) {
        thisx->timer = 30;
    } else if (new_action_fn == ObjLift_Fall) {
        thisx->base.world.pos = thisx->base.home.pos;
        thisx->base.world.rot = thisx->base.home.rot;
        thisx->base.shape.rot = thisx->base.world.rot;
    }
    thisx->action_fn = new_action_fn;
}
