#pragma once
#include <string_view>
#include <vector>
#include "item_location.hpp"

extern std::array<std::string, 5> randomizerHash;

void GenerateHash();

bool SpoilerLog_Write();

void PlacementLog_Msg(std::string_view msg);
bool PlacementLog_Write();
