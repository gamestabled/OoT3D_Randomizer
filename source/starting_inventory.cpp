#include "starting_inventory.hpp"

using namespace Settings;

std::vector<Item> StartingInventory = {};

void AddItemToInventory(Item item, int count = 1) {
  StartingInventory.resize(StartingInventory.size() + count, item);
}

void GenerateStartingInventory() {
  StartingInventory.clear();

  if (Keysanity.Is(KEYSANITY_START_WITH)) {
    if (ForestTempleDungeonMode == DUNGEONMODE_MQ) {
      AddItemToInventory(ForestTemple_SmallKey, 6);
    } else {
      AddItemToInventory(ForestTemple_SmallKey, 5);
    }

    if (FireTempleDungeonMode == DUNGEONMODE_MQ) {
      AddItemToInventory(FireTemple_SmallKey, 5);
    } else {
      AddItemToInventory(FireTemple_SmallKey, 8);
    }

    if (WaterTempleDungeonMode == DUNGEONMODE_MQ) {
      AddItemToInventory(WaterTemple_SmallKey, 2);
    } else {
      AddItemToInventory(WaterTemple_SmallKey, 6);
    }

    if (SpiritTempleDungeonMode == DUNGEONMODE_MQ) {
      AddItemToInventory(SpiritTemple_SmallKey, 7);
    } else {
      AddItemToInventory(SpiritTemple_SmallKey, 5);
    }

    if (ShadowTempleDungeonMode == DUNGEONMODE_MQ) {
      AddItemToInventory(ShadowTemple_SmallKey, 6);
    } else {
      AddItemToInventory(ShadowTemple_SmallKey, 5);
    }

    if (GerudoTrainingGroundsDungeonMode == DUNGEONMODE_MQ) {
      AddItemToInventory(GerudoTrainingGrounds_SmallKey, 3);
    } else {
      AddItemToInventory(GerudoTrainingGrounds_SmallKey, 9);
    }

    if (BottomOfTheWellDungeonMode == DUNGEONMODE_MQ) {
      AddItemToInventory(BottomOfTheWell_SmallKey, 2);
    } else {
      AddItemToInventory(BottomOfTheWell_SmallKey, 3);
    }

    if (GanonsCastleDungeonMode == DUNGEONMODE_MQ) {
      AddItemToInventory(GanonsCastle_SmallKey, 3);
    } else {
      AddItemToInventory(GanonsCastle_SmallKey, 2);
    }

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
