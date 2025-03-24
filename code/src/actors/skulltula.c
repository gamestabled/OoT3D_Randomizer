#include "skulltula.h"
#include "multiplayer.h"
#include "settings.h"
#include "common.h"
#include "objects.h"

#define EnSw_Init ((ActorFunc)GAME_ADDR(0x1691C8))
#define EnSw_Update ((ActorFunc)GAME_ADDR(0x1BB110))

#define EnSw_GoldSkulltulaDeath (void*)GAME_ADDR(0x3B91BC)
#define EnSw_WalltulaIdle ((void*)GAME_ADDR(0x3CDAAC))
#define EnSw_SetupGoingHome ((void*)GAME_ADDR(0x3C2A50))

#define Skullwalltula_IsCloseToPlayer(walltula) \
    (walltula->base.xzDistToPlayer < 250.0 && ABS(walltula->base.yDistToPlayer) < 50.0)

const GsLocOverride rGsLocOverrides[100] = { 0 };

void Gs_SpawnAltLocs(void) {
    if (!IsInGame() || !gSettingsContext.randomGsLocations) {
        return;
    }

    Object_FindEntryOrSpawn(0x24);

    for (u32 i = 0; i < ARRAY_SIZE(rGsLocOverrides); i++) {
        const GsLocOverride* gs = &rGsLocOverrides[i];
        if (gs->bitFlag == 0) {
            // End of list.
            return;
        }

        if (gs->scene == gGlobalContext->sceneNum && gs->room == gGlobalContext->roomNum &&
            (gs->ageCondition == GS_AGE_BOTH || gs->ageCondition == gSaveContext.linkAge)) {

            s16 params = 0;
            if (gs->timeCondition == GS_TIME_ALWAYS) {
                params |= 0x8000;
            } else if (gs->timeCondition == GS_TIME_NIGHT) {
                params |= 0xA000;
            }

            params |= (gs->arrayIndex + 1) << 8;
            params |= gs->bitFlag;

            Actor_Spawn(&gGlobalContext->actorCtx, gGlobalContext, 0x95,      //
                        gs->posRot.pos.x, gs->posRot.pos.y, gs->posRot.pos.z, //
                        gs->posRot.rot.x, gs->posRot.rot.y, gs->posRot.rot.z, params, FALSE);
        }
    }
}

u8 Gs_HasAltLoc(void* ptr, GsParamPointerType ppt, u8 adjustArrayIndex) {
    if (!gSettingsContext.randomGsLocations) {
        return FALSE;
    }

    u8 arrayIndex = 0;
    u8 bitFlag    = 0;

    switch (ppt) {
        case GS_PPT_ACTORENTRY: {
            ActorEntry* actorEntry = ptr;
            arrayIndex             = GS_ARRAY_INDEX(actorEntry->params);
            bitFlag                = GS_BIT_FLAG(actorEntry->params);
            break;
        }
        case GS_PPT_ACTOR_GS:
        case GS_PPT_ACTOR_CRATE:
        case GS_PPT_ACTOR_SOIL: {
            Actor* actor = ptr;
            arrayIndex   = GS_ARRAY_INDEX(actor->params);
            bitFlag      = GS_BIT_FLAG(actor->params);
            break;
        }
        case GS_PPT_ACTOR_TREE: {
            Actor* actor = ptr;
            arrayIndex   = GS_ARRAY_INDEX(actor->home.rot.z);
            bitFlag      = GS_BIT_FLAG(actor->home.rot.z);
            break;
        }
    }

    // Some params have the first index as 1, but in the init function for the Gold Skulltula it's subtracted by one to
    // align with gsFlags in gSaveContext. The post-init array index is what the override data uses.
    if (adjustArrayIndex) {
        arrayIndex -= 1;
    }

    for (u32 i = 0; i < ARRAY_SIZE(rGsLocOverrides); i++) {
        if (rGsLocOverrides[i].bitFlag == 0) {
            // End of list.
            return FALSE;
        }
        if (rGsLocOverrides[i].arrayIndex == arrayIndex && rGsLocOverrides[i].bitFlag == bitFlag) {
            return TRUE;
        }
    }
    return FALSE;
}

