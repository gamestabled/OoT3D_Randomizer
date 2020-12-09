#include "icetrap.h"
#include "objects.h"
#include "z3D/z3D.h"

static u8 pendingFreezes = 0;

u32 IceTrap_IsPending(void) {
    return pendingFreezes > 0;
}

void IceTrap_Push(void) {
    pendingFreezes++;
}

void IceTrap_Give(void) {    
    if (pendingFreezes && ExtendedObject_IsLoaded(&gGlobalContext->objectCtx, ExtendedObject_GetIndex(&gGlobalContext->objectCtx, 0x3))) {
        pendingFreezes--;
        PLAYER->stateFlags1 &= ~0xC00;
        PLAYER->actor.colChkInfo.damage = 0;

        // LinkInvincibility(player, 0x14); //TODO
        LinkDamage(gGlobalContext, PLAYER, 3, 0.0f, 0.0f, 0, 20); //TODO
    }
}

void IceTrap_Update(void) {
    // Make sure zelda_dangeon_keep is loaded
    if (ExtendedObject_GetIndex(&gGlobalContext->objectCtx, 0x3) < 0) {
        ExtendedObject_Spawn(&gGlobalContext->objectCtx, 0x3);
    }
}
