#include "settings.h"

void EnSsh_Update(Actor* thisx, GlobalContext* globalCtx);

void EnSsh_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnSsh_Update(thisx, globalCtx);
    if (gSettingsContext.skulltulaHints && thisx->textId == 0x22) {
        thisx->textId = 0x9400 + thisx->params - 1;
    }
}