u8 Gs_CustomTangibilityCheck(Actor* thisx) {
    typedef struct {
        s16 id;
        u32 blockingDistance;
    } BlockingActor;

    static const BlockingActor blockingActors[] = {
        { 0xEF, 25 },  // Red Ice
        { 0x107, 25 }, // Milk Crate
        { 0x127, 25 }, // Brown Boulder
        { 0x14E, 25 }, // Silver Boulder
        { 0x1A0, 25 }, // Large Wooden Crate
        { 0x1D1, 75 }, // Song of Time Block
        { 0x1D2, 25 }, // Red Boulder
    };

    for (size_t actorType = 0; actorType <= ACTORTYPE_CHEST; actorType++) {
        for (Actor* actor = gGlobalContext->actorCtx.actorList[actorType].first; actor != NULL; actor = actor->next) {
            for (size_t i = 0; i < ARRAY_SIZE(blockingActors); i++) {

                if (actor->id == blockingActors[i].id &&
                    Actor_WorldDistXYZToActor(thisx, actor) < blockingActors[i].blockingDistance) {
                    // Special case for Song of Time blocks
                    if (actor->id == 0x1D1) {
                        typedef struct {
                            char base[444];
                            char irrelevant[20];
                            u8 is_visible;
                        } ObjTimeblock;
                        ObjTimeblock* timeBlock = (ObjTimeblock*)actor;
                        if (!timeBlock->is_visible) {
                            return FALSE;
                        }
                    }
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

Vec3f* Gs_GetCustomTokenSpawnPos(Actor* thisx) {
    static Vec3f spawnPos;
    spawnPos = thisx->world.pos;

    // Lower to adjust for token's center
    // Token spawn position has auto-adjustment when inside walls
    // and is therefor sensitive to this, so don't change!
    spawnPos.y -= 10;

    // Distance from Gold Skulltula
    static const f32 dist = 20;

    Vec3f around = { 0, 0, 0 };

    s16 rx = thisx->world.rot.x;
    s16 ry = thisx->world.rot.y;
    s16 rz = thisx->world.rot.z;

    around.x = Math_SinS(rx) * Math_SinS(ry) * Math_CosS(rz) - Math_CosS(ry) * Math_SinS(rz);
    around.y = Math_CosS(rx) * Math_CosS(rz);
    around.z = Math_SinS(ry) * Math_SinS(rz) + Math_SinS(rx) * Math_CosS(ry) * Math_CosS(rz);

    spawnPos.x += dist * around.x;
    spawnPos.y += dist * around.y;
    spawnPos.z += dist * around.z;

    return &spawnPos;
}

void EnSw_rInit(Actor* thisx, GlobalContext* globalCtx) {
    EnSw_Init(thisx, globalCtx);

    if (gSettingsContext.randomGsLocations && thisx->params & 0xE000) {
        // Post-init rotation fix
        for (u32 i = 0; i < ARRAY_SIZE(rGsLocOverrides); i++) {
            if (rGsLocOverrides[i].arrayIndex == 0 && rGsLocOverrides[i].bitFlag == 0) {
                // End of list.
                break;
            }
            if (rGsLocOverrides[i].arrayIndex == GS_ARRAY_INDEX(thisx->params) &&
                rGsLocOverrides[i].bitFlag == GS_BIT_FLAG(thisx->params)) {

                thisx->world     = rGsLocOverrides[i].posRot;
                thisx->shape.rot = thisx->world.rot;
                break;
            }
        }
    }

    if (gSettingsContext.enemizer == ON && thisx->params == 0) {
        // Randomized Skullwalltulas will appear flat on the ground.
        thisx->shape.rot.x = 0xC000;
        // Force despawn if room is already cleared (in the base game they ignore the flag for some reason)
        if (Flags_GetClear(globalCtx, globalCtx->roomNum)) {
            Actor_Kill(thisx);
        }
    }
}

void EnSw_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnSw* this = (EnSw*)thisx;
    // Remove when token picked up by other player to prevent duplicates
    if (thisx->params & 0xE000) {
        u8 idx = (thisx->params >> 8) & 0x1F;
        if (gSaveContext.gsFlags[idx] & (thisx->params & 0xFF)) {
            Actor_Kill(thisx);
            return;
        }
    }

    void* prev_action_fn = this->action_fn;

    // Fix rotation for the GS in the top room in Fire Temple MQ, which for some reason spawns upside down
    // if the MQ flag is not set and you enter the room from the door.
    if (globalCtx->sceneNum == 4 && gSettingsContext.fireTempleDungeonMode == DUNGEONMODE_MQ && thisx->room == 8) {
        thisx->world.rot.z = 0;
    }

    if (gSettingsContext.enemizer == ON && thisx->params == 0) {
        // Randomized Skullwalltulas: fix facing direction when detecting and attacking the player.
        thisx->shape.rot.y = 0;
        // Always rotate towards player when idle
        if (this->action_fn == EnSw_WalltulaIdle && Skullwalltula_IsCloseToPlayer(this)) {
            this->targetRot = thisx->yawTowardsPlayer;
        }
    }

    EnSw_Update(thisx, globalCtx);

    if (prev_action_fn != this->action_fn && this->action_fn == EnSw_GoldSkulltulaDeath) {
        Multiplayer_Send_ActorUpdate((Actor*)thisx, NULL, 0);
    }
}

typedef void (*FUN_00375B70_proc)(GlobalContext* globalCtx, Actor* actor);
#define FUN_00375B70 ((FUN_00375B70_proc)GAME_ADDR(0x375B70))

void EnSw_Kill(EnSw* thisx, GlobalContext* globalCtx) {
    if (thisx->action_fn == EnSw_GoldSkulltulaDeath || (thisx->base.params & 0x4000 && !gSaveContext.nightFlag)) {
        return;
    }
    // TODO: Fix spin speed
    thisx->unk_word2 = 24;
    FUN_00375B70(globalCtx, &thisx->base); // Not needed?
    thisx->base.colChkInfo.health = 0;
    // thisx->anime.play_speed = 8.0; // Doesn't seem to matter
    thisx->unk_float1       = 16.0;
    thisx->deathTimer_maybe = 15;
    thisx->unk_word1        = 1;
    thisx->action_fn        = EnSw_GoldSkulltulaDeath;
}

// Return -1 to use vanilla check
s32 Skullwalltula_ShouldAttack(EnSw* walltula) {
    if (gSettingsContext.enemizer == OFF) {
        return -1;
    }

    Vec3f posResult;
    CollisionPoly* outPoly;
    s32 bgId;
    // Facing player, being close enough and not having obstacles in the way
    return ABS(walltula->base.yawTowardsPlayer - walltula->base.shape.rot.z) < 0x4000 &&
           Skullwalltula_IsCloseToPlayer(walltula) &&
           !BgCheck_EntityLineTest1(&gGlobalContext->colCtx, &walltula->base.world.pos, &PLAYER->actor.world.pos,
                                    &posResult, &outPoly, TRUE, FALSE, FALSE, TRUE, &bgId);
}

s16 Skullwalltula_GetTargetRotation(s16 orig, EnSw* walltula) {
    if (gSettingsContext.enemizer == OFF) {
        return orig;
    }
    if (walltula->action_fn == EnSw_SetupGoingHome) {
        // Going back to home position, turn around
        return walltula->targetRot + 0x8000;
    }
    // Attacking player, remove Y offset
    walltula->targetPos.y = PLAYER->actor.world.pos.y;
    return walltula->base.yawTowardsPlayer;
}
