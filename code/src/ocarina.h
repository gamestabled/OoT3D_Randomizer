#ifndef _OCARINA_H_
#define _OCARINA_H_

#include "z3D/z3D.h"
#include "z3D/actors/z_item_ocarina.h"

void ItemOcarina_rInit(Actor* ocarina, GlobalContext* globalCtx);
void ItemOcarina_rDestroy(Actor* ocarina, GlobalContext* globalCtx);
void ItemOcarina_rDraw(Actor* ocarina, GlobalContext* globalCtx);

#endif //_OCARINA_H_
