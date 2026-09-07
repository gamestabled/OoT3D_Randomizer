#include "forest_temple_objects.h"
#include "settings.h"
#include "enemizer.h"

/*-------------------------------
|          BgMoriBigst          |
-------------------------------*/

// The 3 Stalfos are represented by entries 0xFD, 0xFE, 0xFF
#define DYNAMIC_ENTRY(x) (0xFD + x)

static s32 sRealClearFlags;

static void ForestStalfosFight_ReplaceSpawnedEnemy(BgMoriBigst* this, Actor* stalfos, s32 stalfosIdx);
static void ForestStalfosFight_OverrideDynapoly(void);

void BgMoriBigst_Update(Actor* thisx, GlobalContext* globalCtx);

void BgMoriBigst_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    BgMoriBigst* this     = (BgMoriBigst*)thisx;
    Actor* prevFirstEnemy = globalCtx->actorCtx.actorList[ACTORTYPE_ENEMY].first;

    BgMoriBigst_Update(thisx, globalCtx);

    Actor* curFirstEnemy = globalCtx->actorCtx.actorList[ACTORTYPE_ENEMY].first;

    if (gSettingsContext.enemizer) {
        if (curFirstEnemy != prevFirstEnemy) {
            if (this->activeStalfosCount == 1) {
                // spawned first stalfos
                ForestStalfosFight_OverrideDynapoly();
                ForestStalfosFight_ReplaceSpawnedEnemy(this, curFirstEnemy, 0);
            } else if (this->activeStalfosCount == 2) {
                // spawned stalfos pair
                ForestStalfosFight_ReplaceSpawnedEnemy(this, curFirstEnemy->next, 1);
                ForestStalfosFight_ReplaceSpawnedEnemy(this, curFirstEnemy, 2);
            }
        }

        // Advance phase when there are no more enemies left
        if (gGlobalContext->actorCtx.actorList[ACTORTYPE_ENEMY].first == NULL) {
            this->activeStalfosCount = 0;
        }
    }
}

Bool ForestStalfosFight_BeforeActorUpdate(Actor* actor) {
    if ( // is fighting randomized upper Stalfos in Forest Temple...
        gSettingsContext.enemizer && gGlobalContext->sceneNum == SCENE_FOREST_TEMPLE && gGlobalContext->roomNum == 6 &&
        gSaveContext.respawn[RESPAWN_MODE_DOWN].pos.y > 700.0f &&
        // ...and this actor is for an enemy.
        (actor->type == ACTORTYPE_ENEMY || actor->id == ACTOR_ANUBIS_SPAWNER || actor->id == ACTOR_HINT_DEKU_SCRUB)) {

        // Prevent randomized enemies from falling down the hole.
        ForestStalfosFight_OverrideDynapoly();
        // Override clear flag to allow spawning enemies (e.g. Biri from Bari).
        sRealClearFlags                      = gGlobalContext->actorCtx.flags.clear;
        gGlobalContext->actorCtx.flags.clear = 0;
        return TRUE;
    }
    return FALSE;
}

void ForestStalfosFight_AfterActorUpdate(Actor* actor) {
    // Restore dynapoly.
    DynaPoly_UpdateContext(gGlobalContext, &gGlobalContext->colCtx.dyna);
    // Restore clear flag.
    gGlobalContext->actorCtx.flags.clear = sRealClearFlags;
}

static void ForestStalfosFight_ReplaceSpawnedEnemy(BgMoriBigst* this, Actor* stalfos, s32 stalfosIdx) {
    EnemyOverride enemyOverride = Enemizer_FindOverride(SCENE_FOREST_TEMPLE, 0, 6, DYNAMIC_ENTRY(stalfosIdx));

    if (enemyOverride.enemyId != ENEMY_INVALID) {
        // Remove spawned stalfos to replace it.
        Actor_Kill(stalfos);

        ActorEntry tempActorEntry = {
            .id = gEnemyTable[enemyOverride.enemyId].actorId,
            .pos = {
                .x = stalfos->world.pos.x,
                .y = stalfos->world.pos.y,
                .z = stalfos->world.pos.z,
            },
            .rot = {
                .x = 0,
                .y = stalfos->yawTowardsPlayer,
                .z = 0,
            },
            .params = gEnemyTable[enemyOverride.enemyId].possibleParams[enemyOverride.paramsIdx],
        };

        // Apply position updates depending on the specific enemy.
        Enemizer_MoveSpecificEnemies(&tempActorEntry);

        // Override clear flag to spawn enemy.
        s32 realClearFlags                   = gGlobalContext->actorCtx.flags.clear;
        gGlobalContext->actorCtx.flags.clear = 0;
        Actor_Spawn(&gGlobalContext->actorCtx, gGlobalContext, tempActorEntry.id, tempActorEntry.pos.x,
                    tempActorEntry.pos.y, tempActorEntry.pos.z, tempActorEntry.rot.x, tempActorEntry.rot.y,
                    tempActorEntry.rot.z, tempActorEntry.params, TRUE);
        gGlobalContext->actorCtx.flags.clear = realClearFlags;
    }
}

// Override dynapoly to cover the central hole in the floor, so randomized enemies won't fall down.
static void ForestStalfosFight_OverrideDynapoly(void) {
    BgMoriBigst* this = (BgMoriBigst*)Actor_Find(&gGlobalContext->actorCtx, ACTOR_FOREST_BIG_STONE, ACTORTYPE_BG);
    if (this == NULL || this->dyna.actor.world.pos.y < 900) {
        // Do nothing if the platform is already lowered.
        return;
    }
    DynaCollisionContext* dynaCtx = &gGlobalContext->colCtx.dyna;
    s32 bgId                      = this->dyna.bgId;
    f32 realPosY                  = this->dyna.actor.world.pos.y;
    this->dyna.actor.world.pos.y  = this->dyna.actor.home.pos.y;
    DynaPoly_UpdateContext(gGlobalContext, &gGlobalContext->colCtx.dyna);
    dynaCtx->bgActors[bgId].prevTransform = dynaCtx->bgActors[bgId].curTransform;
    this->dyna.actor.world.pos.y          = realPosY;
}
