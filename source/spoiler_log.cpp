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

// Returns the randomizer hash as concatenated string, separated by comma.
const std::string GetRandomizerHashAsString() {
  std::string hash = "";
  for (const std::string& str : randomizerHash) {
    hash += str + ", ";
  }
  hash.erase(hash.length() - 2); // Erase last comma
  return hash;
}

static auto GetGeneralPath() {
  return "/3ds/" + Settings::seed + " (" + GetRandomizerHashAsString() + ")";
}

static auto GetSpoilerLogPath() {
  return GetGeneralPath() + "-spoilerlog.xml";
}

static auto GetPlacementLogPath() {
  return GetGeneralPath() + "-placementlog.xml";
}

// Writes the location to the specified node.
static void WriteLocation(
    tinyxml2::XMLElement* parentNode,
    const LocationKey locationKey,
    const bool withPadding = false
) {
  constexpr int16_t LONGEST_NAME = 56; // The longest name of a location.
  constexpr int16_t PRICE_ATTRIBUTE = 12; // Length of a 3-digit price attribute.
  ItemLocation* location = Location(locationKey);

  auto node = parentNode->InsertNewChildElement("location");
  node->SetAttribute("name", location->GetName().c_str());
  node->SetText(location->GetPlacedItemName().c_str());

  if (withPadding) {
    // Insert a padding so we get a kind of table in the XML document.
    int16_t requiredPadding = LONGEST_NAME - location->GetName().length();
    if (location->IsCategory(Category::cShop)) {
      // Shop items have short location names, but come with an additional price attribute.
      requiredPadding -= PRICE_ATTRIBUTE;
    }
    if (requiredPadding >= 0) {
      std::string padding(requiredPadding, ' ');
      node->SetAttribute("_", padding.c_str());
    }
  }

  if (location->IsCategory(Category::cShop)) {
    char price[6];
    sprintf(price, "%03d", location->GetPrice());
    node->SetAttribute("price", price);
  }
  if (!location->IsAddedToPool()) {
    node->SetAttribute("not-added", true);
  }
}

// Writes the settings (without excluded locations, starting inventory and tricks) to the spoilerLog document.
static void WriteSettings(tinyxml2::XMLDocument& spoilerLog, const bool printAll = false) {
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
      WriteLocation(sphereNode, key, true);
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
    WriteLocation(parentNode, key, true);
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
  rootNode->SetAttribute("hash", GetRandomizerHashAsString().c_str());

  WriteSettings(spoilerLog);
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

void PlacementLog_Clear() {
  placementtxt = "";
}

bool PlacementLog_Write() {
  auto placementLog = tinyxml2::XMLDocument();
  placementLog.InsertEndChild(placementLog.NewDeclaration());

  auto rootNode = placementLog.NewElement("placement-log");
  placementLog.InsertEndChild(rootNode);

  rootNode->SetAttribute("version", Settings::version.c_str());
  rootNode->SetAttribute("seed", Settings::seed.c_str());
  rootNode->SetAttribute("hash", GetRandomizerHashAsString().c_str());

  WriteSettings(placementLog, true); // Include hidden settings.
  WriteExcludedLocations(placementLog);
  WriteStartingInventory(placementLog);
  WriteEnabledTricks(placementLog);
  WriteMasterQuestDungeons(placementLog);
  WriteRequiredTrials(placementLog);

  placementtxt = "\n" + placementtxt;

  auto node = rootNode->InsertNewChildElement("log");
  auto contentNode = node->InsertNewText(placementtxt.c_str());
  contentNode->SetCData(true);

  auto e = placementLog.SaveFile(GetPlacementLogPath().c_str());
  return e == tinyxml2::XML_SUCCESS;
}
