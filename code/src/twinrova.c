#include "z3D/z3D.h"
#include "twinrova.h"

#define Boss_Tw_Init_addr 0x1A7E18
#define Boss_Tw_Init ((ActorFunc)Boss_Tw_Init_addr)

#define Boss_Tw_Update_addr 0x1EF880
#define Boss_Tw_Update ((ActorFunc)Boss_Tw_Update_addr)

#define Boss_Tw_Draw_addr 0x1EEDF0
#define Boss_Tw_Draw ((ActorFunc)Boss_Tw_Draw_addr)

#define Boss_Tw_Destroy_addr 0x1A88E8
#define Boss_Tw_Destroy ((ActorFunc)Boss_Tw_Destroy_addr)

#define SomeMusicFunction ((void(*)(u8 unk, u32 music)) 0x36EC40)

#define BOSS_BATTLE_BGM 0x1000589
#define SPIRIT_TEMPLE_BGM 0x10005AC

static u8 fightStarted = 0;
static u8 musicSet = 0;
static u8 appeared = 0;

void Boss_Tw_rInit(Actor* thisx, GlobalContext* globalCtx){
    Boss_Tw_Init(thisx, globalCtx);
    thisx->scale.x = 0.0025f;
    thisx->scale.y = 0.0025f;
    thisx->scale.z = 0.0025f;
}

void Boss_Tw_rUpdate(Actor* thisx, GlobalContext* globalCtx){

    Vec3f pos = PLAYER->actor.world.pos;
    
    if(!fightStarted && pos.x > -100 && pos.x < 100 && pos.y > 200 && pos.z > -100 && pos.z < 100){
        fightStarted = 1;
        SomeMusicFunction(0, BOSS_BATTLE_BGM);
    }
    
    if(fightStarted){
        Boss_Tw_Update(thisx, globalCtx);
        //this makes the witches appear less suddenly, with a progressive size increment
        if(!appeared && thisx->scale.x < 0.025f){
            thisx->scale.x += 0.0005f;
            thisx->scale.y += 0.0005f;
            thisx->scale.z += 0.0005f;
        }
        else if(!appeared){
            appeared = 1;
        }
    }
    else if(!musicSet){
        SomeMusicFunction(0, SPIRIT_TEMPLE_BGM);
        SomeMusicFunction(0, SPIRIT_TEMPLE_BGM); //one doesn't work for some reason
        musicSet = 1;
    }
}

void Boss_Tw_rDraw(Actor* thisx, GlobalContext* globalCtx){
    if(fightStarted)
        Boss_Tw_Draw(thisx, globalCtx);
}

void Boss_Tw_rDestroy(Actor* thisx, GlobalContext* globalCtx){
    if(thisx->params == 0x0001){   //Koume. This check is needed because the elemental
        fightStarted = 0;          //attacks are different instances of the actor
        musicSet = 0;
        appeared = 0;
    }
    
    Boss_Tw_Destroy(thisx, globalCtx);
}
