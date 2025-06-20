#ifndef _DODONGOS_H_
#define _DODONGOS_H_

#include "z3D/z3D.h"

struct EnDodongo;
struct EnDodojr;

typedef void (*EnDodongoActionFunc)(struct EnDodongo*, GlobalContext*);
typedef void (*EnDodojrActionFunc)(struct EnDodojr*, GlobalContext*);

#define EnDodojr_DropItem ((EnDodojrActionFunc)GAME_ADDR(0x3B7C64))

typedef struct EnDodongo {
    /* 0x0000 */ Actor base;
    /* 0x01A4 */ SkelAnime skelAnime;
    /* 0x0228 */ char unk_228[0x750];
    /* 0x0978 */ s32 actionState;
    /* 0x097C */ EnDodongoActionFunc actionFunc;
    /* 0x0980 */ char unk_980[0x47C];
} EnDodongo; // size = 0xDFC
_Static_assert(sizeof(EnDodongo) == 0xDFC, "EnDodongo size");

typedef struct EnDodojr {
    /* 0x0000 */ Actor base;
    /* 0x01A4 */ SkelAnime skelAnime;
    /* 0x0228 */ char unk_228[0x270];
    /* 0x0498 */ EnDodojrActionFunc actionFunc;
    /* 0x049C */ char unk_49C[0x058];
    /* 0x04F4 */ Actor* bomb;
    /* 0x04F8 */ char unk_4F8[0x018];
    /* 0x0510 */ s16 counter; // Used for bouncing and flashing when dying.
    /* 0x0512 */ char unk_512[0x00D];
} EnDodojr; // size = 0x520
_Static_assert(sizeof(EnDodojr) == 0x520, "EnDodojr size");

void EnDodojr_rInit(Actor* thisx, GlobalContext* globalCtx);

#endif //_DODONGOS_H_
