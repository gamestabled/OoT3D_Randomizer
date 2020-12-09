#include "input.h"

#include "z3D/z3D.h"
#include "hid.h"
#include "3ds/svc.h"
#include "utils.h"

InputContext rInputCtx;

void Input_Update(void) {
    rInputCtx.cur.val = real_hid.pad.pads[real_hid.pad.index].curr.val;
    rInputCtx.pressed.val = (rInputCtx.cur.val) & (~rInputCtx.old.val);
    rInputCtx.up.val = (~rInputCtx.cur.val) & (rInputCtx.old.val);
    rInputCtx.old.val = rInputCtx.cur.val;
}

u32 Input_WaitWithTimeout(u32 msec) {
    u32 pressedKey = 0;
    u32 key = 0;
    u32 n = 0;

    // Wait for no keys to be pressed
    while (HID_PAD && (msec == 0 || n <= msec)) {
        svcSleepThread(1 * 1000 * 1000LL);
        n++;
    }

    if (msec != 0 && n >= msec) {
        return 0;
    }

    do {
        // Wait for a key to be pressed
        while (!HID_PAD && (msec == 0 || n < msec)) {
            svcSleepThread(1 * 1000 * 1000LL);
            n++;
        }

        if(msec != 0 && n >= msec) {
            return 0;
        }

        key = HID_PAD;

        //Make sure it's pressed
        for (u32 i = 0x26000; i > 0; i--) {
            if (key != real_hid.pad.pads[real_hid.pad.index].curr.val) break;
            if (i == 1) {
                pressedKey = 1;
            }
        }
    } while(!pressedKey);

    return key;
}

u32 Input_Wait(void) {
    return Input_WaitWithTimeout(0);
}
