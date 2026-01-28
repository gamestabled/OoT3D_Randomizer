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
#include "../code/src/spoiler_data.h"
#include "category.hpp"
#include "item_list.hpp"
#include "hint_list.hpp"
#include "settings.hpp"
#include "keys.hpp"

class Entrance;

enum class ItemLocationType {
    Base,
    Chest,
    Collectable,
    GSToken,
    GrottoScrub,
    Delayed,
    TempleReward,
    HintStone,
    OtherHint,
};

class SpoilerCollectionCheck {
  public:
    SpoilerCollectionCheckType type = SpoilerCollectionCheckType::SPOILER_CHK_NONE;
    u8 scene                        = 0;
    u8 flag                         = 0;

    SpoilerCollectionCheck() {
    }
    SpoilerCollectionCheck(SpoilerCollectionCheckType type_, u8 scene_, u8 flag_)
        : type(type_), scene(scene_), flag(flag_) {
    }

    static auto None() {
        return SpoilerCollectionCheck(SpoilerCollectionCheckType::SPOILER_CHK_NONE, 0x00, 0x00);
    }

    static auto AlwaysCollected() {
        return SpoilerCollectionCheck(SpoilerCollectionCheckType::SPOILER_CHK_ALWAYS_COLLECTED, 0x00, 0x00);
    }

    static auto ItemGetInf(u8 slot) {
        return SpoilerCollectionCheck(SpoilerCollectionCheckType::SPOILER_CHK_ITEM_GET_INF, 0x00, slot);
    }

    static auto EventChkInf(u8 flag) {
        return SpoilerCollectionCheck(SpoilerCollectionCheckType::SPOILER_CHK_EVENT_CHK_INF, 0xFF, flag);
    }

    static auto InfTable(u8 offset, u8 bit) {
        return SpoilerCollectionCheck(SpoilerCollectionCheckType::SPOILER_CHK_INF_TABLE, offset, bit);
    }

    static auto Collectable(u8 scene, u8 flag) {
        return SpoilerCollectionCheck(SpoilerCollectionCheckType::SPOILER_CHK_COLLECTABLE, scene, flag);
    }

    static auto Chest(u8 scene, u8 flag) {
        return SpoilerCollectionCheck(SpoilerCollectionCheckType::SPOILER_CHK_CHEST, scene, flag);
    }

    static auto Cow(u8 scene, u8 flag) {
        return SpoilerCollectionCheck(SpoilerCollectionCheckType::SPOILER_CHK_COW, scene, flag);
    }

    static auto Fishing(u8 bit) {
        return SpoilerCollectionCheck(SpoilerCollectionCheckType::SPOILER_CHK_MINIGAME, 0x00, bit);
    }

    static auto Scrub(u8 scene, u8 bit) {
        return SpoilerCollectionCheck(SpoilerCollectionCheckType::SPOILER_CHK_SCRUB, scene, bit);
    }

    static auto Biggoron(u8 mask) {
        return SpoilerCollectionCheck(SpoilerCollectionCheckType::SPOILER_CHK_BIGGORON, 0x00, mask);
    }

    static auto GerudoToken() {
        return SpoilerCollectionCheck(SpoilerCollectionCheckType::SPOILER_CHK_GERUDO_TOKEN, 0x00, 0x00);
    }

    static auto BigPoePoints() {
        return SpoilerCollectionCheck(SpoilerCollectionCheckType::SPOILER_CHK_POE_POINTS, 0x00, 0x00);
    }

    static auto ShopItem(u8 scene, u8 itemSlot) {
        return SpoilerCollectionCheck(SpoilerCollectionCheckType::SPOILER_CHK_SHOP_ITEM, scene, itemSlot);
    }

    static auto MagicBeans(u8 scene, u8 flag) {
        return SpoilerCollectionCheck(SpoilerCollectionCheckType::SPOILER_CHK_MAGIC_BEANS, scene, flag);
    }

    static auto MasterSword() {
        return SpoilerCollectionCheck(SpoilerCollectionCheckType::SPOILER_CHK_MASTER_SWORD, 0x00, 0x00);
    }
};

class ItemLocation {
  public:
    ItemLocation() = default;
    ItemLocation(u8 scene_, ItemLocationType type_, u8 flag_, std::string name_, HintKey hintKey_, ItemKey vanillaItem_,
                 std::vector<Category> categories_, u16 price_ = 0,
                 SpoilerCollectionCheck collectionCheck_           = SpoilerCollectionCheck(),
                 SpoilerCollectionCheckGroup collectionCheckGroup_ = SpoilerCollectionCheckGroup::GROUP_NO_GROUP)
        : scene(scene_), type(type_), flag(flag_), name(std::move(name_)), hintKey(hintKey_), vanillaItem(vanillaItem_),
          categories(std::move(categories_)), price(price_), collectionCheck(collectionCheck_),
          collectionCheckGroup(collectionCheckGroup_) {
    }

