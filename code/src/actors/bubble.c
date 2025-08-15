#include "bubble.h"
#include "enemizer.h"
#include "common.h"

#define EnBb_Init ((ActorFunc)GAME_ADDR(0x162328))
#define EnBb_Update ((ActorFunc)GAME_ADDR(0x1005ec))

#define Bubble_GetType(actor) ((s16)(thisx->params | 0xFF00))

static void Bubble_CallActorFunc(ActorFunc actorFunc, Actor* thisx, GlobalContext* globalCtx) {
    EnBb* this         = (EnBb*)thisx;
    Path* realPathList = globalCtx->pathList;

    // For randomized Bubbles that expect a Path object from the current scene data, create a simple temporary Path
    // based on the Bubble's initial position, with 2 waypoints on a vertical line.
    if ((Bubble_GetType(thisx) == ENBB_WHITE && Enemizer_IsEnemyRandomized(ENEMY_BUBBLE_WHITE)) ||
        (Bubble_GetType(thisx) == ENBB_GREEN_BIG && Enemizer_IsEnemyRandomized(ENEMY_BUBBLE_GREEN))) {
        // Take the horizontal coordinates from the Bubble's `world` pos, so they will be updated if
        // the actor is pushed by something (e.g. wall collisions).
        // Use the `home` pos to select the vertical coordinates, so they won't change while the actor moves.
        Vec3f checkPos = {
            .x = thisx->world.pos.x,
            .y = thisx->home.pos.y + 50,
            .z = thisx->world.pos.z,
        };
        // Check floor position under the Bubble.
        CollisionPoly floorPoly;
        f32 yGroundIntersect = BgCheck_RaycastDown1(&gGlobalContext->colCtx, &floorPoly, &checkPos);
        // Check water surface position.
        f32 yWaterSurface;
        void* waterBox;
        s32 waterBoxFound = WaterBox_GetSurfaceImpl(gGlobalContext, &gGlobalContext->colCtx, checkPos.x, checkPos.z,
                                                    &yWaterSurface, &waterBox);

        f32 lowY;
        if (waterBoxFound && yWaterSurface < thisx->home.pos.y + 20 && yWaterSurface > yGroundIntersect) {
            lowY = yWaterSurface;
        } else if (yGroundIntersect <= BGCHECK_Y_MIN) {
            lowY = thisx->home.pos.y - 100;
        } else {
            lowY = yGroundIntersect + 50;
        }

        f32 highY = MAX(thisx->home.pos.y, lowY + 150);

        Vec3s tempPoints[2] = {
            {
                .x = thisx->world.pos.x,
                .y = lowY,
                .z = thisx->world.pos.z,
            },
            {
                .x = thisx->world.pos.x,
                .y = highY,
                .z = thisx->world.pos.z,
            },
        };

        // Update current waypoint position stored in the Bubble's data.
        this->waypointPos = (Vec3f){
            .x = tempPoints[this->waypoint].x,
            .y = tempPoints[this->waypoint].y,
            .z = tempPoints[this->waypoint].z,
        };

        Path tempPath       = { .count = 2, .points = tempPoints };
        globalCtx->pathList = &tempPath;
    }

    actorFunc(thisx, globalCtx);

    globalCtx->pathList = realPathList;
}

void EnBb_rInit(Actor* thisx, GlobalContext* globalCtx) {
    Bubble_CallActorFunc(EnBb_Init, thisx, globalCtx);
}

void EnBb_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    Bubble_CallActorFunc(EnBb_Update, thisx, globalCtx);
}
