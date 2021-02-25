#include "starting_inventory.hpp"

using namespace Settings;

std::vector<Item> StartingInventory = {};

void AddItemToInventory(Item item, int count = 1) {
  StartingInventory.resize(StartingInventory.size() + count, item);
}

void GenerateStartingInventory() {
  StartingInventory.clear();

  if (Keysanity.Is(KEYSANITY_START_WITH)) {
    AddItemToInventory(ForestTemple_SmallKey, 5);
    AddItemToInventory(FireTemple_SmallKey, 8);
    AddItemToInventory(WaterTemple_SmallKey, 6);
    AddItemToInventory(SpiritTemple_SmallKey, 5);
    AddItemToInventory(ShadowTemple_SmallKey, 5);
    AddItemToInventory(GerudoTrainingGrounds_SmallKey, 9);
    AddItemToInventory(BottomOfTheWell_SmallKey, 3);
    AddItemToInventory(GanonsCastle_SmallKey, 2);
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
