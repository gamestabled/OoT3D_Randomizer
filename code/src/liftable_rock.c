#include "liftable_rock.h"
#include "settings.h"

#define EnIshi_Init_addr 0x1B5460
#define EnIshi_Init ((ActorFunc)EnIshi_Init_addr)

void EnIshi_rInit(Actor* thisx, GlobalContext* globalCtx) {

    EnIshi_Init(thisx, globalCtx);

    //If dungeon entrance randomizer is on, remove the grey boulders that normally
    //block child Link from reaching the Fire Temple entrance.
    s16 type = thisx->params & 0x1;
    if (type == LARGE_ROCK && gSettingsContext.shuffleDungeonEntrances && globalCtx->sceneNum == 0x61) { //Death Mountain Crater scene
        Actor_Kill(thisx);
    }

}
