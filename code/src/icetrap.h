#ifndef _ICETRAP_H_
#define _ICETRAP_H_

#include "z3D/z3D.h"

extern s8 IceTrap_ActiveCurse;

void IceTrap_Push(u32 key);
void IceTrap_Give(void);
u32 IceTrap_IsPending(void);
void IceTrap_Update(void);
u8 IceTrap_ActivateCurseTrap(s8 curseType);
void IceTrap_DispelCurses(void);

typedef enum {
    ICETRAP_CURSE_SHIELD,
    ICETRAP_CURSE_SWORD,
    ICETRAP_CURSE_DIZZY,
    ICETRAP_CURSE_BLIND,
} IceTrapCurses;

#endif //_ICETRAP_H_
