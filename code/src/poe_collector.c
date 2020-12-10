#include "z3D/z3D.h"
#include "settings.h"
#include "lib/printf.h"

// TODO: Custom text for the number of required points
// char EnGb_TextTemplate[] = "\x7F\x19Oh, you brought a Poe today!\x7F\x01\x7F\x1C\x7F\x19Hmmmm!\x7F\x01\x7F\x1C\x7F\x19Very interesting! This is a \x7F\x1D\x41Big Poe\x7F\x1D\x00!\x7F\x01\x7F\x1C\x7F\x19I'll buy it for \x7F\x1D\x4150 Rupees\x7F\x1D\x00.\x7F\x01\x7F\x1C\x7F\x19On top of that, I'll put \x7F\x1D\x41100 points \x7F\x1D\x00on\x7F\x1Cyour card.\x7F\x01\x7F\x1C\x7F\x19If you earn \x7F\x1D\x41%d points\x7F\x1D\x00, you'll be a\x7F\x1Chappy man! Heh heh.\x7F\x00";

u32 EnGb_CheckPoints(u32 points) {
    return (points == (gSettingsContext.bigPoeTargetCount * 100));
}

u16 EnGb_GetFirstTextbox(void) {
    return 0x9080 + gSettingsContext.bigPoeTargetCount;
}
