#ifndef _EN_BOX_H_
#define _EN_BOX_H_

#include "z3D/z3D.h"

typedef struct EnBox {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x01BC */ SkelAnime skelAnime;
    /* 0x0240 */ char unk_240[0x148];
    /* 0x0388 */ ZARInfo* zarInfo;
    /* 0x038C */ char unk_38C[0xC];
} EnBox; // size = 0x398

#endif //_EN_BOX_H_
