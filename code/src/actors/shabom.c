#include "z3D/z3D.h"
#include "stddef.h"
#include "shabom.h"
#include "settings.h"
#include "enemy_souls.h"

u16 Shabom_CheckEnemySoul(void) {
    return gSettingsContext.shuffleEnemySouls == OFF || EnemySouls_GetSoulFlag(SOUL_SHABOM);
}

// This is currently useless because soulless enemies are invisible
// void EnBubble_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
//     EnBubble* this = (EnBubble*)thisx;

//     EnBubble_Update(thisx, globalCtx);

//     // If the Shabom explodes but its Soul has not been collected, set up its unused functions that make it regrow
//     if (!EnemySouls_CheckSoulForActor(thisx) && this->base.update == NULL) {
//         this->actionFunc = EnBubble_Disappear;

//         // Undo Actor_Kill
//         this->base.draw   = EnBubble_Draw;
//         this->base.update = EnBubble_rUpdate;
//         this->base.flags |= 0x1;
//     }
// }
