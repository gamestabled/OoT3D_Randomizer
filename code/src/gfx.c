#include "gfx.h"
#include "draw.h"
#include "input.h"
#include "3ds/svc.h"
#include "z3D/z3D.h"
#include "dungeon_rewards.h"
#include "rHeap.h"
#include "custom_models.h"
#include "objects.h"
#include "title_screen.h"
#include "settings.h"
#include "spoiler_data.h"

static u8 GfxInit = 0;
static u32 closingButton = 0;
static u8 currentSphere = 0;
static u8 spoilerScroll = 0;

#define MAX_ITEM_LINES 6

static void Gfx_DrawChangeMenuPrompt(void) {
    Draw_DrawString(10, SCREEN_BOT_HEIGHT - 70, COLOR_TITLE, "Warning: Putting your 3DS into sleep mode with this menu up will crash.");
    Draw_DrawString(10, SCREEN_BOT_HEIGHT - 40, COLOR_TITLE, "Press B to close menu");
    Draw_DrawString(10, SCREEN_BOT_HEIGHT - 20, COLOR_TITLE, "Press L/R to change menu");
}

static void Gfx_DrawSeedHash(void) {
    Draw_DrawFormattedString(10, 10, COLOR_TITLE, "Seed Hash:");
    for (u32 hashIndex = 0; hashIndex < 5; ++hashIndex) {
        Draw_DrawFormattedString(10, 10 + SPACING_Y + (hashIndex * SPACING_Y), COLOR_WHITE, "    %s", hashIconNames[gSettingsContext.hashIndexes[hashIndex]]);
    }
    Gfx_DrawChangeMenuPrompt();
    Draw_FlushFramebuffer();
}

static void Gfx_DrawDungeonItems(void) {
    for (u32 dungeonId = 0; dungeonId <= DUNGEON_GERUDO_FORTRESS; ++dungeonId) {
        //special case for Ganon's Castle small keys
        s32 keys = 0;
        if (dungeonId == DUNGEON_GANONS_CASTLE_SECOND_PART) {
          keys = (gSaveContext.dungeonKeys[DUNGEON_GANONS_CASTLE_FIRST_PART] >= 0) ? gSaveContext.dungeonKeys[DUNGEON_GANONS_CASTLE_FIRST_PART] : 0;
        } else {
          keys = (gSaveContext.dungeonKeys[dungeonId] >= 0) ? gSaveContext.dungeonKeys[dungeonId] : 0;
        }

        Draw_DrawFormattedString(10, 10 + (dungeonId * SPACING_Y), COLOR_WHITE, "%-25s %s: %d %s",
            DungeonNames[dungeonId], "Small Keys", keys, gSaveContext.dungeonItems[dungeonId] & 1 ? "Boss Key" : "");
    }
    Gfx_DrawChangeMenuPrompt();
    Draw_FlushFramebuffer();
}

static void Gfx_DrawDungeonRewards(void) {
    for (u32 dungeonId = 0; dungeonId <= DUNGEON_SHADOW_TEMPLE; ++dungeonId) {
        Draw_DrawFormattedString(10, 10 + (dungeonId * SPACING_Y), COLOR_WHITE, "%-30s - %s",
            DungeonNames[dungeonId], (gSettingsContext.shuffleRewards == REWARDSHUFFLE_END_OF_DUNGEON) ? DungeonReward_GetName(dungeonId) : "???");
    }
    Gfx_DrawChangeMenuPrompt();
    Draw_FlushFramebuffer();
}

static void Gfx_DrawSpoilerData(void) {
    if (gSpoilerData.SphereCount > 0) {
        Draw_DrawFormattedString(10, 10, COLOR_TITLE, "Spoiler Log - Sphere %i", currentSphere + 1);
        for (u32 item = 0; item < MAX_ITEM_LINES; ++item) {
        // for (u32 loc = spoilerScroll; loc < gSpoilerData.Spheres[currentSphere].ItemCount; ++loc) {
            u32 locIndex = item + spoilerScroll;
            if (locIndex >= gSpoilerData.Spheres[currentSphere].ItemCount) { break; }

            u32 locPosY = 12 + SPACING_Y + (SPACING_Y * item * 2);
            u32 itemPosY = locPosY + SPACING_Y;
            Draw_DrawString(10, locPosY, COLOR_WHITE,
                gSpoilerData.Spheres[currentSphere].ItemLocations[locIndex].Location);
            Draw_DrawString(10 + SPACING_X, itemPosY, COLOR_WHITE,
                gSpoilerData.Spheres[currentSphere].ItemLocations[locIndex].Item);
        }
    }
    else {
        Draw_DrawString(10, 10, COLOR_TITLE, "Spoiler Log");
        Draw_DrawString(10, 40, COLOR_RED, "No spoiler data generated!");
    }
    Gfx_DrawChangeMenuPrompt();
    Draw_FlushFramebuffer();
}

