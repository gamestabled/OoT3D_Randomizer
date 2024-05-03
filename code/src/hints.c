#include "z3D/z3D.h"
#include "settings.h"

#define MASK_OF_TRUTH_ID 8
#define MAX_SARIAS_SONG_HINTS 64

#define SCENE_YDAN_BOSS 17

typedef u8 (*Player_GetMask_proc)(GlobalContext* globalCtx);
#define Player_GetMask ((Player_GetMask_proc)GAME_ADDR(0x36EF98))

typedef u16 (*ElfMessage_GetSariaText_proc)(GlobalContext* globalCtx);
#define ElfMessage_GetSariaText ((ElfMessage_GetSariaText_proc)GAME_ADDR(0x31C698))

u16 sSariasSongHintTextIds[MAX_SARIAS_SONG_HINTS] = { 0x0A00 };
s32 sNumSariasSongHints                           = 1;
s32 sCurSariasSongHint                            = 0;
s32 sSariasSongHintsLoaded                        = 0;

u8 Hints_CanReadHints(void) {
    return (gSettingsContext.gossipStoneHints == HINTS_NEED_NOTHING) ||
           ((gSettingsContext.gossipStoneHints == HINTS_NO_HINTS ||
             gSettingsContext.gossipStoneHints == HINTS_MASK_OF_TRUTH) &&
            Player_GetMask(gGlobalContext) == MASK_OF_TRUTH_ID) ||
           (gSettingsContext.gossipStoneHints == HINTS_SHARD_OF_AGONY && (gSaveContext.questItems >> 21) & 0x1);
}

u8 Hints_GetHintsSetting(void) {
    return gSettingsContext.gossipStoneHints;
}

void Hints_AddSariasSongHint(u16 textId) {
    if ((textId & 0xFF00) != 0xA00) { // Skip non-hint texts from Gossip Stones
        return;
    }
    u8 textIdSceneOffset = (textId & 0xF0) >> 4;
    u8 textIdLookupBit   = textId & 0xF;

    if (gSaveContext.sceneFlags[SCENE_YDAN_BOSS + textIdSceneOffset].unk & (1 << textIdLookupBit)) {
        return;
    }

    gSaveContext.sceneFlags[SCENE_YDAN_BOSS + textIdSceneOffset].unk |= (1 << textIdLookupBit);

    if (sNumSariasSongHints >= MAX_SARIAS_SONG_HINTS) {
        return;
    } else {
        sSariasSongHintTextIds[sNumSariasSongHints] = textId;
        sNumSariasSongHints++;
    }
}

void Hints_LoadSariasSongHints(void) {
    for (u8 i = 0; i < 0x40; i++) {
        u8 textIdSceneOffset = (i & 0xF0) >> 4;
        u8 textIdLookupBit   = i & 0xF;

        if (gSaveContext.sceneFlags[SCENE_YDAN_BOSS + textIdSceneOffset].unk & (1 << textIdLookupBit)) {
            sSariasSongHintTextIds[sNumSariasSongHints] = 0xA00 + i;
            sNumSariasSongHints++;
        }
    }

    sSariasSongHintsLoaded = 1;
}

u16 Hints_GetNextSariasSongHint(GlobalContext* globalCtx) {
    if (gSettingsContext.gossipStoneHints == HINTS_NO_HINTS) {
        return ElfMessage_GetSariaText(globalCtx);
    }

    if (!sSariasSongHintsLoaded) {
        Hints_LoadSariasSongHints();
    }

    u16 textId = sSariasSongHintTextIds[sCurSariasSongHint];

    sCurSariasSongHint++;
    if (sCurSariasSongHint >= sNumSariasSongHints) {
        sCurSariasSongHint = 0;
    }

    return textId;
}
