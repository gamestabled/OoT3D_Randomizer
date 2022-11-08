#include "spin_attack.h"
#include "icetrap.h"

#define EnMThunder_Init_addr 0x24C910
#define EnMThunder_Init ((ActorFunc)EnMThunder_Init_addr)

void EnMThunder_rInit(Actor* thisx, GlobalContext* globalCtx) {
    if (IceTrap_ActiveCurse != ICETRAP_CURSE_SWORD) {
        EnMThunder_Init(thisx, globalCtx);
    } else {
        Actor_Kill(thisx);
    }
}
