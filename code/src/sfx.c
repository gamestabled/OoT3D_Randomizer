#include "z3D/z3D.h"
#include "settings.h"
#include "sfx.h"
#include "savefile.h"
#include "common.h"

SFXData rSfxData = {0};

/// A custom modulus function has to be used because the following examples for some reason cause unmapped writes:
/// [(sfxID + gGlobalContext->sceneNum) % rSfxData.rSeqMaxes[type]]
/// [gRandInt % rSfxData.rSeqMaxes[type]]
u16 CustomSFXModulus(u16 sfxOverflow, u16 mod) {
    u16 sfxResult = sfxOverflow;
    while (sfxResult >= mod) {
        sfxResult -= mod;
    }
    return sfxResult;
}

u32 SetSFX(u32 original) {
    if (!gExtSaveData.option_EnableSFX && IsInGame()) {
        return SEQ_AUDIO_BLANK;
    }

    u16 sfxID = original - SFX_BASE;
    SeqType type = rSfxData.rSeqTypesSFX[sfxID];

    // Check for invalid sound effect
    if (original < SFX_BASE || original > SFX_BASE + SFX_COUNT || type >= SEQTYPE_COUNT) {
        return original;
    }

    if (gSettingsContext.shuffleSFXCategorically) {
        if (gSettingsContext.shuffleSFX == SHUFFLESFX_SCENESPECIFIC) {
            return rSfxData.rSFXOverrides_Types[type][CustomSFXModulus(sfxID + gGlobalContext->sceneNum, rSfxData.rSeqMaxes[type])];
        }
        else if (gSettingsContext.shuffleSFX == SHUFFLESFX_CHAOS) {
            return rSfxData.rSFXOverrides_Types[type][CustomSFXModulus(sfxID + gRandInt, rSfxData.rSeqMaxes[type])];
        }
    } else {
        if (gSettingsContext.shuffleSFX == SHUFFLESFX_SCENESPECIFIC) {
            return rSfxData.rSFXOverrides_AllTrimmed[CustomSFXModulus(sfxID + gGlobalContext->sceneNum, SFX_COUNT_TRIMMED)];
        }
        else if (gSettingsContext.shuffleSFX == SHUFFLESFX_CHAOS) {
            return rSfxData.rSFXOverrides_AllTrimmed[CustomSFXModulus(sfxID + gRandInt, SFX_COUNT_TRIMMED)];
        }
    }

    return rSfxData.rSFXOverrides_All[sfxID];
}
