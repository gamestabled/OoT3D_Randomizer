#ifndef _EN_SHOPNUTS_H_
#define _EN_SHOPNUTS_H_

#include "z3D/z3D.h"

struct EnShopnuts;

typedef void (*EnShopnutsActionFunc)(struct EnShopnuts* this, GlobalContext* globalCtx);

typedef struct EnShopnuts {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ EnShopnutsActionFunc actionFunc;
    /* 0x1A8 */ char unk_1A8[0x05C];
    /* 0x204 */ SkelAnime anime;
    /* 0x288 */ char unk_288[0x618];
} EnShopnuts;
_Static_assert(sizeof(EnShopnuts) == 0x8A0, "EnShopnuts size");

#endif //_EN_SHOPNUTS_H_
