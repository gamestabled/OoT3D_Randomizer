#include "z3D/z3D.h"
#include "settings.h"
#include "sfx.h"
#include "savefile.h"
#include "common.h"
#include "multiplayer.h"

SFXData rSfxData = {0};

u32 SetSFX(u32 original) {
    // Hack for hookshot as child (adult voice -> child voice)
    if (original == 0x100050D && gSaveContext.linkAge == 1) {
        original = 0x100050B;
    }
    u16 sfxID = original - SFX_BASE;
    SeqType type = rSfxData.rSeqTypesSFX[sfxID];

    // Send SFX
    if (!mp_duplicateSendProtection) {
        if (IsInGame() && sfxID >= 1258 && sfxID <= 1321) {
            Multiplayer_Send_LinkSFX(original);
        }
    }
    mp_duplicateSendProtection = false;

    static const u16 GET_BOXITEM_ID = 1205; // Treat GET_BOXITEM as a fanfare
    if (IsInGame() && ((!gExtSaveData.option_EnableSFX && sfxID != GET_BOXITEM_ID) || (!gExtSaveData.option_EnableBGM && sfxID == GET_BOXITEM_ID))) {
        return SEQ_AUDIO_BLANK;
    }

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
