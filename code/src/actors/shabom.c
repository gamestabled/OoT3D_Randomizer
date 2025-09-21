#include "shabom.h"
#include "settings.h"
#include "enemy_souls.h"

u16 Shabom_CheckEnemySoul(void) {
    return gSettingsContext.shuffleEnemySouls != SHUFFLEENEMYSOULS_ALL || EnemySouls_GetSoulFlag(SOUL_SHABOM);
}
