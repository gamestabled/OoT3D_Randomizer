#include "z3D/z3D.h"
#include "settings.h"

s32 Stalchild_CanDespawn(Actor* stalchild) {
    return gSettingsContext.enemizer == OFF ||
           (stalchild->parent != NULL && (gGlobalContext->sceneNum == SCENE_HYRULE_FIELD ||
                                          Math_Vec3f_DistXZ(&stalchild->home.pos, &PLAYER->actor.world.pos) > 800.0f));
}
