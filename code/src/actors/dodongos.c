#include "z3D/z3D.h"
#include "dodongos.h"
#include "enemy_souls.h"
#include "settings.h"
#include "actor.h"

/*-------------------------------
|           EnDodongo           |
-------------------------------*/

void EnDodongo_Idle(EnDodongo* this, GlobalContext* globalCtx);

static s16 BossDodongo_PrevNumWallCollisions = 0;

Bool Dodongos_AfterSwallowBomb_Normal(EnDodongo* this) {
    if (EnemySouls_IsInvulnerable(&this->base)) {
        this->actionFunc = EnDodongo_Idle;
        return TRUE;
    }

    return FALSE;
}

/*-------------------------------
|            EnDodojr           |
-------------------------------*/

void EnDodojr_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDodojr_JumpAttackBounce(EnDodojr* this, GlobalContext* globalCtx);

Bool Dodongos_AfterSwallowBomb_Baby(EnDodojr* this) {
    if (EnemySouls_IsInvulnerable(&this->base)) {
        this->counter    = 3;
        this->actionFunc = EnDodojr_JumpAttackBounce;
        return TRUE;
    }

    return FALSE;
}

void EnDodojr_rInit(Actor* thisx, GlobalContext* globalCtx) {
    EnDodojr_Init(thisx, globalCtx);

    // Fix vanilla bug that causes dust to be consistently drawn at y=0 when the Baby Dodongo emerges from the ground.
    thisx->floorHeight = thisx->home.pos.y;
}

/*-------------------------------
|          BossDodongo          |
-------------------------------*/

void BossDodongo_Update(Actor* thisx, GlobalContext* globalCtx);
void BossDodongo_DeathCutscene(BossDodongo* this, GlobalContext* globalCtx);

void BossDodongo_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    BossDodongo* this = (BossDodongo*)thisx;
    BossDodongo_Update(thisx, globalCtx);
    if (this->numWallCollisions > BossDodongo_PrevNumWallCollisions && !EnemySouls_IsInvulnerable(thisx)) {
        static const s8 bonkDamageValues[] = {
            [BONKDAMAGE_NONE]    = 0,  //
            [BONKDAMAGE_QUARTER] = 0,  //
            [BONKDAMAGE_HALF]    = 0,  //
            [BONKDAMAGE_ONE]     = 1,  //
            [BONKDAMAGE_TWO]     = 2,  //
            [BONKDAMAGE_FOUR]    = 4,  //
            [BONKDAMAGE_OHKO]    = 12, //
        };
        this->health -= bonkDamageValues[gSettingsContext.bonkDamage];
        if (this->health <= 0) {
            this->health = 0;
            thisx->world.rot.y += 0x4000; // To avoid the camera going out of bounds
        }
    }
    BossDodongo_PrevNumWallCollisions = this->numWallCollisions;
}

void BossDodongo_ReinitModels(BossDodongo* this) {
    Actor_ReinitSkelAnime(&this->actor, &this->anime, 2);
}
