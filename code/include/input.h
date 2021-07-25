#include "z3D/z3D.h"
#include "hid.h"

typedef struct {
    btn_t cur;
    btn_t up;
    btn_t pressed;
    btn_t old;
} InputContext;

void Input_Update(void);
u32 Input_WaitWithTimeout(u32 msec, u32 closingButton);
u32 Input_Wait(void);
u32 buttonCheck(u32 key);

extern InputContext rInputCtx;
