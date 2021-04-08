#include "z3D/z3D.h"

#define EnGanonOrgan_Init_addr 0x280E0C
#define EnGanonOrgan_Init ((ActorFunc)EnGanonOrgan_Init_addr)

void EnGanonOrgan_rInit(Actor* organ, GlobalContext* globalCtx) {
    gSaveContext.eventChkInf[12] &= ~0x80;
    EnGanonOrgan_Init(organ, globalCtx);
}
