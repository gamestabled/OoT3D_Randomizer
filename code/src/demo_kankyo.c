#include "z3D/z3D.h"
#include "demo_kankyo.h"

#define DemoKankyo_Update_addr 0x262EA4
#define DemoKankyo_Update ((ActorFunc)DemoKankyo_Update_addr)

#define DoT_Opening_Cutscene_Pointer ((void*)0x0893AD30)
#define CsTimer (globalCtx->csCtx.frames)

void DemoKankyo_rUpdate(Actor* thisx, GlobalContext* globalCtx){
    DemoKankyo_Update(thisx, globalCtx);

/*  //Warp Song particles. This is meant to skip the warping animations, but it works only in ToT for now, because the
    //animations use different cutscene data in that scene specifically. To avoid confusion, this is commented out for now
    if(thisx->params == 0x000F){
        u8* warpTimer = (((u8*)thisx)+0x01A6);
        //Make camera-panning cutscene start immediately
        if(*warpTimer > 2){
            *warpTimer = 2;
        }
        //Make camera-panning cutscene end immediately
        if(CsTimer < 37){
            CsTimer = 37;
        }
        //Unset Zoneout Type -3 to avoid cutscene at destination
        gSaveContext.respawnFlag = 0;
    }
*/

    //Door of Time, the opening cutscene is playing (only regular one, not beta CS #03)
    if(thisx->params == 0x000D && globalCtx->csCtx.segment == DoT_Opening_Cutscene_Pointer){
        //skip the Spiritual Stones part of the cutscene
        if(CsTimer < 800){
            CsTimer = 800;
        }
        //Make cutscene end when the door is fully open
        else if(CsTimer > 1090 && CsTimer < 1180){
            CsTimer = 1180;
        }
    }
}
