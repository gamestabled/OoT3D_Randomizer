#include "z3D/z3D.h"

typedef u32 (*BgGjyoBridge_Condition)(void);

u32 BgGjyoBridge_ConditionVanilla(void) {
    return ((gSaveContext.questItems & 0x8) && (gSaveContext.questItems & 0x10) 
        && (gSaveContext.items[ItemSlots[ITEM_ARROW_LIGHT]] == ITEM_ARROW_LIGHT));
}

BgGjyoBridge_Condition bridgeCondition = BgGjyoBridge_ConditionVanilla;

u32 BgGjyoBridge_CheckCondition(void) {
    return bridgeCondition();
}