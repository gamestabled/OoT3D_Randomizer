#ifndef _DAMPE_H_
#define _DAMPE_H_

#include "z3D/z3D.h"

/*-------------------------------
|              EnTk             |
-------------------------------*/

typedef struct EnTk {
    /* 0x000 */ char unk_000[0xBA8];
    /* 0xBA8 */ u32 currentReward;
    /* 0xBAC */ char unk_BAC[0x654];
} EnTk;
_Static_assert(sizeof(EnTk) == 0x1200, "EnTk size");

void EnTk_rUpdate(Actor* thisx, GlobalContext* globalCtx);

/*-------------------------------
|           EnPoRelay           |
-------------------------------*/

typedef struct EnPoRelay {
    /* 0x000 */ char unk_000[0xB1C];
    /* 0xB1C */ u8 isSecondRace;
    /* 0xB1D */ char unk_B1D[0x253];
} EnPoRelay;
_Static_assert(sizeof(EnPoRelay) == 0xD70, "EnPoRelay size");

void EnPoRelay_rDestroy(Actor* thisx, GlobalContext* globalCtx);

#endif //_DAMPE_H_
