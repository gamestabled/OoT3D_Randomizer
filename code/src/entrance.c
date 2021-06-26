#include "z3D/z3D.h"
#include "entrance.h"
#include "settings.h"
#include "string.h"
#include "item_override.h"

typedef void (*SetNextEntrance_proc)(struct GlobalContext* globalCtx, s16 entranceIndex, u32 sceneLoadFlag, u32 transition);
#define SetNextEntrance_addr 0x3716F0
#define SetNextEntrance ((SetNextEntrance_proc)SetNextEntrance_addr)

static EntranceOverride rEntranceOverrides[256] = {0};

//This variable is used to store whatever new entrance should lead to
//the Requiem of Spirit check. Otherwise, leaving the Spirit Temple
//will take players to the Requiem cutscene even if it is shuffled.
static s16 newRequiemEntrance = 0x01E1;

//These variables store the new entrance indices for dungeons so that
//savewarping and game overs respawn players at the proper entrance.
//By default, these will be their vanilla values.
static s16 newDekuTreeEntrance              = DEKU_TREE_ENTRANCE;
static s16 newDodongosCavernEntrance        = DODONGOS_CAVERN_ENTRANCE;
static s16 newJabuJabusBellyEntrance        = JABU_JABUS_BELLY_ENTRANCE;
static s16 newForestTempleEntrance          = FOREST_TEMPLE_ENTRANCE;
static s16 newFireTempleEntrance            = FIRE_TEMPLE_ENTRANCE;
static s16 newWaterTempleEntrance           = WATER_TEMPLE_ENTRANCE;
static s16 newSpiritTempleEntrance          = SPIRIT_TEMPLE_ENTRANCE;
static s16 newShadowTempleEntrance          = SHADOW_TEMPLE_ENTRANCE;
static s16 newBottomOfTheWellEntrance       = BOTTOM_OF_THE_WELL_ENTRANCE;
static s16 newGerudoTrainingGroundsEntrance = GERUDO_TRAINING_GROUNDS_ENTRANCE;
static s16 newIceCavernEntrance             = ICE_CAVERN_ENTRANCE;

