#include "enemy_souls.h"
#include "savefile.h"
#include "settings.h"
#include "armos.h"
#include "actor.h"
#include "flying_traps.h"
#include "objects.h"
#include "shabom.h"
#include "poe.h"
#include "octorok.h"
#include "peahat.h"
#include "tektite.h"
#include "lizalfos.h"
#include "biri.h"
#include "skulltula.h"
#include "torch_slug.h"
#include "stinger.h"
#include "deku_baba.h"
#include "beamos.h"
#include "shabom.h"
#include "wallmaster.h"
#include "tentacle.h"
#include "skull_kid.h"
#include "deku_scrubs.h"
#include "business_scrubs.h"
#include "door.h"
#include "flare_dancer.h"
#include "dead_hand.h"
#include "dodongos.h"
#include "tailpasaran.h"
#include "moblin.h"
#include "guay.h"
#include "wolfos.h"
#include "stalfos.h"
#include "gerudos.h"
#include "dark_link.h"
#include "spike.h"
#include "freezard.h"
#include "bubble.h"
#include "keese.h"
#include "redead.h"
#include "like_like.h"

#include <string.h>

typedef void (*ReinitModelsFunc)(Actor* actor);

typedef struct ActorSoulData {
    EnemySoulId soulId;
    ReinitModelsFunc reinitModelsFunc;
} ActorSoulData;

static void SoullessFlames_Draw(void);
static void SoullessModels_RestoreSoul(EnemySoulId soulId);
static void SoullessModels_ReinitGenericSkelAnime(Actor* actor);
static void SoullessModels_HandleRestoreRequest(void);

#define CASE(actorId, soulId, reinitModelsFunc)        \
    case actorId:                                      \
        return (ActorSoulData) {                       \
            soulId, (ReinitModelsFunc)reinitModelsFunc \
        }
