#include "z3D/z3D.h"
#include "twinrova.h"

#define Boss_Tw_Init ((ActorFunc)GAME_ADDR(0x1A7E18))

#define Boss_Tw_Update ((ActorFunc)GAME_ADDR(0x1EF880))

#define Boss_Tw_Draw ((ActorFunc)GAME_ADDR(0x1EEDF0))

#define Boss_Tw_Destroy ((ActorFunc)GAME_ADDR(0x1A88E8))

#define PlayActorMusic ((void (*)(u8 unk, u32 music))GAME_ADDR(0x36EC40))

#define BOSS_BATTLE_BGM 0x1000589

static u8 fightStarted = 0;
static u8 appeared     = 0;

void Boss_Tw_rInit(Actor* thisx, GlobalContext* globalCtx) {
    Boss_Tw_Init(thisx, globalCtx);
    if (thisx->params == 0 || thisx->params == 1) {
        // Kotake or Koume
        thisx->scale.x = 0.0025f;
        thisx->scale.y = 0.0025f;
        thisx->scale.z = 0.0025f;
    }
}

void Boss_Tw_rUpdate(Actor* thisx, GlobalContext* globalCtx) {

    Vec3f pos = PLAYER->actor.world.pos;

    if (!fightStarted && pos.x > -100 && pos.x < 100 && pos.y > 200 && pos.z > -100 && pos.z < 100) {
        fightStarted = 1;
        PlayActorMusic(0, BOSS_BATTLE_BGM);
    }

    if (fightStarted) {
        Boss_Tw_Update(thisx, globalCtx);
        // this makes the witches appear less suddenly, with a progressive size increment
        if (!appeared && thisx->scale.x < 0.025f) {
            thisx->scale.x += 0.0005f;
            thisx->scale.y += 0.0005f;
            thisx->scale.z += 0.0005f;
        } else if (!appeared) {
            appeared = 1;
        }
    }
}

void Boss_Tw_rDraw(Actor* thisx, GlobalContext* globalCtx) {
    if (fightStarted)
        Boss_Tw_Draw(thisx, globalCtx);
}

void Boss_Tw_rDestroy(Actor* thisx, GlobalContext* globalCtx) {
    if (thisx->params == 0x0001) { // Koume. This check is needed because the elemental
        fightStarted = 0;          // attacks are different instances of the actor
        appeared     = 0;
    }

    Boss_Tw_Destroy(thisx, globalCtx);
}
