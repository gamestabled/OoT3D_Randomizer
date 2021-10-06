#include "gfx.h"
#include "3ds/svc.h"
#include "z3D/z3D.h"
#include "dungeon_rewards.h"
#include "rHeap.h"
#include "custom_models.h"
#include "objects.h"
#include "title_screen.h"
#include "settings.h"
#include "spoiler_data.h"
#include "entrance.h"
#include "gfx_options.h"
#include "common.h"

u32 pressed;
bool handledInput;

static u8 GfxInit = 0;
static u32 closingButton = 0;
static u8 currentSphere = 0;
static s16 spoilerScroll = 0;
static s16 allItemsScroll = 0;
static s16 groupItemsScroll = 0;
static s8 currentGroup = 1;
static s16 entranceScroll = 0;
static s32 curMenuIdx = 0;
static float itemPercent = 0;
static u64 lastTick = 0;
static u64 ticksElapsed = 0;
static bool isAsleep = false;

DungeonInfo rDungeonInfoData[10]; 

#define TICKS_PER_SEC 268123480
#define MAX_TICK_DELTA (TICKS_PER_SEC * 3)

static char *spoilerCollectionGroupNames[] = {
    "",
    "Kokiri Forest",
    "Lost Woods",
    "Deku Tree",
    "Forest Temple",
    "Kakariko Village",
    "Bottom of the Well",
    "Shadow Temple",
    "Death Mountain",
    "Goron City",
    "Dodongo's Cavern",
    "Fire Temple",
    "Zora's River",
    "Zora's Domain",
    "Jabu Jabu's Belly",
    "Ice Cavern",
    "Hyrule Field",
    "Lon Lon Ranch",
    "Lake Hylia",
    "Water Temple",
    "Gerudo Valley",
    "Gerudo Training Grounds",
    "Spirit Temple",
    "Hyrule Castle",
    "Ganon's Castle",
};

#define UP_ARROW_CHR 24
#define DOWN_ARROW_CHR 25
#define LEFT_ARROW_CHR 27
#define RIGHT_ARROW_CHR 26
#define UP_SOLID_ARROW_CHR 30
#define DOWN_SOLID_ARROW_CHR 31

#define MAX_ITEM_LINES 9
#define SCROLL_BAR_THICKNESS 2
#define SCROLL_BAR_MIN_THUMB_SIZE 4
#define COLOR_WARN RGB8(0xD1, 0xDF, 0x3C)
#define COLOR_SCROLL_BAR_BG RGB8(0x58, 0x58, 0x58)

#define COLOR_ICON_MASTER_QUEST RGB8(0x53, 0xBA, 0xFF)
#define COLOR_ICON_VANILLA      RGB8(0xFF, 0xE8, 0x97)
#define COLOR_ICON_BOSS_KEY     RGB8(0x20, 0xF9, 0x25)
#define COLOR_ICON_MAP          RGB8(0xF9, 0x97, 0xFF)
#define COLOR_ICON_COMPASS      RGB8(0x20, 0x3A, 0xF9)
#define COLOR_ICON_WOTH         RGB8(0xFF, 0xF8, 0x2D)
#define COLOR_ICON_FOOL         RGB8(0xFF, 0x2D, 0x4B)

void Gfx_SleepQueryCallback(void)
{
    ticksElapsed = 0;
    isAsleep = true;
}

void Gfx_AwakeCallback(void)
{
    ticksElapsed = 0;
    lastTick = svcGetSystemTick();
    isAsleep = false;
}

