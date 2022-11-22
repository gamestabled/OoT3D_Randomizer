#include "carpenter.h"
#include "multiplayer.h"

void EnToryo_SetTradedSawFlag(void) {
    gSaveContext.itemGetInf[3] |= 0x4;
}

#define EnDaiku_Update_addr 0x20F1A8
#define EnDaiku_Update ((ActorFunc)EnDaiku_Update_addr)

#define EnDaiku_WaitFreedom (void*)0x182FF0
#define EnDaiku_InitEscape (void*)0x25A8E4
#define EnDaiku_EscapeRotate (void*)0x2754E4

void EnDaiku_rUpdate(EnDaiku* thisx, GlobalContext* globalCtx) {
    void* prev_action_fn = thisx->action_fn;

    EnDaiku_Update((Actor*)thisx, globalCtx);

    if (prev_action_fn == EnDaiku_WaitFreedom && thisx->action_fn == EnDaiku_InitEscape) {
        Multiplayer_Send_ActorUpdate((Actor*)thisx, NULL, 0);
    }
}

void EnDaiku_StartEscape(EnDaiku* thisx) {
    if (thisx->action_fn != EnDaiku_WaitFreedom) {
        return;
    }
    Actor_Kill((Actor*)thisx);
    // TODO: Start escape instead
    // thisx->action_fn = EnDaiku_EscapeRotate;
}
