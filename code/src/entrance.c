#include "z3D/z3D.h"
#include "entrance.h"
#include "settings.h"
#include "string.h"
#include "item_override.h"

typedef void (*SetNextEntrance_proc)(struct GlobalContext* globalCtx, s16 entranceIndex, u32 sceneLoadFlag, u32 transition);
#define SetNextEntrance_addr 0x3716F0
#define SetNextEntrance ((SetNextEntrance_proc)SetNextEntrance_addr)

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
    
    //Allow Farore's Wind anywhere if given by settings
    if (gSettingsContext.faroresWindAnywhere){
        for (int i = 0; i < 99; i++){
			gRestrictionFlags[i].flags3 &= ~0x30;
			gRestrictionFlags[i].flags3 &= ~0x03;
		}
    }
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

    // Delete the title card for Kokiri Forest from Deku Tree Death Cutscene
    for (index = 0x457; index < 0x45B; ++index) {
        gEntranceTable[index].field = 0x0202;
    }

    // Delete the title card for Death Mountain Trail from Goron Ruby Cutscene
    for (index = 0x47A; index < 0x47E; ++index) {
        gEntranceTable[index].field = 0x0202;
    }

    // Delete the title card for Zora's Fountain from Inside Jabu Jabu's Belly
    for (index = 0x221; index < 0x225; ++index) {
        gEntranceTable[index].field = 0x0102;
    }

    // Delete the title card for Sacred Forest Meadow from Minuet
    for (index = 0x600; index < 0x604; ++index) {
        gEntranceTable[index].field &= ~0x4000;
    }

    // Delete the title card for Temple of Time from Prelude/Savewarp
    for (index = 0x5F4; index < 0x5F8; ++index) {
        gEntranceTable[index].field &= ~0x4000;
    }

    // Delete the title card for Sacred Forest Meadow from Forest Temple Blue Warp
    for (index = 0x608; index < 0x60C; ++index) {
        gEntranceTable[index].field = 0x0102;
    }

    // Delete the title card for Death Mountain Crater from Fire Temple Blue Warp
    for (index = 0x564; index < 0x568; ++index) {
        gEntranceTable[index].field = 0x0102;
    }

    // Delete the title card for Lake Hylia from Water Temple Blue Warp
    for (index = 0x60C; index < 0x610; ++index) {
        gEntranceTable[index].field = 0x0102;
    }

    // Delete the title card for Desert Colossus from Spirit Temple Blue Warp
    for (index = 0x610; index < 0x614; ++index) {
        gEntranceTable[index].field = 0x0102;
    }

    // Delete the title card for Graveyard from Shadow Temple Blue Warp
    for (index = 0x580; index < 0x584; ++index) {
        gEntranceTable[index].field = 0x0102;
    }

    // Delete the title card for Desert Colossus from Requiem
    for (index = 0x1ED; index < 0x1F1; ++index) {
        gEntranceTable[index].field = 0x0102;
    }

    // Delete the title card for Temple of Time from Pulling/Placing Master Sword
    for (index = 0x2CA; index < 0x2CE; ++index) {
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

    // Delete the title card and add a fade in for Hyrule Field from Ocarina of Time cutscene
    for (index = 0x50F; index < 0x513; ++index) {
        gEntranceTable[index].field = 0x010B;
    }
}

void Entrance_DeathInGanonBattle(void) {
    if ((gGlobalContext->sceneNum == 0x004F) && (gSettingsContext.skipTowerEscape == SKIP)) {
        SetNextEntrance(gGlobalContext, 0x517, 0x14, 2);
    } else {
        SetNextEntrance(gGlobalContext, 0x43F, 0x14, 2);
    }
}