static ActorSoulData EnemySouls_GetActorSoulData(s16 actorId) {
    // Some actors don't have a function to reinit models for various reasons:
    // - Flare Dancer Core can't spawn if the player doesn't have the Flare Dancer Soul;
    // - Flying Traps and Armos are handled in their own update function;
    // - Bosses (except KD) are ignored because the player can't get items while they're loaded.
    switch (actorId) {
        // clang-format off
        CASE(ACTOR_POE,                     SOUL_POE,                  EnPoh_ReinitModels);
        CASE(ACTOR_FIELD_POE,               SOUL_POE,                  EnPoField_ReinitModels);
        CASE(ACTOR_POE_SISTER,              SOUL_POE,                  EnPoSisters_ReinitModels);
        CASE(ACTOR_OCTOROK,                 SOUL_OCTOROK,              EnOkuta_ReinitModels);
        CASE(ACTOR_BIG_OCTO,                SOUL_OCTOROK,              SoullessModels_ReinitGenericSkelAnime);
        CASE(ACTOR_KEESE,                   SOUL_KEESE,                EnFirefly_ReinitModels);
        CASE(ACTOR_TEKTITE,                 SOUL_TEKTITE,              EnTite_ReinitModels);
        CASE(ACTOR_LEEVER,                  SOUL_LEEVER,               SoullessModels_ReinitGenericSkelAnime);
        CASE(ACTOR_PEAHAT,                  SOUL_PEAHAT,               EnPeehat_ReinitModels);
        CASE(ACTOR_LIZALFOS,                SOUL_LIZALFOS,             EnZf_ReinitModels);
        CASE(ACTOR_SHABOM,                  SOUL_SHABOM,               EnBubble_ReinitModels);
        CASE(ACTOR_BIRI,                    SOUL_BIRI_BARI,            EnBili_ReinitModels);
        CASE(ACTOR_BARI,                    SOUL_BIRI_BARI,            EnVali_ReinitModels);
        CASE(ACTOR_TAILPASARAN,             SOUL_TAILPASARAN,          EnTp_ReinitModels);
        CASE(ACTOR_SKULLTULA,               SOUL_SKULLTULA,            SoullessModels_ReinitGenericSkelAnime);
        CASE(ACTOR_SKULLWALLTULA,           SOUL_SKULLTULA,            EnSw_ReinitModels);
        CASE(ACTOR_TORCH_SLUG,              SOUL_TORCH_SLUG,           EnBw_ReinitModels);
        CASE(ACTOR_STINGER_FLOOR,           SOUL_STINGER,              EnEiyer_ReinitModels);
        CASE(ACTOR_STINGER_WATER,           SOUL_STINGER,              SoullessModels_ReinitGenericSkelAnime);
        CASE(ACTOR_MOBLIN,                  SOUL_MOBLIN,               EnMb_ReinitModels);
        CASE(ACTOR_ARMOS,                   SOUL_ARMOS,                NULL);
        CASE(ACTOR_DEKU_BABA,               SOUL_DEKU_BABA,            EnDekubaba_ReinitModels);
        CASE(ACTOR_WITHERED_DEKU_BABA,      SOUL_DEKU_BABA,            EnKarebaba_ReinitModels);
        CASE(ACTOR_BUBBLE,                  SOUL_BUBBLE,               EnBb_ReinitModels);
        CASE(ACTOR_FLYING_POT,              SOUL_FLYING_TRAP,          NULL);
        CASE(ACTOR_FLYING_FLOOR_TILE,       SOUL_FLYING_TRAP,          NULL);
        CASE(ACTOR_BEAMOS,                  SOUL_BEAMOS,               EnVm_ReinitModels);
        CASE(ACTOR_WALLMASTER,              SOUL_WALLMASTER,           EnWallmas_ReinitModels);
        CASE(ACTOR_FLOORMASTER,             SOUL_WALLMASTER,           SoullessModels_ReinitGenericSkelAnime);
        CASE(ACTOR_REDEAD,                  SOUL_REDEAD_GIBDO,         EnRd_ReinitModels);
        CASE(ACTOR_SHELL_BLADE,             SOUL_SHELL_BLADE,          SoullessModels_ReinitGenericSkelAnime);
        CASE(ACTOR_LIKE_LIKE,               SOUL_LIKE_LIKE,            EnRr_ReinitModels);
        CASE(ACTOR_PARASITIC_TENTACLE,      SOUL_TENTACLE,             EnBa_ReinitModels);
        CASE(ACTOR_OBSTACLE_TENTACLE,       SOUL_TENTACLE,             EnBx_ReinitModels);
        CASE(ACTOR_ANUBIS,                  SOUL_ANUBIS,               SoullessModels_ReinitGenericSkelAnime);
        CASE(ACTOR_SPIKE,                   SOUL_SPIKE,                EnNy_ReinitModels);
        CASE(ACTOR_SKULL_KID,               SOUL_SKULL_KID,            EnSkj_ReinitModels);
        CASE(ACTOR_FREEZARD,                SOUL_FREEZARD,             EnFz_ReinitModels);
        CASE(ACTOR_HINT_DEKU_SCRUB,         SOUL_DEKU_SCRUB,           EnHintnuts_ReinitModels);
        CASE(ACTOR_MAD_SCRUB,               SOUL_DEKU_SCRUB,           EnDekunuts_ReinitModels);
        CASE(ACTOR_BUSINESS_SCRUB,          SOUL_DEKU_SCRUB,           EnShopnuts_ReinitModels);
        CASE(ACTOR_WOLFOS,                  SOUL_WOLFOS,               EnWf_ReinitModels);
        CASE(ACTOR_STALCHILD,               SOUL_STALCHILD,            SoullessModels_ReinitGenericSkelAnime);
        CASE(ACTOR_GUAY,                    SOUL_GUAY,                 EnCrow_ReinitModels);
        CASE(ACTOR_DOOR_MIMIC,              SOUL_DOOR_MIMIC,           DoorKiller_ReinitModels);
        CASE(ACTOR_STALFOS,                 SOUL_STALFOS,              EnTest_ReinitModels);
        CASE(ACTOR_DARK_LINK,               SOUL_DARK_LINK,            EnTorch2_ReinitModels);
        CASE(ACTOR_FLARE_DANCER,            SOUL_FLARE_DANCER,         EnFd_ReinitModels);
        CASE(ACTOR_FLARE_DANCER_CORE,       SOUL_FLARE_DANCER,         NULL);
        CASE(ACTOR_DEAD_HAND,               SOUL_DEAD_HAND,            EnDh_ReinitModels);
        CASE(ACTOR_DEAD_HAND_HAND,          SOUL_DEAD_HAND,            SoullessModels_ReinitGenericSkelAnime);
        CASE(ACTOR_GERUDO_GUARD,            SOUL_GERUDO,               EnGe2_ReinitModels);
        CASE(ACTOR_GERUDO_FIGHTER,          SOUL_GERUDO,               EnGeldB_ReinitModels);
        CASE(ACTOR_IRON_KNUCKLE,            SOUL_GERUDO,               SoullessModels_ReinitGenericSkelAnime);
        CASE(ACTOR_GOHMA,                   SOUL_GOHMA,                SoullessModels_ReinitGenericSkelAnime);
        CASE(ACTOR_GOHMA_LARVA,             SOUL_GOHMA,                SoullessModels_ReinitGenericSkelAnime);
        CASE(ACTOR_DODONGO,                 SOUL_DODONGO,              SoullessModels_ReinitGenericSkelAnime);
        CASE(ACTOR_BABY_DODONGO,            SOUL_DODONGO,              SoullessModels_ReinitGenericSkelAnime);
        CASE(ACTOR_KING_DODONGO,            SOUL_DODONGO,              BossDodongo_ReinitModels);
        CASE(ACTOR_BARINADE,                SOUL_BARINADE,             NULL);
        CASE(ACTOR_PHANTOM_GANON,           SOUL_PHANTOM_GANON,        NULL);
        CASE(ACTOR_PG_HORSE,                SOUL_PHANTOM_GANON,        NULL);
        CASE(ACTOR_VOLVAGIA_FLYING,         SOUL_VOLVAGIA,             NULL);
        CASE(ACTOR_VOLVAGIA_HOLE,           SOUL_VOLVAGIA,             NULL);
        CASE(ACTOR_MORPHA,                  SOUL_MORPHA,               NULL);
        CASE(ACTOR_BONGO_BONGO,             SOUL_BONGO_BONGO,          NULL);
        CASE(ACTOR_TWINROVA,                SOUL_TWINROVA,             NULL);
        CASE(ACTOR_GANONDORF,               SOUL_GANON,                NULL);
        CASE(ACTOR_GANON,                   SOUL_GANON,                NULL);
        // clang-format on
    }

    return (ActorSoulData){ SOUL_NONE, NULL };
}
#undef CASE

