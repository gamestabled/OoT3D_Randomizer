#include "z3D/z3D.h"
#include "settings.h"

u32 EnBomBowlMan_CheckExplosives(void) {
    if (gSettingsContext.bombchusInLogic) {
        return (gSaveContext.items[ItemSlots[ITEM_BOMBCHU]] != ITEM_NONE);
    } else {
        return (((gSaveContext.upgrades >> 3) & 0x7) != 0);
    }
}
