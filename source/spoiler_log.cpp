#include "spoiler_log.hpp"

#include "dungeon.hpp"
#include "item_list.hpp"
#include "item_location.hpp"
#include "random.hpp"
#include "settings.hpp"
#include "trial.hpp"
#include "tinyxml2.h"
#include "utils.hpp"

#include <3ds.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <string>
#include <vector>

namespace {
  FS_Archive sdmcArchive = 0;
  Handle placementlog;

  std::string placementtxt;

  constexpr std::array<std::string_view, 32> hashIcons = {
    "Deku Stick",
    "Deku Nut",
    "Bow",
    "Slingshot",
    "Fairy Ocarina",
    "Bombchu",
    "Longshot",
    "Boomerang",
    "Lens of Truth",
    "Beans",
    "Megaton Hammer",
    "Bottled Fish",
    "Bottled Milk",
    "Mask of Truth",
    "SOLD OUT",
    "Cucco",
    "Mushroom",
    "Saw",
    "Frog",
    "Master Sword",
    "Mirror Shield",
    "Kokiri Tunic",
    "Hover Boots",
    "Silver Gauntlets",
    "Gold Scale",
    "Shard of Agony",
    "Skull Token",
    "Heart Container",
    "Boss Key",
    "Compass",
    "Map",
    "Big Magic",
  };
}

static RandomizerHash randomizerHash;

void GenerateHash() {
  for (size_t i = 0; i < randomizerHash.size(); i++) {
    const auto iconIndex = static_cast<u8>(Random(0, hashIcons.size()));
    Settings::hashIconIndexes[i] = iconIndex;
    randomizerHash[i] = hashIcons[iconIndex];
  }
}

const RandomizerHash& GetRandomizerHash() {
  return randomizerHash;
}

static auto GetGeneralPath() {
  std::string path = "/3ds/" + Settings::seed;
  for (const auto& str : randomizerHash)
    path += str;
  return path;
}


static auto GetSpoilerLogPath() {
  return GetGeneralPath() + "-spoilerlog.xml";
}

static auto GetPlacementLogPath() {
  return GetGeneralPath() + "-placementlog.txt";
}

static void WriteSettings(std::string& log, const bool printAll = false) {
  //List Settings
  log += "Settings:\n";
  for (const MenuItem* menu : Settings::mainMenu) {
    //don't log the detailed logic, starting inventory, or exclude location menus yet
    if (menu->name == "Detailed Logic Settings" || menu->name == "Starting Inventory" || menu->name == "Exclude Locations" || menu->mode != OPTION_SUB_MENU) {
      continue;
    }

    for (const Option* setting : *menu->settingsList) {
      if ((!setting->IsHidden() && setting->IsCategory(OptionCategory::Setting)) || printAll) {
        log += "\t";
        log += setting->GetName();
        log += ": ";
        log += setting->GetSelectedOptionText();
        log += "\n";
      }
    }
  }

  //List Excluded Locations
  bool excludedHeader = false;
  for (const auto& l : Settings::excludeLocationsOptions) {
    if (l->GetSelectedOptionIndex() == EXCLUDE) {
      if (!excludedHeader) {
        log += "\nExcluded Locations:\n";
        excludedHeader = true;
      }
      std::string name = l->GetName().data();

      //get rid of newline characters if necessary
      if (name.find('\n') != std::string::npos)
        name.replace(name.find('\n'), 1, "");

      log += "\t";
      log += name;
      log += "\n";
    }
  }

  //List Starting Inventory
  bool inventoryHeader = false;
  //start i at 3 to skip over the toggle, 'Start with Consumables', and 'Start with Max Rupees'
  for (size_t i = 3; i < Settings::startingInventoryOptions.size(); i++) {
    const auto setting = Settings::startingInventoryOptions[i];
    if (setting->GetSelectedOptionIndex() != STARTINGINVENTORY_NONE) {
      //only print the header if there's at least 1 starting item
      if (!inventoryHeader) {
        log += "\nStarting Inventory:\n";
        inventoryHeader = true;
      }
      std::string item = setting->GetSelectedOptionText();

      log += "\t";
      log += setting->GetSelectedOptionText();
      log += "\n";
    }
  }

  //List Enabled Tricks
  bool trickHeader = false;
  for (const auto& l : Settings::detailedLogicOptions) {
    if (l->GetSelectedOptionIndex() == TRICK_ENABLED && l->IsCategory(OptionCategory::Setting)) {
      //only print the header if at least one trick is enabled
      if (!trickHeader) {
        log += "\nEnabled Tricks:\n";
        trickHeader = true;
      }

      std::string name = l->GetName().data();

      //get rid of newline characters if necessary
      if (name.find('\n') != std::string::npos)
        name.replace(name.find('\n'), 1, "");

      log += "\t";
      log += name;
      log += "\n";
    }
  }

  //Master Quest Dungeons
  if (Settings::MQDungeonCount.IsNot(0)) {
    log += "\nMaster Quest Dungeons:\n";
    for (const auto* dungeon : Dungeon::dungeonList) {
      if (dungeon->IsMQ()) {
        log += std::string("\t").append(dungeon->GetName()).append("\n");
      }
    }
    log += '\n';
  }

  //Required Trials
  if (Settings::GanonsTrialsCount.IsNot(0)) {
    log += "\nRequired Trials:\n";
    for (const auto* trial : Trial::trialList) {
      if (trial->IsRequired()) {
        log += std::string("\t").append(trial->GetName().english).append("\n");
      }
    }
    log += '\n';
  }
}

