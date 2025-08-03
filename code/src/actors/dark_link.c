#include "dark_link.h"
#include "settings.h"
#include "enemizer.h"
#include "common.h"

#define EnTorch2_Update ((ActorFunc)GAME_ADDR(0x22F0C8))

u8 sPlayerWeaponClanked = FALSE;

void EnTorch2_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnTorch2* this = (EnTorch2*)thisx;

    s32 prevFloorType = sFloorType;

    // Check the 4 meleeWeaponQuads plus the shieldQuad for bounce collisions
    // to detect if the player's weapon clanked against them.
    ColliderQuad* swordShieldQuads = this->darkPlayer.meleeWeaponQuads;
    for (u32 i = 0; i < 5; i++) {
        if (swordShieldQuads[i].base.acFlags & AC_BOUNCED) {
            sPlayerWeaponClanked = TRUE;
        }
    }

    // For enemy randomizer, skip adjusting position after spawning outside of vanilla location.
    if (globalCtx->sceneNum != SCENE_WATER_TEMPLE || globalCtx->roomNum != 13) {
        this->darkPlayer.darkLinkAdjustedSpawnPos = 1;
    }

    // To decide when the battle should start, vanilla code checks distance to player only on the horizontal plane.
    // If the vertical distance is too high, hack the horizontal one to a high value to make the check fail on
    // this frame.
    if (this->actionState == ENTORCH2_WAIT && ABS(thisx->yDistToPlayer) > 200.0f) {
        thisx->xzDistToPlayer = 1000.0f;
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

    sPlayerWeaponClanked = FALSE;
}

Actor* DarkLink_Spawn(Actor* spawner) {
    ActorEntry tempActorEntry = {
        .id = ACTOR_DARK_LINK,
        .pos = {
            .x = spawner->world.pos.x,
            .y = spawner->world.pos.y,
            .z = spawner->world.pos.z,
        },
        .rot = {
            .x = 0,
            .y = spawner->yawTowardsPlayer,
            .z = 0,
        },
        .params = 0,
    };

    if (gSettingsContext.enemizer == ON) {
        EnemyOverride enemyOverride = Enemizer_GetSpawnerOverride();
        tempActorEntry.id           = enemyOverride.actorId;
        tempActorEntry.params       = enemyOverride.params;
        tempActorEntry.pos.z -= 75; // Move enemy outside of the tree.

        // Apply position updates depending on the specific enemy.
        Enemizer_MoveSpecificEnemies(&tempActorEntry);
    }

    return Actor_Spawn(&gGlobalContext->actorCtx, gGlobalContext, tempActorEntry.id, tempActorEntry.pos.x,
                       tempActorEntry.pos.y, tempActorEntry.pos.z, tempActorEntry.rot.x, tempActorEntry.rot.y,
                       tempActorEntry.rot.z, tempActorEntry.params, TRUE);
}

s32 DarkLink_IsAlive(void) {
    // The randomizer changes Dark Link's actor category to Enemy instead of Boss,
    // so the temp clear flag will be set when he's defeated.
    return !Enemizer_IsRoomCleared();
}

// Vanilla code removes hammer recoil for both Links.
// Avoid this when not hitting Dark Link so that Hammer Slides can still work.
u8 DarkLink_ShouldOverridePlayerRecoilSpeed(void) {
    return sPlayerWeaponClanked;
}
