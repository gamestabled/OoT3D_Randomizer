#include "z3D/z3D.h"

typedef struct {
    s16 objectId;
    s8 objectBankIdx;
    s8 objectModelIdx;
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
s32 Model_DrawByActor(Actor* actor);
