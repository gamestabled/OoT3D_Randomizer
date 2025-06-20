#ifndef _MOBLIN_H_
#define _MOBLIN_H_

#include "z3D/z3D.h"

#define ENMB_ATTACK_CLUB_RIGHT 1
#define ENMB_ATTACK_CLUB_MIDDLE 2
#define ENMB_ATTACK_CLUB_LEFT 3

struct EnMb;

typedef void (*EnMbActionFunc)(struct EnMb*, GlobalContext*);

typedef struct EnMb {
    /* 0x0000 */ Actor actor;
    /* 0x01A4 */ char unk_1A4[0x040];
    /* 0x01E4 */ SkelAnime skelAnime;
    /* 0x0268 */ char unk_268[0x688];
    /* 0x08F0 */ EnMbActionFunc actionFunc;
    /* 0x08F4 */ char unk_8F4[0x00E];
    /* 0x0902 */ s16 attack;
    /* 0x0904 */ char unk_904[0x02C];
    /* 0x0930 */ f32 playerDetectionRange;
    /* 0x0934 */ char unk_934[0x278];
} EnMb; // size = 0xBAC
_Static_assert(sizeof(EnMb) == 0xBAC, "EnMb size");

void EnMb_rInit(Actor* thisx, GlobalContext* globalCtx);
void EnMb_rUpdate(Actor* thisx, GlobalContext* globalCtx);

#endif //_MOBLIN_H_
