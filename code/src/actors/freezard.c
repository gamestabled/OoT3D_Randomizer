#include "freezard.h"
#include "actor.h"

void EnFz_ReinitModels(EnFz* this) {
    Actor_DestroySkelModels(&this->actor, &this->mainModel, NULL);
    ZARInfo* zarInfo = Actor_CreateSkelModels(&this->actor, gGlobalContext, &this->mainModel, 0, NULL);

    this->models[60] = this->mainModel;

    MatAnim_Init(this->mainModel->matAnim, ZAR_GetCMABByIndex(zarInfo, 0));
    this->mainModel->matAnim->animMode  = 1;
    this->mainModel->matAnim->animSpeed = 2.0;
}
