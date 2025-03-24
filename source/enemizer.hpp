#pragma once

#include "../code/src/enemizer.h"

#include <string>
#include <functional>

#include "debug.hpp"

namespace Enemizer {

// Conditions used for the logic to place enemies.
enum class LocType {
    ABOVE_GROUND,  // Location is on or above walkable ground.
    ABOVE_VOID,    // Location is over a void plane. Enemy must be able to fly.
    UNDERWATER,    // Location is underwater. Enemy must be defeatable with hookshot and iron boots.
    ABOVE_WATER,   // Location is in the air above a water surface. Enemy must be able to float or fly.
    SHALLOW_WATER, // Location is on or above shallow water.
    SPAWNER,       // Location is a grounded enemy spawner (stalchildren, leevers).
};

typedef enum EnemyId {
    ENEMY_POE,
    ENEMY_STALFOS,
    ENEMY_OCTOROK,
    ENEMY_WALLMASTER,
    ENEMY_DODONGO,
    ENEMY_KEESE_NORMAL,
    ENEMY_KEESE_FIRE,
    ENEMY_KEESE_ICE,
    ENEMY_TEKTITE_RED,
    ENEMY_TEKTITE_BLUE,
    ENEMY_LEEVER,
    ENEMY_PEAHAT,
    ENEMY_PEAHAT_LARVA,
    ENEMY_LIZALFOS,
    ENEMY_DINOLFOS,
    ENEMY_GOHMA_LARVA,
    ENEMY_SHABOM,
    ENEMY_DODONGO_BABY,
    ENEMY_DARK_LINK,
    ENEMY_BIRI,
    ENEMY_TAILPASARAN,
    ENEMY_SKULLTULA,
    ENEMY_TORCH_SLUG,
    ENEMY_STINGER_FLOOR,
    ENEMY_MOBLIN_CLUB,
    ENEMY_MOBLIN_SPEAR,
    ENEMY_ARMOS,
    ENEMY_DEKU_BABA_SMALL,
    ENEMY_DEKU_BABA_BIG,
    ENEMY_MAD_SCRUB,
    ENEMY_BARI,
    ENEMY_BUBBLE_BLUE,
    ENEMY_BUBBLE_FIRE,
    ENEMY_BUBBLE_WHITE,
    ENEMY_BUBBLE_GREEN,
    ENEMY_FLYING_FLOOR_TILE,
    ENEMY_BEAMOS,
    ENEMY_FLOORMASTER,
    ENEMY_REDEAD,
    ENEMY_GIBDO,
    ENEMY_POE_SISTER,
    ENEMY_DEAD_HAND_HAND,
    ENEMY_SKULLWALLTULA,
    ENEMY_FLARE_DANCER,
    ENEMY_DEAD_HAND,
    ENEMY_SHELL_BLADE,
    ENEMY_BIG_OCTO,
    ENEMY_DEKU_BABA_WITHERED,
    ENEMY_LIKE_LIKE,
    ENEMY_PARASITIC_TENTACLE,
    ENEMY_SPIKE,
    ENEMY_ANUBIS,
    ENEMY_IRON_KNUCKLE,
    ENEMY_SKULL_KID,
    ENEMY_FLYING_POT,
    ENEMY_FREEZARD,
    ENEMY_STINGER_WATER,
    ENEMY_GERUDO_FIGHTER,
    ENEMY_WOLFOS,
    ENEMY_STALCHILD,
    ENEMY_GUAY,
    ENEMY_MAX,
} EnemyId;

class EnemyType {
  public:
    EnemyType() = default;
    EnemyType(std::string _name, u16 _actorId, std::vector<u16> _possibleParams, std::vector<LocType> _validLocTypes)
        : name(std::move(_name)), actorId(_actorId), possibleParams(_possibleParams),
          validLocTypes(std::move(_validLocTypes)) {
    }

    bool CanBeAtLocTypes(std::vector<LocType> locTypes) const {
        return std::all_of(locTypes.begin(), locTypes.end(), [this](LocType locType) {
            return std::find(validLocTypes.begin(), validLocTypes.end(), locType) != validLocTypes.end();
        });
    }

    std::string name;
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

    u16 vanillaEnemyId;
    std::vector<LocType> types;
    EnemyType randomizedEnemy;
    u16 randomizedParams;
};

using EnemyLocationsMap_Room  = std::unordered_map<u8, EnemyLocation>;
using EnemyLocationsMap_Layer = std::unordered_map<u8, EnemyLocationsMap_Room>;
using EnemyLocationsMap_Scene = std::unordered_map<u8, EnemyLocationsMap_Layer>;
using EnemyLocationsMap       = std::unordered_map<u8, EnemyLocationsMap_Scene>;

// Possible enemies to choose from for randomization.
extern std::array<EnemyType, ENEMY_MAX> enemyTypes;
// Map of enemy locations that will be randomized. Indices are [scene][layer][room][actorEntry].
// To override dynamic enemy spawners, actorEntry is set to 0xFF.
extern EnemyLocationsMap enemyLocations;

void InitEnemyTypes(void);
void InitEnemyLocations(void);
void AddDuplicateLocations(void);
void RandomizeEnemies(void);
void FillPatchOverrides(std::vector<EnemyOverride>& enemyOverrides);

} // namespace Enemizer
