#include "z3D/z3D.h"
#include "models.h"
#include "item_override.h"
#include "item_table.h"
#include "objects.h"
#include "custom_models.h"
#include "settings.h"
#include "common.h"
#include <stddef.h>

typedef void (*SkeletonAnimationModel_MatrixCopy_proc)(SkeletonAnimationModel* glModel, nn_math_MTX34* mtx);
#define SkeletonAnimationModel_MatrixCopy_addr 0x3721E0
#define SkeletonAnimationModel_MatrixCopy \
    ((SkeletonAnimationModel_MatrixCopy_proc)SkeletonAnimationModel_MatrixCopy_addr)

typedef void (*SkeletonAnimationModel_Draw_proc)(SkeletonAnimationModel* glModel, s32 param_2);
#define SkeletonAnimationModel_Draw_addr 0x372170
#define SkeletonAnimationModel_Draw ((SkeletonAnimationModel_Draw_proc)SkeletonAnimationModel_Draw_addr)

typedef void (*SkeletonAnimationModel_SpawnAt_proc)(Actor* actor, GlobalContext* globalCtx,
                                                    SkeletonAnimationModel** glModel, s32 objModelIdx);
#define SkeletonAnimationModel_SpawnAt_addr 0x372F38
#define SkeletonAnimationModel_SpawnAt ((SkeletonAnimationModel_SpawnAt_proc)SkeletonAnimationModel_SpawnAt_addr)

typedef void (*Actor_SetModelMatrix_proc)(f32 x, f32 y, f32 z, nn_math_MTX34* mtx, ActorShape* shape);
#define Actor_SetModelMatrix_addr 0x3679D0
#define Actor_SetModelMatrix ((Actor_SetModelMatrix_proc)Actor_SetModelMatrix_addr)

#define LOADEDMODELS_MAX 16
Model ModelContext[LOADEDMODELS_MAX] = { 0 };

void Model_SetAnim(SkeletonAnimationModel* model, s16 objectId, u32 objectAnimIdx) {
    void* cmabMan = ExtendedObject_GetCMABByIndex(objectId, objectAnimIdx);
    TexAnim_Spawn(model->unk_0C, cmabMan);
}

void Model_Init(Model* model, GlobalContext* globalCtx) {
    // Should probably parse the ZAR to find the CMBs correctly,
    // but this is fine for now
    void* ZARBuf = rExtendedObjectCtx.status[model->objectBankIdx - OBJECT_EXCHANGE_BANK_MAX].zarInfo.buf;

    // edit the cmbs for custom models
    CustomModels_EditItemCMB(ZARBuf, model->itemRow->objectId, model->itemRow->special);

    model->saModel =
        SkeletonAnimationModel_Spawn(model->actor, globalCtx, model->itemRow->objectId, model->itemRow->objectModelIdx);

    if (model->itemRow->objectId == 0x017F) { // Set the mesh for rupees
        SkeletonAnimationModel_SetMesh(model->saModel, model->itemRow->special);
    }

    CustomModels_ApplyItemCMAB(model->saModel, model->itemRow->objectId, model->itemRow->special);

    if (model->itemRow->cmabIndex >= 0) {
        Model_SetAnim(model->saModel, model->itemRow->objectId, model->itemRow->cmabIndex);
        model->saModel->unk_0C->animSpeed = 2.0f;
        model->saModel->unk_0C->animMode  = 1;
    }

    if (model->itemRow->objectModelIdx2 >= 0) {
        model->saModel2 = SkeletonAnimationModel_Spawn(model->actor, globalCtx, model->itemRow->objectId,
                                                       model->itemRow->objectModelIdx2);
        if (model->itemRow->cmabIndex2 >= 0) {
            Model_SetAnim(model->saModel2, model->itemRow->objectId, model->itemRow->cmabIndex2);
            model->saModel2->unk_0C->animSpeed = 2.0f;
            model->saModel2->unk_0C->animMode  = 1;
        }
    }

    model->loaded = 1;
}

void Model_Destroy(Model* model) {
    if (model->saModel != NULL) {
        model->saModel->vtbl->destroy(model->saModel);
        model->saModel = NULL;
    }
    if (model->saModel2 != NULL) {
        model->saModel2->vtbl->destroy(model->saModel2);
        model->saModel2 = NULL;
    }

    model->actor   = NULL;
    model->itemRow = NULL;
    model->loaded  = 0;
}

