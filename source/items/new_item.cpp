#include "new_item.hpp"

#include <variant>

#include "../logic.hpp"

NewItem::NewItem(Text name_, Type type_, int getItemId_, bool advancement_) :
        name(std::move(name_)),
        type(type_),
        getItemId(getItemId_),
        advancement(advancement_) {
}

// NewItem::NewItem(Text name_, ItemType type_, int getItemId_, bool advancement_, u8* logicVar_, HintKey hintKey_, u16 price_)
//     : name(std::move(name_)),
//       type(type_),
//       getItemId(getItemId_),
//       advancement(advancement_),
//       logicVar(logicVar_),
//       hintKey(hintKey_),
//       price(price_) {}

NewItem::~NewItem() = default;

void NewItem::applyEffect() {
    if (std::holds_alternative<bool*>(logicVar)) {
        *std::get<bool*>(logicVar) = true;
    } else {
        *std::get<uint8_t*>(logicVar) += 1;
    }
    Logic::UpdateHelpers();
}
