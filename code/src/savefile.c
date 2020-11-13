#include "z3D/z3D.h"

void SaveFile_Init() {
    gSaveContext.cutsceneIndex = 0; //no intro cutscene
    gSaveContext.eventChkInf[0x0] |= 0x14;   //spoke to mido and moved him
    gSaveContext.eventChkInf[0x0] |= 0x1020; //met deku tree and opened mouth
    gSaveContext.infTable   [0x0] |= 0x01;   //greeted by Saria

    gSaveContext.eventChkInf[0x3] |= 0x0800; //began Nabooru Battle
    gSaveContext.eventChkInf[0x4] |= 0x8820; //entered MS chamber, Opened DoT, Pulled MS from pedestal
    gSaveContext.eventChkInf[0x5] |= 0x0C37; //Sheik Moved From pedestal and get rid of song cutscenes

    gSaveContext.eventChkInf[0x7] |= 0x00DF; //began boss battles (except twinrova and ganondorf)

    gSaveContext.eventChkInf[0x9] |= 0x0010; //Spoke to nabooru as child
    gSaveContext.eventChkInf[0xA] |= 0x01FB; //entered deku tree, temple of time, Goron city, hyrule castle, Zoras domain, kakariko village, DMT, hyrule field
    gSaveContext.eventChkInf[0xB] |= 0x03FF; //entered DMC, Colossus, Zora's Fountain, Graveyard, JJB, LLR, Gerudo Fortress, Gerudo Valley, Lake Hylia, DC
    gSaveContext.eventChkInf[0xC] |= 0x0022; //Sheik Spawned at MS pedestal as Adult and Saria gift cutscene

    //navi text triggers
    gSaveContext.sceneFlags[0].swch |= 0x80080400; //deku tree vines and door and rolling spike
    gSaveContext.sceneFlags[1].swch |= 0x00004800; //dodongo entrance text and spike trap text

    gSaveContext.sceneFlags[3].swch |= 0x01000000; //forest temple (twisted hallway)

    gSaveContext.sceneFlags[5].swch |= 0x00000080; //water temple (snake water room)

}
