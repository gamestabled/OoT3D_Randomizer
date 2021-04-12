#pragma once

#include <string>
#include <vector>

enum class OptionCategory;

bool CreatePresetDirectories();
std::vector<std::string> GetSettingsPresets();
void LoadCachedSettings();
bool SavePreset(std::string presetName, OptionCategory category);
bool LoadPreset(std::string presetName, OptionCategory category);
bool DeletePreset(std::string presetName, OptionCategory category);
bool SaveSpecifiedPreset(std::string presetName, OptionCategory category);
void SaveCachedSettings();
void LoadCachedSettings();
bool SaveCachedCosmetics();
bool LoadCachedCosmetics();
