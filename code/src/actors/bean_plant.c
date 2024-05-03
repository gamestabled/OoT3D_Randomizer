#include "bean_plant.h"
#include "multiplayer.h"

#define ObjBean_Init ((ActorFunc)GAME_ADDR(0x1E12B0))

#define ObjBean_Update ((ActorFunc)GAME_ADDR(0x214BEC))

#define ObjBean_UnplantedWait (void*)GAME_ADDR(0x15E154)
#define ObjBean_StallGrowth (void*)GAME_ADDR(0x143684)
#define ObjBean_GrowSprout (void*)GAME_ADDR(0x1436C4)

PosRot lastBeanPlant_Home;
s16 lastBeanPlant_Params;

void ObjBean_rInit(ObjBean* thisx, GlobalContext* globalCtx) {
    lastBeanPlant_Home   = thisx->base.home;
    lastBeanPlant_Params = thisx->base.params;
    ObjBean_Init((Actor*)thisx, globalCtx);
}

void ObjBean_rUpdate(ObjBean* thisx, GlobalContext* globalCtx) {
    void* prev_action_fn = thisx->action_fn;

    ObjBean_Update((Actor*)thisx, globalCtx);

    if (prev_action_fn == ObjBean_UnplantedWait && thisx->action_fn == ObjBean_StallGrowth) {
        Multiplayer_Send_ActorUpdate((Actor*)thisx, NULL, 0);
    }
}

void ObjBean_StartGrowth(ObjBean* thisx) {
    if (thisx->action_fn != ObjBean_UnplantedWait) {
        return;
    }
    thisx->action_fn    = ObjBean_GrowSprout;
    thisx->unk_bitfield = ((thisx->unk_bitfield & 0xF0) | 3);
    thisx->base.scale.x = 0.01;
    thisx->base.scale.y = 0.01;
    thisx->base.scale.z = 0.01;
}
