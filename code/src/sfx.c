#include "z3D/z3D.h"
#include "settings.h"
#include "sfx.h"
#include "savefile.h"
#include "common.h"

SFXData rSfxData = {0};

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
            return rSfxData.rSFXOverrides_Types[type][(sfxID + gGlobalContext->sceneNum) % rSfxData.rSeqMaxes[type]];
        }
        else if (gSettingsContext.shuffleSFX == SHUFFLESFX_CHAOS) {
            return rSfxData.rSFXOverrides_Types[type][(sfxID + gRandInt) % rSfxData.rSeqMaxes[type]];
        }
    } else {
        if (gSettingsContext.shuffleSFX == SHUFFLESFX_SCENESPECIFIC) {
            return rSfxData.rSFXOverrides_AllTrimmed[(sfxID + gGlobalContext->sceneNum) % SFX_COUNT_TRIMMED];
        }
        else if (gSettingsContext.shuffleSFX == SHUFFLESFX_CHAOS) {
            return rSfxData.rSFXOverrides_AllTrimmed[(sfxID + gRandInt) % SFX_COUNT_TRIMMED];
        }
    }

    return rSfxData.rSFXOverrides_All[sfxID];
}
