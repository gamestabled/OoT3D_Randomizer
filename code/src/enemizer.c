#include "enemizer.h"
#include "objects.h"
#include "common.h"
#include "savefile.h"
#include "settings.h"
#include "scene.h"
#include "bgm.h"
#include "dark_link.h"
#include "z3D/actors/z_en_item00.h"

#include <stddef.h>

#define SKIP_ACTOR_ENTRY TRUE
#define KEEP_ACTOR_ENTRY FALSE

static EnemyOverride rEnemyOverrides[ENEMY_OVERRIDES_MAX];
static s32 rEnemyOverrides_Count = 0;
static u8 sRoomLoadSignal        = FALSE;
static Actor* sSFMWolfos         = NULL;
static u8 sLastRoomCleared       = FALSE;
EnemizerLocationFlags gEnemizerLocationFlags;

static EnemyOverride Enemizer_FindOverride(u8 scene, u8 layer, u8 room, u8 actorEntry);

// Enemies that need to spawn at ground level to work properly.
static EnemyActorData sGroundedEnemies[] = {
    { .actorId = ACTOR_STALFOS, .actorParams = 0x0002 }, // Rises from ground
    { .actorId = ACTOR_DODONGO, .anyParams = TRUE },
    { .actorId = ACTOR_LEEVER, .anyParams = TRUE },
    { .actorId = ACTOR_GOHMA_LARVA, .actorParams = 0x0007 }, // Stationary egg
    { .actorId = ACTOR_BABY_DODONGO, .anyParams = TRUE },
    { .actorId = ACTOR_DARK_LINK, .anyParams = TRUE },
    { .actorId = ACTOR_TAILPASARAN, .anyParams = TRUE },
    { .actorId = ACTOR_STINGER_FLOOR, .anyParams = TRUE },
    { .actorId = ACTOR_DEKU_BABA, .anyParams = TRUE },
    { .actorId = ACTOR_MAD_SCRUB, .anyParams = TRUE },
    { .actorId = ACTOR_BUBBLE, .actorParams = 0xFFFE }, // Fire Bubble
    { .actorId = ACTOR_FLYING_FLOOR_TILE, .anyParams = TRUE },
    { .actorId = ACTOR_BEAMOS, .anyParams = TRUE },
    { .actorId = ACTOR_REDEAD, .anyParams = TRUE },
    { .actorId = ACTOR_SKULLWALLTULA, .anyParams = TRUE },
    { .actorId = ACTOR_DEAD_HAND_HAND, .anyParams = TRUE },
    { .actorId = ACTOR_WITHERED_DEKU_BABA, .anyParams = TRUE },
    { .actorId = ACTOR_ANUBIS_SPAWNER, .anyParams = TRUE },
    { .actorId = ACTOR_FLYING_POT, .anyParams = TRUE },
    { .actorId = ACTOR_HINT_DEKU_SCRUB, .anyParams = TRUE },
    { .actorId = ACTOR_STALCHILD, .anyParams = TRUE },
};

// clang-format off
static EnemyObjectDependency sEnemyObjectDeps[] = {
    {
        // Poe (actor profile only points to object 1)
        .key      = { .actorId = ACTOR_POE, .actorParams = 0x0000 },
        .objectId = 0x009,
    },
    {
        // Sharp (Composer Brother)
        .key      = { .actorId = ACTOR_POE, .actorParams = 0x0002 },
        .objectId = 0x06E,
    },
    {
        // Flat (Composer Brother)
        .key      = { .actorId = ACTOR_POE, .actorParams = 0x0003 },
        .objectId = 0x06E,
    },
    {
        // Bari -> Biri
        .key      = { .actorId = ACTOR_BARI, .anyParams = TRUE },
        .objectId = 0x021,
    },
    {
        // Dodongo -> dungeon object for fire breath
        .key      = { .actorId = ACTOR_DODONGO, .anyParams = TRUE },
        .objectId = 0x003,
    },
    {
        // Gohma Egg -> dungeon object for egg fragments
        .key      = { .actorId = ACTOR_GOHMA_LARVA, .anyParams = TRUE },
        .objectId = 0x003,
    },
    {
        // Flare Dancer -> dungeon object for flames
        .key      = { .actorId = ACTOR_FLARE_DANCER, .anyParams = TRUE },
        .objectId = 0x003,
    },
    {
        // Like Like -> Deku Shield object
        .key      = { .actorId = ACTOR_LIKE_LIKE, .anyParams = TRUE },
        .objectId = 0x0CB,
    },
    {
        // Like Like -> Hylian Shield object
        .key      = { .actorId = ACTOR_LIKE_LIKE, .anyParams = TRUE },
        .objectId = 0x0DC,
    },
    {
        // Anubis Spawner -> Anubis object (actor profile only points to object 1)
        .key      = { .actorId = ACTOR_ANUBIS_SPAWNER, .anyParams = TRUE },
        .objectId = 0x0D6,
    },
};
// clang-format on

