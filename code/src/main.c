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

#include "z3D/z3D.h"
#include "3ds/extdata.h"
#include "3ds/services/irrst.h"
#include "3ds/svc.h"

GlobalContext* gGlobalContext = NULL;
static u8 rRandomizerInit     = 0;
u32 rGameplayFrames           = 0;

void set_GlobalContext(GlobalContext* globalCtx) {
    gGlobalContext = globalCtx;
}

void Randomizer_Init() {
    rHeap_Init();
    Actor_Init();
    Entrance_Init();
    ItemOverride_Init();
    extDataInit();
    irrstInit();
}

void before_GlobalContext_Update(GlobalContext* globalCtx) {
    if (!rRandomizerInit) {
        Randomizer_Init();
        set_GlobalContext(globalCtx);
        rRandomizerInit = 1;

        s64 output = 0;
        svcGetSystemInfo(&output, 0x20000, 0);
        playingOnCitra = (output != 0);
    }
    rGameplayFrames++;
    ItemOverride_Update();
    ActorSetup_Extra();
    Model_UpdateAll(globalCtx);
    Input_Update();
    SaveFile_EnforceHealthLimit();

    Settings_SkipSongReplays();

    Multiplayer_Run();

    ItemEffect_RupeeAmmo(&gSaveContext);

    Triforce_HandleCreditsWarp();
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

    // CitraPrint("PLAYER->actor.shape.unk_06: 0x%X\n", PLAYER->actor.shape.unk_06);
    // CitraPrint("1 - draw_10: 0x%X", PLAYER->skelAnime.unk_28->unk_0C->unk_00);
    // CitraPrint("2 - draw_10: 0x%X", PLAYER->skelAnime.unk_28->unk_10);
    // CitraPrint("unk_00: 0x%X", PLAYER->skelAnime.unk_28->unk_10->unk_00);
    // CitraPrint("unk_04: 0x%X", PLAYER->skelAnime.unk_28->unk_10->unk_04);
    // CitraPrint("unk_08: 0x%X", PLAYER->skelAnime.unk_28->unk_10->unk_08);
    // CitraPrint("unk_0C: 0x%X", PLAYER->skelAnime.unk_28->unk_10->unk_0C);
    // CitraPrint("unk_10: 0x%X\n", PLAYER->skelAnime.unk_28->unk_10->unk_10);

    Multiplayer_Sync_Update();
}
