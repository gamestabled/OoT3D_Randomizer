#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include "s_settings.h"

#include "z3D/z3D.h"

extern SettingsContext gSettingsContext;
extern const char hashIconNames[32][25];

s32 Settings_ApplyDamageMultiplier(GlobalContext*, s32);
void Settings_SkipSongReplays();

#endif
