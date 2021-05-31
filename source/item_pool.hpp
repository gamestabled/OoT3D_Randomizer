#pragma once

#include <3ds.h>

#include "keys.hpp"

#include <cstddef>
#include <vector>

class ItemLocation;

void AddItemToPool(std::vector<ItemKey>& pool, ItemKey item, size_t count = 1);
ItemKey GetJunkItem();
void PlaceJunkInExcludedLocation(LocationKey il);
void GenerateItemPool();
void AddJunk();

extern std::vector<ItemKey> ItemPool;
extern std::vector<ItemKey> dungeonRewards;
