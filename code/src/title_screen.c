#include "z3D/z3D.h"
#include "custom_models.h"
#include "objects.h"
#include "title_screen.h"

#define EnMag_Init_addr 0x18CBB8
#define EnMag_Init ((ActorFunc)EnMag_Init_addr)

void EnMag_rInit(Actor* thisx, GlobalContext* globalCtx) {
    EnMag* this = (EnMag*)thisx;

    s8 objBankIdx = this->actor.objBankIndex;
    void* titleScreenZAR = globalCtx->objectCtx.status[objBankIdx].zarInfo.buf;
    void* cmabMan;

    s32 extendedObjectBankIdx = Object_Spawn(&rExtendedObjectCtx, OBJECT_CUSTOM_GENERAL_ASSETS);
    CustomModel_EditTitleScreenLogo(titleScreenZAR);

    EnMag_Init(thisx, globalCtx);

    cmabMan = ZAR_GetCMABByIndex(&rExtendedObjectCtx.status[extendedObjectBankIdx].zarInfo, TEXANIM_TITLE_LOGO_US);
    TexAnim_Spawn(this->logoModel->unk_0C, cmabMan);
    this->logoModel->unk_0C->animSpeed = 0.0f;
    this->logoModel->unk_0C->animMode = 0;

    cmabMan = ZAR_GetCMABByIndex(&rExtendedObjectCtx.status[extendedObjectBankIdx].zarInfo, TEXANIM_COPY_NINTENDO);
    TexAnim_Spawn(this->copyrightModel->unk_0C, cmabMan);
    this->copyrightModel->unk_0C->animSpeed = 0.0f;
    this->copyrightModel->unk_0C->animMode = 0;
}
