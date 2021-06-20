#include "deku_tree_mouth.h"
#include "settings.h"

u32 BgTreemouth_ShouldOpen(void) {
    if (gSaveContext.linkAge == AGE_CHILD || gSettingsContext.shuffleDungeonEntrances) {
      return 1;
    } else {
      return 0;
    }
}
