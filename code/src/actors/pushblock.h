#ifndef _PUSHBLOCK_H_
#define _PUSHBLOCK_H_

#include "z3D/z3D.h"

void ObjOshihiki_rUpdate(Actor* thisx, GlobalContext* globalCtx);

typedef struct {
    Vec3f focusPos;
    Vec3f worldPos;
} BgSpot15Rrbox_SendData;

void BgSpot15Rrbox_rUpdate(Actor* thisx, GlobalContext* globalCtx);

#endif //_PUSHBLOCK_H_
