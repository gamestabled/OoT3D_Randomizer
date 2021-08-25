#include "z3D/z3D.h"

void EnMk_SetTradedEyeballFrogFlag(void) {
    gSaveContext.itemGetInf[3] |= 0x20;
}
