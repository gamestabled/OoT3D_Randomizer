#include "bubble.h"
#include "enemizer.h"
#include "enemy_souls.h"
#include "settings.h"
#include "actor.h"

void EnBb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBb_Destroy(Actor* thisx, GlobalContext* globalCtx);

enum FlameMatAnim {
    FLAMEMATANIM_RED   = 0xB,
    FLAMEMATANIM_GREEN = 0xC,
    FLAMEMATANIM_BLUE  = 0xD,
    FLAMEMATANIM_BLACK = 0xE,
};

static EnBbType Bubble_GetType(EnBb* bubble) {
    const s16 params = bubble->actor.params;
    if (params == 0) {
        return ENBB_FLAME_TRAIL;
    }
    return params | 0xFF00;
}

static void Bubble_CallActorFunc(ActorFunc actorFunc, Actor* thisx, GlobalContext* globalCtx) {
    EnBb* this         = (EnBb*)thisx;
    Path* realPathList = globalCtx->pathList;

    // For randomized Bubbles that expect a Path object from the current scene data, create a simple temporary Path
    // based on the Bubble's initial position, with 2 waypoints on a vertical line.
    if ((Bubble_GetType(this) == ENBB_WHITE && Enemizer_IsEnemyRandomized(ENEMY_BUBBLE_WHITE)) ||
        (Bubble_GetType(this) == ENBB_GREEN_BIG && Enemizer_IsEnemyRandomized(ENEMY_BUBBLE_GREEN))) {
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
    EnBb* this = (EnBb*)thisx;

    Bubble_CallActorFunc(EnBb_Init, thisx, globalCtx);

    if (SoullessModels_Enabled && EnemySouls_IsInvulnerable(thisx)) {
        FlameModel_Destroy(&this->flameModel_1);
        FlameModel_Init(&this->flameModel_1, globalCtx, 0, FLAMEMATANIM_BLACK);
        if (this->hasSecondFlameModel != 0) {
            FlameModel_Destroy(&this->flameModel_2);
            FlameModel_Init(&this->flameModel_2, globalCtx, 0, FLAMEMATANIM_BLACK);
        }
    }
}

void EnBb_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    Bubble_CallActorFunc(EnBb_Update, thisx, globalCtx);
}

void EnBb_rDestroy(Actor* thisx, GlobalContext* globalCtx) {
    EnBb* this = (EnBb*)thisx;

    EnBb_Destroy(thisx, globalCtx);

    if (Bubble_GetType(this) == ENBB_WHITE) {
        // Fix vanilla bug: White Bubbles never delete their own "blure" effect, causing
        // a memory leak which can lead to a crash if the space for blures is filled up.
        Effect_Delete(globalCtx, this->blureIdx);
    }
}

void EnBb_ReinitModels(EnBb* this) {
    Actor_ReinitSkelAnime(&this->actor, &this->anime, 0);

    s32 cmabIdx = -1;
    switch (Bubble_GetType(this)) {
        case ENBB_BLUE:
            cmabIdx = FLAMEMATANIM_BLUE;
            break;
        case ENBB_GREEN_BIG:
        case ENBB_GREEN:
            cmabIdx = FLAMEMATANIM_GREEN;
            break;
        case ENBB_RED:
        case ENBB_FLAME_TRAIL:
            cmabIdx = FLAMEMATANIM_RED;
            break;
        default:
            break;
    }

    if (cmabIdx >= 0) {
        FlameModel_Destroy(&this->flameModel_1);
        FlameModel_Init(&this->flameModel_1, gGlobalContext, 0, cmabIdx);
        if (this->hasSecondFlameModel != 0) {
            FlameModel_Destroy(&this->flameModel_2);
            FlameModel_Init(&this->flameModel_2, gGlobalContext, 0, cmabIdx);
        }
    }
}
