#include "dungeon.h"
#include "settings.h"
#include "spoiler_data.h"
#include "common.h"
#include <string.h>

typedef struct {
    u16 spoilerIndex;
    u8 keyAmount;
} KeyData;

static u8 keyFinderInit = 0;
static KeyData keyData[DUNGEON_TREASURE_CHEST_SHOP + 1][10];

// Used to compare key strings and item string of spoiler data.
// The regular strcmp won't be enough since items in shops have a colon and price added after.
static u8 strcmp_key(char* str, const char* keyStr) {
    for (size_t i = 0; i <= strlen(keyStr); i++) {
        if (keyStr[i] == '\0' && (str[i] == '\0' || str[i] == ':')) {
            return 1;
        }
        if (keyStr[i] != str[i]) {
            return 0;
        }
    }
    return 0;
}

static const char* GetKeyName(DungeonId id, u8 keyRing) {
    static const char* noStr = "";

    switch (id) {
        case DUNGEON_FOREST_TEMPLE:
            return keyRing ? keyRingStringForest : smallKeyStringForest;
        case DUNGEON_FIRE_TEMPLE:
            return keyRing ? keyRingStringFire : smallKeyStringFire;
        case DUNGEON_WATER_TEMPLE:
            return keyRing ? keyRingStringWater : smallKeyStringWater;
        case DUNGEON_SPIRIT_TEMPLE:
            return keyRing ? keyRingStringSpirit : smallKeyStringSpirit;
        case DUNGEON_SHADOW_TEMPLE:
            return keyRing ? keyRingStringShadow : smallKeyStringShadow;
        case DUNGEON_BOTTOM_OF_THE_WELL:
            return keyRing ? keyRingStringBotW : smallKeyStringBotW;
        case DUNGEON_GERUDO_TRAINING_GROUNDS:
            return keyRing ? keyRingStringGTG : smallKeyStringGTG;
        case DUNGEON_THIEVES_HIDEOUT:
            return keyRing ? keyRingStringHideout : smallKeyStringHideout;
        case DUNGEON_INSIDE_GANONS_CASTLE:
            return keyRing ? keyRingStringGanon : smallKeyStringGanon;
        case DUNGEON_TREASURE_CHEST_SHOP:
            return smallKeyStringGame;
        default:
            return noStr;
    }
}

u8 Dungeon_KeyAmount(DungeonId id) {
    switch (id) {
        case DUNGEON_FOREST_TEMPLE:
            return gSettingsContext.forestTempleDungeonMode ? FOREST_MQ_KEY_COUNT : FOREST_KEY_COUNT;
        case DUNGEON_FIRE_TEMPLE:
            return gSettingsContext.fireTempleDungeonMode ? FIRE_MQ_KEY_COUNT : FIRE_KEY_COUNT;
        case DUNGEON_WATER_TEMPLE:
            return gSettingsContext.waterTempleDungeonMode ? WATER_MQ_KEY_COUNT : WATER_KEY_COUNT;
        case DUNGEON_SPIRIT_TEMPLE:
            return gSettingsContext.spiritTempleDungeonMode ? SPIRIT_MQ_KEY_COUNT : SPIRIT_KEY_COUNT;
        case DUNGEON_SHADOW_TEMPLE:
            return gSettingsContext.shadowTempleDungeonMode ? SHADOW_MQ_KEY_COUNT : SHADOW_KEY_COUNT;
        case DUNGEON_BOTTOM_OF_THE_WELL:
            return gSettingsContext.bottomOfTheWellDungeonMode ? BOTW_MQ_KEY_COUNT : BOTW_KEY_COUNT;
        case DUNGEON_GERUDO_TRAINING_GROUNDS:
            return gSettingsContext.gerudoTrainingGroundsDungeonMode ? GTG_MQ_KEY_COUNT : GTG_KEY_COUNT;
        case DUNGEON_THIEVES_HIDEOUT:
            if (gSettingsContext.gerudoFortress == GERUDOFORTRESS_NORMAL) {
                return HIDEOUT_KEY_COUNT;
            } else if (gSettingsContext.gerudoFortress == GERUDOFORTRESS_FAST) {
                return 1;
            } else if (gSettingsContext.gerudoFortress == GERUDOFORTRESS_OPEN) {
                return 0;
            }
        case DUNGEON_INSIDE_GANONS_CASTLE:
            return gSettingsContext.ganonsCastleDungeonMode ? GANON_MQ_KEY_COUNT : GANON_KEY_COUNT;
        case DUNGEON_TREASURE_CHEST_SHOP:
            return 6;
        default:
            return 0;
    }
}