static void Gfx_DrawScrollBar(u16 barX, u16 barY, u16 barSize, u16 currentScroll, u16 maxScroll, u16 pageSize) {
    Draw_DrawRect(barX, barY, SCROLL_BAR_THICKNESS, barSize, COLOR_SCROLL_BAR_BG);

    float thumbSizePercent = pageSize / (float)maxScroll;
    if (thumbSizePercent > 1.0f) {
        thumbSizePercent = 1.0f;
    }
    u16 thumbSize = (u16)(thumbSizePercent * barSize);
    if (thumbSize < SCROLL_BAR_MIN_THUMB_SIZE) {
        thumbSize = SCROLL_BAR_MIN_THUMB_SIZE;
    }
    float barThumbPosPercent = (float)currentScroll / (float)(maxScroll - pageSize);
    u16 barThumbPosY = (u16)(barThumbPosPercent * (barSize - thumbSize));
    Draw_DrawRect(barX, barY + barThumbPosY, SCROLL_BAR_THICKNESS, thumbSize, COLOR_WHITE);
}

static void Gfx_GroupsNextGroup() {
    groupItemsScroll = 0;
    s8 prevGroup = currentGroup;
    do {
        ++currentGroup;
        if (currentGroup >= SPOILER_COLLECTION_GROUP_COUNT) { currentGroup = 1; }
    } while (gSpoilerData.GroupItemCounts[currentGroup] == 0 && currentGroup != prevGroup);
}

static void Gfx_GroupsPrevGroup() {
    groupItemsScroll = 0;
    s8 prevGroup = currentGroup;
    do {
        --currentGroup;
        if (currentGroup < 1) { currentGroup = SPOILER_COLLECTION_GROUP_COUNT - 1; }
    } while (gSpoilerData.GroupItemCounts[currentGroup] == 0 && currentGroup != prevGroup);
}

static void Gfx_DrawChangeMenuPrompt(void) {
    Draw_DrawString(10, SCREEN_BOT_HEIGHT - 30, COLOR_TITLE, "Press B to close menu, L/R to change menu");
    if (curMenuIdx == 3) {
        Draw_DrawFormattedString(10, SCREEN_BOT_HEIGHT - 18, COLOR_TITLE, "Press %c/%c/%c/%c to browse spoiler log",
            LEFT_ARROW_CHR, RIGHT_ARROW_CHR, UP_ARROW_CHR, DOWN_ARROW_CHR);
    }
    else if (curMenuIdx == 4 || curMenuIdx == 6) {
        Draw_DrawFormattedString(10, SCREEN_BOT_HEIGHT - 18, COLOR_TITLE, "Press %c/%c/%c/%c to browse items",
            LEFT_ARROW_CHR, RIGHT_ARROW_CHR, UP_ARROW_CHR, DOWN_ARROW_CHR);
    }
    else if (curMenuIdx == 5) {
        Draw_DrawFormattedString(10, SCREEN_BOT_HEIGHT - 18, COLOR_TITLE, "Press %c/%c/%c/%c to browse items, A/Y to change group",
            LEFT_ARROW_CHR, RIGHT_ARROW_CHR, UP_ARROW_CHR, DOWN_ARROW_CHR);
    }
    else if (curMenuIdx == 7) {
        Draw_DrawFormattedString(10, SCREEN_BOT_HEIGHT - 18, COLOR_TITLE, "Press %c/%c to select option, and %c/%c to change it",
            UP_ARROW_CHR, DOWN_ARROW_CHR, LEFT_ARROW_CHR, RIGHT_ARROW_CHR);
    }
}

static void Gfx_UpdatePlayTime(u8 isInGame)
{
    u64 currentTick = svcGetSystemTick();
    if (!isAsleep && isInGame) {
        ticksElapsed += currentTick - lastTick;
        if (ticksElapsed > MAX_TICK_DELTA) {
            // Assume that if more ticks than MAX_TICK_DELTA have passed, it has been a long
            // time since we last checked, which means the the system may have been asleep or the home button pressed.
            // Reset the timer so we don't artificially inflate the play time.
            ticksElapsed = 0;
        } else {
            while (ticksElapsed >= TICKS_PER_SEC) {
                ticksElapsed -= TICKS_PER_SEC;
                ++gExtSaveData.playtimeSeconds;
            }
        }
    }
    lastTick = currentTick;
}

