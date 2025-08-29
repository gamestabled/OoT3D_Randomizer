#include "z3D/z3D.h"
#include "dodongos.h"
#include "enemy_souls.h"

#define EnDodongo_Idle ((EnDodongoActionFunc)GAME_ADDR(0x3E4FE8))
#define EnDodojr_JumpAttackBounce ((EnDodojrActionFunc)GAME_ADDR(0x3D069C))

#define EnDodojr_Init ((ActorFunc)GAME_ADDR(0x1F51E8))

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
