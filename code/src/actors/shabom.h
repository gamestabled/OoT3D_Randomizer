#ifndef _SHABOM_H_
#define _SHABOM_H_

#include "z3D/z3D.h"

struct EnBubble;

typedef void (*EnBubbleActionFunc)(struct EnBubble*, GlobalContext*);

typedef struct EnBubble {
    /* 0x0000 */ Actor base;
    /* 0x01A4 */ EnBubbleActionFunc actionFunc;
    /* 0x01A8 */ Collider collider; // part of ColliderJntSph colliderSphere;
    /* 0x01C0 */ char unk_01C0[0x120];
} EnBubble;

void EnBubble_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBubble_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnBubble_Disappear(EnBubble* this, GlobalContext* globalCtx);
void EnBubble_Pop(EnBubble* this, GlobalContext* globalCtx);

#endif //_SHABOM_H_
