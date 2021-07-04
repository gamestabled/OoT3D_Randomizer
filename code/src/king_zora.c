#include "z3D/z3D.h"
#include "settings.h"
#include "king_zora.h"

#define EnKz_Update_addr 0x1B66F8
#define EnKz_Update ((ActorFunc)EnKz_Update_addr)

u32 EnKz_CheckMovedFlag(void) {
    if ((gSaveContext.eventChkInf[3] & 0x8) ||
        ((gSaveContext.linkAge == AGE_ADULT) && (gSettingsContext.zorasFountain == ZORASFOUNTAIN_ADULT))) {
        return 1;
    } else {
        return 0;
    }
}

u8 And(u32 seed, u8 start, u8 end) {
    u8 value = 1;

    for (u8 i = start; i < end && value; i++) {
        value &= seed >> i;
    }

    return value;
}

u8 Bias(u32 seed) {
    u8 value = (seed & 0x00000007);
    value |= And(seed,  3,  5) << 3;
    value |= And(seed,  5,  7) << 4;
    value |= And(seed,  7, 11) << 5;
    value |= And(seed, 11, 16) << 6;
    return value;
}

void EnKz_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnKz_Update(thisx, globalCtx);
    // Zora's Domain scene, the position check is just to add a 1 frame delay
    if (gSettingsContext.kingZoraSpeed != 1 && globalCtx->sceneNum == 88 && thisx->speedXZ != 0 && thisx->world.pos.x < 628.0f) {
        u8 mweepCount = (gSettingsContext.kingZoraSpeed)? Bias(Hash(0)) + 1 : 1;
        thisx->speedXZ = 6.4f / (2.56f * (mweepCount - 0.58f));
        thisx->world.pos.z = -1783.0f; // lock Z position so the increased speed doesn't mess it up
    }
}
