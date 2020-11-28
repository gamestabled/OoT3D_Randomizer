#ifndef _ITEM_ETCETERA_H_
#define _ITEM_ETCETERA_H_

#include "z3D/z3D.h"

typedef struct ItemEtcetera {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ char unk_1A4[0x12];
    /* 0x1B6 */ s16 getItemId;
    /* 0x1B8 */ char unk_1B8[0x4];
} ItemEtcetera; // size 0x1BC

#endif //_ITEM_ETCETERA_H_
