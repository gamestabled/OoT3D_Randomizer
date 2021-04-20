#include "z3D/z3D.h"
#include "twinrova.h"

#define Boss_Tw_Update_addr 0x1EF880
#define Boss_Tw_Update ((ActorFunc)Boss_Tw_Update_addr)

#define Boss_Tw_Draw_addr 0x1EEDF0
#define Boss_Tw_Draw ((ActorFunc)Boss_Tw_Draw_addr)

#define Boss_Tw_Destroy_addr 0x1A88E8
#define Boss_Tw_Destroy ((ActorFunc)Boss_Tw_Destroy_addr)

static u8 fightStarted = 0;

void Boss_Tw_rUpdate(Actor* thisx, GlobalContext* globalCtx){

    Vec3f pos = PLAYER->actor.prevPos;
    
    if(pos.x > -100 && pos.x < 100 && pos.y > 200 && pos.z > -100 && pos.z < 100)
        fightStarted = 1;
    
    if(fightStarted)
        Boss_Tw_Update(thisx, globalCtx);
}

void Boss_Tw_rDraw(Actor* thisx, GlobalContext* globalCtx){
    if(fightStarted)
        Boss_Tw_Draw(thisx, globalCtx);
}

void Boss_Tw_rDestroy(Actor* thisx, GlobalContext* globalCtx){
    if(thisx->params == 0x0001)    //Koume. This check is needed because the elemental
        fightStarted = 0;          //attacks are different instances of the actor
    
    Boss_Tw_Destroy(thisx, globalCtx);
}
