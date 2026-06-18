#include "tektite.h"
#include "actor.h"

void EnTite_ReinitModels(EnTite* this) {
    SkelAnime* anime = &this->anime;
    Actor_ReinitSkelAnime(&this->actor, anime, 0);
    if (this->actor.params == TEKTITE_RED) {
        void* cmabMan = ZAR_GetCMABByIndex(anime->zarInfo, 0);
        MatAnim_Init(anime->saModel->matAnim, cmabMan);
        anime->saModel->matAnim->animSpeed = 0.0f;
        anime->saModel->matAnim->curFrame  = 1.0f;
    }
}
