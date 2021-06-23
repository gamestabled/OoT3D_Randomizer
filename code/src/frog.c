#include "z3D/z3D.h"
#include "z3D/actors/z_en_fr.h"
#include "settings.h"

void EnFr_rSetReward(EnFr* frog) {
    if (frog->songIndex == FROG_STORMS) {
        frog->reward = GI_HEART_PIECE;
    } else {
        frog->reward = GI_HEART_PIECE_WIN;
    }
}
