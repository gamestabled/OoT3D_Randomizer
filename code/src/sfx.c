#include "z3D/z3D.h"
#include "settings.h"
#include "sfx.h"

static u32 rSFXOverrides[2048] = { 0 };

u32 SetSFX(u32 original) {
    s32 i = original - SFX_BASE;

    if (gSettingsContext.shuffleSFX == SHUFFLESFX_SCENESPECIFIC) {
        return 0x1000001 + ((i + Hash(gGlobalContext->sceneNum)) % SFX_COUNT_SHUFFLED);
    } else if (gSettingsContext.shuffleSFX == SHUFFLESFX_CHAOS) {
        return 0x1000001 + (gRandInt % SFX_COUNT_SHUFFLED);
    }

    u32 sfx;

    // Check for invalid index
    if (i < 0 || i > SFX_COUNT) {
        return original;
    }

    sfx = rSFXOverrides[i];
    // Check for invalid sound effect
    if (sfx < SFX_BASE || sfx > SFX_BASE + SFX_COUNT) {
        return original;
    }

    return rSFXOverrides[i];
}
