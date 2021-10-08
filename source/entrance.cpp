#include "entrance.hpp"

#include "fill.hpp"
#include "settings.hpp"
#include "item_list.hpp"
#include "item_pool.hpp"
#include "item_location.hpp"
#include "debug.hpp"
#include "spoiler_log.hpp"
#include "hints.hpp"

#include <unistd.h>

#include <vector>
#include <utility>
#include <set>
#include <map>
#include <unordered_map>

std::list<EntranceOverride> entranceOverrides = {};
bool noRandomEntrances = false;
EntranceTrackingData entranceTrackingData = {0};

EntranceTrackingData* GetEntranceTrackingData() {
  return &entranceTrackingData;
}

typedef struct {
    EntranceType type;
    AreaKey parentRegion;
    AreaKey connectedRegion;
    s16 index;
    s16 blueWarp;
} EntranceLinkInfo;
                                 //primary,          secondary
using EntranceInfoPair = std::pair<EntranceLinkInfo, EntranceLinkInfo>;
using EntrancePair = std::pair<Entrance*, Entrance*>;

//The entrance randomization algorithm used here is a direct copy of
//the algorithm used in the original N64 randomizer (except now in C++ instead
//of python). It may be easier to understand the algorithm by looking at the
//base randomizer's code instead:
// https://github.com/TestRunnerSRL/OoT-Randomizer/blob/Dev/EntranceShuffle.py

void SetAllEntrancesData(std::vector<EntranceInfoPair>& entranceShuffleTable) {
  for (auto& entrancePair: entranceShuffleTable) {

    auto& forwardEntry = entrancePair.first;
    auto& returnEntry = entrancePair.second;

    //set data
    Entrance* forwardEntrance = AreaTable(forwardEntry.parentRegion)->GetExit(forwardEntry.connectedRegion);
    forwardEntrance->SetIndex(forwardEntry.index);
    forwardEntrance->SetBlueWarp(forwardEntry.blueWarp);
    forwardEntrance->SetType(forwardEntry.type);
    forwardEntrance->SetAsPrimary();
    // if type == 'Grotto':
    //     forward_entrance.data['index'] = 0x1000 + forward_entrance.data['grotto_id']
    if (returnEntry.parentRegion != NONE) {
      Entrance* returnEntrance = AreaTable(returnEntry.parentRegion)->GetExit(returnEntry.connectedRegion);
      returnEntrance->SetIndex(returnEntry.index);
      returnEntrance->SetBlueWarp(returnEntry.blueWarp);
      returnEntrance->SetType(returnEntry.type);
      forwardEntrance->BindTwoWay(returnEntrance);
      // if type == 'Grotto':
      //     return_entrance.data['index'] = 0x2000 + return_entrance.data['grotto_id']
    }
  }
}

static std::vector<Entrance*> AssumeEntrancePool(std::vector<Entrance*>& entrancePool) {
  std::vector<Entrance*> assumedPool = {};
  for (Entrance* entrance : entrancePool) {
    Entrance* assumedForward = entrance->AssumeReachable();
    if (entrance->GetReverse() != nullptr /*&& entrances are not decoupled*/) {
      Entrance* assumedReturn = entrance->GetReverse()->AssumeReachable();
      //mixed pool assumption stuff
      assumedForward->BindTwoWay(assumedReturn);
    }
    assumedPool.push_back(assumedForward);
  }
  return assumedPool;
}

//returns restrictive entrances and soft entrances in an array of size 2 (restrictive vector is index 0, soft is index 1)
static std::array<std::vector<Entrance*>, 2> SplitEntrancesByRequirements(std::vector<Entrance*>& entrancesToSplit, std::vector<Entrance*>& assumedEntrances) {
  //First, disconnect all root assumed entrances and save which regions they were originally connected to, so we can reconnect them later
  std::map<Entrance*, AreaKey> originalConnectedRegions = {};
  std::set<Entrance*> entrancesToDisconnect = {};
  for (Entrance* entrance : assumedEntrances) {
    entrancesToDisconnect.insert(entrance);
    if (entrance->GetReverse() != nullptr) {
      entrancesToDisconnect.insert(entrance->GetReverse());
    }
  }

  //disconnect each entrance temporarily to find restrictive vs soft entrances
  //soft entrances are ones that can be accessed by both ages (child/adult) at both times of day (day/night)
  //restrictive entrances are ones that do not meet this criteria
  for (Entrance* entrance : entrancesToDisconnect) {
    if (entrance->GetConnectedRegionKey() != NONE) {
      originalConnectedRegions[entrance] = entrance->Disconnect();
    }
  }

  std::vector<Entrance*> restrictiveEntrances = {};
  std::vector<Entrance*> softEntrances = {};

  Logic::LogicReset();
  // //Apply the effects of all advancement items to search for entrance accessibility
  std::vector<ItemKey> items = FilterFromPool(ItemPool, [](const ItemKey i){ return ItemTable(i).IsAdvancement();});
  for (ItemKey unplacedItem : items) {
    ItemTable(unplacedItem).ApplyEffect();
  }
  // run a search to see what's accessible
  GetAccessibleLocations(allLocations);

  for (Entrance* entrance : entrancesToSplit) {
    // if an entrance is accessible at all times of day by both ages, it's a soft entrance with no restrictions
    if (entrance->ConditionsMet(true)) {
      softEntrances.push_back(entrance);
    } else {
      restrictiveEntrances.push_back(entrance);
    }
  }

  //Reconnect all disconnected entrances
  for (Entrance* entrance : entrancesToDisconnect) {
    entrance->Connect(originalConnectedRegions[entrance]);
  }

  return {restrictiveEntrances, softEntrances};
}

static bool AreEntrancesCompatible(Entrance* entrance, Entrance* target, std::vector<EntrancePair>& rollbacks) {

  //Entrances shouldn't connect to their own scene, fail in this situation
  if (entrance->GetParentRegion()->scene != "" && entrance->GetParentRegion()->scene == target->GetConnectedRegion()->scene) {
    auto message = "Entrance " + entrance->GetName() + " attempted to connect with own scene target " + target->to_string() + ". Connection failed.\n";
    PlacementLog_Msg(message);
    return false;
  }

  //one-way entrance stuff

  return true;
}

//Change connections between an entrance and a target assumed entrance, in order to test the connections afterwards if necessary
static void ChangeConnections(Entrance* entrance, Entrance* targetEntrance) {
  auto message = "Attempting to connect " + entrance->GetName() + " to " + targetEntrance->to_string() + "\n";
  PlacementLog_Msg(message);
  entrance->Connect(targetEntrance->Disconnect());
  entrance->SetReplacement(targetEntrance->GetReplacement());
  if (entrance->GetReverse() != nullptr /*&& entrances aren't decoupled*/) {
    targetEntrance->GetReplacement()->GetReverse()->Connect(entrance->GetReverse()->GetAssumed()->Disconnect());
    targetEntrance->GetReplacement()->GetReverse()->SetReplacement(entrance->GetReverse());
  }
}

static void RestoreConnections(Entrance* entrance, Entrance* targetEntrance) {
  targetEntrance->Connect(entrance->Disconnect());
  entrance->SetReplacement(nullptr);
  if (entrance->GetReverse() != nullptr /*&& entrances are not decoupled*/) {
    entrance->GetReverse()->GetAssumed()->Connect(targetEntrance->GetReplacement()->GetReverse()->Disconnect());
    targetEntrance->GetReplacement()->GetReverse()->SetReplacement(nullptr);
  }
}

