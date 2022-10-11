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
#include "string.h"
#include "savefile.h"
#include "draw.h"
#include "input.h"
#include "multiplayer.h"

u32 pressed;
bool handledInput;

static u8 GfxInit = 0;
static u32 closingButton = 0;
static u8 currentSphere = 0;
static s16 spoilerScroll = 0;

static s16 allItemsScroll = 0;
static s16 groupItemsScroll = 0;
static s8 currentItemGroup = 1;

static s16 allEntranceScroll = 0;
static s16 groupEntranceScroll = 0;
static s8 currentEntranceGroup = 1;
static u8 destListToggle = 0;

static s32 curMenuIdx = 0;
static bool showingLegend = false;
static u64 lastTick = 0;
static u64 ticksElapsed = 0;
static bool isAsleep = false;

DungeonInfo rDungeonInfoData[10];

#define MAX_TICK_DELTA (TICKS_PER_SEC * 3)

static s8 spoilerGroupDungeonIds[] = {
    -1,
    -1,
    -1,
    DUNGEON_DEKU_TREE,
    DUNGEON_FOREST_TEMPLE,
    -1,
    DUNGEON_BOTTOM_OF_THE_WELL,
    DUNGEON_SHADOW_TEMPLE,
    -1,
    -1,
    DUNGEON_DODONGOS_CAVERN,
    DUNGEON_FIRE_TEMPLE,
    -1,
    -1,
    DUNGEON_JABUJABUS_BELLY,
    DUNGEON_ICE_CAVERN,
    -1,
    -1,
    -1,
    DUNGEON_WATER_TEMPLE,
    -1,
    DUNGEON_GERUDO_TRAINING_GROUNDS,
    DUNGEON_SPIRIT_TEMPLE,
    -1,
    DUNGEON_GANONS_TOWER,
};

