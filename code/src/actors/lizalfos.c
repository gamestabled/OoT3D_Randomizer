#include "lizalfos.h"
#include "settings.h"

#define EnZf_Update ((ActorFunc)GAME_ADDR(0x101C48))

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
