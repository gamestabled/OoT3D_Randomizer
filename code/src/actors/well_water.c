#include "well_water.h"
#include "settings.h"

// This actor is the water that blocks getting into Bottom of the Well as child
#define BgSpot01Idomizu_Init ((ActorFunc)GAME_ADDR(0x2AC704))

void BgSpot01Idomizu_rInit(Actor* thisx, GlobalContext* globalCtx) {

    BgSpot01Idomizu_Init(thisx, globalCtx);

    // Address of this actor's water height variable
    f32* waterHeight = (f32*)((u32)thisx + sizeof(Actor) + 0x04);

    // If dungeon entrance randomizer is on, tie the water being lowered to
    // whether child has drained the well regardless of age. This means that
    // the well water will be raised as adult Link until it's lowered as child.
    if (gSettingsContext.shuffleDungeonEntrances) {
        if (EventCheck(0x67)) {
            *waterHeight = -550.0f;
        } else {
            *waterHeight       = 52.0f;
            thisx->world.pos.y = 52.0f; // without this, the water spawns low and rises up
        }
    }
}
