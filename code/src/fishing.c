#include "z3D/z3D.h"

u32 isFishing(void) {
    return gSaveContext.equips.buttonItems[0] == ITEM_FISHING_POLE && gGlobalContext->sceneNum == 73;
}
