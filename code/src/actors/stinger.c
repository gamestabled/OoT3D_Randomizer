#include "stinger.h"
#include "settings.h"
#include "enemizer.h"
#include "common.h"

void EnEiyer_Update(Actor* thisx, GlobalContext* globalCtx);

void EnEiyer_WanderUnderground(EnEiyer* this, GlobalContext* globalCtx);

void EnEiyer_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnEiyer* this = (EnEiyer*)thisx;

    EnEiyer_Update(thisx, globalCtx);

    if (Enemizer_IsEnemyRandomized(ENEMY_STINGER_FLOOR) && this->actionFunc == EnEiyer_WanderUnderground) {
        // Make Stinger detect collision when wandering underground.
        Actor_UpdateBgCheckInfo(globalCtx, thisx, 5.0f, 27.0f, 30.0f,
                                UPDBGCHECKINFO_WALL | UPDBGCHECKINFO_CEILING | UPDBGCHECKINFO_FLOOR_WATER);

        CollisionPoly floorPoly;
        Vec3f actorPos = (Vec3f){
            .x = thisx->world.pos.x,
            .y = thisx->world.pos.y + 30,
            .z = thisx->world.pos.z,
        };
        f32 yGroundIntersect = BgCheck_RaycastDown1(&gGlobalContext->colCtx, &floorPoly, &actorPos);

        // Snap to ground level if close enough, otherwise undo movement to avoid hovering or falling off platforms.
        if (ABS(thisx->world.pos.y - yGroundIntersect) < 10) {
            thisx->world.pos.y = yGroundIntersect;
        } else {
            thisx->world.pos = thisx->prevPos;
        }
    }
}
