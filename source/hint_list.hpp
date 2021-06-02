#pragma once

#include "hints.hpp"
#include "keys.hpp"

#include <vector>

void HintTable_Init();
const HintText& Hint(u32 hintKey);
std::vector<HintText> GetHintCategory(HintCategory category);
