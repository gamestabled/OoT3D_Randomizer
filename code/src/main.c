#include "rHeap.h"
#include "item_override.h"
#include "actor.h"
#include "input.h"
#include "models.h"
#include "entrance.h"
#include "settings.h"
#include "title_screen.h"
#include "draw.h"
#include "common.h"
#include "savefile.h"
#include "multiplayer.h"
#include "grotto.h"
#include "item_effect.h"
#include "triforce.h"
#include "objects.h"
#include "enemizer.h"
#include "scene.h"

#include "z3D/z3D.h"
#include "3ds/extdata.h"
#include "3ds/services/irrst.h"
#include "3ds/svc.h"

GlobalContext* gGlobalContext = NULL;
static u8 rRandomizerInit     = 0;
u32 rGameplayFrames           = 0;

void Randomizer_Init() {
    rHeap_Init();
    Actor_Init();
    Entrance_Init();
    ItemOverride_Init();
    Enemizer_Init();
    extDataInit();
    irrstInit();

    s64 output = 0;
    svcGetSystemInfo(&output, 0x20000, 0);
    playingOnCitra = (output != 0);
}

void before_Play_Init(GlobalContext* globalCtx) {
    if (!rRandomizerInit) {
        Randomizer_Init();
        rRandomizerInit = 1;
    }
    gGlobalContext = globalCtx;
    rSceneLayer = 0;
}

void before_GlobalContext_Update(GlobalContext* globalCtx) {
    rGameplayFrames++;
    ItemOverride_Update();
    ExtendedObject_UpdateEntries();
    Model_UpdateAll(globalCtx);
    Input_Update();
    SaveFile_EnforceHealthLimit();
    Settings_SkipSongReplays();
    Multiplayer_Run();
    ItemEffect_RupeeAmmo(&gSaveContext);
    Triforce_HandleCreditsWarp();
    Enemizer_Update();
}

void after_GlobalContext_Update() {
    // The alert is always displayed on the Title Screen, and for 10 seconds after opening a save file.
    if (missingRomfsAlert && romfsAlertFrames > 0) {
        Draw_DrawFormattedStringTop(75, 180, COLOR_WHITE,
                                    "WARNING: THE ROMFS FOLDER IS MISSING!\nCOPY IT FROM AND TO THE SAME "
                                    "LOCATIONS\nUSED FOR CODE.IPS AND EXHEADER.BIN");
        if (IsInGame()) {
            romfsAlertFrames--;
        }
    }

    Multiplayer_Sync_Update();

    if (gGlobalContext->state.running == 0) {
        Model_DestroyAll();
    }
}
