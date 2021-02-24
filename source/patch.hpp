#pragma once
#include <set>
#include <3ds.h>
#include "playthrough.hpp"
#include "settings.hpp"
#include "patch_symbols.hpp"
#include "../code/src/settings.h"
#include "../code/src/item_override.h"

#define V_TO_P(addr) (addr - 0x100000)
#define PATCH_CONSOLE 0
#define PATCH_CITRA 1

bool WritePatch();
