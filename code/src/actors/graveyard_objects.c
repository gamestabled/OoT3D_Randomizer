#include "graveyard_objects.h"
#include "multiplayer.h"

#define CsTimer (gGlobalContext->csCtx.frames)

#define BgSpot02Objects_Update ((ActorFunc)GAME_ADDR(0x3831AC))

#define BgSpot02Objects_Explode (void*)GAME_ADDR(0x205EDC)

void BgSpot02Objects_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    BgSpot02Objects_Update(thisx, globalCtx);
    // Royal Family's Tomb.        Tomb opened (or opening).                 Just for safety in case of WW.
    if (thisx->params == 0x0002 && (gSaveContext.eventChkInf[1] & 0x2000) && gSaveContext.sceneSetupIndex < 4) {
        if (CsTimer > 0 && CsTimer < 740) {
            Multiplayer_Send_ActorUpdate(thisx, NULL, 0);
            CsTimer = 740;
        } else if (CsTimer > 740 && CsTimer < 869) {
            CsTimer = 869;
        }
    }
}

void BgSpot02Objects_ExplodeGrave(BgSpot02Objects* thisx) {
    PlaySFX(0x1000219, &thisx->base.world.pos, 4, (f32*)GAME_ADDR(0x54AC20), (f32*)GAME_ADDR(0x54AC20),
            (s8*)GAME_ADDR(0x54AC24)); // NA_SE_EV_GRAVE_EXPLOSION
    thisx->timer     = 38;
    thisx->action_fn = BgSpot02Objects_Explode;
}
