#ifndef _GORON_POT_H_
#define _GORON_POT_H_

#include "z3D/z3D.h"

typedef struct {
    Actor base;
    char dyna[24];
    char collider[32];
    char collider_element[160];
    void* action_fn;
    float unk_float;
    s16 unk_shorts[5];
    s16 timer;
    s16 spin_result;
    u8 dropped_reward;
} GoronPot;

#endif //_GORON_POT_H_
