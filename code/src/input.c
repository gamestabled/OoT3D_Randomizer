#include "input.h"

#include "z3D/z3D.h"
#include "hid.h"

InputContext rInputCtx;

void InputContext_Update(void) {
    rInputCtx.cur.val = real_hid.pad.pads[real_hid.pad.index].curr.val;
    rInputCtx.pressed.val = (rInputCtx.cur.val) & (~rInputCtx.old.val);
    rInputCtx.up.val = (~rInputCtx.cur.val) & (rInputCtx.old.val);
    rInputCtx.old.val = rInputCtx.cur.val;
}
