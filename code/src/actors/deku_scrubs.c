#include "deku_scrubs.h"
#include "settings.h"
#include "enemizer.h"
#include "actor.h"

/*-------------------------------
|           EnDntNomal          |
-------------------------------*/

void EnDntNomal_Update(Actor* thisx, GlobalContext* globalCtx);

void EnDntNomal_SetupTargetWalk(EnDntNomal* this, GlobalContext* globalCtx);
void EnDntNomal_SetupTargetGivePrize(EnDntNomal* this, GlobalContext* globalCtx);
void EnDntNomal_SetupTargetUnburrow(EnDntNomal* this, GlobalContext* globalCtx);

void EnDntNomal_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnDntNomal* this = (EnDntNomal*)thisx;

    EnDntNomal_Update(thisx, globalCtx);

    if (this->actionFunc == EnDntNomal_SetupTargetUnburrow && this->timer4 > 1) {
        this->timer4       = 1;
        thisx->shape.rot.y = 0xC000;
    } else if (this->actionFunc == EnDntNomal_SetupTargetWalk) {
        this->actionFunc = EnDntNomal_SetupTargetGivePrize;
    }
}

/*-------------------------------
|           EnHintnuts          |
-------------------------------*/

#define HINTNUTS_FLOWER 10

void EnHintnuts_Init(Actor* thisx, GlobalContext* globalCtx);

void EnHintnuts_rInit(Actor* thisx, GlobalContext* globalCtx) {
    EnHintnuts* this = (EnHintnuts*)thisx;

    EnHintnuts_Init(thisx, globalCtx);

    if (Enemizer_IsEnemyRandomized(ENEMY_HINT_DEKU_SCRUB)) {
        thisx->textId = this->textIdCopy = 0x3033; // "B-b-b-boooo hooooo!"
    }
}

void EnHintnuts_ReinitModels(EnHintnuts* this) {
    if (this->actor.params == HINTNUTS_FLOWER) {
        Actor_DestroySkelModels(&this->actor, &this->flowerModel, NULL);
        Actor_CreateSkelModels(&this->actor, gGlobalContext, &this->flowerModel, 2, NULL);
    } else {
        Actor_ReinitSkelAnime(&this->actor, &this->anime, 0);
    }
}

/*-------------------------------
|           EnDekunuts          |
-------------------------------*/

#define DEKUNUTS_FLOWER 10

void EnDekunuts_ReinitModels(EnDekunuts* this) {
    if (this->actor.params == DEKUNUTS_FLOWER) {
        Actor_DestroySkelModels(&this->actor, &this->flowerModel, NULL);
        Actor_CreateSkelModels(&this->actor, gGlobalContext, &this->flowerModel, 2, NULL);
    } else {
        Actor_ReinitSkelAnime(&this->actor, &this->anime, 0);
    }
}

/*-------------------------------
|           EnNutsball          |
-------------------------------*/

#define NUTSBALL_TYPE_DEKUNUTS 0
#define NUTSBALL_TYPE_HINTNUTS 1

void EnNutsball_Update(Actor* thisx, GlobalContext* globalCtx);

void EnNutsball_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnNutsball* this = (EnNutsball*)thisx;

    const u8 isFromRandomizedEnemy =
        (thisx->params == NUTSBALL_TYPE_HINTNUTS && Enemizer_IsEnemyRandomized(ENEMY_HINT_DEKU_SCRUB)) ||
        (thisx->params == NUTSBALL_TYPE_DEKUNUTS && Enemizer_IsEnemyRandomized(ENEMY_MAD_SCRUB));

    if (isFromRandomizedEnemy && thisx->bgCheckFlags & BGCHECKFLAG_GROUND && this->timer > 20) {
        // Don't break the projectile if it touches the ground too quickly after being shot, so the player can still
        // reflect it even if the enemy is surrounded by higher ground (like in the GTG Like-Like room).
        thisx->bgCheckFlags &= ~BGCHECKFLAG_GROUND;
    }

    EnNutsball_Update(thisx, globalCtx);
}
