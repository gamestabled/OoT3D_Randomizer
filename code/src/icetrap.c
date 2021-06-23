#include "icetrap.h"
#include "objects.h"
#include "z3D/z3D.h"
#include "settings.h"

static u8 pendingFreezes = 0;
static u8 cooldown = 0;

u32 IceTrap_IsPending(void) {
    return pendingFreezes > 0;
}

void IceTrap_Push(void) {
    pendingFreezes++;
}

void IceTrap_Give(void) {
    if (cooldown == 0 && pendingFreezes && ExtendedObject_IsLoaded(&gGlobalContext->objectCtx, ExtendedObject_GetIndex(&gGlobalContext->objectCtx, 0x3))) {
        u8 damageType = 3; // Default to ice trap
        if (gSettingsContext.randomTrapDmg == 1) { //Basic
            damageType = gRandInt % 4 + 1; // From testing 0-4 are all the unique damage types and 0 is boring
        }
        else if (gSettingsContext.randomTrapDmg == 2) { //Advanced
            damageType = gRandInt % 5; // 0 will be used for the fire trap
        }

        pendingFreezes--;
        PLAYER->stateFlags1 &= ~0xC00;
        if (damageType == 3 || damageType == 0) {
            PLAYER->actor.colChkInfo.damage = 0;
        }
        else{
            PLAYER->actor.colChkInfo.damage = (gSettingsContext.mirrorWorld)? 16 : 8; // Damage Multiplier is accounted for by the patch
        }

        if (PLAYER->invincibilityTimer > 0) {
            PLAYER->invincibilityTimer = 0;
        }

        if (damageType == 0) {
            FireDamage(&(PLAYER->actor), gGlobalContext, 0);
        }
        LinkDamage(gGlobalContext, PLAYER, damageType, 0.0f, 0.0f, 0, 20); //TODO
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
    }
}
