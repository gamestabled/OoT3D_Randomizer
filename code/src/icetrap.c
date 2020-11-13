#include "icetrap.h"

#include "z3D/z3D.h"

static u8 pendingFreezes = 0;

u32 IceTrap_IsPending(void) {
    return pendingFreezes > 0;
}

void IceTrap_Push(void) {
    pendingFreezes++;
}

void IceTrap_Give(void) {
    if (pendingFreezes) {
        pendingFreezes--;
        // LinkInvincibility(player, 0x14); //TODO
        // LinkDamage(globalCtx, player, 0x03, 0, 0, 0x14); //TODO
    }
}