#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <array>
#include <filesystem>
#include <fstream>
#include <vector>

#include "category.hpp"
#include "preset.hpp"
#include "settings.hpp"
#include "tinyxml2.h"

namespace fs = std::filesystem;

static std::string_view GetBasePath(OptionCategory category) {
  static constexpr std::array<std::string_view, 2> paths{
    "/3ds/presets/oot3dr/settings/",
    "/3ds/presets/oot3dr/cosmetics/",
  };

  switch(category) {
    case OptionCategory::Setting :
    case OptionCategory::Cosmetic :
      return paths[static_cast<size_t>(category)];
    case OptionCategory::Toggle :
      break;
  }
  return "";
}

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
  FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, "/3ds/presets/oot3dr"), FS_ATTRIBUTE_DIRECTORY);
  //Create the cosmetics directory if it doesn't exist
  FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, "/3ds/presets/oot3dr/cosmetics"), FS_ATTRIBUTE_DIRECTORY);
  //Create the settings directory if it doesn't exist
  FSUSER_CreateDirectory(sdmcArchive, fsMakePath(PATH_ASCII, "/3ds/presets/oot3dr/settings"), FS_ATTRIBUTE_DIRECTORY);

  // Close SD archive
  FSUSER_CloseArchive(sdmcArchive);
  return true;
}

//Gets the preset filenames
std::vector<std::string> GetSettingsPresets() {
  std::vector<std::string> presetEntries = {};
  for (const auto & entry : fs::directory_iterator(GetBasePath(OptionCategory::Setting))) {
    if(entry.path().stem().string() != "CACHED_SETTINGS") {
      presetEntries.push_back(entry.path().stem().string());
    }
  }
  return presetEntries;
}

std::string PresetPath(std::string presetName, OptionCategory category) {
  return std::string(GetBasePath(category)).append(presetName).append(".xml");
}

/* Presets are now saved as XML files using the tinyxml2 library.
   Documentation: https://leethomason.github.io/tinyxml2/index.html
*/
bool SavePreset(std::string presetName, OptionCategory category) {
  using namespace tinyxml2;

  XMLDocument preset = XMLDocument();
  preset.NewDeclaration();

  for (MenuItem* menu : Settings::mainMenu) {
    if (menu->mode != OPTION_SUB_MENU) {
      continue;
    }
    for (size_t i = 0; i < menu->settingsList->size(); i++) {
      Option* setting = menu->settingsList->at(i);
      if (setting->IsCategory(category)) {

        //Create all necessary elements
        XMLElement* newSetting = preset.NewElement("setting");
        XMLElement* settingName = preset.NewElement("settingName");
        XMLElement* valueName = preset.NewElement("valueName");
        XMLText* settingText = preset.NewText(setting->GetName().data());
        XMLText* valueText = preset.NewText(setting->GetSelectedOptionText().c_str());

        //Some setting names have punctuation in them. Set all values as CDATA so
        //there are no conflicts with XML
        settingText->SetCData(true);
        valueText->SetCData(true);

        //add elements to the document
        settingName->InsertEndChild(settingText);
        valueName->InsertEndChild(valueText);
        newSetting->InsertEndChild(settingName);
        newSetting->InsertEndChild(valueName);
        preset.InsertEndChild(newSetting);
      }
    }
  }

  //setup for file path variable
  std::string filepathStr = PresetPath(presetName, category);
  char* filepath = static_cast<char*>(malloc(filepathStr.length() + 1));
  std::memcpy(filepath, filepathStr.c_str(), filepathStr.length());
  filepath[filepathStr.length()] = '\0';

  XMLError e = preset.SaveFile(filepath);
  if (e != XML_SUCCESS) {
    return false;
  }
  return true;
}

//Read the preset XML file
bool LoadPreset(std::string presetName, OptionCategory category) {
  using namespace tinyxml2;

  //setup for opening the file
  std::string filepathStr = PresetPath(presetName, category);
  char* filepath = static_cast<char*>(malloc(filepathStr.length() + 1));
  std::memcpy(filepath, filepathStr.c_str(), filepathStr.length());
  filepath[filepathStr.length()] = '\0';

  XMLDocument preset;
  XMLError e = preset.LoadFile(filepath);
  if (e != XML_SUCCESS) {
    return false;
  }

  XMLNode* curNode = preset.FirstChild();

  for (MenuItem* menu : Settings::mainMenu) {
    if (menu->mode != OPTION_SUB_MENU) {
      continue;
    }

    for (size_t i = 0; i < menu->settingsList->size(); i++) {
      Option* setting = menu->settingsList->at(i);
      if (setting->IsCategory(category)) {

        /*Since presets are saved linearly, we can simply loop through the nodes as
          we loop through the settings to find most of the matching elements.*/
        std::string settingToFind = std::string{setting->GetName().data()};
        std::string curSettingName = curNode->FirstChildElement("settingName")->GetText();
        std::string curSettingValue = curNode->FirstChildElement("valueName")->GetText();

        if (curSettingName == settingToFind) {
          setting->SetSelectedIndexByString(curSettingValue);
          curNode = curNode->NextSibling();
        } else {
        /*If the current setting and element don't match, then search
          linearly from the beginning. This will get us back on track if the
          next setting and element line up with each other*/
          curNode = preset.FirstChild();
          bool settingFound = false;
          while (curNode != nullptr) {
            curSettingName = curNode->FirstChildElement("settingName")->GetText();
            curSettingValue = curNode->FirstChildElement("valueName")->GetText();

            if (curSettingName == settingToFind) {
              setting->SetSelectedIndexByString(curSettingValue);
              curNode = curNode->NextSibling();
              settingFound = true;
              break;
            }
            curNode = curNode->NextSibling();
          }
          //reset to the beginning if the setting wasn't found
          if (!settingFound) {
            curNode = preset.FirstChild();
          }
        }
      }
    }
  }
  return true;
}

//Delete the selected preset
bool DeletePreset(std::string presetName, OptionCategory category) {
  Result res;
  FS_Archive sdmcArchive = 0;

  const std::string filepath = PresetPath(presetName, category);

  // Open SD archive
  if (!R_SUCCEEDED(res = FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) {
    printf("\x1b[22;5HFailed to load SD Archive.");
    return false;
  }

  FSUSER_DeleteFile(sdmcArchive, fsMakePath(PATH_ASCII, filepath.c_str()));
  return true;
}

//Saves the new preset to a file
bool SaveSpecifiedPreset(std::string presetName, OptionCategory category) {
  //don't save if the user cancelled
  if (presetName.empty()) {
    return false;
  }
  return SavePreset(presetName, category);
}

void SaveCachedSettings() {
  SavePreset("CACHED_SETTINGS", OptionCategory::Setting);
}

void LoadCachedSettings() {
  //If cache file exists, load it
  for (const auto & entry : fs::directory_iterator(GetBasePath(OptionCategory::Setting))) {
    if(entry.path().stem().string() == "CACHED_SETTINGS") {
      LoadPreset("CACHED_SETTINGS", OptionCategory::Setting); //File exists, open
    }
  }
}

bool SaveCachedCosmetics() {
  return SavePreset("CACHED_COSMETICS", OptionCategory::Cosmetic);
}

bool LoadCachedCosmetics() {
  return LoadPreset("CACHED_COSMETICS", OptionCategory::Cosmetic);
}
