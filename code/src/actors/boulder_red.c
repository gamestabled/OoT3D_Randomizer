#include "boulder_red.h"
#include "multiplayer.h"

#define ObjHamishi_Update ((ActorFunc)GAME_ADDR(0x26FD24))

void ObjHamishi_rUpdate(ObjHamishi* thisx, GlobalContext* globalCtx) {
    s16 prevHitCount = thisx->hit_count;

    ObjHamishi_Update((Actor*)thisx, globalCtx);

    if (thisx->hit_count != prevHitCount) {
        Multiplayer_Send_ActorUpdate((Actor*)thisx, NULL, 0);
    }
}

void ObjHamishi_Hit(ObjHamishi* thisx) {
    thisx->hit_count++;
    if (thisx->hit_count < 2) {
        thisx->shake_frames        = 15;
        thisx->shake_position_size = 2.0;
        thisx->shake_rotation_size = 400.0;
    }
}

s16 ObjHamishi_HitCount(ObjHamishi* thisx) {
    return thisx->hit_count;
}
