#include "z3D/z3D.h"
#include "settings.h"

u32 BgGjyoBridge_ConditionVanilla(void) {
    return ((gSaveContext.questItems & 0x8) && (gSaveContext.questItems & 0x10)
        && (gSaveContext.items[ItemSlots[ITEM_ARROW_LIGHT]] == ITEM_ARROW_LIGHT));
}

u32 BgGjyoBridge_ConditionStones(void) {
    return ((gSaveContext.questItems & 0x40000) && (gSaveContext.questItems & 0x80000)
        && (gSaveContext.questItems & 0x100000));
}

u32 BgGjyoBridge_ConditionMedallions(void) {
    return ((gSaveContext.questItems & 0x1) && (gSaveContext.questItems & 0x2)
        && (gSaveContext.questItems & 0x4) && (gSaveContext.questItems & 0x8)
        && (gSaveContext.questItems & 0x10) && (gSaveContext.questItems & 0x20));
}

u32 BgGjyoBridge_CheckCondition(void) {
    switch (gSettingsContext.rainbowBridge) {
        case RAINBOWBRIDGE_OPEN:
            return 1;
        case RAINBOWBRIDGE_VANILLA:
            return BgGjyoBridge_ConditionVanilla();
        case RAINBOWBRIDGE_STONES:
            return BgGjyoBridge_ConditionStones();
        case RAINBOWBRIDGE_MEDALLIONS:
            return BgGjyoBridge_ConditionMedallions();
        case RAINBOWBRIDGE_DUNGEONS:
            return BgGjyoBridge_ConditionStones() && BgGjyoBridge_ConditionMedallions();
        case RAINBOWBRIDGE_TOKENS:
            return gSaveContext.gsTokens >= gSettingsContext.tokenCount;
        default:
            return BgGjyoBridge_ConditionVanilla();
    }
}
