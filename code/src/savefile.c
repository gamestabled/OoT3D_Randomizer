#include "z3D/z3D.h"
#include "settings.h"
#include "savefile.h"

void SaveFile_Init() {
#ifdef ENABLE_DEBUG
    gSaveContext.equipment  |= 0x0FFF;  //Swords, shields, tunics, boots
    gSaveContext.bgsFlag     = 1;
    gSaveContext.bgsHitsLeft = 1;
    gSaveContext.upgrades   |= 0x309;   //bomb bag, quiver, strength, scale
    gSaveContext.questItems |= 0x3FFC0; //songs
    gSaveContext.items[SLOT_OCARINA]  = ITEM_OCARINA_FAIRY;
    gSaveContext.items[SLOT_HOOKSHOT] = ITEM_LONGSHOT;
    gSaveContext.items[SLOT_HAMMER]   = ITEM_HAMMER;
    gSaveContext.items[SLOT_FARORES_WIND] = ITEM_FARORES_WIND;
    gSaveContext.items[SLOT_DINS_FIRE] = ITEM_DINS_FIRE;
    gSaveContext.items[SLOT_BOMB] = ITEM_BOMB;
    gSaveContext.items[SLOT_BOW] = ITEM_BOW;
    gSaveContext.items[SLOT_ARROW_FIRE] = ITEM_ARROW_FIRE;
    gSaveContext.items[SLOT_HOVER_BOOTS] = ITEM_BOOTS_HOVER;
    gSaveContext.items[SLOT_ARROW_LIGHT] = ITEM_ARROW_LIGHT;
    gSaveContext.items[SLOT_BOTTLE_1] = ITEM_FISH;
    gSaveContext.magicAcquired = 1;
    gSaveContext.magicLevel = 2;
    gSaveContext.magic = 48;
    gSaveContext.dungeonKeys[6] = 8;
    gSaveContext.dungeonKeys[7] = 5;
    gSaveContext.ammo[2] = 20; //bombs
    gSaveContext.ammo[3] = 20; //arrows
#endif

    /*-----------------------------------
    |       THINGS TO ALWAYS SET        |
    -----------------------------------*/
    gSaveContext.cutsceneIndex = 0;          //no intro cutscene
    gSaveContext.infTable   [0x0] |= 0x01;   //greeted by Saria
    gSaveContext.infTable  [0x11] |= 0x0400; //Met Darunia in Fire Temple
    gSaveContext.infTable  [0x14] |= 0x000E; //Ruto in Jabu can be escorted immediately
    gSaveContext.eventChkInf[0x3] |= 0x0800; //began Nabooru Battle
    gSaveContext.eventChkInf[0x7] |= 0x01FF; //began boss battles (except Ganondorf)
    gSaveContext.eventChkInf[0x9] |= 0x0010; //Spoke to Nabooru as child
    gSaveContext.eventChkInf[0xA] |= 0x017B; //entrance cutscenes (minus temple of time)
    gSaveContext.eventChkInf[0xB] |= 0x07FF; //more entrance cutscenes
    gSaveContext.eventChkInf[0xC] |= 0x0001; //Nabooru ordered to fight by Twinrova
    gSaveContext.eventChkInf[0xC] |= 0x8000; //Forest Temple entrance cutscene (3ds only)

    gSaveContext.sceneFlags[5].swch |= 0x00010000; //remove Ruto cutscene in Water Temple

    gSaveContext.unk_13D0[4] |= 0x01; //Club Moblin cutscene

    //open lowest Vanilla Fire Temple locked door (to prevent key logic lockouts)
    if (gSettingsContext.fireTempleDungeonMode == DUNGEONMODE_VANILLA) {
        gSaveContext.sceneFlags[DUNGEON_FIRE_TEMPLE].swch |= 0x00800000;
    }
    //open middle locked door in Vanilla Water Temple (to prevent key logic lockouts)
    if (gSettingsContext.waterTempleDungeonMode == DUNGEONMODE_VANILLA) {
        gSaveContext.sceneFlags[DUNGEON_WATER_TEMPLE].swch |= 0x00200000;
    }


    /*-----------------------------------
    |THINGS TO SET DEPENDING ON SETTINGS|
    -----------------------------------*/

    if (gSettingsContext.rainbowBridge == RAINBOWBRIDGE_OPEN) {
        gSaveContext.eventChkInf[0x4] |= 0x2000;
    }

    if (gSettingsContext.resolvedStartingAge == AGE_ADULT) {
        gSaveContext.linkAge       = AGE_ADULT;  //age is adult
        gSaveContext.entranceIndex = 0xF4050000; //spawn at temple of time
        gSaveContext.sceneIndex    = 0x6100;     //^
        gSaveContext.childEquips.equipment = 0x1100; //Child equips Kokiri Tunic and Kokiri Boots, no sword or shield
        gSaveContext.adultEquips.equipment = 0x1120; //Adult equips Kokiri Tunic, Kokiri Boots, and Master Sword
        gSaveContext.infTable[29]  = 0x00; //Unset swordless flag
    }

    //set master quest flag for mirror world
    if (gSettingsContext.mirrorWorld == ON) {
        gSaveContext.masterQuestFlag = 1;
    }

    if (gSettingsContext.startingTime == STARTINGTIME_NIGHT) {
        gSaveContext.dayTime = 0x1400; //Set night time
    }

    if (gSettingsContext.openDoorOfTime) {
        gSaveContext.eventChkInf[0x4] |= 0x0800; //Open Door of Time
    }

    if (gSettingsContext.gerudoFortress == GERUDOFORTRESS_FAST) {
        gSaveContext.eventChkInf[0x9] |= 0x000E; //Free 3 carpenters
        gSaveContext.sceneFlags[DUNGEON_GERUDO_FORTRESS].swch    |= 0x000D01DC; //heard yells/unlocked doors
        gSaveContext.sceneFlags[DUNGEON_GERUDO_FORTRESS].collect |= 0x0000C400; //picked up keys
    } else if (gSettingsContext.gerudoFortress == GERUDOFORTRESS_OPEN) {
        gSaveContext.eventChkInf[0x9] |= 0x000F; //Free all carpenters
        gSaveContext.sceneFlags[DUNGEON_GERUDO_FORTRESS].swch    |= 0x000F01FE; //heard yells/unlocked doors
        gSaveContext.sceneFlags[DUNGEON_GERUDO_FORTRESS].collect |= 0x0000D400; //picked up keys
    }

    if (gSettingsContext.zorasFountain == ZORASFOUNTAIN_OPEN) {
        gSaveContext.eventChkInf[0x3] |= 0x0008; //King Zora Moved Aside
    }

    //Set Skipped Trials
    gSaveContext.eventChkInf[0xB] |= (gSettingsContext.forestTrialSkip) ? 0x0800 : 0;
    gSaveContext.eventChkInf[0xB] |= (gSettingsContext.fireTrialSkip)   ? 0x4000 : 0;
    gSaveContext.eventChkInf[0xB] |= (gSettingsContext.waterTrialSkip)  ? 0x1000 : 0;
    gSaveContext.eventChkInf[0xA] |= (gSettingsContext.spiritTrialSkip) ? 0x2000 : 0;
    gSaveContext.eventChkInf[0xB] |= (gSettingsContext.shadowTrialSkip) ? 0x2000 : 0;
    gSaveContext.eventChkInf[0xB] |= (gSettingsContext.lightTrialSkip)  ? 0x8000 : 0;

    //If all trials are skipped
    if (gSettingsContext.forestTrialSkip && gSettingsContext.fireTrialSkip && gSettingsContext.waterTrialSkip &&
        gSettingsContext.spiritTrialSkip && gSettingsContext.shadowTrialSkip && gSettingsContext.lightTrialSkip) {
            gSaveContext.eventChkInf[0xC] |= 0x0008; //dispel Ganon's Tower Barrier
    }

    //Give Link a starting stone/medallion if he has one (if he doesn't the value is just 0)
    gSaveContext.questItems |= gSettingsContext.linksPocketRewardBitMask;

    if (gSettingsContext.fourPoesCutscene == SKIP) {
        gSaveContext.sceneFlags[3].swch |= 0x08000000; //Remove Poe cutscene in Forest Temple
    }

    if (gSettingsContext.templeOfTimeIntro == SKIP) {
        gSaveContext.eventChkInf[0xA] |= 0x0080; //Remove Temple of Time intro cutscene
    }

    //give maps and compasses
    if (gSettingsContext.mapsAndCompasses == MAPSANDCOMPASSES_START_WITH) {
        for (u8 i = 0; i < 0xA; i++) {
            gSaveContext.dungeonItems[i] |= 0x6;
        }
    }

    //give small keys
    if (gSettingsContext.keysanity == KEYSANITY_START_WITH) {                     //check if MQ dungeon               MQ : Vanilla key count
        gSaveContext.dungeonKeys[DUNGEON_FOREST_TEMPLE]            = gSettingsContext.forestTempleDungeonMode          ? 6 : 5;
        gSaveContext.dungeonKeys[DUNGEON_FIRE_TEMPLE]              = gSettingsContext.fireTempleDungeonMode            ? 5 : 8;
        gSaveContext.dungeonKeys[DUNGEON_WATER_TEMPLE]             = gSettingsContext.waterTempleDungeonMode           ? 2 : 6;
        gSaveContext.dungeonKeys[DUNGEON_SPIRIT_TEMPLE]            = gSettingsContext.spiritTempleDungeonMode          ? 7 : 5;
        gSaveContext.dungeonKeys[DUNGEON_SHADOW_TEMPLE]            = gSettingsContext.shadowTempleDungeonMode          ? 6 : 5;
        gSaveContext.dungeonKeys[DUNGEON_BOTTOM_OF_THE_WELL]       = gSettingsContext.bottomOfTheWellDungeonMode       ? 2 : 3;
        gSaveContext.dungeonKeys[DUNGEON_GERUDO_TRAINING_GROUNDS]  = gSettingsContext.gerudoTrainingGroundsDungeonMode ? 3 : 9;
        gSaveContext.dungeonKeys[DUNGEON_GANONS_CASTLE_FIRST_PART] = gSettingsContext.ganonsCastleDungeonMode          ? 3 : 2;
        //give starting spirit keys for vanilla key locations
    } else if (gSettingsContext.keysanity == KEYSANITY_VANILLA) {
        if (gSettingsContext.spiritTempleDungeonMode == DUNGEONMODE_MQ) {
            gSaveContext.dungeonKeys[DUNGEON_SPIRIT_TEMPLE] = 3;
        }
    }

    //give boss keys
    if (gSettingsContext.bossKeysanity == BOSSKEYSANITY_START_WITH) {
        for (u8 i = 3; i < 8; i++) {
            gSaveContext.dungeonItems[i] |= 0x1;
        }
    }

    //give Ganon's Castle Boss Key
    if (gSettingsContext.ganonsBossKey == GANONSBOSSKEY_START_WITH) {
        gSaveContext.dungeonItems[DUNGEON_GANONS_CASTLE_SECOND_PART] |= 0x1;
    }

    //give the Gerudo Token if Gerudo Fortress is Open and Shuffle Gerudo Card is off
    if (gSettingsContext.gerudoFortress == GERUDOFORTRESS_OPEN && gSettingsContext.shuffleGerudoToken == OFF) {
        gSaveContext.questItems |= 0x00400000;
    }

    //Move mido away from the path to the Deku Tree in Open Forest
    if (gSettingsContext.openForest == OPENFOREST_OPEN) {
      gSaveContext.eventChkInf[0x0] |= 0x0010;
    }

    gSaveContext.eventChkInf[0x0] |= 0x0004; //spoke to mido
    gSaveContext.eventChkInf[0x0] |= 0x1020; //met deku tree and opened mouth

    gSaveContext.eventChkInf[0x4] |= 0x8020; //entered MS chamber, Pulled MS from pedestal

    gSaveContext.eventChkInf[0xC] |= 0x0020; //Sheik Spawned at MS pedestal as Adult
}

