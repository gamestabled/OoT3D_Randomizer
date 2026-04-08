#ifndef _CARPENTER_H_
#define _CARPENTER_H_

#include "z3D/z3D.h"

struct EnDaiku;

typedef void (*EnDaikuActionFunc)(struct EnDaiku* this, GlobalContext* globalCtx);

typedef struct EnDaiku {
    Actor base;
    SkelAnime anime;
    char unk_228[2080];
    EnDaikuActionFunc action_fn;
} EnDaiku;

void EnDaiku_rUpdate(Actor* thisx, GlobalContext* globalCtx);
void EnDaiku_StartEscape(EnDaiku* this);

#endif //_CARPENTER_H_
