#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>

#include <filesystem>
#include <vector>

#include "preset.hpp"
#include "settings.hpp"

namespace fs = std::filesystem;

//Creates preset directories if they don't exist
bool CreatePresetDirectories() {
  Result res;
  FS_Archive sdmcArchive;

  // Open SD archive
  if (!R_SUCCEEDED(res = FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) {
    return false;
  }

  //Create the 3ds directory if it doesn't exist
  FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, "/3ds"), FS_ATTRIBUTE_DIRECTORY);
  //Create the presets directory if it doesn't exist
  FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, "/3ds/presets"), FS_ATTRIBUTE_DIRECTORY);
  //Create the oot3d directory if it doesn't exist
  FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, "/3ds/presets/oot3d"), FS_ATTRIBUTE_DIRECTORY);

  // Close SD archive
  FSUSER_CloseArchive(sdmcArchive);
  return true;
}

//Gets the preset filenames
std::vector<std::string> GetPresets() {
  std::vector<std::string> presetEntries = {};
  for (const auto & entry : fs::directory_iterator("/3ds/presets/oot3d")) {
    if(entry.path().stem().string() != "CACHED_SETTINGS") {
      presetEntries.push_back(entry.path().stem().string());
    }
  }

  return presetEntries;
}

void LoadCachedPreset() {
  //If cache file exists, load it
  for (const auto & entry : fs::directory_iterator("/3ds/presets/oot3d")) {
    if(entry.path().stem().string() == "CACHED_SETTINGS") {
      LoadPreset("CACHED_SETTINGS", false); //File exists, open
    }
  }
}

static std::string PresetPath(std::string_view presetName) {
  return std::string("/3ds/presets/oot3d/").append(presetName).append(".bin");
}

//Load the selected preset
bool LoadPreset(std::string_view presetName, bool print) {

  Result res;
  FS_Archive sdmcArchive = 0;
  Handle presetFile;
  u32 bytesRead = 0;
  u32 totalRW = 0;

  const std::string filepath = PresetPath(presetName);

  // Open SD archive
  if (!R_SUCCEEDED(res = FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) {
    if (print) printf("\x1b[22;5HFailed to load SD Archive.");
    return false;
  }

  // Open preset file
  if (!R_SUCCEEDED(res = FSUSER_OpenFile(&presetFile, sdmcArchive, fsMakePath(PATH_ASCII, filepath.c_str()), FS_OPEN_WRITE | FS_OPEN_CREATE, 0))) {
    if (print) printf("\x1b[22;5HFailed to open preset file %s.", filepath.c_str());
    return false;
  }

  //Read ctx size
  size_t ctxSize;
  if (!R_SUCCEEDED(res = FSFILE_Read(presetFile, &bytesRead, totalRW, &ctxSize, sizeof(ctxSize)))) {
    if (print) printf("\x1b[22;5HFailed to read preset size.");
    return false;
  }
  totalRW += bytesRead;

  //If the sizes don't match, then the preset is incompatible (there's probably a better way to do this)
  if (ctxSize != sizeof(SettingsContext)) {
    return false;
  }

  //Read preset SettingsContext
  SettingsContext ctx;
  if (!R_SUCCEEDED(res = FSFILE_Read(presetFile, &bytesRead, totalRW, &ctx, sizeof(ctx)))) {
    return false;
  }

  FSFILE_Close(presetFile);
  FSUSER_CloseArchive(sdmcArchive);

  Settings::FillSettings(ctx);
  return true;
}

//Saves the new preset to a file
bool SavePreset(std::string_view presetName) {
  Result res;
  FS_Archive sdmcArchive = 0;
  Handle presetFile;
  u32 bytesWritten = 0;
  u32 totalRW = 0;

  const std::string filepath = PresetPath(presetName);
  SettingsContext ctx = Settings::FillContext();

  // Open SD archive
  if (!R_SUCCEEDED(res = FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) {
    return false;
  }

  // Open preset file
  if (!R_SUCCEEDED(res = FSUSER_OpenFile(&presetFile, sdmcArchive, fsMakePath(PATH_ASCII, filepath.c_str()), FS_OPEN_WRITE | FS_OPEN_CREATE, 0))) {
    return false;
  }

  // Write struct size to preset file
  totalRW = 0;
  size_t ctxSize = sizeof(ctx);
  if (!R_SUCCEEDED(res = FSFILE_Write(presetFile, &bytesWritten, totalRW, &ctxSize, sizeof(ctxSize), FS_WRITE_FLUSH))) {
    return false;
  }
  totalRW += bytesWritten;

  // Write struct to preset file
  if (!R_SUCCEEDED(res = FSFILE_Write(presetFile, &bytesWritten, totalRW, &ctx, sizeof(ctx), FS_WRITE_FLUSH))) {
    return false;
  }
  totalRW += bytesWritten;

  FSFILE_Close(presetFile);
  FSUSER_CloseArchive(sdmcArchive);

  return true;
}

//Save cached preset after choosing to generate
bool SaveCachedPreset() {
  return SavePreset("CACHED_SETTINGS");
}

//Saves the new preset to a file
bool SaveSpecifiedPreset(std::string presetName) {
  //don't save if the user cancelled
  if (presetName.empty()) {
    return false;
  }
  return SavePreset(presetName);
}


//Delete the selected preset
bool DeletePreset(std::string_view presetName) {
  Result res;
  FS_Archive sdmcArchive = 0;

  const std::string filepath = PresetPath(presetName);

  // Open SD archive
  if (!R_SUCCEEDED(res = FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) {
    printf("\x1b[22;5HFailed to load SD Archive.");
    return false;
  }

  FSUSER_DeleteFile(sdmcArchive, fsMakePath(PATH_ASCII, filepath.c_str()));
  return true;
}
