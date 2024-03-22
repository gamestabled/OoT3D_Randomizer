#ifndef _LINK_PUPPET_H_
#define _LINK_PUPPET_H_

#include "z3D/z3D.h"
#include "multiplayer_ghosts.h"

typedef struct {
    Actor base;
    SkelAnime skelAnime;
    LinkGhost* ghostPtr;
} EnLinkPuppet;

extern ActorInit EnLinkPuppet_InitVars;

void EnLinkPuppet_Init(Actor* thisx, GlobalContext* globalCtx);
void EnLinkPuppet_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnLinkPuppet_Update(Actor* thisx, GlobalContext* globalCtx);
void EnLinkPuppet_Draw(Actor* thisx, GlobalContext* globalCtx);

#endif //_LINK_PUPPET_H_
