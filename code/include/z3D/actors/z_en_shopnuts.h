#ifndef _EN_SHOPNUTS_H_
#define _EN_SHOPNUTS_H_

#include "z3D/z3D.h"

typedef struct EnShopnuts {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ void* action_fn;
    /* 0x1A8 */ char unk_1A8[0x6F8];
} EnShopnuts; // size 0x8A0

#endif //_EN_SHOPNUTS_H_
