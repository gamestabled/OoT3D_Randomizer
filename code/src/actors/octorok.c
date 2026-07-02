#include "octorok.h"
#include "actor.h"

void EnOkuta_ReinitModels(EnOkuta* this) {
    Actor_DestroySkelModels(&this->actor, &this->rockModel, NULL);
    Actor_CreateSkelModels(&this->actor, gGlobalContext, &this->rockModel, 1, NULL);

    Actor_ReinitSkelAnime(&this->actor, &this->anime, 0);
}