u8 Enemizer_IsEnemyRandomized(EnemyId enemyId) {
    return gSettingsContext.enemizer == ON && gSettingsContext.enemizerList[enemyId] == ENEMYMODE_RANDOMIZED;
}

void Enemizer_Init(void) {
    if (gSettingsContext.enemizer == OFF) {
        return;
    }

    while (rEnemyOverrides[rEnemyOverrides_Count].actorId != 0) {
        rEnemyOverrides_Count++;
    }

    // Initialize flags for specific location overrides.
    // For groups of enemies with the same location type, just check one of them.
    gEnemizerLocationFlags.sfmWolfos      = Enemizer_FindOverride(86, 0, 0, 1).actorId != 0;
    gEnemizerLocationFlags.dcLizalfos     = Enemizer_FindOverride(1, 0, 3, 1).actorId != 0; // both Vanilla and MQ
    gEnemizerLocationFlags.gerudoFighters = Enemizer_FindOverride(12, 0, 1, 1).actorId != 0;
    gEnemizerLocationFlags.nabooruKnuckle = Enemizer_FindOverride(23, 0, 1, 0).actorId != 0;
    gEnemizerLocationFlags.shadowShipStalfos =
        Enemizer_FindOverride(7, 0, 21, gSettingsContext.shadowTempleDungeonMode == DUNGEONMODE_VANILLA ? 13 : 16)
            .actorId != 0;
}

static EnemyOverride Enemizer_FindOverride(u8 scene, u8 layer, u8 room, u8 actorEntry) {
    s32 key   = (scene << 24) | (layer << 16) | (room << 8) | actorEntry;
    s32 start = 0;
    s32 end   = rEnemyOverrides_Count - 1;
    while (start <= end) {
        s32 midIdx           = (start + end) / 2;
        EnemyOverride midOvr = rEnemyOverrides[midIdx];
        if (key < midOvr.key) {
            end = midIdx - 1;
        } else if (key > midOvr.key) {
            start = midIdx + 1;
        } else {
            return midOvr;
        }
    }
    return (EnemyOverride){ 0 };
}

// Helper macro for the function below. Optionally specify dungeon mode as fifth argument.
#define LOC(scene, layer, room, entry, ...) \
    (__VA_OPT__((((u64)__VA_ARGS__) << 32) |)(scene << 24) | (layer << 16) | (room << 8) | entry)

