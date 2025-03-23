#include <stddef.h>
#include <string.h>

#include "link_puppet.h"
#include "objects.h"
#include "custom_models.h"
#include "settings.h"
#include "common.h"

// Draw at most three extra Links. More can cause graphical issues that persist until game restart.
#define MAX_PUPPETS_AT_ONCE 3

ActorInit EnLinkPuppet_InitVars = {
    0x1,                             // ID
    ACTORTYPE_NPC,                   // Type
    0xFF,                            // Room
    0x2000410,                       // Flags
    21,                              // Object ID (20: Adult, 21: Child)
    sizeof(EnLinkPuppet),            //
    (ActorFunc)EnLinkPuppet_Init,    //
    (ActorFunc)EnLinkPuppet_Destroy, //
    (ActorFunc)EnLinkPuppet_Update,  //
    (ActorFunc)EnLinkPuppet_Draw,    //
};

static ColliderCylinderInit EnLinkPupper_ColliderCylinderInit = {
    {
        0x7,
        0x0,
        0x9,
        0x9,
        0x10,
        0x1,
    },
    {
        0x1,
        { 0x0, 0x0, 0x0 },
        { 0xFFCFFFFF, 0x0, 0x0 },
        0x0,
        0x5,
        0x1,
    },
    { 12.0f, 50.0f, 0.0f, { 0.0f, 0.0f, 0.0f } },
};

typedef void (*SkelAnime_InitLink_proc)(SkelAnime* skelAnime, ZARInfo* zarInfo, GlobalContext* globalCtx, void* cmbMan,
                                        void* param_5, u32 animation, s32 limbBufCount, void* jointTable,
                                        void* morphTable);
#define SkelAnime_InitLink ((SkelAnime_InitLink_proc)GAME_ADDR(0x3413EC))

// When posing the model by copying the joint table, the model for some reason gets raised about 12 units.
static const f32 childOffsetY = 12.5f;

void EnLinkPuppet_Init(EnLinkPuppet* this, GlobalContext* globalCtx) {
    this->base.room = -1;

    SkelAnime_InitLink(&this->skelAnime, PLAYER->zarInfo, globalCtx, PLAYER->cmbMan, this->base.unk_178, 0, 9,
                       this->ghostPtr->ghostData.jointTable, NULL);

    // Tunic
    void* cmabMan = NULL;
    if (gSettingsContext.customTunicColors == ON) {
        cmabMan = Object_GetCMABByIndex(OBJECT_CUSTOM_GENERAL_ASSETS,
                                        (gSaveContext.linkAge == 0) ? TEXANIM_LINK_BODY : TEXANIM_CHILD_LINK_BODY);
    } else if (gSaveContext.linkAge == 0) {
        cmabMan = ZAR_GetCMABByIndex(PLAYER->zarInfo, 2);
    }
    if (cmabMan != NULL) {
        TexAnim_Spawn(this->skelAnime.unk_28->unk_0C, cmabMan);
    }
    this->skelAnime.unk_28->unk_0C->animSpeed = 0.0f;
    this->skelAnime.unk_28->unk_0C->animMode  = 0;

    // Mesh Groups
    for (size_t index = 0; index < BIT_COUNT(this->ghostPtr->ghostData.meshGroups1); index++) {
        Model_DisableMeshGroupByIndex(this->skelAnime.unk_28, index);
    }
    for (size_t index = 0; index < BIT_COUNT(this->ghostPtr->ghostData.meshGroups2); index++) {
        Model_DisableMeshGroupByIndex(this->skelAnime.unk_28, index + BIT_COUNT(u32));
    }

    // Collision
    Collider_InitCylinder(gGlobalContext, &this->collider);
    Collider_SetCylinder(gGlobalContext, &this->collider, &this->base, &EnLinkPupper_ColliderCylinderInit);

    // Shadow
    f32 feetShadowScale = (this->ghostPtr->ghostData.age == 0) ? 90.0f : 60.0f;
    ActorShape_Init(&this->base.shape, 0.0f, (void*)GAME_ADDR(0x1D04F4), feetShadowScale);
}

typedef void (*SkelAnime_Free2_proc)(SkelAnime* anime);
#define SkelAnime_Free2 ((SkelAnime_Free2_proc)GAME_ADDR(0x350BE0))

void EnLinkPuppet_Destroy(EnLinkPuppet* this, GlobalContext* globalCtx) {
    SkelAnime_Free2(&this->skelAnime);
}

