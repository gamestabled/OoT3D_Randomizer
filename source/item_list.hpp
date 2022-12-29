#pragma once

#include "item.hpp"
#include "keys.hpp"

void ItemTable_Init();
Item& ItemTable(ItemKey itemKey);
void NewItem(ItemKey itemKey, Item item);
