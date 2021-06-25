#include "icetrap.h"
#include "objects.h"
#include "z3D/z3D.h"
#include "settings.h"

static u8 pendingFreezes = 0;
static u8 cooldown = 0;
static u8 modifyScale = 0;

// LUT for 1 - 0.5sin(0.5x) * 1.1^-x where x = 30 - INDEX
const f32 SCALE_TRAP[] = {
    1.000f, 0.971f, 0.966f, 0.969f, 0.982f,
    1.003f, 1.027f, 1.049f, 1.061f, 1.059f,
    1.040f, 1.006f, 0.963f, 0.921f, 0.892f,
    0.888f, 0.914f, 0.969f, 1.045f, 1.124f,
    1.185f, 1.207f, 1.177f, 1.090f, 0.960f,
    0.814f, 0.690f, 0.625f, 0.652f, 0.782f
};

u32 IceTrap_IsPending(void) {
    return pendingFreezes > 0;
}

void IceTrap_Push(void) {
    pendingFreezes++;
}

void LinkDamageNoKnockback(void) {
    if (PLAYER->invincibilityTimer >= 0) {
        s32 changeHealth = Settings_ApplyDamageMultiplier(gGlobalContext, -(PLAYER->actor.colChkInfo.damage));
        gSaveContext.health += changeHealth / ((gSaveContext.doubleDefense)? 2 : 1);
    }
    if (gSaveContext.health < 0) {
        gSaveContext.health = 0;
    }
    PLAYER->actor.colChkInfo.damage = 0;
    LinkDamage(gGlobalContext, PLAYER, 0, 0.0f, 0.0f, 0, 20);
}

void IceTrap_Give(void) {
    if (cooldown == 0 && pendingFreezes &&
        ExtendedObject_IsLoaded(&gGlobalContext->objectCtx, ExtendedObject_GetIndex(&gGlobalContext->objectCtx, 0x3))) {
        u8 damageType = 3; // Default to ice trap
        if (gSettingsContext.randomTrapDmg == 1) { //Basic
            damageType = gRandInt % 5 + 1; // From testing 0-4 are all the unique damage types and 0 is boring (5 is custom)
        }
        else if (gSettingsContext.randomTrapDmg == 2) { //Advanced
            damageType = gRandInt % 6; // 0 will be used for the fire trap
        }
        modifyScale = (damageType == 5);

        pendingFreezes--;
        PLAYER->stateFlags1 &= ~0xC00;
        if (damageType == 3 || damageType == 0) {
            PLAYER->actor.colChkInfo.damage = 0;
        } else {
            PLAYER->actor.colChkInfo.damage = (gSettingsContext.mirrorWorld) ? 16 : 8; // Damage Multiplier is accounted for by the patch
        }

        if (PLAYER->invincibilityTimer > 0) {
            PLAYER->invincibilityTimer = 0;
        }

        if (damageType == 0) {
            FireDamage(&(PLAYER->actor), gGlobalContext, 0);
        }
        if (damageType == 5) {
            LinkDamageNoKnockback();
        } else {
            LinkDamage(gGlobalContext, PLAYER, damageType, 0.0f, 0.0f, 0, 20);
        }
        cooldown = 30;
    }
}

void IceTrap_Update(void) {
    // Make sure zelda_dangeon_keep is loaded
    if (ExtendedObject_GetIndex(&gGlobalContext->objectCtx, 0x3) < 0) {
        ExtendedObject_Spawn(&gGlobalContext->objectCtx, 0x3);
    }

    if (cooldown != 0) {
        cooldown--;

        if (modifyScale) {
            PLAYER->actor.scale.y = 0.01f * SCALE_TRAP[cooldown];
        }
    }
}
