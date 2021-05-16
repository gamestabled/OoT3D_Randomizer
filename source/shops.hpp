#pragma once
#include "item.hpp"

#include <vector>

extern void SetVanillaShopItems();
extern int GetRandomShopPrice();
extern s16 GetRandomScrubPrice();
extern void PlaceShopItems();
extern int GetShopsanityReplaceAmount();
extern void ShuffleShop(std::vector<Item>& ShopItems, std::vector<int> indicesToExclude);

extern std::vector<Item> ShopItems;
