#pragma once
#include "../../code/include/z3D/z3D.h"
#include "../../code/src/item_override.h"

#include "../items/new_item_table.hpp"

#include <string>

class NewItem;

class NewItemLocation {
public:
    enum class Type {
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

    NewItemLocation(u8 scene_, Type type_, u8 flag_, std::string&& name_) : scene(scene_), type(type_), flag(flag_), name(std::move(name_)) {}

    static auto Base(u8 scene, u8 flag, std::string&& name) {
        return NewItemLocation{ scene, Type::Base, flag, std::move(name) };
    }

    static auto Chest(u8 scene, u8 flag, std::string&& name) {
        return NewItemLocation{ scene, Type::Chest, flag, std::move(name) };
    }

    ItemOverride_Key key() const {
        ItemOverride_Key key;
        key.all = 0;

        key.scene = scene;
        key.type = static_cast<u8>(type); //TODO make sure these match up
        key.flag = flag;
        return key;
    }

    NewItem* getPlacedItem() const {
        return placedItem;
    }

    void setPlacedItem(NewItem* item) {
        placedItem = item;
        //set price
    }

    void setAsHintable() {
        isHintable = true;
    }

private:
    u8 scene;
    Type type;
    u8 flag;

    std::string name;
    NewItem* placedItem = &NewItemTable::none;
    bool isHintable = false;
};
