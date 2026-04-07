#ifndef _ENEMIZER_H_
#define _ENEMIZER_H_

#include "s_enemizer.h"

#include "z3D/z3D.h"

typedef struct EnemyActorData {
    s16 actorId;
    s16 actorParams;
    u8 anyParams;
} EnemyActorData;

typedef struct EnemyObjectDependency {
    EnemyActorData key;
    u16 objectId;
} EnemyObjectDependency;

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
