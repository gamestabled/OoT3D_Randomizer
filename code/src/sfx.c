#include "z3D/z3D.h"
#include "settings.h"
#include "sfx.h"

// Temporary, has to be set manually until rSfxData.rSeqMaxes[type] works
// General Categories
#define SEQ_PLAYER_MAX 101
#define SEQ_ITEM_MAX 77
#define SEQ_EVENT_MAX 215
#define SEQ_ENEMY_MAX 268
#define SEQ_SYSTEM_MAX 66
#define SEQ_VOICE_MAX 161
// Specific Categories
#define SEQ_WALK_MAX 51
#define SEQ_MOVE_MAX 20
#define SEQ_JUMP_MAX 27
#define SEQ_LAND_MAX 38
#define SEQ_FLY_MAX 16
#define SEQ_DEAD_MAX 58
#define SEQ_DAMAGE_MAX 47
#define SEQ_ATTACK_MAX 16
#define SEQ_AMBIENCE_MAX 14

SFXData rSfxData = {0};

u32 SetSFX(u32 original) {
    u16 sfxID = original - SFX_BASE;
    SeqType type = rSfxData.rSeqTypesSFX[sfxID];

    // Check for invalid sound effect                                                   // Only system sfx seem to make noise when played in menus
    if (original < SFX_BASE || original > SFX_BASE + SFX_COUNT || type == SEQ_NOSHUFFLE || (type == SEQ_SYSTEM && !gSettingsContext.shuffleSFXCategorically)) {
        return original;
    }

    if (gSettingsContext.shuffleSFXCategorically) {
        if (gSettingsContext.shuffleSFX == SHUFFLESFX_SCENESPECIFIC) {
            //return rSfxData.rSFXOverrides_Types[type][(sfxID + gGlobalContext->sceneNum) % rSfxData.rSeqMaxes[type]]; //Somehow fails
            switch (type) {
                // General Categories
            case SEQ_PLAYER:
                return rSfxData.rSFXOverrides_Types[type][(sfxID + gGlobalContext->sceneNum) % SEQ_PLAYER_MAX];
            case SEQ_ITEM:
                return rSfxData.rSFXOverrides_Types[type][(sfxID + gGlobalContext->sceneNum) % SEQ_ITEM_MAX];
            case SEQ_EVENT:
                return rSfxData.rSFXOverrides_Types[type][(sfxID + gGlobalContext->sceneNum) % SEQ_EVENT_MAX];
            case SEQ_ENEMY:
                return rSfxData.rSFXOverrides_Types[type][(sfxID + gGlobalContext->sceneNum) % SEQ_ENEMY_MAX];
            case SEQ_SYSTEM:
                return rSfxData.rSFXOverrides_Types[type][(sfxID + gGlobalContext->sceneNum) % SEQ_SYSTEM_MAX];
            case SEQ_VOICE:
                return rSfxData.rSFXOverrides_Types[type][(sfxID + gGlobalContext->sceneNum) % SEQ_VOICE_MAX];
                // Specific Categories
            case SEQ_WALK:
                return rSfxData.rSFXOverrides_Types[type][(sfxID + gGlobalContext->sceneNum) % SEQ_WALK_MAX];
            case SEQ_MOVE:
                return rSfxData.rSFXOverrides_Types[type][(sfxID + gGlobalContext->sceneNum) % SEQ_MOVE_MAX];
            case SEQ_JUMP:
                return rSfxData.rSFXOverrides_Types[type][(sfxID + gGlobalContext->sceneNum) % SEQ_JUMP_MAX];
            case SEQ_LAND:
                return rSfxData.rSFXOverrides_Types[type][(sfxID + gGlobalContext->sceneNum) % SEQ_LAND_MAX];
            case SEQ_FLY:
                return rSfxData.rSFXOverrides_Types[type][(sfxID + gGlobalContext->sceneNum) % SEQ_FLY_MAX];
            case SEQ_DEAD:
                return rSfxData.rSFXOverrides_Types[type][(sfxID + gGlobalContext->sceneNum) % SEQ_DEAD_MAX];
            case SEQ_DAMAGE:
                return rSfxData.rSFXOverrides_Types[type][(sfxID + gGlobalContext->sceneNum) % SEQ_DAMAGE_MAX];
            case SEQ_ATTACK:
                return rSfxData.rSFXOverrides_Types[type][(sfxID + gGlobalContext->sceneNum) % SEQ_ATTACK_MAX];
            case SEQ_AMBIENCE:
                return rSfxData.rSFXOverrides_Types[type][(sfxID + gGlobalContext->sceneNum) % SEQ_AMBIENCE_MAX];
                // Should be unreachable, silences warnings
            default:
                break;
            }
        }
        else if (gSettingsContext.shuffleSFX == SHUFFLESFX_CHAOS) {
            //return rSfxData.rSFXOverrides_Types[type][gRandInt % rSfxData.rSeqMaxes[type]]; //Somehow fails
            switch (type) {
                // General Categories
            case SEQ_PLAYER:
                return rSfxData.rSFXOverrides_Types[type][gRandInt % SEQ_PLAYER_MAX];
            case SEQ_ITEM:
                return rSfxData.rSFXOverrides_Types[type][gRandInt % SEQ_ITEM_MAX];
            case SEQ_EVENT:
                return rSfxData.rSFXOverrides_Types[type][gRandInt % SEQ_EVENT_MAX];
            case SEQ_ENEMY:
                return rSfxData.rSFXOverrides_Types[type][gRandInt % SEQ_ENEMY_MAX];
            case SEQ_SYSTEM:
                return rSfxData.rSFXOverrides_Types[type][gRandInt % SEQ_SYSTEM_MAX];
            case SEQ_VOICE:
                return rSfxData.rSFXOverrides_Types[type][gRandInt % SEQ_VOICE_MAX];
                // Specific Categories
            case SEQ_WALK:
                return rSfxData.rSFXOverrides_Types[type][gRandInt % SEQ_WALK_MAX];
            case SEQ_MOVE:
                return rSfxData.rSFXOverrides_Types[type][gRandInt % SEQ_MOVE_MAX];
            case SEQ_JUMP:
                return rSfxData.rSFXOverrides_Types[type][gRandInt % SEQ_JUMP_MAX];
            case SEQ_LAND:
                return rSfxData.rSFXOverrides_Types[type][gRandInt % SEQ_LAND_MAX];
            case SEQ_FLY:
                return rSfxData.rSFXOverrides_Types[type][gRandInt % SEQ_FLY_MAX];
            case SEQ_DEAD:
                return rSfxData.rSFXOverrides_Types[type][gRandInt % SEQ_DEAD_MAX];
            case SEQ_DAMAGE:
                return rSfxData.rSFXOverrides_Types[type][gRandInt % SEQ_DAMAGE_MAX];
            case SEQ_ATTACK:
                return rSfxData.rSFXOverrides_Types[type][gRandInt % SEQ_ATTACK_MAX];
            case SEQ_AMBIENCE:
                return rSfxData.rSFXOverrides_Types[type][gRandInt % SEQ_AMBIENCE_MAX];
                // Should be unreachable, silences warnings
            default:
                break;
            }
        }
    }
    else {
        if (gSettingsContext.shuffleSFX == SHUFFLESFX_SCENESPECIFIC) {
            return rSfxData.rSFXOverrides_All[(sfxID + gGlobalContext->sceneNum) % SFX_COUNT];
        }
        else if (gSettingsContext.shuffleSFX == SHUFFLESFX_CHAOS) {
            return rSfxData.rSFXOverrides_All[gRandInt % SFX_COUNT];
        }
    }

    return rSfxData.rSFXOverrides_All[sfxID];
}