static void DeleteTargetEntrance(Entrance* targetEntrance) {
  if (targetEntrance->GetConnectedRegionKey() != NONE) {
    targetEntrance->Disconnect();
  }
  if (targetEntrance->GetParentRegionKey() != NONE) {
    targetEntrance->GetParentRegion()->RemoveExit(targetEntrance);
    targetEntrance->SetParentRegion(NONE);
  }
}

static void ConfirmReplacement(Entrance* entrance, Entrance* targetEntrance) {
  DeleteTargetEntrance(targetEntrance);
  if (entrance->GetReverse() != nullptr /*&& entrances are not decoupled*/) {
    auto replacedReverse = targetEntrance->GetReplacement()->GetReverse();
    DeleteTargetEntrance(replacedReverse->GetReverse()->GetAssumed());
  }
}

// Returns whether or not we can affirm the entrance can never be accessed as the given age
static bool EntranceUnreachableAs(Entrance* entrance, u8 age, std::vector<Entrance*> alreadyChecked = {}) {

  if (entrance == nullptr) {
    PlacementLog_Msg("Entrance is nullptr in EntranceUnreachableAs()");
    return true;
  }

  alreadyChecked.push_back(entrance);
  auto type = entrance->GetType();

  // The following cases determine when we say an entrance is not safe to affirm unreachable as the given age
  if (type == EntranceType::WarpSong || type == EntranceType::Overworld) {
    // Note that we consider all overworld entrances as potentially accessible as both ages, to be completely safe
    return false;
  } else if (type == EntranceType::OwlDrop) {
    return age == AGE_ADULT;
  } else if (type == EntranceType::Spawn && entrance->GetConnectedRegionKey() == KF_LINKS_HOUSE) {
    return age == AGE_ADULT;
  } else if (type == EntranceType::Spawn && entrance->GetConnectedRegionKey() == TEMPLE_OF_TIME) {
    return age == AGE_CHILD;
  }

  // Other entrances such as Interior, Dungeon or Grotto are fine unless they have a parent which is one of the above cases
  // Recursively check parent entrances to verify that they are also not reachable as the wrong age
  auto& parentEntrances = entrance->GetParentRegion()->entrances;
  for (Entrance* parentEntrance : parentEntrances) {

    //if parentEntrance is in alreadyChecked, then continue
    if (ElementInContainer(parentEntrance, alreadyChecked)) {
      continue;
    }

    bool unreachable = EntranceUnreachableAs(parentEntrance, age, alreadyChecked);
    if (!unreachable) {
      return false;
    }
  }

  return true;
}

static bool ValidateWorld(Entrance* entrancePlaced) {
  PlacementLog_Msg("Validating world\n");

  // if not world.decouple_entrances:
  // Unless entrances are decoupled, we don't want the player to end up through certain entrances as the wrong age
  // This means we need to hard check that none of the relevant entrances are ever reachable as that age
  // This is mostly relevant when mixing entrance pools or shuffling special interiors (such as windmill or kak potion shop)
  // Warp Songs and Overworld Spawns can also end up inside certain indoors so those need to be handled as well
    std::array<std::string, 2> childForbidden = {"OGC Great Fairy Fountain -> Castle Grounds", "GV Carpenter Tent -> GV Fortress Side"};
    std::array<std::string, 2> adultForbidden = {"HC Great Fairy Fountain -> Castle Grounds", "HC Storms Grotto -> Castle Grounds"};

    auto allShuffleableEntrances = GetShuffleableEntrances(EntranceType::All, false);
    for (auto& entrance: allShuffleableEntrances) {
      if (entrance->IsShuffled()) {
        if (entrance->GetReplacement() != nullptr) {

          auto replacementName = entrance->GetReplacement()->GetName();

          if (ElementInContainer(replacementName, childForbidden) && !EntranceUnreachableAs(entrance, AGE_CHILD, {entrance->GetReplacement()->GetReverse()})) {
            auto message = replacementName + " is replaced by an entrance with a potential child access\n";
            PlacementLog_Msg(message);
            return false;
          } else if (ElementInContainer(replacementName, adultForbidden) && !EntranceUnreachableAs(entrance, AGE_ADULT, {entrance->GetReplacement()->GetReverse()})) {
            auto message = replacementName + " is replaced by an entrance with a potential adult access\n";
            PlacementLog_Msg(message);
            return false;
          }
        }
      } else {
        auto name = entrance->GetName();

        if (ElementInContainer(name, childForbidden) && !EntranceUnreachableAs(entrance, AGE_CHILD, {entrance->GetReverse()})) {
          auto message = name + " is potentially accessible as child\n";
          PlacementLog_Msg(message);
          return false;
        } else if (ElementInContainer(name, adultForbidden) && !EntranceUnreachableAs(entrance, AGE_ADULT, {entrance->GetReverse()})) {
          auto message = name + " is potentially accessible as adult\n";
          PlacementLog_Msg(message);
          return false;
        }
      }
    }

  // Check to make sure all locations are still reachable
  Logic::LogicReset();
  std::vector<ItemKey> itemsToPlace = FilterFromPool(ItemPool, [](const ItemKey i){ return ItemTable(i).IsAdvancement();});
  for (ItemKey unplacedItem : itemsToPlace) {
    ItemTable(unplacedItem).ApplyEffect();
  }
  GetAccessibleLocations(allLocations, SearchMode::AllLocationsReachable);
  if (!allLocationsReachable) {
    return false;
  }

  //check certain conditions when certain types of ER are enabled
  EntranceType type = EntranceType::None;
  if (entrancePlaced != nullptr) {
    type = entrancePlaced->GetType();
  }

  if (Settings::ShuffleInteriorEntrances.IsNot(SHUFFLEINTERIORS_OFF) && Settings::GossipStoneHints.IsNot(HINTS_NO_HINTS) &&
  (entrancePlaced == nullptr || type == EntranceType::Interior || type == EntranceType::SpecialInterior)) {
    //When cows are shuffled, ensure both Impa's House entrances are in the same hint area because the cow is reachable from both sides
    if (Settings::ShuffleCows) {
      auto impasHouseFrontHintRegion = GetHintRegionHintKey(KAK_IMPAS_HOUSE);
      auto impasHouseBackHintRegion = GetHintRegionHintKey(KAK_IMPAS_HOUSE_BACK);
      if (impasHouseFrontHintRegion != NONE && impasHouseBackHintRegion != NONE && impasHouseBackHintRegion != LINKS_POCKET && impasHouseFrontHintRegion != LINKS_POCKET && impasHouseBackHintRegion != impasHouseFrontHintRegion) {
        auto message = "Kak Impas House entrances are not in the same hint area\n";
        PlacementLog_Msg(message);
        return false;
      }
    }
  }

  if ((Settings::ShuffleOverworldEntrances /*|| specialInterior || spawnPositions*/) && (entrancePlaced == nullptr /*|| world.mix_entrance_pools != 'off'*/ ||
  type == EntranceType::SpecialInterior || type == EntranceType::Overworld || type == EntranceType::Spawn || type == EntranceType::WarpSong || type == EntranceType::OwlDrop)) {
    //At least one valid starting region with all basic refills should be reachable without using any items at the beginning of the seed
    Logic::LogicReset();
    GetAccessibleLocations({});
    if (!AreaTable(KOKIRI_FOREST)->HasAccess() && !AreaTable(KAKARIKO_VILLAGE)->HasAccess()) {
      PlacementLog_Msg("Invalid starting area\n");
      return false;
    }

    //Check that a region where time passes is always reachable as both ages without having collected any items
    Logic::LogicReset();
    GetAccessibleLocations({}, SearchMode::BothAgesNoItems);
    if (!Areas::HasTimePassAccess(AGE_CHILD) || !Areas::HasTimePassAccess(AGE_ADULT)) {
      PlacementLog_Msg("Time passing is not guaranteed as both ages\n");
      return false;
    }

    // The player should be able to get back to ToT after going through time, without having collected any items
    // This is important to ensure that the player never loses access to the pedestal after going through time
    if (Settings::ResolvedStartingAge == AGE_CHILD && !AreaTable(TEMPLE_OF_TIME)->Adult()) {
      PlacementLog_Msg("Path to Temple of Time as adult is not guaranteed\n");
      return false;
    } else if (Settings::ResolvedStartingAge == AGE_ADULT && !AreaTable(TEMPLE_OF_TIME)->Child()) {
      PlacementLog_Msg("Path to Temple of Time as child is not guaranteed\n");
      return false;
    }
  }

  // The Big Poe shop should always be accessible as adult without the need to use any bottles
  // This is important to ensure that players can never lock their only bottles by filling them with Big Poes they can't sell
  if ((Settings::ShuffleOverworldEntrances /*|| specialInterior*/) && (entrancePlaced == nullptr /*|| world.mix_entrance_pools != 'off'*/ ||
  type == EntranceType::SpecialInterior || type == EntranceType::Overworld || type == EntranceType::Spawn || type == EntranceType::WarpSong || type == EntranceType::OwlDrop)) {
    Logic::LogicReset();
    GetAccessibleLocations({}, SearchMode::PoeCollectorAccess);
    if (!AreaTable(MARKET_GUARD_HOUSE)->Adult()) {
      PlacementLog_Msg("Big Poe Shop access is not guarenteed as adult\n");
      return false;
    }
  }

  return true;
}

