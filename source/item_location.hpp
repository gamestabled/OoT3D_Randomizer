#pragma once

#include <algorithm>
#include <array>
#include <cstdio>
#include <functional>
#include <set>
#include <string>
#include <unistd.h>
#include <vector>

#include <3ds.h>

#include "../code/include/z3D/z3D.h"
#include "../code/src/item_override.h"
#include "category.hpp"
#include "item_list.hpp"
#include "settings.hpp"
#include "keys.hpp"

class Exit;

enum class ItemLocationType {
    Base,
    Chest,
    Collectable,
    GSToken,
    GrottoScrub,
    Delayed,
    TempleReward,
    Hint,
    HintStone,
};

class ItemLocation {
public:
    ItemLocation() = default;
    ItemLocation(u8 scene_, ItemLocationType type_, u8 flag_, std::string name_, u32 hintKey_, std::vector<Category> categories_, u16 price_ = 0)
        : scene(scene_), type(type_), flag(flag_), name(std::move(name_)), hintKey(hintKey_), categories(std::move(categories_)), price(price_) {}

    ItemOverride_Key Key() const {
        ItemOverride_Key key;
        key.all = 0;

        key.scene = scene;
        key.type = static_cast<u8>(type); //TODO make sure these match up
        key.flag = flag;
        return key;
    }

    u8 GetScene() const {
      return scene;
    }

    u8 GetFlag() const {
      return flag;
    }

    void Use() {
      used = true;
    }

    bool IsUsed() const {
      return used;
    }

    bool IsAddedToPool() const {
      return addedToPool;
    }

    void AddToPool() {
      addedToPool = true;
    }

    void RemoveFromPool() {
      addedToPool = false;
    }

    std::string_view GetName() const {
      return name;
    }

    std::string_view GetPlacedItemName() const {
      return ItemTable(placedItem).GetName();
    }

    u32 GetPlacedItem() const {
      return placedItem;
    }

    void SetPlacedItem(u32 item) {
      placedItem = item;
    }

    void SetPlacedShopItem(u32 item, u16 price_) {
      placedItem = item;
      price = price_;
    }

    //Saves an item to be set as placedItem later
    void SetDelayedItem(u32 item) {
      delayedItem = item;
    }

    void ApplyPlacedItemEffect() {
      ItemTable(placedItem).ApplyEffect();
    }

    //Set placedItem as item saved in SetDelayedItem
    void SaveDelayedItem() {
      placedItem = delayedItem;
      delayedItem = NONE;
    }

    u16 GetPrice() const {
      return price;
    }

    void SetPrice(u16 price_) {
      price = price_;
    }

    bool IsExcluded() const {
      return excludedOption.Value<bool>();
    }

    bool IsCategory(Category category) const {
      return std::any_of(categories.begin(), categories.end(),
                         [category](auto entry) { return entry == category; });
    }

    bool IsDungeon() const {
      return (type != ItemLocationType::GSToken && (scene < 0x0E || (scene > 0x10 && scene < 0x1A))) || (type == ItemLocationType::GSToken && scene < 0x0A);
    }

    bool IsOverworld() const {
      return !IsDungeon();
    }

    Option * GetExcludedOption() {
      return &excludedOption;
    }

    u32 GetHintKey() const {
      return hintKey;
    }

    bool IsHintedAt() const {
      return hintedAt;
    }

    void SetAsHinted() {
      hintedAt = true;
    }

    bool IsHintable() const {
      return isHintable;
    }

    void SetAsHintable() {
      isHintable = true;
    }

    void SetParentRegion(Exit* region) {
      parentRegion = region;
    }

    Exit* GetParentRegion() const {
      return parentRegion;
    }

    void AddExcludeOption() {
      //setting description  /*--------------------------------------------------*/
      std::string_view desc = "Decide which locations you want to exclude from\n"
                              "the location pool. Locations that require an item\n"
                              "to be placed at them based on your current\n"
                              "settings cannot be excluded and won't be shown\n"
                              "unless you change your settings.\n"
                              "\n"
                              "If you exclude to many locations, it might not be\n"
                              "possible to fill the world.";

      //add option to forbid any location from progress items
      if (name.length() < 23) {
        excludedOption = Option::Bool(name, {"Include", "Exclude"}, {desc});
      } else {
        //insert a newline character if the text is too long for one row
        size_t lastSpace = name.rfind(' ', 23);
        std::string settingText = name;
        settingText.replace(lastSpace, 1, "\n ");

        excludedOption = Option::Bool(settingText, {"Include", "Exclude"}, {desc});
      }

      Settings::excludeLocationsOptions.push_back(&excludedOption);
    }

