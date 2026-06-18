#include "boulder_red.h"
#include "multiplayer.h"

void ObjHamishi_Update(Actor* thisx, GlobalContext* globalCtx);

void ObjHamishi_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    ObjHamishi* this = (ObjHamishi*)thisx;

    s16 prevHitCount = this->hit_count;

    ObjHamishi_Update(thisx, globalCtx);

    if (this->hit_count != prevHitCount) {
        Multiplayer_Send_ActorUpdate(thisx, NULL, 0);
    }
}

void ObjHamishi_Hit(ObjHamishi* this) {
    this->hit_count++;
    if (this->hit_count < 2) {
        this->shake_frames        = 15;
        this->shake_position_size = 2.0;
        this->shake_rotation_size = 400.0;
    }
}

s16 ObjHamishi_HitCount(ObjHamishi* this) {
    return this->hit_count;
}
