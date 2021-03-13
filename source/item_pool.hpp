#pragma once
#include "item_list.hpp"
#include "item_location.hpp"
#include "settings.hpp"
#include <vector>

extern std::vector<Item>   AdvancementItemPool;
extern std::vector<Item>   ItemPool;
extern std::array<Item, 9> dungeonRewards;
extern void AddItemToPool(std::vector<Item>& pool, const Item& item, size_t count = 1);
extern Item GetJunkItem();
extern void PlaceJunkInExcludedLocation(ItemLocation* il);
extern void GenerateItemPool();
extern void AddJunk();
