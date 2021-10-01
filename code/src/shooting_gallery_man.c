#include "shooting_gallery_man.h"
#include "entrance.h"
#include "settings.h"

#define EnSyatekiMan_Init_addr 0x283F94
#define EnSyatekiMan_Init ((ActorFunc)EnSyatekiMan_Init_addr)

void EnSyatekiMan_rInit(Actor* thisx, GlobalContext* globalCtx) {
    //If child is in the adult shooting gallery or adult in the child shooting gallery, then despawn the shooting gallery man
    if ((gSaveContext.linkAge == AGE_CHILD && Entrance_SceneAndSpawnAre(0x42, 0x00)) ||
        (gSaveContext.linkAge == AGE_ADULT && Entrance_SceneAndSpawnAre(0x42, 0x01))) {
        Actor_Kill(thisx);
    } else {
        EnSyatekiMan_Init(thisx, globalCtx);
    }
}
