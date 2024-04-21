#include "z3D/z3D.h"
#include "settings.h"

#include "gerudos.h"

#define EnGe1_Init_addr 0x18B218
#define EnGe1_Init ((ActorFunc)EnGe1_Init_addr)

#define EnGe1_Update_addr 0x1D742C
#define EnGe1_Update ((ActorFunc)EnGe1_Update_addr)

#define EnGe1_TalkAfterGame_Archery_addr 0x12A5C8
#define EnGe1_TalkAfterGame_Archery ((ActorFunc)EnGe1_TalkAfterGame_Archery_addr)

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
