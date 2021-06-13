#include "z3D/z3D.h"
#include "entrance.h"
#include "settings.h"
#include "string.h"
#include "item_override.h"

typedef void (*SetNextEntrance_proc)(struct GlobalContext* globalCtx, s16 entranceIndex, u32 sceneLoadFlag, u32 transition);
#define SetNextEntrance_addr 0x3716F0
#define SetNextEntrance ((SetNextEntrance_proc)SetNextEntrance_addr)

static EntranceOverride rEntranceOverrides[128] = {0};

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
    memcpy(&gSceneTable[9],  gSettingsContext.iceCavernDungeonMode             == DUNGEONMODE_MQ ? &gMQDungeonSceneTable[9]  : &gDungeonSceneTable[9],  sizeof(Scene));
    memcpy(&gSceneTable[11], gSettingsContext.gerudoTrainingGroundsDungeonMode == DUNGEONMODE_MQ ? &gMQDungeonSceneTable[11] : &gDungeonSceneTable[11], sizeof(Scene));
    memcpy(&gSceneTable[13], gSettingsContext.ganonsCastleDungeonMode          == DUNGEONMODE_MQ ? &gMQDungeonSceneTable[13] : &gDungeonSceneTable[13], sizeof(Scene));

    gRestrictionFlags[72].flags2 = 0; // Allows warp songs in GTG
    //gRestrictionFlags[93].flags2 = 0; // Allows warp songs in Windmill / Dampe's grave
    gRestrictionFlags[94].flags2 = 0; // Allows warp songs in Ganon's Castle

    gRestrictionFlags[72].flags3 = 0; // Allows farore's wind in GTG
    gRestrictionFlags[94].flags3 = 0; // Allows farore's wind in Ganon's Castle
}

void Entrance_Init(void) {
    s32 index;

    // Skip Child Stealth if given by settings
    if (gSettingsContext.skipChildStealth == SKIP) {
        gEntranceTable[0x07A].scene = 0x4A;
        gEntranceTable[0x07A].spawn = 0x00;
        gEntranceTable[0x07A].field = 0x0183;
    }

    //Skip Tower Escape Sequence if given by settings
    if (gSettingsContext.skipTowerEscape == SKIP) {
        gEntranceTable[0x43F].scene = 0x4F;
        gEntranceTable[0x43F].spawn = 0x01;
        gEntranceTable[0x43F].field = 0x4183;
    }

    const s32 deleteTitleCards[] = {
        0x1ED, // Desert Colossus from Requiem
        0x221, // Zora's Fountain from Inside Jabu Jabu's Belly
        0x2CA, // Temple of Time from Pulling/Placing Master Sword
        0x457, // Kokiri Forest from Deku Tree Death Cutscene
        0x47A, // Death Mountain Trail from Goron Ruby Cutscene
        0x513, // Kakariko Village from Nocturne
        0x564, // Death Mountain Crater from Fire Temple Blue Warp
        0x580, // Graveyard from Shadow Temple Blue Warp
        0x58C, // Temple of Time from LACS
        0x594, // Hyrule Field from Impa's first escort
        0x5F4, // Temple of Time from Prelude/Savewarp
        0x600, // Sacred Forest Meadow from Minuet
        0x608, // Sacred Forest Meadow from Forest Temple Blue Warp
        0x60C, // Lake Hylia from Water Temple Blue Warp
        0x610, // Desert Colossus from Spirit Temple Blue Warp
    };

    //Delete title cards from the following entrance indexes in the above table
    for (size_t i = 0; i < sizeof(deleteTitleCards) / sizeof(s32); i++) {
        index = deleteTitleCards[i];
        for (size_t j = 0; j < 4; j++) {
            gEntranceTable[index + j].field &= ~0x4000;
        }
    }

    // Delete the title card and add a fade in for Hyrule Field from Ocarina of Time cutscene
    for (index = 0x50F; index < 0x513; ++index) {
        gEntranceTable[index].field = 0x010B;
    }

    //copy the entrance table to use for overwriting the original one
    EntranceInfo copyOfEntranceTable[0x613] = {0};
    memcpy(copyOfEntranceTable, gEntranceTable, sizeof(EntranceInfo) * 0x613);

    //rewrite the entrance table for entrance randomizer
    size_t numberOfEntranceOverrides = sizeof(rEntranceOverrides) / sizeof(EntranceOverride);
    for (size_t i = 0; i < numberOfEntranceOverrides; i++) {

        s16 originalIndex = rEntranceOverrides[i].index;
        s16 overrideIndex = rEntranceOverrides[i].override;

        if (originalIndex == overrideIndex) {
            continue;
        }

        for (s16 j = 0; j < 4; j++) {
            gEntranceTable[originalIndex+j].scene = copyOfEntranceTable[overrideIndex+j].scene;
            gEntranceTable[originalIndex+j].spawn = copyOfEntranceTable[overrideIndex+j].spawn;
            gEntranceTable[originalIndex+j].field = copyOfEntranceTable[overrideIndex+j].field;
        }
    }
}

void Entrance_DeathInGanonBattle(void) {
    if ((gGlobalContext->sceneNum == 0x004F) && (gSettingsContext.skipTowerEscape == SKIP)) {
        SetNextEntrance(gGlobalContext, 0x517, 0x14, 2);
    } else {
        SetNextEntrance(gGlobalContext, 0x43F, 0x14, 2);
    }
}
