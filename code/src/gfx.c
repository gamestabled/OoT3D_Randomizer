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
static s16 spoilerScroll = 0;
static s16 allItemsScroll = 0;
static s32 curMenuIdx = 0;

#define UP_ARROW_CHR 24
#define DOWN_ARROW_CHR 25
#define LEFT_ARROW_CHR 27
#define RIGHT_ARROW_CHR 26
#define UP_SOLID_ARROW_CHR 30
#define DOWN_SOLID_ARROW_CHR 31

#define MAX_ITEM_LINES 6
#define COLOR_WARN RGB8(0xD1, 0xDF, 0x3C)

static void Gfx_DrawChangeMenuPrompt(void) {
    Draw_DrawString(10, SCREEN_BOT_HEIGHT - 58, COLOR_WARN, "Warning: Putting your 3DS into sleep mode with this menu up will crash.");
    Draw_DrawString(10, SCREEN_BOT_HEIGHT - 32, COLOR_TITLE, "Press B to close menu, L/R to change menu");
    if (curMenuIdx == 3 || curMenuIdx == 4) {
        Draw_DrawFormattedString(10, SCREEN_BOT_HEIGHT - 20, COLOR_TITLE, "Press %c/%c/%c/%c to browse spoiler log",
            LEFT_ARROW_CHR, RIGHT_ARROW_CHR, UP_ARROW_CHR, DOWN_ARROW_CHR);
    }
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
        u16 itemCount = gSpoilerData.Spheres[currentSphere].ItemCount;

        bool canScrollUp = spoilerScroll > 0;
        bool canScrollDown = itemCount - spoilerScroll > MAX_ITEM_LINES;

        if (canScrollUp)
        {
            Draw_DrawFormattedString(148, 24, COLOR_WHITE, "%c%c%c", UP_SOLID_ARROW_CHR, UP_SOLID_ARROW_CHR, UP_SOLID_ARROW_CHR);
        }

        if (canScrollDown)
        {
            Draw_DrawFormattedString(148, SCREEN_BOT_HEIGHT - 74, COLOR_WHITE, "%c%c%c", DOWN_SOLID_ARROW_CHR, DOWN_SOLID_ARROW_CHR, DOWN_SOLID_ARROW_CHR);
        }

        Draw_DrawFormattedString(74, 10, COLOR_TITLE, "Spoiler Log - Sphere %i / %i", currentSphere + 1, gSpoilerData.SphereCount);

        for (u32 item = 0; item < MAX_ITEM_LINES; ++item) {
            u32 locIndex = item + spoilerScroll;
            if (locIndex >= gSpoilerData.Spheres[currentSphere].ItemCount) { break; }

            u32 locPosY = 34 + (SPACING_Y * item * 2);
            u32 itemPosY = locPosY + SPACING_Y;
            Draw_DrawString(10, locPosY, COLOR_WHITE,
                SpoilerData_GetItemLocationString(gSpoilerData.Spheres[currentSphere].ItemLocations[locIndex]));
            Draw_DrawString(10 + SPACING_X, itemPosY, COLOR_WHITE,
                SpoilerData_GetItemNameString(gSpoilerData.Spheres[currentSphere].ItemLocations[locIndex]));
        }
    }
    else {
        Draw_DrawString(10, 10, COLOR_TITLE, "Spoiler Log");
        Draw_DrawString(10, 40, COLOR_WHITE, "No spoiler log generated!");
    }
    Gfx_DrawChangeMenuPrompt();
    Draw_FlushFramebuffer();
}

