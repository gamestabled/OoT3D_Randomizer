#pragma once
#include "item.hpp"
#include "item_location.hpp"

#include <vector>
#include <string>

struct ItemAndPrice {
    std::string Name;
    int Price;
};

extern void SetVanillaShopItems();
extern int GetRandomShopPrice();
extern s16 GetRandomScrubPrice();
extern int GetShopsanityReplaceAmount();
extern std::string GetIceTrapName(u8 id);
extern int GetShopIndex(ItemLocation* loc);
extern int TransformShopIndex(int index);
extern void PlaceShopItems();
extern void ShuffleShop(std::vector<Item>& ShopItems, std::vector<int> indicesToExclude);

extern std::vector<Item> ShopItems;
extern std::vector<ItemAndPrice> NonShopItems;