static void Gfx_DrawSeedHash(void) {
    Draw_DrawFormattedString(10, 10, COLOR_TITLE, "Seed Hash:");
    for (u32 hashIndex = 0; hashIndex < 5; ++hashIndex) {
        Draw_DrawFormattedString(10 + (SPACING_X * 4), 10 + SPACING_Y + (hashIndex * SPACING_Y), COLOR_WHITE, "%s", hashIconNames[gSettingsContext.hashIndexes[hashIndex]]);
    }

    Draw_DrawString(10, 80, COLOR_TITLE, "Play time:");
    u32 hours = gExtSaveData.playtimeSeconds / 3600;
    u32 minutes = (gExtSaveData.playtimeSeconds / 60) % 60;
    u32 seconds = gExtSaveData.playtimeSeconds % 60;
    Draw_DrawFormattedString(10 + (SPACING_X * 4), 80 + SPACING_Y, COLOR_WHITE, "%02u:%02u:%02u", hours, minutes, seconds);
}

static void Gfx_DrawDungeonItems(void) {
    Draw_DrawString(10, 10, COLOR_TITLE, "Dungeon Items");
    // Draw header icons
    Draw_DrawIcon(220, 10, COLOR_WHITE, ICON_SMALL_KEY);
    Draw_DrawIcon(240, 10, COLOR_WHITE, ICON_BOSS_KEY);
    Draw_DrawIcon(260, 10, COLOR_WHITE, ICON_MAP);
    Draw_DrawIcon(280, 10, COLOR_WHITE, ICON_COMPASS);
    if (gSettingsContext.compassesShowWotH) {
        Draw_DrawIcon(300, 10, COLOR_WHITE, ICON_TRIFORCE);
    }

    for (u32 dungeonId = 0; dungeonId <= DUNGEON_GERUDO_FORTRESS; ++dungeonId) {
        u8 yPos = 24 + (dungeonId * 13);
        bool hasBossKey = gSaveContext.dungeonItems[dungeonId] & 1;
        bool hasCompass = gSaveContext.dungeonItems[dungeonId] & 2;
        bool hasMap = gSaveContext.dungeonItems[dungeonId] & 4;
        bool dungeonIsDiscovered = (gSettingsContext.mapsShowDungeonMode && hasMap) || SaveFile_GetIsSceneDiscovered(dungeonId)
            || (dungeonId == DUNGEON_GANONS_CASTLE_SECOND_PART && SaveFile_GetIsSceneDiscovered(DUNGEON_GANONS_CASTLE_FIRST_PART));

        if (dungeonId <= DUNGEON_GERUDO_TRAINING_GROUNDS) {
            // If we've visited the dungeon, we have the map, or all dungeon modes are known due to settings, show whether it's vanilla or MQ
            // Ganon's Tower and Gerudo Training Grounds don't have maps, so they are only revealed by visiting them
            if (dungeonIsDiscovered || gSettingsContext.dungeonModesKnown) {
                bool isMasterQuest =  gSettingsContext.dungeonModes[dungeonId] == DUNGEONMODE_MQ;
                u32 modeIconColor = isMasterQuest ? COLOR_ICON_MASTER_QUEST : COLOR_ICON_VANILLA;
                Draw_IconType modeIconType = isMasterQuest ? ICON_MASTER_QUEST : ICON_VANILLA;
                Draw_DrawIcon(10, yPos, modeIconColor, modeIconType);
            } else {
                Draw_DrawCharacter(10, yPos, COLOR_DARK_GRAY, '?');
            }
        }
        Draw_DrawString(24, yPos, COLOR_WHITE, DungeonNames[dungeonId == DUNGEON_GANONS_CASTLE_SECOND_PART ? DUNGEON_GANONS_CASTLE_FIRST_PART : dungeonId]);

        if (dungeonId > DUNGEON_JABUJABUS_BELLY && dungeonId != DUNGEON_ICE_CAVERN) {
            //special case for Ganon's Castle small keys
            s32 keys = 0;
            if (dungeonId == DUNGEON_GANONS_CASTLE_SECOND_PART) {
            keys = (gSaveContext.dungeonKeys[DUNGEON_GANONS_CASTLE_FIRST_PART] >= 0) ? gSaveContext.dungeonKeys[DUNGEON_GANONS_CASTLE_FIRST_PART] : 0;
            } else {
            keys = (gSaveContext.dungeonKeys[dungeonId] >= 0) ? gSaveContext.dungeonKeys[dungeonId] : 0;
            }
            Draw_DrawFormattedString(220, yPos, keys > 0 ? COLOR_WHITE : COLOR_DARK_GRAY, "%d", keys);
        }

        if ((dungeonId >= DUNGEON_FOREST_TEMPLE && dungeonId <= DUNGEON_SHADOW_TEMPLE) || dungeonId == DUNGEON_GANONS_CASTLE_SECOND_PART) {
            Draw_DrawIcon(240, yPos, hasBossKey ? COLOR_ICON_BOSS_KEY : COLOR_DARK_GRAY, ICON_BOSS_KEY);
        }
        if (dungeonId <= DUNGEON_ICE_CAVERN) {
            Draw_DrawIcon(260, yPos, hasMap ? COLOR_ICON_MAP : COLOR_DARK_GRAY, ICON_MAP);
            Draw_DrawIcon(280, yPos, hasCompass ? COLOR_ICON_COMPASS : COLOR_DARK_GRAY, ICON_COMPASS);

            if (gSettingsContext.compassesShowWotH) {
                if (hasCompass) {
                    if (rDungeonInfoData[dungeonId] == DUNGEON_WOTH) {
                        Draw_DrawIcon(300, yPos, COLOR_ICON_WOTH, ICON_TRIFORCE);
                    } else if (rDungeonInfoData[dungeonId] == DUNGEON_BARREN) {
                        Draw_DrawIcon(300, yPos, COLOR_ICON_FOOL, ICON_FOOL);
                    } else {
                        Draw_DrawCharacter(300, yPos, COLOR_WHITE, '-');
                    }
                } else {
                    Draw_DrawCharacter(300, yPos, COLOR_DARK_GRAY, '?');
                }
            }
        }
    }
}

