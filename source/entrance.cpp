#include "entrance.hpp"

#include "fill.hpp"
#include "settings.hpp"
#include "item_list.hpp"
#include "item_pool.hpp"
#include "item_location.hpp"
#include "debug.hpp"
#include "spoiler_log.hpp"

#include <unistd.h>

#include <vector>
#include <utility>
#include <set>

std::list<EntranceOverride> entranceOverrides = {};

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
    if (entrance->GetConnectedRegion() != NONE) {
      entrance->TempDisconnect();
    }
  }

  std::vector<Entrance*> restrictiveEntrances = {};
  std::vector<Entrance*> softEntrances = {};

  for (Entrance* entrance : entrancesToSplit) {
    Logic::LogicReset();
    // //Apply the effects of all advancement items to search for entrance accessibility
    std::vector<ItemKey> items = FilterFromPool(ItemPool, [](const ItemKey i){ return ItemTable(i).IsAdvancement();});
    for (ItemKey unplacedItem : items) {
      ItemTable(unplacedItem).ApplyEffect();
    }
    // run a search to see what's accessible
    GetAccessibleLocations(allLocations);

    // if an entrance is accessible at all times of day by both ages, it's a soft entrance with no restrictions
    if (AreaTable(entrance->GetParentRegion())->CheckAllAccess(entrance->GetConnectedRegion())) {
      softEntrances.push_back(entrance);
    } else {
      restrictiveEntrances.push_back(entrance);
    }
  }

  //Reconnect all disconnected entrances
  for (Entrance* entrance : entrancesToDisconnect) {
    entrance->Reconnect();
  }

  return {restrictiveEntrances, softEntrances};
}

static bool AreEntrancesCompatible(Entrance* entrance, Entrance* target, std::vector<EntrancePair>& rollbacks) {

  //Entrances shouldn't connect to their own scene, fail in this situation
  if (AreaTable(entrance->GetParentRegion())->regionName != "" && AreaTable(entrance->GetParentRegion())->regionName == AreaTable(target->GetConnectedRegion())->regionName) {
    CitraPrint("Entrance attempted to connect with own scene. Connection failed.");
    return false;
  }

  //one-way entrance stuff

  return true;
}

//Change connections between an entrance and a target assumed entrance, in order to test the connections afterwards if necessary
static void ChangeConnections(Entrance* entrance, Entrance* targetEntrance) {
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
  if (targetEntrance->GetConnectedRegion() != NONE) {
    targetEntrance->Disconnect();
  }
  if (targetEntrance->GetParentRegion() != NONE) {
    AreaTable(targetEntrance->GetParentRegion())->RemoveExit(targetEntrance);
    targetEntrance->SetParentRegion(NONE);
  }
}

static void ConfirmReplacement(Entrance* entrance, Entrance* targetEntrance) {
  DeleteTargetEntrance(targetEntrance);
  CitraPrint("Connected " + entrance->to_string());
  if (entrance->GetReverse() != nullptr /*&& entrances are not decoupled*/) {
    auto replacedReverse = targetEntrance->GetReplacement()->GetReverse();
    DeleteTargetEntrance(replacedReverse->GetReverse()->GetAssumed());
    CitraPrint("Connected " + replacedReverse->to_string());
  }
}

static bool ValidateWorld(Entrance* entrancePlaced) {

  //Ensure some areas can't be reached as the wrong age

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

  //ensure both Impa's House entrances are in the same hint area because the cow is reachable from both sides

  //The player should be able to get back to ToT after going through time, without having collected any items
  //This is important to ensure that the player never loses access to the pedestal after going through time

  //The Big Poe shop should always be accessible as adult without the need to use any bottles

  return true;
}

static bool ReplaceEntrance(Entrance* entrance, Entrance* target, std::vector<EntrancePair>& rollbacks) {

  if (!AreEntrancesCompatible(entrance, target, rollbacks)) {
    return false;
  }
  ChangeConnections(entrance, target);
  if (ValidateWorld(entrance)) {
    rollbacks.push_back(EntrancePair{entrance, target});
  } else {
    return false;
  }
  return true;
}