EnemySoulId EnemySouls_GetSoulId(s16 actorId) {
    return EnemySouls_GetActorSoulData(actorId).soulId;
}

Bool EnemySouls_GetSoulFlag(EnemySoulId soulId) {
    if (soulId == SOUL_NONE) {
        return TRUE;
    }
    return (gExtSaveData.extInf.enemySouls[(soulId >> 3)] >> (soulId & 0b111)) & 1;
}

static void EnemySouls_SetSoulFlag(EnemySoulId soulId) {
    if (soulId == SOUL_NONE) {
        return;
    }
    gExtSaveData.extInf.enemySouls[(soulId >> 3)] |= (1 << (soulId & 0b111));
}

typedef enum SoulCheckType {
    SOULCHECK_BASE,      // Check only if soul is owned
    SOULCHECK_COLLISION, // Check if enemy can be hit
    SOULCHECK_DRAW,      // Check if enemy should be drawn soulless
} SoulCheckType;

static Bool EnemySouls_CheckSoul(Actor* actor, SoulCheckType soulCheck) {
    if (actor == NULL || (gSettingsContext.shuffleEnemySouls == SHUFFLEENEMYSOULS_OFF) ||
        (gSettingsContext.shuffleEnemySouls == SHUFFLEENEMYSOULS_BOSSES && !Actor_IsBoss(actor))) {
        return TRUE;
    }

    if (soulCheck >= SOULCHECK_COLLISION &&
        // Armos statues and asleep Armos enemies, included so they can be hit and woken up even while soulless
        ((actor->id == ACTOR_ARMOS && ((EnAm*)actor)->textureBlend == 0) ||
         // Dead Hand waiting underground can detect explosions and come out
         (actor->id == ACTOR_DEAD_HAND && actor->shape.yOffset <= -15000.0))) {
        return TRUE;
    }

    if (soulCheck >= SOULCHECK_DRAW &&
        // If enemy is culled, don't draw soulless effects
        (!(actor->flags & ACTOR_FLAG_INSIDE_CULLING_VOLUME) ||
         // If scale is zero, enemy is invisible
         (actor->scale.x == 0 && actor->scale.y == 0 && actor->scale.z == 0) ||
         // Hidden flying traps will appear normal
         FlyingTraps_IsHiddenTrap(actor) ||
         // These will just look normal because the flames appear in the wrong place
         (actor->id == ACTOR_OBSTACLE_TENTACLE &&
          gSettingsContext.soullessEnemiesLook == SOULLESSLOOK_PURPLE_FLAMES))) {
        return TRUE;
    }

    EnemySoulId soulId = EnemySouls_GetSoulId(actor->id);
    return soulId == SOUL_NONE || EnemySouls_GetSoulFlag(soulId);
}

