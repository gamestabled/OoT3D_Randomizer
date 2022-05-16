#include "z3D/z3D.h"
#include "fairy.h"
#include "settings.h"

static u8 lastTargetActorType = 0;

void Fairy_StoreTargetActorType(u8 targetActorType) {
    lastTargetActorType = targetActorType;
}

void changeRainbowColorRGBAf(Color_RGBAf* color) {
    #define COLOR_SPEED 17 //255 = 3*17*5
    if (color->r == 255.0f && color->g != 255.0f && color->b == 0)
        color->g += COLOR_SPEED;
    else if (color->r != 0 && color->g == 255.0f && color->b == 0)
        color->r -= COLOR_SPEED;
    else if (color->r == 0 && color->g == 255.0f && color->b != 255.0f)
        color->b += COLOR_SPEED;
    else if (color->r == 0 && color->g != 0 && color->b == 255.0f)
        color->g -= COLOR_SPEED;
    else if (color->r != 255.0f && color->g == 0 && color->b == 255.0f)
        color->r += COLOR_SPEED;
    else if (color->r == 255.0f && color->g == 0 && color->b != 0)
        color->b -= COLOR_SPEED;
}

void updateNaviColors(EnElf* navi) {

    if (lastTargetActorType == ACTORTYPE_PLAYER) {
        if (gSettingsContext.rainbowIdleNaviInnerColor)
            changeRainbowColorRGBAf(&(navi->innerColor));
        if (gSettingsContext.rainbowIdleNaviOuterColor)
            changeRainbowColorRGBAf(&(navi->outerColor));
    }
    else if (lastTargetActorType == ACTORTYPE_NPC) {
        if (gSettingsContext.rainbowNPCNaviInnerColor)
            changeRainbowColorRGBAf(&(navi->innerColor));
        if (gSettingsContext.rainbowNPCNaviOuterColor)
            changeRainbowColorRGBAf(&(navi->outerColor));
    }
    else if (lastTargetActorType == ACTORTYPE_ENEMY || lastTargetActorType == ACTORTYPE_BOSS) {
        if (gSettingsContext.rainbowEnemyNaviInnerColor)
            changeRainbowColorRGBAf(&(navi->innerColor));
        if (gSettingsContext.rainbowEnemyNaviOuterColor)
            changeRainbowColorRGBAf(&(navi->outerColor));
    }
    else {
        if (gSettingsContext.rainbowPropNaviInnerColor)
            changeRainbowColorRGBAf(&(navi->innerColor));
        if (gSettingsContext.rainbowPropNaviOuterColor)
            changeRainbowColorRGBAf(&(navi->outerColor));
    }
}
