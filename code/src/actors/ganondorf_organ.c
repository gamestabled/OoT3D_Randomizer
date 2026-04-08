#include "z3D/z3D.h"

void EnGanonOrgan_Init(Actor* thisx, GlobalContext* globalCtx);

void EnGanonOrgan_rInit(Actor* organ, GlobalContext* globalCtx) {
    gSaveContext.eventChkInf[12] &= ~0x80;
    EnGanonOrgan_Init(organ, globalCtx);
}
