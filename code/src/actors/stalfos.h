#ifndef _STALFOS_H
#define _STALFOS_H

#include "z3D/z3D.h"

struct EnTest;

typedef void (*EnTestActionFunc)(struct EnTest*, GlobalContext*);

typedef struct EnTest {
    /* 0x0000 */ Actor actor;
    /* 0x01A4 */ char unk_01A4[0x003C];
    /* 0x01E0 */ SkelAnime skelAnime;
    /* 0x0264 */ SkelAnime upperSkelAnime;
    /* 0x02E8 */ char unk_02E8[0x1968];
    /* 0x1C50 */ EnTestActionFunc actionFunc;
    /* 0x1C54 */ char unk_1C54[0x0178];
} EnTest;
_Static_assert(sizeof(EnTest) == 0x1DCC, "EnTest size");

void EnTest_Wait(EnTest* this, GlobalContext* globalCtx);

void EnTest_rUpdate(Actor* thisx, GlobalContext* globalCtx);
void EnTest_ReinitModels(EnTest* this);

#endif //_STALFOS_H
