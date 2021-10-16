#pragma once

#include <array>
#include <string>
#include <string_view>
#include "../code/src/spoiler_data.h"

using RandomizerHash = std::array<std::string, 5>;

void GenerateHash();
void SetSpoilerLogPassCode(u32 passCode);
const RandomizerHash& GetRandomizerHash();

bool SpoilerLog_Write(u8 onlyInGameTracker);
const SpoilerData& GetSpoilerData();

void PlacementLog_Msg(std::string_view msg);
void PlacementLog_Clear();
bool PlacementLog_Write();