static void Enemizer_MoveSpecificLocations(ActorEntry* actorEntry, s32 actorEntryIndex) {
    u32 dungeonModeId = (gGlobalContext->sceneNum == SCENE_INSIDE_GANONS_CASTLE ? 10 : gGlobalContext->sceneNum);

    u64 isMQ = dungeonModeId < ARRAY_SIZE(gSettingsContext.dungeonModes) &&
               gSettingsContext.dungeonModes[dungeonModeId] == DUNGEONMODE_MQ;

    u64 thisLocation = LOC(gGlobalContext->sceneNum, rSceneLayer, gGlobalContext->roomNum, actorEntryIndex, isMQ);

    switch (thisLocation) {
        case LOC(2, 0, 11, 5, DUNGEONMODE_MQ):
            // Move the left like like in the room in MQ jabu to just spawn on the ground
            actorEntry->pos.x = 827;
            actorEntry->pos.y = -300;
            break;
        case LOC(2, 0, 11, 6, DUNGEONMODE_MQ):
            // Move the right like like in the room in MQ jabu to just spawn on the ground
            actorEntry->pos.x = 488;
            actorEntry->pos.y = -300;
            break;
        case LOC(3, 0, 19, 0, DUNGEONMODE_VANILLA):
        case LOC(3, 0, 19, 0, DUNGEONMODE_MQ):
        case LOC(3, 0, 20, 2, DUNGEONMODE_VANILLA):
        case LOC(3, 0, 20, 2, DUNGEONMODE_MQ):
            // Move the wallmasters in the Forest Temple twisted hallways down to the center of the room.
            // These locations should still be restricted to flying enemies because of how the room rotates
            // as the player approaches.
            actorEntry->pos.y = 1278;
            break;
        case LOC(6, 0, 2, 6, DUNGEONMODE_VANILLA):
            // Move the wallmaster in spirit child side out of the wall
            actorEntry->pos.z = -1400;
            break;
        case LOC(6, 0, 3, 0, DUNGEONMODE_VANILLA):
            // Move a green bubble in spirit child side out of the pit
            actorEntry->pos.y = 80;
            break;
        case LOC(6, 0, 4, 0, DUNGEONMODE_VANILLA):
            // Move a skullwalltula in spirit child side out of the wall
            actorEntry->pos.x = -1150;
            break;
        case LOC(6, 0, 4, 1, DUNGEONMODE_VANILLA):
            // Move a skullwalltula in spirit child side out of the wall
            actorEntry->pos.x = -1150;
            break;
        case LOC(6, 0, 3, 3, DUNGEONMODE_MQ):
            // Move a keese in spirit child side out of the wall
            actorEntry->pos.x = -1720;
            actorEntry->pos.z = -570;
            break;
        case LOC(6, 0, 12, 0, DUNGEONMODE_VANILLA):
            // Move a like-like in adult spirit down within the room
            actorEntry->pos.y = 80;
            break;
        case LOC(6, 0, 15, 2, DUNGEONMODE_VANILLA):
            // Move a like-like in adult spirit down within the room
            actorEntry->pos.y = 190;
            break;
        case LOC(6, 0, 26, 2, DUNGEONMODE_VANILLA):
            // Move a white bubble in spirit inside the room
            actorEntry->pos.x = -415;
            actorEntry->pos.z = -440;
            break;
        case LOC(6, 0, 27, 7, DUNGEONMODE_MQ):
            // Move the stalfos in MQ Child spirit down onto the platform
            actorEntry->pos.y = 50;
            break;
        case LOC(7, 0, 8, 0, DUNGEONMODE_VANILLA):
            // Move a skulltula in shadow temple corridor down inside the room
            actorEntry->pos.y = -500;
            break;
        case LOC(7, 0, 8, 1, DUNGEONMODE_VANILLA):
            // Move a skulltula in shadow temple corridor down inside the room
            actorEntry->pos.y = -600;
            break;
        case LOC(7, 0, 8, 2, DUNGEONMODE_VANILLA):
            // Move a skulltula in shadow temple corridor down inside the room
            actorEntry->pos.y = -700;
            break;
        case LOC(7, 0, 8, 3, DUNGEONMODE_VANILLA):
        case LOC(7, 0, 8, 1, DUNGEONMODE_MQ):
            // Move a skulltula in shadow temple corridor down inside the room
            actorEntry->pos.y = -750;
            break;
        case LOC(7, 0, 9, 1, DUNGEONMODE_VANILLA):
        case LOC(7, 0, 9, 5, DUNGEONMODE_MQ):
            // Raise the fire bubble in the shadow temple cavern if it is not vanilla
            if (actorEntry->id != ACTOR_BUBBLE || actorEntry->params != 0xFFFE) {
                actorEntry->pos.y = -1080;
            }
            break;
        case LOC(7, 0, 9, 2, DUNGEONMODE_VANILLA):
            // Move the wallmaster in shadow temple cavern down inside the room
            actorEntry->pos.y = -870;
            break;
        case LOC(7, 0, 21, 13, DUNGEONMODE_VANILLA):
        case LOC(7, 0, 21, 16, DUNGEONMODE_MQ):
            // Move one shadow temple boat stalfos over to the end platform
            actorEntry->pos.x = -2300;
            actorEntry->pos.y = -1360;
            actorEntry->pos.z = -1570;
            break;
        case LOC(7, 0, 21, 14, DUNGEONMODE_VANILLA):
        case LOC(7, 0, 21, 17, DUNGEONMODE_MQ):
            // Move the other shadow temple boat stalfos over to the end platform
            actorEntry->pos.x = -2700;
            actorEntry->pos.y = -1360;
            actorEntry->pos.z = -1570;
            break;
        case LOC(8, 0, 0, 0, DUNGEONMODE_VANILLA):
            // Move a skulltula in BOTW down inside the room
            actorEntry->pos.y = 75;
            break;
        case LOC(8, 0, 0, 4, DUNGEONMODE_VANILLA):
            // Move the wallmaster in the central room of BOTW so it doesn't raycast down into the basement
            actorEntry->pos.z = -950;
            break;
        case LOC(8, 0, 3, 2, DUNGEONMODE_VANILLA):
            // Move a fire keese in the beamos room in BOTW so it doesn't raycast down into the basement
            actorEntry->pos.z = -1075;
            break;
        case LOC(8, 0, 5, 0, DUNGEONMODE_VANILLA):
            // Move a keese in the invisible floor room in BOTW to be over flat ground and not the sloped wall
            actorEntry->pos.x = 250;
            actorEntry->pos.z = -970;
            break;
        case LOC(12, 0, 1, 1):
        case LOC(12, 0, 2, 1):
        case LOC(12, 0, 5, 1):
            // Move Gerudo Fighter down inside the room
            actorEntry->pos.y = 120;
            break;
        case LOC(12, 0, 4, 1):
            // Move Gerudo Fighter down inside the room
            actorEntry->pos.y = -120;
            break;
        case LOC(86, 0, 0, 1):
            // Move the SFM wolfos more towards the center, some enemies might jump over the fence
            actorEntry->pos.x = -195;
            actorEntry->pos.y = 0;
            actorEntry->pos.z = 1900;
            break;
    }
}
#undef LOC

