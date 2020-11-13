#pragma once
#include <string>
#include <set>
#include "item_location.hpp"

#include "../code/include/z3D/z3D.h"
#include "../code/src/item_override.h"


namespace Playthrough {

    class ItemOverride_Compare {
    public:
        bool operator()(ItemOverride lhs, ItemOverride rhs) const {
            return lhs.key.all < rhs.key.all;
        }
    };

    void Reset();
    int  Fill(int settings, u32 seed, std::set<ItemOverride, ItemOverride_Compare>& overrides);
    void PlaceSetItems(std::set<ItemOverride, ItemOverride_Compare>& overrides);
}
