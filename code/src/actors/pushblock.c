#include "pushblock.h"
#include "multiplayer.h"

void ObjOshihiki_Update(Actor* thisx, GlobalContext* globalCtx);

void ObjOshihiki_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    Vec3f prevPos = thisx->world.pos;

    ObjOshihiki_Update(thisx, globalCtx);

    if ((s32)thisx->world.pos.x != (s32)prevPos.x || (s32)thisx->world.pos.y != (s32)prevPos.y ||
        (s32)thisx->world.pos.z != (s32)prevPos.z) {
        Multiplayer_Send_ActorUpdate(thisx, &thisx->world.pos, sizeof(Vec3f));
    }
}

void BgSpot15Rrbox_Update(Actor* thisx, GlobalContext* globalCtx);

void BgSpot15Rrbox_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    Vec3f prevPos = thisx->world.pos;

    BgSpot15Rrbox_Update(thisx, globalCtx);

    if ((s32)thisx->world.pos.x != (s32)prevPos.x || (s32)thisx->world.pos.y != (s32)prevPos.y ||
        (s32)thisx->world.pos.z != (s32)prevPos.z) {
        BgSpot15Rrbox_SendData sendData = { thisx->focus.pos, thisx->world.pos };
        Multiplayer_Send_ActorUpdate(thisx, &sendData, sizeof(BgSpot15Rrbox_SendData));
    }
}
