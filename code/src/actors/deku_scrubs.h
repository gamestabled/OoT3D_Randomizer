#ifndef _DEKU_SCRUBS_H_
#define _DEKU_SCRUBS_H_

#include "z3D/z3D.h"

/*-------------------------------
|           EnDntNomal          |
-------------------------------*/

struct EnDntNomal;

typedef void (*EnDntNomalActionFunc)(struct EnDntNomal* this, GlobalContext* globalCtx);

typedef struct EnDntNomal {
    /* 0x000 */ Actor base;
    /* 0x1A4 */ EnDntNomalActionFunc actionFunc;
    /* 0x1A8 */ char unk_1A8[0x40];
    /* 0x1E8 */ s16 timer1;
    /* 0x1EA */ s16 timer2;
    /* 0x1EC */ s16 timer4;
    /* 0x1EE */ s16 timer5;
    /* 0x1F0 */ s16 blinkTimer;
    /* 0x1F2 */ s16 unkCounter;
    /* 0x1F4 */ s16 timer3;
    /* 0x1F6 */ char unk_1F6[0x702];
} EnDntNomal;
_Static_assert(sizeof(EnDntNomal) == 0x8F8, "EnDntNomal size");

void EnDntNomal_rUpdate(Actor* thisx, GlobalContext* globalCtx);

/*-------------------------------
|           EnHintnuts          |
-------------------------------*/

typedef struct EnHintnuts {
    /* 0x0000 */ Actor actor;
    /* 0x01A4 */ char unk_1A4[0x008];
    /* 0x01AC */ u16 textIdCopy;
    /* 0x01B0 */ char unk_1B0[0x400];
    /* 0x05B0 */ SkelAnime anime;
    /* 0x0634 */ SkeletonAnimationModel* flowerModel;
} EnHintnuts;
_Static_assert(sizeof(EnHintnuts) == 0x638, "EnHintnuts size");

void EnHintnuts_rInit(Actor* thisx, GlobalContext* globalCtx);
void EnHintnuts_ReinitModels(EnHintnuts* this);

/*-------------------------------
|           EnDekunuts          |
-------------------------------*/

typedef struct EnDekunuts {
    /* 0x0000 */ Actor actor;
    /* 0x01A4 */ char unk_1A4[0x064];
    /* 0x0208 */ SkelAnime anime;
    /* 0x028C */ char unk_28C[0x410];
    /* 0x069C */ SkeletonAnimationModel* flowerModel;
} EnDekunuts;
_Static_assert(sizeof(EnDekunuts) == 0x6A0, "EnDekunuts size");

void EnDekunuts_ReinitModels(EnDekunuts* this);

/*-------------------------------
|           EnNutsball          |
-------------------------------*/

typedef struct EnNutsball {
    /* 0x0000 */ Actor actor;
    /* 0x01A4 */ void* actionFunc;
    /* 0x01A8 */ s8 requiredObjectSlot;
    /* 0x01AA */ s16 timer;
    /* 0x01AC */ ColliderCylinder collider;
    /* 0x0204 */ SkeletonAnimationModel* saModel;
} EnNutsball;
_Static_assert(sizeof(EnNutsball) == 0x208, "EnNutsball size");

void EnNutsball_rUpdate(Actor* thisx, GlobalContext* globalCtx);

#endif
