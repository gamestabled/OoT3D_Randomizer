#pragma once

#include <vector>
#include "category.hpp"

extern bool CreatePresetDirectories();
extern std::vector<std::string> GetSettingsPresets();
extern void LoadCachedSettings();
extern bool SavePreset(std::string presetName, OptionCategory category);
extern bool LoadPreset(std::string presetName, OptionCategory category);
extern bool DeletePreset(std::string presetName, OptionCategory category);
extern bool SaveSpecifiedPreset(std::string presetName, OptionCategory category);
extern void SaveCachedSettings();
extern void LoadCachedSettings();
extern bool SaveCachedCosmetics();
extern bool LoadCachedCosmetics();
