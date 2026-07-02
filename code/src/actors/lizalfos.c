#include "lizalfos.h"
#include "settings.h"
#include "enemizer.h"
#include "actor.h"

void EnZf_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZf_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnZf_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    EnZf* this = (EnZf*)thisx;

    EnZf_Update(thisx, globalCtx);

    if (Enemizer_IsEnemyRandomized(ENEMY_LIZALFOS) && this->action == ENZF_ACTION_DROP_IN && this->alpha == 0) {
        // While waiting to ambush player, the Lizalfos can end up past a ceiling into a room above (e.g. in Ganon's
        // Tower). To avoid this, set Y position to 150 units above the floor below the spawn point.
        Vec3f floorCheckPos = thisx->home.pos;
        floorCheckPos.y += 50.0;
        CollisionPoly floorPoly;
        f32 yGroundIntersect = BgCheck_RaycastDown1(&gGlobalContext->colCtx, &floorPoly, &floorCheckPos);
        thisx->world.pos.y   = yGroundIntersect + 150.0f;
    }
}

void EnZf_rDraw(Actor* thisx, GlobalContext* globalCtx) {
    EnZf* this = (EnZf*)thisx;

    // Skip draw function when invisible because the textureless soulless look would draw the model anyway.
    if (this->alpha != 0) {
        EnZf_Draw(thisx, globalCtx);
    }
}

void EnZf_ReinitModels(EnZf* this) {
    Actor_ReinitSkelAnime(&this->actor, &this->anime, this->actor.params == -2 ? 1 : 0);
}
