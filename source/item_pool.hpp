#pragma once
#include "item_list.hpp"
#include "settings.hpp"
#include <vector>

extern std::vector<Item>   AdvancementItemPool;
extern std::vector<Item>   ItemPool;
extern std::array<Item, 9> dungeonRewards;
extern void GenerateItemPool();
extern void AddGreenRupee();