void Enemizer_MoveSpecificEnemies(ActorEntry* actorEntry) {
    f32 yGroundIntersect;
    f32 yUpperGroundIntersect;
    f32 yMidAirPos;
    s32 waterBoxFound;
    f32 yWaterSurface;
    CollisionPoly floorPoly;
    u8 isInvalidGround;
    void* waterBox;
    Vec3f actorPos = (Vec3f){
        .x = actorEntry->pos.x,
        .y = actorEntry->pos.y + 50, // Check for ground even slightly above the actor entry's real position
        .z = actorEntry->pos.z,
    };

    // Ground height below actor.
    yGroundIntersect        = BgCheck_RaycastDown1(&gGlobalContext->colCtx, &floorPoly, &actorPos);
    SurfaceType surfaceType = gGlobalContext->colCtx.stat.colHeader->surfaceTypeList[floorPoly.type];
    isInvalidGround         = yGroundIntersect <= BGCHECK_Y_MIN || SurfaceType_IsLoadingZoneOrVoidPlane(surfaceType);

    Vec3f upperPos = (Vec3f){
        .x = actorEntry->pos.x,
        .y = yGroundIntersect + 200,
        .z = actorEntry->pos.z,
    };
    yUpperGroundIntersect = BgCheck_RaycastDown1(&gGlobalContext->colCtx, &floorPoly, &upperPos);
    // Potential mid-air position to spawn the actor off the ground if needed.
    yMidAirPos = ABS(yUpperGroundIntersect - yGroundIntersect) < 50 ? upperPos.y : yUpperGroundIntersect - 50;

    // Ignore ground checks where the ground is an actor that the raycast fails to detect:
    // - Forest Temple twisted hallways
    // - Fire Temple staircase
    if ((gGlobalContext->sceneNum == SCENE_FOREST_TEMPLE &&
         (gGlobalContext->roomNum == 19 || gGlobalContext->roomNum == 20)) ||
        ((gGlobalContext->sceneNum == SCENE_FIRE_TEMPLE && gGlobalContext->roomNum == 14 &&
          yGroundIntersect < 4150.0))) {
        isInvalidGround = TRUE;
    }

    // If there is a water box, set yWaterSurface.
    waterBoxFound = WaterBox_GetSurfaceImpl(gGlobalContext, &gGlobalContext->colCtx, actorPos.x, actorPos.z,
                                            &yWaterSurface, &waterBox);

    // In Lake Hylia, hardcode yWaterSurface because it might not be correct when the actor entries are spawned.
    if (waterBoxFound && gGlobalContext->sceneNum == SCENE_LAKE_HYLIA) {
        // There are no enemies on the river coming from Gerudo Valley, so always use the main waterbox height.
        yWaterSurface = gSaveContext.eventChkInf[6] & 0x0200 ? -1313.0 : -1993.0;
    }

    // Ignore water boxes below the ground.
    if (waterBoxFound && yWaterSurface < yGroundIntersect) {
        waterBoxFound = FALSE;
    }

    // Adjust position for certain enemies.
    if (actorEntry->id == ACTOR_OCTOROK && waterBoxFound) {
        // Always at water surface
        actorEntry->pos.y = yWaterSurface;
    } else if (actorEntry->id == ACTOR_SKULLTULA) {
        // In mid-air or near water surface
        if (!waterBoxFound && !isInvalidGround) {
            actorEntry->pos.y = yMidAirPos;
        } else if (waterBoxFound && (actorEntry->pos.y > yWaterSurface)) {
            actorEntry->pos.y = yWaterSurface + 50;
        }
    } else if (actorEntry->id == ACTOR_PEAHAT && actorEntry->params == (s16)0xFFFF) { // Grounded Peahat
        // At water surface or on ground.
        if (waterBoxFound) {
            actorEntry->pos.y = yWaterSurface;
        } else if (!isInvalidGround) {
            actorEntry->pos.y = yGroundIntersect;
        }
    } else if (actorEntry->id == ACTOR_BARI ||
               (actorEntry->id == ACTOR_PEAHAT && actorEntry->params == 0x0001)) { // Peahat Larva
        // In mid-air
        if (yMidAirPos > actorEntry->pos.y) {
            actorEntry->pos.y = yMidAirPos;
        }
    } else if (actorEntry->id == ACTOR_BUBBLE && (actorEntry->params & 0x00FF) == 0xFC) { // Green Bubble
        // Slightly above the ground so it doesn't go through it while bobbing up and down.
        if (!isInvalidGround && (actorEntry->pos.y - yGroundIntersect < 60)) {
            actorEntry->pos.y = yGroundIntersect + 60;
        }
    } else if (!isInvalidGround) {
        // Snap enemy to the ground if needed
        for (u32 i = 0; i < ARRAY_SIZE(sGroundedEnemies); i++) {
            if (actorEntry->id == sGroundedEnemies[i].actorId &&
                (sGroundedEnemies[i].anyParams || actorEntry->params == sGroundedEnemies[i].actorParams)) {
                actorEntry->pos.y = yGroundIntersect;
            }
        }
    }
}

