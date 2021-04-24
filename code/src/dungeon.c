#include "settings.h"

u8 Dungeon_GetJabuJabusBellyDungeonMode() {
  if (gSettingsContext.jabuJabusBellyDungeonMode) {
    return DUNGEONMODE_MQ;
  } else {
    return DUNGEONMODE_VANILLA;
  }
}
