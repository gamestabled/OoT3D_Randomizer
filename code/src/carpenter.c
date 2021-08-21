#include "z3D/z3D.h"

void EnToryo_SetTradedSawFlag(void) {
    gSaveContext.itemGetInf[3] |= 0x4;
}
