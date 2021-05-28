#pragma once

#include <3ds.h>
#include <array>
#include <string>
#include <vector>

class Item;
class ItemLocation;

namespace Dungeon {
class DungeonInfo {
public:
    DungeonInfo(std::string name_, u32 map_, u32 compass_,
                u32 smallKey_, u32 bossKey_, u8 vanillaKeyCount_, u8 mqKeyCount_,
                std::vector<u32> vanillaLocations_,
                std::vector<u32> mqLocations_,
                std::vector<u32> sharedLocations_);
    ~DungeonInfo();

    std::string_view GetName() const {
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

    bool IsVanilla() const {
        return !masterQuest;
    }

    u8 GetSmallKeyCount() const {
        return (masterQuest) ? mqKeyCount : vanillaKeyCount;
    }

    u32 GetSmallKey() const;
    u32 GetMap() const;
    u32 GetCompass() const;
    u32 GetBossKey() const;

    void PlaceVanillaMap();
    void PlaceVanillaCompass();
    void PlaceVanillaBossKey();
    void PlaceVanillaSmallKeys();

    // Gets the chosen dungeon locations for a playthrough (so either MQ or Vanilla)
    std::vector<u32> GetDungeonLocations() const;

    // Gets all dungeon locations (MQ + Vanilla)
    std::vector<u32> GetEveryLocation() const;

private:
    std::string name;
    u32 map;
    u32 compass;
    u32 smallKey;
    u32 bossKey;
    u8 vanillaKeyCount;
    u8 mqKeyCount;
    bool masterQuest = false;
    std::vector<u32> vanillaLocations;
    std::vector<u32> mqLocations;
    std::vector<u32> sharedLocations;
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