// Writes the location to the specified node.
static void WriteLocation(tinyxml2::XMLElement* parentNode, const LocationKey locationKey) {
  ItemLocation* location = Location(locationKey);

  auto node = parentNode->InsertNewChildElement("location");
  node->SetAttribute("name", location->GetName().c_str());
  node->SetText(location->GetPlacedItemName().c_str());
  if (location->IsCategory(Category::cShop)) {
    node->SetAttribute("price", location->GetPrice());
  }
  if (!location->IsAddedToPool()) {
    node->SetAttribute("not-added", true);
  }
}

// Writes the settings (without excluded locations, starting inventory and tricks) to the spoilerLog document.
static void WriteSettingsXML(tinyxml2::XMLDocument& spoilerLog, const bool printAll = false) {
  auto parentNode = spoilerLog.NewElement("settings");

  for (const MenuItem* menu : Settings::mainMenu) {
    //don't log the detailed logic, starting inventory, or exclude location menus yet
    if (menu->name == "Detailed Logic Settings"
      || menu->name == "Starting Inventory"
      || menu->name == "Exclude Locations"
      || menu->mode != OPTION_SUB_MENU
    ) {
      continue;
    }

    for (const Option* setting : *menu->settingsList) {
      if (printAll || (!setting->IsHidden() && setting->IsCategory(OptionCategory::Setting))) {
        auto node = parentNode->InsertNewChildElement("setting");
        node->SetAttribute("name", RemoveLineBreaks(setting->GetName()).c_str());
        node->SetText(setting->GetSelectedOptionText().c_str());
      }
    }
  }
  spoilerLog.RootElement()->InsertEndChild(parentNode);
}

// Writes the excluded locations to the spoiler log, if there are any.
static void WriteExcludedLocations(tinyxml2::XMLDocument& spoilerLog) {
  auto parentNode = spoilerLog.NewElement("excluded-locations");

  for (const auto& location : Settings::excludeLocationsOptions) {
    if (location->GetSelectedOptionIndex() == INCLUDE) {
      continue;
    }

    tinyxml2::XMLElement* node = spoilerLog.NewElement("location");
    node->SetAttribute("name", RemoveLineBreaks(location->GetName()).c_str());
    parentNode->InsertEndChild(node);
  }

  if (!parentNode->NoChildren()) {
    spoilerLog.RootElement()->InsertEndChild(parentNode);
  }
}

// Writes the starting inventory to the spoiler log, if there is any.
static void WriteStartingInventory(tinyxml2::XMLDocument& spoilerLog) {
  auto parentNode = spoilerLog.NewElement("starting-inventory");

  // Start at index 3 to skip over the toggle, "Start with Consumables", and "Start with Max Rupees".
  for (size_t i = 3; i < Settings::startingInventoryOptions.size(); ++i) {
    const auto setting = Settings::startingInventoryOptions[i];
    if (setting->GetSelectedOptionIndex() == STARTINGBOTTLE_NONE) {
      continue;
    }

    auto node = parentNode->InsertNewChildElement("item");
    node->SetAttribute("name", setting->GetSelectedOptionText().c_str());
  }

  if (!parentNode->NoChildren()) {
    spoilerLog.RootElement()->InsertEndChild(parentNode);
  }
}

// Writes the enabled tricks to the spoiler log, if there are any.
static void WriteEnabledTricks(tinyxml2::XMLDocument& spoilerLog) {
  auto parentNode = spoilerLog.NewElement("enabled-tricks");

  for (const auto& setting : Settings::detailedLogicOptions) {
    if (setting->GetSelectedOptionIndex() != TRICK_ENABLED || !setting->IsCategory(OptionCategory::Setting)) {
      continue;
    }

    auto node = parentNode->InsertNewChildElement("trick");
    node->SetAttribute("name", RemoveLineBreaks(setting->GetName()).c_str());
  }

  if (!parentNode->NoChildren()) {
    spoilerLog.RootElement()->InsertEndChild(parentNode);
  }
}

// Writes the Master Quest dungeons to the spoiler log, if there are any.
static void WriteMasterQuestDungeons(tinyxml2::XMLDocument& spoilerLog) {
  auto parentNode = spoilerLog.NewElement("master-quest-dungeons");

  for (const auto* dungeon : Dungeon::dungeonList) {
    if (dungeon->IsVanilla()) {
      continue;
    }

    auto node = parentNode->InsertNewChildElement("dungeon");
    node->SetAttribute("name", dungeon->GetName().c_str());
  }

  if (!parentNode->NoChildren()) {
    spoilerLog.RootElement()->InsertEndChild(parentNode);
  }
}

