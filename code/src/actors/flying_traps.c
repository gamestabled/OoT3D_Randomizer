#include "z3D/z3D.h"
#include "flying_traps.h"
#include "enemy_souls.h"
#include "settings.h"
#include "common.h"

#define EnYukabyun_Update ((ActorFunc)GAME_ADDR(0x26E628))

#define EnYukabyun_Levitate ((EnYukabyun_ActionFunc)GAME_ADDR(0x3B9E3C))
#define EnYukabyun_Wait ((EnYukabyun_ActionFunc)GAME_ADDR(0x3E6880))
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

void EnYukabyun_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnYukabyun* this = (EnYukabyun*)thisx;

    if (Enemizer_IsEnemyRandomized(ENEMY_FLYING_FLOOR_TILE)) {
        Vec3f targetPos = (Vec3f){
            .x = PLAYER->actor.world.pos.x,
            .y = PLAYER->actor.world.pos.y + 20,
            .z = PLAYER->actor.world.pos.z,
        };

        if (this->actionFunc == EnYukabyun_Wait) {
            Vec3f posResult;
            CollisionPoly* outPoly;
            s32 bgId;

            // Wait until player is close enough and there are no obstacles in the way.
            u8 shouldWait = thisx->xzDistToPlayer > 500.0 || ABS(thisx->yDistToPlayer) > 50.0 ||
                            BgCheck_EntityLineTest1(&gGlobalContext->colCtx, &this->base.world.pos, &targetPos,
                                                    &posResult, &outPoly, TRUE, FALSE, FALSE, TRUE, &bgId);
            this->waitCounter = shouldWait ? 10 : 0;
        } else if (this->actionFunc == EnYukabyun_Levitate) {
            Math_SmoothStepToF(&thisx->world.pos.y, targetPos.y, 3, 3.0, 0);
        }
    }

    EnYukabyun_Update(thisx, globalCtx);
}
