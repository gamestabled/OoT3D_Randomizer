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

static void Gfx_DrawDungeonItems(void) {
    for (u32 dungeonId = 0; dungeonId <= DUNGEON_GERUDO_FORTRESS; ++dungeonId) {
        s32 keys = (gSaveContext.dungeonKeys[dungeonId] >= 0) ? gSaveContext.dungeonKeys[dungeonId] : 0;
        Draw_DrawFormattedString(10, 10 + (dungeonId * SPACING_Y), COLOR_WHITE, "%-30s %s: %d", 
            DungeonNames[dungeonId], "Small Keys", keys);
    }
    Draw_FlushFramebuffer();
}

static void Gfx_ShowDungeonItems(void) {
    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();
    Gfx_DrawDungeonItems();

    do {
        u32 pressed = Input_WaitWithTimeout(1000);

        if (pressed & BUTTON_B) {
            Draw_ClearFramebuffer();
            Draw_FlushFramebuffer();
            break;
        }
        Gfx_DrawDungeonItems();
    } while(true);
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
    if(gSaveContext.gameMode == 0 && rInputCtx.cur.sel) {
        Gfx_ShowDungeonItems();
        svcSleepThread(1000 * 1000 * 300LL);
    }
}