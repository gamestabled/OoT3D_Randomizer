#include "z3D/z3D.h"
#include "common.h"
#include "settings.h"
#include "enemizer.h"

typedef struct {
    Actor base;
    char unk_1A4[60];
    SkelAnime anime;
    char unk_264[6636];
    ActorFunc action_fn;
} EnTest;

#define EnTest_Wait ((ActorFunc)GAME_ADDR(0x39D8CC))

u8 ShadowShip_HasActiveStalfos(void) {
    if (gEnemizerLocationFlags.shadowShipStalfos) {
        return FALSE;
    }

    for (Actor* actor = gGlobalContext->actorCtx.actorList[ACTORTYPE_ENEMY].first; actor != 0; actor = actor->next) {
        if (actor->id != 0x2) {
            continue;
        }
        EnTest* stalfos = (EnTest*)actor;
        if (stalfos->action_fn != EnTest_Wait) {
            return TRUE;
        }
    }
    return FALSE;
}
