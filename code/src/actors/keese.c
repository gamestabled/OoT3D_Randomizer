#include "keese.h"
#include "actor.h"

void EnFirefly_ReinitModels(EnFirefly* this) {
    Actor_ReinitSkelAnime(&this->actor, &this->skelAnime, 0);
}