static void Gfx_DrawDungeonRewards(void) {
    Draw_DrawString(10, 10, COLOR_TITLE, "Dungeon Rewards");
    for (u32 dungeonId = 0; dungeonId <= DUNGEON_SHADOW_TEMPLE; ++dungeonId) {
        u8 yPos = 24 + (dungeonId * 13);
        Draw_DrawString(24, yPos, COLOR_WHITE, DungeonNames[dungeonId]);

        // Only show reward if the player has collected the compass
        // TODO: Optionally always show the reward
        bool hasCompass = gSaveContext.dungeonItems[dungeonId] & 2;
        Draw_DrawString(190, yPos, hasCompass ? COLOR_WHITE : COLOR_DARK_GRAY, hasCompass ? DungeonReward_GetName(dungeonId) : "???");
    }
}

static void Gfx_DrawSpoilerData(void) {
    if (gSpoilerData.SphereCount > 0) {
        u16 itemCount = gSpoilerData.Spheres[currentSphere].ItemCount;

        Draw_DrawFormattedString(10, 10, COLOR_TITLE, "Spoiler Log - Sphere %i / %i", currentSphere + 1, gSpoilerData.SphereCount);

        u16 sphereItemLocOffset = gSpoilerData.Spheres[currentSphere].ItemLocationsOffset;
        u16 listTopY = 26;
        for (u32 item = 0; item < MAX_ITEM_LINES; ++item) {
            u32 locIndex = item + spoilerScroll;
            if (locIndex >= gSpoilerData.Spheres[currentSphere].ItemCount) { break; }

            u32 locPosY = listTopY + ((SPACING_SMALL_Y + 1) * item * 2);
            u32 itemPosY = locPosY + SPACING_SMALL_Y;
            u16 itemIndex = gSpoilerData.SphereItemLocations[sphereItemLocOffset + locIndex];
            u32 color = SpoilerData_GetIsItemLocationCollected(itemIndex) ? COLOR_GREEN : COLOR_WHITE;
            Draw_DrawString_Small(10, locPosY, color,
                SpoilerData_GetItemLocationString(itemIndex));
            Draw_DrawString_Small(10 + SPACING_SMALL_X, itemPosY, color,
                SpoilerData_GetItemNameString(itemIndex));
        }

        Gfx_DrawScrollBar(SCREEN_BOT_WIDTH - 3, listTopY, SCREEN_BOT_HEIGHT - 40 - listTopY, spoilerScroll, itemCount, MAX_ITEM_LINES);
    }
    else {
        Draw_DrawString(10, 10, COLOR_TITLE, "Spoiler Log");
        Draw_DrawString(10, 40, COLOR_WHITE, "No spoiler log generated!");
    }
}

