#pragma once

#include <3ds.h>

#include "keys.hpp"

#include <vector>

extern std::vector<ItemKey> StartingInventory;

void GenerateStartingInventory();
void ApplyStartingInventory();
