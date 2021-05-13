#ifndef _HEART_CONTAINER_H_
#define _HEART_CONTAINER_H_

#include "z3D/z3D.h"
#include "z3D/actors/z_item_b_heart.h"

void ItemBHeart_rInit(Actor* thisx, GlobalContext* globalCtx);
void ItemBHeart_rDestroy(Actor* thisx, GlobalContext* globalCtx);
void ItemBHeart_rDraw(Actor* thisx, GlobalContext* globalCtX);

#endif //_HEART_CONTAINER_H_