static void Enemizer_SpawnObjectsForActor(s16 actorId, s16 params) {
    Object_FindEntryOrSpawn(gActorOverlayTable[actorId].initInfo->objectId);

    for (u32 i = 0; i < ARRAY_SIZE(sEnemyObjectDeps); i++) {
        if (actorId == sEnemyObjectDeps[i].key.actorId &&
            (sEnemyObjectDeps[i].key.anyParams || params == sEnemyObjectDeps[i].key.actorParams)) {
            Object_FindEntryOrSpawn(sEnemyObjectDeps[i].objectId);
        }
    }
}

u8 Enemizer_OverrideActorEntry(ActorEntry* actorEntry, s32 actorEntryIndex) {
    if (gSettingsContext.enemizer == OFF) {
        return KEEP_ACTOR_ENTRY;
    }

    // Jabu Jabu Shabom Room timer: set 2 minute time limit
    if (gGlobalContext->sceneNum == SCENE_JABU_JABU && gGlobalContext->roomNum == 12 && actorEntry->id == 0x187) {
        actorEntry->params = 0x7878;
        return KEEP_ACTOR_ENTRY;
    }

    EnemyOverride enemyOverride =
        Enemizer_FindOverride(gGlobalContext->sceneNum, rSceneLayer, gGlobalContext->roomNum, actorEntryIndex);

    // Do nothing if the override doesn't exist
    if (enemyOverride.actorId == 0) {
        return KEEP_ACTOR_ENTRY;
    }

    // Skip SFM Wolfos entry if the gate is open.
    if (gGlobalContext->sceneNum == SCENE_SACRED_FOREST_MEADOW && actorEntry->pos.z > 1600 &&
        Flags_GetSwitch(gGlobalContext, 0x1F)) {
        return SKIP_ACTOR_ENTRY;
    }

    if (gGlobalContext->sceneNum == SCENE_DODONGOS_CAVERN && gGlobalContext->roomNum == 3) {
        // Skip DC Lower Lizalfos entries if they have been defeated already.
        if (actorEntry->pos.z < -1540.0 && Flags_GetSwitch(gGlobalContext, 5)) {
            return SKIP_ACTOR_ENTRY;
        }

        // Skip DC Upper Lizalfos entries if they have been defeated already, or if the Lower Lizalfos haven't,
        // or if the player is entering from the lower doors.
        if (actorEntry->pos.z > -1540.0 && (Flags_GetSwitch(gGlobalContext, 6) || !Flags_GetSwitch(gGlobalContext, 5) ||
                                            PLAYER->actor.world.pos.y < 200.0)) {
            return SKIP_ACTOR_ENTRY;
        }
    }

    actorEntry->id     = enemyOverride.actorId;
    actorEntry->params = enemyOverride.params;

    Enemizer_MoveSpecificLocations(actorEntry, actorEntryIndex);
    Enemizer_MoveSpecificEnemies(actorEntry);

    // Clear X and Z rotation to spawn all enemies upright
    actorEntry->rot.x = 0;
    actorEntry->rot.z = 0;

    // Spawn necessary objects
    Enemizer_SpawnObjectsForActor(actorEntry->id, actorEntry->params);

    return KEEP_ACTOR_ENTRY;
}

