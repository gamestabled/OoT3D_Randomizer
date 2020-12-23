#include "z3D/z3D.h"

void Fishing_StoreTempB(void) {
    if (gSaveContext.equips.buttonItems[0] == ITEM_NONE) {
        gSaveContext.buttonStatus[0] = ITEM_BRACELET; // Just use a magic item to detect in restore
    } else {
        gSaveContext.buttonStatus[0] = gSaveContext.equips.buttonItems[0];
    }
}

void Fishing_RestoreTempB(void) {
    if (gSaveContext.buttonStatus[0] != ITEM_BRACELET) {
        gSaveContext.equips.buttonItems[0] = gSaveContext.buttonStatus[0];
    } else {
        gSaveContext.equips.buttonItems[0] = ITEM_NONE;
    }
}
