#include "bean_plant.h"
#include "multiplayer.h"

void ObjBean_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjBean_Update(Actor* thisx, GlobalContext* globalCtx);

void ObjBean_UnplantedWait(ObjBean* this, GlobalContext* globalCtx);
void ObjBean_StallGrowth(ObjBean* this, GlobalContext* globalCtx);
void ObjBean_GrowSprout(ObjBean* this, GlobalContext* globalCtx);

PosRot lastBeanPlant_Home;
s16 lastBeanPlant_Params;

void ObjBean_rInit(Actor* thisx, GlobalContext* globalCtx) {
    lastBeanPlant_Home   = thisx->home;
    lastBeanPlant_Params = thisx->params;
    ObjBean_Init(thisx, globalCtx);
}

void ObjBean_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    ObjBean* this = (ObjBean*)thisx;

    ObjBeanActionFunc prev_action_fn = this->action_fn;

    ObjBean_Update(thisx, globalCtx);

    if (prev_action_fn == ObjBean_UnplantedWait && this->action_fn == ObjBean_StallGrowth) {
        Multiplayer_Send_ActorUpdate(thisx, NULL, 0);
    }
}

void ObjBean_StartGrowth(ObjBean* this) {
    if (this->action_fn != ObjBean_UnplantedWait) {
        return;
    }
    this->action_fn    = ObjBean_GrowSprout;
    this->unk_bitfield = ((this->unk_bitfield & 0xF0) | 3);
    this->base.scale.x = 0.01;
    this->base.scale.y = 0.01;
    this->base.scale.z = 0.01;
}
