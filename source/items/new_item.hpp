#pragma once

#include <variant>
#include "../text.hpp"

class NewItem {
public:
    enum class Type {
        Item,
        Map,
        Compass,
        BossKey,
        SmallKey,
        Token,
        FortressSmallKey,
        Event,
        Drop,
        Refill,
        Song,
        Shop,
        DungeonReward,
    };

    NewItem() = default;
    NewItem(Text name_, Type type_, int getItemId_, bool advancement_);
    // NewItem(Text name_, Type type_, int getItemId_, bool advancement_);
    ~NewItem();

    bool isAdvancement() const {
        return advancement;
    }

    void applyEffect();

private:
    Text name;
    Type type;
    int getItemId;
    bool advancement;
    std::variant<bool*, uint8_t*> logicVar;
};
