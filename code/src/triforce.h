#ifndef _TRIFORCE_H_
#define _TRIFORCE_H_

#include "z3D/z3D.h"

enum TriforceWarp {
    TRIFORCEWARP_OFF,
    TRIFORCEWARP_WHEN_TEXT_COMPLETE, // wait for text completion, then signal NPCs from hook, then warp
    TRIFORCEWARP_WHEN_PLAYER_READY,  // wait for player is ready, then warp
};

extern u8 TriforceWarpStatus;

void Triforce_HandleCreditsWarp(void);

#endif //_TRIFORCE_H_
