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
#include <map>
#include <set>
#include <string>
#include <unordered_map>
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
static SpoilerData spoilerData;

void GenerateHash() {
  for (size_t i = 0; i < randomizerHash.size(); i++) {
    const auto iconIndex = static_cast<u8>(Random(0, hashIcons.size()));
    Settings::hashIconIndexes[i] = iconIndex;
    randomizerHash[i] = hashIcons[iconIndex];
  }

  // Clear out spoiler log data here, in case we aren't going to re-generate it
  spoilerData = { 0 };
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

const SpoilerData& GetSpoilerData() {
  return spoilerData;
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

static void WriteIngameSpoilerLog() {
  u16 spoilerItemIndex = 0;
  u32 spoilerStringOffset = 0;
  bool spoilerOutOfSpace = false;

  // Create map of string data offsets for all _unique_ item locations and names in the playthrough
  // Some item names, like gold skulltula tokens, can appear many times in a playthrough
  std::unordered_map<LocationKey, u16> itemLocationsMap; // Map of LocationKey to an index into spoiler data item locations
  itemLocationsMap.reserve(allLocations.size());
  std::unordered_map<std::string, u16> stringOffsetMap; // Map of strings to their offset into spoiler string data array
  stringOffsetMap.reserve(allLocations.size() * 2);

  for (const LocationKey key : allLocations) {
    auto loc = Location(key);

    auto locName = loc->GetName();
    if (stringOffsetMap.find(locName) == stringOffsetMap.end()) {
      if (spoilerStringOffset + locName.size() + 1 >= SPOILER_STRING_DATA_SIZE) {
        spoilerOutOfSpace = true;
        break;
      } else {
        stringOffsetMap[locName] = spoilerStringOffset;
        spoilerStringOffset += sprintf(&spoilerData.StringData[spoilerStringOffset], "%s", locName.c_str()) + 1;
      }
    }

    auto locItem = loc->GetPlacedItemName().GetEnglish();
    if (stringOffsetMap.find(locItem) == stringOffsetMap.end()) {
      if (spoilerStringOffset + locItem.size() + 1 >= SPOILER_STRING_DATA_SIZE) {
        spoilerOutOfSpace = true;
        break;
      } else {
        stringOffsetMap[locItem] = spoilerStringOffset;
        spoilerStringOffset += sprintf(&spoilerData.StringData[spoilerStringOffset], "%s", locItem.c_str()) + 1;
      }
    }

    spoilerData.ItemLocations[spoilerItemIndex].LocationStrOffset = stringOffsetMap[locName];
    spoilerData.ItemLocations[spoilerItemIndex].ItemStrOffset = stringOffsetMap[locItem];
    spoilerData.ItemLocations[spoilerItemIndex].CollectionCheckType = loc->GetCollectionCheck().type;
    spoilerData.ItemLocations[spoilerItemIndex].LocationScene = loc->GetCollectionCheck().scene;
    spoilerData.ItemLocations[spoilerItemIndex].LocationFlag = loc->GetCollectionCheck().flag;
    itemLocationsMap[key] = spoilerItemIndex++;
  }
  spoilerData.ItemLocationsCount = spoilerItemIndex;

  bool playthroughItemNotFound = false;
  // Write playthrough data to in-game spoiler log
  if (!spoilerOutOfSpace) {
    for (u32 i = 0; i < playthroughLocations.size(); i++) {
      if (i >= SPOILER_SPHERES_MAX) {
        spoilerOutOfSpace = true;
        break;
      }
      for (u32 loc = 0; loc < playthroughLocations[i].size(); ++loc) {
        if (loc >= SPOILER_SPHERE_ITEM_LOCATIONS_MAX) {
          spoilerOutOfSpace = true;
          break;
        }

        const auto foundItemLoc = itemLocationsMap.find(playthroughLocations[i][loc]);
        if (foundItemLoc != itemLocationsMap.end()) {
          spoilerData.Spheres[i].ItemLocations[loc] = foundItemLoc->second;
        } else {
          playthroughItemNotFound = true;
        }
        ++spoilerData.Spheres[i].ItemCount;
      }
      ++spoilerData.SphereCount;
    }
  }

  if (spoilerOutOfSpace || playthroughItemNotFound) { printf("%sError!%s ", YELLOW, WHITE); }
}

// Writes the location to the specified node.
static void WriteLocation(
    tinyxml2::XMLElement* parentNode,
    const LocationKey locationKey,
    const bool withPadding = false
) {
  ItemLocation* location = Location(locationKey);

  auto node = parentNode->InsertNewChildElement("location");
  node->SetAttribute("name", location->GetName().c_str());
  node->SetText(location->GetPlacedItemName().GetEnglish().c_str());

  if (withPadding) {
    constexpr int16_t LONGEST_NAME = 56; // The longest name of a location.
    constexpr int16_t PRICE_ATTRIBUTE = 12; // Length of a 3-digit price attribute.

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
    std::string name = trial->GetName().GetEnglish();
    name[0] = toupper(name[0]); // Capitalize T in "The"
    node->SetAttribute("name", name.c_str());
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
}

// Writes the WOTH locations to the spoiler log, if there are any.
static void WriteWayOfTheHeroLocation(tinyxml2::XMLDocument& spoilerLog) {
  auto parentNode = spoilerLog.NewElement("way-of-the-hero-locations");

  for (const LocationKey key : wothLocations) {
    WriteLocation(parentNode, key, true);
  }

  if (!parentNode->NoChildren()) {
    spoilerLog.RootElement()->InsertEndChild(parentNode);
  }
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
    node->SetText(location->GetPlacedItemName().GetEnglish().c_str());
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
  WriteIngameSpoilerLog();

  auto spoilerLog = tinyxml2::XMLDocument(false);
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
  WriteWayOfTheHeroLocation(spoilerLog);

  playthroughLocations.clear();
  playthroughBeatable = false;
  wothLocations.clear();

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
  auto placementLog = tinyxml2::XMLDocument(false);
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
