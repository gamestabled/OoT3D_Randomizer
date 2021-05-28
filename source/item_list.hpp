#pragma once

#include "item.hpp"

void  ItemTable_Init();
Item& ItemTable(u32 itemKey);
void  NewItem(u32 itemKey, Item item);
