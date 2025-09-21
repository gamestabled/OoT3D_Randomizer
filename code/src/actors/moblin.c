#include "z3D/z3D.h"
#include "moblin.h"
#include "settings.h"
#include "common.h"

#define EnMb_Init ((ActorFunc)GAME_ADDR(0x165BA4))
#define EnMb_Update ((ActorFunc)GAME_ADDR(0x1B6D80))

#define EnMb_ClubWaitPlayerNear ((EnMbActionFunc)GAME_ADDR(0x10B5D0))
#define EnMb_ClubAttack ((EnMbActionFunc)GAME_ADDR(0x136C68))

void EnMb_rInit(Actor* thisx, GlobalContext* globalCtx) {
    EnMb_Init(thisx, globalCtx);

    if (Enemizer_IsEnemyRandomized(ENEMY_MOBLIN_CLUB) && thisx->params == 0x0000) { // Club Moblin
        // Reset position in case it changed on init (the vanilla SFM Moblin teleports
        // on the other side if you come from Forest Temple).
        thisx->world.pos = thisx->home.pos;
        // Skip drawing the shadow because it's only half-implemented in the vanilla game,
        // and always appears at (0,0,0).
        thisx->shape.shadowDrawFunc = NULL;
    }

    if (Enemizer_IsEnemyRandomized(ENEMY_MOBLIN_SPEAR) && thisx->params == (s16)0xFFFF) { // Spear guard
        // Set the size to be like the "spear patrol" type.
        thisx->scale.x = 0.014;
        thisx->scale.y = 0.014;
        thisx->scale.z = 0.014;
    }
}

void EnMb_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnMb* this = (EnMb*)thisx;

    EnMb_Update(thisx, globalCtx);

    if (Enemizer_IsEnemyRandomized(ENEMY_MOBLIN_CLUB) && thisx->params == 0x0000) { // Club Moblin
        if (this->actionFunc == EnMb_ClubAttack) {
            // The rotation is handled below, so always use the central attack.
            this->attack = ENMB_ATTACK_CLUB_MIDDLE;
        }

        // Check facing direction in the same way the base game does in EnMb_ClubWaitPlayerNear
        s16 relYawFromPlayer = this->actor.world.rot.y - this->actor.yawTowardsPlayer;
        u8 isFacingPlayer    = ABS(relYawFromPlayer) < 0x3E80;

        u8 isRaisingClub =
            this->actionFunc == EnMb_ClubAttack && // The Moblin is in the attack action
            this->skelAnime.animLength == 24.0 &&  // Check that this is the correct animation (raising club)
            this->skelAnime.curFrame > 5.0;        // The club has been lifted off the ground

        u8 isClose = Math_Vec3f_DistXZ(&this->actor.home.pos, &PLAYER->actor.world.pos) < this->playerDetectionRange;

        // Rotate towards player when alive, close to Link, not stunned/damaged, and either facing away from Link or
        // raising the club to attack. Do not rotate the rest of the time to make it easier to approach the Moblin and
        // dodge the shockwaves.
        if (thisx->colChkInfo.health != 0 && isClose && thisx->colorFilterTimer == 0 &&
            (!isFacingPlayer || isRaisingClub)) {
            s16 step = isRaisingClub ? 0x1000 : 0x300; // Rotate quickly when attacking
            Math_SmoothStepToS(&thisx->world.rot.y, thisx->yawTowardsPlayer, 3, step, 0);
            thisx->shape.rot.y = thisx->world.rot.y;
        }

        Actor* shockwave = thisx->child;
        if (shockwave != NULL &&
            ((shockwave->update == NULL && shockwave->draw == NULL) || shockwave->id != ACTOR_EN_PART)) {
            // When the shockwave despawns, clear the child pointer.
            thisx->child = shockwave = NULL;
        }
        if (shockwave != NULL) {
            // Make shockwave actor follow sloped ground, and despawn at the edge.
            CollisionPoly floorPoly;
            Vec3f actorPos = (Vec3f){
                .x = shockwave->world.pos.x,
                .y = shockwave->world.pos.y + 30,
                .z = shockwave->world.pos.z,
            };
            f32 yGroundIntersect = BgCheck_RaycastDown1(&gGlobalContext->colCtx, &floorPoly, &actorPos);
            if (ABS(shockwave->world.pos.y - yGroundIntersect) < 30.0) {
                shockwave->world.pos.y = yGroundIntersect;
            } else {
                Actor_Kill(shockwave);
                thisx->child = shockwave = NULL;
            }
        }
    }
}
