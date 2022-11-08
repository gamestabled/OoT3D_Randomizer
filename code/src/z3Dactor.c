#include "z3D/z3Dactor.h"
#include "stddef.h"

void Actor_Kill(Actor* actor) {
    actor->draw   = NULL;
    actor->update = NULL;
    actor->flags &= ~0x1;
}
