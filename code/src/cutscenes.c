#include "z3D/z3D.h"
#include "item_override.h"
#include "settings.h"
#include "z3D/actors/z_bg_dy_yoseizo.h"
#include <stddef.h>

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

u32 Cutscene_CheckLullabyFlag(void) {
    return ((gSaveContext.eventChkInf[5] & 0x200) != 0);
}

void Cutscene_OverrideLullaby(void) {
    gSaveContext.eventChkInf[5] |= 0x200;
    ItemOverride_PushDelayedOverride(0x26);
    gGlobalContext->nextEntranceIndex = 0x594;
    gGlobalContext->sceneLoadFlag = 0x14;
    PLAYER->actor.draw = NULL;
}

u32 Cutscene_CheckEponasSongFlag(void) {
    return ((gSaveContext.eventChkInf[5] & 0x100) != 0);
}

void Cutscene_OverrideEponasSong(void) {
    gSaveContext.eventChkInf[5] |= 0x100;
    ItemOverride_PushDelayedOverride(0x27);
    gGlobalContext->unk_2B7E = 4;
}

u32 Cutscene_CheckSariasSongFlag(void) {
    return ((gSaveContext.eventChkInf[5] & 0x80) != 0);
}

void Cutscene_OverrideSariasSong(void) {
    if (!(gSaveContext.eventChkInf[5] & 0x80)) {
        ItemOverride_PushDelayedOverride(0x28);
        gSaveContext.eventChkInf[5] |= 0x80;
    }
}

void Cutscene_OverrideSunsSong(void) {
    if (!(gSaveContext.eventChkInf[5] & 0x400)) {
        ItemOverride_PushDelayedOverride(0x29);
        gSaveContext.eventChkInf[5] |= 0x400;
    }
}

void Cutscene_OverrideSongOfTime(Actor* ocarina) {
    ItemOverride_PushDelayedOverride(0x2A);
    gGlobalContext->nextEntranceIndex = 0x50F;
    gGlobalContext->sceneLoadFlag = 0x14;
}

void Cutscene_OverrideSongOfStorms(void) {
    gSaveContext.eventChkInf[6] |= 0x20;
    gSaveContext.eventChkInf[5] |= 0x800;
    ItemOverride_PushDelayedOverride(0x2B);
    gGlobalContext->unk_2B7E = 4;
}

void Cutscene_OverrideFairyReward(BgDyYoseizo* fairy) {
    s16 fairyIdx = fairy->unk_D2C;
    
    if (gGlobalContext->sceneNum == 0x3D) {
        if (!(gSaveContext.itemGetInf[1] & (0x100 << fairyIdx))) {
            ItemOverride_PushDelayedOverride(0x10 + fairyIdx);
            gSaveContext.itemGetInf[1] |= (0x100 << fairyIdx);
        }
    } else if (gGlobalContext->sceneNum == 0x3B) {
        if (!(gGlobalContext->actorCtx.flags.chest & (0x1 << fairyIdx))) {
            ItemOverride_PushDelayedOverride(0x13 + fairyIdx);
            gGlobalContext->actorCtx.flags.chest |= (0x1 << fairyIdx);
        }
    }

    gSaveContext.healthAccumulator = 0x140;
    gSaveContext.magic = gSaveContext.magicLevel * 0x30;
    Actor_Kill(&fairy->actor);
}
