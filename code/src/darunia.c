#include "z3D/z3D.h"

u32 EnDu_CheckRewardFlag(void) {
    u32 flag = ((gSaveContext.eventChkInf[3] & 0x40) != 0);
    gSaveContext.eventChkInf[3] |= 0x40;
    return flag;
}