static void Gfx_DrawSpoilerAllItems(void) {
    if (gSpoilerData.ItemLocationsCount > 0) {
        u16 itemCount = gSpoilerData.ItemLocationsCount;

        u16 firstItem = allItemsScroll + 1;
        u16 lastItem = allItemsScroll + MAX_ITEM_LINES;
        if (lastItem > gSpoilerData.ItemLocationsCount) { lastItem = gSpoilerData.ItemLocationsCount; }
        Draw_DrawFormattedString(10, 10, COLOR_TITLE, "All Item Locations (%d - %d) / %d",
            firstItem, lastItem, gSpoilerData.ItemLocationsCount);
        if (!gSettingsContext.ingameSpoilers) {
            Draw_DrawFormattedString(SCREEN_BOT_WIDTH - 10 - (SPACING_X * 6), 10, itemPercent == 100 ? COLOR_GREEN : COLOR_WHITE, "%5.1f%%", itemPercent);
        }

        u16 listTopY = 26;
        for (u32 item = 0; item < MAX_ITEM_LINES; ++item) {
            u32 locIndex = item + allItemsScroll;
            if (locIndex >= gSpoilerData.ItemLocationsCount) { break; }

            u32 locPosY = listTopY + ((SPACING_SMALL_Y + 1) * item * 2);
            u32 itemPosY = locPosY + SPACING_SMALL_Y;
            u32 color = SpoilerData_GetIsItemLocationCollected(locIndex) ? COLOR_GREEN : COLOR_WHITE;
            Draw_DrawString_Small(10, locPosY, color,
                SpoilerData_GetItemLocationString(locIndex));
            const char* itemText = (!gSettingsContext.ingameSpoilers && !SpoilerData_GetIsItemLocationCollected(locIndex)) ? "???" : SpoilerData_GetItemNameString(locIndex);
            Draw_DrawString_Small(10 + SPACING_SMALL_X, itemPosY, color, itemText);
        }

        Gfx_DrawScrollBar(SCREEN_BOT_WIDTH - 3, listTopY, SCREEN_BOT_HEIGHT - 40 - listTopY, allItemsScroll, itemCount, MAX_ITEM_LINES);
    }
    else {
        Draw_DrawString(10, 10, COLOR_TITLE, "All Item Locations");
        Draw_DrawString(10, 40, COLOR_WHITE, "No item location data!");
    }
}

