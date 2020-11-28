#include "z3D/z3D.h"
#include "entrance.h"

void Entrance_Init(void) {
    s32 index;
    
    // Delete the title card for Temple of Time from Outside Temple of Time
    for (index = 0x53; index < 0x57; ++index) {
        gEntranceTable[index].field = 0x0102;
    }

    // Delete the title card for Desert Colossus from Spirit Temple Main Entrance
    for (index = 0x1E1; index < 0x1E5; ++index) {
        gEntranceTable[index].field = 0x0102;
    }
}
