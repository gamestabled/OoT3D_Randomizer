#ifndef _ENEMIZER_H_
#define _ENEMIZER_H_

#include "../include/z3D/z3D.h"

#define ENEMY_OVERRIDES_MAX 800

// This enum's values are sorted so that the enemy names
// appear in alphabetical order in the app.
typedef enum EnemyId {
    ENEMY_INVALID,
    ENEMY_ANUBIS,
    ENEMY_ARMOS,
    ENEMY_BARI,
    ENEMY_BEAMOS,
    ENEMY_BIG_OCTO,
    ENEMY_BIRI,
    ENEMY_BUBBLE_BLUE,
    ENEMY_BUBBLE_FIRE,
    ENEMY_BUBBLE_GREEN,
    ENEMY_BUBBLE_WHITE,
    ENEMY_DARK_LINK,
    ENEMY_DEAD_HAND,
    ENEMY_DEAD_HAND_HAND,
    ENEMY_DEKU_BABA_SMALL,
    ENEMY_DEKU_BABA_BIG,
    ENEMY_DEKU_BABA_WITHERED,
    ENEMY_HINT_DEKU_SCRUB,
    ENEMY_DINOLFOS,
    ENEMY_DODONGO,
    ENEMY_DODONGO_BABY,
    ENEMY_FLARE_DANCER,
    ENEMY_FLOORMASTER,
    ENEMY_FLYING_FLOOR_TILE,
    ENEMY_FLYING_POT,
    ENEMY_FREEZARD,
    ENEMY_GERUDO_FIGHTER,
    ENEMY_GIBDO,
    ENEMY_GOHMA_LARVA,
    ENEMY_GUAY,
    ENEMY_IRON_KNUCKLE,
    ENEMY_KEESE_NORMAL,
    ENEMY_KEESE_FIRE,
    ENEMY_KEESE_ICE,
    ENEMY_LEEVER,
    ENEMY_LIKE_LIKE,
    ENEMY_LIZALFOS,
    ENEMY_MAD_SCRUB,
    ENEMY_MOBLIN_CLUB,
    ENEMY_MOBLIN_SPEAR,
    ENEMY_OCTOROK,
    ENEMY_PARASITIC_TENTACLE,
    ENEMY_PEAHAT,
    ENEMY_PEAHAT_LARVA,
    ENEMY_POE,
    ENEMY_POE_SISTER,
    ENEMY_REDEAD,
    ENEMY_SHABOM,
    ENEMY_SHELL_BLADE,
    ENEMY_SKULLTULA,
    ENEMY_SKULLWALLTULA,
    ENEMY_SKULL_KID,
    ENEMY_SPIKE,
    ENEMY_STALCHILD,
    ENEMY_STALFOS,
    ENEMY_STINGER_FLOOR,
    ENEMY_STINGER_WATER,
    ENEMY_TAILPASARAN,
    ENEMY_TEKTITE_BLUE,
    ENEMY_TEKTITE_RED,
    ENEMY_TORCH_SLUG,
    ENEMY_WALLMASTER,
    ENEMY_WOLFOS,
    ENEMY_MAX,
} EnemyId;

typedef struct EnemyActorData {
    s16 actorId;
    s16 actorParams;
    u8 anyParams;
} EnemyActorData;

typedef struct EnemyObjectDependency {
    EnemyActorData key;
    u16 objectId;
} EnemyObjectDependency;

typedef struct EnemyOverride {
    union {
        s32 key;
        struct {
            u8 actorEntry;
            u8 room;
            u8 layer;
            u8 scene;
        };
    };
    s16 actorId;
    s16 params;
} EnemyOverride;

typedef struct EnemizerLocationFlags {
    u8 sfmWolfos : 1;
    u8 dcLizalfos : 1;
    u8 gerudoFighters : 1;
    u8 nabooruKnuckle : 1;
    u8 shadowShipStalfos : 1;
} EnemizerLocationFlags;

// Helper flags to check if specific location overrides exist
extern EnemizerLocationFlags gEnemizerLocationFlags;

u8 Enemizer_IsEnemyRandomized(EnemyId enemyId);
void Enemizer_Init(void);
void Enemizer_Update(void);
u8 Enemizer_OverrideActorEntry(ActorEntry* entry, s32 actorEntryIndex);
void Enemizer_AfterActorSetup(void);
EnemyOverride Enemizer_GetSpawnerOverride(void);
u8 Enemizer_IsRoomCleared(void);
void Enemizer_MoveSpecificEnemies(ActorEntry* actorEntry);

#endif // _ENEMIZER_H_
