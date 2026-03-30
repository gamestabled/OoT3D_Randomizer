#include "collapsing_platform.h"
#include "multiplayer.h"

void ObjLift_Update(Actor* thisx, GlobalContext* globalCtx);

void ObjLift_Wait(ObjLift* this, GlobalContext* globalCtx);
void ObjLift_Shake(ObjLift* this, GlobalContext* globalCtx);
void ObjLift_Fall(ObjLift* this, GlobalContext* globalCtx);

void ObjLift_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    ObjLift* this = (ObjLift*)thisx;

    ObjLiftActionFunc prev_action_fn = this->action_fn;

    ObjLift_Update(thisx, globalCtx);

    if (prev_action_fn != this->action_fn && prev_action_fn == ObjLift_Wait) {
        Multiplayer_Send_ActorUpdate(thisx, &this->action_fn, sizeof(void*));
    }
}

void ObjLift_SetActionFn(ObjLift* this, ObjLiftActionFunc new_action_fn) {
    if (this->action_fn != ObjLift_Wait) {
        return;
    }
    if (new_action_fn == ObjLift_Shake) {
        this->timer = 30;
    } else if (new_action_fn == ObjLift_Fall) {
        this->base.world.pos = this->base.home.pos;
        this->base.world.rot = this->base.home.rot;
        this->base.shape.rot = this->base.world.rot;
    }
    this->action_fn = new_action_fn;
}
