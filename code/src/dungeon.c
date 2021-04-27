#include "settings.h"

u8 Dungeon_CheckDekuTreeClear() {
  if (EventCheck(0x09) == 0) {
    return 0;
  } else {
    return 1;
  }
}

u8 Dungeon_GetJabuJabusBellyDungeonMode() {
  if (gSettingsContext.jabuJabusBellyDungeonMode) {
    return DUNGEONMODE_MQ;
  } else {
    return DUNGEONMODE_VANILLA;
  }
}
