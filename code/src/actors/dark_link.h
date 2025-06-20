#ifndef _DARK_LINK_H_
#define _DARK_LINK_H_

#include "z3D/z3D.h"

enum EnTorch2ActionState {
    ENTORCH2_WAIT,
    ENTORCH2_ATTACK,
    ENTORCH2_DEATH,
    ENTORCH2_DAMAGE,
};

typedef struct EnTorch2 {
    /* 0x0000 */ Player darkPlayer;
    /* 0x2A4C */ Vec3f spawnPoint;
    /* 0x2A58 */ char unk_2A58[0x45];
    /* 0x2A9D */ u8 actionState;
    /* 0x2A9E */ char unk_2A9E[0xA];
} EnTorch2;
_Static_assert(sizeof(EnTorch2) == 0x2AA8, "EnTorch2 size");

void EnTorch2_rUpdate(Actor* thisx, GlobalContext* globalCtx);

#endif //_DARK_LINK_H_
