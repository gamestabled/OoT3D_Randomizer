#include "z3D/z3D.h"
#include "demo_kankyo.h"

#define DemoKankyo_Update_addr 0x262EA4
#define DemoKankyo_Update ((ActorFunc)DemoKankyo_Update_addr)

#define DoT_Opening_Cutscene_Pointer ((void*)0x0893AD30)
#define CsTimer (globalCtx->csCtx.frames)

void DemoKankyo_rUpdate(Actor* thisx, GlobalContext* globalCtx){
    DemoKankyo_Update(thisx, globalCtx);

    //Warp Song particles
    if(thisx->params == 0x000F){
        globalCtx->sceneLoadFlag = 0x14;
        switch (globalCtx->unk_2304[0x0878]){ //text related variable
            case 0:
                globalCtx->nextEntranceIndex = 0x0600; //Minuet
                break;
            case 1:
                globalCtx->nextEntranceIndex = 0x04F6; //Bolero
                break;
            case 2:
                globalCtx->nextEntranceIndex = 0x0604; //Serenade
                break;
            case 3:
                globalCtx->nextEntranceIndex = 0x01F1; //Requiem
                break;
            case 4:
                globalCtx->nextEntranceIndex = 0x0568; //Nocturne
                break;
            case 5:
                globalCtx->nextEntranceIndex = 0x05F4; //Prelude
                break;
            default:
                globalCtx->sceneLoadFlag = 0; //if something goes wrong, the animation plays normally
        }
        //Unset Zoneout Type -3 to avoid cutscene at destination (technically it's not needed)
        if(gSaveContext.respawnFlag == -3){
            gSaveContext.respawnFlag = 0;
        }
    }

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
