#include "z3D/z3D.h"
#include "item_override.h"
#include "settings.h"

//Patched over call to Item_Give
void Cutscene_OverrideOcarinaSongs(GlobalContext* GlobalContext, ItemID songId) {
    ItemOverride_PushDelayedOverride(songId - ITEM_SONG_MINUET + 0x20); //TODO remove the hardcoded constant?
}

u32 LACS_ConditionVanilla(void) {
    return ((gSaveContext.questItems & 0x8) && (gSaveContext.questItems & 0x10));
}

u32 LACS_ConditionStones(void) {
    return ((gSaveContext.questItems & 0x40000) && (gSaveContext.questItems & 0x80000)
        && (gSaveContext.questItems & 0x100000));
}

u32 LACS_ConditionMedallions(void) {
    return ((gSaveContext.questItems & 0x1) && (gSaveContext.questItems & 0x2)
        && (gSaveContext.questItems & 0x4) && (gSaveContext.questItems & 0x8)
        && (gSaveContext.questItems & 0x10) && (gSaveContext.questItems & 0x20));
}

void Cutscene_OverrideLACS(void) {
    u32 conditionMet = 0;

    switch(gSettingsContext.lacsCondition) {
        case LACSCONDITION_VANILLA:
            conditionMet = LACS_ConditionVanilla();
            break;
        case LACSCONDITION_STONES:
            conditionMet = LACS_ConditionStones();
            break;
        case LACSCONDITION_MEDALLIONS:
            conditionMet = LACS_ConditionMedallions();
            break;
        case LACSCONDITION_DUNGEONS:
            conditionMet = (LACS_ConditionStones() && LACS_ConditionMedallions());
            break;
    }
    if (conditionMet) {
        ItemOverride_PushDelayedOverride(0x01);
        EventSet(0xC4);
        gSaveContext.entranceIndex = 0x53;
    }
}

u32 Cutscene_OverrideRequiem(void) {
    if (!EventCheck(0xAC)) {
        ItemOverride_PushDelayedOverride(0x23);
        EventSet(0xAC);
    }
    return 1;
}
