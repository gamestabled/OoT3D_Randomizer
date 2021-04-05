#ifndef _MODELS_H_
#define _MODELS_H_

#include "z3D/z3D.h"

typedef struct {
    s16 objectId;
    s8 objectBankIdx;
    s8 objectModelIdx;
    s32 objectMeshId;
} ObjectInfo;

typedef struct {
    Actor* actor;
    ObjectInfo info;
    u32 loaded;
    GlModel* glModel;
    f32 scale;
} Model;

void Model_UpdateAll(GlobalContext* globalCtx);

void Model_SpawnByActor(Actor* actor, GlobalContext* globalCtx, u16 baseItemId);
void Model_DestroyByActor(Actor* actor);
void Model_DestroyAll(void);
s32 Model_DrawByActor(Actor* actor);

#endif //_MODELS_H_
