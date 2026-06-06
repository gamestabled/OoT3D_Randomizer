#ifndef _REDEAD_H_
#define _REDEAD_H_

#include "z3D/z3D.h"

typedef enum EnRdType {
    /* -3 */ REDEAD_TYPE_GIBDO_RISING_OUT_OF_COFFIN = -3,
    /* -2 */ REDEAD_TYPE_GIBDO,
    /* -1 */ REDEAD_TYPE_DOES_NOT_MOURN,
    /*  0 */ REDEAD_TYPE_DOES_NOT_MOURN_IF_WALKING,
    /*  1 */ REDEAD_TYPE_REGULAR,
    /*  2 */ REDEAD_TYPE_CRYING,
    /*  3 */ REDEAD_TYPE_INVISIBLE,
} EnRdType;

typedef struct EnRd {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ char unk_1A4[0x03C];
    /* 0x1E0 */ SkelAnime skelAnime;
    /* 0x264 */ char unk_264[0x768];
} EnRd;
_Static_assert(sizeof(EnRd) == 0x9CC, "EnRd size");

void EnRd_ReinitModels(EnRd* this);

#endif //_REDEAD_H_
