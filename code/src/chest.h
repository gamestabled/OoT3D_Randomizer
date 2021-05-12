#ifndef _CHEST_H_
#define _CHEST_H_

#include "z3D/z3D.h"

typedef enum {
  VANILLA_SIZE,
  SIZE_MATCHES_CONTENT,
} ChestSize;

typedef enum {
  ALWAYS_FAST,
  ANIMATION_MATCHES_CONTENT,
} ChestAnim;

typedef enum {
  WOODEN_BIG,
  WOODEN_SMALL,
  DECORATED_BIG,
  DECORATED_SMALL,
} ChestType;

void EnBox_rInit(Actor* thisx, GlobalContext* globalCtx);
u8 Chest_OverrideAnimation();
u8 Chest_OverrideDecoration();

#endif //_CHEST_H_
