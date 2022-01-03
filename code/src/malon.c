#include "malon.h"

#define EnMa1_Init_addr 0x18C334
#define EnMa1_Init ((ActorFunc)EnMa1_Init_addr)

void EnMa1_rInit(Actor* thisx, GlobalContext* globalCtx) {
    if (gSaveContext.eventChkInf[0x1] & 0x0010) { //If Talon has fled the castle...
        gSaveContext.eventChkInf[0x1] |= 0x0040;  //...set "Invited to Sing With Child Malon" flag
    }
    EnMa1_Init(thisx, globalCtx);
}
