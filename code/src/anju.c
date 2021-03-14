#include "z3D/z3D.h"
#include "settings.h"

u32 EnNiwLady_CheckCuccoAmount(u32 cuccosInPen) {
    return cuccosInPen >= gSettingsContext.numRequiredCuccos;
}