static void Gfx_DrawSpoilerItemGroups(void) {
    if (gSpoilerData.ItemLocationsCount > 0) {
        u16 itemCount = gSpoilerData.GroupItemCounts[currentGroup];
        u16 startIndex = gSpoilerData.GroupOffsets[currentGroup];

        if (!gSettingsContext.ingameSpoilers && itemCount > 0) {
            // Gather up completed items to calculate how far along this group is
            u16 completeItems = 0;
            for (u32 i = 0; i < itemCount; ++i) {
                u32 locIndex = i + startIndex;
                if (SpoilerData_GetIsItemLocationCollected(locIndex)) {
                    ++completeItems;
                }
            }
            float groupPercent = ((float)completeItems / (float)itemCount) * 100.0f;
            Draw_DrawFormattedString(SCREEN_BOT_WIDTH - 10 - (SPACING_X * 6), 10, completeItems == itemCount ? COLOR_GREEN : COLOR_WHITE, "%5.1f%%", groupPercent);
        }

        u16 firstItem = groupItemsScroll + 1;
        u16 lastItem = groupItemsScroll + MAX_ITEM_LINES;
        if (lastItem > itemCount) { lastItem = itemCount; }
        Draw_DrawFormattedString(10, 10, COLOR_TITLE, "%s - (%d - %d) / %d",
            spoilerCollectionGroupNames[currentGroup], firstItem, lastItem, itemCount);

        u16 listTopY = 26;
        for (u32 item = 0; item < MAX_ITEM_LINES; ++item) {
            u32 locIndex = item + startIndex + groupItemsScroll;
            if (item >= itemCount) { break; }

            u32 locPosY = listTopY + ((SPACING_SMALL_Y + 1) * item * 2);
            u32 itemPosY = locPosY + SPACING_SMALL_Y;
            bool isCollected =  SpoilerData_GetIsItemLocationCollected(locIndex);
            u32 color = isCollected ? COLOR_GREEN : COLOR_WHITE;
            Draw_DrawString_Small(10, locPosY, color, SpoilerData_GetItemLocationString(locIndex));
            const char* itemText = (!gSettingsContext.ingameSpoilers && !isCollected) ? "???" : SpoilerData_GetItemNameString(locIndex);
            Draw_DrawString_Small(10 + SPACING_SMALL_X, itemPosY, color, itemText);
        }

        Gfx_DrawScrollBar(SCREEN_BOT_WIDTH - 3, listTopY, SCREEN_BOT_HEIGHT - 40 - listTopY, groupItemsScroll, itemCount, MAX_ITEM_LINES);
    }
    else {
        Draw_DrawString(10, 10, COLOR_TITLE, "Item Location Groups");
        Draw_DrawString(10, 40, COLOR_WHITE, "No item location data!");
    }
}

static void Gfx_DrawERTracker(void) {
    if (gSettingsContext.shuffleOverworldEntrances || gSettingsContext.shuffleDungeonEntrances) {
        u16 itemCount = gEntranceTrackingData.EntrancePairsCount;
        u16 firstItem = entranceScroll + 1;
        u16 lastItem = entranceScroll + MAX_ITEM_LINES;
        if (lastItem > itemCount) { lastItem = itemCount; }
        Draw_DrawFormattedString(10, 10, COLOR_TITLE, "Randomized Entrances (%d - %d) / %d",
            firstItem, lastItem, itemCount);

        // TODO random entrances visited percent?
        // Draw_DrawFormattedString(SCREEN_BOT_WIDTH - 10 - (SPACING_X * 6), 10, itemPercent == 100 ? COLOR_GREEN : COLOR_WHITE, "%5.1f%%", itemPercent);

        u16 listTopY = 26;
        for (u32 item = 0; item < MAX_ITEM_LINES; ++item) {
            u32 locIndex = item + entranceScroll;
            if (locIndex >= itemCount) { break; }

            u32 locPosY = listTopY + ((SPACING_SMALL_Y + 1) * item * 2);
            u32 itemPosY = locPosY + SPACING_SMALL_Y;

            EntranceTrackingPair pair = gEntranceTrackingData.EntrancePairs[locIndex];
            bool isDiscovered = SaveFile_GetIsEntranceDiscovered(pair.StartIndex) || SaveFile_GetIsEntranceDiscovered(pair.ReturnIndex);
            u32 color = isDiscovered ? COLOR_GREEN : COLOR_WHITE;
            const char* unknown = "???";
            const char* startName = pair.StartStrOffset != ENTRANCE_INVALID_STRING_OFFSET ? &gEntranceTrackingData.StringData[pair.StartStrOffset] : "START STRING NOT FOUND";
            const char* returnName = pair.ReturnStrOffset != ENTRANCE_INVALID_STRING_OFFSET ? &gEntranceTrackingData.StringData[pair.ReturnStrOffset] : "RETURN STRING NOT FOUND";
            Draw_DrawFormattedString_Small(10, locPosY, color, "%s ->", isDiscovered ? startName : unknown);
            Draw_DrawFormattedString_Small(10, itemPosY, color, "  %s", isDiscovered ? returnName : unknown);
        }

        Gfx_DrawScrollBar(SCREEN_BOT_WIDTH - 3, listTopY, SCREEN_BOT_HEIGHT - 40 - listTopY, entranceScroll, itemCount, MAX_ITEM_LINES);
    }
    else {
        Draw_DrawString(10, 10, COLOR_TITLE, "Entrances");
        Draw_DrawString(10, 40, COLOR_WHITE, "Entrance randomization disabled!");
    }
    Gfx_DrawChangeMenuPrompt();
}

