#include "z3D/z3D.h"
#include "entrance.h"
#include "settings.h"
#include "string.h"

void Scene_Init(void) {
    memcpy(&gSceneTable[0],  gSettingsContext.dekuTreeDungeonMode              == DUNGEONMODE_MQ ? &gMQDungeonSceneTable[0]  : &gDungeonSceneTable[0],  sizeof(Scene));
    memcpy(&gSceneTable[1],  gSettingsContext.dodongosCavernDungeonMode        == DUNGEONMODE_MQ ? &gMQDungeonSceneTable[1]  : &gDungeonSceneTable[1],  sizeof(Scene));
    memcpy(&gSceneTable[2],  gSettingsContext.jabuJabusBellyDungeonMode        == DUNGEONMODE_MQ ? &gMQDungeonSceneTable[2]  : &gDungeonSceneTable[2],  sizeof(Scene));
    memcpy(&gSceneTable[3],  gSettingsContext.forestTempleDungeonMode          == DUNGEONMODE_MQ ? &gMQDungeonSceneTable[3]  : &gDungeonSceneTable[3],  sizeof(Scene));
    memcpy(&gSceneTable[4],  gSettingsContext.fireTempleDungeonMode            == DUNGEONMODE_MQ ? &gMQDungeonSceneTable[4]  : &gDungeonSceneTable[4],  sizeof(Scene));
    memcpy(&gSceneTable[5],  gSettingsContext.waterTempleDungeonMode           == DUNGEONMODE_MQ ? &gMQDungeonSceneTable[5]  : &gDungeonSceneTable[5],  sizeof(Scene));
    memcpy(&gSceneTable[6],  gSettingsContext.spiritTempleDungeonMode          == DUNGEONMODE_MQ ? &gMQDungeonSceneTable[6]  : &gDungeonSceneTable[6],  sizeof(Scene));
    memcpy(&gSceneTable[7],  gSettingsContext.shadowTempleDungeonMode          == DUNGEONMODE_MQ ? &gMQDungeonSceneTable[7]  : &gDungeonSceneTable[7],  sizeof(Scene));
    memcpy(&gSceneTable[8],  gSettingsContext.bottomOfTheWellDungeonMode       == DUNGEONMODE_MQ ? &gMQDungeonSceneTable[8]  : &gDungeonSceneTable[8],  sizeof(Scene));
    memcpy(&gSceneTable[11], gSettingsContext.gerudoTrainingGroundsDungeonMode == DUNGEONMODE_MQ ? &gMQDungeonSceneTable[11] : &gDungeonSceneTable[11], sizeof(Scene));
    memcpy(&gSceneTable[13], gSettingsContext.ganonsCastleDungeonMode          == DUNGEONMODE_MQ ? &gMQDungeonSceneTable[13] : &gDungeonSceneTable[13], sizeof(Scene));
}

void Entrance_Init(void) {
    s32 index;

    // Skip Child Stealth if given by settings
    if (gSettingsContext.skipChildStealth == SKIP) {
        gEntranceTable[0x07A].scene = 0x4A;
        gEntranceTable[0x07A].spawn = 0x01;
        gEntranceTable[0x07A].field = 0x0183;
    }

    // Delete the title card for Desert Colossus from Requiem
    for (index = 0x1ED; index < 0x1F1; ++index) {
        gEntranceTable[index].field = 0x0102;
    }

    // Delete the title card for Kakariko Village from Nocturne
    for (index = 0x513; index < 0x517; ++index) {
        gEntranceTable[index].field = 0x0102;
    }

    // Delete the title card for Temple of Time from LACS
    for (index = 0x58C; index < 0x590; ++index) {
        gEntranceTable[index].field = 0x0102;
    }

    // Delete the title card for Hyrule Field from Impa's first escort
    for (index = 0x594; index < 0x598; ++index) {
        gEntranceTable[index].field = 0x0102;
    }
}