Bool EnemySouls_IsInvulnerable(Actor* actor) {
    return !EnemySouls_CheckSoul(actor, SOULCHECK_COLLISION);
}

Bool EnemySouls_ShouldDrawSoulless(Actor* actor) {
    return !EnemySouls_CheckSoul(actor, SOULCHECK_DRAW);
}

void EnemySouls_OnCollect(EnemySoulId soulId) {
    if (EnemySouls_GetSoulFlag(soulId)) {
        return;
    }

    EnemySouls_SetSoulFlag(soulId);

    if (SoullessModels_Enabled) {
        SoullessModels_RestoreSoul(soulId);
    }
}

void EnemySouls_Update(void) {
    switch (gSettingsContext.soullessEnemiesLook) {
        case SOULLESSLOOK_PURPLE_FLAMES:
            return SoullessFlames_Draw();
        case SOULLESSLOOK_TEXTURELESS:
        case SOULLESSLOOK_GRAYSCALE:
            return SoullessModels_HandleRestoreRequest();
        default:
            return;
    }
}

/*-------------------------------
|    Soulless Flames effect     |
-------------------------------*/

#define SOULLESS_EFFECT_DURATION 8
#define SOULLESS_EFFECT_INTERVAL 3

static void SoullessFlames_SpawnFlame(Vec3f pos, f32 xRange, f32 yRange, f32 zRange, s16 scale) {
    pos.x += xRange * (Rand_ZeroOne() - 0.5);
    pos.y += yRange * (Rand_ZeroOne() - 0.5) + scale / 10;
    pos.z += zRange * (Rand_ZeroOne() - 0.5);
    Vec3f nullVec         = { 0 };
    Color_RGBA8 primColor = {
        .r = 0x6E,
        .g = 0x05,
        .b = 0xFF,
        .a = 0xFF,
    };
    Color_RGBA8 envColor = {
        .r = 0x28,
        .g = 0x00,
        .b = 0xFF,
        .a = 0xFF,
    };
    EffectSsDeadDb_Spawn(gGlobalContext, &pos, &nullVec, &nullVec, scale, -1, primColor.r, primColor.g, primColor.b,
                         primColor.a, envColor.r, envColor.g, envColor.b, 1, SOULLESS_EFFECT_DURATION, 0);
}

static void SoullessFlames_ParseCollider(Collider* collider) {
    if (collider == NULL || !EnemySouls_ShouldDrawSoulless(collider->actor)) {
        return;
    }

    u8 isBoss = collider->actor->type == ACTORTYPE_BOSS;
    switch (collider->shape) {
        case COLSHAPE_JNTSPH:
            ColliderJntSph* jntSphCol = (ColliderJntSph*)collider;
            for (s32 j = 0; j < jntSphCol->count; j++) {
                ColliderJntSphElement* elem = &jntSphCol->elements[j];
                Spheref worldSphere         = elem->dim.worldSphere;
                s16 scale                   = isBoss ? 150 : worldSphere.radius > 10.0f ? 100 : 50;
                SoullessFlames_SpawnFlame(worldSphere.center, worldSphere.radius, worldSphere.radius,
                                          worldSphere.radius, scale);
            }
            break;
        case COLSHAPE_CYLINDER:
            ColliderCylinder* cylCol = (ColliderCylinder*)collider;
            s16 scale                = isBoss ? 150 : cylCol->dim.radius > 10.0f ? 100 : 50;
            SoullessFlames_SpawnFlame(cylCol->dim.position, cylCol->dim.radius, cylCol->dim.height, cylCol->dim.radius,
                                      scale);
            break;
    }
}

