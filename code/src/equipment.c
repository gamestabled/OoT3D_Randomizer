#include "z3D/z3D.h"
#include "savefile.h"
#include "settings.h"

/**
 * @return truthy value if deletion is overridden and should be skipped.
 */
s32 Equipment_OverrideDeletion(s32 equipType, s32 equipValue) {
    if (equipType == EQUIP_TYPE_SHIELD && gSettingsContext.extraShields != EXTRASHIELDS_NEVER) {
        switch (equipValue) {
            case EQUIP_VALUE_SHIELD_DEKU:
                return --gExtSaveData.dekuShieldsCount;
            case EQUIP_VALUE_SHIELD_HYLIAN:
                return --gExtSaveData.hylianShieldsCount;
        }
    }
    return FALSE; // No override, proceed with deletion
}