// Stores the indexes of the gSpoilerData where small keys and key rings are for faster lookup.
static void InitKeyFinder(void) {
    if (keyFinderInit) {
        return;
    }
    keyFinderInit = 1;

    for (size_t i = 0; i < ARRAY_SIZE(keyData); i++) {
        for (size_t j = 0; j < ARRAY_SIZE(keyData[0]); j++) {
            keyData[i][j].spoilerIndex = -1;
        }
    }

    u8 keyDataIndex[DUNGEON_TREASURE_CHEST_SHOP + 1] = { 0 };

    for (size_t item = 0; item < gSpoilerData.ItemLocationsCount; item++) {
        for (DungeonId dungeonId = DUNGEON_FOREST_TEMPLE; dungeonId <= DUNGEON_TREASURE_CHEST_SHOP; dungeonId++) {
            if (dungeonId == DUNGEON_ICE_CAVERN || dungeonId == DUNGEON_GANONS_TOWER ||
                dungeonId == DUNGEON_GANONS_TOWER_COLLAPSING_INTERIOR ||
                dungeonId == DUNGEON_GANONS_CASTLE_COLLAPSING) {
                continue;
            }
            if (strcmp_key(SpoilerData_GetItemNameString(item), GetKeyName(dungeonId, 0))) {
                keyData[dungeonId][keyDataIndex[dungeonId]].spoilerIndex = item;
                keyData[dungeonId][keyDataIndex[dungeonId]].keyAmount    = 1;
                if (dungeonId == DUNGEON_TREASURE_CHEST_SHOP &&
                    gSettingsContext.shuffleChestMinigame == SHUFFLECHESTMINIGAME_PACK) {
                    keyData[dungeonId][keyDataIndex[dungeonId]].keyAmount = Dungeon_KeyAmount(dungeonId);
                }
                keyDataIndex[dungeonId]++;
                break;
            } else if (strcmp_key(SpoilerData_GetItemNameString(item), GetKeyName(dungeonId, 1))) {
                keyData[dungeonId][keyDataIndex[dungeonId]].spoilerIndex = item;
                keyData[dungeonId][keyDataIndex[dungeonId]].keyAmount    = Dungeon_KeyAmount(dungeonId);
                keyDataIndex[dungeonId]++;
                break;
            }
        }
    }
}

u8 Dungeon_FoundSmallKeys(DungeonId id) {
    if (!keyFinderInit) {
        InitKeyFinder();
    }

    u8 amount = 0;
    for (size_t i = 0; i < ARRAY_SIZE(keyData[id]); i++) {
        if (keyData[id][i].spoilerIndex == -1) {
            break;
        }
        if (SpoilerData_GetIsItemLocationCollected(keyData[id][i].spoilerIndex)) {
            amount += keyData[id][i].keyAmount;
        }
    }
    return amount;
}

u8 Dungeon_CheckDekuTreeClear() {
    if (EventCheck(0x09) == 0) {
        return 0;
    } else {
        return 1;
    }
}

u8 Dungeon_GetCurrentDungeonMode() {
    switch (gGlobalContext->sceneNum) {
        case DUNGEON_DEKU_TREE:
            return gSettingsContext.dekuTreeDungeonMode;
        case DUNGEON_DODONGOS_CAVERN:
            return gSettingsContext.dodongosCavernDungeonMode;
        case DUNGEON_JABUJABUS_BELLY:
            return gSettingsContext.jabuJabusBellyDungeonMode;
        case DUNGEON_FOREST_TEMPLE:
            return gSettingsContext.forestTempleDungeonMode;
        case DUNGEON_FIRE_TEMPLE:
            return gSettingsContext.fireTempleDungeonMode;
        case DUNGEON_WATER_TEMPLE:
            return gSettingsContext.waterTempleDungeonMode;
        case DUNGEON_SPIRIT_TEMPLE:
            return gSettingsContext.spiritTempleDungeonMode;
        case DUNGEON_SHADOW_TEMPLE:
            return gSettingsContext.shadowTempleDungeonMode;
        case DUNGEON_BOTTOM_OF_THE_WELL:
            return gSettingsContext.bottomOfTheWellDungeonMode;
        case DUNGEON_ICE_CAVERN:
            return gSettingsContext.iceCavernDungeonMode;
        case DUNGEON_GERUDO_TRAINING_GROUNDS:
            return gSettingsContext.gerudoTrainingGroundsDungeonMode;
        case DUNGEON_INSIDE_GANONS_CASTLE:
            return gSettingsContext.ganonsCastleDungeonMode;
    }

    return gSaveContext.masterQuestFlag;
}
