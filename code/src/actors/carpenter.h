#ifndef _CARPENTER_H_
#define _CARPENTER_H_

#include "z3D/z3D.h"

typedef struct {
    Actor base;
    SkelAnime anime;
    char unk_228[2080];
    void* action_fn;
} EnDaiku;

void EnDaiku_rUpdate(EnDaiku* thisx, GlobalContext* globalCtx);
void EnDaiku_StartEscape(EnDaiku* thisx);

#endif //_CARPENTER_H_
