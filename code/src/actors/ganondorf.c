#include "z3D/z3D.h"
#include "ganondorf.h"

#define BossGanon_Update ((ActorFunc)GAME_ADDR(0x242A94))

void BossGanon_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    s16 prevHealthAccumulator = gSaveContext.healthAccumulator;

    BossGanon_Update(thisx, globalCtx);

    if (gSaveContext.healthCapacity == 0) {
        // Don't fill health if player has 0 hearts.
        gSaveContext.healthAccumulator = prevHealthAccumulator;
    }
}
