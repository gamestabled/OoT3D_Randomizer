#include "flare_dancer.h"
#include "settings.h"

#define EnFd_Update ((ActorFunc)GAME_ADDR(0x1B004C))

#define EnFd_Reappear ((EnFdActionFunc)GAME_ADDR(0x117D98))
#define EnFd_JumpToGround ((EnFdActionFunc)GAME_ADDR(0x3ACD84))

#define EnFdFire_Disappear ((EnFdFireActionFunc)GAME_ADDR(0x3ABFB8))

void EnFd_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnFd* this = (EnFd*)thisx;

    Actor* prevEnemiesHead = globalCtx->actorCtx.actorList[ACTORTYPE_ENEMY].first;

    EnFd_Update(thisx, globalCtx);

    if (gSettingsContext.enemizer == ON) {
        // After Flare Dancer spawns flames, quench the ones spawned previously to reduce lag and memory usage.
        Actor* enemy = globalCtx->actorCtx.actorList[ACTORTYPE_ENEMY].first;
        if (enemy != prevEnemiesHead) {
            enemy = prevEnemiesHead;
            while (enemy != NULL) {
                if (enemy->id == ACTOR_FLARE_DANCER_FLAME) {
                    ((EnFdFire*)enemy)->actionFunc = EnFdFire_Disappear;
                }
                enemy = enemy->next;
            }
        }

        Actor_UpdateBgCheckInfo(globalCtx, thisx, 26.0f, 6.0f, 0.0f, UPDBGCHECKINFO_WALL);

        if (this->actionFunc == EnFd_JumpToGround && thisx->bgCheckFlags & BGCHECKFLAG_WALL) {
            // Prevent Flare Dancer from going through walls when jumping off.
            thisx->world.pos.x = thisx->prevPos.x;
            thisx->world.pos.z = thisx->prevPos.z;
        }

        CollisionPoly floorPoly;
        Vec3f actorPos = (Vec3f){
            .x = thisx->world.pos.x,
            .y = thisx->world.pos.y + 10,
            .z = thisx->world.pos.z,
        };
        f32 yGroundIntersect    = BgCheck_RaycastDown1(&gGlobalContext->colCtx, &floorPoly, &actorPos);
        SurfaceType surfaceType = gGlobalContext->colCtx.stat.colHeader->surfaceTypeList[floorPoly.type];
        u8 isInvalidGround = yGroundIntersect <= BGCHECK_Y_MIN || SurfaceType_IsLoadingZoneOrVoidPlane(surfaceType);

        if (isInvalidGround && thisx->world.pos.y < thisx->home.pos.y - 200.0) {
            // If Flare Dancer falls out of bounds, make it respawn at its home.
            this->actionFunc = EnFd_Reappear;
        }
    }
}
