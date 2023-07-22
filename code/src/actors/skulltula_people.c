#include "settings.h"

#define EnSsh_Update_addr 0x1DF0A4
#define EnSsh_Update ((ActorFunc)EnSsh_Update_addr)

void EnSsh_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnSsh_Update(thisx, globalCtx);
    if (gSettingsContext.skulltulaHints && thisx->textId == 0x22) {
        thisx->textId = 0x9400 + thisx->params - 1;
    }
}
