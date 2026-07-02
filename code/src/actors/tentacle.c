#include "tentacle.h"
#include "actor.h"

/*-------------------------------
|         Enemy Tentacle        |
-------------------------------*/

void EnBa_ReinitModels(EnBa* this) {
    Actor_ReinitSkelAnime(&this->actor, &this->anime, 0);

    this->matAnim = this->anime.saModel->matAnim;
    void* cmabMan = ZAR_GetCMABByIndex(this->anime.zarInfo, 3);
    MatAnim_Init(this->matAnim, cmabMan);
    this->matAnim->animSpeed = 1.0;
    this->matAnim->animMode  = 1;

    FaceAnim_Destroy(&this->faceAnim);
    FaceAnim_Init(&this->faceAnim, &this->anime, 2, -1, -1);
    FaceAnim_SetFrame(&this->faceAnim, 0, this->actor.params);
    FaceAnim_35E330(&this->faceAnim);
}

/*-------------------------------
|     Path Blocking Tentacle    |
-------------------------------*/

void EnBx_ReinitModels(EnBx* this) {
    Actor_ReinitSkelAnime(&this->actor, &this->anime, 2);

    MatAnim_Destroy(&this->matAnim);
    this->matAnim.subSAM10 = this->anime.saModel->subSAM10;
    void* cmabMan          = ZAR_GetCMABByIndex(this->anime.zarInfo, 1);
    MatAnim_Init(&this->matAnim, cmabMan);
    this->matAnim.animSpeed = 1.0;
    this->matAnim.animMode  = 1;

    FaceAnim_Destroy(&this->faceAnim);
    FaceAnim_Init(&this->faceAnim, &this->anime, 0, -1, -1);
    FaceAnim_SetFrame(&this->faceAnim, 0, this->actor.params & 0x7F);
    FaceAnim_35E330(&this->faceAnim);
}
