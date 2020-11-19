#include "spoiler_log.hpp"
#include "item_location.hpp"
#include "item_list.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include <set>
#include <cstring>
#include <vector>
#include <string>

int LONGEST_LINE = 53;

Result res = 0;
FS_Archive sdmcArchive = 0;
Handle spoilerlog;
Handle placementlog;
u32 bytesWritten = 0;
u32 totalRW = 0;

std::string logtxt = "";
std::string placementtxt = "";

void SpoilerLog_SaveLocation(const char *loc, const char *item) {
  logtxt += loc;
  logtxt += ": ";

  //formatting for spoiler log (there's probably an easier way to do this)
  u8 remainingSpaces = LONGEST_LINE - (strlen(loc));
  for (u8 i = 0; i < remainingSpaces; i++) {
    logtxt += " ";
  }

  logtxt += item;
  logtxt += "\n";
}

bool SpoilerLog_Write() {
  for (auto loc = allLocations.begin(); loc != allLocations.end(); loc++) {
    SpoilerLog_SaveLocation((*loc)->getName(), (*loc)->placedItem.getName());
  }

  //Open SD archive
  if (!R_SUCCEEDED(res = FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) return false;
  //Open spoilerlog.txt
  if (!R_SUCCEEDED(res = FSUSER_OpenFile(&spoilerlog, sdmcArchive, fsMakePath(PATH_ASCII, "/3ds/spoilerlog.txt"), FS_OPEN_WRITE | FS_OPEN_CREATE, 0))) return false;
  //write to spoilerlog.txt
  if (!R_SUCCEEDED(res = FSFILE_Write(spoilerlog, &bytesWritten, totalRW, logtxt.c_str(), strlen(logtxt.c_str()), FS_WRITE_FLUSH))) return false;
  return true;
}

void PlacementLog_Msg(const char *msg) {
  placementtxt += msg;
}

bool PlacementLog_Write() {
  //Open SD archive
  if (!R_SUCCEEDED(res = FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, "")))) return false;
  //Open placementlog.txt
  if (!R_SUCCEEDED(res = FSUSER_OpenFile(&placementlog, sdmcArchive, fsMakePath(PATH_ASCII, "/3ds/placementlog.txt"), FS_OPEN_WRITE | FS_OPEN_CREATE, 0))) return false;
  //write to placementlog.txt
  if (!R_SUCCEEDED(res = FSFILE_Write(placementlog, &bytesWritten, totalRW, placementtxt.c_str(), strlen(placementtxt.c_str()), FS_WRITE_FLUSH))) return false;
  return true;
}
