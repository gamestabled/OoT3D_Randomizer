#pragma once

#include <3ds.h>
#include <string>
#include <variant>

union ItemOverride_Value;

enum ItemType {
    ITEMTYPE_ITEM,
    ITEMTYPE_MAP,
    ITEMTYPE_COMPASS,
    ITEMTYPE_BOSSKEY,
    ITEMTYPE_SMALLKEY,
    ITEMTYPE_TOKEN,
    ITEMTYPE_FORTRESS_SMALLKEY,
    ITEMTYPE_EVENT,
    ITEMTYPE_DROP,
    ITEMTYPE_REFILL,
    ITEMTYPE_SONG,
    ITEMTYPE_SHOP,
    ITEMTYPE_DUNGEONREWARD
};

class Item {
public:
    Item(std::string name_, ItemType type_, int getItemId_, bool advancement_, bool* logicVar_, u16 price_ = 0);
    Item(std::string name_, ItemType type_, int getItemId_, bool advancement_, u8* logicVar_, u16 price_ = 0);
    ~Item();

    void ApplyEffect();
    void UndoEffect();

    ItemOverride_Value Value() const;

    std::string_view GetName() const {
        return name;
    }

    bool IsAdvancement() const {
        return advancement;
    }

    int GetItemID() const {
        return getItemId;
    }

    ItemType GetItemType() const {
        return type;
    }

    u16 GetPrice() const {
        return price;
    }

    void SetAsPlaythrough() {
        playthrough = true;
    }

    bool IsPlaythrough() const {
        return playthrough;
    }

    bool IsBottleItem() const {
        return getItemId == 0x0F || //Empty Bottle
               getItemId == 0X14 || //Bottle with Milk
              (getItemId >= 0x8C && getItemId <= 0x94); //Rest of bottled contents
    }

    bool operator== (const Item& right) const {
        return type == right.GetItemType() && getItemId == right.GetItemID();
    }

    bool operator!= (const Item& right) const {
        return !operator==(right);
    }

private:
    std::string name;
    ItemType type;
    int  getItemId;
    bool advancement;
    std::variant<bool*, u8*> logicVar;
    u16  price;
    bool playthrough = false;
};
