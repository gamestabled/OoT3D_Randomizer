#ifndef _TITLE_SCREEN_H_
#define _TITLE_SCREEN_H_

#include "z3D/z3D.h"

typedef struct {
    Actor actor;
    SkeletonAnimationModel* logoModel;
    SkeletonAnimationModel* fireModel;
    SkeletonAnimationModel* copyrightModel;
    char unk_1B0[0x30];
} EnMag; // size 0x1E0;

void EnMag_rInit(Actor* thisx, GlobalContext* globalCtx);

extern u8 missingRomfsAlert;
extern s16 romfsAlertFrames;

#endif //_TITLE_SCREEN_H_
