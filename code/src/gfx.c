#include "gfx.h"
#include "draw.h"
#include "input.h"
#include "3ds/svc.h"
#include "z3D/z3D.h"

static u8 GfxInit = 0;

static void Gfx_TitleScreen(void) {
    Draw_DrawFormattedStringTop(150, 20, COLOR_WHITE, "OoT3D Randomizer Test");
    Draw_FlushFramebufferTop();
}

static void Gfx_DungeonItems(void) {
    Draw_ClearFramebuffer();
    for (u32 dungeonId = 0; dungeonId <= DUNGEON_GERUDO_FORTRESS; ++dungeonId) {
        Draw_DrawFormattedString(10, 10 + (dungeonId * SPACING_Y), COLOR_WHITE, "%-30s %s: %d", 
            DungeonNames[dungeonId], "Small Keys", gSaveContext.dungeonKeys[dungeonId]);
    }
    Draw_FlushFramebuffer();
}

void Gfx_Init(void) {
    Draw_SetupFramebuffer();
    GfxInit = 1;
}

void Gfx_Update(void) {
    if (!GfxInit) {
        Gfx_Init();
    }
    if(gSaveContext.entranceIndex == 0x0629 && gSaveContext.cutsceneIndex == 0xFFF3) {
        Gfx_TitleScreen();
    }
    if(gSaveContext.gameMode == 0 && rInputCtx.cur.d_right) {
        Gfx_DungeonItems();
        while (rInputCtx.cur.d_right) {
            InputContext_Update();
            svcSleepThread(1000);
        }
    }
}