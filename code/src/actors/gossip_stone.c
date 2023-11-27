#include "gossip_stone.h"
#include "z3D/z3D.h"

#define EnGs_Init_addr 0x16461C
#define EnGs_Init ((ActorFunc)EnGs_Init_addr)

void EnGs_rInit(Actor* thisx, GlobalContext* globalCtx) {

    // if this is a generic grotto gossip stone then assign it a message ID
    // based off of the current respawn data. This allows these stones to all have
    // unique hints.
    if ((thisx->params & 0xFF) == 0x18) {

        u8 id = (gSaveContext.respawn[RESPAWN_MODE_RETURN].data & 0xF) + 0x30;

        thisx->params &= 0x00;
        thisx->params |= id;
    }

    EnGs_Init(thisx, globalCtx);
}
