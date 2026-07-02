#include "armos.h"
#include "enemy_souls.h"
#include "actor.h"
#include "objects.h"

void EnAm_Draw(Actor* thisx, GlobalContext* globalCtx);

static void EnAm_ReinitModels(EnAm* this) {
    Actor_ReinitSkelAnime(&this->dyna.actor, &this->anime, 0);
}

void EnAm_rDraw(Actor* thisx, GlobalContext* globalCtx) {
    EnAm* this = (EnAm*)thisx;
    if (SoullessModels_Enabled && EnemySouls_ShouldDrawSoulless(thisx) && !this->rExt.usingModifiedModel) {
        // Modify CMB data and reinit model.
        ObjectEntry* obj = Object_FindEntry(OBJECT_ARMOS);
        SoullessModels_ModifyGenericCmb(obj->zarInfo.cmbMans[ARMOS_CMB_INDEX]);
        EnAm_ReinitModels(this);
        SoullessModels_CmbRestoreRequest = TRUE;
        this->rExt.usingModifiedModel    = TRUE;
    } else if (!EnemySouls_ShouldDrawSoulless(thisx) && this->rExt.usingModifiedModel) {
        // Reinit model with the normal data in the CMB, so it will look normal again.
        EnAm_ReinitModels(this);
        this->rExt.usingModifiedModel = FALSE;
    }

    EnAm_Draw(thisx, globalCtx);
}
