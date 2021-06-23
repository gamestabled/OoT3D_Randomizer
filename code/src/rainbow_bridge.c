#include "z3D/z3D.h"
#include "settings.h"
#include "savefile.h"

#define CsTimer (gGlobalContext->csCtx.frames)

u32 BgGjyoBridge_ConditionVanilla(void) {
    return ((gSaveContext.questItems & 0x8) && (gSaveContext.questItems & 0x10) &&
            (gSaveContext.items[ItemSlots[ITEM_ARROW_LIGHT]] == ITEM_ARROW_LIGHT));
}

u32 BgGjyoBridge_ConditionStones(void) {
    return SaveFile_GetStoneCount() >= gSettingsContext.bridgeStoneCount;
}

u32 BgGjyoBridge_ConditionMedallions(void) {
    return SaveFile_GetMedallionCount() >= gSettingsContext.bridgeMedallionCount;
}

u32 BgGjyoBridge_ConditionRewards(void) {
    return SaveFile_GetMedallionCount() + SaveFile_GetStoneCount() >= gSettingsContext.bridgeRewardCount;
}

u32 BgGjyoBridge_ConditionDungeons(void) {
    return SaveFile_GetDungeonCount() >= gSettingsContext.bridgeDungeonCount;
}

u32 BgGjyoBridge_CheckCondition(void) {
    switch (gSettingsContext.rainbowBridge) {
        case RAINBOWBRIDGE_OPEN:
            return 1;
        case RAINBOWBRIDGE_VANILLA:
            return BgGjyoBridge_ConditionVanilla();
        case RAINBOWBRIDGE_STONES:
            return BgGjyoBridge_ConditionStones();
        case RAINBOWBRIDGE_MEDALLIONS:
            return BgGjyoBridge_ConditionMedallions();
        case RAINBOWBRIDGE_REWARDS:
            return BgGjyoBridge_ConditionRewards();
        case RAINBOWBRIDGE_DUNGEONS:
            return BgGjyoBridge_ConditionDungeons();
        case RAINBOWBRIDGE_TOKENS:
            return gSaveContext.gsTokens >= gSettingsContext.bridgeTokenCount;
        default:
            return BgGjyoBridge_ConditionVanilla();
    }
}

void ShortenRainbowBridgeCS() {
    if (CsTimer < 230)
        CsTimer = 230;
    else if (CsTimer > 405 && CsTimer < 490)
        CsTimer = 490;
    else if (CsTimer > 535 && CsTimer < 779)
        CsTimer = 779;
}
