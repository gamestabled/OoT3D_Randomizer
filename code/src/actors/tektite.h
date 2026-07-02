#ifndef _TEKTITE_H_
#define _TEKTITE_H_

#include "z3D/z3D.h"

typedef enum EnTiteType {
    /* -2 */ TEKTITE_BLUE = -2,
    /* -1 */ TEKTITE_RED,
} EnTiteType;

typedef struct EnTite {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ SkelAnime anime;
    /* 0x228 */ char unk_228[0x4D8];
} EnTite;
_Static_assert(sizeof(EnTite) == 0x700, "EnTite size");

void EnTite_ReinitModels(EnTite* this);

#endif //_TEKTITE_H_
