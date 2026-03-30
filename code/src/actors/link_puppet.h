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

#endif //_LINK_PUPPET_H_
