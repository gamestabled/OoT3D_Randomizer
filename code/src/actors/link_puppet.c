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
    0x1,                  // ID
    ACTORTYPE_NPC,        // Type
    0xFF,                 // Room
    0b110000,             // Flags
    21,                   // Object ID (20: Adult, 21: Child)
    sizeof(EnLinkPuppet), //
    EnLinkPuppet_Init,    //
    EnLinkPuppet_Destroy, //
    EnLinkPuppet_Update,  //
    EnLinkPuppet_Draw,    //
};

// When posing the model by copying the joint table, the model for some reason gets raised about 12 units.
u32 ChildYPosOffset() {
    return playingOnCitra ? 12.5f : 0;
}

typedef void (*SkelAnime_InitLink_proc)(SkelAnime* skelAnime, ZARInfo* zarInfo, GlobalContext* globalCtx, void* cmbMan,
                                        void* param_5, u32 animation, s32 limbBufCount, void* jointTable,
                                        void* morphTable);
#define SkelAnime_InitLink ((SkelAnime_InitLink_proc)0x3413EC)

void EnLinkPuppet_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnLinkPuppet* this = (EnLinkPuppet*)thisx;

    this->base.room = -1;

    SkelAnime_InitLink(&this->skelAnime, PLAYER->zarInfo, globalCtx, PLAYER->cmbMan, thisx->unk_178, 0, 9, NULL, NULL);

    // Tunic
    void* cmabMan = NULL;
    if (gSettingsContext.customTunicColors == ON) {
        s16 exObjectBankIdx = Object_GetIndex(&rExtendedObjectCtx, OBJECT_CUSTOM_GENERAL_ASSETS);
        if (exObjectBankIdx >= 0) {
            cmabMan = ZAR_GetCMABByIndex(&rExtendedObjectCtx.status[exObjectBankIdx].zarInfo,
                                         (gSaveContext.linkAge == 0) ? TEXANIM_LINK_BODY : TEXANIM_CHILD_LINK_BODY);
        }
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
}

typedef void (*SkelAnime_Free2_proc)(SkelAnime* anime);
#define SkelAnime_Free2 ((SkelAnime_Free2_proc)0x350BE0)

void EnLinkPuppet_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnLinkPuppet* this = (EnLinkPuppet*)thisx;

    SkelAnime_Free2(&this->skelAnime);
}

void EnLinkPuppet_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnLinkPuppet* this = (EnLinkPuppet*)thisx;

    if (this->ghostPtr == NULL) {
        // Need to set the ghost data pointer first!
        return;
    }

    if (!this->ghostPtr->inUse) {
        Actor_Kill(thisx);
        return;
    }

    if (this->ghostPtr->ghostData.currentScene != gGlobalContext->sceneNum) {
        Actor_Kill(thisx);
        return;
    }

    this->base.world.pos = this->ghostPtr->ghostData.position;
    this->base.shape.rot = this->ghostPtr->ghostData.rotation;

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

    // Limbs
    if (playingOnCitra) {
        memcpy(this->skelAnime.jointTable, this->ghostPtr->ghostData.jointTable,
               sizeof(this->ghostPtr->ghostData.jointTable));
    }

    // Child Y position workaround
    if (this->ghostPtr->ghostData.age != 0) {
        this->base.world.pos.y -= ChildYPosOffset();
    }
}

typedef void (*SkelAnime_DrawOpa_proc)(SkelAnime* skelAnime, nn_math_MTX34* modelMtx, u32* overrideLimbDraw,
                                       u32* postLimbDraw, Actor* param_5, u32 param_6);
#define SkelAnime_DrawOpa ((SkelAnime_DrawOpa_proc)0x35E240)

typedef void (*EffectSsDeadDb_Spawn_proc)(GlobalContext* globalCtx, Vec3f* position, Vec3f* velocity,
                                          Vec3f* acceleration, s16 scale, s16 scale_step, s16 prim_r, s16 prim_g,
                                          s16 prim_b, s16 prim_a, s16 env_r, s16 env_g, s16 env_b, s16 unused,
                                          s32 frame_duration, s16 play_sound);
#define EffectSsDeadDb_Spawn_addr 0x3642F4
#define EffectSsDeadDb_Spawn ((EffectSsDeadDb_Spawn_proc)EffectSsDeadDb_Spawn_addr)

void EnLinkPuppet_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnLinkPuppet* this = (EnLinkPuppet*)thisx;

    // Check how many Link puppets already exist before this one.
    u8 linkPuppetCount = 0;
    Actor* firstActor  = gGlobalContext->actorCtx.actorList[EnLinkPuppet_InitVars.type].first;
    for (Actor* actor = firstActor; actor != NULL; actor = actor->next) {
        if (actor == thisx) {
            break;
        }
        if (actor->id == EnLinkPuppet_InitVars.id) {
            linkPuppetCount++;
        }
    }

    if (linkPuppetCount < MAX_PUPPETS_AT_ONCE && this->ghostPtr->ghostData.age == gSaveContext.linkAge) {
        SkelAnime_DrawOpa(&this->skelAnime, &this->base.modelMtx, NULL, NULL, thisx, 0);
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
        spawnPos.y += (this->ghostPtr->ghostData.age == 0 ? 50 : (35 + ChildYPosOffset()));
        EffectSsDeadDb_Spawn(gGlobalContext, &spawnPos, &vecEmpty, &vecEmpty,
                             this->ghostPtr->ghostData.age == 0 ? 100 : 70, -1, 80, 80, 80, 0xFF, envR, envG, envB, 1,
                             8, 0);
    }
}
