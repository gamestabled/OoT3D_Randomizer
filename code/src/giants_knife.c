#include "z3D/z3D.h"
#include "settings.h"

u16 GK_SetDurability(void) {
    switch (gSettingsContext.gkDurability) {
        case GKDURABILITY_RANDOMRISK:
            return Bias(Hash(gRandInt)) + 1;
        case GKDURABILITY_RANDOMSAFE:
            return 10 + (gRandInt % 41);
    }
    return 8;
}
