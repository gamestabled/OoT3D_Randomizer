#pragma once
#include <string>
#include <set>
#include "item_location.hpp"

#include "../code/include/z3D/z3D.h"

namespace Playthrough {
    int Playthrough_Init(u32 seed);
    int Playthrough_Repeat(int count = 1);
}
