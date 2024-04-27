#ifndef _MODELS_H_
#define _MODELS_H_

#include "z3D/z3D.h"
#include "item_table.h"

typedef struct {
    Actor* actor;
    ItemRow* itemRow;
    s8 objectBankIdx;
    u8 loaded;
    SkeletonAnimationModel* saModel;
    SkeletonAnimationModel* saModel2;
    f32 scale;
    Vec3f posOffset;
} Model;

void Model_UpdateAll(GlobalContext* globalCtx);

void Model_SpawnByActor(Actor* actor, GlobalContext* globalCtx, u16 baseItemId);
void Model_DestroyByActor(Actor* actor);
void Model_DestroyAll(void);
s32 Model_DrawByActor(Actor* actor);
void Model_SetAnim(SkeletonAnimationModel* model, s16 objectId, u32 objectAnimIdx);

typedef SkeletonAnimationModel* (*SkeletonAnimationModel_Spawn_proc)(Actor* actor, GlobalContext* globalCtx, s16 objId,
                                                                     s32 objModelIdX);
#define SkeletonAnimationModel_Spawn ((SkeletonAnimationModel_Spawn_proc)GAME_ADDR(0x36A924))

typedef void (*SkeletonAnimationModel_SetMesh_proc)(SkeletonAnimationModel* glModel, s32 mesh);
#define SkeletonAnimationModel_SetMesh ((SkeletonAnimationModel_SetMesh_proc)GAME_ADDR(0x369178))

typedef void (*DeleteModel_At_proc)(SkeletonAnimationModel** model);
#define DeleteModel_At ((DeleteModel_At_proc)GAME_ADDR(0x357248))

#endif //_MODELS_H_
