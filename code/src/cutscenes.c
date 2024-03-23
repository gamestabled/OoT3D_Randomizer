#include "z3D/z3D.h"
#include "item_override.h"
#include "settings.h"
#include "savefile.h"
#include "entrance.h"
#include "z3D/actors/z_bg_dy_yoseizo.h"
#include <stddef.h>

// Patched over call to Item_Give
void Cutscene_OverrideOcarinaSongs(GlobalContext* GlobalContext, ItemID songId) {
    ItemOverride_PushDelayedOverride(songId - ITEM_SONG_MINUET + 0x20); // TODO remove the hardcoded constant?
}

u32 LACS_ConditionVanilla(void) {
    return ((gSaveContext.questItems & 0x8) && (gSaveContext.questItems & 0x10));
}

u32 LACS_ConditionStones(void) {
    return SaveFile_GetStoneCount() >= gSettingsContext.lacsStoneCount;
}

u32 LACS_ConditionMedallions(void) {
    return SaveFile_GetMedallionCount() >= gSettingsContext.lacsMedallionCount;
}

u32 LACS_ConditionRewards(void) {
    return SaveFile_GetStoneCount() + SaveFile_GetMedallionCount() >= gSettingsContext.lacsRewardCount;
}

u32 LACS_ConditionDungeons(void) {
    return SaveFile_GetDungeonCount() >= gSettingsContext.lacsDungeonCount;
}

u32 LACS_ConditionTokens(void) {
    return gSaveContext.gsTokens >= gSettingsContext.lacsTokenCount;
}

