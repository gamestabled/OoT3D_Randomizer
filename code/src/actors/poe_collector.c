#include "z3D/z3D.h"
#include "poe_collector.h"
#include "settings.h"

#define TEXT_TELL_POINTS 0x70F5
#define TEXT_GIVE_REWARD 0x70F8

void EnGb_Update(Actor* thisx, GlobalContext* globalCtx);

void EnGb_Talk(EnGb* this, GlobalContext* play);
void EnGb_OfferReward(EnGb* this, GlobalContext* globalCtx);

void EnGb_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnGb* this = (EnGb*)thisx;

    {
        // Fake point count so the collector will give reward at the chosen target count.
        u32 realBigPoePoints = gSaveContext.bigPoePoints;
        gSaveContext.bigPoePoints += 1000 - gSettingsContext.bigPoeTargetCount * 100;
        u32 prevPoints = gSaveContext.bigPoePoints;
        EnGb_Update(thisx, globalCtx);
        u32 addedPoints           = gSaveContext.bigPoePoints - prevPoints;
        gSaveContext.bigPoePoints = realBigPoePoints + addedPoints;
    }

    if (gSettingsContext.shuffleBigPoes && !Flags_GetSwitch(globalCtx, POE_REWARD_SWITCH_FLAG) &&
        gSaveContext.bigPoePoints >= gSettingsContext.bigPoeTargetCount * 100) {
        // Replace normal dialog with reward one.
        if (this->textId == TEXT_TELL_POINTS) {
            this->textId = this->dyna.actor.textId = TEXT_GIVE_REWARD;
        }

        // When starting normal talk action, give reward instead.
        if (this->actionFunc == EnGb_Talk) {
            this->actionFunc = EnGb_OfferReward;
            Flags_SetSwitch(globalCtx, POE_REWARD_SWITCH_FLAG);
        }
    }
}
