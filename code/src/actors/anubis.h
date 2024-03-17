#ifndef _ANUBIS_H_
#define _ANUBIS_H_

#include "z3D/z3D.h"

typedef struct EnAnubice {
    /* 0x0000 */ Actor actor;
    /* 0x01A4 */ SkelAnime skelAnime;
    /* 0x0228 */ char unk_228[0x470];
    /* 0x0698 */ Actor* flameCircles[5];
    // ...
} EnAnubice;

void EnAnubice_rUpdate(Actor* thisx, GlobalContext* globalCtx);

#endif //_ANUBIS_H_
