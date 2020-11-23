#include "z3D/z3D.h"
#include "settings.h"

void SaveFile_Init() {

    //things to always set
    gSaveContext.cutsceneIndex     = 0;      //no intro cutscene
    gSaveContext.infTable   [0x0] |= 0x01;   //greeted by Saria
    gSaveContext.infTable  [0x20] |= 0x000E; //Ruto in Jabu can be escorted immediately
    gSaveContext.itemGetInf [0x1] |= 0x0008; //Deku seeds text
    gSaveContext.eventChkInf[0x3] |= 0x0800; //began Nabooru Battle
    gSaveContext.eventChkInf[0x7] |= 0x00DF; //began boss battles (except Twinrova and Ganondorf)
    gSaveContext.eventChkInf[0x9] |= 0x0010; //Spoke to Nabooru as child
    gSaveContext.eventChkInf[0xA] |= 0x01FB; //entered Deku Tree, Temple of Time, Goron City, Hyrule Castle, Zoras Domain, Kakariko Village, DMT, Hyrule Field
    gSaveContext.eventChkInf[0xB] |= 0x07FF; //entered Ganons Castle Exterior, DMC, Colossus, Zora's Fountain, Graveyard, JJB, LLR, Gerudo Fortress, Gerudo Valley, Lake Hylia, DC

    //navi text triggers
    gSaveContext.sceneFlags [0].swch |= 0x80080400; //deku tree vines and door and rolling spike
    gSaveContext.sceneFlags [1].swch |= 0x00004900; //dodongo entrance text and spike trap text
    gSaveContext.sceneFlags [2].swch |= 0x0F010000; //jabu jabu
    gSaveContext.sceneFlags [3].swch |= 0x01C00300; //forest temple
    gSaveContext.sceneFlags [4].swch |= 0x00080000; //fire temple
    gSaveContext.sceneFlags [5].swch |= 0x00000080; //water temple
    gSaveContext.sceneFlags [9].swch |= 0x00000020; //ice cavern
    gSaveContext.sceneFlags[86].swch |= 0x00004000; //sacred forest meadow

    //open lowest fire temple locked door
    gSaveContext.sceneFlags [4].swch |= 0x00008000;

    //Everything else depends on settings
    //if starting age is adult
    if (gSettingsContext.startingAge == AGE_ADULT) {
      gSaveContext.linkAge       = AGE_ADULT;  //age is adult
      gSaveContext.entranceIndex = 0xF4050000; //spawn at temple of time
      gSaveContext.sceneIndex    = 0x6100;     //^
    }

    //give Link the starting stone or medallion
    gSaveContext.questItems |= gSettingsContext.dungeonRewardBitMask;

    if (gSettingsContext.openDoorOfTime) {
      gSaveContext.eventChkInf[0x4] |= 0x0800; //Open Door of Time
    }

    if (gSettingsContext.shuffleBeanSalesman) {
      gSaveContext.ammo[15] = 9; //Magic bean salesman only sells one more bean
    }

    if (gSettingsContext.rainbowBridge == RAINBOWBRIDGE_OPEN) {
      gSaveContext.eventChkInf[0x4] |= 0x2000; //Rainbow Bridge built
    }

    gSaveContext.eventChkInf[0x0] |= 0x14;   //spoke to mido and moved him
    gSaveContext.eventChkInf[0x0] |= 0x1020; //met deku tree and opened mouth

    gSaveContext.eventChkInf[0x4] |= 0x8020; //entered MS chamber, Pulled MS from pedestal
    gSaveContext.eventChkInf[0x5] |= 0x0C37; //Sheik Moved From pedestal and get rid of song cutscenes

    gSaveContext.eventChkInf[0xC] |= 0x0022; //Sheik Spawned at MS pedestal as Adult and Saria gift cutscene
}
