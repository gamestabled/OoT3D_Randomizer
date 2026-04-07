#pragma once

#include "s_spoiler_data.h"
#include "s_scene_id.h"

#include <3ds.h>
#include <array>
#include <string>
#include <string_view>

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

extern const char* sceneNames[SCENE_MAX];
