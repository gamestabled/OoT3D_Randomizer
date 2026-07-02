#include "deku_baba.h"
#include "actor.h"

void EnDekubaba_ReinitModels(EnDekubaba* this) {
    Actor_DestroySkelModels(&this->actor, &this->stalkModel_1, &this->stalkModel_2, &this->stalkModel_3,
                            &this->leavesModel, &this->stickModel, NULL);
    Actor_CreateSkelModels(&this->actor, gGlobalContext, &this->stalkModel_1, 1, &this->stalkModel_2, 2,
                           &this->stalkModel_3, 3, &this->leavesModel, 4, &this->stickModel, 5, NULL);

    Actor_ReinitSkelAnime(&this->actor, &this->anime, 0);
}

void EnKarebaba_ReinitModels(EnKarebaba* this) {
    Actor_DestroySkelModels(&this->actor, &this->stalkModel_1, &this->stalkModel_2, &this->stalkModel_3,
                            &this->leavesModel, &this->stickModel, NULL);
    Actor_CreateSkelModels(&this->actor, gGlobalContext, &this->stalkModel_1, 1, &this->stalkModel_2, 2,
                           &this->stalkModel_3, 3, &this->leavesModel, 4, &this->stickModel, 5, NULL);

    Actor_ReinitSkelAnime(&this->actor, &this->anime, 0);
}
