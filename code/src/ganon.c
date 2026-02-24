#include "z3D/z3D.h"
#include "savefile.h"

void Ganon_CSEquipMS(void) {
    if (!SaveFile_SwordlessPatchesEnabled()) {
        // By default Master sword is equipped before being discarded
        gSaveContext.equips.equipment      = (gSaveContext.equips.equipment & 0xFFF0) | 0x2;
        gSaveContext.equips.buttonItems[0] = 0x3C;
    } else {
        // In case BGS or kokiri sword equipped return to functionless item
        gSaveContext.equips.equipment      = (gSaveContext.equips.equipment & 0xFFF0);
        gSaveContext.equips.buttonItems[0] = 0xFE;
    }
}

void Ganon_GiveMSMidFight(void) {
    // By default give and equip master sword, otherwise do nothing
    if (!SaveFile_SwordlessPatchesEnabled()) {
        gSaveContext.equipment |= 0x2;
        gSaveContext.equips.equipment      = (gSaveContext.equips.equipment & 0xFFF0) | 0x2;
        gSaveContext.equips.buttonItems[0] = 0x3C;
    }
}

void Ganon_OnFinalBlow(void) {
    gFinalPlaytimeSeconds = gExtSaveData.playtimeSeconds;
    SaveGame(gGlobalContext, FALSE);
}
