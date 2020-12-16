#include "settings.h"

SettingsContext gSettingsContext = {0};

s32 Settings_ApplyDamageMultiplier(GlobalContext* globalCtx, s32 changeHealth) {
    s32 modifiedChangeHealth = changeHealth;
    
    if (changeHealth < 0) {
        switch (gSettingsContext.damageMultiplier) {
            case DAMAGEMULTIPLIER_HALF:
                modifiedChangeHealth /= 2;
                break;
            case DAMAGEMULTIPLIER_DEFAULT:
                break;
            case DAMAGEMULTIPLIER_DOUBLE:
                modifiedChangeHealth *= 2;
                break;
            case DAMAGEMULTIPLIER_QUADRUPLE:
                modifiedChangeHealth *= 4;
                break;
            case DAMAGEMULTIPLIER_OHKO:
                modifiedChangeHealth = -1000;
                break;
        }
    }

    return modifiedChangeHealth;
}
