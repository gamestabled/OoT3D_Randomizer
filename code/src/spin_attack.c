#include "spin_attack.h"
#include "icetrap.h"

#define EnMThunder_Init ((ActorFunc)GAME_ADDR(0x24C910))

void EnMThunder_rInit(Actor* thisx, GlobalContext* globalCtx) {
    if (IceTrap_ActiveCurse != ICETRAP_CURSE_SWORD) {
        EnMThunder_Init(thisx, globalCtx);
    } else {
        Actor_Kill(thisx);
    }
}
