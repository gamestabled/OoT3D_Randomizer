#include "graveyard_objects.h"
#include "multiplayer.h"

#define CsTimer (gGlobalContext->csCtx.frames)

void BgSpot02Objects_Update(Actor* thisx, GlobalContext* globalCtx);

void BgSpot02Objects_Explode(BgSpot02Objects* this, GlobalContext* globalCtx);

void BgSpot02Objects_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    BgSpot02Objects_Update(thisx, globalCtx);
    // Royal Family's Tomb.        Tomb opened (or opening).                 Just for safety in case of WW.
    if (thisx->params == 0x0002 && (gSaveContext.eventChkInf[1] & 0x2000) && gSaveContext.sceneLayer < 4) {
        if (CsTimer > 0 && CsTimer < 740) {
            Multiplayer_Send_ActorUpdate(thisx, NULL, 0);
            CsTimer = 740;
        } else if (CsTimer > 740 && CsTimer < 869) {
            CsTimer = 869;
        }
    }
}

void BgSpot02Objects_ExplodeGrave(BgSpot02Objects* this) {
    PlaySFX(0x1000219, &this->base.world.pos, 4, &gSfxDefaultFreqAndVolScale, &gSfxDefaultFreqAndVolScale,
            &gSfxDefaultReverb); // NA_SE_EV_GRAVE_EXPLOSION
    this->timer     = 38;
    this->action_fn = BgSpot02Objects_Explode;
}