void Model_UpdateAll(GlobalContext* globalCtx) {
    Model* model;

    Object_UpdateBank((ObjectContext*)&rExtendedObjectCtx);

    for (s32 i = 0; i < LOADEDMODELS_MAX; ++i) {
        model = &ModelContext[i];

        // No actor, considered unused
        if (model->actor == NULL) {
            continue;
        }

        // Actor has been killed, destroy the model
        if (model->actor->update == NULL) {
            Model_Destroy(model);
            continue;
        }

        // Actor is alive, model has not been loaded yet
        if ((model->actor != NULL) && (!model->loaded)) {
            if (ExtendedObject_IsLoaded(&globalCtx->objectCtx, model->objectBankIdx)) {
                Model_Init(model, globalCtx);
            }
        }
    }
}

void Actor_SetModelMatrixWrapper(Actor* actor, nn_math_MTX34* mtx) {
    asm volatile("push {r0-r12, lr}\n"
                 "vldr s1,[r0,#0x2C]\n"
                 "vldr s0,[r0,#0xC4]\n"
                 "vldr s2,[r0,#0x58]\n"
                 "vmla.f32 s1,s0,s2\n"  // y coord calc
                 "vldr s0,[r0,#0x28]\n" // x coord
                 "vldr s2,[r0,#0x30]\n" // z coord
                 "add r2,r0,#0xBC\n"
                 "mov r0,r1\n" // mtx
                 "mov r1,r2\n" // shape
                 "push {r0-r12, lr}\n"
                 "bl 0x3679D0\n"
                 "pop {r0-r12, lr}\n"
                 "pop {r0-r12, lr}\n");
}

void Model_UpdateMatrix(Model* model) {
    nn_math_MTX44 scaleMtx = { 0 };
    Actor_SetModelMatrixWrapper(model->actor, &model->saModel->mtx);
    if (model->saModel2 != NULL) {
        f32 tempRotY = model->actor->shape.rot.y;
        // The second model should always face the camera, except for Skull Token
        if (model->itemRow->objectId != 0x015C) {
            model->actor->shape.rot.y = gGlobalContext->mainCamera.camDir.y;
        }
        Actor_SetModelMatrixWrapper(model->actor, &model->saModel2->mtx);
        model->actor->shape.rot.y = tempRotY;
    }

    scaleMtx.data[0][0] = model->scale;
    scaleMtx.data[1][1] = model->scale;
    scaleMtx.data[2][2] = model->scale;
    scaleMtx.data[3][3] = 1.0f;

    Matrix_Multiply(&model->saModel->mtx, &model->saModel->mtx, &scaleMtx);
    Matrix_UpdatePosition(&model->saModel->mtx, &model->saModel->mtx, &model->posOffset);
    if (model->saModel2 != NULL) {
        Matrix_Multiply(&model->saModel2->mtx, &model->saModel2->mtx, &scaleMtx);
        Matrix_UpdatePosition(&model->saModel->mtx, &model->saModel->mtx, &model->posOffset);
    }
}

void Model_Draw(Model* model) {
    if (model->loaded) {
        if (model->saModel != NULL) {
            model->saModel->unk_AC = 1;
            Model_UpdateMatrix(model);
            SkeletonAnimationModel_Draw(model->saModel, 0); // TODO is 0 always okay?
        }
        if (model->saModel2 != NULL) {
            model->saModel2->unk_AC = 1;
            Model_UpdateMatrix(model);
            SkeletonAnimationModel_Draw(model->saModel2, 0);
        }
    }
}

void Model_LookupByOverride(Model* model, ItemOverride override) {
    if (override.key.all != 0) {
        u16 itemId         = override.value.looksLikeItemId ? override.value.looksLikeItemId : override.value.itemId;
        u16 resolvedItemId = ItemTable_ResolveUpgrades(itemId);
        model->itemRow     = ItemTable_GetItemRow(resolvedItemId);
    }
}

void Model_GetObjectBankIndex(Model* model, Actor* actor, GlobalContext* globalCtx) {
    s32 objectBankIdx = ExtendedObject_GetIndex(&globalCtx->objectCtx, model->itemRow->objectId);
    if (objectBankIdx < 0) {
        objectBankIdx = ExtendedObject_Spawn(&globalCtx->objectCtx, model->itemRow->objectId);
    }
    model->objectBankIdx = objectBankIdx;
}

