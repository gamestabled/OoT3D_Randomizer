#include "spoiler_log.hpp"
#include "item_location.hpp"
#include "item_list.hpp"
#include "settings.hpp"

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

static auto GetSeedPath() {
  return "/3ds/" + Settings::seed + "-spoilerlog.txt";
}

bool SpoilerLog_Write() {
  logtxt += "Seed: " + Settings::seed + "\n\n";

  for (const auto* location : allLocations) {
    SpoilerLog_SaveLocation(location->getName(), location->placedItem.getName());
  }

  Result res = 0;
  u32 bytesWritten = 0;

  // Open SD archive
  if (!R_SUCCEEDED(res = FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) {
    return false;
  }

  // Open spoilerlog.txt
  if (!R_SUCCEEDED(res = FSUSER_OpenFile(&spoilerlog, sdmcArchive, fsMakePath(PATH_ASCII, GetSeedPath().c_str()), FS_OPEN_WRITE | FS_OPEN_CREATE, 0))) {
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

  //Open SD archive
  if (!R_SUCCEEDED(res = FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) {
    return false;
  }

  //Open placementlog.txt
  const auto seed_path = "/3ds/" + Settings::seed + "-placementlog.txt";
  if (!R_SUCCEEDED(res = FSUSER_OpenFile(&placementlog, sdmcArchive, fsMakePath(PATH_ASCII, GetSeedPath().c_str()), FS_OPEN_WRITE | FS_OPEN_CREATE, 0))) {
    return false;
  }

  //write to placementlog.txt
  if (!R_SUCCEEDED(res = FSFILE_Write(placementlog, &bytesWritten, 0, placementtxt.c_str(), placementtxt.size(), FS_WRITE_FLUSH))) {
    return false;
  }

  return true;
}
