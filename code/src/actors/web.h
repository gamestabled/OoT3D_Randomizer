#ifndef _WEB_H_
#define _WEB_H_

#include "z3D/z3D.h"

struct BgYdanSp;

typedef void (*BgYdanSpActionFunc)(struct BgYdanSp* this, GlobalContext* globalCtx);

typedef struct BgYdanSp {
    Actor base;
    char dyna[24];
    BgYdanSpActionFunc action_fn;
    char unk_1C0[36];
    f32 some_float;
    char unk_1E8[222];
    u8 timer;
} BgYdanSp;

typedef struct {
    Vec3f homePos;
    BgYdanSpActionFunc action_fn;
} BgYdanSp_SendData;

void BgYdanSp_rUpdate(Actor* thisx, GlobalContext* globalCtx);
void BgYdanSp_SetActionFn(BgYdanSp* this, BgYdanSpActionFunc new_action_fn);

#endif //_WEB_H_
