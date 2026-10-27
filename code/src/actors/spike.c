#include "spike.h"
#include "actor.h"

void EnNy_Init(Actor* thisx, GlobalContext* globalCtx);

void EnNy_rInit(Actor* thisx, GlobalContext* globalCtx) {
    EnNy_Init(thisx, globalCtx);

    // Check ground height below actor, starting from slightly above the actor's real position
    CollisionPoly floorPoly;
    Vec3f actorPos = (Vec3f){
        .x = thisx->world.pos.x,
        .y = thisx->world.pos.y + 50,
        .z = thisx->world.pos.z,
    };
    f32 yGroundIntersect = BgCheck_RaycastDown1(&globalCtx->colCtx, &floorPoly, &actorPos);
    // Raise the Spike off the ground. This fixes an issue causing randomized Spikes in Hyper mode to fall through the
    // floor in Ganon's Tower.
    if (thisx->world.pos.y - yGroundIntersect < 20.0f) {
        thisx->world.pos.y += 20.0f;
    }
}

void EnNy_ReinitModels(EnNy* this) {
    Actor_DestroySkelModelsArray(&this->actor, 15, &this->stoneCoreModel);
    ZARInfo* zarInfo = Actor_CreateSkelModels(
        &this->actor, gGlobalContext, &this->stoneCoreModel, 0, &this->smoothCoreModel, 1, &this->spikesModel, 2,
        &this->debrisModels[0], 0, &this->debrisModels[1], 0, &this->debrisModels[2], 0, &this->debrisModels[3], 0,
        &this->debrisModels[4], 0, &this->debrisModels[5], 0, &this->debrisModels[6], 0, &this->debrisModels[7], 0,
        &this->smokeModels[0], 3, &this->smokeModels[1], 3, &this->smokeModels[2], 3, &this->smokeModels[3], 3, NULL);

    void* cmabMan = ZAR_GetCMABByIndex(zarInfo, 0);
    for (s32 i = 0; i < 4; i++) {
        MatAnim_Init(this->smokeModels[i]->matAnim, cmabMan);
        this->smokeModels[i]->matAnim->animMode  = 1;
        this->smokeModels[i]->matAnim->animSpeed = 2.0;
    }
}
