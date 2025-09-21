#ifndef _BUBBLE_H_
#define _BUBBLE_H_

#include "z3D/z3D.h"

typedef enum EnBbType {
    ENBB_GREEN_BIG = -5,
    ENBB_GREEN,
    ENBB_WHITE,
    ENBB_RED,
    ENBB_BLUE,
    ENBB_FLAME_TRAIL,
    ENBB_KILL_TRAIL = 11,
} EnBbType;

typedef struct EnBb {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ char unk_1A4[0x38C];
    /* 0x530 */ s32 moveMode;
    /* 0x534 */ char unk_534[0x30];
    /* 0x564 */ Vec3f waypointPos;
    /* 0x570 */ u8 path;
    /* 0x571 */ u8 waypoint;
    /* 0x572 */ char unk_572[0x06];
    /* 0x578 */ s32 blureIdx;
    /* 0x57C */ char unk_57C[0x8C];
} EnBb;
_Static_assert(sizeof(EnBb) == 0x608, "EnBb size");

void EnBb_rInit(Actor* thisx, GlobalContext* globalCtx);
void EnBb_rUpdate(Actor* thisx, GlobalContext* globalCtx);
void EnBb_rDestroy(Actor* thisx, GlobalContext* globalCtx);

#endif //_BUBBLE_H_
