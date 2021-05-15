#ifndef _TOKEN_H_
#define _TOKEN_H_

#include "z3D/z3D.h"
#include "z3D/actors/z_en_si.h"

void EnSi_rInit(Actor* token, GlobalContext* globalCtx);
void EnSi_rDestroy(Actor* token, GlobalContext* globalCtx);
void EnSi_rDraw(Actor* token, GlobalContext* globalCtx);

#endif //_TOKEN_H_