static void SoullessFlames_Draw(void) {
    if (PauseContext_GetState() != 0 || rGameplayFrames % SOULLESS_EFFECT_INTERVAL != 0) {
        return;
    }

    // Parse all colliders subscribed to AC
    for (s32 i = 0; i < gGlobalContext->colChkCtx.colAcCount; i++) {
        Collider* collider = gGlobalContext->colChkCtx.colAc[i];
        SoullessFlames_ParseCollider(collider);
    }

    // Parse all colliders subscribed to OC
    for (s32 i = 0; i < gGlobalContext->colChkCtx.colOcCount; i++) {
        Collider* collider = gGlobalContext->colChkCtx.colOc[i];
        SoullessFlames_ParseCollider(collider);
    }
}

/*-------------------------------
|     Soulless Model edits      |
-------------------------------*/

// Used to delay restoring CMB data to the next frame, because some unknown things get initialized during the drawing
// process after the GameState update
u8 SoullessModels_CmbRestoreRequest = FALSE;

// Use CMB name field to store modification status
#define GET_CMB_STATUS(cmbMan) (((CMB_HEAD*)cmbMan->cmbChunk)->name[0])
#define CMBSTATUS_MODIFIED '-'
#define CMBSTATUS_RESTORED '^'

typedef struct CmbMatOriginalData {
    Color_RGBA8 ambient;
    Color_RGBA8 diffuse;
    u8 blendMode;
    u8 texEnvStageUsed;
} CmbMatOriginalData;
_Static_assert(sizeof(CmbMatOriginalData) <= sizeof(((CMB_HEAD*)0)->name) - 1, "CmbMatOriginalData size");

// Store original values for overwritten data in the material's unused Fragment struct.
// If the material does use the Fragment (like in the Freezard model) use the remaining 15 bytes in the CMB's name
// field, but remember to manually check that the model only has 1 material being modified.
static CmbMatOriginalData* CmbMat_GetOrigDataBuffer(Material* mat, CmbManager* cmbMan) {
    void* buf;
    if (mat->isFragmentLightingEnabled) {
        buf = &((CMB_HEAD*)cmbMan->cmbChunk)->name[1];
    } else {
        buf = &mat->fragLighting;
    }

    return (CmbMatOriginalData*)buf;
}

// Don't modify certain models
static Bool SoullessModels_ShouldIgnoreCmb(s16 objId, s32 cmbIdx) {
    switch (objId) {
        case OBJECT_WALLMASTER: // skip hand shadow
            return cmbIdx == 2;
        case OBJECT_TENTACLE: // skip dead blob
            return cmbIdx == 1;
        case OBJECT_DEAD_HAND: // skip dirt wave
            return cmbIdx == 2;
        case OBJECT_FREEZARD: // skip ice breath
            return cmbIdx == 1;
        case OBJECT_POE: // only main body
            return cmbIdx != 0;
        case OBJECT_POE_COMPOSER: // only main body
            return cmbIdx != 0;
        case OBJECT_KING_DODONGO: // only KD body
            return cmbIdx != 2;
        case OBJECT_BARINADE: // only arms, body and jellyfish
            return cmbIdx != 0 && cmbIdx != 3 && cmbIdx != 4 && cmbIdx != 7 && cmbIdx != 12;
        case OBJECT_VOLVAGIA: // only body parts
            return cmbIdx < 1 || cmbIdx > 6;
        case OBJECT_BONGO_BONGO: // only body & hands
            return cmbIdx < 1 || cmbIdx > 3;
        case OBJECT_GANONDORF: // only main body
            return cmbIdx != 2;
        case OBJECT_GANON: // only main body
            return cmbIdx != 0;
        case OBJECT_FLYING_FLOOR_TILE: // handled in own update function
            return TRUE;
        case OBJECT_ARMOS: // handled in own update function
            return TRUE;
    }
    return FALSE;
}

