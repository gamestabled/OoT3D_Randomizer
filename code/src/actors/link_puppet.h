#ifndef _LINK_PUPPET_H_
#define _LINK_PUPPET_H_

#include "z3D/z3D.h"
#include "multiplayer_ghosts.h"

typedef struct {
    Actor base;
    LinkGhost* ghostPtr;
    SkelAnime skelAnime;
    ColliderCylinder collider;
} EnLinkPuppet;

extern ActorInit EnLinkPuppet_InitVars;

void EnLinkPuppet_Init(EnLinkPuppet* this, GlobalContext* globalCtx);
void EnLinkPuppet_Destroy(EnLinkPuppet* this, GlobalContext* globalCtx);
void EnLinkPuppet_Update(EnLinkPuppet* this, GlobalContext* globalCtx);
void EnLinkPuppet_Draw(EnLinkPuppet* this, GlobalContext* globalCtx);

#endif //_LINK_PUPPET_H_
