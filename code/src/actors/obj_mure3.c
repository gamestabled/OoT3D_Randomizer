#include "z3D/z3D.h"
#include "common.h"

u8 isObjMure3Updating   = 0; // global var
u8 extraCollectibleFlag = 0;
#define ObjMure3_Update ((ActorFunc)GAME_ADDR(0x002318ac))

void ObjMure3_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    isObjMure3Updating = TRUE;
    ObjMure3_Update(thisx, globalCtx);
    isObjMure3Updating = FALSE;
}