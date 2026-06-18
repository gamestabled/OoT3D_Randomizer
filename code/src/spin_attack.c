#include "spin_attack.h"
#include "icetrap.h"

void EnMThunder_Init(Actor* thisx, GlobalContext* globalCtx);

void EnMThunder_rInit(Actor* thisx, GlobalContext* globalCtx) {
    if (IceTrap_ActiveCurse != ICETRAP_CURSE_SWORD) {
        EnMThunder_Init(thisx, globalCtx);
    } else {
        Actor_Kill(thisx);
    }
}