    static auto Base(u8 scene, u8 flag, std::string&& name, u32 hintKey, std::vector<Category>&& categories) {
        return ItemLocation{scene, ItemLocationType::Base, flag, std::move(name), hintKey, std::move(categories)};
    }

    static auto Chest(u8 scene, u8 flag, std::string&& name, u32 hintKey, std::vector<Category>&& categories) {
        return ItemLocation{scene, ItemLocationType::Chest, flag, std::move(name), hintKey, std::move(categories)};
    }

    static auto Collectable(u8 scene, u8 flag, std::string&& name, u32 hintKey, std::vector<Category>&& categories) {
        return ItemLocation{scene, ItemLocationType::Collectable, flag, std::move(name), hintKey, std::move(categories)};
    }

    static auto GSToken(u8 scene, u8 flag, std::string&& name, u32 hintKey, std::vector<Category>&& categories) {
        return ItemLocation{scene, ItemLocationType::GSToken, flag, std::move(name), hintKey, std::move(categories)};
    }

    static auto GrottoScrub(u8 scene, u8 flag, std::string&& name, u32 hintKey, std::vector<Category>&& categories) {
        return ItemLocation{scene, ItemLocationType::GrottoScrub, flag, std::move(name), hintKey, std::move(categories)};
    }

    static auto Delayed(u8 scene, u8 flag, std::string&& name, u32 hintKey, std::vector<Category>&& categories) {
        return ItemLocation{scene, ItemLocationType::Delayed, flag, std::move(name), hintKey, std::move(categories)};
    }

    static auto Reward(u8 scene, u8 flag, std::string&& name, u32 hintKey, std::vector<Category>&& categories) {
        return ItemLocation{scene, ItemLocationType::TempleReward, flag, std::move(name), hintKey, std::move(categories)};
    }

    static auto Hint(u8 scene, u8 flag, std::string&& name, std::vector<Category>&& categories) {
        return ItemLocation{scene, ItemLocationType::HintStone, flag, std::move(name), NONE, std::move(categories)};
    }

    static auto HintStone(u8 scene, u8 flag, std::string&& name, std::vector<Category>&& categories) {
        return ItemLocation{scene, ItemLocationType::HintStone, flag, std::move(name), NONE, std::move(categories)};
    }

    void ResetVariables() {
      used = false;
      checked = false;
      addedToPool = false;
      placedItem = NONE;
      delayedItem = NONE;
      hintedAt = false;
      isHintable = false;
      price = 0;
    }

private:
    u8 scene;
    ItemLocationType type;
    u8 flag;
    bool used = false;
    bool checked = false;

    std::string name;
    u32 hintKey = NONE;
    bool hintedAt = false;
    std::vector<Category> categories;
    bool addedToPool = false;
    u32 placedItem = NONE;
    u32 delayedItem = NONE;
    Option excludedOption = Option::Bool(name, {"Include", "Exclude"}, {"", ""});
    u16 price = 0;
    bool isHintable = false;
    Exit* parentRegion = nullptr;
};

class ItemOverride_Compare {
public:
    bool operator()(ItemOverride lhs, ItemOverride rhs) const {
        return lhs.key.all < rhs.key.all;
    }
};

void LocationTable_Init();

ItemLocation* Location(u32 locKey);

extern std::vector<std::vector<u32>> ShopLocationLists;

extern std::vector<u32> gossipStoneLocations;

extern std::vector<u32> dungeonRewardLocations;
extern std::vector<u32> overworldLocations;
extern std::vector<u32> allLocations;
extern std::vector<u32> everyPossibleLocation;

//set of overrides to write to the patch
extern std::set<ItemOverride, ItemOverride_Compare> overrides;

extern std::vector<std::vector<u32>> playthroughLocations;
extern bool playthroughBeatable;

extern u16 itemsPlaced;

void GenerateLocationPool();
void PlaceItemInLocation(u32 loc, u32 item, bool applyEffectImmediately = false);
void PlaceShopItemInLocation(u32 loc, u32 item, u16 price, bool applyEffectImmediately = false);
std::vector<u32> GetLocations(const std::vector<u32>& locationPool, Category category);
void LocationReset();
void ItemReset();
void HintReset();
void AddExcludedOptions();
void CreateOverrides();
