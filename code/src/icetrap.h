#ifndef _ICETRAP_H_
#define _ICETRAP_H_

#include "../include/z3D/z3D.h"

#define CURSETRAP_TEXT_BASE_INDEX 0x8FF0

extern s8 IceTrap_ActiveCurse;
extern u32 possibleChestTraps[20];
extern u32 possibleChestTrapsAmount;
extern u32 dizzyCurseSeed;

void IceTrap_Push(u32 key);
void IceTrap_Give(void);
u32 IceTrap_IsPending(void);
void IceTrap_Update(void);
void IceTrap_InitTypes(void);
u8 IceTrap_ActivateCurseTrap(u8 curseType);
void IceTrap_DispelCurses(void);
u16 IceTrap_CamRoll(u16 roll);

typedef enum {
    ICETRAP_FIRE,
    ICETRAP_KNOCKDOWN,
    ICETRAP_ZELDA2_KNOCKBACK,
    ICETRAP_VANILLA,
    ICETRAP_SHOCK,
    ICETRAP_BOMB_SIMPLE,
    ICETRAP_BOMB_KNOCKDOWN,
    ICETRAP_ANTIFAIRY,
    ICETRAP_RUPPY, // Explosive Rupee
    ICETRAP_SCALE,
    ICETRAP_CURSE_SHIELD,
    ICETRAP_CURSE_SWORD,
    ICETRAP_CURSE_DIZZY,
    ICETRAP_CURSE_BLIND,
    ICETRAP_CURSE_SLOW,
    ICETRAP_CURSE_CROOKED,
    ICETRAP_CURSE_UNSTABLE,
} IceTrapTypes;

#endif //_ICETRAP_H_