static void Entrance_SetNewDungeonEntrances(s16 originalIndex, s16 replacementIndex) {
    switch (replacementIndex) {
        case DEKU_TREE_ENTRANCE :
            newDekuTreeEntrance = originalIndex;
            break;
        case DODONGOS_CAVERN_ENTRANCE :
            newDodongosCavernEntrance = originalIndex;
            break;
        case JABU_JABUS_BELLY_ENTRANCE :
            newJabuJabusBellyEntrance = originalIndex;
            break;
        case FOREST_TEMPLE_ENTRANCE :
            newForestTempleEntrance = originalIndex;
            break;
        case FIRE_TEMPLE_ENTRANCE :
            newFireTempleEntrance = originalIndex;
            break;
        case WATER_TEMPLE_ENTRANCE :
            newWaterTempleEntrance = originalIndex;
            break;
        case SPIRIT_TEMPLE_ENTRANCE :
            newSpiritTempleEntrance = originalIndex;
            break;
        case SHADOW_TEMPLE_ENTRANCE :
            newShadowTempleEntrance = originalIndex;
            break;
        case BOTTOM_OF_THE_WELL_ENTRANCE :
            newBottomOfTheWellEntrance = originalIndex;
            break;
        case ICE_CAVERN_ENTRANCE :
            newIceCavernEntrance = originalIndex;
            break;
        case GERUDO_TRAINING_GROUNDS_ENTRANCE :
            newGerudoTrainingGroundsEntrance = originalIndex;
            break;
    }
}

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
    // Allow Farore's Wind anywhere if the option is enabled
    // Cannot be used in areas affected by a general item restriction
    if (gSettingsContext.faroresWindAnywhere){
        for (int i = 0; i < 99; i++){
			gRestrictionFlags[i].flags3 &= ~0x30;
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

    // Skip Tower Escape Sequence if given by settings
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
        s16 blueWarpIndex = rEntranceOverrides[i].blueWarp;
        s16 overrideIndex = rEntranceOverrides[i].override;

        if (originalIndex == 0 && overrideIndex == 0) {
            continue;
        }

        //check to see if this is the new requiem entrance
        if (overrideIndex == 0x1E1) {
            newRequiemEntrance = originalIndex;
        }

        //check to see if this is a new dungeon entrance
        Entrance_SetNewDungeonEntrances(originalIndex, overrideIndex);

        //Overwrite the original entrance index data with the data from the override index.
        //Using the copy ensures that we don't overwrite data from an index before it needs
        //to be copied somewhere else.
        for (s16 j = 0; j < 4; j++) {
            gEntranceTable[originalIndex+j].scene = copyOfEntranceTable[overrideIndex+j].scene;
            gEntranceTable[originalIndex+j].spawn = copyOfEntranceTable[overrideIndex+j].spawn;
            gEntranceTable[originalIndex+j].field = copyOfEntranceTable[overrideIndex+j].field;

            //If there's a blue warp entrance, overwrite that one as well
            if (blueWarpIndex != 0) {
              gEntranceTable[blueWarpIndex+j].scene = copyOfEntranceTable[overrideIndex+j].scene;
              gEntranceTable[blueWarpIndex+j].spawn = copyOfEntranceTable[overrideIndex+j].spawn;
              gEntranceTable[blueWarpIndex+j].field = copyOfEntranceTable[overrideIndex+j].field;
              //delete title cards coming from blue warps so that delayed overrides don't have to wait for them
              gEntranceTable[blueWarpIndex+j].field &= ~0x4000;
            }
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

s16 Entrance_GetRequiemEntrance(void) {
    return newRequiemEntrance;
}

//Properly respawn the player after a game over, accounding for dungeon entrance
//randomizer. It's easier to rewrite this entirely compared to performing an ASM
//dance for just the boss rooms. Entrance Indexes can be found here:
//https://wiki.cloudmodding.com/oot/Entrance_Table_(Data)
void Entrance_SetGameOverEntrance(void) {

    //Set the current entrance depending on which entrance the player last came through
    switch (gSaveContext.entranceIndex) {
        case 0x040F : //Deku Tree Boss Room
            gSaveContext.entranceIndex = newDekuTreeEntrance;
            return;
        case 0x040B : //Dodongos Cavern Boss Room
            gSaveContext.entranceIndex = newDodongosCavernEntrance;
            return;
        case 0x0301 : //Jabu Jabus Belly Boss Room
            gSaveContext.entranceIndex = newJabuJabusBellyEntrance;
            return;
        case 0x000C : //Fores Temple Boss Room
            gSaveContext.entranceIndex = newForestTempleEntrance;
            return;
        case 0x0305 : //Fire Temple Boss Room
            gSaveContext.entranceIndex = newFireTempleEntrance;
            return;
        case 0x0417 : //Water Temple Boss Room
            gSaveContext.entranceIndex = newWaterTempleEntrance;
            return;
        case 0x008D : //Spirit Temple Boss Room
            gSaveContext.entranceIndex = newSpiritTempleEntrance;
            return;
        case 0x0413 : //Shadow Temple Boss Room
            gSaveContext.entranceIndex = newShadowTempleEntrance;
            return;
        case 0x041F : //Ganondorf Boss Room
            gSaveContext.entranceIndex = 0x041B; // Inside Ganon's Castle -> Ganon's Tower Climb
            return;
    }
}

//Properly savewarp the player accounting for dungeon entrance randomizer.
//It's easier to rewrite this entirely compared to performing an ASM
//dance for just the boss rooms. This removes the behavior where savewarping
//as adult Link in Link's House respawns adult Link in Link's House.
//https://wiki.cloudmodding.com/oot/Entrance_Table_(Data)
void Entrance_SetSavewarpEntrance(void) {

    s16 scene = gSaveContext.sceneIndex;

    if (scene == DUNGEON_DEKU_TREE || scene == DUNGEON_DEKU_TREE_BOSS_ROOM) {
        gSaveContext.entranceIndex = newDekuTreeEntrance;
    } else if (scene == DUNGEON_DODONGOS_CAVERN || scene == DUNGEON_DODONGOS_CAVERN_BOSS_ROOM) {
        gSaveContext.entranceIndex = newDodongosCavernEntrance;
    } else if (scene == DUNGEON_JABUJABUS_BELLY || scene == DUNGEON_JABUJABUS_BELLY_BOSS_ROOM) {
        gSaveContext.entranceIndex = newJabuJabusBellyEntrance;
    } else if (scene == DUNGEON_FOREST_TEMPLE || scene == 0x14) { //Forest Temple Boss Room
        gSaveContext.entranceIndex = newForestTempleEntrance;
    } else if (scene == DUNGEON_FIRE_TEMPLE || scene == 0x15) { //Fire Temple Boss Room
        gSaveContext.entranceIndex = newFireTempleEntrance;
    } else if (scene == DUNGEON_WATER_TEMPLE || scene == 0x16) { //Water Temple Boss Room
        gSaveContext.entranceIndex = newWaterTempleEntrance;
    } else if (scene == DUNGEON_SPIRIT_TEMPLE || scene == 0x17) { //Spirit Temple Boss Room
        gSaveContext.entranceIndex = newSpiritTempleEntrance;
    } else if (scene == DUNGEON_SHADOW_TEMPLE || scene == 0x18) { //Shadow Temple Boss Room
        gSaveContext.entranceIndex = newShadowTempleEntrance;
    } else if (scene == DUNGEON_BOTTOM_OF_THE_WELL) {
        gSaveContext.entranceIndex = newBottomOfTheWellEntrance;
    } else if (scene == DUNGEON_GERUDO_TRAINING_GROUNDS) {
        gSaveContext.entranceIndex = newGerudoTrainingGroundsEntrance;
    } else if (scene == DUNGEON_ICE_CAVERN) {
        gSaveContext.entranceIndex = newIceCavernEntrance;
    } else if (scene == DUNGEON_GANONS_CASTLE_FIRST_PART) {
        gSaveContext.entranceIndex = GANONS_CASTLE_ENTRANCE;
    } else if (scene == DUNGEON_GANONS_CASTLE_SECOND_PART || scene == DUNGEON_GANONS_CASTLE_CRUMBLING || scene == DUNGEON_GANONS_CASTLE_FLOOR_BENEATH_BOSS_CHAMBER || scene == 0x4F || scene == 0x1A) {
        gSaveContext.entranceIndex = 0x041B; // Inside Ganon's Castle -> Ganon's Tower Climb
    } else if (scene == DUNGEON_GERUDO_FORTRESS) {
        gSaveContext.entranceIndex = 0x0486; // Gerudo Fortress -> Thieve's Hideout spawn 0
    } else if (gSaveContext.linkAge == AGE_CHILD) {
        gSaveContext.entranceIndex = 0x00BB; // Link's House Child Spawn
    } else {
        gSaveContext.entranceIndex = 0x05F4; // Temple of Time Adult Spawn
    }
}

void EnableFW() {
    // Leave restriction in Tower Collapse Interior, Castle Collapse, Treasure Box Shop, Tower Collapse Exterior,
    // Grottos area, Fishing Pond, Ganon Battle and for states that disable buttons.
    if (!gSettingsContext.faroresWindAnywhere ||
        gGlobalContext->sceneNum == 14 || gGlobalContext->sceneNum == 15 || gGlobalContext->sceneNum == 16 ||
        gGlobalContext->sceneNum == 26 || gGlobalContext->sceneNum == 62 || gGlobalContext->sceneNum == 73 ||
        gGlobalContext->sceneNum == 79 ||
        gSaveContext.unk_1586[4] & 0x1 ||   // Ingo's Minigame state
        PLAYER->stateFlags1 & 0x08A02000 || // Swimming, riding horse, Down A, hanging from a ledge
        PLAYER->stateFlags2 & 0x00040000    // Blank A
        // Shielding, spinning and getting skull tokens still disable buttons automatically
        ) {
        return;
    }

    for (int i = 1; i < 5; i++) {
        if (gSaveContext.equips.buttonItems[i] == 13) {
            gSaveContext.buttonStatus[i] = 0;
        }
    }
}
