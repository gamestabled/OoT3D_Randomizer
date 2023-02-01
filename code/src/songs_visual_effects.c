#include "z3D/z3D.h"
#include "settings.h"
#include "songs_visual_effects.h"
#include "icetrap.h"
#include "savefile.h"

#define OceffWipe_Update_addr 0x256158
#define OceffWipe_Update ((ActorFunc)OceffWipe_Update_addr)

#define OceffWipe2_Update_addr 0x2714B8
#define OceffWipe2_Update ((ActorFunc)OceffWipe2_Update_addr)

#define OceffWipe3_Update_addr 0x27181C
#define OceffWipe3_Update ((ActorFunc)OceffWipe3_Update_addr)

#define OceffWipe4_Update_addr 0x271C10
#define OceffWipe4_Update ((ActorFunc)OceffWipe4_Update_addr)

#define OceffSpot_Update_addr 0x255BDC
#define OceffSpot_Update ((ActorFunc)OceffSpot_Update_addr)

#define OceffSpot_End_addr 0x10FBD0
#define OceffSpot_End ((ActorFunc)OceffSpot_End_addr)

#define OceffStorm_Update_addr 0x27112C
#define OceffStorm_Update ((ActorFunc)OceffStorm_Update_addr)

// Zelda's Lullaby, Song of Time
void OceffWipe_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    if (gExtSaveData.option_SkipSongReplays == SONGREPLAYS_DONT_SKIP) {
        OceffWipe_Update(thisx, globalCtx);
    } else {
        Actor_Kill(thisx);
    }
}

// Epona's Song
void OceffWipe2_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    if (gExtSaveData.option_SkipSongReplays == SONGREPLAYS_DONT_SKIP) {
        OceffWipe2_Update(thisx, globalCtx);
    } else {
        Actor_Kill(thisx);
    }
}

// Saria's Song
void OceffWipe3_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    if (gExtSaveData.option_SkipSongReplays == SONGREPLAYS_DONT_SKIP) {
        OceffWipe3_Update(thisx, globalCtx);
    } else {
        Actor_Kill(thisx);
    }
}

// Scarecrow's Song
void OceffWipe4_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    if (gExtSaveData.option_SkipSongReplays == SONGREPLAYS_DONT_SKIP) {
        OceffWipe4_Update(thisx, globalCtx);
    } else {
        Actor_Kill(thisx);
    }
}

// Sun's Song
void OceffSpot_rUpdate(Actor* thisx, GlobalContext* globalCtx) {
    if (gExtSaveData.option_SkipSongReplays == SONGREPLAYS_DONT_SKIP) {
        OceffSpot_Update(thisx, globalCtx);
    }
    // Wait for a bit before calling OceffSpot_End, otherwise Link and the music staff spots could start waiting
    // for the Sun's Song light after it's been killed already, causing softlocks and non-functional song switches in MQ
    // Spirit
    else if ((gExtSaveData.option_SkipSongReplays == SONGREPLAYS_SKIP_KEEP_SFX && gGlobalContext->msgMode == 0) ||
             (gExtSaveData.option_SkipSongReplays == SONGREPLAYS_SKIP_NO_SFX &&
              ((PLAYER->stateFlags1 >> 24) & 0x30) != 0x30)) {
        OceffSpot_End(thisx, globalCtx);
    }
}

// Song of Storms
void OceffStorm_rUpdate(Actor* thisx, GlobalContext* globalCtx) {

    if (IceTrap_ActiveCurse == ICETRAP_CURSE_BLIND)
        gStaticContext.dekuNutFlash = -1;

    IceTrap_DispelCurses();

    if (gExtSaveData.option_SkipSongReplays == SONGREPLAYS_DONT_SKIP) {
        OceffStorm_Update(thisx, globalCtx);
    } else {
        Flags_SetEnv(globalCtx, 5);
        Actor_Kill(thisx);
    }
}
