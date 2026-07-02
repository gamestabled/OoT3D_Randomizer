#include "s_message.h"

#include "z3D/z3D.h"
#include "poe_collector.h"
#include "settings.h"

#define TEXT_GIVE_REWARD 0x70F8

void EnGb_Update(Actor* thisx, GlobalContext* globalCtx);

void EnGb_Idle(EnGb* this, GlobalContext* play);
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

    Bool hasRequiredPoints = gSaveContext.bigPoePoints >= gSettingsContext.bigPoeTargetCount * 100;

    if (gSettingsContext.shuffleBigPoes && hasRequiredPoints && !Flags_GetSwitch(globalCtx, POE_REWARD_SWITCH_FLAG)) {
        // Replace normal dialog with reward one.
        if (this->actionFunc == EnGb_Idle) {
            this->textId = this->dyna.actor.textId = TEXT_GIVE_REWARD;
        }

        // When starting normal talk action, give reward instead.
        if (this->actionFunc == EnGb_Talk) {
            this->actionFunc = EnGb_OfferReward;
            Flags_SetSwitch(globalCtx, POE_REWARD_SWITCH_FLAG);
        }
    } else if (!hasRequiredPoints && this->actionFunc == EnGb_Idle) {
        // Custom text to say both current and required points.
        this->textId = this->dyna.actor.textId = CUSTOM_TEXT_POE_COLLECTOR_TELL_POINTS;
    }
}
