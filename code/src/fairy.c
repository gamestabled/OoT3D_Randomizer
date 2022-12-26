#include "z3D/z3D.h"
#include "fairy.h"
#include "settings.h"

#define FAIRY_COLOR_SPEED 17 // 255 = 3*17*5

static u8 lastTargetActorType = 0;

void Fairy_StoreTargetActorType(u8 targetActorType) {
    lastTargetActorType = targetActorType;
}

u8 Fairy_IsNaviInnerRainbowForActorType(u8 type) {
    switch (type) {
        case ACTORTYPE_PLAYER:
            return gSettingsContext.rainbowIdleNaviInnerColor;
        case ACTORTYPE_NPC:
            return gSettingsContext.rainbowNPCNaviInnerColor;
        case ACTORTYPE_ENEMY:
        case ACTORTYPE_BOSS:
            return gSettingsContext.rainbowEnemyNaviInnerColor;
        default:
            return gSettingsContext.rainbowPropNaviInnerColor;
    }
}

u8 Fairy_IsNaviOuterRainbowForActorType(u8 type) {
    switch (type) {
        case ACTORTYPE_PLAYER:
            return gSettingsContext.rainbowIdleNaviOuterColor;
        case ACTORTYPE_NPC:
            return gSettingsContext.rainbowNPCNaviOuterColor;
        case ACTORTYPE_ENEMY:
        case ACTORTYPE_BOSS:
            return gSettingsContext.rainbowEnemyNaviOuterColor;
        default:
            return gSettingsContext.rainbowPropNaviOuterColor;
    }
}

void Fairy_UpdateRainbowNaviColors(EnElf* navi) {
    if (Fairy_IsNaviInnerRainbowForActorType(lastTargetActorType)) {
        Colors_ChangeRainbowColorRGBAf(&(navi->innerColor), FAIRY_COLOR_SPEED, 255.0f);
    }
    if (Fairy_IsNaviOuterRainbowForActorType(lastTargetActorType)) {
        Colors_ChangeRainbowColorRGBAf(&(navi->outerColor), FAIRY_COLOR_SPEED, 255.0f);
    }
}
