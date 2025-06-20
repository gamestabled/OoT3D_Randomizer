#include "leever.h"
#include "settings.h"

#define EnReeba_SetupSurface ((EnReebaActionFunc)GAME_ADDR(0x181394))

s32 Leever_ShouldSurviveOutsideSand(Actor* actor) {
    return gSettingsContext.enemizer == ON &&
           (actor->parent == NULL ||
            (gGlobalContext->sceneNum != SCENE_DESERT_COLOSSUS && gGlobalContext->sceneNum != SCENE_HAUNTED_WASTELAND));
}

void Leever_AfterSink(EnReeba* leever) {
    if (gSettingsContext.enemizer == ON && leever->actor.parent == NULL) {
        leever->actor.world.pos = leever->actor.home.pos;
        leever->actionFunc      = EnReeba_SetupSurface;
    } else {
        Actor_Kill(&leever->actor);
    }
}

void Leever_AfterDie(Actor* actor) {
    if (gSettingsContext.enemizer == ON && actor->parent == NULL && actor->colChkInfo.health == 0) {
        Actor_Kill(actor);
    }
}
