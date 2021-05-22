#include "item.hpp"

#include <array>

#include "logic.hpp"
#include "random.hpp"
#include "hints.hpp"
#include "../code/src/item_override.h"

Item::Item(std::string name_, ItemType type_, int getItemId_, bool advancement_, bool* logicVar_, HintText* hintText_, u16 price_)
    : name(std::move(name_)),
      type(type_),
      getItemId(getItemId_),
      advancement(advancement_),
      logicVar(logicVar_),
      hintText(hintText_),
      price(price_) {}

Item::Item(std::string name_, ItemType type_, int getItemId_, bool advancement_, u8* logicVar_, HintText* hintText_, u16 price_)
    : name(std::move(name_)),
      type(type_),
      getItemId(getItemId_),
      advancement(advancement_),
      logicVar(logicVar_),
      hintText(hintText_),
      price(price_) {}

Item::~Item() = default;

void Item::ApplyEffect() {
    if (std::holds_alternative<bool*>(logicVar)) {
        *std::get<bool*>(logicVar) = true;
    } else {
        *std::get<u8*>(logicVar) += 1;
    }
    Logic::UpdateHelpers();
}

void Item::UndoEffect() {
    if (std::holds_alternative<bool*>(logicVar)) {
        *std::get<bool*>(logicVar) = false;
    } else {
        *std::get<u8*>(logicVar) -= 1;
    }
    Logic::UpdateHelpers();
}

ItemOverride_Value Item::Value() const {
    //Random list of major items for ice trap models
    static constexpr std::array<u16, 10> items = {
        GI_BOOMERANG,
        GI_HAMMER,
        GI_ARROW_LIGHT,
        0x80, //Progressive hookshot
        0x81, //Progressive strength
        0x82, //Progressive bomb bag
        0x83, //Progressive bow
        0x84, //Progressive slingshot
        0x85, //Progressive wallet
        0x8A, //Progressive magic
    };

    ItemOverride_Value val;
    val.all = 0;
    val.itemId = getItemId;
    if (getItemId == GI_ICE_TRAP) {
        val.looksLikeItemId = RandomElement(items);
    }
    if (type == ITEMTYPE_SHOP) {
        // With the current shopsanity implementation, we need a way to detect
        // regular shop items. This method should have no unintended side effects
        // unless there was a multiworld with 256 players... so, it should be fine.
        val.player = 0xFF;
    }
    return val;
}
