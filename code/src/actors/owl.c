#include "z3D/z3D.h"
#include "settings.h"

#define EnOwl_Init ((ActorFunc)GAME_ADDR(0x18DB28))

#define EnOwl_Update ((ActorFunc)GAME_ADDR(0x1DCB60))

static u8 shortcutActivated = 0xFF;

void EnOwl_DespawnInit(Actor* owl, GlobalContext* globalCtx) {
    switch ((owl->params & 0x3C0) >> 6) {
        case 7:
        case 8:
        case 9:
            EnOwl_Init(owl, globalCtx);
            return;
        default:
            Actor_Kill(owl);
    }
}

void EnOwl_rUpdate(Actor* owl, GlobalContext* globalCtx) {
    EnOwl_Update(owl, globalCtx);
    // repeat this for some frames to be sure the cutscene timer
    // isn't reset to 0 by the cutscene
    if (shortcutActivated < 5) {
        if (globalCtx->sceneNum == 96) { // DMT
            globalCtx->csCtx.frames = 600;
            shortcutActivated++;
        } else if (globalCtx->sceneNum == 87 && gSettingsContext.lakeHyliaOwl == SKIP) { // Lake Hylia
            globalCtx->csCtx.frames = 500;
            shortcutActivated++;
        }
    }
}

void EnOwl_FastCutscene() {
    shortcutActivated = 0;
}
