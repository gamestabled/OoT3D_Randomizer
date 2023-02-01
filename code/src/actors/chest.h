#ifndef _CHEST_H_
#define _CHEST_H_

#include "z3D/z3D.h"

typedef enum {
    WOODEN_BIG,
    WOODEN_SMALL,
    DECORATED_BIG,
    DECORATED_SMALL,
} ChestType;

void EnBox_rInit(Actor* thisx, GlobalContext* globalCtx);
void EnBox_rUpdate(Actor* thisx, GlobalContext* globalCtx);
u8 Chest_OverrideAnimation();
u8 Chest_OverrideDecoration();
u8 Chest_OverrideIceSmoke(Actor* thisx);

#endif //_CHEST_H_
