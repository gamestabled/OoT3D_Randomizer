#ifndef _CHEST_H_
#define _CHEST_H_

#include "z3D/z3D.h"

typedef struct EnBox {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x01BC */ SkelAnime skelAnime;
    /* 0x0240 */ char unk_240[0x148];
    /* 0x0388 */ ZARInfo* zarInfo;
    /* 0x038C */ char unk_38C[0xC];
} EnBox; // size = 0x398

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
u8 Chest_OverrideAnimation();
u8 Chest_OverrideIceSmoke(Actor* thisx);

#endif //_CHEST_H_