static const void (*menu_draw_funcs[])(void) = {
    Gfx_DrawSeedHash,
    Gfx_DrawDungeonItems,
    Gfx_DrawDungeonRewards,
    Gfx_DrawSpoilerData,
};

static void Gfx_ShowMenu(void) {
    static s32 curMenuIdx = 0;
    u32 pressed = 0;

    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();

    do {
        if (pressed & closingButton) {
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

        // Controls for spoiler log page
        if (curMenuIdx == 3 && gSpoilerData.SphereCount > 0) {
            if (pressed & BUTTON_LEFT) {
                if (currentSphere == 0) {
                    currentSphere = gSpoilerData.SphereCount - 1;
                    spoilerScroll = 0;
                } else {
                    currentSphere--;
                    spoilerScroll = 0;
                }
                Draw_ClearFramebuffer();
                Draw_FlushFramebuffer();
            } else if (pressed & BUTTON_RIGHT) {
                if (currentSphere == gSpoilerData.SphereCount - 1) {
                    currentSphere = 0;
                    spoilerScroll = 0;
                } else {
                    currentSphere++;
                    spoilerScroll = 0;
                }
                Draw_ClearFramebuffer();
                Draw_FlushFramebuffer();
            } else if (pressed & BUTTON_UP) {
                if (spoilerScroll > 0) { spoilerScroll--; }
                Draw_ClearFramebuffer();
                Draw_FlushFramebuffer();
            } else if (pressed & BUTTON_DOWN) {
                if (spoilerScroll < UINT8_MAX
                    && spoilerScroll < gSpoilerData.Spheres[currentSphere].ItemCount
                    && gSpoilerData.Spheres[currentSphere].ItemCount - spoilerScroll > MAX_ITEM_LINES) {
                    spoilerScroll++;
                }
                Draw_ClearFramebuffer();
                Draw_FlushFramebuffer();
            }
        }

        if (curMenuIdx < 0) {
            curMenuIdx = (ARR_SIZE(menu_draw_funcs) - 1);
        } else if (curMenuIdx >= ARR_SIZE(menu_draw_funcs)) {
            curMenuIdx = 0;
        }

        menu_draw_funcs[curMenuIdx]();
        pressed = Input_WaitWithTimeout(1000, closingButton);

    } while(true);
}

void Gfx_Init(void) {
    Draw_SetupFramebuffer();

    // Setup the title screen logo edits
    gActorOverlayTable[0x171].initInfo->init = EnMag_rInit;

    if(gSettingsContext.menuOpeningButton == 0)         closingButton = BUTTON_B | BUTTON_SELECT;
    else if(gSettingsContext.menuOpeningButton == 1)    closingButton = BUTTON_B | BUTTON_START;
    else if(gSettingsContext.menuOpeningButton == 2)    closingButton = BUTTON_B | BUTTON_UP;
    else if(gSettingsContext.menuOpeningButton == 3)    closingButton = BUTTON_B | BUTTON_DOWN;
    else if(gSettingsContext.menuOpeningButton == 4)    closingButton = BUTTON_B | BUTTON_RIGHT;
    else if(gSettingsContext.menuOpeningButton == 5)    closingButton = BUTTON_B | BUTTON_LEFT;

    GfxInit = 1;
}

static u8 openingButton(void){
        return((gSettingsContext.menuOpeningButton == 0 && rInputCtx.cur.sel) ||
	(gSettingsContext.menuOpeningButton == 1 && rInputCtx.cur.strt) ||
	(gSettingsContext.menuOpeningButton == 2 && rInputCtx.cur.d_up) ||
	(gSettingsContext.menuOpeningButton == 3 && rInputCtx.cur.d_down) ||
	(gSettingsContext.menuOpeningButton == 4 && rInputCtx.cur.d_right) ||
	(gSettingsContext.menuOpeningButton == 5 && rInputCtx.cur.d_left));
}

void Gfx_Update(void) {
    if (!GfxInit) {
        Gfx_Init();
    }

    s32 entr = gSaveContext.entranceIndex;
    s32 mode = gSaveContext.gameMode;
    if(openingButton() &&
        (mode == 0 ||
        (mode == 1 && entr != 0x0629 && entr != 0x0147 && entr != 0x00A0 && entr != 0x008D)
        )
      ){
        Gfx_ShowMenu();
        svcSleepThread(1000 * 1000 * 300LL);
    }
}
