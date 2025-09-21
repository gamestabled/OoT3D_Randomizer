#include "enemizer.hpp"
#include "random.hpp"
#include "settings.hpp"

namespace Enemizer {

static void AssignRandomEnemy(EnemyLocation& loc) {
    std::vector<u16> enemyOptions;
    for (u16 enemyId = ENEMY_INVALID + 1; enemyId < ENEMY_MAX; enemyId++) {
        EnemyType& candidate = enemyTypes[enemyId];
        u8 enemyMode         = Settings::enemizerListOptions.at(enemyId)->GetSelectedOptionIndex();
        if (enemyMode == ENEMYMODE_RANDOMIZED &&
            (enemyId == loc.vanillaEnemyId || candidate.CanBeAtLocTypes(loc.types))) {
            enemyOptions.push_back(enemyId);
        }
    }
    if (enemyOptions.size() > 0) {
        loc.randomizedEnemyId = RandomElement(enemyOptions);
        loc.randomizedParams  = RandomElement(enemyTypes[loc.randomizedEnemyId].possibleParams);
    }
}

void RandomizeEnemies() {
    InitEnemyLocations();

    if (!Settings::Enemizer) {
        return;
    }

    for (auto& scene : enemyLocations) {
        for (auto& layer : scene.second) {
            for (auto& room : layer.second) {
                for (auto& entry : room.second) {
                    EnemyLocation& loc = entry.second;
                    u8 enemyMode       = Settings::enemizerListOptions.at(loc.vanillaEnemyId)->GetSelectedOptionIndex();
                    if (enemyMode != ENEMYMODE_VANILLA) {
                        AssignRandomEnemy(loc);
                    }
                }
            }
        }
    }
    AddDuplicateLocations();
}

void FillPatchOverrides(std::vector<EnemyOverride>& enemyOverrides) {
    for (auto& scene : enemyLocations) {
        for (auto& layer : scene.second) {
            for (auto& room : layer.second) {
                for (auto& entry : room.second) {
                    if (entry.second.randomizedEnemyId == 0) {
                        // Location is not randomized (due to Enemy Type setting being Vanilla)
                        continue;
                    }
                    EnemyType& enemyType = enemyTypes[entry.second.randomizedEnemyId];
                    if (enemyType.actorId != 0) {
                        EnemyOverride ovr;
                        ovr.scene      = scene.first;
                        ovr.layer      = layer.first;
                        ovr.room       = room.first;
                        ovr.actorEntry = entry.first;
                        ovr.actorId    = enemyType.actorId;
                        ovr.params     = entry.second.randomizedParams;
                        enemyOverrides.push_back(ovr);
                    }
                }
            }
        }
    }

    std::sort(enemyOverrides.begin(), enemyOverrides.end(),
              [](const EnemyOverride& a, const EnemyOverride& b) { return a.key < b.key; });

    if (enemyOverrides.size() > ENEMY_OVERRIDES_MAX) {
        printf("ENEMIZER ERROR!");
        CitraPrint("ENEMIZER ERROR: Too many Enemy Overrides (" + std::to_string(enemyOverrides.size()) + ")");
        enemyOverrides.clear();
    }
}

} // namespace Enemizer
