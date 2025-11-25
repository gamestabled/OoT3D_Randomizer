#include "z3D/z3D.h"
#include "common.h"

u8 isObjMure3Updating   = 0;    // global variable for rupee circle rupee replacement.
u8 extraCollectibleFlag = 0x40; // global variable for rupee circle rupee replacement.
#define ObjMure3_Update ((ActorFunc)GAME_ADDR(0x002318ac))

void ObjMure3_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    extraCollectibleFlag = 0x40;
    isObjMure3Updating   = TRUE;
    ObjMure3_Update(thisx, globalCtx);
    isObjMure3Updating = FALSE;
}
