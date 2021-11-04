#include "../include/z3D/z3D.h"
#include "entrance.h"
#include "settings.h"
#include "string.h"
#include "item_override.h"
#include "savefile.h"
#include "common.h"

typedef void (*SetNextEntrance_proc)(struct GlobalContext* globalCtx, s16 entranceIndex, u32 sceneLoadFlag, u32 transition);
#define SetNextEntrance_addr 0x3716F0
#define SetNextEntrance ((SetNextEntrance_proc)SetNextEntrance_addr)

typedef void (*SetEventChkInf_proc)(u32 flag);
#define SetEventChkInf_addr 0x34CBF8
#define SetEventChkInf ((SetEventChkInf_proc)SetEventChkInf_addr)

#define dynamicExitList_addr 0x53C094
#define dynamicExitList ((s16*)dynamicExitList_addr)

EntranceOverride rEntranceOverrides[ENTRANCE_OVERRIDES_MAX_COUNT] = {0};
EntranceTrackingData gEntranceTrackingData = {0};

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
}

static void Entrance_SeparateOGCFairyFountainExit() {
    //Overwrite unused entrance 0x03E8 with values from 0x0340 to use it as the
    //exit from OGC Great Fairy Fountain -> Castle Grounds
    for (size_t i = 0; i < 4; ++i) {
        gEntranceTable[0x3E8 + i] = gEntranceTable[0x340 + i];
    }

    //Overwrite the dynamic exit for the OGC Fairy Fountain to be 0x3E8 instead
    //of 0x340 (0x340 will stay as the exit for the HC Fairy Fountain -> Castle Grounds)
    dynamicExitList[2] = 0x03E8;
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

    // Delete the title card and add a fade in for Hyrule Field from Ocarina of Time cutscene
    for (index = 0x50F; index < 0x513; ++index) {
        gEntranceTable[index].field = 0x010B;
    }

    Entrance_SeparateOGCFairyFountainExit();

    //copy the entrance table to use for overwriting the original one
    EntranceInfo copyOfEntranceTable[0x613] = {0};
    memcpy(copyOfEntranceTable, gEntranceTable, sizeof(EntranceInfo) * 0x613);

    //rewrite the entrance table for entrance randomizer
    for (size_t i = 0; i < ENTRANCE_OVERRIDES_MAX_COUNT; i++) {

        s16 originalIndex = rEntranceOverrides[i].index;
        s16 blueWarpIndex = rEntranceOverrides[i].blueWarp;
        s16 overrideIndex = rEntranceOverrides[i].override;

        if (originalIndex == 0 && overrideIndex == 0) {
            continue;
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
            }
        }

        //Override both land and water entrances for Hyrule Field -> ZR Front and vice versa
        if (originalIndex == 0x00EA) { //Hyrule Field -> ZR Front land entrance
            for (s16 j = 0; j < 4; j++) {
                gEntranceTable[0x01D9+j].scene = copyOfEntranceTable[overrideIndex+j].scene;
                gEntranceTable[0x01D9+j].spawn = copyOfEntranceTable[overrideIndex+j].spawn;
                gEntranceTable[0x01D9+j].field = copyOfEntranceTable[overrideIndex+j].field;
            }
        } else if (originalIndex == 0x0181) { //ZR Front -> Hyrule Field land entrance
            for (s16 j = 0; j < 4; j++) {
                gEntranceTable[0x0311+j].scene = copyOfEntranceTable[overrideIndex+j].scene;
                gEntranceTable[0x0311+j].spawn = copyOfEntranceTable[overrideIndex+j].spawn;
                gEntranceTable[0x0311+j].field = copyOfEntranceTable[overrideIndex+j].field;
            }
        }
    }

    //Set the exit transition of GC Woods Warp -> Lost Woods to a lost woods transition.
    //This works as an easy fix for the Overworld ER bug that continues to play the lost
    //woods music into the next area, even if isn't the lost woods. A "proper" fix would
    //probably be to stop playing the music on any transition though
    if (gSettingsContext.shuffleOverworldEntrances == ON) {
        for (s16 i = 0x4D6; i < 0x4DA; i++) {
            gEntranceTable[i].field &= 0xFF00;
            gEntranceTable[i].field |= 0x002C;
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

u32 Entrance_SceneAndSpawnAre(u8 scene, u8 spawn) {
    EntranceInfo currentEntrance = gEntranceTable[gSaveContext.entranceIndex];
    return currentEntrance.scene == scene && currentEntrance.spawn == spawn;
}

u32 Entrance_IsLostWoodsBridge(void) {
    //  Kokiri Forest -> LW Bridge, index 05E0   Hyrule Field -> LW Bridge, index 04DE
    if (Entrance_SceneAndSpawnAre(0x5B, 0x09) || Entrance_SceneAndSpawnAre(0x5B, 0x08)) {
      return 1;
    } else {
      return 0;
    }
}

void Entrance_EnteredLocation(void) {
    if (!IsInGame()) {
        return;
    }
    SaveFile_SetSceneDiscovered(gGlobalContext->sceneNum);
    SaveFile_SetEntranceDiscovered(gSaveContext.entranceIndex);
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

u8 EntranceCutscene_ShouldPlay(u8 flag) {
    if (gSaveContext.gameMode != 0 || flag == 0x18 || flag == 0xAD || (flag >= 0xBB && flag <= 0xBF)) {
        if (flag == 0xC0) {
            gSaveContext.eventChkInf[0x3] &= ~0x0800; // clear "began Nabooru battle"
        }
        return 1; // cutscene will play normally in DHWW, or always if it's freeing Epona or clearing a Trial
    }
    SetEventChkInf(flag);
    return 0; //cutscene will not play
}

EntranceName entranceNames[] = {
    { 0x0000, "KF" /* > Deku Tree */ , ENTRANCE_GROUP_KOKIRI_FOREST },
    { 0x0209, "Deku Tree" /* > KF */ , ENTRANCE_GROUP_KOKIRI_FOREST },
    { 0x0004, "DMT" /* > Dodongo's Cavern */ , ENTRANCE_GROUP_DEATH_MOUNTAIN_TRAIL },
    { 0x0242, "Dodongo's Cavern" /* > DMT */ , ENTRANCE_GROUP_DEATH_MOUNTAIN_TRAIL },
    { 0x0028, "ZF" /* > Jabu Jabu's Belly */ , ENTRANCE_GROUP_ZORAS_DOMAIN },
    { 0x0221, "Jabu Jabu's Belly" /* > ZF */ , ENTRANCE_GROUP_ZORAS_DOMAIN },
    { 0x0169, "SFM" /* > Forest Temple */ , ENTRANCE_GROUP_LOST_WOODS },
    { 0x0215, "Forest Temple" /* > SFM */ , ENTRANCE_GROUP_LOST_WOODS },
    { 0x0165, "DMC" /* > Fire Temple */ , ENTRANCE_GROUP_DEATH_MOUNTAIN_CRATER },
    { 0x024A, "Fire Temple" /* > DMC */ , ENTRANCE_GROUP_DEATH_MOUNTAIN_CRATER },
    { 0x0010, "LH" /* > Water Temple */ , ENTRANCE_GROUP_LAKE_HYLIA },
    { 0x021D, "Water Temple" /* > LH */ , ENTRANCE_GROUP_LAKE_HYLIA },
    { 0x0082, "Desert Colossus" /* > Spirit Temple */ , ENTRANCE_GROUP_HAUNTED_WASTELAND },
    { 0x01E1, "Spirit Temple" /* > Desert Colossus */ , ENTRANCE_GROUP_HAUNTED_WASTELAND },
    { 0x0037, "Graveyard" /* > Shadow Temple */ , ENTRANCE_GROUP_GRAVEYARD },
    { 0x0205, "Shadow Temple" /* > Graveyard */ , ENTRANCE_GROUP_GRAVEYARD },
    { 0x0098, "Kakariko" /* > Bottom of the Well */ , ENTRANCE_GROUP_KAKARIKO },
    { 0x02A6, "Bottom of the Well" /* > Kakariko */ , ENTRANCE_GROUP_KAKARIKO },
    { 0x0088, "ZF" /* > Ice Cavern */ , ENTRANCE_GROUP_ZORAS_DOMAIN },
    { 0x03D4, "Ice Cavern" /* > ZF */ , ENTRANCE_GROUP_ZORAS_DOMAIN },
    { 0x0008, "GF" /* > Gerudo Training Grounds */ , ENTRANCE_GROUP_GERUDO_VALLEY },
    { 0x03A8, "Gerudo Training Grounds" /* > GF */ , ENTRANCE_GROUP_GERUDO_VALLEY },
    { 0x0433, "KF" /* > Mido's House */ , ENTRANCE_GROUP_KOKIRI_FOREST },
    { 0x0443, "Mido's House" /* > KF */ , ENTRANCE_GROUP_KOKIRI_FOREST },
    { 0x0437, "KF" /* > Saria's House */ , ENTRANCE_GROUP_KOKIRI_FOREST },
    { 0x0447, "Saria's House" /* > KF */ , ENTRANCE_GROUP_KOKIRI_FOREST },
    { 0x009C, "KF" /* > House of Twins */ , ENTRANCE_GROUP_KOKIRI_FOREST },
    { 0x033C, "House of Twins" /* > KF */ , ENTRANCE_GROUP_KOKIRI_FOREST },
    { 0x00C9, "KF" /* > Know-It-All House */ , ENTRANCE_GROUP_KOKIRI_FOREST },
    { 0x026A, "Know-It-All House" /* > KF */ , ENTRANCE_GROUP_KOKIRI_FOREST },
    { 0x00C1, "KF" /* > KF Shop */ , ENTRANCE_GROUP_KOKIRI_FOREST },
    { 0x0266, "KF Shop" /* > KF */ , ENTRANCE_GROUP_KOKIRI_FOREST },
    { 0x0043, "Lake Hylia" /* > LH Lab */ , ENTRANCE_GROUP_LAKE_HYLIA },
    { 0x03CC, "LH Lab" /* > Lake Hylia */ , ENTRANCE_GROUP_LAKE_HYLIA },
    { 0x045F, "Lake Hylia" /* > Fishing Hole */ , ENTRANCE_GROUP_LAKE_HYLIA },
    { 0x0309, "Fishing Hole" /* > Lake Hylia */ , ENTRANCE_GROUP_LAKE_HYLIA },
    { 0x03A0, "GV" /* > Carpenters' Tent */ , ENTRANCE_GROUP_GERUDO_VALLEY },
    { 0x03D0, "Carpenters' Tent" /* > GV */ , ENTRANCE_GROUP_GERUDO_VALLEY },
    { 0x007E, "Market Entrance" /* > Guard House */ , ENTRANCE_GROUP_MARKET },
    { 0x026E, "Guard House" /* > Market Entrance */ , ENTRANCE_GROUP_MARKET },
    { 0x0530, "Market" /* > Mask Shop */ , ENTRANCE_GROUP_MARKET },
    { 0x01D1, "Mask Shop" /* > Market */ , ENTRANCE_GROUP_MARKET },
    { 0x0507, "Market" /* > Bombchu Bowling */ , ENTRANCE_GROUP_MARKET },
    { 0x03BC, "Bombchu Bowling" /* > Market */ , ENTRANCE_GROUP_MARKET },
    { 0x0388, "Market" /* > MK Potion Shop */ , ENTRANCE_GROUP_MARKET },
    { 0x02A2, "MK Potion Shop" /* > Market */ , ENTRANCE_GROUP_MARKET },
    { 0x0063, "Market" /* > Treasure Chest Game */ , ENTRANCE_GROUP_MARKET },
    { 0x01D5, "Treasure Chest Game" /* > Market */ , ENTRANCE_GROUP_MARKET },
    { 0x0528, "Market" /* > Bombchu Shop */ , ENTRANCE_GROUP_MARKET },
    { 0x03C0, "Bombchu Shop" /* > Market */ , ENTRANCE_GROUP_MARKET },
    { 0x043B, "Market" /* > Man-in-Green's House */ , ENTRANCE_GROUP_MARKET },
    { 0x0067, "Man-in-Green's House" /* > Market */ , ENTRANCE_GROUP_MARKET },
    { 0x02FD, "Kakariko" /* > Carpenter Boss House */ , ENTRANCE_GROUP_KAKARIKO },
    { 0x0349, "Carpenter Boss House" /* > Kakariko */ , ENTRANCE_GROUP_KAKARIKO },
    { 0x0550, "Kakariko" /* > House of Skulltula */ , ENTRANCE_GROUP_KAKARIKO },
    { 0x04EE, "House of Skulltula" /* > Kakariko */ , ENTRANCE_GROUP_KAKARIKO },
    { 0x039C, "Kakariko" /* > Impa's House Front */ , ENTRANCE_GROUP_KAKARIKO },
    { 0x0345, "Impa's House Front" /* > Kakariko */ , ENTRANCE_GROUP_KAKARIKO },
    { 0x05C8, "Kakariko" /* > Impa's House Back */ , ENTRANCE_GROUP_KAKARIKO },
    { 0x05DC, "Impa's House Back" /* > Kakariko */ , ENTRANCE_GROUP_KAKARIKO },
    { 0x0072, "Kakariko" /* > Granny's Potion Shop */ , ENTRANCE_GROUP_KAKARIKO },
    { 0x034D, "Granny's Potion Shop" /* > Kakariko */ , ENTRANCE_GROUP_KAKARIKO },
    { 0x030D, "Graveyard" /* > Dampe's Shack */ , ENTRANCE_GROUP_GRAVEYARD },
    { 0x0355, "Dampe's Shack" /* > Graveyard */ , ENTRANCE_GROUP_GRAVEYARD },
    { 0x037C, "Goron City" /* > Goron Shop */ , ENTRANCE_GROUP_GORON_CITY },
    { 0x03FC, "Goron Shop" /* > Goron City */ , ENTRANCE_GROUP_GORON_CITY },
    { 0x0380, "Zora's Domain" /* > Zora Shop */ , ENTRANCE_GROUP_ZORAS_DOMAIN },
    { 0x03C4, "Zora Shop" /* > Zora's Domain */ , ENTRANCE_GROUP_ZORAS_DOMAIN },
    { 0x004F, "Lon Lon Ranch" /* > Talon's House */ , ENTRANCE_GROUP_LON_LON_RANCH },
    { 0x0378, "Talon's House" /* > Lon Lon Ranch */ , ENTRANCE_GROUP_LON_LON_RANCH },
    { 0x02F9, "Lon Lon Ranch" /* > LLR Stables */ , ENTRANCE_GROUP_LON_LON_RANCH },
    { 0x042F, "LLR Stables" /* > Lon Lon Ranch */ , ENTRANCE_GROUP_LON_LON_RANCH },
    { 0x05D0, "Lon Lon Ranch" /* > LLR Tower */ , ENTRANCE_GROUP_LON_LON_RANCH },
    { 0x05D4, "LLR Tower" /* > Lon Lon Ranch */ , ENTRANCE_GROUP_LON_LON_RANCH },
    { 0x052C, "Market" /* > MK Bazaar */ , ENTRANCE_GROUP_MARKET },
    { 0x03B8, "MK Bazaar" /* > Market */ , ENTRANCE_GROUP_MARKET },
    { 0x016D, "Market" /* > MK Shooting Gallery */ , ENTRANCE_GROUP_MARKET },
    { 0x01CD, "MK Shooting Gallery" /* > Market */ , ENTRANCE_GROUP_MARKET },
    { 0x00B7, "Kakariko" /* > Kak Bazaar */ , ENTRANCE_GROUP_KAKARIKO },
    { 0x0201, "Kak Bazaar" /* > Kakariko */ , ENTRANCE_GROUP_KAKARIKO },
    { 0x003B, "Kakariko" /* > Kak Shooting Gallery */ , ENTRANCE_GROUP_KAKARIKO },
    { 0x0463, "Kak Shooting Gallery" /* > Kakariko */ , ENTRANCE_GROUP_KAKARIKO },
    { 0x0588, "Colossus" /* > Colossus Great Fairy Fountain */ , ENTRANCE_GROUP_HAUNTED_WASTELAND },
    { 0x057C, "Colossus Great Fairy Fountain" /* > Colossus */ , ENTRANCE_GROUP_HAUNTED_WASTELAND },
    { 0x0578, "HC Grounds" /* > HC Great Fairy Fountain */ , ENTRANCE_GROUP_HYRULE_CASTLE },
    { 0x0340, "HC Great Fairy Fountain" /* > HC Grounds */ , ENTRANCE_GROUP_HYRULE_CASTLE },
    { 0x04C2, "OGC" /* > OGC Great Fairy Fountain */ , ENTRANCE_GROUP_HYRULE_CASTLE },
    { 0x03E8, "OGC Great Fairy Fountain" /* > OGC */ , ENTRANCE_GROUP_HYRULE_CASTLE },
    { 0x04BE, "DMC" /* > DMC Great Fairy Fountain */ , ENTRANCE_GROUP_DEATH_MOUNTAIN_CRATER },
    { 0x0482, "DMC Great Fairy Fountain" /* > DMC */ , ENTRANCE_GROUP_DEATH_MOUNTAIN_CRATER },
    { 0x0315, "DMT" /* > DMT Great Fairy Fountain */ , ENTRANCE_GROUP_DEATH_MOUNTAIN_TRAIL },
    { 0x045B, "DMT Great Fairy Fountain" /* > DMT */ , ENTRANCE_GROUP_DEATH_MOUNTAIN_TRAIL },
    { 0x0371, "ZF" /* > ZF Great Fairy Fountain */ , ENTRANCE_GROUP_ZORAS_DOMAIN },
    { 0x0394, "ZF Great Fairy Fountain" /* > ZF */ , ENTRANCE_GROUP_ZORAS_DOMAIN },
    { 0x0272, "KF" /* > Link's House */ , ENTRANCE_GROUP_KOKIRI_FOREST },
    { 0x0211, "Link's House" /* > KF */ , ENTRANCE_GROUP_KOKIRI_FOREST },
    { 0x0053, "Outside Temple of Time" /* > Temple of Time */ , ENTRANCE_GROUP_MARKET },
    { 0x0472, "Temple of Time" /* > Outside Temple of Time */ , ENTRANCE_GROUP_MARKET },
    { 0x0453, "Kakariko" /* > Windmill */ , ENTRANCE_GROUP_KAKARIKO },
    { 0x0351, "Windmill" /* > Kakariko */ , ENTRANCE_GROUP_KAKARIKO },
    { 0x0384, "Kakariko" /* > Kak Potion Shop Front */ , ENTRANCE_GROUP_KAKARIKO },
    { 0x044B, "Kak Potion Shop Front" /* > Kakariko */ , ENTRANCE_GROUP_KAKARIKO },
    { 0x03EC, "Kakariko" /* > Kak Potion Shop Back */ , ENTRANCE_GROUP_KAKARIKO },
    { 0x04FF, "Kak Potion Shop Back" /* > Kakariko */ , ENTRANCE_GROUP_KAKARIKO },
    { 0x05E0, "KF" /* > Lost Woods Bridge */ , ENTRANCE_GROUP_KOKIRI_FOREST },
    { 0x020D, "Lost Woods Bridge" /* > KF */ , ENTRANCE_GROUP_LOST_WOODS },
    { 0x011E, "KF" /* > Lost Woods */ , ENTRANCE_GROUP_KOKIRI_FOREST },
    { 0x0286, "Lost Woods" /* > KF */ , ENTRANCE_GROUP_LOST_WOODS },
    { 0x04E2, "Lost Woods" /* > Goron City */ , ENTRANCE_GROUP_LOST_WOODS },
    { 0x04D6, "Goron City" /* > Lost Woods */ , ENTRANCE_GROUP_GORON_CITY },
    { 0x01DD, "Lost Woods" /* > ZR */ , ENTRANCE_GROUP_LOST_WOODS },
    { 0x04DA, "ZR" /* > Lost Woods */ , ENTRANCE_GROUP_ZORAS_DOMAIN },
    { 0x00FC, "Lost Woods" /* > SFM */ , ENTRANCE_GROUP_LOST_WOODS },
    { 0x01A9, "SFM" /* > Lost Woods */ , ENTRANCE_GROUP_LOST_WOODS },
    { 0x0185, "Lost Woods Bridge" /* > Hyrule Field */ , ENTRANCE_GROUP_LOST_WOODS },
    { 0x04DE, "Hyrule Field" /* > Lost Woods Bridge */ , ENTRANCE_GROUP_HYRULE_FIELD },
    { 0x0102, "Hyrule Field" /* > Lake Hylia */ , ENTRANCE_GROUP_HYRULE_FIELD },
    { 0x0189, "Lake Hylia" /* > Hyrule Field */ , ENTRANCE_GROUP_LAKE_HYLIA },
    { 0x0117, "Hyrule Field" /* > GV */ , ENTRANCE_GROUP_HYRULE_FIELD },
    { 0x018D, "GV" /* > Hyrule Field */ , ENTRANCE_GROUP_GERUDO_VALLEY },
    { 0x0276, "Hyrule Field" /* > Market Entrance */ , ENTRANCE_GROUP_HYRULE_FIELD },
    { 0x01FD, "Market Entrance" /* > Hyrule Field */ , ENTRANCE_GROUP_MARKET },
    { 0x00DB, "Hyrule Field" /* > Kakariko */ , ENTRANCE_GROUP_HYRULE_FIELD },
    { 0x017D, "Kakariko" /* > Hyrule Field */ , ENTRANCE_GROUP_KAKARIKO },
    { 0x00EA, "Hyrule Field" /* > ZR */ , ENTRANCE_GROUP_HYRULE_FIELD },
    { 0x0181, "ZR" /* > Hyrule Field */ , ENTRANCE_GROUP_ZORAS_DOMAIN },
    { 0x0157, "Hyrule Field" /* > Lon Lon Ranch */ , ENTRANCE_GROUP_HYRULE_FIELD },
    { 0x01F9, "Lon Lon Ranch" /* > Hyrule Field */ , ENTRANCE_GROUP_LON_LON_RANCH },
    { 0x0328, "Lake Hylia" /* > Zora's Domain */ , ENTRANCE_GROUP_LAKE_HYLIA },
    { 0x0560, "Zora's Domain" /* > Lake Hylia */ , ENTRANCE_GROUP_ZORAS_DOMAIN },
    { 0x0129, "GV" /* > GF */ , ENTRANCE_GROUP_GERUDO_VALLEY },
    { 0x022D, "GF" /* > GV */ , ENTRANCE_GROUP_GERUDO_VALLEY },
    { 0x0130, "GF" /* > Haunted Wasteland */ , ENTRANCE_GROUP_GERUDO_VALLEY },
    { 0x03AC, "Haunted Wasteland" /* > GF */ , ENTRANCE_GROUP_HAUNTED_WASTELAND },
    { 0x0123, "Haunted Wasteland" /* > Desert Colossus */ , ENTRANCE_GROUP_HAUNTED_WASTELAND },
    { 0x0365, "Desert Colossus" /* > Haunted Wasteland */ , ENTRANCE_GROUP_HAUNTED_WASTELAND },
    { 0x00B1, "Market Entrance" /* > Market */ , ENTRANCE_GROUP_MARKET },
    { 0x0033, "Market" /* > Market Entrance */ , ENTRANCE_GROUP_MARKET },
    { 0x0138, "Market" /* > HC Grounds / OGC */ , ENTRANCE_GROUP_MARKET },
    { 0x025A, "HC Grounds / OGC" /* > Market */ , ENTRANCE_GROUP_HYRULE_CASTLE },
    { 0x0171, "Market" /* > Outside Temple of Time */ , ENTRANCE_GROUP_MARKET },
    { 0x025E, "Outside Temple of Time" /* > Market */ , ENTRANCE_GROUP_MARKET },
    { 0x00E4, "Kakariko" /* > Graveyard */ , ENTRANCE_GROUP_KAKARIKO },
    { 0x0195, "Graveyard" /* > Kakariko */ , ENTRANCE_GROUP_GRAVEYARD },
    { 0x013D, "Kakariko" /* > DMT */ , ENTRANCE_GROUP_KAKARIKO },
    { 0x0191, "DMT" /* > Kakariko */ , ENTRANCE_GROUP_DEATH_MOUNTAIN_TRAIL },
    { 0x014D, "DMT" /* > Goron City */ , ENTRANCE_GROUP_DEATH_MOUNTAIN_TRAIL },
    { 0x01B9, "Goron City" /* > DMT */ , ENTRANCE_GROUP_GORON_CITY },
    { 0x0246, "Goron City" /* > DMC */ , ENTRANCE_GROUP_GORON_CITY },
    { 0x01C1, "DMC" /* > Goron City */ , ENTRANCE_GROUP_DEATH_MOUNTAIN_CRATER },
    { 0x0147, "DMT" /* > DMC */ , ENTRANCE_GROUP_DEATH_MOUNTAIN_TRAIL },
    { 0x01BD, "DMC" /* > DMT */ , ENTRANCE_GROUP_DEATH_MOUNTAIN_CRATER },
    { 0x0108, "ZR" /* > Zora's Domain */ , ENTRANCE_GROUP_ZORAS_DOMAIN },
    { 0x019D, "Zora's Domain" /* > ZR */ , ENTRANCE_GROUP_ZORAS_DOMAIN },
    { 0x0225, "Zora's Domain" /* > ZF */ , ENTRANCE_GROUP_ZORAS_DOMAIN },
    { 0x01A1, "ZF" /* > Zora's Domain */ , ENTRANCE_GROUP_ZORAS_DOMAIN },
};

char* GetEntranceName(s16 index_) {
    for (size_t i = 0; i < sizeof(entranceNames) / sizeof(EntranceName); i++) {
        if (index_ == entranceNames[i].index) {
            return entranceNames[i].name;
        }
    }
    return NULL;
}

void InitEntranceTrackingData(void) {
    // Check if entrance randomization is disabled
    if (rEntranceOverrides[0].index == 0 && rEntranceOverrides[0].override == 0) {
        return;
    }

    for (size_t i = 0; i < sizeof(entranceNames) / sizeof(EntranceName); i++) {
        if (entranceNames[i].name == NULL) {
            break;
        }
        for (size_t j = 0; j < ENTRANCE_OVERRIDES_MAX_COUNT; j++) {
            if (rEntranceOverrides[j].index == 0 && rEntranceOverrides[j].override == 0) {
                break;
            }
            if (entranceNames[i].index == rEntranceOverrides[j].index) {
                gEntranceTrackingData.GroupEntranceCounts[entranceNames[i].group]++;
                gEntranceTrackingData.EntranceCount++;
                break;
            }
        }
    }
    u16 offsetTotal = 0;
    for (size_t i = 1; i < SPOILER_ENTRANCE_GROUP_COUNT; i++) {
        offsetTotal += gEntranceTrackingData.GroupEntranceCounts[i - 1];
        gEntranceTrackingData.GroupOffsets[i] = offsetTotal;
    }
}
