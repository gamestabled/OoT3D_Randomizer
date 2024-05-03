#include "web.h"
#include "multiplayer.h"

#define BgYdanSp_Update ((ActorFunc)GAME_ADDR(0x241EF8))

#define BgYdanSp_FloorWebIdle (void*)GAME_ADDR(0x19A8EC)
#define BgYdanSp_WallWebIdle (void*)GAME_ADDR(0x181C88)
#define BgYdanSp_BurnFloorWeb (void*)GAME_ADDR(0x19A52C)
#define BgYdanSp_BurnWallWeb (void*)GAME_ADDR(0x181878)
#define BgYdanSp_FloorWebBreaking (void*)GAME_ADDR(0x1E8438)

void BgYdanSp_rUpdate(BgYdanSp* thisx, GlobalContext* globalCtx) {
    void* prev_action_fn = thisx->action_fn;
    // home.pos gets changed when the action_fn updates, so the previous has to be used.
    Vec3f prevHomePos = thisx->base.home.pos;

    BgYdanSp_Update((Actor*)thisx, globalCtx);

    if (prev_action_fn != thisx->action_fn &&
        (prev_action_fn == BgYdanSp_FloorWebIdle || prev_action_fn == BgYdanSp_WallWebIdle)) {
        BgYdanSp_SendData sendData = { prevHomePos, thisx->action_fn };
        Multiplayer_Send_ActorUpdate((Actor*)thisx, &sendData, sizeof(BgYdanSp_SendData));
    }
}

void BgYdanSp_SetActionFn(BgYdanSp* thisx, void* new_action_fn) {
    if (thisx->action_fn != BgYdanSp_FloorWebIdle && thisx->action_fn != BgYdanSp_WallWebIdle) {
        return;
    }
    if (new_action_fn == BgYdanSp_BurnFloorWeb || new_action_fn == BgYdanSp_BurnWallWeb) {
        thisx->timer = 45;
    } else if (new_action_fn == BgYdanSp_FloorWebBreaking) {
        thisx->some_float = 200.0;
        thisx->base.room  = 0xFF;
        thisx->base.flags |= 0x10;
        thisx->timer = 60;
    }
    thisx->action_fn = new_action_fn;
}
