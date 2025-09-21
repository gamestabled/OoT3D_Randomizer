#include "z3D/z3D.h"
#include "custom_models.h"
#include "objects.h"
#include "title_screen.h"

#define EnMag_Init ((ActorFunc)GAME_ADDR(0x18CBB8))

u8 missingRomfsAlert = 0;
s16 romfsAlertFrames = 0;

void EnMag_rInit(Actor* thisx, GlobalContext* globalCtx) {
    EnMag* this = (EnMag*)thisx;

    void* titleScreenZAR     = Object_GetEntry(this->actor.objectSlot)->zarInfo.buf;
    ZARInfo* customAssetsZAR = &Object_FindEntryOrSpawn(OBJECT_CUSTOM_GENERAL_ASSETS)->zarInfo;
    void* cmabMan;

    CustomModel_EditTitleScreenLogo(titleScreenZAR);

    EnMag_Init(thisx, globalCtx);

    cmabMan = ZAR_GetCMABByIndex(customAssetsZAR, TEXANIM_TITLE_LOGO_US);
    TexAnim_Spawn(this->logoModel->unk_0C, cmabMan);
    this->logoModel->unk_0C->animSpeed = 0.0f;
    this->logoModel->unk_0C->animMode  = 0;

    cmabMan = ZAR_GetCMABByIndex(customAssetsZAR, TEXANIM_COPY_NINTENDO);
    TexAnim_Spawn(this->copyrightModel->unk_0C, cmabMan);
    this->copyrightModel->unk_0C->animSpeed = 0.0f;
    this->copyrightModel->unk_0C->animMode  = 0;

    if (cmabMan == 0) {
        // If the pointer is 0, the romfs folder is not present.
        // The 3DS would've crashed by this point, so this alert is for Citra only.
        missingRomfsAlert = 1;
        romfsAlertFrames  = 300;
    }
}
