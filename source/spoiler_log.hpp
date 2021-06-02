#pragma once

#include <array>
#include <string>
#include <string_view>

using RandomizerHash = std::array<std::string, 5>;

void GenerateHash();
const RandomizerHash& GetRandomizerHash();

bool SpoilerLog_Write();

void PlacementLog_Msg(std::string_view msg);
void PlacementLog_WriteSettings();
void PlacementLog_Clear();
bool PlacementLog_Write();
