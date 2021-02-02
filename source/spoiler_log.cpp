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
  for (auto& str : randomizerHash) {
    str = hashIcons[Random() % hashIcons.size()];
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

bool SpoilerLog_Write() {
  logtxt += "Seed: " + Settings::seed + "\n\n";

  logtxt += "Hash: ";
  for (std::string& str : randomizerHash) {
    logtxt += str + " ";
  }
  logtxt += "\n\n";

  logtxt += "Playthrough:\n";
  for (ItemLocation* location : playthroughLocations) {
    logtxt += "    ";
    SpoilerLog_SaveLocation(location->GetName(), location->GetPlacedItemName());
    logtxt += '\n';
  }

  logtxt += "\nAll Locations:\n\n";
  for (ItemLocation* location : dungeonRewardLocations) {
    SpoilerLog_SaveLocation(location->GetName(), location->GetPlacedItemName());
    logtxt += location->IsAddedToPool() ? "" : " NOT ADDED\n";
  }
  for (ItemLocation* location : allLocations) {
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

  return true;
}

void PlacementLog_Msg(std::string_view msg) {
  placementtxt += msg;
}

bool PlacementLog_Write() {
  Result res = 0;
  u32 bytesWritten = 0;

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

  return true;
}
