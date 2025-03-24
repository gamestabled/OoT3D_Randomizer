#ifndef _ANUBIS_H_
#define _ANUBIS_H_

#include "z3D/z3D.h"

typedef struct EnAnubice {
    /* 0x0000 */ Actor actor;
    /* 0x01A4 */ SkelAnime skelAnime;
    /* 0x0228 */ char unk_228[0x420];
    /* 0x0648 */ s16 isPlayerOutOfRange;
    /* 0x064A */ char unk_64A[0x4E];
    /* 0x0698 */ Actor* flameCircles[5];
    /* 0x06AC */ char unk_6AC[0x5C];
} EnAnubice;
_Static_assert(sizeof(EnAnubice) == 0x708, "EnAnubice size");

void EnAnubice_rUpdate(Actor* thisx, GlobalContext* globalCtx);

#endif //_ANUBIS_H_
