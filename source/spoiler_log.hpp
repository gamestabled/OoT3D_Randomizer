#pragma once

#include <array>
#include <string>
#include <string_view>
#include "../code/src/spoiler_data.h"

using RandomizerHash = std::array<std::string, 5>;

void GenerateHash();
const RandomizerHash& GetRandomizerHash();

bool SpoilerLog_Write();
const SpoilerData& GetSpoilerData();

void PlacementLog_Msg(std::string_view msg);
void PlacementLog_Clear();
bool PlacementLog_Write();
