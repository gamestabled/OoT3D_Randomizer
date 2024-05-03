#include "settings.h"

#define EnSsh_Update ((ActorFunc)GAME_ADDR(0x1DF0A4))

void EnSsh_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnSsh_Update(thisx, globalCtx);
    if (gSettingsContext.skulltulaHints && thisx->textId == 0x22) {
        thisx->textId = 0x9400 + thisx->params - 1;
    }
}
