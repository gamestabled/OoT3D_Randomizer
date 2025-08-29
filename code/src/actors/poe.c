#include "poe.h"
#include "settings.h"

#define EnPoh_Init ((ActorFunc)GAME_ADDR(0x18DF00))
#define EnPoh_Update ((ActorFunc)GAME_ADDR(0x24D368))

/**
 * Composer Brothers set some flags when they spawn and when the player talks to them.
 * This function prevents them from affecting the current scene by either overriding
 * these flags or moving them to the Graveyard scene.
 */
static void Poe_CallActorFunc(ActorFunc actorFunc, Actor* thisx, GlobalContext* globalCtx) {
    ActorFlags prevFlags;
    u8 isRandomizedComposerBrother = Enemizer_IsEnemyRandomized(ENEMY_POE) && (thisx->params & 0x0002) == 0x0002 &&
                                     globalCtx->sceneNum != SCENE_GRAVEYARD;

    if (isRandomizedComposerBrother) {
        prevFlags                          = globalCtx->actorCtx.flags;
        globalCtx->actorCtx.flags.swch     = gSaveContext.sceneFlags[83].swch;
        globalCtx->actorCtx.flags.tempSwch = 0;
        Flags_UnsetSwitch(globalCtx, 0x9); // This flag makes Composer Brothers stop spawning
    }

    actorFunc(thisx, globalCtx);

    if (isRandomizedComposerBrother) {
        gSaveContext.sceneFlags[83].swch = globalCtx->actorCtx.flags.swch;
        globalCtx->actorCtx.flags        = prevFlags;
    }
}

void EnPoh_rInit(Actor* thisx, GlobalContext* globalCtx) {
    Poe_CallActorFunc(EnPoh_Init, thisx, globalCtx);
}

void EnPoh_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    Poe_CallActorFunc(EnPoh_Update, thisx, globalCtx);
}
