#include "like_like.h"
#include "actor.h"

void EnRr_ReinitModels(EnRr* this) {
    Actor_ReinitSkelAnime(&this->actor, &this->skelAnime, 0);
}
