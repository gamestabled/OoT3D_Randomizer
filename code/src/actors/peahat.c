#include "peahat.h"
#include "settings.h"

#define EnPeehat_Update ((ActorFunc)GAME_ADDR(0x167644))

#define STATE_SEEK_PLAYER 14

void EnPeehat_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnPeehat* this = (EnPeehat*)thisx;

    EnPeehat_Update(thisx, globalCtx);

    if (gSettingsContext.enemizer == ON && thisx->params == (s16)0xFFFF) { // Grounded Peahat
        f32 yWaterSurface;
        void* waterBox;
        s32 waterBoxFound = WaterBox_GetSurfaceImpl(gGlobalContext, &gGlobalContext->colCtx, thisx->world.pos.x,
                                                    thisx->world.pos.z, &yWaterSurface, &waterBox);

        // Float on water to work as an aquatic plant.
        if (waterBoxFound && thisx->world.pos.y < yWaterSurface - 10.0) {
            thisx->world.pos.y = yWaterSurface - 10.0;
        }

        // Fly at player's height.
        if (this->state == STATE_SEEK_PLAYER && thisx->world.pos.y < PLAYER->actor.world.pos.y) {
            Math_SmoothStepToF(&thisx->world.pos.y, PLAYER->actor.world.pos.y, 3, 5.0, 0);
        }

        // Vanilla code doesn't check for ceilings.
        Actor_UpdateBgCheckInfo(globalCtx, thisx, 25.0f, 30.0f, 100.0f,
                                UPDBGCHECKINFO_WALL | UPDBGCHECKINFO_CEILING | UPDBGCHECKINFO_FLOOR_WATER);
    }
}
