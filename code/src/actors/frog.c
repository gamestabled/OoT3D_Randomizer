#include "z3D/z3D.h"
#include "z3D/actors/z_en_fr.h"
#include "settings.h"

void EnFr_rSetReward(EnFr* frog) {
    if (frog->songIndex < FROG_STORMS) {
        // Shuffled rupee rewards will use the song index as the override flag (+1 to avoid GetItem 0)
        frog->reward =
            gSettingsContext.shuffleFrogSongRupees == SHUFFLEFROGSONGRUPEES_ON ? frog->songIndex + 1 : GI_RUPEE_PURPLE;
    } else if (frog->songIndex == FROG_STORMS) {
        frog->reward = GI_HEART_PIECE;
    } else {
        frog->reward = GI_HEART_PIECE_WIN;
    }
}

void FrogSongTimer_Init(void) {
    for (u8 i = 0; i < ARRAY_SIZE(sTimerFrogSong); i++) {
        sTimerFrogSong[i] = sTimerFrogSong[i] * gSettingsContext.frogSongTimerMultiplier;
    }
}

s16 EnFr_rSetupFrogSongTimerMultiplier(s16 initialFrogTimer) {
    return initialFrogTimer * gSettingsContext.frogSongTimerMultiplier;
}