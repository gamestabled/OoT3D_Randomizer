#include "carpenter.h"
#include "multiplayer.h"

void EnToryo_SetTradedSawFlag(void) {
    gSaveContext.itemGetInf[3] |= 0x4;
}

void EnDaiku_Update(Actor* thisx, GlobalContext* globalCtx);

void EnDaiku_WaitFreedom(EnDaiku* this, GlobalContext* globalCtx);
void EnDaiku_InitEscape(EnDaiku* this, GlobalContext* globalCtx);
void EnDaiku_EscapeRotate(EnDaiku* this, GlobalContext* globalCtx);

void EnDaiku_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnDaiku* this = (EnDaiku*)thisx;

    EnDaikuActionFunc prev_action_fn = this->action_fn;

    EnDaiku_Update(thisx, globalCtx);

    if (prev_action_fn == EnDaiku_WaitFreedom && this->action_fn == EnDaiku_InitEscape) {
        Multiplayer_Send_ActorUpdate((Actor*)thisx, NULL, 0);
    }
}

void EnDaiku_StartEscape(EnDaiku* this) {
    if (this->action_fn != EnDaiku_WaitFreedom) {
        return;
    }
    Actor_Kill(&this->base);
    // TODO: Start escape instead
    // thisx->action_fn = EnDaiku_EscapeRotate;
}