static bool ReplaceEntrance(Entrance* entrance, Entrance* target, std::vector<EntrancePair>& rollbacks) {

  if (!AreEntrancesCompatible(entrance, target, rollbacks)) {
    return false;
  }
  ChangeConnections(entrance, target);
  if (ValidateWorld(entrance)) {
    rollbacks.push_back(EntrancePair{entrance, target});
    return true;
  } else {
    if (entrance->GetConnectedRegionKey() != NONE) {
      RestoreConnections(entrance, target);
    }
  }
  return false;
}

// Shuffle entrances by placing them instead of entrances in the provided target entrances list
static bool ShuffleEntrances(std::vector<Entrance*>& entrances, std::vector<Entrance*>& targetEntrances, std::vector<EntrancePair>& rollbacks) {

  //place all entrances in the pool, validating after every placement
  for (Entrance* entrance : entrances) {
    if (entrance->GetConnectedRegionKey() != NONE) {
      continue;
    }

    Shuffle(targetEntrances);
    for (Entrance* target : targetEntrances) {
      if (target->GetConnectedRegionKey() == NONE) {
        continue;
      }

      if (ReplaceEntrance(entrance, target, rollbacks)) {
        break;
      }
    }

    if (entrance->GetConnectedRegionKey() == NONE) {
      return false;
    }
  }

  //all entrances were validly connected
  return true;
}

static void ShuffleEntrancePool(std::vector<Entrance*>& entrancePool, std::vector<Entrance*>& targetEntrances) {
  noRandomEntrances = false;

  auto splitEntrances = SplitEntrancesByRequirements(entrancePool, targetEntrances);

  auto& restrictiveEntrances = splitEntrances[0];
  auto& softEntrances = splitEntrances[1];

  int retries = 20;
  while (retries > 0) {
    if (retries != 20) {
      auto message = "Failed to connect entrances. Retrying " + std::to_string(retries) + " more times.\n";
      PlacementLog_Msg(message);
    }
    retries--;

    std::vector<EntrancePair> rollbacks = {};

    //Shuffle Restrictive Entrances first while more regions are available in
    //order to heavily reduce the chances of the placement failing
    bool success = ShuffleEntrances(restrictiveEntrances, targetEntrances, rollbacks);
    if (success) {
      success = ShuffleEntrances(softEntrances, targetEntrances, rollbacks);
      if(!success) {
        for (auto& pair : rollbacks) {
          RestoreConnections(pair.first, pair.second);
        }
        continue;
      }
    } else {
      for (auto& pair : rollbacks) {
        RestoreConnections(pair.first, pair.second);
      }
      continue;
    }

    //fully validate the resulting world to ensure everything is still fine

    //If there are no issues, log the connections and continue
    for (auto& pair : rollbacks) {
      ConfirmReplacement(pair.first, pair.second);
    }
    break;
  }

  if (retries <= 0) {
    printf("\x1b[29;0HEntrance Shuffle failed. Entrances will not be\nshuffled");
    noRandomEntrances = true;
  }
}

