#pragma once

#include <string>
#include <string_view>
#include <vector>
#include "item_location.hpp"

using RandomizerHash = std::array<std::string, 5>;
void GenerateHash();
const RandomizerHash& GetRandomizerHash();

bool SpoilerLog_Write();

void PlacementLog_Msg(std::string_view msg);
void PlacementLog_Clear();
bool PlacementLog_Write();