void Model_InfoLookup(Model* model, Actor* actor, GlobalContext* globalCtx, u16 baseItemId) {
    ItemOverride override;

    // Special case for bombchu drops
    if ((actor->id == 0x15) && (actor->params == 5)) {
        model->itemRow = ItemTable_GetItemRow(GI_BOMBCHUS_5);
        Model_GetObjectBankIndex(model, actor, globalCtx);
        return;
    }

    // Special lookup for the Zora's Sapphire in the Big Octo room
    if ((actor->id == 0x8B) && (globalCtx->sceneNum == 0x02)) {
        ItemOverride_Key key = { .all = 0 };
        key.scene            = 0xFF;
        key.type             = OVR_TEMPLE;
        key.flag             = DUNGEON_JABUJABUS_BELLY;
        override             = ItemOverride_LookupByKey(key);
        if (override.key.all != 0) {
            // Unrotate the Spiritual Stones
            actor->shape.rot.x = 0;
        }
    } else {
        override = ItemOverride_Lookup(actor, globalCtx->sceneNum, baseItemId);
    }

    if (override.key.all != 0) {
        Model_LookupByOverride(model, override);
        Model_GetObjectBankIndex(model, actor, globalCtx);
    }
}

void Model_Create(Model* model, GlobalContext* globalCtx) {
    Model* newModel = NULL;

    for (s32 i = 0; i < LOADEDMODELS_MAX; ++i) {
        if ((ModelContext[i].actor == NULL) && (ModelContext[i].saModel == NULL)) {
            newModel = &ModelContext[i];
            break;
        }
    }

    if (newModel != NULL) {
        newModel->actor         = model->actor;
        newModel->itemRow       = model->itemRow;
        newModel->objectBankIdx = model->objectBankIdx;
        newModel->loaded        = 0;
        newModel->saModel       = NULL;
        newModel->saModel2      = NULL;
        switch (newModel->itemRow->objectId) {
            case 0x00BA: // Medallions
            case 0x019C: // Kokiri Emerald
            case 0x019D: // Goron Ruby
            case 0x019E: // Zora Sapphire
                newModel->scale     = 0.2f;
                newModel->posOffset = (Vec3f){ 0 };
                break;
            case OBJECT_CUSTOM_TRIFORCE_PIECE:
                newModel->scale     = 0.025f;
                newModel->posOffset = (Vec3f){ 0.0f, -800.0f, 0.0f };
                break;
            default:
                newModel->scale     = 0.3f;
                newModel->posOffset = (Vec3f){ 0 };
                break;
        }
    }
}

void Model_SpawnByActor(Actor* actor, GlobalContext* globalCtx, u16 baseItemId) {
    Model model = { NULL, NULL, 0, 0, NULL, NULL };

    Model_InfoLookup(&model, actor, globalCtx, baseItemId);
    if (model.itemRow != NULL) {
        model.actor = actor;
        Model_Create(&model, globalCtx);
    }
}

void Model_DestroyByActor(Actor* actor) {
    for (s32 i = 0; i < LOADEDMODELS_MAX; ++i) {
        if (ModelContext[i].actor == actor) {
            Model_Destroy(&ModelContext[i]);
        }
    }
}

void Model_DestroyAll(void) {
    for (s32 i = 0; i < LOADEDMODELS_MAX; ++i) {
        Model_Destroy(&ModelContext[i]);
    }
}

s32 Model_DrawByActor(Actor* actor) {
    s32 actorDrawn = 0;

    for (s32 i = 0; i < LOADEDMODELS_MAX; ++i) {
        if (ModelContext[i].actor == actor) {
            actorDrawn = 1;
            Model_Draw(&ModelContext[i]);
        }
    }
    return actorDrawn;
}

u32 Model_OverrideMesh(void* unk, u32 meshGroupIndex) {
    // When adult Link holds a deku stick, draw unused deku stick instead of shield.
    if (IsInGameOrBossChallenge() && gSaveContext.linkAge == AGE_ADULT && gSettingsContext.stickAsAdult &&
        PLAYER->heldItemActionParam == 6 && // holding a deku stick
        meshGroupIndex == 23 &&             // meshGroupIndex for deku stick in child object and shield in adult object
        unk == PLAYER->skelAnime.unk_28->unk_draw_struct_14 // check that this is for the player model
    ) {
        return 44; // meshGroupIndex for unused deku stick in adult object
    }

    return meshGroupIndex;
}
