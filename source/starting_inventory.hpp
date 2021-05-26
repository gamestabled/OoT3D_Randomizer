#pragma once

#include <3ds.h>

#include <vector>

extern std::vector<u32> StartingInventory;

void GenerateStartingInventory();
void ApplyStartingInventory();
