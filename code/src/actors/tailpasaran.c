#include "tailpasaran.h"
#include "actor.h"

void EnTp_ReinitModels(EnTp* this) {
    Actor_DestroySkelModels(&this->actor, &this->model, NULL);

    if (this->actor.params <= TAILPASARAN_HEAD || this->actor.params == TAILPASARAN_HEAD_DYING) {
        Actor_CreateSkelModels(&this->actor, gGlobalContext, &this->model, 0, NULL);
        Actor_ReinitSkelAnime(&this->actor, &this->skelAnime, 0);
    } else {
        ZARInfo* zarInfo       = Actor_CreateSkelModels(&this->actor, gGlobalContext, &this->model, 1, NULL);
        this->matAnim.subSAM10 = this->model->subSAM10;
        MatAnim_Init(&this->matAnim, ZAR_GetCMABByIndex(zarInfo, 0));
        this->matAnim.animMode = 1;
    }
}
