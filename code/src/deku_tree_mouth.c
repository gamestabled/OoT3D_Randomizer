#include "settings.h"
#include "z3D/z3D.h"

u32 BgTreemouth_ShouldOpen(void) {
    if (gSaveContext.linkAge == AGE_CHILD || gSettingsContext.shuffleDungeonEntrances) {
      return 1;
    } else {
      return 0;
    }
}