void Cutscene_OverrideLACS(void) {
    u32 conditionMet = 0;

    switch (gSettingsContext.lacsCondition) {
        case LACSCONDITION_VANILLA:
            conditionMet = LACS_ConditionVanilla();
            break;
        case LACSCONDITION_STONES:
            conditionMet = LACS_ConditionStones();
            break;
        case LACSCONDITION_MEDALLIONS:
            conditionMet = LACS_ConditionMedallions();
            break;
        case LACSCONDITION_REWARDS:
            conditionMet = LACS_ConditionRewards();
            break;
        case LACSCONDITION_DUNGEONS:
            conditionMet = LACS_ConditionDungeons();
            break;
        case LACSCONDITION_TOKENS:
            conditionMet = LACS_ConditionTokens();
        case LACSCONDITION_HEARTS:
            conditionMet = gSaveContext.healthCapacity >= gSettingsContext.lacsHeartCount * 16;
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
    if (!EventCheck(0xAC) &&
        Entrance_SceneAndSpawnAre(0x5C, 0x01)) { // Spirit Temple -> Desert Colossus, index 01E1 in the entrance table
        ItemOverride_PushDelayedOverride(0x23);
        EventSet(0xAC);
        gSaveContext.entranceIndex = 0x1ED;
    }
    return 1;
}

void Cutscene_OverrideNocturne(void) {
    if ((gEntranceTable[gSaveContext.entranceIndex].scene == 0x52) && (gSaveContext.linkAge == AGE_ADULT)) {
        if ((gSaveContext.questItems & 0x1) && (gSaveContext.questItems & 0x2) && (gSaveContext.questItems & 0x4)) {
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
    gGlobalContext->sceneLoadFlag     = 0x14;
    PLAYER->actor.draw                = NULL;
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
    gSaveContext.eventChkInf[10] |= 0x200;
    ItemOverride_PushDelayedOverride(0x2A);
    gGlobalContext->nextEntranceIndex = 0x50F;
    gGlobalContext->sceneLoadFlag     = 0x14;
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
    gSaveContext.magic             = gSaveContext.magicLevel * 0x30;
    Actor_Kill(&fairy->actor);
}

// skip dungeon exit cutscenes
void Cutscene_OverrideDekuTree(void) {
    if (EventCheck(0x7) == 0) {
        EventSet(0x7);
        EventSet(0x9);
        ItemOverride_PushDungeonReward(DUNGEON_DEKU_TREE);
        gSaveContext.eventChkInf[0x1] |= 0x1000; // spoke to Mido after Deku Tree's death

        // If warping with FW, let the wrong warp work
        if (gSaveContext.respawnFlag == 3) {
            gSaveContext.nextCutsceneIndex = 0xFFF1;
            return;
        }

        // Skipped if wrong warping
        gSaveContext.nextDayTime = 0x8000;
    }
    gGlobalContext->nextEntranceIndex = Entrance_OverrideNextIndex(0x457);
    gGlobalContext->sceneLoadFlag     = 0x14;
    gGlobalContext->fadeOutTransition = 0xA;
    gSaveContext.nextCutsceneIndex    = 0x0;
}

void Cutscene_OverrideDodongosCavern(void) {
    if (EventCheck(0x25) == 0) {
        EventSet(0x25);
        ItemOverride_PushDungeonReward(DUNGEON_DODONGOS_CAVERN);

        // If warping with FW, let the wrong warp work
        if (gSaveContext.respawnFlag == 3) {
            gSaveContext.nextCutsceneIndex = 0xFFF1;
            return;
        }

        // Skipped if wrong warping
        gSaveContext.nextDayTime = 0x8000;
    }
    gGlobalContext->nextEntranceIndex = Entrance_OverrideNextIndex(0x47A);
    gGlobalContext->sceneLoadFlag     = 0x14;
    gGlobalContext->fadeOutTransition = 0xA;
    gSaveContext.nextCutsceneIndex    = 0x0;
}

void Cutscene_OverrideJabuJabusBelly(void) {
    if (EventCheck(0x37) == 0) {
        EventSet(0x37);
        ItemOverride_PushDungeonReward(DUNGEON_JABUJABUS_BELLY);

        // If warping with FW, let the wrong warp work
        //(this code will never be executed lol)
        if (gSaveContext.respawnFlag == 3) {
            gSaveContext.nextCutsceneIndex = 0xFFF0;
            return;
        }

        // Skipped if wrong warping
        gSaveContext.nextDayTime = 0x8000;
    }
    gGlobalContext->nextEntranceIndex = Entrance_OverrideNextIndex(0x10E);
    gGlobalContext->sceneLoadFlag     = 0x14;
    gGlobalContext->fadeOutTransition = 0xA;
    gSaveContext.nextCutsceneIndex    = 0x0;
}

void Cutscene_OverrideForestTemple(void) {
    if (EventCheck(0x48) == 0) {
        EventSet(0x48);
        ItemOverride_PushDungeonReward(DUNGEON_FOREST_TEMPLE);
        gSaveContext.nextDayTime = 0x8000;
    }

    s16 tempEntr = Entrance_OverrideNextIndex(0x608);
    // If there is no override, use Minuet entrance as child.
    if (gSaveContext.linkAge == AGE_CHILD && tempEntr == 0x608) {
        tempEntr = 0x600;
    }
    gGlobalContext->nextEntranceIndex = tempEntr;
    gGlobalContext->sceneLoadFlag     = 0x14;
    gGlobalContext->fadeOutTransition = 0x3;
    gSaveContext.nextCutsceneIndex    = 0x0;
}

void Cutscene_OverrideFireTemple(void) {
    if (EventCheck(0x49) == 0) {
        EventSet(0x49);
        ItemOverride_PushDungeonReward(DUNGEON_FIRE_TEMPLE);
        gSaveContext.eventChkInf[2] |= 0x8000; // Death Mountain cloud is normal again

        // If warping with FW, let the wrong warp work
        if (gSaveContext.respawnFlag == 3) {
            gSaveContext.nextCutsceneIndex = 0xFFF3;
            return;
        }

        // Skipped if wrong warping
        gSaveContext.nextDayTime = 0x8000;
    }

    s16 tempEntr = Entrance_OverrideNextIndex(0x564);
    // If there is no override, use Bolero entrance as child.
    if (gSaveContext.linkAge == AGE_CHILD && tempEntr == 0x564) {
        tempEntr = 0x4F6;
    }
    gGlobalContext->nextEntranceIndex = tempEntr;
    gGlobalContext->sceneLoadFlag     = 0x14;
    gGlobalContext->fadeOutTransition = 0x3;
    gSaveContext.nextCutsceneIndex    = 0x0;
}

void Cutscene_OverrideWaterTemple(void) {
    if (EventCheck(0x4A) == 0) {
        EventSet(0x4A);
        ItemOverride_PushDungeonReward(DUNGEON_WATER_TEMPLE);
        gSaveContext.eventChkInf[6] |= 0x0200; // Raise Lake Hylia's Water
        gSaveContext.nextDayTime = 0x4000;
    }

    s16 tempEntr = Entrance_OverrideNextIndex(0x60C);
    // If there is no override, use Serenade entrance as child.
    if (gSaveContext.linkAge == AGE_CHILD && tempEntr == 0x60C) {
        tempEntr = 0x604;
    }
    gGlobalContext->nextEntranceIndex = tempEntr;
    gGlobalContext->sceneLoadFlag     = 0x14;
    gGlobalContext->fadeOutTransition = 0x3;
    gSaveContext.nextCutsceneIndex    = 0x0;
}

void Cutscene_OverrideSpiritTemple(void) {
    if (EventCheck(0x47) == 0) {
        EventSet(0x47);
        ItemOverride_PushDungeonReward(DUNGEON_SPIRIT_TEMPLE);
        gSaveContext.nextDayTime = 0x8000;
    }

    s16 tempEntr = Entrance_OverrideNextIndex(0x610);
    // If there is no override, use Requiem entrance as child.
    if (gSaveContext.linkAge == AGE_CHILD && tempEntr == 0x610) {
        tempEntr = 0x1F1;
    }
    gGlobalContext->nextEntranceIndex = tempEntr;
    gGlobalContext->sceneLoadFlag     = 0x14;
    gGlobalContext->fadeOutTransition = 0x3;
    gSaveContext.nextCutsceneIndex    = 0x0;
}

void Cutscene_OverrideShadowTemple(void) {
    if (EventCheck(0x46) == 0) {
        EventSet(0x46);
        ItemOverride_PushDungeonReward(DUNGEON_SHADOW_TEMPLE);
        gSaveContext.nextDayTime = 0x8000;
    }

    s16 tempEntr = Entrance_OverrideNextIndex(0x580);
    // If there is no override, use Nocturne entrance as child.
    if (gSaveContext.linkAge == AGE_CHILD && tempEntr == 0x580) {
        tempEntr = 0x568;
    }
    gGlobalContext->nextEntranceIndex = tempEntr;
    gGlobalContext->sceneLoadFlag     = 0x14;
    gGlobalContext->fadeOutTransition = 0x3;
    gSaveContext.nextCutsceneIndex    = 0x0;
}

void Cutscene_BlueWarpOverride(void) {
    // Set nextEntranceIndex as a flag so that Grotto_CheckSpecialEntrance
    // won't return index 0x7FFF, which can't work to override blue warps.
    gGlobalContext->nextEntranceIndex = 0;
    switch (gGlobalContext->sceneNum - 0x11) { // dungeon index from boss room scene
        case DUNGEON_DEKU_TREE:
            Cutscene_OverrideDekuTree();
            break;
        case DUNGEON_DODONGOS_CAVERN:
            Cutscene_OverrideDodongosCavern();
            break;
        case DUNGEON_JABUJABUS_BELLY:
            Cutscene_OverrideJabuJabusBelly();
            break;
        case DUNGEON_FOREST_TEMPLE:
            Cutscene_OverrideForestTemple();
            break;
        case DUNGEON_FIRE_TEMPLE:
            Cutscene_OverrideFireTemple();
            break;
        case DUNGEON_WATER_TEMPLE:
            Cutscene_OverrideWaterTemple();
            break;
        case DUNGEON_SPIRIT_TEMPLE:
            Cutscene_OverrideSpiritTemple();
            break;
        case DUNGEON_SHADOW_TEMPLE:
            Cutscene_OverrideShadowTemple();
            break;
    }
}
