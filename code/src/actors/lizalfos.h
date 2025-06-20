#ifndef _LIZALFOS_H_
#define _LIZALFOS_H_

#include "z3D/z3D.h"

#define ENZF_ACTION_DROP_IN 0

struct EnZf;

typedef void (*EnZfActionFunc)(struct EnZf*, GlobalContext*);

typedef struct EnZf {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ char unk_1A4[0x8A4];
    /* 0xA48 */ s32 action;
    /* 0xA4C */ char unk_A4C[0x024];
    /* 0xA70 */ s16 alpha;
    /* 0xA72 */ char unk_A72[0x176];
} EnZf;
_Static_assert(sizeof(EnZf) == 0xBE8, "EnZf size");

void EnZf_rUpdate(Actor* thisx, GlobalContext* globalCtx);

#endif //_LIZALFOS_H_
