#include "z3D/z3D.h"
#include "fairy.h"
#include "settings.h"
#include "objects.h"

#define NAVI_COLORS_ARRAY ((Color_RGBA8*)0x50C998)
#define FAIRY_COLOR_SPEED 17   // 255 = 3*17*5
#define FAIRY_COLOR_MAX 255.0f // max value for RGB components

static u8 lastTargetActorType = 0;
// Data to manage the rainbow colors
static void* staticRainbowPointerCMAB = 0;
static void* staticRainbowReticleCMAB = 0;
static Color_RGBA8 staticRainbowColor = { 0 };

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

void Fairy_ApplyColorToTargetCMAB(void* cmab, Color_RGBA8 color) {
    // keyframe 1
    *(f32*)(cmab + 0x6C) = color.r / 255.0f;
    *(f32*)(cmab + 0xAC) = color.g / 255.0f;
    *(f32*)(cmab + 0xEC) = color.b / 255.0f;
    // keyframe 2
    *(f32*)(cmab + 0x7C) = color.r / 255.0f;
    *(f32*)(cmab + 0xBC) = color.g / 255.0f;
    *(f32*)(cmab + 0xFC) = color.b / 255.0f;
    // keyframe 3
    *(f32*)(cmab + 0x8C)  = color.r / 255.0f;
    *(f32*)(cmab + 0xCC)  = color.g / 255.0f;
    *(f32*)(cmab + 0x10C) = color.b / 255.0f;
}

void Fairy_UpdateRainbowNaviColors(EnElf* navi) {
    if (Fairy_IsNaviInnerRainbowForActorType(lastTargetActorType)) {
        Colors_ChangeRainbowColorRGBAf(&(navi->innerColor), FAIRY_COLOR_SPEED, FAIRY_COLOR_MAX);
        staticRainbowColor.r = navi->innerColor.r;
        staticRainbowColor.g = navi->innerColor.g;
        staticRainbowColor.b = navi->innerColor.b;
        staticRainbowColor.a = 0xFF;
    }
    if (Fairy_IsNaviOuterRainbowForActorType(lastTargetActorType)) {
        Colors_ChangeRainbowColorRGBAf(&(navi->outerColor), FAIRY_COLOR_SPEED, FAIRY_COLOR_MAX);
    }

    // Handle target pointer color
    if (staticRainbowPointerCMAB != 0) {
        Fairy_ApplyColorToTargetCMAB(staticRainbowPointerCMAB, staticRainbowColor);
    }
    if (staticRainbowReticleCMAB != 0) {
        Fairy_ApplyColorToTargetCMAB(staticRainbowReticleCMAB, staticRainbowColor);
    }
}

s32 Fairy_SetTargetPointerColor(TargetContext* targetCtx, Actor* targetActor) {
    if (gSettingsContext.customNaviColors == OFF) {
        return 0;
    }

    void** cmabManager = ZAR_GetCMABByIndex(targetCtx->zarInfo, 37); // mark_model_white.cmab as base for all colors
    Fairy_ApplyColorToTargetCMAB(*cmabManager, NAVI_COLORS_ARRAY[targetActor->type * 2]); // get inner color
    staticRainbowPointerCMAB = Fairy_IsNaviInnerRainbowForActorType(targetActor->type) ? *cmabManager : 0;

    TexAnim_Spawn(targetCtx->visibleTargetIndicators.pointer->unk_0C, cmabManager);
    TexAnim_Spawn(targetCtx->hiddenTargetIndicators.pointer->unk_0C, cmabManager);
    targetCtx->pointerActorType = targetActor->type;

    return 1;
}

s32 Fairy_SetTargetReticleColor(TargetContext* targetCtx) {
    if (gSettingsContext.customNaviColors == OFF) {
        return 0;
    }

    void** cmabManager = ZAR_GetCMABByIndex(targetCtx->zarInfo, 41); // target_model_white.cmab as base for all colors
    Fairy_ApplyColorToTargetCMAB(*cmabManager, NAVI_COLORS_ARRAY[targetCtx->reticleActorType * 2]); // get inner color
    staticRainbowReticleCMAB = Fairy_IsNaviInnerRainbowForActorType(targetCtx->reticleActorType) ? *cmabManager : 0;

    for (s32 i = 0; i < 4; i++) {
        TexAnim_Spawn(targetCtx->visibleTargetIndicators.reticle[i]->unk_0C, cmabManager);
        TexAnim_Spawn(targetCtx->visibleTargetIndicators.reticleAfterimageOne[i]->unk_0C, cmabManager);
        TexAnim_Spawn(targetCtx->visibleTargetIndicators.reticleAfterimageTwo[i]->unk_0C, cmabManager);
        TexAnim_Spawn(targetCtx->hiddenTargetIndicators.reticle[i]->unk_0C, cmabManager);
        TexAnim_Spawn(targetCtx->hiddenTargetIndicators.reticleAfterimageOne[i]->unk_0C, cmabManager);
        TexAnim_Spawn(targetCtx->hiddenTargetIndicators.reticleAfterimageTwo[i]->unk_0C, cmabManager);
    }

    return 1;
}

void Fairy_ResetRainbowCMABs(void) {
    staticRainbowPointerCMAB = 0;
    staticRainbowReticleCMAB = 0;
}
