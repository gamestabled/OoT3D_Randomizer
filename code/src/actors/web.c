#include "web.h"
#include "multiplayer.h"

void BgYdanSp_Update(Actor* thisx, GlobalContext* globalCtx);

void BgYdanSp_FloorWebIdle(BgYdanSp* this, GlobalContext* globalCtx);
void BgYdanSp_WallWebIdle(BgYdanSp* this, GlobalContext* globalCtx);
void BgYdanSp_BurnFloorWeb(BgYdanSp* this, GlobalContext* globalCtx);
void BgYdanSp_BurnWallWeb(BgYdanSp* this, GlobalContext* globalCtx);
void BgYdanSp_FloorWebBreaking(BgYdanSp* this, GlobalContext* globalCtx);

void BgYdanSp_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    BgYdanSp* this = (BgYdanSp*)thisx;

    BgYdanSpActionFunc prev_action_fn = this->action_fn;
    // home.pos gets changed when the action_fn updates, so the previous has to be used.
    Vec3f prevHomePos = this->base.home.pos;

    BgYdanSp_Update(thisx, globalCtx);

    if (prev_action_fn != this->action_fn &&
        (prev_action_fn == BgYdanSp_FloorWebIdle || prev_action_fn == BgYdanSp_WallWebIdle)) {
        BgYdanSp_SendData sendData = { prevHomePos, this->action_fn };
        Multiplayer_Send_ActorUpdate(thisx, &sendData, sizeof(BgYdanSp_SendData));
    }
}

void BgYdanSp_SetActionFn(BgYdanSp* this, BgYdanSpActionFunc new_action_fn) {
    if (this->action_fn != BgYdanSp_FloorWebIdle && this->action_fn != BgYdanSp_WallWebIdle) {
        return;
    }
    if (new_action_fn == BgYdanSp_BurnFloorWeb || new_action_fn == BgYdanSp_BurnWallWeb) {
        this->timer = 45;
    } else if (new_action_fn == BgYdanSp_FloorWebBreaking) {
        this->some_float = 200.0;
        this->base.room  = 0xFF;
        this->base.flags |= 0x10;
        this->timer = 60;
    }
    this->action_fn = new_action_fn;
}
