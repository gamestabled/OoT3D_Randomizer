#include "z3D/z3D.h"
#include "custom_models.h"

#define EnMag_Init_addr 0x18CBB8
#define EnMag_Init ((ActorFunc)EnMag_Init_addr)

typedef void (*ZarSetup_Func)(ZARInfo* zarInfo, void* buf, s32 size, s8 param_4);

void EnMag_rInit(Actor* thisx, GlobalContext* globalCtx) {
    s8 objBankIdx = thisx->objBankIndex;
    void* titleScreenZAR = globalCtx->objectCtx.status[objBankIdx].zarInfo.buf;

    CustomModel_EditTitleScreenLogo(titleScreenZAR);

    // Whoops, those edits went and invalidated the CSAB and CMAB managers!
    // For now, we can just re-run the ZARInfo init function to recreate them. TODO: This might 
    // leak the old managers? Worth looking into that once the CSAB/CMAB managers are better
    // understood, but its unlikely to be a big deal since they are small and this should be infrequent
    ((ZarSetup_Func)0x31B124)(&globalCtx->objectCtx.status[objBankIdx].zarInfo, titleScreenZAR, 0xA5CAC, 0);

    EnMag_Init(thisx, globalCtx);
}