EnemyOverride Enemizer_GetSpawnerOverride(void) {
    // Dynamic enemy spawners are represented by actorEntry=0xFF
    return Enemizer_FindOverride(gGlobalContext->sceneNum, rSceneLayer, gGlobalContext->roomNum, 0xFF);
}

u8 Enemizer_IsRoomCleared(void) {
    return (gGlobalContext->actorCtx.flags.tempClear >> gGlobalContext->roomNum) & 1;
}

// Handle opening certain doors that are normally handled by the specific enemies in the area,
// by checking on every frame if the randomized enemies have been defeated.
static void Enemizer_HandleClearConditions(void) {
    if (gGlobalContext->sceneNum == SCENE_SACRED_FOREST_MEADOW && gSaveContext.linkAge == AGE_CHILD &&
        gEnemizerLocationFlags.sfmWolfos && !Flags_GetSwitch(gGlobalContext, 0x1F)) {
        // Handle the entrance gate in the Child layer if it's not open already.
        // Checking the clear flag doesn't work because there are other enemies in the same room, so
        // search for the enemy actor manually. Run the search multiple times if necessary because
        // Skullwalltulas change category to Enemy during their Init function, which might be called
        // on a different update cycle after the actor is spawned.
        if (sSFMWolfos == NULL) {
            Actor* enemy = gGlobalContext->actorCtx.actorList[ACTORTYPE_ENEMY].first;
            for (; enemy != NULL; enemy = enemy->next) {
                if (enemy->world.pos.z > 1600.0 &&
                    // Ignore scrub's flower and bubble's flames
                    ((enemy->id != ACTOR_MAD_SCRUB && enemy->id != ACTOR_BUBBLE) || enemy->parent == NULL)) {
                    sSFMWolfos = enemy;
                    break;
                }
            }
        }
        // Then, on every frame, manually check if the enemy is defeated (actor was killed or changed category).
        // Note: if the randomized enemy is a Bari, the 3 Biris it spawns will be ignored.
        else if (((sSFMWolfos->update == NULL && sSFMWolfos->draw == NULL) || (sSFMWolfos->type != ACTORTYPE_ENEMY))) {
            Flags_SetSwitch(gGlobalContext, 0x1F);
            sSFMWolfos = NULL;
        }
    } else if (gGlobalContext->sceneNum == SCENE_DODONGOS_CAVERN && gGlobalContext->roomNum == 3 &&
               gEnemizerLocationFlags.dcLizalfos) {
        // Miniboss room: open the correct doors when the room is cleared.
        if (Enemizer_IsRoomCleared() && !sLastRoomCleared) {
            u32 flag = Flags_GetSwitch(gGlobalContext, 5) ? 6 : 5;
            Flags_SetSwitch(gGlobalContext, flag);
            sLastRoomCleared = TRUE;
        }
    } else if (gGlobalContext->sceneNum == SCENE_THIEVES_HIDEOUT && gEnemizerLocationFlags.gerudoFighters) {
        const s8 keyFlagsByRoom[6] = { 0, 0x0A, 0x0C, 0, 0x0E, 0x0F };

        s8 keyFlag = keyFlagsByRoom[gGlobalContext->roomNum];
        // Spawn the key when the room is cleared.
        if (Enemizer_IsRoomCleared() && !sLastRoomCleared) {
            // Take the horizontal position from the Gerudo Fighter's actor entry, which is #1 in all 4 rooms.
            Vec3s pos  = gGlobalContext->actorEntryList[1].pos;
            f32 posY   = gGlobalContext->roomNum == 4 ? 0.0f : 240.0f;
            Actor* key = Actor_Spawn(&gGlobalContext->actorCtx, gGlobalContext, ACTOR_EN_ITEM00, pos.x, posY, pos.z, 0,
                                     0, 0, (keyFlag << 8) | ITEM00_SMALL_KEY, FALSE);
            key->gravity     = -0.9f;
            sLastRoomCleared = TRUE;
        }
        // Permanently clear the room when the key is collected, so the enemy doesn't respawn.
        if (Flags_GetCollectible(gGlobalContext, keyFlag)) {
            Flags_SetClear(gGlobalContext, gGlobalContext->roomNum);
        }
    }
}