static Bool SoullessModels_ShouldIgnoreMaterial(s16 objId, s32 cmbIdx, s32 matIdx) {
    return objId == OBJECT_TENTACLE && matIdx == 1; // Don't modify electric field (for both models)
}

static void SwapBuffers(void* first, void* second, s32 size) {
    char buf[8] = { 0 };
    memcpy(&buf, first, size);
    memcpy(first, second, size);
    memcpy(second, &buf, size);
}
#define SwapFields(field) (SwapBuffers(&SWAP_BASE[0]->field, &SWAP_BASE[1]->field, sizeof(SWAP_BASE[0]->field)))

// This function applies combiner edits for some special materials. It swaps certain values between combiners in such a
// way that it can be called again to restore the original values.
static Bool SoullessModels_HandleSpecialCombiner(CMB_MATS* cmbMats, s16 objId, s32 cmbIdx, s32 matIdx) {
    Material* mat = &cmbMats->materials[matIdx];

    s16 specialStageIdx = -1;
    switch (objId) {
        case OBJECT_POE:        // fading effect
        case OBJECT_POE_SISTER: // fading effect
        case OBJECT_WALLMASTER: // color during Floormaster attack
            specialStageIdx = 1;
            break;
        case OBJECT_POE_COMPOSER: // fading effect, only for main body
            if (matIdx == 0 || matIdx == 3) {
                specialStageIdx = 1;
            }
            break;
        case OBJECT_SKULLTULA: // color during attack, only for normal walltula
            if (cmbIdx == 0 && matIdx == 1) {
                specialStageIdx = 1;
            }
            break;
        case OBJECT_REDEAD: // color while frozen by Sun's Song
            specialStageIdx = 2;
            break;
    }

    if (specialStageIdx > -1 && mat->texEnvStagesIndices[specialStageIdx] > -1) {
        Combiner* combiners    = Cmb_GetCombiners(cmbMats);
        Combiner* SWAP_BASE[2] = { &combiners[mat->texEnvStagesIndices[0]],
                                   &combiners[mat->texEnvStagesIndices[specialStageIdx]] };
        SwapFields(combinerModeColor);
        SwapFields(scaleColor);
        SwapFields(sourceColors[1]);
        SwapFields(operandColors[1]);
        SwapFields(sourceAlphas[1]);
        SwapFields(operandAlphas[1]);
        SwapFields(constantColorIndex);

        return TRUE;
    }
    return FALSE;
}

static void SoullessModels_ModifyCmb(CmbManager* cmbMan, s16 objId, s32 cmbIdx) {
    if (GET_CMB_STATUS(cmbMan) == CMBSTATUS_MODIFIED) {
        return;
    }

    GET_CMB_STATUS(cmbMan) = CMBSTATUS_MODIFIED;
    CMB_MATS* cmbMats      = Cmb_GetMatsChunk(cmbMan->cmbChunk);
    CMB_TEX* cmbTex        = Cmb_GetTexChunk(cmbMan->cmbChunk);

    if (gSettingsContext.soullessEnemiesLook == SOULLESSLOOK_TEXTURELESS) {
        // Modify materials to apply the chosen color and skip drawing the textures.
        for (s32 matIdx = 0; matIdx < cmbMats->materialCount; matIdx++) {
            if (SoullessModels_ShouldIgnoreMaterial(objId, cmbIdx, matIdx)) {
                continue;
            }

            Material* mat = &cmbMats->materials[matIdx];

            CmbMatOriginalData* origData = CmbMat_GetOrigDataBuffer(mat, cmbMan);
            origData->blendMode          = mat->blendMode;
            origData->ambient            = mat->ambient;
            origData->diffuse            = mat->diffuse;
            origData->texEnvStageUsed    = mat->texEnvStageUsed;

            // This removes transparency (for things like shaboms or biri) but it's needed to display correct colors.
            mat->blendMode = 0;

            // Set both ambient and diffuse colors to the chosen value.
            mat->ambient = mat->diffuse = gSettingsContext.soullessColor;

            // Remove all combiner stages to show only a shaded textureless color, except for some cases where one
            // combiner is kept and modified.
            if (SoullessModels_HandleSpecialCombiner(cmbMats, objId, cmbIdx, matIdx)) {
                mat->texEnvStageUsed = 1;
            } else {
                mat->texEnvStageUsed = 0;
            }
        }
    } else if (gSettingsContext.soullessEnemiesLook == SOULLESSLOOK_GRAYSCALE) {
        // Modify all combiners to use operand `green` instead of `color`, making the texture draw in grayscale.
        for (Combiner* combiner = Cmb_GetCombiners(cmbMats); (u32)combiner < (u32)cmbTex; combiner++) {
            for (s32 opIdx = 0; opIdx < ARRAY_SIZE(combiner->operandColors); opIdx++) {
                if (combiner->operandColors[opIdx] == COMBINEROP_COLOR) {
                    combiner->operandColors[opIdx] = COMBINEROP_GREEN;
                }
            }
        }
    }
};