static void Gfx_DrawSpoilerAllItems(void) {
    if (gSpoilerData.ItemLocationsCount > 0) {
        u16 itemCount = gSpoilerData.ItemLocationsCount;

        bool canScrollUp = allItemsScroll > 0;
        bool canScrollDown = itemCount - allItemsScroll > MAX_ITEM_LINES;

        if (canScrollUp)
        {
            Draw_DrawFormattedString(148, 24, COLOR_WHITE, "%c%c%c", UP_SOLID_ARROW_CHR, UP_SOLID_ARROW_CHR, UP_SOLID_ARROW_CHR);
        }

        if (canScrollDown)
        {
            Draw_DrawFormattedString(148, SCREEN_BOT_HEIGHT - 74, COLOR_WHITE, "%c%c%c", DOWN_SOLID_ARROW_CHR, DOWN_SOLID_ARROW_CHR, DOWN_SOLID_ARROW_CHR);
        }

        u16 firstItem = allItemsScroll + 1;
        u16 lastItem = allItemsScroll + MAX_ITEM_LINES;
        if (lastItem > gSpoilerData.ItemLocationsCount) { lastItem = gSpoilerData.ItemLocationsCount; }
        Draw_DrawFormattedString(32, 10, COLOR_TITLE, "All Item Locations (%d - %d) / %d",
            firstItem, lastItem, gSpoilerData.ItemLocationsCount);

        for (u32 item = 0; item < MAX_ITEM_LINES; ++item) {
            u32 locIndex = item + allItemsScroll;
            if (locIndex >= gSpoilerData.ItemLocationsCount) { break; }

            u32 locPosY = 34 + (SPACING_Y * item * 2);
            u32 itemPosY = locPosY + SPACING_Y;
            Draw_DrawString(10, locPosY, COLOR_WHITE,
                SpoilerData_GetItemLocationString(locIndex));
            Draw_DrawString(10 + SPACING_X, itemPosY, COLOR_WHITE,
                SpoilerData_GetItemNameString(locIndex));
        }
    }
    else {
        Draw_DrawString(10, 10, COLOR_TITLE, "All Item Locations");
        Draw_DrawString(10, 40, COLOR_WHITE, "No item location data!");
    }
    Gfx_DrawChangeMenuPrompt();
    Draw_FlushFramebuffer();
}

static const void (*menu_draw_funcs[])(void) = {
    Gfx_DrawSeedHash,
    Gfx_DrawDungeonItems,
    Gfx_DrawDungeonRewards,
    Gfx_DrawSpoilerData,
    Gfx_DrawSpoilerAllItems,
};

static s16 Gfx_Scroll(s16 current, s16 scrollDelta, u16 itemCount) {
    s16 maxScroll = itemCount > MAX_ITEM_LINES ? itemCount - MAX_ITEM_LINES : 0;
    current += scrollDelta;
    if (current < 0) { current = 0; }
    else if (current > maxScroll) { current = maxScroll; }
    return current;
}

static void Gfx_ShowMenu(void) {
    u32 pressed = 0;

    Draw_ClearFramebuffer();
    Draw_FlushFramebuffer();

    do {
        bool handledInput = false;
        // Controls for spoiler log and all-items pages come first, as the user may have chosen
        // one of the directional buttons as their menu open/close button and we need to use them
        if (curMenuIdx == 3 && gSpoilerData.SphereCount > 0) {
            // Spoiler log
            u16 itemCount = gSpoilerData.Spheres[currentSphere].ItemCount;
            if (pressed & BUTTON_LEFT) {
                if (currentSphere == 0) {
                    currentSphere = gSpoilerData.SphereCount - 1;
                } else {
                    currentSphere--;
                }
                spoilerScroll = 0;
                handledInput = true;
            } else if (pressed & BUTTON_RIGHT) {
                if (currentSphere < gSpoilerData.SphereCount - 1) {
                    currentSphere++;
                } else {
                    currentSphere = 0;
                }
                spoilerScroll = 0;
                handledInput = true;
            } else if (pressed & BUTTON_UP) {
                spoilerScroll = Gfx_Scroll(spoilerScroll, -1, itemCount);
                handledInput = true;
            } else if (pressed & BUTTON_DOWN) {
                spoilerScroll = Gfx_Scroll(spoilerScroll, 1, itemCount);
                handledInput = true;
            }
        } else if (curMenuIdx == 4 && gSpoilerData.ItemLocationsCount > 0) {
            // All Items list
            u16 itemCount = gSpoilerData.ItemLocationsCount;
            if (pressed & BUTTON_LEFT) {
                allItemsScroll = Gfx_Scroll(allItemsScroll, -MAX_ITEM_LINES * 10, itemCount);
                handledInput = true;
            } else if (pressed & BUTTON_RIGHT) {
                allItemsScroll = Gfx_Scroll(allItemsScroll, MAX_ITEM_LINES * 10, itemCount);
                handledInput = true;
            } else if (pressed & BUTTON_UP) {
                allItemsScroll = Gfx_Scroll(allItemsScroll, -MAX_ITEM_LINES, itemCount);
                handledInput = true;
            } else if (pressed & BUTTON_DOWN) {
                allItemsScroll = Gfx_Scroll(allItemsScroll, MAX_ITEM_LINES, itemCount);
                handledInput = true;
            }
        }

        if (!handledInput) {
            if (pressed & closingButton) {
                Draw_ClearFramebuffer();
                Draw_FlushFramebuffer();
                break;
            } else if (pressed & BUTTON_R1) {
                curMenuIdx++;
                handledInput = true;
            } else if (pressed & BUTTON_L1) {
                curMenuIdx--;
                handledInput = true;
            }
        }

        if (handledInput) {
            Draw_ClearFramebuffer();
            Draw_FlushFramebuffer();
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
