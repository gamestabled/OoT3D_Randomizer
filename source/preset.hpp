#pragma once

#include <string>
#include <vector>

#include <settings.hpp>
#include <item_location.hpp>

enum class OptionCategory;

void CreatePresetDirectories(FS_Archive sdmcArchive);
std::vector<std::string> GetSettingsPresets();
bool SavePreset(std::string_view presetName, OptionCategory category);
bool LoadPreset(std::string_view presetName, OptionCategory category);
bool DeletePreset(std::string_view presetName, OptionCategory category);
bool SaveSpecifiedPreset(std::string_view presetName, OptionCategory category);
void SaveCachedSettings();
void LoadCachedSettings();
bool SaveCachedCosmetics();
void LoadCachedCosmetics();

typedef struct {
    std::string_view name;
    std::string_view description;
    std::vector<std::pair<Option*, u8>> optionOverrides;
    std::vector<LocationKey> excludedLocations;
} PremadePreset;

extern std::vector<PremadePreset*> premadePresets;