void SoullessModels_ModifyGenericCmb(CmbManager* cmbMan) {
    SoullessModels_ModifyCmb(cmbMan, -1, -1);
}

static u8 SoullessModels_RestoreCmb(CmbManager* cmbMan, s16 objId, s32 cmbIdx) {
    if (GET_CMB_STATUS(cmbMan) != CMBSTATUS_MODIFIED) {
        return FALSE;
    }

    GET_CMB_STATUS(cmbMan) = CMBSTATUS_RESTORED;
    CMB_MATS* cmbMats      = Cmb_GetMatsChunk(cmbMan->cmbChunk);
    CMB_TEX* cmbTex        = Cmb_GetTexChunk(cmbMan->cmbChunk);

    if (gSettingsContext.soullessEnemiesLook == SOULLESSLOOK_TEXTURELESS) {
        for (s32 matIdx = 0; matIdx < cmbMats->materialCount; matIdx++) {
            if (SoullessModels_ShouldIgnoreMaterial(objId, cmbIdx, matIdx)) {
                continue;
            }
            Material* mat                = &cmbMats->materials[matIdx];
            CmbMatOriginalData* origData = CmbMat_GetOrigDataBuffer(mat, cmbMan);
            mat->blendMode               = origData->blendMode;
            mat->ambient                 = origData->ambient;
            mat->diffuse                 = origData->diffuse;
            mat->texEnvStageUsed         = origData->texEnvStageUsed;

            SoullessModels_HandleSpecialCombiner(cmbMats, objId, cmbIdx, matIdx);
        }
    } else if (gSettingsContext.soullessEnemiesLook == SOULLESSLOOK_GRAYSCALE) {
        u8 combinerRestored = FALSE;
        for (Combiner* combiner = Cmb_GetCombiners(cmbMats); (u32)combiner < (u32)cmbTex; combiner++) {
            for (s32 opIdx = 0; opIdx < ARRAY_SIZE(combiner->operandColors); opIdx++) {
                if (combiner->operandColors[opIdx] == COMBINEROP_GREEN) {
                    combiner->operandColors[opIdx] = COMBINEROP_COLOR;
                    combinerRestored               = TRUE;
                }
            }
        }
        return combinerRestored;
    }
    return TRUE;
}

static u8 SoullessModels_RestoreGenericCmb(CmbManager* cmbMan) {
    return SoullessModels_RestoreCmb(cmbMan, -1, -1);
}

void SoullessModels_BeforeCmbManagerInit(CmbManager* cmbMan, ZARInfo* zarInfo, s32 cmbIdx) {
    if (!SoullessModels_Enabled || EnemySouls_CheckSoul(gRunningActor, SOULCHECK_BASE)) {
        return;
    }

    ObjectEntry* obj = Object_FindEntryByZarInfo(zarInfo);

    // Ignore CmbManagers from global "keep" objects, even if this actor is the first one to request them (thus causing
    // them to initialize).
    if (obj == NULL || obj->id <= OBJECT_GAMEPLAY_DUNGEON_KEEP || SoullessModels_ShouldIgnoreCmb(obj->id, cmbIdx)) {
        return;
    }

    SoullessModels_ModifyCmb(cmbMan, obj->id, cmbIdx);
}

