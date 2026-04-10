#include "poe.h"
#include "settings.h"
#include "enemizer.h"

void EnPoh_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPoh_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPoh_UpdateLiving(Actor* thisx, GlobalContext* globalCtx);
void EnPoh_UpdateDead(Actor* thisx, GlobalContext* globalCtx);

/**
 * Composer Brothers set some flags when they spawn and when the player talks to them.
 * This function prevents them from affecting the current scene by either overriding
 * these flags or moving them to the Graveyard scene.
 */
static void Poe_CallActorFunc(ActorFunc actorFunc, Actor* thisx, GlobalContext* globalCtx) {
    u32 prevSwchFlags;
    u32 prevTempSwchFlags;
    u8 isRandomizedComposerBrother = Enemizer_IsEnemyRandomized(ENEMY_POE) && (thisx->params & 0x0002) == 0x0002 &&
                                     globalCtx->sceneNum != SCENE_GRAVEYARD;

    if (isRandomizedComposerBrother) {
        prevSwchFlags                      = globalCtx->actorCtx.flags.swch;
        prevTempSwchFlags                  = globalCtx->actorCtx.flags.tempSwch;
        globalCtx->actorCtx.flags.swch     = gSaveContext.sceneFlags[SCENE_GRAVEYARD].swch;
        globalCtx->actorCtx.flags.tempSwch = 0;
        Flags_UnsetSwitch(globalCtx, 0x9); // This flag makes Composer Brothers stop spawning
    }

    actorFunc(thisx, globalCtx);

    if (isRandomizedComposerBrother) {
        gSaveContext.sceneFlags[SCENE_GRAVEYARD].swch = globalCtx->actorCtx.flags.swch;
        globalCtx->actorCtx.flags.swch                = prevSwchFlags;
        globalCtx->actorCtx.flags.tempSwch            = prevTempSwchFlags;
    }
}

void EnPoh_rInit(Actor* thisx, GlobalContext* globalCtx) {
    Poe_CallActorFunc(EnPoh_Init, thisx, globalCtx);
}

static void EnPoh_rUpdateDead(Actor* thisx, GlobalContext* globalCtx) {
    Poe_CallActorFunc(EnPoh_UpdateDead, thisx, globalCtx);
}

static void EnPoh_rUpdateLiving(Actor* thisx, GlobalContext* globalCtx) {
    Poe_CallActorFunc(EnPoh_UpdateLiving, thisx, globalCtx);
    if (thisx->update == EnPoh_UpdateDead) {
        thisx->update = EnPoh_rUpdateDead;
    }
}

void EnPoh_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    Poe_CallActorFunc(EnPoh_Update, thisx, globalCtx);
    if (thisx->update == EnPoh_UpdateLiving) {
        thisx->update = EnPoh_rUpdateLiving;
    }
}
