#include "deku_tree_mouth.h"
#include "settings.h"
#include "z3D/z3D.h"

#define BgTreemouth_Init ((ActorFunc)GAME_ADDR(0x2412B4))

void BgTreemouth_rInit(Actor* thisx, GlobalContext* globalCtx) {

    BgTreemouth_Init(thisx, globalCtx);

    // If dungeon entrance randomizer is on, keep the tree's mouth open as adult
    if (EventCheck(0x05) && gSaveContext.linkAge == AGE_ADULT && gSettingsContext.shuffleDungeonEntrances) {
        // This is the address of some float variable the actor uses to calculate where the mouth should be.
        // If it's 0.0f, the mouth is closed. If it's 1.0f, the mouth is open
        f32* unk_1C0 = (f32*)((u32)thisx + sizeof(Actor) + 0x1C);
        *unk_1C0     = 1.0f;
    }
}