static void SoullessModels_RestoreObject(s16 objId) {
    s32 slot = Object_GetSlot(&gGlobalContext->objectCtx, objId);
    if (slot < 0 || !Object_IsLoaded(&gGlobalContext->objectCtx, slot)) {
        return;
    }

    ObjectEntry* obj = Object_GetEntry(slot);
    ZARInfo* zarInfo = &obj->zarInfo;

    s32 numCMBs = zarInfo->fileTypes[zarInfo->fileTypeMap[0]].numFiles;
    for (s32 cmbIdx = 0; cmbIdx < numCMBs; cmbIdx++) {
        CmbManager* cmbMan = zarInfo->cmbMans[cmbIdx];
        if (cmbMan == NULL) {
            continue;
        }
        // Restore original values for each CMB that was modified.
        u8 modified = SoullessModels_RestoreCmb(cmbMan, objId, cmbIdx);
        if (modified) {
            // Destroy CMB Manager so it will be reinitialized the next time it's needed.
            CmbManager_Destroy(cmbMan);
            gStaticClass_55A19C.sub44->vTable->destroyCmb(gStaticClass_55A19C.sub44, cmbMan);
            zarInfo->cmbMans[cmbIdx] = NULL;
        }
    }
}

static void SoullessModels_ReinitGenericSkelAnime(Actor* actor) {
    struct GenericSkelAnimeActor {
        /* 0x000 */ Actor actor;
        /* 0x1A4 */ SkelAnime anime;
    };
    return Actor_ReinitSkelAnime(actor, &((struct GenericSkelAnimeActor*)actor)->anime, 0);
}

static void SoullessModels_RestoreActor(Actor* actor) {
    ReinitModelsFunc reinitModelsFunc = EnemySouls_GetActorSoulData(actor->id).reinitModelsFunc;
    if (reinitModelsFunc != NULL) {
        reinitModelsFunc(actor);
    }
}

static void SoullessModels_RestoreSoul(EnemySoulId soulId) {
    for (s32 i = 0; i < ACTOR_MAX; i++) {
        ActorInit* profile = gActorOverlayTable[i].initInfo;
        if (profile != NULL && EnemySouls_GetSoulId(profile->id) == soulId) {
            if (profile->id == ACTOR_POE) {
                SoullessModels_RestoreObject(OBJECT_POE);
                SoullessModels_RestoreObject(OBJECT_POE_COMPOSER);
            } else if (profile->objectId > OBJECT_GAMEPLAY_DUNGEON_KEEP) {
                SoullessModels_RestoreObject(profile->objectId);
            }
        }
    }

    for (s32 catIdx = 0; catIdx < ACTORTYPE_MAX; catIdx++) {
        Actor* actor = gGlobalContext->actorCtx.actorList[catIdx].first;
        for (; actor != NULL; actor = actor->next) {
            if (EnemySouls_GetSoulId(actor->id) == soulId) {
                SoullessModels_RestoreActor(actor);
            }
        }
    }
}

static void SoullessModels_HandleRestoreRequest(void) {
    ObjectEntry* obj;
    if (SoullessModels_CmbRestoreRequest) {
        obj = Object_FindEntry(OBJECT_GAMEPLAY_DUNGEON_KEEP);
        if (obj != NULL && obj->zarInfo.cmbMans[POT_CMB_INDEX] != NULL) {
            SoullessModels_RestoreGenericCmb(obj->zarInfo.cmbMans[POT_CMB_INDEX]);
        }
        obj = Object_FindEntry(OBJECT_FLYING_FLOOR_TILE);
        if (obj != NULL && obj->zarInfo.cmbMans[FLYING_TILE_CMB_INDEX] != NULL) {
            SoullessModels_RestoreGenericCmb(obj->zarInfo.cmbMans[FLYING_TILE_CMB_INDEX]);
        }
        obj = Object_FindEntry(OBJECT_ARMOS);
        if (obj != NULL && obj->zarInfo.cmbMans[ARMOS_CMB_INDEX] != NULL) {
            SoullessModels_RestoreGenericCmb(obj->zarInfo.cmbMans[ARMOS_CMB_INDEX]);
        }
        SoullessModels_CmbRestoreRequest = FALSE;
    }
}
