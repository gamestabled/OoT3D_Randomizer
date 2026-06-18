#include "wallmaster.h"
#include "actor.h"

void EnWallmas_ReinitModels(EnWallmas* this) {
    Actor_DestroySkelModels(&this->actor, &this->shadowModel, NULL);
    Actor_CreateSkelModels(&this->actor, gGlobalContext, &this->shadowModel, 2, NULL);

    Actor_ReinitSkelAnime(&this->actor, &this->anime, 1);
}
