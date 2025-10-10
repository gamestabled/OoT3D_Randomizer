#include "iron_knuckle.h"
#include "settings.h"

#define EnIk_Init ((ActorFunc)GAME_ADDR(0x164B0C))
#define EnIk_UpdateEnemy ((ActorFunc)GAME_ADDR(0x1008B4))

void EnIk_Update_Randomized(Actor* thisx, GlobalContext* globalCtx) {
    EnIk_UpdateEnemy(thisx, globalCtx);

    // Change wallCheckHeight from 75 to 50, to prevent falling out of bounds through low walls
    // (e.g. near the crawlspace in Spirit Temple).
    Actor_UpdateBgCheckInfo(globalCtx, thisx, 50.0f, 30.0f, 30.0f,
                            UPDBGCHECKINFO_WALL | UPDBGCHECKINFO_FLOOR_WATER | UPDBGCHECKINFO_FLAG_3 |
                                UPDBGCHECKINFO_FLAG_4);
}

void EnIk_rInit(Actor* thisx, GlobalContext* globalCtx) {
    EnIk* this = (EnIk*)thisx;

    EnIk_Init(thisx, globalCtx);

    if (Enemizer_IsEnemyRandomized(ENEMY_IRON_KNUCKLE)) {
        // Wake up immediately
        this->skelAnime.playSpeed = 1.0f;
        // Override update here because it's also set in EnIk_Init
        this->actor.update = EnIk_Update_Randomized;
    }
}
