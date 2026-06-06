#ifndef _WOLFOS_H_
#define _WOLFOS_H_

#include "z3D/z3D.h"

typedef struct EnWf {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ char unk_1A4[0x03C];
    /* 0x1E0 */ SkelAnime skelAnime;
    /* 0x264 */ FaceAnimation faceAnim;
    /* 0x430 */ char unk_264[0xAE8];
} EnWf;
_Static_assert(sizeof(EnWf) == 0xF18, "EnWf size");

void EnWf_ReinitModels(EnWf* this);

#endif //_WOLFOS_H_
