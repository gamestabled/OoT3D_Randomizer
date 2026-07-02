#include "wolfos.h"
#include "actor.h"

void EnWf_ReinitModels(EnWf* this) {
    Actor_ReinitSkelAnime(&this->actor, &this->skelAnime, 0);

    FaceAnim_Destroy(&this->faceAnim);
    s32 eyeCmabIdx = this->actor.params == 0 ? 0 : 1;
    FaceAnim_Init(&this->faceAnim, &this->skelAnime, eyeCmabIdx, 2, -1);
}
