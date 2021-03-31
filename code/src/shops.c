#include "z3D/z3D.h"
#include "settings.h"

s32 Shop_CheckCanBuyBombchus(void) {
    const u32 slot = ItemSlots[ITEM_BOMBCHU];

    if (gSettingsContext.bombchusInLogic) {
        if (gSaveContext.items[slot] != ITEM_NONE) {
            return 0;
        } else {
            return 2;
        }
    } else {
        if (((gSaveContext.upgrades >> 3) & 0x7) != 0) {
            return 0;
        } else {
            return 2;
        }
    }
}
