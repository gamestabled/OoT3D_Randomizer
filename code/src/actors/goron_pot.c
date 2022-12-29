#include "goron_pot.h"

void BgSpot18Basket_SetRotation(GoronPot* this) {
    if (!this->dropped_reward && !Flags_GetCollectible(gGlobalContext, this->base.params & 0x3F)) {
        // The result is based on the pot's y rotation when the bomb explodes
        this->base.shape.rot.y = 0;
    }
}
