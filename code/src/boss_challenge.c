#include "z3D/z3D.h"
#include "multiplayer.h"

#define STONES_MEDALLIONS_BITMASK 0x001C003F
#define bossChallengeData ((void*)GAME_ADDR(0x5C3F58))
#define bossVictories ((u32*)(bossChallengeData + 0x1C))

static u32 ownedStonesMedallions = 0;
static u8 enteredBCmenu          = 0;

// Called from the menu init function.
// It unlocks all battles by giving all stones/medallions and at least 1 victory per boss.
void BossChallenge_Enter(void) {
    if (!enteredBCmenu) {
        enteredBCmenu         = 1;
        ownedStonesMedallions = gSaveContext.questItems & STONES_MEDALLIONS_BITMASK;
        gSaveContext.questItems |= STONES_MEDALLIONS_BITMASK;

        for (s32 i = 0; i < 8; i++) {
            gSaveContext.bossBattleVictories[i]++;
        }
    }
}

void BossChallenge_ExitMenu(s32 exitType) {
    if (exitType < 0) {
        // Exiting menu to Link's House.
        // Restore the save context variables that were modified by BossChallenge_Enter.
        gSaveContext.questItems = (gSaveContext.questItems & ~STONES_MEDALLIONS_BITMASK) | ownedStonesMedallions;
        for (s32 i = 0; i < 8; i++) {
            gSaveContext.bossBattleVictories[i]--;
        }
        Multiplayer_OnFileLoad();
        enteredBCmenu = 0;
    } else {
        // Exiting menu to a boss battle.
        gSaveContext.eventChkInf[0x7] |= 0x01FF; // began boss battles
    }
}
