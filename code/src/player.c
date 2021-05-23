#include "z3D/z3D.h"
#include "objects.h"
#include "custom_models.h"

void* Player_EditAndRetrieveCMB(ZARInfo* zarInfo, u32 objModelIdx) {
    void* cmbMan = ZAR_GetCMBByIndex(zarInfo, objModelIdx);
    
    if (gSaveContext.linkAge == 0) {
        void* cmb = (void*)(((char*)zarInfo->buf) + 0xDAE8);
        CustomModel_EditLinkToCustomTunic(cmb);
    }

    return cmbMan;
}

void* Player_GetCustomTunicCMAB(void) {
    s16 exObjectBankIdx = Object_GetIndex(&rExtendedObjectCtx, OBJECT_CUSTOM_GENERAL_ASSETS);
    if (exObjectBankIdx < 0) {
        exObjectBankIdx = Object_Spawn(&rExtendedObjectCtx, OBJECT_CUSTOM_GENERAL_ASSETS);
    }
    return ZAR_GetCMABByIndex(&rExtendedObjectCtx.status[exObjectBankIdx].zarInfo, TEXANIM_LINK_BODY);
}
