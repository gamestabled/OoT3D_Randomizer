#ifndef _MODELS_H_
#define _MODELS_H_

#include "z3D/z3D.h"

typedef struct {
    s16 objectId;
    s8 objectBankIdx;
    s8 objectModelIdx;
    s32 objectMeshId; //or anim frame
} ObjectInfo;

typedef struct {
    Actor* actor;
    ObjectInfo info;
    u32 loaded;
    SkeletonAnimationModel* glModel;
    f32 scale;
} Model;

void Model_UpdateAll(GlobalContext* globalCtx);

void Model_SpawnByActor(Actor* actor, GlobalContext* globalCtx, u16 baseItemId);
void Model_DestroyByActor(Actor* actor);
void Model_DestroyAll(void);
s32 Model_DrawByActor(Actor* actor);

typedef SkeletonAnimationModel* (*SkeletonAnimationModel_Spawn_proc)(Actor* actor, GlobalContext* globalCtx, s16 objId, s32 objModelIdX);
#define SkeletonAnimationModel_Spawn_addr 0x36A924
#define SkeletonAnimationModel_Spawn ((SkeletonAnimationModel_Spawn_proc)SkeletonAnimationModel_Spawn_addr)

typedef void (*DeleteModel_At_proc)(SkeletonAnimationModel** model);
#define DeleteModel_At_addr 0x357248
#define DeleteModel_At ((DeleteModel_At_proc)DeleteModel_At_addr)

#endif //_MODELS_H_
