#ifndef _POE_COLLECTOR_H_
#define _POE_COLLECTOR_H_

#include "z3D/z3D.h"

// Scene switch flag for the Ghost Shop/Guard House, unused in vanilla
#define POE_REWARD_SWITCH_FLAG 0

struct EnGb;

typedef void (*EnGbActionFunc)(struct EnGb*, GlobalContext*);

typedef struct EnGb {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x1BC */ SkelAnime skelAnime;
    /* 0x240 */ char jointTable[0x208];
    /* 0x448 */ char morphTable[0x208];
    /* 0x650 */ EnGbActionFunc actionFunc;
    /* 0x654 */ char unk_654[0x17C];
    /* 0x7D0 */ u16 textId;
    /* 0x7D2 */ char unk_7D2[0x0CE];
} EnGb;
_Static_assert(sizeof(EnGb) == 0x8A0, "EnGb size");

void EnGb_rUpdate(Actor* thisx, GlobalContext* globalCtx);

#endif //_POE_COLLECTOR_H_
