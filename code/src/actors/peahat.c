#include "peahat.h"
#include "settings.h"
#include "enemizer.h"
#include "enemy_souls.h"
#include "actor.h"

void EnPeehat_Update(Actor* thisx, GlobalContext* globalCtx);

void EnPeehat_StateAttackRecoil(EnPeehat* this, GlobalContext* globalCtx);
void EnPeehat_Larva_StateSeekPlayer(EnPeehat* this, GlobalContext* globalCtx);

#define STATE_SEEK_PLAYER 14

void EnPeehat_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnPeehat* this = (EnPeehat*)thisx;

    EnPeehat_Update(thisx, globalCtx);

    if (Enemizer_IsEnemyRandomized(ENEMY_PEAHAT) && thisx->params == PEAHAT_TYPE_GROUNDED) {
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

    if (EnemySouls_IsInvulnerable(thisx) && thisx->params == PEAHAT_TYPE_LARVA) {
        // Prevent death when hitting player's shield.
        if (this->actionFunc == EnPeehat_StateAttackRecoil && thisx->speedXZ > -1.0) {
            this->actionFunc = EnPeehat_Larva_StateSeekPlayer;
            this->state      = STATE_SEEK_PLAYER;
            this->colliderQuadBase.atFlags &= ~AT_BOUNCED;
        }

        CollisionPoly floorPoly;
        f32 yGroundIntersect = BgCheck_RaycastDown1(&gGlobalContext->colCtx, &floorPoly, &thisx->world.pos);

        // Keep peahat larvas slightly above ground so their attack collider can still damage the player.
        // Sometimes they can still touch the ground anyway, so there is also a stand-alone patch to prevent
        // them from dying in that case.
        if (thisx->world.pos.y < yGroundIntersect + 10) {
            thisx->world.pos.y = yGroundIntersect + 10;
        }
    }
}

void EnPeehat_ReinitModels(EnPeehat* this) {
    Actor_DestroySkelModels(&this->actor, &this->rootModel, NULL);
    Actor_CreateSkelModels(&this->actor, gGlobalContext, &this->rootModel, 1, NULL);

    Actor_ReinitSkelAnime(&this->actor, &this->anime, 0);
}
