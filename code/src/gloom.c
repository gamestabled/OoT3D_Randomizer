#include "z3D/z3D.h"
#include "settings.h"
#include "savefile.h"

void Gloom_Update(void) {
    if (gSettingsContext.gloomMode == GLOOMMODE_EMPTY) {
        // Round current health up to the next full heart count.
        s16 maxAllowedHealth = ((gSaveContext.health + 0xF) / 0x10) * 0x10;
        if (gSaveContext.healthCapacity > maxAllowedHealth) {
            gSaveContext.healthCapacity = maxAllowedHealth;
        }
    }
}

void Gloom_OnDeath(void) {
    if (gSettingsContext.gloomMode != GLOOMMODE_DEATH) {
        return;
    }

    gSaveContext.healthCapacity -= 0x10;

    if (gSaveContext.healthCapacity <= 0) {
        gSaveContext.healthCapacity = 0;
    }
}

void Gloom_OnHit(void) {
    if (gSettingsContext.gloomMode != GLOOMMODE_DAMAGE && gSettingsContext.gloomMode != GLOOMMODE_COLLISION) {
        return;
    }

    if (gSaveContext.doubleDefense && !gExtSaveData.gloomedHeart) {
        gExtSaveData.gloomedHeart = TRUE;
    } else {
        gSaveContext.healthCapacity -= 0x10;
        gExtSaveData.gloomedHeart = FALSE;
    }

    if (gSaveContext.healthCapacity <= 0) {
        gSaveContext.healthCapacity = 0;
        gSaveContext.health         = 0;
    }
}

s32 Gloom_ShouldDrawHeartBorder(s32 heartIconIdx) {
    u8 isCurrentHeart = heartIconIdx == (gSaveContext.healthCapacity / 0x10) - 1;
    return gSaveContext.doubleDefense && (!isCurrentHeart || !gExtSaveData.gloomedHeart);
}
