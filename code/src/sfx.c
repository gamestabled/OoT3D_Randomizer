#include "z3D/z3D.h"
#include "settings.h"
#include "sfx.h"
#include "savefile.h"
#include "common.h"
#include "multiplayer.h"

SFXData rSfxData = { 0 };

u8 SeqTypeIsMovement(SeqType type) {
    return type == SEQ_WALK || type == SEQ_WALK_LOUD || type == SEQ_JUMP || type == SEQ_LAND || type == SEQ_SLIP ||
           type == SEQ_SLIP_LOOP || type == SEQ_BOUND || type == SEQ_CRAWL;
}

u32 SetSFX(u32 original) {
    // Hack for hookshot as child (adult voice -> child voice)
    if (original == 0x100050D && gSaveContext.linkAge == 1) {
        original = 0x100050B;
    }
    u16 sfxID    = original - SFX_BASE;
    SeqType type = rSfxData.rSeqTypesSFX[sfxID];

    // Send SFX
    if (!mp_duplicateSendProtection) {
        if (IsInGameOrBossChallenge() && sfxID >= 1258 && sfxID <= 1321) {
            Multiplayer_Send_LinkSFX(original);
        }
    }
    mp_duplicateSendProtection = false;

    static const u16 GET_BOXITEM_ID = 1205; // Treat GET_BOXITEM as a fanfare
    if (IsInGameOrBossChallenge() && ((!gExtSaveData.option_EnableSFX && sfxID != GET_BOXITEM_ID) ||
                                      (!gExtSaveData.option_EnableBGM && sfxID == GET_BOXITEM_ID))) {
        return SEQ_AUDIO_BLANK;
    }

    // Check for invalid sound effect
    if (original < SFX_BASE || original > SFX_BASE + SFX_COUNT || type >= SEQTYPE_COUNT ||
        (!gSettingsContext.shuffleSFXFootsteps && SeqTypeIsMovement(type)) ||
        (!gSettingsContext.shuffleSFXLinkVoice && sfxID >= 1258 && sfxID <= 1321)) {
        return original;
    }

    if (gSettingsContext.shuffleSFXCategorically) {
        if (gSettingsContext.shuffleSFX == SHUFFLESFX_SCENESPECIFIC) {
            return rSfxData.rSFXOverrides_Types[type][(sfxID + gGlobalContext->sceneNum) % rSfxData.rSeqCounts[type]];
        } else if (gSettingsContext.shuffleSFX == SHUFFLESFX_CHAOS) {
            return rSfxData.rSFXOverrides_Types[type][(sfxID + gRandInt) % rSfxData.rSeqCounts[type]];
        }
    } else {
        if (gSettingsContext.shuffleSFX == SHUFFLESFX_SCENESPECIFIC) {
            return rSfxData
                .rSFXOverrides_AllTrimmed[(sfxID + gGlobalContext->sceneNum) % rSfxData.rSFXOverrides_TrimmedCount];
        } else if (gSettingsContext.shuffleSFX == SHUFFLESFX_CHAOS) {
            return rSfxData.rSFXOverrides_AllTrimmed[(sfxID + gRandInt) % rSfxData.rSFXOverrides_TrimmedCount];
        }
    }

    return rSfxData.rSFXOverrides_All[sfxID];
}
