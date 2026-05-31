#include "shabom.h"
#include "settings.h"
#include "enemy_souls.h"

u16 Shabom_CheckEnemySoul(void) {
    return gSettingsContext.shuffleEnemySouls != SHUFFLEENEMYSOULS_ALL || EnemySouls_GetSoulFlag(SOUL_SHABOM);
}

void EnBubble_ReinitModels(EnBubble* this) {
    Actor_DestroySkelModels(&this->actor, &this->saModel, NULL);
    Actor_CreateSkelModels(&this->actor, gGlobalContext, &this->saModel, 0, NULL);
}
