#include "well_stone.h"
#include "settings.h"

// This actor is the stone blocking bottom of the well as adult Link. This is
// different from the stone blocking child Link from getting into the well
// early during the day before the well water has been drained.
#define BgSpot01Idosoko_Init ((ActorFunc)GAME_ADDR(0x2AC7C8))

void BgSpot01Idosoko_rInit(Actor* thisx, GlobalContext* globalCtx) {

    BgSpot01Idosoko_Init(thisx, globalCtx);

    // If dungeon entrance randomizer is on, remove the stone as adult Link when
    // child Link has drained the water to the well
    if (EventCheck(0x67) && gSettingsContext.shuffleDungeonEntrances) {
        Actor_Kill(thisx);
    }
}
