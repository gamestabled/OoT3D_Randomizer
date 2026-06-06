#ifndef _ENEMYSOULS_H_
#define _ENEMYSOULS_H_

#include "s_enemy_souls.h"

#include "z3D/z3D.h"
#include "settings.h"

#define SoullessModels_Enabled                                           \
    (gSettingsContext.soullessEnemiesLook == SOULLESSLOOK_TEXTURELESS || \
     gSettingsContext.soullessEnemiesLook == SOULLESSLOOK_GRAYSCALE)

extern u8 SoullessModels_CmbRestoreRequest;

EnemySoulId EnemySouls_GetSoulId(s16 actorId);
Bool EnemySouls_GetSoulFlag(EnemySoulId soulId);
void EnemySouls_OnCollect(EnemySoulId soulId);
Bool EnemySouls_IsInvulnerable(Actor* actor);
Bool EnemySouls_ShouldDrawSoulless(Actor* actor);
void EnemySouls_Update(void);
void SoullessModels_ModifyGenericCmb(CmbManager* cmbMan);

#endif //_ENEMYSOULS_H_
