#include "z3D/z3D.h"

#define EnGanonOrgan_Init ((ActorFunc)GAME_ADDR(0x280E0C))

void EnGanonOrgan_rInit(Actor* organ, GlobalContext* globalCtx) {
    gSaveContext.eventChkInf[12] &= ~0x80;
    EnGanonOrgan_Init(organ, globalCtx);
}
