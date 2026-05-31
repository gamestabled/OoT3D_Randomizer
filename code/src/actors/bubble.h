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
    /* 0x1A4 */ SkelAnime anime;
    /* 0x228 */ char unk_228[0x2D8];
    /* 0x500 */ FlameModelData flameModel_1;
    /* 0x50C */ FlameModelData flameModel_2;
    /* 0x518 */ char unk_518[0x18];
    /* 0x530 */ s32 moveMode;
    /* 0x534 */ char unk_534[0x30];
    /* 0x564 */ Vec3f waypointPos;
    /* 0x570 */ u8 path;
    /* 0x571 */ u8 waypoint;
    /* 0x572 */ u8 flamePrimBlue; // unused?
    /* 0x573 */ u8 flamePrimAlpha;
    /* 0x574 */ struct { u8 r, g, b; } flameEnvColor; // unused?
    /* 0x577 */ u8 hasSecondFlameModel;
    /* 0x578 */ s32 blureIdx;
    /* 0x57C */ char unk_57C[0x8C];
} EnBb;
_Static_assert(sizeof(EnBb) == 0x608, "EnBb size");

void EnBb_rInit(Actor* thisx, GlobalContext* globalCtx);
void EnBb_rUpdate(Actor* thisx, GlobalContext* globalCtx);
void EnBb_rDestroy(Actor* thisx, GlobalContext* globalCtx);

void EnBb_ReinitModels(EnBb* this);

#endif //_BUBBLE_H_
