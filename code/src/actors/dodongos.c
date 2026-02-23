#include "z3D/z3D.h"
#include "dodongos.h"
#include "enemy_souls.h"
#include "settings.h"

#define EnDodongo_Idle ((EnDodongoActionFunc)GAME_ADDR(0x3E4FE8))

#define EnDodojr_Init ((ActorFunc)GAME_ADDR(0x1F51E8))
#define EnDodojr_JumpAttackBounce ((EnDodojrActionFunc)GAME_ADDR(0x3D069C))

#define BossDodongo_Update ((ActorFunc)GAME_ADDR(0x27BE30))
#define BossDodongo_DeathCutscene ((BossDodongoActionFunc)GAME_ADDR(0x3DA7AC))

static s16 BossDodongo_PrevNumWallCollisions = 0;

s32 Dodongos_AfterSwallowBomb_Normal(EnDodongo* this) {
    if (!EnemySouls_CheckSoulForActor(&this->base)) {
        this->actionFunc = EnDodongo_Idle;
        return 1;
    }

    return 0;
}

s32 Dodongos_AfterSwallowBomb_Baby(EnDodojr* this) {
    if (!EnemySouls_CheckSoulForActor(&this->base)) {
        this->counter    = 3;
        this->actionFunc = EnDodojr_JumpAttackBounce;
        return 1;
    }

    return 0;
}

void EnDodojr_rInit(Actor* thisx, GlobalContext* globalCtx) {
    EnDodojr_Init(thisx, globalCtx);

    // Fix vanilla bug that causes dust to be consistently drawn at y=0 when the Baby Dodongo emerges from the ground.
    thisx->floorHeight = thisx->home.pos.y;
}

void BossDodongo_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    BossDodongo* this = (BossDodongo*)thisx;
    BossDodongo_Update(thisx, globalCtx);
    if (this->numWallCollisions > BossDodongo_PrevNumWallCollisions && EnemySouls_CheckSoulForActor(thisx)) {
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
