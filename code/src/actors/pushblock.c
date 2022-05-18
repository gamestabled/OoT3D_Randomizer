#include "pushblock.h"
#include "multiplayer.h"

#define ObjOshihiki_Update_addr 0x286520
#define ObjOshihiki_Update ((ActorFunc)ObjOshihiki_Update_addr)

void ObjOshihiki_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    Vec3f prevPos = thisx->world.pos;

    ObjOshihiki_Update(thisx, globalCtx);

    if ((s32)thisx->world.pos.x != (s32)prevPos.x ||
        (s32)thisx->world.pos.y != (s32)prevPos.y ||
        (s32)thisx->world.pos.z != (s32)prevPos.z) {
        Multiplayer_Send_ActorUpdate(thisx, &thisx->world.pos, sizeof(Vec3f));
    }
}

#define BgSpot15Rrbox_Update_addr 0x2AD484
#define BgSpot15Rrbox_Update ((ActorFunc)BgSpot15Rrbox_Update_addr)

void BgSpot15Rrbox_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    Vec3f prevPos = thisx->world.pos;

    BgSpot15Rrbox_Update(thisx, globalCtx);

    if ((s32)thisx->world.pos.x != (s32)prevPos.x ||
        (s32)thisx->world.pos.y != (s32)prevPos.y ||
        (s32)thisx->world.pos.z != (s32)prevPos.z) {
        BgSpot15Rrbox_SendData sendData = { thisx->focus.pos, thisx->world.pos };
        Multiplayer_Send_ActorUpdate(thisx, &sendData, sizeof(BgSpot15Rrbox_SendData));
    }
}
