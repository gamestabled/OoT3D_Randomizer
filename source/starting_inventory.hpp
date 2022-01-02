#pragma once

#include <3ds.h>

#include "keys.hpp"

#include <vector>

extern std::vector<ItemKey> StartingInventory;
extern u8 AdditionalHeartContainers;

void GenerateStartingInventory();
bool StartingInventoryHasBottle();
void ApplyStartingInventory();
