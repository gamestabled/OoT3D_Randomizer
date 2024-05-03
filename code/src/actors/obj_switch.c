#include "z3D/z3D.h"
#include "obj_switch.h"
#include "settings.h"

#define ObjSwitch_Init ((ActorFunc)GAME_ADDR(0x215A14))

void ObjSwitch_rInit(Actor* thisx, GlobalContext* globalCtx) {

    if (gSettingsContext.spiritTempleDungeonMode == DUNGEONMODE_MQ && globalCtx->sceneNum == 6 // spirit temple
        && thisx->room == 6                            //"shortcut" room with silver blocks
        && gSaveContext.linkAge == 1                   // child
        && globalCtx->actorCtx.flags.swch & 0x00000200 // the block has been pushed in the hole
    ) {
        thisx->world.pos.y += 200;
    }

    ObjSwitch_Init(thisx, globalCtx);
}
