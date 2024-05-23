#include "z3D/z3D.h"
#include "fishing.h"
#include "models.h"
#include "settings.h"

u32 isFishing(void) {
    return gSaveContext.equips.buttonItems[0] == ITEM_FISHING_POLE && gGlobalContext->sceneNum == 73;
}

static s32 rewardObtained(void) {
    u8 obtainedRewardFlag = gSaveContext.linkAge == AGE_ADULT ? 0x8 : 0x4;
    return gSaveContext.fishingStats.flags & obtainedRewardFlag;
}

void Fishing_rInit(Actor* thisx, GlobalContext* globalCtx) {
    u16 baseItemId = gSaveContext.linkAge == AGE_ADULT ? GI_SCALE_GOLD : GI_HEART_PIECE;
    Fishing_Init(thisx, globalCtx);
    if (gSettingsContext.fishingHints && thisx->params == EN_FISH_AQUARIUM && !rewardObtained()) {
        Model_SpawnByActor(thisx, globalCtx, baseItemId);
    }
}

void Fishing_rUpdateFish(Actor* thisx, GlobalContext* globalCtx) {
    Fishing_UpdateFish(thisx, globalCtx);
    if (gSettingsContext.fishingHints && thisx->params == EN_FISH_AQUARIUM && !rewardObtained()) {
        thisx->textId = 0x40AE; // custom text, overrides vanilla "pond owner" record text
    }
}

void Fishing_rDrawFish(Actor* thisx, GlobalContext* globalCtx) {
    static s16 sPrizeRotation = 0x8000; // used because shape.rot.y is reset between update cycles

    if (gSettingsContext.fishingHints && thisx->params == EN_FISH_AQUARIUM && !rewardObtained()) {
        sPrizeRotation += 0x100;
        thisx->shape.rot.y = sPrizeRotation;
        Model_DrawByActor(thisx);
    } else {
        Fishing_DrawFish(thisx, globalCtx);
    }
}
