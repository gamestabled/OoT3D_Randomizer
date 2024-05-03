#include "deku_scrubs.h"

#define EnDntNomal_Update ((ActorFunc)GAME_ADDR(0x280510))

#define EnDntNomal_SetupTargetWalk ((ActorFunc)GAME_ADDR(0x21CED4))
#define EnDntNomal_SetupTargetGivePrize ((ActorFunc)GAME_ADDR(0x2394CC))
#define EnDntNomal_SetupTargetUnburrow ((ActorFunc)GAME_ADDR(0x21CCFC))

void EnDntNomal_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnDntNomal* this = (EnDntNomal*)thisx;

    EnDntNomal_Update(thisx, globalCtx);

    if (this->actionFunc == EnDntNomal_SetupTargetUnburrow && this->timer4 > 1) {
        this->timer4       = 1;
        thisx->shape.rot.y = 0xC000;
    } else if (this->actionFunc == EnDntNomal_SetupTargetWalk) {
        this->actionFunc = EnDntNomal_SetupTargetGivePrize;
    }
}
