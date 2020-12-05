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
        gSaveContext.entranceIndex = 0x58C;
    }
}

void Cutscene_OverrideMinuet(void) {
    gSaveContext.eventChkInf[5] |= 0x1;
    ItemOverride_PushDelayedOverride(0x20);
}

void Cutscene_OverrideBolero(void) {
    gSaveContext.eventChkInf[5] |= 0x2;
    ItemOverride_PushDelayedOverride(0x21);
}

u32 Cutscene_SerenadeCheckChestFlag(void) {
    return ((gGlobalContext->actorCtx.flags.chest & 0x4) != 0);
}

void Cutscene_OverrideSerenade(void) {
    gSaveContext.eventChkInf[5] |= 0x4;
    ItemOverride_PushDelayedOverride(0x22);
}

u32 Cutscene_OverrideRequiem(void) {
    if (!EventCheck(0xAC)) {
        ItemOverride_PushDelayedOverride(0x23);
        EventSet(0xAC);
        gSaveContext.entranceIndex = 0x1ED;
    }
    return 1;
}

void Cutscene_OverrideNocturne(void) {
    if ((gEntranceTable[gSaveContext.entranceIndex].scene == 0x52) && (gSaveContext.linkAge == AGE_ADULT)) {
        if ((gSaveContext.questItems & 0x1) && (gSaveContext.questItems & 0x2)
            && (gSaveContext.questItems & 0x4)) {
            if (!EventCheck(0xAA)) {
                ItemOverride_PushDelayedOverride(0x24);
                EventSet(0xAA);
                gSaveContext.entranceIndex = 0x513;
            }
        }
    }
}

u32 Cutscene_OverridePrelude(void) {
    if (gSaveContext.questItems & 0x1) {
        ItemOverride_PushDelayedOverride(0x25);
        gSaveContext.eventChkInf[5] |= 0x20;
        return 1;
    }
    return 0;
}
