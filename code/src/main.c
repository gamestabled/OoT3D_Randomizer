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

#include "z3D/z3D.h"
#include "3ds/extdata.h"

GlobalContext* gGlobalContext;
static u8 rRandomizerInit = 0;

void set_GlobalContext(GlobalContext* globalCtx) {
    gGlobalContext = globalCtx;
}

void Randomizer_Init() {
    rHeap_Init();
    Actor_Init();
    Entrance_Init();
    ItemOverride_Init();
    extDataInit();
}

void before_GlobalContext_Update(GlobalContext* globalCtx) {
    if (!rRandomizerInit) {
        Randomizer_Init();
        set_GlobalContext(globalCtx);
        rRandomizerInit = 1;
    }
    ItemOverride_Update();
    Model_UpdateAll(globalCtx);
    Input_Update();

    Settings_SkipSongReplays();
}

void after_GlobalContext_Update() {
    // The alert is always displayed on the Title Screen, and for 10 seconds after opening a save file.
    if (missingRomfsAlert && romfsAlertFrames > 0) {
        Draw_DrawFormattedStringTop(75, 180, COLOR_WHITE, "WARNING: THE ROMFS FOLDER IS MISSING!\nCOPY IT FROM AND TO THE SAME LOCATIONS\nUSED FOR CODE.IPS AND EXHEADER.BIN");
        if (IsInGame()) {
            romfsAlertFrames--;
        }
    }
}
