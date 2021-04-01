#pragma once

#include <vector>

extern bool CreatePresetDirectories();
extern std::vector<std::string> GetPresets();
extern void LoadCachedPreset();
extern bool LoadPreset(std::string_view presetName, bool print);
extern bool SaveSpecifiedPreset(std::string presetName);
extern bool SaveCachedPreset();
extern bool DeletePreset(std::string_view presetName);
