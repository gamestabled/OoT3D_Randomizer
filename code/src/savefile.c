#include "z3D/z3D.h"
#include "settings.h"

void SaveFile_Init() {
//#ifdef ENABLE_DEBUG
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
//#endif

    //things to always set
    gSaveContext.cutsceneIndex = 0;          //no intro cutscene
    gSaveContext.infTable   [0x0] |= 0x01;   //greeted by Saria
    gSaveContext.infTable  [0x11] |= 0x0400; //Met Darunia in Fire Temple
    gSaveContext.infTable  [0x14] |= 0x000E; //Ruto in Jabu can be escorted immediately
    gSaveContext.itemGetInf [0x1] |= 0x0800; //Deku seeds text cleared
    gSaveContext.eventChkInf[0x3] |= 0x0800; //began Nabooru Battle
    gSaveContext.eventChkInf[0x7] |= 0x00DF; //began boss battles (except Twinrova and Ganondorf)
    gSaveContext.eventChkInf[0x9] |= 0x0010; //Spoke to Nabooru as child
    gSaveContext.eventChkInf[0xA] |= 0x01FB; //entrance cutscenes
    gSaveContext.eventChkInf[0xB] |= 0x07FF; //more entrance cutscenes
    gSaveContext.eventChkInf[0xC] |= 0x0001; //Nabooru ordered to fight by Twinrova
    gSaveContext.eventChkInf[0xC] |= 0x8000; //Forest Temple entrance cutscene (3ds only)

    //navi text triggers
    gSaveContext.sceneFlags [0].swch |= 0x80080400; //deku tree vines and door and rolling spike
    gSaveContext.sceneFlags [1].swch |= 0x00004900; //dodongo entrance text and spike trap text
    gSaveContext.sceneFlags [2].swch |= 0x0F010000; //jabu jabu
    gSaveContext.sceneFlags [3].swch |= 0x01C00300; //forest temple
    gSaveContext.sceneFlags [4].swch |= 0x00080000; //fire temple
    gSaveContext.sceneFlags [5].swch |= 0x00000080; //water temple
    gSaveContext.sceneFlags [9].swch |= 0x00000020; //ice cavern (doesn't work)
    gSaveContext.sceneFlags[86].swch |= 0x00004000; //sacred forest meadow

    //open lowest fire temple locked door
    gSaveContext.sceneFlags[4].swch |= 0x00800000;

    //Everything past this point depends on settings
    //if starting age is adult
    if (gSettingsContext.startingAge == AGE_ADULT) {
      gSaveContext.linkAge       = AGE_ADULT;  //age is adult
      gSaveContext.entranceIndex = 0xF4050000; //spawn at temple of time
      gSaveContext.sceneIndex    = 0x6100;     //^
    }

    //give Link the starting stone or medallion
    gSaveContext.questItems |= gSettingsContext.dungeonRewardBitMask;

    //Open Door of Time
    if (gSettingsContext.openDoorOfTime) {
      gSaveContext.eventChkInf[0x4] |= 0x0800; //Open Door of Time
    }

    gSaveContext.eventChkInf[0x0] |= 0x14;   //spoke to mido and moved him
    gSaveContext.eventChkInf[0x0] |= 0x1020; //met deku tree and opened mouth

    gSaveContext.eventChkInf[0x4] |= 0x8020; //entered MS chamber, Pulled MS from pedestal
    gSaveContext.eventChkInf[0x5] |= 0x0C37; //Sheik Moved From pedestal and get rid of song cutscenes

    gSaveContext.eventChkInf[0xC] |= 0x0020; //Sheik Spawned at MS pedestal as Adult
}
