#pragma once

#include <3ds.h>

#include <cstddef>
#include <vector>

class ItemLocation;

void AddItemToPool(std::vector<u32>& pool, u32 item, size_t count = 1);
u32 GetJunkItem();
void PlaceJunkInExcludedLocation(u32 il);
void GenerateItemPool();
void AddJunk();

extern std::vector<u32> ItemPool;
extern std::vector<u32> dungeonRewards;