void EnLinkPuppet_Update(EnLinkPuppet* this, GlobalContext* globalCtx) {
    if (!this->ghostPtr->inUse || !this->ghostPtr->isInGame ||
        this->ghostPtr->ghostData.currentScene != gGlobalContext->sceneNum) {
        Actor_Kill(&this->base);
        return;
    }

    this->base.world.pos = this->ghostPtr->ghostData.position;
    this->base.shape.rot = this->ghostPtr->ghostData.rotation;
    // Overwrite prevPos so model doesn't get stuck to terrain because of Actor_UpdateBgCheckInfo
    this->base.prevPos = this->base.world.pos;

    // Mesh Groups
    for (size_t index = 0; index < BIT_COUNT(this->ghostPtr->ghostData.meshGroups1); index++) {
        if (this->ghostPtr->ghostData.meshGroups1 & (0b1 << index)) {
            Model_EnableMeshGroupByIndex(this->skelAnime.unk_28, index);
        } else {
            Model_DisableMeshGroupByIndex(this->skelAnime.unk_28, index);
        }
    }
    for (size_t index = 0; index < BIT_COUNT(this->ghostPtr->ghostData.meshGroups2); index++) {
        if (this->ghostPtr->ghostData.meshGroups2 & (0b1 << index)) {
            Model_EnableMeshGroupByIndex(this->skelAnime.unk_28, index + BIT_COUNT(u32));
        } else {
            Model_DisableMeshGroupByIndex(this->skelAnime.unk_28, index + BIT_COUNT(u32));
        }
    }

    // Tunic
    this->skelAnime.unk_28->unk_0C->curFrame = this->ghostPtr->ghostData.currentTunic;

    // Collider
    Collider_UpdateCylinder(&this->base, &this->collider);
    CollisionCheck_SetOC(gGlobalContext, &gGlobalContext->colChkCtx, &this->collider);
    CollisionCheck_SetAC(gGlobalContext, &gGlobalContext->colChkCtx, &this->collider);

    // Shadow
    f32 ceilingCheckHeight = (this->ghostPtr->ghostData.age == 0) ? 56.0f : 40.0f;
    Actor_UpdateBgCheckInfo(gGlobalContext, (Actor*)this, 26.0f, 6.0f, ceilingCheckHeight, 7);

    // Child Y position workaround
    if (this->ghostPtr->ghostData.age != 0) {
        this->base.world.pos.y -= childOffsetY;
    }
}

#define Vec3f_PlayerFeet_unk ((Vec3f*)GAME_ADDR(0x53CACC))
void EnLinkPuppet_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, nn_math_MTX34* mtx, EnLinkPuppet* this) {
    if (limbIndex != 0x15) {
        Actor_SetFeetPos((Actor*)this, mtx, limbIndex, 5, &Vec3f_PlayerFeet_unk[gSaveContext.linkAge], 8,
                         &Vec3f_PlayerFeet_unk[gSaveContext.linkAge]);
    }
}

typedef void (*SkelAnime_DrawOpa_proc)(SkelAnime* skelAnime, nn_math_MTX34* modelMtx, void* overrideLimbDraw,
                                       void* postLimbDraw, Actor* param_5, u32 param_6);
#define SkelAnime_DrawOpa ((SkelAnime_DrawOpa_proc)GAME_ADDR(0x35E240))

void EnLinkPuppet_Draw(EnLinkPuppet* this, GlobalContext* globalCtx) {
    // Check how many Link puppets already exist before this one.
    u8 linkPuppetCount = 0;
    Actor* firstActor  = gGlobalContext->actorCtx.actorList[EnLinkPuppet_InitVars.type].first;
    for (Actor* actor = firstActor; actor != NULL; actor = actor->next) {
        if (actor == &this->base) {
            break;
        }
        if (actor->id == EnLinkPuppet_InitVars.id) {
            linkPuppetCount++;
        }
    }

    if (linkPuppetCount < MAX_PUPPETS_AT_ONCE && this->ghostPtr->ghostData.age == gSaveContext.linkAge) {
        SkelAnime_DrawOpa(&this->skelAnime, &this->base.modelMtx, NULL, EnLinkPuppet_PostLimbDraw, &this->base, 0);
        return;
    }

    // Only draw flames every 4th frame
    if (rGameplayFrames % 4 == 0) {
        static Vec3f vecEmpty;
        static f32 colorR[] = { 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.5 };
        static f32 colorG[] = { 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.5, 0.0 };
        static f32 colorB[] = { 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0 };

        s16 envR = 100 * colorR[(this->base.params - 1) % ARRAY_SIZE(colorR)];
        s16 envG = 100 * colorG[(this->base.params - 1) % ARRAY_SIZE(colorG)];
        s16 envB = 100 * colorB[(this->base.params - 1) % ARRAY_SIZE(colorB)];

        Vec3f spawnPos = this->base.world.pos;
        spawnPos.y += (this->ghostPtr->ghostData.age == 0) ? 50 : (35 + childOffsetY);
        EffectSsDeadDb_Spawn(gGlobalContext, &spawnPos, &vecEmpty, &vecEmpty,
                             this->ghostPtr->ghostData.age == 0 ? 100 : 70, -1, 80, 80, 80, 0xFF, envR, envG, envB, 1,
                             8, 0);
    }
}
