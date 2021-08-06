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
#include <map>

std::list<EntranceOverride> entranceOverrides = {};
static bool noRandomEntrances = false;

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
    for (auto& entrancePair : entranceShuffleTable) {

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
    std::vector<ItemKey> items = FilterFromPool(ItemPool, [](const ItemKey i) {
        return ItemTable(i).IsAdvancement();
    });
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

static bool ValidateWorld(Entrance* entrancePlaced) {
    PlacementLog_Msg("Validating world\n");
    //Ensure some areas can't be reached as the wrong age

    // Check to make sure all locations are still reachable
    Logic::LogicReset();
    std::vector<ItemKey> itemsToPlace = FilterFromPool(ItemPool, [](const ItemKey i) {
        return ItemTable(i).IsAdvancement();
    });
    for (ItemKey unplacedItem : itemsToPlace) {
        ItemTable(unplacedItem).ApplyEffect();
    }
    GetAccessibleLocations(allLocations, SearchMode::AllLocationsReachable);
    if (!allLocationsReachable) {
        return false;
    }

    //ensure both Impa's House entrances are in the same hint area because the cow is reachable from both sides

    //check certain conditions when certain types of ER are enabled
    EntranceType type = EntranceType::None;
    if (entrancePlaced != nullptr) {
        type = entrancePlaced->GetType();
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
            if (!success) {
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

//Process for setting up the shuffling of all entrances to be shuffled
void ShuffleAllEntrances() {

    std::vector<EntranceInfoPair> entranceShuffleTable = {
        //Parent Region                     Connected Region                  index   blue warp
        {   {EntranceType::Dungeon,   KF_OUTSIDE_DEKU_TREE,             DEKU_TREE_ENTRYWAY,               0x0000},
            {EntranceType::Dungeon,   DEKU_TREE_ENTRYWAY,               KF_OUTSIDE_DEKU_TREE,             0x0209, 0x0457}
        },
        {   {EntranceType::Dungeon,   DEATH_MOUNTAIN_TRAIL,             DODONGOS_CAVERN_ENTRYWAY,         0x0004},
            {EntranceType::Dungeon,   DODONGOS_CAVERN_ENTRYWAY,         DEATH_MOUNTAIN_TRAIL,             0x0242, 0x047A}
        },
        {   {EntranceType::Dungeon,   ZORAS_FOUNTAIN,                   JABU_JABUS_BELLY_ENTRYWAY,        0x0028},
            {EntranceType::Dungeon,   JABU_JABUS_BELLY_ENTRYWAY,        ZORAS_FOUNTAIN,                   0x0221, 0x010E}
        },
        {   {EntranceType::Dungeon,   SACRED_FOREST_MEADOW,             FOREST_TEMPLE_ENTRYWAY,           0x0169},
            {EntranceType::Dungeon,   FOREST_TEMPLE_ENTRYWAY,           SACRED_FOREST_MEADOW,             0x0215, 0x0608}
        },
        {   {EntranceType::Dungeon,   DMC_CENTRAL_LOCAL,                FIRE_TEMPLE_ENTRYWAY,             0x0165},
            {EntranceType::Dungeon,   FIRE_TEMPLE_ENTRYWAY,             DMC_CENTRAL_LOCAL,                0x024A, 0x0564}
        },
        {   {EntranceType::Dungeon,   LAKE_HYLIA,                       WATER_TEMPLE_ENTRYWAY,            0x0010},
            {EntranceType::Dungeon,   WATER_TEMPLE_ENTRYWAY,            LAKE_HYLIA,                       0x021D, 0x060C}
        },
        {   {EntranceType::Dungeon,   DESERT_COLOSSUS,                  SPIRIT_TEMPLE_ENTRYWAY,           0x0082},
            {EntranceType::Dungeon,   SPIRIT_TEMPLE_ENTRYWAY,           DESERT_COLOSSUS,                  0x01E1, 0x0610}
        },
        {   {EntranceType::Dungeon,   GRAVEYARD_WARP_PAD_REGION,        SHADOW_TEMPLE_ENTRYWAY,           0x0037},
            {EntranceType::Dungeon,   SHADOW_TEMPLE_ENTRYWAY,           GRAVEYARD_WARP_PAD_REGION,        0x0205, 0x0580}
        },
        {   {EntranceType::Dungeon,   KAKARIKO_VILLAGE,                 BOTTOM_OF_THE_WELL_ENTRYWAY,      0x0098},
            {EntranceType::Dungeon,   BOTTOM_OF_THE_WELL_ENTRYWAY,      KAKARIKO_VILLAGE,                 0x02A6}
        },
        {   {EntranceType::Dungeon,   ZORAS_FOUNTAIN,                   ICE_CAVERN_ENTRYWAY,              0x0088},
            {EntranceType::Dungeon,   ICE_CAVERN_ENTRYWAY,              ZORAS_FOUNTAIN,                   0x03D4}
        },
        {   {EntranceType::Dungeon,   GERUDO_FORTRESS,                  GERUDO_TRAINING_GROUNDS_ENTRYWAY, 0x0008},
            {EntranceType::Dungeon,   GERUDO_TRAINING_GROUNDS_ENTRYWAY, GERUDO_FORTRESS,                  0x03A8}
        },
        {   {EntranceType::Overworld, KOKIRI_FOREST,                    LW_BRIDGE_FROM_FOREST,            0x05E0},
            {EntranceType::Overworld, LW_BRIDGE,                        KOKIRI_FOREST,                    0x020D}
        },
        {   {EntranceType::Overworld, KOKIRI_FOREST,                    THE_LOST_WOODS,                   0x011E},
            {EntranceType::Overworld, LW_FOREST_EXIT,                   KOKIRI_FOREST,                    0x0286}
        },
        {   {EntranceType::Overworld, THE_LOST_WOODS,                   GC_WOODS_WARP,                    0x04E2},
            {EntranceType::Overworld, GC_WOODS_WARP,                    THE_LOST_WOODS,                   0x04D6}
        },
        {   {EntranceType::Overworld, THE_LOST_WOODS,                   ZORAS_RIVER,                      0x01DD},
            {EntranceType::Overworld, ZORAS_RIVER,                      THE_LOST_WOODS,                   0x04DA}
        },
        {   {EntranceType::Overworld, LW_BEYOND_MIDO,                   SFM_ENTRYWAY,                     0x00FC},
            {EntranceType::Overworld, SFM_ENTRYWAY,                     LW_BEYOND_MIDO,                   0x01A9}
        },
        {   {EntranceType::Overworld, LW_BRIDGE,                        HYRULE_FIELD,                     0x0185},
            {EntranceType::Overworld, HYRULE_FIELD,                     LW_BRIDGE,                        0x04DE}
        },
        {   {EntranceType::Overworld, HYRULE_FIELD,                     LAKE_HYLIA,                       0x0102},
            {EntranceType::Overworld, LAKE_HYLIA,                       HYRULE_FIELD,                     0x0189}
        },
        {   {EntranceType::Overworld, HYRULE_FIELD,                     GERUDO_VALLEY,                    0x0117},
            {EntranceType::Overworld, GERUDO_VALLEY,                    HYRULE_FIELD,                     0x018D}
        },
        {   {EntranceType::Overworld, HYRULE_FIELD,                     MARKET_ENTRANCE,                  0x0276},
            {EntranceType::Overworld, MARKET_ENTRANCE,                  HYRULE_FIELD,                     0x01FD}
        },
        {   {EntranceType::Overworld, HYRULE_FIELD,                     KAKARIKO_VILLAGE,                 0x00DB},
            {EntranceType::Overworld, KAKARIKO_VILLAGE,                 HYRULE_FIELD,                     0x017D}
        },
        {   {EntranceType::Overworld, HYRULE_FIELD,                     ZR_FRONT,                         0x00EA},
            {EntranceType::Overworld, ZR_FRONT,                         HYRULE_FIELD,                     0x0181}
        },
        {   {EntranceType::Overworld, HYRULE_FIELD,                     LON_LON_RANCH,                    0x0157},
            {EntranceType::Overworld, LON_LON_RANCH,                    HYRULE_FIELD,                     0x01F9}
        },
        {   {EntranceType::Overworld, LAKE_HYLIA,                       ZORAS_DOMAIN,                     0x0328},
            {EntranceType::Overworld, ZORAS_DOMAIN,                     LAKE_HYLIA,                       0x0560}
        },
        {   {EntranceType::Overworld, GV_FORTRESS_SIDE,                 GERUDO_FORTRESS,                  0x0129},
            {EntranceType::Overworld, GERUDO_FORTRESS,                  GV_FORTRESS_SIDE,                 0x022D}
        },
        {   {EntranceType::Overworld, GF_OUTSIDE_GATE,                  WASTELAND_NEAR_FORTRESS,          0x0130},
            {EntranceType::Overworld, WASTELAND_NEAR_FORTRESS,          GF_OUTSIDE_GATE,                  0x03AC}
        },
        {   {EntranceType::Overworld, WASTELAND_NEAR_COLOSSUS,          DESERT_COLOSSUS,                  0x0123},
            {EntranceType::Overworld, DESERT_COLOSSUS,                  WASTELAND_NEAR_COLOSSUS,          0x0365}
        },
        {   {EntranceType::Overworld, MARKET_ENTRANCE,                  THE_MARKET,                       0x00B1},
            {EntranceType::Overworld, THE_MARKET,                       MARKET_ENTRANCE,                  0x0033}
        },
        {   {EntranceType::Overworld, THE_MARKET,                       CASTLE_GROUNDS,                   0x0138},
            {EntranceType::Overworld, CASTLE_GROUNDS,                   THE_MARKET,                       0x025A}
        },
        {   {EntranceType::Overworld, THE_MARKET,                       TOT_ENTRANCE,                     0x0171},
            {EntranceType::Overworld, TOT_ENTRANCE,                     THE_MARKET,                       0x025E}
        },
        {   {EntranceType::Overworld, KAKARIKO_VILLAGE,                 THE_GRAVEYARD,                    0x00E4},
            {EntranceType::Overworld, THE_GRAVEYARD,                    KAKARIKO_VILLAGE,                 0x0195}
        },
        {   {EntranceType::Overworld, KAK_BEHIND_GATE,                  DEATH_MOUNTAIN_TRAIL,             0x013D},
            {EntranceType::Overworld, DEATH_MOUNTAIN_TRAIL,             KAK_BEHIND_GATE,                  0x0191}
        },
        {   {EntranceType::Overworld, DEATH_MOUNTAIN_TRAIL,             GORON_CITY,                       0x014D},
            {EntranceType::Overworld, GORON_CITY,                       DEATH_MOUNTAIN_TRAIL,             0x01B9}
        },
        {   {EntranceType::Overworld, GC_DARUNIAS_CHAMBER,              DMC_LOWER_LOCAL,                  0x0246},
            {EntranceType::Overworld, DMC_LOWER_NEARBY,                 GC_DARUNIAS_CHAMBER,              0x01C1}
        },
        {   {EntranceType::Overworld, DMT_SUMMIT,                       DMC_UPPER_LOCAL,                  0x0147},
            {EntranceType::Overworld, DMC_UPPER_NEARBY,                 DMT_SUMMIT,                       0x01BD}
        },
        {   {EntranceType::Overworld, ZR_BEHIND_WATERFALL,              ZORAS_DOMAIN,                     0x0108},
            {EntranceType::Overworld, ZORAS_DOMAIN,                     ZR_BEHIND_WATERFALL,              0x019D}
        },
        {   {EntranceType::Overworld, ZD_BEHIND_KING_ZORA,              ZORAS_FOUNTAIN,                   0x0225},
            {EntranceType::Overworld, ZORAS_FOUNTAIN,                   ZD_BEHIND_KING_ZORA,              0x01A1}
        },
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
            FilterAndEraseFromPool(entrancePools[EntranceType::Dungeon], [](const Entrance * entrance) {
                return entrance->GetParentRegionKey()    == KF_OUTSIDE_DEKU_TREE &&
                       entrance->GetConnectedRegionKey() == DEKU_TREE_ENTRYWAY;
            });
        }

        //decoupled entrances stuff
    }

    //interior entrances

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

    for (Entrance* entrance : allShuffleableEntrances) {

        //Double-check to make sure the entrance is actually shuffled
        if (!entrance->IsShuffled()) {
            continue;
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
}

std::vector<std::list<Entrance*>> playthroughEntrances;
