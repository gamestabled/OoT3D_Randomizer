#include "z3D/z3D.h"
#include "flying_traps.h"
#include "enemy_souls.h"

#define EnYukabyun_Levitate ((EnYukabyun_ActionFunc)GAME_ADDR(0x3B9E3C))
#define EnTuboTrap_WaitForProximity ((EnTuboTrap_ActionFunc)GAME_ADDR(0x3E6F88))

s32 FlyingTraps_Tile_OnImpact(EnYukabyun* this) {
    if (!EnemySouls_CheckSoulForActor(&this->base)) {
        this->actionFunc  = EnYukabyun_Levitate;
        this->waitCounter = 0;
        return 0;
    }
    return 1;
}

s32 FlyingTraps_Pot_OnImpact(EnTuboTrap* this) {
    if (this->base.bgCheckFlags & 0x1) { // Standing on the ground
        this->actionFunc   = EnTuboTrap_WaitForProximity;
        this->base.gravity = 0;
        this->base.speedXZ = 0;
    }

    return EnemySouls_CheckSoulForActor(&this->base);
}
