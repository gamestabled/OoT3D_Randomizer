#ifndef _TITLE_SCREEN_H_
#define _TITLE_SCREEN_H_

#include "z3D/z3D.h"

typedef struct {
    Actor actor;
    GlModel* logoModel;
    GlModel* fireModel;
    GlModel* copyrightModel;
    char unk_1B0[0x30];
} EnMag; //size 0x1E0;

void EnMag_rInit(Actor* thisx, GlobalContext* globalCtx);

#endif //_TITLE_SCREEN_H_
