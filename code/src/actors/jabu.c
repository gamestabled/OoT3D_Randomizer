#include "z3D/z3D.h"
#include "settings.h"
#include "entrance.h"
#include "grotto.h"

#define BgBdanSwitch_Init_addr 0x276508
#define BgBdanSwitch_Init ((ActorFunc)BgBdanSwitch_Init_addr)

void Jabu_SkipOpeningCutscene(void) {
    gGlobalContext->nextEntranceIndex = Entrance_OverrideNextIndex(0x0028);
    gGlobalContext->sceneLoadFlag     = 0x14;
    gGlobalContext->fadeOutTransition = 2;
    // In case Jabu's mouth leads to a grotto return
    Grotto_ForceGrottoReturnOnSpecialEntrance();
}

// Used to make the small crate appear after Ruto gets the sapphire
// By default it would appear only after beating the dungeon
s32 ObjKibako_CheckRuto(void) {
    return gSaveContext.infTable[0x14] & 0x20;
}

void BgBdanSwitch_rInit(Actor* thisx, GlobalContext* globalCtx) {
    // In MQ Jabu, spawn a box if Ruto isn't available in the basement room
    if ((gSaveContext.infTable[0x14] & 0x20 || gSaveContext.eventChkInf[3] & 0x0080) &&
        gSettingsContext.jabuJabusBellyDungeonMode == DUNGEONMODE_MQ && globalCtx->sceneNum == 2 && thisx->room == 3 &&
        ((thisx->params & 0x000F) == 0)) {
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0x110, 222.0f, -1113.0f, -3270.0f, 0, 0, 0, 0, FALSE);
    }
    BgBdanSwitch_Init(thisx, globalCtx);
}
