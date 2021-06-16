#include "entrance.hpp"

#include "fill.hpp"
#include "settings.hpp"
#include "../code/src/entrance.h"

#include <unistd.h>

#include <vector>
#include <utility>
                             //primary,  secondary
using EntrancePair = std::pair<Entrance, Entrance>;

Entrance::Entrance() = default;
Entrance::Entrance(EntranceType type_, AreaKey parentRegion_, AreaKey connectedRegion_, s16 index_, s16 blueWarp_ /*= 0x0000*/)
  : type(type_),
    parentRegion(parentRegion_),
    connectedRegion(connectedRegion_),
    index(index_),
    blueWarp(blueWarp_) {}

Entrance::~Entrance() = default;

std::vector<Entrance> GetAllEntrances(std::vector<EntrancePair> entranceTable) {
  std::vector<Entrance> allEntrances;
  for (auto& entrancePair : entranceTable) {
    allEntrances.push_back(entrancePair.first);
    allEntrances.push_back(entrancePair.second);
  }
  return allEntrances;
}

void SetAllEntrancesData(std::vector<EntrancePair>& entranceTable) {
  for (EntrancePair& entrancePair : entranceTable) {
    auto& forwardEntrance = entrancePair.first;
    auto& returnEntrance = entrancePair.second;

    forwardEntrance.SetAsPrimary();
    // TODO: Grotto stuff
    if (returnEntrance.GetParentRegion() != NONE){

      forwardEntrance.BindTwoWay(returnEntrance);
      // TODO: Grotto stuff
    }
  }
}

std::vector<Entrance> AssumeEntrancePool(std::vector<Entrance>& entrancePool) {
  std::vector<Entrance> assumedPool = {};
  for (Entrance& entrance : entrancePool) {
    CitraPrint("assumedForward = entrance.AssumeReachable()");
    sleep(5);
    auto assumedForward = entrance.AssumeReachable();
    CitraPrint("DONE");
    sleep(5);
    if (entrance.GetReverse() != nullptr /*&& !DecoupleEntrances*/) {
      CitraPrint("assumedReturn = entrance.GetReverse()->AssumeReachable()");
      sleep(5);
      auto assumedReturn = entrance.GetReverse()->AssumeReachable();
      //mixed pools stuff
      CitraPrint("BindTwoWay");
      sleep(5);
      assumedForward.BindTwoWay(assumedReturn);
    }
    assumedPool.push_back(assumedForward);
  }
  return assumedPool;
}

