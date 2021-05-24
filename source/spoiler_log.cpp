#include "spoiler_log.hpp"

#include "dungeon.hpp"
#include "item_list.hpp"
#include "item_location.hpp"
#include "random.hpp"
#include "settings.hpp"
#include "trial.hpp"

#include <3ds.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <string>
#include <vector>

namespace {
  FS_Archive sdmcArchive = 0;
  Handle spoilerlog;
  Handle placementlog;

  std::string logtxt;
  std::string placementtxt;

  std::array<std::string_view, 32> hashIcons = {
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

static void SpoilerLog_SaveLocation(std::string_view loc, std::string_view item) {
  logtxt += loc;
  logtxt += ": ";

  // Formatting for spoiler log
  constexpr u32 LONGEST_LINE = 56;
  const auto remainingSpaces = LONGEST_LINE - loc.size();
  logtxt.append(remainingSpaces, ' ');

  logtxt += item;
  logtxt += '\n';
}

static void SpoilerLog_SaveShopLocation(std::string_view loc, std::string_view item, u16 price) {
  std::string locandprice = "";
  locandprice += loc;
  locandprice += " (Price: " + std::to_string(price) + ")";
  logtxt += locandprice;
  logtxt += ": ";

  // Formatting for spoiler log
  constexpr u32 LONGEST_LINE = 56;
  const auto remainingSpaces = LONGEST_LINE - locandprice.size();
  logtxt.append(remainingSpaces, ' ');

  logtxt += item;
  logtxt += '\n';
}

static auto GetGeneralPath() {
  std::string path = "/3ds/" + Settings::seed;
  for (auto& str : randomizerHash)
    path += str;
  return path;
}


static auto GetSpoilerLogPath() {
  return GetGeneralPath() + "-spoilerlog.txt";
}

static auto GetPlacementLogPath() {
  return GetGeneralPath() + "-placementlog.txt";
}

static void WriteSettings() {
  //List Settings
  logtxt += "Settings:\n";
  for (MenuItem* menu : Settings::mainMenu) {
    //don't log the detailed logic, starting inventory, or exclude location menus yet
    if (menu->name == "Detailed Logic Settings" || menu->name == "Starting Inventory" || menu->name == "Exclude Locations" || menu->mode != OPTION_SUB_MENU) {
      continue;
    }

    for (Option* setting : *menu->settingsList) {
      if (!setting->IsHidden() && setting->IsCategory(OptionCategory::Setting)) {
        logtxt += "\t";
        logtxt += setting->GetName();
        logtxt += ": ";
        logtxt += setting->GetSelectedOptionText();
        logtxt += "\n";
      }
    }
  }

  //List Excluded Locations
  logtxt += "\nExcluded Locations:\n";
  for (auto& l : Settings::excludeLocationsOptions) {
    if (l->GetSelectedOptionIndex() == EXCLUDE) {
      std::string name = l->GetName().data();

      //get rid of newline characters if necessary
      if (name.find('\n') != std::string::npos)
        name.replace(name.find('\n'), 1, "");

      logtxt += "\t";
      logtxt += name;
      logtxt += "\n";
    }
  }

  //List Starting Inventory
  logtxt += "\nStarting Inventory:\n";
  //start i at 3 to skip over the toggle, 'Start with Consumables', and 'Start with Max Rupees'
  for (size_t i = 3; i < Settings::startingInventoryOptions.size(); i++) {
    auto setting = Settings::startingInventoryOptions[i];
    if (setting->GetSelectedOptionIndex() != STARTINGINVENTORY_NONE) {
      std::string item = setting->GetSelectedOptionText();

      logtxt += "\t";
      logtxt += item;
      logtxt += "\n";
    }
  }

  //List Enabled Tricks
  logtxt += "\nEnabled Tricks:\n";
  for (auto& l : Settings::detailedLogicOptions) {
    if (l->GetSelectedOptionIndex() == TRICK_ENABLED && l->IsCategory(OptionCategory::Setting)) {
      std::string name = l->GetName().data();

      //get rid of newline characters if necessary
      if (name.find('\n') != std::string::npos)
        name.replace(name.find('\n'), 1, "");

      logtxt += "\t";
      logtxt += name;
      logtxt += "\n";
    }
  }

  //Master Quest Dungeons
  if (Settings::MQDungeonCount.IsNot(0)) {
    logtxt += "\nMaster Quest Dungeons:\n";
    for (const auto* dungeon : Dungeon::dungeonList) {
      if (dungeon->IsMQ()) {
        logtxt += std::string("\t").append(dungeon->GetName()).append("\n");
      }
    }
    logtxt += '\n';
  }

  //Required Trials
  if (Settings::GanonsTrialsCount.IsNot(0)) {
    logtxt += "\nRequired Trials:\n";
    for (const auto* trial : Trial::trialList) {
      if (trial->IsRequired()) {
        logtxt += std::string("\t").append(trial->GetName().english).append("\n");
      }
    }
    logtxt += '\n';
  }
}

bool SpoilerLog_Write() {
  logtxt += "Version: " + Settings::version + "\n";
  logtxt += "Seed: " + Settings::seed + "\n\n";

  logtxt += "Hash: ";
  for (std::string& str : randomizerHash) {
    logtxt += str + ", ";
  }
  logtxt.erase(logtxt.length() - 2); //Erase last comma
  logtxt += "\n\n";

  WriteSettings();

  //Write playthrough to spoiler, by accessibility sphere
  logtxt += "Playthrough:\n";
  for (uint i = 0; i < playthroughLocations.size(); i++) {
    logtxt += "Sphere " + std::to_string(i+1) + ":\n";
    //Print all item locations in this sphere
    for (ItemLocation* location : playthroughLocations[i]) {
      logtxt += "\t";
      SpoilerLog_SaveLocation(location->GetName(), location->GetPlacedItemName());
      logtxt += '\n';
    }
  }
  playthroughLocations.clear();
  playthroughBeatable = false;

  //Write Hints
  if (Settings::GossipStoneHints.IsNot(HINTS_NO_HINTS)) {
    logtxt += "\nHints:\n";
    for (ItemLocation* location : gossipStoneLocations) {
      logtxt += "\t";
      SpoilerLog_SaveLocation(location->GetName(), location->GetPlacedItemName());
    }
  }

  logtxt += "\nAll Locations:\n";
  for (ItemLocation* location : allLocations) {
    logtxt += "\t";
    if (location->IsCategory(Category::cShop)) { //Shop item
      SpoilerLog_SaveShopLocation(location->GetName(), location->GetPlacedItemName(), location->GetPrice());
    }
    else { //Normal item
      SpoilerLog_SaveLocation(location->GetName(), location->GetPlacedItemName());
    }
    logtxt += location->IsAddedToPool() ? "" : " NOT ADDED\n";
  }

  Result res = 0;
  u32 bytesWritten = 0;
  // Open SD archive
  if (!R_SUCCEEDED(res = FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) {
    return false;
  }

  // Open spoilerlog.txt
  if (!R_SUCCEEDED(res = FSUSER_OpenFile(&spoilerlog, sdmcArchive, fsMakePath(PATH_ASCII, GetSpoilerLogPath().c_str()), FS_OPEN_CREATE | FS_OPEN_WRITE, 0))) {
    return false;
  }

  // Write to spoilerlog.txt
  if (!R_SUCCEEDED(res = FSFILE_Write(spoilerlog, &bytesWritten, 0, logtxt.c_str(), strlen(logtxt.c_str()), FS_WRITE_FLUSH))) {
    return false;
  }

  FSFILE_Close(spoilerlog);
  FSUSER_CloseArchive(sdmcArchive);

  logtxt = "";
  return true;
}

void PlacementLog_Msg(std::string_view msg) {
  placementtxt += msg;
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
