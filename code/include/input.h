#include "z3D/z3D.h"
#include "hid.h"

typedef struct {
    btn_t cur;
    btn_t up;
    btn_t pressed;
    btn_t old;
} InputContext;

void InputContext_Update(void);

extern InputContext rInputCtx;