//Process for setting up the shuffling of all entrances to be shuffled
void ShuffleAllEntrances() {

  std::vector<EntrancePair> entranceShuffleTable = {
                     //From                              To                                index   blue warp
    {Entrance::Dungeon(KF_OUTSIDE_DEKU_TREE,             DEKU_TREE_ENTRYWAY,               0x0000),
     Entrance::Dungeon(DEKU_TREE_ENTRYWAY,               KF_OUTSIDE_DEKU_TREE,             0x0209, 0x0457),},
    {Entrance::Dungeon(DEATH_MOUNTAIN_TRAIL,             DODONGOS_CAVERN_ENTRYWAY,         0x0004),
     Entrance::Dungeon(DODONGOS_CAVERN_ENTRYWAY,         DEATH_MOUNTAIN_TRAIL,             0x0242, 0x047A),},
    {Entrance::Dungeon(ZORAS_FOUNTAIN,                   JABU_JABUS_BELLY_ENTRYWAY,        0x0028),
     Entrance::Dungeon(JABU_JABUS_BELLY_ENTRYWAY,        ZORAS_FOUNTAIN,                   0x0221, 0x010E),},
    {Entrance::Dungeon(SACRED_FOREST_MEADOW,             FOREST_TEMPLE_ENTRYWAY,           0x0169),
     Entrance::Dungeon(FOREST_TEMPLE_ENTRYWAY,           SACRED_FOREST_MEADOW,             0x0215, 0x0608),},
    {Entrance::Dungeon(DMC_CENTRAL_LOCAL,                FIRE_TEMPLE_ENTRYWAY,             0x0165),
     Entrance::Dungeon(FIRE_TEMPLE_ENTRYWAY,             DMC_CENTRAL_LOCAL,                0x024A, 0x0564),},
    {Entrance::Dungeon(LAKE_HYLIA,                       WATER_TEMPLE_ENTRYWAY,            0x0010),
     Entrance::Dungeon(WATER_TEMPLE_ENTRYWAY,            LAKE_HYLIA,                       0x021D, 0x060C),},
    {Entrance::Dungeon(DESERT_COLOSSUS,                  SPIRIT_TEMPLE_ENTRYWAY,           0x0082),
     Entrance::Dungeon(SPIRIT_TEMPLE_ENTRYWAY,           DESERT_COLOSSUS,                  0x01E1, 0x0610),},
    {Entrance::Dungeon(GRAVEYARD_WARP_PAD_REGION,        SHADOW_TEMPLE_ENTRYWAY,           0x0037),
     Entrance::Dungeon(SHADOW_TEMPLE_ENTRYWAY,           GRAVEYARD_WARP_PAD_REGION,        0x0205, 0x0580),},
    {Entrance::Dungeon(KAKARIKO_VILLAGE,                 BOTTOM_OF_THE_WELL_ENTRYWAY,      0x0098),
     Entrance::Dungeon(BOTTOM_OF_THE_WELL_ENTRYWAY,      KAKARIKO_VILLAGE,                 0x02A6),},
    {Entrance::Dungeon(ZORAS_FOUNTAIN,                   ICE_CAVERN_ENTRYWAY,              0x0088),
     Entrance::Dungeon(ICE_CAVERN_ENTRYWAY,              ZORAS_FOUNTAIN,                   0x03D4),},
    {Entrance::Dungeon(GERUDO_FORTRESS,                  GERUDO_TRAINING_GROUNDS_ENTRYWAY, 0x0008),
     Entrance::Dungeon(GERUDO_TRAINING_GROUNDS_ENTRYWAY, GERUDO_FORTRESS,                  0x03A8),},
  };

  SetAllEntrancesData(entranceShuffleTable);

  auto allEntrances = GetAllEntrances(entranceShuffleTable);

  // one_way_entrance_pools = OrderedDict()
     std::vector<Entrance> entrancePool = {};
  // one_way_priorities = {}

  //owl drops

  //spawns

  //warpsongs

  //Shuffle Dungeon Entrances
  if (Settings::ShuffleDungeonEntrances) {
    AddElementsToPool(entrancePool, FilterFromPool(allEntrances, [](const Entrance entrance){CitraPrint(std::to_string(entrance.IsPrimary())); return entrance.GetType() == EntranceType::Dungeon && entrance.IsPrimary();}));

    //open forest stuff

    //decoupled entrances stuff
  }

  //interior entrances

  //grotto entrances

  //overworld entrances

  //Set shuffled entrances as such
  CitraPrint("Set Entrances as shuffled");
  sleep(0.1);
  CitraPrint(std::to_string(entrancePool.size()));
  sleep(0.1);
  for (Entrance& entrance : entrancePool) {
    entrance.SetAsShuffled();
    if (entrance.GetReverse() != nullptr) {
      entrance.GetReverse()->SetAsShuffled();
    }
  }

  //combine entrance pools if decoupled entrances

  //Build target entrance pools and set the assumption for entrances being reachable
  //one way entrance stuff

  //other entrances
  CitraPrint("Assume Entrance Pool");
  sleep(0.1);
  std::vector<Entrance> targetEntrancePool = AssumeEntrancePool(entrancePool);

  CitraPrint("Target Entrances: ");
  sleep(0.1);
  CitraPrint(std::to_string(targetEntrancePool.size()));
  sleep(0.1);
  for (auto& entrance : targetEntrancePool) {
    CitraPrint(entrance.GetName());
  }
  sleep(10000);

  //distribution stuff

  //check placed on-way entrances
  //remove replaced entrances so we don't place two in one target
  //remvoe priority targets if any placed entrances point at their regions

  //place priority entrances

  //delete all targets that we just placed from one way target pools so multiple one way entrances don't use the same target

  //shuffle all entrances among pools to shuffle

}
