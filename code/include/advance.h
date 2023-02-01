/*
 * This comes from a file originally written by n3rdswithgame
 */

#ifndef ADVANCE_H
#define ADVANCE_H

#include <stdint.h>
#include "hid.h"
#include "z3D/z3D.h"

typedef enum {
    NORMAL = 0,
    PAUSED,
    STEP,
    LATCHED
} frame_state_t;

typedef struct {
    frame_state_t advance_state;
    uint8_t latched;
} advance_ctx_t;

typedef struct {
    btn_t cur;
    btn_t up;
    btn_t pressed;
    btn_t old;
} advance_input_t;

extern advance_ctx_t advance_ctx;
extern advance_input_t inputs;

#endif // ADVANCE_H
