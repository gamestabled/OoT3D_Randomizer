#include "z3D/z3D.h"
#include "settings.h"

#include "gerudos.h"

#define EnGe1_Init ((ActorFunc)GAME_ADDR(0x18B218))
#define EnGe1_Update ((ActorFunc)GAME_ADDR(0x1D742C))

#define EnGe1_TalkAfterGame_Archery ((ActorFunc)GAME_ADDR(0x12A5C8))

#define EnGeldB_Init ((ActorFunc)GAME_ADDR(0x1D7BD8))
#define EnGeldB_Update ((ActorFunc)GAME_ADDR(0x14A04C))
#define EnGeldB_Draw ((ActorFunc)GAME_ADDR(0x1B2B00))

void EnGe1_rInit(Actor* thisx, GlobalContext* globalCtx) {
    EnGe1* self = (EnGe1*)thisx;

    if ((self->actor.params & 0xFF) == GE1_TYPE_GATE_OPERATOR) {
        if (gSettingsContext.shuffleGerudoToken || gSettingsContext.shuffleOverworldEntrances
            /* || gSettingsContext.shuffleInteriorEntrances || gSettingsContexts.shuffleSpawnPositions*/) {
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0x138, -1358.0f, 88.0f, -3018.0f, 0, 0x95B0, 0, 0x0302, FALSE);
        }
    } else if ((self->actor.params & 0xFF) == GE1_TYPE_EXTRA_GATE_OPERATOR) {
        self->actor.params &= ~0xFF;
        self->actor.params |= GE1_TYPE_GATE_OPERATOR;
    } else if ((self->actor.params & 0xFF) == GE1_TYPE_TRAINING_GROUNDS_GUARD &&
               gSaveContext.sceneFlags[93].swch & 0x00000004) {
        self->actor.params &= ~0xFF;
        self->actor.params |= GE1_TYPE_NORMAL;
    }

    EnGe1_Init(thisx, globalCtx);
}

void EnGe1_rUpdate(Actor* thisx, GlobalContext* globalCtx) {

    EnGe1_Update(thisx, globalCtx);

    if (gSettingsContext.skipMinigamePhases == SKIP &&
        !(gSaveContext.eventChkInf[6] & 0x0040) // custom flag to execute this code only once per savefile
        && (gSaveContext.infTable[25] & 1)      // obtained Piece of Heart reward
    ) {
        EnGe1_TalkAfterGame_Archery(thisx, globalCtx);
        gSaveContext.eventChkInf[6] |= 0x0040;
    }
}

void EnGeldB_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    u32 prevSwitchFlags = gGlobalContext->actorCtx.flags.swch;

    if (Enemizer_IsEnemyRandomized(ENEMY_GERUDO_FIGHTER)) {
        // Set flag 0 so the Gerudo always spawns.
        gGlobalContext->actorCtx.flags.swch = 1;
    }

    EnGeldB_Update(thisx, globalCtx);

    if (Enemizer_IsEnemyRandomized(ENEMY_GERUDO_FIGHTER)) {
        gGlobalContext->actorCtx.flags.swch = prevSwitchFlags;
    }
}

void EnGeldB_rDraw(Actor* thisx, GlobalContext* globalCtx) {
    EnGeldB* this = (EnGeldB*)thisx;

    EnGeldB_Draw(thisx, globalCtx);

    // If the player is caught by a randomized Gerudo, go back to the last entrance.
    if (Enemizer_IsEnemyRandomized(ENEMY_GERUDO_FIGHTER) && this->spinAttackState > 2 &&
        globalCtx->nextEntranceIndex != -1) {
        globalCtx->nextEntranceIndex = gSaveContext.entranceIndex;
    }
}

u8 GerudoFighter_IsRandomized(void) {
    return Enemizer_IsEnemyRandomized(ENEMY_GERUDO_FIGHTER);
}
