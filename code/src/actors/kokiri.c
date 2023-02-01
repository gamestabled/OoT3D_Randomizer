#include "z3D/z3D.h"
#include "settings.h"

u32 EnKo_CheckOpenForest(void) {
    if ((gSettingsContext.openForest == OPENFOREST_OPEN) || (gSettingsContext.openForest == OPENFOREST_CLOSED_DEKU) ||
        (gSaveContext.eventChkInf[0] & 0x80)) {
        return 1;
    } else {
        return 0;
    }
}

u32 EnKo_CheckForestTempleBeat(void) {
    if (EventCheck(0x48) == 0) {
        return 0;
    } else {
        return 1;
    }
}

u32 EnKo_CheckFadoCanSpawnInLostWoods(void) {
    if ((gSettingsContext.shuffleAdultTradeQuest == SHUFFLEADULTTRADEQUEST_ON) &&
        (gSaveContext.itemGetInf[2] & 0x2000) && !(gSaveContext.itemGetInf[3] & 0x2)) {
        return 1;
    } else if ((gSettingsContext.shuffleAdultTradeQuest == SHUFFLEADULTTRADEQUEST_OFF) &&
               (gSaveContext.items[SLOT_TRADE_ADULT] == ITEM_ODD_POTION)) {
        return 1;
    }
    return 0;
}
