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
  std::array<Option *, 34> settings = {
    &Settings::Logic,
    &Settings::OpenForest,
    &Settings::OpenKakariko,
    &Settings::OpenDoorOfTime,
    &Settings::ZorasFountain,
    &Settings::GerudoFortress,
    &Settings::Bridge,
    &Settings::StartingAge,
    &Settings::BombchusInLogic,
    &Settings::RandomMQDungeons,
    &Settings::ShuffleSongs,
    &Settings::Tokensanity,
    &Settings::Scrubsanity,
    &Settings::ShuffleKokiriSword,
    &Settings::ShuffleOcarinas,
    &Settings::ShuffleWeirdEgg,
    &Settings::ShuffleGerudoToken,
    &Settings::ShuffleMagicBeans,
    &Settings::MapsAndCompasses,
    &Settings::Keysanity,
    &Settings::GerudoKeys,
    &Settings::BossKeysanity,
    &Settings::GanonsBossKey,
    &Settings::SkipChildStealth,
    &Settings::FourPoesCutscene,
    &Settings::TempleOfTimeIntro,
    &Settings::BigPoeTargetCount,
    &Settings::DamageMultiplier,
    &Settings::StartingTime,
    &Settings::GenerateSpoilerLog,
    &Settings::BoomerangAsAdult,
    &Settings::HammerAsChild,
    &Settings::ItemPoolValue,
    &Settings::IceTrapValue,
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

static void WriteSettings() {
  //List Settings
  logtxt += "Settings:\n";
  for (auto& s : settings) {
    logtxt += "\t";
    logtxt += s->GetName();
    logtxt += ": ";
    logtxt += s->GetSelectedOption();
    logtxt += "\n";
  }

  //List Excluded Locations
  logtxt += "\nExcluded Locations:\n";
  for (auto& l : Settings::excludeLocationsOptions) {
    if (l->GetSelectedOption() == "Exclude") {
      std::string name = l->GetName().data();
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
    if (l->GetSelectedOption() == "Enable") {
      std::string name = l->GetName().data();
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
  logtxt += "Seed: " + Settings::seed + "\n\n";

  logtxt += "Hash: ";
  for (std::string& str : randomizerHash) {
    logtxt += str + " ";
  }
  logtxt += "\n\n";

  WriteSettings();

  logtxt += "Playthrough:\n";
  for (ItemLocation* location : playthroughLocations) {
    logtxt += "    ";
    SpoilerLog_SaveLocation(location->GetName(), location->GetPlacedItemName());
    logtxt += '\n';
  }
  playthroughLocations = {};

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

  placementtxt = "";
  return true;
}
