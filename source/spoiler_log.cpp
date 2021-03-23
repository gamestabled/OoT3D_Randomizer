#include "spoiler_log.hpp"
#include "item_list.hpp"
#include "settings.hpp"
#include "random.hpp"

#include <3ds.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <string>

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

std::array<std::string, 5> randomizerHash = {"", "", "", "", ""};

void GenerateHash() {
  for (u32 i = 0; i < 5; i++) {
    u8 iconIndex = Random(0, hashIcons.size());
    Settings::hashIconIndexes[i] = iconIndex;
    randomizerHash[i] = hashIcons[iconIndex];
  }
}

static void SpoilerLog_SaveLocation(std::string_view loc, std::string_view item) {
  logtxt += loc;
  logtxt += ": ";

  // Formatting for spoiler log
  constexpr u32 LONGEST_LINE = 53;
  const auto remainingSpaces = LONGEST_LINE - loc.size();
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
    //don't log the detailed logic or exclude location menus yet
    if (menu->name == "Detailed Logic Settings" || menu->name == "Exclude Locations" || menu->type == MenuItemType::Action) {
      continue;
    }

    for (size_t i = 0; i < menu->settingsList->size(); i++) {
      Option* setting = menu->settingsList->at(i);
      if (!setting->IsHidden()) {
        logtxt += "\t";
        logtxt += setting->GetName();
        logtxt += ": ";
        logtxt += setting->GetSelectedOption();
        logtxt += "\n";
      }
    }
  }

  //List Excluded Locations
  logtxt += "\nExcluded Locations:\n";
  for (auto& l : Settings::excludeLocationsOptions) {
    if (l->GetSelectedOption() == "Exclude") {
      std::string name = l->GetName().data();

      //get rid of newline characters if necessary
      if (name.find('\n') != std::string::npos)
        name.replace(name.find('\n'), 1, "");

      logtxt += "\t";
      logtxt += name;
      logtxt += "\n";
    }
  }

  //List Enabled Tricks
  logtxt += "\nEnabled Tricks:\n";
  for (auto& l : Settings::detailedLogicOptions) {
    if (l->GetSelectedOption() == "Enable" && l->GetName() != "All Tricks") {
      std::string name = l->GetName().data();

      //get rid of newline characters if necessary
      if (name.find('\n') != std::string::npos)
        name.replace(name.find('\n'), 1, "");

      logtxt += "\t";
      logtxt += name;
      logtxt += "\n";
    }
  }

  logtxt += "\n";
}

bool SpoilerLog_Write() {
  logtxt += "Version: " + Settings::version + "\n";
  logtxt += "Seed: " + Settings::seed + "\n\n";

  logtxt += "Hash: ";
  for (std::string& str : randomizerHash) {
    logtxt += str + ", ";
  }
  logtxt += "\n\n";

  WriteSettings();

  logtxt += "Playthrough:\n";
  for (uint i = 0; i < playthroughLocations.size(); i++) {
    logtxt += "Sphere " + std::to_string(i+1) + ":\n";
    std::vector<ItemLocation*> sphere = playthroughLocations[i];
    for (ItemLocation* location : sphere) {
      logtxt += "\t";
      SpoilerLog_SaveLocation(location->GetName(), location->GetPlacedItemName());
      logtxt += '\n';
    }
  }
  playthroughLocations.clear();
  playthroughBeatable = false;

  logtxt += "\nAll Locations:\n";
  for (ItemLocation* location : dungeonRewardLocations) {
    logtxt += "\t";
    SpoilerLog_SaveLocation(location->GetName(), location->GetPlacedItemName());
    logtxt += location->IsAddedToPool() ? "" : " NOT ADDED\n";
  }
  for (ItemLocation* location : allLocations) {
    logtxt += "\t";
    SpoilerLog_SaveLocation(location->GetName(), location->GetPlacedItemName());
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

  placementtxt = "";
  return true;
}
