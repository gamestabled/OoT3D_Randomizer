#ifndef _SHABOM_H_
#define _SHABOM_H_

#include "z3D/z3D.h"

struct EnBubble;

typedef void (*EnBubbleActionFunc)(struct EnBubble*, GlobalContext*);

typedef struct EnBubble {
    /* 0x0000 */ Actor actor;
    /* 0x01A4 */ EnBubbleActionFunc actionFunc;
    /* 0x01A8 */ Collider collider; // part of ColliderJntSph colliderSphere;
    /* 0x01C0 */ char unk_1C0[0x114];
    /* 0x02D4 */ SkeletonAnimationModel* saModel;
    /* 0x02D8 */ char unk_2D8[0x008];
} EnBubble;
_Static_assert(sizeof(EnBubble) == 0x2E0, "EnBubble size");

void EnBubble_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBubble_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnBubble_Disappear(EnBubble* this, GlobalContext* globalCtx);
void EnBubble_Pop(EnBubble* this, GlobalContext* globalCtx);

void EnBubble_ReinitModels(EnBubble* this);

#endif //_SHABOM_H_
