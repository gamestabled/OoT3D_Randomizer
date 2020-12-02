#include "z3D/z3D.h"

// Checks a chest flag for spawning the fire arrows
// Replaces a check for fire arrows in the inventory
u32 ShotSun_CheckChestFlag(void) {
    return ((gGlobalContext->actorCtx.flags.chest & 0x1) != 0);
}
