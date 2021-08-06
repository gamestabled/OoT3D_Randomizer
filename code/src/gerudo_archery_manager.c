#include "z3D/z3D.h"
#include "settings.h"

#define EnGe1_Update_addr 0x1D742C
#define EnGe1_Update ((ActorFunc)EnGe1_Update_addr)

#define EnGe1_TalkAfterGame_Archery_addr 0x12A5C8
#define EnGe1_TalkAfterGame_Archery ((ActorFunc)EnGe1_TalkAfterGame_Archery_addr)

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
