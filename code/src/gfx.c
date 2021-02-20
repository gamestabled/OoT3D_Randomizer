#include "gfx.h"
#include "draw.h"
#include "input.h"
#include "3ds/svc.h"
#include "z3D/z3D.h"
#include "dungeon_rewards.h"
#include "rHeap.h"
#include "custom_models.h"
#include "objects.h"

static u8 GfxInit = 0;

void Gfx_SetupTitleScreenZARInfo(ZARInfo* zarInfo, void* buf, s32 size, s8 param_4) {
    const ObjectContext* objCtx = (ObjectContext*)0x8722298;

    if(gSaveContext.entranceIndex == 0x0629 && gSaveContext.cutsceneIndex == 0xFFF3) {
        if (zarInfo == &objCtx->status[5].zarInfo) {
            CustomModel_EditTitleScreenLogo(buf);
        }
    }
}

static void Gfx_DrawChangeMenuPrompt(void) {
    Draw_DrawString(10, SCREEN_BOT_HEIGHT - 20, COLOR_TITLE, "Press L/R to change menu");
}

static void Gfx_DrawDungeonItems(void) {
    for (u32 dungeonId = 0; dungeonId <= DUNGEON_GERUDO_FORTRESS; ++dungeonId) {
        s32 keys = (gSaveContext.dungeonKeys[dungeonId] >= 0) ? gSaveContext.dungeonKeys[dungeonId] : 0;
        Draw_DrawFormattedString(10, 10 + (dungeonId * SPACING_Y), COLOR_WHITE, "%-30s %s: %d", 
            DungeonNames[dungeonId], "Small Keys", keys);
    }
    Gfx_DrawChangeMenuPrompt();
    Draw_FlushFramebuffer();
}

static void Gfx_DrawDungeonRewards(void) {
    for (u32 dungeonId = 0; dungeonId <= DUNGEON_SHADOW_TEMPLE; ++dungeonId) {
        Draw_DrawFormattedString(10, 10 + (dungeonId * SPACING_Y), COLOR_WHITE, "%-30s - %s", 
            DungeonNames[dungeonId], DungeonReward_GetName(dungeonId));
    }
    Gfx_DrawChangeMenuPrompt();
    Draw_FlushFramebuffer();
}

static const void (*menu_draw_funcs[])(void) = {
    Gfx_DrawDungeonItems,
    Gfx_DrawDungeonRewards,
};

static void Gfx_ShowMenu(void) {
    static s32 curMenuIdx = 0;
    u32 pressed = 0;

    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();

    do {
        if (pressed & BUTTON_B) {
            Draw_ClearFramebuffer();
            Draw_FlushFramebuffer();
            break;
        } else if (pressed & BUTTON_R1) {
            curMenuIdx++;
            Draw_ClearFramebuffer();
            Draw_FlushFramebuffer();
        } else if (pressed & BUTTON_L1) {
            curMenuIdx--;
            Draw_ClearFramebuffer();
            Draw_FlushFramebuffer();
        }

        if (curMenuIdx >= ARR_SIZE(menu_draw_funcs)) {
            curMenuIdx = 0;
        } else if (curMenuIdx < 0) {
            curMenuIdx = (ARR_SIZE(menu_draw_funcs) - 1);
        }

        menu_draw_funcs[curMenuIdx]();
        pressed = Input_WaitWithTimeout(1000);

    } while(true);
}

void Gfx_Init(void) {
    Draw_SetupFramebuffer();

    // Increase the filesize for the title screen object
    gObjectTable[330].size = 0xA5CB0;

    GfxInit = 1;
}

void Gfx_Update(void) {
    if (!GfxInit) {
        Gfx_Init();
    }

    if(gSaveContext.gameMode == 0 && rInputCtx.cur.sel) {
        Gfx_ShowMenu();
        svcSleepThread(1000 * 1000 * 300LL);
    }
}