#pragma once

#include <3ds.h>

#include <array>
#include <string>
#include <string_view>
#include "../code/src/spoiler_data.h"

using RandomizerHash = std::array<std::string, 5>;

void InitLogDirectories(FS_Archive sdmcArchive);

void GenerateHash();
const RandomizerHash& GetRandomizerHash();

void WriteIngameSpoilerLog();

bool SpoilerLog_Write();
const SpoilerData* GetSpoilerData();
const SpoilerDataLocs* GetSpoilerDataLocs(size_t index);

void PlacementLog_Msg(std::string_view msg);
void PlacementLog_Clear();
bool PlacementLog_Write();
