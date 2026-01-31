#include "z3D/z3D.h"
#include "common.h"

u8 gIsObjMure3Updating   = 0;    // global variable for rupee circle rupee replacement.
u8 gExtraCollectibleFlag = 0x40; // global variable for rupee circle rupee replacement.
#define ObjMure3_Update ((ActorFunc)GAME_ADDR(0x002318ac))

void ObjMure3_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    gExtraCollectibleFlag = 0x40;
    gIsObjMure3Updating   = TRUE;
    ObjMure3_Update(thisx, globalCtx);
    gIsObjMure3Updating = FALSE;
}