std::unordered_map<s16, std::string> entranceNames = {
  { 0x0000, "KF Deku Tree Entrance" },
  { 0x0209, "Deku Tree" },
  { 0x0004, "DMT Dodongo's Cavern Entrance" },
  { 0x0242, "Dodongo's Cavern" },
  { 0x0028, "ZF Jabu Jabu's Belly Entrance" },
  { 0x0221, "Jabu Jabu's Belly" },
  { 0x0169, "SFM Forest Temple Entrance" },
  { 0x0215, "Forest Temple" },
  { 0x0165, "DMC Fire Temple Entrance" },
  { 0x024A, "Fire Temple" },
  { 0x0010, "LH Water Temple Entrance" },
  { 0x021D, "Water Temple" },
  { 0x0082, "Colossus Spirit Temple Entrance" },
  { 0x01E1, "Spirit Temple" },
  { 0x0037, "Graveyard Warp Pad" },
  { 0x0205, "Shadow Temple" },
  { 0x0098, "Kakariko Bottom of the Well Entrance" },
  { 0x02A6, "Bottom of the Well" },
  { 0x0088, "ZF Ice Cavern Entrance" },
  { 0x03D4, "Ice Cavern" },
  { 0x0008, "GF Training Grounds Entrance" },
  { 0x03A8, "Gerudo Training Grounds" },
  { 0x0433, "KF from Mido's House" },
  { 0x0443, "Mido's House" },
  { 0x0437, "KF from Saria's House" },
  { 0x0447, "Saria's House" },
  { 0x009C, "KF from House of Twins" },
  { 0x033C, "House of Twins" },
  { 0x00C9, "KF from Know-It-All House" },
  { 0x026A, "Know-It-All House" },
  { 0x00C1, "KF from Shop" },
  { 0x0266, "KF Shop" },
  { 0x0043, "Lake Hylia from Lab" },
  { 0x03CC, "Lake Hylia Lab" },
  { 0x045F, "Lake Hylia from Fishing Hole" },
  { 0x0309, "Lake Hylia Fishing Hole" },
  { 0x03A0, "GV from GF" },
  { 0x03D0, "GV Carpenters' Tent" },
  { 0x007E, "HC Town from Guard House" },
  { 0x026E, "HC Town Guard House" },
  { 0x0530, "Market from Mask Shop" },
  { 0x01D1, "Market Mask Shop" },
  { 0x0507, "Market from Bombchu Bowling" },
  { 0x03BC, "Market Bombchu Bowling" },
  { 0x0388, "Market from Potion Shop" },
  { 0x02A2, "Market Potion Shop" },
  { 0x0063, "Market from Treasure Chest Game" },
  { 0x01D5, "Market Treasure Chest Game" },
  { 0x0528, "Market Back Alley from Bombchu Shop" },
  { 0x03C0, "Market Bombchu Shop" },
  { 0x043B, "Market Back Alley from Man-in-Green's House" },
  { 0x0067, "Market Man-in-Green's House" },
  { 0x02FD, "Kakariko from Carpenter Boss House" },
  { 0x0349, "Carpenter Boss House" },
  { 0x0550, "Kakariko from House of Skulltula" },
  { 0x04EE, "House of Skulltula" },
  { 0x039C, "Kakariko from Impa's House" },
  { 0x0345, "Impa's House" },
  { 0x05C8, "Kakariko from Impa's House Ledge" },
  { 0x05DC, "Impa's House Back" },
  { 0x0072, "Kakariko Backyard" },
  { 0x034D, "Kakariko Odd Poultice Building" },
  { 0x030D, "Graveyard from Dampe's House" },
  { 0x0355, "Dampe's House" },
  { 0x037C, "Goron City from Goron Shop" },
  { 0x03FC, "Goron City Shop" },
  { 0x0380, "Zora's Domain from Zora's Domain Shop" },
  { 0x03C4, "Zora's Domain Shop" },
  { 0x004F, "Lon Lon Ranch from Talon's House" },
  { 0x0378, "Talon's House" },
  { 0x02F9, "Lon Lon Ranch from Stables" },
  { 0x042F, "Lon Lon Ranch Stables" },
  { 0x05D0, "Lon Lon Ranch from Tower" },
  { 0x05D4, "Lon Lon Ranch Tower" },
  { 0x052C, "Market from Bazaar" },
  { 0x03B8, "Market Bazaar" },
  { 0x016D, "Market from Shooting Gallery" },
  { 0x01CD, "Market Shooting Gallery" },
  { 0x00B7, "Kakariko from Bazaar" },
  { 0x0201, "Kakariko Bazaar" },
  { 0x003B, "Kakariko from Shooting Gallery" },
  { 0x0463, "Kakariko Shooting Gallery" },
  { 0x0588, "Colossus from Great Fairy Fountain" },
  { 0x057C, "Colossus Great Fairy Fountain" },
  { 0x0578, "HC Grounds from Great Fairy Fountain" },
  { 0x0340, "HC Great Fairy Fountain" },
  { 0x04C2, "OGC from Great Fairy Fountain" },
  { 0x03E8, "OGC Great Fairy Fountain" },
  { 0x04BE, "DMC from Great Fairy Fountain" },
  { 0x0482, "DMC Great Fairy Fountain" },
  { 0x0315, "DMT from Great Fairy Fountain" },
  { 0x045B, "DMT Great Fairy Fountain" },
  { 0x0371, "ZF from Great Fairy Fountain" },
  { 0x0394, "ZF Great Fairy Fountain" },
  { 0x0272, "KF from Link's House" },
  { 0x0211, "Link's House" },
  { 0x0053, "Outside Temple of Time" },
  { 0x0472, "Temple of Time" },
  { 0x0453, "Kakariko outside Windmill" },
  { 0x0351, "Kakariko Windmill" },
  { 0x0384, "Kakariko from Potion Shop Front" },
  { 0x044B, "Kakariko Potion Shop from Front Entrance" },
  { 0x03EC, "Kakariko Behind Potion Shop" },
  { 0x04FF, "Kakariko Potion Shop from Back Entrance" },
  { 0x05E0, "KF Exit to Lost Woods Bridge" },
  { 0x020D, "Lost Woods Bridge from KF" },
  { 0x011E, "KF from Lost Woods Entrance" },
  { 0x0286, "Lost Woods Exit to KF" },
  { 0x04E2, "Lost Woods from Goron City Warp" },
  { 0x04D6, "Goron City from Lost Woods Warp" },
  { 0x01DD, "Lost Woods from ZR Warp" },
  { 0x04DA, "ZR from Lost Woods Warp" },
  { 0x00FC, "Lost Woods from SFM Entrance" },
  { 0x01A9, "SFM from Lost Woods" },
  { 0x0185, "Lost Woods Bridge from Hyrule Field" },
  { 0x04DE, "Hyrule Field from Lost Woods Bridge" },
  { 0x0102, "Hyrule Field from Lake Hylia" },
  { 0x0189, "Lake Hylia from Hyrule Field" },
  { 0x0117, "Hyrule Field from GV" },
  { 0x018D, "GV from Hyrule Field" },
  { 0x0276, "Hyrule Field from HC Town" },
  { 0x01FD, "HC Town Entrance from Hyrule Field" },
  { 0x00DB, "Hyrule Field from Kakariko" },
  { 0x017D, "Kakariko from Hyrule Field" },
  { 0x00EA, "Hyrule Field from ZR" },
  { 0x0181, "ZR from Hyrule Field" },
  { 0x0157, "Hyrule Field from Lon Lon Ranch" },
  { 0x01F9, "Lon Lon Ranch from Hyrule Field" },
  { 0x0328, "Lake Hylia from Zora's Domain" },
  { 0x0560, "Zora's Domain from Lake Hylia" },
  { 0x0129, "GV from GF" },
  { 0x022D, "GF from GV" },
  { 0x0130, "GF from Haunted Wasteland" },
  { 0x03AC, "Haunted Wasteland from GF" },
  { 0x0123, "Colossus from Haunted Wasteland" },
  { 0x0365, "Haunted Wasteland from Colossus" },
  { 0x00B1, "HC Town Entrance from Market" },
  { 0x0033, "Market from HC Town Entrance" },
  { 0x0138, "Market from Castle Grounds" },
  { 0x025A, "Hyrule Castle Grounds from Market" },
  { 0x0171, "Market from Temple of Time" },
  { 0x025E, "Temple of Time from Market" },
  { 0x00E4, "Kakariko from Graveyard" },
  { 0x0195, "Graveyard from Kakariko" },
  { 0x013D, "Kakariko Gate to DMT" },
  { 0x0191, "DMT to Kakariko" },
  { 0x014D, "DMT Goron City Entrance" },
  { 0x01B9, "Goron City Exit to DMT" },
  { 0x0246, "Goron City Darunia's Chamber" },
  { 0x01C1, "DMC from Darunia's Chamber" },
  { 0x0147, "DMT from Crater" },
  { 0x01BD, "DMC Exit to Summit" },
  { 0x0108, "ZR Entrance to Zora's Domain" },
  { 0x019D, "Zora's Domain Exit to ZR" },
  { 0x0225, "Zora's Domain Behind King Zora" },
  { 0x01A1, "ZF to Zora's Domain" },
};

