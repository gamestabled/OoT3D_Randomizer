#ifndef _EN_TEST_H_
#define _EN_TEST_H_

#include "z3D/z3D.h"

struct EnTest;

typedef void (*EnTestActionFunc)(struct EnTest*, GlobalContext*);

typedef struct EnTest {
    Actor base;
    char unk_1A4[60];
    SkelAnime anime;
    char unk_264[6636];
    EnTestActionFunc action_fn;
} EnTest;

void EnTest_Wait(EnTest* this, GlobalContext* globalCtx);

#endif //_EN_TEST_H_
