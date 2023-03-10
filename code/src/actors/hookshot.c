#include "z3D/z3D.h"
#include "hookshot.h"
#include "settings.h"

#define ArmsHook_Init_addr 0x1EBF84
#define ArmsHook_Init ((ActorFunc)ArmsHook_Init_addr)

#define HookshotRotation (f32*)0x4C257C

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
