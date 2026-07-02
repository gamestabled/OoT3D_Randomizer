#include "spike.h"
#include "actor.h"

void EnNy_ReinitModels(EnNy* this) {
    Actor_DestroySkelModelsArray(&this->actor, 15, &this->stoneCoreModel);
    ZARInfo* zarInfo = Actor_CreateSkelModels(
        &this->actor, gGlobalContext, &this->stoneCoreModel, 0, &this->smoothCoreModel, 1, &this->spikesModel, 2,
        &this->debrisModels[0], 0, &this->debrisModels[1], 0, &this->debrisModels[2], 0, &this->debrisModels[3], 0,
        &this->debrisModels[4], 0, &this->debrisModels[5], 0, &this->debrisModels[6], 0, &this->debrisModels[7], 0,
        &this->smokeModels[0], 3, &this->smokeModels[1], 3, &this->smokeModels[2], 3, &this->smokeModels[3], 3, NULL);

    void* cmabMan = ZAR_GetCMABByIndex(zarInfo, 0);
    for (s32 i = 0; i < 4; i++) {
        MatAnim_Init(this->smokeModels[i]->matAnim, cmabMan);
        this->smokeModels[i]->matAnim->animMode  = 1;
        this->smokeModels[i]->matAnim->animSpeed = 2.0;
    }
}
