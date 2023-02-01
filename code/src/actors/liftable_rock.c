#include "liftable_rock.h"
#include "settings.h"
#include "multiplayer.h"

#define EnIshi_Init_addr 0x1B5460
#define EnIshi_Init ((ActorFunc)EnIshi_Init_addr)

#define EnIshi_Update_addr 0x1F69AC
#define EnIshi_Update ((ActorFunc)EnIshi_Update_addr)

#define EnIshi_LiftedUp (void*)0x3CBAC4

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

void EnIshi_rUpdate(EnIshi* thisx, GlobalContext* globalCtx) {
    void* prev_action_fn = thisx->action_fn;

    EnIshi_Update((Actor*)thisx, globalCtx);

    s16 type = thisx->base.params & 0x1;
    if (type == LARGE_ROCK && prev_action_fn != thisx->action_fn && thisx->action_fn == EnIshi_LiftedUp) {
        Multiplayer_Send_ActorUpdate((Actor*)thisx, NULL, 0);
    }
}
