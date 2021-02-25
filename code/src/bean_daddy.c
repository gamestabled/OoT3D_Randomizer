#include "z3D/z3D.h"
#include "settings.h"

// If beans aren't shuffled, do nothing here
// If they are and the reward hasnt been purchased, return 5 to display the 60 rupees textbox
// If the reward has been purchased, return 10 to prevent another purchase
s8 EnMs_ModifyBeansBought(s8 beansBought) {
    // return gSettingsContext.shuffleMagicBeans ? 1 : 10;
    if (!gSettingsContext.shuffleMagicBeans) {
        return beansBought;
    } else if (!(gGlobalContext->actorCtx.flags.collect & 2)) {
        return 5;
    } else {
        return 10;
    }
}

// If beans are shuffled, sets the price to 60. Otherwise leaves it untouched
s16 EnMs_ModifyPrice(s16 price) {
    return gSettingsContext.shuffleMagicBeans ? 60 : price;
}

// If beans are shuffled, take 60 and set collect flag 1
void EnMs_Purchase(s16 rupeeChange) {
    if (gSettingsContext.shuffleMagicBeans) {
        Rupees_ChangeBy(-60);
        gGlobalContext->actorCtx.flags.collect |= 2;
    } else {
        Rupees_ChangeBy(rupeeChange);
    }
}
