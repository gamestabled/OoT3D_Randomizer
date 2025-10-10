#pragma once

#include "../code/src/enemizer.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "debug.hpp"
#include "settings.hpp"

namespace Enemizer {

// Conditions used for the logic to place enemies.
enum class LocType {
    ABOVE_GROUND,  // Location is on or above walkable ground.
    NARROW_GROUND, // Location is on ground near a pit which the enemy must not be able to fall into.
    ABOVE_VOID,    // Location is over a void plane. Enemy must be able to fly.
    UNDERWATER,    // Location is underwater. Enemy must be defeatable with hookshot and iron boots.
    ABOVE_WATER,   // Location is in the air above a water surface. Enemy must be able to float or fly.
    SHALLOW_WATER, // Location is on or above shallow water.
    SPAWNER,       // Location is a grounded enemy spawner (stalchildren, leevers).
};

class EnemyType {
  public:
    EnemyType() = default;
    EnemyType(std::string _name, bool* _soulVar, u16 _actorId, std::vector<u16> _possibleParams,
              std::vector<LocType> _validLocTypes)
        : name(std::move(_name)), soulVar(_soulVar), actorId(_actorId), possibleParams(_possibleParams),
          validLocTypes(std::move(_validLocTypes)) {
    }

    bool CanBeAtLocTypes(std::vector<LocType> locTypes) const {
        return std::all_of(locTypes.begin(), locTypes.end(), [this](LocType locType) {
            return std::find(validLocTypes.begin(), validLocTypes.end(), locType) != validLocTypes.end();
        });
    }

    bool HasSoul() const {
        return Settings::ShuffleEnemySouls.IsNot(SHUFFLEENEMYSOULS_ALL) || *soulVar;
    }

    std::string name;
    bool* soulVar;
    u16 actorId;
    std::vector<u16> possibleParams; // Values to randomly select as actor params, without affecting the logic.
    std::vector<LocType> validLocTypes;
};

class EnemyLocation {
  public:
    EnemyLocation() = default;
    EnemyLocation(u16 _vanillaEnemyId, LocType _type) : vanillaEnemyId(_vanillaEnemyId), types({ _type }) {
    }
    EnemyLocation(u16 _vanillaEnemyId, std::vector<LocType> _types)
        : vanillaEnemyId(_vanillaEnemyId), types(std::move(_types)) {
    }

    u16 GetEnemyId() {
        return randomizedEnemyId != ENEMY_INVALID ? randomizedEnemyId : vanillaEnemyId;
    }

    bool IsUnderwater() {
        return std::find(types.begin(), types.end(), LocType::UNDERWATER) != types.end();
    }

    u16 vanillaEnemyId    = 0;
    u16 randomizedEnemyId = 0;
    u16 randomizedParams  = 0;
    std::vector<LocType> types;
};

using EnemyLocationsMap_Room  = std::unordered_map<u8, EnemyLocation>;
using EnemyLocationsMap_Layer = std::unordered_map<u8, EnemyLocationsMap_Room>;
using EnemyLocationsMap_Scene = std::unordered_map<u8, EnemyLocationsMap_Layer>;
using EnemyLocationsMap       = std::unordered_map<u8, EnemyLocationsMap_Scene>;

// Possible enemies to choose from for randomization.
extern EnemyType enemyTypes[ENEMY_MAX];
// Map of enemy locations that will be randomized. Indices are [scene][layer][room][actorEntry].
// To override dynamic enemy spawners, actorEntry is set to 0xFF.
extern EnemyLocationsMap enemyLocations;

void InitEnemyTypes(void);
void InitEnemyLocations(void);
void AddDuplicateLocations(void);
void RandomizeEnemies(void);
void FillPatchOverrides(std::vector<EnemyOverride>& enemyOverrides);

} // namespace Enemizer
