#include "item.hpp"

#include <array>

#include "logic.hpp"
#include "random.hpp"
#include "item_pool.hpp"
#include "settings.hpp"
#include "../code/src/item_override.h"

Item::Item(ItemType type_, int getItemId_, ItemClass class_, bool* logicVar_, HintKey hintKey_, u16 price_, Text name_)
    : type(type_), getItemId(getItemId_), itemClass(class_), logicVar(logicVar_), hintKey(hintKey_), price(price_),
      name(std::move(name_)) {
}

Item::Item(ItemType type_, int getItemId_, ItemClass class_, u8* logicVar_, HintKey hintKey_, u16 price_, Text name_)
    : type(type_), getItemId(getItemId_), itemClass(class_), logicVar(logicVar_), hintKey(hintKey_), price(price_),
      name(std::move(name_)) {
}

Item::Item(ItemType type_, int getItemId_, ItemClass class_, bool* logicVar_, HintKey hintKey_, Text name_)
    : Item::Item(type_, getItemId_, class_, logicVar_, hintKey_, 0, name_) {
}

Item::Item(ItemType type_, int getItemId_, ItemClass class_, u8* logicVar_, HintKey hintKey_, Text name_)
    : Item::Item(type_, getItemId_, class_, logicVar_, hintKey_, 0, name_) {
}

Item::~Item() = default;

void Item::ApplyEffect() {
    // If this is a key ring, logically add as many keys as we could need
    if (FOREST_TEMPLE_KEY_RING <= hintKey && hintKey <= GANONS_CASTLE_KEY_RING) {
        *std::get<u8*>(logicVar) += 10;
    } else {
        if (std::holds_alternative<bool*>(logicVar)) {
            *std::get<bool*>(logicVar) = true;
        } else {
            *std::get<u8*>(logicVar) += 1;
        }
    }
    Logic::UpdateHelpers();
}

void Item::UndoEffect() {
    if (FOREST_TEMPLE_KEY_RING <= hintKey && hintKey <= GANONS_CASTLE_KEY_RING) {
        *std::get<u8*>(logicVar) -= 10;
    } else {
        if (std::holds_alternative<bool*>(logicVar)) {
            *std::get<bool*>(logicVar) = false;
        } else {
            *std::get<u8*>(logicVar) -= 1;
        }
    }
    Logic::UpdateHelpers();
}

ItemOverride_Value Item::Value() const {
    ItemOverride_Value val;
    val.all    = 0;
    val.itemId = getItemId;
    if (getItemId == GI_ICE_TRAP) {
        val.looksLikeItemId = RandomElement(IceTrapModels);
    }
    if (!Settings::ColoredBossKeys && (getItemId >= 0x95 && getItemId <= 0x9A)) { // Boss keys
        val.looksLikeItemId = GI_KEY_BOSS;
    }
    if (!Settings::ColoredKeys && (getItemId >= 0xAF && getItemId <= 0xB7)) { // Small keys
        val.looksLikeItemId = GI_KEY_SMALL;
    }
    if (type == ITEMTYPE_SHOP) {
        // With the current shopsanity implementation, we need a way to detect
        // regular shop items. This method should have no unintended side effects
        // unless there was a multiworld with 256 players... so, it should be fine.
        val.player = 0xFF;
    }
    return val;
}
