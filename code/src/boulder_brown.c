#include "z3D/z3D.h"

u32 ObjBombiwa_GetFlag(Actor* thisx, GlobalContext* globalCtx) {
    return Flags_GetSwitch(globalCtx, (u16)thisx->params & 0x3F);
}
