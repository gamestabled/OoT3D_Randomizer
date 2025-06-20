#ifndef _SKULL_KID_H_
#define _SKULL_KID_H_

#include "z3D/z3D.h"

struct EnSkj;

typedef void (*EnSkjActionFunc)(struct EnSkj*, GlobalContext*);

typedef struct EnSkj {
    /* 0x0000 */ Actor actor;
    /* 0x01A4 */ SkelAnime skelAnime;
    /* 0x0228 */ char unk_228[0x784];
    /* 0x09AC */ EnSkjActionFunc actionFunc;
    /* 0x09B0 */ char unk_9B0[0x65];
    /* 0x0A15 */ u8 action;
    /* 0x0A16 */ u8 backflipFlag;
    /* 0x0A17 */ char unk_A17[0x31];
} EnSkj;
_Static_assert(sizeof(EnSkj) == 0xA48, "EnSkj size");

void EnSkj_rUpdate(Actor* thisx, GlobalContext* globalCtx);

#endif //_SKULL_KID_H_
