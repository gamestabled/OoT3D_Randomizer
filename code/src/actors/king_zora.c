#include "z3D/z3D.h"
#include "settings.h"
#include "king_zora.h"
#include "common.h"

#define EnKz_Update ((ActorFunc)GAME_ADDR(0x1B66F8))

u32 EnKz_CheckMovedFlag(void) {
    if ((gSaveContext.eventChkInf[3] & 0x8) ||
        ((gSaveContext.linkAge == AGE_ADULT) && (gSettingsContext.zorasFountain == ZORASFOUNTAIN_ADULT))) {
        return 1;
    } else {
        return 0;
    }
}

void EnKz_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnKz_Update(thisx, globalCtx);
    // Zora's Domain scene, the position check is just to add a 1 frame delay
    if (gSettingsContext.kingZoraSpeed != KINGZORASPEED_VANILLA && globalCtx->sceneNum == 88 && thisx->speedXZ != 0 &&
        thisx->world.pos.x < 628.0f) {
        u8 mweepCount = (gSettingsContext.kingZoraSpeed) ? Bias(Hash(0)) + 1 : 1;
        if (gSettingsContext.kingZoraSpeed == KINGZORASPEED_CUSTOM) {
            mweepCount = gSettingsContext.exactZoraSpeed + 1;
        }
        thisx->speedXZ     = 6.4f / (2.56f * (mweepCount - 0.58f));
        thisx->world.pos.z = -1783.0f; // lock Z position so the increased speed doesn't mess it up
    }
}

void EnKz_SetTradedPrescriptionFlag(void) {
    gSaveContext.itemGetInf[3] |= 0x10;
}