static void (*menu_draw_funcs[])(void) = {
    Gfx_DrawSeedHash,
    Gfx_DrawDungeonItems,
    Gfx_DrawDungeonRewards,
    Gfx_DrawSpoilerData,
    Gfx_DrawSpoilerAllItems,
    Gfx_DrawSpoilerItemGroups,
    Gfx_DrawERTracker,
    Gfx_DrawOptions,
};

static s16 Gfx_Scroll(s16 current, s16 scrollDelta, u16 itemCount) {
    s16 maxScroll = itemCount > MAX_ITEM_LINES ? itemCount - MAX_ITEM_LINES : 0;
    current += scrollDelta;
    if (current < 0) { current = 0; }
    else if (current > maxScroll) { current = maxScroll; }
    return current;
}

static void Gfx_ShowMenu(void) {
    pressed = 0;

    if (!gSettingsContext.ingameSpoilers) {
        float itemsChecked = 0;
        for (u16 i = 0; i < gSpoilerData.ItemLocationsCount; i++) {
            if (SpoilerData_GetIsItemLocationCollected(i)) {
                itemsChecked++;
            }
        }
        itemPercent = (itemsChecked / gSpoilerData.ItemLocationsCount) * 100;
    }

    Draw_ClearFramebuffer();
    if (gSettingsContext.playOption == 0) { Draw_FlushFramebuffer(); }

    do {
        // End the loop if the system has gone to sleep, so the game can properly respond
        if (isAsleep) {
            break;
        }

        handledInput = false;
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
        } else if (curMenuIdx == 5 && gSpoilerData.ItemLocationsCount > 0) {
            // Grouped Items list
            u16 itemCount = gSpoilerData.GroupItemCounts[currentGroup];
            if (pressed & BUTTON_LEFT) {
                groupItemsScroll = Gfx_Scroll(groupItemsScroll, -MAX_ITEM_LINES * 10, itemCount);
                handledInput = true;
            } else if (pressed & BUTTON_RIGHT) {
                groupItemsScroll = Gfx_Scroll(groupItemsScroll, MAX_ITEM_LINES * 10, itemCount);
                handledInput = true;
            } else if (pressed & BUTTON_UP) {
                groupItemsScroll = Gfx_Scroll(groupItemsScroll, -MAX_ITEM_LINES, itemCount);
                handledInput = true;
            } else if (pressed & BUTTON_DOWN) {
                groupItemsScroll = Gfx_Scroll(groupItemsScroll, MAX_ITEM_LINES, itemCount);
                handledInput = true;
            } else if (pressed & BUTTON_A) {
                Gfx_GroupsNextGroup();
                handledInput = true;
            } else if (pressed & BUTTON_Y) {
                Gfx_GroupsPrevGroup();
                handledInput = true;
            }
        } else if (curMenuIdx == 6 && (gSettingsContext.shuffleOverworldEntrances || gSettingsContext.shuffleDungeonEntrances)) {
            // Entrances list
            u16 itemCount = gEntranceTrackingData.EntrancePairsCount;
            if (pressed & BUTTON_LEFT) {
                entranceScroll = Gfx_Scroll(entranceScroll, -MAX_ITEM_LINES * 10, itemCount);
                handledInput = true;
            } else if (pressed & BUTTON_RIGHT) {
                entranceScroll = Gfx_Scroll(entranceScroll, MAX_ITEM_LINES * 10, itemCount);
                handledInput = true;
            } else if (pressed & BUTTON_UP) {
                entranceScroll = Gfx_Scroll(entranceScroll, -MAX_ITEM_LINES, itemCount);
                handledInput = true;
            } else if (pressed & BUTTON_DOWN) {
                entranceScroll = Gfx_Scroll(entranceScroll, MAX_ITEM_LINES, itemCount);
                handledInput = true;
            }
        } else if (curMenuIdx == 7) {
            Gfx_OptionsUpdate();
        }

        if (!handledInput) {
            if (pressed & closingButton) {
                Draw_ClearBackbuffer();
                Draw_CopyBackBuffer();
                if (gSettingsContext.playOption == 0) { Draw_FlushFramebuffer(); }
                break;
            } else if (pressed & BUTTON_R1) {
                do {
                    curMenuIdx++;
                    if (curMenuIdx >= ARR_SIZE(menu_draw_funcs)) {
                        curMenuIdx = 0;
                    }
                } while (menu_draw_funcs[curMenuIdx] == NULL);
                handledInput = true;
            } else if (pressed & BUTTON_L1) {
                do {
                    curMenuIdx--;
                    if (curMenuIdx < 0) {
                        curMenuIdx = (ARR_SIZE(menu_draw_funcs) - 1);
                    }
                } while (menu_draw_funcs[curMenuIdx] == NULL);
                handledInput = true;
            }
        }

        // Only clear the screen if there's been some input
        if (handledInput) {
            Draw_ClearBackbuffer();
        }

        // Continue counting up play time while in the in-game menu
        Gfx_UpdatePlayTime(true);

        menu_draw_funcs[curMenuIdx]();
        Gfx_DrawChangeMenuPrompt();
        Draw_CopyBackBuffer();
        if (gSettingsContext.playOption == 0) { Draw_FlushFramebuffer(); }

        pressed = Input_WaitWithTimeout(1000, closingButton);

    } while(true);
}

