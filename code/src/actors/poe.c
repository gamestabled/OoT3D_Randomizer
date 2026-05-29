#include "poe.h"
#include "settings.h"
#include "enemizer.h"
#include "actor.h"
#include "common.h"

#include "z3D/actors/z_en_item00.h"

/*-------------------------------
|             EnPoh             |
-------------------------------*/

void EnPoh_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPoh_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPoh_UpdateLiving(Actor* thisx, GlobalContext* globalCtx);
void EnPoh_UpdateDead(Actor* thisx, GlobalContext* globalCtx);

/**
 * Composer Brothers set some flags when they spawn and when the player talks to them.
 * This function prevents them from affecting the current scene by either overriding
 * these flags or moving them to the Graveyard scene.
 */
static void Poe_CallActorFunc(ActorFunc actorFunc, Actor* thisx, GlobalContext* globalCtx) {
    u32 prevSwchFlags;
    u32 prevTempSwchFlags;
    u8 isRandomizedComposerBrother = Enemizer_IsEnemyRandomized(ENEMY_POE) && (thisx->params & 0x0002) == 0x0002 &&
                                     globalCtx->sceneNum != SCENE_GRAVEYARD;

    if (isRandomizedComposerBrother) {
        prevSwchFlags                      = globalCtx->actorCtx.flags.swch;
        prevTempSwchFlags                  = globalCtx->actorCtx.flags.tempSwch;
        globalCtx->actorCtx.flags.swch     = gSaveContext.sceneFlags[SCENE_GRAVEYARD].swch;
        globalCtx->actorCtx.flags.tempSwch = 0;
        Flags_UnsetSwitch(globalCtx, 0x9); // This flag makes Composer Brothers stop spawning
    }

    actorFunc(thisx, globalCtx);

    if (isRandomizedComposerBrother) {
        gSaveContext.sceneFlags[SCENE_GRAVEYARD].swch = globalCtx->actorCtx.flags.swch;
        globalCtx->actorCtx.flags.swch                = prevSwchFlags;
        globalCtx->actorCtx.flags.tempSwch            = prevTempSwchFlags;
    }
}

void EnPoh_rInit(Actor* thisx, GlobalContext* globalCtx) {
    Poe_CallActorFunc(EnPoh_Init, thisx, globalCtx);
}

static void EnPoh_rUpdateDead(Actor* thisx, GlobalContext* globalCtx) {
    Poe_CallActorFunc(EnPoh_UpdateDead, thisx, globalCtx);
}

static void EnPoh_rUpdateLiving(Actor* thisx, GlobalContext* globalCtx) {
    Poe_CallActorFunc(EnPoh_UpdateLiving, thisx, globalCtx);
    if (thisx->update == EnPoh_UpdateDead) {
        thisx->update = EnPoh_rUpdateDead;
    }
}

void EnPoh_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    Poe_CallActorFunc(EnPoh_Update, thisx, globalCtx);
    if (thisx->update == EnPoh_UpdateLiving) {
        thisx->update = EnPoh_rUpdateLiving;
    }
}

void EnPoh_ReinitModels(EnPoh* this) {
    Actor_DestroySkelModels(&this->actor, &this->saModel_1, &this->saModel_2, NULL);
    u32 cmb1Index    = this->infoIdx == 0 ? 1 : this->composerLanternCmbIndex;
    u32 cmb2Index    = this->infoIdx == 0 ? 2 : 1;
    ZARInfo* zarInfo = Actor_CreateSkelModels(&this->actor, gGlobalContext, &this->saModel_1, cmb1Index,
                                              &this->saModel_2, cmb2Index, NULL);
    void* cmabMan    = ZAR_GetCMABByIndex(zarInfo, 0);
    MatAnim_Init(this->saModel_2->matAnim, cmabMan);
    this->saModel_2->matAnim->animMode  = 1;
    this->saModel_2->matAnim->animSpeed = 2.0;
    this->saModel_94C                   = this->saModel_1;
    this->saModel_950                   = this->saModel_2;

    Actor_ReinitSkelAnime(&this->actor, &this->anime, 0);
}

/*-------------------------------
|           EnPoField           |
-------------------------------*/

extern u8 EnPoField_SpawnSwitchFlags[10];

void EnPoField_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPoField_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPoField_UpdateDead(Actor* thisx, GlobalContext* globalCtx);

