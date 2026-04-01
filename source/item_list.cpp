#include "item_list.hpp"
#include <array>

std::array<Item, KEY_ENUM_MAX> itemTable;

Item& ItemTable(const ItemKey itemKey) {
    return itemTable[itemKey];
}

// This function should only be used to place items containing hint text
// at gossip stone locations.
void NewItem(const ItemKey itemKey, const Item item) {
    if (itemKey <= BUY_RED_POTION_50) {
        printf("\x1b[25;0HWARNING: ATTEMPTED TO OVERWRITE ITEM %lu\n", itemKey);
        return;
    }

    itemTable[itemKey] = item;
}
