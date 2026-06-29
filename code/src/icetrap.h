#ifndef _ICETRAP_H_
#define _ICETRAP_H_

#include "z3D/z3D.h"

struct ItemOverride;

typedef enum IceTrapType : s8 {
    ICETRAP_NONE = -1,
    ICETRAP_FIRE,
    ICETRAP_KNOCKDOWN,
    ICETRAP_ZELDA2_KNOCKBACK,
    ICETRAP_VANILLA,
    ICETRAP_SHOCK,
    ICETRAP_BOMB_SIMPLE,
    ICETRAP_BOMB_KNOCKDOWN,
    ICETRAP_ANTIFAIRY,
    ICETRAP_RUPOOR,
    ICETRAP_RUPPY, // Explosive Rupee
    ICETRAP_SCALE,
    ICETRAP_CURSE_SHIELD,
    ICETRAP_CURSE_SWORD,
    ICETRAP_CURSE_DIZZY,
    ICETRAP_CURSE_INVISIBLE_TERRAIN,
    ICETRAP_CURSE_INVISIBLE_ACTORS,
    ICETRAP_CURSE_SLOW,
    ICETRAP_CURSE_NAVI,
    ICETRAP_CURSE_CROOKED,
    ICETRAP_CURSE_UNSTABLE,
    ICETRAP_MAX,
} IceTrapType;

extern IceTrapType IceTrap_ActiveCurse;
extern u32 IceTrap_ActiveHash;

void IceTrap_Push(void);
IceTrapType IceTrap_GetType(u32 hash, Bool isFromChest);
void IceTrap_UpdateOverride(struct ItemOverride* override, Bool isFromChest);
void IceTrap_Give(void);
Bool IceTrap_IsPending(void);
void IceTrap_Update(void);
void IceTrap_Init(void);
void IceTrap_ActivateCurseTrap(IceTrapType curseType);
void IceTrap_DispelCurses(void);
u16 IceTrap_CamRoll(u16 roll);
void IceTrap_HandleNaviCurse(void);

#endif //_ICETRAP_H_
