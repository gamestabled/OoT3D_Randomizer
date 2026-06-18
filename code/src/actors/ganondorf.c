#include "z3D/z3D.h"
#include "ganondorf.h"

void BossGanon_Update(Actor* thisx, GlobalContext* globalCtx);

void BossGanon_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    s16 prevHealthAccumulator = gSaveContext.healthAccumulator;

    BossGanon_Update(thisx, globalCtx);

    if (gSaveContext.healthCapacity == 0) {
        // Don't fill health if player has 0 hearts.
        gSaveContext.healthAccumulator = prevHealthAccumulator;
    }
}