void Gfx_Init(void) {
    Draw_SetupFramebuffer();
    Draw_ClearBackbuffer();

    // Setup the title screen logo edits
    gActorOverlayTable[0x171].initInfo->init = EnMag_rInit;

    if(gSettingsContext.menuOpeningButton == 0)         closingButton = BUTTON_B | BUTTON_SELECT;
    else if(gSettingsContext.menuOpeningButton == 1)    closingButton = BUTTON_B | BUTTON_START;
    else if(gSettingsContext.menuOpeningButton == 2)    closingButton = BUTTON_B | BUTTON_UP;
    else if(gSettingsContext.menuOpeningButton == 3)    closingButton = BUTTON_B | BUTTON_DOWN;
    else if(gSettingsContext.menuOpeningButton == 4)    closingButton = BUTTON_B | BUTTON_RIGHT;
    else if(gSettingsContext.menuOpeningButton == 5)    closingButton = BUTTON_B | BUTTON_LEFT;

    if (gSettingsContext.shuffleRewards != REWARDSHUFFLE_END_OF_DUNGEON || !gSettingsContext.compassesShowReward) {
        menu_draw_funcs[2] = NULL;
    }
    if (!gSettingsContext.ingameSpoilers) {
        menu_draw_funcs[3] = NULL;
    }

    if (gSpoilerData.ItemLocationsCount > 0 && gSpoilerData.GroupItemCounts[currentGroup] == 0) {
        Gfx_GroupsNextGroup(); // Call this to go to the first non-empty group page
    }

    InitOptions();

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
        lastTick = svcGetSystemTick();
    }

    Gfx_UpdatePlayTime(IsInGame());

    if(!isAsleep && openingButton() && IsInGame()){
        Gfx_ShowMenu();
        // Check again as it's possible the system was put to sleep while the menu was open
        if (!isAsleep) {
            svcSleepThread(1000 * 1000 * 300LL);
            // Update lastTick one more time so we don't count the added 0.3s sleep
            lastTick = svcGetSystemTick();
        }
    }
}
