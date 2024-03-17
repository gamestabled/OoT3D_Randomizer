#ifndef _SHABOM_H_
#define _SHABOM_H_

#include "z3D/z3D.h"

struct EnBubble;
typedef void (*EnBubbleActionFunc)(struct EnBubble*, GlobalContext*);

#define EnBubble_Update ((ActorFunc)0x228F24)
#define EnBubble_Draw ((ActorFunc)0X228CB4)
#define EnBubble_Disappear ((EnBubbleActionFunc)0x3B5190)

// void EnBubble_rUpdate(Actor* thisx, GlobalContext* globalCtx);

typedef struct EnBubble {
    /* 0x0000 */ Actor base;
    /* 0x01A4 */ EnBubbleActionFunc actionFunc;
    /* 0x01A8 */ Collider collider; // part of ColliderJntSph colliderSphere;
    /* 0x01C0 */ char unk_01C0[0x120];
} EnBubble;

#endif //_SHABOM_H_
