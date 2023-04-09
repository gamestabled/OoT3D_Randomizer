#include "z3D/z3D.h"
#include "hid.h"
#include "3ds/services/irrst.h"

typedef struct {
    btn_t cur;
    btn_t up;
    btn_t pressed;
    btn_t old;
    int16_t touchX;
    int16_t touchY;
    uint32_t touchPressed;
    uint32_t touchHeld;
    circlePosition cStick;
} InputContext;

void Input_Update(void);
u32 Input_WaitWithTimeout(u32 msec, u32 closingButton);
u32 Input_Wait(void);

extern InputContext rInputCtx;
