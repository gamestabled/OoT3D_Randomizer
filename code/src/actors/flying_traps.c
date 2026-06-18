#include "z3D/z3D.h"
#include "flying_traps.h"
#include "enemy_souls.h"
#include "settings.h"
#include "enemizer.h"
#include "objects.h"

/*-------------------------------
|           EnTuboTrap          |
-------------------------------*/

void EnTuboTrap_Draw(Actor* thisx, GlobalContext* globalCtx);
void EnTuboTrap_WaitForProximity(EnTuboTrap* this, GlobalContext* globalCtx);

s32 EnTuboTrap_OnImpact(EnTuboTrap* this) {
    if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) { // Standing on the ground
        this->actionFunc    = EnTuboTrap_WaitForProximity;
        this->actor.gravity = 0;
        this->actor.speedXZ = 0;
        this->actor.flags &= ~ACTOR_FLAG_ATTENTION_ENABLED;
    }

    return !EnemySouls_IsInvulnerable(&this->actor);
}

static void EnTuboTrap_ReinitModels(EnTuboTrap* this) {
    Actor_DestroySkelModels(&this->actor, &this->saModel, NULL);
    Actor_CreateSkelModels(&this->actor, gGlobalContext, &this->saModel, POT_CMB_INDEX, NULL);
}

void EnTuboTrap_rDraw(Actor* thisx, GlobalContext* globalCtx) {
    EnTuboTrap* this = (EnTuboTrap*)thisx;
    if (SoullessModels_Enabled && EnemySouls_ShouldDrawSoulless(thisx) && !this->rExt.usingModifiedModel) {
        // Modify CMB data and reinit model.
        ObjectEntry* obj = Object_FindEntry(OBJECT_GAMEPLAY_DUNGEON_KEEP);
        SoullessModels_ModifyGenericCmb(obj->zarInfo.cmbMans[POT_CMB_INDEX]);
        EnTuboTrap_ReinitModels(this);
        // Request restoring the CMB so other pots will draw normally when spawning (e.g. when another room is loaded).
        SoullessModels_CmbRestoreRequest = TRUE;
        this->rExt.usingModifiedModel    = TRUE;
    } else if (!EnemySouls_ShouldDrawSoulless(thisx) && this->rExt.usingModifiedModel) {
        // Reinit model with the normal data in the CMB, so it will look normal again.
        EnTuboTrap_ReinitModels(this);
        this->rExt.usingModifiedModel = FALSE;
    }

    EnTuboTrap_Draw(thisx, globalCtx);
}

/*-------------------------------
|           EnYukabyun          |
-------------------------------*/

void EnYukabyun_Update(Actor* thisx, GlobalContext* globalCtx);
void EnYukabyun_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnYukabyun_Levitate(EnYukabyun* this, GlobalContext* globalCtx);
void EnYukabyun_Wait(EnYukabyun* this, GlobalContext* globalCtx);

s32 EnYukabyun_OnImpact(EnYukabyun* this) {
    if (EnemySouls_IsInvulnerable(&this->actor)) {
        this->actionFunc  = EnYukabyun_Levitate;
        this->waitCounter = 0;
        this->actor.flags |= 0b101; // keep targetable and hostile flags
        return 0;
    }
    return 1;
}

static void EnYukabyun_ReinitModels(EnYukabyun* this) {
    Actor_DestroySkelModels(&this->actor, &this->saModel, NULL);
    Actor_CreateSkelModels(&this->actor, gGlobalContext, &this->saModel, FLYING_TILE_CMB_INDEX, NULL);
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
                            BgCheck_EntityLineTest1(&gGlobalContext->colCtx, &this->actor.world.pos, &targetPos,
                                                    &posResult, &outPoly, TRUE, FALSE, FALSE, TRUE, &bgId);
            this->waitCounter = shouldWait ? 10 : 0;
        } else if (this->actionFunc == EnYukabyun_Levitate) {
            Math_SmoothStepToF(&thisx->world.pos.y, targetPos.y, 3, 3.0, 0);
        }
    }

    EnYukabyun_Update(thisx, globalCtx);
}

void EnYukabyun_rDraw(Actor* thisx, GlobalContext* globalCtx) {
    EnYukabyun* this = (EnYukabyun*)thisx;

    if (SoullessModels_Enabled && EnemySouls_ShouldDrawSoulless(thisx) && !this->rExt.usingModifiedModel) {
        // Modify CMB data and reinit model.
        ObjectEntry* obj = Object_FindEntry(OBJECT_FLYING_FLOOR_TILE);
        SoullessModels_ModifyGenericCmb(obj->zarInfo.cmbMans[FLYING_TILE_CMB_INDEX]);
        EnYukabyun_ReinitModels(this);
        SoullessModels_CmbRestoreRequest = TRUE;
        this->rExt.usingModifiedModel    = TRUE;
    } else if (!EnemySouls_ShouldDrawSoulless(thisx) && this->rExt.usingModifiedModel) {
        // Reinit model with the normal data in the CMB, so it will look normal again.
        EnYukabyun_ReinitModels(this);
        this->rExt.usingModifiedModel = FALSE;
    }

    EnYukabyun_Draw(thisx, globalCtx);
}

/*-------------------------------
|            Generic            |
-------------------------------*/

u8 FlyingTraps_IsHiddenTrap(Actor* actor) {
    switch (actor->id) {
        case ACTOR_FLYING_FLOOR_TILE:
            return ((EnYukabyun*)actor)->actionFunc == EnYukabyun_Wait;
        case ACTOR_FLYING_POT:
            return ((EnTuboTrap*)actor)->actionFunc == EnTuboTrap_WaitForProximity;
        default:
            return FALSE;
    }
}
