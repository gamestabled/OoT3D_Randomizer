#include "stalfos.h"
#include "settings.h"

#define EnTest_Update ((ActorFunc)GAME_ADDR(0x12E2D0))

void EnTest_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnTest_Update(thisx, globalCtx);

    if (gSettingsContext.enemizer == ON) {
        // Change wallCheckHeight from 75 to 50.
        // This fixes the Stalfos falling out of bounds in the DC miniboss room.
        Actor_UpdateBgCheckInfo(globalCtx, thisx, 50.0f, 30.0f, 30.0f,
                                UPDBGCHECKINFO_WALL | UPDBGCHECKINFO_FLOOR_WATER | UPDBGCHECKINFO_FLAG_3 |
                                    UPDBGCHECKINFO_FLAG_4);
    }
}