static char *spoilerCollectionGroupNames[] = {
    "All Item Locations", // All
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

static char* spoilerEntranceGroupNames[] = {
    "Randomized Entrances", // All
    "Spawns/Warp Songs/Owls",
    "Kokiri Forest",
    "Lost Woods",
    "Sacred Forest Meadow",
    "Kakariko Village",
    "Graveyard",
    "Death Mountain Trail",
    "Death Mountain Crater",
    "Goron City",
    "Zora's River",
    "Zora's Domain",
    "Zora's Fountain",
    "Hyrule Field",
    "Lon Lon Ranch",
    "Lake Hylia",
    "Gerudo Valley",
    "Haunted Wasteland",
    "Market",
    "Hyrule Castle",
};

#define UP_ARROW_CHR 24
#define DOWN_ARROW_CHR 25
#define LEFT_ARROW_CHR 27
#define RIGHT_ARROW_CHR 26
#define H_DOUBLE_ARROW_CHR 29
#define UP_SOLID_ARROW_CHR 30
#define DOWN_SOLID_ARROW_CHR 31

#define MAX_ENTRY_LINES 9
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

#define COLOR_BUTTON_A          RGB8(0xFF, 0x49, 0x3E)
#define COLOR_BUTTON_B          RGB8(0xFD, 0xDD, 0x68)
#define COLOR_BUTTON_X          RGB8(0x32, 0x7D, 0xFE)
#define COLOR_BUTTON_Y          RGB8(0x00, 0xD0, 0x98)

typedef enum {
    PAGE_SEEDHASH,
    PAGE_DUNGEONITEMS,
    PAGE_DUNGEONREWARDS,
    PAGE_SPHERES,
    PAGE_ITEMTRACKER_ALL,
    PAGE_ITEMTRACKER_GROUPS,
    PAGE_ENTRANCETRACKER_ALL,
    PAGE_ENTRANCETRACKER_GROUPS,
    PAGE_OPTIONS,
} GfxPage;

static u32 entranceTypeToColor[] = { COLOR_YELLOW, COLOR_GREEN, COLOR_BLUE, COLOR_ORANGE, COLOR_PINK };

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

static bool IsEntranceDiscovered(s16 index) {
    bool isDiscovered = SaveFile_GetIsEntranceDiscovered(index);
    if (!isDiscovered) {
        // If the pair included one of the hyrule field <-> zora's river entrances,
        // the randomizer will have also overriden the water-based entrances, so check those too
        if ((index == 0x00EA && SaveFile_GetIsEntranceDiscovered(0x01D9)) || (index == 0x01D9 && SaveFile_GetIsEntranceDiscovered(0x00EA))) {
            isDiscovered = true;
        } else if ((index == 0x0181 && SaveFile_GetIsEntranceDiscovered(0x0311)) || (index == 0x0311 && SaveFile_GetIsEntranceDiscovered(0x0181))) {
            isDiscovered = true;
        }
    }
    return isDiscovered;
}

static bool IsDungeonDiscovered(DungeonId dungeonId) {
    if (dungeonId <= DUNGEON_GERUDO_TRAINING_GROUNDS) {
        if (gSettingsContext.dungeonModesKnown[dungeonId]) {
            return true;
        }

        // A dungeon is considered discovered if we've visited the dungeon at least once, we have the map,
        // or the dungeon mode is known due to settings.
        // Ganon's Tower and Gerudo Training Grounds don't have maps, so they are only revealed by visiting them
        bool hasMap = gSaveContext.dungeonItems[dungeonId] & 4;
        bool dungeonIsDiscovered = (gSettingsContext.mapsShowDungeonMode && hasMap) || SaveFile_GetIsSceneDiscovered(dungeonId)
            || (dungeonId == DUNGEON_GANONS_TOWER && SaveFile_GetIsSceneDiscovered(DUNGEON_INSIDE_GANONS_CASTLE));

        return dungeonIsDiscovered;
    }
    return false;
}

static bool CanShowSpoilerGroup(SpoilerCollectionCheckGroup group) {
    s8 dungeonId = spoilerGroupDungeonIds[group];
    return dungeonId == -1 || IsDungeonDiscovered(dungeonId);
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

static void NextItemGroup() {
    groupItemsScroll = 0;
    s8 prevGroup = currentItemGroup;
    do {
        ++currentItemGroup;
        if (currentItemGroup >= SPOILER_COLLECTION_GROUP_COUNT) { currentItemGroup = 1; }
    } while (gSpoilerData.GroupItemCounts[currentItemGroup] == 0 && currentItemGroup != prevGroup);
}

static void PrevItemGroup() {
    groupItemsScroll = 0;
    s8 prevGroup = currentItemGroup;
    do {
        --currentItemGroup;
        if (currentItemGroup < 1) { currentItemGroup = SPOILER_COLLECTION_GROUP_COUNT - 1; }
    } while (gSpoilerData.GroupItemCounts[currentItemGroup] == 0 && currentItemGroup != prevGroup);
}

static void NextEntranceGroup() {
    groupEntranceScroll = 0;
    s8 prevGroup = currentEntranceGroup;
    do {
        ++currentEntranceGroup;
        if (currentEntranceGroup >= SPOILER_ENTRANCE_GROUP_COUNT) { currentEntranceGroup = 1; }
    } while (gEntranceTrackingData.GroupEntranceCounts[destListToggle][currentEntranceGroup] == 0 && currentEntranceGroup != prevGroup);
}

static void PrevEntranceGroup() {
    groupEntranceScroll = 0;
    s8 prevGroup = currentEntranceGroup;
    do {
        --currentEntranceGroup;
        if (currentEntranceGroup < 1) { currentEntranceGroup = SPOILER_ENTRANCE_GROUP_COUNT - 1; }
    } while (gEntranceTrackingData.GroupEntranceCounts[destListToggle][currentEntranceGroup] == 0 && currentEntranceGroup != prevGroup);
}

static void Gfx_DrawButtonPrompts(void) {
    u32 promptY = SCREEN_BOT_HEIGHT - 16;
    u32 textY = promptY - 1;
    // Close prompt, always shown
    Draw_DrawIcon(SCREEN_BOT_WIDTH - 50, promptY, COLOR_BUTTON_B, ICON_BUTTON_B);
    Draw_DrawString(SCREEN_BOT_WIDTH - 38, textY, COLOR_TITLE, "Close");

    if (curMenuIdx == PAGE_DUNGEONITEMS) {
        Draw_DrawIcon(10, promptY, COLOR_BUTTON_A, ICON_BUTTON_A);
        Draw_DrawString(22, textY, COLOR_TITLE, "Toggle Legend");
    } else if (curMenuIdx == PAGE_SPHERES) {
        Draw_DrawIcon(10, promptY, COLOR_WHITE, ICON_BUTTON_DPAD);
        Draw_DrawString(22, textY, COLOR_TITLE, "Browse spoiler log");
    } else if (curMenuIdx >= PAGE_ITEMTRACKER_ALL && curMenuIdx <= PAGE_ENTRANCETRACKER_GROUPS) {
        Draw_DrawIcon(10, promptY, COLOR_WHITE, ICON_BUTTON_DPAD);
        Draw_DrawString(22, textY, COLOR_TITLE, "Browse entries");
        static const u8 offsetX = 114;
        if (curMenuIdx == PAGE_ITEMTRACKER_GROUPS || curMenuIdx == PAGE_ENTRANCETRACKER_GROUPS) {
            Draw_DrawIcon(offsetX, promptY, COLOR_BUTTON_Y, ICON_BUTTON_Y);
            Draw_DrawString(offsetX + 8, textY, COLOR_TITLE, "/");
            Draw_DrawIcon(offsetX + 16, promptY, COLOR_BUTTON_A, ICON_BUTTON_A);
            Draw_DrawString(offsetX + 28, textY, COLOR_TITLE, "Change group");
            if (curMenuIdx == PAGE_ENTRANCETRACKER_GROUPS) {
                static const u8 toggleOffsetX = 222;
                Draw_DrawIcon(toggleOffsetX, promptY, COLOR_BUTTON_X, ICON_BUTTON_X);
                const char* destToggleString = destListToggle ? "Dest" : "Src";
                Draw_DrawString(toggleOffsetX + 12, textY, COLOR_TITLE, destToggleString);
            }
        } else if (curMenuIdx == PAGE_ITEMTRACKER_ALL || curMenuIdx == PAGE_ENTRANCETRACKER_ALL) {
            Draw_DrawIcon(offsetX, promptY, COLOR_BUTTON_A, ICON_BUTTON_A);
            Draw_DrawString(offsetX + 12, textY, COLOR_TITLE, "Toggle Legend");
        }
    } else if (curMenuIdx == PAGE_OPTIONS) {
        Draw_DrawIcon(10, promptY, COLOR_WHITE, ICON_BUTTON_DPAD);
        Draw_DrawString(22, textY, COLOR_TITLE, "Select / change options");
    }
}

static void Gfx_UpdatePlayTime(void)
{
    u64 currentTick = svcGetSystemTick();
    if (!isAsleep && IsInGame()) {
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
    u8 offsetY = 0;
    Draw_DrawFormattedString(10, 16 + (SPACING_Y * offsetY++), COLOR_TITLE, "Seed Hash:");
    for (u32 hashIndex = 0; hashIndex < ARRAY_SIZE(gSettingsContext.hashIndexes); ++hashIndex) {
        Draw_DrawFormattedString(10 + (SPACING_X * 4), 16 + (SPACING_Y * offsetY++), COLOR_WHITE, "%s", hashIconNames[gSettingsContext.hashIndexes[hashIndex]]);
    }
    offsetY++;

    Draw_DrawString(10, 16 + (SPACING_Y * offsetY++), COLOR_TITLE, "Play time:");
    u32 hours = gExtSaveData.playtimeSeconds / 3600;
    u32 minutes = (gExtSaveData.playtimeSeconds / 60) % 60;
    u32 seconds = gExtSaveData.playtimeSeconds % 60;
    Draw_DrawFormattedString(10 + (SPACING_X * 4), 16 + (SPACING_Y * offsetY++), COLOR_WHITE, "%02u:%02u:%02u", hours, minutes, seconds);
    offsetY++;

    if (gSettingsContext.mp_Enabled) {
        Draw_DrawFormattedString(10, 16 + (SPACING_Y * offsetY++), COLOR_TITLE, "Multiplayer:");
        s16 playerCount = Multiplayer_PlayerCount();
        if (playerCount >= 0) {
            Draw_DrawFormattedString(10 + (SPACING_X * 4), 16 + (SPACING_Y * offsetY++), COLOR_WHITE, "Connected players: %d", playerCount);
        } else {
            Draw_DrawFormattedString(10 + (SPACING_X * 4), 16 + (SPACING_Y * offsetY++), COLOR_WHITE, "Connected players: Unknown");
        }
        Draw_DrawFormattedString(10 + (SPACING_X * 4), 16 + (SPACING_Y * offsetY++), COLOR_WHITE, "Received packets: %d", mp_receivedPackets);
        if (gSettingsContext.mp_SharedProgress) {
            Draw_DrawFormattedString(10 + (SPACING_X * 4), 16 + (SPACING_Y * offsetY++), COLOR_WHITE, "Sync ID: %d", gSettingsContext.mp_SyncId);
        }
        offsetY++;
    }
}

static void Gfx_DrawDungeonItems(void) {
    if (showingLegend) {
        Draw_DrawString(10, 16, COLOR_TITLE, "Dungeon Items Legend");
        Draw_DrawIcon(10, 43, COLOR_ICON_VANILLA, ICON_VANILLA);
        Draw_DrawIcon(10, 56, COLOR_ICON_MASTER_QUEST, ICON_MASTER_QUEST);

        Draw_DrawIcon(10, 82, COLOR_WHITE, ICON_SMALL_KEY);
        Draw_DrawIcon(10, 95, COLOR_ICON_BOSS_KEY, ICON_BOSS_KEY);
        Draw_DrawIcon(10, 108, COLOR_ICON_MAP, ICON_MAP);
        Draw_DrawIcon(10, 121, COLOR_ICON_COMPASS, ICON_COMPASS);

        Draw_DrawIcon(10, 147, COLOR_ICON_WOTH, ICON_TRIFORCE);
        Draw_DrawIcon(10, 160, COLOR_ICON_FOOL, ICON_FOOL);
        Draw_DrawString(10, 173, COLOR_WHITE, "-");

        Draw_DrawString(24, 43, COLOR_WHITE, "Vanilla Dungeon");
        Draw_DrawString(24, 56, COLOR_WHITE, "Master Quest Dungeon");

        Draw_DrawString(24, 82, COLOR_WHITE, "Small Key");
        Draw_DrawString(24, 95, COLOR_WHITE, "Boss Key");
        Draw_DrawString(24, 108, COLOR_WHITE, "Map");
        Draw_DrawString(24, 121, COLOR_WHITE, "Compass");

        Draw_DrawString(24, 147, COLOR_WHITE, "Way of the Hero");
        Draw_DrawString(24, 160, COLOR_WHITE, "Barren Location");
        Draw_DrawString(24, 173, COLOR_WHITE, "Non-WotH / Non-Barren Location");
        return;
    }
    Draw_DrawString(10, 16, COLOR_TITLE, "Dungeon Items");
    // Draw header icons
    Draw_DrawIcon(220, 16, COLOR_WHITE, ICON_SMALL_KEY);
    Draw_DrawIcon(240, 16, COLOR_WHITE, ICON_BOSS_KEY);
    Draw_DrawIcon(260, 16, COLOR_WHITE, ICON_MAP);
    Draw_DrawIcon(280, 16, COLOR_WHITE, ICON_COMPASS);
    if (gSettingsContext.compassesShowWotH) {
        Draw_DrawIcon(300, 16, COLOR_WHITE, ICON_TRIFORCE);
    }

    u8 yPos = 0;
    for (u32 dungeonId = 0; dungeonId <= DUNGEON_THIEVES_HIDEOUT; ++dungeonId) {
        yPos = 30 + (dungeonId * 13);
        bool hasBossKey = gSaveContext.dungeonItems[dungeonId] & 1;
        bool hasCompass = gSaveContext.dungeonItems[dungeonId] & 2;
        bool hasMap = gSaveContext.dungeonItems[dungeonId] & 4;

        if (dungeonId <= DUNGEON_GERUDO_TRAINING_GROUNDS) {
            if (IsDungeonDiscovered(dungeonId)) {
                bool isMasterQuest = gSettingsContext.dungeonModes[dungeonId] == DUNGEONMODE_MQ;
                u32 modeIconColor = isMasterQuest ? COLOR_ICON_MASTER_QUEST : COLOR_ICON_VANILLA;
                Draw_IconType modeIconType = isMasterQuest ? ICON_MASTER_QUEST : ICON_VANILLA;
                Draw_DrawIcon(10, yPos, modeIconColor, modeIconType);
            } else {
                Draw_DrawCharacter(10, yPos, COLOR_DARK_GRAY, '?');
            }
        }
        Draw_DrawString(24, yPos, COLOR_WHITE, DungeonNames[dungeonId == DUNGEON_GANONS_TOWER ? DUNGEON_INSIDE_GANONS_CASTLE : dungeonId]);

        if (dungeonId > DUNGEON_JABUJABUS_BELLY && dungeonId != DUNGEON_ICE_CAVERN) {
            //special case for Ganon's Castle small keys
            s32 keys = 0;
            if (dungeonId == DUNGEON_GANONS_TOWER) {
                keys = (gSaveContext.dungeonKeys[DUNGEON_INSIDE_GANONS_CASTLE] >= 0) ? gSaveContext.dungeonKeys[DUNGEON_INSIDE_GANONS_CASTLE] : 0;
            } else {
                keys = (gSaveContext.dungeonKeys[dungeonId] >= 0) ? gSaveContext.dungeonKeys[dungeonId] : 0;
            }
            Draw_DrawFormattedString(220, yPos, keys > 0 ? COLOR_WHITE : COLOR_DARK_GRAY, "%d", keys);
        }

        if ((dungeonId >= DUNGEON_FOREST_TEMPLE && dungeonId <= DUNGEON_SHADOW_TEMPLE) || dungeonId == DUNGEON_GANONS_TOWER) {
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

    // Show key count for Treasure Chest Shop if the option is enabled
    yPos += 13;
    if (gSettingsContext.shuffleChestMinigame) {
        Draw_DrawString(24, yPos, COLOR_WHITE, "Treasure Chest Shop");
        s32 chestGameKeys = (gSaveContext.dungeonKeys[DUNGEON_TREASURE_CHEST_SHOP] >= 0) ? gSaveContext.dungeonKeys[DUNGEON_TREASURE_CHEST_SHOP] : 0;
        Draw_DrawFormattedString(220, yPos, chestGameKeys > 0 ? COLOR_WHITE : COLOR_DARK_GRAY, "%d", chestGameKeys);
    }
}

static void Gfx_DrawDungeonRewards(void) {
    Draw_DrawString(10, 16, COLOR_TITLE, "Dungeon Rewards");
    for (u32 dungeonId = 0; dungeonId <= DUNGEON_SHADOW_TEMPLE; ++dungeonId) {
        u8 yPos = 30 + (dungeonId * 13);
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

        Draw_DrawFormattedString(10, 16, COLOR_TITLE, "Spoiler Log - Sphere %i / %i", currentSphere + 1, gSpoilerData.SphereCount);

        u16 sphereItemLocOffset = gSpoilerData.Spheres[currentSphere].ItemLocationsOffset;
        u16 listTopY = 32;
        for (u32 item = 0; item < MAX_ENTRY_LINES; ++item) {
            u32 locIndex = item + spoilerScroll;
            if (locIndex >= gSpoilerData.Spheres[currentSphere].ItemCount) { break; }

            u32 locPosY = listTopY + ((SPACING_SMALL_Y + 1) * item * 2);
            u32 itemPosY = locPosY + SPACING_SMALL_Y;
            u16 itemIndex = gSpoilerData.SphereItemLocations[sphereItemLocOffset + locIndex];
            u32 color = COLOR_WHITE;
            if (SpoilerData_GetIsItemLocationCollected(itemIndex)) {
                color = COLOR_GREEN;
            } else if (gSpoilerData.ItemLocations[itemIndex].CollectType == COLLECTTYPE_REPEATABLE) {
                color = COLOR_BLUE;
            } else if (gSpoilerData.ItemLocations[itemIndex].CollectType == COLLECTTYPE_NEVER) {
                color = COLOR_ORANGE;
            }
            Draw_DrawString_Small(10, locPosY, color,
                SpoilerData_GetItemLocationString(itemIndex));
            Draw_DrawString_Small(10 + (SPACING_SMALL_X * 2), itemPosY, color,
                SpoilerData_GetItemNameString(itemIndex));
        }

        Gfx_DrawScrollBar(SCREEN_BOT_WIDTH - 3, listTopY, SCREEN_BOT_HEIGHT - 40 - listTopY, spoilerScroll, itemCount, MAX_ENTRY_LINES);
    }
    else {
        Draw_DrawString(10, 16, COLOR_TITLE, "Spoiler Log");
        Draw_DrawString(10, 46, COLOR_WHITE, "No spoiler log generated!");
    }
}

static u8 ViewingGroups() {
    return curMenuIdx == PAGE_ITEMTRACKER_GROUPS || curMenuIdx == PAGE_ENTRANCETRACKER_GROUPS;
}

static void Gfx_DrawItemTracker(void) {
    if (!ViewingGroups() && showingLegend) {
        Draw_DrawString(10, 16, COLOR_TITLE, "Item Color Legend");

        static const u8 squareWidth = 9;
        u16 offsetY = 2;
        Draw_DrawRect(10, 16 + SPACING_Y * offsetY, squareWidth, squareWidth, COLOR_GREEN);
        Draw_DrawString(10 + SPACING_X * 2, 16 + SPACING_Y * offsetY++, COLOR_WHITE, "Collected");
        Draw_DrawRect(10, 16 + SPACING_Y * offsetY, squareWidth, squareWidth, COLOR_BLUE);
        Draw_DrawString(10 + SPACING_X * 2, 16 + SPACING_Y * offsetY++, COLOR_WHITE, "Repeatable");
        Draw_DrawRect(10, 16 + SPACING_Y * offsetY, squareWidth, squareWidth, COLOR_ORANGE);
        Draw_DrawString(10 + SPACING_X * 2, 16 + SPACING_Y * offsetY++, COLOR_WHITE, "Uncollectable");
        return;
    }
    if (ViewingGroups() && !CanShowSpoilerGroup(currentItemGroup)) {
        Draw_DrawString(10, 16, COLOR_TITLE, spoilerCollectionGroupNames[currentItemGroup]);
        Draw_DrawString(10, 46, COLOR_WHITE, "Reveal this dungeon to see the item list.");
        Draw_DrawString(10, 57, COLOR_WHITE, " - Enter the dungeon at least once");
        if (gSettingsContext.mapsShowDungeonMode) {
            Draw_DrawString(10, 68, COLOR_WHITE, " - Find the dungeon's map");
        }
        return;
    }

    u16 itemCount = ViewingGroups() ? gSpoilerData.GroupItemCounts[currentItemGroup] : gSpoilerData.ItemLocationsCount;
    u16 startIndex = ViewingGroups() ? gSpoilerData.GroupOffsets[currentItemGroup] : 0;
    s16* itemScroll = ViewingGroups() ? &groupItemsScroll : &allItemsScroll;

    // Gather up completed items to calculate how far along this group is
    u16 completeItems = 0;
    u16 uncollectableItems = 0;
    for (u32 i = 0; i < itemCount; ++i) {
        u32 locIndex = i + startIndex;
        if (SpoilerData_GetIsItemLocationCollected(locIndex)) {
            completeItems++;
        } else if (gSpoilerData.ItemLocations[locIndex].CollectType == COLLECTTYPE_NEVER ||
            (gSpoilerData.ItemLocations[locIndex].CollectType == COLLECTTYPE_REPEATABLE && SpoilerData_GetIsItemLocationRevealed(locIndex))) {
            uncollectableItems++;
        }
    }
    u16 collectableItems = itemCount - uncollectableItems;
    float groupPercent = ((float)completeItems / (float)collectableItems) * 100.0f;
    Draw_DrawFormattedString(SCREEN_BOT_WIDTH - 10 - (SPACING_X * 6), 16, completeItems == collectableItems ? COLOR_GREEN : COLOR_WHITE, "%5.1f%%", groupPercent);

    u16 firstItem = *itemScroll + 1;
    u16 lastItem = *itemScroll + MAX_ENTRY_LINES;
    if (lastItem > itemCount) { lastItem = itemCount; }
    Draw_DrawFormattedString(10, 16, COLOR_TITLE, "%s - (%d - %d) / %d",
        spoilerCollectionGroupNames[ViewingGroups() ? currentItemGroup : 0], firstItem, lastItem, itemCount);

    u16 listTopY = 32;
    u32 itemGroupIndex = 1; // Keep the last picked group index around to start the search from
    for (u32 item = 0; item < MAX_ENTRY_LINES; ++item) {
        u32 locIndex = item + startIndex + *itemScroll;
        if (item >= itemCount) { break; }

        u32 locPosY = listTopY + ((SPACING_SMALL_Y + 1) * item * 2);
        u32 itemPosY = locPosY + SPACING_SMALL_Y;
        bool isCollected = SpoilerData_GetIsItemLocationCollected(locIndex);

        // Find this item's group index, so we can see if we should hide
        // its name because it's located in an undiscovered dungeon
        for (u32 group = itemGroupIndex; group < SPOILER_COLLECTION_GROUP_COUNT; ++group) {
            u16 groupOffset = gSpoilerData.GroupOffsets[group];
            if (locIndex >= groupOffset && locIndex < groupOffset + gSpoilerData.GroupItemCounts[group]) {
                itemGroupIndex = group;
                break;
            }
        }
        bool canShowGroup = isCollected || CanShowSpoilerGroup(itemGroupIndex);

        u32 color = COLOR_WHITE;
        if (isCollected) {
            color = COLOR_GREEN;
        } else if (canShowGroup) {
            if (gSpoilerData.ItemLocations[locIndex].CollectType == COLLECTTYPE_REPEATABLE && SpoilerData_GetIsItemLocationRevealed(locIndex)) {
                color = COLOR_BLUE;
            } else if (gSpoilerData.ItemLocations[locIndex].CollectType == COLLECTTYPE_NEVER) {
                color = COLOR_ORANGE;
            }
        }
        bool itemRevealed = canShowGroup && (isCollected || SpoilerData_GetIsItemLocationRevealed(locIndex));

        if (canShowGroup) {
            Draw_DrawString_Small(10, locPosY, color, SpoilerData_GetItemLocationString(locIndex));
        } else {
            Draw_DrawFormattedString_Small(10, locPosY, color, "%s (Undiscovered)", spoilerCollectionGroupNames[itemGroupIndex]);
        }
        const char* itemText = itemRevealed ? SpoilerData_GetItemNameString(locIndex) : "???";
        Draw_DrawString_Small(10 + (SPACING_SMALL_X * 2), itemPosY, color, itemText);
    }

    Gfx_DrawScrollBar(SCREEN_BOT_WIDTH - 3, listTopY, SCREEN_BOT_HEIGHT - 40 - listTopY, *itemScroll, itemCount, MAX_ENTRY_LINES);
}

static void Gfx_DrawEntranceTracker(void) {
    if (!ViewingGroups() && showingLegend) {
        Draw_DrawString(10, 16, COLOR_TITLE, "Entrance Color Legend");

        static const u8 squareWidth = 9;
        u16 offsetY = 2;
        Draw_DrawRect(10, 16 + SPACING_Y * offsetY, squareWidth, squareWidth, COLOR_YELLOW);
        Draw_DrawString(10 + SPACING_X * 2, 16 + SPACING_Y * offsetY++, COLOR_WHITE, "Spawns/Warp Songs/Owls");
        Draw_DrawRect(10, 16 + SPACING_Y * offsetY, squareWidth, squareWidth, COLOR_GREEN);
        Draw_DrawString(10 + SPACING_X * 2, 16 + SPACING_Y * offsetY++, COLOR_WHITE, "Overworld");
        Draw_DrawRect(10, 16 + SPACING_Y * offsetY, squareWidth, squareWidth, COLOR_BLUE);
        Draw_DrawString(10 + SPACING_X * 2, 16 + SPACING_Y * offsetY++, COLOR_WHITE, "Interior");
        Draw_DrawRect(10, 16 + SPACING_Y * offsetY, squareWidth, squareWidth, COLOR_ORANGE);
        Draw_DrawString(10 + SPACING_X * 2, 16 + SPACING_Y * offsetY++, COLOR_WHITE, "Grotto");
        Draw_DrawRect(10, 16 + SPACING_Y * offsetY, squareWidth, squareWidth, COLOR_PINK);
        Draw_DrawString(10 + SPACING_X * 2, 16 + SPACING_Y * offsetY++, COLOR_WHITE, "Dungeon");
        return;
    }

    EntranceOverride* entranceList = (ViewingGroups() && destListToggle) ? destList : rEntranceOverrides;

    u16 entranceCount = ViewingGroups() ? gEntranceTrackingData.GroupEntranceCounts[destListToggle][currentEntranceGroup] : gEntranceTrackingData.EntranceCount;
    u16 startIndex = ViewingGroups() ? gEntranceTrackingData.GroupOffsets[destListToggle][currentEntranceGroup] : 0;
    s16* entranceScroll = ViewingGroups() ? &groupEntranceScroll : &allEntranceScroll;

    if (entranceCount > 0) {
        // Gather up discovered entrances to calculate how far along this group is
        u16 discoveredEntrs = 0;
        for (u32 i = 0; i < entranceCount; ++i) {
            u32 locIndex = i + startIndex;
            if (IsEntranceDiscovered(entranceList[locIndex].index)) {
                ++discoveredEntrs;
            }
        }
        float groupPercent = ((float)discoveredEntrs / (float)entranceCount) * 100.0f;
        Draw_DrawFormattedString(SCREEN_BOT_WIDTH - 10 - (SPACING_X * 6), 16, discoveredEntrs == entranceCount ? COLOR_GREEN : COLOR_WHITE, "%5.1f%%", groupPercent);
    }

    u16 firstEntr = *entranceScroll + 1;
    u16 lastEntr = *entranceScroll + MAX_ENTRY_LINES;
    if (lastEntr > entranceCount) { lastEntr = entranceCount; }
    Draw_DrawFormattedString(10, 16, COLOR_TITLE, "%s - (%d - %d) / %d",
        spoilerEntranceGroupNames[ViewingGroups() ? currentEntranceGroup : 0], firstEntr, lastEntr, entranceCount);

    u16 listTopY = 32;
    for (u32 entrance = 0; entrance < MAX_ENTRY_LINES; ++entrance) {
        u32 locIndex = entrance + startIndex + *entranceScroll;
        if (entrance >= entranceCount) { break; }

        u32 locPosY = listTopY + ((SPACING_SMALL_Y + 1) * entrance * 2);
        u32 entrPosY = locPosY + SPACING_SMALL_Y;

        bool isDiscovered = IsEntranceDiscovered(entranceList[locIndex].index);

        const EntranceData* original = GetEntranceData(entranceList[locIndex].index);
        const EntranceData* override = GetEntranceData(entranceList[locIndex].override);

        u32 origSrcColor = isDiscovered ? entranceTypeToColor[original->type] : COLOR_WHITE;
        u32 origDstColor = isDiscovered ? entranceTypeToColor[original->type] : COLOR_WHITE;
        u32 rplcSrcColor = isDiscovered ? entranceTypeToColor[override->type] : COLOR_WHITE;
        u32 rplcDstColor = isDiscovered ? entranceTypeToColor[override->type] : COLOR_WHITE;

        u8 showOriginal = gSettingsContext.ingameSpoilers || (!destListToggle || original->srcGroup == ENTRANCE_GROUP_ONE_WAY) || isDiscovered;
        u8 showOverride = gSettingsContext.ingameSpoilers || ( destListToggle && original->srcGroup != ENTRANCE_GROUP_ONE_WAY) || isDiscovered;

        const char* unknown = "???";

        const char* origSrcName = showOriginal ? original->source      : unknown;
        const char* origDstName = showOriginal ? original->destination : unknown;
        const char* rplcSrcName = showOverride ? override->source      : unknown;
        const char* rplcDstName = showOverride ? override->destination : unknown;

        u16 offsetX = 0;
        Draw_DrawFormattedString_Small(10, locPosY, origSrcColor, "%s", origSrcName);
        offsetX += strlen(origSrcName) + 1;
        // Don't show original destinations for one way entrances
        if (original->srcGroup != ENTRANCE_GROUP_ONE_WAY) {
            Draw_DrawFormattedString_Small(10 + offsetX * SPACING_SMALL_X, locPosY, COLOR_WHITE, "to");
            offsetX += strlen("to") + 1;
            Draw_DrawFormattedString_Small(10 + offsetX * SPACING_SMALL_X, locPosY, origDstColor, "%s", origDstName);
            offsetX += strlen(origDstName) + 1;
        }
        Draw_DrawFormattedString_Small(10 + offsetX * SPACING_SMALL_X, locPosY, COLOR_WHITE, "%c", RIGHT_ARROW_CHR);

        offsetX = 2;
        Draw_DrawFormattedString_Small(10 + offsetX * SPACING_SMALL_X, entrPosY, rplcDstColor, "%s", rplcDstName);
        // Don't show the replacement source area if the area only has one entrance, or if the entrance
        // is one-way
        if (!showOverride || (showOverride && (!override->oneExit && override->srcGroup != ENTRANCE_GROUP_ONE_WAY))) {
            offsetX += strlen(rplcDstName) + 1;
            Draw_DrawFormattedString_Small(10 + offsetX * SPACING_SMALL_X, entrPosY, COLOR_WHITE, "from");
            offsetX += strlen("from") + 1;
            Draw_DrawFormattedString_Small(10 + offsetX * SPACING_SMALL_X, entrPosY, rplcSrcColor, "%s", rplcSrcName);
        }
    }

    Gfx_DrawScrollBar(SCREEN_BOT_WIDTH - 3, listTopY, SCREEN_BOT_HEIGHT - 40 - listTopY, *entranceScroll, entranceCount, MAX_ENTRY_LINES);
}

static void (*menu_draw_funcs[])(void) = {
    // Make sure these line up with the GfxPage enum above
    Gfx_DrawSeedHash,
    Gfx_DrawDungeonItems,
    Gfx_DrawDungeonRewards,
    Gfx_DrawSpoilerData,
    Gfx_DrawItemTracker, // All
    Gfx_DrawItemTracker, // Groups
    Gfx_DrawEntranceTracker, // All
    Gfx_DrawEntranceTracker, // Groups
    Gfx_DrawOptions,
};

static void Gfx_DrawHeader() {
    const u32 totalTabsWidth = 280;
    u32 tabsCount = ARR_SIZE(menu_draw_funcs);
    u32 tabWidthPlusSpace = totalTabsWidth / tabsCount;
    u32 tabXStart = 20;
    u32 tabYStart = 3;
    u32 tabHeightSmall = 4;
    u32 tabHeightBig = 6;

    Draw_DrawIcon(3, 2, COLOR_WHITE, ICON_BUTTON_L_WIDE_1);
    Draw_DrawIcon(11, 2, COLOR_WHITE, ICON_BUTTON_L_WIDE_2);
    Draw_DrawIcon(SCREEN_BOT_WIDTH - 19, 2, COLOR_WHITE, ICON_BUTTON_R_WIDE_1);
    Draw_DrawIcon(SCREEN_BOT_WIDTH - 11, 2, COLOR_WHITE, ICON_BUTTON_R_WIDE_2);

    for (u32 i = 0; i < tabsCount; i++) {
        bool isAvailable = menu_draw_funcs[i] != NULL;
        bool isCurrent = curMenuIdx == i;
        u32 tabX = (u32)(i * tabWidthPlusSpace);
        Draw_DrawRect(tabXStart + tabX,
            isCurrent ? tabYStart : tabYStart + 2,
            i == tabsCount - 1 ? totalTabsWidth - tabX : (tabWidthPlusSpace - 1),
            isCurrent ? tabHeightBig : tabHeightSmall,
            isCurrent ? COLOR_WHITE : (isAvailable ? COLOR_LIGHT_GRAY : COLOR_DARK_GRAY));
    }
}

static s16 Gfx_Scroll(s16 current, s16 scrollDelta, u16 itemCount) {
    s16 maxScroll = itemCount > MAX_ENTRY_LINES ? itemCount - MAX_ENTRY_LINES : 0;
    current += scrollDelta;
    if (current < 0) { current = 0; }
    else if (current > maxScroll) { current = maxScroll; }
    return current;
}

static void Gfx_ShowMenu(void) {
    pressed = 0;

    Draw_ClearFramebuffer();
    if (gSettingsContext.playOption == PLAY_ON_CONSOLE) { Draw_FlushFramebuffer(); }

    do {
        // End the loop if the system has gone to sleep, so the game can properly respond
        if (isAsleep) {
            break;
        }

        handledInput = false;
        // Controls for spoiler log and all-items pages come first, as the user may have chosen
        // one of the directional buttons as their menu open/close button and we need to use them
        if (curMenuIdx == PAGE_DUNGEONITEMS) {
            if (pressed & BUTTON_A) {
                showingLegend = !showingLegend;
                handledInput = true;
            }
        } else if (curMenuIdx == PAGE_SPHERES && gSpoilerData.SphereCount > 0) {
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
        } else if (curMenuIdx == PAGE_ITEMTRACKER_ALL && gSpoilerData.ItemLocationsCount > 0) {
            // All Items list
            if (pressed & BUTTON_A) {
                showingLegend = !showingLegend;
                handledInput = true;
            } else if (!showingLegend) {
                u16 itemCount = gSpoilerData.ItemLocationsCount;
                if (pressed & BUTTON_LEFT) {
                    allItemsScroll = Gfx_Scroll(allItemsScroll, -MAX_ENTRY_LINES * 10, itemCount);
                    handledInput = true;
                } else if (pressed & BUTTON_RIGHT) {
                    allItemsScroll = Gfx_Scroll(allItemsScroll, MAX_ENTRY_LINES * 10, itemCount);
                    handledInput = true;
                } else if (pressed & BUTTON_UP) {
                    allItemsScroll = Gfx_Scroll(allItemsScroll, -MAX_ENTRY_LINES, itemCount);
                    handledInput = true;
                } else if (pressed & BUTTON_DOWN) {
                    allItemsScroll = Gfx_Scroll(allItemsScroll, MAX_ENTRY_LINES, itemCount);
                    handledInput = true;
                }
            }
        } else if (curMenuIdx == PAGE_ITEMTRACKER_GROUPS && gSpoilerData.ItemLocationsCount > 0) {
            // Grouped Items list
            u16 itemCount = gSpoilerData.GroupItemCounts[currentItemGroup];
            if (pressed & BUTTON_LEFT) {
                groupItemsScroll = Gfx_Scroll(groupItemsScroll, -MAX_ENTRY_LINES, itemCount);
                handledInput = true;
            } else if (pressed & BUTTON_RIGHT) {
                groupItemsScroll = Gfx_Scroll(groupItemsScroll, MAX_ENTRY_LINES, itemCount);
                handledInput = true;
            } else if (pressed & BUTTON_UP) {
                groupItemsScroll = Gfx_Scroll(groupItemsScroll, -1, itemCount);
                handledInput = true;
            } else if (pressed & BUTTON_DOWN) {
                groupItemsScroll = Gfx_Scroll(groupItemsScroll, 1, itemCount);
                handledInput = true;
            } else if (pressed & BUTTON_A) {
                NextItemGroup();
                handledInput = true;
            } else if (pressed & BUTTON_Y) {
                PrevItemGroup();
                handledInput = true;
            }
        } else if (curMenuIdx == PAGE_ENTRANCETRACKER_ALL && gEntranceTrackingData.EntranceCount > 0) {
            // Entrances list
            if (pressed & BUTTON_A) {
                showingLegend = !showingLegend;
                handledInput = true;
            } else if (!showingLegend) {
                u16 entranceCount = gEntranceTrackingData.EntranceCount;
                if (pressed & BUTTON_DOWN) {
                    allEntranceScroll = Gfx_Scroll(allEntranceScroll, MAX_ENTRY_LINES, entranceCount);
                    handledInput = true;
                } else if (pressed & BUTTON_UP) {
                    allEntranceScroll = Gfx_Scroll(allEntranceScroll, -MAX_ENTRY_LINES, entranceCount);
                    handledInput = true;
                } else if (pressed & BUTTON_RIGHT) {
                    allEntranceScroll = Gfx_Scroll(allEntranceScroll, MAX_ENTRY_LINES * 10, entranceCount);
                    handledInput = true;
                } else if (pressed & BUTTON_LEFT) {
                    allEntranceScroll = Gfx_Scroll(allEntranceScroll, -MAX_ENTRY_LINES * 10, entranceCount);
                    handledInput = true;
                }
            }
        } else if (curMenuIdx == PAGE_ENTRANCETRACKER_GROUPS && gEntranceTrackingData.EntranceCount > 0) {
            // Grouped Entrances list
            u16 entranceCount = gEntranceTrackingData.GroupEntranceCounts[destListToggle][currentEntranceGroup];
            if (pressed & BUTTON_DOWN) {
                groupEntranceScroll = Gfx_Scroll(groupEntranceScroll, 1, entranceCount);
                handledInput = true;
            } else if (pressed & BUTTON_UP) {
                groupEntranceScroll = Gfx_Scroll(groupEntranceScroll, -1, entranceCount);
                handledInput = true;
            } else if (pressed & BUTTON_RIGHT) {
                groupEntranceScroll = Gfx_Scroll(groupEntranceScroll, MAX_ENTRY_LINES, entranceCount);
                handledInput = true;
            } else if (pressed & BUTTON_LEFT) {
                groupEntranceScroll = Gfx_Scroll(groupEntranceScroll, -MAX_ENTRY_LINES, entranceCount);
                handledInput = true;
            } else if (pressed & BUTTON_A) {
                NextEntranceGroup();
                handledInput = true;
            } else if (pressed & BUTTON_Y) {
                PrevEntranceGroup();
                handledInput = true;
            } else if (pressed & BUTTON_X) {
                destListToggle = !destListToggle;
                handledInput = true;
            }
        } else if (curMenuIdx == PAGE_OPTIONS) {
            Gfx_OptionsUpdate();
        }

        if (!handledInput) {
            if (pressed & closingButton) {
                showingLegend = false;
                Draw_ClearBackbuffer();
                Draw_CopyBackBuffer();
                if (gSettingsContext.playOption == PLAY_ON_CONSOLE) { Draw_FlushFramebuffer(); }
                break;
            } else if (pressed & BUTTON_R1) {
                showingLegend = false;
                do {
                    curMenuIdx++;
                    if (curMenuIdx >= ARR_SIZE(menu_draw_funcs)) {
                        curMenuIdx = 0;
                    }
                } while (menu_draw_funcs[curMenuIdx] == NULL);
                handledInput = true;
            } else if (pressed & BUTTON_L1) {
                showingLegend = false;
                do {
                    curMenuIdx--;
                    if (curMenuIdx < 0) {
                        curMenuIdx = (ARR_SIZE(menu_draw_funcs) - 1);
                    }
                } while (menu_draw_funcs[curMenuIdx] == NULL);
                handledInput = true;
            }
        }

        // Keep updating while in the in-game menu
        Multiplayer_Update(0);

        Draw_ClearBackbuffer();

        // Continue counting up play time while in the in-game menu
        Gfx_UpdatePlayTime();

        menu_draw_funcs[curMenuIdx]();
        Gfx_DrawButtonPrompts();
        Gfx_DrawHeader();
        Draw_CopyBackBuffer();
        if (gSettingsContext.playOption == PLAY_ON_CONSOLE) { Draw_FlushFramebuffer(); }

        pressed = Input_WaitWithTimeout(1000, closingButton);

    } while(true);
}

static void Gfx_ShowMultiplayerSyncMenu(void) {
    Draw_ClearFramebuffer();
    if (gSettingsContext.playOption == PLAY_ON_CONSOLE) { Draw_FlushFramebuffer(); }

    do {
        // End the loop if the system has gone to sleep, so the game can properly respond
        if (isAsleep) {
            break;
        }

        Draw_ClearBackbuffer();

        Multiplayer_Update(0);

        u8 offsetY = 1;
        const char* titleString = mp_foundSyncer ? "Syncing..." : "Looking for syncer...";
        Draw_DrawString(SCREEN_BOT_WIDTH / 2 - (strlen(titleString) / 2) * SPACING_X, 16 + SPACING_Y * offsetY++, COLOR_WHITE, titleString);

        if (mp_foundSyncer) {
            offsetY++;
            static const char* syncPacketNames[] = { "Base Sync", "Save Scene Flags 1", "Save Scene Flags 2", "Save Scene Flags 3", "Save Scene Flags 4", "Entrance Data" };
            static const u8 squareSize = 9;
            for (size_t i = 0; i < ARRAY_SIZE(mp_completeSyncs); i++) {
                Draw_DrawRect(10, 16 + SPACING_Y * offsetY, squareSize, squareSize, COLOR_WHITE);
                Draw_DrawRect(11, 17 + SPACING_Y * offsetY, squareSize - 2, squareSize - 2, mp_completeSyncs[i] ? COLOR_GREEN : COLOR_BLACK);
                Draw_DrawString(10 + SPACING_X * 2, 16 + SPACING_Y * offsetY++, COLOR_WHITE, syncPacketNames[i]);
            }
            if (Multiplayer_GetNeededPacketsMask() != 0) {
                Multiplayer_Send_FullSyncRequest(Multiplayer_GetNeededPacketsMask());
            } else {
                // Syncing is done!
                offsetY++;
                const char* msgString = "Done!";
                Draw_DrawString(SCREEN_BOT_WIDTH / 2 - (strlen(msgString) / 2) * SPACING_X, 16 + SPACING_Y * offsetY, COLOR_WHITE, msgString);
                Draw_CopyBackBuffer();
                svcSleepThread(1000 * 1000 * 1000LL);

                Draw_ClearBackbuffer();
                Draw_CopyBackBuffer();
                if (gSettingsContext.playOption == PLAY_ON_CONSOLE) { Draw_FlushFramebuffer(); }
                mp_isSyncing = false;
                mSaveContextInit = true;
                break;
            }
        } else {
            Multiplayer_Send_FullSyncRequest(0); // Send 0 to only ask for ping, to reduce chance of packet loss
            static u8 syncerSearchTimer = 0;
            // Look for a syncer for 5 seconds
            if (syncerSearchTimer >= 5) {
                Draw_ClearBackbuffer();
                const char* msgString = "No syncer found.";
                Draw_DrawString(SCREEN_BOT_WIDTH / 2 - (strlen(msgString) / 2) * SPACING_X, 10 + SPACING_Y * offsetY, COLOR_WHITE, msgString);
                Draw_CopyBackBuffer();
                svcSleepThread(1000 * 1000 * 1000LL);

                Draw_ClearBackbuffer();
                Draw_CopyBackBuffer();
                if (gSettingsContext.playOption == PLAY_ON_CONSOLE) { Draw_FlushFramebuffer(); }
                mp_isSyncing = false;
                break;
            }
            syncerSearchTimer++;
        }

        Draw_CopyBackBuffer();
        if (gSettingsContext.playOption == PLAY_ON_CONSOLE) { Draw_FlushFramebuffer(); }

        svcSleepThread(1000 * 1000 * 1000LL);

    } while (true);
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
        menu_draw_funcs[PAGE_DUNGEONREWARDS] = NULL;
    }
    if (!gSettingsContext.ingameSpoilers) {
        menu_draw_funcs[PAGE_SPHERES] = NULL;
    }
    if (gSpoilerData.ItemLocationsCount == 0) {
        menu_draw_funcs[PAGE_ITEMTRACKER_ALL] = NULL;
        menu_draw_funcs[PAGE_ITEMTRACKER_GROUPS] = NULL;
    }
    InitEntranceTrackingData();
    if (gEntranceTrackingData.EntranceCount == 0) {
        menu_draw_funcs[PAGE_ENTRANCETRACKER_ALL] = NULL;
        menu_draw_funcs[PAGE_ENTRANCETRACKER_GROUPS] = NULL;
    }

    // Call these to go to the first non-empty group page
    if (gSpoilerData.ItemLocationsCount > 0 && gSpoilerData.GroupItemCounts[currentItemGroup] == 0) {
        NextItemGroup();
    }
    if (gEntranceTrackingData.EntranceCount > 0 && gEntranceTrackingData.GroupEntranceCounts[destListToggle][currentEntranceGroup] == 0) {
        NextEntranceGroup();
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

    if (mp_isSyncing) {
        Gfx_ShowMultiplayerSyncMenu();
    }

    // The update is called here so it works while in different game modes (title screen, file select, boss challenge, credits, MQ unlock)
    static u64 lastTickM = 0;
    static u64 elapsedTicksM = 0;
    elapsedTicksM += svcGetSystemTick() - lastTickM;
    if (elapsedTicksM >= TICKS_PER_SEC) {
        if (!IsInGame()) {
            Multiplayer_Update(0);
        }
        elapsedTicksM = 0;
    }
    lastTickM = svcGetSystemTick();

    Gfx_UpdatePlayTime();

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
