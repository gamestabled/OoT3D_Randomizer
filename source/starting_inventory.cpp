#include "starting_inventory.hpp"

using namespace Settings;

std::vector<Item> StartingInventory = {};

void AddItemToInventory(Item item, int count = 1) {
  StartingInventory.resize(StartingInventory.size() + count, item);
}

void GenerateStartingInventory() {
  StartingInventory.clear();

  if (Keysanity.Is(KEYSANITY_START_WITH)) {
    //                Dungeon small key item,          check if MQ dungeon                 MQ : Vanilla key count
    AddItemToInventory(ForestTemple_SmallKey,          (ForestTempleDungeonMode)          ? 6 : 5);
    AddItemToInventory(FireTemple_SmallKey,            (FireTempleDungeonMode)            ? 5 : 8);
    AddItemToInventory(WaterTemple_SmallKey,           (WaterTempleDungeonMode)           ? 2 : 6);
    AddItemToInventory(SpiritTemple_SmallKey,          (SpiritTempleDungeonMode)          ? 7 : 5);
    AddItemToInventory(ShadowTemple_SmallKey,          (ShadowTempleDungeonMode)          ? 6 : 5);
    AddItemToInventory(GerudoTrainingGrounds_SmallKey, (GerudoTrainingGroundsDungeonMode) ? 3 : 9);
    AddItemToInventory(BottomOfTheWell_SmallKey,       (BottomOfTheWellDungeonMode)       ? 2 : 3);
    AddItemToInventory(GanonsCastle_SmallKey,          (GanonsCastleDungeonMode)          ? 3 : 2);

  } else if (Keysanity.Is(KEYSANITY_VANILLA)) {
  /*Logic cannot handle vanilla key layout in some dungeons
    this is because vanilla expects the dungeon major item to be
    locked behind the keys, which is not always true in rando.
    We can resolve this by starting with some extra keys
    - OoT Randomizer*/
    if (SpiritTempleDungeonMode == DUNGEONMODE_MQ) {
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
