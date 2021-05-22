#include "z3D/z3D.h"
#include "settings.h"
#include "king_zora.h"

#define EnKz_Update_addr 0x1B66F8
#define EnKz_Update ((ActorFunc)EnKz_Update_addr)

u32 EnKz_CheckMovedFlag(void) {
    if ((gSaveContext.eventChkInf[3] & 0x8) || ((gSaveContext.linkAge == AGE_ADULT) && (gSettingsContext.zorasFountain == ZORASFOUNTAIN_ADULT))) {
        return 1;
    } else {
        return 0;
    }
}

void EnKz_rUpdate(Actor* thisx, GlobalContext* globalCtx){
    EnKz_Update(thisx, globalCtx);
    // Zora's Domain scene, the position check is just to add a 1 frame delay
    if(globalCtx->sceneNum == 88 && thisx->speedXZ != 0 && thisx->world.pos.x < 628.0f){
        thisx->speedXZ = 6.4f; //at this speed it takes him one mweep to move out of the way
        thisx->world.pos.z = -1783.0f; //lock Z position so the increased speed doesn't mess it up
    }
}
