#include "settings.h"
#include "z3D/z3D.h"

u8 Dungeon_CheckDekuTreeClear() {
    if (EventCheck(0x09) == 0) {
        return 0;
    } else {
        return 1;
    }
}

u8 Dungeon_GetCurrentDungeonMode() {
    switch (gGlobalContext->sceneNum) {
        case DUNGEON_DEKU_TREE  :
            return gSettingsContext.dekuTreeDungeonMode;
        case DUNGEON_DODONGOS_CAVERN  :
            return gSettingsContext.dodongosCavernDungeonMode;
        case DUNGEON_JABUJABUS_BELLY  :
            return gSettingsContext.jabuJabusBellyDungeonMode;
        case DUNGEON_FOREST_TEMPLE  :
            return gSettingsContext.forestTempleDungeonMode;
        case DUNGEON_FIRE_TEMPLE  :
            return gSettingsContext.fireTempleDungeonMode;
        case DUNGEON_WATER_TEMPLE  :
            return gSettingsContext.waterTempleDungeonMode;
        case DUNGEON_SPIRIT_TEMPLE  :
            return gSettingsContext.spiritTempleDungeonMode;
        case DUNGEON_SHADOW_TEMPLE  :
            return gSettingsContext.shadowTempleDungeonMode;
        case DUNGEON_BOTTOM_OF_THE_WELL  :
            return gSettingsContext.bottomOfTheWellDungeonMode;
        case DUNGEON_ICE_CAVERN  :
            return gSettingsContext.iceCavernDungeonMode;
        case DUNGEON_GERUDO_TRAINING_GROUNDS  :
            return gSettingsContext.gerudoTrainingGroundsDungeonMode;
        case DUNGEON_GANONS_CASTLE_FIRST_PART  :
            return gSettingsContext.ganonsCastleDungeonMode;
    }

    return gSaveContext.masterQuestFlag;
}
