#include "beamos.h"
#include "actor.h"

void EnVm_ReinitModels(EnVm* this) {
    Actor_DestroySkelModels(&this->actor, &this->saModel, NULL);
    Actor_CreateSkelModels(&this->actor, gGlobalContext, &this->saModel, 0, NULL);

    Actor_ReinitSkelAnime(&this->actor, &this->anime, 0);

    MatAnim_Destroy(&this->matAnim);
    this->matAnim.subSAM10 = this->anime.saModel->subSAM10;
    void* cmabMan          = ZAR_GetCMABByIndex(this->anime.zarInfo, 0);
    MatAnim_Init(&this->matAnim, cmabMan);
}
