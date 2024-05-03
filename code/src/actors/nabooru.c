#include "z3D/z3D.h"
#include "nabooru.h"

#define EnNb_Draw ((ActorFunc)GAME_ADDR(0x1B7FBC))

void EnNb_rDraw(Actor* thisx, GlobalContext* globalCtx) {

    // if the scene is Spirit Boss, Nabooru Knuckle is defeated and Nabooru is on the ground, reload scene
    //(Nabooru is teleported to ground level when the cutscene starts, her actor is initially loaded elsewhere)
    if (globalCtx->sceneNum == 23 && (globalCtx->actorCtx.flags.swch & 0x00000020) && thisx->prevPos.y == 0) {
        globalCtx->nextEntranceIndex = 0x008D;
        globalCtx->sceneLoadFlag     = 0x14;
    }

    EnNb_Draw(thisx, globalCtx);
}