//Process for setting up the shuffling of all entrances to be shuffled
void ShuffleAllEntrances() {

  std::vector<EntranceInfoPair> entranceShuffleTable = {
                                   //Parent Region                     Connected Region                  index   blue warp
    {{EntranceType::Dungeon,         KF_OUTSIDE_DEKU_TREE,             DEKU_TREE_ENTRYWAY,               0x0000},
     {EntranceType::Dungeon,         DEKU_TREE_ENTRYWAY,               KF_OUTSIDE_DEKU_TREE,             0x0209, 0x0457}},
    {{EntranceType::Dungeon,         DEATH_MOUNTAIN_TRAIL,             DODONGOS_CAVERN_ENTRYWAY,         0x0004},
     {EntranceType::Dungeon,         DODONGOS_CAVERN_ENTRYWAY,         DEATH_MOUNTAIN_TRAIL,             0x0242, 0x047A}},
    {{EntranceType::Dungeon,         ZORAS_FOUNTAIN,                   JABU_JABUS_BELLY_ENTRYWAY,        0x0028},
     {EntranceType::Dungeon,         JABU_JABUS_BELLY_ENTRYWAY,        ZORAS_FOUNTAIN,                   0x0221, 0x010E}},
    {{EntranceType::Dungeon,         SACRED_FOREST_MEADOW,             FOREST_TEMPLE_ENTRYWAY,           0x0169},
     {EntranceType::Dungeon,         FOREST_TEMPLE_ENTRYWAY,           SACRED_FOREST_MEADOW,             0x0215, 0x0608}},
    {{EntranceType::Dungeon,         DMC_CENTRAL_LOCAL,                FIRE_TEMPLE_ENTRYWAY,             0x0165},
     {EntranceType::Dungeon,         FIRE_TEMPLE_ENTRYWAY,             DMC_CENTRAL_LOCAL,                0x024A, 0x0564}},
    {{EntranceType::Dungeon,         LAKE_HYLIA,                       WATER_TEMPLE_ENTRYWAY,            0x0010},
     {EntranceType::Dungeon,         WATER_TEMPLE_ENTRYWAY,            LAKE_HYLIA,                       0x021D, 0x060C}},
    {{EntranceType::Dungeon,         DESERT_COLOSSUS,                  SPIRIT_TEMPLE_ENTRYWAY,           0x0082},
     {EntranceType::Dungeon,         SPIRIT_TEMPLE_ENTRYWAY,           DESERT_COLOSSUS,                  0x01E1, 0x0610}},
    {{EntranceType::Dungeon,         GRAVEYARD_WARP_PAD_REGION,        SHADOW_TEMPLE_ENTRYWAY,           0x0037},
     {EntranceType::Dungeon,         SHADOW_TEMPLE_ENTRYWAY,           GRAVEYARD_WARP_PAD_REGION,        0x0205, 0x0580}},
    {{EntranceType::Dungeon,         KAKARIKO_VILLAGE,                 BOTTOM_OF_THE_WELL_ENTRYWAY,      0x0098},
     {EntranceType::Dungeon,         BOTTOM_OF_THE_WELL_ENTRYWAY,      KAKARIKO_VILLAGE,                 0x02A6}},
    {{EntranceType::Dungeon,         ZORAS_FOUNTAIN,                   ICE_CAVERN_ENTRYWAY,              0x0088},
     {EntranceType::Dungeon,         ICE_CAVERN_ENTRYWAY,              ZORAS_FOUNTAIN,                   0x03D4}},
    {{EntranceType::Dungeon,         GERUDO_FORTRESS,                  GERUDO_TRAINING_GROUNDS_ENTRYWAY, 0x0008},
     {EntranceType::Dungeon,         GERUDO_TRAINING_GROUNDS_ENTRYWAY, GERUDO_FORTRESS,                  0x03A8}},

    {{EntranceType::Interior,        KOKIRI_FOREST,                    KF_MIDOS_HOUSE,                   0x0433},
     {EntranceType::Interior,        KF_MIDOS_HOUSE,                   KOKIRI_FOREST,                    0x0443}},
    {{EntranceType::Interior,        KOKIRI_FOREST,                    KF_SARIAS_HOUSE,                  0x0437},
     {EntranceType::Interior,        KF_SARIAS_HOUSE,                  KOKIRI_FOREST,                    0x0447}},
    {{EntranceType::Interior,        KOKIRI_FOREST,                    KF_HOUSE_OF_TWINS,                0x009C},
     {EntranceType::Interior,        KF_HOUSE_OF_TWINS,                KOKIRI_FOREST,                    0x033C}},
    {{EntranceType::Interior,        KOKIRI_FOREST,                    KF_KNOW_IT_ALL_HOUSE,             0x00C9},
     {EntranceType::Interior,        KF_KNOW_IT_ALL_HOUSE,             KOKIRI_FOREST,                    0x026A}},
    {{EntranceType::Interior,        KOKIRI_FOREST,                    KF_KOKIRI_SHOP,                   0x00C1},
     {EntranceType::Interior,        KF_KOKIRI_SHOP,                   KOKIRI_FOREST,                    0x0266}},
    {{EntranceType::Interior,        LAKE_HYLIA,                       LH_LAB,                           0x0043},
     {EntranceType::Interior,        LH_LAB,                           LAKE_HYLIA,                       0x03CC}},
    {{EntranceType::Interior,        LH_FISHING_ISLAND,                LH_FISHING_HOLE,                  0x045F},
     {EntranceType::Interior,        LH_FISHING_HOLE,                  LH_FISHING_ISLAND,                0x0309}},
    {{EntranceType::Interior,        GV_FORTRESS_SIDE,                 GV_CARPENTER_TENT,                0x03A0},
     {EntranceType::Interior,        GV_CARPENTER_TENT,                GV_FORTRESS_SIDE,                 0x03D0}},
    {{EntranceType::Interior,        MARKET_ENTRANCE,                  MARKET_GUARD_HOUSE,               0x007E},
     {EntranceType::Interior,        MARKET_GUARD_HOUSE,               MARKET_ENTRANCE,                  0x026E}},
    {{EntranceType::Interior,        THE_MARKET,                       MARKET_MASK_SHOP,                 0x0530},
     {EntranceType::Interior,        MARKET_MASK_SHOP,                 THE_MARKET,                       0x01D1}},
    {{EntranceType::Interior,        THE_MARKET,                       MARKET_BOMBCHU_BOWLING,           0x0507},
     {EntranceType::Interior,        MARKET_BOMBCHU_BOWLING,           THE_MARKET,                       0x03BC}},
    {{EntranceType::Interior,        THE_MARKET,                       MARKET_POTION_SHOP,               0x0388},
     {EntranceType::Interior,        MARKET_POTION_SHOP,               THE_MARKET,                       0x02A2}},
    {{EntranceType::Interior,        THE_MARKET,                       MARKET_TREASURE_CHEST_GAME,       0x0063},
     {EntranceType::Interior,        MARKET_TREASURE_CHEST_GAME,       THE_MARKET,                       0x01D5}},
    {{EntranceType::Interior,        MARKET_BACK_ALLEY,                MARKET_BOMBCHU_SHOP,              0x0528},
     {EntranceType::Interior,        MARKET_BOMBCHU_SHOP,              MARKET_BACK_ALLEY,                0x03C0}},
    {{EntranceType::Interior,        MARKET_BACK_ALLEY,                MARKET_MAN_IN_GREEN_HOUSE,        0x043B},
     {EntranceType::Interior,        MARKET_MAN_IN_GREEN_HOUSE,        MARKET_BACK_ALLEY,                0x0067}},
    {{EntranceType::Interior,        KAKARIKO_VILLAGE,                 KAK_CARPENTER_BOSS_HOUSE,         0x02FD},
     {EntranceType::Interior,        KAK_CARPENTER_BOSS_HOUSE,         KAKARIKO_VILLAGE,                 0x0349}},
    {{EntranceType::Interior,        KAKARIKO_VILLAGE,                 KAK_HOUSE_OF_SKULLTULA,           0x0550},
     {EntranceType::Interior,        KAK_HOUSE_OF_SKULLTULA,           KAKARIKO_VILLAGE,                 0x04EE}},
    {{EntranceType::Interior,        KAKARIKO_VILLAGE,                 KAK_IMPAS_HOUSE,                  0x039C},
     {EntranceType::Interior,        KAK_IMPAS_HOUSE,                  KAKARIKO_VILLAGE,                 0x0345}},
    {{EntranceType::Interior,        KAK_IMPAS_LEDGE,                  KAK_IMPAS_HOUSE_BACK,             0x05C8},
     {EntranceType::Interior,        KAK_IMPAS_HOUSE_BACK,             KAK_IMPAS_LEDGE,                  0x05DC}},
    {{EntranceType::Interior,        KAK_BACKYARD,                     KAK_ODD_POULTICE_BUILDING,        0x0072},
     {EntranceType::Interior,        KAK_ODD_POULTICE_BUILDING,        KAK_BACKYARD,                     0x034D}},
    {{EntranceType::Interior,        THE_GRAVEYARD,                    GRAVEYARD_DAMPES_HOUSE,           0x030D},
     {EntranceType::Interior,        GRAVEYARD_DAMPES_HOUSE,           THE_GRAVEYARD,                    0x0355}},
    {{EntranceType::Interior,        GORON_CITY,                       GC_SHOP,                          0x037C},
     {EntranceType::Interior,        GC_SHOP,                          GORON_CITY,                       0x03FC}},
    {{EntranceType::Interior,        ZORAS_DOMAIN,                     ZD_SHOP,                          0x0380},
     {EntranceType::Interior,        ZD_SHOP,                          ZORAS_DOMAIN,                     0x03C4}},
    {{EntranceType::Interior,        LON_LON_RANCH,                    LLR_TALONS_HOUSE,                 0x004F},
     {EntranceType::Interior,        LLR_TALONS_HOUSE,                 LON_LON_RANCH,                    0x0378}},
    {{EntranceType::Interior,        LON_LON_RANCH,                    LLR_STABLES,                      0x02F9},
     {EntranceType::Interior,        LLR_STABLES,                      LON_LON_RANCH,                    0x042F}},
    {{EntranceType::Interior,        LON_LON_RANCH,                    LLR_TOWER,                        0x05D0},
     {EntranceType::Interior,        LLR_TOWER,                        LON_LON_RANCH,                    0x05D4}},
    {{EntranceType::Interior,        THE_MARKET,                       MARKET_BAZAAR,                    0x052C},
     {EntranceType::Interior,        MARKET_BAZAAR,                    THE_MARKET,                       0x03B8}}, //potential addresses start here
    {{EntranceType::Interior,        THE_MARKET,                       MARKET_SHOOTING_GALLERY,          0x016D},
     {EntranceType::Interior,        MARKET_SHOOTING_GALLERY,          THE_MARKET,                       0x01CD}},
    {{EntranceType::Interior,        KAKARIKO_VILLAGE,                 KAK_BAZAAR,                       0x00B7},
     {EntranceType::Interior,        KAK_BAZAAR,                       KAKARIKO_VILLAGE,                 0x0201}},
    {{EntranceType::Interior,        KAKARIKO_VILLAGE,                 KAK_SHOOTING_GALLERY,             0x003B},
     {EntranceType::Interior,        KAK_SHOOTING_GALLERY,             KAKARIKO_VILLAGE,                 0x0463}},
    {{EntranceType::Interior,        DESERT_COLOSSUS,                  COLOSSUS_GREAT_FAIRY_FOUNTAIN,    0x0588},
     {EntranceType::Interior,        COLOSSUS_GREAT_FAIRY_FOUNTAIN,    DESERT_COLOSSUS,                  0x057C}},
    {{EntranceType::Interior,        HYRULE_CASTLE_GROUNDS,            HC_GREAT_FAIRY_FOUNTAIN,          0x0578},
     {EntranceType::Interior,        HC_GREAT_FAIRY_FOUNTAIN,          CASTLE_GROUNDS,                   0x0340}},
    {{EntranceType::Interior,        GANONS_CASTLE_GROUNDS,            OGC_GREAT_FAIRY_FOUNTAIN,         0x04C2},
     {EntranceType::Interior,        OGC_GREAT_FAIRY_FOUNTAIN,         CASTLE_GROUNDS,                   0x03E8}}, //0x3E8 is an unused entrance index repruposed to differentiate between the HC and OGC fairy fountain exits (normally they both use 0x340)
    {{EntranceType::Interior,        DMC_LOWER_NEARBY,                 DMC_GREAT_FAIRY_FOUNTAIN,         0x04BE},
     {EntranceType::Interior,        DMC_GREAT_FAIRY_FOUNTAIN,         DMC_LOWER_LOCAL,                  0x0482}},
    {{EntranceType::Interior,        DEATH_MOUNTAIN_SUMMIT,            DMT_GREAT_FAIRY_FOUNTAIN,         0x0315},
     {EntranceType::Interior,        DMT_GREAT_FAIRY_FOUNTAIN,         DEATH_MOUNTAIN_SUMMIT,            0x045B}},
    {{EntranceType::Interior,        ZORAS_FOUNTAIN,                   ZF_GREAT_FAIRY_FOUNTAIN,          0x0371},
     {EntranceType::Interior,        ZF_GREAT_FAIRY_FOUNTAIN,          ZORAS_FOUNTAIN,                   0x0394}},

    {{EntranceType::SpecialInterior, KOKIRI_FOREST,                    KF_LINKS_HOUSE,                   0x0272},
     {EntranceType::SpecialInterior, KF_LINKS_HOUSE,                   KOKIRI_FOREST,                    0x0211}},
    {{EntranceType::SpecialInterior, TOT_ENTRANCE,                     TEMPLE_OF_TIME,                   0x0053},
     {EntranceType::SpecialInterior, TEMPLE_OF_TIME,                   TOT_ENTRANCE,                     0x0472}},
    {{EntranceType::SpecialInterior, KAKARIKO_VILLAGE,                 KAK_WINDMILL,                     0x0453},
     {EntranceType::SpecialInterior, KAK_WINDMILL,                     KAKARIKO_VILLAGE,                 0x0351}},
    {{EntranceType::SpecialInterior, KAKARIKO_VILLAGE,                 KAK_POTION_SHOP_FRONT,            0x0384},
     {EntranceType::SpecialInterior, KAK_POTION_SHOP_FRONT,            KAKARIKO_VILLAGE,                 0x044B}},
    {{EntranceType::SpecialInterior, KAK_BACKYARD,                     KAK_POTION_SHOP_BACK,             0x03EC},
     {EntranceType::SpecialInterior, KAK_POTION_SHOP_BACK,             KAK_BACKYARD,                     0x04FF}},

    {{EntranceType::Overworld,       KOKIRI_FOREST,                    LW_BRIDGE_FROM_FOREST,            0x05E0},
     {EntranceType::Overworld,       LW_BRIDGE,                        KOKIRI_FOREST,                    0x020D}},
    {{EntranceType::Overworld,       KOKIRI_FOREST,                    THE_LOST_WOODS,                   0x011E},
     {EntranceType::Overworld,       LW_FOREST_EXIT,                   KOKIRI_FOREST,                    0x0286}},
    {{EntranceType::Overworld,       THE_LOST_WOODS,                   GC_WOODS_WARP,                    0x04E2},
     {EntranceType::Overworld,       GC_WOODS_WARP,                    THE_LOST_WOODS,                   0x04D6}},
    {{EntranceType::Overworld,       THE_LOST_WOODS,                   ZORAS_RIVER,                      0x01DD},
     {EntranceType::Overworld,       ZORAS_RIVER,                      THE_LOST_WOODS,                   0x04DA}},
    {{EntranceType::Overworld,       LW_BEYOND_MIDO,                   SFM_ENTRYWAY,                     0x00FC},
     {EntranceType::Overworld,       SFM_ENTRYWAY,                     LW_BEYOND_MIDO,                   0x01A9}},
    {{EntranceType::Overworld,       LW_BRIDGE,                        HYRULE_FIELD,                     0x0185},
     {EntranceType::Overworld,       HYRULE_FIELD,                     LW_BRIDGE,                        0x04DE}},
    {{EntranceType::Overworld,       HYRULE_FIELD,                     LAKE_HYLIA,                       0x0102},
     {EntranceType::Overworld,       LAKE_HYLIA,                       HYRULE_FIELD,                     0x0189}},
    {{EntranceType::Overworld,       HYRULE_FIELD,                     GERUDO_VALLEY,                    0x0117},
     {EntranceType::Overworld,       GERUDO_VALLEY,                    HYRULE_FIELD,                     0x018D}},
    {{EntranceType::Overworld,       HYRULE_FIELD,                     MARKET_ENTRANCE,                  0x0276},
     {EntranceType::Overworld,       MARKET_ENTRANCE,                  HYRULE_FIELD,                     0x01FD}},
    {{EntranceType::Overworld,       HYRULE_FIELD,                     KAKARIKO_VILLAGE,                 0x00DB},
     {EntranceType::Overworld,       KAKARIKO_VILLAGE,                 HYRULE_FIELD,                     0x017D}},
    {{EntranceType::Overworld,       HYRULE_FIELD,                     ZR_FRONT,                         0x00EA},
     {EntranceType::Overworld,       ZR_FRONT,                         HYRULE_FIELD,                     0x0181}},
    {{EntranceType::Overworld,       HYRULE_FIELD,                     LON_LON_RANCH,                    0x0157},
     {EntranceType::Overworld,       LON_LON_RANCH,                    HYRULE_FIELD,                     0x01F9}},
    {{EntranceType::Overworld,       LAKE_HYLIA,                       ZORAS_DOMAIN,                     0x0328},
     {EntranceType::Overworld,       ZORAS_DOMAIN,                     LAKE_HYLIA,                       0x0560}},
    {{EntranceType::Overworld,       GV_FORTRESS_SIDE,                 GERUDO_FORTRESS,                  0x0129},
     {EntranceType::Overworld,       GERUDO_FORTRESS,                  GV_FORTRESS_SIDE,                 0x022D}},
    {{EntranceType::Overworld,       GF_OUTSIDE_GATE,                  WASTELAND_NEAR_FORTRESS,          0x0130},
     {EntranceType::Overworld,       WASTELAND_NEAR_FORTRESS,          GF_OUTSIDE_GATE,                  0x03AC}},
    {{EntranceType::Overworld,       WASTELAND_NEAR_COLOSSUS,          DESERT_COLOSSUS,                  0x0123},
     {EntranceType::Overworld,       DESERT_COLOSSUS,                  WASTELAND_NEAR_COLOSSUS,          0x0365}},
    {{EntranceType::Overworld,       MARKET_ENTRANCE,                  THE_MARKET,                       0x00B1},
     {EntranceType::Overworld,       THE_MARKET,                       MARKET_ENTRANCE,                  0x0033}},
    {{EntranceType::Overworld,       THE_MARKET,                       CASTLE_GROUNDS,                   0x0138},
     {EntranceType::Overworld,       CASTLE_GROUNDS,                   THE_MARKET,                       0x025A}},
    {{EntranceType::Overworld,       THE_MARKET,                       TOT_ENTRANCE,                     0x0171},
     {EntranceType::Overworld,       TOT_ENTRANCE,                     THE_MARKET,                       0x025E}},
    {{EntranceType::Overworld,       KAKARIKO_VILLAGE,                 THE_GRAVEYARD,                    0x00E4},
     {EntranceType::Overworld,       THE_GRAVEYARD,                    KAKARIKO_VILLAGE,                 0x0195}},
    {{EntranceType::Overworld,       KAK_BEHIND_GATE,                  DEATH_MOUNTAIN_TRAIL,             0x013D},
     {EntranceType::Overworld,       DEATH_MOUNTAIN_TRAIL,             KAK_BEHIND_GATE,                  0x0191}},
    {{EntranceType::Overworld,       DEATH_MOUNTAIN_TRAIL,             GORON_CITY,                       0x014D},
     {EntranceType::Overworld,       GORON_CITY,                       DEATH_MOUNTAIN_TRAIL,             0x01B9}},
    {{EntranceType::Overworld,       GC_DARUNIAS_CHAMBER,              DMC_LOWER_LOCAL,                  0x0246},
     {EntranceType::Overworld,       DMC_LOWER_NEARBY,                 GC_DARUNIAS_CHAMBER,              0x01C1}},
    {{EntranceType::Overworld,       DEATH_MOUNTAIN_SUMMIT,            DMC_UPPER_LOCAL,                  0x0147},
     {EntranceType::Overworld,       DMC_UPPER_NEARBY,                 DEATH_MOUNTAIN_SUMMIT,            0x01BD}},
    {{EntranceType::Overworld,       ZR_BEHIND_WATERFALL,              ZORAS_DOMAIN,                     0x0108},
     {EntranceType::Overworld,       ZORAS_DOMAIN,                     ZR_BEHIND_WATERFALL,              0x019D}},
    {{EntranceType::Overworld,       ZD_BEHIND_KING_ZORA,              ZORAS_FOUNTAIN,                   0x0225},
     {EntranceType::Overworld,       ZORAS_FOUNTAIN,                   ZD_BEHIND_KING_ZORA,              0x01A1}},
  };

  SetAllEntrancesData(entranceShuffleTable);

  // one_way_entrance_pools = OrderedDict()
  std::map<EntranceType, std::vector<Entrance*>> entrancePools = {};
  // one_way_priorities = {}

  //owl drops

  //spawns

  //warpsongs

  //Shuffle Dungeon Entrances
  if (Settings::ShuffleDungeonEntrances) {
    entrancePools[EntranceType::Dungeon] = GetShuffleableEntrances(EntranceType::Dungeon);

    //If forest is closed don't allow a forest escape via spirit temple hands
    if (Settings::OpenForest.Is(OPENFOREST_CLOSED)) {
      FilterAndEraseFromPool(entrancePools[EntranceType::Dungeon], [](const Entrance* entrance){return entrance->GetParentRegionKey()    == KF_OUTSIDE_DEKU_TREE &&
                                                                                                       entrance->GetConnectedRegionKey() == DEKU_TREE_ENTRYWAY;});
    }

    //decoupled entrances stuff
  }

  //interior entrances
  if (Settings::ShuffleInteriorEntrances.IsNot(SHUFFLEINTERIORS_OFF)) {
    entrancePools[EntranceType::Interior] = GetShuffleableEntrances(EntranceType::Interior);
    //special interiors
    if (Settings::ShuffleInteriorEntrances.Is(SHUFFLEINTERIORS_ALL)) {
      AddElementsToPool(entrancePools[EntranceType::SpecialInterior], GetShuffleableEntrances(EntranceType::SpecialInterior));
    }

    //decoupled entrance stuff
  }

  //grotto entrances

  //overworld entrances
  if (Settings::ShuffleOverworldEntrances) {
    bool excludeOverworldReverse = false; //mix_entrance_pools == all && !decouple_entrances
    entrancePools[EntranceType::Overworld] = GetShuffleableEntrances(EntranceType::Overworld, excludeOverworldReverse);
    // if not worlds[0].decouple_entrances:
    //     entrance_pools['Overworld'].remove(world.get_entrance('GV Lower Stream -> Lake Hylia'))
  }

  //Set shuffled entrances as such
  for (auto& pool : entrancePools) {
    for (Entrance* entrance : pool.second) {
      entrance->SetAsShuffled();
      if (entrance->GetReverse() != nullptr) {
        entrance->GetReverse()->SetAsShuffled();
      }
    }
  }

  //combine entrance pools if mixing pools

  //Build target entrance pools and set the assumption for entrances being reachable
  //one way entrance stuff

  //assume entrance pools for each type
  std::map<EntranceType, std::vector<Entrance*>> targetEntrancePools = {};
  for (auto& pool : entrancePools) {
    targetEntrancePools[pool.first] = AssumeEntrancePool(pool.second);
  }

  //distribution stuff

  //check placed on-way entrances
  //remove replaced entrances so we don't place two in one target
  //remvoe priority targets if any placed entrances point at their regions

  //place priority entrances

  //delete all targets that we just placed from one way target pools so multiple one way entrances don't use the same target

  //shuffle all entrances among pools to shuffle
  for (auto& pool : entrancePools) {
    ShuffleEntrancePool(pool.second, targetEntrancePools[pool.first]);
  }
}

