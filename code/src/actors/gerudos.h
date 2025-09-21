#ifndef _GERUDO_ARCHERY_MANAGER_H_
#define _GERUDO_ARCHERY_MANAGER_H_

#include "z3D/z3D.h"

typedef enum {
    /* 0x00 */ GE1_TYPE_GATE_GUARD,
    /* 0x01 */ GE1_TYPE_GATE_OPERATOR,
    /* 0x02 */ GE1_TYPE_EXTRA_GATE_OPERATOR, // Custom new guard type for the extra gate opener
    /* 0x04 */ GE1_TYPE_NORMAL = 4,
    /* 0x05 */ GE1_TYPE_VALLEY_FLOOR,
    /* 0x45 */ GE1_TYPE_HORSEBACK_ARCHERY = 0x45,
    /* 0x46 */ GE1_TYPE_TRAINING_GROUNDS_GUARD
} EnGe1Type;

typedef struct EnGe1 {
    /* 0x0000 */ Actor actor;
    /* 0x01A4 */ char unk_1A4[0x8E4];
} EnGe1;
_Static_assert(sizeof(EnGe1) == 0xA88, "EnGe1 size");

typedef struct EnGeldB {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ char unk_1A4[0xA6A];
    /* 0xC0E */ s16 spinAttackState;
    /* 0xC10 */ char unk_C10[0x004];
    /* 0xC14 */ s16 invisible;
    /* 0xC16 */ char unk_C16[0x1D6];
} EnGeldB;
_Static_assert(sizeof(EnGeldB) == 0xDEC, "EnGeldB size");

void EnGe1_rInit(Actor* thisx, GlobalContext* globalCtx);
void EnGe1_rUpdate(Actor* thisx, GlobalContext* globalCtx);

void EnGeldB_rUpdate(Actor* thisx, GlobalContext* globalCtx);
void EnGeldB_rDraw(Actor* thisx, GlobalContext* globalCtx);

#endif //_GERUDO_ARCHERY_MANAGER_H_
