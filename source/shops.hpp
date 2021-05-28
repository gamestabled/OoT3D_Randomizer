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
extern int GetShopIndex(u32 loc);
extern int TransformShopIndex(int index);
extern void PlaceShopItems();
extern void ShuffleShop(std::vector<u32>& ShopItems, std::vector<int> indicesToExclude);

extern std::vector<u32> ShopItems;
extern std::vector<ItemAndPrice> NonShopItems;