// Some randomized enemies start the Mini Boss battle theme and don't stop it when leaving the room.
// This function will stop the battle theme if there are no more mini bosses loaded.
static void Enemizer_HandleMiniBossBattleTheme(void) {
    // Always check if music should stop when loading another room, otherwise only check if player is not
    // in cutscene mode because Big Octo turns into a prop temporarily during its intro cutscene.
    if (Audio_GetActiveSeqId(0) == BGM_MINI_BOSS && (sRoomLoadSignal || !Player_InCsMode(gGlobalContext))) {
        u8 shouldKeepMiniBossBGM = FALSE;
        Actor* enemy             = gGlobalContext->actorCtx.actorList[ACTORTYPE_ENEMY].first;
        for (; enemy != NULL && !shouldKeepMiniBossBGM; enemy = enemy->next) {
            if (enemy->update == NULL && enemy->draw == NULL) {
                // Ignore killed actors so the music will stop when opening a door rather than after closing it.
                continue;
            }
            switch (enemy->id) {
                case ACTOR_POE_SISTER:
                // case ACTOR_FLARE_DANCER: music is silenced from EnFd_rUpdate
                case ACTOR_DEAD_HAND:
                case ACTOR_BIG_OCTO:
                case ACTOR_GERUDO_FIGHTER:
                    shouldKeepMiniBossBGM = TRUE;
                    break;
                case ACTOR_STALFOS:
                    shouldKeepMiniBossBGM = (enemy->params != 2 && enemy->params != 3);
                    break;
                case ACTOR_DARK_LINK:
                    shouldKeepMiniBossBGM = ((EnTorch2*)enemy)->actionState != ENTORCH2_WAIT;
                    break;
            }
        }

        if (!shouldKeepMiniBossBGM) {
            if (sPrevMainBgmSeqId != -1) {
                Audio_RestoreBGM();
            } else {
                Audio_StopBGM();
            }
        }
    }
}

// Called once per room load, after all actor entries have been spawned.
void Enemizer_AfterActorSetup(void) {
    if (gSettingsContext.enemizer == OFF) {
        return;
    }

    EnemyOverride enemySpawnerOvr = Enemizer_GetSpawnerOverride();
    if (enemySpawnerOvr.actorId != 0) {
        Enemizer_SpawnObjectsForActor(enemySpawnerOvr.actorId, enemySpawnerOvr.params);
    }

    sSFMWolfos       = NULL;
    sLastRoomCleared = FALSE;
    sRoomLoadSignal  = TRUE;
}

// Run special checks on every frame
void Enemizer_Update(void) {
    if (gSettingsContext.enemizer == OFF) {
        return;
    }

    Enemizer_HandleClearConditions();
    Enemizer_HandleMiniBossBattleTheme();

    sRoomLoadSignal = FALSE;
}
