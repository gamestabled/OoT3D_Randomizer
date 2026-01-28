#ifndef _CHEST_H_
#define _CHEST_H_

#include "z3D/z3D.h"
#include "z3D/actors/z_en_box.h"

typedef enum {
    CHEST_MAJOR,
    CHEST_JUNK,
    CHEST_BOSS_KEY,
    CHEST_SMALL_KEY,
    CHEST_BOMBCHUS,
    CHEST_HEART,
    CHEST_SKULL,
    CHESTTYPE_MAX,
} ChestType;

void EnBox_rInit(Actor* thisx, GlobalContext* globalCtx);
void EnBox_rUpdate(Actor* thisx, GlobalContext* globalCtx);
void Chest_ChangeAppearance(Actor* thisx, GlobalContext* globalCtx);
u8 Chest_OverrideAnimation();
u8 Chest_OverrideIceSmoke(Actor* thisx);

#endif //_CHEST_H_
