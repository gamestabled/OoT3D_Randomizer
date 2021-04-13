#include "starting_inventory.hpp"
#include "dungeon.hpp"
#include "debug.hpp"
#include <unistd.h>

#include "item_list.hpp"
#include "settings.hpp"

using namespace Settings;
using namespace Dungeon;

std::vector<Item> StartingInventory;

static void AddItemToInventory(const Item& item, size_t count = 1) {
  StartingInventory.insert(StartingInventory.end(), count, item);
}

void GenerateStartingInventory() {
  StartingInventory.clear();

  if (MapsAndCompasses.Is(MAPSANDCOMPASSES_START_WITH)) {
    for (auto* dungeon : dungeonList) {
      if (dungeon->GetMap() != NoItem) {
        AddItemToInventory(dungeon->GetMap());
      }

      if (dungeon->GetCompass() != NoItem) {
        AddItemToInventory(dungeon->GetCompass());
      }
    }
  }

  if (Keysanity.Is(KEYSANITY_START_WITH)) {
    for (auto* dungeon : dungeonList) {
      if (dungeon->GetSmallKeyCount() > 0) {
        AddItemToInventory(dungeon->GetSmallKey(), dungeon->GetSmallKeyCount());
      }
    }
  } else if (Keysanity.Is(KEYSANITY_VANILLA)) {
    // Logic cannot handle vanilla key layout in some dungeons
    // this is because vanilla expects the dungeon major item to be
    // locked behind the keys, which is not always true in rando.
    // We can resolve this by starting with some extra keys
    // - OoT Randomizer
    if (SpiritTemple.IsMQ()) {
      AddItemToInventory(SpiritTemple_SmallKey, 3);
    }
  }

  if (BossKeysanity.Is(BOSSKEYSANITY_START_WITH)) {
    AddItemToInventory(ForestTemple_BossKey);
    AddItemToInventory(FireTemple_BossKey);
    AddItemToInventory(WaterTemple_BossKey);
    AddItemToInventory(SpiritTemple_BossKey);
    AddItemToInventory(ShadowTemple_BossKey);
  }

  if (GanonsBossKey.Is(GANONSBOSSKEY_START_WITH)) {
    AddItemToInventory(GanonsCastle_BossKey);
  }
}

void ApplyStartingInventory() {
  for (Item& item : StartingInventory) {
    item.ApplyEffect();
  }
}
