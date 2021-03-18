#ifndef _EN_FR_H_
#define _EN_FR_H_

#include "z3D/z3D.h"

typedef enum {
    /* 00 */ FROG_ZL, 
    /* 01 */ FROG_EPONA,
    /* 02 */ FROG_SARIA,
    /* 03 */ FROG_SUNS,
    /* 04 */ FROG_SOT,
    /* 05 */ FROG_STORMS,
    /* 06 */ FROG_CHOIR_SONG,
    /* 07 */ FROG_NO_SONG
} FrogSongType;

typedef struct EnFr {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ char unk_1A4[0xA9A];
    /* 0xC3E */ u8 songIndex;
    /* 0xC3F */ char unk_20C[0x5];
    /* 0xC44 */ s32 reward;
    /* 0xC48 */ char unk_C48[0x208];
} EnFr; // size 0xE50

#endif //_EN_FR_H_