//Create the set of entrances that will be overridden
void CreateEntranceOverrides() {
  entranceOverrides.clear();
  if (noRandomEntrances) {
    return;
  }
  PlacementLog_Msg("\nCREATING ENTRANCE OVERRIDES\n");
  auto allShuffleableEntrances = GetShuffleableEntrances(EntranceType::All, false);

  std::set<s16> shuffledPairIndices;
  u16 entrancePairIndex = 0;

  for (Entrance* entrance : allShuffleableEntrances) {

    //Double-check to make sure the entrance is actually shuffled
    if (!entrance->IsShuffled()) {
      continue;
    }

    if (shuffledPairIndices.find(entrance->GetIndex()) == shuffledPairIndices.end())
    {
      entranceTrackingData.EntrancePairs[entrancePairIndex].StartIndex = entrance->GetIndex();
      entranceTrackingData.EntrancePairs[entrancePairIndex].ReturnIndex = entrance->GetReplacement()->GetReverse()->GetIndex();
      entrancePairIndex++;

      shuffledPairIndices.emplace(entrance->GetIndex());
      shuffledPairIndices.emplace(entrance->GetReplacement()->GetReverse()->GetIndex());
    }

    auto message = "Setting " + entrance->to_string() + "\n";
    PlacementLog_Msg(message);

    s16 originalIndex = entrance->GetIndex();
    s16 originalBlueWarp = entrance->GetBlueWarp();
    s16 replacementIndex = entrance->GetReplacement()->GetIndex();

    entranceOverrides.push_back({
      .index = originalIndex,
      .blueWarp = originalBlueWarp,
      .override = replacementIndex,
    });

    message = "\tOriginal: " + std::to_string(originalIndex) + "\n";
    PlacementLog_Msg(message);
    message = "\tReplacement " + std::to_string(replacementIndex) + "\n";
    PlacementLog_Msg(message);

    //Override both land and water entrances for Hyrule Field -> ZR Front and vice versa
    if (originalIndex == 0x00EA) { //Hyrule Field -> ZR Front land entrance
      entranceOverrides.push_back({
        .index = 0x01D9, //Hyrule Field -> ZR Front water entrance
        .blueWarp = originalBlueWarp,
        .override = replacementIndex,
      });
    } else if (originalIndex == 0x0181) { //ZR Front -> Hyrule Field land entrance
      entranceOverrides.push_back({
        .index = 0x0311, //ZR Front -> Hyrule Field water entrance
        .blueWarp = originalBlueWarp,
        .override = replacementIndex,
      });
    }
  }

  entranceTrackingData.EntrancePairsCount = entrancePairIndex;

  u32 entranceStringOffset = 0;
  bool trackingDataOutOfSpace = false;

  // Create map of entrance indices to their offset into tracking data string data
  std::unordered_map<s16, u16> stringOffsetMap;
  stringOffsetMap.reserve(entranceOverrides.size());
  for (const EntranceOverride& override : entranceOverrides) {
    const auto& entranceName = entranceNames[override.index];
    if (stringOffsetMap.find(override.index) == stringOffsetMap.end()) {
      if (entranceStringOffset + entranceName.size() + 1 >= ENTRANCE_PAIRS_STRING_DATA_SIZE) {
        trackingDataOutOfSpace = true;
        break;
      } else {
        stringOffsetMap[override.index] = entranceStringOffset;
        entranceStringOffset += sprintf(&entranceTrackingData.StringData[entranceStringOffset], "%s", entranceName.c_str()) + 1;
      }
    }
  }

  // Fill in string offset values for the entrance tracking data pairs
  for (int i = 0; i < entranceTrackingData.EntrancePairsCount; i++) {
    if (stringOffsetMap.find(entranceTrackingData.EntrancePairs[i].StartIndex) != stringOffsetMap.end()) {
      entranceTrackingData.EntrancePairs[i].StartStrOffset = stringOffsetMap[entranceTrackingData.EntrancePairs[i].StartIndex];
    } else {
      entranceTrackingData.EntrancePairs[i].StartStrOffset = ENTRANCE_INVALID_STRING_OFFSET;
    }
    if (stringOffsetMap.find(entranceTrackingData.EntrancePairs[i].ReturnIndex) != stringOffsetMap.end()) {
      entranceTrackingData.EntrancePairs[i].ReturnStrOffset = stringOffsetMap[entranceTrackingData.EntrancePairs[i].ReturnIndex];
    } else {
      entranceTrackingData.EntrancePairs[i].ReturnStrOffset = ENTRANCE_INVALID_STRING_OFFSET;
    }
  }

  if (trackingDataOutOfSpace) {
    printf("\x1b[31;Out of space for entrance string data,\nnames may display incorrectly.");
  }
}

std::vector<std::list<Entrance*>> playthroughEntrances;
