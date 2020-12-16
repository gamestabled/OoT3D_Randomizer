#include "z3D/z3D.h"
#include "entrance.h"
#include "settings.h"

void Entrance_Init(void) {
    s32 index;

    // Skip Child Stealth if given by settings
    if (gSettingsContext.skipChildStealth) {
        gEntranceTable[0x07A].scene = 0x4A;
        gEntranceTable[0x07A].spawn = 0x01;
        gEntranceTable[0x07A].field = 0x0183;
    }

    // Delete the title card for Desert Colossus from Requiem
    for (index = 0x1ED; index < 0x1F1; ++index) {
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
}