    ItemOverride_Key Key() const {
        ItemOverride_Key key;
        key.all = 0;

        key.scene = scene;
        key.type  = static_cast<u8>(type); // TODO make sure these match up
        key.flag  = flag;
        return key;
    }

    SpoilerCollectionCheck GetCollectionCheck() const {
        return collectionCheck;
    }

    SpoilerCollectionCheckGroup GetCollectionCheckGroup() const {
        return collectionCheckGroup;
    }

    u8 GetScene() const {
        return scene;
    }

    u8 GetFlag() const {
        return flag;
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

    const std::string& GetName() const {
        return name;
    }

    const Text& GetPlacedItemName() const {
        return ItemTable(placedItem).GetName();
    }

    const Item& GetPlacedItem() const {
        return ItemTable(placedItem);
    }

    ItemKey GetPlacedItemKey() const {
        return placedItem;
    }

    ItemKey GetVanillaItem() const {
        return vanillaItem;
    }

    void SetPlacedItem(const ItemKey item) {
        placedItem = item;
        SetPrice(ItemTable(placedItem).GetPrice());
    }

    // Saves an item to be set as placedItem later
    void SetDelayedItem(const ItemKey item) {
        delayedItem = item;
    }

    // Place the vanilla item in this location
    void PlaceVanillaItem() {
        placedItem = vanillaItem;
    }

    void ApplyPlacedItemEffect() {
        ItemTable(placedItem).ApplyEffect();
    }

    // Set placedItem as item saved in SetDelayedItem
    void SaveDelayedItem() {
        placedItem  = delayedItem;
        delayedItem = NONE;
    }

    u16 GetPrice() const {
        if (ItemTable(placedItem).GetItemType() == ITEMTYPE_SHOP) {
            return ItemTable(placedItem).GetPrice();
        }
        return price;
    }

    void SetPrice(u16 price_) {
        // don't override price if the price was set for shopsanity
        if (hasShopsanityPrice) {
            return;
        }
        price = price_;
    }

    void SetShopsanityPrice(u16 price_) {
        price              = price_;
        hasShopsanityPrice = true;
    }

    bool HasShopsanityPrice() const {
        return hasShopsanityPrice;
    }

    bool IsExcluded() const {
        return excludedOption.Value<bool>();
    }

    bool IsCategory(Category category) const {
        return std::any_of(categories.begin(), categories.end(), [category](auto entry) { return entry == category; });
    }

    bool IsDungeon() const {
        return (type != ItemLocationType::GSToken && (scene < 0x0E || (scene > 0x10 && scene < 0x1A))) ||
               (type == ItemLocationType::GSToken && scene < 0x0A);
    }

    bool IsOverworld() const {
        return !IsDungeon();
    }

    bool IsShop() const {
        return (scene >= 0x2C && scene <= 0x32);
    }

    Option* GetExcludedOption() {
        return &excludedOption;
    }

    const HintKey GetHintKey() const {
        return hintKey;
    }

    const HintText& GetHint() const {
        return Hint(hintKey);
    }

    bool IsHintedAt() const {
        return hintedAt;
    }

    void SetAsHinted() {
        hintedAt = true;
    }

    bool IsHidden() const {
        return hidden;
    }

    void SetHidden(const bool hidden_) {
        hidden = hidden_;
    }

    bool IsHintable() const {
        return isHintable;
    }

    void SetAsHintable() {
        isHintable = true;
    }

    void SetParentRegion(AreaKey region) {
        parentRegion = region;
    }

    AreaKey GetParentRegionKey() const {
        return parentRegion;
    }

    void AddExcludeOption() {
        // setting description  /*--------------------------------------------------*/
        std::string_view desc = "Decide which locations you want to exclude from\n"
                                "the location pool. Locations that require an item\n"
                                "to be placed at them based on your current\n"
                                "settings cannot be excluded and won't be shown\n"
                                "unless you change your settings.\n"
                                "\n"
                                "If you exclude too many locations, it might not\n"
                                "be possible to fill the world.";

        // add option to forbid any location from progress items
        if (name.length() < 23) {
            excludedOption = Option::Bool(name, { "Include", "Exclude" }, { desc });
        } else {
            // insert a newline character if the text is too long for one row
            size_t lastSpace        = name.rfind(' ', 23);
            std::string settingText = name;
            settingText.replace(lastSpace, 1, "\n ");

            excludedOption = Option::Bool(settingText, { "Include", "Exclude" }, { desc });
        }

        Settings::excludeLocationsOptionsVector[collectionCheckGroup].push_back(&excludedOption);
    }

    static auto Base(u8 scene, u8 flag, std::string&& name, const HintKey hintKey, const ItemKey vanillaItem,
                     std::vector<Category>&& categories,
                     SpoilerCollectionCheck collectionCheck           = SpoilerCollectionCheck(),
                     SpoilerCollectionCheckGroup collectionCheckGroup = SpoilerCollectionCheckGroup::GROUP_NO_GROUP) {
        return ItemLocation{ scene,       ItemLocationType::Base, flag, std::move(name), hintKey,
                             vanillaItem, std::move(categories),  0,    collectionCheck, collectionCheckGroup };
    }

    static auto Chest(u8 scene, u8 flag, std::string&& name, const HintKey hintKey, const ItemKey vanillaItem,
                      std::vector<Category>&& categories,
                      SpoilerCollectionCheckGroup collectionCheckGroup = SpoilerCollectionCheckGroup::GROUP_NO_GROUP) {
        return ItemLocation{ scene,
                             ItemLocationType::Chest,
                             flag,
                             std::move(name),
                             hintKey,
                             vanillaItem,
                             std::move(categories),
                             0,
                             SpoilerCollectionCheck(SpoilerCollectionCheckType::SPOILER_CHK_CHEST, scene, flag),
                             collectionCheckGroup };
    }

    static auto Chest(u8 scene, u8 flag, std::string&& name, const HintKey hintKey, const ItemKey vanillaItem,
                      std::vector<Category>&& categories, SpoilerCollectionCheck collectionCheck,
                      SpoilerCollectionCheckGroup collectionCheckGroup = SpoilerCollectionCheckGroup::GROUP_NO_GROUP) {
        return ItemLocation{ scene,       ItemLocationType::Chest, flag, std::move(name), hintKey,
                             vanillaItem, std::move(categories),   0,    collectionCheck, collectionCheckGroup };
    }

    static auto
    Collectable(u8 scene, u8 flag, std::string&& name, const HintKey hintKey, const ItemKey vanillaItem,
                std::vector<Category>&& categories,
                SpoilerCollectionCheckGroup collectionCheckGroup = SpoilerCollectionCheckGroup::GROUP_NO_GROUP) {
        return ItemLocation{ scene,
                             ItemLocationType::Collectable,
                             flag,
                             std::move(name),
                             hintKey,
                             vanillaItem,
                             std::move(categories),
                             0,
                             SpoilerCollectionCheck(SpoilerCollectionCheckType::SPOILER_CHK_COLLECTABLE, scene, flag),
                             collectionCheckGroup };
    }

    static auto
    Collectable(u8 scene, u8 flag, std::string&& name, const HintKey hintKey, const ItemKey vanillaItem,
                std::vector<Category>&& categories, SpoilerCollectionCheck collectionCheck,
                SpoilerCollectionCheckGroup collectionCheckGroup = SpoilerCollectionCheckGroup::GROUP_NO_GROUP) {
        return ItemLocation{ scene,       ItemLocationType::Collectable, flag, std::move(name), hintKey,
                             vanillaItem, std::move(categories),         0,    collectionCheck, collectionCheckGroup };
    }

    static auto
    GSToken(u8 scene, u8 flag, std::string&& name, const HintKey hintKey, std::vector<Category>&& categories,
            SpoilerCollectionCheckGroup collectionCheckGroup = SpoilerCollectionCheckGroup::GROUP_NO_GROUP) {
        return ItemLocation{ scene,
                             ItemLocationType::GSToken,
                             flag,
                             std::move(name),
                             hintKey,
                             GOLD_SKULLTULA_TOKEN,
                             std::move(categories),
                             0,
                             SpoilerCollectionCheck(SpoilerCollectionCheckType::SPOILER_CHK_GOLD_SKULLTULA, scene,
                                                    flag),
                             collectionCheckGroup };
    }

    static auto
    GrottoScrub(u8 scene, u8 flag, std::string&& name, const HintKey hintKey, const ItemKey vanillaItem,
                std::vector<Category>&& categories, SpoilerCollectionCheck collectionCheck = SpoilerCollectionCheck(),
                SpoilerCollectionCheckGroup collectionCheckGroup = SpoilerCollectionCheckGroup::GROUP_NO_GROUP) {
        return ItemLocation{ scene,       ItemLocationType::GrottoScrub, flag, std::move(name), hintKey,
                             vanillaItem, std::move(categories),         0,    collectionCheck, collectionCheckGroup };
    }

    static auto
    Delayed(u8 scene, u8 flag, std::string&& name, const HintKey hintKey, const ItemKey vanillaItem,
            std::vector<Category>&& categories, SpoilerCollectionCheck collectionCheck = SpoilerCollectionCheck(),
            SpoilerCollectionCheckGroup collectionCheckGroup = SpoilerCollectionCheckGroup::GROUP_NO_GROUP) {
        return ItemLocation{ scene,       ItemLocationType::Delayed, flag, std::move(name), hintKey,
                             vanillaItem, std::move(categories),     0,    collectionCheck, collectionCheckGroup };
    }

    static auto Reward(u8 scene, u8 flag, std::string&& name, const HintKey hintKey, const ItemKey vanillaItem,
                       std::vector<Category>&& categories,
                       SpoilerCollectionCheck collectionCheck           = SpoilerCollectionCheck(),
                       SpoilerCollectionCheckGroup collectionCheckGroup = SpoilerCollectionCheckGroup::GROUP_NO_GROUP) {
        return ItemLocation{ scene,       ItemLocationType::TempleReward, flag, std::move(name), hintKey,
                             vanillaItem, std::move(categories),          0,    collectionCheck, collectionCheckGroup };
    }

    static auto OtherHint(u8 scene, u8 flag, std::string&& name, std::vector<Category>&& categories) {
        return ItemLocation{ scene, ItemLocationType::OtherHint, flag, std::move(name), NONE,
                             NONE,  std::move(categories) };
    }

    static auto HintStone(u8 scene, u8 flag, std::string&& name, std::vector<Category>&& categories) {
        return ItemLocation{ scene, ItemLocationType::HintStone, flag, std::move(name), NONE,
                             NONE,  std::move(categories) };
    }

    void ResetVariables() {
        checked            = false;
        addedToPool        = false;
        placedItem         = NONE;
        delayedItem        = NONE;
        hintedAt           = false;
        isHintable         = false;
        price              = 0;
        hasShopsanityPrice = false;
        hidden             = false;
    }

  private:
    u8 scene;
    ItemLocationType type;
    u8 flag;
    bool checked = false;

    std::string name;
    HintKey hintKey     = NONE;
    ItemKey vanillaItem = NONE;
    bool hintedAt       = false;
    std::vector<Category> categories;
    bool addedToPool      = false;
    ItemKey placedItem    = NONE;
    ItemKey delayedItem   = NONE;
    Option excludedOption = Option::Bool(name, { "Include", "Exclude" }, { "", "" });
    u16 price             = 0;
    SpoilerCollectionCheck collectionCheck;
    SpoilerCollectionCheckGroup collectionCheckGroup;
    bool isHintable         = false;
    AreaKey parentRegion    = NONE;
    bool hasShopsanityPrice = false;
    bool hidden             = false;
};

class ItemOverride_Compare {
  public:
    bool operator()(ItemOverride lhs, ItemOverride rhs) const {
        return lhs.key.all < rhs.key.all;
    }
};

void LocationTable_Init();

ItemLocation* Location(LocationKey locKey);

extern std::vector<std::vector<LocationKey>> ShopLocationLists;

extern std::vector<LocationKey> gossipStoneLocations;

extern std::vector<LocationKey> dungeonRewardLocations;
extern std::vector<LocationKey> overworldLocations;
extern std::vector<LocationKey> allLocations;
extern std::vector<LocationKey> everyPossibleLocation;

// Item locations that only exist as child Link in hot areas.
// When Gloom Mode is enabled these will be automatically excluded and excepted from reachability validation.
extern std::vector<LocationKey> childOnlyHotLocations;

// set of overrides to write to the patch
extern std::set<ItemOverride, ItemOverride_Compare> overrides;

extern std::vector<std::vector<LocationKey>> playthroughLocations;
extern std::vector<LocationKey> wothLocations;
extern bool playthroughBeatable;
extern bool allLocationsReachable;
extern bool showItemProgress;

extern u16 itemsPlaced;

void GenerateLocationPool();
void PlaceItemInLocation(LocationKey loc, ItemKey item, bool applyEffectImmediately = false, bool setHidden = false);
std::vector<LocationKey> GetLocations(const std::vector<LocationKey>& locationPool, Category categoryInclude,
                                      Category categoryExclude = Category::cNull);
void LocationReset();
void ItemReset();
void HintReset();
void AddExcludedOptions();
void CreateItemOverrides();
