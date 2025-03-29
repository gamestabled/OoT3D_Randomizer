#include "dark_link.h"
#include "settings.h"
#include "enemizer.h"

#define EnTorch2_Update ((ActorFunc)GAME_ADDR(0x22F0C8))

void EnTorch2_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnTorch2* this = (EnTorch2*)thisx;

    s32 prevFloorType = sFloorType;

    if (gSettingsContext.enemizer == ON) {
        // Skip adjusting position after spawning.
        this->darkPlayer.darkLinkAdjustedSpawnPos = 1;
    }

    EnTorch2_Update(thisx, globalCtx);

    if (gSettingsContext.enemizer == ON) {
        // Restore sFloorType because Dark Link calls Player functions that can modify its value.
        // Without this, things like slippery floors could apply to Link depending on where Dark Link is standing.
        sFloorType = prevFloorType;

        // This value is only used to determine the respawn height after being damaged.
        thisx->floorHeight = PLAYER->actor.floorHeight;

        switch (this->actionState) {
            case ENTORCH2_WAIT:
                // Avoid triggering fall damage effect when spawning in certain locations.
                this->darkPlayer.fallStartHeight = thisx->world.pos.y;
                break;
            case ENTORCH2_ATTACK:
                CollisionPoly floorPoly;
                Vec3f actorPos = (Vec3f){
                    .x = thisx->world.pos.x,
                    .y = thisx->world.pos.y + 10,
                    .z = thisx->world.pos.z,
                };
                f32 yGroundIntersect    = BgCheck_RaycastDown1(&globalCtx->colCtx, &floorPoly, &actorPos);
                SurfaceType surfaceType = globalCtx->colCtx.stat.colHeader->surfaceTypeList[floorPoly.type];
                Actor_UpdateBgCheckInfo(globalCtx, thisx, 0.0f, 0.0f, 0.0f, UPDBGCHECKINFO_FLOOR_WATER);
                u8 isAboveVoidPlane =
                    yGroundIntersect > BGCHECK_Y_MIN && SurfaceType_IsLoadingZoneOrVoidPlane(surfaceType);
                u8 isOnGround  = (thisx->bgCheckFlags & BGCHECKFLAG_GROUND) != 0;
                u8 isBelowLink = PLAYER->actor.world.pos.y - this->darkPlayer.actor.world.pos.y > 500.0;

                // Teleport behind player when falling out of bounds or touching a void plane.
                if ((!isAboveVoidPlane && isBelowLink) || (isAboveVoidPlane && isOnGround)) {
                    this->darkPlayer.actor.world.pos.y = PLAYER->actor.world.pos.y + 40.0f;
                    this->darkPlayer.actor.world.pos.x =
                        (Math_SinS(PLAYER->actor.shape.rot.y) * -120.0f) + PLAYER->actor.world.pos.x;
                    this->darkPlayer.actor.world.pos.z =
                        (Math_CosS(PLAYER->actor.shape.rot.y) * -120.0f) + PLAYER->actor.world.pos.z;

                    this->darkPlayer.actor.home.pos = this->darkPlayer.actor.world.pos;
                }
                break;
            case ENTORCH2_DAMAGE:
                // Ignore water if damaged while swimming.
                thisx->depthInWater = -1.0;
                break;
        }
    }
}

void DarkLink_OverrideSpawnedActor(s16* actorId, s16* params, f32* posZ) {
    if (gSettingsContext.enemizer == OFF) {
        return;
    }

    EnemyOverride enemyOverride = Enemizer_GetSpawnerOverride();

    if (enemyOverride.actorId == 0) {
        return;
    }

    if (actorId != NULL) {
        *actorId = enemyOverride.actorId;
    }
    if (params != NULL) {
        *params = enemyOverride.params;
    }
    if (posZ != NULL) {
        *posZ -= 75.0; // Move enemy outside of the tree.
    }
}
