#include "z3D/z3D.h"

#define EnOwl_Init_Addr 0x18DB28
#define EnOwl_Init ((ActorFunc)EnOwl_Init_Addr)

void EnOwl_DespawnInit(Actor* owl, GlobalContext* globalCtx) {
    switch ((owl->params & 0x3C0) >> 6) {
        case 7:
        case 8:
        case 9:
            EnOwl_Init(owl, globalCtx);
            return;
        default:
            Actor_Kill(owl);
    }
}