void SaveFile_SaveChildBButton(void) {
    gSaveContext.infTable[29] &= 0x00; //Unset the swordless flag when going adult
}

u16 SaveFile_RestoreChildEquips(void) {
    //if Kokiri Sword is not on child B button
    if (gSaveContext.childEquips.buttonItems[0] != ITEM_SWORD_KOKIRI) {
        gSaveContext.infTable[29] |= 0x1; //set swordless flag
    }
    return (gSaveContext.childEquips.equipment & 0xFFF0) | (gSaveContext.equipment & 0x1);
}

u32 SaveFile_CheckGerudoToken(void) {
    return ((gSaveContext.questItems & 0x400000) != 0) ? 1 : 0;
}

void SaveFile_SwapFaroresWind(void) {
    const u32 numWordsToSwap = sizeof(gSaveContext.fw) / sizeof(u32);

    u32* curFWData = (u32*)&gSaveContext.fw;
    u32* storedFWData = &gSaveContext.sceneFlags[0x40].unk;
    u32 tempCur;
    u32 tempStored;

    for (s32 i = 0; i < numWordsToSwap; i++) {
        tempCur = *curFWData;
        tempStored = *storedFWData;
        *curFWData = tempStored;
        *storedFWData = tempCur;

        curFWData++;
        storedFWData += sizeof(SaveSceneFlags);
    }
}

u8 SaveFile_GetMedallionCount(void) {
    u8 count = 0;

    for (u8 i = 0; i <= 5; i++) {
        count += (gSaveContext.questItems >> i) & 0x1;
    }
    return count;
}

u8 SaveFile_GetStoneCount(void) {
    u8 count = 0;

    for (u8 i = 18; i <= 20; i++) {
        count += (gSaveContext.questItems >> i) & 0x1;
    }
    return count;
}

u8 SaveFile_GetDungeonCount(void) {
    u8 count = 0;

    //Adult dungeons
    for (u8 i = 0x6; i <= 0xA; i++) {
        count += (gSaveContext.eventChkInf[4] >> i) & 0x1;
    }

    //Child dungeons
    count += (gSaveContext.eventChkInf[0] >> 9) & 0x1; //Deku Tree
    count += (gSaveContext.eventChkInf[2] >> 5) & 0x1; //Dodongo's Cavern
    count += (gSaveContext.eventChkInf[3] >> 7) & 0x1; //Jabu Jabu's Belly

    return count;
}
