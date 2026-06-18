#include "liftable_rock.h"
#include "settings.h"
#include "multiplayer.h"

void EnIshi_Init(Actor* thisx, GlobalContext* globalCtx);
void EnIshi_Update(Actor* thisx, GlobalContext* globalCtx);

void EnIshi_LiftedUp(EnIshi* this, GlobalContext* globalCtx);

void EnIshi_rInit(Actor* thisx, GlobalContext* globalCtx) {

    EnIshi_Init(thisx, globalCtx);

    // If dungeon entrance randomizer is on, remove the grey boulders that normally
    // block child Link from reaching the Fire Temple entrance.
    s16 type = thisx->params & 0x1;
    if (type == LARGE_ROCK && gSettingsContext.shuffleDungeonEntrances &&
        globalCtx->sceneNum == 0x61) { // Death Mountain Crater scene
        Actor_Kill(thisx);
    }
}

void EnIshi_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnIshi* this = (EnIshi*)thisx;

    EnIshiActionFunc prev_action_fn = this->action_fn;

    EnIshi_Update((Actor*)thisx, globalCtx);

    s16 type = thisx->params & 0x1;
    if (type == LARGE_ROCK && prev_action_fn != this->action_fn && this->action_fn == EnIshi_LiftedUp) {
        Multiplayer_Send_ActorUpdate((Actor*)thisx, NULL, 0);
    }
}