// Shuffle entrances by placing them instead of entrances in the provided target entrances list
static bool ShuffleEntrances(std::vector<Entrance*>& entrances, std::vector<Entrance*>& targetEntrances, std::vector<EntrancePair>& rollbacks) {

  //place all entrances in the pool, validating after every placement
  for (Entrance* entrance : entrances) {
    if (entrance->GetConnectedRegion() != NONE) {
      continue;
    }

    Shuffle(targetEntrances);
    for (Entrance* target : targetEntrances) {
      if (target->GetConnectedRegion() == NONE) {
        continue;
      }

      std::string message = "Attempting to connect " + entrance->to_string() + " and " + target->to_string();
      CitraPrint(message);
      if (ReplaceEntrance(entrance, target, rollbacks)) {
        CitraPrint("success");
        break;
      } else if (entrance->GetConnectedRegion() != NONE) {
        RestoreConnections(entrance, target);
      }
    }

    if (entrance->GetConnectedRegion() == NONE) {
      std::string message = "No more valid entrances for " + entrance->to_string();
      CitraPrint(message);
      return false;
    }
  }

  //all entrances were validly connected
  return true;
}

static void ShuffleEntrancePool(std::vector<Entrance*>& entrancePool, std::vector<Entrance*>& targetEntrances) {

  auto splitEntrances = SplitEntrancesByRequirements(entrancePool, targetEntrances);

  auto& restrictiveEntrances = splitEntrances[0];
  auto& softEntrances = splitEntrances[1];

  int retries = 20;
  while (retries > 0) {
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
}

//Process for setting up the shuffling of all entrances to be shuffled
void ShuffleAllEntrances() {

  std::vector<EntranceInfoPair> entranceShuffleTable = {
                           //Parent Region                     Connected Region                  index   blue warp
    {{EntranceType::Dungeon, KF_OUTSIDE_DEKU_TREE,             DEKU_TREE_ENTRYWAY,               0x0000},
     {EntranceType::Dungeon, DEKU_TREE_ENTRYWAY,               KF_OUTSIDE_DEKU_TREE,             0x0209, 0x0457}},
    {{EntranceType::Dungeon, DEATH_MOUNTAIN_TRAIL,             DODONGOS_CAVERN_ENTRYWAY,         0x0004},
     {EntranceType::Dungeon, DODONGOS_CAVERN_ENTRYWAY,         DEATH_MOUNTAIN_TRAIL,             0x0242, 0x047A}},
    {{EntranceType::Dungeon, ZORAS_FOUNTAIN,                   JABU_JABUS_BELLY_ENTRYWAY,        0x0028},
     {EntranceType::Dungeon, JABU_JABUS_BELLY_ENTRYWAY,        ZORAS_FOUNTAIN,                   0x0221, 0x010E}},
    {{EntranceType::Dungeon, SACRED_FOREST_MEADOW,             FOREST_TEMPLE_ENTRYWAY,           0x0169},
     {EntranceType::Dungeon, FOREST_TEMPLE_ENTRYWAY,           SACRED_FOREST_MEADOW,             0x0215, 0x0608}},
    {{EntranceType::Dungeon, DMC_CENTRAL_LOCAL,                FIRE_TEMPLE_ENTRYWAY,             0x0165},
     {EntranceType::Dungeon, FIRE_TEMPLE_ENTRYWAY,             DMC_CENTRAL_LOCAL,                0x024A, 0x0564}},
    {{EntranceType::Dungeon, LAKE_HYLIA,                       WATER_TEMPLE_ENTRYWAY,            0x0010},
     {EntranceType::Dungeon, WATER_TEMPLE_ENTRYWAY,            LAKE_HYLIA,                       0x021D, 0x060C}},
    {{EntranceType::Dungeon, DESERT_COLOSSUS,                  SPIRIT_TEMPLE_ENTRYWAY,           0x0082},
     {EntranceType::Dungeon, SPIRIT_TEMPLE_ENTRYWAY,           DESERT_COLOSSUS,                  0x01E1, 0x0610}},
    {{EntranceType::Dungeon, GRAVEYARD_WARP_PAD_REGION,        SHADOW_TEMPLE_ENTRYWAY,           0x0037},
     {EntranceType::Dungeon, SHADOW_TEMPLE_ENTRYWAY,           GRAVEYARD_WARP_PAD_REGION,        0x0205, 0x0580}},
    {{EntranceType::Dungeon, KAKARIKO_VILLAGE,                 BOTTOM_OF_THE_WELL_ENTRYWAY,      0x0098},
     {EntranceType::Dungeon, BOTTOM_OF_THE_WELL_ENTRYWAY,      KAKARIKO_VILLAGE,                 0x02A6}},
    {{EntranceType::Dungeon, ZORAS_FOUNTAIN,                   ICE_CAVERN_ENTRYWAY,              0x0088},
     {EntranceType::Dungeon, ICE_CAVERN_ENTRYWAY,              ZORAS_FOUNTAIN,                   0x03D4}},
    {{EntranceType::Dungeon, GERUDO_FORTRESS,                  GERUDO_TRAINING_GROUNDS_ENTRYWAY, 0x0008},
     {EntranceType::Dungeon, GERUDO_TRAINING_GROUNDS_ENTRYWAY, GERUDO_FORTRESS,                  0x03A8}},
  };

  SetAllEntrancesData(entranceShuffleTable);

  // one_way_entrance_pools = OrderedDict()
  std::vector<Entrance*> entrancePool = {};
  // one_way_priorities = {}

  //owl drops

  //spawns

  //warpsongs

  //Shuffle Dungeon Entrances
  if (Settings::ShuffleDungeonEntrances) {
    AddElementsToPool(entrancePool, GetShuffleableEntrances(EntranceType::Dungeon));

    //If forest is closed don't allow a forest escape via spirit temple hands
    // if (Settings::OpenForest.Is(OPENFOREST_CLOSED)) {
    //   FilterAndEraseFromPool(entrancePool, [](const Entrance* entrance){return entrance->GetParentRegion()    == KF_OUTSIDE_DEKU_TREE &&
    //                                                                            entrance->GetConnectedRegion() == DEKU_TREE_ENTRYWAY;});
    // }

    //decoupled entrances stuff
  }

  //interior entrances

  //grotto entrances

  //overworld entrances

  //Set shuffled entrances as such
  for (Entrance* entrance : entrancePool) {
    entrance->SetAsShuffled();
    if (entrance->GetReverse() != nullptr) {
      entrance->GetReverse()->SetAsShuffled();
    }
  }

  //combine entrance pools if mixing pools

  //Build target entrance pools and set the assumption for entrances being reachable
  //one way entrance stuff

  //other entrances
  std::vector<Entrance*> targetEntrancePool = {};
  targetEntrancePool = AssumeEntrancePool(entrancePool);

  //distribution stuff

  //check placed on-way entrances
  //remove replaced entrances so we don't place two in one target
  //remvoe priority targets if any placed entrances point at their regions

  //place priority entrances

  //delete all targets that we just placed from one way target pools so multiple one way entrances don't use the same target

  //shuffle all entrances among pools to shuffle
  ShuffleEntrancePool(entrancePool, targetEntrancePool);

}

//Create the set of entrances that will be overridden
void CreateEntranceOverrides() {
  entranceOverrides.clear();
  PlacementLog_Msg("Creating entrance overrides");
  auto allShuffleableEntrances = GetShuffleableEntrances(EntranceType::All, false);

  for (Entrance* entrance : allShuffleableEntrances) {
    auto message = "Setting " + entrance->to_string();
    PlacementLog_Msg(message);

    s16 originalIndex = entrance->GetIndex();
    s16 originalBlueWarp = entrance->GetBlueWarp();
    s16 replacementIndex = entrance->GetReplacement()->GetIndex();

    entranceOverrides.push_back({
      .index = originalIndex,
      .blueWarp = originalBlueWarp,
      .override = replacementIndex,
    });

    message = "Original: " + std::to_string(originalIndex);
    PlacementLog_Msg(message);
    message = "Replacement " + std::to_string(replacementIndex);
    PlacementLog_Msg(message);
  }
}
