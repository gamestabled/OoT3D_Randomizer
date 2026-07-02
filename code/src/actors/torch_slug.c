#include "torch_slug.h"
#include "actor.h"

void EnBw_ReinitModels(EnBw* this) {
    Actor_ReinitSkelAnime(&this->actor, &this->anime, 0);

    this->matAnim = this->anime.saModel->matAnim;
    void* cmabMan = ZAR_GetCMABByIndex(this->anime.zarInfo, 0);
    MatAnim_Init(this->matAnim, cmabMan);
    this->matAnim->animMode = 1;
}
