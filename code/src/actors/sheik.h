#ifndef _SHEIK_H_
#define _SHEIK_H_

#include "z3D/z3D.h"

typedef struct {
    Actor base;
    SkelAnime anime;
    char unk_228[0x98C];
    s16 eye_index;
    s16 blink_timer;
    s32 action;
    s32 draw_mode;
} EnXc;

void Sheik_Spawn(void);

#endif //_SHEIK_H_
