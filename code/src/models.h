#ifndef _MODELS_H_
#define _MODELS_H_

#include "z3D/z3D.h"
#include "item_table.h"

typedef struct {
    Actor* actor;
    ItemRow* itemRow;
    s8 objectSlot;
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

SkeletonAnimationModel* SkeletonAnimationModel_Spawn(Actor* actor, GlobalContext* globalCtx, s16 objId,
                                                     s32 objModelIdX);
void SkeletonAnimationModel_SetMesh(SkeletonAnimationModel* glModel, s32 mesh);
void DeleteModel_At(SkeletonAnimationModel** model);

#endif //_MODELS_H_
