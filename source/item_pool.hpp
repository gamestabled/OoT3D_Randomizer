#pragma once

#include <cstddef>
#include <vector>

class Item;
class ItemLocation;

void AddItemToPool(std::vector<Item>& pool, const Item& item, size_t count = 1);
Item GetJunkItem();
void PlaceJunkInExcludedLocation(ItemLocation* il);
void GenerateItemPool();
void AddJunk();

extern std::vector<Item> AdvancementItemPool;
extern std::vector<Item> ItemPool;
extern std::vector<Item> dungeonRewards;

