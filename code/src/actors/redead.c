#include "redead.h"
#include "actor.h"

void EnRd_ReinitModels(EnRd* this) {
    s32 cmbIndex = this->actor.params >= REDEAD_TYPE_DOES_NOT_MOURN ? 0 : 1;
    Actor_ReinitSkelAnime(&this->actor, &this->skelAnime, cmbIndex);
}
