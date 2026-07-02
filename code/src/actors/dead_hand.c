#include "dead_hand.h"
#include "settings.h"
#include "enemizer.h"
#include "actor.h"

/*-------------------------------
|              EnDh             |
-------------------------------*/

void EnDh_ReinitModels(EnDh* this) {
    Actor_DestroySkelModels(&this->actor, &this->dirtWaveModel, NULL);
    ZARInfo* zarInfo = Actor_CreateSkelModels(&this->actor, gGlobalContext, &this->dirtWaveModel, 2, NULL);

    this->dirtWaveMatAnim = this->dirtWaveModel->matAnim;
    MatAnim_Init(this->dirtWaveMatAnim, ZAR_GetCMABByIndex(zarInfo, 0));
    this->dirtWaveMatAnim->animSpeed = 2.0;
    this->dirtWaveMatAnim->animMode  = 1;

    Actor_ReinitSkelAnime(&this->actor, &this->anime, 1);
}

/*-------------------------------
|             EnDha             |
-------------------------------*/

void EnDha_Update(Actor* thisx, GlobalContext* globalCtx);

void EnDha_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnDha_Update(thisx, globalCtx);

    thisx->shape.shadowDrawFunc = NULL;

    if (Enemizer_IsEnemyRandomized(ENEMY_DEAD_HAND_HAND) && thisx->parent == NULL &&
        thisx->shape.yOffset <= -12000.0f) {
        // Kill the actor when the hand is defeated so that dungeon rooms can be cleared.
        Actor_Kill(thisx);
    }
}
