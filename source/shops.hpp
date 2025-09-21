#pragma once
#include "item.hpp"
#include "item_location.hpp"

#include <vector>
#include <array>

struct ItemAndPrice {
    Text Name;
    int Price;
    bool Repurchaseable;
};

extern void PlaceVanillaShopItems();
extern std::vector<ItemKey> GetMinVanillaShopItems(int total_replaced);
extern int GetShopPrice();
extern s16 GetRandomScrubPrice();
extern int GetShopsanityReplaceAmount();
extern Text GetIceTrapName(u8 id);
extern int GetShopIndex(LocationKey loc);
extern int TransformShopIndex(int index);

extern std::vector<ItemAndPrice> NonShopItems;
