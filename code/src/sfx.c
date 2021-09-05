#include "z3D/z3D.h"
#include "settings.h"
#include "sfx.h"

SFXData rSfxData = {0};

/// A custom modulus function has to be used because the following examples for some reason cause unmapped writes:
/// [(sfxID + gGlobalContext->sceneNum) % rSfxData.rSeqMaxes[type]]
/// [gRandInt % rSfxData.rSeqMaxes[type]]
u16 CustomSFXModulus(u16 sfxOverflow, SeqType type_) {
    u16 sfxResult = sfxOverflow;
    while (sfxResult >= rSfxData.rSeqMaxes[type_]) {
        sfxResult -= rSfxData.rSeqMaxes[type_];
    }
    return sfxResult;
}

u32 SetSFX(u32 original) {
    u16 sfxID = original - SFX_BASE;
    SeqType type = rSfxData.rSeqTypesSFX[sfxID];

    // Check for invalid sound effect                                                   // Only system sfx seem to make noise when played in menus
    if (original < SFX_BASE || original > SFX_BASE + SFX_COUNT || type == SEQ_NOSHUFFLE || (type == SEQ_SYSTEM && !gSettingsContext.shuffleSFXCategorically)) {
        return original;
    }

    if (gSettingsContext.shuffleSFXCategorically) {
        if (gSettingsContext.shuffleSFX == SHUFFLESFX_SCENESPECIFIC) {
            return rSfxData.rSFXOverrides_Types[type][CustomSFXModulus(sfxID + gGlobalContext->sceneNum, type)];
        }
        else if (gSettingsContext.shuffleSFX == SHUFFLESFX_CHAOS) {
            return rSfxData.rSFXOverrides_Types[type][CustomSFXModulus(sfxID + gRandInt, type)];
        }
    } else {
        if (gSettingsContext.shuffleSFX == SHUFFLESFX_SCENESPECIFIC) {
            return rSfxData.rSFXOverrides_All[(sfxID + gGlobalContext->sceneNum) % SFX_COUNT];
        }
        else if (gSettingsContext.shuffleSFX == SHUFFLESFX_CHAOS) {
            return rSfxData.rSFXOverrides_All[(sfxID + gRandInt) % SFX_COUNT];
        }
    }

    return rSfxData.rSFXOverrides_All[sfxID];
}
