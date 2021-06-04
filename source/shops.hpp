#pragma once
#include "item.hpp"
#include "item_location.hpp"

#include <vector>
#include <string>
#include <array>

struct ItemAndPrice {
    std::string Name;
    int Price;
    bool Repurchaseable;
};

extern void SetVanillaShopItems();
extern std::vector<ItemKey> GetMinVanillaShopItems(int total_replaced);
extern int GetRandomShopPrice();
extern s16 GetRandomScrubPrice();
extern int GetShopsanityReplaceAmount();
extern std::string GetIceTrapName(u8 id);
extern int GetShopIndex(LocationKey loc);
extern int TransformShopIndex(int index);
extern void PlaceShopItems();

extern std::vector<ItemKey> ShopItems;
extern std::vector<ItemAndPrice> NonShopItems;
