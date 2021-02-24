#include "z3D/z3D.h"
#include "settings.h"

void SaveFile_Init() {
#ifdef ENABLE_DEBUG
    gSaveContext.equipment  |= 0xFFFF;  //Swords, shields, tunics, boots
    gSaveContext.upgrades   |= 0x109;   //bomb bag, quiver, strength
    gSaveContext.questItems |= 0x3FFC0; //songs
    gSaveContext.items[SLOT_OCARINA]  = ITEM_OCARINA_FAIRY;
    gSaveContext.items[SLOT_HOOKSHOT] = ITEM_LONGSHOT;
    gSaveContext.items[SLOT_HAMMER]   = ITEM_HAMMER;
    gSaveContext.items[SLOT_FARORES_WIND] = ITEM_FARORES_WIND;
    gSaveContext.items[SLOT_DINS_FIRE] = ITEM_DINS_FIRE;
    gSaveContext.items[SLOT_BOMB] = ITEM_BOMB;
    gSaveContext.items[SLOT_BOW] = ITEM_BOW;
    gSaveContext.items[SLOT_ARROW_FIRE] = ITEM_ARROW_FIRE;
    gSaveContext.magicAcquired = 1;
    gSaveContext.magicLevel = 2;
    gSaveContext.magic = 48;
    gSaveContext.dungeonKeys[6] = 8;
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
    gSaveContext.eventChkInf[0x7] |= 0x00DF; //began boss battles (except Twinrova and Ganondorf)
    gSaveContext.eventChkInf[0x9] |= 0x0010; //Spoke to Nabooru as child
    gSaveContext.eventChkInf[0xA] |= 0x017B; //entrance cutscenes (minus temple of time)
    gSaveContext.eventChkInf[0xB] |= 0x07FF; //more entrance cutscenes
    gSaveContext.eventChkInf[0xC] |= 0x0001; //Nabooru ordered to fight by Twinrova
    gSaveContext.eventChkInf[0xC] |= 0x8000; //Forest Temple entrance cutscene (3ds only)

    gSaveContext.sceneFlags[5].swch |= 0x00010000; //remove Ruto cutscene in Water Temple

    //navi text triggers
    gSaveContext.sceneFlags [0].swch |= 0x80080400; //deku tree vines and door and rolling spike
    gSaveContext.sceneFlags [1].swch |= 0x00004900; //dodongo entrance text and spike trap text
    gSaveContext.sceneFlags [2].swch |= 0x0F010000; //jabu jabu
    gSaveContext.sceneFlags [3].swch |= 0x01C00300; //forest temple
    gSaveContext.sceneFlags [4].swch |= 0x00080000; //fire temple
    gSaveContext.sceneFlags [5].swch |= 0x00000080; //water temple
    gSaveContext.sceneFlags [9].swch |= 0x00000020; //ice cavern TODO: doesn't work
    gSaveContext.sceneFlags[86].swch |= 0x00004000; //sacred forest meadow

    //open lowest Fire Temple locked door (to prevent key logic lockouts)
    gSaveContext.sceneFlags[4].swch |= 0x00800000;

    //open middle locked door in Water Temple (to prevent key logic lockouts)
    gSaveContext.sceneFlags[5].swch |= 0x00200000;

    /*-----------------------------------
    |THINGS TO SET DEPENDING ON SETTINGS|
    -----------------------------------*/

    if (gSettingsContext.startingAge == AGE_ADULT) {
        gSaveContext.linkAge       = AGE_ADULT;  //age is adult
        gSaveContext.entranceIndex = 0xF4050000; //spawn at temple of time
        gSaveContext.sceneIndex    = 0x6100;     //^
        gSaveContext.childEquips.equipment = 0x1100; //Child equips Kokiri Tunic and Kokiri Boots, no sword or shield
    }

    if (gSettingsContext.startingTime == STARTINGTIME_NIGHT) {
        gSaveContext.dayTime = 0x1400; //Set night time
    }

    //give Link the starting stone or medallion
    gSaveContext.questItems |= gSettingsContext.dungeonRewardBitMask;

    if (gSettingsContext.openDoorOfTime) {
        gSaveContext.eventChkInf[0x4] |= 0x0800; //Open Door of Time
    }

    if (gSettingsContext.gerudoFortress == GERUDOFORTRESS_FAST) {
        gSaveContext.eventChkInf[0x9] |= 0x000E; //Free 3 carpenters
    } else if (gSettingsContext.gerudoFortress == GERUDOFORTRESS_OPEN) {
        gSaveContext.eventChkInf[0x9] |= 0x000F; //Free all carpenters
    }

    if (gSettingsContext.zorasFountain == ZORASFOUNTAIN_OPEN) {
        gSaveContext.eventChkInf[0x3] |= 0x0008; //King Zora Moved Aside
    }

    if (gSettingsContext.fourPoesCutscene) {
        gSaveContext.sceneFlags[3].swch |= 0x08000000; //Remove Poe cutscene in Forest Temple
    }

    if (gSettingsContext.templeOfTimeIntro) {
        gSaveContext.eventChkInf[0xA] |= 0x0080; //Remove Temple of Time intro cutscene
    }

    //give maps and compasses
    if (gSettingsContext.mapsAndCompasses == MAPSANDCOMPASSES_START_WITH) {
        for (u8 i = 0; i < 0xA; i++) {
            gSaveContext.dungeonItems[i] |= 0x6;
        }
    }

    gSaveContext.eventChkInf[0x0] |= 0x14;   //spoke to mido and moved him
    gSaveContext.eventChkInf[0x0] |= 0x1020; //met deku tree and opened mouth

    gSaveContext.eventChkInf[0x4] |= 0x8020; //entered MS chamber, Pulled MS from pedestal

    gSaveContext.eventChkInf[0xC] |= 0x0020; //Sheik Spawned at MS pedestal as Adult
}

void SaveFile_SaveChildBButton(void) {
    gSaveContext.childEquips.buttonItems[0] = (gSaveContext.equipment & 0x1) ? ITEM_SWORD_KOKIRI : ITEM_NONE;
}

u16 SaveFile_RestoreChildEquips(void) {
    return (gSaveContext.childEquips.equipment & 0xFFF0) | (gSaveContext.equipment & 0x1);
}

u32 SaveFile_CheckGerudoToken(void) {
    return ((gSaveContext.questItems & 0x400000) != 0) ? 1 : 0;
}