// Writes the required trails to the spoiler log, if there are any.
static void WriteRequiredTrials(tinyxml2::XMLDocument& spoilerLog) {
  auto parentNode = spoilerLog.NewElement("required-trials");

  for (const auto* trial : Trial::trialList) {
    if (trial->IsSkipped()) {
      continue;
    }

    auto node = parentNode->InsertNewChildElement("trial");
    node->SetAttribute("name", trial->GetName().GetEnglish().c_str());
  }

  if (!parentNode->NoChildren()) {
    spoilerLog.RootElement()->InsertEndChild(parentNode);
  }
}

// Writes the intended playthrough to the spoiler log, separated into spheres.
static void WritePlaythrough(tinyxml2::XMLDocument& spoilerLog) {
  auto playthroughNode = spoilerLog.NewElement("playthrough");

  for (uint i = 0; i < playthroughLocations.size(); ++i) {
    auto sphereNode = playthroughNode->InsertNewChildElement("sphere");
    sphereNode->SetAttribute("level", i + 1);

    for (const LocationKey key : playthroughLocations[i]) {
      WriteLocation(sphereNode, key);
    }
  }

  spoilerLog.RootElement()->InsertEndChild(playthroughNode);

  playthroughLocations.clear();
  playthroughBeatable = false;
}

// Writes the hints to the spoiler log, if they are enabled.
static void WriteHints(tinyxml2::XMLDocument& spoilerLog) {
  if (Settings::GossipStoneHints.Is(HINTS_NO_HINTS)) {
    return;
  }

  auto parentNode = spoilerLog.NewElement("hints");

  for (const LocationKey key : gossipStoneLocations) {
    ItemLocation* location = Location(key);

    auto node = parentNode->InsertNewChildElement("hint");
    node->SetAttribute("location", location->GetName().c_str());
    node->SetText(location->GetPlacedItemName().c_str());
  }

  spoilerLog.RootElement()->InsertEndChild(parentNode);
}

static void WriteAllLocations(tinyxml2::XMLDocument& spoilerLog) {
  auto parentNode = spoilerLog.NewElement("all-locations");

  for (const LocationKey key : allLocations) {
    WriteLocation(parentNode, key);
  }

  spoilerLog.RootElement()->InsertEndChild(parentNode);
}

bool SpoilerLog_Write() {
  auto spoilerLog = tinyxml2::XMLDocument();
  spoilerLog.InsertEndChild(spoilerLog.NewDeclaration());

  auto rootNode = spoilerLog.NewElement("spoiler-log");
  spoilerLog.InsertEndChild(rootNode);

  rootNode->SetAttribute("version", Settings::version.c_str());
  rootNode->SetAttribute("seed", Settings::seed.c_str());
  std::string hash = "";
  for (const std::string& str : randomizerHash) {
    hash += str + ", ";
  }
  hash.erase(hash.length() - 2); // Erase last comma
  rootNode->SetAttribute("hash", hash.c_str());

  WriteSettingsXML(spoilerLog);
  WriteExcludedLocations(spoilerLog);
  WriteStartingInventory(spoilerLog);
  WriteEnabledTricks(spoilerLog);
  WriteMasterQuestDungeons(spoilerLog);
  WriteRequiredTrials(spoilerLog);
  WritePlaythrough(spoilerLog);
  WriteHints(spoilerLog);
  WriteAllLocations(spoilerLog);

  auto e = spoilerLog.SaveFile(GetSpoilerLogPath().c_str());
  return e == tinyxml2::XML_SUCCESS;
}

void PlacementLog_Msg(std::string_view msg) {
  placementtxt += msg;
}

void PlacementLog_WriteSettings() {
  WriteSettings(placementtxt, true); //write settings even if they're hidden
}

void PlacementLog_Clear() {
  placementtxt = "";
}

bool PlacementLog_Write() {
  Result res = 0;
  u32 bytesWritten = 0;

  placementtxt += "\nSeed: ";
  placementtxt += Settings::seed;

  // Open SD archive
  if (!R_SUCCEEDED(res = FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) {
    return false;
  }

  // Open placementlog.txt
  if (!R_SUCCEEDED(res = FSUSER_OpenFile(&placementlog, sdmcArchive, fsMakePath(PATH_ASCII, GetPlacementLogPath().c_str()), FS_OPEN_CREATE | FS_OPEN_WRITE, 0))) {
    return false;
  }

  // Write to placementlog.txt
  if (!R_SUCCEEDED(res = FSFILE_Write(placementlog, &bytesWritten, 0, placementtxt.c_str(), placementtxt.size(), FS_WRITE_FLUSH))) {
    return false;
  }

  FSFILE_Close(placementlog);
  FSUSER_CloseArchive(sdmcArchive);

  return true;
}
