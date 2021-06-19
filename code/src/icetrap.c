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
        if (gSettingsContext.randomTrapDmg == ON) {
            damageType = gRandInt % 4 + 1; // From testing 0-4 are all the unique damage types and 0 is boring
        }

        pendingFreezes--;
        PLAYER->stateFlags1 &= ~0xC00;
        PLAYER->actor.colChkInfo.damage = 0;
        // Applying damage normally sometimes wouldn't work when multiple traps were queued due to i-frames so manually setting health
        if (damageType != 3 && gSaveContext.nayrusLoveTimer == 0) {
            u8 damageValue = 8;
            if (gSaveContext.doubleDefense) {
                damageValue /= 2;
            }
            if (gSaveContext.masterQuestFlag) {
                damageValue *= 2;
            }

            gSaveContext.health += Settings_ApplyDamageMultiplier(gGlobalContext, -damageValue);

            if (gSaveContext.health < 0) {
                gSaveContext.health = 0;
            }
        }

        // LinkInvincibility(player, 0x14); //TODO
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
