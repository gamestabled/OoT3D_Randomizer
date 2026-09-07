#include "stalfos.h"
#include "settings.h"
#include "enemizer.h"
#include "actor.h"

void EnTest_Update(Actor* thisx, GlobalContext* globalCtx);

void EnTest_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    const Bool isRandomized = Enemizer_IsEnemyRandomized(ENEMY_STALFOS);
    if (isRandomized && thisx->params == 0x0003 && thisx->floorPoly == PLAYER->actor.floorPoly) {
        // For Stalfos that drop from above when approached, bypass the y distance check if the player
        // is standing on the floor below the enemy.
        thisx->yDistToPlayer = 0;
    }

    EnTest_Update(thisx, globalCtx);

    if (isRandomized) {
        // Change wallCheckHeight from 75 to 50.
        // This fixes the Stalfos falling out of bounds in the DC miniboss room.
        Actor_UpdateBgCheckInfo(globalCtx, thisx, 50.0f, 30.0f, 30.0f,
                                UPDBGCHECKINFO_WALL | UPDBGCHECKINFO_FLOOR_WATER | UPDBGCHECKINFO_FLAG_3 |
                                    UPDBGCHECKINFO_FLAG_4);
    }
}

void EnTest_ReinitModels(EnTest* this) {
    Actor_ReinitSkelAnime(&this->actor, &this->skelAnime, 0);
}
