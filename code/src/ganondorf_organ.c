#include "z3D/z3D.h"
#include "savefile.h"

#define EnGanonOrgan_Init_addr 0x280E0C
#define EnGanonOrgan_Init ((ActorFunc)EnGanonOrgan_Init_addr)

void EnGanonOrgan_rInit(Actor* organ, GlobalContext* globalCtx) {
    gSaveContext.eventChkInf[12] &= ~0x80;
    if (gSaveContext.linkAge == 0 && gSaveContext.magic && gSaveContext.items[SLOT_BOW] != 0xFF &&
        gSaveContext.items[SLOT_ARROW_LIGHT] == ITEM_ARROW_LIGHT && gSaveContext.entranceIndex == 0x41F) {
        gExtSaveData.reachedGanondorfWithItems = 1;
    }
    EnGanonOrgan_Init(organ, globalCtx);
}