void EnPoField_WaitForSpawn(EnPoField* this, GlobalContext* globalCtx);
void EnPoField_SetupWaitForSpawn(EnPoField* this, GlobalContext* globalCtx);
void EnPoField_Appear(EnPoField* this, GlobalContext* globalCtx);
void EnPoField_SoulAppearing(EnPoField* this, GlobalContext* globalCtx);

static void EnPoField_rSetUpdateFunc(Actor* thisx);

static void EnPoField_rPostUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnPoField* this = (EnPoField*)thisx;

    if (gSettingsContext.shuffleBigPoes) {
        if (this->actor.params == EN_PO_FIELD_BIG) {
            s32 collectFlag = this->spawnFlagIndex + 1;
            if (this->actionFunc == EnPoField_SoulAppearing) {
                // When turning into a soul, return idle instead and drop a heart piece that will be overridden.
                Item_DropCollectible(globalCtx, &thisx->world.pos, ITEM00_HEART_PIECE | (collectFlag << 8));
                EnPoField_SetupWaitForSpawn(this, globalCtx);
            } else if (this->actionFunc == EnPoField_Appear) {
                // When spawning, check if the item was already dropped without being collected, and remove it if found.
                Actor* actor = globalCtx->actorCtx.actorList[ACTORTYPE_MISC].first;
                for (; actor != NULL; actor = actor->next) {
                    if (actor->id == ACTOR_EN_ITEM00 && ((EnItem00*)actor)->collectibleFlag == collectFlag) {
                        Actor_Kill(actor);
                    }
                }
            }
        }
        // When the item is collected, set the switch flag to prevent the Big Poe from spawning again.
        for (s32 poeSpawnIdx = 0; poeSpawnIdx < ARRAY_SIZE(EnPoField_SpawnSwitchFlags); poeSpawnIdx++) {
            if (Flags_GetCollectible(globalCtx, poeSpawnIdx + 1)) {
                Flags_SetSwitch(globalCtx, EnPoField_SpawnSwitchFlags[poeSpawnIdx]);
            }
        }
    }
}

static void EnPoField_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnPoField_Update(thisx, globalCtx);
    EnPoField_rPostUpdate(thisx, globalCtx);
    EnPoField_rSetUpdateFunc(thisx);
}

static void EnPoField_rUpdateDead(Actor* thisx, GlobalContext* globalCtx) {
    EnPoField_UpdateDead(thisx, globalCtx);
    EnPoField_rPostUpdate(thisx, globalCtx);
    EnPoField_rSetUpdateFunc(thisx);
}

void EnPoField_rInit(Actor* thisx, GlobalContext* globalCtx) {
    EnPoField_Init(thisx, globalCtx);
    EnPoField_rSetUpdateFunc(thisx);
}

static void EnPoField_rSetUpdateFunc(Actor* thisx) {
    if (thisx->update == EnPoField_Update) {
        thisx->update = EnPoField_rUpdate;
    } else if (thisx->update == EnPoField_UpdateDead) {
        thisx->update = EnPoField_rUpdateDead;
    }
}

void EnPoField_ReinitModels(EnPoField* this) {
    Actor_DestroySkelModels(&this->actor, &this->saModel_1, &this->saModel_2, NULL);
    ZARInfo* zarInfo =
        Actor_CreateSkelModels(&this->actor, gGlobalContext, &this->saModel_1, 1, &this->saModel_2, 3, NULL);
    if (this->actionFunc != EnPoField_WaitForSpawn) {
        void* cmabMan = ZAR_GetCMABByIndex(zarInfo, this->actor.params == EN_PO_FIELD_BIG ? 0 : 1);
        MatAnim_Init(this->saModel_2->matAnim, cmabMan);
        this->saModel_2->matAnim->animMode  = 1;
        this->saModel_2->matAnim->animSpeed = 2.0;
    }

    Actor_ReinitSkelAnime(&this->actor, &this->anime, 0);
}

/*-------------------------------
|           EnPoSister          |
-------------------------------*/

void EnPoSisters_ReinitModels(EnPoSisters* this) {
    Actor_DestroySkelModels(&this->actor, &this->saModel_death, NULL);
    Actor_CreateSkelModels(&this->actor, gGlobalContext, &this->saModel_death, 6, NULL);

    Actor_ReinitSkelAnime(&this->actor, &this->anime, 0);
}
