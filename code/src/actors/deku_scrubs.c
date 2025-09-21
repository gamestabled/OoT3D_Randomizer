#include "deku_scrubs.h"
#include "settings.h"

#define EnDntNomal_Update ((ActorFunc)GAME_ADDR(0x280510))

#define EnDntNomal_SetupTargetWalk ((ActorFunc)GAME_ADDR(0x21CED4))
#define EnDntNomal_SetupTargetGivePrize ((ActorFunc)GAME_ADDR(0x2394CC))
#define EnDntNomal_SetupTargetUnburrow ((ActorFunc)GAME_ADDR(0x21CCFC))

#define EnHintnuts_Init ((ActorFunc)GAME_ADDR(0x22AB2C))

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

void EnHintnuts_rInit(Actor* thisx, GlobalContext* globalCtx) {
    EnHintnuts* this = (EnHintnuts*)thisx;

    EnHintnuts_Init(thisx, globalCtx);

    if (Enemizer_IsEnemyRandomized(ENEMY_HINT_DEKU_SCRUB)) {
        thisx->textId = this->textIdCopy = 0x3033; // "B-b-b-boooo hooooo!"
    }
}
