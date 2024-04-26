#include "z3D/z3D.h"
#include "hookshot.h"
#include "settings.h"

#define ArmsHook_Init ((ActorFunc)GAME_ADDR(0x1EBF84))

#define HookshotRotation (f32*)GAME_ADDR(0x4C257C)

void ArmsHook_rInit(Actor* thisx, GlobalContext* globalCtx) {
    ArmsHook_Init(thisx, globalCtx);
    if (gSaveContext.linkAge == AGE_CHILD) {
        thisx->scale.x /= 5;
        thisx->scale.y /= 5;
        thisx->scale.z /= 5;
    }
}

f32 Hookshot_GetZRotation(void) {
    return gSaveContext.linkAge == AGE_ADULT ? *HookshotRotation : -1.4; // TODO find position and lower that
}
