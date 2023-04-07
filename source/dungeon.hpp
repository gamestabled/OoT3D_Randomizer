#pragma once

#include <3ds.h>
#include <array>
#include <string>
#include <vector>

#include "keys.hpp"

namespace Dungeon {
class DungeonInfo {
  public:
    DungeonInfo(std::string name_, HintKey hintKey, ItemKey map_, ItemKey compass_, ItemKey smallKey_, ItemKey keyRing_,
                ItemKey bossKey_, u8 vanillaKeyCount_, u8 mqKeyCount_, std::vector<LocationKey> vanillaLocations_,
                std::vector<LocationKey> mqLocations_, std::vector<LocationKey> sharedLocations_,
                std::vector<LocationKey> bossRoomLocations_);
    ~DungeonInfo();

    const std::string& GetName() const {
        return name;
    }

    void SetMQ() {
        masterQuest = true;
    }

    void ClearMQ() {
        masterQuest = false;
    }

    bool IsMQ() const {
        return masterQuest;
    }

    void SetKeyRing() {
        hasKeyRing = true;
    }

    void ClearKeyRing() {
        hasKeyRing = false;
    }

    bool HasKeyRing() const {
        return hasKeyRing;
    }

    bool IsVanilla() const {
        return !masterQuest;
    }

    u8 GetSmallKeyCount() const {
        return (masterQuest) ? mqKeyCount : vanillaKeyCount;
    }

    HintKey GetHintKey() const;
    ItemKey GetSmallKey() const;
    ItemKey GetKeyRing() const;
    ItemKey GetMap() const;
    ItemKey GetCompass() const;
    ItemKey GetBossKey() const;

    void PlaceVanillaMap();
    void PlaceVanillaCompass();
    void PlaceVanillaBossKey();
    void PlaceVanillaSmallKeys();

    // Gets the chosen dungeon locations for a playthrough (so either MQ or Vanilla)
    std::vector<LocationKey> GetDungeonLocations() const;

    // Gets all dungeon locations (MQ + Vanilla)
    std::vector<LocationKey> GetEveryLocation() const;

  private:
    std::string name;
    HintKey hintKey;
    ItemKey map;
    ItemKey compass;
    ItemKey smallKey;
    ItemKey keyRing;
    ItemKey bossKey;
    u8 vanillaKeyCount;
    u8 mqKeyCount;
    bool masterQuest = false;
    bool hasKeyRing  = false;
    std::vector<LocationKey> vanillaLocations;
    std::vector<LocationKey> mqLocations;
    std::vector<LocationKey> sharedLocations;
    std::vector<LocationKey> bossRoomLocations;
};

extern DungeonInfo DekuTree;
extern DungeonInfo DodongosCavern;
extern DungeonInfo JabuJabusBelly;
extern DungeonInfo ForestTemple;
extern DungeonInfo FireTemple;
extern DungeonInfo WaterTemple;
extern DungeonInfo SpiritTemple;
extern DungeonInfo ShadowTemple;
extern DungeonInfo BottomOfTheWell;
extern DungeonInfo IceCavern;
extern DungeonInfo GerudoTrainingGrounds;
extern DungeonInfo GanonsCastle;

using DungeonArray = std::array<DungeonInfo*, 12>;

extern const DungeonArray dungeonList;
} // namespace Dungeon
