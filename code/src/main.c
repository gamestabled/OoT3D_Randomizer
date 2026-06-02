#include "rHeap.h"
#include "item_override.h"
#include "actor.h"
#include "input.h"
#include "models.h"
#include "effects.h"
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
#include "gloom.h"
#include "ocarina_notes.h"
#include "icetrap.h"
#include "bgm.h"
#include "business_scrubs.h"
#include "alert.h"

#include "z3D/z3D.h"
#include "3ds/extdata.h"
#include "3ds/services/irrst.h"
#include "3ds/svc.h"

GlobalContext* gGlobalContext = NULL;
static u8 rRandomizerInit     = 0;
u32 rGameplayFrames           = 0;
static AlertType sActiveAlert = ALERT_NONE;
static s16 sAlertFrames       = 0;

static void Alert_Update(void);

void Randomizer_Init() {
    rHeap_Init();
    Actor_Init();
    Entrance_Init();
    ItemOverride_Init();
    Enemizer_Init();
    OcarinaNotes_Init();
    IceTrap_Init();
    extDataInit();
    irrstInit();
    Effects_Init();
    BusinessScrubs_Init();

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
    rSceneLayer    = 0;
}

void before_GlobalContext_Update(GlobalContext* globalCtx) {
    rGameplayFrames++;
    ItemOverride_Update();
    ExtendedObject_UpdateEntries();
    Model_UpdateAll(globalCtx);
    Input_Update();
    Gloom_Update();
    SaveFile_EnforceHealthLimit();
    Settings_SkipSongReplays();
    Multiplayer_Run();
    ItemEffect_RupeeAmmo(&gSaveContext);
    Triforce_HandleCreditsWarp();
    Enemizer_Update();
    Bgm_ApplyFanfareMod();
}

void after_GlobalContext_Update() {
    Alert_Update();
    Multiplayer_Sync_Update();

    if (gGlobalContext->state.running == 0) {
        Model_DestroyAll();
    }
}

void Alert_Set(AlertType alert) {
    sActiveAlert = alert;
    sAlertFrames = 450; // 15 seconds
}

static void Alert_Update(void) {
    if (sActiveAlert == ALERT_NONE || sAlertFrames <= 0) {
        return;
    }

    const char* const alertMessages[] = {
        [ALERT_MISSING_ROMFS] = "WARNING: THE ROMFS FOLDER IS MISSING!\n"
                                "COPY IT ALONGSIDE CODE.IPS AND EXHEADER.BIN",
        [ALERT_HASH_MISMATCH] = "WARNING: THIS SAVE FILE DOES NOT MATCH\n"
                                "THE CURRENT RANDOMIZER SEED!\n"
                                "CONTINUING MAY RESULT IN SOFTLOCKS.\n"
                                "PLEASE CREATE A NEW FILE.",
    };

    // The alert is always displayed on the Title Screen, decrease timer only in game.
    if (IsInGame()) {
        sAlertFrames--;
    } else if (sActiveAlert == ALERT_HASH_MISMATCH) {
        sActiveAlert = ALERT_NONE;
        return;
    }

    Draw_DrawFormattedStringTop(75, 150, COLOR_WHITE, alertMessages[sActiveAlert]);
}
